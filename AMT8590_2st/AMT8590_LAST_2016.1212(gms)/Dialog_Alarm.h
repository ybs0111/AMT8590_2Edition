#if !defined(AFX_DIALOG_ALARM_H__6FB58774_188C_4576_B791_966B99A73E75__INCLUDED_)
#define AFX_DIALOG_ALARM_H__6FB58774_188C_4576_B791_966B99A73E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Alarm.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰�
#include "Public_Function.h"

#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "EditEx.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "SxLogFont.h"
#include "XpButton.h"		// XP Į�� ��ư Ŭ����
#include "ListBoxST.h"      // Į�� ������ ����Ʈ �ڽ� Ŭ���� 
#include "MacButtons.h"
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "BmpImageST.h"		// �˶� ��Ʈ�� �ε� Ŭ���� �߰� 
#include "PictureEx.h"		// GIF ���� �ε� Ŭ���� �߰� 
#include "MatrixStatic.h"	// LCD ���� ���� Ŭ���� �߰� 
#include "MyJamData.h"		// �˶� ��� ���� �ε� �� �˶� �޽��� ���� Ŭ����
#include "FloatST.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Alarm dialog

class CDialog_Alarm : public CDialog
{
// Construction
public:
	CDialog_Alarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Alarm)
	enum { IDD = IDD_DIALOG_ALARM };
	CFloatST	m_msg_alarm_msg;
	CFloatST	m_msg_alarm_time;
	CNewLabel	m_data_alarm_time;
	CMatrixStatic	m_msg_lot_end;
	CFloatST	m_msg_alarm_type;
	CFloatST	m_msg_alarm_title;
	CFloatST	m_msg_alarm_repare;
	CFloatST	m_msg_alarm_code;
	CBmpImageST	m_image_alarm;
	CXPGroupBox	m_group_prev_alarm;
	CXPGroupBox	m_group_alarm_info;
	CPictureEx	m_gif_alarm;
	CNewLabel	m_data_alarm_type;
	CNewLabel	m_data_alarm_code;
	CMacButton	m_btn_prev_alarm_10;
	CMacButton	m_btn_prev_alarm_9;
	CMacButton	m_btn_prev_alarm_8;
	CMacButton	m_btn_prev_alarm_7;
	CMacButton	m_btn_prev_alarm_6;
	CMacButton	m_btn_prev_alarm_5;
	CMacButton	m_btn_prev_alarm_4;
	CMacButton	m_btn_prev_alarm_3;
	CMacButton	m_btn_prev_alarm_2;
	CMacButton	m_btn_prev_alarm_1;
	CMacButton	m_btn_buzzer_off;
	CXPButton	m_btn_alarm_ok;
	//}}AFX_DATA

// Attributes
private:
// 	CFont* mp_alarm_font;  // ��Ʈ ���� ���� ���� 

	// **************************************************************************
	// �˶� ��� ���� �� ��� ���� ���� Ŭ���� ���� ����                         
	// **************************************************************************
	CMyJamData   mcls_alarm_load;
	// **************************************************************************

	// **************************************************************************
	// Į�� ����Ʈ �ڽ� Ŭ���� ���� ����                                         
	// **************************************************************************
	CEditEx   m_edit_alarm_title;
	CEditEx   m_edit_alarm_repare;
	CEditEx   m_edit_alarm_msg;
	// **************************************************************************

	// **************************************************************************
	// �˶� ��� ���� ����Ǿ� �ִ� ���� ���� ���� ���� ����                     
	// **************************************************************************
	CString mstr_data_file;		// �˶� ��� ���� ���� ����� ���ϸ� ���� ���� 
	CString mstr_action_file;	// �˶� ��ġ ���� ���� ����� ���ϸ� ���� ���� 
	// **************************************************************************

// Operation
public:
	void OnAlarm_OcurrDate_Display(int nPos);
	void OnAlarm_PrevAlarm_Display(int n_alarm_pos);
	CString OnAlarm_PrevAlarm_Check(int n_cnt);
	void OnAlarm_PrevList_Caption_Set(int n_cnt);
	void OnAlarm_PrevButton_List_Set(int n_cnt);
	void OnAlarm_PrevList_Set();
	void OnAlarm_Controls_Show(int n_state);
	void OnAlarm_Data_Display(int n_alarm_state);
	void OnAlarm_Image_Style_Set(CString strPath);
	int OnAlarm_Data_Loading();
	void OnAlarm_Default_Data_Load();
	void OnAlarm_EditBox_Set();
	void OnAlarm_LCD_Digital_Set();
	void OnAlarm_Lable_Set();
	void OnAlarm_GroupBox_Set();
	void OnAlarm_Picture_Set();

private:
	CString m_pstrJamCode[10];
	int n_last_alarm;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Alarm)
	public:
	virtual BOOL Create(CWnd* pParentWnd);				// ��޸��� ��ȭ ���� ���� �Լ� ���� 
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Alarm)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();					// �˶� ȭ�� ESC Ű ���� ��� ����Ͽ� �Լ� �߰� 
	afx_msg void OnBtnBuzzerOff();
	afx_msg void OnBtnPrevAlarm1();
	afx_msg void OnBtnPrevAlarm2();
	afx_msg void OnBtnPrevAlarm3();
	afx_msg void OnBtnPrevAlarm4();
	afx_msg void OnBtnPrevAlarm5();
	afx_msg void OnBtnPrevAlarm6();
	afx_msg void OnBtnPrevAlarm7();
	afx_msg void OnBtnPrevAlarm8();
	afx_msg void OnBtnPrevAlarm9();
	afx_msg void OnBtnPrevAlarm10();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_ALARM_H__6FB58774_188C_4576_B791_966B99A73E75__INCLUDED_)
