// ComizoaPublic.cpp: implementation of the CComizoaPublic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComizoaPublic.h"
#include "Cmmsdk.h"
#include "CmmsdkDef.h"
#include "math.h"
#include "io.h"						// ���� ���� ���� �˻� �Լ� ȣ���ϱ� ���ؼ��� �ݵ�� INCLUDE �ʿ� 

#include "CtlBd_Library.h"
#include "COMI_Manager.h"
#include "..\common\ShareMem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CComizoaPublic COMI;


////////////////////////////////////////////////////////////
//version:0.1 (2011.1026) ���Ͱ��� �⺻ �Լ� ���� 
//
////////////////////////////////////////////////////////////


/* ���Ͱ��� �⺻ alarm file ���� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//alarm code 6�ڸ� ���� 
//���ڸ� 0~1���� 2�� : ���͹�ȣ ���� (0~99����)
//���ڸ� 2~5���� 4�� : �˶� ��ȣ ���� �ִ� (0~9999����)
//
//
///////////////////////////////////////////////////////////////
//�⺻ �˶� ���� ����, 7�� ��ġ 
// 0 : ��� �˶�, �޼����� ����ϰ� �˶� ī��Ʈ�� ���� �ʴ´� 
// 1 : ��� �˶�, �˶� ī��Ʈ �� 
// 2 : �������� �˶�, �˶� ī��Ʈ���� �ʴ´�.
// 3 : ....
//
//
///////////////////////////////////////////////////////////////
// �˶� ��Ʈ(��ġ) ����, 9�� ��ġ, �� ������ ������ Ȯ�ν� ����Ѵ� 
// A, B, C, D, E, F, .......Z
//
//
///////////////////////////////////////////////////////////////
// �˶� �޼��� ����Ѵ�, 11�� ���� 
//  
///////////////////////////////////////////////////////////////

010001 3 A "Motor Parametor Setting Error(01 motor)."
010002 3 A "Motor Move Setting Error01 motor)."
010003 1 A "Motor Home Check Error(01 motor)."
010004 1 A "Motor Alarm Error(01 motor)."
010005 1 A "Motor Power Off Error(01 motor)."
010006 1 A "Motor Move Check Error(01 motor)."
010007 2 A "Motor Move Safety Check Error(01 motor)."
010008 1 A "Motor position minus limit error(01 motor)."
010009 1 A "Motor position plus limit error(01 motor)."
010010 1 A "Motor Interrupt check error(01 motor)."
010011 1 A "Motor Move Time Out Check Error(01 motor)."
010012 1 A "Motor allow position Check Error(01 motor)."
010013 1 A "Motor motion done Check Error(01 motor)."

010015 1 A "Interpolation IxMapAxis setting Error(01 IxMap)."
010016 1 A "Interpolation IxMapAxis check Error  (01 IxMap)."
*/



CComizoaPublic::CComizoaPublic()
{
	int i, j=0;

	for(i=0; i<16; i++) ml_LmIndexNumber[i] = i;  //�ִ� 16���� ListIndexMap�� ������ �ִ� 
	for(i=0; i<8; i++)  ml_IxIndexNumber[i] = i;  //�ִ� 8���� IxIndexMap�� ���� �� �ִ� 
	
	//2011.1024 
	mn_max_move_limit_time = 50000; //1��
	mn_max_home_limit_time = 60000; //1�� 
	mn_max_retry_cnt = 3;

	//����ϴ� ���� BD_YES�� �ʱ�ȭ �ؾ� �Ѵ� 
 	for(i=0; i<6; i++)
 	{
 		mn_sd_io_property_flag[i] = BD_YES;	//sd io ���� ������� ���� 
// 		mn_interrupt_flag[i] = BD_NO;        //interrupt ��� ���� ���� 
 	}

	for( i = 0; i < MOTOR_COUNT; i++ )
	{
		m_iAxisDelayFlag[i] = 0;
	}
}

CComizoaPublic::~CComizoaPublic()
{

}

int CComizoaPublic::Initialize_MotBoard(CString s_file) //���� �ʱ�ȭ 
{
	int nRet = -1;
	long nNumAxes = 0;
	
//Ŀ������ ���ͺ��� �ʱ�ȭ ���� 
//1. Ŀ������ ���̺귯���� �������α׷� ������ �ε��Ѵ� 
//2. ���ͺ���(�ϵ����)�� �α��ϰ� ��ġ�� �ʱ�ȭ �Ѵ�   
//3. ���� ���ǵ带 �����Ѵ� cmmCfgSetSpeedPattern(nAxis, nSpeedMode, d_work, d_accel, d_decel);

	nRet = cmmLoadDll(); //���̺귯�� �ε� - ���� ���α׷��� �޸� �������� Ŀ������ ���̺귯�� �ε� 

	if (nRet == TRUE)	//TRUE    1
	{
		nRet = BD_GOOD;
	}
	else
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "cmmLoadDll return error");
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR; //MOT_OPEN_FAIL;
	}

	nRet = cmmGnDeviceLoad(cmTRUE, &nNumAxes);//���ͺ���(�ϵ����)�� �α��ϰ� ��ġ�� �ʱ�ȭ �Ѵ�.
	// cmFALSE�� ���ڰ��� �ٲٸ�, ���α׷��� ����� ������ ���� �Ŀ��� �����°��� �����Ҽ� �ִ�. 
	// ������ ó�� �ѹ��� �ݵ�� TRUE�� �Ǿ� �Ѵ�.

	if (nRet == cmERR_NONE) //���༺�� �ǹ�, nNumAxes=����������� ������ ��ȯ  
	{
		nRet = cmmGnInitFromFile(s_file); //("c:\\AMT7000\\Setting\\amt7000.cme2");
		if (nRet != cmERR_NONE)
		{
			return BD_ERROR; //MOT_OPEN_FAIL;
		}
		mn_motorbd_init_end = BD_YES; 
		
		mn_totalmotoraxis_number = nNumAxes;

		cmmCfgSetSeqMode(cmSEQM_SKIP_RUN); //cmSEQM_SKIP_RUN, cmSEQM_WAIT_RUN

		nRet = BD_GOOD;
	}
	else
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "cmmGnDeviceLoad return error");
			Debug_File_Create(0, mc_normal_msg);
		}

		mn_motorbd_init_end = BD_NO; 
		nRet = BD_ERROR;
	}	
	return nRet;
}

void CComizoaPublic::Close_MotBoard() //���� Ŭ���� 
{
	cmmUnloadDll(); //���̺귯�� ��ε� - ���� ���α׷��� �޸� �������� ���� ���̺귯�� ��ε� 

	cmmGnDeviceUnload(); //�ý��ۿ� ��ġ�� �ϵ���� ��ġ�� ��ε��ϰ� ��ġ����� �����մϴ� 
}

int CComizoaPublic::Set_Simulation_Mode(int n_axis, int n_simul_mode)
{
//	n_simul_mode => 0:�ùķ��̼� ��� ��Ȱ��, 1:�ùķ��̼� ��� Ȱ��

	cmmGnSetSimulMode(n_axis, n_simul_mode);//cmCTRL_SEMI_C , ���ڴ�,(�ǵ�����) �������� ��ǥ��ǥ�� �����Ͽ� �̼��մϴ�
	return BD_GOOD;
} 

//
int CComizoaPublic::Set_CMD_CTL_Mode(int n_axis, int n_cmd_type)
{
//	cmCTRL_OPEN, // Open loop control mode
//	cmCTRL_SEMI_C, // Semi-closed loop control mode (applied only to absolute in-position commands)
//	cmCTRL_FULL_C // Full-closed loop control mode (this is not supported at current version)

	cmmCfgSetCtrlMode(n_axis, n_cmd_type);//cmCTRL_SEMI_C , ���ڴ�,(�ǵ�����) �������� ��ǥ��ǥ�� �����Ͽ� �̼��մϴ�
	return BD_GOOD;
}


int CComizoaPublic::Set_Motor_IO_Property(long n_Axis, long  n_PropId, long n_OnOff)
{
	int nRet = -1;
/*
	// MIO Property ID //
typedef enum _TCmMioPropId{
	cmALM_LOGIC=0, cmALM_MODE=1, cmCMP_LOGIC=2, cmDR_LOGIC=3, cmEL_LOGIC=4, cmEL_MODE=5, 
	cmERC_LOGIC=6, cmERC_OUT=7, cmEZ_LOGIC=8, cmINP_EN=9, cmINP_LOGIC=10, cmLTC_LOGIC=11, 
	cmLTC_LTC2SRC=12, cmORG_LOGIC=13, cmSD_EN=14, cmSD_LOGIC=15, cmSD_LATCH=16, cmSD_MODE=17, cmSTA_MODE=18,
	cmSTA_TRG=19, cmSTP_MODE=20, cmCLR_CNTR=21, cmCLR_SIGTYPE=22, cmCMP_PWIDTH=23, cmERC_ONTIME=24, cmSVON_LOGIC=25,
}TCmMioPropId;
*/
	//CMM_EXTERN long (WINAPI *cmmCfgSetMioProperty)	(long Axis, long PropId, long PropVal);

	//�켱 InPosition On/Off ����� ����Ѵ� 
	nRet = cmmCfgSetMioProperty(n_Axis, n_PropId, n_OnOff);
	if (nRet == cmERR_NONE)
	{//���� ���� 
		return BD_GOOD;
	}
	else
	{//���� ���� 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d]cmmCfgSetMioProperty return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}
	return BD_ERROR;
}


// ******************************************************************************
// ���� POWER ON ���� �Լ�                                                       
// -> ����ϴ� ���� ���� �ִ� ����� ���� �Ķ���� �����Ѵ�                      
// ******************************************************************************
int CComizoaPublic::Set_MotPower(int n_Axis, int n_OnOff) 
{
	int nRet = -1, nRet_2=BD_ERROR;
	double dCurrentPos = 0, dGetPos = 0; 	

	nRet = cmmGnSetServoOn(n_Axis, n_OnOff);
	if (nRet == cmERR_NONE)
	{	 
		if (n_OnOff == BD_YES)
		{
			Sleep(200);
			dCurrentPos = Get_MotCurrentPos(n_Axis); //���ڵ� ���� ���� ��ġ 
			
			//limit �� ���� ���� 
			if (dCurrentPos < md_limit_position[n_Axis][0]) //-1 - limit 
			{//010008 E A "Motor position minus limit error(01 motor)."			 
				sprintf(mc_alarmcode, "%02d0008", n_Axis); 
				nRet_2 = BD_ERROR;
			}	
			else if (dCurrentPos > md_limit_position[n_Axis][1]) //+ limit 
			{//010009 E A "Motor position plus limit error(01 motor)."
				sprintf(mc_alarmcode, "%02d0009", n_Axis);  
				nRet_2 = BD_ERROR;
			}
			else
			{			
				//���� ��ġ�� ���ڴ� �������� �����Ѵ� 
				cmmStGetPosition(n_Axis, cmCNT_COMM, &dGetPos);				//���� Ŀ��� ��ġ 			
				cmmStSetPosition(n_Axis, cmCNT_COMM, (double)dCurrentPos);	//���ڵ� ��ġ�� Ŀ��� ��ġ�� ���� ��Ų�� 
				//cmmStSetPosition(n_Axis, cmCNT_FEED, (double)0);

				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "Axis=%d, CMDPOS[%4.3f] FEEDPOS[%4.3f]", n_Axis, dGetPos, dCurrentPos);
					Debug_File_Create(0, mc_normal_msg);
				}
				nRet_2 = BD_GOOD;
			}
		} 
		else
		{
			nRet_2 = BD_GOOD;
		}
	}
	else
	{
		nRet_2 = BD_ERROR;
	}

	if (nRet_2 == BD_ERROR)
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d]cmmGnSetServoOn OnOff= %d return error", n_Axis, n_OnOff);
			Debug_File_Create(0, mc_normal_msg);
		}
	}

	return nRet_2;
}
// ******************************************************************************


// ******************************************************************************
// 2009.8.2                                               
// -> Command �� Encoder ��ġ�� ���Ѵ�                      
// ******************************************************************************
int CComizoaPublic::Get_Deviation_Position(int n_Axis, double d_AllowPos, double * d_Get_DevPos) 
{
	int nRet = -1;
	char cJamcode[10] = {NULL};
	double d_Cmd=0, d_Feed=0, d_Dev=0, d_CompleteVal=0; 

// 	if (mn_simulation_mode == 1)
// 	{
// 		return BD_GOOD;
//	}

	cmmStGetPosition(n_Axis, cmCNT_COMM, &d_Cmd);	//���� Ŀ��� ��ġ 
	cmmStGetPosition(n_Axis, cmCNT_FEED, &d_Feed);	//���� Feedback ��ġ 
	cmmStGetPosition(n_Axis, cmCNT_DEV, &d_Dev);	//���� ����ī��Ʈ 

	d_CompleteVal =  (double)fabs(d_Cmd - d_Feed);
	//d_CompleteVal = d_Dev;

	if (d_CompleteVal < d_AllowPos) //����
	{//����������� ������ ���� 
		d_Get_DevPos[0] = d_Cmd; d_Get_DevPos[1] = d_Feed; d_Get_DevPos[2] = d_Dev; 
		 nRet = BD_GOOD;
	}
	else //if (d_CompleteVal > d_AllowPos) 
	{//���������� �� Ŀ���� ����  
		d_Get_DevPos[0] = d_Cmd; d_Get_DevPos[1] = d_Feed; d_Get_DevPos[2] = d_Dev; 
		//010012 E A "Motor allow position Check Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0012", n_Axis);  
		nRet = BD_ERROR;
		if (mn_errormsg_debug_mode)
		{
		  sprintf(mc_abnormal_msg,"Axis[%d], CMDPOS[%.3f], FEEDPOS[%4.3f], DEVPOS[%4.3f]", n_Axis, d_Cmd, d_Feed, d_Dev);
 		  Debug_File_Create(0, mc_normal_msg);
		}
	}

	return nRet;
}
// ******************************************************************************


