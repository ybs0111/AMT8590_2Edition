// Screen_List_Operation.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Screen_List_Operation.h"

#include "io.h" 
#include "FileDialogST.h"

/* ****************************************************************************** */
/* ��ȭ ���� Ŭ���� �߰�                                                          */
/* ****************************************************************************** */
#include "Dialog_Infor.h"
#include "Dialog_Select.h"
#include "Dialog_Message.h"
/* ****************************************************************************** */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreen_List_Operation

IMPLEMENT_DYNCREATE(CScreen_List_Operation, CFormView)

CScreen_List_Operation::CScreen_List_Operation()
	: CFormView(CScreen_List_Operation::IDD)
{
	//{{AFX_DATA_INIT(CScreen_List_Operation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScreen_List_Operation::~CScreen_List_Operation()
{
}

void CScreen_List_Operation::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreen_List_Operation)
	DDX_Control(pDX, IDC_RADIO_WORK, m_radio_work);
	DDX_Control(pDX, IDC_RADIO_ALARM, m_radio_alarm);
	DDX_Control(pDX, IDC_RADIO_OPERATION, m_radio_operation);
	DDX_Control(pDX, IDC_RADIO_MACHINE, m_radio_machine);
	DDX_Control(pDX, IDC_RADIO_INTERFACE, m_radio_interface);
	DDX_Control(pDX, IDC_MSG_OPERATION_FILE_NAME, m_msg_operation_file_name);
	DDX_Control(pDX, IDC_MSG_OPERATION_FILE, m_msg_operation_file);
	DDX_Control(pDX, IDC_MONTHCAL_OPERATION, m_monthcal_operation);
	DDX_Control(pDX, IDC_LIST_OPERATION_FILE, m_list_operation_file);
	DDX_Control(pDX, IDC_GROUP_OPERATION_TYPE, m_group_operation_type);
	DDX_Control(pDX, IDC_GROUP_OPERATION_LIST, m_group_operation_list);
	DDX_Control(pDX, IDC_BTN_OPERATION_FILE_REFRESH, m_btn_operation_file_refresh);
	DDX_Control(pDX, IDC_BTN_OPERATION_FILE_DEL, m_btn_operation_file_del);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreen_List_Operation, CFormView)
	//{{AFX_MSG_MAP(CScreen_List_Operation)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST_OPERATION_FILE, OnSelchangeListOperationFile)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCAL_OPERATION, OnSelectMonthcalOperation)
	ON_BN_CLICKED(IDC_RADIO_OPERATION, OnRadioOperation)
	ON_BN_CLICKED(IDC_RADIO_INTERFACE, OnRadioInterface)
	ON_BN_CLICKED(IDC_RADIO_MACHINE, OnRadioMachine)
	ON_BN_CLICKED(IDC_BTN_OPERATION_FILE_DEL, OnBtnOperationFileDel)
	ON_BN_CLICKED(IDC_BTN_OPERATION_FILE_REFRESH, OnBtnOperationFileRefresh)
	ON_BN_CLICKED(IDC_RADIO_ALARM, OnRadioAlarm)
	ON_BN_CLICKED(IDC_RADIO_WORK, OnRadioWork)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreen_List_Operation diagnostics

#ifdef _DEBUG
void CScreen_List_Operation::AssertValid() const
{
	CFormView::AssertValid();
}

void CScreen_List_Operation::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreen_List_Operation message ICTs

void CScreen_List_Operation::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	/* ************************************************************************** */
	/* ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�                                              */
	/* ************************************************************************** */
