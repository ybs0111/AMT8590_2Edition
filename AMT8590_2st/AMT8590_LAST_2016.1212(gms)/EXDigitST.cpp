///////////////////////////////////////////////////////////////////////////////
/* ****************************************************************************** */
// FILE NAME : CEXDigitST.cpp
//
// Copyright (C) 2003 AMT Corporation
// All rights reserved.
//
// CREATED BY  : Lee Kyu Il
// REVISION    :
//     1> 2003. 12. 17 : Created by Lee Kyu Il
// DESCRIPTION :
//     Implementation of the CEXDigitST and associated classes
//	   This code may be used in compiled form in any way you desire. This
//	   file may be redistributed unmodified by any means PROVIDING it is
//	   not sold for profit without the authors written consent, and
//	   providing that this notice and the authors name and all copyright
//	   notices remains intact.
//
//	   An email letting me know how you are using it would be nice as well.
//
//
// REFERENCE   :
// 
/* ****************************************************************************** */
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EXDigitST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEXDigitST

CEXDigitST::CEXDigitST()
{
	m_nPrecision = 2;    /* ����� ������ ���� �ʱ�ȭ */

	m_nValue = 0;        /* ��� ������ ������ �ʱ�ȭ */
	m_strValue.Empty();  /* ��� ���ڿ� ������ �ʱ�ȭ */

	m_b16Flag = FALSE ;  /* ��� ������ ���� �ʱ�ȭ [FALSE:������    TRUE:������] */

	m_bZeroPadding = FALSE;  /* ���� ���� 0���� ä������ ���� �÷��� */

	m_dwResize = ST_RIGHT | ST_BOTTOM;  /* ��Ʈ�� RESIZE �ɼ� [RIGHT-BOTTOM] */

	m_nWidth = 0;        /* ��� ��Ʈ�� �� �ʱ�ȭ */
	m_nHeight = 0;       /* ��� ��Ʈ�� ���� �ʱ�ȭ */

	m_pbmDigit = NULL;   /* ��Ʈ�� �ε� ���� �÷��� �ʱ�ȭ */
}


CEXDigitST::~CEXDigitST()
{
	/* ************************************************************************** */
	/* ��Ʈ���� �ε��� ��� �ش� ���ҽ� �����Ѵ�                                  */
	/* -> �� ��ü�� new �����ڸ� ����Ͽ� �������� �����Ͽ��� ������ �ݵ��       */
	/*    delete�ؾ� �Ѵ�                                                         */
	/* ************************************************************************** */
	if (m_pbmDigit != NULL)
		delete m_pbmDigit;

	m_pbmDigit = NULL;
	/* ************************************************************************** */
}


BEGIN_MESSAGE_MAP(CEXDigitST, CStatic)
	//{{AFX_MSG_MAP(CEXDigitST)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/* ****************************************************************************** */
/* Ŭ���� ���� ���� �Լ�                                                          */
/* -> �ش� Ŭ���� CHILD ���·� �����Ѵ�                                           */
/* ****************************************************************************** */
BOOL CEXDigitST::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	BOOL result ;

	/* ************************************************************************** */
	/* ������ �������Ϳ� ��� �� �����Ѵ�                                         */
	/* -> AfxRegisterWndClass() : Ŭ���� �̸��� �������Ϳ� ����ϴ� �Լ�          */
	/*  : �� �Լ��� Create() ��� �Լ����� ����Ѵ�                               */
	/* -> CreateEx() : ������ ���� �Լ�                                           */
	/* ************************************************************************** */
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;

	result = CWnd::CreateEx(/*WS_EX_CLIENTEDGE | WS_EX_STATICEDGE*/NULL, 
                          className, NULL, dwStyle, 
                          rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
                          pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	/* ************************************************************************** */

	if (result != 0)
		Invalidate() ;  /* ������ ���� ���� �Լ� */

	return result ;
} 
/* ****************************************************************************** */

/////////////////////////////////////////////////////////////////////////////
// CEXDigitST message ICTs


