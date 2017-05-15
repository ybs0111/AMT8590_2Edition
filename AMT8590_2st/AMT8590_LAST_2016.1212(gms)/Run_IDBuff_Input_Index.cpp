// Run_IDBuff_Input_Index.cpp: implementation of the CRun_IDBuff_Input_Index class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "Run_IDBuff_Input_Index.h"

#include "Run_Smema_Ctl.h"
#include "AMTLotManager.h"
#include "RunNetwork.h"
#include "MesEvent.h"
#include "ZebraPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRun_IDBuff_Input_Index g_Run_IDBuff_Input_Index;
CRun_IDBuff_Input_Index::CRun_IDBuff_Input_Index()
{
	st_var.n_boatid_in_flag = CTL_NO;
	mn_InitStep = 0;
	mn_run_step = 0; 
	mn_pick_step = 0;
	mn_place_step = 0;
	mn_bcrIn_step = 0;
	mn_bcrOut_step = 0;
	mn_sever_step = 0;
	mn_fmt_step = 0;
	mn_ccs_step = 0;
	m_nStep_MES = 0;
	mn_mdl_change_step = 0;
	mn_Dugserial = 0;
	mn_idbuffer = 0;
	mn_interlock_sgn = 0;
}

CRun_IDBuff_Input_Index::~CRun_IDBuff_Input_Index()
{
	mn_InitStep = 0;
	mn_run_step = 0; 
	mn_pick_step = 0;
	mn_place_step = 0;
	mn_bcrIn_step = 0;
	mn_bcrOut_step = 0;
	mn_sever_step = 0;
	mn_fmt_step = 0;
	mn_ccs_step = 0;
}


void CRun_IDBuff_Input_Index::Thread_Run()
{
// 	return;
	int n_ret_1=0,n_ret_2=0,n_ret_3=0,n_ret_4=0,n_ret_5=0;
	st_set.n_inputindex_premove_mm_value = 50; //100mm 

	if( Func.OnIsInterruptCondition() != 1 )
		return;

	Run_Smema_Ctl.smema_process_top_8580(0);

	switch (COMI.mn_run_status)
	{
	case dINIT:
		Run_Initial();
		break;
		
	case dRUN:
// 		return;
		if(st_handler.n_only_work_density == 1 )
		{
			break;
		}
		if(st_var.n_bcr_read_input_flag == CTL_YES) //input buffer �б� 
		{
 			n_ret_1 = barcode_read_inout_process(CTL_LEFT);

			if(n_ret_1 == CTL_GOOD)
			{
				st_var.n_bcr_read_input_flag = CTL_NO; //���ڵ� �б� �Ϸ� 
			}
		}
//		if(st_var.n_bcr_read_output_flag == CTL_YES) //2014.1202 //output buffer barcode read 
//		{
//			n_ret_2 = barcode_read_inout_process(CTL_RIGHT);
//			if(n_ret_2 == CTL_GOOD)
//			{
//				st_var.n_bcr_read_output_flag = CTL_NO; //���ڵ� �б� �Ϸ� 
//			}
//		}
		if( st_handler.m_nLotServer == CTL_YES && st_var.n_newlotin == CTL_YES )
		{
			n_ret_3 = OnServerNewLotin();
			if( n_ret_3 == CTL_GOOD)
			{
// 				st_var.n_densityccs = CTL_READY;
// 				st_var.n_bcrccs = CTL_READY;
				CString strLog;
				strLog.Format("[SERVER_NEW_LOT_IN2] = NO. st_var.n_newlotin: %d", st_var.n_newlotin);
				Func.On_LogFile_Add(99, strLog);
			}
		}
		if ( g_lotMgr.GetLotCount() > 0 && (st_var.n_densityccs == CTL_YES || st_var.n_bcrccs == CTL_YES))
		{
			n_ret_4 = OnServerCCS();
			if( n_ret_4 == CTL_GOOD )
			{
				st_var.n_densityccs = CTL_NO;
				st_var.n_bcrccs = CTL_NO;
			}
		}
		if ( st_var.n_boatid_in_flag == CTL_YES )
		{
			n_ret_5 = OnServerBaotIDIn();
			if( n_ret_5 == CTL_GOOD )
			{
				st_var.n_boatid_in_flag = CTL_NO;
			}
		}
// 		if( st_var.n_newbcr_format == CTL_YES)
// 		{
// 			n_ret_4 = OngetFmtfromServer();
// 			if( n_ret_4 == CTL_GOOD)
// 			{
// 				st_var.n_newbcr_format = CTL_NO;
// 			}
// 		}

		Run_Move();
		Run_Model_Change();
	
		break;
		
	default: 
			
		break;
	}
}


void CRun_IDBuff_Input_Index::Run_Initial()
{
	int nRet_1 = 0, nRet_2 = 0,nRet_3 = 0,nRet_4 = 0;
	int i = 0, nFlag=0;
/*	
	if (st_handler.mn_init_state[STEP_INPUT_INDEX] != CTL_NO)		return;		// No �϶��� �ʱ�ȭ �۾��� �Ѵ�. �ʱ�ȭ�� ������ YES->READY�� �Ǳ� ������...
	
	mn_InitStep = st_step.n_init[STEP_INPUT_INDEX]; 
	Func.ThreadFunctionStepTrace(STEP_INPUT_INDEX + STEP_INIT, mn_InitStep);
	
	switch (mn_InitStep)
	{
	case 0:
		if(st_handler.mn_init_state[STEP_TBOX_TRANSFER_RBT] == CTL_NO) break; //Z ���� �ö󰥶����� ��ٸ��� �ȴ� 
		if(st_handler.mn_init_state[STEP_TBOX_PUSHER_RBT] == CTL_NO) break; // 
		if(st_handler.mn_init_state[STEP_SET_PLATE] == CTL_NO) break; // ���� �ִ� ���۴� �̰����� ��� ��������  
		mn_InitStep = 100;
		break;

	default :
		break;
	}
	*/
}


void CRun_IDBuff_Input_Index::Run_Move()
{
	int i=0, nRet_1=0, nRet_2=0, nRet_3=0;
	CString str_msg;
	int nCnt=0;
	
 	
	Func.ThreadFunctionStepTrace( 2, mn_run_step);
	switch(mn_run_step)
	{
	case 0:
// 		if(st_var.n_lotstart == CTL_YES) //smema ����A����e lot start 
// 		if( g_lotMgr.GetLotCount() > 0 &&  g_lotMgr.GetLotAt(0).GetStrLastModule() != "YES" )
// 		{						
			st_sync.n_smema_input_index_req = CTL_REQ; //loader ��� ID Buffer�� ��û�Ѵ�, smema �� ���� 
			mn_run_step = 1000;
// 		}
		break; 

	case 1000:
		if( st_sync.n_smema_input_index_req == CTL_READY)//id buffer�� �ε� ��� �غ�Ǿ����� ��������� ��ȣ 
		{
			//////////////////////////////////////////////////////////////////
			//ID Buffer �� ������ ������ ��Ʈ�� ����� ���� �ޱ� �Ϸ� //buffer in 
			//////////////////////////////////////////////////////////////////
			//if( st_handler.mn_curr_back_conv == 1 )//2016.0615
			if( st_handler.n_without_smema_8580_mc == CTL_YES || st_handler.mn_curr_back_conv == 1)
			{
				CString strLotID, strSerial, strPartID;
				if( g_lotMgr.GetLotCount() <= 0)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[0] = ID_LOT_START;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[1] = ID_LOT_START;
				}
				else
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[0] = 0;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[1] = 0;
				}
				for ( int i = 0; i < 2; i++)
				{
					
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[i] = 0;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[i] = 1;
					if(++mn_idbuffer > 34) mn_idbuffer = 1;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[i] = mn_idbuffer;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[i] = 1;
					
					strLotID = "X0D9UR0536";
					strPartID = "MZ7LN250HMJP-2BE00-G12";
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[i], "%s", strLotID);
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[i], "%s", strPartID);

// 					if(i == 0) strSerial = "S1SMNSAFC07070X";
// 					else	   strSerial = "S1SMNSAFC07021J";

					if( mn_Dugserial >= 999) mn_Dugserial = 0;
					if(i == 0) 
					{
						mn_Dugserial++;
						strSerial.Format("S21HNXAG307%03d", mn_Dugserial);
					}
					//sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[i], "%s", strSerial);
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[i], "%s", strSerial);
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_var[i], "%s", "1");
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_product_id[i], "%s", "2.5");
				}
				if(st_basic.mn_mode_run)
				{
// 					st_var.n_newlotin = CTL_YES;
					st_handler.m_strNewLot = strLotID;
				}

				bool bLot = false;
				for ( i = 0; i < g_lotMgr.GetLotCount(); i++)
				{
					if(g_lotMgr.GetLotAt(i).GetLotID() == "X00QR30450")
					{
						bLot = true;
						break;
					}
				}
				if(bLot == false)
				{
					g_lotMgr.OnNewLotIn(strLotID, strPartID);
					g_lotMgr.GetLotByLotID(strLotID).SetMdlCapa( strPartID.Mid(5,3) + "GB" );
					g_lotMgr.GetLotByLotID(strLotID).SetTotalModule( "200" );
					g_lotMgr.GetLotByLotID(strLotID).SetDenLabelCapa(strPartID.Mid(5,3) + "GB" );//2016.0721
					st_basic.mstr_device_name.MakeUpper();
					int aa = st_basic.mstr_device_name.Find(".TXT", 0);
					if( aa <= 0 )
					{ 
						if (st_handler.cwnd_list != NULL)
						{
							sprintf( st_msg.c_abnormal_msg, "%s can't find (.txt). check device name please", st_basic.mstr_device_name);
							st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
						}
						return;
						//error 
					}
					CString strname = st_basic.mstr_device_name;
					strname.Replace(".TXT", "");					
					st_work.m_strCurModel = strname;
				}
			}
			mn_sever_step = 0;
			mn_run_step = 1100;
			if(st_var.n_newlotin == CTL_YES)
			{
				st_handler.m_nLotServer = CTL_YES;
			}
		}
		break;

	case 1100:
		if(st_var.n_newlotin == CTL_NO)
		{
			if( g_lotMgr.GetLotCount() > 0 && (st_var.n_densityccs == CTL_READY||st_var.n_bcrccs == CTL_READY) )
			{
// 				st_var.n_densityccs = CTL_YES;
// 				st_var.n_bcrccs = CTL_YES; 
				//2016.1209
				if( g_lotMgr.GetLotCount() > 1 )
				{
					st_var.n_densityccs = CTL_YES;
					st_var.n_bcrccs = CTL_YES;
				}
				else
				{
					st_var.n_densityccs = CTL_YES;
					st_var.n_bcrccs = CTL_YES; 
					if( g_lotMgr.GetLotAt(0).GetStrLastModule() == "YES")
					{
						st_var.n_densityccs = CTL_NO;
						st_var.n_bcrccs = CTL_NO; 
					}
				}
				mn_run_step = 1110;
				CString strLog;
				strLog.Format("[NEW_LOT_IN] = NO. densityccs: %d, bcrccs: %d, mn_run_step: %d", st_var.n_densityccs, st_var.n_bcrccs, mn_run_step);
				Func.On_LogFile_Add(99, strLog);
			}
			else
			{
				mn_run_step = 1200;
				//2015.0419
				mn_run_step = 1120;
			}
		}
		break;

	case 1110:
// 		if(st_var.n_densityccs == CTL_NO && st_var.n_bcrccs == CTL_NO)
// 			mn_run_step = 1200;
		//2015.0419
		if(st_var.n_densityccs == CTL_NO && st_var.n_bcrccs == CTL_NO)
			mn_run_step = 1120;
		break;

	case 1120:
		if( ( st_basic.mn_mode_run == CTL_NO || st_handler.n_without_network == CTL_YES ) || 
			(st_basic.mn_mode_run == CTL_YES && Func.CheckLotSerial() == CTL_GOOD))
		{
			mn_run_step = 1200;
// 			mn_run_step = 2000;
		}
		break;

	case 1200:
		//2016.0615
// 		if( st_basic.mn_mode_run == CTL_NO || st_handler.mn_curr_back_conv == 1 )
		if( st_basic.mn_mode_run == CTL_NO && st_basic.n_mode_device == CTL_NO )
		{
			mn_run_step = 2000;
		}
		else
		{
			for ( int i = 0; i < 2; i++)
			{
				//(PRODUCT_NAME=00 BUFFER_SKIP=0 IDBUF=21 SERIAL=S1SMNSAFC06960R VAR=1 ) MD_02=(PRODUCT_NAME=00 BUFFER_SKIP=0 IDBUF=27 SERIAL=S1SMNSAFC07024X VAR=1 )RESULT=PASS
				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[i] == 0 &&
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[i] == 1 )
				{
				}
			}
			if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[0] == 0 && st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[1] == 0 &&
				( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[0] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[i] == 1 ) )
			{
				if(g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete == CTL_NO && g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete == CTL_NO)
				{					
// 					st_var.n_newbcr_format = CTL_YES;
// 					mn_run_step = 1300;
					mn_run_step = 1210;
				}
			}
			else
			{
				mn_run_step = 1300;
			}
		}
		break;

	case 1210:
		//2015.0517
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[CTL_LEFT] == ID_LOT_START || 
			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_last_module[CTL_RIGHT] == ID_LOT_START )
		{ //new lot start , ���ο� lot ����
			
			CString strLotID,strPartID, strModel;
			
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES)
			{
				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
// 				nMdl = Func.GetModelNum(strPartID);
				nMdl = Func.GetModelFromPartID(strPartID, strModel);
				if( st_basic.mn_mode_run == CTL_YES && nMdl != RET_GOOD)//2016.08012
				{//940005 0 A "Not Registered model."
					sprintf(mc_jamcode, "940005");
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9902, COMI.mn_run_status, mc_jamcode);
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "[PartID Error] %s is not correct. Not registered model. check please.", (LPCTSTR) strPartID );
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					break;
				}


