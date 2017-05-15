// Dialog_Infor.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Infor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Infor dialog

CDialog_Infor::CDialog_Infor(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Infor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Infor)
	//}}AFX_DATA_INIT
//	m_caption_main = "User Select Dialog Box"; 
////	m_is_shape_3d = YES;
}

void CDialog_Infor::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Infor)
	DDX_Control(pDX, IDC_INFO_MESSAGE, m_info_message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialog_Infor, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Infor)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Infor message ICTs

BOOL CDialog_Infor::OnInitDialog() 
{
	StandardDialog::OnInitDialog();

	// Start Switch�� ������ ���´�.
	if (st_handler.mn_switch_lock == FALSE)
	{
		st_handler.mn_switch_lock = TRUE;
		mn_dialog = 1;
	}
	else	mn_dialog = 0;
	
	// **************************************************************************
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�                                             
	// **************************************************************************
// 	mp_info_font = NULL;
// 	mp_info_font = new CFont;
// 	mp_info_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************

	OnInfo_Button_Set();	// ��ȭ ���� Į�� ��ư ���� �Լ�
	OnInfo_Lable_Set();		// Į�� �ؽ�Ʈ �ڽ� ���� �Լ�

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Infor::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_info_font;
// 	mp_info_font = NULL;
	// **************************************************************************

	delete mp_info_ok;      // OK ��ư�� ������ ���� ���� 
	delete mp_info_cancel;  // Cancel ��ư�� ������ ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}
	
	CDialog::OnDestroy();
}

void CDialog_Infor::OnInfo_Button_Set()
{
	mp_info_ok = CreateOkButton(IDOK, this);
	mp_info_cancel = CreateCancelButton(IDCANCEL, this);
}

void CDialog_Infor::OnInfo_Lable_Set()
{
	m_info_message.SetFont(Func.mp_info_font);
	m_info_message.SetWindowText(_T(st_msg.mstr_confirm_msg));
	m_info_message.SetCenterText();
	m_info_message.SetColor(RGB(0,0,255));
	m_info_message.SetGradientColor(RGB(0,0,0));
	m_info_message.SetTextColor(RGB(255,255,255));
}