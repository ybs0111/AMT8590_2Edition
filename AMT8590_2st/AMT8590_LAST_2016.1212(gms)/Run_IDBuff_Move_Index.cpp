// Run_IDBuff_Move_Index.cpp: implementation of the CRun_IDBuff_Move_Index class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "Run_IDBuff_Move_Index.h"

#include "Run_Smema_Ctl.h"
#include "Run_IDBuff_Input_Index.h"
#include "RunNetwork.h"
#include "Public_Function.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRun_IDBuff_Move_Index g_Run_IDBuff_Move_Index;

CRun_IDBuff_Move_Index::CRun_IDBuff_Move_Index()
{
	mn_InitStep = 0;
	mn_run_step = 0; 
	mn_density_step = 0;
	mn_pick_left_step = 0;
	mn_place_right_step = 0;
	mn_bcrIn_step = 0;
	mn_bcrOut_step = 0;
}

CRun_IDBuff_Move_Index::~CRun_IDBuff_Move_Index()
{

}

void CRun_IDBuff_Move_Index::Thread_Run()
{
// return;
//	int i=0,nRet_1=0;
//	double dCurPos = 0;
	int n_ret_1=0;

	//st_handler.n_without_idbuffer = CTL_YES;
// 	st_handler.n_without_smema_8580_mc = CTL_NO;
// 	st_handler.n_without_barcode_read = CTL_YES;
// 	st_handler.n_without_network = CTL_NO;
// 	st_handler.n_without_idbuffer = CTL_NO;
// 
// 	st_handler.n_without_density_label_rbt = CTL_YES;
// 	st_handler.n_without_bcr1_rbt = CTL_YES;
// 	st_handler.n_without_bcr2_rbt = CTL_YES;
// 	st_handler.n_without_top_vision_rbt = CTL_YES;
//	Run_Smema_Ctl.top_idbuffer_datainfo_shift(0, SHIFT_IDBUFF_SITE_ALL_CHK); //data shift & clear �̰��� 
		
	if( Func.OnIsInterruptCondition() != 1 )
		return;
	
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
		//2015.0222
		if(st_var.n_bcr_read_output_flag == CTL_YES)
		{
 			n_ret_1 = barcode_read_inout_process(CTL_RIGHT);
			if(n_ret_1 == CTL_GOOD)
			{
				st_var.n_bcr_read_output_flag = CTL_NO; //���ڵ� �б� �Ϸ� 
			}
		}
		Run_Move_Density();
		Run_Move();
		
		break;
		
	default: 
		
		break;
	}

}

void CRun_IDBuff_Move_Index::Run_Initial()
{
	int nRet_1 = 0, nRet_2 = 0,nRet_3 = 0,nRet_4 = 0,nRet_5 = 0,nRet_6 = 0,nRet_7 = 0,nRet_8 = 0;
	int i = 0, nFlag=0, nIodata_1=0, nIodata_2=0;
	
	if (st_handler.mn_init_state[INIT_TOP_IDBUFFER] != CTL_NO)		return;		// No �϶��� �ʱ�ȭ �۾��� �Ѵ�. �ʱ�ȭ�� ������ YES->READY�� �Ǳ� ������...
	
//	mn_InitStep = st_step.n_init[STEP_MOVE_INDEX]; 
//	Func.ThreadFunctionStepTrace(STEP_MOVE_INDEX + STEP_INIT, mn_InitStep);
	
	switch (mn_InitStep)
	{
	case 0:
 		mn_InitStep = 1000;
		break;

	case 1000: //��� fix clamp�� ��´� 
		mn_fixclamp_sol_flag[0] = 1; mn_fixclamp_sol_flag[1] = 1; mn_fixclamp_sol_flag[2] = 1; mn_fixclamp_sol_flag[3] = 1;//clear 
		//������ ���� ������ backward ����  		
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_ON);//clamp
		mn_InitStep = 1010; 
		break;
		
	case 1010: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_ON);//clamp
		if(nRet_1 == CTL_GOOD)
		{ 
			mn_InitStep = 2000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9001, COMI.mn_run_status, mc_jamcode);
			mn_InitStep = 1000;
		}
		break;  

	case 2000:
		g_Run_IDBuff_Input_Index.set_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //Ŭ������ �����ϰ� �̵� �غ� �Ѵ� 
		mn_InitStep = 2010;
		break;
		
	case 2010:
		nRet_1 = g_Run_IDBuff_Input_Index.get_idbuffer_input_clamp_onoff(0, 0, IO_OFF); //
		if(nRet_1 == CTL_GOOD) //Ŭ������ �����Ǿ��ִ��� Ȯ��
		{
			mn_InitStep = 2100;
		}
		else if(nRet_1 == CTL_ERROR) //����
		{
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9002, COMI.mn_run_status, g_Run_IDBuff_Input_Index.mc_jamcode);
			mn_InitStep = 2000;
		}
		break;

	case 2100:
		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);		 
		mn_InitStep = 2110; 
		break;
		
	case 2110:
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);
		if(nRet_1 == CTL_GOOD)
		{
			mn_InitStep = 3000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9003, COMI.mn_run_status, mc_jamcode);
			mn_InitStep = 2100;
		}
		break; 

	case 3000:
		nRet_1 = COMI.HomeCheck_Mot( M_TOPID_LD1, MOT_TIMEOUT);
		if( nRet_1 == BD_GOOD )
		{
			Func.OnInitBtn( RBTN_TOPID_LD_1 ); 
			mn_InitStep = 3100;
		}
		else if( nRet_1 == BD_ERROR )
		{//240001 0 00 "Top ID Buffr LD1 Axis Motor Home Check Error." //2016.0722
			sprintf(mc_jamcode, "240001");  
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(90040,  COMI.mn_run_status, mc_jamcode);
		}
		break;

	case 3100:
		nRet_1 = COMI.HomeCheck_Mot( M_TOPID_LD2, MOT_TIMEOUT);
		if( nRet_1 == BD_GOOD )
		{
			Func.OnInitBtn( RBTN_TOPID_LD_2 ); 
			mn_InitStep = 4000;
		}
		else if( nRet_1 == BD_ERROR )
		{///250001 0 00 "Top ID Buffr LD2 Axis Motor Home Check Error." //2016.0722
			sprintf(mc_jamcode, "250001");  
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9005,  COMI.mn_run_status, mc_jamcode);
		}
		break;

	case 4000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[0] , IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[1] , IO_ON); 
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[2] , IO_ON); 
		nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[3] , IO_ON); 
		nRet_5 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[4] , IO_ON); 
		nRet_6 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[5] , IO_ON); 
		nRet_7 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[6] , IO_ON); 
		nRet_8 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_exist_sensor_check[7] , IO_ON); 

		if(nRet_1 == IO_ON && nRet_2 == IO_ON) //2���� ������ 
		{
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_LEFT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_RIGHT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_LEFT] = 12; //�������� 
			st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[CTL_RIGHT] = 10;				

			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_product_id[CTL_LEFT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_product_id[CTL_RIGHT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_var[CTL_LEFT], "%s", "02");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_var[CTL_RIGHT], "%s", "02");
			
			
// 			ATray tray;
// 			tray.SetPos( IDPOS_DENSITY );
// 			for( int i=0; i<MAX_MODULE; i++ )
// 			{
// 				CString strProductID;	
// 				strProductID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_product_id[i]);
// 				
// 				CString strLotID;		
// 				strLotID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_product_id[i]);
// 				CString strSkip;		
// 				strSkip.Format("%d",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[i]);
// 				CString strArraySN;		
// 				strArraySN.Format("%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuff_num[i] );
// 				CString strSerial="";//		strSerial.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[i]);
// 				CString strVar;			strVar.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_var[i]);
// 				
// 				// ������a ��A
// 				AModule mdl;
// 				mdl.SetModuleInfo( strProductID, strLotID, strSkip, strArraySN, strSerial, strVar );
// 				tray.SetModule(i, mdl);
// 			}	
// 			tray.SetTargetPos( IDPOS_DENSITY );
// 			tray.SetWorkState( EWS_DENSITY );
// 			g_Tray.AddTray( tray );
		}
		else
		{//��� �ϳ��� ������ ������ �ִ� ���̴� ���� �߻����� 
			if(nRet_1 == IO_ON)
			{//2017.0214 alarm modify
				//523040 1 00 "Top_ID_Buffer1_Check_Off_Error."
				sprintf(mc_jamcode, "523040");//"527040");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9006,  COMI.mn_run_status, mc_jamcode);
				break;
			}
			else if(nRet_2 == IO_ON)
			{
				//523050 1 00 "Top_ID_Buffer2_Check_Off_Error."
				sprintf(mc_jamcode, "523050");//"527050");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9007,  COMI.mn_run_status, mc_jamcode);
				break;
			}
		}

		if(nRet_3 == IO_ON && nRet_4 == IO_ON) //2���� ������ 
		{
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_skip_flag[CTL_LEFT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_skip_flag[CTL_RIGHT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuff_num[CTL_LEFT] = 12; //�������� 
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuff_num[CTL_RIGHT] = 10;				
			
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_product_id[CTL_LEFT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_product_id[CTL_RIGHT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_var[CTL_LEFT], "%s", "02");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_var[CTL_RIGHT], "%s", "02");
			
// 			ATray tray;
// 			tray.SetPos( IDPOS_BARCODE1 );
// 			for( int i=0; i<MAX_MODULE; i++ )
// 			{
// 				CString strProductID;	strProductID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_product_id[i]);
// 				
// 				CString strLotID;		strLotID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_product_id[i]);
// 				CString strSkip;		strSkip.Format("%d",st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_skip_flag[i]);
// 				CString strArraySN;		strArraySN.Format("%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuff_num[i] );
// 				CString strSerial="";//		strSerial.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[i]);
// 				CString strVar;			strVar.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].c_var[i]);
// 				
// 				// ������a ��A
// 				AModule mdl;
// 				mdl.SetModuleInfo( strProductID, strLotID, strSkip, strArraySN, strSerial, strVar );
// 				tray.SetModule(i, mdl);
// 			}	
// 			tray.SetTargetPos( IDPOS_BARCODE1 );
// 			tray.SetWorkState( EWS_BARCODE1 );
// 			g_Tray.AddTray( tray );
		}
		else
		{//��� �ϳ��� ������ ������ �ִ� ���̴� ���� �߻����� 
			if(nRet_3 == IO_ON)
			{//523100 1 00 "Top_ID_Buffer3_Check_Off_Error."
				sprintf(mc_jamcode, "523100");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9008,  COMI.mn_run_status, mc_jamcode);
				break;
			}
			else if(nRet_4 == IO_ON)
			{//523110 1 00 "Top_ID_Buffer4_Check_Off_Error."
				sprintf(mc_jamcode, "523110");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(90090,  COMI.mn_run_status, mc_jamcode);
				break;
			}
		}

		if(nRet_5 == IO_ON && nRet_6 == IO_ON) //2���� ������ 
		{
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_skip_flag[CTL_LEFT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_skip_flag[CTL_RIGHT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuff_num[CTL_LEFT] = 12; //�������� 
			st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuff_num[CTL_RIGHT] = 10;				
			
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_product_id[CTL_LEFT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_product_id[CTL_RIGHT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_var[CTL_LEFT], "%s", "02");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_var[CTL_RIGHT], "%s", "02");
			
			
// 			ATray tray;
// 			tray.SetPos( IDPOS_BARCODE2 );
// 			for( int i=0; i<MAX_MODULE; i++ )
// 			{
// 				CString strProductID;	strProductID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_product_id[i]);
// 				
// 				CString strLotID;		strLotID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_product_id[i]);
// 				CString strSkip;		strSkip.Format("%d",st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_skip_flag[i]);
// 				CString strArraySN;		strArraySN.Format("%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuff_num[i] );
// 				CString strSerial="";//		strSerial.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[i]);
// 				CString strVar;			strVar.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].c_var[i]);
// 				
// 				// ������a ��A
// 				AModule mdl;
// 				mdl.SetModuleInfo( strProductID, strLotID, strSkip, strArraySN, strSerial, strVar );
// 				tray.SetModule(i, mdl);
// 			}	
// 			tray.SetTargetPos( IDPOS_BARCODE2 );
// 			tray.SetWorkState( EWS_BARCODE2 );
// 			g_Tray.AddTray( tray );
		
		}
		else
		{//��� �ϳ��� ������ ������ �ִ� ���̴� ���� �߻����� 
			if(nRet_5 == IO_ON)
			{//524021 1 00 "Top_ID_Buffer5_Check_On_Error."
				sprintf(mc_jamcode, "524021");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9010,  COMI.mn_run_status, mc_jamcode);
				break;
			}
			else if(nRet_6 == IO_ON)
			{//524031 1 00 "Top_ID_Buffer6_Check_On_Error."
				sprintf(mc_jamcode, "524031");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9011,  COMI.mn_run_status, mc_jamcode);
				break;
			}
		}

		if(nRet_7 == IO_ON && nRet_8 == IO_ON) //2���� ������ 
		{
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_skip_flag[CTL_LEFT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_skip_flag[CTL_RIGHT] = CTL_YES;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] = 1;
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuff_num[CTL_LEFT] = 12; //�������� 
			st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuff_num[CTL_RIGHT] = 10;				
			
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_product_id[CTL_LEFT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_product_id[CTL_RIGHT], "%s", "01");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_var[CTL_LEFT], "%s", "02");
			sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_var[CTL_RIGHT], "%s", "02");
			
			
