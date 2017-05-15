// Dialog_Pass_Check.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Pass_Check.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Pass_Check dialog

CDialog_Pass_Check::CDialog_Pass_Check(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Pass_Check::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Pass_Check)
	//}}AFX_DATA_INIT
	
	m_caption_main = "Password Check Dialog Box";
//	m_is_shape_3d = YES;
}


void CDialog_Pass_Check::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Pass_Check)
	DDX_Control(pDX, IDC_BTN_PASS_CHK_ADD, m_btn_pass_chk_add);
	DDX_Control(pDX, IDC_TITLE_PASS_CHK, m_title_pass_chk);
	DDX_Control(pDX, IDC_MSG_PASS_CHK, m_msg_pass_chk);
	DDX_Control(pDX, IDC_GROUP_PASS_CHK, m_group_pass_chk);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_SHARP, m_btn_pass_chk_sharp);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_RBRACE_S, m_btn_pass_chk_rbrace_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_RBRACE_B, m_btn_pass_chk_rbrace_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_LINE, m_btn_pass_chk_line);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_LBRACE_S, m_btn_pass_chk_lbrace_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_LBRACE_B, m_btn_pass_chk_lbrace_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_DOT, m_btn_pass_chk_dot);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_DOLLAR, m_btn_pass_chk_dollar);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_DIV, m_btn_pass_chk_div);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_DEL, m_btn_pass_chk_del);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_BACK, m_btn_pass_chk_back);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_Z, m_btn_pass_chk_z);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_Y, m_btn_pass_chk_y);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_X, m_btn_pass_chk_x);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_W, m_btn_pass_chk_w);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_V, m_btn_pass_chk_v);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_U, m_btn_pass_chk_u);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_T, m_btn_pass_chk_t);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_S, m_btn_pass_chk_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_R, m_btn_pass_chk_r);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_Q, m_btn_pass_chk_q);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_P, m_btn_pass_chk_p);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_O, m_btn_pass_chk_o);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_N, m_btn_pass_chk_n);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_M, m_btn_pass_chk_m);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_L, m_btn_pass_chk_l);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_K, m_btn_pass_chk_k);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_J, m_btn_pass_chk_j);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_I, m_btn_pass_chk_i);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_H, m_btn_pass_chk_h);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_G, m_btn_pass_chk_g);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_F, m_btn_pass_chk_f);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_E, m_btn_pass_chk_e);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_D, m_btn_pass_chk_d);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_C, m_btn_pass_chk_c);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_B, m_btn_pass_chk_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_A, m_btn_pass_chk_a);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_9, m_btn_pass_chk_9);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_8, m_btn_pass_chk_8);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_7, m_btn_pass_chk_7);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_6, m_btn_pass_chk_6);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_5, m_btn_pass_chk_5);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_4, m_btn_pass_chk_4);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_3, m_btn_pass_chk_3);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_2, m_btn_pass_chk_2);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_1, m_btn_pass_chk_1);
	DDX_Control(pDX, IDC_BTN_PASS_CHK_0, m_btn_pass_chk_0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Pass_Check, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Pass_Check)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_BACK, OnBtnPassChkBack)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_DEL, OnBtnPassChkDel)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_LBRACE_S, OnBtnPassChkLbraceS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_RBRACE_S, OnBtnPassChkRbraceS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_DIV, OnBtnPassChkDiv)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_LBRACE_B, OnBtnPassChkLbraceB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_RBRACE_B, OnBtnPassChkRbraceB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_DOT, OnBtnPassChkDot)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_ADD, OnBtnPassChkAdd)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_LINE, OnBtnPassChkLine)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_DOLLAR, OnBtnPassChkDollar)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_SHARP, OnBtnPassChkSharp)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_1, OnBtnPassChk1)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_2, OnBtnPassChk2)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_3, OnBtnPassChk3)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_4, OnBtnPassChk4)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_5, OnBtnPassChk5)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_6, OnBtnPassChk6)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_7, OnBtnPassChk7)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_8, OnBtnPassChk8)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_9, OnBtnPassChk9)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_0, OnBtnPassChk0)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_A, OnBtnPassChkA)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_B, OnBtnPassChkB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_C, OnBtnPassChkC)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_D, OnBtnPassChkD)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_E, OnBtnPassChkE)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_F, OnBtnPassChkF)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_G, OnBtnPassChkG)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_H, OnBtnPassChkH)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_I, OnBtnPassChkI)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_J, OnBtnPassChkJ)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_K, OnBtnPassChkK)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_L, OnBtnPassChkL)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_M, OnBtnPassChkM)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_N, OnBtnPassChkN)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_O, OnBtnPassChkO)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_P, OnBtnPassChkP)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_Q, OnBtnPassChkQ)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_R, OnBtnPassChkR)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_S, OnBtnPassChkS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_T, OnBtnPassChkT)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_U, OnBtnPassChkU)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_V, OnBtnPassChkV)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_W, OnBtnPassChkW)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_X, OnBtnPassChkX)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_Y, OnBtnPassChkY)
	ON_BN_CLICKED(IDC_BTN_PASS_CHK_Z, OnBtnPassChkZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Pass_Check message ICTs

BOOL CDialog_Pass_Check::OnInitDialog() 
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
// 	mp_pass_font = NULL;
// 	mp_pass_font = new CFont;
// 	mp_pass_font->CreateFont(17,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************
	
	OnPassChk_GroupBox_Set();
	OnPassChk_Button_Set();
	OnPassChk_Lable_Set();
	OnPassChk_EditBox_Set();
	OnPassChk_Level_Set();

	// System Lock ���� ��ȣ ���� �ε� �Լ�
	if (st_handler.mstr_pass_level != "SystemLock")  OnPassChk_Pass_Data_Load();

	// ��ȣ �Է� ����Ʈ �ڽ��� ��Ŀ�� ����
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Pass_Check::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_pass_font;
// 	mp_pass_font = NULL;
	// **************************************************************************

	delete mp_pass_chk_ok;		// OK ��ư�� ������ ���� ���� 
	delete mp_pass_chk_cancel;  // Cancel ��ư�� ������ ���� ���� 

	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();	
}