// ******************************************************************************
// ���� POWER ���� ���� �Լ�                                                     
//  : ���� �� [0:POWER OFF    1:POWER ON]                                        
// ******************************************************************************
int CComizoaPublic::Get_MotPower(int n_Axis) 
{
	int  nRet = BD_ERROR;
	long dwOnOff=0;

// 	if (mn_simulation_mode == 1)
// 	{
// 		return BD_GOOD;
// 	}

	cmmGnGetServoOn(long(n_Axis), &dwOnOff);	
	if (dwOnOff == cmTRUE)  //1 �Ǵ� cmTRUE //Servo Motor ON
	{
		nRet = BD_GOOD;
	}
	else //0 �Ǵ� cmFALSE //Servo Motor Off
	{
		
		nRet = BD_ERROR;
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� ALARM CLEAR �Լ�                                                         
// -> ����ϴ� ���� ���� �ִ� ����� ���� �Ķ���� �����Ѵ�                      
// ******************************************************************************
int CComizoaPublic::Set_MotAlarmClear(int n_Axis) 
{
	int  nRet = BD_ERROR;

// 	if (mn_simulation_mode == 1)
// 	{
// 		return BD_GOOD;
// 	}

	 nRet = cmmGnPulseAlarmRes(n_Axis, BD_YES, 300, TRUE); //FALSE);
	//nRet = cmmGnPulseAlarmRes(n_Axis, cmFALSE, 300, TRUE); 
	if (nRet == cmERR_NONE)
	{
		nRet = BD_GOOD;
	}
	else
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d]cmmGnPulseAlarmRes return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
		nRet = BD_ERROR;
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� ALARM ���� ���� �Լ�                                                     
// -> ����ϴ� ���� ���� �ִ� ����� ���� �Ķ���� �����Ѵ�                      
//  : ���� �� [0:ALARM NONE    1:ALARM OCCURED]                                  
// ******************************************************************************
int CComizoaPublic::Get_MotAlarmStatus(int n_Axis) 
{
	int  nRet = BD_ERROR;
	long dwMioState=0;
	BOOL bALM_State = 0;

// 	if (mn_simulation_mode == 1)
// 	{//BD_ERROR == �˶��� �߻����� ���� ����
// 		return BD_ERROR;
// 	}

	cmmStReadMioStatuses(n_Axis, &dwMioState);	

	bALM_State = (dwMioState >> cmIOST_ALM) & 0x01;
	if (bALM_State != BD_YES) 
	{//�˶��߻� 
		nRet = BD_GOOD; //�˶��� �߻��� ���� 
	}
	else
	{	//010004 E A "Motor Alarm Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0004", n_Axis);  
		nRet = BD_ERROR; //�˶� �߻����� ���� ����  

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d]cmmStReadMioStatuses return alarm error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� �̵� ���� �Լ�                                                           
// -> nMode     : ���� ���� ��� [0:���� ����    1:���� ����]                    
// -> nAxis     : ������ ���� ��                                                 
// -> wEndCheck : ���� �Ϸ� �˻� ���                                            
//  : [0:�̿Ϸ� �������� �ٸ� ���� ����     1:�Ϸ� �����Ŀ� �ٸ� ���� ����]      
// ******************************************************************************
int CComizoaPublic::Set_MotStop(int n_Mode, int n_Axis) 
{
	int nRet = BD_ERROR;
	int nEndCheck = 0;

// 	if (mn_simulation_mode == 1)
// 	{//BD_ERROR == �˶��� �߻����� ���� ����
// 		return BD_GOOD;
// 	}

	if (n_Mode == 0)  // ���� ���� 
	{
		nRet = cmmSxStop(n_Axis, 0, nEndCheck);
	}
	else             // ��� ����
	{
		nRet = cmmSxStopEmg(n_Axis);
	}

	if (nRet == cmERR_NONE)
	{
		nRet = BD_GOOD;
	}
	else
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmSxStop return alarm error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}

		nRet = BD_ERROR;
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� Ư�� ���� ���� ��ġ ���� �Լ�                                            
// -> �� �Լ������� ���� �Լ� ���� ���� �Ϸ� ���� �˻����� �ʵ��� �Ѵ�           
//  : ���� ������ ����� �� �ִ� ���߿� [0�̳� -] ��� ���ԵǱ� �����̴�         
//  : �Լ� ���� ���� �� [-]�� ���ϵǴ��� �� ���� ��ġ������ ���صɼ� �ֱ� ���� 
// ******************************************************************************
double CComizoaPublic::Get_MotCurrentPos(int n_Axis) 
{
	int    nRet = BD_ERROR;
	double dGetActualPos = 0;

// 	if (mn_simulation_mode == 1)
// 	{//BD_ERROR == �˶��� �߻����� ���� ����
// 		return BD_GOOD;
// 	}

	nRet = cmmStGetPosition(n_Axis, cmCNT_FEED, &dGetActualPos);
	if (nRet == cmERR_NONE)
	{
		return dGetActualPos;  // ���� ��ġ ���� 
	}
	else
	{
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmStGetPosition return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
		nRet = BD_ERROR;
	}

	return (double)nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� �̵� ��ġ ���� ���� �˻� �Լ�                                            
// -> nAxis     : ���� ��ġ �˻��� Ư�� ��                                       
// -> dDistance : ���� ���� ��ġ                                                 
// -> nRange    : ���� ��ġ ��� ���� ����                                       
// ******************************************************************************
int CComizoaPublic::Check_MotPosRange(int n_Axis, double d_Distance, double d_Range) 
{
	int    nRet = BD_ERROR;
	double dGetActualPos=0;
	double dP = 0, dN = 0;

// 	if (mn_simulation_mode == 1)
// 	{//BD_ERROR == �˶��� �߻����� ���� ����
// 		return BD_GOOD;
// 	}

	dN = (double)d_Distance - (double)(d_Range); 
	dP = (double)d_Distance + (double)(d_Range);

//	dGetActualPos = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ� 
	dGetActualPos = g_comiMgr.Get_MotCurrentPos(n_Axis);

	if (dGetActualPos >= dN && dGetActualPos <= dP) 	 
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
	}

	return nRet;
}
// ******************************************************************************



// ******************************************************************************
// ���� INPOSITION �˻� �Լ�                                                     
// -> �������� ��� �ñ׳� ON �����ϸ� �ñ׳� OFF�̴�                            
// ******************************************************************************
int CComizoaPublic::Get_MotInposition(int n_Axis) 
{
	int nRet = BD_ERROR;
	long lMioState = 0;
	BOOL bInPos_State = 0;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	nRet = cmmStReadMioStatuses(n_Axis, &lMioState);
	if (nRet == cmERR_NONE)
	{
		bInPos_State = (lMioState >> cmIOST_INP) & 0x01;
		if (bInPos_State == BD_YES)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}		
	}
	else
	{
		nRet = BD_ERROR;
	}
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� �̵� �Ϸ� �˻� �Լ�                                                      
// -> iMotionDone : [0:���� �Ϸ�    1:���� ��]                                   
// -> �˶� �߻� �� INPOSITION �ñ׳��� �߻����� �ʴ´�                           
// ******************************************************************************
int CComizoaPublic::Get_MotMotionDone(int n_Axis, int n_Mode) 
{
	int  nRet = BD_ERROR, nRet_2 =0 ;
	int  nInposition = 0, nMotionDone = -1;
	long dwMotionDone=0;
	int  nServo_On=0;
	double dCurrPos=0;

	long dwMioState=0;
	long dwMotionStatus[3]={0,0,0};
	BOOL bINPO_State = false;

// 	if (mn_simulation_mode == 1)
// 	{ 
// 		return BD_GOOD;
// 	}

	cmmStReadMioStatuses(n_Axis, &dwMioState);
	bINPO_State = (dwMioState >> cmIOST_INP) & 0x01;

	nRet_2 = cmmSxIsDone(n_Axis, &dwMotionDone);			// Motion Done�̳�?

	if (nRet_2 == cmERR_NONE)
	{
		if (n_Mode == -1)
		{
			if (dwMotionDone == cmTRUE && bINPO_State == cmTRUE) //2009.7.11 james ���� �̹� cmmSxIsDone ���� üũ && INPO_State == cmTRUE) 
			{
				nRet = BD_GOOD;
			}
			else
			{
				nRet = BD_PROCEED;
			}
		}
		else			// Inposition�� ���� ������...
		{
			if (dwMotionDone == cmTRUE)
			{
				nRet = BD_GOOD;
			}
			else
			{
				nRet = BD_PROCEED;
			}
		}
	}
	else 
	{//���� ���� �����϶� 
		//010013 E A "Motor motion done Check Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0013", n_Axis);  
		cmmSxStopEmg(n_Axis);

		//2011.0105 cmmSxStopEmg(n_Axis);				
		nRet = BD_ERROR;

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmSxIsDone return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
		//}	
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� ZERO BIT �˻� �Լ�                                                       
// -> ���� HOMING �� ���Ǵ� �Լ�                                               
//  : HOMING ������ ����Ǹ� �ش� BIT�� 1�� �����ȴ�                             
// ******************************************************************************
int CComizoaPublic::Get_MotMotionZeroReturn(int n_Axis) 
{
	int nRet = BD_ERROR;
	long dwMioState =0;
	BOOL bORG_State = BD_ERROR;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}


	cmmStReadMioStatuses(n_Axis, &dwMioState);
	
	bORG_State = (dwMioState >> cmIOST_ORG) & 0x01;

	if (bORG_State == BD_YES)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� ���� ���� ���� �Լ� [EL(+)    EL(-)    HOME]                             
// -> ���� �÷��� [0:�̰���    1:����]                                           
// ******************************************************************************
int CComizoaPublic::Get_MotIOSensor(int n_Axis, int n_MotSensor, int n_OnOff) 
{
	int nRet = BD_ERROR;
	BOOL bELN_State = 0;
	BOOL bELP_State = 0;
	BOOL bORG_State = 0;
	BOOL bSD_State = 0; //2011.0105 
	long dwMioState = 0;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return n_OnOff;
// 	}

	cmmStReadMioStatuses(n_Axis, &dwMioState);	
	switch(n_MotSensor)
	{
	case MOT_SENS_ELM :  // EL[-] 
		bELN_State = (dwMioState >> cmIOST_ELN) & 0x01;
		if (bELN_State == BD_YES)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}
		break;

	case MOT_SENS_ELP :  // EL[+] 
		bELP_State = (dwMioState >> cmIOST_ELP) & 0x01;
		if (bELP_State == BD_YES)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}
		break;

	case MOT_SENS_HOME :
		bORG_State = (dwMioState >> cmIOST_ORG) & 0x01;
		if (bORG_State == BD_YES)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}
		break;

	case MOT_SENS_SD : //2011.0105 james SD���� ���� �߰� 
		bSD_State = (dwMioState >> cmIOST_SD) & 0x01;
		if (bSD_State == BD_YES)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}
		break;

	default :
		nRet = BD_ERROR; //MOT_INVALID_PARAMETER_NUM;
		break;
	}

	return nRet;
}
// ******************************************************************************



int CComizoaPublic::Set_MotInitSpeed(int n_Axis, double d_work)
{
	cmmSxOptSetIniSpeed(n_Axis, d_work);
	return BD_GOOD;
}

//������ �ӵ� ��� ������ ���Ѵ�(Min ~ Max)
int CComizoaPublic::Set_SpeedRange(int n_Axis, double d_max_pps) //2011.1104 
{//������ �ּ� ~ �ִ� �ӵ��� �����մϴ�.
	//10(min) ~ 655350(max) pps ���� �� 
	// �ִ밪 ������ ���� �ּҰ��� �ڵ� ��� 
	cmmSxOptSetIniSpeed(n_Axis, d_max_pps);
	return BD_GOOD;
}


int CComizoaPublic::Set_HomeSetConfig(int n_Axis, int n_mode, int n_ezcount, int n_revvel, int n_escdist)
{
	int  nRet = BD_ERROR, nFlag = 0;
	int nErrAxis, nErrReason;
// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	nFlag = cmmHomeSetConfig(n_Axis, n_mode, n_ezcount, n_escdist, 0);

	if (nFlag == cmERR_NONE)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nErrAxis = cmmErrParseAxis(nRet);
		nErrReason = cmmErrParseReason(nRet);
		nRet = BD_ERROR;

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmHomeSetConfig return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
	}

	return nRet;
}

int CComizoaPublic::Set_MotHomeSpeed(int n_Axis, double d_work, double d_accel, double d_decel)
{
	int  nRet = BD_ERROR, nFlag = 0;
	int nErrAxis, nErrReason;

// 	if (mn_simulation_mode == 1)
// 	{
// 		return BD_GOOD;
// 	}

	nFlag = cmmHomeSetSpeedPattern(n_Axis, cmSMODE_T, d_work, d_accel, d_decel, 5000);
	
	if (nFlag == cmERR_NONE)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nErrAxis = cmmErrParseAxis(nRet);
		nErrReason = cmmErrParseReason(nRet);
		nRet = BD_ERROR;

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmHomeSetSpeedPattern return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
	}
	return nRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//�ӵ� �������̵� 
///////////////////////////////////////////////////////////////////////////////////////////////
int CComizoaPublic::Set_Override_Speed(int n_Axis, double d_Speed, int n_SpeedMode)  
{
	int  nRet = BD_ERROR, nFlag = 0;
	
	nFlag = cmmCfgSetSpeedPattern_T(n_Axis, n_SpeedMode, d_Speed, md_spd_vel[n_Axis][1], md_spd_vel[n_Axis][2]);
	
	if (nFlag == cmERR_NONE)
	{
		if (cmmOverrideSpeedSet((long)n_Axis) == cmERR_NONE)
		{
			nRet = BD_GOOD;
		}
		else
		{
			nRet = BD_ERROR;
		}
	}
	else
	{
		nRet = BD_ERROR;
	}
	
	return nRet;
}

int CComizoaPublic::Set_MotUnitSpeed(int n_Axis, double n_UnitSpeed) //2011.1104 �߰� 
{
	int  nRet = BD_ERROR, nFlag = 0;

	//1mm/�̵��Ÿ� => 1mm �̵��ϴµ� 1000pulse�� �ʿ��ϸ� ������ ���� cmmCfgSetUnitSpeed(n_Axis, 1000); �ϸ� �ȴ�
	
	//�ʴ� 50mm�� �̵��Ϸ��� ������ ���� �����ϸ� �ȴ� 
	// cmmCfgSetSpeedPattern(n_axis, cmSMODE_C, 50, 0,0);
	// cmmSxMove(n_axis, 10); //50mm/sec�� �ӵ��� 10mm �̵�
	
	
	nFlag = cmmCfgSetUnitSpeed(n_Axis, n_UnitSpeed);

	if (nFlag == cmERR_NONE) 
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmCfgSetUnitSpeed return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
	}
	
	return nRet;
}

// ******************************************************************************
// ���� �ӵ� ���� �Լ�                                                           
// -> nAxis      : ���� �ӵ� ������ Ư�� ��                                      
// -> nCommand   : ������ ���� �ӵ� ���� [ACC/DEC/JOG ��]                        
// -> lParaValue : ������ ���� �ӵ�                                              
// ******************************************************************************
int CComizoaPublic::Set_MotSpeed(int n_SpeedCase, int n_Axis, int n_SpeedMode, double d_work, double d_accel_time, double d_decel_time) 
{
	int  nRet = BD_ERROR;
	double dVel = 0, dAccPPS = 0, dDecPPS = 0;
	int nLimit_Time = 1;

	//n_SpeedCase => MOT_SPD_CM_CTL:�ӵ��� cm�� �����Ѵ�, MOT_SPD_RPM_CTL: �ӵ��� rpm���� ���� 
	//�����δ� ���� / ���� ���� ms ������ �޿� �����̴� ������ ���� 

	/////////////////////////////////////////////////////////////////////////////////////////////
	// MAX Accel / Decel Time ���� 
	/////////////////////////////////////////////////////////////////////////////////////////////
	if (d_accel_time < 10) //min 10 ms ���� �۰� �������� �̷�� ���� �ⱸ�� ���� ������ �����Ѵ� 
	{
		d_accel_time = 50; //50 ms
	}
	else if (d_accel_time > 1000) //max
	{
		d_accel_time = 1000;
	}

	if (d_decel_time < 10) //50 ms ���� �۰� �������� �̷�� ���� �ⱸ�� ���� ������ �����Ѵ� 
	{
		d_decel_time = 50;
	}
	else if (d_decel_time > 1000)//max
	{
		d_decel_time = 1000;
	}

	if (n_SpeedCase == MOT_SPD_CM_CTL)		// �̵� �ӵ� ������ �ʴ� ��ġ����(cm/sec)�� ����� ����Ѵ� 
	{	
		if (d_work < 1 || d_work > 2000)	// 1:�ʴ� 1cm , max:�ʴ� 2000cm �̵� �Ѱ� ����
		{
			d_work = 10;
		}
	}
	else
	{

	}
	
	n_SpeedMode = cmSMODE_S; //���۸�� ���� 

	if (n_SpeedCase == MOT_SPD_ORG ) //Ȩüũ�� ���ۼӵ� ���� 
	{			 
		//cmSMODE_KEEP=-1/* Keep previous setting*/, cmSMODE_C=0 /*Constant */, cmSMODE_T /*Trapeziodal*/, cmSMODE_S /*S-curve*/
		if (d_work > 200) // �ִ� Ȩ üũ �ӵ��� �����Ѵ� 
		{	
			d_work = 2;
		}

		nRet = cmmHomeSetSpeedPattern_T(n_Axis, cmSMODE_S, d_work, d_accel_time/(double)1000, d_decel_time/(double)1000, 1);//2011.0122 1000);

		if (nRet == cmERR_NONE)
		{			
			nRet = BD_GOOD;
		}
		else
		{
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis %d] cmmHomeSetSpeedPattern_T return error", n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			}
			nRet = BD_ERROR;
		}
	}
	else //�����۽� �ӵ����ø�� 
	{
		if (mn_run_status == CTL_dRUN)
		{
			if (mn_runspeed_rate < 10) mn_runspeed_rate = 10;
			dVel = d_work * (double)(((double)mn_runspeed_rate / (double)100)); //d_work //2012,1208
		}
		else
		{
			if (mn_manualspeed_rate < 10) mn_manualspeed_rate = 10;
			dVel = d_work * (double)(((double)mn_manualspeed_rate / (double)100)); //d_work
		}
	 
		if (dVel > 1000)
		{
			dVel = 1000;
		}

//		nRet = cmmCfgSetSpeedPattern_T(n_Axis, n_SpeedMode, dVel, d_accel_time/(double)1000, d_decel_time/(double)1000);//2011.0122 1000);
		nRet = g_comiMgr._cmmCfgSetSpeedPattern_T(n_Axis, n_SpeedMode, dVel, d_accel_time/(double)1000, d_decel_time/(double)1000);

        if (nRet == cmERR_NONE)
		{
			nRet = BD_GOOD;
		}
		else
		{
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis %d] cmmCfgSetSpeedPattern_T return error", n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			}
			nRet = BD_ERROR;
		}
	}

	return nRet;
}

