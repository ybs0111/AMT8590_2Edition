// CtlBd_Function.cpp: implementation of the CCtlBd_Function class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "CtlBd_Function.h"

#include "Cmmsdk.h"
#include "CmmsdkDef.h"
#include "ComizoaPublic.h"
#include "COMI_Manager.h"
#include "IO_Manager.h"
#include "FastechPublic_IO.h"

#include "FAS_HSSI.h"
#include "math.h"

#include "Public_Function.h"
#include "Variable.h"
#include "MyJamData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCtlBd_Function  CtlBdFunc;
CCtlBd_Function::CCtlBd_Function()
{

}

CCtlBd_Function::~CCtlBd_Function()
{
//st_ctlbd.n_TotalMotBoard_Number
}

int CCtlBd_Function::Board_Initialize(int n_mode)
{
	int nRet = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Motor Board Initialize 
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(CTLBD_MOTBD_TYPE == 0) //0:�Ľ��� ���带 ����ϴ� ����̸�, 1:Ŀ������ ���͸� ����ϴ� ��� 
	{
		st_ctlbd.n_TotalMotBoard_Number = 3;  //���ͺ��尡 3�� �ִ� 
		st_ctlbd.n_TotalMotorAxis_Number= 18; //������ �� ������ 18���̴�  
		st_ctlbd.n_MotorAxis_Number[0] = 8;   //0�� ���ͺ���� 8��� �����̴�  
		st_ctlbd.n_MotorAxis_Number[1] = 6;   //1�� ���ͺ���� 6��� �����̴� 
		st_ctlbd.n_MotorAxis_Number[2] = 4;   //2�� ���ͺ���� 4��� �����̴� 
/* 2011.0113 
		nRet = FAS_MOT.Initialize_MotBoard();
		if(nRet = CTLBD_RET_ERROR)
		{
			return CTLBD_RET_ERROR;
		}
*/
	}
	else if(CTLBD_MOTBD_TYPE == 1) //1:Ŀ������ ���带 ����ϴ� ����̸�, 1:Ŀ������ ���͸� ����ϴ� ��� 
	{


	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//I/O Board Initialize 
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(CTLBD_IOBD_TYPE == 0) //0: �Ľ��� I/O ���带 ó���Ҷ� ��� 
	{
		nRet = Initialize_FASIO_Board();
		if(nRet = CTLBD_RET_ERROR)
		{
			return CTLBD_RET_ERROR;
		}
	}

	return  CTLBD_RET_GOOD;
}

int CCtlBd_Function::Robot_Clash_Safety_Check(int n_Mode, int n_SourceAxis, int n_ReferenceAxis, double d_Safety_Gap, double d_TargetPos)
{//d_Safety_Gap = 300; //300mm �̻� ������ �־�� �Ѵ� //DC Loading ����Ʈ 

	//n_Mode => 0: ���� �̵��� �����ϰ� üũ�� �ϴ� ����, 1: ���Ͱ� �̵����϶� üũ�ϴ� ���� 
	int nRet = CTL_ERROR;
	char cJamcode[10] = {NULL};
	double dCurrentPos[2] = {0,0}, dCalPos[3] = {0,0,0}, dSafepos_gap[3] = {0,0,0}, dCurrMotPos = 0; 
	int nSafetyPos_Flag = CTL_NO; 

	//090914 ���ͺ��� ���ͷ�Ʈ �߻� ������ ������ �־� ���� �߰�  && dCurrentPos[1] < st_motor[n_ReferenceAxis].n_interrupt_position + 1
	
// 	dCurrentPos[0] = COMI.Get_MotCurrentPos(n_SourceAxis);    //���� �̵��ϴ� ��
// 	dCurrentPos[1] = COMI.Get_MotCurrentPos(n_ReferenceAxis); //����Ǵ� ���� ���� 
// 	//COMI.Get_Deviation_Position(n_SourceAxis, st_motor[n_SourceAxis].n_allow,st_motor[n_SourceAxis].d_deviation) ;
// 	if(n_SourceAxis == M_DCLDRBT_Y && n_ReferenceAxis == M_DCULDRBT_Y) //LOAD Robot�� DC Test Site�� �̵��ϴ� ���۽� ���  
// 	{
// 		//���� �浹 ������ DC TEST ����Ʈ�� �������� ������ ��ġ�� ���־� ���� ���� ������ ������ �˼� �ְ� �Ѵ� 
// 		dCalPos[0] = (st_motor[n_SourceAxis].d_pos[P_DCLDRBT_DCTEST] - dCurrentPos[0]);	//�ε� �κ�Ʈ 
// 		dCalPos[1] = (st_motor[n_ReferenceAxis].d_pos[P_DCULDRBT_DCTEST] - dCurrentPos[1]);//��ε� �κ�Ʈ 
// 		dCalPos[2] = dCalPos[1] + dCalPos[0];
// 
// 		//090915 ���� �߰� 
// 		if(d_TargetPos > st_motor[n_SourceAxis].d_pos[P_DCLDRBT_DCSAFETY_POS]) 
// 		{
// 			dCurrMotPos = COMI.Get_MotCurrentPos(M_DCULDRBT_Y);
// 			if(dCurrMotPos > st_motor[M_DCULDRBT_Y].n_interrupt_position)
// 			{//����� ���Ͱ� ���ͷ�Ʈ ��ġ�� ����� ���ѻ����̸� ������ ������ �߻����� source motor�� �����ؾ� �Ѵ� 
// 				nSafetyPos_Flag = CTL_NO;
// 			}
// 			else
// 			{//���۷��� ���Ͱ� ���� ��ġ�� ���ͷ�Ʈ ��ġ�� ��� �����̸� �̵��ϰ� �������̶�� �����ϰ� ������ �������� ����, �̵��Ѵ� 
// 				nSafetyPos_Flag = CTL_YES;
// 			}			
// 		}
// 		else
// 		{//Ÿ�� ��ġ�� ���� ���� ��ġ�� ����� ������ �����ϴ� �׳� �̵��ص� �ȴ�  
// 			dCalPos[2] = d_Safety_Gap + 1;//090925 ������ ���� �������� �޿��ϴ� ���� üũ�� �����Ѵ� 
// 			nSafetyPos_Flag = CTL_YES;
// 		}
// 
// 		/////////////////////////////////////////////////////////////
// 		//2011.0123 ���� �߰�, �߸��� ƼĪ�� �߻��� Ȯ������ �߰� 
// 		/////////////////////////////////////////////////////////////
// 		if(d_TargetPos != 0) //d_TargetPos == 0 Ȩüũ�ô� ���� ���� 
// 		{
// 			dSafepos_gap[0] = st_motor[n_SourceAxis].d_pos[P_DCLDRBT_DCTEST] - st_motor[n_SourceAxis].d_pos[P_DCLDRBT_DCSAFETY_POS];
// 			dSafepos_gap[1] = st_motor[n_ReferenceAxis].d_pos[P_DCULDRBT_DCTEST] - st_motor[n_ReferenceAxis].d_pos[P_DCULDRBT_DCSAFETY_POS];
// 			if(dSafepos_gap[0] > dSafepos_gap[1]) //source �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 			else if(dSafepos_gap[0] < dSafepos_gap[1]) //reference �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[1];
// 			}
// 			else 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 
// 			if(dSafepos_gap[2] < (d_Safety_Gap - 10)) //2011.0123 �߰� //���� �����Ǿ� �ִ� ������ġ ���� clash safety pos - 10mm ������ ������ ���� �߻� 
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 
// 				st_msg.mstr_abnormal_msg.Format("[Safety]Safety Pos[%lf] < Clash Pos[%lf - 10mm]", dSafepos_gap[2], d_Safety_Gap);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 		}
// 
// 
// 		//�� ���� Y�� �ӵ� ������ ���ƾ� �Ѵ� 
// 		if(dCalPos[2] > d_Safety_Gap && nSafetyPos_Flag == CTL_YES) //��ȣ ���� �� ���� ���� ��(d_Safety_Gap) �̻����� ������ ��ġ�� �־� ������ ������ �����̴� 
// 		{
// 			nRet = CTL_GOOD; //���� ���� ������ �ƴϴ� 
// 		}
// 		else
// 		{ //������ ��ġ���� �� ������ �־� ������ ���°� �ƴϴ� ���� ���̸� ���߾�� �Ѵ� 
// 			//000009 0 A "Robot �浹���� ���� ������ �߻�-Safety Position Check Error - (Load Robot Y & Unload Robot Y)."
// 			nRet = CTL_ERROR;
// 
// 			if(n_Mode == 1) //���Ͱ� �̵��� ������ üũ�Ͽ� ������ �߻��ϸ� �ش� �̵� ���͸� �� ���� �Ѵ� 
// 			{
// 				cmmSxStopEmg(n_SourceAxis);
// 				CtlBdFunc.ms_ErrMsg.Format("Clash Error Motor E_Stop MotorNum:%d", n_SourceAxis);
// 				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			}
// 
// 			sprintf(cJamcode, "%02d0009", n_SourceAxis);  
// 			alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; //st_work.mn_run_status = CTL_dWARNING;
// 			CtlBdFunc.ms_ErrMsg.Format("Clash_Axis:%d, Mode:%d, Source:%4.3f, Reference:%4.3f, TS:%4.3f, TR:%4.3f, TT:%4.3f",n_SourceAxis, n_Mode, dCurrentPos[0], dCurrentPos[1], dCalPos[0], dCalPos[1], dCalPos[2]);
// 			if (st_handler.cwnd_list != NULL && n_Mode == 1)  // ����Ʈ �� ȭ�� ����
// 			{
// 				st_msg.mstr_abnormal_msg = CtlBdFunc.ms_ErrMsg;
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 			CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 		}
// 	}
// 	else if(n_SourceAxis == M_DCULDRBT_Y && n_ReferenceAxis == M_DCLDRBT_Y) //UNLOAD Robot�� DC Test Site�� �̵��ϴ� ���۽� ���  
// 	{
// 		//���� �浹 ������ DC TEST ����Ʈ�� �������� ������ ��ġ�� ���־� ���� ���� ������ ������ �˼� �ְ� �Ѵ� 
// 		dCalPos[0] = (st_motor[n_SourceAxis].d_pos[P_DCULDRBT_DCTEST] - dCurrentPos[0]);	//�ε� �κ�Ʈ 
// 		dCalPos[1] = (st_motor[n_ReferenceAxis].d_pos[P_DCLDRBT_DCTEST] - dCurrentPos[1]);//��ε� �κ�Ʈ 
// 		dCalPos[2] = dCalPos[1] + dCalPos[0];
// 
// 		//090915 ���� �߰� 
// 		if(d_TargetPos > st_motor[n_SourceAxis].d_pos[P_DCULDRBT_DCSAFETY_POS]) 
// 		{
// 			dCurrMotPos = COMI.Get_MotCurrentPos(M_DCLDRBT_Y);
// 			if(dCurrMotPos > st_motor[M_DCLDRBT_Y].n_interrupt_position)
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 			}
// 			else
// 			{
// 				nSafetyPos_Flag = CTL_YES;
// 			}
// 		}
// 		else
// 		{
// 			dCalPos[2] = d_Safety_Gap + 1;//090925 ������ ���� �������� �޿��ϴ� ���� üũ�� �����Ѵ� 
// 			nSafetyPos_Flag = CTL_YES;
// 		}
// 
// 		/////////////////////////////////////////////////////////////
// 		//2011.0123 ���� �߰�, �߸��� ƼĪ�� �߻��� Ȯ������ �߰� 
// 		/////////////////////////////////////////////////////////////
// 		if(d_TargetPos != 0) //d_TargetPos == 0 Ȩüũ�ô� ���� ���� 
// 		{
// 			dSafepos_gap[0] = st_motor[n_SourceAxis].d_pos[P_DCULDRBT_DCTEST] - st_motor[n_SourceAxis].d_pos[P_DCULDRBT_DCSAFETY_POS];
// 			dSafepos_gap[1] = st_motor[n_ReferenceAxis].d_pos[P_DCLDRBT_DCTEST] - st_motor[n_ReferenceAxis].d_pos[P_DCLDRBT_DCSAFETY_POS];
// 			if(dSafepos_gap[0] > dSafepos_gap[1]) //source �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 			else if(dSafepos_gap[0] < dSafepos_gap[1]) //reference �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[1];
// 			}
// 			else 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 
// 			if(dSafepos_gap[2] < (d_Safety_Gap - 10)) //2011.0123 �߰� //���� �����Ǿ� �ִ� ������ġ ���� clash safety pos - 10mm ������ ������ ���� �߻� 
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 
// 				st_msg.mstr_abnormal_msg.Format("[Safety]Safety Pos[%lf] < Clash Pos[%lf - 10mm]", dSafepos_gap[2], d_Safety_Gap);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 		}
// 		
// 		//�� ���� Y�� �ӵ� ������ ���ƾ� �Ѵ� 
// 		if(dCalPos[2] > d_Safety_Gap && nSafetyPos_Flag == CTL_YES) //��ȣ ���� �� ���� ���� ��(d_Safety_Gap) �̻����� ������ ��ġ�� �־� ������ ������ �����̴� 
// 		{
// 			//CtlBdFunc.ms_ErrMsg.Format("Axis:%d, Source:%.3f, Reference:%.3f, TS:%.3f, TR:%.3f, TT:%.3f",n_SourceAxis, dCurrentPos[0], dCurrentPos[1], dCalPos[0], dCalPos[1], dCalPos[2]);
// 			//if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
// 			//{
// 			//	st_msg.mstr_abnormal_msg = CtlBdFunc.ms_ErrMsg;
// 			//	st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][0] = CTL_YES; st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][1] = 0; //2011.0120 ����   // ���� ���� ��� ��û
// 			//}
// 			nRet = CTL_GOOD; //���� ���� ������ �ƴϴ� 
// 		}
// 		else
// 		{ //������ ��ġ���� �� ������ �־� ������ ���°� �ƴϴ� ���� ���̸� ���߾�� �Ѵ� 
// 			//000009 0 A "Robot �浹���� ���� ������ �߻�-Safety Position Check Error - (Load Robot Y & Unload Robot Y)."
// 			nRet = CTL_ERROR;			
// 			if(n_Mode == 1) //���Ͱ� �̵��� ������ üũ�Ͽ� ������ �߻��ϸ� �ش� �̵� ���͸� �� ���� �Ѵ� 
// 			{
// 				cmmSxStopEmg(n_SourceAxis);
// 				CtlBdFunc.ms_ErrMsg.Format("Clash Error Motor E_Stop MotorNum:%d", n_SourceAxis);
// 				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			}
// 			
// 			sprintf(cJamcode, "%02d0009", n_SourceAxis);  
// 			alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; //st_work.mn_run_status = CTL_dWARNING;
// 			CtlBdFunc.ms_ErrMsg.Format("Clash_Axis:%d, Mode:%d, Source:%4.3f, Reference:%4.3f, TS:%4.3f, TR:%4.3f, TT:%4.3f",n_SourceAxis, n_Mode, dCurrentPos[0], dCurrentPos[1], dCalPos[0], dCalPos[1], dCalPos[2]);
// 			if (st_handler.cwnd_list != NULL && n_Mode == 1)  // ����Ʈ �� ȭ�� ����
// 			{
// 				st_msg.mstr_abnormal_msg = CtlBdFunc.ms_ErrMsg;
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 			CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 		}
// 	}
// 	else if(n_SourceAxis == M_INSERTRBT_Y && n_ReferenceAxis == M_REMOVERBT_Y) //Insert Robot�� BIB Table�� �̵��ϴ� ���� 
// 	{
// 		//���� �浹 ������ DC TEST ����Ʈ�� �������� ������ ��ġ�� ���־� ���� ���� ������ ������ �˼� �ְ� �Ѵ� 
// 		dCalPos[0] = (st_motor[n_SourceAxis].d_pos[P_INSERTRBT_BIBTABLE] - dCurrentPos[0]);	//�ε� �κ�Ʈ 
// 		dCalPos[1] = (st_motor[n_ReferenceAxis].d_pos[P_REMOVERBT_BIBTABLE] - dCurrentPos[1]);//��ε� �κ�Ʈ 
// 
// 		dCalPos[2] = dCalPos[1] + dCalPos[0];
// 
// 		//090915 ���� �߰� 
// 		if(d_TargetPos > st_motor[n_SourceAxis].d_pos[P_INSERTRBT_SAFETY_POS]) 
// 		{
// 			dCurrMotPos = COMI.Get_MotCurrentPos(M_REMOVERBT_Y);
// 			if(dCurrMotPos > st_motor[M_REMOVERBT_Y].n_interrupt_position)
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 			}
// 			else
// 			{
// 				nSafetyPos_Flag = CTL_YES;
// 			}
// 		}
// 		else
// 		{
// 			dCalPos[2] = d_Safety_Gap + 1;//090925 ������ ���� �������� �޿��ϴ� ���� üũ�� �����Ѵ� 
// 			nSafetyPos_Flag = CTL_YES;
// 		}
// 
// 		/////////////////////////////////////////////////////////////
// 		//2011.0123 ���� �߰�, �߸��� ƼĪ�� �߻��� Ȯ������ �߰� 
// 		/////////////////////////////////////////////////////////////
// 		{
// 			dSafepos_gap[0] = st_motor[n_SourceAxis].d_pos[P_INSERTRBT_BIBTABLE] - st_motor[n_SourceAxis].d_pos[P_INSERTRBT_SAFETY_POS];
// 			dSafepos_gap[1] = st_motor[n_ReferenceAxis].d_pos[P_REMOVERBT_BIBTABLE] - st_motor[n_ReferenceAxis].d_pos[P_REMOVERBT_BIBTABLE_SAFETY_POS];
// 			if(dSafepos_gap[0] > dSafepos_gap[1]) //source �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 			else if(dSafepos_gap[0] < dSafepos_gap[1]) //reference �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[1];
// 			}
// 			else 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 
// 			if(dSafepos_gap[2] < (d_Safety_Gap - 10)) //2011.0123 �߰� //���� �����Ǿ� �ִ� ������ġ ���� clash safety pos - 10mm ������ ������ ���� �߻� 
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 
// 				st_msg.mstr_abnormal_msg.Format("[Safety]Safety Pos[%lf] < Clash Pos[%lf - 10mm]", dSafepos_gap[2], d_Safety_Gap);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 		}
// 
// 
// 		//�� ���� Y�� �ӵ� ������ ���ƾ� �Ѵ� 
// 		if(dCalPos[2] > d_Safety_Gap && nSafetyPos_Flag == CTL_YES) //��ȣ ������ ��ġ�� �־� ������ ������ �����̴� 
// 		{
// 			nRet = CTL_GOOD; //���� ���� ������ �ƴϴ� 
// 		}
// 		else
// 		{ //������ ��ġ���� �� ������ �־� ������ ���°� �ƴϴ� ���� ���̸� ���߾�� �Ѵ� 
// 			//000009 0 A "Robot �浹���� ���� ������ �߻�-Safety Position Check Error - (Load Robot Y & Unload Robot Y)."
// 			nRet = CTL_ERROR;
// 			if(n_Mode == 1) //���Ͱ� �̵��� ������ üũ�Ͽ� ������ �߻��ϸ� �ش� �̵� ���͸� �� ���� �Ѵ� 
// 			{
// 				cmmSxStopEmg(n_SourceAxis);
// 				CtlBdFunc.ms_ErrMsg.Format("Clash Error Motor E_Stop MotorNum:%d", n_SourceAxis);
// 				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			}	
// 			sprintf(cJamcode, "%02d0009", n_SourceAxis);  
// 			alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; //st_work.mn_run_status = CTL_dWARNING;
// 			CtlBdFunc.ms_ErrMsg.Format("Clash_Axis:%d, Mode:%d, Source:%4.3f, Reference:%4.3f, TS:%4.3f, TR:%4.3f, TT:%4.3f",n_SourceAxis, n_Mode, dCurrentPos[0], dCurrentPos[1], dCalPos[0], dCalPos[1], dCalPos[2]);
// 			if (st_handler.cwnd_list != NULL && n_Mode == 1)  // ����Ʈ �� ȭ�� ����
// 			{
// 				st_msg.mstr_abnormal_msg = CtlBdFunc.ms_ErrMsg;
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 			CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			//CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_SourceAxis, st_work.mn_run_status, alarm.mstr_code);  
// 		}
// 	}
// 	else if(n_SourceAxis == M_REMOVERBT_Y && n_ReferenceAxis == M_INSERTRBT_Y) //Remove Robot�� BIB Table�� �̵��ϴ� ���� 
// 	{
// 		//���� �浹 ������ DC TEST ����Ʈ�� �������� ������ ��ġ�� ���־� ���� ���� ������ ������ �˼� �ְ� �Ѵ� 
// 		dCalPos[0] = (st_motor[n_SourceAxis].d_pos[P_REMOVERBT_BIBTABLE] - dCurrentPos[0]);	//�ε� �κ�Ʈ 
// 		dCalPos[1] = (st_motor[n_ReferenceAxis].d_pos[P_INSERTRBT_BIBTABLE] - dCurrentPos[1]);//��ε� �κ�Ʈ 
// 		
// 		dCalPos[2] = dCalPos[1] + dCalPos[0];
// 
// 		//090915 ���� �߰� 
// 		if(d_TargetPos > st_motor[n_SourceAxis].d_pos[P_REMOVERBT_BIBTABLE_SAFETY_POS]) 
// 		{
// 			dCurrMotPos = COMI.Get_MotCurrentPos(M_INSERTRBT_Y);
// 			if(dCurrMotPos > st_motor[M_INSERTRBT_Y].n_interrupt_position)
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 			}
// 			else
// 			{
// 				nSafetyPos_Flag = CTL_YES;
// 			}
// 		}
// 		else
// 		{
// 			dCalPos[2] = d_Safety_Gap + 1;	//090925 ������ ���� �������� �޿��ϴ� ���� üũ�� �����Ѵ� 
// 			nSafetyPos_Flag = CTL_YES;
// 		}
// 
// 		/////////////////////////////////////////////////////////////
// 		//2011.0123 ���� �߰�, �߸��� ƼĪ�� �߻��� Ȯ������ �߰� 
// 		/////////////////////////////////////////////////////////////
// 		if(d_TargetPos != 0) //d_TargetPos == 0 Ȩüũ�ô� ���� ���� 
// 		{
// 			dSafepos_gap[0] = st_motor[n_SourceAxis].d_pos[P_REMOVERBT_BIBTABLE] - st_motor[n_SourceAxis].d_pos[P_REMOVERBT_BIBTABLE_SAFETY_POS];
// 			dSafepos_gap[1] = st_motor[n_ReferenceAxis].d_pos[P_INSERTRBT_BIBTABLE] - st_motor[n_ReferenceAxis].d_pos[P_INSERTRBT_SAFETY_POS];
// 			if(dSafepos_gap[0] > dSafepos_gap[1]) //source �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 			else if(dSafepos_gap[0] < dSafepos_gap[1]) //reference �� ���� ��ġ ���� ū ���� 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[1];
// 			}
// 			else 
// 			{
// 				dSafepos_gap[2] = dSafepos_gap[0];
// 			}
// 
// 			if(dSafepos_gap[2] < (d_Safety_Gap - 10)) //2011.0123 �߰� //���� �����Ǿ� �ִ� ������ġ ���� clash safety pos - 10mm ������ ������ ���� �߻� 
// 			{
// 				nSafetyPos_Flag = CTL_NO;
// 
// 				st_msg.mstr_abnormal_msg.Format("[Safety]Safety Pos[%lf] < Clash Pos[%lf - 10mm]", dSafepos_gap[2], d_Safety_Gap);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 		}
// 		
// 		//�� ���� Y�� �ӵ� ������ ���ƾ� �Ѵ� 
// 		if(dCalPos[2] > d_Safety_Gap && nSafetyPos_Flag == CTL_YES) //��ȣ ������ ��ġ�� �־� ������ ������ �����̴� 
// 		{
// 			nRet = CTL_GOOD; //���� ���� ������ �ƴϴ� 
// 		}
// 		else
// 		{ //������ ��ġ���� �� ������ �־� ������ ���°� �ƴϴ� ���� ���̸� ���߾�� �Ѵ� 
// 			//000009 0 A "Robot �浹���� ���� ������ �߻�-Safety Position Check Error - (Load Robot Y & Unload Robot Y)."
// 			nRet = CTL_ERROR;
// 			if(n_Mode == 1) //���Ͱ� �̵��� ������ üũ�Ͽ� ������ �߻��ϸ� �ش� �̵� ���͸� �� ���� �Ѵ� 
// 			{
// 				cmmSxStopEmg(n_SourceAxis);
// 				CtlBdFunc.ms_ErrMsg.Format("Clash Error Motor E_Stop MotorNum:%d", n_SourceAxis);
// 				CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			}	
// 			sprintf(cJamcode, "%02d0009", n_SourceAxis);  
// 			alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; //st_work.mn_run_status = CTL_dWARNING;
// 			CtlBdFunc.ms_ErrMsg.Format("Clash_Axis:%d, Mode:%d, Source:%4.3f, Reference:%4.3f, TS:%4.3f, TR:%4.3f, TT:%4.3f",n_SourceAxis, n_Mode, dCurrentPos[0], dCurrentPos[1], dCalPos[0], dCalPos[1], dCalPos[2]);
// 			if (st_handler.cwnd_list != NULL && n_Mode == 1)  // ����Ʈ �� ȭ�� ����
// 			{
// 				st_msg.mstr_abnormal_msg = CtlBdFunc.ms_ErrMsg;
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
// 			}
// 			CtlBdFunc.Send_Error_Message(MOT_ERR_MSG, n_SourceAxis, alarm.mstr_code, CtlBdFunc.ms_ErrMsg); //2011.0123 
// 			//CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_SourceAxis, st_work.mn_run_status, alarm.mstr_code);  
// 		}
// 	}
// 		
	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inposition ���� �� �Ÿ��� �ӵ��� �����Ѵ� 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CCtlBd_Function::MotorSpeed_Control(int n_Axis, double d_CurrentPos, double d_TargetPos, double * dp_Speed)
{
	double dCurrentPos = 0, dTargetPos = 0, dVal =0, d_abs_val = 0, dAccDecTime=0; 
	int nRetStatus=0;

// 	if(n_Axis == M_DCLDRBT_Z || n_Axis == M_DCULDRBT_Z || n_Axis == M_ULDRBT_Z)
// 	{
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);		
// 
// 		//��ǥ��ġ ��� ����� ==> ������ġ - ��ǥ�̵� ��ġ �̴� 
// 		dVal = dCurrentPos - d_TargetPos;
// 		if(st_motor[n_Axis].d_pos[0] >= d_TargetPos) //P_DCLDRBT_Z_SAFETY == 0 ,��ǥ ������ ������ġ�� ������ ������ �ӵ��� �̵� 
// 		{
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 			//UP�Ҷ��� Inposition�� ����  ���� 
// 			COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 		}
// 		else if(dVal > 0) //�� ��ġ���� ����� ��ġ(Ȩ ��ġ) �� �̵��������� + �� �߻� , ���Ͱ� UP �� �� �߻� 
// 		{
// 			//���� ���õǾ��ִ� �� ��� 
// 			//650,000 13,000,000 13,000,000   ==> 16mm �̵��ϴµ� 65ms �ҿ� 
// 			//300,000  9,000000   9,000000    ==> 16mm �̵��ϴµ� 80ms �ҿ� 
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 
// 			//UP�Ҷ� �Ǵ� ��Ȯ�� ��ǥ�������� ���� �ʾƵ� �Ǵ� �����̸� Inposition�� ���� ���� 
// 			COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 		} //12mm ���Ϸ� ������ �� 
// 		else
// 		{
// 			if(n_Axis == M_DCLDRBT_Z || n_Axis == M_DCULDRBT_Z )
// 			{
// 				if(dVal > -12) //-1 ~ -19 DC�ε�κ��� DC ���Ͽ� ������ - �� �߻�  //Ȩ ��ġ���� ���� �������� �̵��Ϸ��� - ���� �߻��Ѵ� 
// 				{//dAccPPS = (d_work - st_motor[n_Axis].d_initial_speed) / (d_accel_time / 1000);
// 					//dAccDecTime = (d_work - st_motor[n_Axis].d_initial_speed) / (dAccPPS / 1000);
// 					dAccDecTime = (300000 - st_motor[n_Axis].d_initial_speed) / (5000000 / 1000); //60ms		
// 					dp_Speed[0] = 300000; dp_Speed[1] = dAccDecTime; dp_Speed[2] = dAccDecTime; //���� �޼� ���� 9,000,000 �̴� 
// 					
// 					COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 				} 
// 				//20mm ���Ϸ� ������ �� 
// 				else if(dVal > -38) //-1 ~ -19 DC�ε�κ��� DC ���Ͽ� ������ - �� �߻�  //Ȩ ��ġ���� ���� �������� �̵��Ϸ��� - ���� �߻��Ѵ� 
// 				{//dAccPPS = (d_work - st_motor[n_Axis].d_initial_speed) / (d_accel_time / 1000);
// 				 //dAccDecTime = (d_work - st_motor[n_Axis].d_initial_speed) / (dAccPPS / 1000);
// 					dAccDecTime = (300000 - st_motor[n_Axis].d_initial_speed) / (9000000 / 1000); //dAccDecTime = 33 ms			
// 					dp_Speed[0] = 300000; dp_Speed[1] = dAccDecTime; dp_Speed[2] = dAccDecTime; //���� �޼� ���� 9,000,000 �̴� 
// 
// 					COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 				} //20mm�̻� �������� 
// 				else //if(dVal < -38)  //-20 ���� �ε��κ��� Ʈ���̿��� ������, ��ε� �κ��� �μ�Ʈ ���� bottom�� ������ �߻� 
// 				{
// 					//dAccDecTime = (650000 - st_motor[n_Axis].d_initial_speed) / (12000000 / 1000); //dAccDecTime = 300 ms			
// 					//dp_Speed[0] = 650000; dp_Speed[1] = dAccDecTime; dp_Speed[2] = dAccDecTime; //���� �޼� ���� 9,000,000 �̴� 			
// 					dAccDecTime = (st_motor[n_Axis].d_spd_vel[0] - st_motor[n_Axis].d_initial_speed) / (12000000 / 1000); //dAccDecTime = 300 ms			
// 					dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = dAccDecTime; dp_Speed[2] = dAccDecTime; //���� �޼� ���� 9,000,000 �̴� 		
// 					
// 					COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 			
// 				}
// 			}
// 
// 			if(n_Axis == M_DCLDRBT_Z)
// 			{
// 				dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// ///* 2011.0126
// 				if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_LDPLATE_PICK])
// 				{
// 					//091012 dp_Speed[0] = 650000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 					dp_Speed[0] = 450000; dp_Speed[1] = 100; dp_Speed[2] = 50; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_DCBUFF_PICK])
// 				{
// 					dp_Speed[0] = 650000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_DCTEST_PICK])
// 				{
// 					dp_Speed[0] = 450000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_LDPLATE_PLACE])
// 				{
// 					dp_Speed[0] = 650000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_LDBUFF_PLACE])
// 				{
// 					dp_Speed[0] = 650000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCLDRBT_Z].d_pos[P_DCLDRBT_Z_DCTEST_PLACE])
// 				{
// 					//dp_Speed[0] = 450000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 					//091012 dp_Speed[0] = 380000; dp_Speed[1] = 50; dp_Speed[2] = 50; //
// 					dp_Speed[0] = 380000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 				}
// 				else
// 				{
// 					dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 				}
// //*/
// 				COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 			}
// 			else if(n_Axis == M_DCULDRBT_Z)
// 			{
// 				dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 
// ///* 2011.0126 
// 				if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_DCTEST_PICK])
// 				{
// 					dp_Speed[0] = 550000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_DCBUFF_PICK])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_INSERTBUFF_TOP_PICK])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_INSERTBUFF_BOTTOM_PICK])
// 				{
// 					dp_Speed[0] = 550000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_DCTEST_PLACE])
// 				{
// 					dp_Speed[0] = 550000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_DCBUFF_PLACE])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_INSERTBUFF_TOP_PLACE])
// 				{
// 					//dp_Speed[0] = 400000; dp_Speed[1] = 50; dp_Speed[2] = 50; //  
// 					dp_Speed[0] = 400000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_DCULDRBT_Z].d_pos[P_DCULDRBT_Z_INSERTBUFF_BOTTOM_PLACE])
// 				{
// 					//dp_Speed[0] = 550000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 					dp_Speed[0] = 550000; dp_Speed[1] = 50; dp_Speed[2] = 100; //  
// 				}
// 				else
// 				{
// 					dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 				}
// //*/
// 				COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 			}
// 			else// if(n_Axis == M_ULDRBT_Z)
// 			{//090909 
// 				if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_REMOVEBUFF_TOP_PICK])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 100; dp_Speed[2] = 150; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_REMOVEBUFF_MIDDLE_PICK])
// 				{
// 					dp_Speed[0] = 500000; dp_Speed[1] = 100; dp_Speed[2] = 150; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_REMOVEBUFF_BOTTOM_PICK])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 80; dp_Speed[2] = 150; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_MANUALBUFF_PICK])
// 				{
// 					dp_Speed[0] = 500000; dp_Speed[1] = 100; dp_Speed[2] = 150; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_MANUALBUFF_PLACE])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 100; dp_Speed[2] = 150; //  
// 				}
// 				else if(d_TargetPos == st_motor[M_ULDRBT_Z].d_pos[P_ULDRBT_Z_ULDPLATE_PLACE])
// 				{
// 					dp_Speed[0] = 400000; dp_Speed[1] = 80; dp_Speed[2] = 150; //  
// 				}
// 				else
// 				{
// 					dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 				}
// 				COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 			
// 			}
// 		}
// 	}
// 	else if(n_Axis == M_SORTBUFFRBT_Z || n_Axis == M_INSERTRBT_Z || n_Axis == M_REMOVERBT_Z)
// 	{
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);		
// 
// 		//��ǥ��ġ ��� ����� ==> ������ġ - ��ǥ�̵� ��ġ �̴� 
// 		dVal = dCurrentPos - d_TargetPos;
// 		if(dVal > 0) //�� ��ġ���� ����� ��ġ(Ȩ ��ġ) �� �̵��������� + �� �߻� , ���Ͱ� UP �� �� �߻� 
// 		{
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 			//UP�Ҷ� �Ǵ� ��Ȯ�� ��ǥ�������� ���� �ʾƵ� �Ǵ� �����̸� Inposition�� ���� ���� 
// 
// 			if(n_Axis != M_INSERTRBT_Z) //2011.0302 ��鸲 ������ ���� 
// 			{
// 				COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmFALSE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 
// 			}
// 		}
// 		else //motor �� �ٿ� �Ҷ� �߻� 
// 		{
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; //���� �޼� ���� 9,000,000 �̴�
// 			COMI.Set_Motor_IO_Property(n_Axis, cmINP_EN, cmTRUE); //cmINP_EN=9 //cmFALSE = 0 INP ��Ȱ��, cmTRUE = 1 INP Ȱ�� 		
// 		}
// 	}
// 	/*
// 	else if(n_Axis == M_DCLDRBT_X || n_Axis == M_DCULDRBT_X) //���� ������ 
// 	{//�κ�Ʈ X ��ũ�� ���ʹ� ������ �ӵ��� �Լ� �̵��Ͽ� ���� �ʿ����.
// 		dAccDecTime = (st_motor[n_Axis].d_spd_vel[0] - st_motor[n_Axis].d_initial_speed) / (9750000 / 1000); //dAccDecTime = 66.6 ms	//�̵����� �ð� : 289ms		
// 		dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = dAccDecTime; dp_Speed[2] = dAccDecTime; //���� �޼� ���� 9,000,000 �̴� 
// 	}*/
// 	else if(n_Axis == M_DCLDRBT_Y || n_Axis == M_DCULDRBT_Y)// || n_Axis == M_ULDRBT_Y)
// 	{
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);
// 		d_abs_val = fabs(dCurrentPos - d_TargetPos);
// 		dVal = dCurrentPos - d_TargetPos; //090830 fabs(dCurrentPos - d_TargetPos);
// 		if(d_abs_val < st_size.d_tray_dcld_mm_y + 1) //��ġ Y + 2 mm ���� ������ ���ӵ��� �ٿ��Ѵ� , ���� ������ 
// 		{
// 			dp_Speed[0] = 200000; dp_Speed[1] = 100; dp_Speed[2] = 100; //���� �޼� ���� 9,000,000 �̴�
// 		}
// 		else if(n_Axis == M_DCLDRBT_Y && st_motor[M_DCLDRBT_Y].d_pos[P_DCLDRBT_DCSAFETY_POS] == d_TargetPos && dVal < 0) //���Ͱ� ���� �����̸� 
// 		{
// 			dp_Speed[0] = 100000; dp_Speed[1] = 100; dp_Speed[2] = 100; //���� �޼� ���� 9,000,000 �̴�
// 		}
// 		else if(n_Axis == M_DCULDRBT_Y && st_motor[M_DCULDRBT_Y].d_pos[P_DCULDRBT_DCSAFETY_POS] == d_TargetPos && dVal < 0) //���Ͱ� ���� �����̸� 
// 		{
// 			dp_Speed[0] = 100000; dp_Speed[1] = 100; dp_Speed[2] = 100; //���� �޼� ���� 9,000,000 �̴�
// 		}
// 		else
// 		{
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; 
// 		}
// 	}
// 	else if(n_Axis == M_REMOVERBT_Y) 
// 	{//090907
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);
// 		d_abs_val = fabs(dCurrentPos - d_TargetPos);
// 		dVal = dCurrentPos - d_TargetPos; //090830 fabs(dCurrentPos - d_TargetPos);
// 		if(n_Axis == M_REMOVERBT_Y && st_motor[M_REMOVERBT_Y].d_pos[P_REMOVERBT_BIBTABLE_SAFETY_POS] == d_TargetPos && dVal < 0) //���Ͱ� ���� �����̸� 
// 		{
// 			dp_Speed[0] = 10000; dp_Speed[1] = 100; dp_Speed[2] = 100; //���� �޼� ���� 9,000,000 �̴�
// 		}		
// 		else
// 		{
// 			dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; 
// 		}
// 	}
// 	else if(n_Axis == M_ULDRBT_Y)//���� �ӵ� �� 
// 	{
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);
// 		dVal = fabs(dCurrentPos - d_TargetPos);
// 		if(dVal < 50)
// 		{
// 			dp_Speed[0] = 50; dp_Speed[1] = 50; dp_Speed[2] = 50; //speed rate�� 50%�� ���� �Ѵ�
// 		}
// 		else if(dVal < 100) //100mm���� ��ġ 
// 		{
// 			dp_Speed[0] = 60; dp_Speed[1] = 60; dp_Speed[2] = 60; //speed rate�� 50%�� ���� �Ѵ�
// 		}
// 		else if(dVal < 200) //100mm���� ��ġ 
// 		{
// 			dp_Speed[0] = 70; dp_Speed[1] = 70; dp_Speed[2] = 70; //speed rate�� 50%�� ���� �Ѵ�
// 		}
// 		else
// 		{
// 			dp_Speed[0] = 100; dp_Speed[1] = 100; dp_Speed[2] = 100; //speed rate�� 100%�� ���� �Ѵ�
// 		}
// 	}
// 	else if(n_Axis == M_ULDRBT_X) //���� �ӵ� �� 
// 	{
// 		dCurrentPos = COMI.Get_MotCurrentPos(n_Axis);
// 		dVal = fabs(dCurrentPos - d_TargetPos);
// 		if(dVal > 400)
// 		{
// 			dp_Speed[0] = 50; dp_Speed[1] = 50; dp_Speed[2] = 50; //speed rate�� 50%�� ���� �Ѵ�
// 		}		
// 		else
// 		{
// 			dp_Speed[0] = 100; dp_Speed[1] = 100; dp_Speed[2] = 100; //speed rate�� 100%�� ���� �Ѵ�
// 		}
// 	}
// 	else
// 	{
// 		dp_Speed[0] = st_motor[n_Axis].d_spd_vel[0]; dp_Speed[1] = st_motor[n_Axis].d_spd_vel[1]; dp_Speed[2] = st_motor[n_Axis].d_spd_vel[2]; 
// 	}
 
	return CTL_GOOD;
}