// 				strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
// 				st_handler.m_strVisModel = strLotID;
// 				g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
// 				g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
// 				g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
			}
			else if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_YES)
			{
////2015.0711
//				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_RIGHT]);
////

// 				nMdl = Func.GetModelNum(strPartID);
				nMdl = Func.GetModelFromPartID(strPartID, strModel);
				if( st_basic.mn_mode_run == CTL_YES && nMdl != RET_GOOD)//2016.08012
				{//940005 0 A "Not Registered model."
					sprintf(mc_jamcode, "940005");
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9903, COMI.mn_run_status, mc_jamcode);
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "[PartID Error] %s is not correct. Not registered model. check please.", (LPCTSTR) strPartID );
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					break;
				}

// 				strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
// 				st_handler.m_strVisModel = strLotID;
// 				g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
// 				g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
// 				g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
			}
			
// 			st_var.n_last_module_flag = 0; 				
// 			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
// 			{
// 				sprintf(st_msg.c_normal_msg, "[LOT START] lot first start...");
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 			}
// 			mn_run_step = 1220;
// 			CString strMdl = st_basic.mstr_device_name;
// 			CString newMdl = Func.GetModelName(nMdl);
// 			strMdl.TrimLeft(); strMdl.TrimRight();
// 			strMdl.MakeUpper();
// 			strMdl.Replace(".TXT", "");

// 			if(strMdl != newMdl)
// 			{
// 				m_strModelNewname = newMdl;
// 				mn_mdl_change_step = 0;
// 				st_handler.mn_model_change = CTL_YES;
// 			}
			st_var.n_lotstart = ID_LOT_START;

			/*
			st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
			st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
			st_var.n_use_density_count[st_basic.mn_device_type] = 0;
			st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
			*/
			////////////////////////////////////////////////////////////////////////////////////////////
			//2016.1027
			if( g_lotMgr.GetLotCount() > 1 )
			{
				if( g_lotMgr.GetLotAt(0).GetDenLabelCapa() != g_lotMgr.GetLotAt(1).GetDenLabelCapa() )
				{
					st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
					st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
					st_var.n_use_density_count[st_basic.mn_device_type] = 0;
					st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
				}
				else
				{//2016.1031
					if(st_handler.mn_device_type != st_basic.mn_device_type)
					{
						st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
						st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
						st_var.n_use_density_count[st_basic.mn_device_type] = 0;
						st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
					}
				}
			}
			else
			{
				st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
				st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
				st_var.n_use_density_count[st_basic.mn_device_type] = 0;
				st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
			}
			////////////////////////////////////////////////////////////////////////////////////////////
			st_handler.mn_device_type = st_basic.mn_device_type;//2016.1031


			st_var.n_use_top_skip = CTL_NO;
			st_work.mn_chg_job = CTL_NO;

			if(st_work.m_strCurModel != strModel)
			{
				st_work.m_strCurModel = strModel;
				mn_mdl_change_step = 0;
				st_handler.mn_model_change = CTL_YES;
				//2016.0918
				if( st_var.n_using_barcode == 0 )
				{
					st_handler.m_nConformVisAfterModelChange[0] = CTL_YES;
					st_handler.m_nConformVisAfterModelChange[1] = CTL_YES;
				}
				else
				{
					st_handler.m_nConformVisAfterModelChange[2] = CTL_YES;
					st_handler.m_nConformVisAfterModelChange[3] = CTL_YES;
				}
				if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
				{
					sprintf(st_msg.c_normal_msg, "Model change is YES, %s Model change", strModel);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
				}
			}
			else
			{
				st_handler.mn_model_change = CTL_READY;	
			}

			mn_run_step = 1215;
		}
		else
		{
			st_var.n_newbcr_format = CTL_YES;
			mn_run_step = 1300;
		}
		break;

	case 1215:
		if(st_handler.mn_model_change == CTL_READY)
		{
			CString strLotID,strPartID,strLog;

			strLog.Format("[Model_Change] 1.NEW_LOT_IN=%d CurModel: %s", st_var.n_newlotin, st_work.m_strCurModel);
			Func.On_LogFile_Add(99, strLog);

			if(st_var.n_newlotin == CTL_YES)
			{
				strLog.Format("[Model_Change_ERROR] 1.NEW_LOT_IN=%d CurModel: %s", st_var.n_newlotin, st_work.m_strCurModel);
				Func.On_LogFile_Add(99, strLog);
				mn_run_step = 1100;
				break;
			}

			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES)
			{
// 				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
// 				nMdl = Func.GetModelNum(strPartID);
// 				if( nMdl == -1)
// 				{
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf(st_msg.c_abnormal_msg, "[PartID Error] %s is not correct. Not registered model. check please.", (LPCTSTR) strPartID );
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 					}
// 					break;
// 				}				
				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
				strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
				st_handler.m_strVisModel = strLotID;

				g_lotMgr.GetLotByLotID(strLotID).SetLabelVisionModel( st_work.m_strCurModel, ("_" + g_lotMgr.GetLotByLotID(strLotID).GetMdlCapa()) );

				strLog.Format("[LOT START1] 1.LOTID: %s PARTID: %s CurModel: %s", strLotID, strPartID, st_work.m_strCurModel);
				Func.On_LogFile_Add(99, strLog);
				
				if(strPartID.GetAt(15) == 'A')//Only UPC Exist //America
				{		
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(true,false);
					g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_UPC" );
				}
				else if(strPartID.GetAt(15) == 'E' || strPartID.GetAt(15) == 'C' || strPartID.GetAt(15) == 'K')//Europe,China,Korea Only EAN Exist
				{
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(false,true);	
					if(strPartID.GetAt(15) == 'C')//china
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_CHINA" );
					}
					else if(strPartID.GetAt(15) == 'K')//china
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_KOREA" );
					}
					else
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "" );
					}
				}
				else//Both of them exist
				{
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(true,true);
					g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "" );
				}

				g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
				g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
				g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
				if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
				{
					sprintf(st_msg.c_normal_msg, "[LOT START1] 2.lot first start...LOTID: %s PARTID: %s CurModel: %s", strLotID, strPartID, st_work.m_strCurModel);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
				}
			}
			else if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_YES)
			{
// 				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
// 				nMdl = Func.GetModelNum(strPartID);
// 				if( nMdl == -1)
// 				{
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf(st_msg.c_abnormal_msg, "[PartID Error] %s is not correct. Not registered model. check please.", (LPCTSTR) strPartID );
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 					}
// 					break;
// 				}
	
////2015.0711				
// 				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_LEFT]);
				strPartID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_part_num[CTL_RIGHT]);
