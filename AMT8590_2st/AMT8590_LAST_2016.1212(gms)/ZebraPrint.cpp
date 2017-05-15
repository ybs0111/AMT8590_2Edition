// ZebraPrint.cpp: implementation of the CZebraPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "ZebraPrint.h"
#include "io.h"			// ���� ���� ���� �˻� �Լ� ȣ���ϱ� ���ؼ��� �ݵ�� �ʿ�
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CZebraPrint clsZebra;

CZebraPrint::CZebraPrint()
{
	m_nStstusMode = 0;
}

CZebraPrint::~CZebraPrint()
{

}

bool CZebraPrint::OnPrintStatus(CString strCheckData, int nPort)
{
	//3.22 Keyence
	int     nLength;  // ������ �� ���� ���� ���� 
	CString strBody;  // BODY ������ ���� ���� 
	CString str_tmp;
	char  cp_cmd[1024];
	
	int     i=0, j=0;
	int     nStartIndex, nEndIndex;  // BCR �������� ���� �� ���� ��ġ ���� ���� 
	int     nReceivedDataCount=0;
	CString strTempDataCount;  // ������ ���� ���� ���� 
	int		nResultData[100];
	
	CString str_Tmp;
	CString str_Tmp_Data;
	
	memset(&cp_cmd, 0, sizeof(cp_cmd));  // ������ ���� ���� �ʱ�ȭ 
	
	// **************************************************************************
	// ���� ������ �ּ� ���� �˻��Ѵ� [�ּ� 3�ڸ� �̻�]                          
	// **************************************************************************
	nLength = strCheckData.GetLength();
	if(nLength < 3)
	{
		return false;
	}
	// **************************************************************************
	strCheckData.TrimLeft("\r\n");
	strCheckData.TrimRight("\r\n");
	
	strBody = strCheckData;//.Mid(0, nLength - 1);  // [����] ���� 
	strBody.TrimLeft(0x02);		// STX ���� 
	strBody.TrimRight(0x03);	// ETX ���� 

	if(nLength > 50)					//HS�� ����Ÿ�� 50�ڸ��� ����
	{
		strBody.Replace("\2", "");		// �߰��� �ִ� STX ����
		strBody.Replace("\3", ",");		// �߰��� �ִ� ETX�� ,�� ����
	}
	else
	{
		strBody = strBody + ",";
	}
	
/*	
	// **************************************************************************
	// ���� �޽��� ���� ���� �˻��Ѵ�                                            
	// **************************************************************************
	if(strBody.Find("ERROR") >= 0)
	{
		sprintf(st_msg.c_normal_msg,"Label Print Status Received ERROR!");
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0 , NORMAL_MSG);
		return false;
	}
	// **************************************************************************
*/	
	sprintf(cp_cmd, "%s", strBody);
	nLength = strBody.GetLength();
	
	nReceivedDataCount = 0;
	nStartIndex = 0;
	
	// ==============================================================================
	// ����� ���� BCR ������ ���� ������ �����Ѵ�
	// ==============================================================================
	for(j = 0 ; j < 25 ; j++)
	{	
		nEndIndex   = strBody.Find(",", nStartIndex);  // BCR ������ ���� ��ġ ���� 
		
		if (nEndIndex == -1)
		{
			if (nLength - nStartIndex > 0)
			{
				nEndIndex = nLength - 1;
			}
			else
			{
				break;
			}
		}
		
		nResultData[j] = atoi(strBody.Mid(nStartIndex, nEndIndex - nStartIndex));  // BCR ������ ���ڿ� �Ľ� 
		nReceivedDataCount++;
		nStartIndex = nEndIndex + 1;
		
		OnPrintStatus(j, nResultData[j], nPort);
	}

	m_nPrintStatusBin = NVR_PASS;

	return true;
}

void CZebraPrint::Rewind_Mode_TCP(int port)
{
	//2016.0615
	if( st_handler.mn_curr_back_conv == CTL_YES || st_handler.n_without_smema_8580_mc == CTL_YES || st_basic.nBcrFeederUse[port] != CTL_YES )
		return;

	sprintf(st_client[port].ch_send,"%s","^XA^MMT^XZ");//2015,0109
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + port, CLIENT_SEND, port); // LABEL CLIENT	
}