void CDialog_Pass_Check::OnPassChk_Button_Set()
{
	mp_pass_chk_ok = CreateOkButton(IDOK, this);
	mp_pass_chk_cancel = CreateCancelButton(IDCANCEL, this);
}

void CDialog_Pass_Check::OnPassChk_GroupBox_Set()
{
	CSxLogFont pass_chk_logo(15,FW_SEMIBOLD,false,"MS Sans Serif");

//	m_group_pass_chk.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
	m_group_pass_chk.SetBackgroundColor(RGB(206, 206, 206), RGB(255, 255, 204));
	m_group_pass_chk.SetFont(pass_chk_logo);
	m_group_pass_chk.SetCatptionTextColor(RGB(145,25,0));
	m_group_pass_chk.SetFontBold(TRUE);
}

void CDialog_Pass_Check::OnPassChk_Lable_Set()
{
	m_msg_pass_chk.SetFont(Func.mp_pass_font);
	m_msg_pass_chk.SetWindowText(_T("Input Password"));
	m_msg_pass_chk.SetCenterText();
	m_msg_pass_chk.SetColor(RGB(0,0,255));
	m_msg_pass_chk.SetGradientColor(RGB(0,0,0));
	m_msg_pass_chk.SetTextColor(RGB(255,255,255));

	m_title_pass_chk.SetFont(Func.mp_pass_font);
	m_title_pass_chk.SetWindowText(_T("=>"));
	m_title_pass_chk.SetCenterText();
	m_title_pass_chk.SetColor(RGB(0,0,0));
	m_title_pass_chk.SetGradientColor(RGB(0,0,0));
	m_title_pass_chk.SetTextColor(RGB(255,255,255));
}

void CDialog_Pass_Check::OnPassChk_EditBox_Set()
{
	m_edit_pass_chk.SubclassDlgItem( IDC_EDIT_PASS_CHK_DATA, this );
	m_edit_pass_chk.bkColor( RGB(50, 100, 150) );
	m_edit_pass_chk.textColor( RGB(255, 255,255) );
    m_edit_pass_chk.setFont( -16 );
}

void CDialog_Pass_Check::OnPassChk_Level_Set()
{
	if (st_handler.mstr_pass_level == "SystemLock")		mn_pass_level = 0;
	else if (st_handler.mstr_pass_level == "SystemUnlock")	mn_pass_level = 1;
	else if (st_handler.mstr_pass_level == "LevelChange")	mn_pass_level = 2;
}

