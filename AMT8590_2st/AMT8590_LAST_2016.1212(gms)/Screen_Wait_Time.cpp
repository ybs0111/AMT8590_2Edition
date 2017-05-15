// Screen_Wait_Time.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Screen_Wait_Time.h"

// ****************************************************************************** 
// ��ȭ ���� Ŭ���� �߰�                                                          
// ****************************************************************************** 
#include "Dialog_Select.h"
#include "Dialog_Message.h"

#include "Dialog_KeyPad.h"
// ****************************************************************************** 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreen_Wait_Time

IMPLEMENT_DYNCREATE(CScreen_Wait_Time, CFormView)

CScreen_Wait_Time::CScreen_Wait_Time()
	: CFormView(CScreen_Wait_Time::IDD)
{
	//{{AFX_DATA_INIT(CScreen_Wait_Time)
	//}}AFX_DATA_INIT
}

CScreen_Wait_Time::~CScreen_Wait_Time()
{
}

void CScreen_Wait_Time::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreen_Wait_Time)
	DDX_Control(pDX, IDC_BTN_WAIT_APPLY, m_btn_wait_apply);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreen_Wait_Time, CFormView)
	//{{AFX_MSG_MAP(CScreen_Wait_Time)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_WAIT_APPLY, OnBtnWaitApply)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SSM_CLICK, OnCellClick)
	ON_MESSAGE(WM_WAITTIME_APPLY, OnWaitTime_Info_Apply)  // DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� ����
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreen_Wait_Time diagnostics

#ifdef _DEBUG
void CScreen_Wait_Time::AssertValid() const
{
	CFormView::AssertValid();
}

void CScreen_Wait_Time::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreen_Wait_Time message handlers
void CScreen_Wait_Time::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnTimer(nIDEvent);
}

void CScreen_Wait_Time::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// ************************************************************************** 
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�                                              
	// ************************************************************************** 
// 	mp_wait_time_font = NULL;
// 	mp_wait_time_font = new CFont;
// 	mp_wait_time_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// ************************************************************************** 
	OnWaitTime_Data_Display();

	mn_enable = TRUE;
	st_handler.cwnd_waittime = this;  // Wait Time ȭ�鿡 ���� �ڵ� ���� ���� 
}

void CScreen_Wait_Time::OnDestroy() 
{
	int mn_response;  // ��ȭ ���ڿ� ���� ���� �� ���� ����
	int Ret;

	CDialog_Select select_dlg;

	//���α׷��� ���������鼭 Save ���� �ʰ�, Form�� Destroy�Ǵ°��̶�� Setting�� �����Ѵٴ� ���̴�.
	//�񱳵� ���� ����.
	if (st_handler.b_program_exit == false)
	{
		Ret = OnWaitTime_Data_Comparison();

		if (Ret == RET_ERROR)
		{
			st_msg.mstr_confirm_msg = _T("Changed Data! Apply?");
			
			mn_response = select_dlg.DoModal();
			
			if (mn_response == IDOK)
			{
				OnWaitTime_Data_Apply();

				OnWaitTime_LogFile_Create();
			}
			else if (mn_response == IDCANCEL)
			{
				OnWaitTime_Data_Recovery();

				OnWaitTime_Data_Display();

				OnWaitTime_Data_Apply();
			}	
		}
	}

	// ************************************************************************** 
	// ������ ��Ʈ ���� �����Ѵ�                                                  
	// ************************************************************************** 
// 	delete mp_wait_time_font;
// 	mp_wait_time_font = NULL;
	// ************************************************************************** 

	st_handler.cwnd_waittime = NULL;	// Wait Time ȭ�鿡 ���� �ڵ� ���� ���� ���� �ʱ�ȭ 
	
	CFormView::OnDestroy();
}

void CScreen_Wait_Time::OnWaitTime_Data_Set()
{
	int i;

	for(i=0; i<mn_wait_time_cnt; i++)
	{
		mn_on_wait[i][1]		= st_time.n_wait_time[i][1];
		mn_off_wait[i][1]		= st_time.n_wait_time[i][0];
		mn_limit[i][1]			= st_time.n_limit_time[i];
	}
	
	OnWaitTime_Data_BackUp();
}

void CScreen_Wait_Time::OnWaitTime_Data_Recovery()
{
	int i;
	
	for (i = 0; i < E_WAIT_MAX; i ++)
	{
		mn_on_wait[i][1] = mn_on_wait[i][0];
		mn_off_wait[i][1] = mn_off_wait[i][0];
		mn_limit[i][1] = mn_limit[i][0];
	}
}

