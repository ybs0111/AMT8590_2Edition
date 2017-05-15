// FastechPublic_IO.cpp: implementation of the CFastechPublic_IO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FastechPublic_IO.h"

#include "FAS_HSSI.h"
#include "math.h"
//#include "io.h"     // ���� ���� ���� �˻� �Լ� ȣ���ϱ� ���ؼ��� �ݵ�� INCLUDE �ʿ� 
// #include "Srcbase/ALocalization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFastechPublic_IO  FAS_IO;  

CFastechPublic_IO::CFastechPublic_IO()
{
}

CFastechPublic_IO::~CFastechPublic_IO()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//2011.1019 james lee WORD ������ I/O�� �����Ѵ�
//Ver 0.0.1_2011.1019
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


//2011.1019 james //Word ������ ����� ����ϴ� �Լ� 
BOOL CFastechPublic_IO::get_in_bit(int n_IONo, int n_OnOff)  //2011.1019 Simulation ���۱��� �������� onoff �߰� 
{
/*
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo = 0;
	BOOL    bData=0;
*/
// 	if(mn_simulation_mode == 1) //Simulation ����̸� ���α׷��� �����ؾ� �ϴ� I/O ���¸� ���ϴ� ������ ������ �ش� 
// 	{
// 		n_in[n_IONo] = n_OnOff;
// 		return n_in[n_IONo]; 
// 	}

	return n_in[n_IONo];

	//���ϴ� ������� �ʴ´� 
	/*
	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_ReadInputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}	
	return bData;*/
}

int CFastechPublic_IO::set_out_bit(int n_IONo, BOOL b_OnOff) 
{
/*
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;
*/

	n_out[n_IONo] = b_OnOff;
	return STATUS_SUCCESS;


	//���ϴ� ������� �ʴ´� 
	/*
	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_WriteOutputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, b_OnOff);  // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;*/
}

BOOL CFastechPublic_IO::get_out_bit(int n_IONo, int n_OnOff)
{
/*
	CString sMsg;
	int     nRet=0;	
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0,nBitNo=0;
	BOOL    bData;
*/

// 	if(mn_simulation_mode == 1) //Simulation ����̸� ���α׷��� �����ؾ� �ϴ� I/O ���¸� ���ϴ� ������ ������ �ش� 
// 	{		
// 		return n_out[n_IONo] = n_OnOff;
// 	}

	return n_out[n_IONo];
	//���ϴ� ������� �ʴ´� 
	/*
	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);
	
	nRet = HSSI_ReadOutputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}	
	return bData;*/
}

