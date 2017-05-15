// CtlBd_Library.cpp: implementation of the CCtlBd_Library class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CtlBd_Library.h"


#include "io.h"			//2011.0514  ���� ���� ���� �˻� �Լ� ȣ���ϱ� ���ؼ��� �ݵ�� �ʿ�
#include "FAS_HSSI.h"
#include "ComizoaPublic.h"
#include "FastechPublic_IO.h"
#include "CtlBd_Function.h"
#include "SrcPart/APartHandler.h"
#include "IO_Manager.h"

#include "Srcbase\ALocalization.h"//20130930

//2015.0326 james 
#include "Cmmsdk.h"
#include "CmmsdkDef.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtlBd_Library::CCtlBd_Library()
{

}

CCtlBd_Library::~CCtlBd_Library()
{

}

CCtlBd_Library CTL_Lib;

//////////////////////////////////////////////////////////////////////////////
//version:0.1 (2011.1026) 
//�˶��߻� ó�����, ���� �� I/O ���� ���̺귯���� �ʱ�ȭ �� �����Ͽ� ��������ϴ� �Լ����� 
//
//���� �⺻�Լ� 
//1. #include "ComizoaPublic.h"
//2. #include "FastechPublic_IO.h"
///////////////////////////////////////////////////////////////////////////////

int CCtlBd_Library::Alarm_Error_Occurrence(int n_jampos, int n_run_status, char c_alarmcode[10])
{
	//�װ��� �˶��� �߻��ϸ� �� �����忡�� jamcode �� run status ������ �ٲ�� ��� �����ϰ� 
	//������ �ذ������� �����δ� �� �Լ��� �������� ����Ͽ� �˶����� �� ���� ���¸� ǥ���Լ� �ϳ��� 
	//����Ͽ� ��� ���� �� �˶� ������ ó���Ѵ� 
	//
	//�� �����忡 �����ִ� �˶� ó������� �� �Լ��� ��� ����Ѵ� 
   //
	//2013,0123
	if(COMI.mn_run_status == dINIT) alarm.stl_alarm_start_time = GetCurrentTime();
	CTL_Lib.mn_jampos = n_jampos; //jam�� �߻��� ��ġ�� �����Ѵ� 
	CTL_Lib.mn_run_status = n_run_status; //����� �������¸� �����Ѵ� 
	COMI.mn_run_status = n_run_status;
	alarm.mstr_code = c_alarmcode;
	alarm.stl_cur_alarm_time = GetCurrentTime();

	strcpy(mc_alarmcode, c_alarmcode);

//	g_handler.AddAlarmCnt();

//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor1, IO_OFF );
//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor2, IO_OFF );
//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor3, IO_OFF ); //2013,0916

	//2012,1220
	// 	CtlBdFunc.Alarm_Error_Occurrence(CTL_Lib.mn_jampos, COMI.mn_run_status, COMI.mn_run_status, alarm.mc_code);
	MyJamData.On_Alarm_Info_Set_to_Variable(alarm.mstr_code);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_abnormal_msg, "[%d] [%s] [%s]", CTL_Lib.mn_jampos, alarm.mstr_code, st_alarm.mstr_cur_msg);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		//2015.0514
		st_handler.m_strLogEvent = Func.Get_AlarmPartName(atoi(alarm.mstr_code));
	}
// 	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);
	return BD_GOOD;
}

int CCtlBd_Library::Alarm_Error_Occurrence( int n_jampos, int n_run_status, CString strJamCode )
{
	//2013,0123
	if(COMI.mn_run_status == dINIT) alarm.stl_alarm_start_time = GetCurrentTime();
	CTL_Lib.mn_jampos = n_jampos; //jam�� �߻��� ��ġ�� �����Ѵ� 
	CTL_Lib.mn_run_status = n_run_status; //����� �������¸� �����Ѵ� 
	COMI.mn_run_status = n_run_status;
	alarm.mstr_code = strJamCode;
	alarm.stl_cur_alarm_time = GetCurrentTime();

	strcpy(mc_alarmcode, (LPCSTR)strJamCode);

//	g_handler.AddAlarmCnt();

//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor1, IO_OFF );
//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor2, IO_OFF );
//	g_ioMgr.set_out_bit( st_io.o_bin_conveyor3, IO_OFF );

	//2012,1220
// 	CtlBdFunc.Alarm_Error_Occurrence(CTL_Lib.mn_jampos, COMI.mn_run_status, COMI.mn_run_status, alarm.mc_code);
	MyJamData.On_Alarm_Info_Set_to_Variable(alarm.mstr_code);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_abnormal_msg, "[%d] [%s] [%s]", CTL_Lib.mn_jampos, alarm.mstr_code, st_alarm.mstr_cur_msg);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		//2015.0514
		st_handler.m_strLogEvent = Func.Get_AlarmPartName(atoi(alarm.mstr_code));
	}

	
// 	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);
	return BD_GOOD;
}


int CCtlBd_Library::Initialize_motor_board(int n_bd_type, CString s_filename)	//motor ���� �ʱ�ȭ�� ���
{
	int nRet = 0, i=0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Motor Board Initialize 
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(n_bd_type == 0) //0:�Ľ��� ���带 ����ϴ� ����̸�, 1:Ŀ������ ���͸� ����ϴ� ��� 
	{		//���� ���庰 ����� �����Ѵ� 

		COMI.mn_totalmotboard_number = 3;  //���ͺ��尡 3�� �ִ� 
		COMI.mn_totalmotoraxis_number= 18; //������ �� ������ 18���̴�  
		COMI.mn_bd_axis_number[0] = 8;   //0�� ���ͺ���� 8��� �����̴�  
		COMI.mn_bd_axis_number[1] = 6;   //1�� ���ͺ���� 6��� �����̴� 
		COMI.mn_bd_axis_number[2] = 4;   //2�� ���ͺ���� 4��� �����̴� 
 	}
	else if(n_bd_type == 1) //1:Ŀ������ ���带 ����ϴ� ����̸�, 1:Ŀ������ ���͸� ����ϴ� ��� 
	{
		//1. ���� ���� �о���δ� 
		//2. ���� ���� ������ �����Ѵ� 
		nRet = COMI.Initialize_MotBoard(s_filename);			// MOTOR ���� �ʱ�ȭ ���� �˻��Ѵ�
		if (nRet == BD_ERROR)
		{
			sprintf(mc_normal_msg,"[MOTOR BOARD] �ʱ�ȭ ����.");
			LogFile_Write("D:\\AMTLOG\\Motor\\", mc_normal_msg);
			return BD_ERROR;
		}		

		COMI.mn_totalmotboard_number = 3;  //���ͺ��尡 3�� �ִ� 
		COMI.mn_totalmotoraxis_number= 18; //������ �� ������ 18���̴�  
		COMI.mn_bd_axis_number[0] = 8;   //0�� ���ͺ���� 8��� �����̴�  
		COMI.mn_bd_axis_number[1] = 6;   //1�� ���ͺ���� 6��� �����̴� 
		COMI.mn_bd_axis_number[2] = 4;   //2�� ���ͺ���� 4��� �����̴� 

// 		if(COMI.mn_motorbd_init_end == BD_YES)
// 		{			
// 			for(i=0; i<COMI.mn_totalmotoraxis_number; i++)
// 			{//n_simul_mode => 0:�ùķ��̼� ��� ��Ȱ��, 1:�ùķ��̼� ��� Ȱ��
// 
// 				if(COMI.mn_simulation_mode == 1) //���͸� �������� �����Ͽ� ���� ���� ����� ������ �ⱸ���� �̵��Ѱ�ó�� �����Ѵ� 
// 				{//Ȱ��
// 					COMI.Set_Simulation_Mode(i, 1); 
// 				}
// 				else
// 				{//��Ȱ�� 
// 					COMI.Set_Simulation_Mode(i, 0); 
// 				}
// 			}		
//		}
	}

	for( i = 0; i < 100; i++ )
		mn_single_motmove_step[i] = 0;

	return  BD_GOOD;
}

//�Ʒ� ������ I/O ���� �ʱ�ȭ�� �ʿ��� ������ ���� �������̴� 
//��� �ʿ��� ������ �����Ͽ� ����ϸ� �ȴ�.
int CCtlBd_Library::Initialize_io_Board(int n_bd_type)
{
	//if(n_bd_type == 0) //�Ľ��� HSSI I/O board 
	//{
	//}
	int i=0,j=0;
	INT HSSI_speed = 0;
	int Ret = 0;
	INT pMasterNo;
	

	/////////////////�ʱ⿡ �ʱ�ȭ�� //////////////////////////////////////////////////////////////////////
	Ret = FAS_IO.Set_IO_BoardOpen(&pMasterNo, START_NOTHING); //START_LOADDATA); //START_NOTHING); //START_CLEAR);
	
	if (Ret == FALSE)
	{
		return BD_ERROR;
	}

	return BD_GOOD;
}