int CComizoaPublic::Set_MotSpeed_Ratio(int n_Axis, int n_SpeedMode, double d_work_Ratio, double d_accel_Ratio, double d_decel_Ratio) 
{
	int  nRet = BD_ERROR;

	if (d_work_Ratio > 100 || d_work_Ratio < 10)
	{
		d_work_Ratio = 10;
	}
	
	if (d_accel_Ratio > 100 || d_accel_Ratio < 10)
	{
		d_accel_Ratio = 100;
	}
	
	if (d_decel_Ratio > 100 || d_decel_Ratio < 10)
	{
		d_decel_Ratio = 100;
	}

	cmmSxSetSpeedRatio(n_Axis, n_SpeedMode, d_work_Ratio, d_accel_Ratio, d_decel_Ratio);

	nRet = BD_GOOD;
	return nRet;
}
// ******************************************************************************

int CComizoaPublic::Set_MotUnitDist(int n_Axis, double n_UnitDist)
{
	int  nRet = BD_ERROR, nFlag = 0;
	
	nFlag = cmmCfgSetUnitDist(n_Axis, n_UnitDist);
	if (nFlag == cmERR_NONE) 
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] cmmCfgSetUnitDist return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
	}
	
	return nRet;
}

///////////////////////////////////////////////////////////////////////////////////
///// interrupt //////
///////////////////////////////////////////////////////////////////////////////////
int CComizoaPublic::Set_InterruptSetup(int n_Enable, int n_InterruptType)
{// ��� ���ο��� �����ؾ� �Ѵ� mainfrm.cpp���� �ۼ��ؾ� �� 
	int  nRet = BD_ERROR, nFlag = 0;


	if (n_Enable == BD_NO)
	{
		cmmIntHandlerEnable(FALSE); // Disable Interrupt Handling
		return BD_GOOD;
	}

	switch(n_InterruptType)
	{
	case cmIHT_MESSAGE: 
//		cmmIntHandlerSetup(cmIHT_MESSAGE, GetSafeHwnd(), WMU_MotInterrupt, this);
		break;
	case cmIHT_EVENT:
//		cmmIntHandlerSetup(cmIHT_EVENT, g_hEvent, 0, 0);
		break;
	case cmIHT_CALLBACK: 
//		cmmIntHandlerSetup(cmIHT_CALLBACK, InterruptCallback, WMU_MotInterrupt, this);
		break;
	}
	cmmIntHandlerEnable(TRUE); // Enable Interrupt Handling
// 
	return BD_GOOD;
}

int CComizoaPublic::Set_InterruptMask(int n_Axis, long l_Set_InterruptMask[20])
{//cmmIntSetMask
	int  nRet = BD_ERROR, nFlag = 0;
	int  i;
	long lMapMask = 0;
/*
	"Normal Stop", // 0
	"Succesive start", // 1
	"", // 2
	"", // 3
	"Start of acceleration", //4
	"End of acceleration", // 5
	"Start of deceleration", // 6
	"End of deceleration", // 7
	"", // 8
	"", // 9
	"Position error tolerance exceed", // 10
	"General Comparator", // 11
	"Compared trigger", // 12
	"CLR signal resets the counter value", // 13
	"LTC input making counter value latched", // 14
	"ORG input signal ON", // 15
	"SD input signal ON", // 16
	"+DR input changes", // 17
	"-DR input changes" // 18
*/	

	for(i=0; i<19; i++) //i=�ִ� 0~18���� 19���� �� 
	{	
		if (l_Set_InterruptMask[i] == BD_YES)
		{
			lMapMask = lMapMask | (long)pow(2, i);
		}
	}

	nFlag = cmmIntSetMask(n_Axis, lMapMask);
	if (nFlag == cmERR_NONE)
	{

		//lMapMask = 0;
		//cmmIntGetMask(n_Axis, &lMapMask);
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
	}
	
	return nRet;
}

int CComizoaPublic::Get_InterruptEventData(int n_MaxAxis, long l_Get_InterruptMask[20])
{//cmmIntSetMask
	int  nRet = BD_ERROR, nFlag = 0, i;
	long dwErrState=0, dwEvtState=0;
	long dwFlag1=0, dwFlag2=0;
	int nAxis = 0;
/*
	"Normal Stop", // 0
	"Succesive start", // 1
	"", // 2
	"", // 3
	"Start of acceleration", //4
	"End of acceleration", // 5
	"Start of deceleration", // 6
	"End of deceleration", // 7
	"", // 8
	"", // 9
	"Position error tolerance exceed", // 10
	"General Comparator", // 11
	"Compared trigger", // 12
	"CLR signal resets the counter value", // 13
	"LTC input making counter value latched", // 14
	"ORG input signal ON", // 15
	"SD input signal ON", // 16
	"+DR input changes", // 17
	"-DR input changes" // 18
*/	
	//�ش����� Interrupt�� �߻��ߴ��� Ȯ�� 
	cmmIntReadFlag(&dwFlag1, &dwFlag2);

	//���ͷ�Ʈ�� �� ���̶� �߻� �ߴ��� Ȯ���Ѵ� 
	if (n_MaxAxis >= 62 || (dwFlag1 < 1 && dwFlag2 < 1) ) //��� ���͵� ���ͷ�Ʈ�� �߻����� �ʾҴ�
	{
		return BD_ERROR;		
	}

	//������� ���ͷ�Ʈ�� �߻��ߴ��� Ȯ���Ѵ� 
	for(i=0; i<n_MaxAxis; i++)
	{
		if (dwFlag1 < 32) //0qjs ahxj ~ 31�� ���ͱ��� �� 32�࿡ ���� ���ͷ�Ʈ Ȯ�� ���� 
		{
			if (dwFlag1 == pow(2, i)) //pow(2, i) �߻��� �������� ��ȣ�� �� 
			{
				nAxis = i;
				break;
			}
		}
		else  //32�� ���� ~ 63�� ���ͱ��� �� 32�࿡ ���� ���ͷ�Ʈ Ȯ�� ���� 
		{
			if (dwFlag1 == pow(2, i)) //pow(2, i) �߻��� �������� ��ȣ�� �� 
			{
				nAxis = i;
				break;
			}
		}
	}

	if (mn_interrupt_flag[nAxis] != BD_YES) //���ͷ�Ʈ�� ����� ���͸� ���ͷ�Ʈ �߻� ���θ� üũ 
	{
		return BD_PROCEED; //BD_GOOD;
	}
	
	//���ͷ�Ʈ ���� ���� Ȯ�� 
	if (cmmIntReadErrorStatus(nAxis, &dwErrState) == cmERR_NONE && dwErrState < 0)
	{//�����߻� 
		return BD_ERROR;	//������� �ʾƵ� �ȴ� 		
	}
	
	// � Event Interrupt�� �߻��Ͽ����� üũ //
	if (cmmIntReadEventStatus(nAxis, &dwEvtState) == cmERR_NONE  && dwEvtState != 0)
	{
		for(i=0; i<20; i++) // Event interrupt�� ���°��� b0 ~ b19 ��Ʈ�� ����Ѵ�.
		{ 		
			ml_Get_InterruptMask[nAxis][i] = BD_NO;
			if (cmmGetBit(dwEvtState, i))
			{
				ml_Get_InterruptMask[nAxis][i] = BD_YES;  			
			}		 
		}		 
	}

/*	//��� �� ���°� �ƴϸ� ���ͷ�Ʈ ��ŵ �� ���� �ִµ� �̶��� ���ͷ�Ʈ�� ������� �� ����  
	if (st_handler.n_run_status != CTL_dRUN)
	{
		//return ; //BD_ERROR
	}
*/
	//���� ����ϴ� �񱳹��� üũ�Ѵ� 
	if (ml_Get_InterruptMask[nAxis][12] == BD_YES) //CMP ��� üũ, CMP��ġ ���ͷ�Ʈ�� ������ġ �̻����� �̵��ϸ� �߻�  
	{
/*
		if (nAxis == M_DCLDRBT_Y)
		{
			st_sync.n_DCUldRbt_TestSiteMoveEnable_Flag = BD_YES; //�� �÷��״� ���� st_motor[nAxis].l_Get_InterruptMask[x]�� ��ü���� 
		}
		else if (nAxis == M_DCULDRBT_Y) 
		{
			st_sync.n_DCLdRbt_TestSiteMoveEnable_Flag = BD_YES;  //�� �÷��״� ���� st_motor[nAxis].l_Get_InterruptMask[x]�� ��ü���� 					
		}		
		else if (nAxis == M_INSERTRBT_Y) 
		{
			st_motor[nAxis].l_Get_InterruptMask[12] = BD_YES;  //�� �÷��״� ���� st_motor[nAxis].l_Get_InterruptMask[x]�� ��ü���� 					
		}	 
		else if (nAxis == M_REMOVERBT_Y) 
		{
			st_motor[nAxis].l_Get_InterruptMask[12] = BD_YES;  //�� �÷��״� ���� st_motor[nAxis].l_Get_InterruptMask[x]�� ��ü���� 					
		}
*/
		return BD_GOOD; 
	}	 
	return BD_PROCEED;	
}

int CComizoaPublic::Get_InterruptFlag(int n_Axis)
{
	int  nRet = BD_ERROR, nFlag = 0;
	long dwFlag1, dwFlag2;

	cmmIntReadFlag(&dwFlag1, &dwFlag2);

	if (n_Axis < 32)
	{
		nFlag = cmmGetBit(dwFlag1, n_Axis);
	}
	else
	{
		nFlag = cmmGetBit(dwFlag2, (n_Axis - 32));
	}

	return nFlag; //�ش� ���� ���ͷ�Ʈ�� �߻������� TRUE(BD_YES) ���� 
}

///////////////////////////////////////////////////////////////////////////////////////
// ONE POINT COMPARE POSITION SETTING
///////////////////////////////////////////////////////////////////////////////////////
int CComizoaPublic::Set_TriggerSet_OneCompareConfig(int n_Axis, int n_Source, int n_Method, double d_ComparePosition)
{ 
	int  nRet = BD_GOOD, nFlag = 0;

	//n_Mode : 	szCompareSource[4][50] = { 
		//0				"COMMAND Counter",
		//1				"Feedback Counter",
		//2			    "Deviation Counter",
		//3			    "General Counter"

	//CHAR szCompareMethod[6][50] = {
		//0				"Disable",
		//1				"CMP == COUNTER (No direction)",
		//2				"CMP == COUNTER (Only when counting up)",
		//3				"CMP == COUNTER (Only when counting down)",
		//4				"CMP > COUNTER",
		//5				"CMP < COUNTER"
 

	//n_Type : 
	//case ONE_POINT_TRIGGER :
	//case REGULAR_INTERVAL_POINT :
	//case VOLUNTARY_INTERVAL_POINT :

//TCmCntr {cmCNT_COMM/*Command*/, cmCNT_FEED/*Feedback*/, cmCNT_DEV/*Deviation*/,cmCNT_GEN/*General*/, cmCNT_REM/*Remained*/

	nFlag = cmmCmpTrgSetConfig(n_Axis, n_Source, n_Method); //cmmCmpTrgSetConfig) (long Axis, long CmpSrc, long CmpMethod);
	if (nFlag != cmERR_NONE)
	{
		nRet = BD_ERROR; 
	}

	nFlag = cmmCmpTrgSetOneData(n_Axis, d_ComparePosition);
	if (nFlag != cmERR_NONE)
	{
		nRet = BD_ERROR; 
	}

	return nRet;
}
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Pick & Place ���� ���� ���� �̵��Ͽ� �������� List Motiom 
// 2008.9.1 James lee
////////////////////////////////////////////////////////////
int CComizoaPublic::Create_LmIndexMapAxis(long n_MapIndex, long n_AxisCount, long *np_AxisNum) //�ִ� 4����� ����� �� �ֵ��� ���� 
{////Lm������ n_MapIndexNum �� �ִ� 0 ~ 15���� �� 
	int  nRet = BD_ERROR, nFlag = 0, i;
	long nMapMask_1 = 0, nMapMask_2 = 0;
	//char cJamcode[10] = {NULL};

	for(i=0; i<n_AxisCount; i++) //i=�ִ� 0~4���� 4���� �� 
	{			
		if (np_AxisNum[i] <= 31) nMapMask_1 = nMapMask_1 | (long)pow(2, np_AxisNum[i]);
		else				    nMapMask_2 = nMapMask_2 | (long)pow(2, np_AxisNum[i]);	 
	}

	nFlag = cmmLmMapAxes(n_MapIndex, nMapMask_1, nMapMask_2); //Map index ��ȣ�� �ݵ��� 0~15������ �����̾�� �Ѵ�
	if (nFlag == cmERR_NONE)
	{
		nRet = BD_GOOD; //st_coordmot[n_MapIndex].n_indexmap_init = BD_YES;;
	}
	else
	{
		nRet = BD_ERROR; 

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[n_MapIndex %d] cmmLmMapAxes return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
	}

	return nRet;
}