////
				strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
				st_handler.m_strVisModel = strLotID;

				g_lotMgr.GetLotByLotID(strLotID).SetLabelVisionModel( st_work.m_strCurModel, ("_" + g_lotMgr.GetLotByLotID(strLotID).GetMdlCapa()) );
				//visionmodel
				strLog.Format("[LOT START2] 1.LOTID: %s PARTID: %s CurModel: %s", strLotID, strPartID, st_work.m_strCurModel);
				Func.On_LogFile_Add(99, strLog);
				
				if(strPartID.GetAt(15) == 'A')//Only UPC Exist //America
				{		
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(true,false);
					g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_UPC" );
				}
				else if(strPartID.GetAt(15) == 'E' || strPartID.GetAt(15) == 'C' || strPartID.GetAt(15) == 'K')//Europe,China,Korea Only EAN Exist
				{
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(false,true);	
					if(strPartID.GetAt(15) == 'C')//china
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_CHINA" );
					}
					else if(strPartID.GetAt(15) == 'K')//china
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "_KOREA" );
					}
					else
					{
						g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "" );
					}
				}
				else//Both of them exist
				{
					g_lotMgr.GetLotByLotID(strLotID).SetUpcEanType(true,true);
					g_lotMgr.GetLotByLotID(strLotID).SetTBtmVisionModel( st_work.m_strCurModel, "" );
				}

				g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
				g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
				g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
				if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
				{
					sprintf(st_msg.c_normal_msg, "[LOT START2] lot first start...LOTID: %s PARTID: %s CurModel: %s", strLotID, strPartID, st_work.m_strCurModel);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
				}
			}
			st_var.n_last_module_flag = 0; 				
			st_handler.mn_model_change = CTL_NO;
			mn_run_step = 1220;
		}
		break;

	case 1220:
		//g_lotMgr.GetLotByLotID(st_handler.m_strVisModel).SetStartNewLot(false);
		if(g_lotMgr.GetLotByLotID(st_handler.m_strVisModel).GetStrStartNewLot() != "YES" &&
			g_lotMgr.GetLotByLotID(st_handler.m_strVisModel).GetLabelVisionModel() != "YES" )
		{
			st_var.n_newbcr_format = CTL_YES;
			mn_run_step = 1300;
		}
		break;

	case 1300:
 		if( st_var.n_newbcr_format == CTL_NO)
		{
			mn_run_step = 2000;
		}
		break;

	case 2000:
		nRet_1 = idbuffermove_pick_process(0);  //id buffer �� ��´� 
		if(nRet_1 == CTL_GOOD) //���� 
		{
			mn_run_step = 3000;			 
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9101, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 2000;
		}
		break;

	case 3000:		
		st_sync.n_smema_input_index_req = CTL_FREE; //8590�� �������� 8580�� Ŭ������ ������� ��ȣ 

		if( st_basic.mn_mode_run == CTL_YES )
			mn_run_step = 3010;
		else
			mn_run_step = 3100;
		break;

	case 3010:
		//server check 2014.1215)
		if( st_var.n_newbcr_format != CTL_NO ) break;

		if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_LEFT] == CTL_NO &&
			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_RIGHT] == CTL_NO )
		{
			if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES && 
				st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_YES)
			{
				if( st_var.n_boatid_in_flag == CTL_YES ) break;
				
				st_var.n_boatid_in_flag = CTL_NO;// YES;

				//2016.0615 working barcode2 first
				if( st_basic.nBcrFeederUse[2] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_LEFT] = 2;
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_LEFT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_LEFT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_LEFT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_LEFT] = CTL_NO;
				}
				else//if( st_basic.nBcrFeederUse[0] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_LEFT] = 0; 					
		// 			memset(&st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format, 0x00, sizeof(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format));
 					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format, "%s", Func.m_pBctFmtClient[CTL_LEFT]->GetBcrFormat() );
 					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_LEFT] = CTL_NO;//
				}

				if( st_basic.nBcrFeederUse[3] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_RIGHT] = 3; // 4���� barcode label ����Ca A��A�� 
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_RIGHT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_RIGHT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_RIGHT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_RIGHT] = CTL_NO;
				}
				else//st_basic.nBcrFeederUse[1] == CTL_YES
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_RIGHT] = 1; // 2���� barcode label ����Ca A��A�� 
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_RIGHT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_RIGHT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_RIGHT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_RIGHT] = CTL_NO;
				}
			}
			else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES)
			{
				if( st_basic.nBcrFeederUse[0] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_LEFT] = 0; // 1��Io��I���� barcode label ��Io��I����Ca A�ˢ碮��A��E��c 
					// 			memset(&st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format, 0x00, sizeof(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format));
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].c_Format, "%s", Func.m_pBctFmtClient[CTL_LEFT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_LEFT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_LEFT] = CTL_NO;
				}
				else //st_basic.nBcrFeederUse[2] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_LEFT] = 2; // 3���� barcode label ����Ca A��A�� 
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_LEFT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_LEFT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_LEFT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_LEFT] = CTL_NO;
				}
			}
			else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_YES)
			{
				if( st_basic.nBcrFeederUse[3] == CTL_YES)
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_RIGHT] = 3; // 4���� barcode label ����Ca A��A�� 
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_RIGHT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_RIGHT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode2[CTL_RIGHT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_RIGHT] = CTL_NO;
				}
				else //st_basic.nBcrFeederUse[1] == CTL_YES
				{
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrPos[CTL_RIGHT] = 1; // 2���� barcode label ����Ca A��A�� 
					sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_RIGHT].c_Format, "%s",  Func.m_pBctFmtClient[CTL_RIGHT]->GetBcrFormat() );
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].st_barcode1[CTL_RIGHT].nCommand = CTL_YES;
					st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].nBcrExist[CTL_RIGHT] = CTL_NO;
				}
			}
		}
		else if( ( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_RIGHT] == CTL_NO ) ||
			( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_RIGHT] == CTL_YES ))
		{
			sprintf(mc_jamcode, "601100"); //601100 1 00 "id buffer top Input index program flag error, buffer skip flag is not same."
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9102, COMI.mn_run_status, mc_jamcode);
			break;
		}


		mn_run_step = 3100;
		break;

	case 3100:
		if(st_sync.n_smema_input_index_req == CTL_CHANGE) //8580�� Ŭ������ �������� ���� �̵������ϴٴ� ��ȣ 
		{ 		 			
			mn_run_step = 4000;
// 			mn_run_step = 3200;
		}
		break;

	case 3200:
		if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_LEFT] == CTL_NO &&
			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_RIGHT] == CTL_NO )

		{
			if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES &&
				st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_YES )
			{
				if( st_bcr_feeder[CTL_LEFT].st_bcr.bExist == CTL_YES && st_bcr_feeder[CTL_LEFT].st_bcr.nState == EMBS_PASS &&
					st_bcr_feeder[CTL_RIGHT].st_bcr.bExist == CTL_YES && st_bcr_feeder[CTL_RIGHT].st_bcr.nState == EMBS_PASS )
				{
					mn_run_step = 4000;
				}
			}
			else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == CTL_YES &&
				st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_NO )
			{
				if( st_bcr_feeder[CTL_LEFT].st_bcr.bExist == CTL_YES && st_bcr_feeder[CTL_LEFT].st_bcr.nState == EMBS_PASS )
				{
					mn_run_step = 4000;
				}
			}
			else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == CTL_NO )
			{
				if( st_bcr_feeder[CTL_LEFT].st_bcr.bExist == CTL_YES && st_bcr_feeder[CTL_LEFT].st_bcr.nState == EMBS_PASS )
				{
					mn_run_step = 4000;
				}
			}
			else
			{
				mn_run_step = 4000;
			}
		}
		else
		{
			mn_run_step = 4000;
		}
		break; 

	case 4000:	 		
		 //loader ���� ������� �ʰ� �ܵ��� ����üũ��, smema ����� ������ ������ �����  
		Run_Smema_Ctl.top_idbuffer_datainfo_shift(0, SHIFT_IDBUFF_INDEX_ULD_RECV); //8580 network data -> input index �� ���� ���� ����Ʈ 
		 //2�� ���۴� ������ �����ؾ� �Ѵ� 
		if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_RIGHT] == CTL_YES)
		{//dual �϶��� �������� �̵�, ���Ҿ� �ּ��� ���۰� Dual�� �����ؾ� ������ �����ͷ� �����ϰ�, ���� �����͸� Ŭ�����Ѵ�  
			Run_Smema_Ctl.top_idbuffer_datainfo_shift(1, SHIFT_IDBUFF_INDEX_ULD_RECV); //network data clear 
			mn_run_step = 4100;
		} 		
		break;
	 
	case 4100: //id buffer �������� ��ȿ���� �����Ѵ� 
		//ID_LOT_EMPTY = 0, ID_LOT_START == 1, ID_LOT_WORKING == 2, ID_LOT_END == 3 
		if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_RIGHT] == CTL_YES)
		{//�ΰ��� ���۰� �غ�Ǿ� �־�� �Ѵ� 
			
			if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_LEFT] == ID_LOT_START || st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_RIGHT] == ID_LOT_START )
			{ //2015.0517 new lot start , ���ο� lot ����
				st_var.n_lotstart = ID_LOT_START;


//				st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
//				st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
//				st_var.n_use_density_count[st_basic.mn_device_type] = 0;//reset
//				st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;//reset

				/////////////////////////////////////////////////////////////////////////////////////////////
				//2016.1031
				if( g_lotMgr.GetLotCount() > 1 )
				{
					if( g_lotMgr.GetLotAt(0).GetDenLabelCapa() != g_lotMgr.GetLotAt(1).GetDenLabelCapa() )
					{
						st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
						st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
						st_var.n_use_density_count[st_basic.mn_device_type] = 0;
						st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
					}
					else
					{//2016.1031
						if(st_handler.mn_device_type != st_basic.mn_device_type)
						{
							st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
							st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
							st_var.n_use_density_count[st_basic.mn_device_type] = 0;
							st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
						}
					}
				}
				else
				{
					st_var.n_use_density_flag[st_basic.mn_device_type] = CTL_YES;
					st_var.n_use_density_flag[st_basic.mn_device_type+3] = CTL_YES;
					st_var.n_use_density_count[st_basic.mn_device_type] = 0;
					st_var.n_use_density_count[st_basic.mn_device_type+3] = 0;
				}
				/////////////////////////////////////////////////////////////////////////////////////////////
				st_handler.mn_device_type = st_basic.mn_device_type;


				st_var.n_use_top_skip = CTL_NO;//2015.0327
				st_work.mn_chg_job = CTL_NO;

				//2015.0313
				CString strLotID;
				if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_exist[CTL_LEFT] == CTL_YES)
				{
					strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].c_lot_id[CTL_LEFT]);
					st_handler.m_strVisModel = strLotID;
					g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
					//2015.0423
					g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
					g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
				}
				else if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_exist[CTL_RIGHT] == CTL_YES)
				{
					strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].c_lot_id[CTL_RIGHT]);
					st_handler.m_strVisModel = strLotID;
					g_lotMgr.GetLotByLotID(strLotID).SetStartNewLot(true);
					g_lotMgr.GetLotByLotID(strLotID).SetStrLabelVisionModel(true);
					g_lotMgr.GetLotByLotID(strLotID).SetStrPosVisionModel(true);
				}

				st_var.n_last_module_flag = 0; 
				
				if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
				{
					sprintf(st_msg.c_normal_msg, "[LOT START] lot first start...");
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
				}
			}
			else if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_LEFT] == ID_LOT_WORKING || st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_RIGHT] == ID_LOT_WORKING )
			{ // lot �� �������̴� 
				st_var.n_lotstart = ID_LOT_WORKING;//2015.0313				
			}
			else if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_LEFT] == ID_LOT_END || st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_last_module[CTL_RIGHT] == ID_LOT_END) //lot �� ������ ���� 
			{
				 
// 				if(st_count.n_in_work_cnt[CTL_LEFT] + st_count.n_in_work_cnt[CTL_RIGHT] >= st_var.n_set_lot_work_count - 1) //lot end ������ �������� Ȯ��(���� ó�� ���� Ȯ��)
// 				{//������ ���� ���� �۾� ������ ���� �۾��� ������ ������ �������� lot end�� ���� �ȴ� 
// 					if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
// 					{
// 						sprintf(st_msg.c_normal_msg, "[LOT END START] server cnt[%d], handler cnt[%d]", st_var.n_set_lot_work_count, st_count.n_in_work_cnt[CTL_LEFT] + st_count.n_in_work_cnt[CTL_RIGHT]);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 					}
// 				}
// 				else
// 				{ 
// 					if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
// 					{
// 						sprintf(st_msg.c_abnormal_msg, "[LOT END START] server cnt[%d], handler cnt[%d]", st_var.n_set_lot_work_count, st_count.n_in_work_cnt[CTL_LEFT] + st_count.n_in_work_cnt[CTL_RIGHT]);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 					}
// 				}


				st_var.n_lotstart = ID_LOT_END;
				st_var.n_last_module_flag = 1; 
					
				if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
				{
					sprintf(st_msg.c_normal_msg, "[Last Module] = YES, lot end start...");
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
				}
			}
			if( st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_skip_flag[0] == 0 &&
				st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_skip_flag[1] == 0 )
			{
				CString strLotID;
				if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_LEFT] == CTL_YES)
				{
					strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].c_lot_id[CTL_LEFT]);
				}
				else if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_RIGHT] == CTL_YES)
				{
					strLotID.Format("%s",st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].c_lot_id[CTL_RIGHT]);
				}

				if( st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_exist[CTL_LEFT] == 1 )
				{
					g_lotMgr.GetLotByLotID(strLotID).AddInputCnt( PRIME );
					g_lotMgr.GetLotByLotID(strLotID).AddInputCnt( CUM );
					//2015.0606
					st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_count[CTL_LEFT] = g_lotMgr.GetLotByLotID(strLotID).GetInputCnt( PRIME ) ;
				}
				if( st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_exist[CTL_RIGHT] == 1 )
				{
					g_lotMgr.GetLotByLotID(strLotID).AddInputCnt( PRIME );
					g_lotMgr.GetLotByLotID(strLotID).AddInputCnt( CUM );
					//2015.0606
					st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_count[CTL_RIGHT] = g_lotMgr.GetLotByLotID(strLotID).GetInputCnt( PRIME ) ;
				}
			}			
			mn_run_step = 5000;
		}
		else
		{
			sprintf(mc_jamcode, "600220"); //600220 0 A "id buffer top Input index program in not dual mode setting error -[set flag]."
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9102, COMI.mn_run_status, mc_jamcode);
		}
		break;

	case 4200:
		if(st_var.n_densityccs == CTL_NO && st_var.n_bcrccs == CTL_NO)
			mn_run_step = 5000;
		break;


	//////////////////////////////////////////////////////////////////////////
	//�뷮 �� ����Ʈ���� ���۸� ��û�� ���� 
	//////////////////////////////////////////////////////////////////////////
	case 5000: //�뷮�� ��ġ�� ���۰� ����� ��û�ϰ�, �̵� �����ϴ� 
		if(st_sync.n_top_load1_work_req == CTL_REQ) //move index�� ���۸� ��û�� ���� (�뷮�󺧿��� ����Ʈ ���� �۾� ������ ����)
		{			 			
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_NO)
			{
				st_sync.n_top_load1_work_req = CTL_POSSIBLE; //2014.1201 CTL_FREE; //DATA MIX PROTECT, input index�� �۾� ���������� �˸��� ���� �÷��� ���� 
			
				nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY); //�۾����� ���¸� üũ�Ѵ�, ���۰� ������� �Ѥ� ��
				if(nRet_1 == CTL_GOOD)
				{
					st_var.n_event_moveindex_premove_right_start_flag = 0; //clear 
					mn_run_step = 5100;
				}
				else
				{
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9103, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
				}
			}
		}
		else if(st_var.n_event_moveindex_premove_right_start_flag == 1) //2014.1120 ��� ���� ���⸦ ���� ���͸� ���� �̵���Ų�� 
		{
 			st_sync.n_top_load1_work_req = CTL_BUSY; //2014.1201 CTL_FREE; //2014.1126 //DATA MIX PROTECT, input index�Ƣ� AU���� A��CaA��AOA�� ��E���硾a A��C�� CA�������� ��?�Ʃ� 
 			mn_run_step = 5100;
		}
		break;

	case 5100:
		nRet_1 = idbuffermove_place_process(st_var.n_event_moveindex_premove_right_start_flag);//   
		if(nRet_1 == CTL_GOOD) //���� 
		{			
			if(st_var.n_event_inputindex_premove_right_start_flag != 1)
			{
				st_sync.n_smema_input_index_req = CTL_SORT; //1 cycle ����, ���� ��ġ�� ���۰� �������� smema�� �����Ͽ� 1 cycle ������ �˸��� 
			}
			//2014.1127 st_var.n_event_inputindex_premove_right_start_flag = 0; //clear 
			mn_run_step = 5200;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9104, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 5000;
		}
		break;

	case 5200:	
		if(st_sync.n_density_moveindex_shift_req == CTL_REQ)//2014.1201  //index move �� ���� �̼��� ���� 
		{			
			break;
		}

		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] != CTL_NO || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] != CTL_NO)//2014.1201 
		{
			break;
		}
		mn_run_step = 6000;	 
		break;

	case 6000:
// 		if(st_sync.n_top_load1_work_req != CTL_REQ) //2014.1201 st_sync.n_density_moveindex_shift_req != CTL_REQ) //2014.1201  == CTL_REQ) //2014.1127
// 		{
// 			if(st_sync.n_top_load1_work_req == CTL_POSSIBLE)
// 			{
// 
// 			}
// 			else if(st_sync.n_top_load1_work_req == CTL_BUSY)
// 			{
// 				
// 			}
// 			else
// 			{
// 				break; //mn_density_step working......
// 			}
// 		}
		if(st_sync.n_density_moveindex_shift_req == CTL_REQ)//2014.1201  //index move �� ���� �̼��� ���� 
		{			
			break;
		}

// 		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] != CTL_NO || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] != CTL_NO)//2014.1201 
// 		{
// 			break;
// 		}

		//���� ������ ����Ʈ�Ѵ� 
		Run_Smema_Ctl.top_idbuffer_datainfo_shift(0, SHIFT_IDBUFF_INPUT_INDEX); //input index -> set plate�� ���� ���� ����Ʈ 
		nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
		if(nRet_1 == CTL_GOOD)
		{	
			Run_Smema_Ctl.top_idbuffer_datainfo_shift(1, SHIFT_IDBUFF_INPUT_INDEX); //data clear 

			//////////////////////////////////////////////////////////////////////////		
			if ( st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT]	== CTL_YES ||
				st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES )
			{
				// density��ġ id buffer�� �۾��� ���簡 ������ 
				//			if (g_RunNetwork.st_barcodenet[0].nReady == CTL_YES && g_RunNetwork.st_barcodenet[1].nReady == CTL_YES)
				//			{
				//				// ���� ��Ʈ��ũ ����� �غ� �Ϸ� �Ǿ����� 
				//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == CTL_YES)
				//				{
				//					// ������ �۾��� ���簡 ������ serial �Է��� label ���� ��û 
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLotid,		"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_lot_id[CTL_LEFT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cBoatid,	"%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_LEFT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cSerial,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[CTL_LEFT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLabelcode,			g_lotMgr.GetLotAt(0).GetLabelCode());
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLabelcode,			g_lotMgr.GetLotAt(0).GetRibbonCode());
				//
				// 					g_RunNetwork.st_barcodenet[CTL_LEFT].nReady		= CTL_NO; // left Ae����oAA��I����A��E�����ˢ�ˢ�I ����u��I�Ϩ�A��E�ˡ� 
				//					g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete	= CTL_NO; // left label ��?aA��i ��u�ϩ�A�ˢ� 
				//					g_RunNetwork.st_barcodenet[CTL_LEFT].nCommand	= CTL_YES;// left label ��?aA��i ��u�ϩ�A�ˢ� 
				//				
				//					if(st_handler.cwnd_list != NULL )
				//					{
				//						sprintf(st_msg.c_abnormal_msg, "[RunMove] 6100 g_RunNetwork.st_barcodenet[CTL_LEFT].nReady = %d",g_RunNetwork.st_barcodenet[CTL_LEFT].nReady);
				//						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
				//					}
				//				
				//				}
				//
				//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES)
				//				{
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLotid,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_lot_id[CTL_RIGHT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cBoatid,	"%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_RIGHT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cSerial,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[CTL_RIGHT] );
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLabelcode,		g_lotMgr.GetLotAt(0).GetLabelCode());
				//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLabelcode,		g_lotMgr.GetLotAt(0).GetRibbonCode());
				//					
				// 					g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady		= CTL_NO; // left Ae����oAA��I����A��E�����ˢ�ˢ�I ����u��I�Ϩ�A��E�ˡ� 
				//					g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete		= CTL_NO; // left label ��?aA��i ��u�ϩ�A�ˢ� 
				//					g_RunNetwork.st_barcodenet[CTL_RIGHT].nCommand		= CTL_YES;// left label ��?aA��i ��u�ϩ�A�ˢ� 
				//					if(st_handler.cwnd_list != NULL )
				//					{
				//						sprintf(st_msg.c_abnormal_msg, "[RunMove] 6100 g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady = %d",g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady);
				//						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
				//					}
				//				}
				//
				//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == CTL_YES)
				//				{
				//					// label ���� �ʱ�ȭ 
				//					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrExist[CTL_LEFT] = CTL_NO;
				//				}
				//
				//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES)
				//				{
				//					// label ���� �ʱ�ȭ 
				//					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrExist[CTL_RIGHT] = CTL_NO;
				//				}
				
				st_sync.n_top_load1_work_req = CTL_READY; //��� ���۸� ������ �Դ�, �̶� �뷮���� �۾��� ������ �� �ִ�
				st_var.n_event_inputindex_premove_right_start_flag = 0; //clear 
				mn_run_step = 7000;

				//2014,1210
				st_var.n_bcr_read_input_flag = CTL_NO; //clear 
				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES
					&& st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_RIGHT] == CTL_NO)
				{				 
					if(st_basic.mn_leftbcr == CTL_YES) //���ڵ带 ����Ҷ��� �������� 
					{
						st_var.n_bcr_read_input_flag = CTL_YES;
					}
				}

				//			}
			}
			else
			{
				st_sync.n_top_load1_work_req = CTL_READY; //��� ���۸� ������ �Դ�, �̶� �뷮���� �۾��� ������ �� �ִ�
				st_var.n_event_inputindex_premove_right_start_flag = 0; //clear 
				mn_run_step = 7000;
			}
			//2014.1126 mn_run_step = 6100;
		}
		else
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9105, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
		}
		break;	
 
