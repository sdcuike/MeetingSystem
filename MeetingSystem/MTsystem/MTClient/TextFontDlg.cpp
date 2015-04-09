// TextFontDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "TextFontDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextFontDlg dialog


CTextFontDlg::CTextFontDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextFontDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextFontDlg)
	m_FontBetween = 0.0f;
	m_FontHeight = 0.0f;
	m_FontWide = 0.0f;
	m_Angle1 = 0.0f;
	m_Angle2 = 0.0f;
	//}}AFX_DATA_INIT
}

CTextFontDlg::CTextFontDlg( float FontHeight,float FontWide,float Angle1,float Angle2, float FontBetween,CWnd* pParent /*= NULL*/ )
     : CDialog(CTextFontDlg::IDD, pParent)
{
	m_FontHeight = FontHeight;
	m_FontWide = FontWide;
	m_Angle1 = Angle1;
	m_Angle2 = Angle2;
	m_FontBetween = FontBetween;
}


void CTextFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextFontDlg)
	DDX_Text(pDX, IDC_EDIT_FONTBETWEEN, m_FontBetween);
	DDX_Text(pDX, IDC_EDIT_FONTHIGHT, m_FontHeight);
	DDX_Text(pDX, IDC_EDIT_FONTWIDE, m_FontWide);
	DDX_Text(pDX, IDC_EDIT_TEXTANGEL, m_Angle1);
	DDX_Text(pDX, IDC_EDIT_FONTANGEL, m_Angle2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextFontDlg, CDialog)
	//{{AFX_MSG_MAP(CTextFontDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextFontDlg message handlers