int CFastechPublic_IO::IO_ReadWrite(int n_bd_num, int n_port_num, int n_slave_num, int n_rw_mode)
{//n_rw_mode : -1:������ �ʱ�ȭ, 0=> initialize i/o ���� read, 1:input, 2:output
	WORD	wData = 0;
	int     i=0, nRet=0, nBoardID=-1, nPortNo=0, nSlaveNo=0, nIO_Num = 0;
 
//#define MAX_PCI_SLOT 8	// 0~7 8��
//#define MAX_PORT_NO 4	// 0~3 4��
//#define MAX_SLAVE_NO 8	// 0~7 8��


	//���� ������ �̿��Ͽ� io port ��ȣ�� �����Ѵ� 
	if(n_bd_num < 0 || n_bd_num > MAX_PCI_SLOT - 6) //MAX_PCI_SLOT - 1)
	{//	����� ���� 8����� ��밡���ϳ� ���� MAX�� 2������ �Ѵ� 
		AfxMessageBox("IO Board [0 ~ 1] Max Num Over");//[0 ~ 7] Max Num Over");
		return BD_ERROR;
	}
	else nBoardID = n_bd_num * 4000;

	if(n_port_num < 0 || n_port_num > MAX_PORT_NO - 1)
	{
		AfxMessageBox("IO Board Port [0 ~ 3] Max Num Over");
		return BD_ERROR;
	}
	else nPortNo   = n_port_num * 1000;

	if(n_slave_num < 0 || n_slave_num > MAX_SLAVE_NO - 1)
	{
		AfxMessageBox("IO Board Slave [0 ~ 7] Max Num Over");
		return BD_ERROR;
	}
	else nSlaveNo   = n_slave_num * 100;
	
	
    nIO_Num = nBoardID + nPortNo + nSlaveNo;
	if(nIO_Num > HSSI_MAX_IO - 1) //#define HSSI_MAX_IO		8716 //max io board 2�� ������ �����Ͽ� ������� //max io board 4�� ������ ó���Ѵ� 
	{
		AfxMessageBox("IO Num [8715] Max Num Over");
		return BD_ERROR;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��� I/O port�� define �� �����Ʈ �ʱ�ȭ �� I/O ���� �������� �� ��Ʈ�� ���¸� �о� ������ �����Ͽ� �ش� 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(n_rw_mode == -1) //input, output port ������� ó�� �ѹ� �ʱ�ȭ �� �� 
	{
		for(i=0; i<HSSI_MAX_IO; i++) //��Ʈ ��� ���� �ʱ�ȭ 
		{
			n_in[i]  = 0;//-1;
			n_out[i] = -1;
		}
	}

// 	if(mn_simulation_mode == 1) //Simulation ����̸� ���α׷��� �����ؾ� �ϴ� I/O ���¸� ���ϴ� ������ ������ �ش� 
// 	{//������ ���ķ��̼� ���� ���α׷� �׽�Ʈ�� ������ ������ ������ ������ Ŭ���� �Ǵ� �����Ѵ� 
// 		return BD_GOOD; 
// 	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ�� ó���ѹ� Input �� output port�� ���¸� �޴´� 
	//////////////////////////////////////////////////////////////////////////////////////////////////
	if(n_rw_mode == 0) //initialize total input/ output read mode 
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� ���� ���� �ѹ� �ʱ�ȭ
		// in/out ������ -1�̸� ������� �ʴ� ��Ʈ�̰�, 0 �Ǵ� 1�̸� ���������� ��񿡼� �ÿ��ϴ� �����̴� 
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// ************************************************************************** //
		// �Է�(��� ��ȣ 00��)								                          //
		// ************************************************************************** //
		nRet = HSSI_ReadInputWord(n_bd_num, n_port_num, n_slave_num, &wData); //(iMasterID, iPortNo, iSlaveNo, &wData); 
		if(nRet != STATUS_SUCCESS){return BD_ERROR;};//error

		n_in[nIO_Num + 0]	= (wData & DBIT0)   ? 1 : 0 ;		// PS000 (���: 0	��Ʈ: 0) 
		n_in[nIO_Num + 1]	= (wData & DBIT1)   ? 1 : 0 ;		// PS001 (���: 0	��Ʈ: 1) 
		n_in[nIO_Num + 2]	= (wData & DBIT2)   ? 1 : 0 ;		// PS002 (���: 0	��Ʈ: 2) 
		n_in[nIO_Num + 3]	= (wData & DBIT3)   ? 1 : 0 ;		// PS003 (���: 0	��Ʈ: 3) 
		n_in[nIO_Num + 4]	= (wData & DBIT4)   ? 1 : 0 ;		// PS004 (���: 0	��Ʈ: 4)
		n_in[nIO_Num + 5]	= (wData & DBIT5)   ? 1 : 0 ;		// PS005 (���: 0	��Ʈ: 5) 
		n_in[nIO_Num + 6]	= (wData & DBIT6)   ? 1 : 0 ;		// PS006 (���: 0	��Ʈ: 6) 
		n_in[nIO_Num + 7]	= (wData & DBIT7)   ? 1 : 0 ;		// PS007 (���: 0	��Ʈ: 7) 
		n_in[nIO_Num + 8]	= (wData & DBIT8)   ? 1 : 0 ;		// PS008 (���: 0	��Ʈ: 8) 
		n_in[nIO_Num + 9]	= (wData & DBIT9)   ? 1 : 0 ;		// PS009 (���: 0	��Ʈ: 9) 
		n_in[nIO_Num + 10]	= (wData & DBIT10)  ? 1 : 0 ;		// PS010 (���: 0	��Ʈ: 10) 
		n_in[nIO_Num + 11]	= (wData & DBIT11)  ? 1 : 0 ;		// PS011 (���: 0	��Ʈ: 11) 
		n_in[nIO_Num + 12]	= (wData & DBIT12)  ? 1 : 0 ;		// PS012 (���: 0	��Ʈ: 12) 
		n_in[nIO_Num + 13]	= (wData & DBIT13)  ? 1 : 0 ;		// PS013 (���: 0	��Ʈ: 13) 
		n_in[nIO_Num + 14]	= (wData & DBIT14)  ? 1 : 0 ;		// PS014 (���: 0	��Ʈ: 14) 
		n_in[nIO_Num + 15]	= (wData & DBIT15)  ? 1 : 0 ;		// PS015 (���: 0	��Ʈ: 15) 

		// ************************************************************************** //
		// ���(��� ��ȣ 00��)								                          //
		// ************************************************************************** //
		nRet = HSSI_ReadOutputWord(n_bd_num, n_port_num, n_slave_num, &wData); //(iMasterID, iPortNo, iSlaveNo, &wData); 
		if(nRet != STATUS_SUCCESS){return BD_ERROR;};//error

		for(i=0; i<16; i++)//io port 16��
		{
// 			if(n_out[nIO_Num + i] == 0 || n_out[nIO_Num + i] == 1) //0:off, 1:on
// 			{
				if     (i == 0)	n_out[nIO_Num + 0]		= (wData & DBIT0)   ? 1 : 0 ;		// S000 (���: 0	��Ʈ: 0) 
				else if(i == 1)	n_out[nIO_Num + 1]		= (wData & DBIT1)   ? 1 : 0 ;		// S001 (���: 0	��Ʈ: 1) 
				else if(i == 2) n_out[nIO_Num + 2]		= (wData & DBIT2)   ? 1 : 0 ;		// S002 (���: 0	��Ʈ: 2) 
				else if(i == 3) n_out[nIO_Num + 3]		= (wData & DBIT3)   ? 1 : 0 ;		// S003 (���: 0	��Ʈ: 3) 
				else if(i == 4) n_out[nIO_Num + 4]		= (wData & DBIT4)   ? 1 : 0 ;		// S004 (���: 0	��Ʈ: 4)
				else if(i == 5) n_out[nIO_Num + 5]		= (wData & DBIT5)   ? 1 : 0 ;		// S005 (���: 0	��Ʈ: 5) 
				else if(i == 6) n_out[nIO_Num + 6]		= (wData & DBIT6)   ? 1 : 0 ;		// S006 (���: 0	��Ʈ: 6) 
				else if(i == 7) n_out[nIO_Num + 7]		= (wData & DBIT7)   ? 1 : 0 ;		// S007 (���: 0	��Ʈ: 7) 
				else if(i == 8) n_out[nIO_Num + 8]		= (wData & DBIT8)   ? 1 : 0 ;		// S008 (���: 0	��Ʈ: 8) 
				else if(i == 9) n_out[nIO_Num + 9]		= (wData & DBIT9)   ? 1 : 0 ;		// S009 (���: 0	��Ʈ: 9) 
				else if(i == 10) n_out[nIO_Num + 10]	= (wData & DBIT10)  ? 1 : 0 ;		// S010 (���: 0	��Ʈ: 10) 
				else if(i == 11) n_out[nIO_Num + 11]	= (wData & DBIT11)  ? 1 : 0 ;		// S011 (���: 0	��Ʈ: 11) 
				else if(i == 12) n_out[nIO_Num + 12]	= (wData & DBIT12)  ? 1 : 0 ;		// S012 (���: 0	��Ʈ: 12) 
				else if(i == 13) n_out[nIO_Num + 13]	= (wData & DBIT13)  ? 1 : 0 ;		// S013 (���: 0	��Ʈ: 13) 
				else if(i == 14) n_out[nIO_Num + 14]	= (wData & DBIT14)  ? 1 : 0 ;		// S014 (���: 0	��Ʈ: 14) 
				else if(i == 15) n_out[nIO_Num + 15]	= (wData & DBIT15)  ? 1 : 0 ;		// S015 (���: 0	��Ʈ: 15) 
//			}
		}
	}	

	if(n_rw_mode == 1 || n_rw_mode == 2) //input read mode
	{
		// ************************************************************************** //
		// �Է�(��� ��ȣ 00��)								                          //
		// ************************************************************************** //
		nRet = HSSI_ReadInputWord(n_bd_num, n_port_num, n_slave_num, &wData); //(iMasterID, iPortNo, iSlaveNo, &wData); 
		if(nRet != STATUS_SUCCESS){return BD_ERROR;};//error

		n_in[nIO_Num + 0]	= (wData & DBIT0)   ? 1 : 0 ;		// PS000 (���: 0	��Ʈ: 0) 
		n_in[nIO_Num + 1]	= (wData & DBIT1)   ? 1 : 0 ;		// PS001 (���: 0	��Ʈ: 1) 
		n_in[nIO_Num + 2]	= (wData & DBIT2)   ? 1 : 0 ;		// PS002 (���: 0	��Ʈ: 2) 
		n_in[nIO_Num + 3]	= (wData & DBIT3)   ? 1 : 0 ;		// PS003 (���: 0	��Ʈ: 3) 
		n_in[nIO_Num + 4]	= (wData & DBIT4)   ? 1 : 0 ;		// PS004 (���: 0	��Ʈ: 4)
		n_in[nIO_Num + 5]	= (wData & DBIT5)   ? 1 : 0 ;		// PS005 (���: 0	��Ʈ: 5) 
		n_in[nIO_Num + 6]	= (wData & DBIT6)   ? 1 : 0 ;		// PS006 (���: 0	��Ʈ: 6) 
		n_in[nIO_Num + 7]	= (wData & DBIT7)   ? 1 : 0 ;		// PS007 (���: 0	��Ʈ: 7) 
		n_in[nIO_Num + 8]	= (wData & DBIT8)   ? 1 : 0 ;		// PS008 (���: 0	��Ʈ: 8) 
		n_in[nIO_Num + 9]	= (wData & DBIT9)   ? 1 : 0 ;		// PS009 (���: 0	��Ʈ: 9) 
		n_in[nIO_Num + 10]	= (wData & DBIT10)  ? 1 : 0 ;		// PS010 (���: 0	��Ʈ: 10) 
		n_in[nIO_Num + 11]	= (wData & DBIT11)  ? 1 : 0 ;		// PS011 (���: 0	��Ʈ: 11) 
		n_in[nIO_Num + 12]	= (wData & DBIT12)  ? 1 : 0 ;		// PS012 (���: 0	��Ʈ: 12) 
		n_in[nIO_Num + 13]	= (wData & DBIT13)  ? 1 : 0 ;		// PS013 (���: 0	��Ʈ: 13) 
		n_in[nIO_Num + 14]	= (wData & DBIT14)  ? 1 : 0 ;		// PS014 (���: 0	��Ʈ: 14) 
		n_in[nIO_Num + 15]	= (wData & DBIT15)  ? 1 : 0 ;		// PS015 (���: 0	��Ʈ: 15) 
	}

	if(n_rw_mode == 1 || n_rw_mode == 2) //output mode
	{
		// ************************************************************************** //
		// �Է�(��� ��ȣ 00��)								                          //
		// ************************************************************************** //
		wData = 0;
		for(i=0; i<16; i++)//io port 16��
		{
			if(n_out[nIO_Num + i] == 0 || n_out[nIO_Num + i] == 1) //0:off, 1:on
			{
				if     (i == 0)  wData += n_out[nIO_Num + i]		* DBIT0;  // S000 (���: 0	��Ʈ: 0)
				else if(i == 1)  wData += n_out[nIO_Num + i]		* DBIT1;  // S001 (���: 0	��Ʈ: 1)
				else if(i == 2)  wData += n_out[nIO_Num + i]		* DBIT2;  // S002 (���: 0	��Ʈ: 2)
				else if(i == 3)  wData += n_out[nIO_Num + i]		* DBIT3;  // S003 (���: 0	��Ʈ: 3)
				else if(i == 4)  wData += n_out[nIO_Num + i]		* DBIT4;  // S004 (���: 0	��Ʈ: 4)
				else if(i == 5)  wData += n_out[nIO_Num + i]		* DBIT5;  // S005 (���: 0	��Ʈ: 5)
				else if(i == 6)  wData += n_out[nIO_Num + i]		* DBIT6;  // S006 (���: 0	��Ʈ: 6)
				else if(i == 7)  wData += n_out[nIO_Num + i]		* DBIT7;  // S007 (���: 0	��Ʈ: 7)
				else if(i == 8)  wData += n_out[nIO_Num + i]		* DBIT8;  // S008 (���: 0	��Ʈ: 8)
				else if(i == 9)  wData += n_out[nIO_Num + i]		* DBIT9;  // S009 (���: 0	��Ʈ: 9)
				else if(i == 10) wData += n_out[nIO_Num + i]		* DBIT10; // S010 (���: 0	��Ʈ: 10)
				else if(i == 11) wData += n_out[nIO_Num + i]		* DBIT11; // S011 (���: 0	��Ʈ: 11)
				else if(i == 12) wData += n_out[nIO_Num + i]		* DBIT12; // S012 (���: 0	��Ʈ: 12)
				else if(i == 13) wData += n_out[nIO_Num + i]		* DBIT13; // S013 (���: 0	��Ʈ: 13)
				else if(i == 14) wData += n_out[nIO_Num + i]		* DBIT14; // S014 (���: 0	��Ʈ: 14)
				else if(i == 15) wData += n_out[nIO_Num + i]		* DBIT15; // S015 (���: 0	��Ʈ: 15)
			}
		}

		nRet = HSSI_WriteOutputWord(n_bd_num, n_port_num, n_slave_num, wData);//(iMasterID, iPortNo, iSlaveNo, wData); //TRUE = enable, FALSE = Dasible
		if(nRet != STATUS_SUCCESS){return BD_ERROR;};//error 
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2011.1019 james lee WORD ������ I/O�� �����Ѵ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// ******************************************************************************
// I/O ���� ���̺귯�� �ʱ�ȭ �Լ�                                                   
// ******************************************************************************
// ******************************************************************************
// I/O ���� ���� �Լ�                                                            
// ******************************************************************************
int CFastechPublic_IO::Set_IO_BoardOpen(INT* pn_MasterNo, int n_OpenMethod) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterNo=0;

	nRet = HSSI_Open(&nMasterNo, n_OpenMethod);  // HSSI �ʱ�ȭ �Լ� 
	if (nRet == STATUS_SUCCESS)
	{
		*pn_MasterNo = nMasterNo;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// I/O ���� ���� �Լ�                                                            
// ******************************************************************************
int CFastechPublic_IO::Set_IO_BoardClose(bool b_CloseMethod) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_Close(b_CloseMethod);  // HSSI ���ҽ� ���� �Լ� 
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}

	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� �Լ� [WORD ����]                                 
// ******************************************************************************
int CFastechPublic_IO::Set_IO_DefineWord(int n_MasterID, int n_PortNo, int n_SlaveNo, WORD w_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_WriteDirectionWord(n_MasterID, n_PortNo, n_SlaveNo, w_Data);  // SLAVE I/O ����� ����� ���� �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� �Լ� [BYTE ����]                                 
// ******************************************************************************
int CFastechPublic_IO::Set_IO_DefineByte(int n_MasterID, int n_PortNo, int n_SlaveNo, int n_Type, BYTE bt_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_WriteDirectionByte(n_MasterID, n_PortNo, n_SlaveNo, n_Type, bt_Data);  // SLAVE I/O ����� ����� ���� �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� �Լ� [BIT ����]                                  
// ******************************************************************************
int CFastechPublic_IO::Set_IO_DefineBit(int n_IONo, BOOL b_Data) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_WriteDirectionBit(nMasterID, nPortNo, nSlaveNo, nBitNo, b_Data);  // SLAVE I/O ����� ����� ���� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� ���� ���� [WORD ����]                            
// ******************************************************************************
int CFastechPublic_IO::Get_IO_DefineWord(int n_MasterID, int n_PortNo, int n_SlaveNo, WORD* pw_Data) 
{
	CString sMsg;
	int     nRet=0;
	WORD    wData=0;

	nRet = HSSI_ReadDirectionWord(n_MasterID, n_PortNo, n_SlaveNo, &wData);  // SLAVE I/O ����� ����� ���� ���� ���� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
		*pw_Data = wData;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� ���� ���� [BYTE ����]                            
// ******************************************************************************
int CFastechPublic_IO::Get_IO_DefineByte(int n_MasterID, INT n_PortNo, int n_SlaveNo, int n_Type, BYTE* pb_Data) 
{
	CString sMsg;
	int     nRet=0;
	BYTE    bData=0;

	nRet = HSSI_ReadDirectionByte(n_MasterID, n_PortNo, n_SlaveNo, n_Type, &bData);  // SLAVE I/O ����� ����� ���� ���� ���� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
		*pb_Data = bData;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� ����� ���� ���� ���� [BIT ����]                             
// ******************************************************************************
int CFastechPublic_IO::Get_IO_DefineBit(int n_IONo, BOOL* pb_Data) 
{
	CString sMsg;
	int     nRet=0;
	BOOL    bData;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_ReadDirectionBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ����� ����� ���� ���� ���� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
		*pb_Data = bData;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// PC�� ����� ������ ���� ���� �˻� �Լ�                                        
// ******************************************************************************
int CFastechPublic_IO::Search_IO_Master(INT* pn_MasterNo) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterNo=0;

	nRet = HSSI_GetAttachedMasterBoard(&nMasterNo);  // ���� PC�� ����Ǿ� �ִ� ������ ���� ���� ���� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		*pn_MasterNo = nMasterNo;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}

	return nRet;
}
// ******************************************************************************


// ******************************************************************************
// ������ ���忡 ����� PORT ���� �˻� �Լ�                                      
// ******************************************************************************
int CFastechPublic_IO::Search_IO_Port(int n_MasterID, INT* pn_PortNo) 
{
	CString sMsg;
	int     nRet=0;
	INT     nPortNo=0;

	nRet = HSSI_GetAttachedPort(n_MasterID, &nPortNo);  // ������ ������ ���� �����ϴ� PORT ���� ���� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		*pn_PortNo = nPortNo;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// PORT�� ����� SLAVE �˻� �Լ�                                                 
// ******************************************************************************
int CFastechPublic_IO::Search_IO_Slave(int n_MasterID, int n_PortNo, INT* pn_SlaveNo) 
{
	CString sMsg;
	int     nRet=0;	
	INT     nSlaveNo=0;

	nRet = HSSI_GetAttachedSlaveModule(n_MasterID, n_PortNo, &nSlaveNo);  // PORT�� ����� SLAVE I/O ��� �˻� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		*pn_SlaveNo = nSlaveNo;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O MODULE�� ENABLE ���·� ������ ���忡 ����Ǿ� �ִ��� �˻� �Լ�      
// ******************************************************************************
int CFastechPublic_IO::Check_IO_SlaveStatus(int n_MasterID, int n_PortNo, int n_SlaveNo) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_IsExistSlaveModule(n_MasterID, n_PortNo, n_SlaveNo);  // SLAVE I/O MODULE�� ENABLE ���·� ������ ���忡 ����Ǿ� �ִ��� �˻� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// PORT�� ����� SLAVE [ENABLE/DISABLE] ���� �˻� �Լ�                           
// ******************************************************************************
BOOL CFastechPublic_IO::Check_IO_Slave(int n_MasterID, int n_PortNo, int n_SlaveID) 
{
	int nSlaveInfo;

	FAS_STATUS  fasResult;

	// **************************************************************************
	// nSlaveInfo : �������κ��� ���� ��Ʈ �������� 8���� BIT���� �� SLAVE����   
	//              ���� ���°� ����� BCD�� ����ִ�                            
	// -> BIT 1   : SLAVE I/O ����� ����Ǿ� ENABLE�� ����                      
	// -> BIT 0   : SLAVE I/O ����� ������� �ʾ� DISABLE�� ����                
	// **************************************************************************
	fasResult = HSSI_GetAttachedSlaveModule(n_MasterID, n_PortNo, &nSlaveInfo);  // PORT�� ����� SLAVE I/O ��� �˻� �Լ�
	if (((nSlaveInfo >> n_SlaveID) & 0x1) != 1)
	{
		return BD_ERROR;
	}
	// **************************************************************************

	return BD_GOOD;
}
// ******************************************************************************

// ******************************************************************************
// PORT�� SLAVE I/O ������ ��� �ӵ� ���� �Լ�                                 
// -> PORT_SPEED_05 : 0.5 Mbps                                                   
// -> PORT_SPEED_10 : 1.0 Mbps                                                   
// -> PORT_SPEED_20 : 2.0 Mbps                                                   
// ******************************************************************************
int CFastechPublic_IO::Set_IO_HSSISpeed(int n_MasterID, int n_PortNo, int n_Type) 
{
	CString sMsg;
	int     nRet=0, nFlag = BD_ERROR;

	nRet = HSSI_SetCommSpeed(n_MasterID, n_PortNo, n_Type);  // �ش� PORT�� I/O ��� ������ ��� �ӵ� ���� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// PORT�� SLAVE I/O ������ ��� �ӵ� ���� �Լ�                                 
// -> PORT_SPEED_05 : 0.5 Mbps                                                   
// -> PORT_SPEED_10 : 1.0 Mbps                                                   
// -> PORT_SPEED_20 : 2.0 Mbps                                                   
// ******************************************************************************
int CFastechPublic_IO::Get_IO_HSSISpeed(int n_MasterID, int n_PortNo, INT* pn_Type) 
{
	CString sMsg;
	int     nRet=0;
	INT     nType;

	nRet = HSSI_GetCommSpeed(n_MasterID, n_PortNo, &nType);  // �ش� PORT�� I/O ��� ������ ��� �ӵ� ���� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		*pn_Type = nType;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ���� ���� ���� �˻� �Լ�                                                      
// ******************************************************************************
int CFastechPublic_IO::Check_IO_BoardExist(int n_MaxSlot, int n_MaxPort, int n_MaxSlave) 
{
	int nMasterID, nPortNo, nSlaveID;
	int nRet=0;

	while(1)
	{
		for(nMasterID=0; nMasterID<n_MaxSlot; nMasterID++)
		{
			nRet = Check_IO_MasterStatus(nMasterID);  // ������ ���� ���� ���� �˻� �Լ�
			if (nRet != BD_GOOD)
			{
				continue ;
			}

			for(nPortNo=0; nPortNo<n_MaxPort; nPortNo)
			{
				nRet = Check_IO_PortStatus(nMasterID, nPortNo);  // PORT ���� ���� �� ���� ���� �˻� �Լ�
				if (nRet != BD_GOOD)
				{
					continue ;
				}

				for(nSlaveID=0; nSlaveID<n_MaxSlave; nSlaveID++)
				{
					nRet = Check_IO_SlaveStatus(nMasterID, nPortNo, nSlaveID);  // SLAVE I/O MODULE�� ENABLE ���·� ������ ���忡 ����Ǿ� �ִ��� �˻� �Լ�
					if (nRet != BD_GOOD)
					{
						continue ;
					}
				}
			}
		}
	}

	return 0;
}
// ******************************************************************************

// ******************************************************************************
// PORT�� ����� ��� SLAVE I/O ��� �ڵ� ENABLE �Լ�                            
// ******************************************************************************
int CFastechPublic_IO::Set_IO_PortAutoEnable(int n_MasterID, int n_PortNo) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_PortAutoEnable(n_MasterID, n_PortNo);  // �ش� PORT�� ����� ��� SLAVE I/O ��� �ڵ� ENABLE �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
		nRet = BD_ERROR;
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� ���� ENABLE/DISABLE ���� �Լ�                                  
// ******************************************************************************
int CFastechPublic_IO::Set_IO_SlaveEnable(int n_MasterID, int n_PortNo, int n_SlaveNo, BOOL b_Enable) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_EnableSlaveModule(n_MasterID, n_PortNo, n_SlaveNo, b_Enable);  // �ش� SLAVE I/O ��� ���� ENABLE/DISABLE ���� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************


// ******************************************************************************

// ******************************************************************************
// Ư�� ��ġ BIT�� �˻� �Լ�                                                     
// ******************************************************************************
BOOL CFastechPublic_IO::Check_Bit(long n_Value, int n_BitPos) 
{
	unsigned long nMask = 0x0001;  // ����ũ BIT ���� 
	nMask <<= n_BitPos;  // ������ BIT ��ġ�� �̵� [SHIFT] 

	return (n_Value & nMask);  // �ش� BIT ���� �� ���� 
}
// ******************************************************************************

// ******************************************************************************
// Ư�� ��ġ BIT ���� �Լ�                                                       
// ******************************************************************************
void CFastechPublic_IO::Set_Bit(long &n_Value, int n_Bit, BOOL b_On) 
{
	unsigned long nMask = 0x0001;  // ����ũ BIT ���� 
	nMask <<= n_Bit;  // ������ BIT ��ġ�� �̵� [SHIFT] 

	if ( b_On )
	{
		n_Value |= nMask;
	}
	else
	{
		n_Value &= ~nMask;
	}
}
// ******************************************************************************

// ******************************************************************************
// HSSI ���� ������ Ȯ�� �� �˻� �Լ�                                            
// -> �Է� �Ķ���ʹ� �ϵ��� �������� �ԷµǾ�� �Ѵ�                            
//  : I/O MAP ���� �����Ѵ�                                                      
//  : I/O MAP ������ 4�ڸ��� �����ȴ�                                            
// ******************************************************************************
int CFastechPublic_IO::Search_IO_BoardInformation(int n_Type, int n_Data) 
{
	int nFlag     = BD_ERROR;
	int nBardData = 0;

	// **************************************************************************
	// I/O PORT�� ���� �ִ� ������� 7127�� �����Ѵ�                             
	// -> �ִ� ��� : ������ ���� 2���� ���� [I/O PORT�� 2048]                   
	// **************************************************************************
	if (n_Data > HSSI_MAX_IO) //HSSI_MAX_IO = 7715
		return BD_ERROR;
	// **************************************************************************

	switch(n_Type)
	{
	case 0 :  // ������ ���� 
		// **********************************************************************
		// 0[0, 1, 2, 3]    1[4, 5, 6, 7]    2[8, 9, 10, 11]    3[12, 13, 14, 15]
		// -> ������ ���� 1�忡 �ִ� 4 PORT ����ȴ�                             
		// **********************************************************************
		nBardData = n_Data / 4000;
		// **********************************************************************
		break;

	case 1 :  // PORT 
		// **********************************************************************
		// I/O MAP ��ȣ�� 1000���� ������ ���� PORT ��ȣ�� �ǵ��� ���ǵǾ� �ִ�  
		// -> PORT ���� ������ �ִ� [0 - 15] �̴�                                
		// -> ������ ����� �ִ� 2������ �����Ѵ�                                
		// **********************************************************************
		nBardData = n_Data / 1000;

		if (nBardData>3)
			nBardData -= 4;
		// **********************************************************************
		break;

	case 2 :  // SLAVE 
		// **********************************************************************
		// �� PORT�� ����� SLAVE ��ȣ�� �����Ѵ�                                
		// -> PORT �� �ִ� [0 - 7] ����ȴ�                                      
		// **********************************************************************
		nBardData = n_Data     % 1000;
		nBardData = nBardData / 100;
		// **********************************************************************
		break;

	case 3 :  // I/O BIT 
		// **********************************************************************
		// �ش� I/O BIT ��ġ �����Ѵ�                                            
		// -> I/O BIT�� �ִ� [0 - 15] ������ �� �ִ�                             
		//  : IN/OUT ���´� ���Ƿ� ���� �����Ѵ�                                 
		// **********************************************************************
		nBardData = n_Data     % 1000;
		nBardData = nBardData % 100;
		// **********************************************************************
		break;

	default :
		return BD_ERROR;
		break;
	}

	return nBardData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [WORD ����]                    
// ******************************************************************************
int CFastechPublic_IO::Set_IO_LatchWord(int n_MasterID, int n_PortNo, int n_SlaveNo, WORD w_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_SetLatchWord(n_MasterID, n_PortNo, n_SlaveNo, w_Data);  // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BYTE ����]                    
// ******************************************************************************
int CFastechPublic_IO::Set_IO_LatchByte(int n_MasterID, int n_PortNo, int n_SlaveNo, int n_Type, BYTE bt_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_SetLatchByte(n_MasterID, n_PortNo, n_SlaveNo, n_Type, bt_Data);  // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BIT ����]                     
// ******************************************************************************
int CFastechPublic_IO::Set_IO_LatchBit(int n_IONo, BOOL b_Data) 
{
	CString sMsg;
	int     nRet=0;	
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_SetLatchBit(nMasterID, nPortNo, nSlaveNo, nBitNo, b_Data);  // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]                             
// ******************************************************************************
WORD CFastechPublic_IO::Get_IO_LatchWord(int n_MasterID, int n_PortNo, int n_SlaveNo) 
{
	CString sMsg;
	int     nRet=0;
	
	WORD    wData=0;

	nRet = HSSI_ReadLatchWord(n_MasterID, n_PortNo, n_SlaveNo, &wData);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
		//wData�� ������ ���� //wData = BD_GOOD;
	}
	else
	{
		wData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return wData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]                             
// ******************************************************************************
BYTE CFastechPublic_IO::Get_IO_LatchByte(int n_MasterID, INT n_PortNo, int n_SlaveNo, int n_Type) 
{
	CString sMsg;
	int     nRet=0;	
	BYTE    bData=0;

	nRet = HSSI_ReadLatchByte(n_MasterID, n_PortNo, n_SlaveNo, n_Type, &bData);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{	 
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return bData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]                              
// ******************************************************************************
BOOL CFastechPublic_IO::Get_IO_LatchBit(int n_IONo) 
{
	CString sMsg;
	int     nRet=0;
	BOOL    bData=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_ReadLatchBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return bData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]                             
// ******************************************************************************
int CFastechPublic_IO::Reset_IO_LatchWord(int n_MasterID, int n_PortNo, int n_SlaveNo, WORD w_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_ResetLatchWord(n_MasterID, n_PortNo, n_SlaveNo, w_Data);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
		nRet = BD_GOOD;
	}
	else
	{
		nRet = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]                             
// ******************************************************************************
int CFastechPublic_IO::Reset_IO_LatchByte(int n_MasterID, int n_PortNo, int n_SlaveNo, int n_Type, BYTE bt_Data) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_ResetLatchByte(n_MasterID, n_PortNo, n_SlaveNo, n_Type, bt_Data);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]                              
// ******************************************************************************
int CFastechPublic_IO::Reset_IO_LatchBit(int n_IONo, BOOL b_Data) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_SetLatchBit(nMasterID, nPortNo, nSlaveNo, nBitNo, b_Data);  // SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// ������ ���� ���� ���� �˻� �Լ�                                               
// ******************************************************************************
int CFastechPublic_IO::Check_IO_MasterStatus(INT n_MasterID) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_IsExistMasterBoard(n_MasterID);  // ������ ���� ���� ���� �˻� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// PORT ���� ���� �� ���� ���� �˻� �Լ�                                         
// ******************************************************************************
int CFastechPublic_IO::Check_IO_PortStatus(int n_MasterID, int n_PortNo) 
{
	CString sMsg;
	int     nRet=0;

	nRet = HSSI_IsExistPort(n_MasterID, n_PortNo);  // PORT ���� ���� �� ���� ���� �˻� �Լ�
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//I/O�� ���� �����Ѵ�  james Lee 2008.9.5
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [WORD ����]                                
// ******************************************************************************
int CFastechPublic_IO::Set_Out_Word(int n_IONo, WORD w_Data) 
{
	CString sMsg;
	int     nRet=0;	
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);

	nRet = HSSI_WriteOutputWord(nMasterID, nPortNo, nSlaveNo, w_Data);  // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BYTE ����]                                
// ******************************************************************************
int CFastechPublic_IO::Set_Out_Byte(int n_IONo, int n_Type, BYTE bt_Data) 
{
	CString sMsg;
	int     nRet=0;	
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);

	nRet = HSSI_WriteOutputByte(nMasterID, nPortNo, nSlaveNo, n_Type, bt_Data);  // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BIT ����]                                 
// ******************************************************************************
int CFastechPublic_IO::Set_Out_Bit(int n_IONo, BOOL b_OnOff) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_WriteOutputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, b_OnOff);  // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return nRet;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� �Է� ��ȣ READ �Լ� [WORD ����]                                
// ******************************************************************************
WORD CFastechPublic_IO::Get_In_Word(int n_IONo) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;
	WORD    wData=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);

	nRet = HSSI_ReadInputWord(nMasterID, nPortNo, nSlaveNo, &wData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		wData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return wData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ READ �Լ� [WORD ����]                                
// ******************************************************************************
WORD CFastechPublic_IO::Get_Out_Word(int n_IONo)
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;
	WORD    wData=0;
	
	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);
	
	nRet = HSSI_ReadOutputWord(nMasterID, nPortNo, nSlaveNo, &wData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [WORD ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		wData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return wData;	
}

// ******************************************************************************
// SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BYTE ����]                                
// ******************************************************************************
BYTE CFastechPublic_IO::Get_In_Byte(int n_IONo, int n_Type) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;
	BYTE    btData=0;

	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);

	nRet = HSSI_ReadInputByte(nMasterID, nPortNo, nSlaveNo, n_Type, &btData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		btData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return btData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ READ �Լ� [BYTE ����]                                
// ******************************************************************************
BYTE CFastechPublic_IO::Get_Out_Byte(int n_IONo, int n_Type)
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0;
	BYTE    btData=0;
	
	nMasterID = Search_IO_BoardInformation(0, n_IONo * 100);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo * 100);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo * 100);
	
	nRet = HSSI_ReadOutputByte(nMasterID, nPortNo, nSlaveNo, n_Type, &btData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BYTE ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		btData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return btData;
}

BOOL CFastechPublic_IO::Get_In_Bit(int nIONo, int n_SetTime)//james 2010,0128, long * np_GetTime) 
{
	CString sMsg;
	int     iRet=0;	
	INT     iMasterID=0, iPortNo=0, iSlaveNo=0, iBitNo=0;
	BOOL    bData;
	long long_Time = 0;
	
	iMasterID = Search_IO_BoardInformation(0, nIONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	iPortNo   = Search_IO_BoardInformation(1, nIONo);
	iSlaveNo  = Search_IO_BoardInformation(2, nIONo);
	iBitNo    = Search_IO_BoardInformation(3, nIONo);
	
	iRet = HSSI_ReadInputBit(iMasterID, iPortNo, iSlaveNo, iBitNo, &bData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]
	if (iRet == STATUS_SUCCESS)
	{
		//bData = MOT_FALSE;
	}
	else
	{
		bData = CTLBD_RET_ERROR;
		sMsg = ErrorOccurInfo(iRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (CTLBD_IO_DEBUGMODE)
		{
			AfxMessageBox(sMsg);
		}
	}
	//james test
	if(bData == CTL_ON)
	{
		
		mn_io_in_time_0[nIONo][0] = GetCurrentTime();
		
		mn_io_in_time_0[nIONo][1] = GetCurrentTime();
		long_Time = mn_io_in_time_0[nIONo][1] - mn_io_in_time_1[nIONo][0];
		if(long_Time > (n_SetTime * 3)) //091127 100))
		{
			mn_io_in_time_1[nIONo][0] = GetCurrentTime();
			bData = CTL_IO_PROCEED; //091127 
		}
		else if(long_Time > n_SetTime)
		{
			bData = CTL_ON; 
		}
		else if(long_Time < 0) //091010 �߰� 
		{
			mn_io_in_time_1[nIONo][0] = GetCurrentTime();
			bData = CTL_IO_PROCEED; //091127
		}		
		else
		{
			bData = CTL_IO_PROCEED; 
		}		 
	}
	else //CTL_OFF
	{
		mn_io_in_time_1[nIONo][0] = GetCurrentTime();
		
		mn_io_in_time_1[nIONo][1] = GetCurrentTime();
		long_Time = mn_io_in_time_1[nIONo][1] - mn_io_in_time_0[nIONo][0];
		
		if(long_Time > (n_SetTime * 3)) //091127 100))
		{
			mn_io_in_time_0[nIONo][0] = GetCurrentTime();
			bData = CTL_IO_PROCEED; //091127
		}
		else if(long_Time > n_SetTime)
		{
			bData = CTL_OFF; 			
		}
		else if(long_Time < 0) //091010 �߰� 
		{
			mn_io_in_time_0[nIONo][0] = GetCurrentTime();
			bData = CTL_IO_PROCEED; //091127
		}
		else
		{			
			bData = CTL_IO_PROCEED; 
		}		 
	}
	
	return bData;
}
// ******************************************************************************

// ******************************************************************************
// SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]                                 
// ******************************************************************************
BOOL CFastechPublic_IO::Get_In_Bit(int n_IONo) 
{
	CString sMsg;
	int     nRet=0;
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0, nBitNo = 0;
	BOOL    bData;

	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);

	nRet = HSSI_ReadInputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return bData;
}




// ******************************************************************************
// SLAVE I/O ��� ��� ��ȣ READ �Լ� [BIT ����]                                 
// ******************************************************************************
BOOL CFastechPublic_IO::Get_Out_Bit(int n_IONo)
{
	CString sMsg;
	int     nRet=0;	
	INT     nMasterID=0, nPortNo=0, nSlaveNo=0,nBitNo=0;
	BOOL    bData;
	
	nMasterID = Search_IO_BoardInformation(0, n_IONo);  // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	nPortNo   = Search_IO_BoardInformation(1, n_IONo);
	nSlaveNo  = Search_IO_BoardInformation(2, n_IONo);
	nBitNo    = Search_IO_BoardInformation(3, n_IONo);
	
	nRet = HSSI_ReadOutputBit(nMasterID, nPortNo, nSlaveNo, nBitNo, &bData);  // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]
	if (nRet == STATUS_SUCCESS)
	{
	}
	else
	{
		bData = BD_ERROR;
		sMsg = ErrorOccurInfo(nRet);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�
		if (mn_errormsg_debug_mode)	AfxMessageBox(sMsg);
	}
	
	return bData;
}
// ******************************************************************************




// ******************************************************************************
// HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�                                        
// -> nErrorNum                : �߻��� ���� ��ȣ                                
// -> STATUS_SUCCESS = 0x0     : ���� ����                                       
// -> STATUS_ERROR_NO_DEVICE   : ���� ���� ���� ������                           
// -> STATUS_ERROR_READ        : READ ���� ����                                  
// -> STATUS_ERROR_WRITE       : WRITE ���� ����                                 
// -> STATUS_ERROR_INITIALIZE  : �ʱ�ȭ ���� [RESET ����]                        
// -> STATUS_ERROR_COMMAND     : CMD ��뿡 ���� �߻�                            
// -> STATUS_ERROR_FILE        : FILE�� ���� �߻�                                
// -> STATUS_ERROR_PORT        : PORT ������                                     
// -> STATUS_ERROR_SLAVE       : SLAVE�� ON �ƴ�                                 
// -> STATUS_NOTUSE_COMMAND    : �������� �ʴ� ��ɾ�                            
// -> STATUS_INVALID_BOARDID   : �ش� ���� ������                                
// -> STATUS_INVALID_PORTNO    : �ش� PORT ������                                
// -> STATUS_INVALID_SLAVEID   : �ش� SLAVE ������                               
// -> STATUS_INVALID_PARAMETER : �Ķ���� �Է� ����                              
// -> STATUS_INVALID_DLL       : �߸��� DLL ���                                 
// ******************************************************************************
CString CFastechPublic_IO::ErrorOccurInfo(int nErrorNum) 
{
	CString sErrorMsg;  // ���� �޽��� �ӽ� ���� ���� 

	if (nErrorNum == STATUS_ERROR_NO_DEVICE)
	{
		sErrorMsg = _T("���� ���� ���� ������");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("The running boards already exist");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_READ)
	{
		sErrorMsg = _T("READ ���� ����");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("READ operation fails");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_WRITE)
	{
		sErrorMsg = _T("WRITE ���� ����");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("WRITE operation fails");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_INITIALIZE)
	{
		sErrorMsg = _T("�ʱ�ȭ ���� [RESET ����]");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Failed to initialize [RESET included]");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_COMMAND)
	{
		sErrorMsg = _T("CMD ��뿡 ���� �߻�");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Problems on using CMD");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_FILE)
	{
		sErrorMsg = _T("FILE�� ���� �߻�");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("FILE occur with");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_PORT)
	{
		sErrorMsg = _T("PORT ������");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("PORT already exist");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_ERROR_SLAVE)
	{
		sErrorMsg = _T("SLAVE�� ON �ƴ�");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Not a SLAVE ON");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_NOTUSE_COMMAND)
	{
		sErrorMsg = _T("�������� �ʴ� ��ɾ�");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Commands that are not supported");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_INVALID_BOARDID)
	{
		sErrorMsg = _T("�ش� ���� ������");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("The board already exist");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_INVALID_PORTNO)
	{
		sErrorMsg = _T("�ش� PORT ������");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("PORT that already exist");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_INVALID_SLAVEID)
	{
		sErrorMsg = _T("�ش� SLAVE ������");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("SLAVE that already exist");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_INVALID_PARAMETER)
	{
		sErrorMsg = _T("�Ķ���� �Է� ����");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Input parameters failed");	// 20130926 kjh english
	}
	else if (nErrorNum == STATUS_INVALID_DLL)
	{
		sErrorMsg = _T("�߸��� DLL ���");
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg = _T("Using the wrong DLL");	// 20130926 kjh english
	}
	else
	{
		sErrorMsg.Format(_T("���ǵ��� ���� HSSI ���� �ڵ� = %d"), nErrorNum);
		if(g_local.GetLocalType() == LOCAL_ENG) sErrorMsg.Format(_T("HSSI error code is not defined = %d"), nErrorNum);	// 20130926 kjh english
	}

// 	strncpy(cMsg, sErrorMsg, sizeof(cMsg)-1);
// 	cMsg[sizeof(cMsg)-1] = '\0'; //2011.0518

	return sErrorMsg;
}
// ******************************************************************************

/*
int CFastechPublic_IO::Check_IO_Port(int n_io, int n_time, int n_flag)
{
	int Ret = CTLBD_READY;	// �Լ� ���� �÷��� ���� 
	
	if (n_time == 0)	// ��� �ð����� �ٷ� ���ϰ��� �޾ƾ� �Ѵ�.
	{
		if (Get_IO_InportBit(n_io) == TRUE)
		{
			Ret = CTLBD_YES;
		}
		else	Ret = CTLBD_NO;
	}
	else				// ���� �ð����� Ȯ���ϰ�, ���ϰ��� �޴´�.
	{
		if (IOFlag[n_io] != true)
		{
			IOTime[n_io][0]	= GetCurrentTime();
			IOFlag[n_io] = true;
		}
		else if (Get_IO_InportBit(n_io) == TRUE && IOFlag[n_io] == true)
		{
			IOTime[n_io][1] = GetCurrentTime();
			IOTime[n_io][2] = IOTime[n_io][1] - IOTime[n_io][0];
			
			if (IOTime[n_io][2] >= n_time)
			{
				IOFlag[n_io] = false;
				Ret = CTLBD_YES;
			}
		}
		else if (Get_IO_InportBit(n_io) == FALSE && IOFlag[n_io] == true)
		{
			IOTime[n_io][1] = GetCurrentTime();
			IOTime[n_io][2] = IOTime[n_io][1] - IOTime[n_io][0];
			
			if (IOTime[n_io][2] >= n_time)
			{
				IOFlag[n_io] = false;
				Ret = CTLBD_NO;
			}
		}
	}
	
	return Ret;
}

int CFastechPublic_IO::Check_IO_Port_Yield(int n_io, int n_time, int n_yield)
{
	int Ret = CTLBD_READY;	// �Լ� ���� �÷��� ���� 
	
	if (IOYFlag[n_io] != true)
	{
		IOYTime[n_io][0] = GetCurrentTime();
		IOYFlag[n_io] = true;
		// Yield Check �ʱ�ȭ. 2K6/05/18/ViboX
		IOYCount[n_io][0] = 0;					// false
		IOYCount[n_io][1] = 0;					// true
		IOYCount[n_io][2] = 0;					// total
	}
	else if (Get_IO_InportBit(n_io) == TRUE && IOYFlag[n_io] == true)
	{
		IOYCount[n_io][1]++;
	}
	else if (Get_IO_InportBit(n_io) == FALSE && IOYFlag[n_io] == true)
	{
		IOYCount[n_io][0]++;
	}
	
	if (IOYFlag[n_io] == true)
	{
		IOYTime[n_io][1] = GetCurrentTime();
		IOYTime[n_io][2] = IOYTime[n_io][1] - IOYTime[n_io][0];
		
		if (IOYTime[n_io][2] >= n_time)
		{
			
			IOYCount[n_io][2] = IOYCount[n_io][1] + IOYCount[n_io][0];
			
			if (IOYCount[n_io][2] <= 0)
			{
				return CTLBD_NO;
			}
			IOYYield[n_io] = (float)IOYCount[n_io][1] / IOYCount[n_io][2];
			
			if (IOYYield[n_io] >= n_yield)
			{
				Ret = CTLBD_YES;
			}
			else
			{
				Ret = CTLBD_NO;
			}
			IOYFlag[n_io] = false;
		}
	}
	return Ret;
}

*/