// 	mp_operation_list_font = NULL;
// 	mp_operation_list_font = new CFont;
// 	mp_operation_list_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	/* ************************************************************************** */

	/* ************************************************************************** */
    /* ����� �˶� BIN ��� ���� ���� ���� ����                                 */
    /* ************************************************************************** */
	mn_type_select = 1;					// �ʱ� ���� ���� ���� 

	mstr_selected_Date.Empty();			// ���õ� ��¥ ���� ���� ���� �ʱ�ȭ 
	mstr_operation_file_name.Empty();	// ���õ� ���� �̸��� �����ϱ� ���� ���� ����

	mstr_default_path = "D:\\AMTLOG\\";  

	OnOperation_List_Full_Path_Set(mn_type_select);			// ���� ���� �ε��� ��ü ���� ���� ���� �Լ� */
	/* ************************************************************************** */

	mstr_file_full_name = "";								// Save as�� Reset~ 2K4/08/16/ViboX

	OnOperation_List_GroupBox_Set();
	OnOperation_List_Lable_Set();
	OnOperation_List_EditBox_Set();
	OnOperation_List_RadioButton_Set();
	OnOperation_List_State_Change(mn_type_select);

	OnOperation_List_Create_ImageList();	
	m_list_operation_file.SetImageList(&mp_operation_image_list);

	OnOperation_List_Init_List(LPCTSTR(mstr_full_path));	// �˶� ��� ��� ȭ�鿡 ����� ���� ��� �ʱ�ȭ �۾� �Լ�

	m_monthcal_operation.SetMaxSelCount(2);
}

void CScreen_List_Operation::OnDestroy() 
{
	mp_operation_image_list.DeleteImageList();

	/* ************************************************************************** */
	/* ������ ��Ʈ ���� �����Ѵ�                                                  */
	/* ************************************************************************** */
// 	delete mp_operation_list_font;
// 	mp_operation_list_font = NULL;
	/* ************************************************************************** */

	CFormView::OnDestroy();
}

void CScreen_List_Operation::OnOperation_List_GroupBox_Set()
{
	CSxLogFont operation_list_font(15,FW_SEMIBOLD,false,"MS Sans Serif");

//	m_group_operation_list.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
//	m_group_operation_list.SetBackgroundColor(RGB(201, 201, 151), RGB(255, 255, 204));
	m_group_operation_list.SetFont(operation_list_font);
	m_group_operation_list.SetCatptionTextColor(RGB(145,25,0));
	m_group_operation_list.SetFontBold(TRUE);

//	m_group_operation_type.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
//	m_group_operation_type.SetBackgroundColor(RGB(201, 201, 151), RGB(255, 255, 204));
	m_group_operation_type.SetFont(operation_list_font);
	m_group_operation_type.SetCatptionTextColor(RGB(145,25,0));
	m_group_operation_type.SetFontBold(TRUE);
}

void CScreen_List_Operation::OnOperation_List_Lable_Set()
{	
	m_msg_operation_file.SetFont(Func.mp_operation_list_font);
	m_msg_operation_file.SetWindowText(_T("Select Display File"));
	m_msg_operation_file.SetCenterText();
	m_msg_operation_file.SetColor(RGB(0,0,255));
	m_msg_operation_file.SetGradientColor(RGB(255,0,0));
	m_msg_operation_file.SetTextColor(RGB(255,255,255));

	m_msg_operation_file_name.SetFont(Func.mp_operation_list_font);
	m_msg_operation_file_name.SetWindowText(_T(""));
	m_msg_operation_file_name.SetCenterText();
	m_msg_operation_file_name.SetColor(RGB(0,0,255));
	m_msg_operation_file_name.SetGradientColor(RGB(0,0,0));
	m_msg_operation_file_name.SetTextColor(RGB(255,255,255));
}

void CScreen_List_Operation::OnOperation_List_EditBox_Set()
{	
	m_edit_operation_content.SubclassDlgItem(IDC_EDIT_OPERATION_DISPLAY, this);
	m_edit_operation_content.bkColor( RGB(50, 100, 150) );
	m_edit_operation_content.textColor( RGB(255, 255,255) );
	m_edit_operation_content.setFont(-14, FW_BOLD, DEFAULT_PITCH | FF_DONTCARE, "MS Mincho");
}