void CEXDigitST::OnPaint() 
{
	/* ************************************************************************** */
	/* BeginPaint() : ��ġ ���ؽ�Ʈ�� �Ҵ��ϰ� ���ŵ� ������ ���� ������          */
	/*                ��ȯ�ϴ� ������ ������ ������ ���μ����� �����Ѵ�           */
	/* -> �� �Լ��� WM_PAINT �޽��� ���信 ���� ��������                          */
	/* ************************************************************************** */
	PAINTSTRUCT lpPaint;
	BeginPaint(&lpPaint);
	/* ************************************************************************** */

	CWindowDC dc(this);

	/* ************************************************************************** */
	/* ��Ʈ���� �ε� �Ϸ�� ��� �ش� ��Ʈ���� ����Ͽ� ������ ī���� ����Ѵ�    */
	/* ************************************************************************** */
	if (m_pbmDigit->m_hObject)
		DrawDigits(&dc);  /* ������ ī���� ��� �Լ� */
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* EndPaint() : ������ �۾��� ���Ḧ ��Ÿ����                                 */
	/* -> ��� ������ �۾��� ����Ǹ� BeginPaint() �Ŀ� �� ���־�� �Ѵ�          */
	/* -> BeginPaint() �Լ��� ���� ī���̳� Ŀ���� �������ٸ� EndPaint() �Լ���   */
	/*    �װ��� �����Ѵ�                                                         */
	/* ************************************************************************** */
	EndPaint(&lpPaint);
	/* ************************************************************************** */
} 


BOOL CEXDigitST::SetStyle(UINT nBitmapId, int nPrecision)
{
	BITMAP bm;
	BOOL bRet;

	/* ************************************************************************** */
	/* ��Ʈ���� �ε��� ��� �ش� ���ҽ� �����Ѵ�                                  */
	/* -> �� ��ü�� new �����ڸ� ����Ͽ� �������� �����Ͽ��� ������ �ݵ��       */
	/*    delete�ؾ� �Ѵ�                                                         */
	/* ************************************************************************** */
	if (m_pbmDigit != NULL)
	{
		delete m_pbmDigit;

		m_pbmDigit = NULL;
	}
	/* ************************************************************************** */

	m_pbmDigit = new CBitmap;  /* ���ο� ��Ʈ�� ���� */

	/* ************************************************************************** */
	/* ���ο� ��Ʈ�� �ε��Ѵ�                                                     */
	/* -> LoadBitmap() : ����� ���ҽ� ���Ϸκ��� ��Ʈ�� ���ҽ��� �о� ���δ�     */
	/*  : ���� ���α׷��� BITMAP ���� ����ؼ� ���ҽ� ��ũ��Ʈ ����(.RC)��        */
	/*    ��Ʈ���� �����ؾ� �Ѵ�                                                  */
	/*  : ��Ʈ���� ����� ������ ���� ���α׷��� DeleteObject()�� ȣ���ؼ�        */
	/*    �޸𸮿��� ��Ʈ���� �����ؾ� �Ѵ�                                       */
	/*  : �� �Լ��� ��ġ ������ ��Ʈ��(DDB)�̳� ��ġ ������ ��Ʈ��(DIB)�� �д´�  */
	/*  : DIB�� �о� ���̸� DDB�� ��ȯ�ϰ� ���� ������ �о������                 */
	/* -> GetBitmap() : ȣ��� ��Ʈ���� ũ�⸦ ���Ѵ�                             */
	/* ************************************************************************** */
	bRet = m_pbmDigit->LoadBitmap(nBitmapId);
	if (bRet == TRUE)
	{
		m_pbmDigit->GetBitmap(&bm);

		m_nWidth = (int)bm.bmWidth / 13;  /* �Ѱ� ��Ʈ�� ���� ����Ѵ� */
		m_nHeight = bm.bmHeight;          /* ��Ʈ�� ���� ���� */

		SetPrecision(nPrecision);  /* �Է� ���� �˻� �Լ� */
	}
	/* ************************************************************************** */

	return bRet;
}

