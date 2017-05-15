// Dialog_Pass_Change.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Pass_Change.h"

#include "Srcbase\ALocalization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Pass_Change dialog


CDialog_Pass_Change::CDialog_Pass_Change(CWnd* pParent /*=NULL*/)
	: StandardDialog(CDialog_Pass_Change::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Pass_Change)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_caption_main = "Password Change Dialog Box";
//	m_is_shape_3d = YES;
}


void CDialog_Pass_Change::DoDataExchange(CDataExchange* pDX)
{
	StandardDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Pass_Change)
	DDX_Control(pDX, IDC_RADIO_PASS_VERIFY, m_radio_pass_verify);
	DDX_Control(pDX, IDC_RADIO_PASS_OLD, m_radio_pass_old);
	DDX_Control(pDX, IDC_RADIO_PASS_NEW, m_radio_pass_new);
	DDX_Control(pDX, IDC_MSG_PASS_CHG, m_msg_pass_chg);
	DDX_Control(pDX, IDC_GROUP_PASS_CHG, m_group_pass_chg);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_SHARP, m_btn_pass_chg_sharp);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_RBRACE_S, m_btn_pass_chg_rbrace_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_RBRACE_B, m_btn_pass_chg_rbrace_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_LINE, m_btn_pass_chg_line);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_LBRACE_S, m_btn_pass_chg_lbrace_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_LBRACE_B, m_btn_pass_chg_lbrace_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_DOT, m_btn_pass_chg_dot);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_DOLLAR, m_btn_pass_chg_dollar);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_DIV, m_btn_pass_chg_div);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_ADD, m_btn_pass_chg_add);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_DEL, m_btn_pass_chg_del);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_BACK, m_btn_pass_chg_back);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_Z, m_btn_pass_chg_z);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_Y, m_btn_pass_chg_y);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_X, m_btn_pass_chg_x);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_W, m_btn_pass_chg_w);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_V, m_btn_pass_chg_v);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_U, m_btn_pass_chg_u);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_T, m_btn_pass_chg_t);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_S, m_btn_pass_chg_s);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_R, m_btn_pass_chg_r);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_Q, m_btn_pass_chg_q);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_P, m_btn_pass_chg_p);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_O, m_btn_pass_chg_o);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_N, m_btn_pass_chg_n);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_M, m_btn_pass_chg_m);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_L, m_btn_pass_chg_l);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_K, m_btn_pass_chg_k);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_J, m_btn_pass_chg_j);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_I, m_btn_pass_chg_i);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_H, m_btn_pass_chg_h);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_G, m_btn_pass_chg_g);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_F, m_btn_pass_chg_f);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_E, m_btn_pass_chg_e);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_D, m_btn_pass_chg_d);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_C, m_btn_pass_chg_c);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_B, m_btn_pass_chg_b);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_A, m_btn_pass_chg_a);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_9, m_btn_pass_chg_9);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_8, m_btn_pass_chg_8);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_7, m_btn_pass_chg_7);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_6, m_btn_pass_chg_6);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_5, m_btn_pass_chg_5);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_4, m_btn_pass_chg_4);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_3, m_btn_pass_chg_3);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_2, m_btn_pass_chg_2);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_1, m_btn_pass_chg_1);
	DDX_Control(pDX, IDC_BTN_PASS_CHG_0, m_btn_pass_chg_0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Pass_Change, StandardDialog)
	//{{AFX_MSG_MAP(CDialog_Pass_Change)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_PASS_OLD, OnRadioPassOld)
	ON_BN_CLICKED(IDC_RADIO_PASS_NEW, OnRadioPassNew)
	ON_BN_CLICKED(IDC_RADIO_PASS_VERIFY, OnRadioPassVerify)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_BACK, OnBtnPassChgBack)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_DEL, OnBtnPassChgDel)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_1, OnBtnPassChg1)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_2, OnBtnPassChg2)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_3, OnBtnPassChg3)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_4, OnBtnPassChg4)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_5, OnBtnPassChg5)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_6, OnBtnPassChg6)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_7, OnBtnPassChg7)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_8, OnBtnPassChg8)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_9, OnBtnPassChg9)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_0, OnBtnPassChg0)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_A, OnBtnPassChgA)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_B, OnBtnPassChgB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_C, OnBtnPassChgC)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_D, OnBtnPassChgD)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_E, OnBtnPassChgE)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_F, OnBtnPassChgF)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_G, OnBtnPassChgG)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_H, OnBtnPassChgH)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_I, OnBtnPassChgI)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_J, OnBtnPassChgJ)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_K, OnBtnPassChgK)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_L, OnBtnPassChgL)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_M, OnBtnPassChgM)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_N, OnBtnPassChgN)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_O, OnBtnPassChgO)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_P, OnBtnPassChgP)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_Q, OnBtnPassChgQ)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_R, OnBtnPassChgR)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_S, OnBtnPassChgS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_T, OnBtnPassChgT)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_U, OnBtnPassChgU)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_V, OnBtnPassChgV)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_W, OnBtnPassChgW)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_X, OnBtnPassChgX)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_Y, OnBtnPassChgY)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_Z, OnBtnPassChgZ)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_LBRACE_S, OnBtnPassChgLbraceS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_RBRACE_S, OnBtnPassChgRbraceS)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_DIV, OnBtnPassChgDiv)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_LBRACE_B, OnBtnPassChgLbraceB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_RBRACE_B, OnBtnPassChgRbraceB)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_DOT, OnBtnPassChgDot)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_ADD, OnBtnPassChgAdd)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_LINE, OnBtnPassChgLine)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_DOLLAR, OnBtnPassChgDollar)
	ON_BN_CLICKED(IDC_BTN_PASS_CHG_SHARP, OnBtnPassChgSharp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Pass_Change message ICTs

BOOL CDialog_Pass_Change::OnInitDialog() 
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
// 	mp_change_font = NULL;
// 	mp_change_font = new CFont;
// 	mp_change_font->CreateFont(16,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************
	
	OnPassChange_Button_Set();						// ��ȣ ���� ��ȭ ���� Į�� ��ư ���� �Լ�
	OnPassChange_GroupBox_Set();					// ��ȣ ���� ��ȭ ���� Į�� �׷� �ڽ� ���� �Լ�
	OnPassChange_Lable_Set();						// ��ȣ ���� ��ȭ ���� Į�� �ؽ�Ʈ �ڽ� ���� �Լ�
	OnPassChange_EditBox_Set();						// ��ȣ ���� ��ȭ ���� Į�� ����Ʈ �ڽ� ���� �Լ�
	OnPassChange_RadioButton_Set();					// ��ȣ ���� ��ȭ ���� ���� ��ư ���� �Լ�
	
	mn_pass_state = 0;								// ��ȣ ���� �ʱ� ���� ���� ���� 

	OnPassChange_Radio_State_Set(mn_pass_state);	// ���� ��ư ���� ���� �Լ�
	OnPassChange_Password_Focus(mn_pass_state);		// ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�

	OnPassChange_Pass_Data_Load();					// ������ ��ȣ ���� �ε� �Լ�

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Pass_Change::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�                                                 
	// **************************************************************************
// 	delete mp_change_font;
// 	mp_change_font = NULL;
	// **************************************************************************

	delete mp_pass_chg_ok;		// OK ��ư�� ������ ���� ���� 
	delete mp_pass_chg_cancel;  // Cancel ��ư�� ������ ���� ����
	
	if (mn_dialog == 1)
	{
		st_handler.mn_switch_lock = FALSE;
	}

	StandardDialog::OnDestroy();
}

