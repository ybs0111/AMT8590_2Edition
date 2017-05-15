// Dialog_List.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_List.h"
#include <atlconv.h>  // TCP/IP ���� Ŭ���� �߰�

#include "Public_Function.h"
#include "SrcBase\ACriticalSection.h"

// ******************************************************************************
// ��Ʈ��ũ ��� ��� ����                                                       
// ******************************************************************************
const int SOCK_TCP = 0;
const int SOCK_UDP = 1;
// ******************************************************************************

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMutex mutexlog;

/////////////////////////////////////////////////////////////////////////////
// CDialog_List dialog


CDialog_List::CDialog_List()
{
	//{{AFX_DATA_INIT(CDialog_List)
	//}}AFX_DATA_INIT
	int i;

	CString mstr_temp;			// ������ ���� �ӽ� ���� ���� 
	char chr_data[50];
	mstr_normal_old_msg = "";
	mstr_abnormal_old_msg = "";
	
	for (i = 0; i < MAX_SERVER_NUM; i++)
	{
		mp_server[i] = NULL;
		mp_client[i] = NULL;
	}

	ml_listmsg_write_time = 10000;

	st_path.mstr_basic =			_T("c:\\AMT8590\\Setting\\BasicTerm.TXT");		// ȯ�� ���� ���� ���� ���Ͽ� ���� ���� ���� 
	
	:: GetPrivateProfileString("ADMIN", "FMachine_Server_Port", "9999", chr_data, 10, st_path.mstr_basic);
	mstr_temp = chr_data;
	mstr_temp.MakeUpper();     // ���ڿ� �빮�ڷ� ����
	mstr_temp.TrimLeft(' ');   // ���� ���ڿ� ���� ����              
	mstr_temp.TrimRight(' ');  // ���� ���ڿ� ���� ����
//	Run_Network.m_Net_FMachine.SetPort( atoi((LPCSTR)mstr_temp) );

	mn_port[0] = atoi(mstr_temp);
	
	for (i = 0; i < 10; i++)
	{
		mn_header[i] = 0;
		mstr_rpy_msg[i] = "";
		mstr_body[i] = "";

		mn_header_C[i] = 0;
		mstr_body_C[i] = "";
	}
	
}


void CDialog_List::DoDataExchange(CDataExchange* pDX)
{
	CInitDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_List)
	DDX_Control(pDX, IDC_MSG_EQP_ID, m_msg_eqp_id);
	DDX_Control(pDX, IDC_MSG_DEVICE_NAME, m_msg_device_name);
	DDX_Control(pDX, IDC_LABEL_EQP_ID, m_label_eqp_id);
	DDX_Control(pDX, IDC_LABEL_DEVICE_NAME, m_label_device_name);
	DDX_Control(pDX, IDC_LIST_DATA, m_list_data);
	DDX_Control(pDX, IDC_LIST_CLOCK, m_list_clock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_List, CInitDialogBar)
	//{{AFX_MSG_MAP(CDialog_List)
	ON_WM_DESTROY()
	ON_LBN_DBLCLK(IDC_LIST_DATA, OnDblclkListData)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_LIST_DATA, OnListDataUpdate)  // ���� �޽��� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� �޽��� ����  
	ON_MESSAGE(WM_SOCKET_ACCEPT, OnSocketAccept)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_List message handlers