int CCtlBd_Library::Motor_SafetyCheck(int n_mode, int n_axis, double d_targetpos) 	//���� ���� ���� ���ý� ��� 
{
	//���� �����Ͽ��� �����Ͽ� ��� �����Ѵ� 

	// ��) 
	// n_Mode = 0:Home Check, 1:Start, 2:Check, 3:Jog, 4:Length Change
	char cJamcode[10] = {NULL};
	int nRet = 0, nRet1 = 0, nRet2 = 0, nRet3 = 0;
	double d_CurPos[4] = {0,};
	double d_Pos[4] = {0,};
	double d_GapCheck = 0;
	int i = 0;
	CString strJamCode;

	nRet = Func.OnIsDoorOpen();
	if ( nRet != 0)//2015,0207
	{		
		strJamCode.Format("5370%d1",nRet);
		CTL_Lib.Alarm_Error_Occurrence( 991, dWARNING, strJamCode );
		sprintf(st_msg.c_abnormal_msg, "991,[DOOR CHECK] Door Open being done Run become.");
		if (st_handler.cwnd_list != NULL)  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		return BD_ERROR;
	}

//2011.0201 �ּ�ó�� 	int n_SetTime = 50; //091127 20->50���� ���� 100; //500ms ���� ��� ����Ǹ� �׶� ��μ� I/O ���� return 

	// **************************************************************************
	// ���� �˶� ���� �˻��Ѵ�                                                   
	// -> �˶� �߻��� ��� �˶� �����Ѵ�                                         
	// **************************************************************************
	//software limit �� ���� üũ ���� 
	if(d_targetpos < COMI.md_limit_position[n_axis][0] && st_handler.mn_virtual_mode == 0 ) //
	{
		sprintf(cJamcode, "%02d0004", n_axis);
		Alarm_Error_Occurrence(11, CTL_dWARNING, cJamcode);
		
		if (st_handler.cwnd_list != NULL)
		{  // ����Ʈ �� ȭ�� ����
			sprintf(st_msg.c_abnormal_msg, "Motor[%d] Software Limit Error_1[%4.3f] [%4.3f]", n_axis, COMI.md_limit_position[n_axis][0], d_targetpos);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
		}
		return BD_ERROR;
	}	
	if(d_targetpos > COMI.md_limit_position[n_axis][1] && st_handler.mn_virtual_mode == 0 ) //
	{
		sprintf(cJamcode, "%02d0004", n_axis);
		Alarm_Error_Occurrence(12, CTL_dWARNING, cJamcode);
		
		if (st_handler.cwnd_list != NULL)
		{  // ����Ʈ �� ȭ�� ����
			sprintf(st_msg.c_abnormal_msg, "Motor[%d] Software Limit Error_2[%4.3f] [%4.3f]", n_axis, COMI.md_limit_position[n_axis][1], d_targetpos);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
		}
		return BD_ERROR;
	}

	// **************************************************************************
	// ���� �Ŀ� ���� �˻��Ѵ�                                                   
	// -> ���� POWER OFF �� POWER ON ���·� �����                               
	// **************************************************************************
	if (g_comiMgr.Get_MotPower(n_axis) == CTL_ERROR )          // ���� POWER ���� �˻� �Լ� 
	{
		if (COMI.Set_MotPower(n_axis, CTL_ON) == CTLBD_RET_GOOD)       // ���� POWER ON ���� �Լ� 
		{
			if (st_handler.cwnd_list != NULL)
			{  // ����Ʈ �� ȭ�� ����
				sprintf(st_msg.c_normal_msg, "[MotorPowerOn_1] Axis=%d, rcnt=%d", n_axis, st_motor[n_axis].n_retry_cnt);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
			}

			if (COMI.Get_MotPower(n_axis) == CTL_ERROR)  // ���� POWER ���� �˻� �Լ� 
			{
				if (st_motor[n_axis].n_retry_cnt > (MOT_RTY_CNT))
				{
					sprintf(cJamcode, "%02d0005", n_axis);
					Alarm_Error_Occurrence(13, CTL_dWARNING, cJamcode);	
					return BD_ERROR;
				}
				else
				{
					COMI.mn_retry_cnt[n_axis]++ ;
					return BD_RETRY;
				}
			}
		}
		else
		{
			if (st_motor[n_axis].n_retry_cnt > MOT_RTY_CNT)
			{
				printf(cJamcode, "%02d0005", n_axis);
				Alarm_Error_Occurrence(14, CTL_dWARNING, cJamcode);		
				return BD_ERROR;
			}
			else
			{
				COMI.mn_retry_cnt[n_axis]++ ;
				return BD_RETRY;
			}
		}
	}

	//���� �˶� �߻��� ó�� ���� 
	if (COMI.Get_MotAlarmStatus(n_axis) == CTL_ERROR)      // ���� ALARM ���� �˻� �Լ� 
	{
		if (COMI.Set_MotAlarmClear(n_axis) == CTL_GOOD)       // ���� ALARM CLEAR �Լ� 
		{
			//091119 james			Sleep(1000);  // ���� �ð� �Ŀ� ���� Ȯ���ϱ� ���� SLEEP ����Ѵ� 
			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
			{
				sprintf(st_msg.c_normal_msg, "[Alarm Reset] Axis=%d, rcnt=%d", n_axis, COMI.mn_retry_cnt[n_axis]);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			if (COMI.Get_MotAlarmStatus(n_axis) == CTL_ERROR )  // ���� ALARM ���� �˻� �Լ� 
			{
				if (COMI.mn_retry_cnt[n_axis] > MOT_RTY_CNT)
				{			
					sprintf(cJamcode, "%02d0002",  n_axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;	
					sprintf(alarm.mc_code, "%02d0002", n_axis);
					CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Get Alarm Check Error", n_axis, COMI.mn_retry_cnt[n_axis]);				
					CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_axis, cJamcode, CtlBdFunc.ms_ErrMsg);
					//2011.0210 COMI.mn_retry_cnt[n_axis] = 0;  // �˶� ���� �õ� Ƚ�� 
					return CTL_ERROR;
				}
				else
				{
					COMI.mn_retry_cnt[n_axis]++ ;
					return CTL_RETRY;
				}
			}
		}
		else
		{
			if (COMI.mn_retry_cnt[n_axis] > MOT_RTY_CNT)
			{
				sprintf(cJamcode, "%02d0002",  n_axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;	
				sprintf(alarm.mc_code, "%02d0002", n_axis);
				CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Set Alarm Return Error", n_axis, COMI.mn_retry_cnt[n_axis]);				
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_axis, cJamcode, CtlBdFunc.ms_ErrMsg);
				
				//2011.0210 COMI.mn_retry_cnt[n_axis] = 0;  // �˶� ���� �õ� Ƚ�� 
				return CTL_ERROR;
			}
			else
			{
				COMI.mn_retry_cnt[n_axis]++ ;
				return CTL_RETRY;
			}
		}
	}
	// **************************************************************************

	// **************************************************************************
	// ������ ���� ��ġ�� üũ�Ѵ�. ��� �°� �ִ°� ����. ���ʿ� ������ ���� �ҷ��� ��� �ҵ�.                                           
	//***************************************************************************


 	switch( n_axis )
	{
	case M_BCR_FEEDER_1:
		if(d_targetpos < st_motor[M_BCR_FEEDER_1].d_pos[P_BCR_FEEDER_VISION])
		{
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > ( st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - 10*COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ) &&
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_X) > ( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1] + 170 ) ) )
			{
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(16, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(16, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
		}
		break;
	case M_BCR_FEEDER_2:
		if(d_targetpos < st_motor[M_BCR_FEEDER_2].d_pos[P_BCR_FEEDER_VISION])
		{
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > ( st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - 10*COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ) &&
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_X) > ( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK1] + 170 ) ) )
			{
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(16, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(16, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
		}
		break;

	case M_BCR_FEEDER_3:
		if(d_targetpos < st_motor[M_BCR_FEEDER_3].d_pos[P_BCR_FEEDER_VISION])
		{
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > ( st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - 10*COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ) &&
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_X) < ( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2] + 370 ) ) )
			{
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(17, CTL_dWARNING, "220008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(17, CTL_dWARNING, "220008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
		}
		break;

	case M_BCR_FEEDER_4:
		if(d_targetpos < st_motor[M_BCR_FEEDER_4].d_pos[P_BCR_FEEDER_VISION])
		{
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > ( st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - 10*COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ) &&
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_X) < ( st_motor[M_BCR_ATTACH1_X].d_pos[P_X_BCR_PICK2] + 370 ) ) )
			{
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(17, CTL_dWARNING, "220008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(17, CTL_dWARNING, "220008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(15, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
		}
		break;

	case M_D_VISION_X:
		break;
		
	case M_D_ATTACH_X:
	case M_D_ATTACH_Y:
		if( COMI.Get_MotCurrentPos(M_D_ATTACH_Z1) > st_motor[M_D_ATTACH_Z1].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z1] && st_handler.mn_virtual_mode == 0 )
		{//020008 0 00 "Density Attach Z1 Axis Motor is Non Safety Pos." //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence(19, CTL_dWARNING, "130008" ); 
			CTL_Lib.Alarm_Error_Occurrence(19, CTL_dWARNING, "020008" );
			return BD_ERROR;
		}
		if( COMI.Get_MotCurrentPos(M_D_ATTACH_Z2) > st_motor[M_D_ATTACH_Z2].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z2] && st_handler.mn_virtual_mode == 0 )
		{//030008 0 00 "Density Attach Z2 Axis Motor is Non Safety Pos." //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence(20, CTL_dWARNING, "140008" ); 
			CTL_Lib.Alarm_Error_Occurrence(20, CTL_dWARNING, "030008" ); 
			return BD_ERROR;
		}
		break;
		
	case M_D_ATTACH_Z1:
		break;
	case M_D_ATTACH_Z2:
		break;
	case M_BCR_VISION_X:
		break;
	case M_L_REJECT_X:

		if( g_ioMgr.get_in_bit( st_io.i_reject_rbt_up_chk, IO_ON) == IO_OFF || 
			g_ioMgr.get_in_bit( st_io.i_reject_rbt_down_chk, IO_OFF) == IO_ON)
		{
			CString strErr;
			strErr.Format("5%04d%d",st_io.i_reject_rbt_up_chk, IO_OFF);

			CTL_Lib.Alarm_Error_Occurrence(21, CTL_dWARNING, strErr);
			return BD_ERROR;

		}
		break;


	case M_BCR_ATTACH1_X:
	case M_BCR_ATTACH1_Y:
		if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] ||
			 COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
		{//100008 0 00 "Unload Robot Z Axis Motor is Non Safety Pos. //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence(22, CTL_dWARNING, "180008" );
			CTL_Lib.Alarm_Error_Occurrence(22, CTL_dWARNING, "100008" );
			return BD_ERROR;
		}

		if( g_ioMgr.get_out_bit(st_io.o_distribute_rbt_left_btm_vacuum_fwdback, IO_OFF) == IO_ON ||
			g_ioMgr.get_out_bit(st_io.o_distribute_rbt_right_btm_vacuum_fwdback, IO_OFF) == IO_ON ||
			g_ioMgr.get_in_bit(st_io.i_distribute_rbt_left_btm_vacuum_bwd_chk, IO_ON) == IO_OFF ||
			g_ioMgr.get_in_bit(st_io.i_distribute_rbt_right_btm_vacuum_bwd_chk, IO_ON) == IO_OFF )
		{
			CString strError;
			if( g_ioMgr.get_in_bit(st_io.i_distribute_rbt_left_btm_vacuum_bwd_chk, IO_ON) == IO_OFF)
			{
				strError.Format("5%04d%d",st_io.i_distribute_rbt_left_btm_vacuum_bwd_chk, IO_OFF);
				CTL_Lib.Alarm_Error_Occurrence(5022, CTL_dWARNING, strError );
			}
			else
			{
				strError.Format("5%04d%d",st_io.i_distribute_rbt_right_btm_vacuum_bwd_chk, IO_OFF);
				CTL_Lib.Alarm_Error_Occurrence(5023, CTL_dWARNING, strError );
			}
			return BD_ERROR;
		}
		break;

	case M_BCR_ATTACH1_Z1:
		{
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[0], IO_OFF);
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[0], IO_ON);
		
			//3:Jog
			if( n_mode != 3 && COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_REJECT] - 50 - COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1990, CTL_dWARNING, "180008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1990, CTL_dWARNING, "100008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1990, BCR_ATTACH1_Z1 Place Pos, ATTACH1_Z1 value is too low -> target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
			}
			if( n_mode != 3 && COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) >= st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_REJECT] + 50 +  COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1991, CTL_dWARNING, "180008" );  //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1991, CTL_dWARNING, "100008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1991, BCR_ATTACH1_Z1 Pick Pos, ATTACH1_Z1 value is too low->target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
			}//2016.0805
			if( n_mode != 3 && COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) >= st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_REJECT] + 50 +  COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1991, CTL_dWARNING, "180008" );  //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1991, CTL_dWARNING, "100008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1991, BCR_ATTACH1_Z1 Pick Pos, ATTACH1_Z1 value is too low->target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK1] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3800, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3801, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3802, CTL_dWARNING, strJamCode );
					return BD_ERROR;
				}
				else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3803, CTL_dWARNING, strJamCode );
					return BD_ERROR;					
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1603, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1603, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}//2016.0805
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK2] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3800, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3801, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3802, CTL_dWARNING, strJamCode );
					return BD_ERROR;
				}
				else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3803, CTL_dWARNING, strJamCode );
					return BD_ERROR;					
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1603, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1603, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN] )
			{
				if(nRet1 != IO_ON || nRet2 != IO_OFF) 
				{
					if(nRet1 != IO_ON)
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3804, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3805, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON) == IO_OFF ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					CString strErr;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
						strErr.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[0], IO_OFF);
					else
						strErr.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(23, CTL_dWARNING, strErr );
					return BD_ERROR;

				}

				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1604, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1604, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3806, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[0]);
						CTL_Lib.Alarm_Error_Occurrence( 3807, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[0], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3808, CTL_dWARNING, strJamCode );
					return BD_ERROR;					
				}
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(3809, CTL_dWARNING, "180008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(3809, CTL_dWARNING, "100008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "3809,BCR_ATTACH1_Z1 Error Pos, ATTACH1_Z1 value is too low -> target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1605, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1605, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( (n_mode != 3 && n_mode != 0 ) && (d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK1] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] ) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(3990, CTL_dWARNING, "180008" ); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(3990, CTL_dWARNING, "100008" );
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "3990, BCR_ATTACH1_Z1 Position error, ATTACH1_Z1 value is No Position -> target position: [%4.3f]", d_targetpos);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}
				return BD_ERROR;
			}
			if( (n_mode != 3 && n_mode != 0 ) && (d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_PICK2] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_DOWN] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_BCR_ERROR] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] ) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(3990, CTL_dWARNING, "180008" ); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(3990, CTL_dWARNING, "100008" );
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "3990, BCR_ATTACH1_Z1 Position error, ATTACH1_Z1 value is No Position -> target position: [%4.3f]", d_targetpos);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}
				return BD_ERROR;
			}
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				  COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				  COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				  COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) )
			{
				
			}
			else if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) )
			{
				
			}
			else
			{
				if( (n_mode != 3 && n_mode != 0 ) && ( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] ) )//2016.0721
				{
					//CTL_Lib.Alarm_Error_Occurrence(233, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(233, CTL_dWARNING, "090008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "233, BCR_ATTACH1_Z1, BCR_ATTACH1_Y  Position error -> position: [%4.3f]", COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y));
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;

				}
			}
		}
		break;

	case M_BCR_ATTACH1_Z2:
		{
			nRet1 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_fwd_chk[1], IO_OFF);
			nRet2 =  g_ioMgr.get_in_bit(st_io.i_distribute_rbt_box_rotator_bwd_chk[1], IO_ON);

			//3:Jog
			if( n_mode != 3 && COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - 50 - COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1992, CTL_dWARNING, "200008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1992, CTL_dWARNING, "110008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1992, BCR_ATTACH1_Z2 Place Pos, ATTACH1_Z2 value is too low ->target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
			}
			if( n_mode != 3 && COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) >= st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + 50 +  COMI.md_allow_value[M_BCR_ATTACH1_Y] )
			{
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1993, CTL_dWARNING, "200008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1993, CTL_dWARNING, "110008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1993, BCR_ATTACH1_Z2 Pick Pos, ATTACH1_Z2 value is too low ->target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
				//2016.0805
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(1993, CTL_dWARNING, "200008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1993, CTL_dWARNING, "110008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "1993, BCR_ATTACH1_Z2 Pick Pos, ATTACH1_Z2 value is too low ->target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
			}
			
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK1] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3810, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3811, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3812, CTL_dWARNING, strJamCode );
					return BD_ERROR;
				}
				else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3813, CTL_dWARNING, strJamCode );
					return BD_ERROR;
					
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1607, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1607, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK2] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3810, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3811, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3812, CTL_dWARNING, strJamCode );
					return BD_ERROR;
				}
				else if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3813, CTL_dWARNING, strJamCode );
					return BD_ERROR;
					
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1607, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1607, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN] )
			{
				if(nRet1 != IO_ON || nRet2 != IO_OFF) 
				{
					if(nRet1 != IO_ON)
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3814, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3815, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON) == IO_OFF ||
					g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					CString strErr;
					if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
						strErr.Format("5%04d%d", st_io.i_distribute_rbt_top_vacuum_bwd_chk[1], IO_OFF);
					else
						strErr.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(1608, CTL_dWARNING, strErr );
					return BD_ERROR;
					
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1609, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1609, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( d_targetpos == st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR] )
			{
				if(nRet1 != IO_OFF || nRet2 != IO_ON) 
				{
					if(nRet1 != IO_OFF)
					{
						strJamCode.Format("5%04d0",st_io.i_distribute_rbt_box_rotator_fwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3816, CTL_dWARNING, strJamCode );
					}
					else
					{
						strJamCode.Format("5%04d1",st_io.i_distribute_rbt_box_rotator_bwd_chk[1]);
						CTL_Lib.Alarm_Error_Occurrence( 3817, CTL_dWARNING, strJamCode );
					}
				}
				if( g_ioMgr.get_in_bit( st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_ON) == IO_OFF )
				{
					strJamCode.Format("5%04d%d", st_io.i_distribute_rbt_btm_vacuum_bwd_chk[1], IO_OFF);
					CTL_Lib.Alarm_Error_Occurrence(3818, CTL_dWARNING, strJamCode );
					return BD_ERROR;					
				}
				if( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence(3819, CTL_dWARNING, "200008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(3819, CTL_dWARNING, "110008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "3819, BCR_ATTACH1_Z2 Error Pos, ATTACH1_Z2 value is too low -> target position: [%4.3f]", d_targetpos);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}
				if( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
					COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] )
				{
					
				}
				else
				{
					//CTL_Lib.Alarm_Error_Occurrence(1610, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(1610, CTL_dWARNING, "090008" );
					return BD_ERROR;
				}
			}
			if( (n_mode != 3 && n_mode != 0 ) && (d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK1] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] ) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(3991, CTL_dWARNING, "200008" ); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(3991, CTL_dWARNING, "110008" );
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "3991, BCR_ATTACH1_Z2 Position error, ATTACH1_Z2 value is No Position -> target position: [%4.3f]", d_targetpos);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}
				return BD_ERROR;
			}//2016.0805
			if( (n_mode != 3 && n_mode != 0 ) && (d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_PICK2] &&
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_DOWN] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_ERROR] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] && 
				d_targetpos != st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_UP] ) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(3991, CTL_dWARNING, "200008" ); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(3992, CTL_dWARNING, "110008" );
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "3991, BCR_ATTACH1_Z2 Position error, ATTACH1_Z2 value is No Position -> target position: [%4.3f]", d_targetpos);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}
				return BD_ERROR;
			}
			if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK1] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) )
			{
				
			}
			else if( ( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PICK2] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_REJECT] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) ||
				( COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) > st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] - COMI.md_allow_value[M_BCR_ATTACH1_Y] &&
				COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) )
			{
				
			}
			else
			{
				if( (n_mode != 3 && n_mode != 0 ) && ( d_targetpos > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_BCR_SAFETY] ) )//2016.0721
				{
					//CTL_Lib.Alarm_Error_Occurrence(243, CTL_dWARNING, "170008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(243, CTL_dWARNING, "110008" );
					if (st_handler.cwnd_list != NULL)
					{
						sprintf(st_msg.c_abnormal_msg, "243, BCR_ATTACH1_Z2, BCR_ATTACH1_Y  Position error -> position: [%4.3f]", COMI.Get_MotCurrentPos(M_BCR_ATTACH1_Y));
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					}
					return BD_ERROR;
				}

			}
		}
		break;

	case M_TOP_VISION_X:
		break;

	case M_BTM_VISION_X:
		if( COMI.Get_MotCurrentPos(M_ULD_Z) > st_motor[M_ULD_Z].d_pos[P_ULD_Z_VIS_POS] + COMI.md_allow_value[M_ULD_Z] && st_handler.mn_virtual_mode == 0 )
		{//180008 0 00 "Unload Robot Z Axis Motor is Non Safety Pos. //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence(28, CTL_dWARNING, "300008" );
			CTL_Lib.Alarm_Error_Occurrence(28, CTL_dWARNING, "180008" );
			return BD_ERROR;
		}		
		break;

	case M_ULD_Y:
		if( COMI.Get_MotCurrentPos(M_ULD_Z) > st_motor[M_ULD_Z].d_pos[P_ULD_Z_UP] + COMI.md_allow_value[M_ULD_Z] && st_handler.mn_virtual_mode == 0 )
		{//180008 0 00 "Unload Robot Z Axis Motor is Non Safety Pos. //2016.0722
			//CTL_Lib.Alarm_Error_Occurrence(29, CTL_dWARNING, "300008" );
			CTL_Lib.Alarm_Error_Occurrence(29, CTL_dWARNING, "180008" );
			return BD_ERROR;
		}
		if( (g_ioMgr.get_in_bit( st_io.i_uld_rbt_left_up_chk, IO_ON) == IO_OFF || g_ioMgr.get_in_bit( st_io.i_uld_rbt_left_down_chk, IO_OFF) == IO_ON) && st_handler.mn_virtual_mode == 0 )
		{
			sprintf(cJamcode, "5%04d%d", st_io.i_uld_rbt_left_up_chk, IO_OFF);
			Alarm_Error_Occurrence(30, CTL_dWARNING, cJamcode);
			return BD_ERROR;
		}
		if( (g_ioMgr.get_in_bit( st_io.i_uld_rbt_right_up_chk, IO_ON) == IO_OFF || g_ioMgr.get_in_bit( st_io.i_uld_rbt_right_down_chk, IO_OFF) == IO_ON) && st_handler.mn_virtual_mode == 0 )
		{
			sprintf(cJamcode, "5%04d%d", st_io.i_uld_rbt_right_up_chk, IO_OFF);
			Alarm_Error_Occurrence(31, CTL_dWARNING, cJamcode);
			return BD_ERROR;
		}
		break;

	case M_ULD_Z:
		if( d_targetpos == st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_POS] ||
			d_targetpos == st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_READY_POS] )
		{
			if( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS] - COMI.md_allow_value[M_ULD_Y] &&
				COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS] + COMI.md_allow_value[M_ULD_Y] )
			{

			}
			else
			{
				if( (n_mode != 3 && n_mode != 0 ) )
				{
					//CTL_Lib.Alarm_Error_Occurrence(29, CTL_dWARNING, "300008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(29, CTL_dWARNING, "180008" );
					return BD_ERROR;
				}
			}
		}
		if( d_targetpos == st_motor[M_ULD_Z].d_pos[P_ULD_Z_CONV_POS] )
		{
			if( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_CONV_POS] - COMI.md_allow_value[M_ULD_Y] &&
				COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_CONV_POS] + COMI.md_allow_value[M_ULD_Y] )
			{
				
			}
			else
			{
				if( (n_mode != 3 && n_mode != 0 ) )
				{
					//CTL_Lib.Alarm_Error_Occurrence(2929, CTL_dWARNING, "300008" ); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(2929, CTL_dWARNING, "180008" );
					return BD_ERROR;
				}
			}
		}
		if( d_targetpos == st_motor[M_ULD_Z].d_pos[P_ULD_Z_REJ_POS] )
		{
			if( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_REJ_POS] - COMI.md_allow_value[M_ULD_Y] &&
				COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_REJ_POS] + COMI.md_allow_value[M_ULD_Y] )
			{
				
			}
			else
			{
				if( (n_mode != 3 && n_mode != 0 ) )
				{
					//CTL_Lib.Alarm_Error_Occurrence(2930, CTL_dWARNING, "300008" );
					CTL_Lib.Alarm_Error_Occurrence(2930, CTL_dWARNING, "180008" );
					return BD_ERROR;
				}
			}
		}
		if( (n_mode != 3 && n_mode != 0 ) && (d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_SAFETY] &&
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_UP] && 
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_POS] &&
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_VIS_POS] &&
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_CONV_POS] &&
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_REJ_POS] &&
			d_targetpos != st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_READY_POS] ) )
		{
			CTL_Lib.Alarm_Error_Occurrence(3999, CTL_dWARNING, "180008" ); //2016.0722
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_msg.c_abnormal_msg, "3999, M_ULD_Y Position error -> target position: [%4.3f]", d_targetpos);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
			}
			return BD_ERROR;
		}

		if( ( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS] - COMI.md_allow_value[M_ULD_Y] &&
			  COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS] + COMI.md_allow_value[M_ULD_Y] ) ||
			( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_VIS_POS] - COMI.md_allow_value[M_ULD_Y] &&
			  COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_VIS_POS] + COMI.md_allow_value[M_ULD_Y] ) ||
			( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_CONV_POS] - COMI.md_allow_value[M_ULD_Y] &&
			  COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_CONV_POS] + COMI.md_allow_value[M_ULD_Y] ) ||
			( COMI.Get_MotCurrentPos(M_ULD_Y) > st_motor[M_ULD_Y].d_pos[P_ULD_Y_REJ_POS] - COMI.md_allow_value[M_ULD_Y] &&
			  COMI.Get_MotCurrentPos(M_ULD_Y) < st_motor[M_ULD_Y].d_pos[P_ULD_Y_REJ_POS] + COMI.md_allow_value[M_ULD_Y] ) )
		{
			
		}
		else
		{
			if( d_targetpos > ( st_motor[M_ULD_Z].d_pos[P_ULD_Z_SAFETY] + COMI.md_allow_value[M_ULD_Z] ) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(2939, CTL_dWARNING, "300008" ); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(2939, CTL_dWARNING, "180008" );
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "2939, M_ULD_Y  Position error -> position: [%4.3f]", COMI.Get_MotCurrentPos(M_ULD_Y));
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}
				return BD_ERROR;
			}
		}
		break;

	case M_ULD_CV_PITCH:
		break;
	case M_IDBUFFER_EL:

		if( g_ioMgr.get_in_bit( st_io.i_idbuffer_elv_pusher_fwd_chk, IO_OFF) == IO_ON ||
			g_ioMgr.get_in_bit( st_io.i_idbuffer_elv_pusher_bwd_chk, IO_ON) == IO_OFF)
		{
			CString strError;
			if( g_ioMgr.get_in_bit( st_io.i_idbuffer_elv_pusher_fwd_chk, IO_OFF) == IO_ON)
				strError.Format("5%04d%d",st_io.i_idbuffer_elv_pusher_fwd_chk, IO_ON);
			else
				strError.Format("5%04d%d",st_io.i_idbuffer_elv_pusher_bwd_chk, IO_OFF);

			CTL_Lib.Alarm_Error_Occurrence( 89, dWARNING, strError );
			COMI.Set_MotStop( true, M_IDBUFFER_EL);
			return BD_ERROR;
		}

		if( COMI.Get_MotCurrentPos(M_TOPID_LD2) > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_SAFETY] + COMI.md_allow_value[M_TOPID_LD2] && st_handler.mn_virtual_mode == 0 )
		{//250008 0 00 "Top ID Buffr LD2 Axis Motor is Non Safety Pos." //2016.0722
			if( d_targetpos > st_motor[M_IDBUFFER_EL].d_pos[P_UPBUFFER] + COMI.md_allow_value[M_IDBUFFER_EL] ||
				(COMI.Get_MotCurrentPos(M_IDBUFFER_EL) > st_motor[M_IDBUFFER_EL].d_pos[P_UPBUFFER] + COMI.md_allow_value[M_IDBUFFER_EL]) )
			{
				//CTL_Lib.Alarm_Error_Occurrence(25, CTL_dWARNING, "340008"); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(25, CTL_dWARNING, "250008");
				COMI.Set_MotStop( 30, M_IDBUFFER_EL);
				return BD_ERROR;
			}

		}
		if( COMI.Get_MotCurrentPos(M_BTMID_ULD2) > st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_SAFETY] + COMI.md_allow_value[M_BTMID_ULD1] && st_handler.mn_virtual_mode == 0 )
		{//340008 0 00 "Bottom ID Buffr ULD4 Axis Motor is Non Safety Pos."
//			st_io.i_btm_idbuffer_uld1_shifter_hook_fwd_chk						= 3306;
//			st_io.i_btm_idbuffer_uld1_shifter_hook_back_chk						= 3307;

			if( g_ioMgr.get_in_bit(st_io.i_btm_idbuffer_uld1_shifter_hook_fwd_chk, IO_OFF) == IO_ON ||
				g_ioMgr.get_in_bit(st_io.i_btm_idbuffer_uld1_shifter_hook_back_chk, IO_ON) == IO_OFF)
			{
				CString strError;
				strError.Format("5%04d%%d",st_io.i_btm_idbuffer_uld1_shifter_hook_fwd_chk, IO_ON);
				CTL_Lib.Alarm_Error_Occurrence(25, CTL_dWARNING, strError);
				COMI.Set_MotStop( 31, M_IDBUFFER_EL);
				return BD_ERROR;
			}
//			CTL_Lib.Alarm_Error_Occurrence(26, CTL_dWARNING, "340008");
		}
		if(COMI.Get_MotCurrentPos(M_BTMID_ULD2) > st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_PICK] + COMI.md_allow_value[M_BTMID_ULD2])
		{
			CString strError;
			strError.Format("%02d0008",M_BTMID_ULD2);
			CTL_Lib.Alarm_Error_Occurrence(26, CTL_dWARNING, strError);
			COMI.Set_MotStop( 32, M_IDBUFFER_EL);
			return BD_ERROR;
		}
		break;

	case M_TOPID_LD1://2014.1018
