// Run_Barcode_Works.cpp : implementation file
//

#include "stdafx.h"
#include "handler.h"
#include "Run_Barcode_Works.h"

#include "AMTRegistry.h"
#include "SrcPart/APartRobot.h"
#include "SrcPart/APartHandler.h"
#include "SrcPart/APartTestSite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRun_Barcode_Works

IMPLEMENT_SERIAL(CRun_Barcode_Works, CObject, 1)
CRun_Barcode_Works g_Run_Barcode_Works;
CRun_Barcode_Works::CRun_Barcode_Works()
{
	Thread_Variable_Initial();
}

CRun_Barcode_Works::~CRun_Barcode_Works()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRun_Barcode_Works message handlers
void CRun_Barcode_Works::Thread_Variable_Initial()
{
	mn_InitStep = 0;
	mn_RunStep = 0;
	mn_RestoreStep = 0;

}

void CRun_Barcode_Works::Thread_Run()
{
// return;
																				
	if( Func.OnIsInterruptCondition() != 1 )
		return;

// 	st_handler.n_only_work_bcr1 = CTL_YES;
	switch (COMI.mn_run_status)
	{
	case dINIT:
		Run_Initial();
		break;
		
	case dRUN:
// 		return;
 		Run_Move1();
		Run_Move2();
		break;
	
	case dREINSTATE:
		Run_Reinstate();
// 		Run_Reinstate2();
		break;

	case dRESTORE:
		Run_Restore();
		break;
		
	default:
		if (st_handler.mn_menu_num != 501)
		{
			
		}
		
		break;
	}


	Run_Move_Box_UpDn();
	for ( int i = 0; i < 2; i++ )
	{
		Run_Move_M_Top_Vacuum( i );
		Run_Move_M_Btm_Vacuum( i );
		Run_Move_M_RollerFwdBwd(i);
	}

	for ( int j = 0; j < 2; j++ )
	{
		Run_Move_RollerFwdBwd( j );
	}

}


void CRun_Barcode_Works::Run_Initial()
{
	if( st_handler.mn_init_state[INIT_BARCODE_ROBOT] != CTL_NO )	return;

	switch(mn_InitStep)
	{
	case EBCRI_START: mn_InitStep = EBCRI_CHECK_ROBOT_CHK; break;

	case EBCRI_CHECK_ROBOT_CHK: EBCRI_Check_Rbot_Chk(); break;

	case EBCRI_HOMECHK_RBT1_Z1: EBCRI_HomeCheck_Z( M_BCR_ATTACH1_Z1 ); break;
	case EBCRI_HOMECHK_RBT1_Z2: EBCRI_HomeCheck_Z( M_BCR_ATTACH1_Z2 ); break;

	case EBCRI_TOP_VACUUM_BWD: EBCRI_Top_Vacuum_Backward(); break;
	case EBCRI_TOP_VACUUM_BWD_CHK: EBCRI_Top_Vacuum_Backward_Check(); break;

	case EBCRI_BTM_VACUUM_BWD: EBCRI_Btm_Vacuum_Backward(); break;
	case EBCRI_BTM_VACUUM_BWD_CHK: EBCRI_Btm_Vacuum_Backward_Check(); break;

	case EBCRI_VACUUM_ON: 
		EBCRI_VacuumOnOff(IO_ON); 
		m_dwTimeInit = GetCurrentTime();
		break;
	case EBCRI_BARCODE_EMPTY_CHK: 
		if( GetCurrentTime() - m_dwTimeInit < 0 ) m_dwTimeInit = GetCurrentTime();
		else if( GetCurrentTime() - m_dwTimeInit < st_time.n_wait_time[E_WAIT_BCR_VACUUM][IO_ON]) break;
		EBCRI_Barcode_Empty_Check(); break;

	case EBCRI_VACUUM_OFF: EBCRI_VacuumOnOff(IO_OFF); break;
	case EBCRI_EJECT_ON: 
		EBCRI_EjectOnOff(IO_ON); 
		m_dwTimeInit = GetCurrentTime();
		break;
	case EBCRI_EJECT_OFF: 
		if( GetCurrentTime() - m_dwTimeInit < 0 ) m_dwTimeInit = GetCurrentTime();
		else if( GetCurrentTime() - m_dwTimeInit < st_time.n_wait_time[E_WAIT_BCR_EJECT][IO_ON]) break;
		EBCRI_EjectOnOff(IO_OFF); break;

	case EBCRI_HOMECHK_RBT1_X: EBCRI_HomeCheck_X(M_BCR_ATTACH1_X); break;
	case EBCRI_HOMECHK_RBT1_Y: EBCRI_HomeCheck_Y(M_BCR_ATTACH1_Y); break;

	case EBCRI_MOVE_SAFETY_RBT1_X: EBCRI_Move_Safety_X(M_BCR_ATTACH1_X); break;

	case EBCRI_BOX_SAFETY:
		ReqBoxUpDn(BACKWARD);
		mn_InitStep = EBCRI_BOX_SAFETY_CHK;

		break;

	case EBCRI_BOX_SAFETY_CHK:
		if(m_fbboxupdn != FB_NONE ) break;
		if(m_fbboxupdn != FB_NONE ) break;
		if( CheckBoxUpDn( IO_OFF) != true)
		{
			CString strJamCode;
			if( CheckBoxUpDn( IO_OFF) != true )
				strJamCode.Format("5%04d%d", st_io.i_top_box_up_clamp_chk, IO_OFF);
			else
				strJamCode.Format("5%04d%d", st_io.i_top_box_up_clamp_chk, IO_OFF);
			CTL_Lib.Alarm_Error_Occurrence( 1373, dWARNING, strJamCode );
			break;
		}
		mn_InitStep = EBCRI_BOX_ROTATE;
		break;

	case EBCRI_BOX_ROTATE:
		ReqMRotateFwdBwd( 0 ,BACKWARD);
		ReqMRotateFwdBwd( 1 ,BACKWARD);
		mn_InitStep = EBCRI_BOX_ROTATE_CHK;
		break;

	case EBCRI_BOX_ROTATE_CHK:
		if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
		if( m_fbmrotatefwdbwd[1] != FB_NONE) break;

		mn_InitStep = EBCRI_FINISH;
		break;

	case EBCRI_FINISH: EBCRI_Finish(); break;


	}

}

void CRun_Barcode_Works::EBCRI_Check_Rbot_Chk()
{
	if( st_handler.mn_init_state[INIT_ROLLER_ROBOT] != CTL_NO ) return;
	mn_InitStep = EBCRI_HOMECHK_RBT1_Z1;
}

void CRun_Barcode_Works::EBCRI_HomeCheck_Z( int nAxis )
{	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);
	if( nRet == BD_GOOD )
	{
		if( nAxis == M_BCR_ATTACH1_Z1)
		{
			mn_InitStep = EBCRI_HOMECHK_RBT1_Z2;
			Func.OnInitBtn( RBTN_BCR_ATTACH1_Z1 );//2014.1018
		}
		else if( nAxis == M_BCR_ATTACH1_Z2)
		{
			mn_InitStep = EBCRI_TOP_VACUUM_BWD;
			Func.OnInitBtn( RBTN_BCR_ATTACH1_Z2 );//2014.1018
		}
	}
	else if( nRet == BD_ERROR )
	{//180001 0 00 "Distribute#1 Attach Z#1 Axis Motor Home Check Error."
		//200001 0 00 "Distribute#1 Attach Z#2 Axis Motor Home Check Error."
		//230001 0 00 "Distribute#2 Attach Z#1 Axis Motor Home Check Error."
		//250001 0 00 "Distribute#2 Attach Z#2 Axis Motor Home Check Error."
	
		//2016.0722
// 		CString strJamCode = "180001";
// 		if	   ( nAxis == M_BCR_ATTACH1_Z2) strJamCode = "200001";
		CString strJamCode = "100001";
		if	   ( nAxis == M_BCR_ATTACH1_Z2) strJamCode = "110001";
		CTL_Lib.Alarm_Error_Occurrence(200, CTL_dWARNING, strJamCode );
	}

}

void CRun_Barcode_Works::EBCRI_HomeCheck_X( int nAxis )
{
	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);

	if( nRet == BD_GOOD )
	{
		if(nAxis == M_BCR_ATTACH1_X)
		{
//			Func.OnInitBtn( RBTN_BCR_ATTACH1_X );//2014.1018
			Func.OnInitBtn( RBTN_BCR_ATTACH1_R1 );//2014.1018
			Func.OnInitBtn( RBTN_BCR_ATTACH1_R2 );//2014.1018
			mn_InitStep = EBCRI_HOMECHK_RBT1_Y;
		}
	}
	else if( nRet == BD_ERROR )
	{//170001 0 00 "Distribute#1 Attach X Axis Motor Home Check Error."
		//220001 0 00 "Distribute#2 Attach X Axis Motor Home Check Error."
		CString strJamCode = "080001";
		CTL_Lib.Alarm_Error_Occurrence(201, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::EBCRI_HomeCheck_Y( int nAxis )
{
	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);
	
	if( nRet == BD_GOOD )
	{
		if(nAxis == M_BCR_ATTACH1_Y)
		{
			//			Func.OnInitBtn( RBTN_BCR_ATTACH1_X );//2014.1018
			Func.OnInitBtn( RBTN_BCR_ATTACH1_R1 );//2014.1018
			Func.OnInitBtn( RBTN_BCR_ATTACH1_R2 );//2014.1018
			mn_InitStep = EBCRI_MOVE_SAFETY_RBT1_X;
		}
	}
	else if( nRet == BD_ERROR )
	{//170001 0 00 "Distribute#1 Attach X Axis Motor Home Check Error."
		//220001 0 00 "Distribute#2 Attach X Axis Motor Home Check Error."
		CString strJamCode = "090001";
		CTL_Lib.Alarm_Error_Occurrence(201, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::EBCRI_Move_Safety_X( int nAxis )
{
	int nRet = CTL_Lib.Single_Move( nAxis, st_motor[nAxis].d_pos[P_X_BCR_SAFETY], st_basic.nManualSpeed);
	
	if( nRet == BD_GOOD )
	{
		if(nAxis == M_BCR_ATTACH1_X)
		{
			mn_InitStep = EBCRI_BOX_SAFETY;
			Func.OnInitBtn( RBTN_BCR_ATTACH1_X );
		}
	}
	else if( nRet == BD_ERROR )
	{//000006 1 00 "Density_Feeder1_Axis_Motor_Move_Error."
	//	CString strJamCode = "170006"; //2016.0722
		CString strJamCode = "080006";
		CTL_Lib.Alarm_Error_Occurrence(298, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::EBCRI_HomeCheck_R( int nAxis)
{
	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);
	if( nRet == BD_GOOD )
	{
		mn_InitStep = EBCRI_HOMECHK_RBT1_R2;

//		Func.OnInitBtn( RBTN_SITE1_Z + (m_nSiteID - INIT_TEST_SITE_1 ) * 5 );
	}
	else if( nRet == BD_ERROR )
	{//040001 0 00 "Distribute#1 Attach R#1 Axis Motor Home Check Error." //2016.0722
		//210001 0 00 "Distribute#1 Attach R#2 Axis Motor Home Check Error."
		//240001 0 00 "Distribute#2 Attach R#1 Axis Motor Home Check Error."
		//260001 0 00 "Distribute#2 Attach R#2 Axis Motor Home Check Error."

		//CString strJamCode = "190001";
		CString strJamCode = "040001"; //2016.0722
		CTL_Lib.Alarm_Error_Occurrence(206, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::EBCRI_VacuumOnOff(int iOnOff)
{
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_left_top_vacuum , iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_right_top_vacuum, iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_left_top_vacuum , iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_right_top_vacuum, iOnOff );

	if( iOnOff == IO_ON)
	{
		mn_InitStep = EBCRI_BARCODE_EMPTY_CHK;
		m_dwTimeInit = GetCurrentTime();
	}
	else
	{
		mn_InitStep = EBCRI_EJECT_ON;
	}
}

void CRun_Barcode_Works::EBCRI_Barcode_Empty_Check()
{
//515081 1 00 "Distribution Label Robot1 Left Top Vacuum On Check Error."
//515091 1 00 "Distribution Label Robot1 Left Bottom Vacuum On Check Error."
//516081 1 00 "Distribution Label Robot1 Right Top Vacuum On Check Error."
//516091 1 00 "Distribution Label Robot1 Right Bottom Vacuum On Check Error."
//520081 1 00 "Distribution Label Robot2 Left Top Vacuum On Check Error."
//520091 1 00 "Distribution Label Robot2 Left Bottom Vacuum On Check Error."
//521081 1 00 "Distribution Label Robot2 Right Top Vacuum On Check Error."
//521091 1 00 "Distribution Label Robot2 Right Bottom Vacuum On Check Error."
	if( GetCurrentTime() - m_dwTimeInit <= 0 ) m_dwTimeInit = GetCurrentTime();
	if( GetCurrentTime() - m_dwTimeInit < st_time.n_wait_time[E_WAIT_BCR_PICK_VACUUM][1] ) return;

	if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_left_top_vacuum_chk ) == IO_ON )
	{
		CTL_Lib.Alarm_Error_Occurrence( 210, dWARNING, "515031" );
		return;
	}
	else if(g_ioMgr.get_in_bit( st_io.i_distribute_rbt_right_top_vacuum_chk ) == IO_ON)
	{
		CTL_Lib.Alarm_Error_Occurrence( 212, dWARNING, "515081" );
		return;
	}

	mn_InitStep = EBCRI_VACUUM_OFF;
}

void CRun_Barcode_Works::EBCRI_EjectOnOff( int iOnOff )
{
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_left_top_eject, iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_left_btm_eject, iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_right_top_eject, iOnOff );
	g_ioMgr.set_out_bit( st_io.o_distribute_rbt_right_btm_eject, iOnOff );

	if( iOnOff == IO_ON) mn_InitStep = EBCRI_EJECT_OFF;
	else				 mn_InitStep = EBCRI_HOMECHK_RBT1_X;

}

void CRun_Barcode_Works::EBCRI_Top_Vacuum_Backward()
{
	ReqMTopVac( EBVS_LEFT , BACKWARD );
	ReqMTopVac( EBVS_RIGHT, BACKWARD );	
	mn_InitStep = EBCRI_TOP_VACUUM_BWD_CHK;
}

void CRun_Barcode_Works::EBCRI_Top_Vacuum_Backward_Check()
{
	if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) return;
	if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) return;

	mn_InitStep = EBCRI_BTM_VACUUM_BWD;
}

void CRun_Barcode_Works::EBCRI_Btm_Vacuum_Backward()
{
	ReqMBtmVac( EBVS_LEFT , BACKWARD );
	ReqMBtmVac( EBVS_RIGHT, BACKWARD );
	//2015.0206
	//ReqM2BtmVac( EBVS_RIGHT, BACKWARD );
	mn_InitStep = EBCRI_BTM_VACUUM_BWD_CHK;

}

void CRun_Barcode_Works::EBCRI_Btm_Vacuum_Backward_Check()
{
	if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) return;
	if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) return;
	//2015.0206
	//if( GetM2BtmVac( EBVS_RIGHT ) != FB_NONE ) return;

	mn_InitStep = EBCRI_VACUUM_ON;
}

void CRun_Barcode_Works::ReqBoxUpDn( EFB efb)
{
	m_fbboxupdn = efb;
	m_step_box_updn = ESTEP_CYL_START;
}

void CRun_Barcode_Works::ReqMTopVac( int nSite, EFB efb )
{
	m_fbmtopvac[nSite] = efb;
	m_step_mtopvac[nSite] = ESTEP_CYL_START;	
}

void CRun_Barcode_Works::ReqMBtmVac( int nSite, EFB efb )
{
	m_fbmbtmvac[nSite] = efb;
	m_step_mbtmvac[nSite] = ESTEP_CYL_START;
}



void CRun_Barcode_Works::ReqRollingFwdBwd( int pos, EFB efb )
{
	m_fbrollingfwdbwd[pos] = efb;
	m_step_rolling_fwdbwd[pos] = ESTEP_CYL_START;
}

void CRun_Barcode_Works::SetMTopVac( int nSite, int iOnOff )
{
	int nVac_1 = st_io.o_distribute_rbt_top_vacuum_fwdback[nSite];
	
	g_ioMgr.set_out_bit( nVac_1, iOnOff);
}

void CRun_Barcode_Works::SetMBtmVac( int nSite, int iOnOff )
{
	int nVac_1 = st_io.o_distribute_rbt_btm_vacuum_fwdback[nSite];
	g_ioMgr.set_out_bit( nVac_1, iOnOff);
}


bool CRun_Barcode_Works::CheckMTopVac( int nSite, int iOnOff )
{
	int nLock_2 = st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite];

	if( g_ioMgr.get_in_bit( nLock_2 ) != !iOnOff) return false;

	return true;
}

bool CRun_Barcode_Works::CheckMBtmVac( int nSite, int iOnOff )
{
	int nLock_2 = st_io.i_distribute_rbt_btm_vacuum_bwd_chk[nSite];

	if( g_ioMgr.get_in_bit( nLock_2 ) != !iOnOff) return false;

	return true;
}


void CRun_Barcode_Works::SetBoxUpDn( int iOnOff )
{
	int nfwd = st_io.o_top_box_up_clamp;
	int nbwd = st_io.o_top_box_dn_clamp;

	g_ioMgr.set_out_bit( nfwd, iOnOff);
	g_ioMgr.set_out_bit( nbwd, !iOnOff);
}

bool CRun_Barcode_Works::CheckBoxUpDn( int iOnOff )
{
	int ifwd = st_io.i_top_box_up_clamp_chk ;
	int ibwd = st_io.i_top_box_dn_clamp_chk;

	if( g_ioMgr.get_in_bit( ifwd ) != iOnOff) return false;
	if( g_ioMgr.get_in_bit( ibwd ) != !iOnOff) return false;

	return true;
}