// 			ATray tray;
// 			tray.SetPos( IDPOS_TOP_VISION );
// 			for( int i=0; i<MAX_MODULE; i++ )
// 			{
// 				CString strProductID;	strProductID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_product_id[i]);
// 				
// 				CString strLotID;		strLotID.Format("%s", st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_product_id[i]);
// 				CString strSkip;		strSkip.Format("%d",st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_skip_flag[i]);
// 				CString strArraySN;		strArraySN.Format("%02d", st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuff_num[i] );
// 				CString strSerial="";//		strSerial.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].c_serial[i]);
// 				CString strVar;			strVar.Format( "%s",st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].c_var[i]);
// 				
// 				// ������a ��A
// 				AModule mdl;
// 				mdl.SetModuleInfo( strProductID, strLotID, strSkip, strArraySN, strSerial, strVar );
// 				tray.SetModule(i, mdl);
// 			}	
// 			tray.SetTargetPos( IDPOS_TOP_VISION );
// 			tray.SetWorkState( EWS_TOPVISION );
// 			g_Tray.AddTray( tray );
		
		}
		else
		{//��� �ϳ��� ������ ������ �ִ� ���̴� ���� �߻����� 
			if(nRet_7 == IO_ON)
			{//524080 1 00 "Top_ID_Buffer7_Check_Off_Error."
				sprintf(mc_jamcode, "524080");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9012,  COMI.mn_run_status, mc_jamcode);
				break;
			}
			else if(nRet_8 == IO_ON)
			{//524090 1 00 "Top_ID_Buffer8_Check_Off_Error."
				sprintf(mc_jamcode, "524090");  
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9013,  COMI.mn_run_status, mc_jamcode);
				break;
			}
		}
		mn_InitStep = 5000;
		break;

	case 5000:
		mn_fixclamp_sol_flag[0] = 1; mn_fixclamp_sol_flag[1] = 1; mn_fixclamp_sol_flag[2] = 1; mn_fixclamp_sol_flag[3] = 1;//clear 
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == 1)
		{
			mn_fixclamp_sol_flag[0] = 0;
		}
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] == 1)
		{
			mn_fixclamp_sol_flag[1] = 0;
		}
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] == 1)
		{
			mn_fixclamp_sol_flag[2] = 0;
		}
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == 1 || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == 1)
		{
			mn_fixclamp_sol_flag[3] = 0;
		}

		//������ ���� ������ backward ����  		
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//clamp
		mn_InitStep = 5010; 
		break;
		
	case 5010: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//clamp
		if(nRet_1 == CTL_GOOD)
		{ 
			mn_InitStep = 6000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9014, COMI.mn_run_status, mc_jamcode);
			mn_InitStep = 5000;
		}
		break;  

	case 6000:
		nRet_1 = idbuffer_move_index_left_input_process(0);
		if(nRet_1 == CTL_GOOD)
		{
			mn_InitStep = 7000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9015, COMI.mn_run_status = dWARNING, mc_jamcode);
			mn_InitStep = 6000;
		}
		break;

	case 7000:
		Func.OnInitBtn( RBTN_TOPID_LD );//2014.1018
		st_handler.mn_init_state[INIT_TOP_IDBUFFER] = CTL_YES;
		mn_InitStep = 0;
		break;

	default:
		break;
	}
}

void CRun_IDBuff_Move_Index::Run_Move_Density()
{
	int i=0, nRet_1=0, nRet_2=0, nRet_3=0;
	CString str_msg;
	int nCnt=0;

 
 
	Func.ThreadFunctionStepTrace( 9, mn_density_step);
	switch(mn_density_step)
	{
	case 0:
		
		mn_density_step = 1000; 
		break;

////////////////////////////////////////////////////////////////////////////////////////////////
//index move �� �����ϱ� ���� ������ üũ�Ѵ� , �� 2���� ���� �������� ����ȴ�  
///////////////////////////////////////////////
//���� ��� ũ�� 3���� 
/////////////////////////////////////////////////
//1. ���۰� ó�� ���� input index ȿ���� ���� �̸� ��� ������ �Ҷ� : step 2000
//2. tbox �� �۾��� ���� ���۳�, skip ���۸� ������, sealing �۾��� ��û�� (left move & pick) : step 3000
//3. ���۸� ������(right move & place)                      
//	 - sealing�� �Ҷ�                                                 : step 6000
//   - output buffer�θ� �̵��Ҷ�									  : step 7000
//	 - sealing & ouput buffer �����Ҷ�								  : step 6000
/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

	case 1000: //���� üũ 		//i/o ���¿� program flag �� ���Ѵ� 
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_NO )
		{
			//2014.1201 if(st_var.n_event_inputindex_premove_right_start_flag == 1) break; //2014.1127 

			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
			if(nRet_1 == CTL_GOOD)
			{
				//mn_work_site_num = 0;
				mn_density_step = 2000; //DENSITY ����Ʈ�� ���۰� ����� �Ѵ� 
			} 
		}
//2014.1201 
// 		else if(st_sync.n_top_load1_work_req == CTL_READY) //2014.1126 //idbuffer index move�� input site�� ���۸� ��û�Ѵ� 
// 		{
// 			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
// 			if(nRet_1 == CTL_GOOD) //2014.1127
// 			{
// 				mn_density_step = 2200;
// 			}
// 		}
		else if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES)
		{ //�ּ��� 1�� �̻��� ����Ʈ���� ���۸� ������ �������� ���� �� �̵� �����ϴ� 
			
			//SHIFT_IDBUFF_INDEX_DENSITY �۾� ���� Ȯ�� 
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_RIGHT] == CTL_YES) //�۾����� �ʰ� ��ŵ�ϴ� �����϶� 
			{//
				 //st_sync.n_density_work_req = CTL_READY; //�۾��� �ʿ����, �۾� ��ŵ  
				if(st_sync.n_density_work_req == CTL_REQ)
				{
					 mn_density_step = 3000;
				}
			} 
			else if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES) //�۾��� ���簡 �ִ� 
			{
				nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
				if(nRet_1 == CTL_GOOD)
				{
					
					//�������
//					if ( g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete == CTL_YES && g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete == CTL_YES)
//					{
//						// ������ ����� �Ϸ� �Ǿ����� 
//						g_RunNetwork.st_barcodenet[CTL_LEFT].nComplete = CTL_NO;
//						g_RunNetwork.st_barcodenet[CTL_RIGHT].nComplete= CTL_NO;
//						
//						if( st_basic.nBcrFeederUse[0] == CTL_YES)
//						{
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_LEFT] = 0; // 1�� barcode label ���� ��ġ 
//							sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].c_Format, "%s", Func.m_pBctFmtClient[0]->GetBcrFormat() );
//
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nCommand = CTL_YES;
//						}
//						else
//						{
//							if( st_basic.nBcrFeederUse[2] == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_LEFT] = 2; // 3�� barcode label ���� ��ġ 
//								sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].c_Format, "%s",  Func.m_pBctFmtClient[0]->GetBcrFormat() );
//
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nCommand = CTL_YES;
//							}
//						}
//
//						if( st_basic.nBcrFeederUse[1] == CTL_YES)
//						{
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_RIGHT] = 1; // 2�� barcode label ���� ��ġ 
//							sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].c_Format, "%s",  Func.m_pBctFmtClient[1]->GetBcrFormat() );
//
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nCommand = CTL_YES;
//						}
//						else
//						{
//							if( st_basic.nBcrFeederUse[3] == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_RIGHT] = 3; // 4�� barcode label ���� ��ġ 
//								sprintf(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].c_Format, "%s",  Func.m_pBctFmtClient[1]->GetBcrFormat() );
//
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nCommand = CTL_YES;
//							}
//						}
//					}

					if(st_sync.n_density_work_req == CTL_REQ) //�۾� ��û  
					{

//						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_LEFT] == 0)
//						{
//							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete = CTL_NO;
//								nRet_1 = CTL_YES;
//							}
//						}
//						else
//						{
//							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete = CTL_NO;
//								nRet_1 = CTL_YES;
//							}
//						}
//						
//						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_RIGHT] == 1)
//						{
//							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete = CTL_NO;							
//								nRet_2 = CTL_YES;
//							}
//						}
//						else
//						{
//							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete == CTL_YES)
//							{
//								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete = CTL_NO;							
//								nRet_2 = CTL_YES;
//							}
//						}
//						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nCommand == CTL_NO &&
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nCommand == CTL_NO &&
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nCommand == CTL_NO &&
//							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nCommand == CTL_NO )
//						{
							mn_density_step = 3000; //�� ����Ʈ���� CTL_REQ�� �κ��� �۾��Ѵ� //buffer site�� ���°� ��� ���� �̾�� �Ѵ� 
//						}
					}
					