////2015.0705
// 		if( ( COMI.Get_MotCurrentPos( M_D_ATTACH_Y ) > (st_motor[M_D_ATTACH_Y].d_pos[P_XY_PLACE_DENSITY] - COMI.md_allow_value[M_D_ATTACH_Y]) ) &&
// 			( COMI.Get_MotCurrentPos( M_D_ATTACH_Y ) < (st_motor[M_D_ATTACH_Y].d_pos[P_XY_PLACE_DENSITY] + COMI.md_allow_value[M_D_ATTACH_Y]) ) )
		if( COMI.Get_MotCurrentPos( M_D_ATTACH_Y ) < st_motor[M_D_ATTACH_Y].d_pos[P_XY_PLACE_DENSITY] + 50 + COMI.md_allow_value[M_D_ATTACH_Y] )
		{
			if( COMI.Get_MotCurrentPos( M_D_ATTACH_Z1) > st_motor[M_D_ATTACH_Z1].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z1] ||
				COMI.Get_MotCurrentPos( M_D_ATTACH_Z2) > st_motor[M_D_ATTACH_Z2].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z2] )
			{
				if( d_targetpos < st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK] - COMI.md_allow_value[M_TOPID_LD1])
				{
					//CTL_Lib.Alarm_Error_Occurrence( 1905, dWARNING, "120008"); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence( 1905, dWARNING, "010008");
					return BD_ERROR;
				}
			}
		}
