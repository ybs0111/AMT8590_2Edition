///////////////////////////////////////////////////////////////////////////////
/* ****************************************************************************** */
// FILE NAME : CCharSetCtrl.cpp
//
// Copyright (C) 2003 AMT Corporation
// All rights reserved.
//
// CREATED BY  : Lee Kyu Il
// REVISION    :
//     1> 2003. 12. 16 : Created by Lee Kyu Il
// DESCRIPTION :
//     Implementation of the CCharSetCtrl and associated classes
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
#include "charsetctrl.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PERFORM_MOUSEMOVE

/////////////////////////////////////////////////////////////////////////////
// CCharSetCtrl

CCharSetCtrl::CCharSetCtrl()
{
	int i, j, k;

    RegisterWindowClass();  /* Ŭ���� �������Ϳ� ����ϴ� �Լ� */

	/* ************************************************************************** */
	/* �� �׸��µ� �ʿ��� ���� ������ �ʱ�ȭ�Ѵ�                                  */
	/* -> GetSysColor() : ���� ���÷��� ��ġ�� ���� Į�� ���� ��´�            */
	/*  : �� ������ ����� ������ Ŭ������ ����� Ŭ������ ����� �������� ���   */
	/* -> LoadStandardCursor() : �⺻ Ŀ���� �ε��Ѵ�                             */
	/* -> AfxRegisterClass() : �־��� Ŭ������ �������Ϳ� ����Ѵ�                */
	/* -> AfxThrowResourceException() : ���ҽ� �ε� ���� �� ���� ó���Ѵ�         */
	/* ************************************************************************** */
	m_nRows=1;  /* �ʱ� �� ROW ���� */
	m_nCols=16;  /* �ʱ� �� COL ���� */

	m_crLine=::GetSysColor(COLOR_GRAYTEXT);      /* �� ���� Į�� */

	m_crText=::GetSysColor(COLOR_WINDOWTEXT);    /* ���� ����� ���� Į�� */
	m_crBkg=::GetSysColor(COLOR_WINDOW);         /* �� ��� Į�� */
	
	m_crHiliteText=RGB(0,0,255);                 /* ���̶���Ʈ ���� ����� ���� Į�� */
	m_crHiliteBkg=::GetSysColor(COLOR_BTNFACE);  /* ���̶���Ʈ �� ��� Į�� */

	m_nHiliteCol=-1;  /* ���̶���Ʈ ��ų �� COL ��ġ */
	m_nHiliteRow=-1;  /* ���̶���Ʈ ��ų �� ROW ��ġ */

	m_strFaceName="Arial";  /* ���� ����� ��Ʈ �̸� */
	m_bBold=FALSE;          /* ���� ���� ���� �÷��� */
	m_bItalic=FALSE;        /* ���� ���Ÿ� ���� �÷��� */

	m_nSelect=-1;  /* ���õ� �� ��ġ ���� ���� */
	m_nStart=32;

	for(i=0; i<m_nRows; i++)
	{
		for(j=0; j<m_nCols; j++)
		{
			k = i*m_nCols+j;
			mc_BcrColor[k] = RGB(0,0,255);
			mc_TcrColor[k] = ::GetSysColor(COLOR_WINDOWTEXT);

			mstr_Out[k].Empty();
		}
	}
	/* ************************************************************************** */
}

CCharSetCtrl::~CCharSetCtrl()
{
}

/* ****************************************************************************** */
/* Ŭ���� �������Ϳ� ����ϴ� �Լ�                                                */
/* -> �ش� Ŭ���� �������Ϳ� ��ϵ��� ���� ��� Ŭ���� ��Ͻ�Ų��                 */
/* ****************************************************************************** */
BOOL CCharSetCtrl::RegisterWindowClass()
{
	/* ************************************************************************** */
	/* AfxGetInstanceHandle() : ���� ���ø����̼ǿ� ���� �ν��Ͻ� �ڵ� ���� �Լ�  */
	/* ************************************************************************** */
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* �������Ϳ� ���ο� Ŭ������ ����Ѵ�                                        */
	/* -> GetClassInfo() : �־��� ������ Ŭ������ ���� WNDCLASS ������ ��´�     */
	/*  : �� ������ ����� ������ Ŭ������ ����� Ŭ������ ����� �������� ���   */
	/* -> LoadStandardCursor() : �⺻ Ŀ���� �ε��Ѵ�                             */
	/* -> AfxRegisterClass() : �־��� Ŭ������ �������Ϳ� ����Ѵ�                */
	/* -> AfxThrowResourceException() : ���ҽ� �ε� ���� �� ���� ó���Ѵ�         */
	/* ************************************************************************** */
    if (!(::GetClassInfo(hInst, CHARSETCTRL_CLASSNAME, &wndcls)))
    {
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = CHARSETCTRL_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }
	/* ************************************************************************** */

    return TRUE;
}
/* ****************************************************************************** */

