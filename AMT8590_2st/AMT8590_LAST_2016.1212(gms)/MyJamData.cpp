// MyJamData.cpp: implementation of the CMyJamData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Handler.h"
#include "MyJamData.h"

#include "io.h" 
#include "Public_Function.h"  // ���� ���� �� I/O ���� ���� Ŭ����
#include "FastechPublic_IO.h"
#include "ComizoaPublic.h"
#include "SrcPart/APartHandler.h"
#include "AMTLotManager.h"
#include "XGemClient.h"
#include "AMTRegistry.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyJamData			MyJamData;
CMyJamData::CMyJamData()
{
	mn_noError = FALSE;
	m_timeAlarmLastDay = AMTRegistry::RegReadAlarmTime();
}

CMyJamData::~CMyJamData()
{

}

/* ****************************************************************************** */
/* �߻� �˶� ���� ���� �Լ�                                                       */
/* -> strPath     : �˶� ���� ���� ���� ���� ����                                 */
/* -> strDataFile : �˶� ���� ����� File Name(File Name+Ȯ����)                        */
/* -> strCode     : �߻��� �˶� Code                                              */
/* ****************************************************************************** */
CString CMyJamData::On_Alarm_Display_Info_Load(CString strPath, CString strDataFile, CString strActionFile, CString strCode)
{
	CString str_file_path;  // ���� ���� ���� */
	CString str_alarm_chk;  // �Լ� ���� ���� ���� ���� */
	int n_pos;

	str_file_path = strPath;
	if (str_file_path.Right(1) != "\\")  // ���� ��� ������ ���� �˻� */
	{
		str_file_path += "\\";
	}

	str_alarm_chk = On_Alarm_Bmp_Data_Load(str_file_path, strDataFile, strCode);  // �߻� �˶� ���� ǥ�ÿ� �׸� File Name ���� �Լ� */
	n_pos = str_alarm_chk.Find("Trouble");
	if (n_pos >= 0)  // ���� �߻�
	{
		return str_alarm_chk;
	}

	str_alarm_chk = On_Alarm_Style_Data_Load(str_file_path, strDataFile, strCode);  // �˶� �߻� ���� ǥ�� ���� �� ��� ��ġ ���� �Լ� */
	n_pos = str_alarm_chk.Find("Trouble");
	if (n_pos >= 0)  // ���� �߻�
	{
		return str_alarm_chk;
	}

	str_alarm_chk = On_Alarm_Repair_Data_Load(str_file_path, strActionFile, strCode);  // �߻��� �˶��� ���� ��ġ ���� ���� �Լ� */
	n_pos = str_alarm_chk.Find("Trouble");
	if (n_pos >= 0)  // ���� �߻�
	{
		return str_alarm_chk;
	}

	return str_alarm_chk;
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �߻� �˶� ���� ǥ�ÿ� �׸� File Name ���� �Լ�                                 */
/* -> strPath     : �˶� ǥ�� �׸� ���� ���� ����                                 */
/* -> strDataFile : �˶� ǥ�� �׸� File Name(File Name+Ȯ����)                    */
/* -> strCode     : �߻��� �˶� Code                                              */
/* ****************************************************************************** */
CString CMyJamData::On_Alarm_Bmp_Data_Load(CString strPath, CString strDataFile, CString strCode)
{
	CString str_return_data;  // �Լ� ���� �÷���
	CString str_file;  // �˶� ǥ�ÿ� �׸��� ���� [����]+[File Name] ���� ����
	CString str_temp;  // �˶� ǥ�ÿ� �׸� File Name �ӽ� ���� ����

	char chr_buf[1000];

	str_return_data = _T("OK");  // �Լ� ���� �÷��� �ʱ�ȭ

	str_file = strPath + strDataFile;  // [����]+[File Name] ����

	if (!GetPrivateProfileString(strCode, "DEF", "", chr_buf, 1000, str_file))
	{
		str_return_data = "File Name : "+ str_file;
		str_return_data += "\r\n";
		str_return_data += "[DEF] The information we read. Trouble -> Code : ";
		str_return_data += strCode;

		return str_return_data;
	}

	str_temp.Format("%s", chr_buf);
	st_alarm.mstr_bmp_file = str_temp;  // �˶� ǥ�ÿ� �׷� File Name ����

	return str_return_data;
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �˶� �߻� ���� ǥ�� ���� �� ��� ��ġ ���� �Լ�                                */
/* -> strPath     : ���� ǥ�� ���� ���� ���� ����                                 */
/* -> strDataFile : ���� ǥ�� ���� ���� File Name(File Name+Ȯ����)               */
/* -> strCode     : �߻��� �˶� Code                                              */
/* ****************************************************************************** */
CString CMyJamData::On_Alarm_Style_Data_Load(CString strPath, CString strDataFile, CString strCode)
{
	CString str_chk_data;		// �Լ� ���� �÷���
	CString str_chk_file;		// �˶� ���� ǥ�� ������ ���� [����]+[File Name] ���� ����
	CString str_chk, str_chk2;  // �˶� ���� ǥ�� ���� �� ��ġ ���� ����
	int start=0, end, i;		// ���� ������ ��ġ ���� ����
	int max=4;					// ���� ������ �ִ� ���� (ȭ��ǥ ������� �ʱ�ȭ)

	char chr_buf[1000];
	char num[20];

	str_chk_data = _T("OK");  // �Լ� ���� �÷��� �ʱ�ȭ

	str_chk_file = strPath + strDataFile;  // [����]+[File Name] ����

	if (!GetPrivateProfileString(strCode, "STYLE", "", chr_buf, 1000, str_chk_file))
	{
		str_chk_data = "File Name : "+ str_chk_file;
		str_chk_data += "\r\n";
		str_chk_data += "[STYLE] The information we read. Trouble -> Code : ";
		str_chk_data += strCode;

		return str_chk_data;
	}

	str_chk.Format("%s", chr_buf);

	for(i=0; i<max; i++)
	{
		end = str_chk.Find(';', start);
		if (end == -1)  // ������ ������
		{
			break;
		}
		else            // ������ ����
		{
			str_chk2 = str_chk.Mid(start, end-start);  // ������ ������ �� �� ������ ����
			str_chk2.TrimLeft(' ');
			str_chk2.TrimRight(' ');

			if (i == 0)  // �˶� ���� ǥ�� ����
			{
				st_alarm.mstr_style = str_chk2;       // �˶� ���� ǥ�� ���� ����
				if (st_alarm.mstr_style == "CIRCLE")  // ���� ǥ�� ���� 8�� ����
				{
					max = 8;    
				}
				else if (st_alarm.mstr_style == "NONE")
				{
					max = 1;
				}
			}
			else
			{
				lstrcpy(num, str_chk2);
				if (i == 1)
				{
					st_alarm.mn_Cx = atoi(num);         // X�� �ȼ� ��ġ
				}
				else if (i == 2)
				{
					st_alarm.mn_Cy = atoi(num);         // Y�� �ȼ� ��ġ
				}
				else if (i == 3)
				{
					st_alarm.mn_Offset = atoi(num);     // �� ũ��
				}
				else if (i == 4)
				{
					st_alarm.mn_LineWidth = atoi(num);  // ���� �β�
				}
				else if (i == 5)
				{
					st_alarm.mn_R = atoi(num);          // RGB �� R ��
				}
				else if (i == 6)
				{
					st_alarm.mn_G = atoi(num);          // RGB �� G ��
				}
				else if (i == 7) 
				{
					st_alarm.mn_B = atoi(num);          // RGB �� B ��
				}
				/* ************************************************************** */
			}

			start = end + 1;  // ���� ������ ��ġ ����
		}
	}

	if (i != max)  // Data Format ����
	{
		str_chk_data = "File Name : "+ str_chk_file;
		str_chk_data += "\r\n";
		str_chk_data += "[STYLE] Data Format. Trouble -> Code : ";
		str_chk_data += strCode;

		return str_chk_data;
	}

	return str_chk_data;
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �߻��� �˶��� ���� ��ġ ���� ���� �Լ�                                         */
/* -> strPath       : �˶� ��ġ ���� ����� ���� ����                             */
/* -> strActionFile : �˶� ��ġ ���� ����� File Name(File Name+Ȯ����)           */
/* -> strCode       : �߻��� �˶� Code                                            */
/* ****************************************************************************** */
CString CMyJamData::On_Alarm_Repair_Data_Load(CString strPath, CString strActionFile, CString strCode)
{
	CString str_return_val;		// �Լ� ���� �÷���
	CString str_repair_file;	// ��ġ ���׿� ���� [����]+[File Name] ���� ����
	CString str_act_item;		// ��ġ ���� ���� ��ġ ���� ����
	CString str_act_temp;		// ��ġ ���� �ӽ� ���� ����
	int n_chk_cnt;				// ��ġ ���� ���� ���� ����
	int i; 
	
	char chr_buf[1000];

	str_return_val = _T("OK");  // �Լ� ���� �÷��� �ʱ�ȭ

	str_repair_file = strPath + strActionFile;  // [����]+[File Name] ����

	if (!GetPrivateProfileString(strCode, "COUNT", "0", chr_buf, 10, str_repair_file))
	{
		str_return_val = "File Name : "+ str_repair_file;
		str_return_val += "\r\n";
		str_return_val += "[COUNT] The information we read. Trouble -> Code : ";
		str_return_val += strCode;

		return str_return_val;
	}

	n_chk_cnt = atoi(chr_buf);  // ���� ��ġ ���� ���� ����
	if (n_chk_cnt<1)
	{
		str_return_val = "File Name : "+ str_repair_file;
		str_return_val += "\r\n";
		str_return_val += "[COUNT] Data Format Trouble -> Code : ";
		str_return_val += strCode;

		return str_return_val;
	}
	else
	{
		st_alarm.mn_action_cnt = n_chk_cnt;
	}

	(st_alarm.mstr_repair_msg).Empty();  //  ��ġ ���� ���� ���� �ʱ�ȭ

	for (i=0; i<(st_alarm.mn_action_cnt); i++)   
	{
		str_act_item.Format("%d", i+1);  // ��ġ ���� ���� ���� ��ġ ����
		if (!GetPrivateProfileString(strCode, (LPCTSTR)str_act_item, "", chr_buf, 1000, str_repair_file))
		{
			str_return_val = "File Name : "+ str_repair_file;
			str_return_val += "\r\n";
			str_return_val += "An action subject. The information we read. Trouble";

			str_return_val += "\r\n";
			str_return_val += "Code : ";
			str_return_val += strCode;

			str_return_val += "\r\n";
			str_return_val += "Position : ";
			str_return_val += str_act_item;

			return str_return_val;
		}
		/* ********************************************************************** */

		st_alarm.mstr_repair_msg += "\r\n";			//��ġ ���׿� �� ù���� ����.

		str_act_temp.Format(" %s", chr_buf);  // ��ġ ���� ����
		st_alarm.mstr_repair_msg += str_act_temp;

		if (i != ((st_alarm.mn_action_cnt)-1))  
			st_alarm.mstr_repair_msg += "\r\n";  // ��ġ ���� �ܶ� ������ ����
	}
	/* ************************************************************************** */
	
	return str_return_val;
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �߻��� �˶� ȭ�� ��� �Լ�                                                     */
/* ****************************************************************************** */
void CMyJamData::On_Alarm_Display()
{
	CString str_cnt, str_temp;
	char temp_code[10]={0,}, temp_cnt[10]={0,}, chr_buf[20]={0,};
	
	CString str_display_time;	// ���� ��¿� �ð� ���� ����
	CString str_alarm_code;		// �߻��� �˶� �ڵ� ���� ����
	CString str_alarm_msg;		// �߻��� �˶� �޽��� ���� ����
	int n_cur_hour=0;				// ���� �ð� ���� ����
	int n_chk=0;					// ������ �˶� �ڵ� ���� ����
	long n_chk_time=0;			// �˶� �߻� �ð� ���� ���� ����
	int n_data_save = 0;		// Jam�� ������ ���̳�?

	COleDateTime cur_time;
	CTime alarm_occured_time;

 	/* ************************************************************************** */
 	/* ��� ���� �� �˶� �߻��ߴ��� �˻��Ѵ�                                      */
 	/* -> �˶� �߻��� ��� �α� ���� �� �ӽ� ���Ͽ� �����ϰ� ȭ�鿡 ����Ѵ�      */
 	/* ************************************************************************** */
 	if (COMI.mn_run_status == CTL_dJAM || COMI.mn_run_status == CTL_dWARNING || COMI.mn_run_status == CTL_dLOTEND)  // �˶� �߻�
 	{	
		//alarm.mstr_code = "990001";

		if (st_handler.mn_alarm_screen == TRUE)	return; 
 		/* ********************************************************************** */
 		/* �˶� ȭ�� ��� �Ұ����� ��� �˻��Ѵ�.                                 */
 		/* -> st_handler.mn_system_lock : SYSTEM LOCK ���� �÷���                  */
 		/* ********************************************************************** */
 		if (st_handler.mn_system_lock != FALSE)  // SYSTEM LOCK
 		{
 			return;  // ���� ����
 		}
 		/* ********************************************************************** */

		//�˶� �߻��ϸ� ������ �˶��ð��� �����Ѵ�.
		st_work.mn_jam = CTL_YES;//2015.0327
		st_handler.m_dwJamStartTime = GetCurrentTime();
 

 		/* ************************************************************************** */
 		/* �˶� �߻��� �ð� �����Ѵ�                                                  */
 		/* ************************************************************************** */
 		cur_time = COleDateTime::GetCurrentTime();
 		n_cur_hour = cur_time.GetHour();
 
 		alarm_occured_time = CTime::GetCurrentTime();
 		str_display_time = alarm_occured_time.Format("%c");
 		/* ************************************************************************** */

 
 		/* ********************************************************************** */
 		/* �˶� ȭ�� ��� ���� �� �˶� ī��Ʈ ���� �˻��Ѵ�                       */
 		/* -> �̹� �˶� ȭ�� ��� ���� ��� �� ����� �ʿ� ������                 */
 		/*    �� ��쿡 �߻��ϴ� �˶��� �����Ѵ�                                  */
 		/*  : �˶� ȭ�� ��� �߿� �˶� Code ����Ǹ� ��� �޽��� �޶����� ����    */
 		/* -> st_handler.mn_alarm_screen : �˶� ȭ�� ��� ���� �÷���              */
 		/* -> st_alarm.mn_cur_state : �˶� ���� ���� �÷���                        */
 		/* ********************************************************************** */
 		if (st_handler.mn_alarm_screen != TRUE)  // �˶� ȭ�� �����
 		{
 			if (COMI.mn_run_status == CTL_dLOTEND)		
 			{
 				alarm.mn_reset_status = CTL_NO;
 			}
 			else	alarm.mn_reset_status = CTL_YES;
 
 			//�߻��� �˶��� List�� �ִ´�.
 			if (alarm.mstr_code != "")
 			{
 				/* ************************************************************************** */
 				/* ���� �߻��� �˶��� ���� �޽��� ���� �����Ѵ�                               */
 				/* ************************************************************************** */
 				On_Alarm_Info_Set_to_Variable(alarm.mstr_code);  // �߻��� �˶� �޽��� ���� ������ �����ϴ� �Լ�
 				/* ************************************************************************** */
 				sprintf(temp_code, "%s", alarm.mstr_code);
// 				str_cnt.Format("%d", st_alarm.mn_cur_state);
 				sprintf(temp_cnt, "%s", str_cnt);
 
 				/* ************************************************************************** */
 				/* �ٷ� ���� �߻��� �˶� �ڵ�� ���Ͽ� ������ ��� �˶� ī��Ʈ ������       */
 				/* -> �˶� ī��Ʈ �ð� ������ 30�ʷ� �����Ѵ�                                 */
 				/* ************************************************************************** */
 				alarm.stl_cur_alarm_time = GetCurrentTime();
 
 				n_chk = atoi(alarm.mstr_code);
				n_data_save = CTL_NO;				// �⺻�� NO

				//st_basic.mn_alarm_delay_time = 10;
 				
 				if (alarm.stl_prev_code == n_chk)	// �˶� �ڵ� ����
 				{
// 					n_chk_time = alarm.stl_cur_alarm_time - alarm.stl_prev_alarm_time; 

					n_chk_time = alarm.stl_cur_alarm_time - alarm.stl_alarm_start_time; 
 					
 					if (n_chk_time < st_basic.mn_alarm_delay_time * 1000 /*|| alarm.stl_alarm_start_time == 0*/)						// Basic���� �����Ҽ� �ְ� ������. 2K9/11/19/ViboX
 					{
 						alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
 					}
 					else
 					{
 						alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
 						n_data_save = CTL_YES;			// Jam�� ���� �� Count�� �Ѵ�.
 					}
 				}
 				else
 				{
 					/* ********************************************************************** */
 					/* �߻��� �˶� ������ ���� ������ ��ü�Ѵ�                                */
 					/* -> ������ �߻��ϴ� �˶��� ���ϴ� ������ ���ȴ�                     */
 					/* ********************************************************************** */
//  					alarm.stl_prev_code = n_chk;
//  					alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
//  					/* ********************************************************************** */
//  
//  					n_data_save = CTL_YES;				// Jam�� ���� �� Count�� �Ѵ�.
					mn_noError = FALSE;
					n_chk_time = alarm.stl_cur_alarm_time - alarm.stl_alarm_start_time; 
// 					if (n_chk_time < 5 * 1000/*2��*/)
// 					{
// 						alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
// 						mn_noError = TRUE;
// // 						On_Occured_Alarm_Saving_to_File();  // �߻��� �˶� �α� ���Ͽ� �����ϴ� �Լ�
// 					}
// 					else
// 					{
// 						alarm.stl_prev_code = n_chk;
						alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
						n_data_save = CTL_YES;			// Jam�� ���� �� Count�� �Ѵ�.
// 					}
				}
 				/* ************************************************************************** */
 			}

			if (st_handler.mn_status == CTL_NO || /*st_basic.mn_mode_run == CTL_NO ||*/ st_handler.mn_virtual_supply == 1/* || (g_lotMgr.GetLotIDAt(0).GetLength() < 5)*/)
			{
				n_data_save = CTL_NO;
			}

 			if (n_data_save == CTL_YES)
 			{
				if (st_alarm.mstr_cur_state == "1")			// Count�ϴ� Alarm�̸�... 2K9/08/28/ViboX
				{
					alarm.mn_alarm_occured++;
					alarm.mn_alarm_occured_day++;

					str_temp = LPCTSTR(_itoa(alarm.mn_alarm_occured_day, chr_buf, 10)) ;
					:: WritePrivateProfileString("BasicData", "Day_Alarm_Count", LPCTSTR(str_temp), st_path.mstr_basic);
				}

				if (st_handler.mn_status == CTL_YES)					// ��� �������̳�
				{
					if (st_alarm.mstr_cur_state == "1")	
						g_handler.AddAlarmCnt();
					On_Occured_Alarm_Saving_to_File();  // �߻��� �˶� �α� ���Ͽ� �����ϴ� �Լ�
				}
				alarm.mn_svr_alarm = CTL_NO;
				if( alarm.mstr_code == "900101" || alarm.mstr_code == "900102" || 
					alarm.mstr_code == "900103" || alarm.mstr_code == "900104")
				{
					alarm.mn_svr_alarm = CTL_YES;
				}
 			}
 
 			st_handler.mn_alarm_screen = TRUE;	// �˶� ȭ�� ��� �÷��� ����
 
 			Func.OnSet_IO_Port_Alarm();			// �˶� ���� I/O ��� �Լ�

			//2015.0413
			if( st_basic.mn_mode_xgem == CTL_YES )
			{
				g_xgem_client.SetGemAlarmState(alarm.mstr_code, 1);
			}

 			::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 7, 1);  // ���� �����ӿ� �˶� ȭ�� ��� ��û 
 
 			if (st_handler.cwnd_title != NULL)  // Ÿ��Ʋ �� ��� �˻�
 				st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, MACHINE_STATUS, COMI.mn_run_status);  // Ÿ��Ʋ [�˶�] ��� ��û

			//2016.0919
			st_work.n_jamcode_flag	= CTL_YES;
			alarm.str_lastcode = alarm.mstr_code;
			st_work.t_jamcode_start = CTime::GetCurrentTime();

 		}
// 		/* ********************************************************************** */
 	}
	/* ************************************************************************** */
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �߻��� �˶� �α� ���Ͽ� �����ϴ� �Լ�                                          */
/* ****************************************************************************** */
void CMyJamData::On_Occured_Alarm_Saving_to_File()
{
	CString str_display_time;	// ���� ��¿� �ð� ���� ����
	CString str_alarm_code;		// �߻��� �˶� Code ���� ����
	CString str_alarm_msg;		// �߻��� �˶� �޽��� ���� ����
	int n_cur_hour;				// ���� �ð� ���� ����
	int n_chk;					// ������ �˶� Code ���� ����
	long n_chk_time;			// �˶� �߻� �ð� ���� ���� ����

	COleDateTime cur_time;
	CTime alarm_occured_time;

	/* ************************************************************************** */
	/* �˶� �߻��� �ð� �����Ѵ�                                                  */
	/* -> SHIFT ���� �˻� �� �˶� �߻� �ð� �����ϱ� ���Ͽ� �ʿ�                  */
	/* ************************************************************************** */
	cur_time = COleDateTime::GetCurrentTime();
	n_cur_hour = cur_time.GetHour();

	alarm_occured_time = CTime::GetCurrentTime();
	str_display_time = alarm_occured_time.Format("%Y/%m/%d  %H:%M:%S");
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* �˶� Code �� �˶� �޽��� �Լ� ������ �����Ѵ�                              */
	/* -> ����� �� �Լ� ȣ�� ���� ���ο� �˶��� �߻��ϴ� ��� �˶� Code��        */
	/*    ��ġ ���� �� ��Ÿ ������ ��ġ���� ���� �� �ִ�                          */
	/* -> alarm.mstr_code : ���� �߻��� �˶� Code ���� ���� ����                   */
	/* -> st_alarm.mstr_cur_msg : �߻��� �˶� �޽��� ���� ����                     */
	/* ************************************************************************** */
	str_alarm_code = alarm.mstr_code;
	str_alarm_msg = st_alarm.mstr_cur_msg;

	st_alarmdb.mole_date = COleDateTime::GetCurrentTime();

// 	st_alarmdb.mstrlot_no = st_pcb[1].strLotNumber;
// 	st_alarmdb.mstrpart_no = st_pcb[1].strPartNumber;

	st_alarmdb.mstrAlarmCode = str_alarm_code;
	st_alarmdb.mstrAlarmMsg = str_alarm_msg;
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* �Ϻ�, ���� �˶� �߻� Ƚ�� �ӽ� ���Ͽ� �߰��Ѵ�                             */
	/* ************************************************************************** */
	//2012,0306
// 	if(mn_noError == TRUE)
// 	{
		mn_noError = FALSE;
		//2015.0404 under daily display
// 		On_Daily_ListFile_Add(str_alarm_code, str_display_time, str_alarm_msg); // �Ϻ�, ���� �˶� ���� ����Ʈ ���Ͽ� �߰� �Լ� */
// 		On_UnderDaily_ListFile_Add(str_alarm_code, str_display_time, str_alarm_msg); // �Ϻ�, ���� �˶� ���� ����Ʈ ���Ͽ� �߰� �Լ� */
// 		return;
// 	}
	
	//2015.0404 
	if (st_alarm.mstr_cur_state == "1")			// Count�ϴ� Alarm�̸�... 2K9/08/28/ViboX
	{
		On_Daily_ListFile_Add(str_alarm_code, str_display_time, str_alarm_msg); // �Ϻ�, ���� �˶� ���� ����Ʈ ���Ͽ� �߰� �Լ� */
// 		On_UnderDaily_ListFile_Add(str_alarm_code, str_display_time, str_alarm_msg); // �Ϻ�, ���� �˶� ���� ����Ʈ ���Ͽ� �߰� �Լ� */
//		Func.DB_Write_Alarm(st_alarmdb);

		{//2015.0513
			CString strLog;
// 			strLog.Format(", Error, %s, %s, %s", alarm.mstr_code, st_handler.m_strLogEvent, str_alarm_msg);
			strLog.Format(" Error, %s", st_handler.m_strLogEvent);
			Func.On_LogFile_Add(LOG_EVENT, strLog, 1);
		}
	}
	else
	{
		On_UnderDaily_ListFile_Add(str_alarm_code, str_display_time, str_alarm_msg); // �Ϻ�, ���� �˶� ���� ����Ʈ ���Ͽ� �߰� �Լ� */
// 		Func.DB_Write_Alarm(st_alarmdb);
	}
	/* ************************************************************************** */
	
	/* ************************************************************************** */
	/* �ٷ� ���� �߻��� �˶� Code�� ���Ͽ� ������ ��� �˶� ī��Ʈ ������       */
	/* -> �˶� ī��Ʈ �ð� ������ 30�ʷ� �����Ѵ�                                 */
	/* ************************************************************************** */
	alarm.stl_cur_alarm_time = GetCurrentTime();

	n_chk = atoi(str_alarm_code);
	
	if (alarm.stl_prev_code == n_chk)  // �˶� Code ����
	{
		n_chk_time = alarm.stl_cur_alarm_time - alarm.stl_prev_alarm_time; 
		
		if (n_chk_time < 30000) 
		{
			alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
			return;
		}
	}
	else
	{
		/* ********************************************************************** */
		/* �߻��� �˶� ������ ���� ������ ��ü�Ѵ�                                */
		/* -> ������ �߻��ϴ� �˶��� ���ϴ� ������ ���ȴ�                     */
		/* ********************************************************************** */
		alarm.stl_prev_code = n_chk;
		alarm.stl_prev_alarm_time = alarm.stl_cur_alarm_time;
		/* ********************************************************************** */
	}
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* SHIFT�� �˶� �߻� Ƚ�� �ӽ� ���� ���Ͽ� �˶� �߰��Ѵ�                      */
	/* -> �˶� �߻� Ƚ�� �ӽ� ���� ���� ������ �� ������ �˶� ����Ʈ ���� �̸���  */
	/*    �Ϻ� ���� �̸����� ����� ������ ������ �����ϴ�                        */
	/* ************************************************************************** */
	if (n_cur_hour >= 6 && n_cur_hour < 14)  // SHIFT �� DAY */
	{
//		mcls_alarm_list.On_Shift_File_Add(1, str_alarm_code, str_display_time);  // SHIFT�� �˶� �߻� Ƚ�� ���� �ӽ� ���Ͽ� �߰� �Լ� */
	}
	else if (n_cur_hour >= 14 && n_cur_hour < 22)  // SHIFT �� SWING */
	{
//		mcls_alarm_list.On_Shift_File_Add(2, str_alarm_code, str_display_time);  // SHIFT�� �˶� �߻� Ƚ�� ���� �ӽ� ���Ͽ� �߰� �Լ� */
	}
	else  // SHIFT �� GY */
	{
//		mcls_alarm_list.On_Shift_File_Add(3, str_alarm_code, str_display_time);  // SHIFT�� �˶� �߻� Ƚ�� ���� �ӽ� ���Ͽ� �߰� �Լ� */
	}
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* LOT�� �˶� �߻� Ƚ�� �ӽ� ���Ͽ� �߰��Ѵ�                                  */
	/* ************************************************************************** */
//	mcls_alarm_list.On_Lot_ListFile_Add(str_alarm_code, str_display_time);  // LOT�� �˶� �߻� Ƚ�� ���� �ӽ� ���Ͽ� �߰� �Լ� */
	/* ************************************************************************** */
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* ���Ͽ� ����� ��� �˶� ���� ���� ������ �����ϴ� �Լ�                         */
/* ****************************************************************************** */
void CMyJamData::On_Alarm_Info_Load()
{
	CString str_load_file;
	CString str_read_data;  // ���Ͽ� ����� �� ���� ���� ���� ����
	CString str_temp_data;
	CString str_comment_data;
	int n_count, n_len;
	int n_pos = 0 ;

	char chr_s[300];
	FILE  *fp ;  // ���� �ڵ� ���� ����

	str_load_file = _T("c:\\AMT8590\\Bmp\\Error.txt"); 

	/* ************************************************************************** */
    /* �˶� ���� ������ ���� ����ü ��� ���� �ʱ�ȭ                              */
    /* ************************************************************************** */
	for (n_count = 0; n_count < 2000; n_count++)  
	{
		(st_alarm.mstr_e_content[n_count]).Empty();  // ���Ͽ��� �ε��� �� ���� ���� ���� ���� �ʱ�ȭ
		(st_alarm.mstr_e_code[n_count]).Empty();     // �˶� Code ���� ���� �ʱ�ȭ
		(st_alarm.mstr_e_state[n_count]).Empty();    // �˶� ���� ���� ���� �ʱ�ȭ
		(st_alarm.mstr_e_part[n_count]).Empty();     // �˶� �߻� ���� ���� ���� �ʱ�ȭ
		(st_alarm.mstr_e_msg[n_count]).Empty();      // �˶� �޽��� ���� ���� �ʱ�ȭ
	}
	/* ************************************************************************** */
	/* ************************************************************************** */
    /* �˶� ���� ����� ���� ����                                                 */
    /* ************************************************************************** */
	if ((fp=fopen(str_load_file,"rt"))==NULL)  
	{
		Func.MsgLog("The failure because we open the file.");
		return ;
	}
	/* ************************************************************************** */

	/* ************************************************************************** */
    /* ������ ���� �������� ��� �о� ���� ������ �����Ѵ�                        */
    /* ************************************************************************** */
	while(!feof(fp))  // ���� ������ �˻�
	{
		sprintf(chr_s, "");
		
        if (fgets(chr_s,300,fp)==NULL && ferror(fp))
		{   
			Func.MsgLog("The failure because we read the file.");
			return ;
		}
		
		str_read_data.Format("%s",chr_s);  // ���Ͽ��� ���� �� ���� ���� ����

		n_len = lstrlen(str_read_data);		//���� üũ

		if (!str_read_data.IsEmpty() && n_len > 2)
		{
			str_comment_data = str_read_data.Left(2);		//�ּ������� Ȯ���Ѵ�.

			if (str_comment_data != "//")					//�ּ����� �ƴ϶��...
			{
				st_alarm.mstr_e_content[n_pos] = str_read_data;         // ���Ͽ��� �ε��� �� ���� ���� ����
				st_alarm.mstr_e_code[n_pos] = str_read_data.Left(6) ;    // �˶� Code ����
				st_alarm.mstr_e_state[n_pos] = str_read_data.Mid(7,1) ;  // �˶� ���� ����
				st_alarm.mstr_e_part[n_pos] = str_read_data.Mid(9,1) ;   // �˶� �߻� ���� ����

				str_temp_data = str_read_data.Mid(12,270);
				
				if (st_alarm.mstr_e_code[n_pos] != "UNK000")
				{
					st_alarm.mstr_e_msg[n_pos] = str_temp_data.Left(str_temp_data.GetLength() - 3) ;  // ���� ���� �˶� �޽��� ����
				}
				else
				{
					st_alarm.mstr_e_msg[n_pos] = str_temp_data.Left(str_temp_data.GetLength() - 1) ;  // ���� ���� �˶� �޽��� ����
				}
				n_pos++;
			}
		}
	}
	/* ************************************************************************** */

	fclose(fp) ;  // ���� ����
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* �߻��� �˶� �޽��� ���� ������ �����ϴ� �Լ�                                   */
/* ****************************************************************************** */
void CMyJamData::On_Alarm_Info_Set_to_Variable(CString strErrCode)
{
	int n_cnt ;
	int n_cur_num = -1;    // �˶��� ���� �迭 ��ġ ���� ����
	CString str_err_code;  // �˶� Code ���� ����
	CString strPath;

	CString mstr_create_file;  // �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ����
	CString mstr_content;  // �� ���ο� ����� ���ڿ� ���� ���� ���� 
	int mn_existence;      // ���� ���� ���� ���� �÷��� 
	char fileName[256];    // �˻��� ���� ���� ���� �Լ� 
	FILE  *fp ;            // ���Ͽ� ���� ������ ���� ���� 
	
	CString str_title_time, str_file_time, str_new_file, str_display_time;		// ���Ͽ� ����� Ÿ��Ʋ �ð� ���� ����
	int n_cur_year, n_cur_month, n_cur_day;		// ��, ��, �� ���� ����
	
	COleDateTime mtime_cur;						// ���� �ð� ���� ����
	CTime mp_time_cur, alarm_occured_time;							// Ÿ��Ʋ �ð� ���� ����

	/* ************************************************************************** */
    /* �Էµ� �˶� Code���� ��/�� ������ �����Ѵ�                                 */
    /* ************************************************************************** */
	str_err_code = strErrCode;
	str_err_code.TrimLeft(' ');	
	str_err_code.TrimRight(' ');
	/* ************************************************************************** */

	/* ************************************************************************** */
    /* �߻��� �˶� Code�� ���� �迭 ��ġ �˻��Ѵ�                                 */
    /* ************************************************************************** */
	for(n_cnt=0; n_cnt<2000; n_cnt++)
	{  
		if ( (st_alarm.mstr_e_code[n_cnt]).Compare(str_err_code) == 0 )
		{
			n_cur_num = n_cnt ; 
			break;
		}
	}
	/* ************************************************************************** */
	
	if (n_cur_num == -1)  // ������ �˶�
	{
		/* ************************************************************************** */
		/* ���� �̸����� ����� ��¥ �����Ѵ�                                         */
		/* ************************************************************************** */
		mtime_cur = COleDateTime::GetCurrentTime();
		
		n_cur_year = mtime_cur.GetYear();  
		n_cur_month = mtime_cur.GetMonth();  
		n_cur_day = mtime_cur.GetDay();  

		alarm_occured_time = CTime::GetCurrentTime();
		str_display_time = alarm_occured_time.Format("%Y/%m/%d  %H:%M:%S");
		
		str_new_file.Format("ACD%04d%02d%02d", n_cur_year, n_cur_month, n_cur_day);
		
		mstr_create_file = "D:\\AMTLOG\\Log\\AlarmCodeDebug\\" + str_new_file;
		mstr_create_file += ".TXT";
		
		sprintf(fileName, "%s", mstr_create_file);
		mn_existence = access(fileName,0);
		
		if (mn_existence == -1)  /* ���� ������ */
		{
			mstr_create_file = "D:\\AMTLOG\\Log\\AlarmCodeDebug\\" + str_new_file;
			mstr_create_file += ".TXT";
			/* ********************************************************************** */
		}
		
		/* ************************************************************************** */
		/* �˶� �߻� Ƚ�� ���� ���� ���Ͽ� �߰� ������ ���� ���Ϸ� ����               */
		/* ************************************************************************** */
		if ((fp=fopen(mstr_create_file,"a+"))==NULL)  
		{
//			Func.MsgLog("���� ���� ����!..");
			return;
		}
		/* ************************************************************************** */
		
		mstr_content = "Can't find alarm code : " + str_err_code;
		fprintf(fp,"%s\n",mstr_content) ;
		mstr_content = "time : " + str_display_time;
		fprintf(fp,"%s\n",mstr_content) ;
		mstr_content = "------------------------------------------------------------------";
		fprintf(fp,"%s\n",mstr_content) ;
		
		if (ferror(fp))  
		{
			Func.MsgLog("file save failed!..") ;
			fclose(fp);
			return ;
		}
		/* ************************************************************************** */
		
		fclose(fp);  /* ���� ���� */

		alarm.mstr_pcode = alarm.mstr_code;
// 		alarm.mstr_code = "990000";
// 		sprintf(alarm.mc_code, "990000");
// 		str_err_code = "990000";
		alarm.mstr_code = "990000";
		sprintf(alarm.mc_code, "990000");
		str_err_code = "990000";

		for (n_cnt=0; n_cnt<2000; n_cnt++)
		{  
			if ( (st_alarm.mstr_e_code[n_cnt]).Compare(str_err_code) == 0 )
			{
				n_cur_num = n_cnt ; 
				break;
			}
		}
		/* ************************************************************************** */
	}
	
	/* ************************************************************************** */
    /* �߻��� �˶��� ���� ���¿� �޽��� ���� ������ �����Ѵ�                      */
    /* ************************************************************************** */
//	st_alarm.mn_cur_state = atoi(st_alarm.mstr_e_state[n_cur_num]);
	st_alarm.mstr_cur_state = st_alarm.mstr_e_state[n_cur_num];
	st_alarm.mstr_cur_msg = st_alarm.mstr_e_msg[n_cur_num];
	/* ************************************************************************** */
}
/* ****************************************************************************** */
void CMyJamData::On_UnderDaily_ListFile_Add(CString str_alarm_code, CString str_display_time, CString str_alarm_msg)
{
	CString mstr_file_name;    // ���������� ������ ���� �̸� ���� ���� 
	CString mstr_create_file;  // �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ���� 
	CString mstr_list_name, mstr_temp_data;  // �� �κк� �˶� �߻� Ƚ�� ���� ������ �α� ���� ���� ���� ���� 
	CString mstr_content;  // �� ���ο� ����� ���ڿ� ���� ���� ���� 
	int mn_existence;      // ���� ���� ���� ���� �÷��� 
	char fileName[256];    // �˻��� ���� ���� ���� �Լ� 
	FILE  *fp ;            // ���Ͽ� ���� ������ ���� ���� 
	
	CString str_title_time, str_file_time, str_new_file;		// ���Ͽ� ����� Ÿ��Ʋ �ð� ���� ����
	int n_cur_year, n_cur_month, n_cur_day;		// ��, ��, �� ���� ����
	
	COleDateTime mtime_cur;						// ���� �ð� ���� ����
	CTime mp_time_cur;							// Ÿ��Ʋ �ð� ���� ����
	
	/* ************************************************************************** */
	/* ���� �̸����� ����� ��¥ �����Ѵ�                                         */
	/* ************************************************************************** */
	mtime_cur = COleDateTime::GetCurrentTime();
	
// 	COleDateTimeSpan span( 0, 22, 0, 0 ); // �Ϸ�.
// 	COleDateTime timeLastDay( m_timeAlarmLastDay );
// 	COleDateTime timeSpan = COleDateTime::GetCurrentTime() - span;
// 	if( timeSpan >= timeLastDay )
// 	{
// 		COleDateTimeSpan span2( 1, 0, 0, 0 );
// 		timeSpan += span2;
// 		timeSpan.GetAsSystemTime(m_timeAlarmLastDay );
// 		m_timeAlarmLastDay.wHour = 0;
// 		m_timeAlarmLastDay.wMinute = 0;
// 		m_timeAlarmLastDay.wSecond = 0;
// 		m_timeAlarmLastDay.wMilliseconds = 0;
// 		
// 		AMTRegistry::RegWriteAlarmTime( m_timeAlarmLastDay );
// 		n_cur_year = timeSpan.GetYear();  
// 		n_cur_month = timeSpan.GetMonth();  
// 		n_cur_day = timeSpan.GetDay(); 
// 	}
// 	else
// 	{
		n_cur_year = mtime_cur.GetYear();  
		n_cur_month = mtime_cur.GetMonth();  
		n_cur_day = mtime_cur.GetDay(); 
// 	}

	
	str_new_file.Format("DY%04d%02d%02d", n_cur_year, n_cur_month, n_cur_day);
	
	if (str_alarm_code.IsEmpty()==TRUE)  /* �˶� �ڵ� ������ */
	{
		//Func.MsgLog("Alarm �ڵ� ����!.."); 
		return;
	}
	
	mstr_create_file = "D:\\AMTLOG\\Alarm\\UnderDaily\\" + str_new_file;
	mstr_create_file += ".TXT";
	
	sprintf(fileName, "%s", mstr_create_file);
	mn_existence = access(fileName,0);
	
	if (mn_existence == -1)  /* ���� ������ */
	{
		mstr_create_file = "D:\\AMTLOG\\Alarm\\UnderDaily\\" + str_new_file;
		mstr_create_file += ".TXT";
		/* ********************************************************************** */
	}
	
	/* ************************************************************************** */
	/* �˶� �߻� Ƚ�� ���� ���� ���Ͽ� �߰� ������ ���� ���Ϸ� ����               */
	/* ************************************************************************** */
	if ((fp=fopen(mstr_create_file,"a+"))==NULL)  
	{
		Func.MsgLog("1.File open failed!..");
		return;
	}
	/* ************************************************************************** */
	
	/* ************************************************************************** */
	/* �α� ���Ͽ� ���� �߻��� �˶� ���� �����Ѵ�                                 */
	/* ************************************************************************** */
	//mstr_content = "--------------------------------------------------------";
	//fprintf(fp,"%s\n",mstr_content) ;
	
	st_alarm.mn_e_list++;
	
	mstr_temp_data.Format("| %4d |", st_alarm.mn_e_list);
	mstr_content = mstr_temp_data; 
	mstr_temp_data.Format(" %6s |", str_alarm_code);
	mstr_content += mstr_temp_data; 
	mstr_temp_data.Format(" %-44s |", str_alarm_msg);
	mstr_content += mstr_temp_data;
	mstr_temp_data.Format("          |     |");
	mstr_content += mstr_temp_data;
	mstr_temp_data.Format(" %17s |", str_display_time);
	mstr_content += mstr_temp_data;
	fprintf(fp,"%s\n",mstr_content) ;
	
	mstr_content = "+------------------------------------------------------------------------------------------------------+";
	fprintf(fp,"%s\n",mstr_content) ;
	
	if (ferror(fp))  
	{
		Func.MsgLog("file save failed!..") ;
		fclose(fp);
		return ;
	}
	/* ************************************************************************** */
	
	fclose(fp);  /* ���� ���� */
}

void CMyJamData::On_Daily_ListFile_Add(CString str_alarm_code, CString str_display_time, CString str_alarm_msg)
{
	CString mstr_file_name;    // ���������� ������ ���� �̸� ���� ���� 
	CString mstr_create_file,mstr_create_file1;  // �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ���� 
	CString mstr_list_name, mstr_temp_data,mstr_temp_data1;  // �� �κк� �˶� �߻� Ƚ�� ���� ������ �α� ���� ���� ���� ���� 
	CString mstr_content,mstr_content1;  // �� ���ο� ����� ���ڿ� ���� ���� ���� 
	int mn_existence;      // ���� ���� ���� ���� �÷��� 
	char fileName[256];    // �˻��� ���� ���� ���� �Լ� 
	FILE  *fp ;            // ���Ͽ� ���� ������ ���� ���� 
	FILE *fp1;

	CString str_title_time, str_file_time, str_new_file,str_new_file1;		// ���Ͽ� ����� Ÿ��Ʋ �ð� ���� ����
	int n_cur_year, n_cur_month, n_cur_day;		// ��, ��, �� ���� ����
	
	COleDateTime mtime_cur;						// ���� �ð� ���� ����
	CTime mp_time_cur;							// Ÿ��Ʋ �ð� ���� ����
	
	/* ************************************************************************** */
	/* ���� �̸����� ����� ��¥ �����Ѵ�                                         */
	/* ************************************************************************** */
	mtime_cur = COleDateTime::GetCurrentTime();
	
	COleDateTimeSpan span( 0, 22, 0, 0 ); // �Ϸ�.
	COleDateTime timeLastDay( m_timeAlarmLastDay );
	COleDateTime timeSpan = COleDateTime::GetCurrentTime() - span;
	if( timeSpan >= timeLastDay )
	{
		COleDateTimeSpan span2( 1, 0, 0, 0 );
		timeSpan += span2;
		timeSpan.GetAsSystemTime( m_timeAlarmLastDay );
		m_timeAlarmLastDay.wHour = 0;
		m_timeAlarmLastDay.wMinute = 0;
		m_timeAlarmLastDay.wSecond = 0;
		m_timeAlarmLastDay.wMilliseconds = 0;
		
		AMTRegistry::RegWriteAlarmTime( m_timeAlarmLastDay );
		n_cur_year = timeSpan.GetYear();  
		n_cur_month = timeSpan.GetMonth();  
		n_cur_day = timeSpan.GetDay(); 
		st_alarm.mn_e_list = 0;
	}
	else
	{
		n_cur_year = timeLastDay.GetYear();// timeSpan.GetYear();  
		n_cur_month = timeLastDay.GetMonth();// timeSpan.GetMonth();  
		n_cur_day = timeLastDay.GetDay();// timeSpan.GetDay(); 
	}
	
	str_new_file.Format("DY%04d%02d%02d", n_cur_year, n_cur_month, n_cur_day);
	str_new_file1.Format("Error_%04d%02d%02d", n_cur_year, n_cur_month, n_cur_day);

	if (str_alarm_code.IsEmpty()==TRUE)  /* �˶� �ڵ� ������ */
	{
		//Func.MsgLog("Alarm �ڵ� ����!.."); 
		return;
	}

	mstr_create_file = "D:\\AMTLOG\\Alarm\\Daily\\" + str_new_file;
	mstr_create_file += ".TXT";

	mstr_create_file1 = st_path.mstr_error_path + str_new_file1;
	mstr_create_file1 += ".TXT";

	sprintf(fileName, "%s", mstr_create_file);
	mn_existence = access(fileName,0);
	
	if (mn_existence == -1)  /* ���� ������ */
	{
		mstr_create_file = "D:\\AMTLOG\\Alarm\\Daily\\" + str_new_file;
		mstr_create_file += ".TXT";
		/* ********************************************************************** */
	}

	sprintf(fileName, "%s", mstr_create_file1);
	mn_existence = access(fileName,0);
	
	if (mn_existence == -1)  /* ���� ������ */
	{
		mstr_create_file1 = st_path.mstr_error_path + str_new_file1;
		mstr_create_file1 += ".TXT";
		/* ********************************************************************** */
	}

	/* ************************************************************************** */
	/* �˶� �߻� Ƚ�� ���� ���� ���Ͽ� �߰� ������ ���� ���Ϸ� ����               */
	/* ************************************************************************** */
	if ((fp=fopen(mstr_create_file,"a+"))==NULL)  
	{
		Func.MsgLog("2.File open failed!..");
		return;
	}
	if ((fp1=fopen(mstr_create_file1,"a+"))==NULL)  
	{
		Func.MsgLog("2.File1 open failed!..");
		fclose(fp);
		return;
	}
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* �α� ���Ͽ� ���� �߻��� �˶� ���� �����Ѵ�                                 */
	/* ************************************************************************** */
	//mstr_content = "--------------------------------------------------------";
	//fprintf(fp,"%s\n",mstr_content) ;

	st_alarm.mn_e_list++;

	mstr_temp_data.Format("| %4d |", st_alarm.mn_e_list);
	mstr_content = mstr_temp_data; 
	mstr_temp_data.Format(" %6s |", str_alarm_code);
	mstr_content += mstr_temp_data; 
	mstr_temp_data.Format(" %-44s |", str_alarm_msg);
	mstr_content += mstr_temp_data;
	mstr_temp_data.Format("          |     |");
	mstr_content += mstr_temp_data;
	mstr_temp_data.Format(" %17s |", str_display_time);
	mstr_content += mstr_temp_data;
	fprintf(fp,"%s\n",mstr_content) ;

	mstr_content = "+------------------------------------------------------------------------------------------------------+";
	fprintf(fp,"%s\n",mstr_content) ;

	if (ferror(fp))  
	{
		Func.MsgLog("file save failed!..") ;
		fclose(fp);
		return ;
	}
	/* ************************************************************************** */

	fclose(fp);  /* ���� ���� */

	//2015.0513
	mstr_temp_data1.Format(" %17s, ", str_display_time);
	mstr_content1 = mstr_temp_data1;
	mstr_temp_data1.Format(" %6s, ", str_alarm_code);
	mstr_content1 += mstr_temp_data1; 
	mstr_temp_data1.Format(" %30s, ", st_handler.m_strLogEvent);
	mstr_content1 += mstr_temp_data1; 	
	mstr_temp_data1.Format(" %-44s ", str_alarm_msg);
	mstr_content1 += mstr_temp_data1; 
	fprintf(fp1,"%s\n",mstr_content1) ;
	
	if (ferror(fp1))  
	{
		Func.MsgLog("file1 save failed!..") ;
		fclose(fp1);
		return ;
	}
	fclose(fp1);
}

CString GetJamCode_Work_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

//525100 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check Off Error."
//525101 1 00 "Top ID Buffer LD1 Shifter Hook Clamp Check On Error."
//525110 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check Off Error."
//525111 1 00 "Top ID Buffer LD1 Shifter Hook UnClamp Check On Error."
//525120 1 00 "Top ID Buffer LD2 Shifter Left Hook Clamp Check Off Error."
//525121 1 00 "Top ID Buffer LD2 Shifter Left Hook Clamp Check On Error."
//525130 1 00 "Top ID Buffer LD2 Shifter Left Hook UnClamp Check Off Error."
//525131 1 00 "Top ID Buffer LD2 Shifter Left Hook UnClamp Check On Error."
//525140 1 00 "Top ID Buffer LD2 Shifter Right Hook Clamp Check Off Error."
//525141 1 00 "Top ID Buffer LD2 Shifter Right Hook Clamp Check On Error."
//525150 1 00 "Top ID Buffer LD2 Shifter Right Hook UnClamp Check Off Error."
//525151 1 00 "Top ID Buffer LD2 Shifter Right Hook UnClamp Check On Error."
CString GetJamCode_Hook_Clamp_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

//525080 1 00 "Top ID Buffer LD1 Shifter Hook Forward Check Off Error."
//525081 1 00 "Top ID Buffer LD1 Shifter Hook Forward Check On Error."
//525090 1 00 "Top ID Buffer LD1 Shifter Hook Backward Check Off Error."
//525091 1 00 "Top ID Buffer LD1 Shifter Hook Backward Check On Error."
//527000 1 00 "Top ID Buffer LD2 Shifter Hook Forward Check Off Error."
//527001 1 00 "Top ID Buffer LD2 Shifter Hook Forward Check On Error."
//527010 1 00 "Top ID Buffer LD2 Shifter Hook Backward Check Off Error."
//527011 1 00 "Top ID Buffer LD2 Shifter Hook Backward Check On Error."
CString GetJamCode_Hook_FwdBwd_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}
//527020 1 00 "Top ID Buffer1.2 Clamp Check Off Error."
//527021 1 00 "Top ID Buffer1.2 Clamp Check On Error."
//527030 1 00 "Top ID Buffer1.2 UnClamp Check Off Error."
//527031 1 00 "Top ID Buffer1.2 UnClamp Check On Error."
CString GetJamCode_Load_Clamp_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Paper_FwdBwd_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_FeederLock_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Bcr_Vacuum_Fwdbwd_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Bcr_Plate_UoDown_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Bcr_Guide_FwdBwd_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Bcr_Guide_UpDown_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Rolling_FwdBwd_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Unload_Picker_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Unload_Convey_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}


CString GetJamCode_VacuumDn_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "5%04d%d", iIdx, iOn );
	return strJamCode;
}

//223060 1 A "Barcode Robot Picker #1 Cylinder Up Check Off Error."
//223061 1 A "Barcode Robot Picker #1 Cylinder Up Check On Error."
//223070 1 A "Barcode Robot Picker #1 Cylinder Down Check Off Error."
//223071 1 A "Barcode Robot Picker #1 Cylinder Down Check On Error."
//223080 1 A "Barcode Robot Picker #2 Cylinder Up Check Off Error."
//223081 1 A "Barcode Robot Picker #2 Cylinder Up Check On Error."
//223090 1 A "Barcode Robot Picker #2 Cylinder Down Check Off Error."
//223091 1 A "Barcode Robot Picker #2 Cylinder Down Check On Error."
//223100 1 A "Barcode Robot Picker #3 Cylinder Up Check Off Error."
//223101 1 A "Barcode Robot Picker #3 Cylinder Up Check On Error."
//223110 1 A "Barcode Robot Picker #3 Cylinder Down Check Off Error."
//223111 1 A "Barcode Robot Picker #3 Cylinder Down Check On Error."
//223120 1 A "Barcode Robot Picker #4 Cylinder Up Check Off Error."
//223121 1 A "Barcode Robot Picker #4 Cylinder Up Check On Error."
//223130 1 A "Barcode Robot Picker #4 Cylinder Down Check Off Error."
//223131 1 A "Barcode Robot Picker #4 Cylinder Down Check On Error."
CString GetJamCode_BcrVacuumDn_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "223%02d%d", (iIdx*2)+6+1+iOn, iOn );
	return strJamCode;
}
//223140 1 A "Barcode Robot Rotator 0 degree Check Off Error."
//223141 1 A "Barcode Robot Rotator 0 degree Check On Error."
//223150 1 A "Barcode Robot Rotator 180 degree Check Off Error."
//223151 1 A "Barcode Robot Rotator 180 degree Check On Error."
CString GetJamCode_BcrRotator_Time( int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", iIdx, iOn );
	return strJamCode;
}

