// TextWriteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "TextWriteDlg.h"
#include "resource.h"
#include "TextFontDlg.h"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextWriteDlg dialog


CTextWriteDlg::CTextWriteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextWriteDlg::IDD, pParent)
{

	m_FontHeight = 20;
	m_FontWide = 8;
	m_Angle1 = 0;
	m_Angle2 = 0;
	m_FontBetween = 1;

	//{{AFX_DATA_INIT(CTextWriteDlg)
	m_Text = _T("");
	//}}AFX_DATA_INIT
}

CTextWriteDlg::CTextWriteDlg( CWnd* pParent,CString Text,
							 float FontHeight,float FontWide,float Angle1,
							 float Angle2,float FontBetween )
	: CDialog(CTextWriteDlg::IDD, pParent)
{
	m_pWhiteBoard=(CWhiteBoard*)pParent; //记录传入的指针
	m_Text=Text;                         //标注文本的内容

	m_FontHeight = FontHeight;
	m_FontWide = FontWide;
	m_Angle1 = Angle1;
	m_Angle2 = Angle2;
	m_FontBetween = FontBetween;
}


void CTextWriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextWriteDlg)
	DDX_Text(pDX, IDC_TEXT_EDIT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextWriteDlg, CDialog)
	//{{AFX_MSG_MAP(CTextWriteDlg)
	ON_BN_CLICKED(IDOKTEXT, OnOktext)
	ON_BN_CLICKED(IDCANCELTEXT, OnCanceltext)
	ON_EN_CHANGE(IDC_TEXT_EDIT, OnChangeTextEdit)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextWriteDlg message handlers

void CTextWriteDlg::OnOktext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pWhiteBoard->SendMessage(WM_COMMAND,ID_TEXT_ONOK);
	CDialog::OnOK();
}

void CTextWriteDlg::OnCanceltext() 
{
	// TODO: Add your control notification handler code here
	m_pWhiteBoard->SendMessage(WM_COMMAND,ID_TEXT_ONCANCEL);
	CDialog::OnCancel();
}

void CTextWriteDlg::OnChangeTextEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	UpdateData(TRUE); //将控制（编辑框IDC_TEXT_EDIT)中的内容传递到映射变量
	m_pWhiteBoard->SendMessage(WM_COMMAND,ID_TEXT_MESSAGE);
}

BOOL CTextWriteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CEdit *pedit=(CEdit*)GetDlgItem(IDC_TEXT_EDIT);
	pedit->SetFocus();  //进入对话框时，将输入焦点设置在编辑框内
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTextWriteDlg::IsOpen()
{
	return(m_hWnd?TRUE:FALSE);
}

BOOL CTextWriteDlg::IsVisible()
{
	if (!IsOpen())
	{
		return FALSE;
	}

	WINDOWPLACEMENT scrn;
	GetWindowPlacement(&scrn);
	if (scrn.showCmd==SW_SHOW)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CTextWriteDlg::Init( CString Text,float FontHeight,float FontWide,float Angle1,float Angle2,float FontBetween )
{
	m_Text=Text;
	m_FontHeight = FontHeight;
	m_FontWide = FontWide;
	m_Angle1 = Angle1;
	m_Angle2 = Angle2;
	m_FontBetween = FontBetween;
}

void CTextWriteDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	CTextFontDlg pDg1(m_FontHeight,m_FontWide,m_Angle1,m_Angle2,m_FontBetween);
	if(pDg1.DoModal()==IDOK)
	{
		m_FontHeight=pDg1.m_FontHeight;
		m_FontWide=pDg1.m_FontWide;
		m_Angle1=pDg1.m_Angle1;
		m_Angle2=pDg1.m_Angle2;
		m_FontBetween=pDg1.m_FontBetween;
		UpdateData();		
		m_pWhiteBoard->SendMessage(WM_COMMAND,ID_TEXT_MESSAGE);
	}
}