void CRun_Barcode_Works::Run_Move_Box_UpDn()
{
	if( m_fbboxupdn == FB_NONE ) return;

	int iOnOff = IO_ON;
	if( m_fbboxupdn == BACKWARD )
		iOnOff = IO_OFF;

	switch(m_step_box_updn)
	{
	case ESTEP_CYL_START: 
		m_step_box_updn = ESTEP_CYL_MOVE; 
		mn_retry_cnt = 0;//2015.0218
		break;

	case 5:
		{
			if( GetCurrentTime() - m_dwTimeBoxupdnStart > st_time.n_limit_time[E_WAIT_BCR_GUIDE_FWDBWD] )
			{
				m_step_box_updn = ESTEP_CYL_MOVE;
			}
			else if( GetCurrentTime() - m_dwTimeBoxupdn <= 0 )
			{
				m_dwTimeBoxupdn = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_MOVE:
		{
			SetBoxUpDn( iOnOff );
			if(COMI.mn_run_status == dRUN){
				st_work.mn_bcr_box_updn = iOnOff;
			}
			m_step_box_updn = ESTEP_CYL_CHK;
			m_dwTimeBoxupdnStart = GetCurrentTime();
		}
		break;


	case ESTEP_CYL_CHK:
		{
			if(CheckBoxUpDn(iOnOff))
			{
				m_step_box_updn = ESTEP_CYL_FINISH;
				m_dwTimeBoxupdn = GetCurrentTime();
			}
			else if( GetCurrentTime() - m_dwTimeBoxupdnStart > (DWORD)st_time.n_limit_time[E_WAIT_BCR_GUIDE_FWDBWD] )
			{
				if(COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
				{
					////2015.0218
// 					CString strJamCode;
// 					strJamCode.Format("5%04d%d", st_io.i_top_box_up_clamp_chk[nSite], iOnOff);
// 					CTL_Lib.Alarm_Error_Occurrence( 219, dWARNING, strJamCode );
 
					mn_retry_cnt++;
					if(mn_retry_cnt > st_basic.mn_network_retry_cnt)
					{
						mn_retry_cnt = 0;

						CString strJamCode;
						strJamCode.Format("5%04d%d", st_io.i_top_box_up_clamp_chk, iOnOff);
						CTL_Lib.Alarm_Error_Occurrence( 219, dWARNING, strJamCode );
					}
					else
					{
						SetBoxUpDn( !iOnOff );
						m_dwTimeBoxupdn = GetCurrentTime();
						m_step_box_updn = ENUM_STEP_CYL(5);
					}
					////
				}
			}
			else if( GetCurrentTime() - m_dwTimeBoxupdn <= 0 )
			{
				m_dwTimeBoxupdn = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_FINISH:
		{
			if( GetCurrentTime() - m_dwTimeBoxupdn < 0 ) m_dwTimeBoxupdn = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeBoxupdn < st_time.n_wait_time[E_WAIT_BCR_GUIDE_FWDBWD][iOnOff] )
				return;

			m_step_box_updn = ESTEP_CYL_START;
			m_fbboxupdn = FB_NONE;
		}
		break;
	}
}

void CRun_Barcode_Works::Run_Move_M_Top_Vacuum( int nSite)
{
	if(m_fbmtopvac[nSite] == FB_NONE) return;
	int iOnOff = IO_ON;
	if( m_fbmtopvac[nSite] == BACKWARD)
		iOnOff = IO_OFF;

	switch(m_step_mtopvac[nSite])
	{
	case ESTEP_CYL_START: m_step_mtopvac[nSite] = ESTEP_CYL_MOVE;	break;
	case ESTEP_CYL_MOVE:
		{
			SetMTopVac( nSite, iOnOff);
			if(COMI.mn_run_status == dRUN){
				st_work.mn_bcr_m1top_vac_fwdback[nSite] = iOnOff;
			}
			m_step_mtopvac[nSite] = ESTEP_CYL_CHK;
			m_dwTimeMTopVacStart[nSite] = GetCurrentTime();
		}
		break;

	case ESTEP_CYL_CHK:
		{
			if( st_handler.mn_virtual_mode == 1 || CheckMTopVac( nSite, iOnOff ) )
			{
				m_step_mtopvac[nSite] = ESTEP_CYL_FINISH;
				m_dwTimeMTopVac[nSite] = GetCurrentTime();
			}
			else if( GetCurrentTime() - m_dwTimeMTopVacStart[nSite] > st_time.n_limit_time[E_WAIT_BCR_VACUUM_FWDBWD] )
			{
				if( COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
				{
					CString strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite], iOnOff );
					CTL_Lib.Alarm_Error_Occurrence( 220, dWARNING, strJamCode );
				}
			}
			else if( GetCurrentTime() - m_dwTimeMTopVacStart[nSite] < 0 )
			{
				m_dwTimeMTopVacStart[nSite] = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_FINISH:
		{
			if( GetCurrentTime() - m_dwTimeMTopVac[nSite] < 0 )
				m_dwTimeMTopVac[nSite] = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeMTopVac[nSite] < st_time.n_wait_time[E_WAIT_BCR_VACUUM_FWDBWD][iOnOff] )
				return;

			m_step_mtopvac[nSite] = ESTEP_CYL_START;
			m_fbmtopvac[nSite] = FB_NONE;
		}
		break;	
	}

}


void CRun_Barcode_Works::Run_Move_M_Btm_Vacuum( int nSite)
{
	if(m_fbmbtmvac[nSite] == FB_NONE) return;
	int iOnOff = IO_ON;
	if( m_fbmbtmvac[nSite] == BACKWARD)
		iOnOff = IO_OFF;

	switch(m_step_mbtmvac[nSite])
	{
	case ESTEP_CYL_START: m_step_mbtmvac[nSite] = ESTEP_CYL_MOVE;	break;
	case ESTEP_CYL_MOVE:
		{
			SetMBtmVac( nSite, iOnOff);
			if(COMI.mn_run_status == dRUN){
				st_work.mn_bcr_m1btm_vac_fwdback[nSite] = iOnOff;
			}
			m_step_mbtmvac[nSite] = ESTEP_CYL_CHK;
			m_dwTimeMBtmVacStart[nSite] = GetCurrentTime();
		}
		break;

	case ESTEP_CYL_CHK:
		{
			if( st_handler.mn_virtual_mode == 1 || CheckMBtmVac( nSite, iOnOff ) )
			{
				m_step_mbtmvac[nSite] = ESTEP_CYL_FINISH;
				m_dwTimeMBtmVac[nSite] = GetCurrentTime();
			}
			else if( GetCurrentTime() - m_dwTimeMBtmVacStart[nSite] > st_time.n_limit_time[E_WAIT_BCR_VACUUM_FWDBWD] )
			{
				if( COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
				{
					CString strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[nSite], iOnOff );
					CTL_Lib.Alarm_Error_Occurrence( 297, dWARNING, strJamCode );
					if(st_var.n_tboxmv_forming_cv_mode == CTL_YES)
					{
						SetMBtmVac( nSite, IO_OFF);//2015.0915
						st_var.n_tboxmv_forming_cv_mode = CTL_NO;
						m_step_mbtmvac[nSite] = ESTEP_CYL_FINISH;//2015.0331
					}
				}
			}
			else if( GetCurrentTime() - m_dwTimeMBtmVacStart[nSite] < 0 )
			{
				m_dwTimeMBtmVacStart[nSite] = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_FINISH:
		{
			if( GetCurrentTime() - m_dwTimeMBtmVac[nSite] < 0 )
				m_dwTimeMBtmVac[nSite] = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeMBtmVac[nSite] < st_time.n_wait_time[E_WAIT_BCR_VACUUM_FWDBWD][iOnOff] )
				return;

			m_step_mbtmvac[nSite] = ESTEP_CYL_START;
			m_fbmbtmvac[nSite] = FB_NONE;
		}
		break;	
	}

}

void CRun_Barcode_Works::SetRollingFwdBwd( int pos, int iOnOff )
{
	int nRoll = st_io.o_rolling_push_fwdback[pos];

	g_ioMgr.set_out_bit( nRoll, iOnOff);
}

bool CRun_Barcode_Works::CheckRollingFwdBwd( int nPos, int iOnOff )
{
	int nRoll_1 = st_io.i_rolling_push_fwd_chk[nPos];
	int nRoll_3 = st_io.i_rolling_push_bwd_chk[nPos];

	if( g_ioMgr.get_in_bit( nRoll_1 ) != iOnOff) return false;
	if( g_ioMgr.get_in_bit( nRoll_3 ) != !iOnOff) return false;

	return true;
}

//void CRun_Barcode_Works::Run_Move_RollerFwdBwd(int nSite)
//{
//	if(m_fbrollingfwdbwd[nSite] == FB_NONE) return;//2014.1018 FU_NONE -> FB_NONE
//	
//	int iOnOff = IO_ON;
//	
//	if( m_fbrollingfwdbwd[nSite] == BACKWARD)
//		iOnOff = IO_OFF;
//
//	switch(m_step_rolling_fwdbwd[nSite])
//	{
//	case ESTEP_CYL_START: m_step_rolling_fwdbwd[nSite] = ESTEP_CYL_MOVE;	break;
//	case ESTEP_CYL_MOVE:
//		{
//			SetRollingFwdBwd( nSite, iOnOff);
//			if(COMI.mn_run_status == dRUN){
//				st_work.mn_rolling_fwdback[nSite] = iOnOff;
//			}
//			m_step_rolling_fwdbwd[nSite] = ESTEP_CYL_CHK;
//			m_dwTimeRollingFwdBwdStart[nSite] = GetCurrentTime();
//		}
//		break;
//
//	case ESTEP_CYL_CHK:
//		{
//			if( st_handler.mn_virtual_mode == 1 || CheckRollingFwdBwd( nSite, iOnOff ) )
//			{
//				m_step_rolling_fwdbwd[nSite] = ESTEP_CYL_FINISH;
//				m_dwTimeRollingFwdBwd[nSite] = GetCurrentTime();
//			}
//			else if( GetCurrentTime() - m_dwTimeRollingFwdBwdStart[nSite] > st_time.n_limit_time[E_WAIT_ROLLING_FWDBWD] )
//			{
//				if( COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
//				{
//					CString strJamCode = GetJamCode_Rolling_FwdBwd_Time(st_io.i_rolling_push_fwd_chk[nSite][ERLP_LEFT], iOnOff );
//					CTL_Lib.Alarm_Error_Occurrence( 225, dWARNING, strJamCode );
//				}
//			}
//			else if( GetCurrentTime() - m_dwTimeRollingFwdBwdStart[nSite] < 0 )
//			{
//				m_dwTimeRollingFwdBwdStart[nSite] = GetCurrentTime();
//			}
//		}
//		break;
//
//	case ESTEP_CYL_FINISH:
//		{
//			if( GetCurrentTime() - m_dwTimeRollingFwdBwd[nSite] < 0 )
//				m_dwTimeRollingFwdBwd[nSite] = GetCurrentTime();
//			else if( GetCurrentTime() - m_dwTimeRollingFwdBwd[nSite] < st_time.n_wait_time[E_WAIT_ROLLING_FWDBWD][iOnOff] )
//				return;
//
//			m_step_rolling_fwdbwd[nSite] = ESTEP_CYL_START;
//			m_fbrollingfwdbwd[nSite] = FB_NONE;
//		}
//		break;	
//	}
//}

void CRun_Barcode_Works::Run_Move_RollerFwdBwd( int nPos)
{
	if(m_fbrollingfwdbwd[nPos] == FB_NONE) return;
	
	int iOnOff = IO_ON;
	
	if( m_fbrollingfwdbwd[nPos] == BACKWARD)
		iOnOff = IO_OFF;

	switch(m_step_rolling_fwdbwd[nPos])
	{
	case ESTEP_CYL_START: m_step_rolling_fwdbwd[nPos] = ESTEP_CYL_MOVE;	break;
	case ESTEP_CYL_MOVE:
		{
			SetRollingFwdBwd( nPos, iOnOff);
			if(COMI.mn_run_status == dRUN){
				st_work.mn_rolling_fwdback[nPos] = iOnOff;
			}
			m_step_rolling_fwdbwd[nPos] = ESTEP_CYL_CHK;
			m_dwTimeRollingFwdBwdStart[nPos] = GetCurrentTime();
		}
		break;

	case ESTEP_CYL_CHK:
		{
			if( st_handler.mn_virtual_mode == 1 || CheckRollingFwdBwd( nPos, iOnOff ) )
			{
				m_step_rolling_fwdbwd[nPos] = ESTEP_CYL_FINISH;
				m_dwTimeRollingFwdBwd[nPos] = GetCurrentTime();
			}
			else if( GetCurrentTime() - m_dwTimeRollingFwdBwdStart[nPos] > st_time.n_limit_time[E_WAIT_ROLLING_FWDBWD] )
			{
				if( COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
				{
					CString strJamCode = GetJamCode_Rolling_FwdBwd_Time(st_io.i_rolling_push_fwd_chk[nPos], iOnOff );
					CTL_Lib.Alarm_Error_Occurrence( 225, dWARNING, strJamCode );
				}
			}
			else if( GetCurrentTime() - m_dwTimeRollingFwdBwdStart[nPos] < 0 )
			{
				m_dwTimeRollingFwdBwdStart[nPos] = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_FINISH:
		{
			if( GetCurrentTime() - m_dwTimeRollingFwdBwd[nPos] < 0 )
				m_dwTimeRollingFwdBwd[nPos] = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeRollingFwdBwd[nPos] < st_time.n_wait_time[E_WAIT_ROLLING_FWDBWD][iOnOff] )
				return;

			m_step_rolling_fwdbwd[nPos] = ESTEP_CYL_START;
			m_fbrollingfwdbwd[nPos] = FB_NONE;
		}
		break;	
	}
}

void CRun_Barcode_Works::ReqMRotateFwdBwd( int nSite, EFB efb)
{
	m_fbmrotatefwdbwd[nSite] = efb;
	m_step_mrotate_fwdbwd[nSite] = ESTEP_CYL_START;
}

void CRun_Barcode_Works::SetMRotateFwdBwd( int nSite, int iOnOff )
{
	int ofwd = st_io.o_distribute_rbt_box_rotator_fwd_cylinder[nSite];
	int obwd = st_io.o_distribute_rbt_box_rotator_bwd_cylinder[nSite];

	g_ioMgr.set_out_bit( ofwd, iOnOff);
	g_ioMgr.set_out_bit( obwd, !iOnOff);
}

bool CRun_Barcode_Works::CheckMRotateFwdBwd( int nSite, int iOnOff )
{
	int nfwd = st_io.i_distribute_rbt_box_rotator_fwd_chk[nSite] ;
	int nbwd = st_io.i_distribute_rbt_box_rotator_bwd_chk[nSite];

	if( g_ioMgr.get_in_bit( nfwd ) != iOnOff) return false;
	if( g_ioMgr.get_in_bit( nbwd ) != !iOnOff) return false;

	return true;
}

void CRun_Barcode_Works::Run_Move_M_RollerFwdBwd(int nSite)
{
	if(m_fbmrotatefwdbwd[nSite] == FB_NONE) return;//2014.1018 FU_NONE -> FB_NONE
	
	int iOnOff = IO_ON;	
	if( m_fbmrotatefwdbwd[nSite] == BACKWARD)
		iOnOff = IO_OFF;

	switch(m_step_mrotate_fwdbwd[nSite])
	{
	case ESTEP_CYL_START: m_step_mrotate_fwdbwd[nSite] = ESTEP_CYL_MOVE;	break;
	case ESTEP_CYL_MOVE:
		{
			SetMRotateFwdBwd( nSite, iOnOff);
			if(COMI.mn_run_status == dRUN){
				st_work.mn_m1rotate_fwdback[nSite] = iOnOff;
			}
			m_step_mrotate_fwdbwd[nSite] = ESTEP_CYL_CHK;
			m_dwTimeMRotatefwdbwdStart[nSite] = GetCurrentTime();
		}
		break;

	case ESTEP_CYL_CHK:
		{
			if( st_handler.mn_virtual_mode == 1 || CheckMRotateFwdBwd( nSite, iOnOff ) )
			{
				m_step_mrotate_fwdbwd[nSite] = ESTEP_CYL_FINISH;
				m_dwTimeMRotatefwdbwd[nSite] = GetCurrentTime();
			}
			else if( GetCurrentTime() - m_dwTimeMRotatefwdbwdStart[nSite] > st_time.n_limit_time[E_WAIT_ROLLING_FWDBWD] )
			{
				if( COMI.mn_run_status == dRUN || COMI.mn_run_status == dINIT )
				{
					CString strErr;
					strErr.Format("5%04d%d",st_io.i_distribute_rbt_box_rotator_fwd_chk[nSite],iOnOff);
					CTL_Lib.Alarm_Error_Occurrence( 226, dWARNING, strErr );
				}
			}
			else if( GetCurrentTime() - m_dwTimeMRotatefwdbwdStart[nSite] < 0 )
			{
				m_dwTimeMRotatefwdbwdStart[nSite] = GetCurrentTime();
			}
		}
		break;

	case ESTEP_CYL_FINISH:
		{
			if( GetCurrentTime() - m_dwTimeMRotatefwdbwd[nSite] < 0 )
				m_dwTimeMRotatefwdbwd[nSite] = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeMRotatefwdbwd[nSite] < st_time.n_wait_time[E_WAIT_ROLLING_FWDBWD][iOnOff] )
				return;

			m_step_mrotate_fwdbwd[nSite] = ESTEP_CYL_START;
			m_fbmrotatefwdbwd[nSite] = FB_NONE;
		}
		break;	
	}
}


void CRun_Barcode_Works::EBCRI_Finish()
{
// 	if(m_fbboxupdn[0] != FB_NONE ) break;
// 	if(m_fbboxupdn[1] != FB_NONE ) break;

	Func.OnInitBtn( RBTN_BCR_ATTACH );//2014.1018
	st_handler.mn_init_state[INIT_BARCODE_ROBOT] = CTL_YES;
	mn_InitStep = EBCRI_START;
}

bool CRun_Barcode_Works::Run_Bcr_Move_Chk1_Jam( stJobPicker job )
{
	CString strJamCode;

	Func.ThreadFunctionStepTrace(20, job.bcr1_step);
	switch( job.bcr1_step )
	{
	case BCR1_NONE:
		break;

	case BCR1_PICK_LABEL_ROTATE_CHK:
	case BCR1_PICK_R1_SAFETY:
	case BCR1_PICK_R2_SAFETY:
	case BCR1_PICK_LABEL_MOVE_READY_POS:
	case BCR1_PICK_LABEL_MOVE_READY:
// 		if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 0, IO_OFF ) == false )		return false;
// 		if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 1, IO_OFF ) == false )		return false;
//		if( Chk_Robot1_guide_updn( 0, IO_ON ) == false )			return false;//guide up
//		if( Chk_Robot1_guide_updn( 1, IO_ON ) == false )			return false;
		break;

	case BCR1_PICK_LABEL_DOWN_CHK:
	case BCR1_PICK_LABEL_VACUUM:
	case BCR1_PICK_LABEL_UP:
	case BCR1_PICK_LABEL_VACUUM_CHK:
	case BCR1_PICK_LABEL_FINISH:
		if( /*st_basic.n_mode_device && */Chk_Robot_rollingfwdbwd( IO_OFF ) == false )			return false;
		break;

	case BCR1_PLACE_LABEL_PUSH_VACUUM:
// 		if( job.iRobotFirst != -1)
// 			if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 0, IO_ON ) == false )			return false;
// 
// 		if(st_basic.n_mode_device && job.iRobotSecond != -1)
// 			if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 1, IO_ON ) == false )			return false;
//		if( Chk_Robot1_guide_updn( 0, IO_OFF ) == false )			return false;//guide down
//		if( Chk_Robot1_guide_updn( 1, IO_OFF ) == false )			return false;
		break;

	case BCR1_PLACE_LABEL_PULL_CHK:
// 		if( job.iRobotFirst != -1)
// 			if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 0, IO_OFF ) == false )		return false;
// 		if( st_basic.n_mode_device && job.iRobotSecond != -1)
// 			if( st_basic.n_mode_device && Chk_Robot1_vacuum_fwdbwd( 1, IO_OFF ) == false )		return false;
// 		if( st_basic.n_mode_device && Chk_Robot_rollingfwdbwd( 1, IO_ON ) == false )			return false;
//		if( Chk_Robot1_guide_updn( 0, IO_ON ) == false )			return false;
//		if( Chk_Robot1_guide_updn( 1, IO_ON ) == false )			return false;
		break;

// 	case BCR1_PLACE_LABEL_SAFETY:
	case BCR1_PLACE_LABEL_FINISH:	
		if( /*st_basic.n_mode_device && */Chk_Robot_rollingfwdbwd( IO_OFF ) == false )			return false;
//		if( Chk_Robot1_guide_updn( 0, IO_ON ) == false )			return false;//guide up
//		if( Chk_Robot1_guide_updn( 1, IO_ON ) == false )			return false;
		break;
	}

	return true;
}

bool CRun_Barcode_Works::Chk_Robot1_vacuum_fwdbwd( int nSite, int iOn )
{
	if( /*g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_top_vacuum_fwd_chk[nSite], iOn ) == iOn &&*/
		g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite], !iOn ) == !iOn &&
		/*g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_btm_vacuum_fwd_chk[nSite], iOn ) == iOn &&*/
		g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[nSite], !iOn ) == !iOn)
	{
		return true;
	}

	CString strJamCode;
	strJamCode.Format("5%04d%d",st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite], iOn);
	CTL_Lib.Alarm_Error_Occurrence( 230, dWARNING, strJamCode );
	return false;
}

//bool CRun_Barcode_Works::Chk_Robot1_guide_updn( int nSite, int iOn )
//{
//	if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_box_guide_up_chk[nSite], iOn ) == iOn &&
//		g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_box_guide_down_chk[nSite], !iOn ) == !iOn)
//	{
//		return true;
//	}
//
//	CString strJamCode;
//	strJamCode.Format("5%04d%d",st_io.i_distribute_rbt1_box_guide_up_chk[nSite], iOn);
//	CTL_Lib.Alarm_Error_Occurrence( 232, dWARNING, strJamCode );
//	return false;
//}

bool CRun_Barcode_Works::Chk_Robot_rollingfwdbwd( int iOn )
{
	if( g_ioMgr.get_in_bit( st_io.i_rolling_push_fwd_chk[ERLP_LEFT], iOn ) == iOn &&
		g_ioMgr.get_in_bit( st_io.i_rolling_push_fwd_chk[ERLP_RIGHT], iOn ) == iOn  )
	{
		return true;
	}

	CString strJamCode;
	strJamCode.Format("5%04d%d",st_io.i_rolling_push_fwd_chk[ERLP_LEFT], iOn);
	CTL_Lib.Alarm_Error_Occurrence( 233, dWARNING, strJamCode );
	return false;
}



bool CRun_Barcode_Works::Chk_Robot2_vacuum_fwdbwd( int nSite, int iOn )
{
	if( /*g_ioMgr.get_in_bit( st_io.i_distribute_rbt2_top_vacuum_fwd_chk[nSite], iOn ) == iOn &&*/
		g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite], iOn ) == iOn &&
		/*g_ioMgr.get_in_bit( st_io.i_distribute_rbt2_btm_vacuum_fwd_chk[nSite], iOn ) == iOn &&*/
		g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[nSite], iOn ) == iOn)
	{
		return true;
	}

	CString strJamCode;
	strJamCode.Format("5%04d%d",st_io.i_distribute_rbt_top_vacuum_bwd_chk[nSite], iOn);
	CTL_Lib.Alarm_Error_Occurrence( 234, dWARNING, strJamCode );
	return false;
}


//bool CRun_Barcode_Works::Chk_Robot2_guide_updn( int nSite, int iOn )
//{
//	if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt2_box_guide_up_chk[nSite], iOn ) == iOn &&
//		g_ioMgr.get_in_bit( st_io.i_distribute_rbt2_box_guide_down_chk[nSite], iOn ) == iOn)
//	{
//		return true;
//	}
//
//	CString strJamCode;
//	strJamCode.Format("5%04d%d",st_io.i_distribute_rbt2_box_guide_up_chk[nSite], iOn);
//	CTL_Lib.Alarm_Error_Occurrence( 236, dWARNING, strJamCode );
//	return false;
//}


bool CRun_Barcode_Works::Run_Bcr_Move_Chk1_Time()
{
	switch( bcr1_step_old )
	{
	case BCR1_PICK_Z1_SAFETY:
 		if( InTimeRobot1( 10000 ) == false )
 		{//100006 1 00 "Distribute#1 Attach Z#1 Axis Motor Move Error."//2016.0722
			//CTL_Lib.Alarm_Error_Occurrence( 240, dWARNING, "180006" );
			CTL_Lib.Alarm_Error_Occurrence( 240, dWARNING, "100006" );
			m_dwTime_Robot1 = GetCurrentTime();
			return false;
 		}
		break;
	case BCR1_PICK_Z2_SAFETY:
 		if( InTimeRobot1( 10000 ) == false )
 		{//110006 1 00 "Distribute#1 Attach Z#2 Axis Motor Move Error." //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence( 241, dWARNING, "200006" );
			CTL_Lib.Alarm_Error_Occurrence( 241, dWARNING, "110006" );
			m_dwTime_Robot1 = GetCurrentTime();
			return false;
 		}
		break;
	}

	return true;
}

bool CRun_Barcode_Works::InTimeRobot1( int iMilliSec )
{
	DWORD dwtime = GetCurrentTime();
	//2012,1220
	if( GetCurrentTime() - m_dwTime_Robot1 < 0 )
	{
		m_dwTime_Robot1 = GetCurrentTime();
	}
	if( GetCurrentTime() - m_dwTime_Robot1 < iMilliSec )
		return true;

	return false;
}