//204140 0 A " "Test-Site Picker Robot Rotator Cylinder On Check Off Error."
//204141 0 A " "Test-Site Picker Robot Rotator Cylinder On Check On Error."
//204150 0 A " "Test-Site Picker Robot Rotator Cylinder Off Check Off Error."
//204151 0 A " "Test-Site Picker Robot Rotator Cylinder Off Check On Error."
CString GetJamCode_Rotator_Time( int iIdx, int iOn )
{//204090 0 A "Test-Site Picker Robot Rotator Cylinder Off Off Error."
 //204091 0 A "Test-Site Picker Robot Rotator Cylinder Off On Error."
	CString strJamCode;
	strJamCode.Format( "2%04d%d", iIdx, iOn );
	return strJamCode;
}

CString GetJamCode_Rotator_Chk( int iOn )
{
//204140 0 A "Test-Site Picker Robot Rotator Cylinder On Check Off Error."
//204141 0 A "Test-Site Picker Robot Rotator Cylinder On Check On Error."
//204150 0 A "Test-Site Picker Robot Rotator Cylinder Off Check Off Error."
//204151 0 A "Test-Site Picker Robot Rotator Cylinder Off Check On Error."

	CString strJamCode;
	strJamCode.Format( "20414%d", iOn );
	return strJamCode;
}

