#if !defined(AFX_SCREEN_MOTOR_H__52DCE9AA_3AEE_4C15_B5CA_E5372B940AE0__INCLUDED_)
#define AFX_SCREEN_MOTOR_H__52DCE9AA_3AEE_4C15_B5CA_E5372B940AE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Screen_Motor.h : header file
//
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 
#include "Public_Function.h"
#include "NewLabel.h"		// Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "editex.h"			// Į�� ����Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "BtnST.h"          // Į�� ��ư ���� Ŭ���� �߰� 
#include "XPGroupBox.h"		// Į�� �׷� �ڽ� ���� Ŭ���� �߰� 
#include "sxlogfont.h"
#include "LedButton.h"      // LED ��ư Ŭ����
#include "EXDigitST.h"		// ������ ī���� ���� Ŭ���� �߰� 
#include "MacButtons.h"
#include "Digit.h"
#include "GradientStatic.h" // �׶��̼� Į�� �ؽ�Ʈ �ڽ� ���� Ŭ���� �߰� 
#include "PictureEx.h"		// GIF ������ �ε��ϱ� ���� Ŭ���� �߰� 
#include "BmpImageST.h"		// �˶� ��Ʈ�� �ε� Ŭ���� �߰� 
//#include "CharSetCtrl.h"
#include "FloatST.h"
//#include "FastechPublic.h"
#include "GridControlAlg.h"
#include "MatrixStatic.h"
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CScreen_Motor form view
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScreen_Motor : public CFormView
{
public:
	int				m_n_part_cnt;
	int				m_n_part_axis_cnt[20];
	int				m_n_part_axis[20][12];
	
	CString			m_str_part_info[20];
	CString			m_str_part_name[20];
	CString			m_str_part_axis_name[20][12];

	TSpread			*m_grid_part;
	TSpread			*m_grid_motor;

	CPicture		m_p_bmp_view;
	GridControlAlg	m_p_grid;
public:
// 	CFont* mp_main_font;
public:
	CScreen_Motor();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScreen_Motor)

// Form Data
public:
	//{{AFX_DATA(CScreen_Motor)
	enum { IDD = IDD_SCREEN_MOTOR };
	CMacButton	m_btn_motor_speed;
	CXPGroupBox	m_group_part_information;
	CXPGroupBox	m_group_motor_part;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void Init_Motor_Grid();
	void OnMotor_Part_List(int n_col, int n_axis);
	void Init_Group();
	void Init_Part_Grid();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreen_Motor)
	public:
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreen_Motor();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScreen_Motor)
	afx_msg void OnPaint();
	afx_msg void OnBtnMotorSpeed();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMotor_Work_Message(WPARAM wParam,LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREEN_MOTOR_H__52DCE9AA_3AEE_4C15_B5CA_E5372B940AE0__INCLUDED_)
