#if !defined(AFX_DIALOG_SELECT_H__5434031F_5D9B_4F24_B635_7054AA5A324D__INCLUDED_)
#define AFX_DIALOG_SELECT_H__5434031F_5D9B_4F24_B635_7054AA5A324D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Select.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "MacButtons.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Select dialog

class CDialog_Select : public StandardDialog
{
// Construction
public:
	void OnSelect_Button_Set();
	void OnSelect_Lable_Set();
	CDialog_Select(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Select)
	enum { IDD = IDD_DIALOG_SELECT };
	CGradientStatic	m_select_message;
	//}}AFX_DATA

// Attributes
private:
	CButton *mp_select_yes, *mp_select_no, *mp_select_exit;	// ��ư�� ���� ������ ����
// 	CFont* mp_select_font;					// ��Ʈ ���� ���� ���� 

	int mn_dialog;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Select)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Select)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_SELECT_H__5434031F_5D9B_4F24_B635_7054AA5A324D__INCLUDED_)
