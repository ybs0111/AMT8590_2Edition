#if !defined(AFX_DIALOG_MENU_H__C5179E92_3334_4DA4_BFC1_8382069FB945__INCLUDED_)
#define AFX_DIALOG_MENU_H__C5179E92_3334_4DA4_BFC1_8382069FB945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Menu.h : header file
//
#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰� 
#include "GradientStatic.h"		// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "ListBoxST.h"			// Į�� ������ ����Ʈ �ڽ� ���� Ŭ���� �߰� 
/////////////////////////////////////////////////////////////////////////////
// CDialog_Menu dialog

class CDialog_Menu : public StandardDialog
{
// Construction
public:
	void OnMenu_ID_Sending(CString str_selected_menu);
	void OnCreate_Menu_Image_List();
	void OnCreate_Menu_ListBox();
	void OnMenu_Lable_Set();
	void OnMenu_Button_Set();
	CDialog_Menu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Menu)
	enum { IDD = IDD_DIALOG_MENU };
	CGradientStatic	m_msg_menu;
	CListBoxST	m_list_menu;
	//}}AFX_DATA

// Attributes
private:
// 	CFont* mp_menu_font;			// ��Ʈ ���� ���� ���� 

	CButton *mp_menu_ok;			// ���� ��ư�� ���� ������ ���� 

	int mn_dialog;

	CImageList mp_menu_image_list;  // �̹��� ����Ʈ ���� 

	CString mp_menu_name;			// ���õ� �޴� ���� ���� ���� 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Menu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Menu)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeListMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MENU_H__C5179E92_3334_4DA4_BFC1_8382069FB945__INCLUDED_)
