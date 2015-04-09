#if !defined(AFX_TEXTWRITEDLG_H__A8E1D5D0_996B_4399_A5B1_A8A209D0E534__INCLUDED_)
#define AFX_TEXTWRITEDLG_H__A8E1D5D0_996B_4399_A5B1_A8A209D0E534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextWriteDlg.h : header file
//
#include "WhiteBoard.h"
#include "TextFontDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CTextWriteDlg dialog

class CTextWriteDlg : public CDialog
{
// Construction
public:
	CTextWriteDlg(CWnd* pParent = NULL);   // standard constructor

	CTextWriteDlg(CWnd* pParent,CString Text,float FontHeight,
		          float FontWide,float Angle1,float Angle2,float FontBetween);

	CWhiteBoard *m_pWhiteBoard; //用来指向调用对话框的目标对象的指针
	BOOL IsOpen();
	BOOL IsVisible();
	void Init(CString Text,float FontHeight,float FontWide,float Angle1,
			  float Angle2,float FontBetween);

	float	m_FontHeight;
	float	m_FontWide;
	float	m_Angle1;
	float	m_Angle2;
	float	m_FontBetween;
// Dialog Data
	//{{AFX_DATA(CTextWriteDlg)
	enum { IDD = IDD_WRITE_TEXT };
	CString	m_Text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextWriteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextWriteDlg)
	afx_msg void OnOktext();
	afx_msg void OnCanceltext();
	afx_msg void OnChangeTextEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// TextFontDlg dialog

class TextFontDlg : public CDialog
{
	// Construction
public:
	TextFontDlg(CWnd* pParent = NULL);   // standard constructor
	TextFontDlg(float FontHeight,float FontWide,float Angle1,float Angle2,float FontBetween,CWnd* pParent = NULL);
	// Dialog Data
	//{{AFX_DATA(TextFontDlg)
	enum { IDD = ID_TEXT_FONT };
	float	m_FontHeight;
	float	m_FontWide;
	float	m_Angle1;
	float	m_Angle2;
	float	m_FontBetween;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TextFontDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(TextFontDlg)
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTWRITEDLG_H__A8E1D5D0_996B_4399_A5B1_A8A209D0E534__INCLUDED_)