// 					if(st_handler.n_without_density_label_rbt == CTL_YES) //��c��eCIAo ��EA����C��I ����A�� 
// 					{
// 						st_sync.n_density_work_req = CTL_READY; //AU����CO CE��a����A��, AU���� ����A��
// 					}

// 					nRet_1 = CTL_NO;
// 					nRet_2 = CTL_NO;
// 					if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_LEFT] == 0)
// 					{
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete == CTL_YES)
// 						{
//  							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete = CTL_NO;
// 							nRet_1 = CTL_YES;
// 						}
// 					}
// 					else
// 					{
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete == CTL_YES)
// 						{
//  							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete = CTL_NO;
// 							nRet_1 = CTL_YES;
// 						}
// 					}
// 
// 					if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_RIGHT] == 1)
// 					{
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete == CTL_YES)
// 						{
//  							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete = CTL_NO;							
// 							nRet_2 = CTL_YES;
// 						}
// 					}
// 					else
// 					{
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete == CTL_YES)
// 						{
//  							st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete = CTL_NO;							
// 							nRet_2 = CTL_YES;
// 						}
// 					}

// 					if (nRet_1 == CTL_YES && nRet_2 == CTL_YES)
// 					{
// 						mn_density_step = 3000;
// 					}
// 					if (nRet_1 == CTL_YES && nRet_2 == CTL_YES)
// 					{
// 						mn_density_step = 3000;
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_LEFT] == 0)
// 						{
// 							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete == CTL_YES)
// 							{
// 								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[0].nComplete = CTL_NO;								
// 							}
// 						}
// 						else
// 						{
// 							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete == CTL_YES)
// 							{
// 								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[0].nComplete = CTL_NO;								
// 							}
// 						}
// 						
// 						if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].nBcrPos[CTL_RIGHT] == 1)
// 						{
// 							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete == CTL_YES)
// 							{
// 								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode1[1].nComplete = CTL_NO;
// 							}
// 						}
// 						else
// 						{
// 							if (st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete == CTL_YES)
// 							{
// 								st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].st_barcode2[1].nComplete = CTL_NO;								
// 							}
// 						}
// 					}
				}
				else
				{		
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(9020, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);			
				} 	
			} 
		}		
		break;

	///////////////////////////////////////////////////////////
	// input index���� ���۸� �޴´�  
	///////////////////////////////////////////////////////////
	case 2000:
		st_sync.n_top_load1_work_req = CTL_REQ;

		ml_until_wait[0] = GetCurrentTime();
		mn_density_step = 2100;
		break;

	case 2100:
		if(st_sync.n_top_load1_work_req == CTL_READY) //idbuffer index move�� input site�� ���۸� ��û�Ѵ� 
		{
			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
			if(nRet_1 == CTL_GOOD) //2014.1127
			{
				mn_density_step = 2200;
			}
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//�ε��� �ð��� ���̱� ���� �۾��� ���� ���۴� �̵� ��Ų�� 
		else if(st_sync.n_top_load1_work_req == CTL_REQ) //���� �۾��� ���۰� 8580 ��񿡼� �������� ���� ���·� �����ð� �Ⱑ�� �� ������ ���� ���� 
		{
			ml_until_wait[1] = GetCurrentTime();
			ml_until_wait[2] =  ml_until_wait[1] - ml_until_wait[0];
			if(ml_until_wait[2] > 5000) //2014.1111 //5�� �̻� �ε� ���۰� ���޵��� ������ ���� ���  ���� ���۸� ��ȯ�� �� ������ ��ȯ��Ų�� 
			{
				if(st_sync.n_bcr_1_work_req == CTL_REQ && st_sync.n_bcr_2_work_req == CTL_REQ && st_sync.n_topvision_work_req == CTL_REQ && st_sync.n_unload_elevator_req == CTL_REQ)
				{
					if( ((st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] == CTL_YES)
				 			||	(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] == CTL_YES )
				 			||	(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == CTL_YES) )
							&& (st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_NO && st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_NO) ) //unload elevator���� ���۰� ����� �Ѵ� 
					{
						st_sync.n_top_load1_work_req = CTL_FREE; //flag protect �ϱ� ���� ���� 
						mn_density_step = 2110;
					}
				}
			}
		}
		break;

	case 2110:
		st_sync.n_density_moveindex_shift_req = CTL_REQ;
		mn_density_step = 2120;
		break;
		
	case 2120:
		if(st_sync.n_density_moveindex_shift_req == CTL_READY) //index �� �������� �̵��Ͽ� data shift�� ���� �ش� ������ CTL_FREE�� �ٽ� ���ǿ� ���� �������� 
		{
			//2014,1127
// 			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
// 			if(nRet_1 == CTL_GOOD)
// 			{	
				st_sync.n_density_moveindex_shift_req = CTL_CLEAR;
				mn_density_step = 2130;
// 			}
// 			else
// 			{
// 				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
// 				CTL_Lib.Alarm_Error_Occurrence(9205, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
// 			}			
		}
		break;
		
	case 2130:
		if(st_sync.n_top_load1_work_req == CTL_FREE) //2014.1201 //index move ��� 
		{
			mn_density_step = 2000;
		}
		else
		{
			if(st_sync.n_top_load1_work_req ==  CTL_POSSIBLE || st_sync.n_top_load1_work_req == CTL_BUSY || st_sync.n_top_load1_work_req == CTL_READY)//2014.1201 input index ��� 
			{
				ml_until_wait[0] = GetCurrentTime();
				mn_density_step = 2100;
			}
			
		}
		
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////2014.1111
//////////////////////////////////////////////////////////////////////////////////////////////////////////2014.1111
 

		//���۰� 8590 ��� SHIFT_IDBUFF_INDEX_DENSITY ����Ʈ�� ������ ���� 
	case 2200:
		set_idbuff_fix_clamp1_2_onoff(0, IO_ON);
		mn_density_step = 2210;
		break;

	case 2210:
		nRet_1 = get_idbuff_fix_clamp1_2_onoff(0, IO_ON);
		if(nRet_1 == CTL_GOOD)
		{
			mn_density_step = 2300;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9021, COMI.mn_run_status, mc_jamcode);
			mn_density_step = 2200;
		}
		break; 

	case 2300:
		nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
		if(nRet_1 == CTL_GOOD)
		{
			mn_density_step = 2400; //DENSITY ����Ʈ�� ���۰� ����� �Ѵ� 
		}	
		else
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9022, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
		}
		break;

	case 2400:
		st_sync.n_inputindex_moveindex_clamp_exchange_req = CTL_REQ; //id buffer�� ���� ���Ҵٴ� �÷��� 
		st_sync.n_top_load1_work_req = CTL_CHANGE;
		mn_density_step = 2500;
		break;

	case 2500:
		if(st_sync.n_top_load1_work_req == CTL_SORT) //input index�� Ŭ������ Ǯ���� 
		{
			st_sync.n_top_load1_work_req = CTL_CLEAR;
			mn_density_step = 2600;
		}
		break;

	case 2600:
		mn_density_step = 1000;
		break;

///////////////////////////////////////////////////////////
// �۾� �ϷḦ ��ٸ��� 
///////////////////////////////////////////////////////////
	case 3000:
		nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
		if(nRet_1 == CTL_GOOD)
		{				 
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES) //top fold ��ġ 
			{
				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_skip_flag[CTL_RIGHT] == CTL_YES)
				{
					//�̶��� �Ǹ� �۾��� ���� �ʴ´� 
				}
				else
				{
					if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_LEFT]== CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_exist[CTL_RIGHT] == CTL_YES) //t box 
					{//t box�� ���� �Ҷ��� ���� 
						if(st_handler.n_without_density_label_rbt == CTL_NO) //CTL_YES�̸� ������� �����Ƿ� ��ŵ 
						{
							st_sync.n_density_work_req = CTL_READY;
						}
					}
				}
			}
			
			mn_density_step = 3100;
		}
		else
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9023, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
		}			
		break;

	case 3100:

		if(st_sync.n_density_work_req == CTL_REQ) //new work start req
		{//�۾��� �� ����,  ���ڵ� �κ�Ʈ���� ���ο� ���۸� ��û�� ���� 
			mn_density_step = 3200;
		}
		break;

	case 3200:
		if(st_sync.n_top_load1_work_req ==  CTL_READY)//2014.1201 input index ��� 
		{//input���� id���۰� ���� �̵����̸� ó�������� ��� .
			 mn_density_step = 2100;
			 break;
		} 

		st_sync.n_density_moveindex_shift_req = CTL_REQ; //���ؽ� �̵� ��û 
		mn_density_step = 3300;
		break;

	case 3300:
		if(st_sync.n_density_moveindex_shift_req == CTL_READY) //index �� �������� �̵��Ͽ� data shift�� ���� �ش� ������ CTL_FREE�� �ٽ� ���ǿ� ���� �������� 
		{
//2014.1431
// 			nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
// 			if(nRet_1 == CTL_GOOD || st_var.n_event_inputindex_premove_right_start_flag == 1)
// 			{	
 				st_sync.n_density_moveindex_shift_req = CTL_CLEAR;
 				mn_density_step = 4000; //2014.1201 1000;
// 			}
// 			else
// 			{
// 				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
// 				CTL_Lib.Alarm_Error_Occurrence(9024, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);
// 			}			
		}
		break;


	case 4000://2014.1201 
		if(st_sync.n_top_load1_work_req ==  CTL_POSSIBLE || st_sync.n_top_load1_work_req == CTL_BUSY || st_sync.n_top_load1_work_req == CTL_READY)//2014.1201 input index ��� 
		{
			ml_until_wait[0] = GetCurrentTime();
			mn_density_step = 2100;
		}
		else
		{
			mn_density_step = 1000;
		}
		break;


	default:
		break;

	}
}