int CComizoaPublic::Create_IxIndexMapAxis(long n_MapIndex, long n_AxisCount, long *np_AxisNum) //�ִ� 4����� ����� �� �ֵ��� ���� 
{////Ix������ n_MapIndexNum �� �ִ� 0 ~ 7���� �� 
	int  nRet = BD_ERROR, nFlag = 0, i;
	long nMapMask_1 = 0, nMapMask_2 = 0;
	//char cJamcode[10] = {NULL};

	for(i=0; i<n_AxisCount; i++) //i=�ִ� 0~3���� 4���� �� 
	{			
		if (np_AxisNum[i] <= 31)  nMapMask_1 = nMapMask_1 | (long)pow(2, np_AxisNum[i]);
		else					 nMapMask_2 = nMapMask_2 | (long)pow(2, np_AxisNum[i]);	 
	}

	nFlag = cmmIxMapAxes(n_MapIndex, nMapMask_1, nMapMask_2); //Map index ��ȣ�� �ݵ�� 0~7������ �����̾�� �Ѵ� 
	if (nFlag == cmERR_NONE)
	{
		nRet = BD_GOOD; //st_linearmot[n_MapIndex].n_indexmap_init = BD_YES;
	}
	else
	{
		nRet = BD_ERROR; 

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[n_MapIndex %d] cmmIxMapAxes return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
	}
	return nRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//��ġ �������̵� 
///////////////////////////////////////////////////////////////////////////////////////////////
int CComizoaPublic::Set_Override_Move_Pos(int n_Axis, double d_TargetPos)  
{
	int  nRet = BD_ERROR, nFlag = 0;
	long lp_OverrideFlag = 0; 

	lp_OverrideFlag = 0; 
	nFlag = cmmOverrideMoveTo(n_Axis, d_TargetPos, &lp_OverrideFlag);
	if (nFlag == cmERR_NONE && lp_OverrideFlag == 0)  
	{
		if (lp_OverrideFlag == 0) //1:���� ����, 0:����ȵ� //��ǥ ��ġ �� �������̵� 
		{
			nRet = BD_GOOD;
		}
	}
	else
	{

	}

	return nRet;
}




// ******************************************************************************
// ���� �̵� �Լ�                                                                
// -> int nAxis        : ���ǵ� ���� ID ��ȣ                                     
// -> int nRunMode     : ���� MOVE ��� [1:RUN MODE  2:MANUAL MODE]              
// -> double dDistance : ���� �̵� �Ÿ�                                          
// -> double dVelocity : ���� VEL �ӵ�                                           
// ******************************************************************************

//2015.0326 james ���� 
int CComizoaPublic::Start_SingleMove(int n_Axis, double d_Distance, int n_SpeedRatio) // (int ratio = 100) //2011.0105 ���� 
{
	int  nRet = BD_ERROR, nFlag = 0;
	double d_SpeedVel;
	double dCurrPos = 0;
	long dwMotionDone=0;

//	double dp_Vel[3]; 
	double d_Speed[3];
/*
//	double dRatio[3]; 
	long lErrorCode;
	short int nErrorParseAxis;
	short int nErrorParseReason;
	char cErrorMsg[200];
	CString sMsg;
*/

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	nRet = CTL_Lib.Motor_SafetyCheck(1, n_Axis, d_Distance);

	if (nRet != BD_GOOD)
	{
		if (mn_retry_cnt[n_Axis] < mn_max_retry_cnt) //2011.0201 ���� �߰� 
		{//�ݺ� ������ �����Ѵ� 
			if (mn_retry_cnt[n_Axis] == 0)
			{
				ml_retry_time_wait[n_Axis][0] = GetCurrentTime();
			}

			mn_retry_cnt[n_Axis]++ ;//2011.0224 �߰� 
			return BD_PROCEED;
		}
		else
		{
			ml_retry_time_wait[n_Axis][1] = GetCurrentTime();
			ml_retry_time_wait[n_Axis][2] = ml_retry_time_wait[n_Axis][1] - ml_retry_time_wait[n_Axis][0];
			if (ml_retry_time_wait[n_Axis][2] < mn_max_move_limit_time/10) //3�� ���� �ϋ��� �ݺ� ������ �Ѵ� 
			{
				mn_retry_cnt[n_Axis]++ ;//2011.0224 �߰� 
				return BD_PROCEED;
			}
			else if (ml_retry_time_wait[n_Axis][2] < 0)
			{
				ml_retry_time_wait[n_Axis][0] = GetCurrentTime();
			}
			//�ݺ� Ƚ�� ���� ũ�� ���������� ���� ���� ó�� 
		}

		cmmSxStopEmg(n_Axis); //2009.6.30 �߰� 

		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis %d] SafetyCheck return error", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}

//	nRet = cmmSxIsDone(n_Axis, &dwMotionDone);			// Motion Done�̳�?
	nRet = g_comiMgr._cmmSxIsDone(n_Axis, &dwMotionDone);

	if (nRet == cmERR_NONE)
	{
		if (dwMotionDone != cmTRUE) //��� ���� �Ϸ� == 1, �������� 0
		{			
			cmmSxStopEmg(n_Axis); //091012 �������̸� ���� ��Ű�� �ٽ� �����Ѵ� 
			return BD_RETRY;

			//010013 E A "Motor motion done Check Error(01 motor)."
			sprintf(mc_alarmcode, "%02d0013", n_Axis);  
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[%d] Start_SingleMove cmmSxIsDone Check Error", n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			}

			cmmSxStopEmg(n_Axis);	
			
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis %d] cmmSxIsDone return error", n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			}
			return BD_ERROR;
		}

		nRet = Get_Deviation_Position(n_Axis, (double)md_allow_value[n_Axis], md_deviation[n_Axis]) ; //0.5 mm			
		if (nRet != BD_GOOD)
		{				
			ml_retry_time_wait[n_Axis][1] = GetCurrentTime();
			ml_retry_time_wait[n_Axis][2] = ml_retry_time_wait[n_Axis][1] - ml_retry_time_wait[n_Axis][0];
			
			if (ml_retry_time_wait[n_Axis][2] < 0)
			{
				ml_retry_time_wait[n_Axis][0] = GetCurrentTime();
			}
			if (ml_retry_time_wait[n_Axis][2] < 1000)
			{
				return BD_RETRY;
			}
			
//			dCurrPos = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�
			dCurrPos = g_comiMgr.Get_MotCurrentPos(n_Axis);
			
			/* 2015.0326 james �߿��ϴ�, ��ġ �� ������ �����ϴ� �̰������� ���� ���� 
			cmmStGetPosition(n_Axis, cmCNT_FEED, &dCurrPos);	//���� Ŀ��� ��ġ 
			cmmStSetPosition(n_Axis, cmCNT_COMM, dCurrPos); //���ڵ� ��ġ�� Ŀ��� ��ġ�� ���� ��Ų�� 

			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "Axis=%d, CMDPOS[%4.3f] FEEDPOS[%4.3f]", n_Axis, d_Distance, dCurrPos);
				Debug_File_Create(0, mc_normal_msg);
			}*///2015.0326 james �߿��ϴ� 
		}
	}
	else
	{//�Լ� ���� ���� 
		if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)  
		{			
			cmmSxStopEmg(n_Axis);	

			//010001 E A "Motor Parametor Setting Error(01 motor)."
			sprintf(mc_alarmcode, "%02d0001", n_Axis); 
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[%d] cmmSxIsDone start single_return", n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			}
			//2013,0405
			CTL_Lib.Alarm_Error_Occurrence(3000, CTL_dWARNING, mc_alarmcode);

			return BD_ERROR;
		}
		else
		{
			mn_retry_cnt[n_Axis]++;  
		}
	}
 
/* james test 
	nRet = cmmCfgGetSpeedPattern(n_Axis, &lErrorCode, &dRatio[0], &dRatio[1], &dRatio[2]);
	if (nRet != cmERR_NONE) //james test
	{
		return BD_ERROR;
	}
	cmmSxGetSpeedRatio(n_Axis, &lErrorCode, &dRatio[0], &dRatio[1],&dRatio[2]);
*/

	if (n_SpeedRatio >= 10 && n_SpeedRatio <= 500) //�ּ� 10% ~ 500% ���� �ӵ��� ���� �� �� �ִ� 
	{//d_SpeedRatio = 100, ���õ� �ӵ� 100=100%, 200=200%, 50=50% 
		d_SpeedVel = (double)(md_spd_vel[n_Axis][0] * (double)((n_SpeedRatio) / 100.));//mn_spd_rate_mnu
	}
	else if (n_SpeedRatio >= 0)
	{
		d_SpeedVel = (double)(md_spd_vel[n_Axis][0] * 0.1); //10% �ӵ��� ����Ʈ ���� 
	}
	else //if (n_SpeedRatio < 0 && n_SpeedRatio < -500)
	{//- ���� ������ ������ / ���� ���� �����Ѵ� 
		d_SpeedVel = (double)(md_spd_vel[n_Axis][0] / abs(n_SpeedRatio));
	}
	
	d_Speed[0] = d_SpeedVel; d_Speed[1] = md_spd_vel[n_Axis][1]; d_Speed[2] = md_spd_vel[n_Axis][2];
	
	if (d_Speed[0] < 0) //�ӵ��� �̰����� ������ ������ �ӵ��� �̵����� 
	{	//�̹� õõ�� �����̴� �ӵ� 
		d_Speed[0] = 10; //2015.0326 james �ӵ��� �ʹ� ���� ������ �ɼ� �־� 10 ���� ���� 1; //d_SpeedVel;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//V_0.1.1 nRet = Set_MotSpeed(MOT_SPD_VEL, n_Axis, cmSMODE_T, dp_SpeedVel, st_motor[n_Axis].d_spd_vel[1], st_motor[n_Axis].d_spd_vel[2]);
	nRet = Set_MotSpeed(MOT_SPD_VEL, n_Axis, cmSMODE_S, d_Speed[0], d_Speed[1], d_Speed[2]); //V_0.1.1 
	if (nRet == BD_ERROR)
	{
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", n_Axis); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] Set_MotSpeed start single_return", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		} 
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3001, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

//	nRet = cmmSxSetSpeedRatio(n_Axis, cmSMODE_T, 100,100,100); //cmSMODE_KEEP, 100, 100, 100);	
	nRet = g_comiMgr._cmmSxSetSpeedRatio(n_Axis, cmSMODE_S, 100,100,100); //cmSMODE_KEEP, 100, 100, 100);
	if (nRet == BD_ERROR)
	{
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", n_Axis); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmSxSetSpeedRatio start single_return", n_Axis);
			Debug_File_Create(0, mc_normal_msg);
		} 
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3002, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

	
	// 2016/08/16///////////////////////////////////////////////////////////////
// 	if( m_iAxisDelayFlag[n_Axis] == 0 )
// 	{
// 		m_iAxisDelayFlag[n_Axis] = 1;
// 		m_dwAxisDelayTime[n_Axis] = GetCurrentTime();
// 		return BD_PROCEED;
// 	}
// 	else if( m_iAxisDelayFlag[n_Axis] == 1 )
// 	{
// 		if( GetCurrentTime() - m_dwAxisDelayTime[n_Axis] > 100 )
// 		{
// 			m_iAxisDelayFlag[n_Axis] = 2;
// 		}
// 		else if( GetCurrentTime() - m_dwAxisDelayTime[n_Axis] < 0 )
// 		{
// 			m_dwAxisDelayTime[n_Axis] = GetCurrentTime();
// 		}
// 		return BD_PROCEED;
// 	}
// 
// 	m_iAxisDelayFlag[n_Axis] = 2;
	


//	nRet = cmmSxMoveToStart(n_Axis, d_Distance);
	nRet = g_comiMgr._cmmSxMoveToStart(n_Axis, d_Distance);

	if (nRet == cmERR_NONE)
	{
		ml_motion_move_time[n_Axis][0] = GetCurrentTime();
		
		if (mn_run_status == CTL_dRUN)	//090825 handler�� ���󰡵����϶��� Ŀ��� �����͸� ���, �޴��� ������ ��ŵ 
		{
			md_cmdpos_backup[n_Axis] = d_Distance;
		}

		mn_interrupt_flag[n_Axis] = BD_NO;
		return BD_GOOD;
	}
	else
	{
/* james test 
		nRet = cmmCfgGetSpeedPattern(n_Axis, &lErrorCode, &dRatio[0], &dRatio[1], &dRatio[2]);
		if (nRet != cmERR_NONE) //james test
		{
			return BD_ERROR;
		}
		cmmSxGetSpeedRatio(n_Axis, &lErrorCode, &dRatio[0], &dRatio[1],&dRatio[2]);
*/
		
		nRet = Get_Deviation_Position(n_Axis, (double)md_allow_value[n_Axis], md_deviation[n_Axis])  ; //0.5 mm
		if (nRet == BD_ERROR)
		{		
			if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)  
			{
				//010002 E A "Motor Move Setting Error01 motor)."
				sprintf(mc_alarmcode, "%02d0002", n_Axis); 
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[%d] Target= %4.3f, CmdPos= %4.3f, FeedPos=%4.3f", n_Axis, d_Distance, md_deviation[n_Axis][0], md_deviation[n_Axis][1]);
					Debug_File_Create(0, mc_normal_msg);
				} 
//				dCurrPos = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�	
				dCurrPos = g_comiMgr.Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�	

				cmmSxStopEmg(n_Axis);
				
				mn_retry_cnt[n_Axis] = 0;

				//2013,0405
				CTL_Lib.Alarm_Error_Occurrence(3003, CTL_dWARNING, mc_alarmcode);
				return BD_ERROR;
			}
			else
			{
				mn_retry_cnt[n_Axis]++ ;
				return BD_RETRY;								
			}			
		}
	/*			 
		lErrorCode = nRet;
		cmmErrGetLastCode(&lErrorCode);						//������ �߻��� ���� �ڵ� Ȯ��  
		nErrorParseAxis = cmmErrParseAxis(lErrorCode);     //������ �߻���Ų �� ������ �����´� 
		nErrorParseReason = cmmErrParseReason(lErrorCode); //error code�� �޴´� 
		cmmErrGetString(lErrorCode, cErrorMsg, 200);
		
		sMsg.Format("Msg=%s", cErrorMsg);
*/

		//010002 E A "Motor Move Setting Error 01 motor)."
		sprintf(mc_alarmcode, "%02d0002", n_Axis); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] Target= %4.3f, CurPos= %4.3f", n_Axis, d_Distance, dCurrPos);
			Debug_File_Create(0, mc_normal_msg);
		} 

//		dCurrPos = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�
		dCurrPos = g_comiMgr.Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�
		cmmSxStopEmg(n_Axis);
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3004, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

	return BD_ERROR;
}
// ******************************************************************************