BOOL CDialog_List::OnInitDialogBar() 
{
	CInitDialogBar::OnInitDialogBar();
	
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�
// 	mp_list_font = NULL;
// 	mp_list_font = new CFont;
// 	mp_list_font->CreateFont(14,6,0,0,900,0,0,0,0,0,0,PROOF_QUALITY,0,"MS Sans Serif");
	
	OnList_Digital_Clock_Set();				// �ð� ����.
	OnList_Check_Tab_Stops(TRUE);			// Tab ��� ���� ���� �Լ�
	OnList_Lable_Set();						// ��Ÿ ������ ���� Label ���� �Լ�

//	g_Net.OnStartServer();
//	g_Net.OnInitClientAddress();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_List::OnDestroy() 
{
	int i;

	// ������ ��Ʈ ���� �����Ѵ�
// 	delete mp_list_font;
// 	mp_list_font = NULL;

	for (i = 0; i < MAX_SERVER_NUM; i++)
	{
		if (mp_server[i] != NULL)
		{
			delete mp_server[i];
			mp_server[i] = NULL;
		}
	}

	CInitDialogBar::OnDestroy();
}

void CDialog_List::OnList_Digital_Clock_Set()
{
	m_list_clock.Start(IDB_CLOCKST_PANE, IDB_CLOCKST_BIG, IDB_CLOCKST_SMALL);
}

void CDialog_List::OnList_Lable_Set()
{
	m_label_eqp_id.SetText("EQP ID");
	m_label_eqp_id.SetTextColor(RGB(0, 0, 0));
	m_label_eqp_id.SetBkColor(RGB(181, 182, 140));
	m_label_eqp_id.SetFontBold(TRUE);
	m_label_eqp_id.SetFontName("MS Sans Serif");
	m_label_eqp_id.SetFontSize(11);
	
	m_msg_eqp_id.SetFont(Func.mp_list_font);
	m_msg_eqp_id.SetCenterText();
	m_msg_eqp_id.SetColor(RGB(0,0,0));
	m_msg_eqp_id.SetGradientColor(RGB(0,0,0));
	m_msg_eqp_id.SetTextColor(RGB(255,255,255));
	
	m_label_device_name.SetText("DEVICE NAME");
	m_label_device_name.SetTextColor(RGB(0, 0, 0));
	m_label_device_name.SetBkColor(RGB(181, 182, 140));
	m_label_device_name.SetFontBold(TRUE);
	m_label_device_name.SetFontName("MS Sans Serif");
	m_label_device_name.SetFontSize(11);
	
	m_msg_device_name.SetFont(Func.mp_list_font);
	m_msg_device_name.SetCenterText();
	m_msg_device_name.SetColor(RGB(0,0,0));
	m_msg_device_name.SetGradientColor(RGB(0,0,0));
	m_msg_device_name.SetTextColor(RGB(255,255,255));
}

void CDialog_List::OnList_Check_Tab_Stops(int mb_use_tab_stops)
{
	DWORD dwRemove = (mb_use_tab_stops ? 0 : LBS_USETABSTOPS);
	DWORD dwAdd = (mb_use_tab_stops ? LBS_USETABSTOPS : 0);
	
	m_list_data.ModifyStyle(dwRemove, dwAdd);
	m_list_data.RedrawWindow();
}

LRESULT CDialog_List:: OnListDataUpdate(WPARAM wParam,LPARAM lParam)
{
	//2013,1021
//	CSingleLock sing(&mutexlog);
//	sing.Lock();

	int n_mode = wParam;					// �ø��� ��Ʈ ���� �Լ� ������ ���� 
	
	OnList_Message_Clear();					// ����Ʈ �ڽ� ��Ʈ�ѿ� �߰��� ��� ������ ���� �Լ�
	
	switch(lParam)
	{
	case RECEIVE_MSG:						// ���� �޽��� 
		OnList_Receive_Msg_Display(n_mode);	// ����Ʈ �ڽ� ��Ʈ�ѿ� ���� �޽��� �߰� �Լ�
		break;
		
	case SEND_MSG:							// �۽� �޼���
		OnList_Send_Msg_Display(n_mode);	// ����Ʈ �ڽ� ��Ʈ�ѿ� �۽� �޽��� �߰� �Լ�
		break;
		
	case NORMAL_MSG:						// ���� ����
		OnList_Normal_Msg_Display();		// ����Ʈ �ڽ� ��Ʈ�ѿ� ���� �޽��� �߰� �Լ�
		break;
		
	case ABNORMAL_MSG:						// ������ ����
		OnList_Abnormal_Msg_Display();		// ����Ʈ �ڽ� ��Ʈ�ѿ� ���� �޽��� �߰� �Լ�
		break;		
		
	case MACHINE_INFO:						// ��� ���� ����
		OnList_Machine_Data_Set();
		break;
		
	case DEVICE_INFO:						// ����̽��� ���� ����
		OnList_Machine_Data_Set();
		break;
		
	case EQP_MSG:						// ���� ����
		OnList_Eqp_Msg_Display();		// ����Ʈ �ڽ� ��Ʈ�ѿ� ���� �޽��� �߰� �Լ�
		break;
	}
	
//	sing.Unlock();
	return 0 ;
}

void CDialog_List::OnList_Message_Clear()
{
	int nIndex = m_list_data.GetCount();
	
	if (nIndex < 500) return;
	
	m_list_data.ResetContent();   // ����Ʈ �ڽ� ��Ʈ�ѿ� �߰��� ��� ������ ���� 
}


void CDialog_List::OnList_Normal_Msg_Display()
{
	int mn_index;	
	std::string mstr_msg =  "";
	CString sTime;
	
	SYSTEMTIME csTime;
	
	GetLocalTime(&csTime);
	
	csTime.wHour;
	csTime.wMinute;
	csTime.wSecond;
	csTime.wMilliseconds;
	
	sTime.Format("[%02d:%02d:%02d.%03d] ", csTime.wHour, csTime.wMinute, csTime.wSecond, csTime.wMilliseconds);

	//  ���� �ð� �̻��϶��� �޽��� ���� Ȯ���Ͽ� ���Ϸ� ���� 
	if (mstr_normal_old_msg == st_msg.c_normal_msg)
	{
		// ���� �޼����� ������ ���� ó�� 
		ml_list_msgterm_time_normal[1] = GetCurrentTime();
		ml_list_msgterm_time_normal[2] = ml_list_msgterm_time_normal[1] - ml_list_msgterm_time_normal[0];
		
		if (ml_list_msgterm_time_normal[2] > ml_listmsg_write_time) 
		{
			//OK ���Ϸ� ���� ���� 
		}
		else
		{
			ml_list_msgterm_time_normal[0] = GetCurrentTime();
			return;
		}
	}
	
	if (st_msg.c_normal_msg != _T(""))
	{
		ml_list_msgterm_time_normal[0] = GetCurrentTime();
		
		mstr_normal_old_msg =	st_msg.c_normal_msg;
		mstr_msg = sTime + st_msg.c_normal_msg;
	}
	else
	{
		mstr_msg = "Display Message is Empty";
	}
	
	mn_index = m_list_data.AddString(mstr_msg.c_str(), RGB(0, 0, 255));  // ���� �Էµ� ���� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� 
	m_list_data.SetCurSel(mn_index);
	
	Func.On_LogFile_Add(99, st_msg.c_normal_msg);
}

void CDialog_List::OnList_Abnormal_Msg_Display()
{
	int mn_index;
	std::string mstr_msg =  "";
	CString sTime;

	SYSTEMTIME csTime;

	GetLocalTime(&csTime);

	csTime.wHour;
	csTime.wMinute;
	csTime.wSecond;
	csTime.wMilliseconds;

	sTime.Format("[%02d:%02d:%02d.%03d] ", csTime.wHour, csTime.wMinute, csTime.wSecond, csTime.wMilliseconds);
	
	// ���� �ð� �̻��϶��� �޽��� ���� Ȯ���Ͽ� ���Ϸ� ���� 
	if (mstr_abnormal_old_msg == st_msg.c_abnormal_msg)
	{
		// ���� �޼����� ������ ���� ó�� 
		ml_list_msgterm_time_abnormal[1] = GetCurrentTime();
		ml_list_msgterm_time_abnormal[2] = ml_list_msgterm_time_abnormal[1] - ml_list_msgterm_time_abnormal[0];
		
		if (ml_list_msgterm_time_abnormal[2] > ml_listmsg_write_time) 
		{
			//OK ���Ϸ� ���� ���� 
		}
		else
		{
			ml_list_msgterm_time_abnormal[0] = GetCurrentTime();
			return;
		}
	}
	
	if (st_msg.c_abnormal_msg != _T(""))
	{
		ml_list_msgterm_time_abnormal[0] = GetCurrentTime();
		
		mstr_abnormal_old_msg =	st_msg.c_abnormal_msg;
		mstr_msg   =	sTime + st_msg.c_abnormal_msg;
	}
	else
	{
		mstr_msg = "Display Message is Empty";
	}
	
	mn_index = m_list_data.AddString(mstr_msg.c_str(), RGB(255, 0, 0));  // ���� �Էµ� ���� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� 
	m_list_data.SetCurSel(mn_index);
	
	Func.On_LogFile_Add(99, st_msg.c_abnormal_msg);
}

void CDialog_List::OnList_Send_Msg_Display(int n_mode)
{
	int mn_index;				// ����Ʈ �ڽ��� �߰��� ������ ��ġ ���� ���� 
	CString s;					// �ý��� �ð� ���� �ӽ� ���� ���� 
	CString mstr_name;			// �ø��� ��Ʈ �� �ð� ���� ���� ���� 
	CString mstr_msg = "\t";	// ����Ʈ �ڽ��� �߰��� ���� ���� ���� 
	CTime mp_cur_time;			// ���� �ð� ���� ���� ���� 

	CString str_send;

	/* ************************************************************************** */
	/* �ø��� ��Ʈ �� �޽��� ������ ���� ���� ���� �κ�                           */
	/* ************************************************************************** */
	str_send.Format("SND     Com %02d   : ", n_mode);

	mp_cur_time = CTime::GetCurrentTime() ;  // ���� �ð� ���� ��´�. 
	s = mp_cur_time.Format("%p %H %M %S") ;  // �ð� ���� ���� ���� (����/���� , �ð� , �� , �� )

	mstr_name = str_send + s;  // �߰��� Ÿ��Ʋ ���� ���� 

	mn_index = m_list_data.AddString(mstr_name, RGB(0, 0, 255));  // ����Ʈ �ڽ� ��Ʈ�ѿ� Ÿ��Ʋ ���� �߰� 
	m_list_data.SetCurSel(mn_index);

	st_msg.mstr_send = st_serial.mcomm_snd[n_mode-1];
	if (st_msg.mstr_send != _T(""))  mstr_msg += st_msg.mstr_send;
	else   mstr_msg += "Display Message is Empty";

	Func.On_LogFile_Add(1, mstr_msg);
	Func.On_LogFile_Add(99, mstr_msg);

	mn_index = m_list_data.AddString(mstr_msg, RGB(50, 100, 150));  // ���� �Էµ� ���� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� 
	m_list_data.SetCurSel(mn_index);
}

void CDialog_List::OnList_Receive_Msg_Display(int n_mode)
{
	int mn_index;		// ����Ʈ �ڽ��� �߰��� ������ ��ġ ���� ���� 
	CString s;			// �ý��� �ð� ���� �ӽ� ���� ���� 
	CString mstr_name;  // �ø��� ��Ʈ �� �ð� ���� ���� ���� 
	CString mstr_msg = "\t";  // ����Ʈ �ڽ��� �߰��� ���� ���� ���� 
	CTime mp_cur_time;  // ���� �ð� ���� ���� ���� 

	CString str_rcv;
	
	/* ************************************************************************** */
	/* �ø��� ��Ʈ �� �޽��� ������ ���� ���� ���� �κ�                           */
	/* ************************************************************************** */
	str_rcv.Format("RCV     Com %02d   : ", n_mode);
	
	mp_cur_time = CTime::GetCurrentTime() ;  // ���� �ð� ���� ��´�. 
	s = mp_cur_time.Format("%p %H %M %S") ;  // �ð� ���� ���� ���� (����/���� , �ð� , �� , �� )
	
	mstr_name = str_rcv + s;  // �߰��� Ÿ��Ʋ ���� ���� 
	
	mn_index = m_list_data.AddString(mstr_name, RGB(255, 0, 255));  // ����Ʈ �ڽ� ��Ʈ�ѿ� Ÿ��Ʋ ���� �߰� 
	m_list_data.SetCurSel(mn_index);
	
	if (st_msg.mstr_recive != _T(""))  mstr_msg += st_msg.mstr_recive;
	else   mstr_msg += "Display Message is Empty";

	Func.On_LogFile_Add(1, mstr_msg);
	Func.On_LogFile_Add(99, mstr_msg);

	mn_index = m_list_data.AddString(mstr_msg, RGB(50, 100, 150));  // ���� �Էµ� ���� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� 
	m_list_data.SetCurSel(mn_index);
}

void CDialog_List::OnList_Eqp_Msg_Display()
{
	std::string mstr_msg =  "";
	CString sTime;
	
	SYSTEMTIME csTime;
	
	GetLocalTime(&csTime);
	
	csTime.wHour;
	csTime.wMinute;
	csTime.wSecond;
	csTime.wMilliseconds;
	
	sTime.Format("%02d:%02d:%02d.%03d ", csTime.wHour, csTime.wMinute, csTime.wSecond, csTime.wMilliseconds);
	
	//  ���� �ð� �̻��϶��� �޽��� ���� Ȯ���Ͽ� ���Ϸ� ���� 
	if (mstr_eqp_old_msg == st_msg.c_eqp_msg)
	{
		// ���� �޼����� ������ ���� ó�� 
		ml_list_msgeqp_time_normal[1] = GetCurrentTime();
		ml_list_msgeqp_time_normal[2] = ml_list_msgeqp_time_normal[1] - ml_list_msgeqp_time_normal[0];
		
		if (ml_list_msgeqp_time_normal[2] > ml_listmsg_write_time) 
		{
			//OK ���Ϸ� ���� ���� 
		}
		else
		{
			ml_list_msgeqp_time_normal[0] = GetCurrentTime();
			return;
		}
	}
	
	if (st_msg.c_eqp_msg != _T(""))
	{
		ml_list_msgeqp_time_normal[0] = GetCurrentTime();
		
		mstr_eqp_old_msg =	st_msg.c_eqp_msg;
		mstr_msg = sTime + st_msg.c_eqp_msg;
	}
	else
	{
		mstr_msg = "Display Message is Empty";
	}
	
// 	mn_index = m_list_data.AddString(mstr_msg.c_str(), RGB(0, 0, 255));  // ���� �Էµ� ���� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰� 
// 	m_list_data.SetCurSel(mn_index);
	
	Func.On_LogFile_Add(LOG_ERROR, st_msg.c_eqp_msg);
}

//////////////////////////// send //////////////////////////////////////////////////////

void CDialog_List::OnList_Machine_Data_Set()
{
	m_msg_eqp_id.SetWindowText(_T(st_lamp.mstr_equip_id));		// ��� ȣ�� ���� ��� 
	m_msg_device_name.SetWindowText(_T(st_basic.mstr_device_name));		// DEVICE ���� ���
}

void CDialog_List::OnDblclkListData() 
{
	CString mstr_cur_year, mstr_cur_month, mstr_cur_day, str_display_time; // ���� ��, ��, �� ���� ���������� ��ȯ�Ͽ� ������ ���� 
	int mn_cur_year, mn_cur_month, mn_cur_day; // ���� ��, ��, �� ���� ���� ���� 
	CString mstr_file_name;		// ���������� ������ ���� �̸� ���� ���� 
	CString mstr_create_file;	// �˶� ���� ������ ���Ͽ� ���� [����]+[���ϸ�]+[Ȯ����] ���� ���� 
	COleDateTime time_cur;		// �˻��� �ð� ���� ���� ���� 

	// **************************************************************************
	// ���� �̸����� ����� ��¥ ������ ��´�                                   
	// **************************************************************************
	time_cur = COleDateTime::GetCurrentTime();  // ���� �ð� ������ ��´�. 
	
	mn_cur_year = time_cur.GetYear();  
	mn_cur_month = time_cur.GetMonth();  
    mn_cur_day = time_cur.GetDay();  
	
	// **************************************************************************
	// ��¥ ������ ���������� ��ȯ�Ͽ� ������ �����Ѵ�                           
	// **************************************************************************
	mstr_cur_year.Format("%04d", mn_cur_year);
	mstr_cur_month.Format("%02d", mn_cur_month);
	mstr_cur_day.Format("%02d", mn_cur_day);
	
	mstr_file_name = "TOT" + mstr_cur_year;
	mstr_file_name += mstr_cur_month; 
	mstr_file_name += mstr_cur_day; 
	mstr_create_file = st_path.mstr_total + mstr_file_name;
	mstr_create_file += ".TXT";

	::ShellExecute(NULL, NULL, "NotePAD.exe", mstr_create_file, NULL, SW_SHOWNORMAL);// TODO: Add your control notification handler code here
}

LRESULT CDialog_List::OnSocketAccept( WPARAM wParam,LPARAM lParam )
{
//	g_Net.ClientAccept( wParam );
	return 0;
}
