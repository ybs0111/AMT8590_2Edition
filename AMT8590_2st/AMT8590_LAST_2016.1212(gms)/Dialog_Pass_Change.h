#if !defined(AFX_DIALOG_PASS_CHANGE_H__6A12D9B4_3633_42E7_B488_B2CABF205C2F__INCLUDED_)
#define AFX_DIALOG_PASS_CHANGE_H__6A12D9B4_3633_42E7_B488_B2CABF205C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Pass_Change.h : header file
//

#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "editex.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "LedButton.h"		// LED ��ư ���� Ŭ���� �߰� 
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "sxlogfont.h"
#include "MacButtons.h"
// ******************************************************************************
// ��ȣ ���� �ε� �� ���� Ŭ���� �߰�                                            
// ******************************************************************************
#include "MyBasicData.h"           
// ******************************************************************************
/////////////////////////////////////////////////////////////////////////////
// CDialog_Pass_Change dialog

class CDialog_Pass_Change : public StandardDialog
{
// Construction
public:
	CDialog_Pass_Change(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Pass_Change)
	enum { IDD = IDD_DIALOG_PASS_CHANGE };
	CLedButton	m_radio_pass_verify;
	CLedButton	m_radio_pass_old;
	CLedButton	m_radio_pass_new;
	CGradientStatic	m_msg_pass_chg;
	CXPGroupBox	m_group_pass_chg;
	CMacButton	m_btn_pass_chg_sharp;
	CMacButton	m_btn_pass_chg_rbrace_s;
	CMacButton	m_btn_pass_chg_rbrace_b;
	CMacButton	m_btn_pass_chg_line;
	CMacButton	m_btn_pass_chg_lbrace_s;
	CMacButton	m_btn_pass_chg_lbrace_b;
	CMacButton	m_btn_pass_chg_dot;
	CMacButton	m_btn_pass_chg_dollar;
	CMacButton	m_btn_pass_chg_div;
	CMacButton	m_btn_pass_chg_add;
	CMacButton	m_btn_pass_chg_del;
	CMacButton	m_btn_pass_chg_back;
	CMacButton	m_btn_pass_chg_z;
	CMacButton	m_btn_pass_chg_y;
	CMacButton	m_btn_pass_chg_x;
	CMacButton	m_btn_pass_chg_w;
	CMacButton	m_btn_pass_chg_v;
	CMacButton	m_btn_pass_chg_u;
	CMacButton	m_btn_pass_chg_t;
	CMacButton	m_btn_pass_chg_s;
	CMacButton	m_btn_pass_chg_r;
	CMacButton	m_btn_pass_chg_q;
	CMacButton	m_btn_pass_chg_p;
	CMacButton	m_btn_pass_chg_o;
	CMacButton	m_btn_pass_chg_n;
	CMacButton	m_btn_pass_chg_m;
	CMacButton	m_btn_pass_chg_l;
	CMacButton	m_btn_pass_chg_k;
	CMacButton	m_btn_pass_chg_j;
	CMacButton	m_btn_pass_chg_i;
	CMacButton	m_btn_pass_chg_h;
	CMacButton	m_btn_pass_chg_g;
	CMacButton	m_btn_pass_chg_f;
	CMacButton	m_btn_pass_chg_e;
	CMacButton	m_btn_pass_chg_d;
	CMacButton	m_btn_pass_chg_c;
	CMacButton	m_btn_pass_chg_b;
	CMacButton	m_btn_pass_chg_a;
	CMacButton	m_btn_pass_chg_9;
	CMacButton	m_btn_pass_chg_8;
	CMacButton	m_btn_pass_chg_7;
	CMacButton	m_btn_pass_chg_6;
	CMacButton	m_btn_pass_chg_5;
	CMacButton	m_btn_pass_chg_4;
	CMacButton	m_btn_pass_chg_3;
	CMacButton	m_btn_pass_chg_2;
	CMacButton	m_btn_pass_chg_1;
	CMacButton	m_btn_pass_chg_0;
	//}}AFX_DATA

// Attributes
private:
// 	CFont* mp_change_font;							// ��Ʈ ���� ���� ���� 
	CButton *mp_pass_chg_ok, *mp_pass_chg_cancel;	// ��ư�� ���� ������ ����

	int mn_dialog;

	// **************************************************************************
	// ��ȣ ���� �ε�/���� Ŭ���� ���� ����                                      
	// **************************************************************************
	CMyBasicData mcls_pass_chg;
	// **************************************************************************

