// Dialog_Keyboard.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Keyboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Keyboard dialog
CDialog_Keyboard Keyboard;

CDialog_Keyboard::CDialog_Keyboard(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Keyboard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Keyboard)
	//}}AFX_DATA_INIT
	m_caption_main = "String Input Dialog Box";
//	m_is_shape_3d = YES;
}


void CDialog_Keyboard::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Keyboard)
	DDX_Control(pDX, IDC_MSG_BOARD, m_msg_board);
	DDX_Control(pDX, IDC_GROUP_BOARD, m_group_board);
	DDX_Control(pDX, IDC_BTN_BOARD_SHARP, m_btn_board_sharp);
	DDX_Control(pDX, IDC_BTN_BOARD_RBRACE_S, m_btn_board_rbrace_s);
	DDX_Control(pDX, IDC_BTN_BOARD_RBRACE_B, m_btn_board_rbrace_b);
	DDX_Control(pDX, IDC_BTN_BOARD_LINE, m_btn_board_line);
	DDX_Control(pDX, IDC_BTN_BOARD_LBRACE_S, m_btn_board_lbrace_s);
	DDX_Control(pDX, IDC_BTN_BOARD_LBRACE_B, m_btn_board_lbrace_b);
	DDX_Control(pDX, IDC_BTN_BOARD_DOT, m_btn_board_dot);
	DDX_Control(pDX, IDC_BTN_BOARD_DOLLAR, m_btn_board_dollar);
	DDX_Control(pDX, IDC_BTN_BOARD_DIV, m_btn_board_div);
	DDX_Control(pDX, IDC_BTN_BOARD_DEL, m_btn_board_del);
	DDX_Control(pDX, IDC_BTN_BOARD_BACK, m_btn_board_back);
	DDX_Control(pDX, IDC_BTN_BOARD_ADD, m_btn_board_add);
	DDX_Control(pDX, IDC_BTN_BOARD_Z, m_btn_board_z);
	DDX_Control(pDX, IDC_BTN_BOARD_Y, m_btn_board_y);
	DDX_Control(pDX, IDC_BTN_BOARD_X, m_btn_board_x);
	DDX_Control(pDX, IDC_BTN_BOARD_W, m_btn_board_w);
	DDX_Control(pDX, IDC_BTN_BOARD_V, m_btn_board_v);
	DDX_Control(pDX, IDC_BTN_BOARD_U, m_btn_board_u);
	DDX_Control(pDX, IDC_BTN_BOARD_T, m_btn_board_t);
	DDX_Control(pDX, IDC_BTN_BOARD_S, m_btn_board_s);
	DDX_Control(pDX, IDC_BTN_BOARD_R, m_btn_board_r);
	DDX_Control(pDX, IDC_BTN_BOARD_Q, m_btn_board_q);
	DDX_Control(pDX, IDC_BTN_BOARD_P, m_btn_board_p);
	DDX_Control(pDX, IDC_BTN_BOARD_O, m_btn_board_o);
	DDX_Control(pDX, IDC_BTN_BOARD_N, m_btn_board_n);
	DDX_Control(pDX, IDC_BTN_BOARD_M, m_btn_board_m);
	DDX_Control(pDX, IDC_BTN_BOARD_L, m_btn_board_l);
	DDX_Control(pDX, IDC_BTN_BOARD_K, m_btn_board_k);
	DDX_Control(pDX, IDC_BTN_BOARD_J, m_btn_board_j);
	DDX_Control(pDX, IDC_BTN_BOARD_I, m_btn_board_i);
	DDX_Control(pDX, IDC_BTN_BOARD_H, m_btn_board_h);
	DDX_Control(pDX, IDC_BTN_BOARD_G, m_btn_board_g);
	DDX_Control(pDX, IDC_BTN_BOARD_F, m_btn_board_f);
	DDX_Control(pDX, IDC_BTN_BOARD_E, m_btn_board_e);
	DDX_Control(pDX, IDC_BTN_BOARD_D, m_btn_board_d);
	DDX_Control(pDX, IDC_BTN_BOARD_C, m_btn_board_c);
	DDX_Control(pDX, IDC_BTN_BOARD_B, m_btn_board_b);
	DDX_Control(pDX, IDC_BTN_BOARD_A, m_btn_board_a);
	DDX_Control(pDX, IDC_BTN_BOARD_9, m_btn_board_9);
	DDX_Control(pDX, IDC_BTN_BOARD_8, m_btn_board_8);
	DDX_Control(pDX, IDC_BTN_BOARD_7, m_btn_board_7);
	DDX_Control(pDX, IDC_BTN_BOARD_6, m_btn_board_6);
	DDX_Control(pDX, IDC_BTN_BOARD_5, m_btn_board_5);
	DDX_Control(pDX, IDC_BTN_BOARD_4, m_btn_board_4);
	DDX_Control(pDX, IDC_BTN_BOARD_3, m_btn_board_3);
	DDX_Control(pDX, IDC_BTN_BOARD_2, m_btn_board_2);
	DDX_Control(pDX, IDC_BTN_BOARD_1, m_btn_board_1);
	DDX_Control(pDX, IDC_BTN_BOARD_0, m_btn_board_0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Keyboard, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Keyboard)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_BOARD_BACK, OnBtnBoardBack)
	ON_BN_CLICKED(IDC_BTN_BOARD_DEL, OnBtnBoardDel)
	ON_BN_CLICKED(IDC_BTN_BOARD_1, OnBtnBoard1)
	ON_BN_CLICKED(IDC_BTN_BOARD_2, OnBtnBoard2)
	ON_BN_CLICKED(IDC_BTN_BOARD_3, OnBtnBoard3)
	ON_BN_CLICKED(IDC_BTN_BOARD_4, OnBtnBoard4)
	ON_BN_CLICKED(IDC_BTN_BOARD_5, OnBtnBoard5)
	ON_BN_CLICKED(IDC_BTN_BOARD_6, OnBtnBoard6)
	ON_BN_CLICKED(IDC_BTN_BOARD_7, OnBtnBoard7)
	ON_BN_CLICKED(IDC_BTN_BOARD_8, OnBtnBoard8)
	ON_BN_CLICKED(IDC_BTN_BOARD_9, OnBtnBoard9)
	ON_BN_CLICKED(IDC_BTN_BOARD_0, OnBtnBoard0)
	ON_BN_CLICKED(IDC_BTN_BOARD_A, OnBtnBoardA)
	ON_BN_CLICKED(IDC_BTN_BOARD_B, OnBtnBoardB)
	ON_BN_CLICKED(IDC_BTN_BOARD_C, OnBtnBoardC)
	ON_BN_CLICKED(IDC_BTN_BOARD_D, OnBtnBoardD)
	ON_BN_CLICKED(IDC_BTN_BOARD_E, OnBtnBoardE)
	ON_BN_CLICKED(IDC_BTN_BOARD_F, OnBtnBoardF)
	ON_BN_CLICKED(IDC_BTN_BOARD_G, OnBtnBoardG)
	ON_BN_CLICKED(IDC_BTN_BOARD_H, OnBtnBoardH)
	ON_BN_CLICKED(IDC_BTN_BOARD_I, OnBtnBoardI)
	ON_BN_CLICKED(IDC_BTN_BOARD_J, OnBtnBoardJ)
	ON_BN_CLICKED(IDC_BTN_BOARD_K, OnBtnBoardK)
	ON_BN_CLICKED(IDC_BTN_BOARD_L, OnBtnBoardL)
	ON_BN_CLICKED(IDC_BTN_BOARD_M, OnBtnBoardM)
	ON_BN_CLICKED(IDC_BTN_BOARD_N, OnBtnBoardN)
	ON_BN_CLICKED(IDC_BTN_BOARD_O, OnBtnBoardO)
	ON_BN_CLICKED(IDC_BTN_BOARD_P, OnBtnBoardP)
	ON_BN_CLICKED(IDC_BTN_BOARD_Q, OnBtnBoardQ)
	ON_BN_CLICKED(IDC_BTN_BOARD_R, OnBtnBoardR)
	ON_BN_CLICKED(IDC_BTN_BOARD_S, OnBtnBoardS)
	ON_BN_CLICKED(IDC_BTN_BOARD_T, OnBtnBoardT)
	ON_BN_CLICKED(IDC_BTN_BOARD_U, OnBtnBoardU)
	ON_BN_CLICKED(IDC_BTN_BOARD_V, OnBtnBoardV)
	ON_BN_CLICKED(IDC_BTN_BOARD_W, OnBtnBoardW)
	ON_BN_CLICKED(IDC_BTN_BOARD_X, OnBtnBoardX)
	ON_BN_CLICKED(IDC_BTN_BOARD_Y, OnBtnBoardY)
	ON_BN_CLICKED(IDC_BTN_BOARD_Z, OnBtnBoardZ)
	ON_BN_CLICKED(IDC_BTN_BOARD_LBRACE_S, OnBtnBoardLbraceS)
	ON_BN_CLICKED(IDC_BTN_BOARD_RBRACE_S, OnBtnBoardRbraceS)
	ON_BN_CLICKED(IDC_BTN_BOARD_DIV, OnBtnBoardDiv)
	ON_BN_CLICKED(IDC_BTN_BOARD_LBRACE_B, OnBtnBoardLbraceB)
	ON_BN_CLICKED(IDC_BTN_BOARD_RBRACE_B, OnBtnBoardRbraceB)
	ON_BN_CLICKED(IDC_BTN_BOARD_DOT, OnBtnBoardDot)
	ON_BN_CLICKED(IDC_BTN_BOARD_ADD, OnBtnBoardAdd)
	ON_BN_CLICKED(IDC_BTN_BOARD_LINE, OnBtnBoardLine)
	ON_BN_CLICKED(IDC_BTN_BOARD_DOLLAR, OnBtnBoardDollar)
	ON_BN_CLICKED(IDC_BTN_BOARD_SHARP, OnBtnBoardSharp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Keyboard message ICTs

BOOL CDialog_Keyboard::OnInitDialog() 
{
	StandardDialog::OnInitDialog();

	// Start Switch�� ������ ���´�.
	if (st_handler.mn_switch_lock == FALSE)
		st_handler.mn_switch_lock = TRUE;
	
	// **************************************************************************
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�                                             
	// **************************************************************************
// 	mp_board_font = NULL;
// 	mp_board_font = new CFont;
// 	mp_board_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************

	OnKeyboard_GroupBox_Set();		// Ű���� ��ȭ ���� Į�� �׷� �ڽ� ���� �Լ�
	OnKeyboard_Lable_Set();			// Ű���� ��ȭ ���� Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
	OnKeyboard_EditBoxSet();		// Ű���� ��ȭ ���� Į�� ����Ʈ �ڽ� ���� �Լ�
	OnKeyboard_Button_Set();		// Ű���� ��ȭ ���� Į�� ��ư ���� �Լ�
	OnKeyboard_Title_data_Set();	// �޽��� ���� Ŭ���� ���� ���� �� Ű���� ȭ�� ��� �Լ�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Keyboard::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_board_font;
// 	mp_board_font = NULL;
	// **************************************************************************

	delete mp_board_ok;		// OK ��ư�� ������ ���� ���� 
	delete mp_board_cancel; // Cancel ��ư�� ������ ���� ���� 

	st_handler.mn_switch_lock = FALSE;

	StandardDialog::OnDestroy();
}

void CDialog_Keyboard::OnKeyboard_GroupBox_Set()
{
	CSxLogFont board_Logo(15,FW_SEMIBOLD,false,"MS Sans Serif");

//	m_group_board.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
	m_group_board.SetBackgroundColor(RGB(206, 206, 206), RGB(255, 255, 204));
	m_group_board.SetFont(board_Logo);
	m_group_board.SetCatptionTextColor(RGB(145,25,0));
	m_group_board.SetFontBold(TRUE);
}

void CDialog_Keyboard::OnKeyboard_Lable_Set()
{
	CString str_msg = "Input : ";

	m_msg_board.SetFont(Func.mp_board_font);

	if (st_msg.mstr_keyboard_msg == "")
	{
		str_msg += "String Data~";
	}
	else
	{
		str_msg += st_msg.mstr_keyboard_msg;
	}
	m_msg_board.SetWindowText(_T(str_msg));
	m_msg_board.SetCenterText();
	m_msg_board.SetColor(RGB(0,0,255));
	m_msg_board.SetGradientColor(RGB(0,0,0));
	m_msg_board.SetTextColor(RGB(255,255,255));
}

void CDialog_Keyboard::OnKeyboard_EditBoxSet()
{
	m_edit_board_data.SubclassDlgItem(IDC_EDIT_BOARD_DATA, this);
	m_edit_board_data.bkColor( RGB(50, 100, 150) );
	m_edit_board_data.textColor( RGB(255, 255,255) );
    m_edit_board_data.setFont(-16, FW_BOLD, DEFAULT_PITCH | FF_DONTCARE, "MS Sans Serif");
}

void CDialog_Keyboard::OnKeyboard_Button_Set()
{
	mp_board_ok = CreateOkButton(IDOK, this);
	mp_board_cancel = CreateCancelButton(IDCANCEL, this);
}

void CDialog_Keyboard::OnKeyboard_Title_data_Set()
{
	mp_title_info = st_msg.mstr_typing_msg;  // ���� ������ ����� Ÿ��Ʋ ���� Ŭ���� ������ ���� 
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
}

void CDialog_Keyboard::OnKeyboard_Title_data_Transfer()
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info) ;

	mp_title_info.TrimLeft(' ');               
	mp_title_info.TrimRight(' ');
}