void CEXDigitST::SetValue(int nValue, BOOL bRepaint)
{
	char chr_buf[20];

	m_nValue = nValue;   /* ���ο� ��� �� ���� */
	m_strValue = LPCTSTR(_itoa(m_nValue, chr_buf, 10));	// String�� ��ȯ

	m_b16Flag = FALSE ;  /* ������ ������ ��� �÷��� ���� */

	/* ************************************************************************** */
	/* ������ ������ �ٽ� �׸���                                                  */
	/* -> InvalidateRect() : �־��� �����쿡 ���� ���� ������ ������ ���簢����   */
	/*    �����̴� �Լ�                                                           */
	/*  : ���� ������ �ٽ� �׷����� �ϴ� �������� �κ��� �����Ѵ�                 */
	/* ************************************************************************** */
	if (bRepaint == TRUE)
		Invalidate(FALSE);
	/* ************************************************************************** */
}

void CEXDigitST::SetValue(double dValue, BOOL bRepaint)
{
	char chr_buf[20];
	
	m_nValue = (int)dValue;   /* ���ο� ��� �� ���� */
	m_strValue = LPCTSTR(_itoa(m_nValue, chr_buf, 10));	// String�� ��ȯ

	m_b16Flag = FALSE ;  /* ������ ������ ��� �÷��� ���� */

	/* ************************************************************************** */
	/* ������ ������ �ٽ� �׸���                                                  */
	/* -> InvalidateRect() : �־��� �����쿡 ���� ���� ������ ������ ���簢����   */
	/*    �����̴� �Լ�                                                           */
	/*  : ���� ������ �ٽ� �׷����� �ϴ� �������� �κ��� �����Ѵ�                 */
	/* ************************************************************************** */
	if (bRepaint == TRUE)
		Invalidate(FALSE);
	/* ************************************************************************** */
}

void CEXDigitST::SetValue(CString strValue, BOOL bRepaint)
{
	if (strValue == "")		strValue = "0";
   	m_strValue = strValue;			// ���ο� ��� �� ����

	m_nValue = atoi(m_strValue);	// int�� ��ȯ.

	m_b16Flag = TRUE ;				// ������ ������ ��� �÷��� ����

	if (bRepaint == TRUE)
		OnPaint();
}


int CEXDigitST::GetValue()
{
	return m_nValue;
}

CString CEXDigitST::GetValueString()
{
	return m_strValue;
}

void CEXDigitST::SetPrecision(int nPrecision, BOOL bResize)
{
	/* ************************************************************************** */
	/* �Էµ� ���� ��� �������� �����ϴ��� �˻��Ѵ�                              */
	/* -> ������ ���ǿ� ���� ��Ʈ���� Ŭ���̾�Ʈ �����쿡 �����Ѵ�                */
	/* ************************************************************************** */
	if (nPrecision >= ST_MIN_PRECISION && nPrecision <= ST_MAX_PRECISION)
		m_nPrecision = nPrecision;
	/* ************************************************************************** */

	if (bResize == TRUE)
		Resize();  /* ��Ʈ�� ���� �Լ� */
}


int CEXDigitST::GetPrecision()
{
	return m_nPrecision;
}


void CEXDigitST::SetResize(DWORD dwResize, BOOL bResize)
{
	m_dwResize = dwResize;

	if (bResize == TRUE)
		Resize();  /* ��Ʈ�� ���� �Լ� */
}


DWORD CEXDigitST::GetResize()
{
	return m_dwResize;
}


void CEXDigitST::SetZeroPadding(BOOL bPad, BOOL bRepaint)
{
	m_bZeroPadding = bPad;  /* �е� ��Ÿ�� ���� */

	if (bRepaint == TRUE)
		Invalidate(FALSE);  /* ������ ���� ���� �Լ� */
}


BOOL CEXDigitST::GetZeroPadding()
{
	return m_bZeroPadding;
}


void CEXDigitST::Inc(BOOL bRepaint)
{
	SetValue(GetValue() + 1, bRepaint);  /* 1 ������ ������ ��� �Լ� */
}


void CEXDigitST::Dec(BOOL bRepaint)
{
	SetValue(GetValue() - 1, bRepaint);  /* 1 ���ҵ� ������ ��� �Լ� */
}


const char* CEXDigitST::GetVersionC()
{
	return "1.1";  /* ���� ���� */
}


const short CEXDigitST::GetVersionI()
{
	return 10;
} 


