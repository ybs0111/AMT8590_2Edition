// Dialog_Select.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Select.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Select dialog


CDialog_Select::CDialog_Select(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Select::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Select)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_caption_main = "User Select Dialog Box"; 
//	m_is_shape_3d = YES;
}


void CDialog_Select::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Select)
	DDX_Control(pDX, IDC_SELECT_MESSAGE, m_select_message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Select, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Select)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDEXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Select message ICTs

BOOL CDialog_Select::OnInitDialog() 
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
// 	mp_select_font = NULL;
// 	mp_select_font = new CFont;
// 	mp_select_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************

	OnSelect_Button_Set();	// ��ȭ ���� Į�� ��ư ���� �Լ�
	OnSelect_Lable_Set();	// Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Select::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_select_font;
// 	mp_select_font = NULL;
	// **************************************************************************

	delete mp_select_exit;	// OK ��ư�� ������ ���� ���� 
	delete mp_select_yes;	// OK ��ư�� ������ ���� ���� 
	delete mp_select_no;	// Cancel ��ư�� ������ ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();	
}

void CDialog_Select::OnSelect_Lable_Set()
{
	m_select_message.SetFont(Func.mp_select_font);
	m_select_message.SetWindowText(_T(st_msg.mstr_confirm_msg));
	m_select_message.SetCenterText();
	m_select_message.SetColor(RGB(0,0,255));
	m_select_message.SetGradientColor(RGB(0,0,0));
	m_select_message.SetTextColor(RGB(255,255,255));
}

void CDialog_Select::OnSelect_Button_Set()
{
	mp_select_yes = CreateOkButton(IDOK, this);
	mp_select_no = CreateCancelButton(IDCANCEL, this);
	mp_select_exit = CreateCancelButton(IDEXIT, this);

	mp_select_exit->ShowWindow(SW_HIDE);
}

void CDialog_Select::OnExit() 
{
	StandardDialog::EndDialog(5);
}

BOOL CDialog_Select::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			StandardDialog::EndDialog(5);
		}
	}

	return StandardDialog::PreTranslateMessage(pMsg);
}