void CZebraPrint::Print_Complete_Set_TCP(int port)
{
/*	CString mstr_data[3];

	mstr_data[0] = "^XA^SXK,D,Y,Y";
	mstr_data[1].Format("%d", st_basic.n_Port[port]);
	mstr_data[2] = "^XZ";

	sprintf(st_client[port].ch_send,"%s,%s,%s%s", mstr_data[0], st_basic.mstr_IP[port], mstr_data[1], mstr_data[2]);
	::PostMessage(st_handler.hWnd, WM_CLIENT_MSG_2, CLIENT_SEND, port); // LABEL CLIENT	*/
}

void CZebraPrint::Print_Complete_Reset_TCP(int port)
{
/*	CString mstr_data[3];
	
	mstr_data[0] = "^XA^SXK,D,N,N";
	mstr_data[1].Format("%d", st_basic.n_Port[port]);
	mstr_data[2] = "^XZ";
	
	sprintf(st_client[port].ch_send,"%s,%s,%s%s", mstr_data[0], st_basic.mstr_IP[port], mstr_data[1], mstr_data[2]);
	::PostMessage(st_handler.hWnd, WM_CLIENT_MSG_2, CLIENT_SEND, port); // LABEL CLIENT	*/
}

void CZebraPrint::Printer_Status_TCP(int port)
{
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + port, CLIENT_CONNECT, port); // LABEL CLIENT	
	::Sleep(1000);
	sprintf(st_client[port].ch_send,"%s","~HS");
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + port, CLIENT_SEND, port); // LABEL CLIENT	
}


bool CZebraPrint::OnPrintStatus_Serial(CString strCheckData, int nPort)
{
/*	//3.22 Keyence
	int     nLength;  // ������ �� ���� ���� ���� 
	CString strBody;  // BODY ������ ���� ���� 
	
	char  cp_cmd[1024];
	
	int     j;
	int     nStartIndex, nEndIndex;  // BCR �������� ���� �� ���� ��ġ ���� ���� 
	int     nReceivedDataCount=0;
	CString strTempDataCount;  // ������ ���� ���� ���� 
	int     nResultData[100];
	
	CString str_Tmp;
	CString str_Tmp_Data;
	
	memset(&cp_cmd, 0, sizeof(cp_cmd));  // ������ ���� ���� �ʱ�ȭ 
	
	// **************************************************************************
	// ���� ������ �ּ� ���� �˻��Ѵ� [�ּ� 3�ڸ� �̻�]                          
	// **************************************************************************
	nLength = strCheckData.GetLength();
	if(nLength < 3)
	{
		return false;
	}
	// **************************************************************************
	strCheckData.TrimLeft("\r\n");
	strCheckData.TrimRight("\r\n");

	strBody = strCheckData;//.Mid(0, nLength - 1);  // [����] ���� 
	strBody.TrimLeft(0x02);
	strBody.TrimRight(0x03);
	strBody = strBody + ",";
	
	// **************************************************************************
	// ���� �޽��� ���� ���� �˻��Ѵ�                                            
	// **************************************************************************
	if(strBody.Find("ERROR") >= 0)
	{
		sprintf(st_msg.c_normal_msg,"Label Print ERROR!!!");
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0 , NORMAL_MSG);
		return false;
	}
	// **************************************************************************
	
	sprintf(cp_cmd, "%s", strBody);
	nLength = strBody.GetLength();
		
	nReceivedDataCount = 0;
	nStartIndex = 0;

	// ==============================================================================
	// ����� ���� BCR ������ ���� ������ �����Ѵ�
	// ==============================================================================
		for(j = 0 ; j < 13 ; j++)
		{

			nEndIndex   = strBody.Find(",", nStartIndex);  // BCR ������ ���� ��ġ ���� 
			
			if (nEndIndex == -1)
			{
				if (nLength - nStartIndex > 0)
				{
					nEndIndex = nLength - 1;
				}
				else
				{
					break;
				}
			}

			nResultData[j] = atoi(strBody.Mid(nStartIndex, nEndIndex - nStartIndex));  // BCR ������ ���ڿ� �Ľ� 
			nReceivedDataCount++;
			nStartIndex = nEndIndex + 1;

			if (st_barcode.n_barcode_hs_cnt == 0)
 			{
				OnPrintStatus(j, nResultData[j], nPort);
				if (j == 11) 
				{
					st_barcode.n_barcode_hs_cnt += 1;
					break;
				}
 			}
 			else if (st_barcode.n_barcode_hs_cnt == 1)
 			{
				OnPrintStatus(j+12, nResultData[j], nPort);
				if (j == 10) 
				{
					st_barcode.n_barcode_hs_cnt += 1;
					break;
				}
 			}
 			else if (st_barcode.n_barcode_hs_cnt == 2)
 			{
				OnPrintStatus(j+23, nResultData[j], nPort);
				if (j == 1) 
				{
					st_barcode.n_barcode_hs_cnt = 0;
					break;
				}
 			}
		}
		
*/		
	return true;
}