void CRun_IDBuff_Move_Index::Run_Move()
{
	int i=0, nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0;
	CString str_msg;
	int nRunStep = 0, nCnt=0;

//	nRunStep = STEP_MOVE_INDEX;
 
	Func.ThreadFunctionStepTrace( 10, mn_run_step);
	switch(mn_run_step)
	{
	case 0:
		
		mn_run_step = 1000; 
		break;

////////////////////////////////////////////////////////////////////////////////////////////////
//index move �� �����ϱ� ���� ������ üũ�Ѵ� , �� 2���� ���� �������� ����ȴ�  
///////////////////////////////////////////////
//���� ��� ũ�� 3���� 
/////////////////////////////////////////////////
//1. ���۰� ó�� ���� input index ȿ���� ���� �̸� ��� ������ �Ҷ� : step 2000
//2. tbox �� �۾��� ���� ���۳�, skip ���۸� ������, sealing �۾��� ��û�� (left move & pick) : step 3000
//3. ���۸� ������(right move & place)                      
//	 - sealing�� �Ҷ�                                                 : step 6000
//   - output buffer�θ� �̵��Ҷ�									  : step 7000
//	 - sealing & ouput buffer �����Ҷ�								  : step 6000
/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

	case 1000: //���� üũ 		//i/o ���¿� program flag �� ���Ѵ� 
		
		if(st_sync.n_density_moveindex_shift_req == CTL_REQ) //buffer�� �ϳ��� �۾��� ����  ���� �����Ҷ� CTL_REQ�� �Ѵ� 
		{
			if(st_sync.n_bcr_1_work_req == CTL_REQ && st_sync.n_bcr_2_work_req == CTL_REQ && st_sync.n_topvision_work_req == CTL_REQ &&  st_sync.n_unload_elevator_req == CTL_REQ)
			{
				nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY);  
				nRet_2 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_SITE_ALL_CHK); 

				if(nRet_1 == CTL_GOOD && nRet_2 == CTL_GOOD)
				{
					st_sync.n_inputindex_moveindex_clamp_exchange_req = CTL_CLEAR;
					mn_run_step = 2000;
				}
				else
				{		
					alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
					CTL_Lib.Alarm_Error_Occurrence(90250, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);			
				} 
			}
			else if(st_sync.n_inputindex_moveindex_clamp_exchange_req == CTL_REQ) //2014.1201 add //move index�ˡ�| ��?iA�Ϩ�A�ˡ�����I AI��i��?EA A����������ICA�����ˢ� AaA�ˡ��ˡ�e, ��oA������I �ˡ�UAaA��i A����C����  gripper�ˡ�A �ϩ�o����i ��oI�ˡ���c left����I AI��i��?CI��?��I gripper�ˡ�| ��oI�ˡ���c Aa�ˡ�A�ˡ�U 
			{
				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES)
				{
					nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer1_chk, IO_ON); 
					nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer2_chk, IO_ON); 
					if(st_handler.n_without_idbuffer == CTL_YES)
					{
						nRet_1 = IO_ON; nRet_2 = IO_ON;
					}
					if(nRet_1 == IO_ON && nRet_2 == IO_ON)
					{
						st_sync.n_inputindex_moveindex_clamp_exchange_req = CTL_CLEAR;
						mn_run_step = 1100;
					}
				}
			}
		}
		else if(st_sync.n_inputindex_moveindex_clamp_exchange_req == CTL_REQ) //move index�� �������� �̵��� Ŭ������ ������, �ð� ������ ����  gripper�� ���� �̸� left�� �̵��Ͽ� gripper�� �̸� ��´� 
		{
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES)
			{
				nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer1_chk, IO_ON); 
				nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer2_chk, IO_ON); 
				if(st_handler.n_without_idbuffer == CTL_YES)
				{
					nRet_1 = IO_ON; nRet_2 = IO_ON;
				}
				if(nRet_1 == IO_ON && nRet_2 == IO_ON)
				{
					st_sync.n_inputindex_moveindex_clamp_exchange_req = CTL_CLEAR;
					mn_run_step = 1100;
				}
			}
		}
		break;

	case 1100:
		nRet_1 = idbuffer_move_index_left_input_process(0);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 1200;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(90260, COMI.mn_run_status = dWARNING, mc_jamcode);
			mn_run_step = 1100;
		}
		break; 

	case 1200:
		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);		 
		mn_run_step = 1210; 
		break;
		
	case 1210:
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 1300;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9027, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 1200;
		}
		break; 
		
	case 1300:
//2014.1201 
  		mn_run_step = 1000;
  		break;

		mn_fixclamp_sol_flag[0] = 1; mn_fixclamp_sol_flag[1] = 1; mn_fixclamp_sol_flag[2] = 1; mn_fixclamp_sol_flag[3] = 1;//clear 
		//������ ���� ������ backward ����  		
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp
		mn_run_step = 1310; 
		break;
		
	case 1310: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp
		if(nRet_1 == CTL_GOOD)
		{ 
			mn_run_step = 1400;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9028, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 1300;
		}
		break;  

	case 1400:
		mn_run_step = 1000;
		break;


	case 2000:
		nRet_1 = idbuffer_move_index_left_input_process(0);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 2100;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9029, COMI.mn_run_status = dWARNING, mc_jamcode);
			mn_run_step = 2000;
		}
		break; 

	case 2100: 
		nRet_1 = COMI.Check_MotPosRange(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK],  COMI.md_allow_value[M_TOPID_LD2]); //(int n_Axis, double d_Distance, int n_Range) 
		if (nRet_1 != BD_GOOD)
		{//080012 0 A "MOTOR ALLOW POSITION CHECK ERROR -[M_IDBUFFER_MOVE_INDEX]."
			sprintf(mc_jamcode, "%02d0012", M_TOPID_LD2); //left move pos�� �־�� �ϴµ� �ٸ� ��ġ�̸� ���� 
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9030,  COMI.mn_run_status, mc_jamcode);
			break;			 
		}
		
		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);		 
		mn_run_step = 2110; 
		break;
		
	case 2110:
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 2200;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9031, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 2100;
		}
		break; 

	case 2200:
		mn_fixclamp_sol_flag[0] = 1; mn_fixclamp_sol_flag[1] = 1; mn_fixclamp_sol_flag[2] = 1; mn_fixclamp_sol_flag[3] = 1;//clear 
		 //������ ���� ������ backward ����  		
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp
		mn_run_step = 2210; 
		break;
		
	case 2210: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp
		if(nRet_1 == CTL_GOOD)
		{ 
			mn_run_step = 3000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9032, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 2200;
		}
		break;  

	case 3000: 		
		nRet_1 = idbuffer_move_index_right_output_process(0);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 4000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9033, COMI.mn_run_status = dWARNING, mc_jamcode);
			mn_run_step = 3000;
		}
		break; 

/*
		if(1) //������ ���� ó�� //st_var.n_top_idbuffer_exist_status_check_info[28] == CTL_YES || st_var.n_top_idbuffer_exist_status_check_info[29] == CTL_YES) //index gripper 7,8���� ��� ������ 
		{//fix clamp�� ���� ������ �ȵ�, ���� �̵��� ���� ���ǿ��� �߰��Ǿ� ���� 
			
			nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON); 
			nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer34_unclamp_chk, IO_ON); 
			nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer56_unclamp_chk, IO_ON); 
			nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer78_unclamp_chk, IO_ON); 

			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES)
			{//600248 0 A "top t box check io sensor and program flag status check error[out buffer left] -[PS0514].
				sprintf(mc_jamcode, "600248"); 
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(0, COMI.mn_run_status, mc_jamcode);
				break;
			}
			else if(nRet_1 != IO_ON || nRet_2 != IO_ON || nRet_3 != IO_ON || nRet_4 != IO_ON) //fix clamp #3�� clamp ���� 
			{// 
				//526031 1 00 "Top ID Buffer1.2 UnClamp Cylinder On Error."
				//526041 1 00 "Top ID Buffer3.4 UnClamp Cylinder On Error."
				//526051 1 00 "Top ID Buffer5.6 UnClamp Cylinder On Error."
				//526061 1 00 "Top ID Buffer7.8 UnClamp Cylinder On Error."
				if(nRet_1 != IO_ON)			sprintf(mc_jamcode, "526031"); 
				else if(nRet_2 != IO_ON)	sprintf(mc_jamcode, "526041"); 
				else if(nRet_3 != IO_ON)	sprintf(mc_jamcode, "526051"); 
				else                        sprintf(mc_jamcode, "526061"); 
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(0, COMI.mn_run_status, mc_jamcode);			
				break;
			} 
		}		
			
		nRet_1 = COMI.Start_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD], COMI.mn_runspeed_rate);  // �ش� ��ġ�� �̵�
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{				
			mn_run_step = 3010; 
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_run_step = 3000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(0, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "090004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING;
			mn_run_step = 3000;
		}
		break;
		
	case 3010:
		nRet_1 = COMI.Check_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD]);  // �̵� �Ϸ� Ȯ��
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			mn_run_step = 4000;			
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_run_step = 3000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(0, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "090004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING;
			mn_run_step = 3000;
		}
		break;
*/
	case 4000: //�ð� ������ ����(input index �̵��� ����) ���� �����͸� �̼��Ѵ� 
		////////////////////////////////////////////////
		// ���� ���� �� ���� 
		////////////////////////////////////////////////
		
		//��� ��ġ�� ������ ��ȿ�ϸ� �ٷ� �� ����Ʈ�� ������ �������� ����Ʈ�Ѵ�(���� �ش� ������ ������ �����ϸ鼭 ���� update �Ѵ� 
		//////////////////////////////////////////////////////////
		// Move index �� ������ ��ġ�� �ڷḦ ����Ʈ �Ѵ� 
		//////////////////////////////////////////////////////////
		Run_Smema_Ctl.top_idbuffer_datainfo_shift(0, SHIFT_IDBUFF_SITE_ALL_CHK); //data shift & clear �̰��� 
		
		st_sync.n_density_moveindex_shift_req = CTL_READY; //�ˢ碮��uO�ˢ�Ii�ˢ�Ii Ca��E��cioA��E��ci A��E��c�ˢ��?C�ˢ碮�����ע�I �ˢ�E�ˢ�ϡ�OAu AI��E��c���סˢ碮E��cA�ˢ�E?�ˢ�E��Ec�ˢ碮��u��E��c����I �ˢ碮���ˢ�ϡ�?�ˢ碮��uo�ˢ�E�ˢ�ϡ�| �ˢ碮��uA�ˢ碮����E��cAC�ˢ碮�����ע�I A�ˢ碮�����ע�I�ˢ�E�ˢ�IU(�ˢ碮���ˢ�ϡ�ACO��E��c����ua Aa�ˢ碮���ˢ�ϡ�n�ˢ�E?�ˢ�E��Ec�ˢ碮��u��E��c����I ����Ioo�ˢ碮����E��cU�ˢ�E�ˢ�ϡ�| ��E��ci�ˢ�E��Ec�ˢ�E�ˢ�ϡ��ˢ�Ec ����Io�ˢ碮���ˢ硧I��E��c����ua A��E��c�ˢ��?C�ˢ碮�����ע�I �ˢ碮���ˢ�ϡ�?��E��c���סˢ碮��I��E��c 
		
		if(st_var.n_event_moveindex_premove_right_start_flag == 1)
		{
			st_var.n_event_moveindex_premove_right_start_flag = 0; //clear 2014.1121
// 			if(st_handler.cwnd_list != NULL)
// 			{
// 				sprintf(st_msg.c_normal_msg, "[event_move1] moveindex_premove_right_start_flag=%d.inputindex_premove_right_start_flag=%d, %d, %d, %d",
// 					st_var.n_event_moveindex_premove_right_start_flag, st_var.n_event_inputindex_premove_right_start_flag, mn_density_step, mn_pick_left_step, mn_place_right_step);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 				Func.On_LogFile_Add(99, st_msg.c_normal_msg);
// 			}
		}
		else
		{
// 			if(st_handler.cwnd_list != NULL)
// 			{
// 				sprintf(st_msg.c_normal_msg, "[event_move2] moveindex_premove_right_start_flag=0.inputindex_premove_right_start_flag=%d, %d, %d, %d",
// 					st_var.n_event_inputindex_premove_right_start_flag, mn_density_step, mn_pick_left_step, mn_place_right_step);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 				Func.On_LogFile_Add(99, st_msg.c_normal_msg);
// 			}
		}

		mn_run_step = 5000;
		break;

	case 5000:
		//2015.0227
		if(st_var.n_event_inputindex_premove_right_start_flag == 1 || st_sync.n_top_load1_work_req == CTL_BUSY) 