// ******************************************************************************
// ���� �̵� ��ġ ���е� �˻� �Լ�                                               
// -> int nAxis        : ���ǵ� ���� ID ��ȣ                                     
// -> double dDistance : ���� �̵� �Ÿ�                                          
// ******************************************************************************
int CComizoaPublic::Check_SingleMove(int n_Axis, double d_Distance)  //2015.0326 james ���� 
{
	int    nRet=0, nRetDone;
	double dCurrPos[4]={0,0,0,0};
	long dwMotionDone=0;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	nRet = CTL_Lib.Motor_SafetyCheck(2, n_Axis, d_Distance);
	if (nRet == BD_ERROR)
	{
		if (mn_retry_cnt[n_Axis] < mn_max_retry_cnt)   
		{//�ݺ� ������ �����Ѵ� 
			if (mn_retry_cnt[n_Axis] == 0)
			{
				ml_retry_time_wait[n_Axis][0] = GetCurrentTime();
			}
			mn_retry_cnt[n_Axis]++ ;//2011.0224 �߰� 
			return BD_PROCEED;
		}
		else
		{
			//�ݺ� Ƚ�� ���� ũ�� ���������� ���� ���� ó�� 
			ml_retry_time_wait[n_Axis][1] = GetCurrentTime();
			ml_retry_time_wait[n_Axis][2] = ml_retry_time_wait[n_Axis][1] - ml_retry_time_wait[n_Axis][0];
			if (ml_retry_time_wait[n_Axis][2] < 0)//2013,0608
			{
				ml_retry_time_wait[n_Axis][0] = GetCurrentTime();
			}
			if (ml_retry_time_wait[n_Axis][2] < 500) //500ms ���� �϶��� �ݺ� ������ �Ѵ� 
			{
				return BD_PROCEED; //2011.0224 �߰� ���� //�켱 ��� ���� return BD_RET_PROCEED;
			}
		}

		mn_retry_cnt[n_Axis] = 0;  
		cmmSxStopEmg(n_Axis);  
		return BD_SAFETY;  
	}	

	//st_motor[n_Axis].d_cmd_feed_allow = 0.1; //0.1.mm �����߻��� ���� üũ 

	ml_motion_move_time[n_Axis][1] = GetCurrentTime();
	ml_motion_move_time[n_Axis][2] = ml_motion_move_time[n_Axis][1] - ml_motion_move_time[n_Axis][0];

	//james test nRet = Get_MotMotionDone(n_Axis);  // ���� �̵� �Ϸ� �˻� �Լ� 
//	nRetDone = cmmSxIsDone(n_Axis, &dwMotionDone);			// Motion Done�̳�?
	nRetDone = g_comiMgr._cmmSxIsDone(n_Axis, &dwMotionDone);

	if (nRetDone == cmERR_NONE)
	{
		if (dwMotionDone == cmTRUE) //��� ���� �Ϸ� == 1, �������� 0
		{	
			if (mn_sd_io_property_flag[n_Axis] == BD_YES) 
			{
				COMI.Set_Motor_IO_Property(n_Axis, cmSD_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
			}
			
			// 2016/08/18//////////////////////////////
			if( n_Axis != 19 )
			{
				nRet = Get_MotInposition( n_Axis );

				if( nRet != BD_GOOD )
					return BD_PROCEED;
			}

			nRet = Check_MotPosRange(n_Axis, d_Distance, md_allow_value[n_Axis]); //(int n_Axis, double d_Distance, int n_Range) 
			if (nRet == BD_GOOD)
			{
				mn_retry_cnt[n_Axis] = 0; 
				return BD_GOOD;// 
			}
			else
			{
				if (ml_motion_move_time[n_Axis][2] > 2000) //2015.0326 james ������ ����Ϸ�Ǿ����� ���� ��ٸ� �ʿ���� (mn_max_move_limit_time/10)) //MOT_MOVE_LIMITTIME) //���� ���� �Ϸ� �����̴� ��ٸ� �ʿ� ���� MOT_MOVE_LIMITTIME)
				{	
					if (mn_sd_io_property_flag[n_Axis] == BD_YES) 
					{
						COMI.Set_Motor_IO_Property(n_Axis, cmSD_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
					}

					
					if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
					{
						mn_retry_cnt[n_Axis] = 0; 

//						dCurrPos[0] = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�		
						dCurrPos[0] = g_comiMgr.Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�

						cmmSxStopEmg(n_Axis);	

						//010002 E A "Motor Move Setting Error 01 motor)."
						sprintf(mc_alarmcode, "%02d0002", n_Axis); 
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[%d] Check_MotPosRange Target= %4.3f, CurPos= %4.3f", n_Axis, d_Distance, dCurrPos[0]);
							Debug_File_Create(0, mc_normal_msg);
						}
						//2013,0405
						CTL_Lib.Alarm_Error_Occurrence(3010, CTL_dWARNING, mc_alarmcode);

						return BD_ERROR;
					}
					else
					{
						mn_retry_cnt[n_Axis]++ ;
						return BD_RETRY;								
					}
				}
				else if (ml_motion_move_time[n_Axis][2] < 0)
				{
					ml_motion_move_time[n_Axis][0] = GetCurrentTime();
				}
			}
		}
		else 
		{//���Ͱ� ���� �̵����϶��� �����ҋ����� ��ٸ��� 
			if (ml_motion_move_time[n_Axis][2] > mn_max_move_limit_time)
			{			
				if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
				{
					mn_retry_cnt[n_Axis] = 0; 

//						dCurrPos[0] = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�		
						dCurrPos[0] = g_comiMgr.Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�
						cmmSxStopEmg(n_Axis);	

						//010002 E A "Motor Move Setting Error 01 motor)."
						sprintf(mc_alarmcode, "%02d0002", n_Axis); 
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[%d] Check_MotPosRange Target= %4.3f, CurPos= %4.3f", n_Axis, d_Distance, dCurrPos[0]);
							Debug_File_Create(0, mc_normal_msg);
						} 
						//2013,0405
						CTL_Lib.Alarm_Error_Occurrence(3011, CTL_dWARNING, mc_alarmcode);
						return BD_ERROR;
				}
				else
				{//2011.0305 
					mn_retry_cnt[n_Axis]++ ;
					return BD_RETRY;	
				}
			}	
			else if (ml_motion_move_time[n_Axis][2] < 0)
			{
				ml_motion_move_time[n_Axis][0] = GetCurrentTime();
			}
		}	
	}
	else 
	{//���� ���� �����϶� 
		if (mn_sd_io_property_flag[n_Axis] == BD_YES)
		{
			COMI.Set_Motor_IO_Property(n_Axis, cmSD_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
		}
		

		if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
		{
			mn_retry_cnt[n_Axis] = 0; 

//				dCurrPos[0] = Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�	
				dCurrPos[0] = g_comiMgr.Get_MotCurrentPos(n_Axis);  // ���� Ư�� ���� ���� ��ġ ���� �Լ�

				cmmSxStopEmg(n_Axis);	

				//010002 E A "Motor Move Setting Error 01 motor)."
				sprintf(mc_alarmcode, "%02d0002", n_Axis); 
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[%d] Check_MotPosRange Target= %4.3f, CurPos= %4.3f", n_Axis, d_Distance, dCurrPos[0]);
					Debug_File_Create(0, mc_normal_msg);
				} 
				//2013,0405
				CTL_Lib.Alarm_Error_Occurrence(3012, CTL_dWARNING, mc_alarmcode);
				return BD_ERROR;
		}
		else
		{//2011.0305 
			mn_retry_cnt[n_Axis]++ ;
			return BD_RETRY;	
		}
	}
	
	return BD_PROCEED;
}

// ******************************************************************************

// ******************************************************************************
// ���� ���� �̵� �Լ�                                                           
// ******************************************************************************
//2015.0326 james �Ʒ� �Լ� ���� 
int CComizoaPublic::Start_LinearMove(int n_MapIndex, double *dp_PosList, double *dp_SpdRatio)  //n_MapIndex�� �̸� ���õǾ� �־�� �Ѵ� 
{//2�� ���� 
//	int    nSafetyCheck = 0, Ret, i=0;
	int    i, nRet=-1;
	double dTargetPos[4]={0,};
	long nListIsDone = 0;
	double dp_Vel[4]={0,0,0, 0};//2015.0326 james �ִ� 4����� ���� ���� �����Ͽ� ���� dp_Vel[3]={0,0,0};

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	if(1 || mn_indexmap_init[n_MapIndex] == BD_NO || n_MapIndex >= 8) //2015.0326 james	if (1 || mn_indexmap_init[n_MapIndex] != BD_YES || n_MapIndex >= 8) 
	{//�ʱ�ȭ ���� ���� ���� 
		nRet = Create_IxIndexMapAxis(n_MapIndex, ml_axiscnt[n_MapIndex], mp_axisnum[n_MapIndex]);
		if (nRet == BD_GOOD)
		{
			mn_indexmap_init[n_MapIndex]  = BD_YES;
		}
		else //if (nRet == BD_ERROR)
		{
			//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
			sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[%d] Create_IxIndexMapAxis return error", n_MapIndex);
				Debug_File_Create(0, mc_normal_msg);
			}
			//2013,0405
			CTL_Lib.Alarm_Error_Occurrence(3012, CTL_dWARNING, mc_alarmcode);
			return BD_ERROR;  
		}
	}

	if (ml_axiscnt[n_MapIndex] < 2 || ml_axiscnt[n_MapIndex] > 4) //2015.0326 james �ִ� 4����� ���� �����ϴ� 
	{
		//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] ml_axiscnt[n_MapIndex] < 2 return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3013, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

	for(i=0; i<ml_axiscnt[n_MapIndex]; i++)
	{
		nRet = CTL_Lib.Motor_SafetyCheck(1, mp_axisnum[n_MapIndex][i], dp_PosList[i]);
		if (nRet == BD_ERROR)
		{	//safety error �� �ش� �Լ����� �ڵ� ���� 
			cmmIxStopEmg(n_MapIndex);
			return BD_ERROR;

		}
		else if (nRet == BD_RETRY)  
		{
			return BD_RETRY;
		}
//   		Set_MotSpeed(MOT_SPD_VEL, st_linearmot[n_MapIndex].lp_AxisNum[i], cmSMODE_S,
//   			st_motor[st_linearmot[n_MapIndex].lp_AxisNum[i]].d_spd_vel[0], 
//   			st_motor[st_linearmot[n_MapIndex].lp_AxisNum[i]].d_spd_vel[1], 
//   			st_motor[st_linearmot[n_MapIndex].lp_AxisNum[i]].d_spd_vel[2]);

		dTargetPos[i] = dp_PosList[i];
	}
	//2015.0326 james ���� ������ ���� �ӵ� ����
	for(i=0; i<ml_axiscnt[n_MapIndex]; i++)
	{
		dp_Vel[i] = (double)(md_spd_vel[mp_axisnum[n_MapIndex][i]][0] * ((double)dp_SpdRatio[0] / (double)100));
		nRet = Set_MotSpeed(MOT_SPD_VEL, mp_axisnum[n_MapIndex][i], cmSMODE_S, 
			dp_Vel[i], md_spd_vel[mp_axisnum[n_MapIndex][i]][1], md_spd_vel[mp_axisnum[n_MapIndex][i]][2]);  //((double)n_SpeedRatio / (double)100)) 
		if(nRet == BD_ERROR)
		{
			//500000 D A "Interpolation IxMapAxis 0�� Setting Error."
			sprintf(mc_alarmcode, "5000%02d", n_MapIndex); 
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[%d][%d] Create_IxIndexMapAxis Set_MotSpeed_1 return error", n_MapIndex, mp_axisnum[n_MapIndex][i]);
				Debug_File_Create(0, mc_normal_msg);
			}
			//2013,0405
			CTL_Lib.Alarm_Error_Occurrence(3014, CTL_dWARNING, mc_alarmcode);
			return BD_ERROR;
		}
	}

	dp_SpdRatio[0] = dp_SpdRatio[0] * (double)((mn_runspeed_rate / 100.));  
	nRet = cmmIxSetSpeedPattern(n_MapIndex, cmFALSE, cmSMODE_S, dp_SpdRatio[0], dp_SpdRatio[1], dp_SpdRatio[2]);//cmmIxSetSpeedPattern)	(long MapIndex, long IsVectorSpeed, long SpeedMode, double Vel, double Acc, double Dec);
	
	if (nRet != cmERR_NONE)
	{
		//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmIxSetSpeedPattern return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		
		cmmIxStopEmg(n_MapIndex);
		return BD_ERROR;
	}

/*2015.0326 james 
	nRet = Set_MotSpeed(MOT_SPD_CM_CTL, mp_axisnum[n_MapIndex][0], cmSMODE_T, 
		md_spd_vel[mp_axisnum[n_MapIndex][0]][0], md_spd_vel[mp_axisnum[n_MapIndex][0]][1], md_spd_vel[mp_axisnum[n_MapIndex][0]][2]);  
	if (nRet == BD_ERROR)
	{
		//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] Create_IxIndexMapAxis Set_MotSpeed_0 return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}
	
	nRet = Set_MotSpeed(MOT_SPD_CM_CTL, mp_axisnum[n_MapIndex][1], cmSMODE_T, 
		md_spd_vel[mp_axisnum[n_MapIndex][1]][0], md_spd_vel[mp_axisnum[n_MapIndex][1]][1], md_spd_vel[mp_axisnum[n_MapIndex][1]][2]);  
	if (nRet == BD_ERROR)
	{
		//500000 D A "Interpolation IxMapAxis 0�� Setting Error."
		sprintf(mc_alarmcode, "5000%02d", n_MapIndex); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] Create_IxIndexMapAxis Set_MotSpeed_1 return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}

//	dp_SpdRatio[0] = dp_SpdRatio[0] * (double)((mn_runspeed_rate / 100.)); //james test 090311	// test �ּ� ó�� 20130306 (�λ���� �׽�Ʈ��� ����) ��� �ݺ����� ��� �ӵ� ���� kjh
	//cmmIxSetSpeedPattern)	(long MapIndex, long IsVectorSpeed, long SpeedMode, double Vel, double Acc, double Dec);
  	
	nRet = cmmIxSetSpeedPattern(n_MapIndex, cmFALSE, cmSMODE_T, dp_SpdRatio[0], dp_SpdRatio[1], dp_SpdRatio[2]);

  	if (nRet != cmERR_NONE)
	{
		//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmIxSetSpeedPattern return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}
	//Set_MotSpeed_Ratio(int n_Axis, int n_SpeedMode, double d_work_Ratio, double d_accel_Ratio, double d_decel_Ratio) 
	//cmFALSE = Master Speed�� ���õǸ� % �� Speed�� �����ȴ� 
*/ //2015.0326 james 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��� ���� �Ϸ� ���θ� Ȯ���Ѵ� 
	nRet = g_comiMgr._cmmIxIsDone(n_MapIndex, &nListIsDone);
	if (nRet == cmERR_NONE) 
	{//�Լ� ���� ���� 
		if (nListIsDone != cmTRUE) //0:����Ʈ ����� �������� ����, 1: ����� �Ϸ�� ���� 
		{
			cmmIxStopEmg(n_MapIndex); 
			return 0; 
			//2015.0326 james �߰� 
			
			mn_linear_retry_cnt[n_MapIndex] = 0;  //2015.0326 james mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 
			cmmIxStopEmg(n_MapIndex);
			
			//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
			sprintf(mc_alarmcode, "%02d0015", n_MapIndex); 

			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[%d] cmmIxIsDone return error", n_MapIndex);
				Debug_File_Create(0, mc_normal_msg);
			}
			//2013,0405
			CTL_Lib.Alarm_Error_Occurrence(3017, CTL_dWARNING, mc_alarmcode);
			return BD_ERROR;
		}
	}
	else
	{//���ϰ��� ������ �ƴϴ� 
		//010015 E A "Interpolation IxMapAxis setting Error(01 motor)."
		cmmIxStopEmg(n_MapIndex);

		sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmIxIsDone return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}
		mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3018, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	nRet = g_comiMgr._cmmIxLineToStart(n_MapIndex, dTargetPos);	
	if (nRet == cmERR_NONE)
	{
		ml_linear_move_time[n_MapIndex][0] = GetCurrentTime(); //2015.0325 james ���� ml_motion_move_time[mp_axisnum[n_MapIndex][0]][0] = GetCurrentTime();
		for(i=0; i<ml_axiscnt[n_MapIndex]; i++)
		{
			if (mn_run_status == CTL_dRUN)	//090825 handler�� ���󰡵����϶��� Ŀ��� �����͸� ���, �޴��� ������ ��ŵ 
			{
				md_cmdpos_backup[mp_axisnum[n_MapIndex][i]] = dp_PosList[i];
			}
		}

		return BD_GOOD;
	}
	else
	{
		mn_linear_retry_cnt[n_MapIndex] = 0;  //2015.0326 james 

		sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmIxLineToStart return error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}		

		cmmIxStopEmg(n_MapIndex);
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3019, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

	return BD_PROCEED;  
}