////
		if( d_targetpos < st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK] - COMI.md_allow_value[M_TOPID_LD1])
		{

			if( COMI.Get_MotCurrentPos( M_TOPID_LD2 ) < st_motor[M_TOPID_LD2].d_pos[P_ROLLER_SAGETY] + COMI.md_allow_value[M_TOPID_LD2] && st_handler.mn_virtual_mode == 0 )
			{//250008 0 00 "Top ID Buffr LD2 Axis Motor is Non Safety Pos." //2016.0722
				if( g_ioMgr.get_in_bit( st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk, IO_OFF) == IO_ON ||
					g_ioMgr.get_in_bit( st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON) == IO_OFF)	//2014.1018			
				{
					//CTL_Lib.Alarm_Error_Occurrence(37, CTL_dWARNING, "340008"); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence(37, CTL_dWARNING, "250008");
					return BD_ERROR;
				}
			}
		}


		if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[0]) == IO_ON || 
			g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[0]) == IO_OFF )
		{
			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_clamp[0]) == IO_ON || g_ioMgr.get_in_bit(st_io.i_top_idbuffer_unclamp[0]) == IO_OFF )
			{
				CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[0], IO_ON );
				CTL_Lib.Alarm_Error_Occurrence( 1901, dWARNING, strJamCode );
				return BD_ERROR;
			}