// 		if(st_var.n_event_moveindex_premove_right_start_flag == 1) 
		{
// 			if(st_handler.cwnd_list != NULL)
// 			{
// 				sprintf(st_msg.c_abnormal_msg, "[Move_Index_X1] n_top_load1_work_req=%d, n_event_inputindex_premove_right_start_flag=%d, n_event_moveindex_premove_right_start_flag=%d",	
// 					st_sync.n_top_load1_work_req, st_var.n_event_inputindex_premove_right_start_flag, st_var.n_event_moveindex_premove_right_start_flag);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 				Func.On_LogFile_Add(99, st_msg.c_abnormal_msg);
// 			}
			mn_run_step = 5100;
			break;
		}

		nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_INDEX_DENSITY); 
		if(nRet_1 == CTL_GOOD || st_var.n_event_inputindex_premove_right_start_flag == 1) //2014.1127
// 		if(nRet_1 == CTL_GOOD || st_var.n_event_moveindex_premove_right_start_flag == 1) //2014.1127
		{
// 			if(st_handler.cwnd_list != NULL)
// 			{
// 				sprintf(st_msg.c_abnormal_msg, "[Move_Index_X2] n_top_load1_work_req=%d, n_event_inputindex_premove_right_start_flag=%d, n_event_moveindex_premove_right_start_flag=%d",	
// 					st_sync.n_top_load1_work_req, st_var.n_event_inputindex_premove_right_start_flag, st_var.n_event_moveindex_premove_right_start_flag);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 				Func.On_LogFile_Add(99, st_msg.c_abnormal_msg);
// 			}
			mn_run_step = 5100; //plate & sealing & output buffer site�� ���°� ��� ���� �̾�� �Ѵ� 
		}
		else
		{		
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9034, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);	
			
			if(st_handler.cwnd_list != NULL)
			{
				sprintf(st_msg.c_abnormal_msg, "[Move_Index_X3] n_top_load1_work_req=%d, n_event_inputindex_premove_right_start_flag=%d, n_event_moveindex_premove_right_start_flag=%d",	
					st_sync.n_top_load1_work_req, st_var.n_event_inputindex_premove_right_start_flag, st_var.n_event_moveindex_premove_right_start_flag);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				Func.On_LogFile_Add(99, st_msg.c_abnormal_msg);
			}

		} 		
		break;
		
	case 5100:
		//2016.0807
// 		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] == CTL_YES) //top fold ��ġ 
// 		{
// 			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_skip_flag[CTL_RIGHT] == CTL_YES)
// 			{
// 				//�̶��� �Ǹ� �۾��� ���� �ʴ´� 
// 			}
// 			else
// 			{
// 				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_exist[CTL_LEFT]== CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_exist[CTL_RIGHT] == CTL_YES) //t box 
// 				{//t box�� ���� �Ҷ��� ���� 
// // 					if(st_handler.n_without_bcr1_rbt == CTL_NO) //Mirrir ��ŵ 
// // 					{
// 						st_sync.n_bcr_1_work_req = CTL_READY;
// // 					}					
// 				}
// 			}
// 		}
		
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] == CTL_YES) //top fold ��ġ 
		{
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_skip_flag[CTL_RIGHT] == CTL_YES)
			{
				//�̶��� �Ǹ� �۾��� ���� �ʴ´� 
			}
			else
			{
				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_exist[CTL_LEFT]== CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_exist[CTL_RIGHT] == CTL_YES) //t box 
				{//t box�� ���� �Ҷ��� ���� 
// 					if(st_handler.n_without_bcr2_rbt == CTL_NO) //Mirrir ��ŵ
// 					{
						st_sync.n_bcr_1_work_req = CTL_READY;//2016.0807
						st_sync.n_bcr_2_work_req = CTL_READY;
// 					}
				}
			}
		}
		
		
		
		
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == CTL_YES) //top fold ��ġ 
		{
			if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_skip_flag[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_skip_flag[CTL_RIGHT] == CTL_YES)
			{
				//�̶��� �Ǹ� �۾��� ���� �ʴ´� 
			}
			else
			{
				st_var.n_bcr_read_output_flag = CTL_NO;
				if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_exist[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_exist[CTL_RIGHT] == CTL_YES) //t box 
				{//t box�� ���� �Ҷ��� ���� 
					if(st_handler.n_without_top_vision_rbt == CTL_NO) //CTL_YES�̸� ������� �����Ƿ� ��ŵ 
					{
						st_sync.n_topvision_work_req = CTL_READY;
						//2015.0222
						if(st_basic.mn_rightbcr == CTL_YES) //���ڵ带 ����Ҷ��� �������� 
						{
							st_var.n_bcr_read_output_flag = CTL_YES;
						}
					}
					
				}
			}
		}
		
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES) //top insert ��ġ 
		{
			st_sync.n_unload_elevator_req = CTL_READY;
		}
		mn_run_step = 6000;
		break;

	case 6000://���� ��ġ�� ����üũ �� Ŭ���� ���� 
		mn_fixclamp_sol_flag[0] = 0; mn_fixclamp_sol_flag[1] = 0; mn_fixclamp_sol_flag[2] = 0; mn_fixclamp_sol_flag[3] = 0; 
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] == CTL_YES) //�⺻ ������ CV_DUAL mode �� �����Ѵ� 
		{//gripper #1,#2,#3
			mn_fixclamp_sol_flag[1] = 1; 
		}
		
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] == CTL_YES ) //�⺻ ������ CV_DUAL mode �� �����Ѵ� 
		{//gripper #4,#5,#6
			mn_fixclamp_sol_flag[2] = 1; 
		} 
		
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == CTL_YES) //�⺻ ������ CV_DUAL mode �� �����Ѵ� 
		{//gripper #7,#8
			mn_fixclamp_sol_flag[3] = 1; 
		}
		
		//clamp �� ��Ҵ� 
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_ON); //clamp 	 
		
		mn_run_step = 6010;
		break;
		
	case 6010:
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_ON); //clamp
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 6100;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(90350, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 6000;
		}
		break; 	

	case 6100:
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES) //top insert ��ġ 
		{
			if(st_sync.n_unload_elevator_req == CTL_FREE) //elevator gripper clamp ���� 
			{
				mn_run_step = 6200;
			}
		}
		else
		{
			mn_run_step = 6200;
		}
		break;

	case 6200:		
		nRet_1 = Run_Smema_Ctl.top_idbuffer_sensor_flag_status_check(0, SHIFT_IDBUFF_SITE_ALL_CHK); //bcr1~SHIFT_IDBUFF_INDEX_ULD
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 7000; //bcr1 ~ SHIFT_IDBUFF_INDEX_ULD buffer site�� ���°� ��� ���� �̾�� �Ѵ� 
		}
		else
		{		
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9036, COMI.mn_run_status, Run_Smema_Ctl.mc_jamcode);			
		} 	
		break;
		
	case 7000: //gripper�� ���Ҵ� 
		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);		 
		mn_run_step = 7010; 
		break;
		
	case 7010:
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);
		if(nRet_1 == CTL_GOOD)
		{
			mn_run_step = 7100;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9037, COMI.mn_run_status, mc_jamcode);
			mn_run_step = 7000;
		}
		break; 	

	case 7100:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_ON); 
		
		if(nRet_1 != IO_ON && nRet_2 != IO_ON) 
		{	//525051 1 00 "Top ID Buffer LD2 Shifter Left Hook UnClamp Cylinder On Error."
			//525071 1 00 "Top ID Buffer LD2 Shifter Right Hook UnClamp Cylinder On Error."
			if(nRet_1 != IO_ON) sprintf(mc_jamcode, "525051"); 
			else                sprintf(mc_jamcode, "525071");   
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9038, COMI.mn_run_status, mc_jamcode);
			break;
		}		
		
		//�̸� ���ʹ� �̵��ϰ� �Ѵ� 
		nRet_1 = COMI.Start_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK], COMI.mn_runspeed_rate * 1.5);  // �ش� ��ġ�� �̵�		
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{			
			mn_run_step = 7200;
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_run_step = 7100;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9039, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_run_step = 7100;
		}
		break;   

	case 7200:
		nRet_1 = COMI.Check_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK]);  // �̵� �Ϸ� Ȯ��
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			mn_run_step = 8000;			
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_run_step = 7100;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9040, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_run_step = 7100;
		}
		break;

	case 8000:
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES) //top insert ��ġ 
		{
			st_sync.n_unload_elevator_req = CTL_CHANGE;
		}
		

// 	 
// 		if((st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_DENSITY].n_idbuffer[CTL_RIGHT] == CTL_YES)
// 		||	(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR1].n_idbuffer[CTL_RIGHT] == CTL_YES)
// 		||	(st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_BCR2].n_idbuffer[CTL_RIGHT] == CTL_YES )
// 		||	(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == CTL_YES && st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == CTL_YES)
// 		if(	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || 
// 			st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES )
// 		{
// 			st_sync.n_unload_elevator_req = CTL_READY;
// 			mn_run_step = 1000;
// 		}	  
		mn_run_step = 1000;
 		break;

	case 9000: //2014.1201 
		if(st_sync.n_top_load1_work_req == CTL_REQ)
		{

		}

		break;


 
	default :
		break;
	}
}


