#if !defined(AFX_SCREEN_ADMIN_H__EB1175A4_638C_47E2_B09B_2AB54A977A29__INCLUDED_)
#define AFX_SCREEN_ADMIN_H__EB1175A4_638C_47E2_B09B_2AB54A977A29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Screen_Admin.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "Public_Function.h"
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "editex.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "BtnST.h"          // Į�� ��ư ���� Ŭ���� �߰� 
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "sxlogfont.h"
#include "MacButtons.h"
#include "ListBoxST.h"      // Į�� ������ ����Ʈ �ڽ� Ŭ����
#include "xpbutton.h"		// XP Į�� ��ư Ŭ����
#include "EXDigitST.h"		// ������ ī���� Ŭ����
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "FloatST.h"
#include "LedButton.h"				// LED ��ư ���� Ŭ���� �߰� 
#include "Digit.h"

/////////////////////////////////////////////////////////////////////////////
// CScreen_Admin form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScreen_Admin : public CFormView
{
public:
	CScreen_Admin();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScreen_Admin)

// Form Data
public:
	//{{AFX_DATA(CScreen_Admin)
	enum { IDD = IDD_SCREEN_ADMIN };
	CButton	m_chk_auto_serial_create;
	CButton	m_chk_only_flow;
	CButton	m_chk_dryrun_density;
	CButton	m_chk_without_btm_8580s;
	CButton	m_chk_only_density;
	CButton	m_chk_only_bcr1;
	CButton	m_chk_without_top_vision;
	CButton	m_chk_without_smema_bcr_read;
	CButton	m_chk_without_network;
	CButton	m_chk_without_idbuffer;
	CButton	m_chk_without_density_rbt;
	CButton	m_chk_without_bcr2_rbt;
	CButton	m_chk_without_bcr1_rbt;
	CButton	m_chk_without_smema_8580s;
	CButton	m_chk_virtual_buffer;
	CButton	m_chk_virtual_supply;
	CButton	m_chk_Virtual;
	//}}AFX_DATA

// Attributes
public:	



// Operations
public:
	void OnAdmin_Data_Set();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreen_Admin)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreen_Admin();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void GridColor(UINT nID, int row, int col, COLORREF bk, COLORREF tk);
	void GridControl(UINT nID, int type, int row, int col, int pos);
	void GridData(UINT nID, int row, int col, CString data);
	void GridFont(UINT nID, int row, int col, int size);
	void GridMerge(UINT nID, int srow, int scol, int nrow, int ncol);
	CString GetGridData( UINT nID, int row, int col );

	// Generated message map functions
	//{{AFX_MSG(CScreen_Admin)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnFileEditor();
	afx_msg void OnChkVirtualSupply();
	afx_msg void OnChkWithBuffer();
	afx_msg void OnChkWithoutSmemaBarcodeRead();
	afx_msg void OnChkWithoutSmema8580mc();
	afx_msg void OnChkWithoutNetwork();
	afx_msg void OnChkWithoutIdbuffer();
	afx_msg void OnChkWithoutDensity();
	afx_msg void OnChkWithoutBcr1();
	afx_msg void OnChkWithoutBcr2();
	afx_msg void OnChkWithoutTopVision();
	afx_msg void OnChkOnlyBcr1();
	afx_msg void OnChkOnlyDensity();
	afx_msg void OnChkWithoutBtm8580s();
	afx_msg void OnChkDryrunDensity();
	afx_msg void OnChkVirtual();
	afx_msg void OnChkOnlyFlow();
	afx_msg void OnChkAutoSerial();
	afx_msg void OnBtnFileServer();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREEN_ADMIN_H__EB1175A4_638C_47E2_B09B_2AB54A977A29__INCLUDED_)
