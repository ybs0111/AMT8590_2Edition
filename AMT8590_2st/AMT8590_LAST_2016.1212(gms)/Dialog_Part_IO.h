#if !defined(AFX_DIALOG_PART_IO_H__0D376FD6_2F3D_4E27_8347_BDB5B857F43E__INCLUDED_)
#define AFX_DIALOG_PART_IO_H__0D376FD6_2F3D_4E27_8347_BDB5B857F43E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Part_IO.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Part_IO dialog
#include "BtnST.h"          // Į�� ��ư ���� Ŭ���� �߰�  
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "EditEx.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "EXDigitST.h"		// ������ ī���� Ŭ����
#include "LedButton.h"      // LED ��ư Ŭ����
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "SxLogFont.h"
#include "MacButtons.h"
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "XpButton.h"		// XP Į�� ��ư Ŭ����
#include "Dialog_Message.h"
#include "FastechPublic_IO.h"		// Fastech ���� ���� Class
#include "ComizoaPublic.h"
#include "GridControlAlg.h"
#include "Digit.h"

class CDialog_Part_IO : public CDialog
{
public:
// 	CFont			*m_p_font;
	CPoint			m_cp_coord;
	GridControlAlg m_p_grid;

	TSpread			*m_grid_input;
	TSpread			*m_grid_output;

	int				m_n_part;
	int				m_n_in[100];
	int				m_n_in_port[100];
	int				m_n_in_num[100];
	int				m_n_out[100];
	int				m_n_out_port[100];
	int				m_n_out_num[100];
	int				m_n_in_cnt;
	int				m_n_out_cnt;

	CString			m_str_in[100];
	CString			m_str_out[100];
// Construction
public:
	BOOL Create();
	void OnOutputCheck();
	void OnInputCheck();
	void Init_Output();
	void Init_Input();
	void Init_Grid_IO();
	void Init_Group();
	void Init_Button();
	CDialog_Part_IO(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Part_IO)
	enum { IDD = IDD_DIALOG_PART_IO };
	CButtonST	m_btn_exit;
	CXPGroupBox	m_group_output;
	CXPGroupBox	m_group_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Part_IO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Part_IO)
	afx_msg void OnBtnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_PART_IO_H__0D376FD6_2F3D_4E27_8347_BDB5B857F43E__INCLUDED_)