// 			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_clamp[1]) == IO_ON || g_ioMgr.get_in_bit(st_io.i_top_idbuffer_unclamp[1]) == IO_OFF )
// 			{				
// 				CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[1], IO_ON );
// 				CTL_Lib.Alarm_Error_Occurrence( 1902, dWARNING, strJamCode );
// 			}
		}

		//2016.0725
		if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[0]) == IO_ON || 
			g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[0]) == IO_OFF )
		{
			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[1]) == IO_ON || 
				g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[1]) == IO_OFF )
			{

				if( COMI.Get_MotCurrentPos(M_TOPID_LD1) < st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK] - COMI.md_allow_value[M_TOPID_LD1] &&
					COMI.Get_MotCurrentPos(M_TOPID_LD2) <= st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + COMI.md_allow_value[M_TOPID_LD2] )
				{
					CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[0], IO_ON );
					CTL_Lib.Alarm_Error_Occurrence( 1902, dWARNING, strJamCode );
					return BD_ERROR;
				}
			}
		}

		break;

	case M_TOPID_LD2:
		if( COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Y ) < st_motor[M_BCR_ATTACH1_Y].d_pos[P_Y_BCR_PLACE] + COMI.md_allow_value[M_BCR_ATTACH1_Y])
		{
			int nRet_1 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk, IO_ON); 
			int nRet_2 = g_ioMgr.get_in_bit(st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk, IO_ON); 
			if( nRet_1 != IO_ON || nRet_2 != IO_ON || d_targetpos == st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD])
			{
				if( COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] ||
					COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
				{
					//CTL_Lib.Alarm_Error_Occurrence( 1903, dWARNING, "170008"); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence( 1903, dWARNING, "090008");
					return BD_ERROR;
				}
			}
		}
		if(	COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Y ) < ( st_motor[M_BCR_ATTACH1_Y].d_pos[P_X_BCR_REJECT] + 50 + COMI.md_allow_value[M_BCR_ATTACH1_Y] ) )
		{
			if( COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z1) > st_motor[M_BCR_ATTACH1_Z1].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z1] ||
				COMI.Get_MotCurrentPos( M_BCR_ATTACH1_Z2) > st_motor[M_BCR_ATTACH1_Z2].d_pos[P_Z_SAFETY] + COMI.md_allow_value[M_BCR_ATTACH1_Z2] )
			{
				if( d_targetpos >= st_motor[ M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD])
				{
					CTL_Lib.Alarm_Error_Occurrence( 1903, dWARNING, "220008");
					return BD_ERROR;
				}
			}
		}

