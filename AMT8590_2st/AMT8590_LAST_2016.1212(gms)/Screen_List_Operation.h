#if !defined(AFX_SCREEN_LIST_OPERATION_H__F7709F14_7D5E_4FD2_B238_20A5C1D78821__INCLUDED_)
#define AFX_SCREEN_LIST_OPERATION_H__F7709F14_7D5E_4FD2_B238_20A5C1D78821__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Screen_List_Operation.h : header file
//
#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰�
#include "Public_Function.h"	// ���� �Լ� ���� Ŭ���� �߰�
#include "EditEx.h"				// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "LedButton.h"			// LED ��ư Ŭ����
#include "XPGroupBox.h"			// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "SxLogFont.h"
#include "ListBoxST.h"			// Į�� ������ ����Ʈ �ڽ� Ŭ���� 
#include "MacButtons.h"
#include "GradientStatic.h"		// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
/////////////////////////////////////////////////////////////////////////////
// CScreen_List_Operation form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScreen_List_Operation : public CFormView
{
public:
	CScreen_List_Operation();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScreen_List_Operation)

// Form Data
public:
	//{{AFX_DATA(CScreen_List_Operation)
	enum { IDD = IDD_SCREEN_LIST_OPERATION };
	CLedButton	m_radio_work;
	CLedButton	m_radio_alarm;
	CLedButton	m_radio_operation;
	CLedButton	m_radio_machine;
	CLedButton	m_radio_interface;
	CLedButton	m_radio_barcode;
	CGradientStatic	m_msg_operation_file_name;
	CGradientStatic	m_msg_operation_file;
	CMonthCalCtrl	m_monthcal_operation;
	CListBoxST	m_list_operation_file;
	CXPGroupBox	m_group_operation_type;
	CXPGroupBox	m_group_operation_list;
	CMacButton	m_btn_operation_file_refresh;
	CMacButton	m_btn_operation_file_del;
	//}}AFX_DATA

// Attributes
public:
// 	CFont* mp_operation_list_font;			// ��Ʈ ���� ���� ���� 

	CImageList mp_operation_image_list;		// �̹��� ����Ʈ ���� 

	CString mstr_operation_file_name;		// ���õ� ���� �̸� ���� ���� ���� 

	/* ************************************************************************** */
	/* Į�� ����Ʈ �ڽ� Ŭ���� ���� ����                                          */
	/* ************************************************************************** */
	CEditEx  m_edit_operation_content;
	/* ************************************************************************** */
	
	/* ************************************************************************** */
	/* �˶� ����Ʈ ���� ��� �� ���� ���� ���� ���� Ŭ���� ���� ����              */
	/* ************************************************************************** */
	int mn_type_select;					// ������ ã�� ��� ���� ���� ���� 

	CString mstr_default_path;			// �ʱ⿡ ���� �ε��� ���� ���� ���� ���� 
	CString mstr_full_path;				// ���� �ε��� [����]+[���ϸ�]+[Ȯ����] ���� ���� ���� 

	CString mstr_selected_Date;			// ���� ������ ��¥ ���� ���� ���� ���� (��+��+��/��+��/��+��+��)

	CString mstr_temp_file;				// ���� �̸� �ӽ� ���� ���� 
	CString mstr_file_full_name;		// Save as ��ų�� ����Ѵ�. 2K4/08/16/ViboX
	/* ************************************************************************** */

// Operations
public:
	void OnOperation_List_Display_Selected_Day();
	void OnOperation_List_Reset_AllItem();
	int OnOperation_List_Selected_File_Name_Check();
	void OnOperation_List_Selected_File_Load(CString str_folder, CString str_file);
	BOOL AddItem(int n_index, WIN32_FIND_DATA *pfd);
	void OnOperation_List_Full_Path_Set(int n_selected);
	int OnOperation_List_Init_List(LPCTSTR pszPath);
	void OnOperation_List_Create_ImageList();
	void OnOperation_List_State_Change(int n_state);
	void OnOperation_List_RadioButton_Set();
	void OnOperation_List_EditBox_Set();
	void OnOperation_List_Lable_Set();
	void OnOperation_List_GroupBox_Set();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreen_List_Operation)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreen_List_Operation();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScreen_List_Operation)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeListOperationFile();
	afx_msg void OnSelectMonthcalOperation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioOperation();
	afx_msg void OnRadioInterface();
	afx_msg void OnRadioMachine();
	afx_msg void OnRadioBarcode();
	afx_msg void OnBtnOperationFileDel();
	afx_msg void OnBtnOperationFileRefresh();
	afx_msg void OnRadioAlarm();
	afx_msg void OnRadioWork();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREEN_LIST_OPERATION_H__F7709F14_7D5E_4FD2_B238_20A5C1D78821__INCLUDED_)