BEGIN_MESSAGE_MAP(CCharSetCtrl, CWnd)
	//{{AFX_MSG_MAP(CCharSetCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharSetCtrl message handlers

void CCharSetCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	int i, j, k;

	CPen linePen(PS_SOLID, 1, m_crLine);
	CPen textPen(PS_SOLID, 1, m_crText);
	CFont ctrlFont;

	/* ************************************************************************** */
	/* GetClientRect() : �־��� �������� Ŭ���̾�Ʈ ���� �簢���� ��� �Լ�       */
	/* -> ��ǥ�� �������� Ŭ���̾�Ʈ �������κ��� ���Ǵ� ��� ��ǥ�̴�          */
	/*  : ����, ���� ����� ��ǥ�� (0,0)�̴�                                    */
	/* -> GetClientRect() Ư�� �������� Ŭ���̾�Ʈ ������ ũ�� �˰� ���� ��       */
	/*    �����ϰ� ����� �� �ִ�                                                 */
	/* FillSolidRect() : �־��� �簢�� ������ �־��� Į��� ä���                */
	/* ************************************************************************** */
	GetClientRect(m_Rect);

	dc.FillSolidRect(m_Rect, GetSysColor(COLOR_BTNFACE));
	/* ************************************************************************** */
	
	/* ************************************************************************** */
	/* -> SelectObject() : ��ġ ���ؽ�Ʈ�� ���� ������Ʈ(��Ʈ) ����               */
	/* ************************************************************************** */
	CPen* pOldPen=dc.SelectObject(&linePen);
	/* ************************************************************************** */
	
	/* ************************************************************************** */
	/* ���� �׸���                                                                */
	/* -> MoveTo() : ������ ��ġ ���ؽ�Ʈ�� ������ ������ ��ġ�� �����δ�         */
	/*  : ������ ��ġ�� LineTo()�� ���� �پ��� �׸��� �Լ��� ���ȴ�             */
	/* -> LineTo() : ������ ������ �p�� ��ġ�� ���� �׸���                        */
	/*  : ���� ���� ������ ������ �׸��� �ȴ�                                     */
	/* ************************************************************************** */
	m_nRangeCol=m_Rect.Width();
	m_nStepCol=m_nRangeCol/(m_nCols);
	m_nRangeRow=m_Rect.Height();
	m_nStepRow=m_nRangeRow/(m_nRows);
	
	m_Rect.right=m_Rect.left+m_nCols*m_nStepCol;
	m_Rect.bottom=m_Rect.top+m_nRows*m_nStepRow;

	for(i=0; i<=m_nCols; i++)
	{
		dc.MoveTo(m_Rect.left + i*m_nStepCol, m_Rect.top);
		dc.LineTo(m_Rect.left + i*m_nStepCol, m_Rect.Height());
	}

	for(j=0; j<=m_nRows; j++)
	{
		dc.MoveTo(m_Rect.left, m_Rect.top + j*m_nStepRow);
		dc.LineTo(m_Rect.Width()+1, m_Rect.top + j*m_nStepRow);
	}
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* ���� ����� ��Ʈ�� �����Ѵ�                                                */
	/* -> CreateFont() : �־��� Ư����� ���� �۲��� �����Ѵ�                   */
	/*  : ���� ���α׷��� �� �۲��� �����Ͽ� � ��ġ���� ����� �� �ִ�         */
	/*  : �Ϲ������� ���� ���α׷��� ���� �ϳ��� �۲ø��� ������ ���� ���        */
	/*    CreateFont() �Լ��� ����Ѵ�                                            */
	/*  : �� �Լ��� �۲� �����Ͱ� LOGFONT ����ü�� �����ϹǷ� ����ϱ� ����       */
	/* -> SetTextColor() : ������ ������ ��ġ ���ؽ�Ʈ�� �ؽ�Ʈ ���� �����Ѵ�     */
	/*  : �⺻�� �ؽ�Ʈ ���� �����̴�                                             */
	/*  : �� �Լ��� �ؽ�Ʈ ��¿� ��� RGB ���� ������ �� �ִ�                  */
	/*  : ���� ��ġ ���ؽ�Ʈ�� �����ǰų� �ٸ� �׽�Ʈ ���� ������ ������ ��ȿ�Ѵ� */
	/* -> SetBkColor() : ������ �����Ѵ�                                        */
	/*  : ������ �ؽ�Ʈ�� �׸� �� ��Ʈ���� �÷��� �ܻ����� ��ȯ�� �� �̿�ǰ�   */
	/*    ��鿡 ���� ������ �ִ� ���鿡 �̿�ȴ�                                 */
	/* -> DeleteObject() : GDI ��ü�� �����                                      */
	/*  : GetStockObject() �Լ��� ������ ��ü�� ���ܵȴ�                          */
	/*  : GDI ��ü�� �����ϴ� �Լ��� ����� ��� �ݵ�� ������ ��ü�� ������ �Ѵ� */
	/*  : ������ �ϴ� ��ü�δ� ��, ��Ʈ��, �귯��, ����, �ȷ�Ʈ, ��Ʈ ���̴�      */
	/*  : ���� ��ġ ���ؽ�Ʈ���� ���õ� ��ü�� ���ؼ��� DeleteObject() �Լ���     */
	/*    ����ϸ� �ȵȴ�                                                         */
	/*  : ���� ��ġ ���ؽ�Ʈ�� ���õ� ��ü�� ���� �� ���� ��ü�� �����Ǳ� ����    */
	/*  : ������ NT�� ��� ���� ��ġ ���ؽ�Ʈ���� ���õ� ��ü�� �� �Լ���         */
	/*    ȣ���ϴ� ���� ������� �ʴ´�                                           */
	/*  : ���� ������� ��ü�� �귯���� ��� �귯�ø� ����� ���� ����ߴ�        */
	/*    ��Ʈ���� �� �Լ��� ���� ���� ����                                       */
	/*  : �׷� ��� ���� �� ��ü�� ������ �Ѵ�                                    */
	/* ************************************************************************** */
	dc.SelectObject(pOldPen);
	
	ctrlFont.CreateFont
	(
		min(m_nStepCol-10, m_nStepRow-10),
		0,
		0,
		0,
		m_bBold ? FW_BOLD : FW_NORMAL,
		m_bItalic,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		m_strFaceName
	);

	CFont* pOldFont=dc.SelectObject(&ctrlFont);
	dc.SetTextColor(m_crText);
	dc.SetBkColor(m_crBkg);
	
	for(i=0; i<m_nRows; i++)
	{
		for(j=0; j<m_nCols; j++)
		{
			k = i*m_nCols+j;
			DrawCell(&dc, i, j, mc_BcrColor[k], mc_TcrColor[k], mstr_Out[k]);  /* ���� �����ϴ� �Լ� */
		}
	}

	dc.SelectObject(pOldFont);
	ctrlFont.DeleteObject();
	linePen.DeleteObject();
	textPen.DeleteObject();
	/* ************************************************************************** */
}