void CRun_Barcode_Works::Run_Move1()
{

	COMI.ml_axiscnt[M_ROBOT_BARCODE_INDEX] = 2;
	COMI.mp_axisnum[M_ROBOT_BARCODE_INDEX][0] = M_BCR_ATTACH1_X;
	COMI.mp_axisnum[M_ROBOT_BARCODE_INDEX][1] = M_BCR_ATTACH1_Y;

	int nJobCnt = Func.m_pRobot[SITE_BARCODE1]->GetJobCount();
	//2016.0615
//  	Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
	int nJobCnt2 = Func.m_pRobot[SITE_BARCODE2]->GetJobCount();

	if( nJobCnt == 0 || nJobCnt2 > 0)
		return;

//  	Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();


	stJobPicker& job = Func.m_pRobot[SITE_BARCODE1]->GetFirstJob();

	if( bcr1_step_old != job.bcr1_step)
	{
		bcr1_step_old = job.bcr1_step;
		m_dwTime_Robot1 = GetCurrentTime();
		if( nJobCnt == 0 )
			return;
			
		if( Run_Bcr_Move_Chk1_Jam( job ) == false )
			return;
	}
	
	if( Run_Bcr_Move_Chk1_Time() == false )
		return;

	Func.ThreadFunctionStepTrace(21, job.bcr1_step);
	switch( job.bcr1_step )
	{
	case BCR1_NONE:	break;

	case BCR1_PICK_LABEL_READY:
		{
			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z1);
			if( dPos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
			{
				job.bcr1_step = BCR1_PICK_Z1_SAFETY;
				break;
			}
			dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z2);
			if( dPos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
			{
				job.bcr1_step = BCR1_PICK_Z2_SAFETY;
				break;
			}

			job.bcr1_step = BCR1_PICK_LABEL_TOP_CHK;
			
			m_dwTimeTact = GetCurrentTime();
			
		}
		break;

	case BCR1_PICK_Z1_SAFETY:
		{
			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_PICK_LABEL_PICK_READY;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 250, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PICK_Z2_SAFETY:
		{
			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_PICK_LABEL_READY;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 251, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PICK_LABEL_TOP_CHK:
		{
			int nLock_2 = st_io.i_distribute_rbt_top_vacuum_bwd_chk[0];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON  )
			{
				job.bcr1_step = BCR1_PICK_LABEL_TOP_LEFT_BACKWPRD;
				break;
			}
			nLock_2 = st_io.i_distribute_rbt_top_vacuum_bwd_chk[1];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON )
			{
				job.bcr1_step = BCR1_PICK_LABEL_TOP_RIGHT_BACKWPRD;
				break;
			}

			job.bcr1_step = BCR1_PICK_LABEL_BTM_CHK;

		}
		break;

	case BCR1_PICK_LABEL_TOP_LEFT_BACKWPRD:
		ReqMTopVac( EBVS_LEFT , BACKWARD );
		ReqMTopVac( EBVS_RIGHT , BACKWARD );
		job.bcr1_step = BCR1_PICK_LABEL_TOP_LEFT_BACKWPRD_CHK;
		break;

	case BCR1_PICK_LABEL_TOP_LEFT_BACKWPRD_CHK:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_PICK_LABEL_TOP_CHK;
		break;
		
	case BCR1_PICK_LABEL_TOP_RIGHT_BACKWPRD:
		ReqMTopVac( EBVS_RIGHT, BACKWARD );
		job.bcr1_step = BCR1_PICK_LABEL_TOP_RIGHT_BACKWPRD_CHK;
		break;

	case BCR1_PICK_LABEL_TOP_RIGHT_BACKWPRD_CHK:
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_PICK_LABEL_TOP_CHK;
		break;

	case BCR1_PICK_LABEL_BTM_CHK:
		{
			int nLock_2 = st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0];

			if( ( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON ))
			{
				job.bcr1_step = BCR1_PICK_LABEL_BTM_LEFT_BACKWPRD;
				break;
			}
			nLock_2 = st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1];

			if( ( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON ) )
			{
				job.bcr1_step = BCR1_PICK_LABEL_BTM_RIGHT_BACKWPRD;
				break;
			}

			job.bcr1_step = BCR1_PICK_LABEL_ROTATE_CHK;

		}
		break;

	case BCR1_PICK_LABEL_BTM_LEFT_BACKWPRD:
		ReqMBtmVac( EBVS_LEFT , BACKWARD );
		ReqMBtmVac( EBVS_RIGHT, BACKWARD );
		job.bcr1_step = BCR1_PICK_LABEL_BTM_LEFT_BACKWPRD_CHK;
		break;

	case BCR1_PICK_LABEL_BTM_LEFT_BACKWPRD_CHK:
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_PICK_LABEL_BTM_CHK;
		break;

	case BCR1_PICK_LABEL_BTM_RIGHT_BACKWPRD:
 		ReqMBtmVac( EBVS_RIGHT, BACKWARD );
		job.bcr1_step = BCR1_PICK_LABEL_BTM_RIGHT_BACKWPRD_CHK;
		break;

	case BCR1_PICK_LABEL_BTM_RIGHT_BACKWPRD_CHK:
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_PICK_LABEL_BTM_CHK;
		break;

	case BCR1_PICK_LABEL_ROTATE_CHK:
		{
//			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_R1);
//			if( dPos > st_motor[M_BCR_ATTACH1_R1].d_pos[P_R_BCR_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_R1] )
//			{
//				job.bcr1_step = BCR1_PICK_R1_SAFETY;
//				break;
//			}
//			dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_R2);
//			if( dPos > st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_R2] )
//			{
//				job.bcr1_step = BCR1_PICK_R2_SAFETY;
//				break;
//			}
//
//			job.bcr1_step = BCR1_PICK_LABEL_MOVE_READY_POS;		
			mn_mot_flag[0][0] = 0; mn_mot_flag[0][1] = 0;
			job.bcr1_step = BCR1_PICK_R1_SAFETY;
		
		}
		break;

	case BCR1_PICK_R1_SAFETY://2014,1205
		{
			ReqMRotateFwdBwd( 0 ,BACKWARD);
			ReqMRotateFwdBwd( 1 ,BACKWARD);
			job.bcr1_step = BCR1_PICK_R2_SAFETY;
     		m_dwTime_Robot1 = GetCurrentTime();
		}
		break;

	case BCR1_PICK_R2_SAFETY://2014,1205
		{
 			int nRet1,nRet2,nRet3,nRet4;
//			if( GetCurrentTime() - m_dwTime_Robot1 < 0 ) m_dwTime_Robot1 = GetCurrentTime();

			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
			
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_OFF);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_ON); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_OFF);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_ON);
			
			if(nRet1 == IO_OFF && nRet2 == IO_ON && nRet3 == IO_OFF && nRet4 == IO_ON)
			{
				//2015.0827
				mn_bcr_pick_error[0] = mn_bcr_pick_error[1] = CTL_NO;
				st_handler.mn_retest_cnt = 0;
				job.bcr1_step = BCR1_PICK_LABEL_MOVE_READY_POS;
			}
			else
			{
				job.bcr1_step = BCR1_PICK_R1_SAFETY;
			}
		}
		break;

	case BCR1_PICK_LABEL_MOVE_READY_POS:
		{
			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_X);
			double dPos1 = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Y);
			int nRet_1 = COMI.Check_MotPosRange(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1], COMI.md_allow_value[M_BCR_ATTACH1_X]);
			int nRet_2 = COMI.Check_MotPosRange(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1], COMI.md_allow_value[M_BCR_ATTACH1_Y]);
			if (nRet_1 != BD_GOOD || nRet_2 != BD_GOOD) //Y축이 작업 가능한 위치에 와 있는지 확인한다 
			{
				job.bcr1_step = BCR1_PICK_LABEL_MOVE_READY;	//처음으로 가서 다시 시작한다 		 
				break;
			}

			if( dPos > st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_X] &&
				dPos < st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_X] &&
				dPos > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				dPos < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				job.bcr1_step = BCR1_PICK_LABEL_PICK_READY;
				break;
			}
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[0], IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[1], IO_OFF);
			job.bcr1_step = BCR1_PICK_LABEL_MOVE_READY;				
		}
		break;

	case BCR1_PICK_LABEL_MOVE_READY:
		{
// 			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK], st_basic.nRunSpeed );
// 			if( nRet == BD_GOOD )
// 			{
// 				job.bcr1_step = BCR1_PICK_LABEL_PICK_READY;
// 			}
// 			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 254, CTL_dWARNING, alarm.mstr_code );
// 			}

			double m_dPos[2];
			m_dPos[0] = st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1];
			m_dPos[1] = st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1];
			long lAxis[2];
			lAxis[0] = M_BCR_ATTACH1_X;
			lAxis[1] = M_BCR_ATTACH1_Y;
			
			double dSpeedRatio[3];
			dSpeedRatio[0] = (double)st_basic.nRunSpeed;
			dSpeedRatio[1] = (double)st_basic.nRunSpeed;
			dSpeedRatio[2] = (double)st_basic.nRunSpeed;
			
			int nRet = CTL_Lib.Linear_Move( M_ROBOT_BARCODE_INDEX, 2, lAxis, m_dPos, dSpeedRatio );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_PICK_LABEL_PICK_READY;				
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 590, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;
		

	case BCR1_PICK_LABEL_PICK_READY:
		{
			if( job.iRobotFirst != -1)
			{
					g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[job.iRobotFirst], IO_OFF);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_ON);//2014,1117

					ReqMTopVac( job.iRobotFirst, BACKWARD);
// 					ReqMBtmVac( job.iRobotFirst, BACKWARD);
			}
			if( job.iRobotSecond != -1)
			{
					g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[job.iRobotSecond], IO_OFF);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_ON);//2014,1117
					ReqMTopVac( job.iRobotSecond, BACKWARD);
// 					ReqMBtmVac( job.iRobotSecond, BACKWARD);
			}
			mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
			job.bcr1_step = BCR1_PICK_LABEL_DOWN;	
		}
		break;

	case BCR1_PICK_LABEL_DOWN:
		{
			int nRet1,nRet2;
			nRet1 = nRet2 = BD_ERROR;
			if( job.iRobotFirst != -1)
			{
				if( (st_handler.mn_retest_cnt == 0 && mn_bcr_pick_error[job.iRobotFirst] == CTL_NO) ||
					(st_handler.mn_retest_cnt >= 1 && mn_bcr_pick_error[job.iRobotFirst] == CTL_YES) )
				{
					nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK2], st_basic.nRunSpeed );
				}
				else
				{
					nRet1 = BD_ERROR;
				}
			}
			else
			{
				nRet1 = BD_ERROR;
			}
			if( job.iRobotSecond != -1)
			{				
				if( (st_handler.mn_retest_cnt == 0 && mn_bcr_pick_error[job.iRobotSecond] == CTL_NO) ||
					(st_handler.mn_retest_cnt >= 1 && mn_bcr_pick_error[job.iRobotSecond] == CTL_YES) )
				{
					nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK2], st_basic.nRunSpeed );
				}
				else
				{
					nRet2 = BD_GOOD;
				}
			}
			else
			{
				nRet2 = BD_ERROR;
			}
			if( nRet1 == BD_GOOD ) mn_mot_flag[0][0] = 1;
			if( nRet2 == BD_GOOD ) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{
				mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
				////2014.1120 ysj
				if( job.iRobotFirst != -1)
				{
					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_ON);
// 					g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_btm_vacuum[job.iRobotFirst], IO_ON);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_ON);//2014,1117
				}
				if( job.iRobotSecond != -1)
				{
					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_ON);
// 					g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_btm_vacuum[job.iRobotSecond], IO_ON);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_ON);//2014,1117
				}

				job.bcr1_step = BCR1_PICK_LABEL_DOWN_CHK;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 255, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PICK_LABEL_DOWN_CHK:
		{
			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
// 				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
			}
			if( job.iRobotSecond != -1)
			{
 				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
// 				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
			}
			job.bcr1_step = BCR1_PICK_LABEL_VACUUM;	
		}
		break;

	case BCR1_PICK_LABEL_VACUUM:
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_ON);
// 				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotFirst], IO_ON);
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_ON);
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_ON);
// 				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotSecond], IO_ON);
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_ON);
			}
			job.bcr1_step = BCR1_PICK_LABEL_VACUUM_CHK;	
			m_dwTime_Robot1 = GetCurrentTime();
		}
		break;

	case BCR1_PICK_LABEL_VACUUM_CHK:
		{
// 			if( GetCurrentTime() - m_dwTime_Robot1 < 0 ) m_dwTime_Robot1 = GetCurrentTime();
// 			if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PICK_VACUUM][IO_ON] ) break;

			
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_ON);

				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
				{
				}
				else
				{
					if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] ) break;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 256, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Top Vacuum Off Check Error.";
					}
					else
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
//						CString strError;
//						strError.Format("5%04d0",st_io.i_distribute_rbt1_btm_vacuum_chk[job.iRobotFirst]);
//						CTL_Lib.Alarm_Error_Occurrence( 257, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Bottom Vacuum Off Check Error.";
					}
// 					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
//					break;

				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_ON);
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
				{
				}
				else
				{
					if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] ) break;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
//						CString strError;
//						strError.Format("5%04d0",st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotSecond]);
//						CTL_Lib.Alarm_Error_Occurrence( 258, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Top Vacuum Off Check Error.";
					}
					else
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
//						CString strError;
//						strError.Format("5%04d0",st_io.i_distribute_rbt1_btm_vacuum_chk[job.iRobotSecond]);
//						CTL_Lib.Alarm_Error_Occurrence( 259, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Bottom Vacuum Off Check Error.";
					}
// 					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
//					break;

				}
			}
			m_dwTime_Robot1 = GetCurrentTime();
			mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
			job.bcr1_step = BCR1_PICK_LABEL_UP;	
		}
		break;

	case BCR1_PICK_LABEL_UP:
		{

			if( GetCurrentTime() - m_dwTime_Robot1 < 0 ) m_dwTime_Robot1 = GetCurrentTime();
			if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PICK_VACUUM][IO_ON] ) break;

			int nnSite = 0;
			if(job.iRobotFirst != -1) nnSite = job.iRobotFirst;
			else if(job.iRobotSecond != -1) nnSite = job.iRobotSecond;
			//2015.0120
			if( GetCurrentTime() - st_handler.m_lBcrOutTime[nnSite] < 0 ) st_handler.m_lBcrOutTime[nnSite]  = GetCurrentTime();
			if( GetCurrentTime() - st_handler.m_lBcrOutTime[nnSite] > 60000 ) 
			{
				if( GetCurrentTime() - m_dwTime_Robot1 < 0 ) m_dwTime_Robot1 = GetCurrentTime();
				if( GetCurrentTime() - m_dwTime_Robot1 < 3500 ) break;
			}
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{
				job.bcr1_step = BCR1_PICK_LABEL_UP_VACUUM_CHK;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 260, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PICK_LABEL_UP_VACUUM_CHK:
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);

				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
				{
				}
				else 
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
						if(st_handler.mn_retest_cnt >= 2 && mn_bcr_pick_error[job.iRobotFirst] == CTL_YES)
						{
							CString strError;
							strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
							CTL_Lib.Alarm_Error_Occurrence( 261, CTL_dWARNING, strError );
						}
						else
						{
							mn_bcr_pick_error[job.iRobotFirst] = CTL_YES;
							st_handler.mn_retest_cnt++;
							mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
							job.bcr1_step = BCR1_PICK_LABEL_DOWN;
							break;
						}
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Top Vacuum Off Check Error.";
					}
					else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
						CString strError;
						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
						CTL_Lib.Alarm_Error_Occurrence( 262, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Bottom Vacuum Off Check Error.";
					}
// 					Func.OnSet_IO_Port_Stop();
//  					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
					job.bcr1_step = BCR1_STEP(252);
					break;
				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
				{
				}
				else
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
						if(st_handler.mn_retest_cnt >= 2 && mn_bcr_pick_error[job.iRobotSecond] == CTL_YES)
						{
							CString strError;
							strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
							CTL_Lib.Alarm_Error_Occurrence( 263, CTL_dWARNING, strError );
						}
						else
						{
							mn_bcr_pick_error[job.iRobotSecond] = CTL_YES;
							st_handler.mn_retest_cnt++;
							mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
							job.bcr1_step = BCR1_PICK_LABEL_DOWN;
							break;
						}
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Top Vacuum Off Check Error.";
					}
					else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_OFF )
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
						CString strError;
						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
						CTL_Lib.Alarm_Error_Occurrence( 264, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot1 Left Bottom Vacuum Off Check Error.";
					}
// 					Func.OnSet_IO_Port_Stop();
//  					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
					job.bcr1_step = BCR1_STEP(252);
					break;

				}
			}
			job.bcr1_step = BCR1_PICK_LABEL_FINISH;


			if( job.iRobotFirst != -1)
			{
// 				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);
				ReqMTopVac( job.iRobotFirst, BACKWARD);
				ReqMBtmVac( job.iRobotFirst, BACKWARD);
				g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst], IO_OFF);
//				COMI.Start_SingleMove(M_BCR_FEEDER_1+job.iRobotFirst, st_motor[M_BCR_FEEDER_1+job.iRobotFirst].d_pos[P_BCR_FEEDER_PICK], st_basic.nRunSpeed);
			}
			if( job.iRobotSecond != -1)
			{
// 				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
				ReqMTopVac( job.iRobotSecond, BACKWARD);
				ReqMBtmVac( job.iRobotSecond, BACKWARD);
				g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond], IO_OFF);
//				COMI.Start_SingleMove(M_BCR_FEEDER_1+job.iRobotSecond, st_motor[M_BCR_FEEDER_1+job.iRobotSecond].d_pos[P_BCR_FEEDER_PICK], st_basic.nRunSpeed);
			}
		}
		break;

	case 251:
		if( m_fbmrotatefwdbwd[EBVS_LEFT] != FB_NONE) break;
		if( m_fbmrotatefwdbwd[EBVS_RIGHT] != FB_NONE) break;
		job.bcr1_step = BCR1_STEP(252);
		break;

	case 252:
		{
			bool nfwd1 = CheckMRotateFwdBwd( EBVS_LEFT, IO_OFF );
			bool nfwd2 = CheckMRotateFwdBwd( EBVS_RIGHT, IO_OFF );
			if( nfwd1 == true && nfwd2 == true )
			{
				ReqMTopVac( EBVS_LEFT , FORWARD );
				ReqMTopVac( EBVS_RIGHT , FORWARD );
				ReqMBtmVac( EBVS_LEFT , BACKWARD );
				ReqMBtmVac( EBVS_RIGHT, BACKWARD );
				job.bcr1_step = BCR1_STEP(253);			
			}
			else
			{
				ReqMRotateFwdBwd( EBVS_LEFT ,BACKWARD);
				ReqMRotateFwdBwd( EBVS_RIGHT ,BACKWARD);
				job.bcr1_step = BCR1_STEP(251);			
			}
		}
		break;

	case 253:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
		job.bcr1_step = BCR1_STEP(254);
		break;

	case 254:
		{
// 			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD)
// 			{
// 				job.bcr1_step = BCR1_STEP(255);
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 271, CTL_dWARNING, alarm.mstr_code );
// 			}

			double m_dPos[2];
			m_dPos[0] = st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT];
			m_dPos[1] = st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT];
			long lAxis[2];
			lAxis[0] = M_BCR_ATTACH1_X;
			lAxis[1] = M_BCR_ATTACH1_Y;
			
			double dSpeedRatio[3];
			dSpeedRatio[0] = (double)st_basic.nRunSpeed;
			dSpeedRatio[1] = (double)st_basic.nRunSpeed;
			dSpeedRatio[2] = (double)st_basic.nRunSpeed;
			
			int nRet = CTL_Lib.Linear_Move( M_ROBOT_BARCODE_INDEX, 2, lAxis, m_dPos, dSpeedRatio );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_STEP(255);		
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 271, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 255:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				job.bcr1_step = BCR1_STEP(256);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 260, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 256:
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_ON);
		m_dwTime_Robot1 = GetCurrentTime();
		job.bcr1_step = BCR1_STEP(260);
		break;

	case 260:
		if( GetCurrentTime() - m_dwTime_Robot1 < 0) m_dwTime_Robot1 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		mn_mot_flag[0][0] = 0;
		mn_mot_flag[0][1] = 0;
		job.bcr1_step = BCR1_STEP(261);
		break;

	case 261:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{

				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);

				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_OFF);
				//Func.OnSet_IO_Port_Stop();