void CEXDigitST::DrawDigits(CDC* pDC)
{
	char szValue[ST_MAX_PRECISION+1];

	int nLoop;
	int destX;
	CRect rectCtrl;
	int nAsciiChar;
	CBitmap* pOldBitmap;

	/* ************************************************************************** */
	/* �޸� DC �����Ѵ�                                                         */
	/* -> CreateCompatibleDC() : �־��� ��ġ�� ���� �޸� DC�� �����Ѵ�          */
	/*  : �޸� DC�� �׸��� �۾��� ���� ����ϱ� ���� ���� ���α׷��� �ݵ��     */
	/*    ������ ���� ������ ��Ʈ���� �����Ͽ� DC�� �����ؾ� �Ѵ�                 */
	/*  : ��Ʈ���� ���õ� �ķ� DC�� ȭ�鿡 �����ϰų� ����� �̹��� �غ� ����     */
	/*  : DC�� �� �̻� �ʿ����� ������ DeleteDC() �Լ��� ����Ͽ� DC �����ؾ� ��  */
	/*  : �� �Լ��� ������(raster) ����� �����ϴ� ��ġ���� ����� �� �ִ�        */
	/*  : �� ����� �����ϴ����� ���δ� GetDeviceCaps() �Լ��� ����ϸ� �ȴ�      */
	/* ************************************************************************** */
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* ���ο� ��Ʈ�� �����Ѵ�                                                     */
	/* -> SelectObject() : ��ġ ���ؽ�Ʈ�� ���� ������Ʈ(��Ʈ) �����Ѵ�           */
	/* -> GetClientRect() : �־��� �������� Ŭ���̾�Ʈ ���� �簢���� ��� �Լ�    */
	/*  : ��ǥ�� �������� Ŭ���̾�Ʈ �������κ��� ���Ǵ� ���� ��ǥ�̴�          */
	/*  : ���� ����� ��ǥ�� (0,0)�̴�                                            */
	/* ************************************************************************** */
	pOldBitmap = memDC.SelectObject(m_pbmDigit);
	
	GetClientRect(rectCtrl);
	/* ************************************************************************** */

	destX = ST_BORDER_SPACE;  /* �׵θ��κ����� OFFSET ���� */

	PrepareString(szValue);  /* ����� ���� ���� �Լ� */

	/* ************************************************************************** */
	/* �Էµ� �����Ϳ� �ش��ϴ� ��Ʈ���� ����Ѵ�                                 */
	/* -> BitBlt() : ��Ʈ���� ��Ÿ���µ� ���Ǵ� ǥ�� �Լ��� ��Ʈ����            */
	/*    �޸� ��ġ ���ؽ�Ʈ���� ������ ��ġ ���ؽ�Ʈ ���� �ٸ� ��ġ ���ؽ�Ʈ�� */
	/*    �����ϴ� ������ �Ѵ�                                                    */
	/*  : �� �Լ��� ����Ϸ��� ���� ��Ʈ���� �޸� ��ġ ���ؽ�Ʈ�� �о� ���� ��  */
	/*    CreateCompatibleDC() �Լ��� ��Ʈ���� �����ؾ� �Ѵ�                      */
	/*  : ��Ʈ���� ������ ���� �ڵ带 ����ؼ� ���� ���� ������ �� �ִ�         */
	/*  : ��� ��ġ�� �� �Լ��� ���������� �ʱ� ������ GetDeviceCaps() �Լ��κ��� */
	/*    ��ȯ�Ǵ� RASTERCAPS ���� Ȯ���ؼ� ���� ���� Ȯ���ؾ� �Ѵ�               */
	/* ************************************************************************** */
	for(nLoop=0; nLoop<m_nPrecision; nLoop++)
	{
		if (m_bZeroPadding == TRUE && m_nValue >= 0)
			nAsciiChar = 0;
		else
			nAsciiChar = 10;

		if (szValue[nLoop] >= '0' && szValue[nLoop] <= '9')  /* 0-9������ ������ ��� */
			nAsciiChar = szValue[nLoop] - 48;

		if (szValue[nLoop] == '.')  /* �Ҽ����� ��� */
			nAsciiChar = 12;

		if (szValue[nLoop] == '-')  /* - ��ȣ�� ��� */
			nAsciiChar = 11;

		pDC->BitBlt(destX, ST_BORDER_SPACE, m_nWidth, m_nHeight, &memDC, 0+(m_nWidth*nAsciiChar), 0, SRCCOPY);
		destX += m_nWidth;
	}
	/* ************************************************************************** */

	memDC.SelectObject(pOldBitmap);
}


