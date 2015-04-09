#if !defined(AFX_TEXTEDIT_H__A1AB5819_A5F3_49CD_B294_00C8CECFA642__INCLUDED_)
#define AFX_TEXTEDIT_H__A1AB5819_A5F3_49CD_B294_00C8CECFA642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextEdit window

class CTextEdit : public CEdit
{
// Construction
public:
	CTextEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTEDIT_H__A1AB5819_A5F3_49CD_B294_00C8CECFA642__INCLUDED_)
