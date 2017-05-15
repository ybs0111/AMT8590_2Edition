// APartShortkey.h: interface for the APartShortkey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APARTSHORTKEY_H__1226ACE3_4FC8_40CC_95EF_875120FA789B__INCLUDED_)
#define AFX_APARTSHORTKEY_H__1226ACE3_4FC8_40CC_95EF_875120FA789B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class APartShortkey  
{
public:
	APartShortkey();
	virtual ~APartShortkey();

public:
	void CheckKeyboard( MSG* pMsg );
	bool IsPressed( int iKey ) { return m_bControl[iKey]; }
	void SetPressed( int iKey, bool bVal ) { m_bControl[iKey] = bVal; }

protected:
	bool m_bControl[256];
};

extern APartShortkey	g_ShortKey;

#endif // !defined(AFX_APARTSHORTKEY_H__1226ACE3_4FC8_40CC_95EF_875120FA789B__INCLUDED_)