// 				::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);

				job.bcr1_step = BCR1_STEP(262);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 260, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 262:
		{
			ReqMTopVac( EBVS_LEFT , BACKWARD );
			ReqMTopVac( EBVS_RIGHT , BACKWARD );
			ReqMBtmVac( EBVS_LEFT , BACKWARD );
			ReqMBtmVac( EBVS_RIGHT, BACKWARD );
			job.bcr1_step = BCR1_STEP(263);			
		}
		break;

	case 263:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_STEP(264);
		break;

	case 264:
		if( st_basic.n_mode_device && job.iRobotFirst != -1)
		{
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515081 1 00 "Distribution Label Robot1 Left Top Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 261, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515091 1 00 "Distribution Label Robot1 Left Bottom Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 262, CTL_dWARNING, strError );
				break;
			}
			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotFirst], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotFirst], IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(265, dWARNING, strError);
				break;
			}
		}
		if( st_basic.n_mode_device && job.iRobotSecond != -1)
		{
			//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 263, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
			{
				//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 264, CTL_dWARNING, strError );
				break;
			}
			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotSecond], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotSecond], IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(266, dWARNING, strError);				
				break;
			}
		}
		job.bcr1_step = BCR1_STEP(265);
		break;

	case 265:
		if( job.iRobotFirst != -1)
		{
			ReqMTopVac( job.iRobotFirst, BACKWARD);
			ReqMBtmVac( job.iRobotFirst, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst], IO_OFF);
		}
		if( job.iRobotSecond != -1)
		{
			ReqMTopVac( job.iRobotSecond, BACKWARD);
			ReqMBtmVac( job.iRobotSecond, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond], IO_OFF);
		}
		job.bcr1_step = BCR1_STEP(266);
		break;

	case 266:
		{			
			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);//2014,1117
				
			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);//2014,1117
			}
			
			if( job.iRobotFirst != -1)
			{
				//st_bcr_feeder[job.iRobotFirst].st_bcr.bExist = false;
				st_bcr_feeder[job.iRobotFirst].st_bcr.nState = EMBS_FAIL;
				//2015.0226 try pickup reject
				//memset( &st_bcr_feeder[job.iRobotFirst], 0x00, sizeof(st_bcr_feeder[job.iRobotFirst]));
			}
			if( job.iRobotSecond != -1)
			{				
				//st_bcr_feeder[job.iRobotSecond].st_bcr.bExist = false;
				st_bcr_feeder[job.iRobotSecond].st_bcr.nState = EMBS_FAIL;
				//2015.0226 try pickup reject
				//memset( &st_bcr_feeder[job.iRobotSecond], 0x00, sizeof(st_bcr_feeder[job.iRobotSecond]));
			}			
			
			Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
			Func.Handler_Recovery_Data_Write();
		}
		break;

	case BCR1_PICK_LABEL_FINISH:
		{

			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);//2014,1117

			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);//2014,1117
			}
			if( job.iRobotFirst != -1)
			{
				st_bcr_rbt[0].bPick[job.iRobotFirst] = st_bcr_feeder[job.iRobotFirst].st_bcr.bOut;
				st_bcr_feeder[job.iRobotFirst].st_bcr.bExist = false;
				memcpy( &st_bcr_rbt[0].st_bcr[job.iRobotFirst], &st_bcr_feeder[job.iRobotFirst].st_bcr, sizeof(st_bcr_feeder[job.iRobotFirst].st_bcr));
				memset( &st_bcr_feeder[job.iRobotFirst], 0x00, sizeof(st_bcr_feeder[job.iRobotFirst]));
			}
			if( job.iRobotSecond != -1)
			{				
				st_bcr_rbt[0].bPick[job.iRobotSecond] = st_bcr_feeder[job.iRobotSecond].st_bcr.bOut;
				st_bcr_feeder[job.iRobotSecond].st_bcr.bExist = false;
				memcpy( &st_bcr_rbt[0].st_bcr[job.iRobotSecond], &st_bcr_feeder[job.iRobotSecond].st_bcr, sizeof(st_bcr_feeder[job.iRobotSecond].st_bcr));
				memset( &st_bcr_feeder[job.iRobotSecond], 0x00, sizeof(st_bcr_feeder[job.iRobotSecond]));
			}
		
			// UI 업데이트
			if( st_handler.cwnd_main )
			{
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDT_SEL_TRAY);
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDR_PICKER);
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDS_TESTSITE);
			}			
			job.bcr1_step = BCR1_STEP(271);
			mn_mot_flag[0][0]=0;mn_mot_flag[0][1]=0;mn_mot_flag[0][2]=0;
		}
		break;

	case 271://2014,1205
		{
			int nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
			int nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE], st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD )
			{
				mn_mot_flag[0][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD )
			{
				mn_mot_flag[0][1] = CTL_YES;
			}
			
			if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES )
			{
				mn_mot_flag[0][0] = 0; mn_mot_flag[0][1] = mn_mot_flag[0][2] = 0; //clear 
				job.bcr1_step = BCR1_STEP(272);
				//2015.0206
				if( job.iRobotFirst != -1)
				{
					ReqMRotateFwdBwd( job.iRobotFirst , FORWARD);
				}
				if( job.iRobotSecond != -1)
				{
					ReqMRotateFwdBwd( job.iRobotSecond , FORWARD);
				}
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 265, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 272:
		{
			//	int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_R_BCR_PLACE], st_basic.nRunSpeed );
			//	int nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_R_BCR_PLACE], st_basic.nRunSpeed );
			int nRet1 = COMI.Check_SingleMove(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE]);  // 이동 완료 ?
			int nRet2 = COMI.Check_SingleMove(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE]);  // 이동 완료 ?
			if( nRet1 == BD_GOOD)
			{
				mn_mot_flag[0][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD)
			{
				mn_mot_flag[0][1] = CTL_YES;
			}

			if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES)
			{
				mn_mot_flag[0][0] = mn_mot_flag[0][1] = CTL_NO;
				job.bcr1_step = BCR1_STEP(273);
				m_dwTime_Robot1 = GetCurrentTime();//2014,1205
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				job.bcr1_step = BCR1_STEP(2711);
				CTL_Lib.Alarm_Error_Occurrence( 266, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
		
	case 273://roller ready//2014,1205
		{
			int nRet1,nRet2,nRet3,nRet4;
			CString strError;

			//if( job.iRobotFirst != -1)
				if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			//if( job.iRobotSecond != -1)
				if( m_fbmrotatefwdbwd[1] != FB_NONE) break;

//			if( GetCurrentTime() - m_dwTime_Robot1 < 0 ) m_dwTime_Robot1 = GetCurrentTime();
			if( job.iRobotFirst != -1)
			{
				nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_ON);//place position
				nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_OFF); //pick position
			}
			else
			{
				nRet1 = IO_ON;
				nRet2 = IO_OFF;
			}
			if( job.iRobotSecond != -1)
			{
				nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_ON);
				nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_OFF);
			}
			else
			{
				nRet3 = IO_ON;
				nRet4 = IO_OFF;
			}
			
			if(nRet1 == IO_ON && nRet2 == IO_OFF && nRet3 == IO_ON && nRet4 == IO_OFF)
			{
				Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
				Func.Handler_Recovery_Data_Write();
			}
			else
			{
				if(nRet1 != IO_ON) 
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 2266, CTL_dWARNING, strError );
				}
				else if(nRet2 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 267, CTL_dWARNING, strError );
				}
				else if(nRet3 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 268, CTL_dWARNING, strError );
				}
				else if(nRet4 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 269, CTL_dWARNING, strError );
				}
			}
		}
		break;

	case BCR1_PLACE_LABEL_READY:
		{
			//2015.0327
			bool bWork = true;
			int nRet1,nRet2;
			CString strError,strRbt,strIDBuff;
			if( job.iRobotFirst != -1)
			{
				if( st_bcr_rbt[0].st_bcr[job.iRobotFirst].nState == EMBS_FAIL )
				{
					bWork = false;
				}
				//2016.0916
				strRbt.Format("%s", st_bcr_rbt[0].st_bcr[1].c_serial);
				strIDBuff.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_serial[0]);
				strError = strIDBuff.Left(strIDBuff.GetLength()-1);
				if( !Func.CmpStrFile(strRbt, strError) )
				{
					strError = _T( "650000" );
					CTL_Lib.Alarm_Error_Occurrence( 7269, CTL_dWARNING, strError );
					break;
				}

			}
			if( job.iRobotSecond != -1)
			{
				if( st_bcr_rbt[0].st_bcr[job.iRobotSecond].nState == EMBS_FAIL )
				{
					bWork = false;
				}
				//2016.0916
				strRbt.Format("%s", st_bcr_rbt[0].st_bcr[0].c_serial);
				strIDBuff.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_serial[1]);
				strError = strIDBuff.Left(strIDBuff.GetLength()-1);
				if( !Func.CmpStrFile(strRbt, strError) )
				{
					strError = _T( "650000" );
					CTL_Lib.Alarm_Error_Occurrence( 7369, CTL_dWARNING, strError );
					break;
				}
			}

			if(bWork == false)//reject
			{
				job.bcr1_step = BCR1_STEP(432);
			}
			else
			{
				nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
				nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE], st_basic.nRunSpeed );
				
				if( nRet1 == BD_GOOD)
				{
					mn_mot_flag[0][0] = CTL_YES;
				}
				if( nRet2 == BD_GOOD)
				{
					mn_mot_flag[0][1] = CTL_YES;
				}
				
				if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES)
				{
					mn_mot_flag[0][0] = 0; mn_mot_flag[0][1] = mn_mot_flag[0][2] = 0; //clear 
					job.bcr1_step = BCR1_PLACE_LABEL_X_READY;
				}
				else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
				{
					CTL_Lib.Alarm_Error_Occurrence( 270, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case BCR1_PLACE_LABEL_X_READY:
		{
			int nRet1 = COMI.Check_SingleMove(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE]);
			int nRet2 = COMI.Check_SingleMove(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE]);
			
			if( nRet1 == BD_GOOD)
			{
				mn_mot_flag[0][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD)
			{
				mn_mot_flag[0][1] = CTL_YES;
			}

			if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES)
			{
				mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
				job.bcr1_step = BCR1_PLACE_LABEL_READY2;
				m_dwTime_Robot1 = GetCurrentTime();//2014,1205
// 				if( job.iRobotFirst != -1)
// 				{
					ReqMRotateFwdBwd( 0, FORWARD);
// 				}
// 				if( job.iRobotSecond != -1)
// 				{
					ReqMRotateFwdBwd( 1, FORWARD);
// 				}
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
				job.bcr1_step = BCR1_PLACE_LABEL_READY;
				CTL_Lib.Alarm_Error_Occurrence( 271, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;


	case BCR1_PLACE_LABEL_READY2://roller ready//2014,1205
		{

			int nRet1,nRet2,nRet3,nRet4;
			CString strError;
	
			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
			
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_ON);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_OFF); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_ON);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_OFF);	
			
			if(nRet1 == IO_ON && nRet2 == IO_OFF && nRet3 == IO_ON && nRet4 == IO_OFF)
			{
				double dpos = COMI.Get_MotCurrentPos(M_INDEX_X);
				if( dpos > st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS] - COMI.md_allow_value[M_INDEX_X] && dpos < st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS] + COMI.md_allow_value[M_INDEX_X] )
				{
					job.bcr1_step = BCR1_PLACE_LABEL_DOWN;
				}
				else
				{
					job.bcr1_step = BCR1_PLACE_LABEL_ROLLER_X_POS;
				}
			}
			else
			{
				if( job.iRobotFirst != -1)
				{
					if(nRet1 != IO_ON) 
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 273, CTL_dWARNING, strError );
					}
					else if(nRet2 != IO_OFF)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 274, CTL_dWARNING, strError );
					}
				}
				if( job.iRobotSecond != -1)
				{
					if(nRet3 != IO_ON)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 275, CTL_dWARNING, strError );
					}
					else if(nRet4 != IO_OFF)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 276, CTL_dWARNING, strError );
					}
				}
			}
		}
		break;

	case BCR1_PLACE_LABEL_ROLLER_X_POS:
		{
			int	nRet = CTL_Lib.Single_Move( M_INDEX_X, st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_PLACE_LABEL_DOWN;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 277, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PLACE_LABEL_DOWN:
		{//제품이 도달되어 있는지 체크한다.

			int nRet1,nRet2;
// 			if(job.iRobotFirst != -1)
// 			{
				nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN], st_basic.nRunSpeed );
// 			}
// 			else
// 			{
// 				nRet1 = BD_GOOD;
// 			}
// 			if(job.iRobotSecond != -1)
// 			{				
				nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN], st_basic.nRunSpeed );
// 			}
// 			else
// 			{
// 				nRet2 = BD_GOOD;
// 			}
			if(nRet1 == BD_GOOD && nRet2 == BD_GOOD/* && nRet3 == BD_GOOD*/)
			{
				job.bcr1_step = BCR1_PLACE_LABEL_PUSH;
				ReqBoxUpDn(FORWARD);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY/* || nRet3 == BD_ERROR || nRet3 == BD_SAFETY */)
			{
				CTL_Lib.Alarm_Error_Occurrence( 278, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
	
	case BCR1_PLACE_LABEL_PUSH:
		{
			int nRet3 = CTL_Lib.Single_Move( M_INDEX_ROLLER1, st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_POS], st_basic.nRunSpeed );
			if( nRet3 == BD_GOOD)
			{
// 				if( job.iRobotFirst != -1)
// 				{
// 					ReqMTopVac( job.iRobotFirst, FORWARD);
// 					ReqRollingFwdBwd( 0, job.iRobotFirst, FORWARD);
					ReqMTopVac( 0, FORWARD);
					ReqRollingFwdBwd( 0, FORWARD);
// 				}
// 				if( job.iRobotSecond != -1)
// 				{
// 					ReqMTopVac( job.iRobotSecond, FORWARD);
// 					ReqRollingFwdBwd( 0, job.iRobotSecond, FORWARD);
					ReqMTopVac( 1, FORWARD);
					ReqRollingFwdBwd( 1, FORWARD);
// 				}
				//ReqRollingFwdBwd( 1, FORWARD);
				
				job.bcr1_step = BCR1_PLACE_LABEL_XPLACE;
			}
			else if( nRet3 == BD_ERROR || nRet3 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 279, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;

	case BCR1_PLACE_LABEL_XPLACE:
		{
			if( m_fbboxupdn != FB_NONE ) break;
			if( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] > (st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] + 5) || st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] < (st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_DOWN]))
			{
				if(st_handler.cwnd_list != NULL)
				{
// 					sprintf(st_msg.c_abnormal_msg, "[BAR ROBOT] Picker Down pos is more than Picker Pick(5mm) or is less than. Position Error Check ");
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
//					break;
				}
			}
// 			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD )
// 			{
				job.bcr1_step = BCR1_PLACE_LABEL_PUSH_CHK;
// 			}
// 			else if( nRet1 == BD_ERROR )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 280, CTL_dWARNING, alarm.mstr_code );
// 			}
		}
		break;
		

	case BCR1_PLACE_LABEL_PUSH_CHK:
		{
// 			if( job.iRobotFirst != -1)
// 			{
// 				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
// 				ReqMBtmVac( job.iRobotFirst, FORWARD);
// 				if( GetRollingFwdBwd( 0, job.iRobotFirst ) != FB_NONE ) break;
				if( GetMTopVac( 0 ) != FB_NONE ) break;
				ReqMBtmVac( 0, FORWARD);
				if( GetRollingFwdBwd( 0 ) != FB_NONE ) break;
// 			}
// 			if( job.iRobotSecond != -1)
// 			{
				if( GetMTopVac( 1 ) != FB_NONE ) break;
				ReqMBtmVac( 1, FORWARD);
				if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;
//			}
			st_var.n_tboxmv_forming_cv_mode = CTL_YES;//2015.0331
//			if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;
			job.bcr1_step = BCR1_PLACE_LABEL_PUSH_VACUUM;
		}
		break;

	case BCR1_PLACE_LABEL_PUSH_VACUUM:
		{
// 			if( job.iRobotFirst != -1)
// 				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( 0 ) != FB_NONE ) break;
// 			if( job.iRobotSecond != -1)
// 				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( 1 ) != FB_NONE ) break;

				st_var.n_tboxmv_forming_cv_mode = CTL_NO;//2015.0331

				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[0], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[0], IO_OFF);

				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[1], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[1], IO_OFF);
			job.bcr1_step = BCR1_PLACE_LABEL_VACUUM_CHK;	
		}
		break;

	case BCR1_PLACE_LABEL_VACUUM_CHK:
		{

			if( job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_ON);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_ON);
// 				ReqMBtmVac( job.iRobotFirst, BACKWARD);
// 				ReqRollingFwdBwd( 0, job.iRobotFirst, BACKWARD);
			}
			ReqMBtmVac( 0, BACKWARD);
			ReqRollingFwdBwd( 0, BACKWARD);
			if( job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_ON);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_ON);
// 				ReqMBtmVac( job.iRobotSecond, BACKWARD);
// 				ReqRollingFwdBwd( 0, job.iRobotSecond, BACKWARD);
			}
			ReqMBtmVac( 1, BACKWARD);
			ReqRollingFwdBwd( 1, BACKWARD);
//			ReqRollingFwdBwd( 1, BACKWARD);
			m_dwTime_Robot1 = GetCurrentTime();
			job.bcr1_step = BCR1_PLACE_LABEL_PULL;
		}
		break;

	case BCR1_PLACE_LABEL_PULL:
		if( GetCurrentTime() - m_dwTime_Robot1 < 0) m_dwTime_Robot1 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		{
			if( job.iRobotFirst != -1)
			{
// 				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_OFF);
// 				ReqMTopVac( job.iRobotFirst, BACKWARD);
// 				if( GetRollingFwdBwd( 0, job.iRobotFirst ) != FB_NONE ) break;
			}
			if( job.iRobotSecond != -1)
			{
// 				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_OFF);
// 				ReqMTopVac( job.iRobotSecond, BACKWARD);
// 				if( GetRollingFwdBwd( 0, job.iRobotSecond ) != FB_NONE ) break;
			}
			if( GetMBtmVac( 0 ) != FB_NONE ) break;
			ReqMTopVac( 0, BACKWARD);
			if( GetRollingFwdBwd( 0 ) != FB_NONE ) break;
			if( GetMBtmVac( 1 ) != FB_NONE ) break;
			ReqMTopVac( 1, BACKWARD);
			if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;
//			if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;

			job.bcr1_step = BCR1_PLACE_LABEL_PULL_CHK;
		}
		break;
		
	case BCR1_PLACE_LABEL_PULL_CHK:
		{
			if(job.iRobotFirst != -1)
			{
// 				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_OFF);
			}
			if( GetMTopVac( 0 ) != FB_NONE ) break;
			if(job.iRobotSecond != -1)
			{
// 				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_OFF);
 			}
			if( GetMTopVac( 1 ) != FB_NONE ) break;
			job.bcr1_step = BCR1_PLACE_LABEL_VACUUM_RECHK;	
			m_dwTime_Robot1 = GetCurrentTime();
		}
		break;

	case BCR1_PLACE_LABEL_VACUUM_RECHK:
		if( GetCurrentTime() - m_dwTime_Robot1 < 0) m_dwTime_Robot1 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF &&
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
				{
				}
				else 
				{
// 					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotFirst], IO_OFF) == IO_ON )
// 					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 281, CTL_dWARNING, strError );
// 					}
// 					else
// 					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_btm_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 282, CTL_dWARNING, strError );
// 					}
// 					break;
				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_OFF) == IO_OFF &&
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_OFF) == IO_OFF )
				{
				}
				else if( GetCurrentTime() - m_dwTime_Robot1 > st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] )
				{
// 					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotFirst], IO_OFF) == IO_ON )
// 					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_top_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 283, CTL_dWARNING, strError );
// 					}
// 					else
// 					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_btm_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 284, CTL_dWARNING, "515090" );
// 					}
// 					break;
				}
			}
			ReqBoxUpDn( BACKWARD);//2014.1120 ysj
			job.bcr1_step = BCR1_PLACE_LABEL_XDOWN_BACK;
		}
		break;

	case BCR1_PLACE_LABEL_XDOWN_BACK:
		{
			job.bcr1_step = BCR1_PLACE_LABEL_UP;
			mn_mot_flag[0][0] = 0;
			mn_mot_flag[0][1] = 0;
			mn_mot_flag[0][2] = 0;
		}
		break;

	case 431:
		if( m_fbmrotatefwdbwd[EBVS_LEFT] != FB_NONE) break;
		if( m_fbmrotatefwdbwd[EBVS_RIGHT] != FB_NONE) break;
		job.bcr1_step = BCR1_STEP(432);
		break;
		
	case 432:
		{
			bool nfwd1 = CheckMRotateFwdBwd( EBVS_LEFT, IO_OFF );
			bool nfwd2 = CheckMRotateFwdBwd( EBVS_RIGHT, IO_OFF );
			if( nfwd1 == true && nfwd2 == true )
			{
				ReqMTopVac( EBVS_LEFT , FORWARD );
				ReqMTopVac( EBVS_RIGHT , FORWARD );
				ReqMBtmVac( EBVS_LEFT , BACKWARD );
				ReqMBtmVac( EBVS_RIGHT, BACKWARD );
				job.bcr1_step = BCR1_STEP(433);			
			}
			else
			{
				ReqMRotateFwdBwd( EBVS_LEFT ,BACKWARD);
				ReqMRotateFwdBwd( EBVS_RIGHT ,BACKWARD);
				job.bcr1_step = BCR1_STEP(431);			
			}
		}
		break;
		
	case 433:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		mn_mot_flag[0][0] = mn_mot_flag[0][1] = 0;
		job.bcr1_step = BCR1_STEP(434);
		break;
		
	case 434:
		{
// 			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD)
// 			{
// 				job.bcr1_step = BCR1_STEP(435);
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 371, CTL_dWARNING, alarm.mstr_code );
// 			}

			double m_dPos[2];
			m_dPos[0] = st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT];
			m_dPos[1] = st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT];
			long lAxis[2];
			lAxis[0] = M_BCR_ATTACH1_X;
			lAxis[1] = M_BCR_ATTACH1_Y;
			
			double dSpeedRatio[3];
			dSpeedRatio[0] = (double)st_basic.nRunSpeed;
			dSpeedRatio[1] = (double)st_basic.nRunSpeed;
			dSpeedRatio[2] = (double)st_basic.nRunSpeed;
			
			int nRet = CTL_Lib.Linear_Move( M_ROBOT_BARCODE_INDEX, 2, lAxis, m_dPos, dSpeedRatio );
			if( nRet == BD_GOOD )
			{
				job.bcr1_step = BCR1_STEP(435);
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 371, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;
		
	case 435:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				job.bcr1_step = BCR1_STEP(436);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 372, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 436:
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_ON);
		m_dwTime_Robot1 = GetCurrentTime();
		job.bcr1_step = BCR1_STEP(440);
		break;

	case 440:
		if( GetCurrentTime() - m_dwTime_Robot1 < 0) m_dwTime_Robot1 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot1 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		mn_mot_flag[0][0] = 0;
		mn_mot_flag[0][1] = 0;
		job.bcr1_step = BCR1_STEP(441);
		break;

	case 441:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1)
			{
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_OFF);
				//Func.OnSet_IO_Port_Stop();
				// 				::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
				
				job.bcr1_step = BCR1_STEP(442);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 360, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 442:
		{
			ReqMTopVac( EBVS_LEFT , BACKWARD );
			ReqMTopVac( EBVS_RIGHT , BACKWARD );
			ReqMBtmVac( EBVS_LEFT , BACKWARD );
			ReqMBtmVac( EBVS_RIGHT, BACKWARD );
			job.bcr1_step = BCR1_STEP(443);			
		}
		break;

	case 443:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr1_step = BCR1_STEP(444);
		break;

	case 444:
		if( st_basic.n_mode_device && job.iRobotFirst != -1)
		{
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515081 1 00 "Distribution Label Robot1 Left Top Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 361, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515091 1 00 "Distribution Label Robot1 Left Bottom Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 362, CTL_dWARNING, strError );
				break;
			}