int CRun_IDBuff_Move_Index::idbuffer_move_index_left_input_process(int n_site) 
{
	int nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0, nRet_5=0, nRet_6=0;
	CString str_msg;
	int nSubStep=0;
	int nFunRet=CTL_PROCEED;

//	nSubStep = sb_INDEX_MOVE_LEFT; 

	Func.ThreadFunctionStepTrace( 11, mn_pick_left_step);

	switch(mn_pick_left_step)
	{
	case 0: //������ ���� ���¸�
		nRet_1 = COMI.Check_MotPosRange(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK],  COMI.md_allow_value[M_TOPID_LD2]); //(int n_Axis, double d_Distance, int n_Range) 
		if (nRet_1 == BD_GOOD)
		{//080012 0 A "MOTOR ALLOW POSITION CHECK ERROR -[M_IDBUFFER_MOVE_INDEX]."
			nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_ON); 
			nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_clamp_chk, IO_ON); 
			if(nRet_1 == IO_ON && nRet_2 == IO_ON)
			{
				set_moveindex_gripper_length_onoff(0, 0, IO_ON); //����
				mn_pick_left_step = 4000;
				break;
			}			
			 
		}
		mn_pick_left_step = 1000;
		break;

	case 1000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_ON); 
		if(nRet_1 == IO_ON && nRet_2 == IO_ON)
		{
			mn_pick_left_step = 2000;
			break;
		}

		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);
		mn_pick_left_step = 1010; 
		break;
		
	case 1010: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);		
		
		if(nRet_1 == CTL_GOOD)
		{
			mn_pick_left_step = 2000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9041, COMI.mn_run_status, mc_jamcode);
			mn_pick_left_step = 1000;
		}
		break; 	

	case 2000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_ON); 
		
		if(nRet_1 != IO_ON && nRet_2 != IO_ON) 
		{	//525051 1 00 "Top ID Buffer LD2 Shifter Left Hook UnClamp Cylinder On Error."
			//525071 1 00 "Top ID Buffer LD2 Shifter Right Hook UnClamp Cylinder On Error."
			if(nRet_1 != IO_ON) sprintf(mc_jamcode, "525051"); 
			else                sprintf(mc_jamcode, "525071");   
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9042, COMI.mn_run_status, mc_jamcode);
			break;
		}	
		

		nRet_1 = COMI.Start_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK], COMI.mn_runspeed_rate * 1.5);  // �ش� ��ġ�� �̵�
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			set_moveindex_gripper_length_onoff(0, 0, IO_ON); //����
			
			mn_pick_left_step = 2100; 
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_pick_left_step = 2000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9043, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_pick_left_step = 2000;
		}
		break;

	case 2100:
		nRet_1 = COMI.Check_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK]);  // �̵� �Ϸ� Ȯ��
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			mn_pick_left_step = 3000;
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_pick_left_step = 2000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9044, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_pick_left_step = 2000;
		}
		break;

	case 3000:  
		nRet_1 = get_moveindex_gripper_length_onoff(0, 0, IO_ON);		
		if(nRet_1 == CTL_GOOD)
		{
			mn_pick_left_step = 4000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9045, COMI.mn_run_status, mc_jamcode);
			mn_pick_left_step = 3100;
		}
		break; 

	case 3100:
		set_moveindex_gripper_length_onoff(0, 0, IO_ON); //����
		mn_pick_left_step = 3000;
		break;

	case 4000:
		nFunRet = CTL_GOOD;
		mn_pick_left_step = 0;
		break;

	default :
		AfxMessageBox("idbuffer_move_index_left_input_process ==> Step error");
		break;
	}

	return nFunRet;
}

 
int CRun_IDBuff_Move_Index::idbuffer_move_index_right_output_process(int n_site) 
{
	int nRet_1=0, nRet_2=0, nRet_3=0, nRet_4=0, nRet_5=0, nRet_6=0;
	CString str_msg;
	int nSubStep=0;
	int nFunRet=CTL_PROCEED;
	long lMotionDone=0;//2014.1120 
	double dwCurrentPos =0;

//	nSubStep = sb_INDEX_MOVE_RIGHT; 
	Func.ThreadFunctionStepTrace( 12, mn_place_right_step);
	switch(mn_place_right_step)
	{
	case 0: //������ ���� ���¸� üũ�Ѵ� 		
		mn_place_right_step = 1000;
		break;

	case 1000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_clamp_chk, IO_ON); 
		if(nRet_1 == IO_ON && nRet_2 == IO_ON)
		{
			mn_place_right_step = 2000;
			break;
		}

		set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);		 
		mn_place_right_step = 1010; 
		break;

	case 1010:
		nRet_1 = get_moveindex_gripper_onoff(CTL_DUAL, 0, IO_ON);
		if(nRet_1 == CTL_GOOD)
		{
			mn_place_right_step = 2000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			set_moveindex_gripper_onoff(CTL_DUAL, 0, IO_OFF);

			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9046, COMI.mn_run_status, mc_jamcode);
			mn_place_right_step = 1000;
		}
		break; 

	case 2000:
		mn_fixclamp_sol_flag[0] = 1; mn_fixclamp_sol_flag[1] = 1; mn_fixclamp_sol_flag[2] = 1; mn_fixclamp_sol_flag[3] = 1;//clear 
		//������ ���� ������ backward ����  		
		set_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp

		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer34_unclamp_chk, IO_ON); 
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer56_unclamp_chk, IO_ON); 
		nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer78_unclamp_chk, IO_ON); 
		if(nRet_1 == IO_ON && nRet_2 == IO_ON && nRet_3 == IO_ON && nRet_4 == IO_ON) //�̹� open�Ǿ� ������ �ٷ� �������� 
		{
			set_moveindex_gripper_length_onoff(0, 0, IO_OFF);
			mn_place_right_step = 3000;
			break;
		}

		
		mn_place_right_step = 2010; 
		break;
		
	case 2010: //�̶� fix clamp�� id buffer�� üũ�ϴ� ������ �־�, unclamp ���¿����� ���۸� üũ�� �� ���� 
		nRet_1 = get_idbuff_fix_clamp_select_onoff(mn_fixclamp_sol_flag, IO_OFF);//unclamp
		//nRet_2 = get_moveindex_gripper_length_onoff(0, 0, IO_OFF);
		if(nRet_1 == CTL_GOOD)// && nRet_2 == CTL_GOOD)
		{ 
			set_moveindex_gripper_length_onoff(0, 0, IO_OFF);
			mn_place_right_step = 3000;
		}
		else if(nRet_1 == CTL_ERROR)// || nRet_2 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9047, COMI.mn_run_status, mc_jamcode);
			mn_place_right_step = 2000;
		}
		break;  

	case 3000:
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON); 
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer34_unclamp_chk, IO_ON); 
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer56_unclamp_chk, IO_ON); 
		nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer78_unclamp_chk, IO_ON); 
			
		if(nRet_1 != IO_ON || nRet_2 != IO_ON || nRet_3 != IO_ON || nRet_4 != IO_ON) //fix clamp #3�� clamp ���� 
		{// 
			//526031 1 00 "Top ID Buffer1.2 UnClamp Cylinder On Error."
			//526041 1 00 "Top ID Buffer3.4 UnClamp Cylinder On Error."
			//526051 1 00 "Top ID Buffer5.6 UnClamp Cylinder On Error."
			//526061 1 00 "Top ID Buffer7.8 UnClamp Cylinder On Error."
			if(nRet_1 != IO_ON)			sprintf(mc_jamcode, "526031"); 
			else if(nRet_2 != IO_ON)	sprintf(mc_jamcode, "526041"); 
			else if(nRet_3 != IO_ON)	sprintf(mc_jamcode, "526051"); 
			else                        sprintf(mc_jamcode, "526061"); 
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9048, COMI.mn_run_status, mc_jamcode);			
			break;
		} 

		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuffer[CTL_RIGHT] == CTL_YES) //unload elevator���� ���۰� ����� �Ѵ� 
		{//600248 0 A "unload id buffer check io sensor and program flag status check error.
			sprintf(mc_jamcode, "600248"); 
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9049, COMI.mn_run_status, mc_jamcode);
			break;
		}

		//unloader ���Ͱ� �۾� ������ ��ġ�� �ƴϸ� ���� �ϸ� �ȵ� 
		if(st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_LEFT] == CTL_YES || st_idbuff_info[SHIFT_IDBUFF_INDEX_TOP].n_idbuffer[CTL_RIGHT] == CTL_YES) //unload elevator�� �� ���۰���������
		{//�켱 ������ ���� ������ ���������� ���ʹ� �۾� ������ ��ġ�� �־�� �Ѵ� 
			nRet_1 = COMI.Check_MotPosRange(M_ULD_Z, st_motor[M_ULD_Z].d_pos[P_ULD_Z_UP],  COMI.md_allow_value[M_ULD_Z]); //(int n_Axis, double d_Distance, int n_Range) 
		//	double dpos = g_comiMgr.Get_MotCurrentPos(M_ULD_Z);
			nRet_2 = COMI.Check_MotPosRange(M_IDBUFFER_EL, st_motor[M_IDBUFFER_EL].d_pos[P_UPBUFFER],  COMI.md_allow_value[M_IDBUFFER_EL]); //(int n_Axis, double d_Distance, int n_Range) 

			if ( COMI.Get_MotCurrentPos(M_ULD_Z) > (st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_POS] + COMI.md_allow_value[M_ULD_Z]) &&
				COMI.Check_MotPosRange( M_ULD_Y, st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS], COMI.md_allow_value[M_ULD_Y] ) == BD_GOOD)
			{//080012 0 A "MOTOR ALLOW POSITION CHECK ERROR -[M_IDBUFFER_MOVE_INDEX]."
				sprintf(mc_jamcode, "%02d0008", M_ULD_Z); //left move pos�� �־�� �ϴµ� �ٸ� ��ġ�̸� ���� 
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9050,  COMI.mn_run_status, mc_jamcode);
				break;			 
			}
			if ( nRet_2 != BD_GOOD )
			{//080012 0 A "MOTOR ALLOW POSITION CHECK ERROR -[M_IDBUFFER_MOVE_INDEX]."
				sprintf(mc_jamcode, "%02d0008", M_IDBUFFER_EL); //left move pos�� �־�� �ϴµ� �ٸ� ��ġ�̸� ���� 
				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
				CTL_Lib.Alarm_Error_Occurrence(9051,  COMI.mn_run_status, mc_jamcode);
				break;			 
			}
			if( g_ioMgr.get_in_bit(st_io.i_idbuffer_elv_hook_clamp_chk) == IO_ON ||
				g_ioMgr.get_in_bit(st_io.i_idbuffer_elv_hook_unclamp_chk) == IO_OFF )
			{
				CString strError;
				strError.Format("5%04d%d",st_io.i_idbuffer_elv_hook_unclamp_chk, IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(9052, CTL_dWARNING, strError);
				break;
			}


		 
// 			nRet_1 = COMI.Check_MotPosRange(M_ULD_Y, st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS],  COMI.md_allow_value[M_ULD_Y]); //(int n_Axis, double d_Distance, int n_Range) 
// 			if (nRet_1 != BD_GOOD)
// 			{//080012 0 A "MOTOR ALLOW POSITION CHECK ERROR -[M_IDBUFFER_MOVE_INDEX]."
// 				sprintf(mc_jamcode, "%02d0012", P_ULD_Y_PICK_POS); //left move pos�� �־�� �ϴµ� �ٸ� ��ġ�̸� ���� 
// 				alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING;  COMI.mn_run_status = dWARNING;
// 				CTL_Lib.Alarm_Error_Occurrence(0,  COMI.mn_run_status, mc_jamcode);
// 				break;			 
// 			}  
		}
		
	

		
		nRet_1 = COMI.Start_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD], COMI.mn_runspeed_rate);  // �ش� ��ġ�� �̵�
		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			st_var.n_event_moveindex_premove_right_start_flag = 0; //clear 2014.1120 
			mn_place_right_step = 3100; 
		}
		else if (nRet_1 == BD_RETRY)
		{
			mn_place_right_step = 3000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9053, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_place_right_step = 3000;
		}
		break;
		
	case 3100:
		nRet_1 = COMI.Check_SingleMove(M_TOPID_LD2, st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD]);  // �̵� �Ϸ� Ȯ��
		if(nRet_1 == BD_PROCEED) //2014.1120 indx time ���� 
		{
			nRet_3 = g_comiMgr._cmmSxIsDone(M_TOPID_LD2, &lMotionDone); //index move�� �̵����̰� //��� ���� �Ϸ� == 1, �������� 0
			dwCurrentPos = g_comiMgr.Get_MotCurrentPos(M_TOPID_LD2);
			if(nRet_3 == cmERR_NONE &&  lMotionDone != cmTRUE) //���� ���� �̵����̰� 
			{
				if(dwCurrentPos > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + st_set.n_inputindex_premove_mm_value) //right ��ġ���� -5mm�̻� ������ ���� ������ �� �������� �ʾ����� ������ üũ�Ѵ� 
				{
					if(st_var.n_event_moveindex_premove_right_start_flag == 0) //index move�� �̵����϶��� �����̴� 
					{
						 st_var.n_event_moveindex_premove_right_start_flag = 1; //2014.1120 
					}
				}
			}
		}

		if (nRet_1 == BD_GOOD) //���͸� �δ� ��� ID BUFFER�� �ִ� ��ġ�� �̵��Ͽ� ���۸� ���� ���� ���� �´� 
		{	
			mn_place_right_step = 4000;
		}
		else if (nRet_1 == BD_RETRY)
		{
			st_var.n_event_moveindex_premove_right_start_flag = 2; //2014.1120 
			mn_place_right_step = 3000;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{//���� �˶��� �̹� ó�������� �̰������� �� ���¸� �ٲٸ� �ȴ� 
			st_var.n_event_moveindex_premove_right_start_flag = 3; //2014.1120 
			COMI.mn_run_status = dWARNING;  
			CTL_Lib.Alarm_Error_Occurrence(9054, COMI.mn_run_status, COMI.mc_alarmcode);//alarm.str_code = "250004"; alarm.n_count_mode = 0; alarm.n_type_mode = CTL_dWARNING; st_work.mn_run_status = CTL_dWARNING; //2016.0722
			mn_place_right_step = 3000;
		}
		break;


	case 4000:		
		nRet_1 = get_moveindex_gripper_length_onoff(0, 0, IO_OFF);
		if(nRet_1 == CTL_GOOD)
		{ 
			mn_place_right_step = 5000;
		}
		else if(nRet_1 == CTL_ERROR)
		{
			alarm.mstr_code = _T(mc_jamcode); alarm.mn_count_mode = 0; alarm.mn_type_mode = dWARNING; COMI.mn_run_status = dWARNING;
			CTL_Lib.Alarm_Error_Occurrence(9055, COMI.mn_run_status, mc_jamcode);
			mn_place_right_step = 4100;
		}
		break;  

	case 4100:
		set_moveindex_gripper_length_onoff(0, 0, IO_OFF);
		mn_place_right_step = 4000; 
		break;

	case 5000:
		nFunRet = CTL_GOOD;
		mn_place_right_step = 0;
		break;




	default :
		AfxMessageBox("idbuffer_move_index_right_output_process ==> Step error");
		break;
	}

	return nFunRet;
}


