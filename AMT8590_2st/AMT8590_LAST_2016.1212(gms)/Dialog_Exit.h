#if !defined(AFX_DIALOG_EXIT_H__17BF0EAC_CA69_4650_8981_C624963F81C6__INCLUDED_)
#define AFX_DIALOG_EXIT_H__17BF0EAC_CA69_4650_8981_C624963F81C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Exit.h : header file
//

#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h"	// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 

/////////////////////////////////////////////////////////////////////////////
// CDialog_Exit dialog

class CDialog_Exit : public StandardDialog
{
// Construction
public:
	void OnExit_Lable_Set();
	void OnExit_Button_Set();
	CDialog_Exit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Exit)
	enum { IDD = IDD_DIALOG_EXIT };
	CGradientStatic	m_msg_exit;
	//}}AFX_DATA

// Attributes
private:
	CButton *mp_btn_ok, *mp_btn_cancel, *mp_btn_saveok;  // ��ư�� ���� ������ ����
// 	CFont* mp_exit_font;  // ��Ʈ ���� ���� ���� 

	int mn_dialog;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Exit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Exit)
	afx_msg void OnSaveok();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_EXIT_H__17BF0EAC_CA69_4650_8981_C624963F81C6__INCLUDED_)
