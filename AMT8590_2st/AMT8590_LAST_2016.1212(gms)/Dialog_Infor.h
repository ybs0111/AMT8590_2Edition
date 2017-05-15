#if !defined(AFX_DIALOG_INFOR_H__668C2594_B92B_459E_9685_B1055B476DDB__INCLUDED_)
#define AFX_DIALOG_INFOR_H__668C2594_B92B_459E_9685_B1055B476DDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Infor.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
/////////////////////////////////////////////////////////////////////////////
// CDialog_Infor dialog

class CDialog_Infor : public StandardDialog
{
// Construction
public:
	void OnInfo_Lable_Set();
	void OnInfo_Button_Set();
	CDialog_Infor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Infor)
	enum { IDD = IDD_DIALOG_INFOR };
	CGradientStatic	m_info_message;
	//}}AFX_DATA

// Attributes
private:
	CButton *mp_info_ok, *mp_info_cancel;	// ��ư�� ���� ������ ����
// 	CFont* mp_info_font;					// ��Ʈ ���� ���� ���� 

	int mn_dialog;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Infor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Infor)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_INFOR_H__668C2594_B92B_459E_9685_B1055B476DDB__INCLUDED_)
