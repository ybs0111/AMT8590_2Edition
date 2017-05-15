// RUN_IO_ReadWrite.h: interface for the CRUN_IO_ReadWrite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUN_IO_READWRITE_H__7C671354_3075_4672_BBCD_4586CDAC5684__INCLUDED_)
#define AFX_RUN_IO_READWRITE_H__7C671354_3075_4672_BBCD_4586CDAC5684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRUN_IO_ReadWrite  
{
public:
	CRUN_IO_ReadWrite();
	virtual ~CRUN_IO_ReadWrite();
	
// Operations
public:	
	void Run_Total_IORead();
	void	Init_Total_IORead(int n_mode) ; //��� I/O ����� �ʱ�ȭ�� I/O�� ���¸� �о� �ش� ��Ʈ�� �⺻ ������ �޾� ������ �ʱ�ȭ �Ѵ� 

};
extern CRUN_IO_ReadWrite		RUN_IO_ReadWrite;

#endif // !defined(AFX_RUN_IO_READWRITE_H__7C671354_3075_4672_BBCD_4586CDAC5684__INCLUDED_)
