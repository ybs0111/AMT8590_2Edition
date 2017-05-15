// FastechPublic_IO.h: interface for the CFastechPublic_IO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FASTECHPUBLIC_IO_H__C22EE9E3_BCDD_43ED_B749_CDFE31F58416__INCLUDED_)
#define AFX_FASTECHPUBLIC_IO_H__C22EE9E3_BCDD_43ED_B749_CDFE31F58416__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////
//DLL ������ ���濹�� //2011.1007 �߰� 
/////////////////////////////////////////////////////////
#define BD_NO				0		//� ������ Ŭ����� ���� 
#define BD_YES				1		//� ������ ��û�� ���� 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//motor, i/O ������� ���ϰ��� �� �͸� ����Ѵ�  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BD_ERROR	   -1
#define BD_PROCEED		0
#define BD_GOOD			1
#define BD_RETRY		2
#define BD_SAFETY		3


#define DBIT0	0x0001 
#define DBIT1	0x0002 
#define DBIT2	0x0004 
#define DBIT3	0x0008 
#define DBIT4	0x0010 
#define DBIT5	0x0020 
#define DBIT6	0x0040 
#define DBIT7	0x0080 

#define DBIT8	0x0100 
#define DBIT9	0x0200 
#define DBIT10	0x0400 
#define DBIT11	0x0800 
#define DBIT12	0x1000 
#define DBIT13	0x2000 
#define DBIT14	0x4000 
#define DBIT15	0x8000 

#define DBIT16	0x00010000 
#define DBIT17	0x00020000 
#define DBIT18	0x00040000 
#define DBIT19	0x00080000 
#define DBIT20	0x00100000 
#define DBIT21	0x00200000 
#define DBIT22	0x00400000 
#define DBIT23	0x00800000 

#define DBIT24	0x01000000 
#define DBIT25	0x02000000 
#define DBIT26	0x04000000 
#define DBIT27	0x08000000 
#define DBIT28	0x10000000 
#define DBIT29	0x20000000 
#define DBIT30	0x40000000 
#define DBIT31	0x80000000 
//#define HSSI_DEBUG		1 //2011.1019 
//#define HSSI_GOOD			0
//#define HSSI_ERROR		-1
#define HSSI_MAX_IO		7715 //max io board 2�� ������ �����Ͽ� ������� //max io board 4�� ������ ó���Ѵ� 

class CFastechPublic_IO  
{
public:
	CFastechPublic_IO();
	virtual ~CFastechPublic_IO();

public:
	int mn_errormsg_debug_mode; //���� �޼��� ��¹�� => 0:������ , 1:���
//	int mn_simulation_mode; //���� ������ ���� ���  => 0:������ , 1:��� 

	long mn_io_in_time_0[HSSI_MAX_IO][2]; //maxio == 6500
	long mn_io_in_time_1[HSSI_MAX_IO][2]; //maxio == 6500

	int n_in[HSSI_MAX_IO];   // ��ü �� ��Ʈ I/O ���� ���� ����
	int n_out[HSSI_MAX_IO];  // ��ü �ƿ� ��Ʈ I/O ���� ���� ����

public:

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//2011.1019 james lee WORD ������ I/O�� �����Ѵ�
	//Ver 0.0.1_2011.1019
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int IO_ReadWrite(int n_bd_num, int n_port_num, int n_slave_num, int n_rw_mode);//2011.1019 james //Word ������ ����� ����ϴ� �Լ� 
	int get_in_bit(int n_IONo, int n_OnOff);  //2011.1019 Simulation ���۱��� �������� onoff �߰� //Word ������ ����� ����ϴ� �Լ�
	int set_out_bit(int n_IONo, int n_OnOff); //2011.1019 Simulation ���۱��� �������� onoff �߰� //Word ������ ����� ����ϴ� �Լ�
	int get_out_bit(int n_IONo, int n_OnOff); //2011.1019 Simulation ���۱��� �������� onoff �߰� //Word ������ ����� ����ϴ� �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////