// 	case 6100:
// 		//////////////////////////////////////////////////////////////////////////		
// 		if ( st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT]	== CTL_YES ||
// 		     st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES )
// 		{
			// density��ġ id buffer�� �۾��� ���簡 ������ 
//			if (g_RunNetwork.st_barcodenet[0].nReady == CTL_YES && g_RunNetwork.st_barcodenet[1].nReady == CTL_YES)
//			{
//				// ���� ��Ʈ��ũ ����� �غ� �Ϸ� �Ǿ����� 
//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == CTL_YES)
//				{
//					// ������ �۾��� ���簡 ������ serial �Է��� label ���� ��û 
//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLotid,		"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_lot_id[CTL_LEFT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cBoatid,	"%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_LEFT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cSerial,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[CTL_LEFT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLabelcode,			g_lotMgr.GetLotAt(0).GetLabelCode());
//					sprintf(g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLabelcode,			g_lotMgr.GetLotAt(0).GetRibbonCode());
//
// 					g_RunNetwork.st_barcodenet[CTL_LEFT].nReady		= CTL_NO; // left Ae����oAA��I����A��E�����ˢ�ˢ�I ����u��I�Ϩ�A��E�ˡ� 
//					g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete	= CTL_NO; // left label ��?aA��i ��u�ϩ�A�ˢ� 
//					g_RunNetwork.st_barcodenet[CTL_LEFT].nCommand	= CTL_YES;// left label ��?aA��i ��u�ϩ�A�ˢ� 
//				
//					if(st_handler.cwnd_list != NULL )
//					{
//						sprintf(st_msg.c_abnormal_msg, "[RunMove] 6100 g_RunNetwork.st_barcodenet[CTL_LEFT].nReady = %d",g_RunNetwork.st_barcodenet[CTL_LEFT].nReady);
//						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
//					}
//				
//				}
//
//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES)
//				{
//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLotid,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_lot_id[CTL_RIGHT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cBoatid,	"%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_RIGHT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cSerial,	"%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[CTL_RIGHT] );
//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLabelcode,		g_lotMgr.GetLotAt(0).GetLabelCode());
//					sprintf(g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLabelcode,		g_lotMgr.GetLotAt(0).GetRibbonCode());
//					
// 					g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady		= CTL_NO; // left Ae����oAA��I����A��E�����ˢ�ˢ�I ����u��I�Ϩ�A��E�ˡ� 
//					g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete		= CTL_NO; // left label ��?aA��i ��u�ϩ�A�ˢ� 
//					g_RunNetwork.st_barcodenet[CTL_RIGHT].nCommand		= CTL_YES;// left label ��?aA��i ��u�ϩ�A�ˢ� 
//					if(st_handler.cwnd_list != NULL )
//					{
//						sprintf(st_msg.c_abnormal_msg, "[RunMove] 6100 g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady = %d",g_RunNetwork.st_barcodenet[CTL_RIGHT].nReady);
//						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
//					}
//				}
//
//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == CTL_YES)
//				{
//					// label ���� �ʱ�ȭ 
//					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrExist[CTL_LEFT] = CTL_NO;
//				}
//
//				if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES)
//				{
//					// label ���� �ʱ�ȭ 
//					st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrExist[CTL_RIGHT] = CTL_NO;
//				}
// 
// 				st_sync.n_top_load1_work_req = CTL_READY; //��� ���۸� ������ �Դ�, �̶� �뷮���� �۾��� ������ �� �ִ�
// 				mn_run_step = 7000;
// //			}
// 		}
// 		else
// 		{
// 			st_sync.n_top_load1_work_req = CTL_READY; //��� ���۸� ������ �Դ�, �̶� �뷮���� �۾��� ������ �� �ִ�
// 			mn_run_step = 7000;
// 		}
// 		break;

	case 7000:
		if(st_sync.n_top_load1_work_req == CTL_CHANGE)
		{//�뷮 �� �ڿ� move index �� ���۸� ��� �ִ� ���·� input index�� ��� �ִ� gripper�� Ǯ�� �δ� ���� �̵��Ͽ� ���۸� �̸� ��� ���� 
			//����� ������ ���� ���°� ��ġ�ϸ� ���� ������ �ϴ� 
			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY); //�۾��� ���¸� üũ�Ѵ�, ���۰� �־�� �Ѵ�  
			if(nRet_1 == CTL_GOOD)
			{
				mn_run_step = 7100;
				mn_run_step = 7010;
			}
			else
			{
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9106, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
			} 
		}
		break;

		//2014,1221
	case 7010:
		if( st_basic.n_mode_device == 1 )
		{
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES
				&& st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_RIGHT] == CTL_NO)
			{
				if ( st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == 1 )
				{
// 					if( st_basic.mn_mode_run == 0 || st_handler.nCommand[CTL_LEFT] != CTL_NO || st_handler.nComplete[CTL_LEFT] != CTL_YES ||
// 						st_handler.nCommand[CTL_RIGHT] != CTL_NO || st_handler.nComplete[CTL_RIGHT] != CTL_YES )
// 						break;
				}
			}
		}
		mn_run_step = 7100;
		break;


	case 7100://����ִ� ���� ����, 8470 �δ� ���� �̵��Ͽ� �������� �۾��� �غ� �Ѵ� 
		set_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //Ŭ������ �����ϰ� �̵� �غ� �Ѵ� 
		mn_run_step = 7110;
		break;

	case 7110:
		nRet_1 = get_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			mn_run_step = 8000;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9107, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 7100;
		}
		break;

	case 8000:
		//2015.0222
		if(st_basic.mn_leftbcr == CTL_YES && st_var.n_bcr_read_input_flag == CTL_YES) break;
		st_sync.n_top_load1_work_req = CTL_SORT; //Ŭ������ ���Ҵ� , one cycle �Ϸ� 
		mn_run_step = 8100;
		break;

	case 8100: //�̸� �̵��Ͽ� loader MC�� �� ���� 
		nRet_1 = CTL_Lib.Single_Move(M_TOPID_LD1, st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK], COMI.mn_runspeed_rate);  
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{			
			mn_run_step = 9000;
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_run_step = 8100;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9108, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "240004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_run_step = 8100;															
		}
		break; 

	case 9000:
		if(st_var.n_last_module_flag == 1) //last module�� YES�̴� lot�� ������ �����̴�, ���ο� lot�� �� �� ���������� ���ο� ����� �������� ���ϰ� ����  
		{
			mn_run_step = 0;

			//test 2014.1115
			if(st_sync.n_smema_input_index_req == CTL_CLEAR) //smema �۾��� ���� ���� 
			{
				
				st_sync.n_smema_input_index_req = CTL_REQ; //8580 ��� ID Buffer�� �̸� �غ��ϰ� ��û�Ѵ� 
				mn_run_step = 1000;
			}

			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
			{
				sprintf(st_msg.c_normal_msg, "[input index] = LOT END, Step = 0");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}
		}
		else
		{
			if(st_sync.n_smema_input_index_req == CTL_CLEAR) //smema �۾��� ���� ���� 
			{

				st_sync.n_smema_input_index_req = CTL_REQ; //8580 ��� ID Buffer�� �̸� �غ��ϰ� ��û�Ѵ� 
				mn_run_step = 1000;
			}			
		}		
		break;
 
	default :
		break;
	}
}

void CRun_IDBuff_Input_Index::Run_Model_Change()
{
	int nRet_1, kk =0;
	CString str_save_file;
	switch(mn_mdl_change_step)
	{
	case 0 :
		if(st_handler.mn_model_change == CTL_YES)
		{//2016.0726
			if( st_handler.mn_curr_back_conv == 1 || st_basic.n_mode_device == 0 )
			{
				mn_mdl_change_step = 3800;
			}
			else
			{
				Func.LoadRegModelData();
				mn_mdl_change_step = 100;
			}
		}
		break;

	case 100:
		{
			if( st_basic.mn_mode_run == false )
			{
				CString strname = st_basic.mstr_device_name;
				strname.Replace(".TXT", "");					
				st_work.m_strCurModel = strname;
			}

			bool bMdl = false;
			for ( int i = 0; i < st_work.m_nMdlTotal; i++)
			{
				if( st_work.m_strModelName[i] == st_work.m_strCurModel/*m_strModelNewname*/)
				{
					bMdl = true;
					break;
				}
			}
			if(bMdl == false)
			{
				//There is no model
				mn_mdl_change_step = 0;
				break;
			}

			mn_mdl_change_step = 1000;
		}
		break;

	case 1000:
		//apply teaching
		st_basic.mstr_device_name = /*m_strModelNewname*/st_work.m_strCurModel + _T(".TXT");
		mn_mdl_change_step = 1100;
		break;

	case 1100:
		mcls_basic.OnDaily_Count_Save();
		mcls_basic.OnBasic_Data_Load();
		nRet_1 = mcls_basic.On_Teach_Data_Load();
		
		if ( nRet_1 == -1 )
		{
			Func.RunRegPartID();
			mn_mdl_change_step = 1200;
			break;
		}
		
		if (st_handler.cwnd_list != NULL)// ����Ʈ �� ȭ�� ����
		{
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, DEVICE_INFO);  // ����̽� ���� ��� ��û
		}
		
		if(st_handler.cwnd_list != NULL )
		{
			sprintf(st_msg.c_normal_msg, "Device Change = %s", st_basic.mstr_device_name);					
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}
		mn_mdl_change_step = 3000;
		//2016.1212
		mn_mdl_change_step = 2000;
		break;
		
	case 1200:
		Func.SendRegPartID();

		// 600411 0 A "Can't find Recipe file."
		sprintf(mc_jamcode,"600411");
		COMI.mn_run_status = CTL_dWARNING;
		CTL_Lib.Alarm_Error_Occurrence(9201, COMI.mn_run_status, mc_jamcode);
		if( st_handler.cwnd_list != NULL )
		{
			sprintf(st_msg.c_normal_msg, " Cannot find model file => %s", st_basic.mstr_device_name);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}		
		mn_mdl_change_step = 0;
		break;

		//2016.1212
	case 2000:
		if( g_lotMgr.GetLotCount() == 1 )
		{
			nRet_1 = COMI.Check_MotPosRange(M_ULD_ROLLER_PITCH, st_motor[M_ULD_ROLLER_PITCH].d_pos[P_GUIDE_UNLOAD_POS], COMI.md_allow_value[M_ULD_ROLLER_PITCH] );
			if (nRet_1 != BD_GOOD)
			{
				mn_mdl_change_step = 2100;
			}
			else
			{
				mn_mdl_change_step = 2200;
			}
		}
		else
		{
			mn_mdl_change_step = 3000;
		}
		break;

	case 2100:
		nRet_1 = CTL_Lib.Single_Move( M_ULD_ROLLER_PITCH, st_motor[ M_ULD_ROLLER_PITCH].d_pos[P_GUIDE_UNLOAD_POS], (int)st_basic.nRunSpeed );
		if( nRet_1 == BD_GOOD )
		{
			mn_mdl_change_step = 2200;
		}
		else if( nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY )
		{
			CTL_Lib.Alarm_Error_Occurrence( 2307, CTL_dWARNING, alarm.mstr_code );
		}
		break;

	case 2200:
		nRet_1 = COMI.Check_MotPosRange(M_INDEX_ROLLER1, st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY], COMI.md_allow_value[M_INDEX_ROLLER1] );
		if (nRet_1 != BD_GOOD)
		{
			mn_mdl_change_step = 2300;
		}
		else
		{
			mn_mdl_change_step = 3000;
		}
		break;

	case 2300:
		nRet_1 = CTL_Lib.Single_Move( M_INDEX_ROLLER1, st_motor[ M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY], (int)st_basic.nRunSpeed );
		if( nRet_1 == BD_GOOD )
		{
			mn_mdl_change_step = 3000;
		}
		else if( nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY )
		{
			CTL_Lib.Alarm_Error_Occurrence( 2309, CTL_dWARNING, alarm.mstr_code );
		}
		break;


	case 3000:
		for ( kk = 0; kk < 4; kk++)
		{
			clsZebra.SetDarkness_TCP(kk);
		}
		m_dwTime_sendbcrstatus = GetCurrentTime();
		mn_mdl_change_step = 3100;
		break;

	case 3100:
		if( GetCurrentTime() - m_dwTime_sendbcrstatus <= 0) m_dwTime_sendbcrstatus = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_sendbcrstatus > 500)
		{
			mn_mdl_change_step = 3200;
		}
		break;

	case 3200:
		for ( kk = 0; kk < 4; kk++)
		{
			clsZebra.LabelTop_TCP(kk);
		}
		m_dwTime_sendbcrstatus = GetCurrentTime();
		mn_mdl_change_step = 3300;
		break;
		
	case 3300:
		if( GetCurrentTime() - m_dwTime_sendbcrstatus <= 0) m_dwTime_sendbcrstatus = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_sendbcrstatus > 500)
		{
			mn_mdl_change_step = 3400;
		}
		break;

	case 3400:
		for ( kk = 0; kk < 4; kk++)
		{
			clsZebra.OnPrintAnswerMode(2, 0, kk);
		}
		m_dwTime_sendbcrstatus = GetCurrentTime();
		mn_mdl_change_step = 3500;
		break;
		
	case 3500:
		if( GetCurrentTime() - m_dwTime_sendbcrstatus <= 0) m_dwTime_sendbcrstatus = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_sendbcrstatus > 500)
		{
			mn_mdl_change_step = 3600;
		}
		break;
		
	case 3600:
		for ( kk = 0; kk < 4; kk++)
		{
			clsZebra.Rewind_Mode_TCP(kk);
		}
		m_dwTime_sendbcrstatus = GetCurrentTime();
		mn_mdl_change_step = 3700;
		break;
		
	case 3700:
		if( GetCurrentTime() - m_dwTime_sendbcrstatus <= 0) m_dwTime_sendbcrstatus = GetCurrentTime();
		if( GetCurrentTime() - m_dwTime_sendbcrstatus > 500)
		{
			mn_mdl_change_step = 3800;
		}
		break;

	case 3800:
		st_handler.mn_model_change = CTL_READY;
		mn_mdl_change_step = 0;
		break;
	}

}