void CScreen_Wait_Time::OnWaitTime_Data_Display()
{
	OnWaitTime_Init_Time();
}

int CScreen_Wait_Time::OnWaitTime_Data_Comparison()
{
	int Ret = CTLBD_RET_GOOD;
	int i;
	
	for (i = 0; i < E_WAIT_MAX; i ++)
	{
		if (mn_on_wait[i][0] != mn_on_wait[i][1])			Ret = CTLBD_RET_ERROR;
		if (mn_off_wait[i][0] != mn_off_wait[i][1])			Ret = CTLBD_RET_ERROR;
		if (mn_limit[i][0] != mn_limit[i][1])				Ret = CTLBD_RET_ERROR;
	}

	return Ret;
}

void CScreen_Wait_Time::OnWaitTime_Data_BackUp()
{
	int i;

	for (i = 0; i < E_WAIT_MAX; i ++)
	{
		mn_on_wait[i][0] = mn_on_wait[i][1];
		mn_off_wait[i][0] = mn_off_wait[i][1];
		mn_limit[i][0] = mn_limit[i][1];
	}
}

void CScreen_Wait_Time::OnWaitTime_Data_Apply()
{
	int i;

	for (i = 0; i < E_WAIT_MAX; i++)
	{
		st_time.n_wait_time[i][1] = mn_on_wait[i][1];
		st_time.n_wait_time[i][0] = mn_off_wait[i][1];
		st_time.n_limit_time[i] = mn_limit[i][1];
	}
}

// ****************************************************************************** 
//  ȭ�� ���� ���� ��û �޽���                                                    
// ****************************************************************************** 
LRESULT CScreen_Wait_Time::OnWaitTime_Info_Apply(WPARAM wParam, LPARAM lParam)  
{
	OnWaitTime_Data_Apply();		// ȭ�� ���� ���� ���� ������ ���� �Լ�
	
	OnWaitTime_LogFile_Create();
	
	OnWaitTime_Data_BackUp();
	
	return 0;
}

void CScreen_Wait_Time::OnWaitTime_LogFile_Create()
{
	CString str_msg;
	CString str_data;
	CString str_old_data;
	CString str_io_name;
	int i;
	
	for (i = 0; i < E_WAIT_MAX; i++)
	{
		str_io_name = mstr_wait_time_name[i];

		if (mn_on_wait[i][1] != mn_on_wait[i][0])
		{
			str_data.Format("%d", mn_on_wait[i][1]);
			str_old_data.Format("%d", mn_on_wait[i][0]);
			str_msg.Format("[Time Set] %s On Wait Time was changed by %s To %s", str_io_name, str_old_data, str_data);
			Func.On_LogFile_Add(0, str_msg);
			Func.On_LogFile_Add(99, str_msg);
		}

		if (mn_off_wait[i][1] != mn_off_wait[i][0])
		{
			str_data.Format("%d", mn_off_wait[i][1]);
			str_old_data.Format("%d", mn_off_wait[i][0]);
			str_msg.Format("[Time Set] %s Off Wait Time was changed by %s To %s", str_io_name, str_old_data, str_data);
			Func.On_LogFile_Add(0, str_msg);
			Func.On_LogFile_Add(99, str_msg);
		}

		if (mn_limit[i][1] != mn_limit[i][0])
		{
			str_data.Format("%d", mn_limit[i][1]);
			str_old_data.Format("%d", mn_limit[i][0]);
			str_msg.Format("[Time Set] %s Limit Time was changed by %s To %s", str_io_name, str_old_data, str_data);
			Func.On_LogFile_Add(0, str_msg);
			Func.On_LogFile_Add(99, str_msg);
		}
	}
}