int CCtlBd_Function::Alarm_Error_Occurrence(int n_Count, int n_Type, int n_Status, CString s_JamCode)
{
      alarm.mn_count_mode = n_Count; alarm.mn_type_mode = n_Type; COMI.mn_run_status = n_Status; 
	  alarm.mstr_code = s_JamCode; 
	  sprintf(alarm.mc_code, s_JamCode);
	  
	  MyJamData.On_Alarm_Info_Set_to_Variable(alarm.mstr_code);
	  
	  if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	  {
		  if (MOT_DEBUG)
		  {
			  sprintf(st_msg.c_abnormal_msg, "[ALARM]=> [%d] [%s] [%s]", alarm.mn_count_mode, alarm.mstr_code, st_alarm.mstr_cur_msg);
			  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		  }
		  else
		  {
//			  st_msg.mstr_abnormal_msg.Format("[%s] [%s]", alarm.mstr_code, st_alarm.mstr_cur_msg);
			  sprintf(st_msg.c_abnormal_msg, "[%d] [%s] [%s]", alarm.mn_count_mode, alarm.mstr_code, st_alarm.mstr_cur_msg);
			  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		  }
		  //2015.0514
		  st_handler.m_strLogEvent = Func.Get_AlarmPartName(atoi(alarm.mstr_code));
	  }
// 	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);	  

	return CTL_GOOD;
}