int CRun_IDBuff_Input_Index::idbuffermove_pick_process(int n_site) //�ε� ����Ʈ���� ���� ���� 
{
	int nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0, nRet_5=0, nRet_6=0;
	CString str_msg;
	int nSubStep=0;
	int nFunRet=CTL_PROCEED;
 
	//nSubStep = sb_INPUT_INDEX_LOADER;
	//Func.ThreadFunctionStepTrace(sb_INPUT_INDEX_LOADER + STEP_SUB, st_step.n_sub[nSubStep]);

	switch(mn_pick_step)
	{
	case 0: //������ ���� ���¸� üũ�Ѵ� 		
		mn_pick_step = 1000;
		break;

	//////////////////////////////////////////////////////////////
	//8580 ��� �ִ� idbuffer�� ������ �̵��Ͽ� ���� ������ ���� 
	//////////////////////////////////////////////////////////////
	case 1000:
		
		set_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //Ŭ������ �����ϰ� �̵� �غ� �Ѵ� 
		mn_pick_step = 1010;
		break;

	case 1010:
		nRet_1 = get_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			set_idbuffer_input_length_onoff(0, 0, IO_OFF);
			mn_pick_step = 2000;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9109, COMI.mn_run_status, mc_jamcode);
			mn_pick_step = 1000;
		}
		break;

	case 2000:
		nRet_1 = CTL_Lib.Single_Move(M_TOPID_LD1, st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK], COMI.mn_runspeed_rate);  
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{			
			mn_pick_step = 2100;
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_pick_step = 2000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9110, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "240004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
																						
			mn_pick_step = 2000;
		}
		break; 	

	case 2100:
		nRet_1 = get_idbuffer_input_length_onoff(0, 0, IO_OFF);
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			mn_pick_step = 3000;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{ 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9111, COMI.mn_run_status, mc_jamcode);
			mn_pick_step = 2200;
		}
		break;

	case 2200:
		set_idbuffer_input_length_onoff(0, 0, IO_OFF);
		mn_pick_step = 2100;
		break;

	case 3000:		 
		set_idbuffer_input_clamp_onoff(0, 0, IO_ON); //8580 MC�� �ִ� id buffer�� ��´� 
		mn_pick_step = 3010;
		break;

	case 3010:
		nRet_1 = get_idbuffer_input_clamp_onoff(0, 0, IO_ON); //
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			mn_pick_step = 4000;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			set_idbuffer_input_clamp_onoff(0, 0, IO_OFF); 

			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9112, COMI.mn_run_status, mc_jamcode);
			mn_pick_step = 3000;
		}
		break;

	case 4000:
		nFunRet = CTL_GOOD;
		mn_pick_step = 0;
		break;
	}
 
	return nFunRet;
}

//2016.1122
int CRun_IDBuff_Input_Index::Interlock_run()
{
	int nFunRet = CTL_PROCEED;
	int nRet_1=0;

	nRet_1 = g_ioMgr.get_in_bit(st_io.i_front_top_machine_stop_signal_chk, IO_ON);
	if( nRet_1 == IO_ON )
	{
		if( mn_interlock_sgn == 1 || mn_interlock_sgn == 2 )
		{
			mn_interlock_sgn = 2;
		}
		else
		{
			mn_interlock_sgn = 1;
			m_lWaitInterlock[0] = GetCurrentTime();
		}
	}
	else
	{
		mn_interlock_sgn = 0;
	}

	if( mn_interlock_sgn == 2)
	{
		m_lWaitInterlock[1] = GetCurrentTime();
		m_lWaitInterlock[2] = m_lWaitInterlock[1] - m_lWaitInterlock[0];
		if( m_lWaitInterlock[2] <= 0 ) m_lWaitInterlock[0] = GetCurrentTime();
		if( m_lWaitInterlock[2] >= 200 )
		{
			nFunRet = RET_GOOD;
		}
	}

	return nFunRet;
}	

int CRun_IDBuff_Input_Index::idbuffermove_place_process(int n_pre_move_flag) //���Ա⿡ ���۸� ���µ���  
{
	int nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0, nRet_5=0, nRet_6=0;
	CString str_msg;
	int nSubStep=0;
	int nFunRet=CTL_PROCEED;
	int nBarcodeCount =0;

	long lMotionDone=0;//2014.1120 
	double dwCurrentPos =0;

 
// 	nSubStep = sb_INPUT_INDEX_SEALING;
// 	Func.ThreadFunctionStepTrace(sb_INPUT_INDEX_SEALING + STEP_SUB, st_step.n_sub[nSubStep]);

//	if( g_ioMgr.get_in_bit(st_io.i_front_top_machine_stop_signal_chk, IO_ON) == IO_ON )
//		return nFunRet;
	//2016.1122
	if( Interlock_run() == CTL_GOOD )
	{
		return nFunRet;
	}

	Func.ThreadFunctionStepTrace( 7, mn_place_step);
	switch(mn_place_step)
	{
	case 0: //������ ���� ���¸� üũ�Ѵ� 	
		st_var.n_event_inputindex_premove_right_start_flag = 0; //2014.1120 clear 
		mn_retry_cnt = 0;
		mn_place_step = 1000;
		break;
	//////////////////////////////////////////////////////////////
	//8590 ���� ���۸� �̼��ϴ� �۾� ���� 
	//////////////////////////////////////////////////////////////
	case 1000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer1_chk, IO_OFF); //ID Buffer ���� �ľ�//����� �Ѵ� 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer2_chk, IO_OFF); //ID Buffer ���� �ľ�//����� �Ѵ� 
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON);
		//���Ͱ� left �� �ִ� ���¿��� clamp�ϰ� ������ ������ ����. �̰��� ���� safety�� ���� 

		if(n_pre_move_flag == 1) //�̸� �����̴� ������ �� 
		{
			nRet_1 = IO_OFF; nRet_2 = IO_OFF; 
		}

		if(nRet_1 != IO_OFF || nRet_2 != IO_OFF || nRet_3 != IO_ON)
		{
			if(nRet_1 != IO_OFF)		sprintf(mc_jamcode, "523040");//2017.0214 "527040");//527040 1 00 "Top ID Buffer1 Check Off Error."
			else if(nRet_2 != IO_OFF)   sprintf(mc_jamcode, "523050");//"527050");//527050 1 00 "Top ID Buffer2 Check Off Error."
			else						sprintf(mc_jamcode, "523031");//"526031");//526031 1 00 "Top ID Buffer1.2 UnClamp Cylinder On Error."
																	 //523031 1 00 "Top_ID_Buffer1_Buffer2_UnClamp_Check_On_Error."

			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9120, COMI.mn_run_status, mc_jamcode);
		}
		else
		{
			mn_place_step = 1100;			
		}
		break;

	case 1100://2014.1120 
		if(n_pre_move_flag == 1 || (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_NO))
		{//���� ������ ����� �Ѵ� 
			st_var.n_event_inputindex_premove_right_start_flag = 0; //2014.1120 clear 
			mn_place_step = 2000;
		}
		else
		{//�˶� �ڵ�� �ӽ� ��� 
			sprintf(mc_jamcode, "523040");//2017.0214 "527040");//527040 1 00 "Top ID Buffer1 Check Off Error." //523040 1 00 "Top_ID_Buffer1_Check_Off_Error."
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9121, COMI.mn_run_status, mc_jamcode);
		}
		break;

	case 2000:	
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_clamp_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_unclamp_chk, IO_OFF);
		if(nRet_1 != IO_ON || nRet_2 != IO_OFF)
		{	//521101 1 00 "Top_ID_Buffer_LD1_Shifter_Hook_Clamp_Check_On_Error."
			sprintf(mc_jamcode, "521101"); 
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9122, COMI.mn_run_status, mc_jamcode);
			break;
		}

		if(n_pre_move_flag == 1) //���� ���⸦ ���� �̸� �̵��ϴ� ���̸� 
		{
			nRet_3 = g_comiMgr._cmmSxIsDone(M_TOPID_LD2, &lMotionDone); //index move�� �̵����̰� //��� ���� �Ϸ� == 1, �������� 0
			dwCurrentPos = g_comiMgr.Get_MotCurrentPos(M_TOPID_LD2);
			if(dwCurrentPos > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + st_set.n_inputindex_premove_mm_value) //right ��ġ���� -5mm�̻� ������ ���� ������ �� �������� �ʾ����� ������ üũ�Ѵ� 
			{
				if(nRet_3 == cmERR_NONE &&  lMotionDone != cmTRUE) //index move�� �̵����϶��� �����̴� 
				{
					//���Ͱ� �������̴� �ð� ������ ���� ���� �����ϴ� ���̸� ���� �̵����� 
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else //�������� �������� ���� ��ġ�� ������ ���� ���·� �����̴� ���̸� 
		{
			nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_OFF);
			nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON);
			if(nRet_1 != IO_OFF || nRet_2 != IO_ON)
			{
				dwCurrentPos = g_comiMgr.Get_MotCurrentPos(M_TOPID_LD2);
				if(dwCurrentPos < st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD] - COMI.md_allow_value[M_TOPID_LD2]) //right ��ġ���� -5mm�̻� ������ ���� ������ �� �������� �ʾ����� ������ üũ�Ѵ� 
				{
					sprintf(mc_jamcode, "%02d0008", M_TOPID_LD2);
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9123, COMI.mn_run_status, mc_jamcode);
					break;
				}
			}
		}


		nRet_1 = COMI.Start_SingleMove(M_TOPID_LD1, st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_LAOD], COMI.mn_runspeed_rate);  // �ش� ��ġ�� �̵�
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			mn_place_step = 2100; 
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_place_step = 2000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9124, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "240004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_place_step = 2000;
		}
		break;
		
	case 2100:
		nRet_1 = COMI.Check_SingleMove(M_TOPID_LD1, st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_LAOD]);  // �̵� �Ϸ� Ȯ��
		if(nRet_1 == BD_PROCEED) //2014.1120 indx time ���� 
		{
			if(st_var.n_event_inputindex_premove_right_start_flag == 0) //index move�� �̵����϶��� �����̴� 
			{
				nRet_3 = g_comiMgr._cmmSxIsDone(M_TOPID_LD1, &lMotionDone); //index move�� �̵����̰� //��� ���� �Ϸ� == 1, �������� 0
				dwCurrentPos = g_comiMgr.Get_MotCurrentPos(M_TOPID_LD1);
				if(nRet_3 == cmERR_NONE &&  lMotionDone != cmTRUE) //���� ���� �̵����̰� 
				{
					if(dwCurrentPos < st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK] - st_set.n_inputindex_premove_mm_value) //right ��ġ���� -5mm�̻� ������ ���� ������ �� �������� �ʾ����� ������ üũ�Ѵ� 
					{
						
						set_idbuffer_input_length_onoff(0, 0, IO_ON);

						//���Ͱ� �������̴� �ð� ������ ���� ���� �����ϴ� ���̸� ���� �̵����� 
						st_sync.n_smema_input_index_req = CTL_SORT; //1 cycle ����, ���� ��ġ�� ���۰� �������� smema�� �����Ͽ� 1 cycle ������ �˸��� 
						st_var.n_event_inputindex_premove_right_start_flag = 1;						
					}
				}
			}
		}

		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{					
			mn_place_step = 2200;
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_place_step = 2000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9125, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "240004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_place_step = 2000;
		}
		break; 

	case 2200:
		set_idbuffer_input_length_onoff(0, 0, IO_ON);
		mn_place_step = 2300;
		break;

	case 2300:
		nRet_1 = get_idbuffer_input_length_onoff(0, 0, IO_ON);
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			mn_place_step = 3000;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9126, COMI.mn_run_status, mc_jamcode);
			mn_place_step = 2200;
		}
		break;

	case 3000:
		if(st_handler.n_without_barcode_read == CTL_YES) //���ڵ带 ������� ������ 
		{
			mn_place_step = 4000;		
			
		}
		else
		{
			
			// 		//���ڵ带 üũ�Ѵ� 
			// 		st_var.n_barcode_read_req[0] = CTL_REQ; //loader site ���ڵ� �б� ���� 
			// 		mn_retry_cnt = 0;
	// 		clsBarcode.OnBarcodeReset(); //2014.1102 
			mn_place_step = 3100;	

		}
		break;

	case 3100:		
