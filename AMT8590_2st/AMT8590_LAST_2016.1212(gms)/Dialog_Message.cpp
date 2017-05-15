// Dialog_Message.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Message dialog

CDialog_Message::CDialog_Message(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Message::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Message)
	//}}AFX_DATA_INIT
	m_caption_main = "User Message Dialog Box";
//	m_is_shape_3d = YES;
}

void CDialog_Message::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Message)
	DDX_Control(pDX, IDC_MSG_MESSAGE, m_msg_message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialog_Message, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Message)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Message message ICTs

BOOL CDialog_Message::OnInitDialog() 
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
// 	mp_msg_font = NULL;
// 	mp_msg_font = new CFont;
// 	mp_msg_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************
	
	OnMsg_Button_Set(); // ��ȭ ���� Į�� ��ư ���� �Լ�
	OnMsg_Lable_Set();  // Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Message::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_msg_font;
// 	mp_msg_font = NULL;
	// **************************************************************************

	delete mp_msg_ok;  // OK ��ư�� ������ ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();	
}

void CDialog_Message::OnMsg_Button_Set()
{
	mp_msg_ok = CreateOkButton(IDOK, this);
}

void CDialog_Message::OnMsg_Lable_Set()
{
	m_msg_message.SetFont(Func.mp_msg_font);
	m_msg_message.SetWindowText(_T(st_msg.str_fallacy_msg));
	m_msg_message.SetCenterText();
	m_msg_message.SetColor(RGB(0,0,255));
	m_msg_message.SetGradientColor(RGB(0,0,0));
	m_msg_message.SetTextColor(RGB(255,255,255));
}