// 		if( COMI.Get_MotCurrentPos( M_D_ATTACH_Y ) < st_motor[M_D_ATTACH_Y].d_pos[P_XY_PLACE_DENSITY] - COMI.md_allow_value[M_D_ATTACH_Y] )
// 		{
// 			if( COMI.Get_MotCurrentPos( M_D_ATTACH_Z1) > st_motor[M_D_ATTACH_Z1].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z1] ||
// 				COMI.Get_MotCurrentPos( M_D_ATTACH_Z2) > st_motor[M_D_ATTACH_Z2].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z2] )
// 			{
// 				CTL_Lib.Alarm_Error_Occurrence( 1904, dWARNING, "120008");
// 				return BD_ERROR;
// 			}
// 		}
		
		if( COMI.Get_MotCurrentPos( M_D_ATTACH_Y ) < st_motor[M_D_ATTACH_Y].d_pos[P_XY_PLACE_DENSITY] + 50 + COMI.md_allow_value[M_D_ATTACH_Y] )
		{
			if( COMI.Get_MotCurrentPos( M_D_ATTACH_Z1) > st_motor[M_D_ATTACH_Z1].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z1] ||
				COMI.Get_MotCurrentPos( M_D_ATTACH_Z2) > st_motor[M_D_ATTACH_Z2].d_pos[P_Z_DENSITY_SAFETY] + COMI.md_allow_value[M_D_ATTACH_Z2] )
			{
				if( d_targetpos >= st_motor[ M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD])
				{
					//CTL_Lib.Alarm_Error_Occurrence( 1984, dWARNING, "120008"); //2016.0722
					CTL_Lib.Alarm_Error_Occurrence( 1984, dWARNING, "010008");
					return BD_ERROR;
				}
			}
		}		

		if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[1]) == IO_ON || 
			g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[1]) == IO_OFF )
		{
			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_clamp[0]) == IO_ON || g_ioMgr.get_in_bit(st_io.i_top_idbuffer_unclamp[0]) == IO_OFF )
			{
				CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[0], IO_ON );
				CTL_Lib.Alarm_Error_Occurrence( 1901, dWARNING, strJamCode );
				return BD_ERROR;
			}
			if( COMI.Get_MotCurrentPos(M_TOPID_LD1) < st_motor[M_TOPID_LD1].d_pos[P_LDBUFFER_PICK] - COMI.md_allow_value[M_TOPID_LD1] &&
				COMI.Get_MotCurrentPos(M_TOPID_LD2) <= st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + COMI.md_allow_value[M_TOPID_LD2] )
			{
				if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[0]) == IO_ON || 
					g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[0]) == IO_OFF )
				{				
					CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[0], IO_ON );
					CTL_Lib.Alarm_Error_Occurrence( 1902, dWARNING, strJamCode );
					return BD_ERROR;
				}
			}

		}
		if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_clamp[2]) == IO_ON || 
			g_ioMgr.get_in_bit(st_io.i_top_idbuffer_shifter_hook_unclamp[2]) == IO_OFF )
		{
			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_clamp[2]) == IO_ON || g_ioMgr.get_in_bit(st_io.i_top_idbuffer_unclamp[2]) == IO_OFF )
			{
				CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[2], IO_ON );
				CTL_Lib.Alarm_Error_Occurrence( 1903, dWARNING, strJamCode );
				return BD_ERROR;
			}
			if( g_ioMgr.get_in_bit(st_io.i_top_idbuffer_clamp[3]) == IO_ON || g_ioMgr.get_in_bit(st_io.i_top_idbuffer_unclamp[3]) == IO_OFF )
			{				
				CString strJamCode = GetJamCode_Load_Clamp_Time(st_io.i_top_idbuffer_clamp[3], IO_ON );
				CTL_Lib.Alarm_Error_Occurrence( 1904, dWARNING, strJamCode );
				return BD_ERROR;
			}			
		}

		if( COMI.Get_MotCurrentPos(M_INDEX_ROLLER1) > st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY] + COMI.md_allow_value[M_INDEX_ROLLER1] && st_handler.mn_virtual_mode == 0 )
		{//220008 0 00 "Index Rolling1 Axis Motor is Non Safety Pos." //2016.0722
			if( d_targetpos >= st_motor[ M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD])
			{
				//CTL_Lib.Alarm_Error_Occurrence(38, CTL_dWARNING, "380008"); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(38, CTL_dWARNING, "220008");
				return BD_ERROR;
			}
		}
		if(d_targetpos > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + 100)
		{
			if( COMI.Get_MotCurrentPos( M_IDBUFFER_EL) < st_motor[M_IDBUFFER_EL].d_pos[P_UPBUFFER] - COMI.md_allow_value[M_IDBUFFER_EL] )
			{
				//CTL_Lib.Alarm_Error_Occurrence(40, CTL_dWARNING, "320008"); //2016.0722
				CTL_Lib.Alarm_Error_Occurrence(40, CTL_dWARNING, "230008");
				return BD_ERROR;
			}
			else
			{
				if( g_ioMgr.get_in_bit(st_io.i_idbuffer_elv_hook_clamp_chk) == IO_ON ||
					g_ioMgr.get_in_bit(st_io.i_idbuffer_elv_hook_unclamp_chk) == IO_OFF )
				{
					CString strError;
					strError.Format("5%04d%d",st_io.i_idbuffer_elv_hook_unclamp_chk, IO_ON);
					CTL_Lib.Alarm_Error_Occurrence(3439, CTL_dWARNING, strError);
					return BD_ERROR;
				}
			}
		}
		if( d_targetpos > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_PICK] + 100 &&
			(g_ioMgr.get_in_bit(st_io.i_top_box_supportup_chk, IO_OFF) == IO_ON || 
			g_ioMgr.get_in_bit(st_io.i_top_box_supportdn_chk, IO_ON) == IO_OFF) )
		{
			CString strError;
			if(st_io.i_top_box_supportup_chk == IO_ON)
			{
				strError.Format("5%04d%d", st_io.i_top_box_supportup_chk, IO_ON);
			}
			else
			{
				strError.Format("5%04d%d", st_io.i_top_box_supportdn_chk, IO_OFF);
			}
// 			COMI.Set_MotStop( 0, M_TOPID_LD2 );

			CTL_Lib.Alarm_Error_Occurrence(3459, CTL_dWARNING, strError);
			return BD_ERROR;

		}
		nRet1 = COMI.Check_MotPosRange(M_ULD_Y, st_motor[M_ULD_Y].d_pos[P_ULD_Y_PICK_POS], COMI.md_allow_value[M_ULD_Y]);
		if( nRet1 == BD_GOOD && d_targetpos > st_motor[M_TOPID_LD2].d_pos[P_LDBUFFER_LAOD] - 10)
		{
			if( COMI.Get_MotCurrentPos(M_ULD_Z) > st_motor[M_ULD_Z].d_pos[P_ULD_Z_PICK_READY_POS] + COMI.md_allow_value[M_ULD_Z] )
			{//180008 0 00 "Unload Robot Z Axis Motor is Non Safety Pos. //2016.0722
				//CTL_Lib.Alarm_Error_Occurrence(98, CTL_dWARNING, "300008" );
				CTL_Lib.Alarm_Error_Occurrence(98, CTL_dWARNING, "180008" );
				return BD_ERROR;
			}
		}

		break;
	case M_BTMID_ULD1:
		if(d_targetpos > (st_motor[M_BTMID_ULD1].d_pos[P_ULDBUFFER_PICK] + COMI.md_allow_value[M_BTMID_ULD1]) )
		{
			if( g_ioMgr.get_in_bit(st_io.i_btm_idbuffer34_clamp_chk) == IO_ON || 
				g_ioMgr.get_in_bit(st_io.i_btm_idbuffer34_unclamp_chk) == IO_OFF )
			{
				CString strError;
				strError.Format("5%04d%d",st_io.i_btm_idbuffer34_clamp_chk, IO_ON);						
				COMI.Set_MotStop(0, M_BTMID_ULD1);
				CTL_Lib.Alarm_Error_Occurrence(441, CTL_dWARNING, strError);
				return BD_ERROR;
			}
		}

		break;
	case M_BTMID_ULD2:
		{
			int iHook_Clamp_1 = st_io.i_btm_idbuffer_shifter_hook_fwd[1];
			int iHook_UnClamp_1 = st_io.i_btm_idbuffer_shifter_hook_bwd[1];
			int iHook_Clamp_2 = st_io.i_btm_idbuffer_shifter_hook_fwd[2];
			int iHook_UnClamp_2 = st_io.i_btm_idbuffer_shifter_hook_bwd[2];
			if( /*(COMI.Get_MotCurrentPos(M_BTMID_ULD2) > st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_SAFETY] + 100) &&*/
				(d_targetpos < st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_SAFETY] + COMI.md_allow_value[M_BTMID_ULD2]) )
			{
	// 			st_io.i_btm_idbuffer_uld2_shifter_hook_fwd1_chk						= 3404;
	// 			st_io.i_btm_idbuffer_uld2_shifter_hook_back1_chk					= 3405;
	// 			st_io.i_btm_idbuffer_uld2_shifter_hook_fwd2_chk						= 3406;
	// 			st_io.i_btm_idbuffer_uld2_shifter_hook_back2_chk					= 3407;

				if( g_ioMgr.get_in_bit(iHook_Clamp_1) == IO_ON || g_ioMgr.get_in_bit(iHook_UnClamp_1) == IO_OFF ||
					g_ioMgr.get_in_bit(iHook_Clamp_2) == IO_ON || g_ioMgr.get_in_bit(iHook_UnClamp_2) == IO_OFF )
				{
					CString strError;
					if( g_ioMgr.get_in_bit(iHook_Clamp_1) == IO_ON || g_ioMgr.get_in_bit(iHook_UnClamp_1) == IO_OFF )
						strError.Format("5%04d%d",st_io.i_btm_idbuffer_shifter_hook_fwd[1], IO_ON);
					else
						strError.Format("5%04d%d",st_io.i_btm_idbuffer_shifter_hook_fwd[2], IO_ON);

					COMI.Set_MotStop(0, M_BTMID_ULD2);
					CTL_Lib.Alarm_Error_Occurrence(41, CTL_dWARNING, strError);
					return BD_ERROR;
				}
			}

			if( (COMI.Get_MotCurrentPos(M_BTMID_ULD2) > st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_SAFETY] + COMI.md_allow_value[M_BTMID_ULD2] ) &&
				(d_targetpos < st_motor[M_BTMID_ULD2].d_pos[P_ULDBUFFER_SAFETY] + COMI.md_allow_value[M_BTMID_ULD2]) &&
				(g_ioMgr.get_in_bit( st_io.i_top_idbuffer_ld1_shifter_hook_clamp_chk, IO_OFF) == IO_ON ||
				 g_ioMgr.get_in_bit( st_io.i_top_idbuffer_ld1_shifter_hook_unclamp_chk, IO_ON) == IO_OFF) ) 
			{
				if( g_ioMgr.get_in_bit(st_io.i_btm_idbuffer12_clamp_chk) == IO_ON || 
					g_ioMgr.get_in_bit(st_io.i_btm_idbuffer12_unclamp_chk) == IO_OFF )
				{
					if( COMI.mn_run_status != dINIT )//2015.0825
					{
						CString strError;
						strError.Format("5%04d%d",st_io.i_btm_idbuffer12_clamp_chk, IO_ON);						
						COMI.Set_MotStop(0, M_BTMID_ULD2);
						CTL_Lib.Alarm_Error_Occurrence(42, CTL_dWARNING, strError);
						return BD_ERROR;
					}
				}
			}			

		}

		break;
	case M_INDEX_X:
		if( COMI.Get_MotCurrentPos(M_INDEX_ROLLER1) > ( st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY] + COMI.md_allow_value[M_INDEX_ROLLER1] ) )
		{
			if( COMI.Get_MotCurrentPos(M_INDEX_ROLLER1) > ( st_motor[M_INDEX_ROLLER1].d_pos[P_ROLLER_SAGETY] + COMI.md_allow_value[M_INDEX_ROLLER1] ) )
			{//220008 0 A "Index_Rolling1_Axis_Motor_is_Non_Safety_Pos." //2016.0722
				//CTL_Lib.Alarm_Error_Occurrence(8142, CTL_dWARNING, "380008");
				CTL_Lib.Alarm_Error_Occurrence(8142, CTL_dWARNING, "220008");
				sprintf(st_msg.c_abnormal_msg, "8142, [M_INDEX_X] M_INDEX_X can't move because of M_INDEX_ROLLER1.");
				if (st_handler.cwnd_list != NULL)  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);

				return BD_ERROR;
			}
			else
			{//390008 0 A "Index_Rolling2_Axis_Motor_is_Non_Safety_Pos."
				CTL_Lib.Alarm_Error_Occurrence(8143, CTL_dWARNING, "390008");
				sprintf(st_msg.c_abnormal_msg, "8143, [M_INDEX_X] M_INDEX_X can't move because of M_INDEX_ROLLER2.");
				return BD_ERROR;

			}
		}
		
		break;

	case M_INDEX_ROLLER1:
		{
			int aa = 10;
		}
		break;

	case M_ULD_ROLLER_PITCH:
		break;

	}

	st_motor[n_axis].mn_retry_time_flag = CTL_NO;//2011.0201 �߰� 

	return BD_GOOD;
}