CString GetJamCode_SorterPickerDn_Chk( int iIdx, int iOn )
{
//202000 0 A "Sorting Robot Picker #1 Cylinder On/Off Off Error."
//202001 0 A "Sorting Robot Picker #1 Cylinder On/Off On Error."
//202010 0 A "Sorting Robot Picker #2 Cylinder On/Off Off Error."
//202011 0 A "Sorting Robot Picker #2 Cylinder On/Off On Error."
//202020 0 A "Sorting Robot Picker #3 Cylinder On/Off Off Error."
//202021 0 A "Sorting Robot Picker #3 Cylinder On/Off On Error."
//202030 0 A "Sorting Robot Picker #4 Cylinder On/Off Off Error."
//202031 0 A "Sorting Robot Picker #4 Cylinder On/Off On Error."

//202060 0 A "Sorting Robot Picker #1 Cylinder Up Check Off Error."
//202061 0 A "Sorting Robot Picker #1 Cylinder Up Check On Error."
//202070 0 A "Sorting Robot Picker #1 Cylinder Down Check Off Error."
//202071 0 A "Sorting Robot Picker #1 Cylinder Down Check On Error."
//202080 0 A "Sorting Robot Picker #2 Cylinder Up Check Off Error."
//202081 0 A "Sorting Robot Picker #2 Cylinder Up Check On Error."
//202090 0 A "Sorting Robot Picker #2 Cylinder Down Check Off Error."
//202091 0 A "Sorting Robot Picker #2 Cylinder Down Check On Error."
//202100 0 A "Sorting Robot Picker #3 Cylinder Up Check Off Error."
//202101 0 A "Sorting Robot Picker #3 Cylinder Up Check On Error."
//202110 0 A "Sorting Robot Picker #3 Cylinder Down Check Off Error."
//202111 0 A "Sorting Robot Picker #3 Cylinder Down Check On Error."
//202120 0 A "Sorting Robot Picker #4 Cylinder Up Check Off Error."
//202121 0 A "Sorting Robot Picker #4 Cylinder Up Check On Error."
//202130 0 A "Sorting Robot Picker #4 Cylinder Down Check Off Error."
//202131 0 A "Sorting Robot Picker #4 Cylinder Down Check On Error."
	CString strJamCode;
	strJamCode.Format( "202%02d%d", 7+(2*iIdx), iOn );
	return strJamCode;
}