BOOL CCharSetCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return CWnd::OnEraseBkgnd(pDC);
}

void CCharSetCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	// In our case this is not needed - yet - so just drop through to
    // the base class
	CWnd::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CCharSetCtrl methods

BOOL CCharSetCtrl::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
	return CWnd::Create(CHARSETCTRL_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

void CCharSetCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}

void CCharSetCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
}

void CCharSetCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);
}

void CCharSetCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CCharSetCtrl::PreTranslateMessage(MSG* pMsg) 
{
	return CWnd::PreTranslateMessage(pMsg);
}

void CCharSetCtrl::DrawCell(CDC* pDC, int nRow, int nCol, const COLORREF crBkColor, const COLORREF crTextColor, CString crText)
{
	CString strOut;
	strOut="0";

	strOut =crText;

	CRect rcHilite(m_Rect.left + nCol*m_nStepCol+1, 
				m_Rect.top + nRow*m_nStepRow+1, 
				m_Rect.left + (nCol+1)*m_nStepCol, 
				m_Rect.top + (nRow+1)*m_nStepRow);

	CRect rcText(m_Rect.left + nCol*m_nStepCol+2, 
				m_Rect.top + nRow*m_nStepRow+2, 
				m_Rect.left + (nCol+1)*m_nStepCol-1, 
				m_Rect.top + (nRow+1)*m_nStepRow-1);
	
	/* ************************************************************************** */
	/* �־��� Į�� ����Ͽ� ���� �����Ѵ�                                       */
	/* -> SetBkMode() : ������ ������ �����Ѵ�                                  */
	/*  : ��� ���� �����찡 �ؽ�Ʈ�� ���� ���� ������ �׸��� ���� ��Ʈ����     */
	/*    �ܻ����� ��ȯ�ϴ� ����� �����Ѵ�                                       */
	/* -> FillSolidRect() : ������ �簢���� �־��� �귯�÷� ä���                */
	/* -> DrawText() : ���ϴ� ��� �������� �ؽ�Ʈ�� �׸���                       */
	/* ************************************************************************** */
	pDC->SetBkMode(TRANSPARENT);
	if (nCol==m_nHiliteCol && nRow==m_nHiliteRow)
	{
		/*
		pDC->SetTextColor(m_crHiliteText);
		pDC->SetBkColor(m_crHiliteBkg);

		pDC->FillSolidRect(rcHilite, m_crHiliteBkg);
		pDC->DrawText(strOut, rcText, DT_CENTER | DT_VCENTER);
		*/
		pDC->SetTextColor(crTextColor);
		pDC->SetBkColor(crBkColor);

		pDC->FillSolidRect(rcHilite, crBkColor);
		pDC->DrawText(strOut, rcText, DT_CENTER | DT_VCENTER);
	}
	else
	{
		/*
		pDC->SetTextColor(m_crText);
		pDC->SetBkColor(m_crBkg);

		pDC->FillSolidRect(rcHilite, m_crBkg);
		pDC->DrawText(strOut, rcText, DT_CENTER | DT_VCENTER);
		*/
		pDC->SetTextColor(crTextColor);
		pDC->SetBkColor(crBkColor);

		pDC->FillSolidRect(rcHilite, crBkColor);
		pDC->DrawText(strOut, rcText, DT_CENTER | DT_VCENTER);
	}
	/* ************************************************************************** */
}