BOOL CDialog_Keyboard::OnKeyboard_Length_Check(CString strData)
{
	int mn_cnt;

	mn_cnt = strlen(strData);
	
	if (mn_cnt > 22) return FALSE;

	return TRUE;
}

void CDialog_Keyboard::OnBtnBoardBack() 
{
	CString Data;
	int nCnt;

	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	nCnt=strlen(mp_title_info);
	
	if (nCnt == 0) return;
	else 
	{
		Data = mp_title_info;
		mp_title_info=Data.Left(nCnt-1);
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardDel() 
{
	mp_title_info =_T("") ;
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
}

void CDialog_Keyboard::OnOK() 
{
	OnKeyboard_Title_data_Transfer();			// Ű���� �Է� ���� ���� ������ ���� �Լ�

	st_msg.mstr_typing_msg = mp_title_info;	// Ŭ���� ������ ����� Ÿ��Ʋ ���� ���� ������ ���� 

	StandardDialog::OnOK();
}

void CDialog_Keyboard::OnBtnBoard1() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard2() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("2");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard3() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("3");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard4() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("4");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard5() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("5");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard6() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("6");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard7() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("7");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard8() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("8");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard9() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("9");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoard0() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("0");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardA() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("A");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardB() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("B");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardC() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("C");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardD() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("D");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardE() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("E");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardF() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("F");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardG() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("G");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardH() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("H");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardI() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("I");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardJ() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("J");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardK() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("K");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardL() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("L");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardM() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("M");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardN() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("N");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardO() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("O");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardP() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("P");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardQ() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("Q");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardR() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("R");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardS() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("S");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardT() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("T");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardU() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("U");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardV() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("V");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardW() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("W");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardX() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("X");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardY() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("Y");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardZ() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("Z");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardLbraceS() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("(");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardRbraceS() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T(")");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardDiv() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("/");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardLbraceB() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("[");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardRbraceB() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("]");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardDot() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T(".");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardAdd() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("+");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardLine() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("-");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardDollar() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("$");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

void CDialog_Keyboard::OnBtnBoardSharp() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->GetWindowText(mp_title_info);

	if(!OnKeyboard_Length_Check(mp_title_info))  return;   // �Է� ����̽� ���� Length üũ �Լ�
	else 
	{
		mp_title_info +=_T("#");
		((CEdit*)GetDlgItem(IDC_EDIT_BOARD_DATA))->SetWindowText(mp_title_info);
	}
}

BOOL CDialog_Keyboard::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if		(pMsg->wParam == VK_BACK)		{OnBtnBoardBack(); return true;}
		else if (pMsg->wParam == VK_DELETE)		{OnBtnBoardDel(); return true;}
		else if (pMsg->wParam == '1')			{OnBtnBoard1(); return true;}
		else if (pMsg->wParam == '2')			{OnBtnBoard2(); return true;}
		else if (pMsg->wParam == '3')			
		{
			if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				OnBtnBoardSharp(); 
				return true;
			}
			else
			{
				OnBtnBoard3(); 
				return true;
			}
		}
		else if (pMsg->wParam == '4')			
		{
			if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				OnBtnBoardDollar(); 
				return true;
			}
			else
			{
				OnBtnBoard4(); 
				return true;
			}
		}
		else if (pMsg->wParam == '5')			{OnBtnBoard5(); return true;}
		else if (pMsg->wParam == '6')			{OnBtnBoard6(); return true;}
		else if (pMsg->wParam == '7')			{OnBtnBoard7(); return true;}
		else if (pMsg->wParam == '8')			{OnBtnBoard8(); return true;}
		else if (pMsg->wParam == '9')			
		{
			if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				OnBtnBoardLbraceS(); 
				return true;
			}
			else
			{
				OnBtnBoard9(); 
				return true;
			}
		}
		else if (pMsg->wParam == '0')			
		{
			if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				OnBtnBoardRbraceS(); 
				return true;
			}
			else
			{
				OnBtnBoard0(); 
				return true;
			}
		}
		else if (pMsg->wParam == 'A')			{OnBtnBoardA(); return true;}
		else if (pMsg->wParam == 'B')			{OnBtnBoardB(); return true;}
		else if (pMsg->wParam == 'C')			{OnBtnBoardC(); return true;}
		else if (pMsg->wParam == 'D')			{OnBtnBoardD(); return true;}
		else if (pMsg->wParam == 'E')			{OnBtnBoardE(); return true;}
		else if (pMsg->wParam == 'F')			{OnBtnBoardF(); return true;}
		else if (pMsg->wParam == 'G')			{OnBtnBoardG(); return true;}
		else if (pMsg->wParam == 'H')			{OnBtnBoardH(); return true;}
		else if (pMsg->wParam == 'I')			{OnBtnBoardI(); return true;}
		else if (pMsg->wParam == 'J')			{OnBtnBoardJ(); return true;}
		else if (pMsg->wParam == 'K')			{OnBtnBoardK(); return true;}
		else if (pMsg->wParam == 'L')			{OnBtnBoardL(); return true;}
		else if (pMsg->wParam == 'M')			{OnBtnBoardM(); return true;}
		else if (pMsg->wParam == 'N')			{OnBtnBoardN(); return true;}
		else if (pMsg->wParam == 'O')			{OnBtnBoardO(); return true;}
		else if (pMsg->wParam == 'P')			{OnBtnBoardP(); return true;}
		else if (pMsg->wParam == 'Q')			{OnBtnBoardQ(); return true;}
		else if (pMsg->wParam == 'R')			{OnBtnBoardR(); return true;}
		else if (pMsg->wParam == 'S')			{OnBtnBoardS(); return true;}
		else if (pMsg->wParam == 'T')			{OnBtnBoardT(); return true;}
		else if (pMsg->wParam == 'U')			{OnBtnBoardU(); return true;}
		else if (pMsg->wParam == 'V')			{OnBtnBoardV(); return true;}
		else if (pMsg->wParam == 'W')			{OnBtnBoardW(); return true;}
		else if (pMsg->wParam == 'X')			{OnBtnBoardX(); return true;}
		else if (pMsg->wParam == 'Y')			{OnBtnBoardY(); return true;}
		else if (pMsg->wParam == 'Z')			{OnBtnBoardZ(); return true;}
		else if (pMsg->wParam == 191)			{OnBtnBoardDiv(); return true;}
		else if (pMsg->wParam == 219)			{OnBtnBoardLbraceB(); return true;}
		else if (pMsg->wParam == 221)			{OnBtnBoardRbraceB(); return true;}
		else if (pMsg->wParam == 190)			{OnBtnBoardDot(); return true;}
		else if (pMsg->wParam == VK_ADD)		{OnBtnBoardAdd(); return true;}
		else if (pMsg->wParam == 189)			{OnBtnBoardLine(); return true;}
		else if (pMsg->wParam == 187)			
		{
			if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				OnBtnBoardAdd(); 
				return true;
			}
		}
		else if (pMsg->wParam == VK_RETURN)		{OnOK(); return true;}
	}

	return StandardDialog::PreTranslateMessage(pMsg);
}

CString CDialog_Keyboard::GetEditString(CString strText, CString strPrev)
{
	CString strResult;
	int n_response;
	
	CDialog_Keyboard  keyboard_dlg;
	
	st_msg.mstr_keyboard_msg = strText;
	st_msg.mstr_typing_msg = strPrev;
	
	n_response = keyboard_dlg.DoModal();
	
	if (n_response == IDOK)
	{
		strResult = st_msg.mstr_typing_msg;
	}
	else
	{
		strResult = strPrev;
	}
	
	return strResult;
}
