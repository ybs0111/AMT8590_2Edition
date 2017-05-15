// Dialog_Part_IO.cpp : implementation file
//

#include "stdafx.h"
#include "handler.h"
#include "Dialog_Part_IO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Part_IO dialog
#define TM_IN_READ		100
#define TM_OUT_READ		200

CDialog_Part_IO::CDialog_Part_IO(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Part_IO::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Part_IO)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog_Part_IO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Part_IO)
	DDX_Control(pDX, IDC_BTN_EXIT, m_btn_exit);
	DDX_Control(pDX, IDC_GROUP_OUTPUT, m_group_output);
	DDX_Control(pDX, IDC_GROUP_INPUT, m_group_input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Part_IO, CDialog)
	//{{AFX_MSG_MAP(CDialog_Part_IO)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(SSM_CLICK  , OnCellClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Part_IO message handlers

void CDialog_Part_IO::Init_Button()
{
	short	shBtnColor = 30;
	
	m_btn_exit.SetFont(Func.mp_iopart_font);
	m_btn_exit.SetIcon(IDI_EXIT);
	m_btn_exit.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btn_exit.SetButtonColor(1);
	m_btn_exit.SetTooltipText("IO Dialog Exit");
}

void CDialog_Part_IO::Init_Group()
{
	CSxLogFont main_font(15,FW_SEMIBOLD,false,"Arial");
	
	m_group_input.SetFont(main_font);
	m_group_input.SetCatptionTextColor(RGB(145,25,0));
	m_group_input.SetFontBold(TRUE);
	m_group_input.SetWindowText("Input");
	
	m_group_output.SetFont(main_font);
	m_group_output.SetCatptionTextColor(RGB(145,25,0));
	m_group_output.SetFontBold(TRUE);
	m_group_output.SetWindowText("Output");
}

void CDialog_Part_IO::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
//	CDialog::OnCancel();
	DestroyWindow();
}

BOOL CDialog_Part_IO::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rectArea;

// 	m_p_font = NULL;
// 	m_p_font = new CFont;
// 	m_p_font->CreateFont(16,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");


	GetClientRect(rectArea);
	MoveWindow(m_cp_coord.x, m_cp_coord.y, rectArea.Width(), rectArea.Height(), TRUE);
	
	Init_Grid_IO();
	Init_Button();
	Init_Group();

	SetTimer(TM_IN_READ, 100, NULL);
	SetTimer(TM_OUT_READ, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Part_IO::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case TM_IN_READ:
			OnInputCheck();
			break;

		case TM_OUT_READ:
			OnOutputCheck();
			break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDialog_Part_IO::Init_Grid_IO()
{
	int   i;
	CString str_tmp;
	m_grid_input = (TSpread*)GetDlgItem(IDC_CUSTOM_INPUT);
	
	m_p_grid.GridFileOpen(m_grid_input, st_path.mstr_io_part_map, "sheet1");
	
	m_n_in_cnt	= 0;
	m_n_out_cnt	= 0;

	m_n_in_cnt	= atoi(m_p_grid.GridCellText(m_grid_input, 3, ((m_n_part * 6) + 3)+1));
	m_n_out_cnt = atoi(m_p_grid.GridCellText(m_grid_input, 3, ((m_n_part * 6) + 6)+1));

	for(i=0; i<m_n_in_cnt; i++)
	{
		m_n_in_port[i]	= atoi(m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 0)+2));
		m_n_in_num[i]	= atoi(m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 1)+2));
		m_str_in[i]		= m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 2)+2);
	}

	for(i=0; i<m_n_out_cnt; i++)
	{
		m_n_out_port[i]	= atoi(m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 3)+2));
		m_n_out_num[i]	= atoi(m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 4)+2));
		m_str_out[i]	= m_p_grid.GridCellText(m_grid_input, i+5, ((m_n_part * 6) + 5)+2);
	}

	Init_Input();
	Init_Output();
}