void CDialog_Pass_Check::OnPassChk_Pass_Data_Load()
{
	mstr_temp_chk.Empty();		// ��ȣ �ӽ� ���� ���� �ʱ�ȭ
	mstr_level1_chk.Empty();	// ���� ��ȣ �ӽ� ���� ���� �ʱ�ȭ 
	mstr_level2_chk.Empty();	// ���� ��ȣ �ӽ� ���� ���� �ʱ�ȭ 
	mstr_level3_chk.Empty();	//2014,0606 ybs

	mcls_pass_chk.OnPassWord_Load("Level1");			// ������ ���� ��ȣ ���� �ε� �Լ�

	if ((st_msg.mstr_password).IsEmpty())  m_msg_pass_chk.SetWindowText(_T("Haven't Password"));
	else	mstr_level1_chk = st_msg.mstr_password;	// ���� ������ ����� ��ȣ ���� Ŭ���� ������ ���� 

	mcls_pass_chk.OnPassWord_Load("Level2");			// ������ ���� ��ȣ ���� �ε� �Լ�

	if ((st_msg.mstr_password).IsEmpty())  m_msg_pass_chk.SetWindowText(_T("Haven't Password"));
	else	mstr_level2_chk = st_msg.mstr_password;	// ���� ������ ����� ��ȣ ���� Ŭ���� ������ ���� 

	mcls_pass_chk.OnPassWord_Load("Lock");				// ������ ���� ��ȣ �ε� �Լ�
	
	if ((st_msg.mstr_password).IsEmpty())	m_msg_pass_chk.SetWindowText(_T("Haven't Password"));
	else	mstr_temp_chk = st_msg.mstr_password;		// ��ȣ ���� Ŭ���� ������ ����

	mstr_admin_chk = "ADMIN";							// ��ȣ ���� Ŭ���� ������ ���� 
	mstr_level3_chk = "ADMIN";	//2014,0606 ybs
}

BOOL CDialog_Pass_Check::OnPassChk_Length_Check()
{
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk.MakeUpper();
	mstr_pass_chk.TrimLeft(' ');               
	mstr_pass_chk.TrimRight(' ');

	mn_cnt=strlen(mstr_pass_chk) ;
	if (mn_cnt >= 15) return FALSE;

	return TRUE;
}