void CDialog_Pass_Change::OnPassChange_GroupBox_Set()
{
	CSxLogFont pass_chg_logo(15,FW_SEMIBOLD,false,"MS Sans Serif");

//	m_group_pass_chg.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
	m_group_pass_chg.SetBackgroundColor(RGB(206, 206, 206), RGB(255, 255, 204));
	m_group_pass_chg.SetFont(pass_chg_logo);
	m_group_pass_chg.SetCatptionTextColor(RGB(145,25,0));
	m_group_pass_chg.SetFontBold(TRUE);
}

void CDialog_Pass_Change::OnPassChange_Lable_Set()
{
	m_msg_pass_chg.SetFont(Func.mp_change_font);
	m_msg_pass_chg.SetWindowText(_T("Change the New Password"));
	m_msg_pass_chg.SetCenterText();
	m_msg_pass_chg.SetColor(RGB(0,0,255));
	m_msg_pass_chg.SetGradientColor(RGB(0,0,0));
	m_msg_pass_chg.SetTextColor(RGB(255,255,255));
}

void CDialog_Pass_Change::OnPassChange_Button_Set()
{
	mp_pass_chg_ok = CreateOkButton(IDOK, this);
	mp_pass_chg_cancel = CreateCancelButton(IDCANCEL, this);
}

