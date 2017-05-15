#if !defined(AFX_DIALOG_KEYPAD_H__4327F976_376C_4AC5_A81C_DCB89D9EE2B3__INCLUDED_)
#define AFX_DIALOG_KEYPAD_H__4327F976_376C_4AC5_A81C_DCB89D9EE2B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_KeyPad.h : header file
//
#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h"		// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "XPGroupBox.h"			// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "EditEx.h"				// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "sxlogfont.h"
#include "MacButtons.h"
#include "EXDigitST.h"			// ������ ī���� ���� Ŭ���� �߰� 
/////////////////////////////////////////////////////////////////////////////
// CDialog_KeyPad dialog

class CDialog_KeyPad : public StandardDialog
{
// Construction
public:
	CDialog_KeyPad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_KeyPad)
	enum { IDD = IDD_DIALOG_KEYPAD };
	CMacButton	m_btn_pad_minus;
	CMacButton	m_btn_pad_reset;
	CGradientStatic	m_msg_old_value;
	CGradientStatic	m_msg_new_value;
	CMacButton	m_btn_pad_dot;
	CMacButton	m_btn_pad_1001;
	CMacButton	m_btn_pad_1000;
	CMacButton	m_btn_pad_101;
	CMacButton	m_btn_pad_100;
	CMacButton	m_btn_pad_11;
	CMacButton	m_btn_pad_10;
	CMacButton	m_btn_pad_9;
	CMacButton	m_btn_pad_8;
	CMacButton	m_btn_pad_7;
	CMacButton	m_btn_pad_6;
	CMacButton	m_btn_pad_5;
	CMacButton	m_btn_pad_4;
	CMacButton	m_btn_pad_3;
	CMacButton	m_btn_pad_2;
	CMacButton	m_btn_pad_1;
	CMacButton	m_btn_pad_0;
	CGradientStatic	m_msg_keypad_limit;
	CXPGroupBox	m_group_keypad;
	CMacButton	m_btn_pad_del;
	CMacButton	m_btn_pad_back;
	//}}AFX_DATA
public:
	CPoint m_ptRef;
	CPoint m_ptRefLeft;
	int m_point;

// Attributes
private:
	CButton *mp_pad_ok, *mp_pad_cancel;		// ��ư�� ���� ������ ����
// 	CFont* mp_pad_font;						// ��Ʈ ���� ���� ���� 

	int mn_dialog;							// ���̾�αװ� �� �ִ��� Ȯ���Ѵ�.
											// ��� ���� ��ư�� �����ϱ� ����.
	BOOL m_bFirst;

	// ******************************************************************************
	// Ű�е� ���� ���� ����                                                         
	// ******************************************************************************
	CString mstr_old_val;	// ������ Ű�е� ���� ���������� �����ϱ� ���� ���� 
	CString mstr_new_val;	// ���� �Էµ� Ű�е� ���� ���������� �����ϱ� ���� ���� 

	long ml_cnt_chk;		// �Էµ� Ű�е� ���� ���������� �����Ͽ� �����ϱ� ���� ����
	double md_cnt_chk;		// �Էµ� Ű�е� ���� ���������� �����Ͽ� �����ϱ� ���� ����
	double md_old_cnt_chk;		// �Էµ� Ű�е� ���� ���������� �����Ͽ� �����ϱ� ���� ����

	char buffer[12]; 
	int mn_cnt;				// �Էµ� ������ �� ���� ���� ���� ���� 
	int mn_pos;				// '-'���� �Է��� ��� '-' ���� ��ư�� ���������� ���� ���� ���� 
	int mn_dot_pos;			// '.'���� �Է��� ��� '.' ���� ��ư�� ���������� ���� ���� ���� 

	BOOL b_limit_value;

	int mn_minus;

	CEditEx  m_edit_keypad_title;

	CEXDigitST  mp_dgt_old_val;		// ������ ī���� Ŭ���� ���� ����
	CEXDigitST  mp_dgt_val;			// ������ ī���� Ŭ���� ���� ����
	// ******************************************************************************

public:
	CString GetNumEditString_I(int nMin, int nMax, int nPrev, CString strText, CRect rRect = (0,0,0,0));
	CString GetNumEditString_D(double dMin, double dMax, double dPrev, CString strText, CRect rRect = (0,0,0,0));
	void OnKeyPad_CountData_Set();
	void OnKeyPad_Button_Set();
	void OnKeyPad_Label_Set();
	void OnKeyPad_GroupBox_Set();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_KeyPad)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_KeyPad)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnBtnPadBack();
	afx_msg void OnBtnPadDel();
	afx_msg void OnBtnPad0();
	afx_msg void OnBtnPad1();
	afx_msg void OnBtnPad2();
	afx_msg void OnBtnPad3();
	afx_msg void OnBtnPad4();
	afx_msg void OnBtnPad5();
	afx_msg void OnBtnPad6();
	afx_msg void OnBtnPad7();
	afx_msg void OnBtnPad8();
	afx_msg void OnBtnPad9();
	afx_msg void OnBtnPad10();
	afx_msg void OnBtnPad11();
	afx_msg void OnBtnPad100();
	afx_msg void OnBtnPad101();
	afx_msg void OnBtnPad1000();
	afx_msg void OnBtnPad1001();
	afx_msg void OnPaint();
	afx_msg void OnBtnPadDot();
	afx_msg void OnBtnPadReset();
	afx_msg void OnBtnPadMinus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CDialog_KeyPad KeyPad;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_KEYPAD_H__4327F976_376C_4AC5_A81C_DCB89D9EE2B3__INCLUDED_)