//2015.0326 james �Ʒ� �Լ� ���� 
int CComizoaPublic::Check_LinearMove(int n_MapIndex, double *dp_PosList) 
{
	int nRet=0, i=0;
	long nListIsDone = 0;
	int  nCurrPosEndCnt = 0;
	double dCurrPos[2] = {0,0};
	double dGap[2] = {0,0};

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	for(i=0; i<ml_axiscnt[n_MapIndex]; i++)
	{
		nRet = CTL_Lib.Motor_SafetyCheck(2, mp_axisnum[n_MapIndex][i], dp_PosList[i]);
		if (nRet == BD_ERROR)
		{
			cmmIxStopEmg(n_MapIndex); //2009.06.30 �߰� 
			return BD_ERROR;
		}
		else if (nRet == BD_RETRY) //091216 �߰� 
		{
			return BD_RETRY;
		}
	}

	nRet = g_comiMgr._cmmIxIsDone(n_MapIndex, &nListIsDone);
	if (nRet == cmERR_NONE) //�Լ� ���� ���� 
	{
		//2015.0326 james 
		//ml_motion_move_time[mp_axisnum[n_MapIndex][0]][1] = GetCurrentTime();
		//ml_motion_move_time[mp_axisnum[n_MapIndex][0]][2] = ml_motion_move_time[mp_axisnum[n_MapIndex][0]][1] - ml_motion_move_time[mp_axisnum[n_MapIndex][0]][0];
		ml_linear_move_time[n_MapIndex][1] = GetCurrentTime();
		ml_linear_move_time[n_MapIndex][2] = ml_linear_move_time[n_MapIndex][1] - ml_linear_move_time[n_MapIndex][0];
		if(ml_linear_move_time[n_MapIndex][2] < 0)
		{
			ml_linear_move_time[n_MapIndex][0] = GetCurrentTime();
			ml_linear_move_time[n_MapIndex][2] = 0;
		}

		if (nListIsDone == cmTRUE) //0:����Ʈ ����� �������� ����, 1: ����� �Ϸ�� ���� 
		{

			// 2016/08/18//////////////////////////////
			nRet = Get_MotInposition( mp_axisnum[n_MapIndex][0] );
			
			if( nRet != BD_GOOD )
				return BD_PROCEED;

			nRet = Get_MotInposition( mp_axisnum[n_MapIndex][1] );
			
			if( nRet != BD_GOOD )
				return BD_PROCEED;

			nCurrPosEndCnt = 0;
			for(i=0; i<ml_axiscnt[n_MapIndex]; i++) //�ִ� �ѹ��� 4�� ������������ �̵����� 
			{
// 				nRet = Check_MotPosRange(mp_axisnum[n_MapIndex][i], dp_PosList[i], md_allow_value[mp_axisnum[n_MapIndex][0]]); //(int n_Axis, double d_Distance, int n_Range) 
				nRet = Check_MotPosRange(mp_axisnum[n_MapIndex][i], dp_PosList[i], md_allow_value[mp_axisnum[n_MapIndex][i]]);//2015.0326 james  //(int n_Axis, double d_Distance, int n_Range) 
				if (nRet == BD_GOOD)
				{					
					nCurrPosEndCnt++;
				}
			}			

			if (nCurrPosEndCnt >= ml_axiscnt[n_MapIndex]) //james test
			{
				mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 

				return BD_GOOD;
			}
			else
			{//�������� �Ϸ������� ��ġ�� ������ ���� 
				 
				/*2015.0326 james 
				if (ml_motion_move_time[mp_axisnum[n_MapIndex][0]][2] > 2000) //090609 MOT_MOVE_LIMITTIME)
				{
					if (mn_retry_cnt[mp_axisnum[n_MapIndex][0]] > mn_max_retry_cnt)
					{
						mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 

						sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[%d] cmmIxIsDone return_1 error", n_MapIndex);
							Debug_File_Create(0, mc_normal_msg);
						}

						cmmIxStopEmg(n_MapIndex);
						return BD_ERROR;
					}
					else
					{					
						mn_retry_cnt[mp_axisnum[n_MapIndex][0]]++;
						return BD_RETRY;
					}
				}*/
				//2015.0326 james �߰� 
				if (ml_linear_move_time[n_MapIndex][2] > 2000) //090609 MOT_MOVE_LIMITTIME)
				{
					if(mn_linear_retry_cnt[n_MapIndex] > mn_max_retry_cnt)
					{
						mn_linear_retry_cnt[n_MapIndex] = 0; 
						sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[%d] cmmIxIsDone return_1 error", n_MapIndex);
							Debug_File_Create(0, mc_normal_msg);
						}
						
						cmmIxStopEmg(n_MapIndex);
						return BD_ERROR;
					}
					else
					{					
						mn_linear_retry_cnt[n_MapIndex]++;
						return BD_RETRY;
					}
				}//2015.0326 james 
				else if(ml_motion_move_time[mp_axisnum[n_MapIndex][0]][2] < 0)//2013,0608
				{
					ml_motion_move_time[mp_axisnum[n_MapIndex][0]][0] = GetCurrentTime();
				}
			} 
		}
		else //0 �̸� �Ϸ���� ���� ���� 
		{//���� ���� ���� ���� 
			/*2015.0326 james 
			if (ml_motion_move_time[mp_axisnum[n_MapIndex][0]][2] > mn_max_move_limit_time) //5�� �̻� �������� �������� ���� 
			{				
				mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 

				sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[%d] cmmIxIsDone return_2 error", n_MapIndex);
					Debug_File_Create(0, mc_normal_msg);
				}

				cmmIxStopEmg(n_MapIndex);
				return BD_ERROR;
			}
			else
			{
				return BD_PROCEED; 
			}*/
			//2015.0326 james 
			if(ml_linear_move_time[n_MapIndex][2] > mn_max_move_limit_time) //5�� �̻� �������� �������� ���� 
			{				
				mn_linear_retry_cnt[n_MapIndex] = 0; 
				sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[%d] cmmIxIsDone return_2 error", n_MapIndex);
					Debug_File_Create(0, mc_normal_msg);
				}
				
				cmmIxStopEmg(n_MapIndex);
				return BD_ERROR;
			}
			else
			{
				return BD_PROCEED; 
			}
		}
	}
	else
	{ //���� ����  
		mn_retry_cnt[mp_axisnum[n_MapIndex][0]] = 0; 

		sprintf(mc_alarmcode, "%02d0015", n_MapIndex);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[%d] cmmIxIsDone return_3 error", n_MapIndex);
			Debug_File_Create(0, mc_normal_msg);
		}

		cmmIxStopEmg(n_MapIndex);
		//2013,0405
		CTL_Lib.Alarm_Error_Occurrence(3022, CTL_dWARNING, mc_alarmcode);
		return BD_ERROR;
	}

	return BD_PROCEED; //MOT_PROCEED;
}

// ******************************************************************************

// ******************************************************************************
// ���� ���� �̵� �Լ�                                                           
// ******************************************************************************
int CComizoaPublic::Start_MultiMove(long l_AxisCnt, long *lp_AxisNum, double *dp_PosList, double *dp_SpdRatio)//long l_AxisCnt, long *lp_Axis, double *dp_AbsPos, int n_SpeedRatio) 
{//2�� ���� 
//	int    nSafetyCheck = 0, Ret, i=0;
	int    i, nRet=-1;
	double dTargetPos[4]={0,};

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}
	
	
	for(i=0; i<l_AxisCnt; i++)
	{
		nRet = CTL_Lib.Motor_SafetyCheck(1, lp_AxisNum[i], dp_PosList[i]);
		if (nRet == BD_ERROR)
		{
			cmmSxStopEmg(lp_AxisNum[i]);		
			return BD_ERROR;
		}
		else if (nRet == BD_RETRY) //091216 �߰� 
		{
			return BD_RETRY;
		}
	}

	for(i=0; i<l_AxisCnt; i++)
	{
		nRet = Set_MotSpeed(MOT_SPD_CM_CTL, lp_AxisNum[i], cmSMODE_S, md_spd_vel[lp_AxisNum[i]][0], md_spd_vel[lp_AxisNum[i]][1], md_spd_vel[lp_AxisNum[i]][2]);
		
		if (nRet == BD_ERROR)
		{//010002 E A "Motor Move Setting Error01 motor)."
			sprintf(mc_alarmcode, "%02d0002", lp_AxisNum[i]);
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis=%d] multi move speed return error", lp_AxisNum[i]);
				Debug_File_Create(0, mc_normal_msg);
			}
			return BD_ERROR;
		}

		Set_MotSpeed_Ratio(lp_AxisNum[i], cmSMODE_T, dp_SpdRatio[0], dp_SpdRatio[1], dp_SpdRatio[2]);//V_0.1.4 090726 cmSMODE_KEEP 
		
		dTargetPos[i] = dp_PosList[i];
	}

	nRet = cmmMxMoveToStart(l_AxisCnt, lp_AxisNum, dTargetPos);	
	if (nRet == cmERR_NONE)
	{
		
		for(i=0; i<l_AxisCnt; i++)
		{
			if (mn_run_status == CTL_dRUN)	//090825 handler�� ���󰡵����϶��� Ŀ��� �����͸� ���, �޴��� ������ ��ŵ 
			{
				md_cmdpos_backup[lp_AxisNum[i]] = dp_PosList[i];
			}
		}
		ml_motion_move_time[lp_AxisNum[0]][0] = GetCurrentTime();

		return BD_GOOD;
	}
	else
	{
		sprintf(mc_alarmcode, "%02d0002", lp_AxisNum[0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] cmmMxMoveToStart return error", lp_AxisNum[0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}

	return BD_PROCEED;
}
// ******************************************************************************
// ���� ���� �̵� ��ġ ���е� �˻� �Լ�                                          
// -> WORD wBoardID      : ���ǵ� ���� ���� ID ��ȣ                              
// -> int *npAxis        : ���� �� ���� �迭�� ���� ������                       
// -> double *dpAbsPos   : ���� �̵� �Ÿ� ���� �迭�� ���� ������                
// ******************************************************************************
int CComizoaPublic::Check_MultiMove(long l_AxisCnt, long *lp_AxisNum, double *dp_PosList) 
{
	int    i, nRet=0;
	double dCurrPos[4]={0,};
	long nListIsDone = 0;
	int nCurrPosEndCnt;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	for(i=0; i<l_AxisCnt; i++)
	{
		nRet = CTL_Lib.Motor_SafetyCheck(2, lp_AxisNum[i], dp_PosList[i]);
		if (nRet == BD_ERROR)
		{
			cmmSxStopEmg(lp_AxisNum[i]);	
			return BD_ERROR; //MOT_SAFETY_ERROR;
		}	
		else if (nRet == BD_RETRY) //091216 �߰� 
		{
			return BD_RETRY;
		}
	}

	ml_motion_move_time[lp_AxisNum[0]][1] = GetCurrentTime();
	ml_motion_move_time[lp_AxisNum[0]][2] = ml_motion_move_time[lp_AxisNum[0]][1] - ml_motion_move_time[lp_AxisNum[0]][0];

	nRet = cmmMxIsDone(l_AxisCnt, lp_AxisNum, &nListIsDone);
	if (nRet == cmERR_NONE) //���� ���� 
	{
		if (nListIsDone == cmTRUE) //0:����Ʈ ����� �������� ����, 1: ����� �Ϸ�� ���� 
		{
			nCurrPosEndCnt = 0;
			for(i=0; i<l_AxisCnt; i++) //�ִ� �ѹ��� 4�� ������������ �̵����� 
			{
				nRet = Check_MotPosRange(lp_AxisNum[i], dp_PosList[i], md_allow_value[lp_AxisNum[i]]); //(int n_Axis, double d_Distance, int n_Range) 
				if (nRet == BD_GOOD)
				{					
					nCurrPosEndCnt++;
				}
			}

			if (nCurrPosEndCnt == l_AxisCnt)
			{
				mn_retry_cnt[lp_AxisNum[0]] =  0;
				return BD_GOOD;
			}
			else
			{//�������� �Ϸ� 
				if (ml_motion_move_time[lp_AxisNum[0]][2] > 2000) //090609 MOT_MOVE_LIMITTIME)
				{
					if (mn_retry_cnt[lp_AxisNum[0]] > mn_max_retry_cnt)
					{
						mn_retry_cnt[lp_AxisNum[0]] =  0;

						//010006 E A "Motor Move Check Error(01 motor)."
						sprintf(mc_alarmcode, "%02d0006", lp_AxisNum[0]);
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[axis=%d] cmmMxIsDone return error", lp_AxisNum[0]);
							Debug_File_Create(0, mc_normal_msg);
						}
						return BD_ERROR;
					}
					else
					{
						mn_retry_cnt[lp_AxisNum[0]]++ ;
						return BD_RETRY;								
					}			
				}
				else if(ml_motion_move_time[lp_AxisNum[0]][2] < 0)//2013,0608
				{
					ml_motion_move_time[lp_AxisNum[0]][0] = GetCurrentTime();
				}
			} 
		}
		else //0 �̸� �Ϸ���� ���� ���� 
		{	//���� ���� ���� 		
			if (ml_motion_move_time[lp_AxisNum[0]][2] > mn_max_move_limit_time) //MOT_MOVE_LIMITTIME�� �̻� �������� �������� ���� 
			{
				mn_retry_cnt[lp_AxisNum[0]] =  0;

				//010006 E A "Motor Move Check Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0006", lp_AxisNum[0]);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] cmmMxIsDone nListIsDone return error", lp_AxisNum[0]);
					Debug_File_Create(0, mc_normal_msg);
				}
				return BD_ERROR;
			}
			else
			{
				nRet = BD_PROCEED;
			}
		}
	}
	else
	{ //�����̸� ���� 
		//010006 E A "Motor Move Check Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0006", lp_AxisNum[0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] cmmMxIsDone return_0 error", lp_AxisNum[0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;
	}

	return BD_PROCEED;
}
// ******************************************************************************


///////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ���� ������ ����� 0~3, 4~7���� 4�� ���� �����Ѵ� 
///////////////////////////////////////////////////////////////////////////////////////////////////
int CComizoaPublic::Start_CoordinatedMove(long n_LmIndexNum) //���Ӻ��� ��� 
{
	int i,j;
	int nRet =0;
	double dSpeedRatio[3] = {100,100,100}; 

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

//Index Map ��ȣ �� ���� 
	nRet = Create_LmIndexMapAxis(n_LmIndexNum, ml_coord_totalaxiscnt[n_LmIndexNum], ml_coord_totalaxisnum[n_LmIndexNum]); //l_TotalAxisCnt = �ִ� 4����� ����� �� �ֵ��� ���� 
	if (nRet == BD_GOOD)
	{				
		mn_coord_indexmap_init[n_LmIndexNum] = BD_YES;
	}
	else //if (nRet == BD_ERROR)
	{//Index Map �ۼ� ���� 
		//cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
		mn_coord_indexmap_init[n_LmIndexNum] = BD_NO;

		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", ml_coord_totalaxisnum[n_LmIndexNum][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] Create_LmIndexMapAxis return_0 error", ml_coord_totalaxisnum[n_LmIndexNum][0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;  
	}


	if (mn_coord_indexmap_init[n_LmIndexNum] != BD_YES || n_LmIndexNum >= 8) 
	{//�ʱ�ȭ ���� ���� ���� 
		//cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", ml_coord_totalaxisnum[n_LmIndexNum][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] Create_LmIndexMapAxis return_0 error", ml_coord_totalaxisnum[n_LmIndexNum][0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;  
	}

	
	nRet = cmmLmBeginList(n_LmIndexNum); 
	if (nRet != cmERR_NONE)
	{ 
		//cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", ml_coord_totalaxisnum[n_LmIndexNum][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] cmmLmBeginList return_0 error", ml_coord_totalaxisnum[n_LmIndexNum][0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR;  
	}

	for(i=0; i<ml_coord_totalaxiscnt[n_LmIndexNum]; i++) //�����̵� �����̵� �ѹ� ������ 1ȸ�� ���� �̵��ϴ� Ƚ���� �����Ѵ�  
	{
		if (ml_coord_subaxiscnt[n_LmIndexNum][i] == 1) //���� �̵��Ѵٴ� �÷��� 
		{	
			nRet = Start_SingleMove(ml_coord_subaxisnum[n_LmIndexNum][i][0], md_coord_poslist[n_LmIndexNum][i][0]); //double *dp_SpeedRatio) 

			if (nRet != BD_YES)//cmERR_NONE)
			{
				//cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
				//010002 E A "Motor Move Setting Error01 motor)."
				sprintf(mc_alarmcode, "%02d0002", ml_coord_subaxisnum[n_LmIndexNum][i][0]);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] coord Start_SingleMove return_0 error",ml_coord_subaxisnum[n_LmIndexNum][i][0]);
					Debug_File_Create(0, mc_normal_msg);
				}
			}
		}
		else if (ml_coord_subaxiscnt[n_LmIndexNum][i] > 1) //2�� �̻� ������������ �̵��Ѵٴ� �÷��� 
		{ 
			//Axis Mask ������ �̸� ���Ͽ� ������ ���ƾ� �Ѵ�  
			//cmmIxMapAxes(n_IxIndexNum, nMapMask[0], nMapMask[1]);
			//LmIndexMap_Create(int n_LmMode, int n_MapIndexNum, int n_AxisCount, int n_AxisNum[4]) //�ִ� 4����� ����� �� �ֵ��� ���� 

			ml_axiscnt[n_LmIndexNum] = ml_coord_subaxiscnt[n_LmIndexNum][i];

			for(j=0; j<ml_axiscnt[n_LmIndexNum]; j++)
			{
				mp_axisnum[n_LmIndexNum][j] = ml_coord_subaxisnum[n_LmIndexNum][i][j];
				//st_linearmot[n_LmIndexNum].lp_AxisNum[1] = st_coordmot[n_LmIndexNum].lp_SubAxisNum[i];
			}

			nRet = Start_LinearMove(n_LmIndexNum, md_coord_poslist[n_LmIndexNum][i], dSpeedRatio);
			if (nRet != BD_GOOD)
			{
				cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 

				//010002 E A "Motor Move Setting Error01 motor)."
				sprintf(mc_alarmcode, "%02d0002", ml_coord_subaxisnum[n_LmIndexNum][i][0]);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] coord Start_LinearMove return_0 error",ml_coord_subaxisnum[n_LmIndexNum][i][0]);
					Debug_File_Create(0, mc_normal_msg);
				}
				return BD_ERROR; 
			}