// 		 //���ڵ� ��� 			
// 		nBarcodeCount = clsBarcode.OnBarcodeCount();
// 
// 		if(nBarcodeCount == 2) //2�� ���� 
// 		{//���ڵ�� �д� ������ loader site �� right(clsBarcode.OnBarcodeReadData[0]) �ϰ� , left(clsBarcode.OnBarcodeReadData[1]) �� �д´� 
// 			st_var.n_barcode_read_data[0][0] = atoi(clsBarcode.OnBarcodeReadData(1));//right buffer
// 			st_var.n_barcode_read_data[0][1] = atoi(clsBarcode.OnBarcodeReadData(0));//left buffer
// 			st_var.n_barcode_read_data[0][2] = nBarcodeCount;
// 			st_step.n_sub[nSubStep] = 2300;	
// 		}
// 		else
// 		{
// 			if(mn_retry_cnt <= 3)
// 			{
// 				mn_retry_cnt++;
// 				mn_place_step = 2500;		
// 			}
// 			else
// 			{
// 				sprintf(mc_jamcode, "800100");//800100 0 A "���ڵ� 2���� ������ ���������� ���� ���߽��ϴ�."					
// 				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; st_handler.n_run_status = dWARNING;
// 				CTL_Lib.Alarm_Error_Occurrence(0, st_handler.n_run_status, mc_jamcode);
// 
// 				mn_retry_cnt = 0;
// 				mn_place_step = 2500;	
// 
// 			}
// 		} 

		mn_place_step = 4000;		
		break;
 
	case 4000: //����� ���� �Դ��� Ȯ���Ѵ� 
		mn_place_step = 5000; //fix clamp�� clamp�ϱ� ������ ���۸� �������� ���� ��ŵ  
		break;

		if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_LEFT] == CTL_YES)
		{
			nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer1_chk, IO_ON); //ID Buffer ���� �ľ� 
		}
		else nRet_1 = IO_ON;

		if(st_idbuff_info[SHIFT_IDBUFF_INPUT_INDEX].n_idbuffer[CTL_RIGHT] == CTL_YES)
		{			
			nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer2_chk, IO_ON); //ID Buffer ���� �ľ� 
		}
		else nRet_2 = IO_ON; 

		if(st_handler.n_without_idbuffer == CTL_YES)// 
		{
			nRet_1 = IO_ON; nRet_2 = IO_ON;//20140929	
		}

		if(nRet_1 != IO_ON || nRet_2 != IO_ON)
		{
			if(nRet_1 != IO_ON)	sprintf(mc_jamcode, "523041");//2017.0214 "527041");//527041 1 00 "Top ID Buffer1 Check On Error."
			else 			        sprintf(mc_jamcode, "523051");//"527051");//527051 1 00 "Top ID Buffer2 Check On Error."

			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9127, COMI.mn_run_status, mc_jamcode);
		}
		else
		{
			mn_place_step = 5000;
		}
		break;

	case 5000:
		nFunRet = CTL_GOOD;
		mn_place_step = 0;
		break;


	default :
		break;
	}
 
	return nFunRet;
}


//clamp 
int CRun_IDBuff_Input_Index::set_idbuffer_input_clamp_onoff(int n_site, int n_ionum, int n_onoff)
{
	if(n_onoff == IO_OFF) //normal ���� normal backward
	{//unclamp
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_clamp, IO_OFF); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_unclamp, IO_ON); 
	}
	else
	{//clamp 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_clamp, IO_ON); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_unclamp, IO_OFF); 
	}
	
	mb_idbuff_input_clamp_flag = true;
	ml_idbuff_input_clamp_wait[0] = GetCurrentTime();
	return true;
}

