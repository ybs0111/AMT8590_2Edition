#if !defined(AFX_DIALOG_MOTOR_PART_H__D92C8009_9331_4229_A389_61B449EEFB6B__INCLUDED_)
#define AFX_DIALOG_MOTOR_PART_H__D92C8009_9331_4229_A389_61B449EEFB6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Motor_Part.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Motor_Part dialog
#include "BtnST.h"          // Į�� ��ư ���� Ŭ���� �߰�  
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "EditEx.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "EXDigitST.h"		// ������ ī���� Ŭ����
#include "LedButton.h"      // LED ��ư Ŭ����
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "SxLogFont.h"
#include "MacButtons.h"
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "XpButton.h"		// XP Į�� ��ư Ŭ����
#include "Dialog_Message.h"
#include "FastechPublic_IO.h"		// Fastech ���� ���� Class
#include "ComizoaPublic.h"
#include "GridControlAlg.h"
#include "Digit.h"
#include "Dialog_Motor_Axis_Tab.h"


class CDialog_Motor_Part : public CDialog
{
public:
// 	CFont			* m_p_font;
	CPoint			m_cp_coord;

	int				m_n_part;
	int				m_n_part_axis_cnt;
	int				m_n_part_axis[10];
	int				m_n_axis_pos_num[10];
	int				m_n_axis_minus_el[10];
	int				m_n_axis_plus_el[10];
	int				m_n_axis_home[10];
	int				m_n_axis_direction[10];
	int				m_n_axis_account[10];

	CString			m_str_part_name;
	CString			m_str_part_axis_name[10];
	CString			m_str_axis_pos_name[10][20];
	CString			m_str_axis_pos_info[10][20];

	int				mn_tab_number;

// Construction
public:
	void OnMotorPart_Select_Axis(int nAxis);
	void OnMotor_Part_Change(int nPart);
	void Init_Button();
	void Init_Group();
	BOOL Create();
	CDialog_Motor_Part(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Motor_Part)
	enum { IDD = IDD_MOTOR_PART };
	CButtonST	m_chk_axis_12;
	CButtonST	m_chk_axis_11;
	CButtonST	m_btn_io;
	CDialog_Motor_Axis_Tab	m_tab_motor_part;
	CButtonST	m_chk_axis_9;
	CButtonST	m_chk_axis_8;
	CButtonST	m_chk_axis_7;
	CButtonST	m_chk_axis_6;
	CButtonST	m_chk_axis_5;
	CButtonST	m_chk_axis_4;
	CButtonST	m_chk_axis_3;
	CButtonST	m_chk_axis_2;
	CButtonST	m_chk_axis_10;
	CButtonST	m_chk_axis_1;
	CXPGroupBox	m_group_part;
	CButtonST	m_btn_exit;
	CButtonST	m_btn_manual;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Motor_Part)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Motor_Part)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExit();
	afx_msg void OnChkAxis1();
	afx_msg void OnChkAxis10();
	afx_msg void OnChkAxis2();
	afx_msg void OnChkAxis3();
	afx_msg void OnChkAxis4();
	afx_msg void OnChkAxis5();
	afx_msg void OnChkAxis6();
	afx_msg void OnChkAxis7();
	afx_msg void OnChkAxis8();
	afx_msg void OnChkAxis9();
	afx_msg void OnBtnIo();
	afx_msg void OnChkAxis12();
	afx_msg void OnChkAxis11();
	afx_msg void OnBtnManual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MOTOR_PART_H__D92C8009_9331_4229_A389_61B449EEFB6B__INCLUDED_)
