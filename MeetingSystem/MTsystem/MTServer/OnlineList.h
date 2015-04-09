#if !defined(AFX_ONLINELIST_H__43ADC819_ED9A_4789_857F_6615CFC1E029__INCLUDED_)
#define AFX_ONLINELIST_H__43ADC819_ED9A_4789_857F_6615CFC1E029__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnlineList.h : header file
//
#include "StdAfx.h"
#include <afxcmn.h>
/////////////////////////////////////////////////////////////////////////////
// COnlineList window

class COnlineList : public CListCtrl
{
// Construction
public:
	COnlineList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnlineList)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Remove(char* name);
	void AddItem(short i, char* name, char* text);
	virtual ~COnlineList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COnlineList)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONLINELIST_H__43ADC819_ED9A_4789_857F_6615CFC1E029__INCLUDED_)
