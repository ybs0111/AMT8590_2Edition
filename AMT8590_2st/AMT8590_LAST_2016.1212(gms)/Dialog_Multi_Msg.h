#if !defined(AFX_DIALOG_MULTI_MSG_H__6FD2B577_A8DC_44D0_AB1D_342A1CE43100__INCLUDED_)
#define AFX_DIALOG_MULTI_MSG_H__6FD2B577_A8DC_44D0_AB1D_342A1CE43100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Multi_Msg.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 

#include "Public_Function.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Multi_Msg dialog

class CDialog_Multi_Msg : public StandardDialog
{
// Construction
public:
	void OnMMsg_Button_Set();
	void OnMMsg_Lable_Set();
	void OnMMsg_Picture_Set();
	CDialog_Multi_Msg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Multi_Msg)
	enum { IDD = IDD_DIALOG_MULTI_MSG };
	CNewLabel	m_msg_m_message;
	//}}AFX_DATA

// Attributes
private:
// 	CFont* mp_m_msg_font;  // ��Ʈ ���� ���� ���� 
	CButton *mp_m_msg_ok;  // ��ư�� ���� ������ ����
	int mn_dialog;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Multi_Msg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Multi_Msg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MULTI_MSG_H__6FD2B577_A8DC_44D0_AB1D_342A1CE43100__INCLUDED_)