//clamp 
int CRun_IDBuff_Input_Index::get_idbuffer_input_clamp_onoff(int n_site, int n_ionum, int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2; 
	
	//525100 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check Off Error."
	//525101 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check On Error."
	//525110 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check Off Error."
	//525111 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check On Error."
	
	ml_idbuff_input_clamp_wait[1] = GetCurrentTime();
	ml_idbuff_input_clamp_wait[2] = ml_idbuff_input_clamp_wait[1] - ml_idbuff_input_clamp_wait[0];
	
	if(n_onoff == IO_ON) //clamp 
	{// 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_clamp_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_unclamp_chk, IO_OFF);
		
		if(mb_idbuff_input_clamp_flag == true && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			mb_idbuff_input_clamp_flag = false; 
			ml_idbuff_input_clamp_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_input_clamp_flag == false && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			if(ml_idbuff_input_clamp_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_input_clamp_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{//521101 1 00 "Top_ID_Buffer_LD1_Shifter_Hook_Clamp_Check_On_Error."
			sprintf(mc_jamcode, "521101"); 
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_OFF)  //unclamp
	{ 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_clamp_chk, IO_OFF);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_unclamp_chk, IO_ON);
		
		if(mb_idbuff_input_clamp_flag == true && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			mb_idbuff_input_clamp_flag = false; 
			ml_idbuff_input_clamp_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_input_clamp_flag == false && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			if(ml_idbuff_input_clamp_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_input_clamp_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{//521111 1 00 "Top_ID_Buffer_LD1_Shifter_Hook_UnClamp_Check_On_Error."
			sprintf(mc_jamcode, "521111"); 
			nFunRet = CTL_ERROR;
		}
	}
	
	return nFunRet;
}


//length
int CRun_IDBuff_Input_Index::set_idbuffer_input_length_onoff(int n_site, int n_ionum, int n_onoff)
{
	//normal close
	if(n_onoff == IO_OFF) //normal ���� normal backward
	{//close
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_fwd, IO_OFF); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_bwd, IO_ON); 
	}
	else
	{//open 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_fwd, IO_ON); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld1_shifter_hook_bwd, IO_OFF); 
	}
	
	mb_idbuff_input_length_flag = true;
	ml_idbuff_input_length_wait[0] = GetCurrentTime();
	return true;
}


int CRun_IDBuff_Input_Index::get_idbuffer_input_length_onoff(int n_site, int n_ionum, int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2; 
	
	//525080 1 00 "Top ID Buffer LD1 Shifter Hook Forward Check Off Error."
	//525081 1 00 "Top ID Buffer LD1 Shifter Hook Forward Check On Error."
	//525090 1 00 "Top ID Buffer LD1 Shifter Hook Backward Check Off Error."
	//525091 1 00 "Top ID Buffer LD1 Shifter Hook Backward Check On Error."

	
	ml_idbuff_input_length_wait[1] = GetCurrentTime();
	ml_idbuff_input_length_wait[2] = ml_idbuff_input_length_wait[1] - ml_idbuff_input_length_wait[0];
	
	if(n_onoff == IO_OFF) //normal close 
	{// 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_fwd_chk, IO_OFF);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_bwd_chk, IO_ON);
		
		if(mb_idbuff_input_length_flag == true && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			mb_idbuff_input_length_flag = false; 
			ml_idbuff_input_length_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_input_length_flag == false && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			if(ml_idbuff_input_length_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_input_length_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{//525091 1 00 "Top ID Buffer LD1 Shifter Hook Backward Check On Error."
			sprintf(mc_jamcode, "525091"); 
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_ON)  //open
	{ 		
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_fwd_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld1_shifter_hook_bwd_chk, IO_OFF);
		
		if(mb_idbuff_input_length_flag == true && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			mb_idbuff_input_length_flag = false; 
			ml_idbuff_input_length_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_input_length_flag == false && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			if(ml_idbuff_input_length_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_input_length_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{//525081 1 00 "Top ID Buffer LD1 Shifter Hook Forward Check On Error."	
			sprintf(mc_jamcode, "525081"); 
			nFunRet = CTL_ERROR;
		}
		
	}
	
	return nFunRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CRun_IDBuff_Input_Index::barcode_read_inout_process(int n_site) //2014,1210
{
 	int nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0, nRet_5=0, nRet_6=0;
	CString str_msg;
	int nFunRet=CTL_PROCEED;
	int nShift_idbuff_Pos, nCheckSite_Pos;

	if(n_site == CTL_LEFT)
	{
		nShift_idbuff_Pos = SHIFT_IDBUFF_INDEX_DENSITY;
		//2016.0807
		//nCheckSite_Pos = CTL_LEFT;
		nCheckSite_Pos = CTL_RIGHT;
	}
	else
	{
		nShift_idbuff_Pos = SHIFT_IDBUFF_INDEX_TOP;
		//nCheckSite_Pos = CTL_RIGHT;
		//2016.0807
		nCheckSite_Pos = CTL_LEFT;
	}

	Func.ThreadFunctionStepTrace( 5, mn_bcrIn_step);

	switch(mn_bcrIn_step)
	{
	case 0: //������ ���� ���¸� üũ�Ѵ� 	
		if(st_basic.mn_leftbcr == CTL_YES || st_basic.mn_leftbcr == CTL_YES) 
		{
			mn_bcrIn_step = 1000;
		}
		else
		{
			mn_bcrIn_step = 6000;
		}
		mn_barcode_retry_cnt[n_site] = 0;
		break;

	//////////////////////////////////////////////////////////////
	//8570 ��� �ִ� idbuffer�� ������ �̵��Ͽ� ���� ������ ���� 
	//////////////////////////////////////////////////////////////
	case 1000:	
		if(st_basic.mn_leftbcr == CTL_YES || st_basic.mn_leftbcr == CTL_YES) 
		{
			st_sync.n_barcode_read_serial_num[n_site][CTL_LEFT] = 0; //CLEAR 
			st_sync.n_barcode_read_serial_num[n_site][CTL_RIGHT] = 0; //CLEAR 

			ml_barcode_limit_time[n_site][0] = GetCurrentTime();
			if(n_site == CTL_LEFT)
			{
				Func.OnBcrInputreader();
			}
			else
			{
				Func.OnBcrOutputreader();
			}
			mn_bcrIn_step = 2000;
		} 
		break;
		
	case 2000:		 
		if(st_sync.n_barcode_read_serial_num[n_site][nCheckSite_Pos] > 0)
		{//end
			if(st_idbuff_info[nShift_idbuff_Pos].n_idbuff_num[nCheckSite_Pos] == st_sync.n_barcode_read_serial_num[n_site][nCheckSite_Pos])
			{//== ok
				mn_bcrIn_step = 6000;
			}
			else
			{
				if(st_idbuff_info[nShift_idbuff_Pos].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[nShift_idbuff_Pos].n_skip_flag[CTL_RIGHT] == CTL_YES)
				{
					mn_bcrIn_step = 6000;
				}
				else
				{
					mn_barcode_retry_cnt[n_site]++;
					if(mn_barcode_retry_cnt[n_site] > st_basic.mn_network_retry_cnt)
					{
						mn_barcode_retry_cnt[n_site] = 0;
						mn_bcrIn_step = 0;
						
						if(n_site == CTL_LEFT)	sprintf(mc_jamcode, "800021"); //800021 0 A "barcode read serial number mismatch error[load Input site]."
						else                    sprintf(mc_jamcode, "800023"); //800023 0 A "barcode read serial number mismatch error[lable output site]." 
						alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; CTL_Lib.mn_run_status = dWARNING;
						CTL_Lib.Alarm_Error_Occurrence(9128, dWARNING, mc_jamcode);					
					}
					else
					{
						mn_bcrIn_step = 1000;
					}
				}
			}
			
		}
		else if(st_sync.n_barcode_read_serial_num[n_site][CTL_LEFT] == -1)
		{
			mn_barcode_retry_cnt[n_site]++;
			if(mn_barcode_retry_cnt[n_site] > st_basic.mn_network_retry_cnt)
			{
				mn_barcode_retry_cnt[n_site] = 0;
				mn_bcrIn_step = 1000;
				
				if(n_site == CTL_LEFT)	sprintf(mc_jamcode, "800020"); //800020 0 A "barcode read error[load Input site]."
				else                    sprintf(mc_jamcode, "800022"); //800022 0 A "barcode read error[lable output site]."
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; CTL_Lib.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9129, dWARNING, mc_jamcode);					
			}
			else
			{
				mn_bcrIn_step = 1000;
			}
		}
		else
		{
			ml_barcode_limit_time[n_site][1] = GetCurrentTime();
			ml_barcode_limit_time[n_site][2] = ml_barcode_limit_time[n_site][1] - ml_barcode_limit_time[n_site][0];
			if(ml_barcode_limit_time[n_site][2] > st_basic.mn_network_wait_time)
			{
				mn_barcode_retry_cnt[n_site]++;
				if(mn_barcode_retry_cnt[n_site] > st_basic.mn_network_retry_cnt)
				{
					mn_barcode_retry_cnt[n_site] = 0;
					mn_bcrIn_step = 1000;
					
					if(n_site == CTL_LEFT)	sprintf(mc_jamcode, "800020"); //800020 0 A "barcode read error[load Input site]."
					else                    sprintf(mc_jamcode, "800022"); //800022 0 A "barcode read error[lable output site]."
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; CTL_Lib.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9130, dWARNING, mc_jamcode);					
				}
				else
				{
					mn_bcrIn_step = 1000;
				}
			}
		}
		break;

	case 6000:
		nFunRet = CTL_GOOD;
		mn_bcrIn_step = 0;
		break;
	}

	return nFunRet;
}

int CRun_IDBuff_Input_Index::OnServerNewLotin()
{
	int nFuncRet = CTL_PROCEED;
	int nRet = VAR_INIT_;
	CString sSerial = "";
	CString strJamCode;

	Func.ThreadFunctionStepTrace( 3, mn_sever_step);

	switch(mn_sever_step)
	{
	case 0:
		{
			m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
			mn_sever_step = 10;
		}
		break;

	case 10:
		m_nRetryTest = 0;
		st_mes_data.srt_LOT_ID = st_handler.m_strNewLot;
		st_mes_data.srt_SERIAL = "";
		st_mes_data.srt_RETRY="NO";
		m_nRetryCnt = 0;
		st_mes_data.srt_RETRY_CNT = (LPCTSTR)"0";
		mn_sever_step = 100;
		break;

	case 20:
		m_nRetryTest++;
		if( m_nRetryCnt > 3 ) m_nRetryCnt = 1;
		st_mes_data.srt_RETRY_CNT.Format("%d", m_nRetryTest);
		st_mes_data.srt_RETRY="YES";
		mn_sever_step = 100;
		break;
		
	case 100:
		evMes.OnPutToQueue(MES_PACKING_MASTER_INFO);
		
		(st_client[0].stComm[MES_PACKING_MASTER_INFO]).nResponse = CTL_PROCEED;
		
		m_dwTimeBcrFNetwork[0] = GetCurrentTime();
		mn_sever_step = 101;		
		break;
	
	case 101:
		m_dwTimeBcrFNetwork[1] = GetCurrentTime();
		m_dwTimeBcrFNetwork[2] = m_dwTimeBcrFNetwork[1] - m_dwTimeBcrFNetwork[0];
		if (m_dwTimeBcrFNetwork[2] < 0)
		{
			m_dwTimeBcrFNetwork[0] = GetCurrentTime();
			break;
		}
		if (m_dwTimeBcrFNetwork[2] > 500)
		{
			m_dwTimeBcrFNetwork[0] = GetCurrentTime();
			mn_sever_step = 110;
		}
		break;

	case 110:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_PACKING_MASTER_INFO]).nResponse == CTL_GOOD)
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_sever_step = 200;
			}
			else
			{
				m_dwTimeBcrFNetwork[1] = GetCurrentTime();
				m_dwTimeBcrFNetwork[2] = m_dwTimeBcrFNetwork[1] - m_dwTimeBcrFNetwork[0];
				if (m_dwTimeBcrFNetwork[2] < 0)
				{
					m_dwTimeBcrFNetwork[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTimeBcrFNetwork[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_sever_step = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_sever_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9131, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_PACKING_MASTER_INFO]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_sever_step = 100;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					// 900105 1 00 "New Lot does not response from server"
					alarm.mstr_code		= "900105";
					CTL_Lib.Alarm_Error_Occurrence(9132, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTimeBcrFNetwork[1] = GetCurrentTime();
				m_dwTimeBcrFNetwork[2] = m_dwTimeBcrFNetwork[1] - m_dwTimeBcrFNetwork[0];
				if (m_dwTimeBcrFNetwork[2] < 0)
				{
					m_dwTimeBcrFNetwork[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTimeBcrFNetwork[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCount = 5;
					}
					mn_sever_step = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCount >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
						m_nStep_MES = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9133, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTimeBcrFNetwork[1] = GetCurrentTime();
			m_dwTimeBcrFNetwork[2] = m_dwTimeBcrFNetwork[1] - m_dwTimeBcrFNetwork[0];
			if (m_dwTimeBcrFNetwork[2] < 0)
			{
				m_dwTimeBcrFNetwork[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTimeBcrFNetwork[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCount++;	// ��õ� Ƚ�� ����
				if (m_nRetryCount > 5)
				{
					m_nRetryCount = 5;
				}
				mn_sever_step = 100;	// ��� ��õ� �������� ����
				
				if (m_nRetryCount >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
					mn_sever_step = 100;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9134, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 200:
// 		m_nReq_MES	= WORK_NONE_;	// [����] Id ���� ���� �۾� ��û �÷���
		{
			CString strLog;
			strLog.Format("[SERVER_NEW_LOT_IN1] = NO. st_var.n_newlotin: %d", st_var.n_newlotin);
			Func.On_LogFile_Add(99, strLog);
			mn_sever_step	= 0;
			st_var.n_newlotin = CTL_NO;
			st_handler.m_nLotServer = CTL_NO;
			nFuncRet = CTL_GOOD;
		}
		break;
	}

	return nFuncRet;
}

int CRun_IDBuff_Input_Index::OngetFmtfromServer()
{
	int nFuncRet = CTLBD_RET_PROCEED;
	int mn_gleft = 0, mn_gright = 0;
	CString strJamCode;
	
	switch(mn_fmt_step)
	{
	case 0:
		mn_left = mn_right = 0;
		mn_comm_pos = CTL_LEFT;
		mn_fmt_step = 1000;
		break;

	case 1000:
// 		if( st_handler.mn_curr_back_conv == 1 || ( st_basic.n_mode_device == 1 && st_basic.mn_mode_run == 1 &&
// 			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_LEFT] == CTL_NO &&
// 			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[CTL_RIGHT] == CTL_NO ) )
// 		{
// 			if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_LEFT] == 1 &&
// 				st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_RIGHT] == 1 &&
// 				( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == 1 ||
// 				st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == 1 ) )
// 			{
// 				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == 1 )
// 				{
// 					mn_left = 1;
// 					g_RunNetwork.st_barcodenet[CTL_LEFT].nCommand = CTL_YES;
// 				}
// 				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == 1 )
// 				{
// 					mn_right = 1;
// 					g_RunNetwork.st_barcodenet[CTL_RIGHT].nCommand = CTL_YES;						
// 				}
// 			}
// 			mn_fmt_step = 1100;
// 		}
// 		else
// 		{
// 			mn_fmt_step = 2000;	
// 		}
		if( st_handler.mn_curr_back_conv == 1 || ( st_basic.n_mode_device == 1 && st_basic.mn_mode_run == 1 &&
			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_skip_flag[mn_comm_pos] == CTL_NO ) )
		{
			if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[mn_comm_pos] == 1 &&
				( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[mn_comm_pos] == 1) )
			{
				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[mn_comm_pos] == 1 )
				{
					g_RunNetwork.st_barcodenet[mn_comm_pos].nCommand = CTL_YES;
				}
			}
			mn_fmt_step = 1100;
		}
		break;

	case 1100:
		if(g_RunNetwork.st_barcodenet[mn_comm_pos].nComplete == CTL_YES)
		{
			mn_fmt_step = 2000;
		}
		else if( g_RunNetwork.st_barcodenet[mn_comm_pos].nCommand == CTL_NO)
		{
			//mn_fmt_step = 2000;
		}
		break;

	case 2000:
		if( g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete == CTL_YES &&
			g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete == CTL_YES ) 
		{
			mn_fmt_step = 3000;
		}
		else
		{
			if( g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete != CTL_YES )
			{
				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_LEFT] == 1 &&
					( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == 0) )
				{
					if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
					{
						sprintf(st_msg.c_abnormal_msg, "[FmtFromServer] CTL_LEFT is not Device");
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					sprintf(mc_jamcode, "601000"); //601000 1 00 "id buffer top Input index program in Left flag setting error from front machine.
					CTL_Lib.Alarm_Error_Occurrence(9135, dWARNING, mc_jamcode);
				}
				else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_LEFT] == 1 &&
					( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_LEFT] == 1) )
				{
					mn_comm_pos = CTL_LEFT;
					mn_fmt_step = 1000;
				}
			}
			else if( g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete != CTL_YES )
			{
				if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_RIGHT] == 1 &&
					( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == 0) )
				{
					if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
					{
						sprintf(st_msg.c_abnormal_msg, "[FmtFromServer] CTL_RIGHT is not Device");
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
				}
				else if( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuffer[CTL_RIGHT] == 1 &&
					( st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_exist[CTL_RIGHT] == 1) )
				{
					mn_comm_pos = CTL_RIGHT;
					mn_fmt_step = 1000;
				}				
			}
		}
		break;

	case 3000:
		g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete = CTL_NO;
		g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete = CTL_NO;
		nFuncRet = CTLBD_RET_GOOD;
		mn_fmt_step = 0;
		break;
	}

	return nFuncRet;
}

int CRun_IDBuff_Input_Index::OnServerCCS()
{
	int nFuncRet = CTL_PROCEED;

	int nRet = VAR_INIT_;
	CString sSerial = "";

	Func.ThreadFunctionStepTrace( 4, mn_ccs_step);
	switch(mn_ccs_step)
	{
	case 0: 
		// [Eqp->MES] �޽��� ���� ��û�� ��ٸ�
		//if (m_nReq_MES == WORK_SUPPLY_)
		{
			m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
			mn_ccs_step = 10;
		}
		break;

	case 10:
// 		771000 1 00 "Density CCS is not same."
// 		772000 1 00 "BCR Label CCS is not same."
		if( Func.CmpStrFile(st_handler.m_strDensityLabel[st_basic.mn_device_type], st_handler.m_strDensityLabel[st_basic.mn_device_type+3] ))
		{
			if( Func.CmpStrFile(st_handler.m_strDistributionLabel[0], st_handler.m_strDistributionLabel[1] ) &&
				Func.CmpStrFile(st_handler.m_strDistributionLabel[2], st_handler.m_strDistributionLabel[3] ) &&
				Func.CmpStrFile(st_handler.m_strDistributionLabel[0], st_handler.m_strDistributionLabel[2] ) )
			{
				if( Func.CmpStrFile(st_handler.m_strDistributionRibbon[0], st_handler.m_strDistributionRibbon[1] ) &&
					Func.CmpStrFile(st_handler.m_strDistributionRibbon[2], st_handler.m_strDistributionRibbon[3] ) &&
					Func.CmpStrFile(st_handler.m_strDistributionRibbon[0], st_handler.m_strDistributionRibbon[2] ) )
				{
					mn_ccs_step = 100;
				}
				else
				{
					alarm.mstr_code		= "772000";
					CTL_Lib.Alarm_Error_Occurrence(9136, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				alarm.mstr_code		= "772000";
				CTL_Lib.Alarm_Error_Occurrence(9136, CTL_dWARNING, alarm.mstr_code );
			}
		}
		else
		{
			alarm.mstr_code		= "771000";
			CTL_Lib.Alarm_Error_Occurrence(9136, CTL_dWARNING, alarm.mstr_code );
		}
		break;
		
	case 100:
		// - �̰����� ����� ���翡 ���� ������ Ȯ���ؾ� �� �κ��� (TRACE_PK_SSD_) ����ü �κ���
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[0]);
		if (sSerial != "")
		{
			//2015.0619
// 			evMes.OnPutToQueue(MES_BOAT_ID_MODIF_LIN_);
// 			
// 			m_dwTime_Network[0] = GetCurrentTime();
// 			mn_ccs_step = 110;
			m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
			mn_ccs_step = 200;
		}
		// ������ ��쿡�� �޽��� �������� ����
// 		else
// 		{
// 			mn_ccs_step = 200;
// 		}
		break;

	case 110:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_LIN_]).nResponse == CTL_GOOD)
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_ccs_step = 200;
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9136, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_LIN_]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 100;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 100;	// ��� ��õ� �������� ����
					
					// 900104 1 00 "Density CCS or DTBT CCS does not response from server"
					alarm.mstr_code		= "900104";
					CTL_Lib.Alarm_Error_Occurrence(9137, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9138, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTime_Network[1] = GetCurrentTime();
			m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
			if (m_dwTime_Network[2] < 0)
			{
				m_dwTime_Network[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 100;	// ��� ��õ� �������� ����
				
				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 100;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9139, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 200:
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);
		if (sSerial != "")
		{
			st_mes_data.srt_LOT_ID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
			st_mes_data.srt_BOAT_ID.Format("%d", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_LEFT]);
			st_mes_data.srt_C_SERIAL.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);

			//2016.0721
/*			
			if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
			{
				st_basic.mn_device_type = 0;
			}
			else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
			{
				st_basic.mn_device_type = 1;
			}
			else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
			{
				st_basic.mn_device_type = 2;
			}
			else
			{
				st_basic.mn_device_type = 2;
			}
*/
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//st_handler.mn_device_types have to update at ID_START. It will just check mn_device_type in here.
			//2016.1031
			if( st_handler.mn_device_type > -1 && st_handler.mn_device_type < 3)
			{
				if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[st_handler.mn_device_type])
				{
					st_basic.mn_device_type = st_handler.mn_device_type;
				}
				else
				{
					if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
					{
						st_basic.mn_device_type = 0;
					}
					else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
					{
						st_basic.mn_device_type = 1;
					}
					else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
					{
						st_basic.mn_device_type = 2;
					}
					else
					{
						st_basic.mn_device_type = 2;				
					}
				}
			}
			else
			{
				if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
				{
					st_basic.mn_device_type = 0;
				}
				else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
				{
					st_basic.mn_device_type = 1;
				}
				else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
				{
					st_basic.mn_device_type = 2;
				}
				else
				{
					st_basic.mn_device_type = 2;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			//2015.0428
			st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s",st_handler.m_strDensityLabel[st_basic.mn_device_type]);
			//st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.m_strDensity[st_basic.mn_device_type]);
			//2015.0404
			//if( g_lotMgr.GetLotCount() <= 1 )
			//	st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetDenLabelCode());
			//else
			//	st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCode());
			evMes.OnPutToQueue(MES_BRAND_DENSITY_LABEL_CCS);

			m_dwTime_Network[0] = GetCurrentTime();
			mn_ccs_step = 210;
		}
		// ������ ��쿡�� �޽��� �������� ����
// 		else
// 		{
// 			mn_ccs_step = 300;
// 		}
		break;

	case 210:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BRAND_DENSITY_LABEL_CCS]).nResponse == CTL_GOOD )
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_ccs_step = 300;
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 200;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(10002, CTL_dWARNING, alarm.mstr_code );
					}
				}				
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BRAND_DENSITY_LABEL_CCS]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 200;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 200;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9140, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 200;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 200;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9141, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTime_Network[1] = GetCurrentTime();
			m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
			if (m_dwTime_Network[2] < 0)
			{
				m_dwTime_Network[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 200;	// ��� ��õ� �������� ����
				
				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 200;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9142, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 300:
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);
		if (sSerial != "")
		{
			st_mes_data.srt_LOT_ID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
			st_mes_data.srt_BOAT_ID.Format("%d", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_RIGHT]);
			st_mes_data.srt_C_SERIAL.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);

			//2016.0721
