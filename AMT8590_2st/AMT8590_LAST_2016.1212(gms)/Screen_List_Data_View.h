#if !defined(AFX_SCREEN_LIST_DATA_VIEW_H__0D762DB9_0DE5_4388_8EE6_917F70773947__INCLUDED_)
#define AFX_SCREEN_LIST_DATA_VIEW_H__0D762DB9_0DE5_4388_8EE6_917F70773947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Screen_List_Data_View.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScreen_List_Data_View form view
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
#include "GridControlAlg.h"
#include "FPSDateTimeCtrl.h"
#include "FPSDatePickerCtrl.h"
#include "FPSMiniCalendarCtrl.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScreen_List_Data_View : public CFormView
{
public:
	CScreen_List_Data_View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScreen_List_Data_View)

// Form Data
public:
	//{{AFX_DATA(CScreen_List_Data_View)
	enum { IDD = IDD_SCREEN_LIST_DATA_VIEW };
	CMacButton	m_btn_buffer_search;
	CMacButton	m_btn_start_time;
	CMacButton	m_btn_end_time;
	CMacButton	m_btn_day_today;
	CMacButton	m_btn_day_prev;
	CMacButton	m_btn_day_next;
	CMacRadioButton	m_radio_board;
	CMacRadioButton	m_radio_lot;
	CMacRadioButton	m_radio_all;
	CXPGroupBox	m_group_start_date;
	CXPGroupBox	m_group_end_date;
	CXPGroupBox	m_group_data;
	CMacButton	m_btn_view_retest;
	CMacButton	m_btn_view_prime;
	CMacButton	m_btn_view;
	CMacButton	m_btn_serach_time;
	CMacButton	m_btn_search_boardoff;
	CMacButton	m_btn_search_ground;
	CMacButton	m_btn_search_alarm;
	CMacButton	m_btn_save;
	//}}AFX_DATA

// Attributes
public:
	COleDateTime		m_oledate[2];
	COleDateTime		m_oletime[2];
	CFPSDateTimeCtrl	m_pstart_date;
	CFPSDateTimeCtrl	m_pend_date;
	
	CFPSDateTimeCtrl	m_pstart_time;
	CFPSDateTimeCtrl	m_pend_time;
	
// 	CFont* mp_mainfont;
	GridControlAlg m_pGrid;
	
	int mn_view_type;
	int mn_pcb_cnt;
	
	int mn_high_val_pos[5];
	double md_high_val_data[5];
	
	CString mstr_file_name;				// ���õ� ���� �̸� ���� ���� ���� 
	CString mstr_temp_file;				// ���� �̸� �ӽ� ���� ���� 
	CString mstr_file_full_name;		// Save as ��ų�� ����Ѵ�. 2K4/08/16/ViboX
	
	double md_test_count_p[10];			// �� �׽�Ʈ Ƚ��		// Edit 10 Para 6 -> 10
	double md_test_count_c[10];			// �� �׽�Ʈ Ƚ��		// Edit 10 Para 6 -> 10
	double md_test_count_pt;			// �� �׽�Ʈ Ƚ��
	double md_test_count_ct;			// �� �׽�Ʈ Ƚ��
	double md_test_good_p[10];			// �� Ƚ��. - ������.	// Edit 10 Para 6 -> 10
	double md_test_good_c[10];			// �� Ƚ��. - CUM.		// Edit 10 Para 6 -> 10
	double md_test_good_pt;				// �� Ƚ��. - CUM.	
	double md_test_good_ct;				// �� Ƚ��. - CUM.

	// by. galmg.
	double md_board_hto;
	double md_board_bto;
	double md_board_nto;
	double md_board_fail;
	
	double md_test_yield_p[10];			// Edit 10 Para 6 -> 10
	double md_test_yield_c[10];			// Edit 10 Para 6 -> 10
	double md_test_yield_pt;
	double md_test_yield_ct;
	double md_test_yield_cum;
	
	double md_socket_count[10];
	double md_socket_count_t;
	
	double md_socket_live[10];
	double md_socket_live_t;
	
	double md_socket_live_yield[10];
	double md_socket_live_yield_t;

	double md_board_count[80];
	double md_board_count_t;
	
	double md_board_live[80];
	double md_board_live_t;
	
	double md_board_live_yield[80];	// Edit 10 Para 6 -> 10
	double md_board_live_yield_t;
	
	double md_pcb_test_count;			// PCB Base Test Count
	double md_pcb_good_count;			// PCB Base Good Count
	double md_pcb_yield;				// PCB Base Yield

	double md_board_result_count_t;
	double md_board_result_yield_t;
	double md_board_fail_t;
	double md_board_good_t;


	double md_board_result_count[80];
	double md_board_good[80];
	double md_board_result_yield[80];
	
	int nSearchMethod;
	
	double dTime[6][2];
	
	int mn_board_view_p[80][5];			// ���� View���� �� ����. [����][��] Prime  : 0-Pass, 1-NTO, 2-BTO, 3-HTO, 4-FAIL
	int mn_board_view_r[80][5];			// ���� View���� �� ����. [����][��] Retest
	
	int mn_socket_view_mode;

// Operations
public:
	void Display_Buffer(int count);
	void Init_Buffer();
	void Display_Socket_Detail();
	CString OnDateCheck(int nYearS, int nMonthS, int nDayS, int nHourS, int nMinS, int nSecS, int nYearE, int nMonthE, int nDayE, int nHourE, int nMinE, int nSecE);
	void Init_Board();
	void Display_Ground(int count);
	void Init_Ground();
	void Init_BoardOff();
	void Display_Alarm(int count);
	void Init_Alarm();
	void Display_Ground_Date(int count, CString strtime);
	void Display_Time(int count);
	void Init_Time();
	void Init_Data();
	void OnData_Search_Change();
	void Init_Chart();
	void Display_LotNo(int count, CString lot_no);
	void Init_Device();
	void Init_Group();
	void Init_Lot();
	void Init_Date();

	void Display_Data();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreen_List_Data_View)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreen_List_Data_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScreen_List_Data_View)
	afx_msg void OnDestroy();
	afx_msg void OnBtnSearchTime();
	afx_msg void OnBtnSearchAlarm();
	afx_msg void OnRadioAll();
	afx_msg void OnRadioLot();
	afx_msg void OnRadioBoard();
	afx_msg void OnBtnSearchGround();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnDayPrev();
	afx_msg void OnBtnDayNext();
	afx_msg void OnBtnDayToday();
	afx_msg void OnBtnView();
	afx_msg void OnBtnViewPrime();
	afx_msg void OnBtnViewRetest();
	afx_msg void OnBtnStartTime();
	afx_msg void OnBtnEndTime();
	afx_msg void OnBtnBufferSearch();
	//}}AFX_MSG
	afx_msg void OnCellClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREEN_LIST_DATA_VIEW_H__0D762DB9_0DE5_4388_8EE6_917F70773947__INCLUDED_)
