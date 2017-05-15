#if !defined(AFX_SCREEN_WAIT_TIME_H__F41690DE_3119_41C4_AEBD_B5B088DAF340__INCLUDED_)
#define AFX_SCREEN_WAIT_TIME_H__F41690DE_3119_41C4_AEBD_B5B088DAF340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Screen_Wait_Time.h : header file
//

#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰� 
#include "Public_Function.h"
#include "GradientStatic.h"		// �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "MacButtons.h"
#include "EXDigitST.h"			// ������ ī���� ���� Ŭ���� �߰� 
#include "FloatST.h"
#include "XpButton.h"			// XP Į�� ��ư Ŭ����

/* ****************************************************************************** */
/* ���� ���� �ε� �� ���� Ŭ����                                                  */
/* ****************************************************************************** */
#include "MyBasicData.h"
/* ****************************************************************************** */

/////////////////////////////////////////////////////////////////////////////
// CScreen_Wait_Time form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScreen_Wait_Time : public CFormView
{
public:
	CScreen_Wait_Time();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScreen_Wait_Time)

// Form Data
public:
	//{{AFX_DATA(CScreen_Wait_Time)
	enum { IDD = IDD_SCREEN_WAIT_TIME };
	CMacButton	m_btn_wait_apply;
	//}}AFX_DATA

// Attributes
public:
// 	CFont* mp_wait_time_font;		// ��Ʈ ���� ���� ����
	TSpread			*m_grid_time;
	
	CMyBasicData     mcls_waittime;	// �⺻ ���� ���� �ε� �� ���� Ŭ����

	GridControlAlg	mp_grid;
	
	int				mn_wait_time_cnt;
	int				mn_on_wait[E_WAIT_MAX][2];
	int				mn_off_wait[E_WAIT_MAX][2];
	int				mn_limit[E_WAIT_MAX][2];

	int				mn_on_used[E_WAIT_MAX];
	int				mn_off_used[E_WAIT_MAX];
	int				mn_limit_used[E_WAIT_MAX];
	
	CString			mstr_wait_time_name[E_WAIT_MAX];
	
	int mn_enable;

// Operations
public:
	void On_Controls_Enable(int nState);
	void OnWaitTime_Init_Time();
	void OnWaitTime_LogFile_Create();
	void OnWaitTime_Data_Apply();
	void OnWaitTime_Data_BackUp();
	int OnWaitTime_Data_Comparison();
	void OnWaitTime_Data_Display();
	void OnWaitTime_Data_Recovery();
	void OnWaitTime_Data_Set();
	void OnChangeValue(int nid, int nrow, int ncol);
	void GridMerge(UINT nID, int srow, int scol, int nrow, int ncol);
	void GridFont(UINT nID, int row, int col, int size);
	void GridData(UINT nID, int row, int col, CString data);
	void GridControl(UINT nID, int type, int row, int col, int pos);
	void GridColor(UINT nID, int row, int col, COLORREF bk, COLORREF tk);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreen_Wait_Time)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreen_Wait_Time();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScreen_Wait_Time)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnWaitApply();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWaitTime_Info_Apply(WPARAM wParam, LPARAM lParam);  // Wait Time ȭ�� ���� ���� ��û �޽���
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREEN_WAIT_TIME_H__F41690DE_3119_41C4_AEBD_B5B088DAF340__INCLUDED_)