void CDialog_Pass_Change::OnPassChange_EditBox_Set()
{
	m_edit_pass_old.SubclassDlgItem(IDC_EDIT_PASS_CHG_OLD, this);
	m_edit_pass_old.bkColor(RGB(100, 150, 200));
	m_edit_pass_old.textColor(RGB(255, 255,255));
    m_edit_pass_old.setFont(-16);

	m_edit_pass_new.SubclassDlgItem(IDC_EDIT_PASS_CHG_NEW, this);
	m_edit_pass_new.bkColor(RGB(50, 100, 150));
	m_edit_pass_new.textColor(RGB(255, 255,255));
    m_edit_pass_new.setFont(-16);

	m_edit_pass_verify.SubclassDlgItem(IDC_EDIT_PASS_CHG_VERIFY, this);
	m_edit_pass_verify.bkColor(RGB(50, 100, 150));
	m_edit_pass_verify.textColor(RGB(255, 255,255));
    m_edit_pass_verify.setFont(-16);
}

void CDialog_Pass_Change::OnPassChange_RadioButton_Set()
{
	//Set images
    m_radio_pass_old.SetImage(IDB_REDBUTTON, 15);
	m_radio_pass_new.SetImage(IDB_REDBUTTON, 15);
	m_radio_pass_verify.SetImage(IDB_REDBUTTON, 15);
}

void CDialog_Pass_Change::OnPassChange_Radio_State_Set(int n_state)
{
	switch(n_state)
	{
	case 0 :
		m_radio_pass_old.Depress(true);
		m_radio_pass_new.Depress(false);
		m_radio_pass_verify.Depress(false);
		break;
	case 1 :
		m_radio_pass_old.Depress(false);
		m_radio_pass_new.Depress(true);
		m_radio_pass_verify.Depress(false);
		break;
	case 2 :
		m_radio_pass_old.Depress(false);
		m_radio_pass_new.Depress(false);
		m_radio_pass_verify.Depress(true);
		break;
	default :
		break;
	}
}

void CDialog_Pass_Change::OnPassChange_Pass_Data_Load()
{
	mstr_temp.Empty();  // ���� ��ȣ �ӽ� ���� ���� �ʱ�ȭ 

	mcls_pass_chg.OnPassWord_Load(st_handler.mstr_pass_level);  // ������ ���� ��ȣ ���� �ε� �Լ�

	if ((st_msg.mstr_password).IsEmpty())  m_msg_pass_chg.SetWindowText(_T("Appropriate password does not exist."));
	else   mstr_temp = st_msg.mstr_password;  // ���� ������ ����� ��ȣ ���� Ŭ���� ������ ���� 
}

void CDialog_Pass_Change::OnPassChange_Error_Display(CString n_text, CString n_level)
{
	m_msg_pass_chg.SetWindowText(_T(n_text + n_level));

	mp_old_data.Empty();
	mp_new_data.Empty();
	mp_verify_data.Empty();

	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
}

void CDialog_Pass_Change::OnPassChange_Password_Focus(int idx)
{
	switch(idx)
	{
	case 0:  // ���� ��ȣ 
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetFocus();
		break;
	case 1:  // �� ��ȣ 
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetFocus();
		break;
	case 2:  // ��ȣ Ȯ�� 
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetFocus();
		break;
	default:
		break;
	}
}

BOOL CDialog_Pass_Change::OnPassChange_Length_Check(int n_case)
{
	switch(n_case)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data.MakeUpper();
		mp_old_data.TrimLeft(' ');               
		mp_old_data.TrimRight(' ');

		mn_cnt=strlen(mp_old_data) ;
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data.MakeUpper();
		mp_new_data.TrimLeft(' ');               
		mp_new_data.TrimRight(' ');

		mn_cnt=strlen(mp_new_data) ;
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data.MakeUpper();
		mp_verify_data.TrimLeft(' ');               
		mp_verify_data.TrimRight(' ');

		mn_cnt=strlen(mp_verify_data) ;
		break;
	default:
		return FALSE;
		break;
	}

	if (mn_cnt >= 15) return FALSE;

	return TRUE;
}