void CEXDigitST::Resize()
{
	CRect rectCtrl;

	Invalidate();  /* ������ ���� ���� �Լ� */

	/* ************************************************************************** */
	/* ��� ��Ʈ���� ����� ������ �缳���Ѵ�                                     */
	/* -> GetWindowRect() : �����츦 �ѷ��δ� �簢���� ũ�⸦ ���� lprc��         */
	/*    ����Ű�� RECT ����ü�� �� ���� �����Ѵ�                                 */
	/*  : ����� ��ǥ�� �ȼ� �����̸� ȭ���� ���� ����� �������� ����Ѵ�        */
	/* -> GetParent() : �־��� �����츦 �����ϰ� �ִ� �������� �ڵ��� ��´�      */
	/*  : �ڽ� �����찡 �޽����� �θ� ������� ���� ���ΰ��� ����ϱ� ����        */
	/*    � �ڽ� �������� �θ� ������ �ڵ��� ��µ� ���ȴ�                   */
	/*  : �� �������� �θ� �����쿡 ���� ������ ��� ���� ���� �� �ִ�          */
	/* -> ScreenToClient() : ȭ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ�Ѵ�               */
	/*  : ���콺 Ŀ���� ��ġ�� ������ Ŭ���̾�Ʈ ������ X/Y�� ��ȯ�ϱ� ����       */
	/*    ���� GetCursorPos() �Լ��� �����Ͽ� ���ȴ�                            */
	/*  : ó���Ǳ� ���� ������ �� �ִ�                                            */
	/*  : ���� �׸��ų� �ؽ�Ʈ ��ġ��Ű�� ���� WM_MOUSEMOVE �޽��� ó���� �� ��� */
	/* ************************************************************************** */
	GetWindowRect(rectCtrl);
	GetParent()->ScreenToClient(rectCtrl);
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* �Էµ� �����Ϳ� �ش��ϴ� ��Ʈ���� ����Ѵ�                                 */
	/* -> MoveWindow() : �������� ��ġ�� ũ�⸦ �����Ѵ�                          */
	/*  : �ֻ��� ���� �����쿡 �־ ��ǥü��� ȭ���� ���� ����� �����̸�,     */
	/*    �ڽ� �����쿡 �־�� �θ� �������� Ŭ���̾�Ʈ ������ �����̴�         */
	/* ************************************************************************** */
	if (m_dwResize & ST_RIGHT)   /* RIGHT�� �缳�� */
		rectCtrl.right = rectCtrl.left + (m_nWidth * m_nPrecision)+(ST_BORDER_SPACE*2);
	else                         /* LEFT�� �缳�� */
		rectCtrl.left = rectCtrl.right - (m_nWidth * m_nPrecision)-(ST_BORDER_SPACE*2);

	if (m_dwResize & ST_BOTTOM)  /* BOTTOM���� �缳�� */
		rectCtrl.bottom = rectCtrl.top + m_nHeight+(ST_BORDER_SPACE*2);
	else                         /* TOP���� �缳�� */
		rectCtrl.top = rectCtrl.bottom - m_nHeight-(ST_BORDER_SPACE*2);

	MoveWindow(rectCtrl);
	/* ************************************************************************** */
}


void CEXDigitST::PrepareString(char* szDest)
{
	char szStr[ST_MAX_PRECISION+1];	

	if (m_b16Flag == FALSE)
	{
		sprintf(szStr, "%*d", m_nPrecision,m_nValue);
		sprintf(szDest, "%*s", m_nPrecision, &szStr[strlen(szStr)-m_nPrecision]);
	}
	else
	{
		sprintf(szStr, "%*s", m_nPrecision,(LPSTR)(LPCSTR)m_strValue);
		sprintf(szDest, "%*s", m_nPrecision, &szStr[strlen(szStr)-m_nPrecision]);
	}

}

#undef ST_MIN_PRECISION
#undef ST_MAX_PRECISION
#undef ST_BORDER_SPACE