	int  Search_IO_BoardInformation(int nType, int nData);             // HSSI ���� ������ Ȯ�� �� �˻� �Լ�
	int  Set_IO_BoardOpen(INT* piMasterNo, int nOpenMethod);           // I/O ���� ���� �Լ�
	int  Set_IO_BoardClose(bool bCloseMethod);                         // I/O ���� ���� �Լ�
	int  Search_IO_Master(INT* piMasterNo);                            // PC�� ����� ������ ���� ���� �˻� �Լ�
	int  Search_IO_Port(int nMasterID, INT* piPortNo);                 // ������ ���忡 ����� PORT ���� �˻� �Լ�
	int  Search_IO_Slave(int nMasterID, int nPortNo, INT* piSlaveNo);  // PORT�� ����� SLAVE �˻� �Լ�
	BOOL Check_IO_Slave(int nMasterID, int nPortNo, int nSlaveID);     // PORT�� ����� SLAVE [ENABLE/DISABLE] ���� �˻� �Լ�

	int  Set_IO_HSSISpeed(int nMasterID, int nPortNo, int nType);                  // PORT�� SLAVE I/O ������ ��� �ӵ� ���� �Լ�
	int  Get_IO_HSSISpeed(int nMasterID, int nPortNo, INT* piType);                // PORT�� SLAVE I/O ������ ��� �ӵ� ���� �Լ�
	int  Set_IO_PortAutoEnable(int nMasterID, int nPortNo);                           // PORT�� ����� ��� SLAVE I/O ��� �ڵ� ENABLE �Լ�
	int  Set_IO_SlaveEnable(int nMasterID, int nPortNo, int nSlaveNo, BOOL bEnable);  // SLAVE I/O ��� ���� ENABLE/DISABLE ���� �Լ�
	
	int  Set_IO_DefineWord(int nMasterID, int nPortNo, int nSlaveNo, WORD wData);               // SLAVE I/O ����� ����� ���� �Լ� [WORD ����]
	int  Set_IO_DefineByte(int nMasterID, int nPortNo, int nSlaveNo, int nType, BYTE btData);   // SLAVE I/O ����� ����� ���� �Լ� [BYTE ����]
	int  Set_IO_DefineBit(int nIONo, BOOL bData);                                               // SLAVE I/O ����� ����� ���� �Լ� [BIT ����]
	int  Get_IO_DefineWord(int nMasterID, int nPortNo, int nSlaveNo, WORD* pwData);             // SLAVE I/O ����� ����� ���� ���� ���� [WORD ����]
	int  Get_IO_DefineByte(int nMasterID, INT iPortNo, int nSlaveNo, int nType, BYTE* pbData);  // SLAVE I/O ����� ����� ���� ���� ���� [BYTE ����]
	int  Get_IO_DefineBit(int nIONo, BOOL* pbData);                                             // SLAVE I/O ����� ����� ���� ���� ���� [BIT ����]
	
	int  Set_IO_LatchWord(int nMasterID, int nPortNo, int nSlaveNo, WORD wData);                  // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [WORD ����]
	int  Set_IO_LatchByte(int nMasterID, int nPortNo, int nSlaveNo, int nType, BYTE btData);      // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BYTE ����]
	int  Set_IO_LatchBit(int nIONo, BOOL bData);                                                  // SLAVE I/O ����� �Է��� LATCH ���� ���� �Լ� [BIT ����]
	WORD Get_IO_LatchWord(int nMasterID, int nPortNo, int nSlaveNo);                              // SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]
	BYTE Get_IO_LatchByte(int nMasterID, INT iPortNo, int nSlaveNo, int nType);                   // SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]
	BOOL Get_IO_LatchBit(int nIONo);                                                              // SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]
	int  Reset_IO_LatchWord(int nMasterID, int nPortNo, int nSlaveNo, WORD wData);                // SLAVE I/O ����� LATCH ���� ���� �Լ� [WORD ����]
	int  Reset_IO_LatchByte(int nMasterID, int nPortNo, int nSlaveNo, int nType, BYTE btData);    // SLAVE I/O ����� LATCH ���� ���� �Լ� [BYTE ����]
	int  Reset_IO_LatchBit(int nIONo, BOOL bData);                                                // SLAVE I/O ����� LATCH ���� ���� �Լ� [BIT ����]
	