void CScreen_Wait_Time::OnWaitTime_Init_Time()
{
	int i, j;
	CString str_tmp;
	
	m_grid_time = (TSpread*)GetDlgItem(IDC_CUSTOM_TIME);
	
	mp_grid.GridFileOpen(m_grid_time, st_path.mstr_wait_time_map, "sheet1");
	
	mn_wait_time_cnt = 0;
	mn_wait_time_cnt = atoi(mp_grid.GridCellText(m_grid_time, 1, 3));
	
	if(mn_wait_time_cnt == 0) return;
	
	for(i=0; i<mn_wait_time_cnt; i++)
	{
		mn_on_used[i]				= atoi(mp_grid.GridCellText(m_grid_time, i+4, 4));
		mn_off_used[i]				= atoi(mp_grid.GridCellText(m_grid_time, i+4, 5));
		mn_limit_used[i]			= atoi(mp_grid.GridCellText(m_grid_time, i+4, 6));
		mstr_wait_time_name[i]		= mp_grid.GridCellText(m_grid_time, i+4, 2);
	}
	
	OnWaitTime_Data_Set();
	
	mp_grid.GridReset(m_grid_time);
	// �빮�� 
	mp_grid.GridCellSelectDisplay(m_grid_time, TRUE);
	mp_grid.GridRowHeader(m_grid_time, FALSE);
	mp_grid.GridColHeader(m_grid_time, TRUE);
	mp_grid.GridHorizontal(m_grid_time, FALSE);
	mp_grid.GridVertical(m_grid_time, TRUE);
	mp_grid.GridAutoSize(m_grid_time, FALSE);
	
	mp_grid.GridCellRows(m_grid_time, mn_wait_time_cnt);
	mp_grid.GridCellCols(m_grid_time, 5);


	for(i=0; i<mn_wait_time_cnt+1; i++)
	{
		mp_grid.GridCellHeight_L(m_grid_time, i, (double)30);
		
		if(i == 0)
		{
			for(j=0; j<5; j++)
			{
				switch(j)
				{
					case 0:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, (double)5);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, "No.");
						break;

					case 1:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, (double)54);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, "Name");
						break;

					case 2:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, (double)20);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, "On Time (ms)");
						break;

					case 3:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, (double)20);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, "Off Time (ms)");
						break;

					case 4:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, (double)20);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, "Limit Time (ms)");
						break;
				}

				mp_grid.GridCellControlStatic(m_grid_time, i, j+1);
			}
		}
		else
		{
			for(j=0; j<5; j++)
			{
				switch(j)
				{
					case 0:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, 5);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 14);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLUE_D, WHITE_C);
						str_tmp.Format("%d", i);
						mp_grid.GridCellText(m_grid_time, i, j+1, str_tmp);
						break;

					case 1:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, 54);

						mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 14);
						mp_grid.GridCellColor(m_grid_time, i, j+1, BLACK_L, YELLOW_C);
						mp_grid.GridCellText(m_grid_time, i, j+1, mstr_wait_time_name[i-1]);
						break;

					case 2:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, 20);
						
						if(mn_on_used[i-1] == CTL_YES)
						{
							mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
							mp_grid.GridCellColor(m_grid_time, i, j+1, GREEN_L, BLACK_C);
							str_tmp.Format("%d", mn_on_wait[i-1][1]);
							mp_grid.GridCellText(m_grid_time, i, j+1, str_tmp);
						}
						else
						{
							mp_grid.GridCellColor(m_grid_time, i, j+1, DSERBLE_BC, YELLOW_C);
							mp_grid.GridCellText(m_grid_time, i, j+1, "-");
						}
						break;

					case 3:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, 20);

						if(mn_off_used[i-1] == CTL_YES)
						{
							mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
							mp_grid.GridCellColor(m_grid_time, i, j+1, RED_L, BLACK_C);
							str_tmp.Format("%d", mn_off_wait[i-1][1]);
							mp_grid.GridCellText(m_grid_time, i, j+1, str_tmp);
						}
						else
						{
							mp_grid.GridCellColor(m_grid_time, i, j+1, DSERBLE_BC, YELLOW_C);
							mp_grid.GridCellText(m_grid_time, i, j+1, "-");
						}
						break;

					case 4:
						mp_grid.GridCellWidth_L(m_grid_time, j+1, 20);

						if(mn_limit_used[i-1] == CTL_YES)
						{
							mp_grid.GridCellFont(m_grid_time, i, j+1, "MS Sans Serif", 18);
							mp_grid.GridCellColor(m_grid_time, i, j+1, YELLOW_L, BLACK_C);
							str_tmp.Format("%d", mn_limit[i-1][1]);
							mp_grid.GridCellText(m_grid_time, i, j+1, str_tmp);
						}
						else
						{
							mp_grid.GridCellColor(m_grid_time, i, j+1, DSERBLE_BC, YELLOW_C);
							mp_grid.GridCellText(m_grid_time, i, j+1, "-");
						}
						break;
				}
	
				mp_grid.GridCellControlStatic(m_grid_time, i, j+1);
			}
		}
	}
}