//210040 0 A " "Test-Site C.O.K Plate #1 Forward Check Off Error."
//210041 0 A " "Test-Site C.O.K Plate #1 Forward Check On Error."
//210050 0 A " "Test-Site C.O.K Plate #1 Backward Check Off Error."
//210051 0 A " "Test-Site C.O.K Plate #1 Backward Check On Error."
//210060 0 A " "Test-Site C.O.K Plate #2 Forward Check Off Error."
//210061 0 A " "Test-Site C.O.K Plate #2 Forward Check On Error."
//210070 0 A " "Test-Site C.O.K Plate #2 Backward Check Off Error."
//210071 0 A " "Test-Site C.O.K Plate #2 Backward Check On Error."
//210080 0 A " "Test-Site C.O.K Plate #3 Forward Check Off Error."
//210081 0 A " "Test-Site C.O.K Plate #3 Forward Check On Error."
//210090 0 A " "Test-Site C.O.K Plate #3 Backward Check Off Error."
//210091 0 A " "Test-Site C.O.K Plate #3 Backward Check On Error."
//210100 0 A " "Test-Site C.O.K Plate #4 Forward Check Off Error."
//210101 0 A " "Test-Site C.O.K Plate #4 Forward Check On Error."
//210110 0 A " "Test-Site C.O.K Plate #4 Backward Check Off Error."
//210111 0 A " "Test-Site C.O.K Plate #4 Backward Check On Error."
//210120 0 A " "Test-Site C.O.K Plate #5 Forward Check Off Error."
//210121 0 A " "Test-Site C.O.K Plate #5 Forward Check On Error."
//210130 0 A " "Test-Site C.O.K Plate #5 Backward Check Off Error."
//210131 0 A " "Test-Site C.O.K Plate #5 Backward Check On Error."
CString GetJamCode_TS_Plate_Chk( int nSite, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", nSite, iOn );
	return strJamCode;
}
//211100 0 A " "Test-Site C.O.K Insert #1- 1 Forward Check Off Error."
//211101 0 A " "Test-Site C.O.K Insert #1- 1 Forward Check On Error."
//211110 0 A " "Test-Site C.O.K Insert #1- 1 Backward Check Off Error."
//211111 0 A " "Test-Site C.O.K Insert #1- 1 Backward Check On Error."
//211120 0 A " "Test-Site C.O.K Insert #1- 2 Forward Check Off Error."
//211121 0 A " "Test-Site C.O.K Insert #1- 2 Forward Check On Error."
//211130 0 A " "Test-Site C.O.K Insert #1- 2 Backward Check Off Error."
//211131 0 A " "Test-Site C.O.K Insert #1- 2 Backward Check On Error."
//211140 0 A " "Test-Site C.O.K Insert #1- 3 Forward Check Off Error."
//211141 0 A " "Test-Site C.O.K Insert #1- 3 Forward Check On Error."
//211150 0 A " "Test-Site C.O.K Insert #1- 3 Backward Check Off Error."
//211151 0 A " "Test-Site C.O.K Insert #1- 3 Backward Check On Error."
//212000 0 A " "Test-Site C.O.K Insert #1- 4 Forward Check Off Error."
//212001 0 A " "Test-Site C.O.K Insert #1- 4 Forward Check On Error."
//212010 0 A " "Test-Site C.O.K Insert #1- 4 Backward Check Off Error."
//212011 0 A " "Test-Site C.O.K Insert #1- 4 Backward Check On Error."
//212020 0 A " "Test-Site C.O.K Insert #1- 5 Forward Check Off Error."
//212021 0 A " "Test-Site C.O.K Insert #1- 5 Forward Check On Error."
//212030 0 A " "Test-Site C.O.K Insert #1- 5 Backward Check Off Error."
//212031 0 A " "Test-Site C.O.K Insert #1- 5 Backward Check On Error."
//212040 0 A " "Test-Site C.O.K Insert #1- 6 Forward Check Off Error."
//212041 0 A " "Test-Site C.O.K Insert #1- 6 Forward Check On Error."
//212050 0 A " "Test-Site C.O.K Insert #1- 6 Backward Check Off Error."
//212051 0 A " "Test-Site C.O.K Insert #1- 6 Backward Check On Error."
//212060 0 A " "Test-Site C.O.K Insert #2- 1 Forward Check Off Error."
//212061 0 A " "Test-Site C.O.K Insert #2- 1 Forward Check On Error."
//212070 0 A " "Test-Site C.O.K Insert #2- 1 Backward Check Off Error."
//212071 0 A " "Test-Site C.O.K Insert #2- 1 Backward Check On Error."
//212080 0 A " "Test-Site C.O.K Insert #2- 2 Forward Check Off Error."
//212081 0 A " "Test-Site C.O.K Insert #2- 2 Forward Check On Error."
//212090 0 A " "Test-Site C.O.K Insert #2- 2 Backward Check Off Error."
//212091 0 A " "Test-Site C.O.K Insert #2- 2 Backward Check On Error."
//212100 0 A " "Test-Site C.O.K Insert #2- 3 Forward Check Off Error."
//212101 0 A " "Test-Site C.O.K Insert #2- 3 Forward Check On Error."
//212110 0 A " "Test-Site C.O.K Insert #2- 3 Backward Check Off Error."
//212111 0 A " "Test-Site C.O.K Insert #2- 3 Backward Check On Error."
//212120 0 A " "Test-Site C.O.K Insert #2- 4 Forward Check Off Error."
//212121 0 A " "Test-Site C.O.K Insert #2- 4 Forward Check On Error."
//212130 0 A " "Test-Site C.O.K Insert #2- 4 Backward Check Off Error."
//212131 0 A " "Test-Site C.O.K Insert #2- 4 Backward Check On Error."
//212140 0 A " "Test-Site C.O.K Insert #2- 5 Forward Check Off Error."
//212141 0 A " "Test-Site C.O.K Insert #2- 5 Forward Check On Error."
//212150 0 A " "Test-Site C.O.K Insert #2- 5 Backward Check Off Error."
//212151 0 A " "Test-Site C.O.K Insert #2- 5 Backward Check On Error."
//213000 0 A " "Test-Site C.O.K Insert #2- 6 Forward Check Off Error."
//213001 0 A " "Test-Site C.O.K Insert #2- 6 Forward Check On Error."
//213010 0 A " "Test-Site C.O.K Insert #2- 6 Backward Check Off Error."
//213011 0 A " "Test-Site C.O.K Insert #2- 6 Backward Check On Error."
//213020 0 A " "Test-Site C.O.K Insert #3- 1 Forward Check Off Error."
//213021 0 A " "Test-Site C.O.K Insert #3- 1 Forward Check On Error."
//213030 0 A " "Test-Site C.O.K Insert #3- 1 Backward Check Off Error."
//213031 0 A " "Test-Site C.O.K Insert #3- 1 Backward Check On Error."
//213040 0 A " "Test-Site C.O.K Insert #3- 2 Forward Check Off Error."
//213041 0 A " "Test-Site C.O.K Insert #3- 2 Forward Check On Error."
//213050 0 A " "Test-Site C.O.K Insert #3- 2 Backward Check Off Error."
//213051 0 A " "Test-Site C.O.K Insert #3- 2 Backward Check On Error."
//213060 0 A " "Test-Site C.O.K Insert #3- 3 Forward Check Off Error."
//213061 0 A " "Test-Site C.O.K Insert #3- 3 Forward Check On Error."
//213070 0 A " "Test-Site C.O.K Insert #3- 3 Backward Check Off Error."
//213071 0 A " "Test-Site C.O.K Insert #3- 3 Backward Check On Error."
//213080 0 A " "Test-Site C.O.K Insert #3- 4 Forward Check Off Error."
//213081 0 A " "Test-Site C.O.K Insert #3- 4 Forward Check On Error."
//213090 0 A " "Test-Site C.O.K Insert #3- 4 Backward Check Off Error."
//213091 0 A " "Test-Site C.O.K Insert #3- 4 Backward Check On Error."
//213100 0 A " "Test-Site C.O.K Insert #3- 5 Forward Check Off Error."
//213101 0 A " "Test-Site C.O.K Insert #3- 5 Forward Check On Error."
//213110 0 A " "Test-Site C.O.K Insert #3- 5 Backward Check Off Error."
//213111 0 A " "Test-Site C.O.K Insert #3- 5 Backward Check On Error."
//213120 0 A " "Test-Site C.O.K Insert #3- 6 Forward Check Off Error."
//213121 0 A " "Test-Site C.O.K Insert #3- 6 Forward Check On Error."
//213130 0 A " "Test-Site C.O.K Insert #3- 6 Backward Check Off Error."
//213131 0 A " "Test-Site C.O.K Insert #3- 6 Backward Check On Error."
//213140 0 A " "Test-Site C.O.K Insert #4- 1 Forward Check Off Error."
//213141 0 A " "Test-Site C.O.K Insert #4- 1 Forward Check On Error."
//213150 0 A " "Test-Site C.O.K Insert #4- 1 Backward Check Off Error."
//213151 0 A " "Test-Site C.O.K Insert #4- 1 Backward Check On Error."
//214000 0 A " "Test-Site C.O.K Insert #4- 2 Forward Check Off Error."
//214001 0 A " "Test-Site C.O.K Insert #4- 2 Forward Check On Error."
//214010 0 A " "Test-Site C.O.K Insert #4- 2 Backward Check Off Error."
//214011 0 A " "Test-Site C.O.K Insert #4- 2 Backward Check On Error."
//214020 0 A " "Test-Site C.O.K Insert #4- 3 Forward Check Off Error."
//214021 0 A " "Test-Site C.O.K Insert #4- 3 Forward Check On Error."
//214030 0 A " "Test-Site C.O.K Insert #4- 3 Backward Check Off Error."
//214031 0 A " "Test-Site C.O.K Insert #4- 3 Backward Check On Error."
//214040 0 A " "Test-Site C.O.K Insert #4- 4 Forward Check Off Error."
//214041 0 A " "Test-Site C.O.K Insert #4- 4 Forward Check On Error."
//214050 0 A " "Test-Site C.O.K Insert #4- 4 Backward Check Off Error."
//214051 0 A " "Test-Site C.O.K Insert #4- 4 Backward Check On Error."
//214060 0 A " "Test-Site C.O.K Insert #4- 5 Forward Check Off Error."
//214061 0 A " "Test-Site C.O.K Insert #4- 5 Forward Check On Error."
//214070 0 A " "Test-Site C.O.K Insert #4- 5 Backward Check Off Error."
//214071 0 A " "Test-Site C.O.K Insert #4- 5 Backward Check On Error."
//214080 0 A " "Test-Site C.O.K Insert #4- 6 Forward Check Off Error."
//214081 0 A " "Test-Site C.O.K Insert #4- 6 Forward Check On Error."
//214090 0 A " "Test-Site C.O.K Insert #4- 6 Backward Check Off Error."
//214091 0 A " "Test-Site C.O.K Insert #4- 6 Backward Check On Error."
//214100 0 A " "Test-Site C.O.K Insert #5- 1 Forward Check Off Error."
//214101 0 A " "Test-Site C.O.K Insert #5- 1 Forward Check On Error."
//214110 0 A " "Test-Site C.O.K Insert #5- 1 Backward Check Off Error."
//214111 0 A " "Test-Site C.O.K Insert #5- 1 Backward Check On Error."
//214120 0 A " "Test-Site C.O.K Insert #5- 2 Forward Check Off Error."
//214121 0 A " "Test-Site C.O.K Insert #5- 2 Forward Check On Error."
//214130 0 A " "Test-Site C.O.K Insert #5- 2 Backward Check Off Error."
//214131 0 A " "Test-Site C.O.K Insert #5- 2 Backward Check On Error."
//214140 0 A " "Test-Site C.O.K Insert #5- 3 Forward Check Off Error."
//214141 0 A " "Test-Site C.O.K Insert #5- 3 Forward Check On Error."
//214150 0 A " "Test-Site C.O.K Insert #5- 3 Backward Check Off Error."
//214151 0 A " "Test-Site C.O.K Insert #5- 3 Backward Check On Error."
//215000 0 A " "Test-Site C.O.K Insert #5- 4 Forward Check Off Error."
//215001 0 A " "Test-Site C.O.K Insert #5- 4 Forward Check On Error."
//215010 0 A " "Test-Site C.O.K Insert #5- 4 Backward Check Off Error."
//215011 0 A " "Test-Site C.O.K Insert #5- 4 Backward Check On Error."
//215020 0 A " "Test-Site C.O.K Insert #5- 5 Forward Check Off Error."
//215021 0 A " "Test-Site C.O.K Insert #5- 5 Forward Check On Error."
//215030 0 A " "Test-Site C.O.K Insert #5- 5 Backward Check Off Error."
//215031 0 A " "Test-Site C.O.K Insert #5- 5 Backward Check On Error."
//215040 0 A " "Test-Site C.O.K Insert #5- 6 Forward Check Off Error."
//215041 0 A " "Test-Site C.O.K Insert #5- 6 Forward Check On Error."
//215050 0 A " "Test-Site C.O.K Insert #5- 6 Backward Check Off Error."
//215051 0 A " "Test-Site C.O.K Insert #5- 6 Backward Check On Error."
CString GetJamCode_TS_Insert_Chk( int nSite, int iIdx, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", iIdx, iOn );
	return strJamCode;
}
//211000 0 A " "Test-Site C.O.K Lock #1 Check Off Error."
//211001 0 A " "Test-Site C.O.K Lock #1 Check On Error."
//211010 0 A " "Test-Site C.O.K UnLock #1 Check Off Error."
//211011 0 A " "Test-Site C.O.K UnLock #1 Check On Error."
//211020 0 A " "Test-Site C.O.K Lock #2 Check Off Error."
//211021 0 A " "Test-Site C.O.K Lock #2 Check On Error."
//211030 0 A " "Test-Site C.O.K UnLock #2 Check Off Error."
//211031 0 A " "Test-Site C.O.K UnLock #2 Check On Error."
//211040 0 A " "Test-Site C.O.K Lock #3 Check Off Error."
//211041 0 A " "Test-Site C.O.K Lock #3 Check On Error."
//211050 0 A " "Test-Site C.O.K UnLock #3 Check Off Error."
//211051 0 A " "Test-Site C.O.K UnLock #3 Check On Error."
//211060 0 A " "Test-Site C.O.K Lock #4 Check Off Error."
//211061 0 A " "Test-Site C.O.K Lock #4 Check On Error."
//211070 0 A " "Test-Site C.O.K UnLock #4 Check Off Error."
//211071 0 A " "Test-Site C.O.K UnLock #4 Check On Error."
//211080 0 A " "Test-Site C.O.K Lock #5 Check Off Error."
//211081 0 A " "Test-Site C.O.K Lock #5 Check On Error."
//211090 0 A " "Test-Site C.O.K UnLock #5 Check Off Error."
//211091 0 A " "Test-Site C.O.K UnLock #5 Check On Error."
CString GetJamCode_TS_Lock_Chk( int nSite, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", nSite, iOn );
	return strJamCode;
}
//210000 0 A " "Hifix Left Clamp Check Off Error."
//210001 0 A " "Hifix Left Clamp Check On Error."
//210010 0 A " "Hifix Left UnClamp Check Off Error."
//210011 0 A " "Hifix Left UnClamp Check On Error."
//210020 0 A " "Hifix Right Clamp Check Off Error."
//210021 0 A " "Hifix Right Clamp Check On Error."
//210030 0 A " "Hifix Right UnClamp Check Off Error."
//210031 0 A " "Hifix Right UnClamp Check On Error."
CString GetJamCode_HF_Clamp_Chk( int nSite, int iOn )
{
	CString strJamCode;
// 	strJamCode.Format( "C0F%d0%d", nSite+1, iOn );
	strJamCode.Format( "2%04d%d", nSite, iOn );
	return strJamCode;
}
//206010 0 A " "Test-Site C.O.K Insert #1- 1 Forward/Backward On/Off Off Error."
//206011 0 A " "Test-Site C.O.K Insert #1- 1 Forward/Backward On/Off On Error."
//206020 0 A " "Test-Site C.O.K Insert #1- 2 Forward/Backward On/Off Off Error."
//206021 0 A " "Test-Site C.O.K Insert #1- 2 Forward/Backward On/Off On Error."
//206030 0 A " "Test-Site C.O.K Insert #1- 3 Forward/Backward On/Off Off Error."
//206031 0 A " "Test-Site C.O.K Insert #1- 3 Forward/Backward On/Off On Error."
//206040 0 A " "Test-Site C.O.K Insert #1- 4 Forward/Backward On/Off Off Error."
//206041 0 A " "Test-Site C.O.K Insert #1- 4 Forward/Backward On/Off On Error."
//206050 0 A " "Test-Site C.O.K Insert #1- 5 Forward/Backward On/Off Off Error."
//206051 0 A " "Test-Site C.O.K Insert #1- 5 Forward/Backward On/Off On Error."
//206060 0 A " "Test-Site C.O.K Insert #1- 6 Forward/Backward On/Off Off Error."
//206061 0 A " "Test-Site C.O.K Insert #1- 6 Forward/Backward On/Off On Error."
//206070 0 A " "Test-Site C.O.K Insert #2- 1 Forward/Backward On/Off Off Error."
//206071 0 A " "Test-Site C.O.K Insert #2- 1 Forward/Backward On/Off On Error."
//206080 0 A " "Test-Site C.O.K Insert #2- 2 Forward/Backward On/Off Off Error."
//206081 0 A " "Test-Site C.O.K Insert #2- 2 Forward/Backward On/Off On Error."
//206090 0 A " "Test-Site C.O.K Insert #2- 3 Forward/Backward On/Off Off Error."
//206091 0 A " "Test-Site C.O.K Insert #2- 3 Forward/Backward On/Off On Error."
//206100 0 A " "Test-Site C.O.K Insert #2- 4 Forward/Backward On/Off Off Error."
//206101 0 A " "Test-Site C.O.K Insert #2- 4 Forward/Backward On/Off On Error."
//206110 0 A " "Test-Site C.O.K Insert #2- 5 Forward/Backward On/Off Off Error."
//206111 0 A " "Test-Site C.O.K Insert #2- 5 Forward/Backward On/Off On Error."
//206120 0 A " "Test-Site C.O.K Insert #2- 6 Forward/Backward On/Off Off Error."
//206121 0 A " "Test-Site C.O.K Insert #2- 6 Forward/Backward On/Off On Error."
//206130 0 A " "Test-Site C.O.K Insert #3- 1 Forward/Backward On/Off Off Error."
//206131 0 A " "Test-Site C.O.K Insert #3- 1 Forward/Backward On/Off On Error."
//206140 0 A " "Test-Site C.O.K Insert #3- 2 Forward/Backward On/Off Off Error."
//206141 0 A " "Test-Site C.O.K Insert #3- 2 Forward/Backward On/Off On Error."
//206150 0 A " "Test-Site C.O.K Insert #3- 3 Forward/Backward On/Off Off Error."
//206151 0 A " "Test-Site C.O.K Insert #3- 3 Forward/Backward On/Off On Error."
//207000 0 A " "Test-Site C.O.K Insert #3- 4 Forward/Backward On/Off Off Error."
//207001 0 A " "Test-Site C.O.K Insert #3- 4 Forward/Backward On/Off On Error."
//207010 0 A " "Test-Site C.O.K Insert #3- 5 Forward/Backward On/Off Off Error."
//207011 0 A " "Test-Site C.O.K Insert #3- 5 Forward/Backward On/Off On Error."
//207020 0 A " "Test-Site C.O.K Insert #3- 6 Forward/Backward On/Off Off Error."
//207021 0 A " "Test-Site C.O.K Insert #3- 6 Forward/Backward On/Off On Error."
//207030 0 A " "Test-Site C.O.K Insert #4- 1 Forward/Backward On/Off Off Error."
//207031 0 A " "Test-Site C.O.K Insert #4- 1 Forward/Backward On/Off On Error."
//207040 0 A " "Test-Site C.O.K Insert #4- 2 Forward/Backward On/Off Off Error."
//207041 0 A " "Test-Site C.O.K Insert #4- 2 Forward/Backward On/Off On Error."
//207050 0 A " "Test-Site C.O.K Insert #4- 3 Forward/Backward On/Off Off Error."
//207051 0 A " "Test-Site C.O.K Insert #4- 3 Forward/Backward On/Off On Error."
//207060 0 A " "Test-Site C.O.K Insert #4- 4 Forward/Backward On/Off Off Error."
//207061 0 A " "Test-Site C.O.K Insert #4- 4 Forward/Backward On/Off On Error."
//207070 0 A " "Test-Site C.O.K Insert #4- 5 Forward/Backward On/Off Off Error."
//207071 0 A " "Test-Site C.O.K Insert #4- 5 Forward/Backward On/Off On Error."
//207080 0 A " "Test-Site C.O.K Insert #4- 6 Forward/Backward On/Off Off Error."
//207081 0 A " "Test-Site C.O.K Insert #4- 6 Forward/Backward On/Off On Error."
//207090 0 A " "Test-Site C.O.K Insert #5- 1 Forward/Backward On/Off Off Error."
//207091 0 A " "Test-Site C.O.K Insert #5- 1 Forward/Backward On/Off On Error."
//207100 0 A " "Test-Site C.O.K Insert #5- 2 Forward/Backward On/Off Off Error."
//207101 0 A " "Test-Site C.O.K Insert #5- 2 Forward/Backward On/Off On Error."
//207110 0 A " "Test-Site C.O.K Insert #5- 3 Forward/Backward On/Off Off Error."
//207111 0 A " "Test-Site C.O.K Insert #5- 3 Forward/Backward On/Off On Error."
//207120 0 A " "Test-Site C.O.K Insert #5- 4 Forward/Backward On/Off Off Error."
//207121 0 A " "Test-Site C.O.K Insert #5- 4 Forward/Backward On/Off On Error."
//207130 0 A " "Test-Site C.O.K Insert #5- 5 Forward/Backward On/Off Off Error."
//207131 0 A " "Test-Site C.O.K Insert #5- 5 Forward/Backward On/Off On Error."
//207140 0 A " "Test-Site C.O.K Insert #5- 6 Forward/Backward On/Off Off Error."
//207141 0 A " "Test-Site C.O.K Insert #5- 6 Forward/Backward On/Off On Error."
CString GetJamCode_TS_Insert_Time( int nSite, int iIdx, int iOn )
{
	CString strJamCode;
//	if(nSite < 3 && iIdx < 2)
//	{
//		strJamCode.Format( "206%02d%d", (nSite * 6 + 1) + iIdx, iOn );
//	}
//	else if(nSite < 3 && iIdx < 3)
//	{
//		strJamCode.Format( "207%02d%d", iIdx, iOn );
//	}
//	else
//	{
//		strJamCode.Format( "207%02d%d", ((nSite-3)*6 + 3) + iIdx, iOn );
//	}
	strJamCode.Format( "2%04d%d", iIdx, iOn );
	return strJamCode;
}
//210040 0 A " "Test-Site C.O.K Plate #1 Forward Check Off Error."
//210041 0 A " "Test-Site C.O.K Plate #1 Forward Check On Error."
//210050 0 A " "Test-Site C.O.K Plate #1 Backward Check Off Error."
//210051 0 A " "Test-Site C.O.K Plate #1 Backward Check On Error."
//210060 0 A " "Test-Site C.O.K Plate #2 Forward Check Off Error."
//210061 0 A " "Test-Site C.O.K Plate #2 Forward Check On Error."
//210070 0 A " "Test-Site C.O.K Plate #2 Backward Check Off Error."
//210071 0 A " "Test-Site C.O.K Plate #2 Backward Check On Error."
//210080 0 A " "Test-Site C.O.K Plate #3 Forward Check Off Error."
//210081 0 A " "Test-Site C.O.K Plate #3 Forward Check On Error."
//210090 0 A " "Test-Site C.O.K Plate #3 Backward Check Off Error."
//210091 0 A " "Test-Site C.O.K Plate #3 Backward Check On Error."
//210100 0 A " "Test-Site C.O.K Plate #4 Forward Check Off Error."
//210101 0 A " "Test-Site C.O.K Plate #4 Forward Check On Error."
//210110 0 A " "Test-Site C.O.K Plate #4 Backward Check Off Error."
//210111 0 A " "Test-Site C.O.K Plate #4 Backward Check On Error."
//210120 0 A " "Test-Site C.O.K Plate #5 Forward Check Off Error."
//210121 0 A " "Test-Site C.O.K Plate #5 Forward Check On Error."
//210130 0 A " "Test-Site C.O.K Plate #5 Backward Check Off Error."
//210131 0 A " "Test-Site C.O.K Plate #5 Backward Check On Error."
CString GetJamCode_TS_Plate_Time( int nSite, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", nSite, iOn );
	return strJamCode;
}
//211000 0 A " "Test-Site C.O.K Lock #1 Check Off Error."
//211001 0 A " "Test-Site C.O.K Lock #1 Check On Error."
//211010 0 A " "Test-Site C.O.K UnLock #1 Check Off Error."
//211011 0 A " "Test-Site C.O.K UnLock #1 Check On Error."
//211020 0 A " "Test-Site C.O.K Lock #2 Check Off Error."
//211021 0 A " "Test-Site C.O.K Lock #2 Check On Error."
//211030 0 A " "Test-Site C.O.K UnLock #2 Check Off Error."
//211031 0 A " "Test-Site C.O.K UnLock #2 Check On Error."
//211040 0 A " "Test-Site C.O.K Lock #3 Check Off Error."
//211041 0 A " "Test-Site C.O.K Lock #3 Check On Error."
//211050 0 A " "Test-Site C.O.K UnLock #3 Check Off Error."
//211051 0 A " "Test-Site C.O.K UnLock #3 Check On Error."
//211060 0 A " "Test-Site C.O.K Lock #4 Check Off Error."
//211061 0 A " "Test-Site C.O.K Lock #4 Check On Error."
//211070 0 A " "Test-Site C.O.K UnLock #4 Check Off Error."
//211071 0 A " "Test-Site C.O.K UnLock #4 Check On Error."
//211080 0 A " "Test-Site C.O.K Lock #5 Check Off Error."
//211081 0 A " "Test-Site C.O.K Lock #5 Check On Error."
//211090 0 A " "Test-Site C.O.K UnLock #5 Check Off Error."
//211091 0 A " "Test-Site C.O.K UnLock #5 Check On Error."
CString GetJamCode_TS_Lock_Time( int nSite, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2%04d%d", nSite+1, iOn );
	return strJamCode;
}