	// **************************************************************************
	// Į�� ����Ʈ �ڽ� Ŭ���� ���� ����                                         
	// **************************************************************************
	CEditEx m_edit_pass_old;
	CEditEx m_edit_pass_new;
	CEditEx m_edit_pass_verify;
	// **************************************************************************

	// **************************************************************************
	// ����Ʈ �ڽ��� �Էµ� ��ȣ üũ ���� ���� ����                             
	// **************************************************************************
	CString mstr_temp;		// ���� ��ȣ �ӽ� ���� ���� 
	int mn_pass_state;		// ��ȣ ���� ���� ���� ���� (old(0) / new(1) / verify(2))
	int mn_cnt;				// ����Ʈ �ڽ��� �Էµ� ��ȣ ���� �˻� ���� ���� ���� 

	CString mp_old_data;	// ���� ��ȣ ���� ���� ���� 
	CString mp_new_data;	// ���� �Էµ� ��ȣ ���� ���� ���� 
	CString mp_verify_data; // Ȯ�� ��ȣ ���� ���� ���� 
	// **************************************************************************

// Operations
public:
	BOOL OnPassChange_Length_Check(int n_case);
	void OnPassChange_Password_Focus(int idx);
	void OnPassChange_Error_Display(CString n_text, CString n_level);
	void OnPassChange_Pass_Data_Load();
	void OnPassChange_Radio_State_Set(int n_state);
	void OnPassChange_RadioButton_Set();
	void OnPassChange_EditBox_Set();
	void OnPassChange_Button_Set();
	void OnPassChange_Lable_Set();
	void OnPassChange_GroupBox_Set();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Pass_Change)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Pass_Change)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnRadioPassOld();
	afx_msg void OnRadioPassNew();
	afx_msg void OnRadioPassVerify();
	afx_msg void OnBtnPassChgBack();
	afx_msg void OnBtnPassChgDel();
	afx_msg void OnBtnPassChg1();
	afx_msg void OnBtnPassChg2();
	afx_msg void OnBtnPassChg3();
	afx_msg void OnBtnPassChg4();
	afx_msg void OnBtnPassChg5();
	afx_msg void OnBtnPassChg6();
	afx_msg void OnBtnPassChg7();
	afx_msg void OnBtnPassChg8();
	afx_msg void OnBtnPassChg9();
	afx_msg void OnBtnPassChg0();
	afx_msg void OnBtnPassChgA();
	afx_msg void OnBtnPassChgB();
	afx_msg void OnBtnPassChgC();
	afx_msg void OnBtnPassChgD();
	afx_msg void OnBtnPassChgE();
	afx_msg void OnBtnPassChgF();
	afx_msg void OnBtnPassChgG();
	afx_msg void OnBtnPassChgH();
	afx_msg void OnBtnPassChgI();
	afx_msg void OnBtnPassChgJ();
	afx_msg void OnBtnPassChgK();
	afx_msg void OnBtnPassChgL();
	afx_msg void OnBtnPassChgM();
	afx_msg void OnBtnPassChgN();
	afx_msg void OnBtnPassChgO();
	afx_msg void OnBtnPassChgP();
	afx_msg void OnBtnPassChgQ();
	afx_msg void OnBtnPassChgR();
	afx_msg void OnBtnPassChgS();
	afx_msg void OnBtnPassChgT();
	afx_msg void OnBtnPassChgU();
	afx_msg void OnBtnPassChgV();
	afx_msg void OnBtnPassChgW();
	afx_msg void OnBtnPassChgX();
	afx_msg void OnBtnPassChgY();
	afx_msg void OnBtnPassChgZ();
	afx_msg void OnBtnPassChgLbraceS();
	afx_msg void OnBtnPassChgRbraceS();
	afx_msg void OnBtnPassChgDiv();
	afx_msg void OnBtnPassChgLbraceB();
	afx_msg void OnBtnPassChgRbraceB();
	afx_msg void OnBtnPassChgDot();
	afx_msg void OnBtnPassChgAdd();
	afx_msg void OnBtnPassChgLine();
	afx_msg void OnBtnPassChgDollar();
	afx_msg void OnBtnPassChgSharp();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_PASS_CHANGE_H__6A12D9B4_3633_42E7_B488_B2CABF205C2F__INCLUDED_)