void CZebraPrint::Rewind_Mode_Serial(int port)
{
/*	CString strLabelPrint;
	
	CString str_print_data;
	
	str_print_data = "^XA^MMR^XZ";	//Rewind
	strLabelPrint.Format("%c%s%c", 0x02, str_print_data, 0x03);//���ڵ� ������ �б� ���� ���
	
	st_serial.mstr_snd[port] = strLabelPrint;
	::PostMessage(st_handler.hWnd, WM_DATA_SEND, port + 1, 0);
	::Sleep(100);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[BCR Test] %s",strLabelPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}*/
}

void CZebraPrint::Print_Complete_Set_Serial(int port)
{
/*	CString strLabelPrint;
	
	CString str_print_data;
	
	str_print_data = "^XA^SXK,A,Y,Y^XZ";//20120906
	strLabelPrint.Format("%c%s%c", 0x02, str_print_data, 0x03);//���ڵ� ������ �б� ���� ���
	
	st_serial.mstr_snd[port] = strLabelPrint;
	::PostMessage(st_handler.hWnd, WM_DATA_SEND, port, 0);
	::Sleep(100);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[BCR Test] %s",strLabelPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}*/
}

void CZebraPrint::Print_Complete_Reset_Serial(int port)
{
/*	CString strLabelPrint;
	
	CString str_print_data;
	
	str_print_data = "^XA^SXK,A,N,N^XZ";//20120906
	strLabelPrint.Format("%c%s%c", 0x02, str_print_data, 0x03);//���ڵ� ������ �б� ���� ���
	
	st_serial.mstr_snd[port] = strLabelPrint;
	::PostMessage(st_handler.hWnd, WM_DATA_SEND, port + 1, 0);
	::Sleep(100);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[BCR Test] %s",strLabelPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}*/
}


int CZebraPrint::Rewind_Mode_LPT1()
{
	CString str_print_data;
	
	str_print_data = "^XA^MMR^XZ";	//Rewind
	
	if(OnOutLptPort(str_print_data) == CTLBD_RET_ERROR)
	{
		return CTLBD_RET_ERROR;
	}
	
	return CTLBD_RET_GOOD;
}

int CZebraPrint::Print_Complete_Set_LPT1()	//20120630
{
	CString str_print_data;
	
	str_print_data = "^XA^SXK,B,Y,Y^XZ";//20120906
	
	if(OnOutLptPort(str_print_data) == CTLBD_RET_ERROR)
	{
		return CTLBD_RET_ERROR;
	}
	
	return CTLBD_RET_GOOD;
}

int CZebraPrint::Print_Complete_Reset_LPT1()	//20120630
{
	CString str_print_data;
	
	str_print_data = "^XA^SXK,B,N,N^XZ";//20120906
	
	if(OnOutLptPort(str_print_data) == CTLBD_RET_ERROR)
	{
		return CTLBD_RET_ERROR;
	}
	
	return CTLBD_RET_GOOD;
}