void CScreen_List_Operation::OnOperation_List_RadioButton_Set()
{
	//Set images
    m_radio_operation.SetImage(IDB_REDBUTTON, 15);
	m_radio_interface.SetImage(IDB_REDBUTTON, 15);
    m_radio_machine.SetImage(IDB_REDBUTTON, 15);
	m_radio_alarm.SetImage(IDB_REDBUTTON, 15);
	m_radio_work.SetImage(IDB_REDBUTTON, 15);
}

void CScreen_List_Operation::OnOperation_List_State_Change(int n_state)
{
	switch(n_state)
	{
	case 1 :
		m_radio_operation.Depress(true);
		m_radio_interface.Depress(false);
		m_radio_machine.Depress(false);
		m_radio_alarm.Depress(false);
		m_radio_work.Depress(false);
		break;

	case 2 :
		m_radio_operation.Depress(false);
		m_radio_interface.Depress(true);
		m_radio_machine.Depress(false);
		m_radio_alarm.Depress(false);
		m_radio_work.Depress(false);
		break;

	case 3 :
		m_radio_operation.Depress(false);
		m_radio_interface.Depress(false);
		m_radio_machine.Depress(true);
		m_radio_alarm.Depress(false);
		m_radio_work.Depress(false);
		break;

	case 4 :
		m_radio_operation.Depress(false);
		m_radio_interface.Depress(false);
		m_radio_machine.Depress(false);
		m_radio_alarm.Depress(true);
		m_radio_work.Depress(false);
		break;

	case 5 :
		m_radio_operation.Depress(false);
		m_radio_interface.Depress(false);
		m_radio_machine.Depress(false);
		m_radio_alarm.Depress(false);
		m_radio_work.Depress(true);
		break;

	default:
		break;
	}
}

void CScreen_List_Operation::OnOperation_List_Create_ImageList()
{
	BOOL bRetValue = FALSE;

	// Create image list
	bRetValue = mp_operation_image_list.Create(16, 16, ILC_COLOR32 | ILC_MASK, 5, 1);
	ASSERT(bRetValue == TRUE);
}

int CScreen_List_Operation::OnOperation_List_Init_List(LPCTSTR pszPath)
{
	int mn_chk;					// �Լ� ���� �÷��� ���� ���� 
    CString str_path = pszPath; // ���� ���� ���� 

	HANDLE hFind;
    WIN32_FIND_DATA fd;
	int mn_count = 0;			// ����Ʈ �ڽ� ��Ʈ�ѿ� �߰��� ���� ���� ���� ���� ���� 

	if (str_path.Right (1) != "\\")
        str_path += "\\";

	str_path += "*.*";

	// ������ �� ��� �ִ��� ã�ƺ���. 2K4/08/31/ViboX
/*	if ((hFind = ::FindFirstFile ((LPCTSTR) str_path, &fd)) != INVALID_HANDLE_VALUE) 
	{
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		{
			mn_count++;
        }

        while (::FindNextFile (hFind, &fd)) 
		{
            mn_count++;
        }
		::FindClose(hFind);
    }
*/  
    if ((hFind = ::FindFirstFile ((LPCTSTR) str_path, &fd)) != INVALID_HANDLE_VALUE) 
	{
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		{
			mn_chk = AddItem (mn_count, &fd);
			if (mn_chk == TRUE)  mn_count++;
        }

        while (::FindNextFile (hFind, &fd)) 
		{
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				mn_chk = AddItem (mn_count, &fd);
				if (mn_chk == FALSE) 
				{
					break;
				}
				else if (mn_chk == RET_ERROR)  mn_count--;
			}
            mn_count++;
        }
		::FindClose(hFind);
    }

	m_list_operation_file.SetCurSel(mn_count - 2);
	
	return mn_count;
}