void CDialog_Part_IO::Init_Input()
{
	int   i, j;
	CString str_tmp;
	
	m_grid_input = (TSpread*)GetDlgItem(IDC_CUSTOM_INPUT);
	
	m_p_grid.GridReset(m_grid_input);
	// �빮�� 
	m_p_grid.GridCellSelectDisplay(m_grid_input, TRUE);
	
	m_p_grid.GridRowHeader(m_grid_input, FALSE);
	m_p_grid.GridColHeader(m_grid_input, TRUE);
	m_p_grid.GridHorizontal(m_grid_input, FALSE);
	m_p_grid.GridVertical(m_grid_input, TRUE);
	m_p_grid.GridAutoSize(m_grid_input, FALSE);
	m_p_grid.GridAutoSize(m_grid_input, FALSE);
	m_p_grid.GridCellRows(m_grid_input, m_n_in_cnt);
	m_p_grid.GridCellCols(m_grid_input, 2);

// 	if (mn_io_type[port][num][i] == IO_IN)
// 	{
// 		GridColor(IDC_CUSTOM_IO, i+4, 1, RGB(200, 255, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 2, RGB(200, 255, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 3, RGB(200, 255, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 5, RGB(200, 255, 200), RGB(25, 25, 85));
// 		GridData(IDC_CUSTOM_IO, i+4, 3, "Input");
// 	}
// 	else if (mn_io_type[port][num][i] == IO_OUT)
// 	{
// 		GridColor(IDC_CUSTOM_IO, i+4, 1, RGB(255, 200, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 2, RGB(255, 200, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 3, RGB(255, 200, 200), RGB(25, 25, 85));
// 		GridColor(IDC_CUSTOM_IO, i+4, 5, RGB(255, 200, 200), RGB(25, 25, 85));
// 		GridData(IDC_CUSTOM_IO, i+4, 3, "Output");
// 	}
	
	for(i=0; i<m_n_in_cnt+1; i++)
	{
		m_p_grid.GridCellHeight_L(m_grid_input, i, 25);
		for(j=0; j<2; j++)
		{
			if(j==0)
			{
				m_p_grid.GridCellWidth_L(m_grid_input, j+1, 10);
			}
			else
			{
				m_p_grid.GridCellWidth_L(m_grid_input, j+1, 40);
			}
			
			m_p_grid.GridCellControlStatic(m_grid_input, i, j+1);
		}
	}

	m_p_grid.GridCellFont(m_grid_input, 0, 1, "MS Sans Serif", 14);
	m_p_grid.GridCellColor(m_grid_input, 0, 1, BLACK_L, YELLOW_C);
	m_p_grid.GridCellText(m_grid_input, 0, 1, "STATUS");

	m_p_grid.GridCellFont(m_grid_input, 0, 2, "MS Sans Serif", 14);
	m_p_grid.GridCellColor(m_grid_input, 0, 2, BLACK_L, YELLOW_C);
	m_p_grid.GridCellText(m_grid_input, 0, 2, "Description");

	for(i=0; i<m_n_in_cnt; i++)
	{
		m_p_grid.GridCellFont(m_grid_input, i+1, 1, "MS Sans Serif", 10);
		m_p_grid.GridCellColor(m_grid_input, i+1, 1, RGB(st_set.mn_grid_r[0][1], st_set.mn_grid_g[0][1], st_set.mn_grid_b[0][1]), 
													 RGB(st_set.mn_text_r[0][1], st_set.mn_text_g[0][1], st_set.mn_text_b[0][1]));
		m_p_grid.GridCellText(m_grid_input, i+1, 1, "OFF");

		m_p_grid.GridCellFont(m_grid_input, i+1, 2, "MS Sans Serif", 10);
		m_p_grid.GridCellColor(m_grid_input, i+1, 2, YELLOW_L, BLACK_L);
		m_p_grid.GridCellText(m_grid_input, i+1, 2, m_str_in[i]);
	}
}

void CDialog_Part_IO::Init_Output()
{
	int   i, j;
	CString str_tmp;
	
	m_grid_output = (TSpread*)GetDlgItem(IDC_CUSTOM_OUTPUT);
	
	m_p_grid.GridReset(m_grid_output);
	// �빮�� 
	m_p_grid.GridCellSelectDisplay(m_grid_output, TRUE);
	
	m_p_grid.GridRowHeader(m_grid_output, FALSE);
	m_p_grid.GridColHeader(m_grid_output, TRUE);
	m_p_grid.GridHorizontal(m_grid_output, FALSE);
	m_p_grid.GridVertical(m_grid_output, TRUE);
	m_p_grid.GridAutoSize(m_grid_output, FALSE);
	m_p_grid.GridAutoSize(m_grid_output, FALSE);
	m_p_grid.GridCellRows(m_grid_output, m_n_out_cnt);
	m_p_grid.GridCellCols(m_grid_output, 2);
	
	for(i=0; i<m_n_out_cnt+1; i++)
	{
		m_p_grid.GridCellHeight_L(m_grid_output, i, 25);
		for(j=0; j<2; j++)
		{
			if(j==0)
			{
				m_p_grid.GridCellWidth_L(m_grid_output, j+1, 10);
			}
			else
			{
				m_p_grid.GridCellWidth_L(m_grid_output, j+1, 40);
			}
			
			m_p_grid.GridCellControlStatic(m_grid_output, i, j+1);
		}
	}
	
	m_p_grid.GridCellFont(m_grid_output, 0, 1, "MS Sans Serif", 14);
	m_p_grid.GridCellColor(m_grid_output, 0, 1, BLACK_L, YELLOW_C);
	m_p_grid.GridCellText(m_grid_output, 0, 1, "ON / OFF");
	
	m_p_grid.GridCellFont(m_grid_output, 0, 2, "MS Sans Serif", 14);
	m_p_grid.GridCellColor(m_grid_output, 0, 2, BLACK_L, YELLOW_C);
	m_p_grid.GridCellText(m_grid_output, 0, 2, "Description");
	
	for(i=0; i<m_n_out_cnt; i++)
	{
		m_p_grid.GridCellFont(m_grid_output, i+1, 1, "MS Sans Serif", 10);
		m_p_grid.GridCellColor(m_grid_output, i+1, 1, RGB(255, 128, 64), WHITE_C);
		m_p_grid.GridCellText(m_grid_output, i+1, 1, "OFF");
		
		m_p_grid.GridCellFont(m_grid_output, i+1, 2, "MS Sans Serif", 10);
		m_p_grid.GridCellColor(m_grid_output, i+1, 2, GREEN_L, BLACK_L);
		m_p_grid.GridCellText(m_grid_output, i+1, 2, m_str_out[i]);
	}
}

