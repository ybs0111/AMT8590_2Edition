// Dialog_Exit.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Exit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Exit dialog


CDialog_Exit::CDialog_Exit(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Exit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Exit)
	//}}AFX_DATA_INIT
	m_caption_main = "Program Exit Dialog Box";
//	m_is_shape_3d = YES;
}


void CDialog_Exit::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Exit)
	DDX_Control(pDX, IDC_MSG_EXIT, m_msg_exit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Exit, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Exit)
	ON_BN_CLICKED(IDSAVEOK, OnSaveok)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Exit message ICTs

BOOL CDialog_Exit::OnInitDialog() 
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
// 	mp_exit_font = NULL;
// 	mp_exit_font = new CFont;
// 	mp_exit_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************

	OnExit_Button_Set();	// ��ȭ ���� Į�� ��ư ���� �Լ�
	OnExit_Lable_Set();		// Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Exit::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�
	// **************************************************************************
// 	delete mp_exit_font;
// 	mp_exit_font = NULL;
	// **************************************************************************

	delete mp_btn_ok;		// OK ��ư�� ���� ���� ���� 
	delete mp_btn_cancel;	// Cancel ��ư�� ���� ���� ���� 
	delete mp_btn_saveok;	// Save & OK ��ư�� ���� ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();
}

void CDialog_Exit::OnSaveok() 
{
	StandardDialog::EndDialog(5);	
}

void CDialog_Exit::OnExit_Button_Set()
{
	mp_btn_ok =		CreateOkButton(IDOK, this);
	mp_btn_cancel = CreateCancelButton(IDCANCEL, this);
	mp_btn_saveok = CreateSaveOkButton(IDSAVEOK, this);
}

void CDialog_Exit::OnExit_Lable_Set()
{
	m_msg_exit.SetFont(Func.mp_exit_font);
	m_msg_exit.SetWindowText(_T("AMT8590 SSD PACKING HANDLER Program Exit"));
	m_msg_exit.SetCenterText();
	m_msg_exit.SetColor(RGB(0,0,0));
	m_msg_exit.SetGradientColor(RGB(0,0,255));
	m_msg_exit.SetTextColor(RGB(255,255,255));
}