//gripper clamp  
int CRun_IDBuff_Move_Index::set_moveindex_gripper_onoff(int n_site, int n_ionum, int n_onoff)
{
	if(n_onoff == IO_OFF) //normal ���� normal backward
	{//unclamp
		if(n_site == CTL_LEFT)//left gripper�� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_clamp, IO_OFF); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_unclamp, IO_ON); 
		}
		else if(n_site == CTL_RIGHT)//left gripper�� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_clamp, IO_OFF); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_unclamp, IO_ON); 
		}
		else //if(n_site == CTL_DUAL)
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_clamp, IO_OFF); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_unclamp, IO_ON); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_clamp, IO_OFF); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_unclamp, IO_ON); 
		}	
	}
	else
	{//clamp 
		if(n_site == CTL_LEFT)//left gripper�� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_clamp, IO_ON); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_unclamp, IO_OFF); 
		}
		else if(n_site == CTL_RIGHT)//left gripper�� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_clamp, IO_ON); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_unclamp, IO_ON); 
		}
		else //if(n_site == CTL_DUAL)
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_clamp, IO_ON); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_left_hook_unclamp, IO_OFF); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_clamp, IO_ON); 
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_right_hook_unclamp, IO_OFF); 
		}
	}
	
	mb_index_grippe_flag[n_site] = true;
	ml_index_gripper_wait[n_site][0] = GetCurrentTime();
	return true;
}

//gripper clamp 
int CRun_IDBuff_Move_Index::get_moveindex_gripper_onoff(int n_site, int n_ionum, int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2, nRet_3, nRet_4; 
	
	//525100 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check Off Error."
	//525101 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check On Error."
	//525110 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check Off Error."
	//525111 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check On Error."
	
	ml_index_gripper_wait[n_site][1] = GetCurrentTime();
	ml_index_gripper_wait[n_site][2] = ml_index_gripper_wait[n_site][1] - ml_index_gripper_wait[n_site][0];
	
	if(n_onoff == IO_ON) //clamp 
	{// 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_OFF);
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_clamp_chk, IO_ON);
		nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_OFF);

		if(n_site == CTL_LEFT)//left gripper�� 
		{			 
			nRet_3 = IO_ON;
			nRet_4 = IO_OFF;
		}
		else if(n_site == CTL_RIGHT)
		{
			nRet_1 = IO_ON;
			nRet_2 = IO_OFF;
		}
		else //if(n_site == CTL_DUAL)
		{			 
		}
		
		if(mb_index_grippe_flag[n_site] == true && nRet_1 == IO_ON && nRet_2 == IO_OFF && nRet_3 == IO_ON && nRet_4 == IO_OFF) 
		{
			mb_index_grippe_flag[n_site] = false; 
			ml_index_gripper_wait[n_site][0] = GetCurrentTime();				
		}
		else if(mb_index_grippe_flag[n_site] == false && nRet_1 == IO_ON && nRet_2 == IO_OFF && nRet_3 == IO_ON && nRet_4 == IO_OFF) 
		{
			if(ml_index_gripper_wait[n_site][2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_index_gripper_wait[n_site][2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{
			//525121 1 00 "Top ID Buffer LD2 Shifter Left Hook Clamp Check On Error."
			//525141 1 00 "Top ID Buffer LD2 Shifter Right Hook Clamp Check On Error."
			if(n_site == CTL_LEFT) sprintf(mc_jamcode, "525121"); 
			else if(n_site == CTL_RIGHT) sprintf(mc_jamcode, "525141"); 
			else //if(n_site == CTL_DUAL)
			{
				if(nRet_1 != IO_ON || nRet_2 != IO_OFF) sprintf(mc_jamcode, "525121"); 
				else									sprintf(mc_jamcode, "525141"); 
			}
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_OFF)  //unclamp
	{ 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_OFF);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON);
		nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_clamp_chk, IO_OFF);
		nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_ON);
		if(n_site == CTL_LEFT)//left gripper�� 
		{			 
			nRet_3 = IO_OFF;
			nRet_4 = IO_ON;
		}
		else if(n_site == CTL_RIGHT)
		{
			nRet_1 = IO_OFF;
			nRet_2 = IO_ON;
		}
		else //if(n_site == CTL_DUAL)
		{			 
		}
		
		if(mb_index_grippe_flag[n_site] == true && nRet_1 == IO_OFF && nRet_2 == IO_ON && nRet_3 == IO_OFF && nRet_4 == IO_ON) 
		{
			mb_index_grippe_flag[n_site] = false; 
			ml_index_gripper_wait[n_site][0] = GetCurrentTime();				
		}
		else if(mb_index_grippe_flag[n_site] == false && nRet_1 == IO_OFF && nRet_2 == IO_ON && nRet_3 == IO_OFF && nRet_4 == IO_ON) 
		{
			if(ml_index_gripper_wait[n_site][2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_index_gripper_wait[n_site][2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{   //525120 1 00 "Top ID Buffer LD2 Shifter Left Hook Clamp Check Off Error."
			//525140 1 00 "Top ID Buffer LD2 Shifter Right Hook Clamp Check Off Error."
			if(n_site == CTL_LEFT) sprintf(mc_jamcode, "525120"); 
			else if(n_site == CTL_RIGHT) sprintf(mc_jamcode, "525140"); 
			else //if(n_site == CTL_DUAL)
			{
				if(nRet_1 != IO_ON || nRet_2 != IO_OFF) sprintf(mc_jamcode, "525120"); 
				else									sprintf(mc_jamcode, "525140"); 
			}
			nFunRet = CTL_ERROR;
		}
	}
	
	return nFunRet;
}


//length
int CRun_IDBuff_Move_Index::set_moveindex_gripper_length_onoff(int n_site, int n_ionum, int n_onoff)
{
	//normal close
	if(n_onoff == IO_OFF) //normal ���� normal backward, ���Ǹ� ���� 
	{//close
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_hook_fwd, IO_OFF); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_hook_bwd, IO_ON); 
	}
	else
	{//open 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_hook_fwd, IO_ON); 
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer_ld2_shifter_hook_bwd, IO_OFF); 
	}
	
	mb_idbuff_index_length_flag = true;
	ml_idbuff_index_length_wait[0] = GetCurrentTime();
	return true;
}


