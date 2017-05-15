#if !defined(AFX_DIALOG_BTM_IDBUFFER_INFO_H__F3361FA8_C977_426D_86A2_019420F6E38E__INCLUDED_)
#define AFX_DIALOG_BTM_IDBUFFER_INFO_H__F3361FA8_C977_426D_86A2_019420F6E38E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Btm_IDBuffer_Info.h : header file
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
// CDialog_Btm_IDBuffer_Info dialog

class CDialog_Btm_IDBuffer_Info : public StandardDialog
{
// Construction
private:
	CEditEx m_edit_btm_id_buffer_info_left_1;
	CEditEx m_edit_btm_id_buffer_info_left_2;
	CEditEx m_edit_btm_id_buffer_info_left_3;
	CEditEx m_edit_btm_id_buffer_info_left_4;
	CEditEx m_edit_btm_id_buffer_info_left_5;
	CEditEx m_edit_btm_id_buffer_info_left_6;
	CEditEx m_edit_btm_id_buffer_info_left_7;
	CEditEx m_edit_btm_id_buffer_info_left_8;
	CEditEx m_edit_btm_id_buffer_info_left_9;
	CEditEx m_edit_btm_id_buffer_info_left_10;
	CEditEx m_edit_btm_id_buffer_info_left_11;
	
	CEditEx m_edit_btm_id_buffer_info_right_1;
	CEditEx m_edit_btm_id_buffer_info_right_2;
	CEditEx m_edit_btm_id_buffer_info_right_3;
	CEditEx m_edit_btm_id_buffer_info_right_4;
	CEditEx m_edit_btm_id_buffer_info_right_5;
	CEditEx m_edit_btm_id_buffer_info_right_6;
	CEditEx m_edit_btm_id_buffer_info_right_7;
	CEditEx m_edit_btm_id_buffer_info_right_8;
	CEditEx m_edit_btm_id_buffer_info_right_9;
	CEditEx m_edit_btm_id_buffer_info_right_10;
	CEditEx m_edit_btm_id_buffer_info_right_11;
	
	CEditEx m_edit_btm_id_buffer_info_title_1;
	CEditEx m_edit_btm_id_buffer_info_title_2;
	
	CString mstr_btm_id_buffer_info_old[20][2];
	CString mstr_btm_id_buffer_info_new[20][2];
	
	CString mstr_btm_id_buffer_info_title_1;
	CString mstr_btm_id_buffer_info_title_2;
	
	
	int mn_btm_dialog;
public:
	CDialog_Btm_IDBuffer_Info(CWnd* pParent = NULL);   // standard constructor
	void OnIDBuffer_Btm_EditBox_Set();
	void OnIDBuffer_Btm_GroupBox_Set();
	
	void OnBTMIDBuffer_Input_Info(int nPos);
	void OnBTMIDBuffer_Output_Info(int nPos);
// Dialog Data
	//{{AFX_DATA(CDialog_Btm_IDBuffer_Info)
	enum { IDD = IDD_DIALOG_IDBUFFER_BTM_INFO };
	CXPGroupBox	m_group_btm_idbuffer_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Btm_IDBuffer_Info)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Btm_IDBuffer_Info)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnApply();
	afx_msg void OnBtnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CDialog_Btm_IDBuffer_Info BTM_IDBuffer_Info;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_BTM_IDBUFFER_INFO_H__F3361FA8_C977_426D_86A2_019420F6E38E__INCLUDED_)