void CDialog_Part_IO::OnInputCheck()
{
	int bit;
	int i;
	m_grid_input = (TSpread*)GetDlgItem(IDC_CUSTOM_INPUT);

	for(i=0; i<m_n_in_cnt; i++)
	{
		bit = (m_n_in_port[i] * 100) + m_n_in_num[i];
		
		if(FAS_IO.Get_In_Bit(bit) == IO_ON)
		{
			m_p_grid.GridCellText(m_grid_input, i+1, 1, "ON");
			m_p_grid.GridCellColor(m_grid_input, i+1, 1, RGB(0, 128, 0), WHITE_C);
		}
		else
		{
			m_p_grid.GridCellText(m_grid_input, i+1, 1, "OFF");
			m_p_grid.GridCellColor(m_grid_input, i+1, 1, RGB(128, 255, 128), BLACK_L);
		}
	}
}

void CDialog_Part_IO::OnOutputCheck()
{
	int bit;
	int i;

	m_grid_output = (TSpread*)GetDlgItem(IDC_CUSTOM_OUTPUT);
	
	for(i=0; i<m_n_out_cnt; i++)
	{
		bit = (m_n_out_port[i] * 100) + m_n_out_num[i];

		if(FAS_IO.Get_Out_Bit(bit) == IO_ON)
		{
			m_p_grid.GridCellText(m_grid_output, i+1, 1, "ON");
			m_p_grid.GridCellColor(m_grid_output, i+1, 1, RGB(255, 128, 64), WHITE_C);
		}
		else
		{
			m_p_grid.GridCellText(m_grid_output, i+1, 1, "OFF");
			m_p_grid.GridCellColor(m_grid_output, i+1, 1, RGB(128, 64, 0), BLACK_C);
		}
	}
}

void CDialog_Part_IO::OnCellClick(WPARAM wParam, LPARAM lParam)
{
	LPSS_CELLCOORD lpcc = (LPSS_CELLCOORD)lParam;
	int output;
	int bit;
	CString str_tmp;
	
	if(lpcc->Col != 1) return;

	if(wParam==IDC_CUSTOM_OUTPUT)
	{
		m_grid_output = (TSpread*)GetDlgItem(IDC_CUSTOM_OUTPUT);

		bit = (m_n_out_port[lpcc->Row-1] * 100) + m_n_out_num[lpcc->Row-1];
		output = FAS_IO.Get_Out_Bit(bit);
		
		FAS_IO.set_out_bit(bit, !output);

		if (!output == IO_ON)
		{
			str_tmp = "On";
		}
		else
		{
			str_tmp = "Off";
		}
		
		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
		{
			//st_msg.mstr_normal_msg.Format("%s did  %s", m_str_out[lpcc->Row-1], str_tmp);
			sprintf(st_msg.c_normal_msg, "%s did  %s", m_str_out[lpcc->Row-1], str_tmp);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}
	}
}

BOOL CDialog_Part_IO::Create()
{
	return CDialog::Create( CDialog_Part_IO::IDD );
}

void CDialog_Part_IO::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class	
	delete this;
	Func.m_p_io = NULL;
	CDialog::PostNcDestroy();
}

void CDialog_Part_IO::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
// 	if(m_p_font != NULL)
// 	{
// 		delete m_p_font;
// 		m_p_font = NULL;
// 	}
	
	KillTimer(TM_IN_READ);
	KillTimer(TM_OUT_READ);
}