//2011.0123 �Ϻ� ���� ���� 
//�̰��� �˶� �޼��� �� �Ϻ� ������ ���Ϸ� �����ϴ� ��Ȱ�� ����Ѵ� 
int CCtlBd_Function::Send_Error_Message(int n_Mode, int n_Axis, CString s_JamCode, CString s_JamMsg)
{
	long lErrorCode;
	short int nErrorParseAxis;
	short int nErrorParseReason;
	char cErrorMsg[200];
	CString sMsg, sTemp;
	
	memset(&cErrorMsg, 0, sizeof(cErrorMsg));  // ������ ���� ���� �ʱ�ȭ 

	//2011.0123 �Ʒ����� �߰� if(MOT_DEBUG) Func.On_LogFile_Add(3, CtlBdFunc.ms_ErrMsg);

	//2011.0123 �Ʒ����� �߰� 
	if(n_Mode == MOT_ERR_MSG) 
	{//���� �޼����� �޾� ����Ʈ ȭ�鿡 ���÷��� �Ѵ�   
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
//			st_msg.mstr_abnormal_msg = s_JamMsg;
			sprintf(st_msg.c_abnormal_msg,s_JamMsg);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		}		
	}
	else if(n_Mode == MOT_ERR_CODE)
	{//jamcode  ���� 		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
//			st_msg.mstr_abnormal_msg = s_JamMsg;
			sprintf(st_msg.c_abnormal_msg, s_JamMsg);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		}	
	}
	else
	{//jamcode  ���� 		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
//			st_msg.mstr_normal_msg = s_JamMsg;
			sprintf(st_msg.c_normal_msg, s_JamMsg);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}	
	}//2011.0123 �߰� 







