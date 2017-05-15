#if !defined(AFX_DIALOG_DATA_MODULE_H__0C01380B_6F48_4405_B724_DD2D1FB95F2B__INCLUDED_)
#define AFX_DIALOG_DATA_MODULE_H__0C01380B_6F48_4405_B724_DD2D1FB95F2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Data_Module.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Data_Module dialog

enum ENUM_DATA_MODULE_SELECTE
{
	EDMS_NONE,
	EDMS_DENSITY,
	EDMS_BACR1,
	EDMS_BACR2,
	EDMS_TOP,
	EDMS_UNLOAD,
	EDMS_DENRBT,
	EDMS_BCR1RBT,
	EDMS_BCR2RBT,
	EDMS_TOPRBT,
	EDMS_ULDRBT,
	EDMS_TRAY1,
	EDMS_TRAY2,
	EDMS_TRAY3,
	EDMS_TRAY4,
	EDMS_TRAY5,
	EDMS_TRAY6,
	EDMS_TRAY7,
	EDMS_TRAY8,
	EDMS_TRAY9,
	EDMS_TRAY10,
	EDMS_TRAY11,
	EDMS_TRAY12,

};

class CDialog_Data_Module : public StandardDialog
{
// Construction
public:
	CDialog_Data_Module(CWnd* pParent = NULL);   // standard constructor
	CImageList			*m_pImagelist;
// Dialog Data
	//{{AFX_DATA(CDialog_Data_Module)
	enum { IDD = IDD_DIALOG_DATA_MODULE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Data_Module)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Grid
	void GridColor(UINT nID, int row, int col, COLORREF bk, COLORREF tk);
	void GridControl(UINT nID, int type, int row, int col, int pos);
	void GridData(UINT nID, int row, int col, CString data);
	void GridFont(UINT nID, int row, int col, int size);
	void GridMerge(UINT nID, int srow, int scol, int nrow, int ncol);
	CString GetGridData( UINT nID, int row, int col );
	void OnInitTree();
	void OnInit_TestSite();
	void OnInit_RobotPicker();
	void OnInit_ModuleInfo();

	void OnDisplay_TestSite();
	void OnDisplay_Robot();
	void OnDisplay_ModuleInfo();

	// Generated message map functions
	//{{AFX_MSG(CDialog_Data_Module)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnModuleSet();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()


protected:
	//2013,0715
	EMODULE_STATE m_strFirstS;
	int m_nNumMax;
	CString m_strCombo;


	ENUM_DATA_MODULE_SELECTE m_selected;

	int m_nSelected_ModuleIdx;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_DATA_MODULE_H__0C01380B_6F48_4405_B724_DD2D1FB95F2B__INCLUDED_)