void CScreen_List_Operation::OnOperation_List_Full_Path_Set(int n_selected)
{
	switch(n_selected)
	{
	case 1 :  // Operation ��� ���� 
		mstr_full_path = mstr_default_path + "Log\\Operation\\";
		break;
	case 2 :  // Interface ��� ���� 
		mstr_full_path = mstr_default_path + "Log\\Interface\\";
		break;
	case 3 :  // Machine ��� ���� 
		mstr_full_path = mstr_default_path + "Log\\Machine\\";
		break;
	case 4 :  // Alarm ��� ���� 
		mstr_full_path = mstr_default_path + "Alarm\\daily\\";
		break;
	case 5 :  // Work ��� ���� 
		mstr_full_path = mstr_default_path + "Log\\Time\\";
		break;
	default :
		break;
	}
}

BOOL CScreen_List_Operation::AddItem(int n_index, WIN32_FIND_DATA *pfd)
{
	int mn_pos;

	HICON	hIcon = NULL;

	/* ************************************************************************** */
    /* �ش� ���� ����Ʈ ��Ʈ�ѿ� �߰����� ���� �˻��Ѵ�                           */
    /* ************************************************************************** */
	if (!mstr_selected_Date.IsEmpty()) 
	{
		mstr_temp_file = (pfd->cFileName);
		mn_pos = mstr_temp_file.Find(mstr_selected_Date);  // �޷¿��� ������ ��¥ ������ ���� �̸��� �����ϴ��� �˻� 
		if (mn_pos == -1)  // ������ ��¥ ������ ���� �̸��� �������� �ʴ� ��� 
		{
			return RET_ERROR;
		}
	}
	/* ************************************************************************** */

	hIcon = AfxGetApp()->LoadIcon(IDI_OPEN_FOLDER);
	mp_operation_image_list.Add(hIcon);

	if (m_list_operation_file.AddString(_T(pfd->cFileName), n_index - 1) == -1)  return FALSE;

    return TRUE;
}