/*
	if(n_Mode == MOT_ERR_MSG) 
	{//���� �޼����� �޾� ����Ʈ ȭ�鿡 ���÷��� �Ѵ�   
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
			st_msg.mstr_abnormal_msg = s_JamMsg;
			st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][0] = CTL_YES; st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][1] = 0; //2011.0120 ����   // ���� ���� ��� ��û
		}		
	}
	else if(n_Mode == MOT_ERR_CODE)
	{//jamcode  ���� 		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
			st_msg.mstr_abnormal_msg = s_JamMsg;
			st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][0] = CTL_YES; st_timer.n_cmd_dialog_list_msg[ABNORMAL_MSG][1] = 0; //2011.0120 ����   // ���� ���� ��� ��û
		}	
	}
*/	
	if(CTLBD_DEBUG_MODE) 
	{
		if(CTLBD_MOTBD_TYPE == 0) //�Ľ��� ���� 
		{

		}
		else if(CTLBD_MOTBD_TYPE == 1) //Ŀ������ ���� 
		{
			cmmErrGetLastCode(&lErrorCode);						//������ �߻��� ���� �ڵ� Ȯ��  
			nErrorParseAxis = cmmErrParseAxis(lErrorCode);     //������ �߻���Ų �� ������ �����´� 
			nErrorParseReason = cmmErrParseReason(lErrorCode); //error code�� �޴´� 
			cmmErrGetString(lErrorCode, cErrorMsg, 200);

			sTemp.Format("Msg=%s", cErrorMsg);
			sMsg.Format("[MSG]MotNum:%d, ECode=%d, EAxis=%d, EReason=%d, Msg[%s]", n_Axis, lErrorCode, nErrorParseAxis, nErrorParseReason, sTemp);
			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
			{
//				st_msg.mstr_abnormal_msg = sMsg;
				sprintf(st_msg.c_abnormal_msg, sMsg);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				//2011.0218 if(MOT_DEBUG) Func.On_LogFile_Add(3, st_msg.mstr_abnormal_msg);
			}	
		}
	} 
	//2011.0123 ���� alarm.mstr_code = s_JamCode; //alarm.mn_count_mode = 0; alarm.mn_type_mode = CTL_dWARNING;
	
	return CTLBD_YES; 
}