// 			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotFirst], IO_ON) == IO_ON)
// 			{
// 				CString strError;
// 				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotFirst], IO_ON);
// 				CTL_Lib.Alarm_Error_Occurrence(365, dWARNING, strError);
// 				break;
// 			}
		}
		if( st_basic.n_mode_device && job.iRobotSecond != -1)
		{
			//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 363, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
			{
				//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 364, CTL_dWARNING, strError );
				break;
			}
// 			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotSecond], IO_ON) == IO_ON)
// 			{
// 				CString strError;
// 				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotSecond], IO_ON);
// 				CTL_Lib.Alarm_Error_Occurrence(366, dWARNING, strError);				
// 				break;
// 			}
		}
		job.bcr1_step = BCR1_STEP(445);
		break;

	case 445:
		if( job.iRobotFirst != -1)
		{
			ReqMTopVac( job.iRobotFirst, BACKWARD);
			ReqMBtmVac( job.iRobotFirst, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst], IO_OFF);
		}
		if( job.iRobotSecond != -1)
		{
			ReqMTopVac( job.iRobotSecond, BACKWARD);
			ReqMBtmVac( job.iRobotSecond, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond], IO_OFF);
		}
		job.bcr1_step = BCR1_STEP(446);
		break;

	case 446:
		{			
			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);//2014,1117
				
			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);//2014,1117
			}
			
			if( job.iRobotFirst != -1)
			{
				st_bcr_rbt[0].bPick[job.iRobotFirst] = 0;
				st_bcr_rbt[0].st_bcr[job.iRobotFirst].bExist = 0;
				st_bcr_rbt[0].st_bcr[job.iRobotFirst].bOut = 0;
			}
			if( job.iRobotSecond != -1)
			{				
				st_bcr_rbt[0].bPick[job.iRobotSecond] = 0;					
				st_bcr_rbt[0].st_bcr[job.iRobotSecond].bExist = 0;
				st_bcr_rbt[0].st_bcr[job.iRobotSecond].bOut = 0;
			}			
			
			Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
			Func.Handler_Recovery_Data_Write();
		}
		break;

	case BCR1_PLACE_LABEL_UP:
		{
			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			int nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			int nRet3 = CTL_Lib.Single_Move( M_INDEX_ROLLER1, st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[0][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[0][1] = 1;
			if(nRet3 == BD_GOOD) mn_mot_flag[0][2] = 1;
			if( mn_mot_flag[0][0] == 1 && mn_mot_flag[0][1] == 1 && mn_mot_flag[0][2] == 1 )
			{
				job.bcr1_step = BCR1_PLACE_LABEL_SAFETY;
				mn_mot_flag[0][0] = 0;
				mn_mot_flag[0][1] = 0;
				mn_mot_flag[0][2] = 0;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY || nRet3 == BD_ERROR || nRet3 == BD_SAFETY)
			{
				CTL_Lib.Alarm_Error_Occurrence( 285, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR1_PLACE_LABEL_SAFETY://2014,1205
		{
// 			int nRet1,nRet2,nRet3;
// 			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK], st_basic.nRunSpeed );
// 			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R1, st_motor[M_BCR_ATTACH1_R1].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			nRet3 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R2, st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			if(nRet1 == BD_GOOD) mn_mot_flag[0] = 1;
// 			if(nRet2 == BD_GOOD) mn_mot_flag[1] = 1;
// 			if(nRet3 == BD_GOOD) mn_mot_flag[2] = 1;
// 			if( mn_mot_flag[0] == 1 && mn_mot_flag[1] == 1 && mn_mot_flag[2] == 1 )
// 			{
// 				job.bcr1_step = BCR1_PLACE_LABEL_FINISH;
// 				mn_mot_flag[0] = 0;
// 				mn_mot_flag[1] = 0;
// 				mn_mot_flag[2] = 0;
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY || nRet3 == BD_ERROR || nRet3 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 286, CTL_dWARNING, alarm.mstr_code );
// 			}

//			int nRet1,nRet2,nRet3;
//			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK], st_basic.nRunSpeed );
//
//			g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_fwd_cylinder[0], IO_OFF);//place pos
//			g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_bwd_cylinder[0], IO_ON);//pick pos
//			nRet2 = BD_GOOD;
//
//			g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_fwd_cylinder[1], IO_OFF);
//			g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_bwd_cylinder[1], IO_ON);
//			nRet3 = BD_GOOD;
//
//			if(nRet1 == BD_GOOD) mn_mot_flag[0] = 1;
//			if(nRet2 == BD_GOOD) mn_mot_flag[1] = 1;
//			if(nRet3 == BD_GOOD) mn_mot_flag[2] = 1;
//			if( mn_mot_flag[0] == 1 && mn_mot_flag[1] == 1 && mn_mot_flag[2] == 1 )
//			{
//				job.bcr1_step = BCR1_STEP(451);
//				mn_mot_flag[0] = 0;
//				mn_mot_flag[1] = 0;
//				mn_mot_flag[2] = 0;
//				m_dwTime_Robot1 = GetCurrentTime();
//			}
//			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY/* || nRet2 == BD_ERROR || nRet2 == BD_SAFETY || nRet3 == BD_ERROR || nRet3 == BD_SAFETY */)
//			{
//				CTL_Lib.Alarm_Error_Occurrence( 287, CTL_dWARNING, alarm.mstr_code );
//			}

			int nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1], st_basic.nRunSpeed );
			int nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1], st_basic.nRunSpeed );

			if( nRet1 == BD_GOOD )
			{
				mn_mot_flag[0][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD )
			{
				mn_mot_flag[0][1] = CTL_YES;
			}
			
			if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES )
			{
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_fwd_cylinder[0], IO_OFF);//place pos
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_bwd_cylinder[0], IO_ON);//pick pos
//
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_fwd_cylinder[1], IO_OFF);
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_rotator_bwd_cylinder[1], IO_ON);

				//2015.0206
				ReqMRotateFwdBwd( 0, BACKWARD );
				ReqMRotateFwdBwd( 1, BACKWARD );
				job.bcr1_step = BCR1_STEP(461);
				mn_mot_flag[0][0] = 0;
				mn_mot_flag[0][1] = 0;
				mn_mot_flag[0][2] = 0;
				m_dwTime_Robot1 = GetCurrentTime();
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY)
			{
				CTL_Lib.Alarm_Error_Occurrence( 292, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 461://2014,1205
		{			
			int nRet1 = COMI.Check_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1] );
			int nRet2 = COMI.Check_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_PICK1] );

			if( nRet1 == BD_GOOD )
			{
				mn_mot_flag[0][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD )
			{
				mn_mot_flag[0][1] = CTL_YES;
			}
			
			if( mn_mot_flag[0][0] == CTL_YES && mn_mot_flag[0][1] == CTL_YES )
			{
				//2015.0206
// 				ReqMRotateFwdBwd( 0, BACKWARD );
// 				ReqMRotateFwdBwd( 1, BACKWARD );
				job.bcr1_step = BCR1_STEP(462);
// 				if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
// 				if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
// 				
// 				int nRet1,nRet2,nRet3,nRet4;
// 				CString strError;
// 				nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt1_box_rotator_fwd_chk[0], IO_OFF);//place position
// 				nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt1_box_rotator_bwd_chk[0], IO_ON); //pick position
// 				nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt1_box_rotator_fwd_chk[1], IO_OFF);
// 				nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt1_box_rotator_bwd_chk[1], IO_ON);	
// 				
// 				if(nRet1 == IO_OFF && nRet2 == IO_ON && nRet3 == IO_OFF && nRet4 == IO_ON)
// 				{
// 					job.bcr1_step = BCR1_PLACE_LABEL_FINISH;
// 				}
// 				else
// 				{
// 					if(nRet1 != IO_OFF) 
// 					{
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_box_rotator_fwd_chk[0]);
// 						CTL_Lib.Alarm_Error_Occurrence( 289, CTL_dWARNING, strError );
// 					}
// 					else if(nRet2 != IO_ON)
// 					{
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_box_rotator_bwd_chk[0]);
// 						CTL_Lib.Alarm_Error_Occurrence( 290, CTL_dWARNING, strError );
// 					}
// 					else if(nRet3 != IO_OFF)
// 					{
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_box_rotator_fwd_chk[1]);
// 						CTL_Lib.Alarm_Error_Occurrence( 291, CTL_dWARNING, strError );
// 					}
// 					else if(nRet4 != IO_ON)
// 					{
// 						strError.Format("5%04d0",st_io.i_distribute_rbt1_box_rotator_bwd_chk[1]);
// 						CTL_Lib.Alarm_Error_Occurrence( 292, CTL_dWARNING, strError );
// 					}
// 				}
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY)
			{
				job.bcr1_step = BCR1_PLACE_LABEL_SAFETY;
				mn_mot_flag[0][0] = 0;
				mn_mot_flag[0][1] = 0;
				mn_mot_flag[0][2] = 0;
				CTL_Lib.Alarm_Error_Occurrence( 293, CTL_dWARNING, alarm.mstr_code );
			}			
		}
		break;

	case 462:
		{
			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
			
			int nRet1,nRet2,nRet3,nRet4;
			CString strError;
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_OFF);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_ON); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_OFF);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_ON);	
			
			if(nRet1 == IO_OFF && nRet2 == IO_ON && nRet3 == IO_OFF && nRet4 == IO_ON)
			{
				job.bcr1_step = BCR1_PLACE_LABEL_FINISH;
			}
			else
			{
				if(nRet1 != IO_OFF) 
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 289, CTL_dWARNING, strError );
				}
				else if(nRet2 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 290, CTL_dWARNING, strError );
				}
				else if(nRet3 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 291, CTL_dWARNING, strError );
				}
				else if(nRet4 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 292, CTL_dWARNING, strError );
				}
			}
		}

		break;

	case BCR1_PLACE_LABEL_FINISH:
		{
			if(m_fbboxupdn != FB_NONE ) break;

			if( job.iRobotFirst != -1)
			{
				st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].nBcrExist[CTL_LEFT] = CTL_YES;
				memcpy( &st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].st_barcode1[job.iRobotFirst], &st_bcr_rbt[0].st_bcr[job.iRobotFirst], sizeof(st_bcrinfo_param));
			}
			if( job.iRobotSecond != -1)
			{
				st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].nBcrExist[CTL_RIGHT] = CTL_YES;
				memcpy( &st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].st_barcode1[job.iRobotSecond], &st_bcr_rbt[0].st_bcr[job.iRobotSecond], sizeof(st_bcrinfo_param));
			}
			if( job.iRobotFirst != -1 || job.iRobotSecond != -1)
			{
				if( job.iRobotFirst != -1)
				{
					st_bcr_rbt[0].bPick[job.iRobotFirst] = 0;
					st_bcr_rbt[0].st_bcr[job.iRobotFirst].bExist = 0;
					st_bcr_rbt[0].st_bcr[job.iRobotFirst].bOut = 0;
				}
				if( job.iRobotSecond != -1)
				{
					st_bcr_rbt[0].bPick[job.iRobotSecond] = 0;					
					st_bcr_rbt[0].st_bcr[job.iRobotSecond].bExist = 0;
					st_bcr_rbt[0].st_bcr[job.iRobotSecond].bOut = 0;
				}
				memset( &st_bcr_rbt[0], 0x00, sizeof(st_bcr_rbt[0]));
			}

			Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
//			Func.BackupData();//2013,1018

			st_sync.n_bcr_2_work_req = CTL_REQ;
			st_sync.n_bcr_1_work_req = CTL_REQ;//2016.0817

			if(st_handler.n_only_work_bcr1 == CTL_YES)
			{
				//2014,1117
				if( job.iRobotFirst != -1)
					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[job.iRobotFirst].nComplete = CTL_NO;
				if( job.iRobotSecond != -1)
					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[job.iRobotSecond].nComplete = CTL_NO;
				st_sync.n_bcr_1_work_req = CTL_READY;
			}

			if(GetCurrentTime() - m_dwTimeTact <= 0 ) m_dwTimeTact = GetCurrentTime();
			if( GetCurrentTime() - m_dwTimeTact >= 0 && GetCurrentTime() - m_dwTimeTact < 900000 &&
				st_handler.cwnd_list != NULL)
			{
				sprintf(st_msg.c_normal_msg, "[BARCODE1]Tact time : %d", GetCurrentTime() - m_dwTimeTact);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 				Func.On_LogFile_Add(LOG_MACHINE, st_msg.c_normal_msg);
			}
			m_dwTimeTact = GetCurrentTime();


			Func.Handler_Recovery_Data_Write();
			st_handler.mn_btm_ready = 1;
		}		
		break;
	}
}

bool CRun_Barcode_Works::Run_Bcr_Move_Chk2_Jam( stJobPicker job )
{
	CString strJamCode;

	Func.ThreadFunctionStepTrace(22, job.bcr2_step);
	switch( job.bcr2_step )
	{
	case BCR2_NONE:
		break;

	case BCR2_PICK_LABEL_ROTATE_CHK:
	case BCR2_PICK_R1_SAFETY:
	case BCR2_PICK_R2_SAFETY:
	case BCR2_PICK_LABEL_MOVE_READY_POS:
	case BCR2_PICK_LABEL_MOVE_READY:
// 		if( Chk_Robot2_vacuum_fwdbwd( 0, IO_OFF ) == false )		return false;
// 		if( Chk_Robot2_vacuum_fwdbwd( 1, IO_OFF ) == false )		return false;
// 		if( Chk_Robot_rollingfwdbwd( IO_OFF ) == false )			return false;
//		if( Chk_Robot2_guide_updn( 0, IO_ON ) == false )			return false;//guide up
//		if( Chk_Robot2_guide_updn( 1, IO_ON ) == false )			return false;
		break;

	case BCR2_PICK_LABEL_DOWN_CHK:
	case BCR2_PICK_LABEL_VACUUM:
	case BCR2_PICK_LABEL_UP:
	case BCR2_PICK_LABEL_VACUUM_CHK:
	case BCR2_PICK_LABEL_FINISH:
		if( Chk_Robot_rollingfwdbwd( IO_OFF ) == false )			return false;
		break;

	case BCR2_PLACE_LABEL_PUSH_VACUUM:
// 		if(job.iRobotFirst != -1)
// 			if( Chk_Robot2_vacuum_fwdbwd( 0, IO_ON ) == false )			return false;
// 		if(job.iRobotSecond != -1)
// 			if( Chk_Robot2_vacuum_fwdbwd( 1, IO_ON ) == false )			return false;
//		if( Chk_Robot2_guide_updn( 0, IO_OFF ) == false )			return false;//guide down
//		if( Chk_Robot2_guide_updn( 1, IO_OFF ) == false )			return false;
		break;

	case BCR2_PLACE_LABEL_PULL_CHK:
// 		if(job.iRobotFirst != -1)
// 			if( Chk_Robot2_vacuum_fwdbwd( 0, IO_OFF ) == false )		return false;
// 		if(job.iRobotSecond != -1)
// 			if( Chk_Robot2_vacuum_fwdbwd( 1, IO_OFF ) == false )		return false;
// 		if( Chk_Robot_rollingfwdbwd( IO_ON ) == false )			return false;
//		if( Chk_Robot2_guide_updn( 0, IO_ON ) == false )			return false;
//		if( Chk_Robot2_guide_updn( 1, IO_ON ) == false )			return false;
		break;

	case BCR2_PLACE_LABEL_SAFETY:
	case BCR2_PLACE_LABEL_FINISH:	
		if( Chk_Robot_rollingfwdbwd( IO_OFF ) == false )			return false;
//		if( Chk_Robot2_guide_updn( 0, IO_ON ) == false )			return false;//guide up
//		if( Chk_Robot2_guide_updn( 1, IO_ON ) == false )			return false;
		break;
	}
	
	return true;
}

bool CRun_Barcode_Works::Run_Bcr_Move_Chk2_Time()
{
	switch( bcr1_step_old )
	{
	case BCR2_PICK_Z1_SAFETY:
 		if( InTimeRobot2( 10000 ) == false )
 		{//230006 1 00 "Distribute#2 Attach Z#1 Axis Motor Move Error."
			CTL_Lib.Alarm_Error_Occurrence( 1301, dWARNING, "230006" );
			return false;
 		}
		break;
	case BCR2_PICK_Z2_SAFETY:
 		if( InTimeRobot2( 10000 ) == false )
 		{//250006 1 00 "Distribute#2 Attach Z#2 Axis Motor Move Error."
			CTL_Lib.Alarm_Error_Occurrence( 1302, dWARNING, "250006" );
			return false;
 		}
		break;
	}

	return true;
}

bool CRun_Barcode_Works::InTimeRobot2( int iMilliSec )
{
	DWORD dwtime = GetCurrentTime();
	//2012,1220
	if( GetCurrentTime() - m_dwTime_Robot2 < 0 )
	{
		m_dwTime_Robot2 = GetCurrentTime();
	}
	if( GetCurrentTime() - m_dwTime_Robot2 < iMilliSec )
		return true;
	
	return false;
}

void CRun_Barcode_Works::Run_Move2()
{
	COMI.ml_axiscnt[M_ROBOT_BARCODE_INDEX] = 2;
	COMI.mp_axisnum[M_ROBOT_BARCODE_INDEX][0] = M_BCR_ATTACH1_X;
	COMI.mp_axisnum[M_ROBOT_BARCODE_INDEX][1] = M_BCR_ATTACH1_Y;
	
	int nJobCnt = Func.m_pRobot[SITE_BARCODE2]->GetJobCount();
	//2016.0615
	int nJobCnt2 = Func.m_pRobot[SITE_BARCODE1]->GetJobCount();
// 	Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
	if( nJobCnt == 0 || nJobCnt2 > 0)
		return;

//   	Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();


	stJobPicker& job = Func.m_pRobot[SITE_BARCODE2]->GetFirstJob();

	if( bcr2_step_old != job.bcr2_step)
	{
		bcr2_step_old = job.bcr2_step;
		m_dwTime_Robot2 = GetCurrentTime();
		if( nJobCnt == 0 )
			return;
			
		if( Run_Bcr_Move_Chk2_Jam( job ) == false )
			return;
	}
	if( Run_Bcr_Move_Chk2_Time() == false )
		return;

	Func.ThreadFunctionStepTrace(23, job.bcr2_step);
	switch( job.bcr2_step )
	{
	case BCR2_NONE:	break;

	case BCR2_PICK_LABEL_READY:
		{
			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z1);
			if( dPos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
			{
				job.bcr2_step = BCR2_PICK_Z1_SAFETY;
				break;
			}
			dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z2);
			if( dPos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
			{
				job.bcr2_step = BCR2_PICK_Z2_SAFETY;
				break;
			}

			job.bcr2_step = BCR2_PICK_LABEL_TOP_CHK;	
			
		}
		break;

	case BCR2_PICK_Z1_SAFETY:
		{
			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr2_step = BCR2_PICK_LABEL_READY;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1303, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR2_PICK_Z2_SAFETY:
		{
			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr2_step = BCR2_PICK_LABEL_READY;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1304, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR2_PICK_LABEL_TOP_CHK:
		{
			int nLock_2 = st_io.i_distribute_rbt_top_vacuum_bwd_chk[0];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON)//2014,1205
			{
				job.bcr2_step = BCR2_PICK_LABEL_TOP_LEFT_BACKWPRD;
				break;
			}
			nLock_2 = st_io.i_distribute_rbt_top_vacuum_bwd_chk[1];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON)//2014,1205
			{
				job.bcr2_step = BCR2_PICK_LABEL_TOP_RIGHT_BACKWPRD;
				break;
			}

			job.bcr2_step = BCR2_PICK_LABEL_BTM_CHK;

		}
		break;

	case BCR2_PICK_LABEL_TOP_LEFT_BACKWPRD:
		ReqMTopVac( EBVS_LEFT , BACKWARD );
		ReqMTopVac( EBVS_RIGHT , BACKWARD );
		job.bcr2_step = BCR2_PICK_LABEL_TOP_LEFT_BACKWPRD_CHK;
		break;

	case BCR2_PICK_LABEL_TOP_LEFT_BACKWPRD_CHK:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr2_step = BCR2_PICK_LABEL_TOP_CHK;
		break;
		
	case BCR2_PICK_LABEL_TOP_RIGHT_BACKWPRD:
		ReqMTopVac( EBVS_RIGHT, BACKWARD );
		job.bcr2_step = BCR2_PICK_LABEL_TOP_RIGHT_BACKWPRD_CHK;
		break;

	case BCR2_PICK_LABEL_TOP_RIGHT_BACKWPRD_CHK:
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr2_step = BCR2_PICK_LABEL_TOP_CHK;
		break;

	case BCR2_PICK_LABEL_BTM_CHK:
		{
			int nLock_2 = st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON)
			{
				job.bcr2_step = BCR2_PICK_LABEL_BTM_LEFT_BACKWPRD;
				break;
			}
			nLock_2 = st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1];

			if( /*g_ioMgr.get_in_bit( nLock_1 ) != IO_OFF ||*/ g_ioMgr.get_in_bit( nLock_2 ) != IO_ON)
			{
				job.bcr2_step = BCR2_PICK_LABEL_BTM_RIGHT_BACKWPRD;
				break;
			}

			job.bcr2_step = BCR2_PICK_LABEL_ROTATE_CHK;

		}
		break;

	case BCR2_PICK_LABEL_BTM_LEFT_BACKWPRD:
		ReqMBtmVac( EBVS_LEFT , BACKWARD );
		ReqMBtmVac( EBVS_RIGHT, BACKWARD );
		job.bcr2_step = BCR2_PICK_LABEL_BTM_LEFT_BACKWPRD_CHK;
		break;

	case BCR2_PICK_LABEL_BTM_LEFT_BACKWPRD_CHK:
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr2_step = BCR2_PICK_LABEL_BTM_CHK;
		break;

	case BCR2_PICK_LABEL_BTM_RIGHT_BACKWPRD:
		ReqMBtmVac( EBVS_RIGHT, BACKWARD );
		job.bcr2_step = BCR2_PICK_LABEL_BTM_RIGHT_BACKWPRD_CHK;
		break;

	case BCR2_PICK_LABEL_BTM_RIGHT_BACKWPRD_CHK:
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;//2014,1205 GetMBtmVac -> GetM2BtmVac 변경
		job.bcr2_step = BCR2_PICK_LABEL_BTM_CHK;
		break;

	case BCR2_PICK_LABEL_ROTATE_CHK://2014,1205 
		{
// 			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_R1);
// 			if( 0 && dPos > st_motor[M_BCR_ATTACH1_R1].d_pos[P_R_BCR_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_R1] )
// 			{
// 				job.bcr2_step = BCR2_PICK_R1_SAFETY;
// 				break;
// 			}
// 			dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_R2);
// 			if( 0 && dPos > st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_R2] )
// 			{
// 				job.bcr2_step = BCR2_PICK_R2_SAFETY;
// 				break;
// 			}
// 
// 			job.bcr2_step = BCR2_PICK_LABEL_MOVE_READY_POS;		
			mn_mot_flag[1][0] = 0; mn_mot_flag[1][1] = 0;
			job.bcr2_step = BCR2_PICK_R1_SAFETY;
			
		}
		break;

	case BCR2_PICK_R1_SAFETY://2014,1205
		{
// 			int nRet1,nRet2;
// 			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R1, st_motor[M_BCR_ATTACH1_R1].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R2, st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			if( 1 || nRet1 == BD_GOOD && nRet2 == BD_GOOD)
// 			{
// 				job.bcr2_step = BCR2_PICK_LABEL_ROTATE_CHK;
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1305, CTL_dWARNING, alarm.mstr_code );
// 			}
//			for(int i=0; i<2; i++)
//			{
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_fwd_cylinder[i], IO_OFF);
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_bwd_cylinder[i], IO_ON);
//			}		
			ReqMRotateFwdBwd( 0 ,BACKWARD);
			ReqMRotateFwdBwd( 1 ,BACKWARD);
			job.bcr2_step = BCR2_PICK_R2_SAFETY;
			m_dwTime_Robot2 = GetCurrentTime();
		}
		break;

	case BCR2_PICK_R2_SAFETY://2014,1205
		{
// 			int nRet1;
// 			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R2, st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD)
// 			{
// 				job.bcr2_step = BCR2_PICK_LABEL_ROTATE_CHK;
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1306, CTL_dWARNING, alarm.mstr_code );
// 			}
			int nRet1,nRet2,nRet3,nRet4;