void CScreen_List_Operation::OnOperation_List_Selected_File_Load(CString str_folder, CString str_file)
{
	int ndx;					// ����Ʈ �ڽ��� ��µ� ���ڿ� ��ü ���� ���� ���� ���� 
	int mn_existence;			// ���� ���� ���� ���� ���� 
	CString mstr_chk_file;		// ����� ���Ͽ� ���� [����]+[���ϸ�] ���� ���� 
	CString mstr_description;	// ���õ� ���� ���� �ӽ� ���� ���� 
	CString mstr_temp_file;		// ���� ���õ� ���ϸ� �ӽ� ���� ���� 
	char fileName[256];			// ����� ���� ���� ���� ���� 
	char buffer[256001];	// ���� ���� �� �� ���� ���� �ӽ� ���� ���� 

	m_msg_operation_file.SetWindowText(_T("Select Display File"));

	/* ************************************************************************** */
    /* ���� ���õ� ������ �̹� ��µ� �������� �˻��Ѵ�                           */
	/* -> ���� �̸� ��� ����Ʈ �ڽ����� �о ���ؾ� �Ѵ�                     */
    /* ************************************************************************** */
	mstr_temp_file = m_msg_operation_file_name.GetWindowText();
	mstr_temp_file.MakeUpper();
	mstr_temp_file.TrimLeft(' ');               
	mstr_temp_file.TrimRight(' ');

	if (mstr_operation_file_name == mstr_temp_file)  return ;  // ���õ� ������ ���� ��µǾ� �ִ� ���ϰ� ������ ��� ���� 
	/* ************************************************************************** */

	mstr_chk_file = str_folder + str_file;  // ���õ� ���Ͽ� ���� [����]+[���ϸ�] ���� 

	sprintf(fileName, "%s", mstr_chk_file);
	mn_existence = access(fileName,0) ;
	if(mn_existence != -1)  
	{
		FILE *fp = fopen ( fileName, "r" );

		if ( fp == (FILE *)NULL ) 
		{
			m_msg_operation_file.SetWindowText(_T("File Open Error~!!"));
			return ;
		}

		mstr_description.Empty();  // ���� ���� ���� ���� �ʱ�ȭ 

		while ( !feof(fp) )
		{
			if ( fgets ( buffer, 256000, fp ) == NULL )  break;

			if ( strlen(buffer) )   buffer[strlen(buffer)-1] = 0;
			strcat ( buffer, "\r\n" );

			mstr_description += buffer;
		}
		fclose(fp);

		((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->SetWindowText(_T("")); 
		((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->SetFocus();

		ndx = ((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->GetWindowTextLength();

		((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->SendMessage(EM_SETSEL, ndx, ndx);
//		((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->SendMessage(EM_REPLACESEL, 0, (LPARAM)(LPCSTR)mstr_description);
		((CEdit*)GetDlgItem(IDC_EDIT_OPERATION_DISPLAY))->SetWindowText(_T(mstr_description));
	}
	else   
	{
		m_msg_operation_file.SetWindowText(_T("Not Exist File~!"));
		return ;
	}
}

int CScreen_List_Operation::OnOperation_List_Selected_File_Name_Check()
{
	int mn_pos;  // ��ġ ���� ���� ���� 
	CString mstr_chk_file;  // ���õ� ���Ͽ� ���� [����]+[���ϸ�] ���� ���� 
	CString mstr_chk_ext;  // ���� ���� �� Ȯ���� �������� �����ϱ� ���� ���� 

	m_msg_operation_file.SetWindowText(_T("Select Display File"));

	mstr_operation_file_name.MakeUpper();
	mstr_operation_file_name.TrimLeft(' ');
	mstr_operation_file_name.TrimRight(' ');

	if (mstr_operation_file_name.IsEmpty()) 
	{
		m_msg_operation_file.SetWindowText(_T("File name error~!"));
		return FALSE;
	}

	mn_pos = mstr_operation_file_name.Find(" ");		// ���� ���� ���� �˻� 
	if (mn_pos != -1)
	{
		m_msg_operation_file.SetWindowText(_T("File name in space error~!"));
		return FALSE;
	}

	mstr_chk_file = mstr_full_path + mstr_operation_file_name;  // ���Ͽ� ���� [����]+[���ϸ�] ���� ���� 
	mn_pos = mstr_chk_file.Find(".");						// Ȯ���� ��ġ �˻� 
	if (mn_pos == -1) mstr_chk_file += ".TXT";
	else 
	{
		mstr_chk_ext = mstr_chk_file.Mid(mn_pos);	// ���õ� ���� ���� �� ���� Ȯ���� �������� ���� 
		if (mstr_chk_ext != ".TXT")					// .TXT �̿ܿ��� ������ ó��
		{
			m_msg_operation_file.SetWindowText(_T("An extension input error occurrence."));
			return FALSE;
		}
	}

	return TRUE;
}

void CScreen_List_Operation::OnOperation_List_Reset_AllItem()
{	
	mstr_selected_Date.Empty();						// ���õ� ��¥ ���� ���� ���� �ʱ�ȭ 
	mstr_operation_file_name.Empty();					// ���õ� ���� �̸� ���� ���� ���� �ʱ�ȭ 

	OnOperation_List_Full_Path_Set(mn_type_select);		// ���� ���� �ε��� ��ü ���� ���� ���� �Լ�
	OnOperation_List_State_Change(mn_type_select);		// ���� ���� ���� ���� ��ư ���� ���� �Լ�

	/* ************************************************************************** */
	/* �ش� ���� �ȿ� �����ϴ� ���� ���� ���Ӱ� ����Ʈ �ڽ� ��Ʈ�ѿ� �߰�         */
	/* ************************************************************************** */
	m_list_operation_file.ResetContent();				// ����Ʈ �ڽ� ��Ʈ�ѿ� �߰��� ��� ���� ���� 
	mp_operation_image_list.DeleteImageList();			// �̹��� ����Ʈ�� ������ ��� ���� ���� ���� 

	OnOperation_List_Create_ImageList();				// �׽�Ʈ ��� ��� ȭ�鿡 ����� �̹��� ���� �Լ�

	// Associate image list to list box
	m_list_operation_file.SetImageList(&mp_operation_image_list);

	OnOperation_List_Init_List(LPCTSTR(mstr_full_path)); // �׽�Ʈ ��� ��� ȭ�鿡 ����� ���� ��� �ʱ�ȭ �۾� �Լ�

	mstr_file_full_name = "";							// Save as�� Reset~ 2K4/08/16/ViboX
	m_msg_operation_file_name.SetWindowText(_T(mstr_file_full_name));

	m_msg_operation_file.SetWindowText(_T("Select Display File"));
	/* ************************************************************************** */
}

void CScreen_List_Operation::OnOperation_List_Display_Selected_Day()
{
	COleDateTime ctMinRange, ctMaxRange;
	CString mstr_date_msg, mstr_chk_file;

	if (m_monthcal_operation.GetSelRange(ctMinRange, ctMaxRange))
	{
		/* ********************************************************************** */
		/* ����� ���� ���� �����Ѵ�                                              */
		/* ********************************************************************** */
		switch(mn_type_select)
		{
		case 1 :  // Operation ��� ���� �̸� ���� ���� 
			mstr_date_msg = ctMinRange.Format(_T("%Y%m%d"));
			mstr_chk_file = "OP" + mstr_date_msg;
			break;
		case 2 :  // Interface ��� ���� �̸� ���� ���� 
			mstr_date_msg = ctMinRange.Format(_T("%Y%m%d"));
			mstr_chk_file = "IT" + mstr_date_msg;
			break;
		case 3 :  // Machine ��� ���� �̸� ���� ���� 
			mstr_date_msg = ctMinRange.Format(_T("%Y%m"));
			mstr_chk_file = "MC" + mstr_date_msg;
			break;
		case 4 :  // Alarm ��� ���� �̸� ���� ���� 
			mstr_date_msg = ctMinRange.Format(_T("%Y%m%d"));
			mstr_chk_file = "DY" + mstr_date_msg;
			break;
		default :
			break;
		}
		/* ********************************************************************** */

		if (mstr_date_msg.IsEmpty()) return;		// ���õ� ��¥ ������ ������ ��� ���� 

		if (mstr_selected_Date != mstr_chk_file)	// ������ ��¥�� ���� ���� ������� �˻� 
		{
			mstr_selected_Date = mstr_chk_file;		// ���� ������ ��¥�� ���� ���� ���� ���� 

			/* ****************************************************************** */
			/* �ش� �����ȿ� �����ϴ� ���� ���� ���Ӱ� ����Ʈ �ڽ��� �߰�         */
			/* ****************************************************************** */
			m_list_operation_file.ResetContent();		// ����Ʈ �ڽ� ��Ʈ�ѿ� ������ ��� ���� ���� 
			mp_operation_image_list.DeleteImageList();  // �̹��� ����Ʈ�� ������ ��� ���� ���� 

			OnOperation_List_Create_ImageList();		// �׽�Ʈ ��� ��� ȭ�鿡 ����� �̹��� ���� �Լ�

			// Associate image list to list box
			m_list_operation_file.SetImageList(&mp_operation_image_list);

			OnOperation_List_Init_List(LPCTSTR(mstr_full_path)); // �׽�Ʈ ��� ��� ȭ�鿡 ����� ���� ��� �ʱ�ȭ �۾� �Լ�
			/* ****************************************************************** */
		}
	}
}

void CScreen_List_Operation::OnSelchangeListOperationFile() 
{
	int mn_index = m_list_operation_file.GetCurSel();  // ���� ���õ� ����Ʈ ��Ʈ�� ��ġ ���� ���� 

	if (mn_index != LB_ERR)  // ������ ���ÿ� ���� �߻��ߴ��� �˻� 
	{
		m_list_operation_file.GetText(mn_index, mstr_operation_file_name);				// ���� ���õ� ���� ���� ��´� 

		OnOperation_List_Selected_File_Load(mstr_full_path, mstr_operation_file_name);	// ���õ� ���� ���� ��� �Լ�

		mstr_file_full_name = mstr_full_path + mstr_operation_file_name;				// Save as ��ų ��, ����Ѵ�. 2K4/08/16/ViboX

		m_msg_operation_file_name.SetWindowText(_T(mstr_operation_file_name));			// ���õ� ������ �̸��� ��� ��Ų��.		
	}
}

void CScreen_List_Operation::OnSelectMonthcalOperation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOperation_List_Display_Selected_Day();			// ���� ���õ� ��¥ ���� ������� ����� ���� ���� ���� �Լ�
	
	*pResult = 0;
}

void CScreen_List_Operation::OnRadioOperation() 
{
	if (mn_type_select != 1)  
	{
		mn_type_select = 1;								// Operation ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�

		OnOperation_List_Reset_AllItem();				// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
	}
}

void CScreen_List_Operation::OnRadioInterface() 
{
	if (mn_type_select != 2)  
	{
		mn_type_select = 2;								// Interface ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�

		OnOperation_List_Reset_AllItem();				// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
	}
}

void CScreen_List_Operation::OnRadioMachine() 
{
	if (mn_type_select != 3)  
	{
		mn_type_select = 3;								// Machine ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�

		OnOperation_List_Reset_AllItem();				// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
	}
}

void CScreen_List_Operation::OnBtnOperationFileDel() 
{
	char path[MAX_PATH] = {0};
	//������ �۾���θ� ���� ���� �Ѵ�.
	GetCurrentDirectory(MAX_PATH, path);

	if (mstr_file_full_name == "")	return;			// ���� ������ ���� ��쿡�� ����...

	CFileDialogST	dlg(FALSE, NULL, mstr_operation_file_name, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, _T("All files\0*.*\0"), this);
	CString			sPathName, str_temp_file, str_ext, str_chk_ext;
	int				nRetValue, n_pos;

	nRetValue = dlg.DoModal();
	
	if (nRetValue == IDOK)
	{
		sPathName = dlg.GetPathName();

		n_pos = mstr_file_full_name.Find(".");			// ���� ������ Ȯ���� ��ġ �˻�

		if (n_pos == -1)								// ���纻 Ȯ���� ������
		{
			str_ext = ".txt";
		}
		else 
		{		
			str_ext = mstr_file_full_name.Mid(n_pos);	// ���� ���� Ȯ���� ����
		}

		n_pos = sPathName.Find(".");					// ���纻 Ȯ���� ��ġ �˻�
	
		if (n_pos == -1)								// ���纻 Ȯ���� ������
		{
			sPathName += _T(str_ext);					// ���纻 Ȯ���� �߰�
		}

		CopyFile(mstr_file_full_name, sPathName, TRUE);
		
		SetCurrentDirectory(path);						// �۾� ��θ� ���� ��η� ���� �Ѵ�.
	}
}

void CScreen_List_Operation::OnBtnOperationFileRefresh() 
{
	if (mn_type_select != 1)
	{
		mn_type_select = 1;								// �Ϻ� �˶� ����Ʈ ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�
	}

	OnOperation_List_Reset_AllItem();					// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
}

void CScreen_List_Operation::OnRadioAlarm() 
{
	if (mn_type_select != 4)
	{
		mn_type_select = 4;								// Barcode ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�
		
		OnOperation_List_Reset_AllItem();				// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
	}
}

void CScreen_List_Operation::OnRadioWork() 
{
	if (mn_type_select != 5)
	{
		mn_type_select = 5;								// Barcode ���� ���� 
		OnOperation_List_State_Change(mn_type_select);	// ���� ���� ���� ���� ��ư ���� ���� �Լ�
		
		OnOperation_List_Reset_AllItem();				// ����Ʈ ��Ʈ�ѿ� ������ ��� ������ ���� ���� �� �� ���� �Լ�
	}
}