CString GetJamCode_SorterModuleExist_Chk( int nPicker, int iOn )
{
//201090 0 A "Sorting Robot Picker #1 Vacuum Check Off Error."
//201091 0 A "Sorting Robot Picker #1 Vacuum Check On Error."
//201100 0 A "Sorting Robot Picker #2 Vacuum Check Off Error."
//201101 0 A "Sorting Robot Picker #2 Vacuum Check On Error."
//201110 0 A "Sorting Robot Picker #3 Vacuum Check Off Error."
//201111 0 A "Sorting Robot Picker #3 Vacuum Check On Error."
//201120 0 A "Sorting Robot Picker #4 Vacuum Check Off Error."
//201121 0 A "Sorting Robot Picker #4 Vacuum Check On Error."
	CString strJamCode;
	strJamCode.Format( "201%02d%d", nPicker+9, iOn );
	return strJamCode;
}
//204100 0 A " "Test-Site Picker Robot #1 Vacuum Check Off Error."
//204101 0 A " "Test-Site Picker Robot #1 Vacuum Check On Error."
//204110 0 A " "Test-Site Picker Robot #2 Vacuum Check Off Error."
//204111 0 A " "Test-Site Picker Robot #2 Vacuum Check On Error."
//204120 0 A " "Test-Site Picker Robot #3 Vacuum Check Off Error."
//204121 0 A " "Test-Site Picker Robot #3 Vacuum Check On Error."
//204130 0 A " "Test-Site Picker Robot #4 Vacuum Check Off Error."
//204131 0 A " "Test-Site Picker Robot #4 Vacuum Check On Error."
CString GetJamCode_ModuleExist_Chk( int nPicker, int iOn )
{
	CString strJamCode;
	strJamCode.Format( "2041%d%d", nPicker, iOn );
	return strJamCode;
}