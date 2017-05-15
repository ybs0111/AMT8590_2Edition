#ifndef _EXDIGITST_H
#define _EXDIGITST_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define ST_MIN_PRECISION	1   /* ����� ������ �ּ� ���� */
#define ST_MAX_PRECISION	10  /* ����� ������ �ִ� ���� */
#define ST_BORDER_SPACE		3   /* �׵θ��� ��Ʈ�� ������ ���� */

/////////////////////////////////////////////////////////////////////////////
// CEXDigitST window

class CEXDigitST : public CStatic
{
// Construction
public:
	CEXDigitST();
	virtual ~CEXDigitST();

    enum {	ST_LEFT			= 0x01, 
			ST_TOP			= 0x02,
			ST_RIGHT		= 0x04,
			ST_BOTTOM		= 0x08};

public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEXDigitST)
	//}}AFX_VIRTUAL

// Operations
public:
	CString GetValueString();
	void SetValue(double dValue, BOOL bRepaint = TRUE);
	BOOL m_b16Flag;  /* ��� ������ ���� ���� ���� */
	
	Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = NULL) ;  /* Ŭ���� ���� ���� �Լ� */
	void SetValue (CString strValue, BOOL bRepaint = TRUE);  /* ���ο� ��� �� ���� �Լ� */
	BOOL SetStyle(UINT nBitmapId, int nPrecision);           /* ��� ���� ���� �Լ� */

	void SetValue(int nValue, BOOL bRepaint = TRUE);         /* ���ο� ��� �� ���� �Լ� */
	int GetValue();         /* ��� �� ���� �Լ� */

	void SetPrecision(int nPrecision, BOOL bResize = TRUE);  /* �Է� ���� �˻� �Լ� */
	int GetPrecision();     /* �Է� ���� ���� �Լ� */

	void SetResize(DWORD dwResize, BOOL bResize = TRUE);     /* ��Ʈ�� ���� �Լ� */
	DWORD GetResize();      /* ��Ʈ�� ũ�� ���� �Լ� */

	void SetZeroPadding(BOOL bPad = FALSE, BOOL bRepaint = TRUE);  /* �е� ��Ÿ�� ���� �Լ� */
	BOOL GetZeroPadding();  /* �е� ��Ÿ�� ���� �Լ� */

	void Inc(BOOL bRepaint = TRUE);  /* ��� ������ 1 ���� �Լ� */
	void Dec(BOOL bRepaint = TRUE);  /* ��� ������ 1 ���� �Լ� */

	static const char* GetVersionC();  /* Ŭ���� ���� ���� �Լ� */
	static const short GetVersionI();  /* Ŭ���� ���� ���� �Լ� */

protected:
	//{{AFX_MSG(CEXDigitST)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void Resize();  /* ��Ʈ�� �� ���� �Լ� */
	void PrepareString(char* szDest);  /* ��� ���ڿ� ���� �Լ� */
	void DrawDigits(CDC* pDC);         /* ������ ī���� ��� �Լ� */

	CBitmap* m_pbmDigit;  /* ��Ʈ�� ���� ���� */
	int m_nWidth;   /* ��Ʈ�� �� ���� ���� */
	int m_nHeight;  /* ��Ʈ�� ���� ���� ���� */

	int m_nPrecision;    /* ����� ��Ʈ�� ���� ���� ���� */
	int m_nValue;        /* ��� ������ ���� ���� */
	CString m_strValue;  /* ��� ���ڿ� ���� ���� */

	BOOL m_bZeroPadding;  /* �е� �÷��� */
	DWORD m_dwResize;     /* ��Ʈ�� ���� �ɼ� ���� ���� */
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
