#if !defined(AFX_DIALOG_IDBUFFER_INFO_H__78EB9629_404E_4CE0_88A0_62F6BD1B8A75__INCLUDED_)
#define AFX_DIALOG_IDBUFFER_INFO_H__78EB9629_404E_4CE0_88A0_62F6BD1B8A75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_IDBuffer_Info.h : header file
//
#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰�
#include "Public_Function.h"	// ���� �Լ� ���� Ŭ���� �߰�
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "editEx.h"				// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "BtnST.h"          // Į�� ��ư ���� Ŭ���� �߰� 
#include "XPGroupBox.h"			// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "SxLogFont.h"
#include "MacButtons.h"
#include "ListBoxST.h"			// Į�� ������ ����Ʈ �ڽ� Ŭ���� 
#include "xpbutton.h"			// XP Į�� ��ư Ŭ����
#include "EXDigitST.h"			// ������ ī���� Ŭ����
#include "GradientStatic.h"		// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "FloatST.h"
#include "FastechPublic_IO.h"		// Fastech ���� ���� Class
#include "LedButton.h"			// LED ��ư Ŭ����

/////////////////////////////////////////////////////////////////////////////
// CDialog_IDBuffer_Info dialog

class CDialog_IDBuffer_Info : public StandardDialog
{
// Construction
public:
	CDialog_IDBuffer_Info(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_IDBuffer_Info)
	enum { IDD = IDD_DIALOG_IDBUFFER_INFO };
	CXPGroupBox	m_group_idbuffer_info;
	CXPGroupBox	m_group_idbuffer_info2;
	CXPGroupBox	m_group_run_step;

	CGradientStatic	m_msg_run_step_1;
	CGradientStatic	m_msg_run_step_2;
	CGradientStatic	m_msg_run_step_3;
	CGradientStatic	m_msg_run_step_4;
	CGradientStatic	m_msg_run_step_5;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
private:
	CEditEx m_edit_id_buffer_info_left_1;
	CEditEx m_edit_id_buffer_info_left_2;
	CEditEx m_edit_id_buffer_info_left_3;
	CEditEx m_edit_id_buffer_info_left_4;
	CEditEx m_edit_id_buffer_info_left_5;
	CEditEx m_edit_id_buffer_info_left_6;
	CEditEx m_edit_id_buffer_info_left_7;
	CEditEx m_edit_id_buffer_info_left_8;
	CEditEx m_edit_id_buffer_info_left_9;
	CEditEx m_edit_id_buffer_info_left_10;
	CEditEx m_edit_id_buffer_info_left_11;
	
	CEditEx m_edit_id_buffer_info_right_1;
	CEditEx m_edit_id_buffer_info_right_2;
	CEditEx m_edit_id_buffer_info_right_3;
	CEditEx m_edit_id_buffer_info_right_4;
	CEditEx m_edit_id_buffer_info_right_5;
	CEditEx m_edit_id_buffer_info_right_6;
	CEditEx m_edit_id_buffer_info_right_7;
	CEditEx m_edit_id_buffer_info_right_8;
	CEditEx m_edit_id_buffer_info_right_9;
	CEditEx m_edit_id_buffer_info_right_10;
	CEditEx m_edit_id_buffer_info_right_11;

	CEditEx m_edit_id_buffer_info_title_1;
	CEditEx m_edit_id_buffer_info_title_2;

	CEditEx m_edit_run_step_1;
	CEditEx m_edit_run_step_2;
	CEditEx m_edit_run_step_3;
	CEditEx m_edit_run_step_4;
	

	CString mstr_id_buffer_info_old[20][2];
	CString mstr_id_buffer_info_new[20][2];

	CString mstr_id_buffer_info_title_1;
	CString mstr_id_buffer_info_title_2;

	int mn_dialog;

public:
	void OnIDBuffer_EditBox_Set();
	void OnIDBuffer_GroupBox_Set();
	void OnIDBuffer_Label_Set();

	void OnIDBuffer_Input_Info(int nPos);
	void OnBTMIDBuffer_Input_Info(int nPos);

	void OnIDBuffer_Output_Info(int nPos);
	void OnBTMIDBuffer_Output_Info(int nPos);
	
	void OnRun_Step_Input_Info(int nPos);
	void OnRun_Step_Output_Info(int nPos);
	
	void OnIDBuffer_Show_Enable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_IDBuffer_Info)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_IDBuffer_Info)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnApply();
	afx_msg void OnBtnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CDialog_IDBuffer_Info IDBuffer_Info;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_IDBUFFER_INFO_H__78EB9629_404E_4CE0_88A0_62F6BD1B8A75__INCLUDED_)