void CCharSetCtrl::DrawCell(CDC* pDC, int nChar)
{
	int nCol=(nChar-m_nStart)%m_nCols;
	int nRow=(int)((nChar-m_nStart)/m_nCols);

	int k = nRow*m_nCols+nCol;
	DrawCell(pDC, nRow, nCol, mc_BcrColor[k], mc_TcrColor[k], mstr_Out[k]);  /* ���� �׸��� �Լ� */
}

void CCharSetCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDblClk(nFlags, point);
}

/* ****************************************************************************** */
/* ���õ� �� ��ġ ���� �Լ�                                                       */
/* ****************************************************************************** */
void CCharSetCtrl::SetSelection(int nRow, int nCol)
{
	int nChar=m_nStart+m_nCols*nRow+nCol;
	SetSelection(nChar);  /* ���õ� �� �׸��� �Լ� */
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* ���õ� �� �׸��� �Լ�                                                          */
/* ****************************************************************************** */
void CCharSetCtrl::SetSelection(int nSelect)
{
	int nOldSelect=m_nSelect;
	m_nSelect=nSelect;

	CClientDC dc (this);
	CFont ctrlFont;
	
	ctrlFont.CreateFont
	(
		min(m_nStepCol, m_nStepRow),
		0,
		0,
		0,
		m_bBold ? FW_BOLD : FW_NORMAL,
		m_bItalic,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		m_strFaceName
	);

	CFont* pOldFont=dc.SelectObject(&ctrlFont);
	
	if (nOldSelect!=-1)
		DrawCell(&dc, nOldSelect);
	if (m_nSelect!=-1)
		DrawCell(&dc, m_nSelect);

	dc.SelectObject(pOldFont);
	ctrlFont.DeleteObject();
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* Ư�� ��Ͽ� ���� Į�� ���� �Լ�                                                */
/* ****************************************************************************** */
void CCharSetCtrl::SetBlock(UINT nBlockNumber, COLORREF BcrColor, COLORREF TcrColor, CString strText)
{
	mc_BcrColor[nBlockNumber] = BcrColor;
	mc_TcrColor[nBlockNumber] = TcrColor;

	mstr_Out[nBlockNumber] = strText;
}
/* ****************************************************************************** */

/* ****************************************************************************** */
/* Ŭ���̾�Ʈ ���� �����ϴ� �Լ�                                                  */
/* ****************************************************************************** */
void CCharSetCtrl::Refresh()
{
	Invalidate();  /* ������ ���� ���� �Լ� */
}
/* ****************************************************************************** */

void CCharSetCtrl::SetRows(int nRows)
{
	m_nRows=nRows;
	Invalidate();
}
void CCharSetCtrl::SetCols(int nCols)
{
	m_nCols=nCols;
	Invalidate();
}

void CCharSetCtrl::SetColorLine(COLORREF crLine)
{
	m_crLine=crLine;
	Invalidate();
}

void CCharSetCtrl::SetColorBkg(COLORREF crBkg)
{
	m_crBkg=crBkg;
	Invalidate();
}

void CCharSetCtrl::SetColorText(COLORREF crText)
{
	m_crText=crText;
	Invalidate();
}

void CCharSetCtrl::SetColorHiliteBkg(COLORREF crHiliteBkg)
{
	m_crHiliteBkg=crHiliteBkg;
	Invalidate();
}

void CCharSetCtrl::SetColorHiliteText(COLORREF crHiliteText)
{
	m_crHiliteText=crHiliteText;
	Invalidate();
}

void CCharSetCtrl::SetFaceName(CString strFaceName)
{
	m_strFaceName=strFaceName;
	Invalidate();
}

void CCharSetCtrl::SetBold(BOOL bBold)
{
	m_bBold=bBold;
	Invalidate();
}

void CCharSetCtrl::SetItalic(BOOL bItalic)
{
	m_bItalic=bItalic;
	Invalidate();
}

void CCharSetCtrl::SetStart(int nStart)
{
	m_nStart=nStart;
	Invalidate();
}

int CCharSetCtrl::GetRows()
{
	return m_nRows;
}

int CCharSetCtrl::GetCols()
{
	return m_nCols;
}

COLORREF CCharSetCtrl::GetColorLine()
{
	return m_crLine;
}

COLORREF CCharSetCtrl::GetColorBkg()
{
	return m_crBkg;
}

COLORREF CCharSetCtrl::GetColorText()
{
	return m_crText;
}

COLORREF CCharSetCtrl::GetColorHiliteBkg()
{
	return m_crHiliteBkg;
}

COLORREF CCharSetCtrl::GetColorHiliteText()
{
	return m_crHiliteText;
}

CString CCharSetCtrl::GetFaceName()
{
	return m_strFaceName;
}

BOOL CCharSetCtrl::GetBold()
{
	return m_bBold;
}

BOOL CCharSetCtrl::GetItalic()
{
	return m_bItalic;
}

int CCharSetCtrl::GetSelection()
{
	return m_nSelect;
}

int CCharSetCtrl::GetStart()
{
	return m_nStart;
}

void CCharSetCtrl::SetText(UINT nBlockNumber, CString strText)
{
	mstr_Out[nBlockNumber] = strText;
	Invalidate();
}

void CCharSetCtrl::SetTextColor(UINT nBlockNumber, COLORREF TcrColor)
{
	mc_TcrColor[nBlockNumber] = TcrColor;
	Invalidate();
}