int CCtlBd_Function::OnMotor_SafetyCheck(int n_Mode, int n_Axis, double d_TargetPos)
{
	// n_Mode = 0:Home Check, 1:Start, 2:Check, 3:Jog
	char cJamcode[10] = {NULL};
	int nRet = 0, nRet_1 = 0, nRet_2 = 0, nRet_3=0;
	double d_CurPos[3] = {0,};
	double d_Pos[3] = {0,};
	double d_GapCheck = 0;
	int i = 0;

	// **************************************************************************
	// ���� �˶� ���� �˻��Ѵ�                                                   
	// -> �˶� �߻��� ��� �˶� �����Ѵ�                                         
	// **************************************************************************

	//software limit �� ���� üũ ���� 
	if(d_TargetPos < st_motor[n_Axis].md_limit_position[0]) //
	{//000004
		sprintf(cJamcode, "%02d0004", n_Axis);  
		alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; COMI.mn_run_status = CTL_dWARNING;
		sprintf(alarm.mc_code, "%02d0004", n_Axis);
		CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);
		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
			sprintf(st_msg.c_abnormal_msg, "Motor[%d] Software Limit Error_1[%4.3f] [%4.3f]", n_Axis, st_motor[n_Axis].md_limit_position[0], d_TargetPos);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		}		
		return CTL_ERROR;
	}	

	if(d_TargetPos > st_motor[n_Axis].md_limit_position[1]) //
	{
		sprintf(cJamcode, "%02d0004", n_Axis);  
		alarm.mstr_code = _T(cJamcode); 	alarm.mn_type_mode = CTL_dWARNING; COMI.mn_run_status = CTL_dWARNING;
		sprintf(alarm.mc_code, "%02d0004", n_Axis);
		CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);
		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
			sprintf(st_msg.c_abnormal_msg, "Motor[%d] Software Limit Error_2[%4.3f] [%4.3f]", n_Axis, st_motor[n_Axis].md_limit_position[1], d_TargetPos);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		}
		return CTL_ERROR;
	}

	// **************************************************************************
	// ���� �Ŀ� ���� �˻��Ѵ�                                                   
	// -> ���� POWER OFF �� POWER ON ���·� �����                               
	// **************************************************************************
	if (COMI.Get_MotPower(n_Axis) == CTL_ERROR )          // ���� POWER ���� �˻� �Լ� 
	{
		if (COMI.Set_MotPower(n_Axis, CTL_ON) == CTLBD_RET_GOOD)       // ���� POWER ON ���� �Լ� 
		{
			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
			{
				sprintf(st_msg.c_normal_msg, "[MotorPowerOn_1] Axis=%d, rcnt=%d", n_Axis, st_motor[n_Axis].mn_retry_cnt);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			if (COMI.Get_MotPower(n_Axis) == CTL_ERROR)  // ���� POWER ���� �˻� �Լ� 
			{
				if (st_motor[n_Axis].mn_retry_cnt > (MOT_RTY_CNT))
				{
					sprintf(cJamcode, "%02d0005",  n_Axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;		
					sprintf(alarm.mc_code, "%02d0005", n_Axis);
					CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Get Power Check Error", n_Axis, st_motor[n_Axis].mn_retry_cnt);				
					CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);

					//2011.0210 st_motor[n_Axis].mn_retry_cnt = 0;
					return CTL_ERROR;
				}
				else
				{
					st_motor[n_Axis].mn_retry_cnt++ ;
					return CTL_RETRY;
				}
			}
		}
		else
		{
			if (st_motor[n_Axis].mn_retry_cnt > MOT_RTY_CNT)
			{
				sprintf(cJamcode, "%02d0005",  n_Axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;		
				sprintf(alarm.mc_code, "%02d0005", n_Axis);
				CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Set Power return Error", n_Axis, st_motor[n_Axis].mn_retry_cnt);				
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);
				
				return CTL_ERROR;
			}
			else
			{
				st_motor[n_Axis].mn_retry_cnt++ ;
				return CTL_RETRY;
			}
		}
	}

	//���� �˶� �߻��� ó�� ���� 
	if (COMI.Get_MotAlarmStatus(n_Axis) == CTL_ERROR)      // ���� ALARM ���� �˻� �Լ� 
	{
		if (COMI.Set_MotAlarmClear(n_Axis) == CTL_GOOD)       // ���� ALARM CLEAR �Լ� 
		{
			if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
			{
				sprintf(st_msg.c_normal_msg, "[Alarm Reset] Axis=%d, rcnt=%d", n_Axis, st_motor[n_Axis].mn_retry_cnt);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			if (COMI.Get_MotAlarmStatus(n_Axis) == CTL_ERROR )  // ���� ALARM ���� �˻� �Լ� 
			{
				if (st_motor[n_Axis].mn_retry_cnt > MOT_RTY_CNT)
				{			
					sprintf(cJamcode, "%02d0002",  n_Axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;	
					sprintf(alarm.mc_code, "%02d0002", n_Axis);
					CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Get Alarm Check Error", n_Axis, st_motor[n_Axis].mn_retry_cnt);				
					CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);
					return CTL_ERROR;
				}
				else
				{
					st_motor[n_Axis].mn_retry_cnt++ ;
					return CTL_RETRY;
				}
			}
		}
		else
		{
			if (st_motor[n_Axis].mn_retry_cnt > MOT_RTY_CNT)
			{
				sprintf(cJamcode, "%02d0002",  n_Axis); alarm.mstr_code = _T(cJamcode); //091216 	alarm.mn_count_mode = MOT_DEBUG;	
				sprintf(alarm.mc_code, "%02d0002", n_Axis);
				CtlBdFunc.ms_ErrMsg.Format("[Safety] Mot[%d] rcnt[%d] Set Alarm Return Error", n_Axis, st_motor[n_Axis].mn_retry_cnt);				
				CtlBdFunc.Send_Error_Message(MOT_ERR_CODE, n_Axis, cJamcode, CtlBdFunc.ms_ErrMsg);
				
				return CTL_ERROR;
			}
			else
			{
				st_motor[n_Axis].mn_retry_cnt++ ;
				return CTL_RETRY;
			}
		}
	}
	// **************************************************************************


	st_motor[n_Axis].mn_retry_time_flag = CTL_NO;//2011.0201 �߰� 
	return CTLBD_RET_GOOD;
}


int CCtlBd_Function::Initialize_FASIO_Board(void) 
{
	int m=0, p=0, s=0, i;
	int nRet=0;
	WORD wMaskMap = 0;

	INT nHSSI_speed=0;
	INT nMasterNo=0, nPortNo =0, nSlaveNo=0; 

	nRet = FAS_IO.Set_IO_BoardOpen(&nMasterNo, START_NOTHING);  // I/O ���� ���� �Լ� 
	if (nRet == CTLBD_RET_ERROR)
	{
		return CTLBD_RET_ERROR; //IO_BOARD_OPEN_FAILED;
	}

	nRet = FAS_IO.Search_IO_Master(&nMasterNo);              // PC�� ����� ������ ���� ���� �˻� �Լ� 
	if (nRet == CTLBD_RET_ERROR)
	{
		return CTLBD_RET_ERROR;
	}
	
	for(m=0; m<nMasterNo; m++)
	{
		nRet = FAS_IO.Search_IO_Port(m, &nPortNo);						// ������ ���忡 ����� PORT ���� �˻� �Լ� 
		if (nRet == CTLBD_RET_ERROR) return CTLBD_RET_ERROR;	//PORT_SEARCH_FAILED;
		
		for(p=0; p<nPortNo; p++)
		{
			nRet = FAS_IO.Set_IO_HSSISpeed(m, p, PORT_SPEED_10);		// PORT�� SLAVE I/O ������ ��� �ӵ� ���� �Լ� 
			if (nRet == CTLBD_RET_ERROR) return CTLBD_RET_ERROR; //IO_SPEED_SET_FAILED;
			 
			nRet = FAS_IO.Search_IO_Slave(m, p, &nSlaveNo);			// PORT�� ����� SLAVE �˻� �Լ� 
			if (nRet == CTLBD_RET_ERROR) return CTLBD_RET_ERROR; //IO_SLAVE_SEARCH_FAILED;

			for(s=0; s<nSlaveNo; s++)
			{
				nRet = FAS_IO.Set_IO_SlaveEnable(m, p, s, CTLBD_YES);		// SLAVE I/O ��� ���� ENABLE/DISABLE ���� �Լ� 
				if (nRet == CTLBD_RET_ERROR)	return CTLBD_RET_ERROR; //IO_SLAVE_ENABLE_FAILED;

				wMaskMap = 0; //clear
				for(i=0; i<16; i++) //0~15 ������ Port 16bit ����, ������ I/O ���¸� �����Ѵ� 
				{			
					wMaskMap = wMaskMap | (WORD)pow(2, mw_IOMaskMap[m][p][s][i]);					 
				}
				FAS_IO.Set_IO_DefineWord(m, p, s, wMaskMap); // x Master, x��Ʈ, x�� �����̺� , 16bit ����
				//FAS_IO.Set_IO_DefineWord(0, 0, 0, 0x0003); // 0�� Master, 0�� ��Ʈ, 0�� �����̺� , 16bit ����
				//FAS_IO.Set_IO_DefineWord(0, 0, 1, 0x0003); // 0�� Master, 0�� ��Ʈ, 1�� �����̺� , 16bit ����
				//FAS_IO.Set_IO_DefineWord(0, 1, 0, 0x00ff); // 0�� Master, 1�� ��Ʈ, 0�� �����̺� , 16bit ����
			}
		}
	}
	
	return CTLBD_RET_GOOD;
}



int CCtlBd_Function::Initialize_InterruptMask_TriggerConfig(void) 
{
	int i, nAxis;
//	st_motor[0].ml_Set_InterruptMask[12] = CTL_YES;
//	COMI.Set_InterruptMask(0, st_motor[0].l_Set_InterruptMask);
	
//	double dRatio[3] = {100,100,100};
	//Set_TriggerSet_OneCompareConfig(int n_Axis, int n_Source, int n_Method, double d_ComparePosition)
//	COMI.Set_TriggerSet_OneCompareConfig(0, 0, 1, 5000);


//	st_motor[].mn_interrupt_flag

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

int		n_interrupt_source;  //���ͷ�Ʈ ó�� ���� 
	    //n_Mode : 	szCompareSource[4][50] = { 
		//0				"COMMAND Counter",
		//1				"Feedback Counter",
		//2			    "Deviation Counter",
		//3			    "General Counter"

	int		n_interrupt_method; //����ϴ� ���� ����  
		//CHAR szCompareMethod[6][50] = {
		//0				"Disable",
		//1				"CMP == COUNTER (No direction)",
		//2				"CMP == COUNTER (Only when counting up)",
		//3				"CMP == COUNTER (Only when counting down)",
		//4				"CMP > COUNTER",
		//5				"CMP < COUNTER"
*/	
	for(i=0; i<5; i++)	//for(nAxis=0; nAxis<MOTOR_COUNT; nAxis++)
	{
		if(i == 0)
		{
			nAxis = 0; 
			st_motor[nAxis].mn_interrupt_flag = CTL_YES; //dc load robot Y ������ ���� 
		}
		else if(i == 1)
		{
			nAxis = 5;
			st_motor[nAxis].mn_interrupt_flag = CTL_YES; //dc unload robot Y ������ ����
		}
		else if(i == 2) 
		{
			nAxis = 16;	
			st_motor[nAxis].mn_interrupt_flag = CTL_YES; //insert robot Y ������ ����
		}
		else if(i == 3)
		{
			nAxis = 19;		//2009.5.27 james ���� Ǫ�� �߰� 
			//st_motor[nAxis].mn_interrupt_flag = CTL_YES; //���� Ǫ�� ������ ����
		}
		else if(i == 4)
		{
			nAxis = 20;	
			st_motor[nAxis].mn_interrupt_flag = CTL_YES; //remove robot Y ������ ����
		}

		if(st_motor[nAxis].mn_interrupt_flag == CTL_YES) //���ͷ�Ʈ�� ����ϴ� �����̸� 
		{
			st_motor[nAxis].ml_Set_InterruptMask[0] = CTL_NO; //"Normal Stop", // 0
			st_motor[nAxis].ml_Set_InterruptMask[1] = CTL_NO; //"Succesive start", // 1
			st_motor[nAxis].ml_Set_InterruptMask[2] = CTL_NO; //"", // 2
			st_motor[nAxis].ml_Set_InterruptMask[3] = CTL_NO; //"", // 3
			st_motor[nAxis].ml_Set_InterruptMask[4] = CTL_NO; //"Start of acceleration", //4
			st_motor[nAxis].ml_Set_InterruptMask[5] = CTL_NO; //End of acceleration", // 5
			st_motor[nAxis].ml_Set_InterruptMask[6] = CTL_NO; //"Start of deceleration", // 6
			st_motor[nAxis].ml_Set_InterruptMask[7] = CTL_NO; //"End of deceleration", // 7
			st_motor[nAxis].ml_Set_InterruptMask[8] = CTL_NO; //"", // 8
			st_motor[nAxis].ml_Set_InterruptMask[9] = CTL_NO; //"", // 9
			st_motor[nAxis].ml_Set_InterruptMask[10] = CTL_NO; //"Position error tolerance exceed", // 10
			st_motor[nAxis].ml_Set_InterruptMask[11] = CTL_NO; //"General Comparator", // 11

			//�̰͸� �켱 ����Ѵ� 
			st_motor[nAxis].ml_Set_InterruptMask[12] = CTL_YES; //"Compared trigger", // 12

			st_motor[nAxis].ml_Set_InterruptMask[13] = CTL_NO; //"CLR signal resets the counter value", // 13
			st_motor[nAxis].ml_Set_InterruptMask[14] = CTL_NO; //"LTC input making counter value latched", // 14
			st_motor[nAxis].ml_Set_InterruptMask[15] = CTL_NO; //"ORG input signal ON", // 15
			st_motor[nAxis].ml_Set_InterruptMask[16] = CTL_NO; //"SD input signal ON", // 16
			st_motor[nAxis].ml_Set_InterruptMask[17] = CTL_NO; //"+DR input changes", // 17
			st_motor[nAxis].ml_Set_InterruptMask[18] = CTL_NO; //"-DR input changes" // 18

			//���ͷ�Ʈ ����Ű ������ �����Ѵ� 
			//Set_InterruptMask(int n_Axis, long l_Set_InterruptMask[19])
			COMI.Set_InterruptMask(nAxis, st_motor[nAxis].ml_Set_InterruptMask);

			//���ͷ�Ʈ �߻� ���� �� ���� ���� 
			//Set_TriggerSet_OneCompareConfig(int n_Axis, int n_Source, int n_Method, double d_ComparePosition)
			COMI.Set_TriggerSet_OneCompareConfig(nAxis, st_motor[nAxis].mn_interrupt_source, st_motor[nAxis].mn_interrupt_method, st_motor[nAxis].mn_interrupt_position);
		}
	}		
	return CTL_GOOD;
}