//			if( GetCurrentTime() - m_dwTime_Robot2 < 0 ) m_dwTime_Robot2 = GetCurrentTime();
			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;

			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_OFF);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_ON); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_OFF);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_ON);
			
			if(nRet1 == IO_OFF && nRet2 == IO_ON && nRet3 == IO_OFF && nRet4 == IO_ON)
			{
				//2015.0827
				mn_bcr_pick_error[0] = mn_bcr_pick_error[1] = CTL_NO;
				st_handler.mn_retest_cnt = 0;
				job.bcr2_step = BCR2_PICK_LABEL_MOVE_READY_POS;
			}		
			else
			{
				job.bcr2_step = BCR2_PICK_R1_SAFETY;
			}
		}
		break;

	case BCR2_PICK_LABEL_MOVE_READY_POS:
		{
			double dPos = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_X);
			double dPos1 = COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Y);
			int nRet_1 = COMI.Check_MotPosRange(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2], COMI.md_allow_value[M_BCR_ATTACH1_X]);//COMI.mn_allow_value[n_MotNum]
			int nRet_2 = COMI.Check_MotPosRange(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2], COMI.md_allow_value[M_BCR_ATTACH1_Y]);
			if (nRet_1 != BD_GOOD || nRet_2 != BD_GOOD) //Y축이 작업 가능한 위치에 와 있는지 확인한다 
			{
				job.bcr2_step = BCR2_PICK_LABEL_MOVE_READY;	//처음으로 가서 다시 시작한다 
				break;
			}

			if( dPos > st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_X] &&
				dPos < st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_X] &&
				dPos > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				dPos < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				job.bcr2_step = BCR2_PICK_LABEL_PICK_READY;
				break;
			}
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[2], IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[3], IO_OFF);

			job.bcr2_step = BCR2_PICK_LABEL_MOVE_READY;	
			
		}
		break;

	case BCR2_PICK_LABEL_MOVE_READY://2014,1205 M_BCR_ATTACH1_X -> M_BCR_ATTACH2_X 변경
		{
// 			int nRet = CTL_Lib.Single_Move( M_BCR_ATTACH2_X, st_motor[M_BCR_ATTACH2_X].d_pos[P_X_BCR_PICK], st_basic.nRunSpeed );
// 			if( nRet == BD_GOOD )
// 			{
// 				job.bcr2_step = BCR2_PICK_LABEL_PICK_READY;
// 			}
// 			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1307, CTL_dWARNING, alarm.mstr_code );
// 			}
			double m_dPos[2];
			m_dPos[0] = st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2];
			m_dPos[1] = st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2];
			long lAxis[2];
			lAxis[0] = M_BCR_ATTACH1_X;
			lAxis[1] = M_BCR_ATTACH1_Y;
			
			double dSpeedRatio[3];
			dSpeedRatio[0] = (double)st_basic.nRunSpeed;
			dSpeedRatio[1] = (double)st_basic.nRunSpeed;
			dSpeedRatio[2] = (double)st_basic.nRunSpeed;
			
			int nRet = CTL_Lib.Linear_Move( M_ROBOT_BARCODE_INDEX, 2, lAxis, m_dPos, dSpeedRatio );
			if( nRet == BD_GOOD )
			{
				job.bcr2_step = BCR2_PICK_LABEL_PICK_READY;		
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1307, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		

	case BCR2_PICK_LABEL_PICK_READY:
		{
			if(job.iRobotFirst != -1)
			{
					g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[job.iRobotFirst + 2], IO_OFF);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_ON);//2014,1117
					ReqMTopVac( job.iRobotFirst, BACKWARD);
//					ReqM2BtmVac( job.iRobotFirst, BACKWARD);
			}
			if(job.iRobotSecond != -1)
			{
					g_ioMgr.set_out_bit(st_io.o_distribute_plate_vacuum[job.iRobotSecond + 2], IO_OFF);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_ON);
					ReqMTopVac( job.iRobotSecond, BACKWARD);
//					ReqM2BtmVac( job.iRobotSecond, FORWARD);
			}
			mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
			job.bcr2_step = BCR2_PICK_LABEL_DOWN;	
		}
		break;

	case BCR2_PICK_LABEL_DOWN:
		{
			int nRet1,nRet2;
			if(job.iRobotFirst != -1)
			{
				if( (st_handler.mn_retest_cnt == 0 && mn_bcr_pick_error[job.iRobotFirst] == CTL_NO) ||
					(st_handler.mn_retest_cnt >= 1 && mn_bcr_pick_error[job.iRobotFirst] == CTL_YES) )
				{
					nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK2], st_basic.nRunSpeed );
				}
				else
				{
					nRet1 = BD_ERROR;
				}
			}
			else
			{
				nRet1 = BD_ERROR;
			}
			if(job.iRobotSecond != -1)
			{				
				if( (st_handler.mn_retest_cnt == 0 && mn_bcr_pick_error[job.iRobotSecond] == CTL_NO) ||
					(st_handler.mn_retest_cnt >= 1 && mn_bcr_pick_error[job.iRobotSecond] == CTL_YES) )
				{
					nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK2], st_basic.nRunSpeed );
				}
				else
				{
					nRet2 = BD_ERROR;
				}
			}
			else
			{
				nRet2 = BD_ERROR;
			}

			if( nRet1 == BD_GOOD ) mn_mot_flag[1][0] = 1;
			if( nRet2 == BD_GOOD ) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
				////2014.1120 ysj
				if( job.iRobotFirst != -1)
				{
					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_ON);
// 					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotFirst], IO_ON);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_ON);//2014,1117
				}
				if( job.iRobotSecond != -1)
				{
					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_ON);
// 					g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotSecond], IO_ON);
					g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_ON);//2014,1117
				}
				
				job.bcr2_step = BCR2_PICK_LABEL_DOWN_CHK;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1308, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR2_PICK_LABEL_DOWN_CHK:
		{
			if(job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
//				if( GetM2BtmVac( job.iRobotFirst ) != FB_NONE ) break;
			}
			if(job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
//				if( GetM2BtmVac( job.iRobotSecond ) != FB_NONE ) break;
			}
			job.bcr2_step = BCR2_PICK_LABEL_VACUUM;	

		}
		break;

	case BCR2_PICK_LABEL_VACUUM:
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_ON);
// 				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotFirst], IO_ON);
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_ON);
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_ON);
// 				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotSecond], IO_ON);
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_ON);
			}
			job.bcr2_step = BCR2_PICK_LABEL_VACUUM_CHK;	
			m_dwTime_Robot2 = GetCurrentTime();
		}
		break;

	case BCR2_PICK_LABEL_VACUUM_CHK:
		{
// 			if( GetCurrentTime() - m_dwTime_Robot2 < 0 ) m_dwTime_Robot2 = GetCurrentTime();
// 			if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PICK_VACUUM][IO_ON] ) break;

			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_ON);

				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
				{
				}
				else 
				{
					if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] ) break;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1309, CTL_dWARNING, strError );
					}
					else
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1310, CTL_dWARNING, strError );
					}
// 					break;
				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_ON);
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
				{
				}
				else 
				{
					if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] ) break;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1311, CTL_dWARNING, strError );
					}
					else
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1312, CTL_dWARNING, strError );
					}
// 					break;
				}
			}
			m_dwTime_Robot2 = GetCurrentTime();//2015.0120 ysj
			mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
			job.bcr2_step = BCR2_PICK_LABEL_UP;			
		}
		break;

	case BCR2_PICK_LABEL_UP:
		{
			if( GetCurrentTime() - m_dwTime_Robot2 < 0 ) m_dwTime_Robot2 = GetCurrentTime();
			if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PICK_VACUUM][IO_ON] ) break;

			int nnSite = 0;
			if(job.iRobotFirst != -1) nnSite = job.iRobotFirst;
			else if(job.iRobotSecond != -1) nnSite = job.iRobotSecond;
			if( GetCurrentTime() - st_handler.m_lBcrOutTime[nnSite + 2] < 0 ) st_handler.m_lBcrOutTime[nnSite + 2]  = GetCurrentTime();
			if( GetCurrentTime() - st_handler.m_lBcrOutTime[nnSite + 2] > 60000 ) 
			{
				if( GetCurrentTime() - m_dwTime_Robot2 < 0 ) m_dwTime_Robot2 = GetCurrentTime();
				if( GetCurrentTime() - m_dwTime_Robot2 < 3500 ) break;
			}
			////
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				job.bcr2_step = BCR2_PICK_LABEL_UP_VACUUM_CHK;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1315, CTL_dWARNING, alarm.mstr_code );
			}
		
		}
		break;

	case BCR2_PICK_LABEL_UP_VACUUM_CHK:
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst+2], IO_OFF);
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
				{
				}
				else 
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
						if(mn_bcr_pick_error[job.iRobotFirst] == CTL_YES)
						{
							CString strError;
							strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
							CTL_Lib.Alarm_Error_Occurrence( 1316, CTL_dWARNING, strError );
						}
						else
						{
							mn_bcr_pick_error[job.iRobotFirst] = CTL_YES;
							st_handler.mn_retest_cnt++;
							mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
							job.bcr2_step = BCR2_PICK_LABEL_DOWN;
							break;
						}
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot2 Left Top Vacuum Off Check Error.";
////
					}
					else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
						CString strError;
						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
						CTL_Lib.Alarm_Error_Occurrence( 1317, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot2 Left Bottom Vacuum Off Check Error.";
////
					}
					////2015.0120 ysj
// 					Func.OnSet_IO_Port_Stop();
// 					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
					job.bcr2_step = BCR2_STEP(252);
					////
					break;
				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond+2], IO_OFF);
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
				{
				}
				else
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
						if(mn_bcr_pick_error[job.iRobotSecond] == CTL_YES)
						{
							CString strError;
							strError.Format("5%04d0",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
							CTL_Lib.Alarm_Error_Occurrence( 1318, CTL_dWARNING, strError );
						}
						else
						{
							mn_bcr_pick_error[job.iRobotSecond] = CTL_YES;
							st_handler.mn_retest_cnt++;
							mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
							job.bcr2_step = BCR2_PICK_LABEL_DOWN;
							break;
						}
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot2 Left Top Vacuum Off Check Error.";
					}
					else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_OFF )
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
						CString strError;
						strError.Format("5%04d0",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
						CTL_Lib.Alarm_Error_Occurrence( 1319, CTL_dWARNING, strError );
// 						st_msg.mstr_event_msg[0] = "Distribution Label Robot2 Left Bottom Vacuum Off Check Error.";
					}
// 					COMI.mn_run_status = dSTOP;
// 					::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
					job.bcr2_step = BCR2_STEP(252);
					break;
				}
			}
			job.bcr2_step = BCR2_PICK_LABEL_FINISH;	
			
			if( job.iRobotFirst != -1)
			{
// 				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst], IO_OFF);
				ReqMTopVac( job.iRobotFirst, BACKWARD);
				ReqMBtmVac( job.iRobotFirst, BACKWARD);
				g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst + 2], IO_OFF);
//				COMI.Start_SingleMove(M_BCR_FEEDER_1+job.iRobotFirst, st_motor[M_BCR_FEEDER_1+job.iRobotFirst].d_pos[P_BCR_FEEDER_PICK], st_basic.nRunSpeed);
			}
			if( job.iRobotSecond != -1)
			{
// 				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
				ReqMTopVac( job.iRobotSecond, BACKWARD);
				ReqMBtmVac( job.iRobotSecond, BACKWARD);
				g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond + 2], IO_OFF);
//				COMI.Start_SingleMove(M_BCR_FEEDER_1+job.iRobotSecond, st_motor[M_BCR_FEEDER_1+job.iRobotSecond].d_pos[P_BCR_FEEDER_PICK], st_basic.nRunSpeed);
			}

		}
		break;
		
	case 251:
		if( m_fbmrotatefwdbwd[EBVS_LEFT] != FB_NONE) break;
		if( m_fbmrotatefwdbwd[EBVS_RIGHT] != FB_NONE) break;
		job.bcr2_step = BCR2_STEP(252);
		break;
		
	case 252:
		{
			bool nfwd1 = CheckMRotateFwdBwd( EBVS_LEFT, IO_OFF );
			bool nfwd2 = CheckMRotateFwdBwd( EBVS_RIGHT, IO_OFF );
			if( nfwd1 == true && nfwd2 == true )
			{
				ReqMTopVac( EBVS_LEFT , FORWARD );
				ReqMTopVac( EBVS_RIGHT , FORWARD );
				ReqMBtmVac( EBVS_LEFT , BACKWARD );
				ReqMBtmVac( EBVS_RIGHT, BACKWARD );
				job.bcr2_step = BCR2_STEP(253);			
			}
			else
			{
				ReqMRotateFwdBwd( EBVS_LEFT ,BACKWARD);
				ReqMRotateFwdBwd( EBVS_RIGHT ,BACKWARD);
				job.bcr2_step = BCR2_STEP(251);			
			}
		}
		break;
		
	case 253:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
		job.bcr2_step = BCR2_STEP(254);
		break;

	case 254:
		{
// 			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD)
// 			{
// 				job.bcr2_step = BCR2_STEP(255);
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 271, CTL_dWARNING, alarm.mstr_code );
// 			}

			double m_dPos[2];
			m_dPos[0] = st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT];
			m_dPos[1] = st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT];
			long lAxis[2];
			lAxis[0] = M_BCR_ATTACH1_X;
			lAxis[1] = M_BCR_ATTACH1_Y;
			
			double dSpeedRatio[3];
			dSpeedRatio[0] = (double)st_basic.nRunSpeed;
			dSpeedRatio[1] = (double)st_basic.nRunSpeed;
			dSpeedRatio[2] = (double)st_basic.nRunSpeed;
			
			int nRet = CTL_Lib.Linear_Move( M_ROBOT_BARCODE_INDEX, 2, lAxis, m_dPos, dSpeedRatio );
			if( nRet == BD_GOOD )
			{
				job.bcr2_step = BCR2_STEP(255);
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 271, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;
		
	case 255:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				job.bcr2_step = BCR2_STEP(256);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 260, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 256:
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_ON);
		m_dwTime_Robot2 = GetCurrentTime();
		job.bcr2_step = BCR2_STEP(260);
		break;
		
	case 260:
		if( GetCurrentTime() - m_dwTime_Robot2 < 0) m_dwTime_Robot2 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		mn_mot_flag[1][0] = 0;
		mn_mot_flag[1][1] = 0;
		job.bcr2_step = BCR2_STEP(261);
		break;
		
	case 261:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_OFF);				
// 				::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
				job.bcr2_step = BCR2_STEP(262);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 260, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 262:
		{
			ReqMTopVac( EBVS_LEFT , BACKWARD );
			ReqMTopVac( EBVS_RIGHT , BACKWARD );
			ReqMBtmVac( EBVS_LEFT , BACKWARD );
			ReqMBtmVac( EBVS_RIGHT, BACKWARD );
			job.bcr2_step = BCR2_STEP(263);			
		}
		break;
		
	case 263:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr2_step = BCR2_STEP(264);
		break;

	case 264:
		if( st_basic.n_mode_device && job.iRobotFirst != -1)
		{
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515081 1 00 "Distribution Label Robot1 Left Top Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 1261, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515091 1 00 "Distribution Label Robot1 Left Bottom Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 1262, CTL_dWARNING, strError );
				break;
			}
			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotFirst+2], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotFirst+2], IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(1265, dWARNING, strError);
				break;
			}
		}
		if( st_basic.n_mode_device && job.iRobotSecond != -1)
		{
			//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 1263, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
			{
				//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 1264, CTL_dWARNING, strError );
				break;
			}
			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotSecond+2], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotSecond+2], IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(1266, dWARNING, strError);				
				break;
			}
		}
		job.bcr2_step = BCR2_STEP(265);
		break;
		
	case 265:
		if( job.iRobotFirst != -1)
		{
			ReqMTopVac( job.iRobotFirst, BACKWARD);
			ReqMBtmVac( job.iRobotFirst, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst + 2], IO_OFF);
		}
		if( job.iRobotSecond != -1)
		{
			ReqMTopVac( job.iRobotSecond, BACKWARD);
			ReqMBtmVac( job.iRobotSecond, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond + 2], IO_OFF);
		}
		job.bcr2_step = BCR2_STEP(266);
		break;
		
	case 266:
		{			
			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_OFF);//2014,1117
				
			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_OFF);//2014,1117
			}
			
			if( job.iRobotFirst != -1)
			{
// 				st_bcr_feeder[job.iRobotFirst + 2].st_bcr.bExist = false;
// 				memset( &st_bcr_feeder[job.iRobotFirst + 2], 0x00, sizeof(st_bcr_feeder[job.iRobotFirst + 2]));
				st_bcr_feeder[job.iRobotFirst + 2].st_bcr.nState = EMBS_FAIL;
			}
			if( job.iRobotSecond != -1)
			{				
// 				st_bcr_feeder[job.iRobotSecond + 2].st_bcr.bExist = false;
// 				memset( &st_bcr_feeder[job.iRobotSecond + 2], 0x00, sizeof(st_bcr_feeder[job.iRobotSecond + 2]));
				st_bcr_feeder[job.iRobotSecond + 2].st_bcr.nState = EMBS_FAIL;
			}			
			
			Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();
			Func.Handler_Recovery_Data_Write();
		}
		break;

////
	case BCR2_PICK_LABEL_FINISH:
		{

			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_OFF);//2014,1117
				
			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_OFF);//2014,1117
			}

			if( job.iRobotFirst != -1)
			{
				st_bcr_rbt[1].bPick[job.iRobotFirst] = st_bcr_feeder[job.iRobotFirst + 2].st_bcr.bOut;
				st_bcr_feeder[job.iRobotFirst + 2].st_bcr.bExist = false;
				memcpy( &st_bcr_rbt[1].st_bcr[job.iRobotFirst], &st_bcr_feeder[job.iRobotFirst + 2].st_bcr, sizeof(st_bcr_feeder[job.iRobotFirst + 2].st_bcr));
				memset( &st_bcr_feeder[job.iRobotFirst + 2], 0x00, sizeof(st_bcr_feeder[job.iRobotFirst + 2]));
			}
			if( job.iRobotSecond != -1)
			{
				//2016.0726
				//st_bcr_rbt[1].bPick[job.iRobotSecond+2] = st_bcr_feeder[job.iRobotSecond + 2].st_bcr.bOut;
				st_bcr_rbt[1].bPick[job.iRobotSecond] = st_bcr_feeder[job.iRobotSecond + 2].st_bcr.bOut;
				st_bcr_feeder[job.iRobotSecond + 2].st_bcr.bExist = false;
				memcpy( &st_bcr_rbt[1].st_bcr[job.iRobotSecond], &st_bcr_feeder[job.iRobotSecond + 2].st_bcr, sizeof(st_bcr_feeder[job.iRobotSecond + 2].st_bcr));
				memset( &st_bcr_feeder[job.iRobotSecond + 2], 0x00, sizeof(st_bcr_feeder[job.iRobotSecond + 2]));
			}
		
			// UI 업데이트
			if( st_handler.cwnd_main )
			{
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDT_SEL_TRAY);
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDR_PICKER);
				st_handler.cwnd_main->PostMessage( WM_DRAW_DATA_MAIN, EDDS_TESTSITE);
			}
// 			Func.Handler_Recovery_Data_Write();
			job.bcr2_step = BCR2_STEP(271);
			mn_mot_flag[1][0]=0;mn_mot_flag[1][1]=0;mn_mot_flag[1][2]=0;
		}
		break;

	////2014,1205
	case 271://2014,1205
		{
			int nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
			int nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE], st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD )
			{
				mn_mot_flag[1][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD )
			{
				mn_mot_flag[1][1] = CTL_YES;
			}
			
			if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES )
			{
				mn_mot_flag[1][0] = 0; mn_mot_flag[1][1] = mn_mot_flag[1][2] = 0; //clear 
				job.bcr2_step = BCR2_STEP(272);			
				if( job.iRobotFirst != -1)
				{
					ReqMRotateFwdBwd( job.iRobotFirst , FORWARD);
				}
				if( job.iRobotSecond != -1)
				{
					ReqMRotateFwdBwd( job.iRobotSecond , FORWARD);
				}
			}
			else if( nRet1== BD_ERROR || nRet1 == BD_SAFETY  )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1320, CTL_dWARNING, alarm.mstr_code );
			}			
		}
		break;
		
	case 272:
		{
			int nRet1 = COMI.Check_SingleMove(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE]);  // 이동 완료 ?
			int nRet2 = COMI.Check_SingleMove(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE]);  // 이동 완료 ?
			if( nRet1 == BD_GOOD)
			{
				mn_mot_flag[1][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD)
			{
				mn_mot_flag[1][1] = CTL_YES;
			}
			
			if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES)
			{
				mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
				job.bcr2_step = BCR2_STEP(273);
				m_dwTime_Robot2 = GetCurrentTime();//2014,1205
// 				if( job.iRobotFirst != -1)
// 				{
// 					ReqMRotateFwdBwd( job.iRobotFirst ,FORWARD);
// 				}
// 				if( job.iRobotSecond != -1)
// 				{
// 					ReqMRotateFwdBwd( job.iRobotSecond ,FORWARD);
// 				}
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
			{
				job.bcr2_step = BCR2_STEP(271);
				CTL_Lib.Alarm_Error_Occurrence( 1321, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
		
	case 273://roller ready//2014,1205
		{
			int nRet1,nRet2,nRet3,nRet4;
			CString strError;

// 			if( job.iRobotFirst != -1)
 				if( m_fbmrotatefwdbwd[0] != FB_NONE) break;//2015.0120 ysj
// 			if( job.iRobotSecond != -1)
 				if( m_fbmrotatefwdbwd[1] != FB_NONE) break;//2015.0120 ysj
////2015.0120 ysj
// 			if( m_fbm2rotatefwdbwd[0] != FB_NONE) break;
// 			if( m_fbm2rotatefwdbwd[1] != FB_NONE) break;
////
//			if( GetCurrentTime() - m_dwTime_Robot2 < 0 ) m_dwTime_Robot2 = GetCurrentTime();
			if( job.iRobotFirst != -1)
			{
				nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_ON);//place position
				nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_OFF); //pick position
			}
			else
			{
				nRet1 = IO_ON;
				nRet2 = IO_OFF;
			}
			if( job.iRobotSecond != -1)
			{
				nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_ON);
				nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_OFF);
			}
			else
			{
				nRet3 = IO_ON;
				nRet4 = IO_OFF;
			}			
			
			if(nRet1 == IO_ON && nRet2 == IO_OFF && nRet3 == IO_ON && nRet4 == IO_OFF)
			{
				Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();
				Func.Handler_Recovery_Data_Write();
			}
			else
			{
				if(nRet1 != IO_ON) 
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 1322, CTL_dWARNING, strError );
				}
				else if(nRet2 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 1323, CTL_dWARNING, strError );
				}
				else if(nRet3 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 1324, CTL_dWARNING, strError );
				}
				else if(nRet4 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 1325, CTL_dWARNING, strError );
				}
			}
		}
		break;



	////
	case BCR2_PLACE_LABEL_READY:
		{//2015.0327
			bool bWork = true;
			int nRet1,nRet2;
			CString strError,strRbt,strIDBuff;
			if( job.iRobotFirst != -1)
			{
				if( st_bcr_rbt[1].st_bcr[job.iRobotFirst].nState == EMBS_FAIL )
				{
					bWork = false;
				}
				//2016.0812
				strRbt.Format("%s", st_bcr_rbt[1].st_bcr[1].c_serial);
				strIDBuff.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_serial[0]);
				strError = strIDBuff.Left(strIDBuff.GetLength()-1);
				if( !Func.CmpStrFile(strRbt, strError) )
				{
					strError = _T( "650000" );
					CTL_Lib.Alarm_Error_Occurrence( 8269, CTL_dWARNING, strError );
					break;
				}
			}
			if( job.iRobotSecond != -1)
			{
				if( st_bcr_rbt[1].st_bcr[job.iRobotSecond].nState == EMBS_FAIL )
				{
					bWork = false;
				}
				//2016.0812
				strRbt.Format("%s", st_bcr_rbt[1].st_bcr[0].c_serial);
				strIDBuff.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_serial[1]);
				strError = strIDBuff.Left(strIDBuff.GetLength()-1);
				if( !Func.CmpStrFile(strRbt, strError) )
				{
					strError = _T( "650000" );
					CTL_Lib.Alarm_Error_Occurrence( 8369, CTL_dWARNING, strError );
					break;
				}
			}
			
			if(bWork == false)//reject
			{
				job.bcr2_step = BCR2_STEP(432);
			}
			else
			{
				nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
				nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE], st_basic.nRunSpeed );
				
				if( nRet1 == BD_GOOD)
				{
					mn_mot_flag[1][0] = CTL_YES;
				}
				if( nRet2 == BD_GOOD)
				{
					mn_mot_flag[1][1] = CTL_YES;
				}
				
				if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES)
				{
					mn_mot_flag[1][0] = 0; mn_mot_flag[1][1] = mn_mot_flag[1][2] = 0; //clear 
					job.bcr2_step = BCR2_PLACE_LABEL_X_READY;
				}			
				else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
				{
					CTL_Lib.Alarm_Error_Occurrence( 1327, CTL_dWARNING, alarm.mstr_code );
				}
			}			
			
		}
		break;

	////2014,1205
	case BCR2_PLACE_LABEL_X_READY:
		{
			int nRet1 = COMI.Check_SingleMove(M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE]);
			int nRet2 = COMI.Check_SingleMove(M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE]);
			
			if( nRet1 == BD_GOOD)
			{
				mn_mot_flag[1][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD)
			{
				mn_mot_flag[1][1] = CTL_YES;
			}
			
			if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES)
			{
				mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
				job.bcr2_step = BCR2_PLACE_LABEL_READY2;
				m_dwTime_Robot2 = GetCurrentTime();
				//if( job.iRobotFirst != -1)
				//{
					ReqMRotateFwdBwd( 0 ,FORWARD);
				//}
				//if( job.iRobotSecond != -1)
				//{
					ReqMRotateFwdBwd( 1 ,FORWARD);
				//}
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
			{
				job.bcr2_step = BCR2_PLACE_LABEL_READY;
				mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
				CTL_Lib.Alarm_Error_Occurrence( 1328, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
	////
	case BCR2_PLACE_LABEL_READY2://roller ready//2014,1205
		{			
			int nRet1,nRet2,nRet3,nRet4;
			CString strError;
			
			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
			
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_ON);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_OFF); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_ON);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_OFF);
			
			if(nRet1 == IO_ON && nRet2 == IO_OFF && nRet3 == IO_ON && nRet4 == IO_OFF)
			{
				double dpos = COMI.Get_MotCurrentPos(M_INDEX_X);
				if( dpos > st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS] - COMI.md_allow_value[M_INDEX_X] && dpos < st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS] + COMI.md_allow_value[M_INDEX_X] )
				{
					job.bcr2_step = BCR2_PLACE_LABEL_DOWN;
				}
				else
				{
					job.bcr2_step = BCR2_PLACE_LABEL_ROLLER_X_POS;
				}
			}
			else
			{
				if( job.iRobotFirst != -1)
				{
					if(nRet1 != IO_ON) 
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 1329, CTL_dWARNING, strError );
					}
					else if(nRet2 != IO_OFF)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 1330, CTL_dWARNING, strError );
					}
				}
				if( job.iRobotSecond != -1)
				{
					if(nRet3 != IO_ON)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 1331, CTL_dWARNING, strError );
					}
					else if(nRet4 != IO_OFF)
					{
						strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 1332, CTL_dWARNING, strError );
					}
				}
			}			

		}
		break;

	case BCR2_PLACE_LABEL_ROLLER_X_POS:
		{
			int	nRet = CTL_Lib.Single_Move( M_INDEX_X, st_motor[M_INDEX_X].d_pos[P_X_ROLLER_POS], st_basic.nRunSpeed );
			if( nRet == BD_GOOD )
			{
				job.bcr2_step = BCR2_PLACE_LABEL_DOWN;
			}
			else if( nRet == BD_ERROR || nRet == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1333, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;	


	case BCR2_PLACE_LABEL_DOWN:
		{//제품이 도달되어 있는지 체크한다.

			int nRet1,nRet2;
// 			if(job.iRobotFirst != -1)
// 			{
				nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN], st_basic.nRunSpeed );
// 			}
// 			else
// 			{
// 				nRet1 = BD_GOOD;
// 			}
// 			if(job.iRobotSecond != -1)
// 			{				
				nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN], st_basic.nRunSpeed );