void CDialog_Pass_Check::OnOK() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk.MakeUpper();
	mstr_pass_chk.TrimLeft(' ');               
	mstr_pass_chk.TrimRight(' ');

	switch(mn_pass_level)
	{
	case 0:						// System Lock Mode
		mcls_pass_chk.OnPassWord_Save("Lock", mstr_pass_chk);  // System Lock ��ȣ ���� ���� �Լ�
		break;

	case 1:						// System Unlock Mode
		if (mstr_temp_chk == mstr_pass_chk)
		{

		}
		else														//�̵� ���� �ƴҶ�...
		{
			m_msg_pass_chk.SetWindowText(_T("Invalid Password"));

			mstr_pass_chk.Empty();

			((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
			((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetFocus();

			if (st_handler.cwnd_list != NULL)
			{
//				st_msg.mstr_abnormal_msg = "Invalid Password.";
				sprintf(st_msg.c_abnormal_msg, "Invalid Password.");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
			}
			return;
		}

		break;

	case 2:						// Level Change Mode
		if (mstr_level1_chk == mstr_pass_chk)						// ��ȣ�� Level1�϶�...
		{
			st_handler.mn_level_maint = TRUE;						// ����Ʈ ����(Level 1) �÷��� ����
			
			if (st_handler.cwnd_list != NULL)
			{
//				st_msg.mstr_normal_msg = "Level 1 Mode (Maintenance Mode)";
				sprintf(st_msg.c_normal_msg, "Level 1 Mode (Maintenance Mode)");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
		}
		else if (mstr_level2_chk == mstr_pass_chk)					// ��ȣ�� Level2�϶�...
		{
			st_handler.mn_level_teach = TRUE;						// ƼĪ ����(Level 2) ���� �÷��� �ʱ�ȭ

			if (st_handler.cwnd_list != NULL)
			{
//				st_msg.mstr_normal_msg = "Level 2 Mode (Machine Teaching Mode)";
				sprintf(st_msg.c_normal_msg, "Level 2 Mode (Machine Teaching Mode)");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
		}
// 		else if (mstr_admin_chk == mstr_pass_chk)	//��ȣ�� Programmer ����϶�... //2014.0606 ysj
// 		{
// 			st_handler.mn_level_teach = TRUE;						// ƼĪ ����(Level 2) ���� �÷��� �ʱ�ȭ
// 			
// 			if (st_handler.cwnd_list != NULL)
// 			{
// //				st_msg.mstr_normal_msg = "Admin Mode (Machine Administrator Mode)";
// 				sprintf(st_msg.c_normal_msg, "Admin Mode (Machine Administrator Mode)");
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
// 			}
// 
// 			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
// 			if (st_handler.mn_menu_num != 801)
// 			::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 8, 1);	// Administrator ȭ������ ��ȯ ��û
// 		}
		else if ("ADMINSPEED" == mstr_pass_chk)
		{
			st_handler.mn_level_speed = TRUE;
			
			if (st_handler.cwnd_list != NULL)
			{
//				st_msg.mstr_normal_msg = "Speed Mode (Machine Speed Mode)";
				sprintf(st_msg.c_normal_msg, "Speed Mode (Machine Speed Mode)");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}
		}
		else if ("ADMIN" == mstr_pass_chk)//2014.0606 ysj ó�� üũ�� ��ȣ ���� OK ��ư ������ ����� //mstr_level3_chk)//2014,0606 ybs
		{
			st_handler.mn_level_ver = TRUE;
			st_handler.mn_level_teach = TRUE; //2014.0606 ysj

			if (st_handler.cwnd_list != NULL)
			{
				//				st_msg.mstr_normal_msg = "Speed Mode (Machine Speed Mode)";
				sprintf(st_msg.c_normal_msg, "Admin Mode (Machine Administrator Mode)");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}
			////2014.0606 ysj
			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
			if (st_handler.mn_menu_num != 801)
			::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 8, 1);	// Administrator ȭ������ ��ȯ ��û
			////
		}
		else														// �̵� ���� �ƴҶ�...
		{
			m_msg_pass_chk.SetWindowText(_T("Invalid Password"));

			mstr_pass_chk.Empty();
			((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
			((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetFocus();

			st_handler.mn_level_maint = FALSE;						// ����Ʈ ����(Level 1) �÷��� �ʱ�ȭ
			st_handler.mn_level_teach = FALSE;						// ƼĪ ����(Level 2) �÷��� �ʱ�ȭ	
			st_handler.mn_level_ver = FALSE;//2014,0606 ybs

			if (st_handler.cwnd_list != NULL)
			{
//				st_msg.mstr_abnormal_msg = "Invalid Password.";
				sprintf(st_msg.c_abnormal_msg, "Invalid Password.");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
			}

			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
			return;
		}
		break;
	}

	StandardDialog::OnOK();
}

void CDialog_Pass_Check::OnBtnPassChkBack() 
{
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mn_cnt=strlen(mstr_pass_chk) ;

	if (mn_cnt == 0) return;

	CString Data( _T(mstr_pass_chk)) ;
	mstr_pass_chk = Data.Left(mn_cnt-1) ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkDel() 
{
	mstr_pass_chk.Empty();
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk1() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("1") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk2() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("2") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk3() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("3") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk4() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("4") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk5() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("5") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk6() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("6") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk7() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("7") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk8() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("8") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk9() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("9") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChk0() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("0") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkA() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("A") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkB() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("B") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkC() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("C") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkD() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("D") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkE() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("E") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkF() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("F") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkG() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("G") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkH() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("H") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkI() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("I") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkJ() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("J") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkK() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("K") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkL() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("L") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkM() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("M") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkN() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("N") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkO() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("O") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkP() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("P") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkQ() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("Q") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkR() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("R") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkS() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("S") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkT() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("T") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkU() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("U") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkV() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("V") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkW() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("W") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkX() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("X") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkY() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("Y") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkZ() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("Z") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}
void CDialog_Pass_Check::OnBtnPassChkLbraceS() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("(") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkRbraceS() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T(")") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkDiv() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("/") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkLbraceB() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("[") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkRbraceB() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("]") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkDot() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T(".") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkAdd() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("+") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkLine() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("-") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkDollar() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("$") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}

void CDialog_Pass_Check::OnBtnPassChkSharp() 
{
	if(!OnPassChk_Length_Check())  return;

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->GetWindowText(mstr_pass_chk);
	mstr_pass_chk +=_T("#") ;
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHK_DATA))->SetWindowText(mstr_pass_chk);
}
