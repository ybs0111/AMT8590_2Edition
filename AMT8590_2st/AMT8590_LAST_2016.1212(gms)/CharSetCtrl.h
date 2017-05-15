#if !defined(_CHARSETCTRL_H__INCLUDED_)
#define _CHARSETCTRL_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCharSetCtrl window

#define CHARSETCTRL_CLASSNAME    _T("MFCCharSetCtrl")  /* Ŭ���� �̸� ���� */

#define BTNST_MAX_COLORS  256	/* ���� ũ�� */

class CCharSetCtrl : public CWnd
{
// Construction
public:
	CCharSetCtrl();

// Attributes
protected:
	int m_nRows;  /* �� ROW ���� ���� ���� */
	int m_nCols;  /* �� COL ���� ���� ���� */

	COLORREF m_crLine;        /* �� ���� Į�� ���� ���� */
	COLORREF m_crBkg;         /* �� ��� Į�� ���� ���� */
	COLORREF m_crText;        /* �ؽ�Ʈ Į�� ���� ���� */
	COLORREF m_crHiliteBkg;   /* ���̶���Ʈ ��� Į�� ���� ���� */
	COLORREF m_crHiliteText;  /* ���̶���Ʈ ��� �ؽ�Ʈ Į�� ���� ���� */

	CRect m_Rect;
	int m_nRangeCol;
	int m_nStepCol;
	int m_nRangeRow;
	int m_nStepRow;

	int m_nHiliteCol;
	int m_nHiliteRow;
	int m_nSelect;
	int m_nStart;

	CString m_strFaceName;  /* ������ ��Ʈ�� ���� ���� */
	BOOL m_bBold;           /* ���� ���� ���� �÷��� */
	BOOL m_bItalic;         /* ���Ÿ� ���� �÷��� */


// Attributes
public:
	COLORREF mc_TcrColor[BTNST_MAX_COLORS];  /* �ؽ�Ʈ Į�� ���� ���� */
	COLORREF mc_BcrColor[BTNST_MAX_COLORS];	 /* �� ��� Į�� ���� ���� */

	CString mstr_Out[BTNST_MAX_COLORS];      /* ����� ���ڿ� ���� ���� */


// Operations
public:
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharSetCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

public:
	void SetBlock(UINT nBlockNumber, COLORREF BcrColor, COLORREF TcrColor, CString strText);  /* Ư�� ��Ͽ� ���� Į�� ���� ���� �Լ� */
	void Refresh();  /* Ŭ���̾�Ʈ ���� �����ϴ� �Լ� */

	void SetRows(int nRows);  /* �� ROW ���� ���� �Լ� */
	void SetCols(int nCols);  /* �� COL ���� ���� �Լ� */

	void SetColorBkg(COLORREF crLine);   /* �� ��� Į�� ���� �Լ� */
	void SetColorLine(COLORREF crBkg);   /* �� �׵θ� ���� Į�� ���� �Լ� */
	void SetColorText(COLORREF crText);  /* ���� ����� �ؽ�Ʈ Į�� ���� �Լ� */
	void SetColorHiliteBkg(COLORREF crHiliteBkg);    /* ���̶���Ʈ �� ��� Į�� ���� �Լ� */
	void SetColorHiliteText(COLORREF crHiliteText);  /* ���̶���Ʈ �ؽ�Ʈ Į�� ���� �Լ� */

	void SetFaceName(CString strFaceName);  /* ����� ��Ʈ�� ���� �Լ� */
	void SetBold(BOOL bBold);               /* ���� ���� �ɼ� ���� �Լ� */
	void SetItalic(BOOL bItalic);           /* ���Ÿ� �ɼ� ���� �Լ� */

	void SetSelection(int nSelect);         /* ���õ� �� ��ġ ���� �Լ� */
	void SetSelection(int nRow, int nCol);  /* ���õ� �� �׸��� �Լ� */
	void SetStart(int nStart);

	int GetRows();  /* ���� ROW ���� ���� �Լ� */
	int GetCols();  /* ���� COL ���� ���� �Լ� */

	COLORREF GetColorLine();  /* ���� �׵θ� ���� Į�� ���� �Լ� */
	COLORREF GetColorBkg();   /* �� ��� Į�� ���� �Լ� */
	COLORREF GetColorText();  /* ���� ����� �ؽ�Ʈ Į�� ���� �Լ� */
	COLORREF GetColorHiliteBkg();   /* ���̶���Ʈ �� ��� Į�� ���� �Լ� */
	COLORREF GetColorHiliteText();  /* ���̶���Ʈ �ؽ�Ʈ Į�� ���� �Լ� */

	CString GetFaceName();  /* ���� ������ ��Ʈ�� ���� �Լ� */
	BOOL GetBold();         /* ���� ���� �ɼ� ���� ���� �Լ� */
	BOOL GetItalic();       /* ���Ÿ� �ɼ� ���� ���� �Լ� */
	
	int GetSelection();     /* ���õ� �� ��ġ ���� �Լ� */
	int GetStart();         /* CHAR ���� �� ���� �Լ� */

// Implementation
public:
	void SetTextColor(UINT nBlockNumber, COLORREF TcrColor);
	void SetText(UINT nBlockNumber, CString strText);
	virtual ~CCharSetCtrl();
protected:
    BOOL RegisterWindowClass();

	void DrawCell(CDC* pDC, int nRow, int nCol, const COLORREF crBkColor, const COLORREF crTextColor, CString crText);
	void DrawCell(CDC*, int);
	// Generated message map functions
protected:
	//{{AFX_MSG(CCharSetCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_CHARSETCTRL_H__INCLUDED_)