/*
			//Index Map ��ȣ �� ���� 
			nRet = Create_IxIndexMapAxis(n_LmIndexNum, st_coordmot[n_LmIndexNum].lp_SubAxisCnt[i], st_coordmot[n_LmIndexNum].lp_SubAxisNum[i]); //n_AxisCnt = �ִ� 4����� ����� �� �ֵ��� ���� 
			if (nRet == BD_GOOD)
			{
				st_coordmot[n_LmIndexNum].n_indexmap_init = BD_YES;
			}
			else //if (nRet == BD_ERROR)
			{//Index Map �ۼ� ���� 
				sprintf(cJamcode, "%02d0046",  st_coordmot[st_coordmot[n_LmIndexNum].lp_IxIndexNum[i]].lp_IxIndexNum[i]); //000046 1 70 "List Motion_0 LmIndexMap  Start Return Check Error."
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, cJamcode);

				nErrAxis = cmmErrParseAxis(nRet);
				nErrReason = cmmErrParseReason(nRet);
				CtlBdFunc.ms_ErrMsg.Format("[MOVE ERROR] %02d Axis : %d", nErrAxis, nErrReason);
				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, CtlBdFunc.ms_ErrMsg);
				return BD_ERROR;  
			}
			
			if (st_coordmot[n_LmIndexNum].n_indexmap_init != BD_YES || n_LmIndexNum >= 8)  //0~7
			{//�ʱ�ȭ ���� ���� ���� 
				sprintf(cJamcode, "%02d0025",  st_coordmot[n_LmIndexNum].lp_IxIndexNum[i]); //000025 1 70 "Linear Motion_0 IxIndexMap Create Check Error."
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, cJamcode);
				return BD_ERROR;  
			}

			nRet = cmmIxSetSpeedPattern(st_coordmot[n_LmIndexNum].lp_IxIndexNum[i], cmFALSE, cmSMODE_S, 100, 100, 100); //����, ����, ���� ratio 
			if (nRet != cmERR_NONE)	{CtlBdFunc.Send_Error_Message(0, "cmmIxSetSpeedPattern return Error"); return BD_ERROR; }			

			nRet = cmmIxLineToStart(n_LmIndexNum, st_coordmot[n_LmIndexNum].dp_PosList[i]);
			if (nRet != cmERR_NONE)
			{
				sprintf(cJamcode, "%02d0020",  st_coordmot[n_LmIndexNum].lp_IxIndexNum[i]); //000020 1 70 "Linear Motion_0 Start Error."
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, cJamcode);
				nErrAxis = cmmErrParseAxis(nRet);
				nErrReason = cmmErrParseReason(nRet);
				CtlBdFunc.ms_ErrMsg.Format("[MOVE ERROR] %02d Axis : %d", nErrAxis, nErrReason);
				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, CtlBdFunc.ms_ErrMsg);
				 return BD_ERROR; 
			}
*/
		}
		else 
		{
			//AfxMessageBox("List Motion Motor Axis define Error");
			//cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 

			//010002 E A "Motor Move Setting Error01 motor)."
			sprintf(mc_alarmcode, "%02d0002", ml_coord_subaxisnum[n_LmIndexNum][i][0]);
			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis=%d] coord Start_LinearMove return_0 error",ml_coord_subaxisnum[n_LmIndexNum][i][0]);
				Debug_File_Create(0, mc_normal_msg);
			}
			return BD_ERROR; 
		}
	}

	nRet = cmmLmEndList(n_LmIndexNum); //map ���� �Ϸ� 
	if (nRet != cmERR_NONE)
	{
		cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 

		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", ml_coord_subaxisnum[n_LmIndexNum][0][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] coord cmmLmEndList return_0 error",ml_coord_subaxisnum[n_LmIndexNum][i][0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		return BD_ERROR; 
	}

	nRet = cmmLmStartMotion(n_LmIndexNum); //���ݺ��� �̵� ���� i 
	if (nRet == cmERR_NONE) //�������� ��ε��� �Ϸ� 
	{	//������ ������ Ŀ��� ������ �����Ѵ� 
		for(i=0; i<ml_coord_totalmovecnt[n_LmIndexNum]; i++) //�����̵� �����̵� �ѹ� ������ 1ȸ�� ���� �̵��ϴ� Ƚ���� �����Ѵ�  
		{
			if (ml_coord_subaxiscnt[n_LmIndexNum][i] == 1) //���� �̵��Ѵٴ� �÷��� 
			{
				md_cmdpos_backup[ml_coord_subaxisnum[n_LmIndexNum][i][0]] = md_coord_poslist[n_LmIndexNum][i][0];			
			}
			else if (ml_coord_subaxiscnt[n_LmIndexNum][i] > 1) //2�� �̻��� ������������ �̵��Ѵٴ� �÷��� 
			{
				for(j=0; j<ml_coord_subaxiscnt[n_LmIndexNum][i]; j++)
				{
					md_cmdpos_backup[ml_coord_subaxisnum[n_LmIndexNum][i][j]] = md_coord_poslist[n_LmIndexNum][i][j];
				}				 
			}
		}				
	}
	else
	{		
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", ml_coord_subaxisnum[n_LmIndexNum][0][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] coord cmmLmEndList return_0 error",ml_coord_subaxisnum[n_LmIndexNum][0][0]);
			Debug_File_Create(0, mc_normal_msg);
		}

		cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
		return BD_ERROR; 
	}

	ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][0] = GetCurrentTime();

	//st_coordmot[n_LmIndexNum].n_indexmap_init = BD_YES; //james test 
	return BD_GOOD;
} 

int CComizoaPublic::Check_CoordinatedMove(int n_LmIndexNum)
{
	long nRet=0, nDoneRet=1, i=0;
	long lListIsDone;
	int  nMotCntNum = 0, nCurrPosYes = 0;
	double dCurrPos[4]={0,0,0,0};
	CString sErrMsg;

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}

	ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][1] = GetCurrentTime(); 
	ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][2] = ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][1]- ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][0];

	nDoneRet = cmmLmIsDone(n_LmIndexNum, &lListIsDone); //james test lListIsDone ���� Ȯ���� �� 
	//if (nDoneRet == cmERR_NONE) //��� ���� ���� 
	if (lListIsDone == cmTRUE)
	{
		if (lListIsDone == cmTRUE) //BD_YES) //0:����Ʈ ����� �������� ����, 1: ����� �Ϸ�� ���� 
		{
			for(i=0; i<ml_coord_totalaxiscnt[n_LmIndexNum]; i++) //�ִ� �ѹ��� 4�� ������������ �̵����� 
			{//
				nRet = Check_MotPosRange(ml_coord_totalaxisnum[n_LmIndexNum][i], md_cmdpos_backup[ml_coord_totalaxisnum[n_LmIndexNum][i]],md_allow_value[ml_coord_totalaxisnum[n_LmIndexNum][i]]); //(int n_Axis, double d_Distance, int n_Range) 
				if (nRet == BD_GOOD)
				{ 					
					nCurrPosYes++;
					dCurrPos[i]++;
				}
				else
				{

					dCurrPos[i]--;

				}
			}
			//james test 
			//if (nCurrPosYes >= st_coordmot[n_LmIndexNum].l_TotalAxisCnt - 2)
			if (nCurrPosYes >= ml_coord_totalaxiscnt[n_LmIndexNum])
			{
				mn_retry_cnt[ml_coord_totalaxisnum[n_LmIndexNum][0]] = 0;
				return BD_GOOD;
			}
			else
			{//�������� �Ϸ� 
				if (ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][2] > 2000) //090609 MOT_MOVE_LIMITTIME)
				{
					if (mn_retry_cnt[ml_coord_subaxisnum[n_LmIndexNum][0][0]] > mn_max_retry_cnt)
					{
						//010006 E A "Motor Move Check Error(01 motor)."
						sprintf(mc_alarmcode, "%02d0006", ml_coord_subaxisnum[n_LmIndexNum][0][0]);
						if (mn_errormsg_debug_mode)
						{
							sprintf(mc_normal_msg, "[axis=%d] coord cmmLmEndList return_0 error",ml_coord_subaxisnum[n_LmIndexNum][0][0]);
							Debug_File_Create(0, mc_normal_msg);
						}

						cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
						return BD_ERROR;
					}
					else
					{
						mn_retry_cnt[ml_coord_subaxisnum[n_LmIndexNum][0][0]]++;
						cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 

						return BD_RETRY;
					}		
				}
				else if(ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][2] < 0)//2013,0608
				{
					ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][0] = GetCurrentTime();
				}
				else
				{
					for(i=0; i<ml_coord_totalaxiscnt[n_LmIndexNum]; i++) //�ִ� �ѹ��� 4�� ������������ �̵����� 
					{
						nRet = Check_MotPosRange(ml_coord_totalaxisnum[n_LmIndexNum][i], md_cmdpos_backup[ml_coord_totalaxisnum[n_LmIndexNum][i]],
							md_allow_value[ml_coord_totalaxisnum[n_LmIndexNum][i]]); //(int n_Axis, double d_Distance, int n_Range) 
					}			
				}
			} 
		}
		else //0 �̸� �Ϸ���� ���� ���� 
		{	//���� ���� ���� 		
			if (ml_motion_move_time[ml_coord_subaxisnum[n_LmIndexNum][0][0]][2] > mn_max_move_limit_time) //5�� �̻� �������� �������� ���� 
			{
				for(i=0; i<ml_coord_totalaxiscnt[n_LmIndexNum]; i++) //�ִ� �ѹ��� 4�� ������������ �̵����� 
				{
					nRet = Check_MotPosRange(ml_coord_totalaxisnum[n_LmIndexNum][i], md_cmdpos_backup[ml_coord_totalaxisnum[n_LmIndexNum][i]],
						md_allow_value[ml_coord_totalaxisnum[n_LmIndexNum][i]]); //(int n_Axis, double d_Distance, int n_Range) 
					if (nRet == BD_GOOD)
					{ 
						nCurrPosYes++;
					}
					else
					{
						
						dCurrPos[0]++;
						
					}
				}

				//010006 E A "Motor Move Check Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0006", ml_coord_subaxisnum[n_LmIndexNum][0][0]);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] coord cmmLmEndList return_0 error",ml_coord_subaxisnum[n_LmIndexNum][0][0]);
					Debug_File_Create(0, mc_normal_msg);
				}
				cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 

				return BD_ERROR;						
			}
		}
	}
	else
	{ //�����̸� ����

		//010006 E A "Motor Move Check Error(01 motor)."
		sprintf(mc_alarmcode, "%02d0006", ml_coord_subaxisnum[n_LmIndexNum][0][0]);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d] coord cmmLmEndList return_0 error",ml_coord_subaxisnum[n_LmIndexNum][0][0]);
			Debug_File_Create(0, mc_normal_msg);
		}
		cmmLmAbortMotion(n_LmIndexNum); //������ ���� �߻��� ���� ���� ��Ų�� 
		return BD_ERROR;						
	}

	return BD_PROCEED;
}

