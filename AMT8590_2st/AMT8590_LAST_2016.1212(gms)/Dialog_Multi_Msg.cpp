// Dialog_Multi_Msg.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Multi_Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Multi_Msg dialog


CDialog_Multi_Msg::CDialog_Multi_Msg(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Multi_Msg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Multi_Msg)
	//}}AFX_DATA_INIT
	m_caption_main = "User Message Dialog Box";
}


void CDialog_Multi_Msg::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Multi_Msg)
	DDX_Control(pDX, IDC_MSG_M_MESSAGE, m_msg_m_message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Multi_Msg, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Multi_Msg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Multi_Msg message ICTs

BOOL CDialog_Multi_Msg::OnInitDialog() 
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
// 	mp_m_msg_font = NULL;
// 	mp_m_msg_font = new CFont;
// 	mp_m_msg_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************
	
	OnMMsg_Button_Set(); // ��ȭ ���� Į�� ��ư ���� �Լ�
	OnMMsg_Lable_Set();  // Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Multi_Msg::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_m_msg_font;
// 	mp_m_msg_font = NULL;
	// **************************************************************************

	delete mp_m_msg_ok;  // OK ��ư�� ������ ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();
}

void CDialog_Multi_Msg::OnMMsg_Lable_Set()
{
	m_msg_m_message.SetAlignment(CNewLabel::HORZ_CENTER | CNewLabel::VERT_CENTER);
	m_msg_m_message.SetTextColor(RGB(0, 0, 0));
	m_msg_m_message.SetBkColor(RGB(181, 182, 140));
	m_msg_m_message.SetFontBold(TRUE);
	m_msg_m_message.SetFontName("MS Sans Serif");
	m_msg_m_message.SetFontSize(20);

	m_msg_m_message.SetText(_T(st_msg.str_fallacy_msg));
}

void CDialog_Multi_Msg::OnMMsg_Button_Set()
{
	mp_m_msg_ok = CreateOkButton(IDOK, this);
}