	int  Check_IO_MasterStatus(INT nMasterID);                            // ������ ���� ���� ���� �˻� �Լ�
	int  Check_IO_PortStatus(int nMasterID, int nPortNo);                 // PORT ���� ���� �� ���� ���� �˻� �Լ�
	int  Check_IO_SlaveStatus(int nMasterID, int nPortNo, int nSlaveNo);  // SLAVE I/O MODULE�� ENABLE ���·� ������ ���忡 ����Ǿ� �ִ��� �˻� �Լ�

	int  Check_IO_BoardExist(int nMaxSlot, int nMaxPort, int nMaxSlave);  // ���� ���� ���� �˻� �Լ�

	BOOL Check_Bit(long nValue, int nBitPos);            // Ư�� ��ġ BIT�� �˻� �Լ�
	void Set_Bit(long &nValue, int nBit, BOOL bOn);      // Ư�� ��ġ BIT ���� �Լ�

	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// I/O ���� LIB
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int  Initialize_Auto_IO_Board(void);   // I/O ���� ���̺귯�� �ʱ�ȭ �Լ�

	int  Set_Out_Word(int nIONo, WORD wData);              // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [WORD ����]
	int  Set_Out_Byte(int nIONo, int nType, BYTE btData);  // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BYTE ����]
	int  Set_Out_Bit (int nIONo, BOOL bOnOff);             // SLAVE I/O ��� ��� ��ȣ �߻� �Լ� [BIT ����]

	WORD Get_In_Word(int nIONo);                           // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [WORD ����]
	BYTE Get_In_Byte(int nIONo, int nType);                // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BYTE ����]
	BOOL Get_In_Bit(int nIONo);                            // SLAVE I/O ��� �Է� ��ȣ READ �Լ� [BIT ����]

	BOOL Get_In_Bit(int nIONo, int n_SetTime);//james 2010,0128 , long * np_GetTime) ; //james 2009.5.27 �����ϰ� �ִ� �ð��� ã�� ���� �߰� 

	WORD Get_Out_Word(int nIONo);							// SLAVE I/O ��� ��� ��ȣ READ �Լ� [WORD ����]
	BYTE Get_Out_Byte(int nIONo, int nType);				// SLAVE I/O ��� ��� ��ȣ READ �Լ� [BYTE ����]
	BOOL Get_Out_Bit(int nIONo);							// SLAVE I/O ��� ��� ��ȣ READ �Լ� [BIT ����]

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Word(16bit) ������ �����Ѵ� //Picker ���� ��� ���� �ۼ�  
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int Lib_Set_Output_16(int nIoNum, int nOnOff, int *np_Data);  
	int Lib_Get_Input_16(int nIoNum, int nOnOff, int *np_Data);
	int Lib_Get_Output_16(int nIoNum, int nOnOff, int *np_Data);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	int Check_IO_Port_Yield(int n_io, int n_time, int n_yield = 70);
//	int Check_IO_Port(int n_io, int n_time = 0, int n_flag = CTL_ON);
		

	
	
	// **************************************************************************
	// I/O ���� ���� Ŭ����                                                      
	// **************************************************************************
	CString ErrorOccurInfo(int nErrorNum);  // HSSI DLL �Լ� ȣ�� ���� ���� �Ľ� �Լ�

};
extern CFastechPublic_IO  FAS_IO;  

#endif // !defined(AFX_FASTECHPUBLIC_IO_H__C22EE9E3_BCDD_43ED_B749_CDFE31F58416__INCLUDED_)