BOOL CCtlBd_Library::CreateFolder(LPCTSTR szPath)
{
	int nRet = 0;
	CString strTemp;
	CString strPath = szPath;
	
    do{
        nRet = strPath.Find('\\' , nRet + 1);
        if (nRet > 0 )
        {
            strTemp = strPath.Left(nRet+1);
			
            if (_access(strTemp.operator LPCTSTR(), 00) == -1)
			{
				CreateDirectory(strTemp , NULL);
			}
        }
    }while (nRet != -1);
	
    return nRet;
}

int CCtlBd_Library::FileSizeCheck(char * cp_filename, int n_size, int n_check)
{
	CFileFind finder;
	long nLen=0, nflag=0;
	BOOL bContinue;
	
	if(bContinue = finder.FindFile(cp_filename))
	{	
		if (n_check == BD_YES)			// Size�� üũ�ϴ°��̸�...
		{
			finder.FindFile(cp_filename);
			finder.FindNextFile();
			finder.GetFileName();
			nLen = finder.GetLength();
			if(nLen > n_size)
			{
				nflag = 1;
			}
			finder.Close();	
		}
		else						// Size�� Ȯ���ϴ°��̸�...
		{
			finder.FindFile(cp_filename);
			finder.FindNextFile();
			finder.GetFileName();
			nLen = finder.GetLength();
			
			nflag = nLen;
			
			finder.Close();	
		}
	}
	
	return nflag;
}

int CCtlBd_Library::LogFile_Write(char * cp_dir_path, char * cp_msg)
{
//2011.0417	sing.Lock(); //2011.0417 

	CString mstr_cur_year, mstr_cur_month, mstr_cur_day, str_display_time; // ���� ��, ��, �� ���� ���������� ��ȯ�Ͽ� ������ ���� 
	int mn_cur_year, mn_cur_month, mn_cur_day, mn_cur_hour; // ���� ��, ��, �� ���� ���� ���� 
	CString mstr_file_name, mstr_dir_path, str_msg;		// ���������� ������ ���� �̸� ���� ���� 
	CString mstr_create_file;	// �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ���� 
	CString mstr_list_name, mstr_temp_data;  // �� �κк� �˶� �߻� Ƚ�� ���� ������ �α� ���� ���� ���� ���� 
	CString mstr_content;		// �� ���ο� ����� ���ڿ� ���� ���� ���� 
	COleDateTime time_cur;		// �˻��� �ð� ���� ���� ���� 
	CTime m_time_current;		// ������ ����� ���� �ð� ���� ���� ����
	char chr_buf[20]={0,};
	int mn_existence, nlength;			// ���� ���� ���� ���� �÷��� 
	char cfileName[256]={0,};			// �˻��� ���� ���� ���� �Լ� 
	FILE  *fp ;					// ���Ͽ� ���� ������ ���� ���� 

	CString BackupName;
	CString mstr_cur_hour, mstr_cur_min, mstr_cur_sec;
	int Ret=0;

	nlength = strlen(cp_msg);
	if(nlength <= 0) //������ �޼����� ���� 
	{
		return BD_ERROR;
	}
	str_msg = cp_msg;
 
	// **************************************************************************
	// ���� �̸����� ����� ��¥ ������ ��´�                                   
	// **************************************************************************
	time_cur = COleDateTime::GetCurrentTime();  // ���� �ð� ������ ��´�. 

	m_time_current = CTime::GetCurrentTime() ;  // ������ ������ ���� �ð� ���� ��´�. 

	mn_cur_year = time_cur.GetYear();  

	mn_cur_month = time_cur.GetMonth();  

    mn_cur_day = time_cur.GetDay();  

	mn_cur_hour = time_cur.GetHour();
	// **************************************************************************

	// **************************************************************************
	// ��¥ ������ ���������� ��ȯ�Ͽ� ������ �����Ѵ�                           
	// **************************************************************************
	mstr_cur_year = LPCTSTR(_itoa( mn_cur_year, chr_buf, 10 ));  
	mstr_cur_month.Format("%02d", mn_cur_month);
	mstr_cur_day.Format("%02d", mn_cur_day);

	// **************************************************************************
	// ���� �ð� ���� ��´�                                                     
	// **************************************************************************
	mn_cur_hour = time_cur.GetHour();				// ���� �ð� ������ �����Ѵ�. 
	mstr_cur_hour.Format("%d",time_cur.GetHour());	// ���� �ð� ������ �����Ѵ�.
	mstr_cur_min.Format("%d",time_cur.GetMinute());	// ���� �� ������ �����Ѵ�. 
	mstr_cur_sec.Format("%d",time_cur.GetSecond());	// ���� �� ������ �����Ѵ�. 
	str_display_time = m_time_current.Format("%c");	// ����Ʈ ���Ͽ� ����� Ÿ��Ʋ �ð� ���� ���� 
	// **************************************************************************


	mstr_dir_path = cp_dir_path;
	mstr_file_name = mstr_cur_year;
	mstr_file_name += mstr_cur_month; 
	mstr_file_name += mstr_cur_day; 
	mstr_create_file = mstr_dir_path + mstr_file_name;

	mstr_create_file += ".TXT";

	sprintf(cfileName, "%s", mstr_create_file);
	mn_existence = access(cfileName,0) ;	
	if (mn_existence == -1)
	{//�ش� ������ �������� �ʴ� �����̴� 
		CreateFolder(cp_dir_path); 
	}
	else 
	{//�ش� ������ �̹� �����Ѵ�.
		//���� 
	}
	
	Ret = FileSizeCheck(cfileName, 1048576, BD_YES); //size and rename	
	if(Ret == 1) //file size over
	{
		BackupName = mstr_create_file + mstr_cur_hour + mstr_cur_min +  mstr_cur_sec + ".bak" ;
		rename(mstr_create_file, BackupName);
	}

	if ((fp = fopen(mstr_create_file,"a+")) == NULL)  
	{
		//AfxMessageBox("File open failure!..");
		sprintf(mc_normal_msg,"LogFile_Write a+ Error"); 
		
 		return BD_ERROR;
	}
	// **************************************************************************
	
	mstr_content += str_display_time;
	mstr_content += " : " + str_msg;

	fprintf(fp,"%s\n",mstr_content) ;
	if (ferror(fp))  
	{
		sprintf(mc_normal_msg,"LogFile_Write ferror return error");

		clearerr(fp); //2011.0418 

		fclose(fp) ;  //2011.0417  ���� ����

//2011.0417		sing.Unlock(); //2011.0417 �߰� 
		return BD_ERROR;
	}
	// **************************************************************************
	fclose(fp);  // ������ �����Ѵ�.

//2011.0417	sing.Unlock(); //2011.0417 �߰� 
	return BD_GOOD;
}

int CCtlBd_Library::Single_Move(int n_MotNum, double d_MotPos, int n_SpeedRate)
{
	int nFuncRet = BD_PROCEED;
	int nRet;

// 	if(n_MotNum == 17 && mn_single_motmove_step[n_MotNum] == 200)
// 	{
// 		nRet = 1;
// 	}
	
	switch(mn_single_motmove_step[n_MotNum])
	{
	case 0:
		nRet = COMI.Check_MotPosRange(n_MotNum, d_MotPos, COMI.md_allow_value[n_MotNum]);
		if (nRet == BD_GOOD) //�̹� �ش� ��ġ�� �� ������ �������� �ʰ� ���� �̵��� ������ 
		{
			nFuncRet = BD_GOOD;
			break;
		}
		
		mn_mot_retry_cnt[n_MotNum] = 0;
		mn_mot_max_retry_cnt = 3; //�ִ� 3ȸ ��Ʈ���� ������ �����Ѵ� 
		mn_single_motmove_step[n_MotNum] = 100;
		break;
		
	case 100:
		if(COMI.mn_run_status == dRUN) st_work.md_reinstatement_Pos[0][n_MotNum] = d_MotPos;
		nRet = COMI.Start_SingleMove(n_MotNum, d_MotPos, n_SpeedRate);  // �ش� ��ġ�� �̵�
		if (nRet == BD_GOOD)
		{
			mn_single_motmove_step[n_MotNum] = 200;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			mn_mot_retry_cnt[n_MotNum]++;
			
			if(mn_mot_retry_cnt[n_MotNum] > mn_mot_max_retry_cnt) 
			{
				mn_single_motmove_step[n_MotNum] = 0;
				nFuncRet = nRet;
			}
			else 
			{				
				mn_single_motmove_step[n_MotNum] = 100;
			}
		}
		else if (nRet == BD_RETRY)  // ���� ��õ�
		{
			if(mn_mot_retry_cnt[n_MotNum] > mn_mot_max_retry_cnt) 
			{
				mn_single_motmove_step[n_MotNum] = 0;
				nFuncRet = BD_ERROR;
			}
			else 
			{				
				mn_single_motmove_step[n_MotNum] = 100;
			}
		}
		break;
		
	case 200:
		nRet = COMI.Check_SingleMove(n_MotNum, d_MotPos);  // �̵� �Ϸ� Ȯ��
		if (nRet == BD_GOOD)  // ���� �Ϸ�
		{
			mn_single_motmove_step[n_MotNum] = 0;
			nFuncRet = nRet;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			mn_mot_retry_cnt[n_MotNum]++;
			
			if(mn_mot_retry_cnt[n_MotNum] > mn_mot_max_retry_cnt) 
			{
				mn_single_motmove_step[n_MotNum] = 0;
				nFuncRet = nRet;
			}
			else 
			{				
				mn_single_motmove_step[n_MotNum] = 100;
			}
		}
		else if (nRet == BD_RETRY)  // ���� ��õ�
		{
			// ���ѷ����� �������� ������ Ƚ���� �����ؼ� ����ϸ� ���� ����
			mn_mot_retry_cnt[n_MotNum]++;
			
			if(mn_mot_retry_cnt[n_MotNum] > mn_mot_max_retry_cnt) 
			{
				mn_single_motmove_step[n_MotNum] = 0;
				nFuncRet = BD_ERROR;
			}
			else 
			{				
				mn_single_motmove_step[n_MotNum] = 100;
			}
		}
		break;
	}
	return nFuncRet;
}