void CZebraPrint::Printer_Status_Serial(int port)
{
/*	CString strLabelPrint;
	
	CString str_print_data;
	
	str_print_data = "~HS";//20120906
	strLabelPrint.Format("%c%s%c", 0x02, str_print_data, 0x03);//���ڵ� ������ �б� ���� ���
	
	st_serial.mstr_snd[port] = strLabelPrint;
	::PostMessage(st_handler.hWnd, WM_DATA_SEND, port, 0);
	::Sleep(100);
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[BCR Test] %s",strLabelPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}*/
}

void CZebraPrint::OnPrintStatus(int nRtnSplit, int nFlagName, int nPort)
{
	int nComPort = nPort;
	
	switch(nRtnSplit)
	{
		case JPL_COMM:
			m_nComm				= nFlagName;
			break;

		case JPL_PAPER_OUT_FLAG:	//���� ���� 
			m_nPaperOutFlag		= nFlagName;
			break;

		case JPL_PAUSE_FLAG:		//Pause ��ư üũ
			m_nPauseFlag		= nFlagName;
			break;

		case JPL_LABEL_LENGTH:
			m_nLabelLength		= nFlagName;
			break;

		case JPL_RCV_BUF_FORMAT_NO:
			m_nRcvBufFormatNo	= nFlagName;
			break;

		case JPL_BUF_FULL_FLAG:
			m_nBufFullFlag		= nFlagName;
			break;

		case JPL_COMM_DMODE_FLAG:
			m_nCommDModeFlag	= nFlagName;
			break;

		case JPL_PARTIAL_FORMAT_FLAG:
			m_nPartialFormatFlag= nFlagName;
			break;

		case JPL_UNUSED:
			m_nUnused			= nFlagName;
			break;

		case JPL_CORRUP_RAM_FLAG:
			m_nCorruptRamFlag	= nFlagName;
			break;

		case JPL_UNDER_TEM_RANGE:
			m_nUnderTemRange	= nFlagName;
			break;

		case JPL_OVER_TEM_RANGE:
			m_nOverTemRange		= nFlagName;
			break;

		case JPL_FUNC_SETTING:
			m_nFuncSetting			= nFlagName;
			break;

		case JPL_UNUSED1:
			m_nUnused				= nFlagName;
			break;

		case JPL_HEAD_UP_FLAG:		//Head Up, Down üũ
			m_nHeadUpFlag			= nFlagName;
			break;

		case JPL_RIBBON_OUTFLAG:	//���� ���� 
			m_nRibbonOutFlag		= nFlagName;
			break;

		case JPL_THEMAL_TRANSFER_MD_FLAG:
			m_nThermalTransferModeFlag = nFlagName;
			break;

		case JPL_PRINT_MODE:
			m_nPrintMode			= nFlagName;
			break;

		case JPL_PRINT_WIDTH_MODE:
			m_nPrintWidthMode		= nFlagName;
			break;

		case JPL_LABEL_WAIT_FLAG:
			m_nLabelWaitFlag		= nFlagName;
			break;

		case JPL_LABEL_REMAING:
			m_nLabelsRemaing		= nFlagName;
			break;

		case JPL_PRINT_MOVING_FLAG:
			m_nPrintMovingFlag		= nFlagName;
			break;

		case JPL_GRAPHIC_IMG_SAV_NO:
			m_nGraphicImgSavNo		= nFlagName;
			break;

		case JPL_PASS_WORD:
			m_nPsWord				= nFlagName;
			break;

		case JPL_RAM_INIT_STATE:
			m_nRamInitState			= nFlagName;
			break;	
	}
}


