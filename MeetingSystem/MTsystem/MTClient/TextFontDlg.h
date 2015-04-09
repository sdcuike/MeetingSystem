#if !defined(AFX_TEXTFONTDLG_H__82362470_BDC8_457E_A070_D2C39DC3DA51__INCLUDED_)
#define AFX_TEXTFONTDLG_H__82362470_BDC8_457E_A070_D2C39DC3DA51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextFontDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextFontDlg dialog

class CTextFontDlg : public CDialog
{
// Construction
public:
	CTextFontDlg(CWnd* pParent = NULL);   // standard constructor

	CTextFontDlg(float FontHeight,float FontWide,float Angle1,float Angle2,
		         float FontBetween,CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CTextFontDlg)
	enum { IDD = ID_TEXT_FONT };
	float	m_FontBetween;
	float	m_FontHeight;
	float	m_FontWide;
	float	m_Angle1;
	float	m_Angle2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextFontDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextFontDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTFONTDLG_H__82362470_BDC8_457E_A070_D2C39DC3DA51__INCLUDED_)