//2015.0326 james ���� 
int CCtlBd_Library::Linear_Move(int n_LinearMapIndex, long l_AxisCnt, long *lp_AxisNum, double *dp_PosList, double *dp_SpdRatio)
{
	int nFuncRet = BD_PROCEED;
	int nRet[4] = {0,}, nCnt =0, i=0;
	
	switch(mn_linear_motmove_step[n_LinearMapIndex])
	{
	case 0:

		nCnt = 0;
		st_linearmot[n_LinearMapIndex].l_AxisCnt = l_AxisCnt;
		COMI.ml_axiscnt[n_LinearMapIndex] = l_AxisCnt; //2015.0326 james ���̺귯���� ������ ���Ⱑ �ʿ��ϴ� ���� �������� 
		for(i=0; i<l_AxisCnt; i++)
		{		
			COMI.mp_axisnum[n_LinearMapIndex][i] = lp_AxisNum[i]; //2015.0326 james ���̺귯���� ������ ���Ⱑ �ʿ��ϴ� ���� �������� 
			st_linearmot[n_LinearMapIndex].lp_AxisNum[i] = lp_AxisNum[i]; 
			st_linearmot[n_LinearMapIndex].dp_PosList[i] = dp_PosList[i];

			nRet[i] = COMI.Check_MotPosRange(lp_AxisNum[i], dp_PosList[i], COMI.md_allow_value[lp_AxisNum[i]]);
			if(nRet[i] == BD_GOOD) nCnt++;
		}

		if(nCnt == l_AxisCnt)
		{//�̹� ��� ������ ���� ��ġ�� �̵��Ϸ��� ��ġ�� ������ �ȿ� ������ ������ �ʿ䰡 ������ ������.
			nFuncRet = BD_GOOD;
			break;
		}
		
		mn_linear_retry_cnt[n_LinearMapIndex] = 0;
		mn_linear_max_retry_cnt = 3; //�ִ� 3ȸ ��Ʈ���� ������ �����Ѵ� 
		mn_linear_motmove_step[n_LinearMapIndex] = 100;
		break;
		
	case 100:
		if(COMI.mn_run_status == dRUN)
		{
			st_work.md_reinstatement_Pos[0][lp_AxisNum[0]] = dp_PosList[0];
			st_work.md_reinstatement_Pos[0][lp_AxisNum[1]] = dp_PosList[1];
		}
		nRet[0] = COMI.Start_LinearMove(n_LinearMapIndex, st_linearmot[n_LinearMapIndex].dp_PosList, dp_SpdRatio);
		if (nRet[0] == BD_GOOD)
		{
			mn_linear_motmove_step[n_LinearMapIndex] = 200;
		}
		else if (nRet[0] == BD_ERROR || nRet[0] == BD_SAFETY)
		{
			mn_linear_retry_cnt[n_LinearMapIndex]++;
			
			if(mn_linear_retry_cnt[n_LinearMapIndex] > mn_linear_max_retry_cnt) 
			{
				mn_linear_motmove_step[n_LinearMapIndex] = 0;
				nFuncRet = nRet[0];
			}
			else 
			{				
				mn_linear_motmove_step[n_LinearMapIndex] = 100;
			}
		}
		else if (nRet[0] == BD_RETRY)  // ���� ��õ�
		{
			if(mn_linear_retry_cnt[n_LinearMapIndex] > mn_linear_max_retry_cnt) 
			{
				mn_linear_motmove_step[n_LinearMapIndex] = 0;
				//900000 1 A "Retry ȸ�� �����ʰ�(3ȸ) ����."
				alarm.mstr_code = _T("900000");
				nFuncRet = BD_ERROR;
			}
			else 
			{				
				mn_linear_motmove_step[n_LinearMapIndex] = 100;
			}
		}
		break;
		
	case 200:
		nRet[0] = COMI.Check_LinearMove(n_LinearMapIndex, st_linearmot[n_LinearMapIndex].dp_PosList) ;
		if (nRet[0] == BD_GOOD)  // ���� �Ϸ�
		{
			mn_linear_motmove_step[n_LinearMapIndex] = 0;
			nFuncRet = nRet[0];
		}
		else if (nRet[0] == BD_ERROR || nRet[0] == BD_SAFETY)
		{
			mn_linear_retry_cnt[n_LinearMapIndex]++;
			
			if(mn_linear_retry_cnt[n_LinearMapIndex] > mn_linear_max_retry_cnt) 
			{
				mn_linear_motmove_step[n_LinearMapIndex] = 0;
				nFuncRet = nRet[0];
			}
			else 
			{				
				mn_linear_motmove_step[n_LinearMapIndex] = 100;
			}
		}
		else if (nRet[0] == BD_RETRY)  // ���� ��õ�
		{
			// ���ѷ����� �������� ������ Ƚ���� �����ؼ� ����ϸ� ���� ����
			mn_linear_retry_cnt[n_LinearMapIndex]++;
			
			if(mn_linear_retry_cnt[n_LinearMapIndex] > mn_linear_max_retry_cnt) 
			{
				mn_linear_motmove_step[n_LinearMapIndex] = 0;
				//900000 1 A "Retry ȸ�� �����ʰ�(3ȸ) ����."
				alarm.mstr_code = _T("900000");
				nFuncRet = BD_ERROR;
			}
			else 
			{				
				mn_linear_motmove_step[n_LinearMapIndex] = 100;
			}
		}	
		break;
	}
	return nFuncRet;
}

int CCtlBd_Library::SD_Sensor_Enable(int n_Mode, int n_AxisNum, int n_Enable)
{//Constant speed mode ������ SD ��ȣ �Է��� ���õ˴ϴ�.
	int nFuncRet = BD_PROCEED;
	
	if(n_Enable == CTL_YES) 
	{
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_EN, cmTRUE);  
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_LOGIC,cmFALSE);
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_MODE,cmTRUE);
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_LATCH, cmTRUE);
		
		
	}
	else
	{
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_EN, cmFALSE);  
		//COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_LOGIC,cmTRUE);
		//COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_MODE,cmTRUE);
		COMI.Set_Motor_IO_Property(n_AxisNum, cmSD_LATCH, cmFALSE);
		
	}
	
	return BD_GOOD;
}

//ctl_Process_conv
void CCtlBd_Library::Process_Move_Conv( int nMode, int nSite)
{
	if( st_handler.mn_safety_area == CTL_YES )
	{
		g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_OFF );
		g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
		if(st_sync.n_Move_conv == CTL_READY)
		{
			st_sync.n_Move_conv = CTL_REQ;
		}
		return;
	}
	
	nRetConvR = IO_OFF;
	nRetConv = g_ioMgr.get_in_bit( st_io.i_out_cv_box3_chk, IO_ON );
	if( nRetConv == IO_ON )
	{
		nRetConvR = IO_ON;
	}
	
	if( st_sync.n_Move_conv == CTL_REQ)
	{
		if( nRetConvR == IO_OFF )
		{
			g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_ON );
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_ON );
		}
		else
		{
			g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_OFF );
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
		}
		st_sync.n_Move_conv = CTL_READY;
	}
	else if(st_sync.n_Move_conv == CTL_READY)
	{
		if( nRetConvR == IO_OFF )
		{
			g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_ON );
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_ON );
		}
		else
		{
			g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_OFF );
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
		}

		if( nRetConvR == IO_ON)
		{
			st_sync.n_Move_conv = CTL_CHANGE;
			nRetConv = IO_OFF;
		}
	}
	
	if(st_sync.n_Move_conv == CTL_CHANGE)
	{
		g_ioMgr.set_out_bit( st_io.o_uld_cv_motor_onoff, IO_OFF );
		g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
		st_sync.n_Move_conv = CTL_NO;
	}
}

void CCtlBd_Library::Process_Out_Conv( int nMode, int nSite)
{
	if( st_handler.mn_safety_area == CTL_YES )
	{
		if(st_sync.n_Out_conv == CTL_READY)
		{
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_ON );
			st_sync.n_Out_conv = CTL_REQ;
		}
	}
	
	if( st_sync.n_Move_conv == CTL_NO )
	{
		nRetConvR = IO_OFF;
		nRetConv = g_ioMgr.get_in_bit( st_io.i_out_cv_box3_chk, IO_ON );
		nRetConv |=	g_ioMgr.get_in_bit( st_io.i_out_cv_box2_chk, IO_ON );
		if( nRetConv == IO_ON )
		{
			nRetConvR = IO_ON;
		}
		
		if( st_sync.n_Out_conv == CTL_REQ)
		{

			st_sync.n_Out_conv = CTL_READY;
			
		}
		else if(st_sync.n_Out_conv == CTL_READY)
		{
			if( nRetConvR == IO_OFF )
			{
				g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_ON );
			}
			else
			{
				g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
			}
	// 		nRetConv = IO_OFF;
	// 		nRetConvR = IO_OFF;
			if( nRetConvR == IO_ON)
			{
				st_sync.n_Out_conv = CTL_CHANGE;
				nRetConv = IO_OFF;
			}
		}
		if(st_sync.n_Out_conv == CTL_CHANGE )
		{
			g_ioMgr.set_out_bit( st_io.o_out_rear_cv_motor_onoff, IO_OFF );
			st_sync.n_Out_conv = CTL_NO;
		}
		
	}
}