int CRun_IDBuff_Move_Index::get_moveindex_gripper_length_onoff(int n_site, int n_ionum, int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2; 
	
	//526000 1 00 "Top ID Buffer LD2 Shifter Hook Forward Cylinder Off Error."
	//526001 1 00 "Top ID Buffer LD2 Shifter Hook Forward Cylinder On Error."
	//526010 1 00 "Top ID Buffer LD2 Shifter Hook Backward Cylinder Off Error."
	//526011 1 00 "Top ID Buffer LD2 Shifter Hook Backward Cylinder On Error."

	
	ml_idbuff_index_length_wait[1] = GetCurrentTime();
	ml_idbuff_index_length_wait[2] = ml_idbuff_index_length_wait[1] - ml_idbuff_index_length_wait[0];
	
	if(n_onoff == IO_OFF) //normal close 
	{// 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_hook_fwd_chk, IO_OFF);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_hook_bwd_chk, IO_ON);
		
		if(mb_idbuff_index_length_flag == true && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			mb_idbuff_index_length_flag = false; 
			ml_idbuff_index_length_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_index_length_flag == false && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			if(ml_idbuff_index_length_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_index_length_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{//523011 1 00 "Top_ID_Buffer_LD2_Shifter_Hook_Backward_Check_On_Error."
			sprintf(mc_jamcode, "523011"); 
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_ON)  //open
	{ 		
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_hook_fwd_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_hook_bwd_chk, IO_OFF);
		
		if(mb_idbuff_index_length_flag == true && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			mb_idbuff_index_length_flag = false; 
			ml_idbuff_index_length_wait[0] = GetCurrentTime();				
		}
		else if(mb_idbuff_index_length_flag == false && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			if(ml_idbuff_index_length_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_idbuff_index_length_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{//523001 1 00 "Top_ID_Buffer_LD2_Shifter_Hook_Forward_Check_On_Error."
			sprintf(mc_jamcode, "523001"); 
			nFunRet = CTL_ERROR;
		}
		
	}
	
	return nFunRet;
}

int CRun_IDBuff_Move_Index::set_idbuff_fix_clamp1_2_onoff(int n_site, int n_onoff)
{
 
	if(n_onoff == IO_OFF) //normal ���� normal backward, unclamp ���� 
	{
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_clamp, IO_OFF);  
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_unclamp, IO_ON); 
	}
	else//clamp ���� 
	{
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_clamp, IO_ON);  
		g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_unclamp, IO_OFF); 
	}
 
	mb_fix_clamp1_2_flag = true;
	ml_fix_clamp1_2_wait[0] = GetCurrentTime();
	return true; 
}

int CRun_IDBuff_Move_Index::get_idbuff_fix_clamp1_2_onoff(int n_site, int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2; 
		
	ml_fix_clamp1_2_wait[1] = GetCurrentTime();
	ml_fix_clamp1_2_wait[2] = ml_fix_clamp1_2_wait[1] - ml_fix_clamp1_2_wait[0];
	
	if(n_onoff == IO_OFF) //normal open 
	{// 
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_clamp_chk, IO_OFF);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON);
		
		if(mb_fix_clamp1_2_flag == true && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			mb_fix_clamp1_2_flag = false; 
			ml_fix_clamp1_2_wait[0] = GetCurrentTime();				
		}
		else if(mb_fix_clamp1_2_flag == false && nRet_1 == IO_OFF && nRet_2 == IO_ON) 
		{
			if(ml_fix_clamp1_2_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_fix_clamp1_2_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{////526031 1 00 "Top ID Buffer1.2 UnClamp Cylinder On Error."
			sprintf(mc_jamcode, "526031"); 
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_ON)  //close
	{ 		
		nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_clamp_chk, IO_ON);
		nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_OFF);
		
		if(mb_fix_clamp1_2_flag == true && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			mb_fix_clamp1_2_flag = false; 
			ml_fix_clamp1_2_wait[0] = GetCurrentTime();				
		}
		else if(mb_fix_clamp1_2_flag == false && nRet_1 == IO_ON && nRet_2 == IO_OFF) 
		{
			if(ml_fix_clamp1_2_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_FWDBWD][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_fix_clamp1_2_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_FWDBWD])
		{////526021 1 00 "Top ID Buffer1.2 Clamp Cylinder On Error."
			sprintf(mc_jamcode, "526021"); 
			nFunRet = CTL_ERROR;
		}
		
	}
	
	return nFunRet; 
}


int CRun_IDBuff_Move_Index::set_idbuff_fix_clamp_select_onoff(int n_site[4], int n_onoff)
{
	if(n_site[0] == 1) //fix clamp #1 ���� 
	{
		if(n_onoff == IO_OFF) //normal ���� normal backward, unclamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_clamp, IO_OFF);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_unclamp, IO_ON); 
		}
		else//clamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_clamp, IO_ON);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer12_unclamp, IO_OFF); 
		}
	}
	if(n_site[1] == 1) //fix clamp #2 ���� 
	{
		if(n_onoff == IO_OFF) //normal ���� normal backward, unclamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer34_clamp, IO_OFF);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer34_unclamp, IO_ON); 
		}
		else//clamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer34_clamp, IO_ON);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer34_unclamp, IO_OFF); 
		}
	}
	if(n_site[2] == 1) //fix clamp #3 ���� 
	{
		if(n_onoff == IO_OFF) //normal ���� normal backward, unclamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer56_clamp, IO_OFF);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer56_unclamp, IO_ON); 
		}
		else//clamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer56_clamp, IO_ON);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer56_unclamp, IO_OFF); 
		}
	}

	if(n_site[3] == 1) //fix clamp #4 ���� 
	{
		if(n_onoff == IO_OFF) //normal ���� normal backward, unclamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer78_clamp, IO_OFF);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer78_unclamp, IO_ON); 
		}
		else//clamp ���� 
		{
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer78_clamp, IO_ON);  
			g_ioMgr.set_out_bit(st_io.o_top_idbuffer78_unclamp, IO_OFF); 
		}
	}
 
	mb_fix_clamp_select_flag = true;
	ml_fix_clamp_select_wait[0] = GetCurrentTime();
	return true;
}


int CRun_IDBuff_Move_Index::get_idbuff_fix_clamp_select_onoff(int n_site[4], int n_onoff)
{
	int nFunRet=CTL_PROCEED;
	int nRet_1, nRet_2=0, nRet_3=0, nRet_4=0; 

	
	ml_fix_clamp_select_wait[1] = GetCurrentTime();
	ml_fix_clamp_select_wait[2] = ml_fix_clamp_select_wait[1] - ml_fix_clamp_select_wait[0];
	
	if(n_onoff == IO_ON) //forward 
	{// 
		if(n_site[0] == 1 ) nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_clamp_chk, IO_ON); 
		else nRet_1 = IO_ON;

		if(n_site[1] == 1 ) nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer34_clamp_chk, IO_ON); 
		else nRet_2 = IO_ON;

		if(n_site[2] == 1 ) nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer56_clamp_chk, IO_ON);  
		else nRet_3 = IO_ON;

		if(n_site[3] == 1 ) nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer78_clamp_chk, IO_ON);  
		else nRet_4 = IO_ON;

		if(mb_fix_clamp_select_flag == true && nRet_1 == IO_ON && nRet_2 == IO_ON && nRet_3 == IO_ON && nRet_4 == IO_ON) 
		{
			mb_fix_clamp_select_flag = false; 
			ml_fix_clamp_select_wait[0] = GetCurrentTime();				
		}
		else if(mb_fix_clamp_select_flag == false && nRet_1 == IO_ON && nRet_2 == IO_ON && nRet_3 == IO_ON && nRet_4 == IO_ON) 
		{
			if(ml_fix_clamp_select_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][1])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_fix_clamp_select_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{   //523021 1 00 "Top ID Buffer1.2 Clamp Cylinder On Error."
			//523041 1 00 "Top ID Buffer3.4 Clamp Cylinder On Error."
			//523051 1 00 "Top ID Buffer5.6 Clamp Cylinder On Error."
			//523061 1 00 "Top ID Buffer7.8 Clamp Cylinder On Error."
			if(nRet_1 != IO_ON)			sprintf(mc_jamcode, "523021"); //2016.0721
			else if(nRet_2 != IO_ON)	sprintf(mc_jamcode, "523041"); 
			else if(nRet_3 != IO_ON)	sprintf(mc_jamcode, "523061"); 
			else                        sprintf(mc_jamcode, "523081"); 
			nFunRet = CTL_ERROR;
		}
	}
	else //if(n_onoff == IO_OFF)  //backward
	{ 
		if(n_site[0] == 1 ) nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer12_unclamp_chk, IO_ON); 
		else nRet_1 = IO_ON;

		if(n_site[1] == 1 ) nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer34_unclamp_chk, IO_ON); 
		else nRet_2 = IO_ON;

		if(n_site[2] == 1 ) nRet_3 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer56_unclamp_chk, IO_ON);  
		else nRet_3 = IO_ON; 

		if(n_site[3] == 1 ) nRet_4 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer78_unclamp_chk, IO_ON);  
		else nRet_4 = IO_ON; 

		if(mb_fix_clamp_select_flag == true && nRet_1 == IO_ON && nRet_2 == IO_ON && nRet_3 == IO_ON  && nRet_4 == IO_ON) 
		{
			mb_fix_clamp_select_flag = false; 
			ml_fix_clamp_select_wait[0] = GetCurrentTime();				
		}
		else if(mb_fix_clamp_select_flag == false && nRet_1 == IO_ON && nRet_2 == IO_ON && nRet_3 == IO_ON  && nRet_4 == IO_ON) 
		{
			if(ml_fix_clamp_select_wait[2] > st_time.n_wait_time[E_WAIT_HOOK_CLAMP][0])
			{
				nFunRet = CTL_GOOD;
			}
		}
		else if(ml_fix_clamp_select_wait[2] > st_time.n_limit_time[E_WAIT_HOOK_CLAMP])
		{   //523031 1 00 "Top ID Buffer1.2 UnClamp Cylinder On Error."
			//523041 1 00 "Top ID Buffer3.4 UnClamp Cylinder On Error."
			//523051 1 00 "Top ID Buffer5.6 UnClamp Cylinder On Error."
			//523061 1 00 "Top ID Buffer7.8 UnClamp Cylinder On Error."
			if(nRet_1 != IO_ON)			sprintf(mc_jamcode, "523031"); //2016.0721
			else if(nRet_2 != IO_ON)	sprintf(mc_jamcode, "523041"); 
			else if(nRet_3 != IO_ON)	sprintf(mc_jamcode, "523051"); 
			else                        sprintf(mc_jamcode, "523061"); 
			nFunRet = CTL_ERROR;
		}
	}

	return nFunRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CRun_IDBuff_Move_Index::barcode_read_inout_process(int n_site)
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
		//2016.0807
		//nCheckSite_Pos = CTL_RIGHT;
		nCheckSite_Pos = CTL_LEFT;
	}

	Func.ThreadFunctionStepTrace( 13, mn_bcrIn_step);

	switch(mn_bcrIn_step)
	{
	case 0: //������ ���� ���¸� üũ�Ѵ� 	
		if(st_basic.mn_rightbcr == CTL_YES) 
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
		if(st_basic.mn_rightbcr == CTL_YES) 
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