// 			}
// 			else
// 			{
// 				nRet2 = BD_GOOD;
// 			}
			if(nRet1 == BD_GOOD && nRet2 == BD_GOOD/* && nRet3 == BD_GOOD*/)
			{
				job.bcr2_step = BCR2_PLACE_LABEL_PUSH;
				ReqBoxUpDn( FORWARD);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY/* || nRet3 == BD_ERROR || nRet3 == BD_SAFETY */)
			{
				CTL_Lib.Alarm_Error_Occurrence( 1334, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;
	
	case BCR2_PLACE_LABEL_PUSH://2014,1205
		{
			int nRet3 = CTL_Lib.Single_Move( M_INDEX_ROLLER1, st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_POS], st_basic.nRunSpeed );
			if( nRet3 == BD_GOOD)
			{
// 				if(job.iRobotFirst != -1)
// 				{
// 					ReqM2TopVac( job.iRobotFirst, FORWARD);
// 					ReqRollingFwdBwd( 1, job.iRobotFirst, FORWARD);
					ReqMTopVac( 0, FORWARD);
					ReqRollingFwdBwd( 0, FORWARD);
// 				}
// 				if(job.iRobotSecond != -1)
// 				{
// 					ReqM2TopVac( job.iRobotSecond, FORWARD);
// 					ReqRollingFwdBwd( 1, job.iRobotSecond, FORWARD);
					ReqMTopVac( 1, FORWARD);
					ReqRollingFwdBwd( 1, FORWARD);
//				}
				//ReqRollingFwdBwd( 2, FORWARD);
			
				job.bcr2_step = BCR2_PLACE_LABEL_XPLACE;
			}
			else if( nRet3 == BD_ERROR || nRet3 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1335, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;

	////2014,1205
	case BCR2_PLACE_LABEL_XPLACE:
		{
			if( m_fbboxupdn != FB_NONE ) break;
			if( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] > (st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] + 5) || st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE] < (st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_DOWN]))
			{
				if(st_handler.cwnd_list != NULL)
				{
// 					sprintf(st_msg.c_abnormal_msg, "[BAR ROBOT] Picker Down pos is more than Picker Pick(5mm) or is less than. Position Error Check ");
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
//					break;
				}
			}
// 			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PLACE], st_basic.nRunSpeed );
// 			if( nRet1 == BD_GOOD )
// 			{
				job.bcr2_step = BCR2_PLACE_LABEL_PUSH_CHK;
// 			}
// 			else if( nRet1 == BD_ERROR )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1336, CTL_dWARNING, alarm.mstr_code );
// 			}
		}
		break;		
		
	////
	case BCR2_PLACE_LABEL_PUSH_CHK:
		{
// 			if( job.iRobotFirst != -1)
// 			{
// 				if( GetM2TopVac( job.iRobotFirst ) != FB_NONE ) break;
// 				ReqM2BtmVac( job.iRobotFirst, FORWARD);
// 				if( GetRollingFwdBwd( 1, job.iRobotFirst ) != FB_NONE ) break;
				if( GetMTopVac( 0 ) != FB_NONE ) break;
				ReqMBtmVac( 0, FORWARD);
				if( GetRollingFwdBwd( 0 ) != FB_NONE ) break;
// 			}
// 			if( job.iRobotSecond != -1)
// 			{
				if( GetMTopVac( 1 ) != FB_NONE ) break;
				ReqMBtmVac( 1, FORWARD);
				if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;
// 			}
			st_var.n_tboxmv_sealing_cv_mode = CTL_YES;//2015.0331
			//if( GetRollingFwdBwd( 2 ) != FB_NONE ) break;
			job.bcr2_step = BCR2_PLACE_LABEL_PUSH_VACUUM;

		}
		break;

	case BCR2_PLACE_LABEL_PUSH_VACUUM:
		{
// 			if( job.iRobotFirst != -1)
// 				if( GetM2BtmVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( 0 ) != FB_NONE ) break;
// 			if( job.iRobotSecond != -1)
// 				if( GetM2BtmVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( 1 ) != FB_NONE ) break;

				st_var.n_tboxmv_sealing_cv_mode = CTL_NO;//2015.0331
					
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[0], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[0], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[1], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[1], IO_OFF);
			job.bcr2_step = BCR2_PLACE_LABEL_VACUUM_CHK;	
		}
		break;

	case BCR2_PLACE_LABEL_VACUUM_CHK:
		{
			if(job.iRobotFirst != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_ON);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_ON);
// 				ReqM2BtmVac( job.iRobotFirst, BACKWARD);
// 				ReqRollingFwdBwd( 1, job.iRobotFirst, BACKWARD);
			}
			ReqMBtmVac( 0, BACKWARD);
			ReqRollingFwdBwd( 0, BACKWARD);
			if(job.iRobotSecond != -1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_ON);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_ON);
// 				ReqM2BtmVac( job.iRobotSecond, BACKWARD);
// 				ReqRollingFwdBwd( 1, job.iRobotSecond, BACKWARD);
			}
			ReqMBtmVac( 1, BACKWARD);
			ReqRollingFwdBwd( 1, BACKWARD);
//			ReqRollingFwdBwd( 2, BACKWARD);
			job.bcr2_step = BCR2_PLACE_LABEL_PULL;
			m_dwTime_Robot2 = GetCurrentTime();
		}		
		break;

	case BCR2_PLACE_LABEL_PULL://2014,1205
		if( GetCurrentTime() - m_dwTime_Robot2 < 0) m_dwTime_Robot2 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		{
			if(job.iRobotFirst != -1)
			{
// 				if( GetM2BtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_OFF);
// 				ReqM2TopVac( job.iRobotFirst, BACKWARD);
// 				if( GetRollingFwdBwd( 1, job.iRobotFirst ) != FB_NONE ) break;
			}
			if(job.iRobotSecond != -1)
			{
// 				if( GetM2BtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_OFF);
// 				ReqM2TopVac( job.iRobotSecond, BACKWARD);
// 				if( GetRollingFwdBwd( 1, job.iRobotSecond ) != FB_NONE ) break;
			}
			if( GetMBtmVac( 0 ) != FB_NONE ) break;
			ReqMTopVac( 0, BACKWARD);
			if( GetRollingFwdBwd( 0 ) != FB_NONE ) break;
			if( GetMBtmVac( 1 ) != FB_NONE ) break;
			ReqMTopVac( 1, BACKWARD);
			if( GetRollingFwdBwd( 1 ) != FB_NONE ) break;
//			if( GetRollingFwdBwd( 2 ) != FB_NONE ) break;

			job.bcr2_step = BCR2_PLACE_LABEL_PULL_CHK;		
		}
		break;
		
	case BCR2_PLACE_LABEL_PULL_CHK:
		{
			if(job.iRobotFirst != -1)
			{
// 				if( GetM2TopVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotFirst], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotFirst], IO_OFF);
			}
			if( GetMTopVac( 0 ) != FB_NONE ) break;
			if(job.iRobotSecond != -1)
			{
// 				if( GetM2TopVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[job.iRobotSecond], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[job.iRobotSecond], IO_OFF);
			}
			if( GetMTopVac( 1 ) != FB_NONE ) break;
			job.bcr2_step = BCR2_PLACE_LABEL_VACUUM_RECHK;	
			m_dwTime_Robot2 = GetCurrentTime();
		}
		break;

	case BCR2_PLACE_LABEL_VACUUM_RECHK:
		if( GetCurrentTime() - m_dwTime_Robot2 < 0) m_dwTime_Robot2 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		{
			if( st_basic.n_mode_device && job.iRobotFirst != -1)
			{
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF &&
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_OFF )
				{
				}
				else 
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_OFF) == IO_ON )
					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt2_top_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1337, CTL_dWARNING, strError );
					}
					else
					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt2_btm_vacuum_chk[job.iRobotFirst]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1338, CTL_dWARNING, strError );
					}
					//break;
				}
			}
			if( st_basic.n_mode_device && job.iRobotSecond != -1)
			{
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_OFF) == IO_OFF &&
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_OFF) == IO_OFF )
				{
				}
				else if( GetCurrentTime() - m_dwTime_Robot2 > st_time.n_limit_time[E_WAIT_BCR_PICK_VACUUM] )
				{
// 					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt2_top_vacuum_chk[job.iRobotFirst], IO_OFF) == IO_ON )
// 					{//515080 1 00 "Distribution Label Robot1 Left Top Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt2_top_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1339, CTL_dWARNING, strError );
// 					}
// 					else
// 					{//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
// 						CString strError;
// 						strError.Format("5%04d0",st_io.i_distribute_rbt2_btm_vacuum_chk[job.iRobotSecond]);
// 						CTL_Lib.Alarm_Error_Occurrence( 1340, CTL_dWARNING, "515090" );
// 					}
// 					break;
				}
			}
			ReqBoxUpDn( BACKWARD);//2014,1205
			job.bcr2_step = BCR2_PLACE_LABEL_XDOWN_BACK;// BCR2_PLACE_LABEL_UP;//2014,1205	
		}
		break;

	case BCR2_PLACE_LABEL_XDOWN_BACK:
		{
			job.bcr2_step = BCR2_PLACE_LABEL_UP;
			mn_mot_flag[1][0] = 0;
			mn_mot_flag[1][1] = 0;
			mn_mot_flag[1][2] = 0;
		}
		break;
		
	case 431:
		if( m_fbmrotatefwdbwd[EBVS_LEFT] != FB_NONE) break;
		if( m_fbmrotatefwdbwd[EBVS_RIGHT] != FB_NONE) break;
		job.bcr2_step = BCR2_STEP(432);
		break;

		
	case 432:
		{
			bool nfwd1 = CheckMRotateFwdBwd( EBVS_LEFT, IO_OFF );
			bool nfwd2 = CheckMRotateFwdBwd( EBVS_RIGHT, IO_OFF );
			if( nfwd1 == true && nfwd2 == true )
			{
				ReqMTopVac( EBVS_LEFT , FORWARD );
				ReqMTopVac( EBVS_RIGHT , FORWARD );
				ReqMBtmVac( EBVS_LEFT , BACKWARD );
				ReqMBtmVac( EBVS_RIGHT, BACKWARD );
				job.bcr2_step = BCR2_STEP(433);			
			}
			else
			{
				ReqMRotateFwdBwd( EBVS_LEFT ,BACKWARD);
				ReqMRotateFwdBwd( EBVS_RIGHT ,BACKWARD);
				job.bcr2_step = BCR2_STEP(431);			
			}
		}
		break;
		
	case 433:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		mn_mot_flag[1][0] = mn_mot_flag[1][1] = 0;
		job.bcr2_step = BCR2_STEP(434);
		break;

	case 434:
		{
			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_REJECT], st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD)
			{
				job.bcr2_step = BCR2_STEP(435);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 471, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 435:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				job.bcr2_step = BCR2_STEP(436);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 472, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 436:
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_ON);
		g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_ON);
		m_dwTime_Robot2 = GetCurrentTime();
		job.bcr2_step = BCR2_STEP(440);
		break;
		
	case 440:
		if( GetCurrentTime() - m_dwTime_Robot2 < 0) m_dwTime_Robot2 = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Robot2 < st_time.n_wait_time[E_WAIT_BCR_PLACE_EJECT][IO_ON]) break;
		mn_mot_flag[1][0] = 0;
		mn_mot_flag[1][1] = 0;
		job.bcr2_step = BCR2_STEP(441);
		break;
		
	case 441:
		{
			int nRet1,nRet2;
			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1 , st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2 , st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1)
			{
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_LEFT], IO_OFF);				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[EBVS_RIGHT], IO_OFF);
				
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_LEFT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[EBVS_RIGHT], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[EBVS_RIGHT], IO_OFF);				
// 				::PostMessage(st_handler.hWnd, WM_MAIN_EVENT, CTL_YES, 0);
				job.bcr2_step = BCR2_STEP(442);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 473, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;
		
	case 442:
		{
			ReqMTopVac( EBVS_LEFT , BACKWARD );
			ReqMTopVac( EBVS_RIGHT , BACKWARD );
			ReqMBtmVac( EBVS_LEFT , BACKWARD );
			ReqMBtmVac( EBVS_RIGHT, BACKWARD );
			job.bcr2_step = BCR2_STEP(443);			
		}
		break;
		
	case 443:
		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) break;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) break;
		job.bcr2_step = BCR2_STEP(444);
		break;

	case 444:
		if( st_basic.n_mode_device && job.iRobotFirst != -1)
		{
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515081 1 00 "Distribution Label Robot1 Left Top Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 474, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst], IO_ON) == IO_ON )
			{//515091 1 00 "Distribution Label Robot1 Left Bottom Vacuum On Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotFirst]);
				CTL_Lib.Alarm_Error_Occurrence( 475, CTL_dWARNING, strError );
				break;
			}
// 			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotFirst+2], IO_ON) == IO_ON)
// 			{
// 				CString strError;
// 				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotFirst+2], IO_ON);
// 				CTL_Lib.Alarm_Error_Occurrence(476, dWARNING, strError);
// 				break;
// 			}
		}
		if( st_basic.n_mode_device && job.iRobotSecond != -1)
		{
			//  				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond], IO_OFF);
			if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON)
			{
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_top_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 477, CTL_dWARNING, strError );
				break;
			}
			else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond], IO_ON) == IO_ON )
			{
				//515090 1 00 "Distribution Label Robot1 Left Bottom Vacuum Off Check Error."
				CString strError;
				strError.Format("5%04d1",st_io.i_distribute_rbt_btm_vacuum_chk[job.iRobotSecond]);
				CTL_Lib.Alarm_Error_Occurrence( 478, CTL_dWARNING, strError );
				break;
			}