int CZebraPrint::OnBarcodeMake(int nDir, int nPort)
{
/*	int mn_existence;   // ���� ���� ���� ���� ���� 
	int n_by= -1, n_bc = -1;
	int pos[3];
	int length;
	
	char fileName[256];   // ����� ���� ���� ���� ���� 
	char buffer[1024+1]; // ���� ���� �� �� ���� ���� �ӽ� ���� ���� 
	
	CString str_print_data;
	CString str_tmp;
	CString str_description; // ���õ� ���� ���� �ӽ� ���� ���� 
	
	sprintf(fileName, "C:\\AMT8490\\BARCODE.TXT");
	
	mn_existence = access(fileName, 0);
	
	if (mn_existence != -1)  
	{
		FILE *fp = fopen ( fileName, "r" );
		
		if ( fp == (FILE *)NULL ) 
		{
			return CTLBD_RET_ERROR;
		}
		
		str_description.Empty();  // ���� ���� ���� ���� �ʱ�ȭ
		
		while (!feof(fp))
		{
			if (fgets(buffer, 1024, fp) == NULL)  break;
			
			if (strlen(buffer))   buffer[strlen(buffer)] = 0;
			strcat (buffer, "\r\n");
			str_description += buffer;
		}
		
		fclose(fp);
	}
	
	length = str_description.GetLength();
	
	pos[0] = str_description.Find("^BY", 0);
	pos[1] = str_description.Find("^FD", pos[0]);
	pos[2] = str_description.Find("^FS", pos[1]);
	
	if (nDir == 0)
	{
		str_tmp = "^BXN";
	}
	else
	{
		str_tmp = "^BXI";
	}
	
	str_print_data = str_description.Mid(0, pos[1]);
	str_print_data += st_barcode.str_barcode_tag;
	str_print_data += str_description.Mid(pos[2]+3, length - (pos[2]+3));
	
	if(st_basic.n_mode_barcode_print == 1)
	{	
//		st_serial.mstr_snd[nPort-1] = str_print_data;
	}
	else
	{	
		if(OnOutLptPort(str_print_data) == CTLBD_RET_ERROR)
		{
			return CTLBD_RET_ERROR;
		}
	}
	*/
	return CTLBD_RET_GOOD;
}

int CZebraPrint::OnOutLptPort(CString str_text)
{
	HANDLE hLpt;
	DWORD dwWritten; 
	
    hLpt = CreateFile("LPT1:", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
    if (hLpt == INVALID_HANDLE_VALUE)
	{ 
        AfxMessageBox("Can not open LPT1 !!!");
		
		return CTLBD_RET_ERROR;
	}
    else
	{ 
        WriteFile(hLpt, str_text, str_text.GetLength(), &dwWritten, NULL);
        CloseHandle(hLpt); 
    }
	
	return CTLBD_RET_GOOD;
}


void CZebraPrint::OnPrintAnswerMode(int nMethod, int nMode, int nPort)//2014.1104 ysj
{
	CString strPrint;

	//2016.0615
	if( st_handler.mn_curr_back_conv == CTL_YES || st_handler.n_without_smema_8580_mc == CTL_YES || st_basic.nBcrFeederUse[nPort] != CTL_YES )
		return;
	
	if(nPort == CLS_BCR_PRINTER1)
	{
		if (nMode == 0)
		strPrint = "^XA^SXK,D,Y,Y,192.168.1.16,9100^XZ";	 // print ���� Ȯ�� 
		else 
		strPrint = "^XA^SXK,D,N,N,192.168.1.16,9100^XZ";	 // print ���� Ȯ�� 
	}
	else if(nPort == CLS_BCR_PRINTER2)
	{
		if (nMode == 0)
			strPrint = "^XA^SXK,D,Y,Y,192.168.1.16,9101^XZ";	 // print ���� Ȯ�� 
		else 
			strPrint = "^XA^SXK,D,N,N,192.168.1.16,9101^XZ";	 // print ���� Ȯ�� 
	} 
	else if(nPort == CLS_BCR_PRINTER3)
	{
		if (nMode == 0)
			strPrint = "^XA^SXK,D,Y,Y,192.168.1.16,9102^XZ";	 // print ���� Ȯ�� 
		else 
			strPrint = "^XA^SXK,D,N,N,192.168.1.16,9102^XZ";	 // print ���� Ȯ�� 
	} 
	else if(nPort == CLS_BCR_PRINTER4)
	{
		if (nMode == 0)
			strPrint = "^XA^SXK,D,Y,Y,192.168.1.16,9103^XZ";	 // print ���� Ȯ�� 
		else 
			strPrint = "^XA^SXK,D,N,N,192.168.1.16,9103^XZ";	 // print ���� Ȯ�� 
	}

// 	if (nMode == 0)
// 	{
// 		strPrint = "^XA^SXK,D,Y,Y,192.168.1.16,9101^XZ";	 // print AA��a E��AI ������a 
// 	}
// 	else
// 	{
// 		strPrint = "^XA^SXK,D,N,N,192.168.1.16,9101^XZ";	// print AA��a E��AI ��ECO.
// 	}
	
	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;

//		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	
	}

	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[PRINT_Answer] %s", strPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}
}