/*			if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
		{
				st_basic.mn_device_type = 0;
			}
			else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
			{
				st_basic.mn_device_type = 1;
			}
			else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
			{
				st_basic.mn_device_type = 2;
			}
			else
			{
				st_basic.mn_device_type = 2;
			}
*/

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//st_handler.mn_device_types have to update at ID_START. It will just check mn_device_type in here.
			//2016.1031
			if( st_handler.mn_device_type > -1 && st_handler.mn_device_type < 3)
			{
				if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[st_handler.mn_device_type])
				{
					st_basic.mn_device_type = st_handler.mn_device_type;
				}
				else
				{
					if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
					{
						st_basic.mn_device_type = 0;
					}
					else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
					{
						st_basic.mn_device_type = 1;
					}
					else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
					{
						st_basic.mn_device_type = 2;
					}
					else
					{
						st_basic.mn_device_type = 2;				
					}
				}
			}
			else
			{
				if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[0])
				{
					st_basic.mn_device_type = 0;
				}
				else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[1])
				{
					st_basic.mn_device_type = 1;
				}
				else if(g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCapa() == st_handler.m_strDensityCapa[2])
				{
					st_basic.mn_device_type = 2;
				}
				else
				{
					st_basic.mn_device_type = 2;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			//2015.0428
			st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s",st_handler.m_strDensityLabel[st_basic.mn_device_type+3]);
			//st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.m_strDensity[st_basic.mn_device_type]);

			//2015.0404
			//if( g_lotMgr.GetLotCount() <= 0 )
			//	st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetDenLabelCode());
			//else
			//	st_mes_data.srt_DEN_LABEL_MAT_CODE.Format("%s", g_lotMgr.GetLotByLotID(st_mes_data.srt_LOT_ID).GetDenLabelCode());

			evMes.OnPutToQueue(MES_BRAND_DENSITY_LABEL_CCS);

			m_dwTime_Network[0] = GetCurrentTime();
			mn_ccs_step = 310;
		}
		break;

	case 310:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BRAND_DENSITY_LABEL_CCS]).nResponse == CTL_GOOD )
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_ccs_step = 400;
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 300;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(10002, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BRAND_DENSITY_LABEL_CCS]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 300;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 300;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9149, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 300;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 300;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9146, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTime_Network[1] = GetCurrentTime();
			m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
			if (m_dwTime_Network[2] < 0)
			{
				m_dwTime_Network[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 300;	// ��� ��õ� �������� ����
				
				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 300;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9192, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 400:
		// - �̰����� ����� ���翡 ���� ������ Ȯ���ؾ� �� �κ��� (TRACE_PK_SSD_) ����ü �κ���
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);
		if (sSerial != "")
		{
			st_mes_data.srt_LOT_ID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
			st_mes_data.srt_BOAT_ID.Format("%d", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_RIGHT]);
			st_mes_data.srt_C_SERIAL.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);
			//st_mes_data.srt_DTBT_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetLabelCode());
			//st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetRibbonCode());
			//2015.0428
			if( st_var.n_using_barcode == 0 )
			{
				st_mes_data.srt_DTBT_MAT_CODE.Format("%s", st_handler.m_strDistributionLabel[1]);
				st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", st_handler.m_strDistributionRibbon[1]);
			}
			else
			{
				st_mes_data.srt_DTBT_MAT_CODE.Format("%s", st_handler.m_strDistributionLabel[3]);
				st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", st_handler.m_strDistributionRibbon[3]);
			}

			evMes.OnPutToQueue(MES_BRAND_DTBT_LABEL_CCS);
			
			m_dwTime_Network[0] = GetCurrentTime();
			mn_ccs_step = 410;
		}
		// ������ ��쿡�� �޽��� �������� ����
		else
		{
			mn_ccs_step = 500;
		}
		break;

	case 410:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BRAND_DTBT_LABEL_CCS]).nResponse == CTL_GOOD)
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_ccs_step = 500;
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 400;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 400;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9143, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BRAND_DTBT_LABEL_CCS]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 400;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 400;	// ��� ��õ� �������� ����
					
					// 900104 1 00 "Density CCS or DTBT CCS does not response from server"
					alarm.mstr_code		= "900104";
					CTL_Lib.Alarm_Error_Occurrence(9144, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 400;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 400;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9145, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTime_Network[1] = GetCurrentTime();
			m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
			if (m_dwTime_Network[2] < 0)
			{
				m_dwTime_Network[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 400;	// ��� ��õ� �������� ����
				
				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 400;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9146, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 500:
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);
		if (sSerial != "")
		{
			st_mes_data.srt_LOT_ID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
			st_mes_data.srt_BOAT_ID.Format("%d", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_LEFT]);
			st_mes_data.srt_C_SERIAL.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);
			//2015.0224
			//st_mes_data.srt_DTBT_MAT_CODE.Format("%s",st_handler.m_strDistributionLabel[0]);
//			st_mes_data.srt_DTBT_MAT_CODE.Format("%s", g_lotMgr.m_strBcrLabel[0]);
// 			st_mes_data.srt_DTBT_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetLabelCode());
			//2015.0224
			//st_mes_data.srt_RIBBON_MAT_CODE.Format("%s",st_handler.m_strDistributionRibbon[0]);
// 			st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", g_lotMgr.m_strBcrRibbon[0]);
// 			st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", g_lotMgr.GetLotAt(0).GetRibbonCode());
			//2015.0428
			if( st_var.n_using_barcode == 0 )
			{
				st_mes_data.srt_DTBT_MAT_CODE.Format("%s", st_handler.m_strDistributionLabel[0]);
				st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", st_handler.m_strDistributionRibbon[0]);
			}
			else
			{
				st_mes_data.srt_DTBT_MAT_CODE.Format("%s", st_handler.m_strDistributionLabel[2]);
				st_mes_data.srt_RIBBON_MAT_CODE.Format("%s", st_handler.m_strDistributionRibbon[2]);
			}

			evMes.OnPutToQueue(MES_BRAND_DTBT_LABEL_CCS);

			m_dwTime_Network[0] = GetCurrentTime();
			mn_ccs_step = 510;
		}
		// ������ ��쿡�� �޽��� �������� ����
		else
		{
			mn_ccs_step = 600;
		}
		break;

	case 510:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ( (st_client[0].stComm[MES_BRAND_DTBT_LABEL_CCS]).nResponse == CTL_GOOD )
			{
				m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
				mn_ccs_step = 600;
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 500;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(10001, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BRAND_DTBT_LABEL_CCS]).nResponse == CTL_ERROR)
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 500;	// ��� ��õ� �������� ����

				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 500;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9147, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_dwTime_Network[1] = GetCurrentTime();
				m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
				if (m_dwTime_Network[2] < 0)
				{
					m_dwTime_Network[0] = GetCurrentTime();
					break;
				}
				
				if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCnt++;	// ��õ� Ƚ�� ����
					if (m_nRetryCnt > 5)
					{
						m_nRetryCnt = 5;
					}
					mn_ccs_step = 500;	// ��� ��õ� �������� ����
					
					if (m_nRetryCnt >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
						mn_ccs_step = 500;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9148, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_dwTime_Network[1] = GetCurrentTime();
			m_dwTime_Network[2] = m_dwTime_Network[1] - m_dwTime_Network[0];
			if (m_dwTime_Network[2] < 0)
			{
				m_dwTime_Network[0] = GetCurrentTime();
				break;
			}
			
			if (m_dwTime_Network[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCnt++;	// ��õ� Ƚ�� ����
				if (m_nRetryCnt > 5)
				{
					m_nRetryCnt = 5;
				}
				mn_ccs_step = 500;	// ��� ��õ� �������� ����
				
				if (m_nRetryCnt >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCnt = 0;	// [����] �۾� ��õ� Ƚ��
					mn_ccs_step = 500;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9149, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 600:
// 		m_nReq_MES	= WORK_NONE_;	// [����] Id ���� ���� �۾� ��û �÷���
		mn_ccs_step	= 0;
		nFuncRet = CTL_GOOD;
		break;
	}
	return nFuncRet;
}

int CRun_IDBuff_Input_Index::OnServerBaotIDIn()
{
	int nFuncRet = CTL_PROCEED;

	int nRet = VAR_INIT_;
	CString sSerial = "";

	Func.ThreadFunctionStepTrace( 6, m_nStep_MES);
	switch(m_nStep_MES)
	{
	case 0: 
		// [Eqp->MES] �޽��� ���� ��û�� ��ٸ�
		//if (m_nReq_MES == WORK_SUPPLY_)
		{
			m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
			m_nStep_MES = 100;
		}
		break;

	case 100:
		// - �̰����� ����� ���翡 ���� ������ Ȯ���ؾ� �� �κ��� (TRACE_PK_SSD_) ����ü �κ���
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[0]);
		if (sSerial != "")
		{
			evMes.OnPutToQueue(MES_BOAT_ID_MODIF_LIN_);
			
			m_lWaitResp[0] = GetCurrentTime();
			m_nStep_MES = 110;
		}
		// ������ ��쿡�� �޽��� �������� ����
		else
		{
			m_nStep_MES = 200;
		}
		break;

	case 110:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_LIN_]).nResponse == CTL_GOOD)
			{
				m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
				m_nStep_MES = 200;
			}
			else
			{
				m_lWaitResp[1] = GetCurrentTime();
				m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
				if (m_lWaitResp[2] < 0)
				{
					m_lWaitResp[0] = GetCurrentTime();
					break;
				}
				
				if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCount++;	// ��õ� Ƚ�� ����
					if (m_nRetryCount > 5)
					{
						m_nRetryCount = 5;
					}
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCount >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
						m_nStep_MES = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9150, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_LIN_]).nResponse == CTL_ERROR)
			{
				m_nRetryCount++;	// ��õ� Ƚ�� ����
				if (m_nRetryCount > 5)
				{
					m_nRetryCount = 5;
				}
				m_nStep_MES = 100;	// ��� ��õ� �������� ����

				if (m_nRetryCount >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9151, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_lWaitResp[1] = GetCurrentTime();
				m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
				if (m_lWaitResp[2] < 0)
				{
					m_lWaitResp[0] = GetCurrentTime();
					break;
				}
				
				if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCount++;	// ��õ� Ƚ�� ����
					if (m_nRetryCount > 5)
					{
						m_nRetryCount = 5;
					}
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCount >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
						m_nStep_MES = 100;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9152, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_lWaitResp[1] = GetCurrentTime();
			m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
			if (m_lWaitResp[2] < 0)
			{
				m_lWaitResp[0] = GetCurrentTime();
				break;
			}
			
			if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCount++;	// ��õ� Ƚ�� ����
				if (m_nRetryCount > 5)
				{
					m_nRetryCount = 5;
				}
				m_nStep_MES = 100;	// ��� ��õ� �������� ����
				
				if (m_nRetryCount >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9153, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 200:
		sSerial.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[1]);
		if (sSerial != "")
		{
			evMes.OnPutToQueue(MES_BOAT_ID_MODIF_RIN_);

			m_lWaitResp[0] = GetCurrentTime();
			m_nStep_MES = 210;
		}
		// ������ ��쿡�� �޽��� �������� ����
		else
		{
			m_nStep_MES = 300;
		}
		break;

	case 210:
		nRet = evMes.OnGet_MesWork();
		// ���������� ���� ����
		if (nRet == REPLY_CORRECT_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_RIN_]).nResponse == CTL_GOOD)
			{
				m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
				m_nStep_MES = 300;
			}
			else
			{
				m_lWaitResp[1] = GetCurrentTime();
				m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
				if (m_lWaitResp[2] < 0)
				{
					m_lWaitResp[0] = GetCurrentTime();
					break;
				}
				
				if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCount++;	// ��õ� Ƚ�� ����
					if (m_nRetryCount > 5)
					{
						m_nRetryCount = 5;
					}
					m_nStep_MES = 100;	// ��� ��õ� �������� ����
					
					if (m_nRetryCount >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
						m_nStep_MES = 200;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9450, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		// ���� ���ſ� ���� �߻�
		else if (nRet == REPLY_ERROR_)
		{
			if ((st_client[0].stComm[MES_BOAT_ID_MODIF_RIN_]).nResponse == CTL_ERROR)
			{
				m_nRetryCount++;	// ��õ� Ƚ�� ����
				if (m_nRetryCount > 5)
				{
					m_nRetryCount = 5;
				}
				m_nStep_MES = 200;	// ��� ��õ� �������� ����

				if (m_nRetryCount >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
					m_nStep_MES = 200;	// ��� ��õ� �������� ����
					
					// 900103 1 00 "Boat id does not response from server or Server  Error."
					alarm.mstr_code		= "900103";
					CTL_Lib.Alarm_Error_Occurrence(9154, CTL_dWARNING, alarm.mstr_code );
				}
			}
			else
			{
				m_lWaitResp[1] = GetCurrentTime();
				m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
				if (m_lWaitResp[2] < 0)
				{
					m_lWaitResp[0] = GetCurrentTime();
					break;
				}
				
				if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
				{
					m_nRetryCount++;	// ��õ� Ƚ�� ����
					if (m_nRetryCount > 5)
					{
						m_nRetryCount = 5;
					}
					m_nStep_MES = 200;	// ��� ��õ� �������� ����
					
					if (m_nRetryCount >= 5)
					{
						// ��ſ� ���� �߻� [������ �ذ� ��� ����]
						m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
						m_nStep_MES = 200;	// ��� ��õ� �������� ����
						
						// 900101 1 0 "MES_NOT_RESPONSE_ERR"
						alarm.mstr_code		= "900101";
						CTL_Lib.Alarm_Error_Occurrence(9155, CTL_dWARNING, alarm.mstr_code );
					}
				}
			}
		}
		else
		{
			m_lWaitResp[1] = GetCurrentTime();
			m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
			if (m_lWaitResp[2] < 0)
			{
				m_lWaitResp[0] = GetCurrentTime();
				break;
			}
			
			if (m_lWaitResp[2] > (MES_TIME_OUT+1000))
			{
				m_nRetryCount++;	// ��õ� Ƚ�� ����
				if (m_nRetryCount > 5)
				{
					m_nRetryCount = 5;
				}
				m_nStep_MES = 200;	// ��� ��õ� �������� ����
				
				if (m_nRetryCount >= 5)
				{
					// ��ſ� ���� �߻� [������ �ذ� ��� ����]
					m_nRetryCount = 0;	// [����] �۾� ��õ� Ƚ��
					m_nStep_MES = 200;	// ��� ��õ� �������� ����
					
					// 900101 1 0 "MES_NOT_RESPONSE_ERR"
					alarm.mstr_code		= "900101";
					CTL_Lib.Alarm_Error_Occurrence(9156, CTL_dWARNING, alarm.mstr_code );
				}
			}
		}
		break;

	case 300:
// 		m_nReq_MES	= WORK_NONE_;	// [����] Id ���� ���� �۾� ��û �÷���
		m_nStep_MES	= 0;
		nFuncRet = CTL_GOOD;
		break;
	}
	return nFuncRet;
}