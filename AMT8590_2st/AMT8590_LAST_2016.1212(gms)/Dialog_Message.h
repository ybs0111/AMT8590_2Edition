#if !defined(AFX_DIALOG_MESSAGE_H__5215CFC6_6A71_4E50_BEC0_1122A9459B0A__INCLUDED_)
#define AFX_DIALOG_MESSAGE_H__5215CFC6_6A71_4E50_BEC0_1122A9459B0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Message.h : header file
//

#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 

#include "Public_Function.h"

/////////////////////////////////////////////////////////////////////////////
// CDialog_Message dialog

class CDialog_Message : public StandardDialog
{
// Construction
public:
	CDialog_Message(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Message)
	enum { IDD = IDD_DIALOG_MESSAGE };
	CGradientStatic	m_msg_message;
	//}}AFX_DATA

// Attributes
private:
// 	CFont* mp_msg_font;  // ��Ʈ ���� ���� ���� 
	CButton *mp_msg_ok;  // ��ư�� ���� ������ ����
	int mn_dialog;

// Operations
public:
	void OnMsg_Lable_Set();
	void OnMsg_Button_Set();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Message)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Message)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MESSAGE_H__5215CFC6_6A71_4E50_BEC0_1122A9459B0A__INCLUDED_)