void CZebraPrint::OnPrintLabelMode(int nMethod, int nMode, int nPort)
{
	CString strPrint;
	
	if (nMode == 0)
	{
		strPrint = "^XA^MMT^XZ";	//Tear off
	}
	else if (nMode == 1)
	{
		strPrint = "^XA^MMP^XZ";	//Peel off
	}
	else
	{
		strPrint = "^XA^MMR^XZ";	//Rewind
	}
	
	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;
		
		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_ZEBRA_CLIENT_MSG_1 + nPort, CLIENT_SEND, 0); // LABEL CLIENT	
	}
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[PRINT_LabelMode] %s", strPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}
}


void CZebraPrint::OnPrintPauseMode(int nMethod, int nMode, int nPort)
{
	CString strPrint;
	
	if (nMode == 0)
	{
		strPrint = "^XA~PP^XZ";	//
	}
	else
	{
		strPrint = "^XA~PS^XZ";	//
	}

	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;
		
//		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_ZEBRA_CLIENT_MSG_1 + nPort, CLIENT_SEND, 0); // LABEL CLIENT	
	}
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[PRINT_PauseMode] %s", strPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}
}


void CZebraPrint::OnPrintStatusCheck(int nMethod, int nPort) // 20140906 jtkim
{
	CString strPrint;
	
	m_nPrintStatusBin = NVR_NONE;

	strPrint = "~HS";//"^XA~HS^XZ";	//
//	strPrint += "^XA^SXK,A,Y,Y^XZ";
	
	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;
		
//		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	

	}
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[PRINT_Status] %s", strPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}
}


CString	CZebraPrint::OnPrintLabelOffset(int nOffsetX, int nOffsetY, CString strText)
{
	CString strData;
	CString strOld;
	CString strNew;

	int nPos;
	int nX, nY;

	strData = strText;
	nPos = strData.Find(_T("LH"), 0);

	strOld = strData.Mid(nPos, 9);

	nX = atoi(strOld.Mid(2, 3));
	nY = atoi(strOld.Mid(6, 3));

	strNew.Format("LH%03d,%03d", nX + nOffsetX, nY + nOffsetY);
	strNew = strNew + "^MMT";
	strData.Replace(strOld, strNew);

	return strData;
}


void CZebraPrint::OnPrintOutput(int nMethod, int nPort, int nOffsetX, int nOffsetY, CString strText)
{
	CString strPrint;
	
	m_nPrintStatusBin = NVR_NONE;
	
	strPrint = OnPrintLabelOffset(nOffsetX, nOffsetY, strText);
	
	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;
		
//		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	
	}
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
// 		sprintf(st_msg.c_normal_msg,"[PRINT_Output] %s", strPrint);
// 		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
		CString sTmp;
		sTmp.Format("[PRINT_Output] %s", strPrint);
		Func.On_LogFile_Add(LOG_TOTAL, sTmp);
	}
}


void CZebraPrint::OnPrintCalibration(int nMethod, int nPort)
{
	CString strPrint;
	
	m_nPrintStatusBin = NVR_NONE;
	
	strPrint = "^XA~JC^XZ";	//
	
	if (nMethod == 0)
	{
		clsZebra.OnOutLptPort(strPrint);
	}
	else if (nMethod == 1)
	{
//		st_serial.str_snd[nPort] = strPrint;
		
//		::SendMessage(st_handler.hWnd, WM_DATA_SEND, nPort, 0);
	}
	else
	{
		sprintf(st_client[nPort].ch_send,"%s",strPrint);
		::SendMessage(st_handler.hWnd, WM_ZEBRA_CLIENT_MSG_1 + nPort, CLIENT_SEND, 0); // LABEL CLIENT	
	}
	
	if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
	{
		sprintf(st_msg.c_normal_msg,"[PRINT_Cal] %s", strPrint);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� ���� ��� ��û
	}
}