// ******************************************************************************
// ���� ���� HOMING �۾� ���� �Լ�                                               
// ******************************************************************************
int CComizoaPublic::HomeCheck_Mot(int n_Axis, int n_TimeOut) 
{
	int  nRet =-1, nRet_1, nRet_2, nRet_3, nFuncRet;
	long IsEnable=0;
	double LimitN=0, LimitP=0;

	if( st_handler.mn_virtual_mode )
	{
		nFuncRet = BD_PROCEED;
		g_sm.SetData( (SM_TYPE)(SMT_M_D_FEEDER_1_TARGET + n_Axis), "0");
		if( g_sm.GetData( (SM_TYPE)(SMT_M_D_FEEDER_1_POSITION + n_Axis) ) == "0" )
		{
			nFuncRet = BD_GOOD;
		}
		return nFuncRet;
	}

	nFuncRet = BD_PROCEED;
	int n_HomeMode = mn_homecheck_method[n_Axis];

	if (n_HomeMode == 1) //org
	{	
		n_HomeMode = 0;
	}
	else if (n_HomeMode == 6)//el-
	{
		n_HomeMode = 1;
	}
	
	nRet = CTL_Lib.Motor_SafetyCheck(0, n_Axis, 0);
	if (nRet == BD_ERROR)
	{
		//2011.0127 ���� mn_homechk_flag = BD_NO;   
		Set_MotStop(1, n_Axis);
		mn_home_step[n_Axis] = 0; //2011.0129 �߰� 

		return BD_ERROR;
	}
	else if (nRet == BD_RETRY) //091216 �߰� 
	{
		return BD_RETRY;
	}

	switch(mn_home_step[n_Axis])
	{
	case 0 :
		if (1 || mn_sd_io_property_flag[n_Axis] == BD_YES) 
		{
			Set_Motor_IO_Property(n_Axis, cmSD_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
		}

		cmmSxStopEmg(n_Axis);
		Set_MotSpeed(MOT_SPD_ORG, n_Axis, cmSMODE_T, md_spd_home[n_Axis], 100, 100) ; //st_motor[i].d_spd_home[0] * 10, st_motor[i].d_spd_home[0] * 10);
		
		cmmCfgSetSoftLimit(n_Axis, FALSE, md_limit_position[n_Axis][0], md_limit_position[n_Axis][1]); //S/W limit ���� 
		mn_home_step[n_Axis] = 100;
		break;

	case 100:
		if (Get_MotAlarmStatus(n_Axis) == BD_GOOD)  // BD_ERROR�� �˶��� �߻����� ���� ���� 
		{
			mn_home_step[n_Axis] = 200;
		}
		else
		{
			mn_home_step[n_Axis] = 110;
		}
		break;

	case 110 :
		if ( Set_MotAlarmClear(n_Axis) == BD_GOOD)  // ���� ALARM CLEAR �Լ�
		{
			mn_home_step[n_Axis]  = 100;
		}
		else
		{
			if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
			{
				mn_retry_cnt[n_Axis] = 0;						
				mn_home_step[n_Axis] = 0;
				//2011.0127 ���� st_motor[n_Axis].b_homechk_flag = BD_NO;
				nFuncRet = BD_ERROR;

				//010004 E A "Motor Alarm Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0004", n_Axis);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] org Set_MotAlarmClear return error",n_Axis);
					Debug_File_Create(0, mc_normal_msg);
				}
			}
			else
			{
				mn_retry_cnt[n_Axis]++ ;
				mn_home_step[n_Axis] = 110;
			}
		}
		break;

	case 200 :
//		if ( Get_MotPower(n_Axis) == BD_GOOD )  
		if ( g_comiMgr.Get_MotPower(n_Axis) == BD_GOOD ) 
		{// ���� POWER ���� ON
			mn_home_step[n_Axis] = 300;
		}
		else
		{
			mn_home_step[n_Axis] = 210;
		}
		break;

	case 210 :
		if ( Set_MotPower(n_Axis, BD_YES) == BD_GOOD )  // ���� POWER ON ���� �Լ�
		{
			mn_home_step[n_Axis]  = 200;
		}
		else
		{
			if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
			{
				mn_retry_cnt[n_Axis] = 0;
				mn_home_step[n_Axis] = 0;
				//2011.0127 ���� st_motor[n_Axis].b_homechk_flag = BD_NO;
				nFuncRet = BD_ERROR;

				//010005 E A "Motor Power Off Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0005", n_Axis);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] org Set_MotAlarmClear return error",n_Axis);
					Debug_File_Create(0, mc_normal_msg);
				}
			}
			else
			{
				mn_retry_cnt[n_Axis]++ ;
				mn_home_step[n_Axis] = 210;
			}
		}
		break;

	case 300 :  // ���� HOMING 
		nRet = cmmHomeMoveStart(n_Axis, cmFALSE);
		if (nRet == cmERR_NONE)
		{
			ml_motion_move_time[n_Axis][0] = GetCurrentTime();
			mn_home_step[n_Axis] = 310;
		}
		else
		{
			if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
			{				
				Set_MotStop(1, n_Axis);  // FAS ���� �̵� ���� �Լ�
				mn_home_step[n_Axis] = 0;
				mn_retry_cnt[n_Axis] = 0;
				nFuncRet = BD_ERROR;

				//010003 E A "Motor Home Check Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0003", n_Axis);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d] org Set_MotAlarmClear return error",n_Axis);
					Debug_File_Create(0, mc_normal_msg);
				} 
			}
			else
			{
				mn_retry_cnt[n_Axis]++ ;
				mn_home_step[n_Axis] = 300;
			}
		}
		break;	

	case 310 :  // MOTION DONE �˻� 		
		nRet_1 = Get_MotMotionDone(n_Axis);        // ���� �̵� �Ϸ� �˻� �Լ� //Ȩ üũ�ô� ���� �ȵ�,  ������ ���߸� YES �� 
		nRet_2 = Get_MotMotionZeroReturn(n_Axis);  // ���� ZERO BIT �˻� �Լ� 
		cmmHomeGetSuccess(n_Axis, &IsEnable);
		if (IsEnable == cmTRUE) nRet_3 = BD_GOOD;
		else nRet_3 = BD_ERROR;

		if (n_HomeMode == MOT_SENS_HOME) //home sensor�� Ȩ üũ�ϴ� ����̸� 
		{
			if (nRet_1 == BD_GOOD && nRet_2 == BD_GOOD && nRet_3 == BD_GOOD)
			{
				ml_motion_move_time[n_Axis][0] = GetCurrentTime();
				mn_home_step[n_Axis] = 320;
			}	
			else if (nRet_1 == BD_GOOD) //2011.0209 �߰� Ȩ üũ ������ ������ ������ 
			{
				mn_retry_cnt[n_Axis]++ ;
 				mn_home_step[n_Axis] = 301;
			}
		}
		else if (n_HomeMode == MOT_SENS_ELM) //-EL sensor�� Ȩ üũ�ϴ� ����̸� 
		{//st_motor[n_Axis].n_homecheck_method == 6)	// -EL�� Ȩüũ �ϴ� ������ ��쿡�� ZeroReturn�� ���� �ʴ´�.
			if (nRet_1 == BD_GOOD && nRet_3 == BD_GOOD)
			{
				mn_home_step[n_Axis] = 400;				
			}
		}

		ml_motion_move_time[n_Axis][1] = GetCurrentTime();
		ml_motion_move_time[n_Axis][2] = ml_motion_move_time[n_Axis][1] - ml_motion_move_time[n_Axis][0];
		
		if (ml_motion_move_time[n_Axis][2] >= n_TimeOut)
		{
			if (mn_retry_cnt[n_Axis] > mn_max_retry_cnt)
			{				
				Set_MotStop(1, n_Axis);  // FAS ���� �̵� ���� �Լ�
				mn_retry_cnt[n_Axis] = 0;
				mn_home_step[n_Axis] = 0;
				//2011.0127 ���� st_motor[n_Axis].b_homechk_flag = BD_NO;
				nFuncRet = BD_ERROR;

				//010003 E A "Motor Home Check Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0003", n_Axis);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d %d %d %d] org cmmHomeGetSuccess return error",n_Axis, nRet_1, nRet_2, nRet_3);
					Debug_File_Create(0, mc_normal_msg);
				} 
			}
			else
			{
				mn_retry_cnt[n_Axis]++;
//				mn_home_step[n_Axis] = 300;
			}
		}
		else if(ml_motion_move_time[n_Axis][2] < 0)
		{
			ml_motion_move_time[n_Axis][0] = GetCurrentTime();
		}
		break;	

	case 301: //2011.0209 �߰� Ʈ���� Ʈ������ Z�� break�� ����� on/off ���� �Ⱦ� ���� �̵� �� Ȩüũ ���� 
		Set_MotAlarmClear(n_Axis);
		mn_home_step[n_Axis] = 0;
		break;

	case 320 :  // HOME ���� �˻� 
		if (Get_MotIOSensor(n_Axis, MOT_SENS_HOME) == BD_GOOD)  // ���� ���� ���� �˻� �Լ� [EL(+)    EL(-)    HOME]
		{
			mn_home_step[n_Axis] = 400;
		}
		else
		{
			ml_motion_move_time[n_Axis][1] = GetCurrentTime();
			ml_motion_move_time[n_Axis][2] = ml_motion_move_time[n_Axis][1] - ml_motion_move_time[n_Axis][0];
			if (ml_motion_move_time[n_Axis][2] > 500)
			{
				Set_MotStop(1, n_Axis);  // ���� �̵� ���� �Լ�
				mn_retry_cnt[n_Axis] = 0;
				mn_home_step[n_Axis] = 0;
				//2011.0127 ���� st_motor[n_Axis].b_homechk_flag = BD_NO;
				nFuncRet = BD_ERROR;

				//010003 E A "Motor Home Check Error(01 motor)."
				sprintf(mc_alarmcode, "%02d0003", n_Axis);
				if (mn_errormsg_debug_mode)
				{
					sprintf(mc_normal_msg, "[axis=%d ] org MOT_SENS_HOME return error",n_Axis);
					Debug_File_Create(0, mc_normal_msg);
				} 
			}			
			else if(ml_motion_move_time[n_Axis][2] < 0)
			{
				ml_motion_move_time[n_Axis][0] = GetCurrentTime();
			}
		}
		break;

	case 400:
		ml_motion_move_time[n_Axis][0] = GetCurrentTime();
		mn_home_step[n_Axis] = 410;
		break;


	case 410 :  // ���� Ŀ�ǵ� ��ġ �ʱ�ȭ 
		ml_motion_move_time[n_Axis][1] = GetCurrentTime();
		ml_motion_move_time[n_Axis][2] = ml_motion_move_time[n_Axis][1] - ml_motion_move_time[n_Axis][0];
		if (ml_motion_move_time[n_Axis][2] > 1000) //1���Ŀ� ������ ���¿��� ���ڴ� 0�� Ŭ���� 
		{
			cmmStSetPosition(n_Axis, cmCNT_COMM, (double)0);
			cmmStSetPosition(n_Axis, cmCNT_FEED, (double)0);

			if (mn_errormsg_debug_mode)
			{
				sprintf(mc_normal_msg, "[axis=%d ] org check end ok",n_Axis);
				Debug_File_Create(0, mc_normal_msg);
			} 

			mn_home_step[n_Axis] = 500;
		}		 
		else if(ml_motion_move_time[n_Axis][2] < 0)
		{
			ml_motion_move_time[n_Axis][0] = GetCurrentTime();
		}
		break;

	case 500 :  // HOMING �Ϸ� 
 		cmmCfgSetSoftLimit(n_Axis, TRUE, md_limit_position[n_Axis][0], md_limit_position[n_Axis][1]); //S/W limit ����  
 		mn_retry_cnt[n_Axis] = 0;
		mn_home_step[n_Axis] = 0;
		mn_homechk_flag[n_Axis] = BD_YES;  

		//cmmCfgGetSoftLimit(n_Axis, &IsEnable, &LimitN, &LimitP);
		cmmSxStopEmg(n_Axis);
		nFuncRet = BD_GOOD;
		break;
	}

	return nFuncRet;  
}

int CComizoaPublic::Start_JogMove(long l_AxisNum, long l_Dir)//2011.0112 , double d_SpeedRatio[3])
{
	int  nRet = 0; 

// 	if (mn_simulation_mode == 1)
// 	{// 
// 		return BD_GOOD;
// 	}
	
	nRet = CTL_Lib.Motor_SafetyCheck(3, l_AxisNum, 0);
	if (nRet != BD_GOOD)
	{
		if (nRet == BD_RETRY) //091216 �߰� 
		{
			return BD_RETRY;
		}

		return BD_ERROR; //MOT_MOT_RETRY, BD_ERROR; MOT_SAFETY_ERROR;
	}
/*
	nRet = Set_MotSpeed(MOT_SPD_VEL, l_AxisNum, cmSMODE_KEEP, d_SpeedRatio[0], st_motor[l_AxisNum].d_spd_vel[1], st_motor[l_AxisNum].d_spd_vel[2]);
	if (nRet == CTL_ERROR)
	{
		sprintf(cJamcode, "%02d0004",  l_AxisNum); alarm.str_code = _T(cJamcode); //091216//000004 1 00 "Load Index Motor Move Setting Error."
		CtlBdFunc.ms_ErrMsg.Format("[Start_JogMove] Check Error");				
		CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, l_AxisNum, cJamcode, CtlBdFunc.ms_ErrMsg);
		return BD_ERROR;
	}	
*/
	if (mn_sd_io_property_flag[l_AxisNum] == BD_YES) //2011.0104 SD ���� �߰����� ��� �߰� 
	{//2011.0104 james ��� �߰� 
		COMI.Set_Motor_IO_Property(l_AxisNum, cmSD_EN, cmFALSE);	//cmSD_EN=14 //cmFALSE = 0 SD ��Ȱ��, cmTRUE = 1 SD Ȱ�� 
	}

	
	nRet = cmmSxVMoveStart(l_AxisNum, l_Dir);
	if (nRet == cmERR_NONE)
	{
		return BD_GOOD;
	}
	else
	{
		//010002 E A "Motor Move Setting Error01 motor)."
		sprintf(mc_alarmcode, "%02d0002", l_AxisNum);
		if (mn_errormsg_debug_mode)
		{
			sprintf(mc_normal_msg, "[axis=%d ] cmmSxVMoveStart return error",l_AxisNum);
			Debug_File_Create(0, mc_normal_msg);
		} 
		return BD_ERROR;
	}
	
	return BD_ERROR;
}




int CComizoaPublic::Debug_File_Create(int n_mode, CString s_msg)
{
//2011.0417	sing.Lock(); //2011.0417 

	CString mstr_cur_year, mstr_cur_month, mstr_cur_day, str_display_time; // ���� ��, ��, �� ���� ���������� ��ȯ�Ͽ� ������ ���� 
	int mn_cur_year, mn_cur_month, mn_cur_day, mn_cur_hour; // ���� ��, ��, �� ���� ���� ���� 
	CString mstr_file_name;		// ���������� ������ ���� �̸� ���� ���� 
	CString mstr_create_file;	// �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ���� 
	CString mstr_list_name, mstr_temp_data;  // �� �κк� �˶� �߻� Ƚ�� ���� ������ �α� ���� ���� ���� ���� 
	CString mstr_content;		// �� ���ο� ����� ���ڿ� ���� ���� ���� 
	COleDateTime time_cur;		// �˻��� �ð� ���� ���� ���� 
	CTime m_time_current;		// ������ ����� ���� �ð� ���� ���� ����
	char chr_buf[20]={0,};
	int mn_existence;			// ���� ���� ���� ���� �÷��� 
	char fileName[256]={0,};			// �˻��� ���� ���� ���� �Լ� 
	FILE  *fp ;					// ���Ͽ� ���� ������ ���� ���� 

	CString BackupName;
	CString mstr_cur_hour, mstr_cur_min, mstr_cur_sec;
	int nRet=BD_GOOD;

	if (s_msg.IsEmpty() == TRUE)  
	{
		return BD_ERROR;
	}

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


	mstr_file_name =  mstr_cur_year;
	mstr_file_name += mstr_cur_month; 
	mstr_file_name += mstr_cur_day; 
	mstr_create_file = "D:\\AMTLOG\\Motor\\" + mstr_file_name;
	mstr_create_file += ".TXT";

	sprintf(fileName, "%s", mstr_create_file);
	mn_existence = access(fileName,0) ;

	nRet = FileSizeCheck(mstr_create_file, 1048576, BD_YES); //size and rename
	if (nRet == 1) //file size over
	{
		BackupName = mstr_create_file + mstr_cur_hour + mstr_cur_min +  mstr_cur_sec + ".bak" ;
		rename(mstr_create_file, BackupName);
	}

	if ((fp = fopen(mstr_create_file,"a+")) == NULL)  
	{
		//AfxMessageBox("File open failure!..");
		sprintf(mc_normal_msg, "File open failure!.._4");
		return BD_ERROR;
	}

	// **************************************************************************
	// �α� ���Ͽ� ���� �߻��� �˶� ���� �����Ѵ�                                
	// **************************************************************************
	
	mstr_content = str_display_time;

	mstr_content += " : " + s_msg;

	fprintf(fp,"%s\n",mstr_content) ;

	if (ferror(fp))  
	{
		sprintf(mc_normal_msg,"Debug_File_Create ferror return error");	
		clearerr(fp); //2011.0418 

		fclose(fp) ;  //2011.0417  ���� ����
		return BD_ERROR;
	}
	fclose(fp);  // ������ �����Ѵ�.

	return nRet;
}

int CComizoaPublic::FileSizeCheck(CString s_filename, long l_size, int n_check)
{
	CFileFind finder;
	long Len=0, flag=0;
	BOOL bContinue;
	
	if (bContinue = finder.FindFile(s_filename))
	{	
		if (n_check == BD_YES)			// Size�� üũ�ϴ°��̸�...
		{
			finder.FindFile(s_filename);
			finder.FindNextFile();
			finder.GetFileName();
			Len = finder.GetLength();
			if (Len > l_size)
			{
				flag = 1;
			}
			finder.Close();	
		}
		else						// Size�� Ȯ���ϴ°��̸�...
		{
			finder.FindFile(s_filename);
			finder.FindNextFile();
			finder.GetFileName();
			Len = finder.GetLength();
			
			flag = Len;
			
			finder.Close();	
		}
	}
	
	return flag;
}