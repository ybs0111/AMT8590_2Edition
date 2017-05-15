// Screen_Lock.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Screen_Lock.h"
#include "ComizoaPublic.h"

// ******************************************************************************
// ��ȭ ���� Ŭ���� �߰�                                                         
// ******************************************************************************
#include "Dialog_Pass_Check.h"
// ******************************************************************************

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreen_Lock

IMPLEMENT_DYNCREATE(CScreen_Lock, CFormView)

CScreen_Lock::CScreen_Lock()
	: CFormView(CScreen_Lock::IDD)
{
	//{{AFX_DATA_INIT(CScreen_Lock)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScreen_Lock::~CScreen_Lock()
{
}

void CScreen_Lock::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreen_Lock)
	DDX_Control(pDX, IDC_MSG_LOCK, m_msg_lock);
	DDX_Control(pDX, IDC_GIF_LOCK, m_gif_lock);
	DDX_Control(pDX, IDC_BTN_UNLOCK, m_btn_unlock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreen_Lock, CFormView)
	//{{AFX_MSG_MAP(CScreen_Lock)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_UNLOCK, OnBtnUnlock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreen_Lock diagnostics

#ifdef _DEBUG
void CScreen_Lock::AssertValid() const
{
	CFormView::AssertValid();
}

void CScreen_Lock::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreen_Lock message handlers

void CScreen_Lock::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// **************************************************************************
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�                                             
	// **************************************************************************
// 	mp_lock_font = NULL;
// 	mp_lock_font = new CFont;
// 	mp_lock_font->CreateFont(42,0,0,0,0,0,0,0,0,0,0,DEFAULT_QUALITY,0,"Arial Black Italic");
	// **************************************************************************
	
	COMI.mn_run_status = CTL_dLOCK;
	st_handler.mn_system_lock = TRUE;	// �ý��� ��� ���� ���� 
	
	OnLock_Label_Set();					// Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
	OnLock_Picture_Set();				// GIF �׸� ���� �ε� �Լ�
}

void CScreen_Lock::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_lock_font;
// 	mp_lock_font = NULL;
	// **************************************************************************
	
	COMI.mn_run_status = CTL_dSTOP;

	CFormView::OnDestroy();
}

void CScreen_Lock::OnBtnUnlock() 
{
	int nResponse;								// ��ȭ ���ڿ� ���� ���� �� ���� ����
	
	CDialog_Pass_Check pass_chk_dlg ;			// ��ȣ �˻� ��ȭ ���� Ŭ���� ���� ���� 
	
	st_handler.mstr_pass_level = _T("SystemUnlock");		// ��ȣ ���� ���� ���� 
	
	nResponse = pass_chk_dlg.DoModal();
	
	if (nResponse == IDOK)
	{
		st_handler.mn_system_lock = FALSE;	// �ý��� ��� ���� ����

		:: WritePrivateProfileString("Password", "SysLockStatus", LPCTSTR("NO"), st_path.mstr_basic);
		
		if (st_handler.cwnd_list != NULL)
		{
//			st_msg.mstr_normal_msg = "System Unlocking.";
			sprintf(st_msg.c_normal_msg, "System Unlocking.");
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}
		
		::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 1, 1);  // ���� ���������� �޽��� �����Ͽ� ���� ȭ������ ��ȯ 
	}
	else if (nResponse == IDCANCEL)
	{
	}
}

void CScreen_Lock::OnLock_Label_Set()
{
	m_msg_lock.SetFont(Func.mp_lock_font);
	m_msg_lock.SetWindowText(_T("System Lock Mode! Impossible of operation!"));
	m_msg_lock.SetCenterText();
	m_msg_lock.SetColor(RGB(255,0,0));
	m_msg_lock.SetGradientColor(RGB(0,0,0));
	m_msg_lock.SetTextColor(RGB(255,255,255));
}

void CScreen_Lock::OnLock_Picture_Set()
{
	if (m_gif_lock.Load(MAKEINTRESOURCE(IDR_GIF_LOCK),_T("GIF")))
		m_gif_lock.Draw();
}