// 			else if(g_ioMgr.get_in_bit(st_io.i_bcr_label_chk[job.iRobotSecond+2], IO_ON) == IO_ON)
// 			{
// 				CString strError;
// 				strError.Format("5%04d%d", st_io.i_bcr_label_chk[job.iRobotSecond+2], IO_ON);
// 				CTL_Lib.Alarm_Error_Occurrence(479, dWARNING, strError);				
// 				break;
// 			}
		}
		job.bcr2_step = BCR2_STEP(445);
		break;
		
	case 445:
		if( job.iRobotFirst != -1)
		{
			ReqMTopVac( job.iRobotFirst, BACKWARD);
			ReqMBtmVac( job.iRobotFirst, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotFirst + 2], IO_OFF);
		}
		if( job.iRobotSecond != -1)
		{
			ReqMTopVac( job.iRobotSecond, BACKWARD);
			ReqMBtmVac( job.iRobotSecond, BACKWARD);
			g_ioMgr.set_out_bit(st_io.o_distribute_plate_updown[job.iRobotSecond + 2], IO_OFF);
		}
		job.bcr2_step = BCR2_STEP(446);
		break;
		
	case 446:
		{			
			if( job.iRobotFirst != -1)
			{
				if( GetMTopVac( job.iRobotFirst ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotFirst ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotFirst + 2], IO_OFF);//2014,1117
				
			}
			if( job.iRobotSecond != -1)
			{
				if( GetMTopVac( job.iRobotSecond ) != FB_NONE ) break;
				if( GetMBtmVac( job.iRobotSecond ) != FB_NONE ) break;
				g_ioMgr.set_out_bit(st_io.o_distribute_eject_vacuum[job.iRobotSecond + 2], IO_OFF);//2014,1117
			}
			
			if( job.iRobotFirst != -1)
			{
				st_bcr_rbt[1].bPick[job.iRobotFirst] = 0;
				st_bcr_rbt[1].st_bcr[job.iRobotFirst].bExist = 0;
				st_bcr_rbt[1].st_bcr[job.iRobotFirst].bOut = 0;
			}
			if( job.iRobotSecond != -1)
			{				
				st_bcr_rbt[1].bPick[job.iRobotSecond] = 0;					
				st_bcr_rbt[1].st_bcr[job.iRobotSecond].bExist = 0;
				st_bcr_rbt[1].st_bcr[job.iRobotSecond].bOut = 0;
			}			
			
			Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();
			Func.Handler_Recovery_Data_Write();
		}
		break;
	////
	case BCR2_PLACE_LABEL_UP://2014,1205
		{
			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			int nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP], st_basic.nRunSpeed );
			int nRet3 = CTL_Lib.Single_Move( M_INDEX_ROLLER1, st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY], st_basic.nRunSpeed );
			if(nRet1 == BD_GOOD) mn_mot_flag[1][0] = 1;
			if(nRet2 == BD_GOOD) mn_mot_flag[1][1] = 1;
			if(nRet3 == BD_GOOD) mn_mot_flag[1][2] = 1;
			if( mn_mot_flag[1][0] == 1 && mn_mot_flag[1][1] == 1 && mn_mot_flag[1][2] == 1 )
			{
				job.bcr2_step = BCR2_PLACE_LABEL_SAFETY;
				mn_mot_flag[1][0] = 0;
				mn_mot_flag[1][1] = 0;
				mn_mot_flag[1][2] = 0;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY || nRet3 == BD_ERROR || nRet3 == BD_SAFETY)
			{
				CTL_Lib.Alarm_Error_Occurrence( 1341, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case BCR2_PLACE_LABEL_SAFETY://2014,1205
		{
// 			int nRet1,nRet2,nRet3;
// 			nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK], st_basic.nRunSpeed );
// // 			nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R1, st_motor[M_BCR_ATTACH1_R1].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// // 			nRet3 = CTL_Lib.Single_Move( M_BCR_ATTACH1_R2, st_motor[M_BCR_ATTACH1_R2].d_pos[P_R_BCR_PICK], st_basic.nRunSpeed );
// 			nRet2 = nRet3 = BD_GOOD;
// 			if(nRet1 == BD_GOOD && nRet2 == BD_GOOD && nRet3 == BD_GOOD)
// 			{
// 				job.bcr2_step = BCR2_PLACE_LABEL_FINISH;
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY || nRet3 == BD_ERROR || nRet3 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1342, CTL_dWARNING, alarm.mstr_code );
// 			}
	
			int nRet1, nRet2;
			nRet1 = COMI.Start_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2], st_basic.nRunSpeed );
			nRet2 = COMI.Start_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_PICK2], st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD )
			{
				mn_mot_flag[1][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD )
			{
				mn_mot_flag[1][1] = CTL_YES;
			}
			
			if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES )
			{
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_fwd_cylinder[0], IO_OFF);//place pos
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_bwd_cylinder[0], IO_ON);//pick pos
//				
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_fwd_cylinder[1], IO_OFF);
//				g_ioMgr.set_out_bit( st_io.o_distribute_rbt2_box_rotator_bwd_cylinder[1], IO_ON);
				
				ReqMRotateFwdBwd( 0, BACKWARD );
				ReqMRotateFwdBwd( 1, BACKWARD );
				job.bcr2_step = BCR2_STEP(461);
				mn_mot_flag[1][0] = 0;
				mn_mot_flag[1][1] = 0;
				mn_mot_flag[1][2] = 0;
				m_dwTime_Robot2 = GetCurrentTime();
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1343, CTL_dWARNING, alarm.mstr_code );
				mn_mot_flag[1][0] = 0;
				mn_mot_flag[1][1] = 0;
				mn_mot_flag[1][2] = 0;
			}
		}
		break;

	////2014,1205
	case 461://2014,1205
		{
			int nRet1 = COMI.Check_SingleMove( M_BCR_ATTACH1_X, st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2] );
			int nRet2 = COMI.Check_SingleMove( M_BCR_ATTACH1_Y, st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_PICK2] );  // 이동 완료 ?
			if( nRet1 == BD_GOOD)
			{
				mn_mot_flag[1][0] = CTL_YES;
			}
			if( nRet2 == BD_GOOD)
			{
				mn_mot_flag[1][1] = CTL_YES;
			}
			
			if( mn_mot_flag[1][0] == CTL_YES && mn_mot_flag[1][1] == CTL_YES)
			{
				ReqMRotateFwdBwd( 0, BACKWARD );
				ReqMRotateFwdBwd( 1, BACKWARD );
				mn_mot_flag[1][0] = 0;
				mn_mot_flag[1][1] = 0;
				mn_mot_flag[1][2] = 0;
				job.bcr2_step = BCR2_STEP(462);
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY)
			{
				job.bcr2_step = BCR2_PLACE_LABEL_SAFETY;
				CTL_Lib.Alarm_Error_Occurrence( 1348, CTL_dWARNING, alarm.mstr_code );
				mn_mot_flag[1][0] = 0;
				mn_mot_flag[1][1] = 0;
				mn_mot_flag[1][2] = 0;
			}			
			
		}
		break;
	////
		
	case 462:
		{
			if( m_fbmrotatefwdbwd[0] != FB_NONE) break;
			if( m_fbmrotatefwdbwd[1] != FB_NONE) break;
			
			int nRet1,nRet2,nRet3,nRet4;
			CString strError;
			
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_OFF);//place position
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_ON); //pick position
			nRet3 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_OFF);
			nRet4 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_ON);	
			
			if(nRet1 == IO_OFF && nRet2 == IO_ON && nRet3 == IO_OFF && nRet4 == IO_ON)
			{
				job.bcr2_step = BCR2_PLACE_LABEL_FINISH;
			}
			else
			{
				if(nRet1 != IO_OFF) 
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 1344, CTL_dWARNING, strError );
				}
				else if(nRet2 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
					CTL_Lib.Alarm_Error_Occurrence( 1345, CTL_dWARNING, strError );
				}
				else if(nRet3 != IO_OFF)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 1346, CTL_dWARNING, strError );
				}
				else if(nRet4 != IO_ON)
				{
					strError.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
					CTL_Lib.Alarm_Error_Occurrence( 1347, CTL_dWARNING, strError );
				}
			}
		}

		break;
		
	case BCR2_PLACE_LABEL_FINISH:
		{
			if(m_fbboxupdn != FB_NONE ) break;

			if( job.iRobotFirst != -1)
			{
				st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].nBcrExist[CTL_LEFT] = CTL_YES;
				memcpy( &st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].st_barcode2[job.iRobotFirst], &st_bcr_rbt[1].st_bcr[job.iRobotFirst], sizeof(st_bcrinfo_param));
			}
			if( job.iRobotSecond != -1)
			{				
				st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].nBcrExist[CTL_RIGHT] = CTL_YES;
				memcpy( &st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].st_barcode2[job.iRobotSecond], &st_bcr_rbt[1].st_bcr[job.iRobotSecond], sizeof(st_bcrinfo_param));
			}

			////2014,1205
			if( job.iRobotFirst != -1 || job.iRobotSecond != -1)
			{
				if( job.iRobotFirst != -1)
				{
					st_bcr_rbt[1].bPick[job.iRobotFirst] = 0;
					st_bcr_rbt[1].st_bcr[job.iRobotFirst].bExist = 0;
					st_bcr_rbt[1].st_bcr[job.iRobotFirst].bOut = 0;
				}
				if( job.iRobotSecond != -1)
				{
					st_bcr_rbt[1].bPick[job.iRobotSecond] = 0;					
					st_bcr_rbt[1].st_bcr[job.iRobotSecond].bExist = 0;
					st_bcr_rbt[1].st_bcr[job.iRobotSecond].bOut = 0;
				}
				memset( &st_bcr_rbt[1], 0x00, sizeof(st_bcr_rbt[1]));
			}			
			////
			
			Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();
//			Func.BackupData();//2013,1018

			st_sync.n_bcr_2_work_req = CTL_REQ;
			st_sync.n_bcr_1_work_req = CTL_REQ;//2016.0817

			if(st_handler.n_only_work_bcr1 == CTL_YES)
			{
				//2014,1117
				if( job.iRobotFirst != -1)
					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[job.iRobotFirst].nComplete = CTL_NO;
				if( job.iRobotSecond != -1)
					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[job.iRobotSecond].nComplete = CTL_NO;
				st_sync.n_bcr_2_work_req = CTL_READY;
			}
			
// 			if(GetCurrentTime() - m_dwTimeTact <= 0 ) m_dwTimeTact = GetCurrentTime();
// 			if( GetCurrentTime() - m_dwTimeTact >= 0 && GetCurrentTime() - m_dwTimeTact < 900000 &&
// 				st_handler.cwnd_list != NULL)
// 			{
// 				sprintf(st_msg.c_normal_msg, "[BARCODE2]Tact time : %d", GetCurrentTime() - m_dwTimeTact);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 				Func.On_LogFile_Add(LOG_MACHINE, st_msg.c_normal_msg);
// 			}
// 			m_dwTimeTact = GetCurrentTime();			
			
			Func.Handler_Recovery_Data_Write();
			st_handler.mn_btm_ready = 1;
			////
		}
		break;
	}

}

void CRun_Barcode_Works::Run_Reinstate()
{
	if(st_handler.mn_Rcvy_state[RCVY_BARCODE1] == CTL_YES) return;
	int nRet[4];

	switch(mn_RcvyStep1)
	{
	case 0:
		{
			nRet[0] = COMI.Check_MotPosRange(M_BCR_ATTACH1_X, COMI.md_cmdpos_backup[M_BCR_ATTACH1_X], COMI.md_allow_value[M_BCR_ATTACH1_X]);
			nRet[2] = COMI.Check_MotPosRange(M_BCR_ATTACH1_Z1, COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z1], COMI.md_allow_value[M_BCR_ATTACH1_Z1]);
			nRet[3] = COMI.Check_MotPosRange(M_BCR_ATTACH1_Z2, COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z2], COMI.md_allow_value[M_BCR_ATTACH1_Z2]);

			bool nRecy = false;
			for( int i = 0; i < 4; i++)
			{
				m_nReq_Rcvy[0][i] = CTL_NO;
				if(nRet[i] == BD_ERROR)
				{
					m_nReq_Rcvy[0][i] = CTL_YES;
					nRecy = true;
				}
			}

			if(nRecy == false) mn_RcvyStep1 = 9000;
			else
			{
				m_dPos_TmpRcvyZ1_1 = COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z1];
				m_dPos_TmpRcvyZ1_2 = COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z2];
				mn_RcvyStep1 = 100;
			}
		}
		break;

	case 100:
		{
			for ( int i = 0; i < 2; i++)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum_fwdback[i], IO_OFF);
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum_fwdback[i], IO_OFF);
// 				g_ioMgr.set_out_bit( st_io.o_distribute_rbt1_box_guide_fwdback[i], IO_OFF);//2014,1125 ysj
			}
			m_dwTime_Recvy[0] = GetCurrentTime();
			mn_RcvyStep1 = 110;
		}
		break;

	case 110:
		{
			if( GetCurrentTime() - m_dwTime_Recvy[0] < 0 ) m_dwTime_Recvy[0] = GetCurrentTime();
			if( GetCurrentTime() - m_dwTime_Recvy[0] < 500) break;

			mn_RcvyStep1 = 120;
			for ( int i = 0; i < 2; i++)
			{
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[i], IO_ON) == IO_OFF ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i], IO_ON) == IO_OFF)// ||
					//g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_box_guide_back_chk[i], IO_ON) == IO_OFF )//2014,1125 ysj
				{
					mn_RcvyStep1 = 110;
					break;
				}
			}
			if( GetCurrentTime() - m_dwTime_Recvy[0] > 10000)
			{
				for ( int i = 0; i < 2; i++)
				{
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[i], IO_ON) == IO_OFF)
					{
						CString strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_top_vacuum_bwd_chk[i], IO_OFF );
						CTL_Lib.Alarm_Error_Occurrence( 1349, dWARNING, strJamCode );
						break;
					}
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i], IO_ON) == IO_OFF )
					{
						CString strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i], IO_OFF );
						CTL_Lib.Alarm_Error_Occurrence( 1350, dWARNING, strJamCode );
						break;
					}
// 					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt1_box_guide_back_chk[i], IO_ON) == IO_OFF )
// 					{
// 						CString strJamCode = GetJamCode_Bcr_Guide_FwdBwd_Time(st_io.i_distribute_rbt1_box_guide_fwd_chk[i], IO_OFF );
// 						CTL_Lib.Alarm_Error_Occurrence( 1351, dWARNING, strJamCode );
// 						break;
// 					}
				}
			}
		}
		break;

	case 120:
		{
			int nRet1 = CTL_Lib.Single_Move(M_BCR_ATTACH1_Z1, st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_SAFETY], (int)st_basic.nRunSpeed );
			int nRet2 = CTL_Lib.Single_Move(M_BCR_ATTACH1_Z2, st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY], (int)st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD && nRet2 == BD_GOOD )
			{
				COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z1] = m_dPos_TmpRcvyZ1_1;
				COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z2] = m_dPos_TmpRcvyZ1_2;
				mn_RcvyStep1 = 1000;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1352, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case 1000:
		{
			if (m_nReq_Rcvy[0][1] == CTL_NO)
			{
				mn_RcvyStep1 = 2000;
				break;
			}
// 			int nRet1 = CTL_Lib.Single_Move(M_BCR_ATTACH1_R1, COMI.md_cmdpos_backup[M_BCR_ATTACH1_R1], (int)st_basic.nRunSpeed );
// 			int nRet2 = CTL_Lib.Single_Move(M_BCR_ATTACH1_R2, COMI.md_cmdpos_backup[M_BCR_ATTACH1_R2], (int)st_basic.nRunSpeed );
// 			if( 1 /*|| (nRet1 == BD_GOOD && nRet2 == BD_GOOD )*/)
// 			{
				mn_RcvyStep1 = 2000;
// 			}
// 			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY ||  nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1353, CTL_dWARNING, alarm.mstr_code );
// 			}
		}
		break;

	case 2000:
		{
			if (m_nReq_Rcvy[0][0] == CTL_NO)
			{
				mn_RcvyStep1 = 3000;
				break;
			}
			int nRet1 = CTL_Lib.Single_Move(M_BCR_ATTACH1_X, COMI.md_cmdpos_backup[M_BCR_ATTACH1_X], (int)st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD)
			{
				mn_RcvyStep1 = 3000;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1354, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;

	case 3000:
		{
			if(m_nReq_Rcvy[0][2] == CTL_NO && m_nReq_Rcvy[0][3] == CTL_NO)
			{
				mn_RcvyStep1 = 4000;
				break;
			}
			int nRet1 = CTL_Lib.Single_Move(M_BCR_ATTACH1_Z1, COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z1], (int)st_basic.nRunSpeed );
			int nRet2 = CTL_Lib.Single_Move(M_BCR_ATTACH1_Z2, COMI.md_cmdpos_backup[M_BCR_ATTACH1_Z2], (int)st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD && nRet2 == BD_GOOD)
			{
				mn_RcvyStep1 = 4000;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY || nRet2 == BD_ERROR || nRet2 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1355, CTL_dWARNING, alarm.mstr_code );
			}

		}
		break;

	case 4000:
		{
			for (int i =0; i < 2; i++)
			{
				EFB efb;
				if( st_work.mn_bcr_m1top_vac_fwdback[i] == IO_ON) efb = FORWARD;
				else											  efb = BACKWARD;
				ReqMTopVac(i, efb);
				if( st_work.mn_bcr_m1btm_vac_fwdback[i] == IO_ON) efb = FORWARD;
				else											  efb = BACKWARD;
				ReqMBtmVac(i, efb);
				if( st_work.mn_bcr_m1guide_fwdback[i] == IO_ON) efb = FORWARD;
				else											  efb = BACKWARD;
				//ReqM1GuideFwdBwd( i, efb);
			}
			m_dwTime_Recvy[0] = GetCurrentTime();
			mn_RcvyStep1 = 4100;
		}
		break;
		
	case 4100:
		if( GetCurrentTime() - m_dwTime_Recvy[0] < 0 ) m_dwTime_Recvy[0] = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_Recvy[0] < 500) break;

		if( GetCurrentTime() - m_dwTime_Recvy[0] > 10000)
		{
			CString strJamCode;
			for ( int i = 0; i < 2; i++)
			{
				if( g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[i], st_work.mn_bcr_mtop_vac_fwdback[i]) != !st_work.mn_bcr_m1top_vac_fwdback[i] )
				{
					strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_top_vacuum_bwd_chk[i], st_work.mn_bcr_m1top_vac_fwdback[i] );
					CTL_Lib.Alarm_Error_Occurrence( 1356, dWARNING, strJamCode );
					break;
				}
				if( g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i], st_work.mn_bcr_m1btm_vac_fwdback[i]) != !st_work.mn_bcr_m1btm_vac_fwdback[i] )
				{
					strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i], st_work.mn_bcr_m1btm_vac_fwdback[i] );
					CTL_Lib.Alarm_Error_Occurrence( 1357, dWARNING, strJamCode );
					break;
				}
// 				if( g_ioMgr.get_in_bit(st_io.o_distribute_rbt2_box_guide_fwdback[i], st_work.mn_bcr_m2btm_vac_fwdback[i]) != !st_work.mn_bcr_m2guide_fwdback[i] )
// 				{
// 					strJamCode = GetJamCode_Bcr_Vacuum_Fwdbwd_Time(st_io.i_distribute_rbt2_box_guide_back_chk[i], st_work.mn_bcr_m2btm_vac_fwdback[i] );
// 					CTL_Lib.Alarm_Error_Occurrence( 225, dWARNING, strJamCode );
// 					break;
// 				}
			}
		}

		if( GetMTopVac( EBVS_LEFT ) != FB_NONE ) return;
		if( GetMTopVac( EBVS_RIGHT ) != FB_NONE ) return;
		if( GetMBtmVac( EBVS_LEFT ) != FB_NONE ) return;
		if( GetMBtmVac( EBVS_RIGHT ) != FB_NONE ) return;

		mn_RcvyStep2 = 9000;
		break;
		


	case 9000:
		st_handler.mn_Rcvy_state[RCVY_BARCODE1] = CTL_YES;
		mn_RcvyStep1 = 0;
		break;
	}
}

void CRun_Barcode_Works::EDRR_HomeCheck_R( int nAxis)
{
	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);
	if( 1 || nRet == BD_GOOD )
	{
		mn_InitStep = EBRR_HOMECHK_RBT1_R2;

//		Func.OnInitBtn( RBTN_SITE1_Z + (m_nSiteID - INIT_TEST_SITE_1 ) * 5 );
	}
	else if( nRet == BD_ERROR )
	{//040001 0 00 "Distribute#1 Attach R#1 Axis Motor Home Check Error." //2016.0722
		//210001 0 00 "Distribute#1 Attach R#2 Axis Motor Home Check Error."
		//240001 0 00 "Distribute#2 Attach R#1 Axis Motor Home Check Error."
		//260001 0 00 "Distribute#2 Attach R#2 Axis Motor Home Check Error."

		//CString strJamCode = "190001"; //2016.0722
		CString strJamCode = "040001";
		CTL_Lib.Alarm_Error_Occurrence(1368, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::EDRR_HomeCheck_X( int nAxis )
{
	int nRet = COMI.HomeCheck_Mot( nAxis, MOT_TIMEOUT);

	if( nRet == BD_GOOD )
	{
		if(nAxis == M_BCR_ATTACH1_X)
		{
			mn_InitStep = EBRR_HOMECHK_RBT2_X;
			Func.OnInitBtn( RBTN_BCR_ATTACH1_X );//2014.1018
		}
	}
	else if( nRet == BD_ERROR )
	{//170001 0 00 "Distribute#1 Attach X Axis Motor Home Check Error."
		//220001 0 00 "Distribute#2 Attach X Axis Motor Home Check Error."
		CString strJamCode = "170001";
		CTL_Lib.Alarm_Error_Occurrence(1369, CTL_dWARNING, strJamCode );
	}
}

void CRun_Barcode_Works::Run_Restore()
{
	if( st_handler.mn_init_state[INIT_BARCODE_ROBOT] != CTL_NO )	return;
	switch(mn_RestoreStep)
	{
	case EBRR_START: mn_RestoreStep = EBRR_Z_SAFETY;	break;
	case EBRR_Z_SAFETY:
		{
			int nRet1 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z1, st_motor[ M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY], (int)st_basic.nRunSpeed );
			int nRet2 = CTL_Lib.Single_Move( M_BCR_ATTACH1_Z2, st_motor[ M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY], (int)st_basic.nRunSpeed );
			if( nRet1 == BD_GOOD && nRet2 == BD_GOOD)
			{
				mn_RestoreStep = EBRR_VACUUM1_CHK;
			}
			else if( nRet1 == BD_ERROR || nRet1 == BD_SAFETY )
			{
				CTL_Lib.Alarm_Error_Occurrence( 1370, CTL_dWARNING, alarm.mstr_code );
			}
		}
		break;

	case EBRR_VACUUM1_CHK:
		{
			CString strJamCode;
			if( st_basic.n_mode_device && g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF) == IO_OFF)
			{
				mn_RestoreStep = EBRR_VACUUM2_CHK;
			}
			else
			{
				CString strError;
				if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON);
				}
				else if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON);
				}
				else if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON);
				}
				else
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON);
				}
				CTL_Lib.Alarm_Error_Occurrence( 1371, CTL_dWARNING, strError );
			}
		}
		break;

	case EBRR_VACUUM2_CHK:
		{
			CString strJamCode;
			if( st_basic.n_mode_device && g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF) == IO_OFF &&
				g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF) == IO_OFF)
			{
				mn_RestoreStep = EBRR_VACUUM_OFF;
			}
			else
			{
				CString strError;
				if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON);
				}
				else if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON);
				}
				else if(g_ioMgr.get_in_bit(st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF) == IO_ON)
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON);
				}
				else
				{
					strError.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON);
				}
				CTL_Lib.Alarm_Error_Occurrence( 1372, CTL_dWARNING, strError );
			}
		}
		break;

	case EBRR_VACUUM_OFF:
		{
			for ( int i = 0;i < 2; i++)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_vacuum[i] , IO_OFF );
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_vacuum[i] , IO_OFF );
			}
			m_dwTimeInit = GetCurrentTime();
			mn_RestoreStep = EBRR_BLOW_ON;
		}
		break;

	case EBRR_BLOW_ON:
		{
			if( GetCurrentTime() - m_dwTimeInit < 0 ) m_dwTimeInit = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeInit < st_time.n_wait_time[E_WAIT_BCR_VACUUM][IO_ON]) break;
			for ( int i = 0;i < 2; i++)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[i] , IO_ON );
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[i] , IO_ON );
			}
			mn_RestoreStep = EBRR_BLOW_OFF;
			m_dwTimeInit = GetCurrentTime();
		}
		break;

	case EBRR_BLOW_OFF:
		{
			if( GetCurrentTime() - m_dwTimeInit < 0 ) m_dwTimeInit = GetCurrentTime();
			else if( GetCurrentTime() - m_dwTimeInit < st_time.n_wait_time[E_WAIT_BCR_EJECT][IO_ON]) break;
			for ( int i = 0;i < 2; i++)
			{
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_top_eject[i] , IO_OFF );
				g_ioMgr.set_out_bit( st_io.o_distribute_rbt_btm_eject[i] , IO_OFF );
			}
			mn_RestoreStep = EBRR_CYL_OFF;
		}
		break;

	case EBRR_CYL_OFF:
// 		ReqM1GuideFwdBwd( EBVS_LEFT , BACKWARD );
// 		ReqM1GuideFwdBwd( EBVS_RIGHT, BACKWARD );
// 		ReqM2GuideFwdBwd( EBVS_LEFT , BACKWARD );
// 		ReqM2GuideFwdBwd( EBVS_RIGHT, BACKWARD );
		mn_RestoreStep = EBRR_CYL_OFF_CHK;
		break;

	case EBRR_CYL_OFF_CHK:
// 		if( GetM1GuideFwdBwd( EBVS_LEFT ) != FB_NONE ) return;
// 		if( GetM1GuideFwdBwd( EBVS_RIGHT ) != FB_NONE ) return;
// 		if( GetM2GuideFwdBwd( EBVS_LEFT ) != FB_NONE ) return;
// 		if( GetM2GuideFwdBwd( EBVS_RIGHT ) != FB_NONE ) return;
		mn_RestoreStep = EBRR_HOMECHK_RBT1_X;
		break;

	case EBRR_HOMECHK_RBT1_X: EDRR_HomeCheck_X(M_BCR_ATTACH1_X); break;
	case EBRR_FINISH:
		for ( int i = 0; i < Func.m_pRobot[SITE_BARCODE1]->GetJobCount(); i++)
		{
			Func.m_pRobot[SITE_BARCODE1]->EraseFirstJob();
		}		
		for ( int j = 0; i < Func.m_pRobot[SITE_BARCODE2]->GetJobCount(); j++)
		{
			Func.m_pRobot[SITE_BARCODE2]->EraseFirstJob();
		}		

		st_handler.mn_init_state[INIT_BARCODE_ROBOT] = CTL_YES;
		mn_RestoreStep = EBRR_START;
		break;
	}
}

void CRun_Barcode_Works::OnRobot_FinalPos()
{
}

void CRun_Barcode_Works::Serialize(CArchive &ar)
{
}

