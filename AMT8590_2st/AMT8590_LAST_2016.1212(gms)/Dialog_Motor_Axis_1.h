#if !defined(AFX_DIALOG_MOTOR_AXIS_1_H__2C597DAB_C483_4F88_AE46_F5EBF7E4FAFA__INCLUDED_)
#define AFX_DIALOG_MOTOR_AXIS_1_H__2C597DAB_C483_4F88_AE46_F5EBF7E4FAFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Motor_Axis_1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Motor_Axis_1 dialog
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
#include "Picture.h"

class CDialog_Motor_Axis_1 : public CDialog
{
public:
	CPicture		m_p_bmp_view;
	GridControlAlg	m_p_grid;
	
	BOOL			m_b_stop_req;	// ESTOP ��û �÷��� �ʱ�ȭ
	
	TSpread			*m_grid_motor_pos;
	TSpread			*m_grid_motor_info;
	
	double			m_d_data;
	double			m_d_position[50][2];//50
	
	int				m_n_move_mode;
	int				m_n_axis;
	int				m_n_part;
	int				m_n_cmd_row;
	int				m_n_cmd_col;
	int				m_n_position_num;
	int				m_n_plus_el;
	int				m_n_minus_el;
	int				m_n_home;
	int				m_n_sd;
	
	CString			m_str_position_name[50];//32
	CString			m_str_position_bmp[50];//32
	CString			m_str_axis_name;
	CString			m_strTempMSG;
// 	CFont			* m_p_font;
// Construction
public:
	void	Init_Grid_Info();
	void	OnButtonControl(BOOL b_flag);
	void	MotorCompletion(int nrow, int ncol);
	void	MotorPositionCheck();
	void	MotorStatusCheck();
	void	Data_HistoryLog();
	void	Data_Recovery();
	int		Data_Comparison();
	void	Data_Apply();
	void	Data_Backup();
	void	Data_Init( int iSelected );
	void	Init_Grid_Pos();
	void	Init_Radio();
	void	Init_Digit();
	void	Init_Group();
	void	Init_Label();
	void	Init_Button();

	void	SetDataForSelected( int iSelected );
	CDialog_Motor_Axis_1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Motor_Axis_1)
	enum { IDD = IDD_MOTOR_AXIS_1 };
	CMacButton	m_btn_apply;
	CButtonST	m_btn_right;
	CButtonST	m_btn_left;
	CButtonST	m_btn_home;
	CXPGroupBox	m_group_axis_info;
	CXPGroupBox	m_group_motor;
	CXPGroupBox	m_group_move;
	CButtonST	m_btn_emg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Motor_Axis_1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Motor_Axis_1)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBtnEmg();
	afx_msg void OnBtnHome();
	afx_msg void OnBtnApply();
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMotorCompletion(WPARAM wParam,LPARAM lParam);

	LONG OnUserLButtonDown(WPARAM wParam, LPARAM lParam);
	LONG OnUserLButtonUp(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MOTOR_AXIS_1_H__2C597DAB_C483_4F88_AE46_F5EBF7E4FAFA__INCLUDED_)