void CDialog_Pass_Change::OnRadioPassOld() 
{
	if (mn_pass_state != 0)  
	{
		mn_pass_state = 0;								// ���� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state);	// ���� ��ư ���� ���� �Լ�
	}

	OnPassChange_Password_Focus(mn_pass_state);			// ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
}

void CDialog_Pass_Change::OnRadioPassNew() 
{
	if (mn_pass_state != 1)  
	{
		mn_pass_state = 1;								// ���� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state);	// ���� ��ư ���� ���� �Լ�
	}

	OnPassChange_Password_Focus(mn_pass_state);			// ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
}

void CDialog_Pass_Change::OnRadioPassVerify() 
{
	if (mn_pass_state != 2)  
	{
		mn_pass_state = 2;								// ���� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state);	// ���� ��ư ���� ���� �Լ�
	}

	OnPassChange_Password_Focus(mn_pass_state);			// ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
}

void CDialog_Pass_Change::OnBtnPassChgBack() 
{
	CString Data;  // �Է� ���� �ӽ� ���� ���� 

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mn_cnt=strlen(mp_old_data) ;
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mn_cnt=strlen(mp_new_data) ;
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mn_cnt=strlen(mp_verify_data) ;
		break;
	default:
		break;
	}

	if (mn_cnt == 0) return;  // �Է� �����Ͱ� �������� �ʴ� ��쿡�� ���� 

	switch(mn_pass_state)
	{
	case 0:
		Data = mp_old_data ;
		mp_old_data=Data.Left(mn_cnt-1) ;
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		Data = mp_new_data ;
		mp_new_data=Data.Left(mn_cnt-1) ;
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		Data = mp_verify_data ;
		mp_verify_data=Data.Left(mn_cnt-1) ;
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgDel() 
{
	switch(mn_pass_state)  
	{
	case 0:
		mp_old_data.Empty();
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		mp_new_data.Empty();
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		mp_verify_data.Empty();
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg1() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg2() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("2");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("2");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("2");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg3() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("3");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("3");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("3");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg4() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("4");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("4");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("4");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg5() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("5");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("5");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("5");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg6() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("6");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("6");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("6");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg7() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("7");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("7");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("7");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg8() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("8");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("8");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("8");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg9() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("9");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("9");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("9");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChg0() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("0");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("0");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("0");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgA() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("A");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("A");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("A");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgB() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("B");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("B");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("B");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgC() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("C");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("C");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("C");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgD() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("D");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("D");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("D");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgE() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("E");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("E");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("E");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgF() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("F");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("F");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("F");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgG() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("G");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("G");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("G");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgH() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("H");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("H");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("H");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgI() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("I");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("I");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("I");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgJ() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("J");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("J");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("J");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgK() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("K");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("K");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("K");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgL() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("L");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("L");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("L");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgM() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("M");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("M");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("M");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgN() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("N");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("N");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("N");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgO() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("1");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgP() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("P");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("P");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("P");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgQ() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("Q");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("Q");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("Q");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgR() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("R");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("R");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("R");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgS() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("S");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("S");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("S");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgT() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("T");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("T");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("T");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgU() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("U");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("U");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("U");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgV() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("V");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("V");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("V");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgW() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("W");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("W");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("W");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgX() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("X");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("X");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("X");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgY() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("Y");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("Y");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("Y");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgZ() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("Z");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("Z");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("Z");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgLbraceS() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("(");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("(");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("(");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgRbraceS() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T(")");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T(")");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T(")");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgDiv() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("/");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("/");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("/");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgLbraceB() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("[");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("[");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("[");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgRbraceB() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("]");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("]");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("]");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgDot() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T(".");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T(".");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T(".");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgAdd() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("+");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("+");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("+");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgLine() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("-");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("-");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("-");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgDollar() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("$");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("$");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("$");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnBtnPassChgSharp() 
{
	if(!OnPassChange_Length_Check(mn_pass_state))  return;

	switch(mn_pass_state)
	{
	case 0:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
		mp_old_data +=_T("#");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->SetWindowText(mp_old_data);
		break;
	case 1:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
		mp_new_data +=_T("#");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
		mp_verify_data +=_T("#");
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		break;
	default:
		break;
	}
}

void CDialog_Pass_Change::OnOK() 
{
	int n_len, n_check_num = 0, n_check_string = 0, n_check_extra = 0;
	char chr_data[50];
	CString strOtherPassword;

	if (st_handler.mstr_pass_level == "Level1")				// Level 1
	{
		:: GetPrivateProfileString("Password", "Level_2", "M", chr_data, 50, st_path.mstr_basic);
		strOtherPassword = chr_data;
		strOtherPassword.MakeUpper();     // ���ڿ� �빮�ڷ� ����
		strOtherPassword.TrimLeft(' ');   // ���� ���ڿ� ���� ����              
		strOtherPassword.TrimRight(' ');  // ���� ���ڿ� ���� ����
	}
	else if (st_handler.mstr_pass_level == "Level2")			// Level 1
	{
		:: GetPrivateProfileString("Password", "Level_1", "M", chr_data, 50, st_path.mstr_basic);
		strOtherPassword = chr_data;
		strOtherPassword.MakeUpper();     // ���ڿ� �빮�ڷ� ����
		strOtherPassword.TrimLeft(' ');   // ���� ���ڿ� ���� ����              
		strOtherPassword.TrimRight(' ');  // ���� ���ڿ� ���� ����
	}


	// **************************************************************************
	// ���� ��ȣ �Է� ���� �˻�                                                  
	// **************************************************************************
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_OLD))->GetWindowText(mp_old_data);
	mp_old_data.MakeUpper();
	mp_old_data.TrimLeft(' ');               
	mp_old_data.TrimRight(' ');

	if (mp_old_data.IsEmpty())
	{
		OnPassChange_Error_Display(_T("Password Input Fail : "), st_handler.mstr_pass_level); // ��ȣ ���� �� �߻��� ���� ���� ��� �Լ�
		
		mn_pass_state = 0;  // ���� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state); // ���� ��ư ���� ���� �Լ�
		OnPassChange_Password_Focus(mn_pass_state); // ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
		
		return;
	}

	if (mstr_temp != mp_old_data)  // ���� ��ȣ �Է� ���� �˻� 
	{
		OnPassChange_Error_Display(_T("Password is inaccurate : "), st_handler.mstr_pass_level); // ��ȣ ���� �� �߻��� ���� ���� ��� �Լ�
		
		mn_pass_state = 0;  // ���� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state); // ���� ��ư ���� ���� �Լ�
		OnPassChange_Password_Focus(mn_pass_state); // ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
		
		return;
	}
	// **************************************************************************

	// **************************************************************************
	// �� ��ȣ �Է� ���� �˻�                                                    
	// **************************************************************************
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->GetWindowText(mp_new_data);
	mp_new_data.MakeUpper();
	mp_new_data.TrimLeft(' ');               
	mp_new_data.TrimRight(' ');

	if (mp_new_data.IsEmpty())
	{
		m_msg_pass_chg.SetWindowText(_T("New password input mistake"));

		mp_new_data.Empty();
		mp_verify_data.Empty();

		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);

		mn_pass_state = 1;  // �� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state); // ���� ��ư ���� ���� �Լ�
		OnPassChange_Password_Focus(mn_pass_state); // ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�

		return;
	}
	// **************************************************************************

	// **************************************************************************
	// Ȯ�� ��ȣ �Է� ���� �˻�                                                  
	// **************************************************************************
	((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->GetWindowText(mp_verify_data);
	mp_verify_data.MakeUpper();
	mp_verify_data.TrimLeft(' ');               
	mp_verify_data.TrimRight(' ');

	if (mp_verify_data.IsEmpty())
	{
		m_msg_pass_chg.SetWindowText(_T("Confirmation password input mistake."));

		mp_verify_data.Empty();
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);

		mn_pass_state = 2;  // ��ȣ Ȯ�� ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state); // ���� ��ư ���� ���� �Լ�
		OnPassChange_Password_Focus(mn_pass_state); // ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�
		
		return;
	}

	if (mp_verify_data != mp_new_data)  // �� ��ȣ ������ ��ȣ Ȯ�� ���� ��ġ ���� �˻� 
	{
		m_msg_pass_chg.SetWindowText(_T("Confirmation password input mistake."));

		mp_new_data.Empty();
		mp_verify_data.Empty();

		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);

		mn_pass_state = 1;  // �� ��ȣ ���·� ���� 

		OnPassChange_Radio_State_Set(mn_pass_state);	// ���� ��ư ���� ���� �Լ�
		OnPassChange_Password_Focus(mn_pass_state);		// ��ȣ �Է� Į�� ����Ʈ �ڽ� ��Ŀ�� ���� �Լ�

		return;
	}
	// **************************************************************************

	// **************************************************************************
	//  ADMINISTRATOR�� �浹 �˻�                                                
	// **************************************************************************
	if (mp_new_data == "ADMINISTRATOR" || mp_new_data == "ADMIN" || mp_new_data == "AMTSW" || mp_new_data == "AMT8590")			// ������ ���̵�� ���� ����.
	{
		m_msg_pass_chg.SetWindowText(_T("����Ҽ� ���� ��ȣ�Դϴ�."));
		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Not be registered is the password."));
		mp_new_data.Empty();
		mp_verify_data.Empty();
		
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		return;
	}
 
	n_len = mp_new_data.GetLength();
	
// 	if (n_len > 50)
// 	{
// 		m_msg_pass_chg.SetWindowText(_T("�Է� �����Դϴ�. 50�� ���Ϸ� �����ֽʽÿ�."));
// 		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Please set to less than 50 characters."));
// 		
// 		mp_new_data.Empty();
// 		mp_verify_data.Empty();
// 		
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
// 		return;
// 	}
// 	else if (n_len < 6)
// 	{
// 		m_msg_pass_chg.SetWindowText(_T("�Է� �����Դϴ�. 6�� �̻����� �����ֽʽÿ�."));
// 		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Please set at least 6 characters."));
// 		
// 		mp_new_data.Empty();
// 		mp_verify_data.Empty();
// 		
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
// 		return;
// 	}
// 	
// 	strcpy(chr_data, mp_new_data);
// 	
// 	for (i = 0; i < n_len; i++)
// 	{
// 		if (chr_data[i] >= 48 && chr_data[i] <= 57)			// ���� Ȯ��
// 		{
// 			n_check_num++;
// 		}
// 		else if (chr_data[i] >= 65 && chr_data[i] <= 90)	// ���� Ȯ��
// 		{
// 			n_check_string++;
// 		}
// 		else
// 		{
// 			n_check_extra++;
// 		}
// 	}
// 	
// 	if (n_check_string < 3)
// 	{
// 		m_msg_pass_chg.SetWindowText(_T("�Է� �����Դϴ�. ���ē��� 3�� �̻� ���� �ʾҽ��ϴ�."));
// 		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Alphabet did not go more than 3 characters."));
// 		
// 		mp_new_data.Empty();
// 		mp_verify_data.Empty();
// 		
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
// 		return;
// 	}
// 	
// 	if (n_check_num < 3)
// 	{
// 		m_msg_pass_chg.SetWindowText(_T("�Է� �����Դϴ�. ���ڰ� 3�� �̻� ���� �ʾҽ��ϴ�."));
// 		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Numbers did not go longer than 3 characters."));
// 		
// 		mp_new_data.Empty();
// 		mp_verify_data.Empty();
// 		
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
// 		return;
// 	}
// 	
// 	if (n_check_extra > 0)
// 	{
// 		m_msg_pass_chg.SetWindowText(_T("�Է� �����Դϴ�. Ư�����ڰ� �����ϴ�."));
// 		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Special characters are entered."));
// 		
// 		mp_new_data.Empty();
// 		mp_verify_data.Empty();
// 		
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
// 		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
// 		return;
// 	}
// 	// **************************************************************************

	if (strOtherPassword == mp_new_data)									// �ٸ� ��ȣ�� ���ٸ�.
	{
		m_msg_pass_chg.SetWindowText(_T("�����Դϴ�. �ٸ��� ��ȣ�� �����մϴ�."));
		if ( g_local.GetLocalType() == LOCAL_ENG )	m_msg_pass_chg.SetWindowText(_T("Is a typographical error. Password is the same as the other."));
		
		mp_new_data.Empty();
		mp_verify_data.Empty();
		
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_NEW))->SetWindowText(mp_new_data);
		((CEdit*)GetDlgItem(IDC_EDIT_PASS_CHG_VERIFY))->SetWindowText(mp_verify_data);
		return;
	}
	mcls_pass_chg.OnPassWord_Save(st_handler.mstr_pass_level, mp_new_data);	// ������ ���� ��ȣ ���� ���� �Լ�

	StandardDialog::OnOK();
}