void CZebraPrint::OnPrintComplete(CString strRev)
{
	int nNum;

	nNum = -1;
	nNum = strRev.Find("PQ JOB COMPLETED", 0);
	
	if (nNum >= 0)
	{
		m_nPrintStatusBin = NVR_PASS;
	}
	else
	{
		m_nPrintStatusBin = NVR_FAIL;
	}

// 	if (st_handler.cwnd_list != NULL)  // ����������� ��U E����e A��Ac
// 	{
// 		sprintf(st_msg.c_normal_msg,"[PRINT_COMPLETE] %s", strRev);
// 		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �좯AU ��C���� Aa��A ��aA��
// 	}

}



////2015.0413
void CZebraPrint::SetDarkness_TCP(int nPort)
{
	CString mstr_data[2];
	CString str_print_data;
	int i;	

	//2016.0615
	if( st_handler.mn_curr_back_conv == CTL_YES || st_handler.n_without_smema_8580_mc == CTL_YES || st_basic.nBcrFeederUse[nPort] != CTL_YES )
		return;
	
	for(i=0; i<2; i++)
	{
		mstr_data[i] = "";
	}
	str_print_data = "";

	mstr_data[0] = "~SD";

	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_CONNECT, nPort); // LABEL CLIENT	
	::Sleep(500);
	if(nPort == CLS_BCR_PRINTER1)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_sd[0]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[1]);//2015,0109
	}
	else if(nPort == CLS_BCR_PRINTER2)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_sd[1]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[1]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER3)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_sd[2]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[1]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER4)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_sd[3]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[1]);//2015,0109
	}

	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	

}

void CZebraPrint::LabelTop_TCP(int nPort)
{
	CString mstr_data[3];
	CString str_print_data;
	int i;	

	//2016.0615
	if( st_handler.mn_curr_back_conv == CTL_YES || st_handler.n_without_smema_8580_mc == CTL_YES || st_basic.nBcrFeederUse[nPort] != CTL_YES )
		return;
	
	for(i=0; i<3; i++)
	{
		mstr_data[i] = "";
	}
	str_print_data = "";
	
	mstr_data[0] = "^XA^LT";
		
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_CONNECT, nPort); // LABEL CLIENT	
	::Sleep(500);
	if(nPort == CLS_BCR_PRINTER1)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_lt[0]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	}
	else if(nPort == CLS_BCR_PRINTER2)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_lt[1]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER3)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_lt[2]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER4)
	{
		str_print_data.Format("%d", st_barcode.mn_labelset_lt[3]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	}
	
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	
	
}

void CZebraPrint::LabelHome_TCP(int nPort)
{
	CString mstr_data[3];
	CString str_print_data;
	int i;	

	for(i=0; i<3; i++)
	{
		mstr_data[i] = "";
	}
	str_print_data = "";

	mstr_data[0] = "^XA^LH";
	
	if(nPort == CLS_BCR_PRINTER1)
	{
		str_print_data.Format("%d,%d", st_barcode.mn_labelset_lhx[0], st_barcode.mn_labelset_lhy[0]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	}
	else if(nPort == CLS_BCR_PRINTER2)
	{
		str_print_data.Format("%d,%d", st_barcode.mn_labelset_lhx[1], st_barcode.mn_labelset_lhy[1]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER3)
	{
		str_print_data.Format("%d,%d", st_barcode.mn_labelset_lhx[2], st_barcode.mn_labelset_lhy[2]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	} 
	else if(nPort == CLS_BCR_PRINTER4)
	{
		str_print_data.Format("%d,%d", st_barcode.mn_labelset_lhx[3], st_barcode.mn_labelset_lhy[3]);
		mstr_data[1] = mstr_data[0] + str_print_data;
		mstr_data[2] = mstr_data[1] + "^XZ";
		sprintf(st_client[nPort].ch_send,"%s",mstr_data[2]);//2015,0109
	}
	
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + nPort, CLIENT_SEND, nPort); // LABEL CLIENT	
	
}
////