void CScreen_Wait_Time::GridColor(UINT nID, int row, int col, COLORREF bk, COLORREF tk)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	Grid->SetColor(col, row, bk, tk);
	Grid->SetBackColorStyle(SS_BACKCOLORSTYLE_UNDERGRID);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CScreen_Wait_Time::GridControl(UINT nID, int type, int row, int col, int pos)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	SS_CELLTYPE CellType;
	SS_DATEFORMAT dateFormat = { TRUE, '/', IDF_DDMMYY, FALSE };
	SS_TIMEFORMAT tmFormat;
	CString strList;
	strList = "combo1\tcombo2\tcombo3\tcombo4\tcombo5\tcombo6";
	double a = 0.5;

	switch (type)
	{
		case DATE:			
			Grid->SetTypeDate(&CellType, 0 , &dateFormat, NULL, NULL);
			break;

		case EDIT:
			Grid->SetTypeEdit(&CellType,ES_CENTER,60,SS_CHRSET_CHR,SS_CASE_NOCASE);
			break;

		case COMBO:
			// SetValue(col, row, data); data = ""0"(1����) data = "1"(2����) data = "2"(3����)
			Grid->SetTypeComboBox(&CellType, 0, strList);
			break;

		case BUTTON:
			if (pos == 0)
			{
				Grid->SetTypeButton(&CellType, SBS_DEFPUSHBUTTON, "Go", NULL, SUPERBTN_PICT_NONE,
					NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 2, NULL);
			}
			else
			{
				Grid->SetTypeButton(&CellType, SBS_DEFPUSHBUTTON, "Read", NULL, SUPERBTN_PICT_NONE,
					NULL, SUPERBTN_PICT_NONE,SUPERBTN_TYPE_NORMAL, 2, NULL);
			}
			break;

		case STATIC:
			Grid->SetTypeStaticText(&CellType, SS_TEXT_CENTER | SS_TEXT_VCENTER);
			break;

		case TIME:
			tmFormat.b24Hour=TRUE;
			tmFormat.bSpin=FALSE;
			tmFormat.bSeconds=FALSE;
			tmFormat.cSeparator=':';
			Grid->SetTypeTime(&CellType, 0, &tmFormat, NULL, NULL);
			break;

		case PERCENT:
			Grid->SetTypePercentEx(&CellType,ES_LEFTALIGN,2,.01,100,".",0,0,0,0,1.001);
			break;

		case CHECK1:
			Grid->SetTypeCheckBox(&CellType,BS_CENTER, "", 
				"CheckUp", BT_BITMAP,
				"CheckDown", BT_BITMAP,
				"CheckFocusUp", BT_BITMAP,
				"CheckFocusDown", BT_BITMAP,
				"CheckDisabledUp", BT_BITMAP,
				"CheckDisabledDown", BT_BITMAP);
			break;

		case NUMBER:
			Grid->SetTypeNumberEx(&CellType,0,pos, 0, 10000,0,".",",",0,0,1,0,1.001);
			break;
	}
	
	Grid->SetCellType(col,row,&CellType);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CScreen_Wait_Time::GridData(UINT nID, int row, int col, CString data)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	Grid->SetValue(col, row, data);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CScreen_Wait_Time::GridFont(UINT nID, int row, int col, int size)
{
	TSpread *Grid = (TSpread *)GetDlgItem(nID);
	HFONT font;
	CString strTemp;
	
	font = CreateFont(size, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "����ü");
	Grid->SetFont(col, row, font, TRUE);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CScreen_Wait_Time::GridMerge(UINT nID, int srow, int scol, int nrow, int ncol)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	Grid->AddCellSpan(scol, srow, ncol, nrow);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CScreen_Wait_Time::OnCellClick(WPARAM wParam, LPARAM lParam)
{
	int nId = -1;
	LPSS_CELLCOORD lpcc = (LPSS_CELLCOORD)lParam;
	
	if (mn_enable != TRUE)					return;
	if (lpcc->Col == 1 || lpcc->Col == 2)	return;

	switch (wParam)
	{
	case IDC_CUSTOM_TIME:
		nId = 0;
		break;	
	}
	
	if (nId > -1)
	{
		if (lpcc->Col == 3)
		{
			if (mn_on_used[lpcc->Row-1] == CTL_NO) return;
		}
		else if (lpcc->Col == 4)
		{
			if (mn_off_used[lpcc->Row-1] == CTL_NO) return;
		}
		else if (lpcc->Col == 5)
		{
			if (mn_limit_used[lpcc->Row-1] == CTL_NO) return;
		}

		OnChangeValue(nId, lpcc->Row, lpcc->Col);
	}
}

void CScreen_Wait_Time::OnChangeValue(int nid, int nrow, int ncol)
{
	TSpread *Grid; 
	CString strTmp;
	char chvalue[100];
	char chText[100];
	CString strText;
	CString strText2;
	int nValue, i;

	CString str_temp;	// ������ ���� �ӽ� ���� ���� 

	if (nid == 0)
	{
		Grid = (TSpread*)GetDlgItem(IDC_CUSTOM_TIME);
		
		Grid->GetValue(ncol, nrow, chvalue);
		nValue = atoi(chvalue);
		strTmp.Format("%d", nValue);
		
		Grid->GetValue(2, nrow, chText);
		strText = chText;

		Grid->GetValue(ncol, 0, chText);
		strText2 = chText;

		if (nrow == 1)		// ��ü ����.
		{
			st_msg.mstr_keypad_msg.Format("[TIME SET] All Contents, %s set", strText2);
		}
		else
		{
			st_msg.mstr_keypad_msg.Format("[TIME SET] %s, %s set", strText, strText2);
		}
		
		st_msg.mstr_keypad_val = strTmp;
		
		strTmp = KeyPad.GetNumEditString_I(0, 99999, atoi(st_msg.mstr_keypad_val), st_msg.mstr_keypad_msg);

		if (ncol == 1)
		{
		}
		else if (ncol == 3)		// On Wait
		{
			if (nrow == 0)		// ��ü ����.
			{
				for (i = 0; i < E_WAIT_MAX; i++)
				{	
					if (mn_on_used[i] == CTL_NO) continue;

					mn_on_wait[i][1] = atoi(strTmp);
					strTmp.Format("%d", mn_on_wait[i][1]);

					Grid->SetValue(ncol, i + 1, strTmp);
				}
				if( Grid != NULL )
				{
					Grid = NULL;
					delete Grid;
				}
				return;
			}
			else
			{
				mn_on_wait[nrow-1][1] = atoi(strTmp);
				strTmp.Format("%d", mn_on_wait[nrow-1][1]);
			}
		}
		else if (ncol == 4)		// Off Wait
		{
			if (nrow == 0)		// ��ü ����.
			{
				for (i = 0; i < E_WAIT_MAX; i++)
				{	
					if (mn_off_used[i] == CTL_NO) continue;
					mn_off_wait[i][1] = atoi(strTmp);
					strTmp.Format("%d", mn_off_wait[i][1]);
					
					Grid->SetValue(ncol, i + 1, strTmp);
				}
				if( Grid != NULL )
				{
					Grid = NULL;
					delete Grid;
				}
				return;
			}
			else
			{
				mn_off_wait[nrow-1][1] = atoi(strTmp);
				strTmp.Format("%d", mn_off_wait[nrow-1][1]);
			}
		}
		else if (ncol == 5)		// Limit
		{
			if (nrow == 0)		// ��ü ����.
			{
				for (i = 0; i < E_WAIT_MAX; i++)
				{	
					if (mn_limit_used[i] == CTL_NO) continue;
					mn_limit[i][1] = atoi(strTmp);
					strTmp.Format("%d", mn_limit[i][1]);
					
					Grid->SetValue(ncol, i + 1, strTmp);
				}
				if( Grid != NULL )
				{
					Grid = NULL;
					delete Grid;
				}
				return;
			}
			else
			{
				mn_limit[nrow-1][1] = atoi(strTmp);
				strTmp.Format("%d", mn_limit[nrow-1][1]);
			}
		}

		Grid->SetValue(ncol, nrow, strTmp);

		if( Grid != NULL )
		{
			Grid = NULL;
			delete Grid;
		}
	}
}

void CScreen_Wait_Time::On_Controls_Enable(int nState)
{
	mn_enable = nState;
	m_btn_wait_apply.EnableWindow(nState);
}	

void CScreen_Wait_Time::OnBtnWaitApply() 
{
	int n_response;  // ��ȭ ���� ���� �÷���
	
	CDialog_Select  select_dlg;
	
	st_msg.mstr_confirm_msg = _T("Wait Time : Setting Data Apply?");
	
	n_response = select_dlg.DoModal();
	
	if (n_response == IDOK)
	{
		OnWaitTime_Data_Apply();			// ȭ�� ���� ���� ���� ������ ���� �Լ�
		
		OnWaitTime_LogFile_Create();
		
		OnWaitTime_Data_BackUp();
	}
	else if (n_response == IDCANCEL)
	{
		
	}
}