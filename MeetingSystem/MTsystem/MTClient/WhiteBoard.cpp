// WhiteBoard.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "WhiteBoard.h"
#include "MainFrm.h"
#include "ChatClientDoc.h"
#include "ChatClientView.h"
#include "TextWriteDlg.h"
#include "Message.h"
#include <afxcmn.h>
#include <cmath>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoard dialog

static UINT indicators[]=
{
	ID_INDICATOR_DRAWTYPE,//��ͼ����ָʾ��
	ID_INDICATOR_CAPS,//��ʾCaps Lock��״̬
    ID_INDICATOR_NUM,//��ʾNum Lock ��״̬
};


CWhiteBoard::CWhiteBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CWhiteBoard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWhiteBoard)
	//}}AFX_DATA_INIT
	m_pColor=1;  //���ñ�ɫ
	m_brColor=1; //�������ɫ
	m_bColor=0; //��ǰ��ɫ�����
	m_LineType=0; //��������
	m_LineWide=1; //�����߿�

	m_Layer=1; //ѡ��ǰͼ��

	PointXyz=new PontStruct[3000]; //��̬�洢����ֱ�߶���Ľṹ����
	m_DrwaCurrent=100;

	pTextDlg=NULL;
	//�������ó�ʼ�����С
	m_FontHeight=20;
	m_FontWide=10;
	m_TextAngle=0;
	m_FontAngle=0;
	m_FontBetween=1;
	m_TextString.Empty();
	m_Text1=new CText();  //����һ����ע�ı�����


    m_clorDraw=RGB(233,125,244); //��ǰ��ͼ�������ɫ,�����ʻ�ˢ����ɫ
	m_nPenWide=1; //���ʴ�ϸ
	m_nBrushStye=HS_CROSS; //��ˢ������

}


void CWhiteBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhiteBoard)
	DDX_Control(pDX, IDC_RESHOWCOLOR, m_displaySCLOR);
	DDX_Control(pDX, IDC_BTNWCOLOSSEL, m_colorDraw);
	DDX_Control(pDX, IDC_EDIT_WHITEBOARCOLOSNOWSEL, m_editclor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWhiteBoard, CDialog)
	//{{AFX_MSG_MAP(CWhiteBoard)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTNWCOLOSSEL, OnBtnwcolossel)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_PLINE, OnDrawPline)
	ON_COMMAND(ID_DRAW_RGN, OnDrawRgn)
	ON_COMMAND(ID_DRAW_ARC, OnDrawArc)
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(ID_DRAW_CIRCLEL, OnDrawCirclel)
	ON_COMMAND(ID_DRAW_TEXT, OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ARC, OnUpdateDrawArc)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLEL, OnUpdateDrawCirclel)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PLINE, OnUpdateDrawPline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RGN, OnUpdateDrawRgn)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, OnUpdateDrawText)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_TEXT_MESSAGE,DrawText)
	ON_COMMAND(ID_TEXT_ONOK,DrawTextOnOk)
	ON_COMMAND(ID_TEXT_ONCANCEL,DrawTextOnCancel)
	ON_COMMAND(ID_DRAW_CRCLELINE, OnDrawCrcleline)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_COMMAND(ID_LINEWIDE_ONE, OnLinewideOne)
	ON_COMMAND(ID_LINEWIDE_TWO, OnLinewideTwo)
	ON_COMMAND(ID_LINEWIDE_THREE, OnLinewideThree)
	ON_COMMAND(ID_HS_VERTICAL, OnHsVertical)
	ON_COMMAND(ID_HS_SOLID, OnHsSolid)
	ON_COMMAND(ID_HS_HORZIONTAL, OnHsHorziontal)
	ON_COMMAND(ID_HS_FDIAGONAL, OnHsFdiagonal)
	ON_COMMAND(ID_HS_DIAGCROSS, OnHsDiagcross)
	ON_COMMAND(ID_HS_CROSS, OnHsCross)
	ON_COMMAND(ID_HS_BDIAGONAL, OnHsBdiagonal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhiteBoard message handlers

void CWhiteBoard::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	//�õ�ָ��ǰ�ĵ���ָ��
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                  AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	
	CClientDC dc(this);
	float r;
	float xx1,yy1,xx2,yy2;
	int x1,x2,y1,y2,Lb,Index,id_only;
	BOOL m_Fill;

	if (m_DrwaCurrent==1)   //������ڻ���ֱ��
	{
		if (PushNumb==0)   //����ǵ�һ�ΰ���������
		{
			PushNumb++;    //�����������Ĵ�����1��
			mPointOrign=point;  //ֱ�ߵ������ڰ��е�
			mPointOld=point;    //��¼���ΰ��е�
			SetCapture();      //��׽�������
		}
		else if (PushNumb==1)      //�ڶ��ΰ���������(������ֱ�ߵĽ�����)
		{
			
			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
			dc.MoveTo(mPointOrign);
			dc.LineTo(point);
			dc.SelectObject(pOldPen);
			pen.DeleteObject();
			PushNumb=0;   //���������´���Ϊ0�����½���ֱ�ߵĻ���
			ReleaseCapture();  //�ͷŲ�׽�Ĺ��

			pDoc->msg.type=30;
			pDoc->msg.m_DrawCurrent=1;
			pDoc->msg.m_nPenWide=m_nPenWide;
			pDoc->msg.color=m_clorDraw;
			pDoc->msg.m_PointNumber=2;
			pDoc->msg.m_HvaePN[0]=mPointOrign;
			pDoc->msg.m_HvaePN[1]=point;
			pDoc->SendMsg();

			mPointOrign=point;
		}
	}
	else if (m_DrwaCurrent==2 || m_DrwaCurrent==3) //���ڽ��н�����������ֱ�߻���������
	{
		if (PushNumb==0)     //����ǵ�һ�ΰ���������
		{
			SetCapture();   //��׽���
			mPointOrign=point;//ԭ�������갴�е�
			mPointOld=point; //����갴�е���Ϊ����ƶ�ʱ����һ����
		}
		else          //�������ϰ���������ʱ
		{
			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
			dc.MoveTo(mPointOrign);
			dc.LineTo(point);
			dc.SelectObject(pOldPen);
			pen.DeleteObject();

			pDoc->msg.type=30;                  //��Ϣ����Ϊ���Ӱװ�Ĵ�����Ϣ
			pDoc->msg.m_DrawCurrent=1;          //��ǰ���ڻ��Ƶ�����
			pDoc->msg.m_nPenWide=m_nPenWide;    //���ʿ��
			pDoc->msg.color=m_clorDraw;         //������ɫ
			pDoc->msg.m_PointNumber=2;          //����ĵ�ĸ���
			pDoc->msg.m_HvaePN[0]=mPointOrign;  //���
			pDoc->msg.m_HvaePN[1]=point;        //�յ�
			pDoc->SendMsg();
	

			mPointOrign=mPointOld; //����һ������Ϊԭ��
			mPointOld=point;   //����갴�е���Ϊ����ƶ�ʱ����һ����
		}
		PushNumb++;   //��¼�����������Ĵ���
	}
	else if (m_DrwaCurrent==4 || m_DrwaCurrent==5)//������ڻ���Բ��Բ������
	{
		if (PushNumb==0)         //����ǵ�һ�ΰ���������
		{
			mPointOrign=point;  //ԭ����ڰ��е�
			mPointOld=point;   //��һ����Ҳ���ڰ��е�
			PushNumb++;			//�����������Ĵ�����1
			SetCapture();      //��׽���
		}
		else             //����������ϰ���������
		{
			
			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2) +
				pow((float)(mPointOrign.y-point.y),2)); //����õ�Բ�İ뾶

			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
				

			if (m_DrwaCurrent==4)  //������ڻ���Բ
			{
				m_Fill=FALSE;
				dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
			}
			else         //������ڻ���Բ������
			{
				m_Fill=TRUE;
				CBrush brush;
				CBrush *pOldBrush;
				if (m_nBrushStye ==7)
				{
					brush.CreateSolidBrush(m_clorDraw);
				}
				else
				{
					brush.CreateHatchBrush(m_nBrushStye,m_clorDraw);
				}
				
				pOldBrush=dc.SelectObject(&brush);
				dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
				dc.SelectObject(pOldBrush);
				brush.DeleteObject();

			}

			dc.SelectObject(pOldPen);
			pen.DeleteObject();
			PushNumb=0;      //��갴������Ϊ0�����½���Բ�Ľ������Ʋ���
			ReleaseCapture(); //�ͷŲ�׽�����

			pDoc->msg.type=30;
			pDoc->msg.m_DrawCurrent=4;
			pDoc->msg.m_nBrushStye=m_nBrushStye;
			pDoc->msg.b_Fill=m_Fill;
			pDoc->msg.m_nPenWide=m_nPenWide;
			pDoc->msg.color=m_clorDraw;
			pDoc->msg.m_PointNumber=2;
			pDoc->msg.m_HvaePN[0]=mPointOrign;
			pDoc->msg.m_HvaePN[1]=point;
			pDoc->SendMsg();
		}
	}
	else if (m_DrwaCurrent==6)  //���ڻ���Բ��
	{
		if(PushNumb==0)   // ��һ�ΰ���������
		{
			SetCapture();
			DrawArcYes=0;
			mPointOrign1=point; //��¼Բ����һ��
			PushNumb++;
		}
		else if (PushNumb==1)  //�ڶ��ΰ���������
		{
			mPointOrign=point; //��¼��Բ���ĵڶ���
			PushNumb++;
		}
		else			//�����ΰ���������
		{
			jsarc(mPointOrign1,mPointOrign,point,&m_CircleX,&m_CircleY,&m_CircleR,
				  &m_Angle1,&m_Angle2);   //����Բ���ļ���Ҫ��
			id_only=pDoc->GetGraphID(4); //�õ�Ҫ����Բ����Ψһʶ���
			pDoc->AddArc(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,id_only,
				m_CircleX,m_CircleY,m_CircleR,m_Fill,m_Angle1,m_Angle2)
				->Draw(&dc,0,0,m_brColor);   //����һ��Բ�����»���Բ��
			PushNumb=0;		// ��������������Ϊ0�����½���Բ���Ļ���
			ReleaseCapture();  //�ͷŲ�׽�����
		}
	}
	else if (m_DrwaCurrent==7)  //���ڽ��б�ע�ı��Ľ������Ʋ���
	{
		//�õ����е��ʵ������
		m_TextX=point.x;
		m_TextY=point.y;

		if (!pTextDlg)
		{
			//�����ע�ı��Ի�����󲻴��ڣ������Ի������
			pTextDlg=new CTextWriteDlg(this,m_TextString,m_FontHeight,m_FontWide,
				m_TextAngle,m_FontAngle,m_FontBetween); //������ע�ı��Ի������

			ASSERT(pTextDlg);
		}
		if (!(pTextDlg->IsOpen()))  //����Ի��򴰿�û�н����������Ի��򴰿�
		{
			pTextDlg->Create(IDD_WRITE_TEXT,this);
		}
		if (!(pTextDlg->IsVisible()))  //����Ի��򴰿ڵ�ǰ���ɼ�
		{
			pTextDlg->ShowWindow(SW_SHOW);  //ʹ��ע�ı��Ի���ɼ�
		}
	}
	else if (m_DrwaCurrent==8 )   //���ڻ�������������״
	{  
		mPointOrign=point;  //ֱ�ߵ������ڰ��е�
		mPointOld=mPointOrign;
		SetCapture();  //��׽�������
		PushNumb++;
		
		
	}
	

}

void CWhiteBoard::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
    
	CDialog::OnLButtonUp(nFlags, point);
}



BOOL CWhiteBoard::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
    if ( !CDialog::PreCreateWindow(cs))
    {
		return FALSE;
    }

	cs.style&=~WS_MAXIMIZEBOX;
	cs.style&=~WS_SIZEBOX;
	return  TRUE;
}

BOOL CWhiteBoard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	// Create the toolbar. To understand the meaning of the styles used, you 
    // can take a look at the MSDN for the Create function of the CToolBar class.

	m_wndToolBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | 
						CBRS_FLYBY | CBRS_BORDER_BOTTOM  );


	m_wndStyleSel.Create(this,WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_TOOLTIPS | 
						CBRS_FLYBY | CBRS_BORDER_BOTTOM );
	// I have assumed that you have named your m_wndToolBar resource as IDR_TOOLBARWHITEBOARD.
	// If you have given it a different name, change the line below to accomodate 
	// that by changing the parameter for the LoadToolBar function.
	  
	m_wndToolBar.LoadToolBar(IDR_TOOLBAROFWHITEBOARD);

	m_wndStyleSel.LoadToolBar(IDR_WHSTYLE);

	CRect retClientStart;
	CRect retClientNow;

	GetClientRect(retClientStart);

	// To reposition and resize the control bar
    
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, retClientNow);
	CPoint ptoffset(retClientNow.left-retClientStart.left, retClientNow.top-retClientStart.top);

	CRect rcChild;
	CWnd* pwndChild=GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptoffset);
		pwndChild->MoveWindow(rcChild,FALSE);
		pwndChild=pwndChild->GetNextWindow();
	}

	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right+=retClientStart.Width()-retClientNow.Width();
	rcWindow.bottom+=retClientStart.Height()-retClientNow.Height();
	MoveWindow(rcWindow,FALSE);

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
		
	//����״̬��
	m_wndStatusBar.CreateEx(this, SBT_TOOLTIPS, WS_CHILD|WS_VISIBLE|CBRS_BOTTOM, AFX_IDW_STATUS_BAR);
    
	// Set the indicators namely caps and nums lock status
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	CRect rect;
	GetClientRect(&rect);
	m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_DRAWTYPE,SBPS_NORMAL, 2*rect.Width()/3);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_CAPS,SBPS_POPOUT,rect.Width()/10);
//  m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_NUM,SBPS_NORMAL,rect.Width()/2);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	m_wndStatusBar.GetStatusBarCtrl().SetBkColor(RGB(180,180,180));


	m_colorDraw.SetBuddy(m_editclor);//�󶨵��༭��
	 
	m_displaySCLOR.SetBackgroundColor(FALSE,RGB(45,234,123));



	const CWnd * pWndInsertAfter;
	pWndInsertAfter = &wndTopMost;
    SetWindowPos(pWndInsertAfter,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWhiteBoard::OnBtnwcolossel() 
{
	// TODO: Add your control notification handler code here
	m_clorDraw=m_colorDraw.GetColor();
	m_displaySCLOR.SetBackgroundColor(FALSE,m_clorDraw);
	

}



void CWhiteBoard::OnDrawLine() 
{
	// TODO: Add your command handler code here
	PushNumb=0;		//��ʶ������´���
	m_DrwaCurrent=1; //��ʶ����ֱ�߻��Ʋ���
	m_wndStatusBar.SetPaneText(0,"ֱ��");
}

void CWhiteBoard::OnDrawPline() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=2;//��ʶ���ж���λ��Ʋ���
	m_wndStatusBar.SetPaneText(0,"�����");
}

void CWhiteBoard::OnDrawRgn() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=3;//��ʶ���ж�����������
	m_wndStatusBar.SetPaneText(0,"���������");
}

void CWhiteBoard::OnDrawArc() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=6;//��ʶ����Բ�����Ʋ���
	m_wndStatusBar.SetPaneText(0,"Բ��");
}

void CWhiteBoard::OnDrawCircle() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=4;//��ʶ����Բ���ƵĲ���
	m_wndStatusBar.SetPaneText(0,"Բ");
}

void CWhiteBoard::OnDrawCirclel() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=5;//��ʶ����Բ����Ĳ���
	m_wndStatusBar.SetPaneText(0,"Բ������");

}

void CWhiteBoard::OnDrawText() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //��ʶ������´���
	m_DrwaCurrent=7;//��ʶ�����ı����ƵĲ���
	m_wndStatusBar.SetPaneText(0,"�ı�");
}

BOOL CWhiteBoard::OnToolTipText( UINT, NMHDR* pNMHDR, LRESULT* pResult )
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	// UNICODE��Ϣ
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	//TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFromΪ��������HWND 
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	
	if (nID != 0) //��Ϊ�ָ���
	{
		strTipText.LoadString(nID);
		strTipText = strTipText.Mid(strTipText.Find('\n',0)+1);
		
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		}
		else
		{
			_mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			_wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
		}
		else
		{
			lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#endif
		
		*pResult = 0;
		
		// ʹ��������ʾ������������
		::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,SWP_NOACTIVATE|
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER); 
		return TRUE;
	}
	return TRUE;

}

void CWhiteBoard::OnUpdateDrawArc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWhiteBoard::OnUpdateDrawCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWhiteBoard::OnUpdateDrawCirclel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWhiteBoard::OnUpdateDrawLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrwaCurrent==1);
    
}

void CWhiteBoard::OnUpdateDrawPline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrwaCurrent==2);
}

void CWhiteBoard::OnUpdateDrawRgn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CWhiteBoard::OnUpdateDrawText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}



void CWhiteBoard::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HCURSOR hcrsor=AfxGetApp()->LoadCursor(IDC_MYCURSOR);
	SetCursor(hcrsor);
   

	//�õ�ָ��ǰ�ĵ���ָ��
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                 AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	CPen pen(0,0,RGB(0,0,0));     //����CPen����
	CPen *pOldPen=dc.SelectObject(&pen); //�ڵ�ǰ��ͼ������ѡ��CPen����.
	dc.SetROP2(R2_NOT);   //ѡ��ɫ�Ļ���ģʽ

	BOOL pb;

	if (m_DrwaCurrent==1 && PushNumb==1) //����ǻ���ֱ�߲����Ѿ�������ֱ�ߵ����
	{
		if (mPointOld!=point) //������������ƶ�������һ���㲻��ͬ������㵽��
		{		              //һ���ƶ����ֱ�߲��������ƴ���㵽�����ƶ����ֱ��
			 dc.MoveTo(mPointOrign);
			 dc.LineTo(mPointOld); //������һ��ֱ��
			 dc.MoveTo(mPointOrign);
			 dc.LineTo(point);  //����ֱ����㵽����ƶ��������
			 mPointOld=point; //����ǰ�����¼Ϊ�´��ƶ���������һ���ƶ���
			
		}
	}
	else if ((m_DrwaCurrent==2||m_DrwaCurrent==3) &&PushNumb>=1) 
		//������ڻ�������ֱ�߻����Σ����Ұ��µ�һ��
	{
		if (mPointOld!=point)  //�����ǰ����ƶ�������һ���ƶ��㲻ͬ�����ϸ����㵽�ϸ�
							//�ƶ�������߲��������ƴ��ϸ��ƶ��㵽��ǰ����ƶ��������
		{
			dc.MoveTo(mPointOrign);
			dc.LineTo(mPointOld); //����ԭ����ֱ��
			dc.MoveTo(mPointOrign); 
			dc.LineTo(point);   //�����ϸ����㵽��ǰ����ƶ����ֱ��
			mPointOld=point;

		}
	}
	else if ((m_DrwaCurrent==4 || m_DrwaCurrent==5) && PushNumb>=1)
		// ������ڻ���Բ��Բ�����򣬲��Ѿ�����Բ�ε�
	{
		
		if (mPointOld!=point) //�����ǰ����ƶ�������һ���ƶ��㲻ͬ��������ԭ���ƶ���
			                  //��Բ���������ƾ�����ǰ���Բ
		{
			if (m_DrwaCurrent==4)  //�������ͨԲ�����ò����״̬
			{
				dc.SelectStockObject(NULL_BRUSH);
			}
			float r;
			r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2) +
			   pow((float)(mPointOrign.y-mPointOld.y),2) ); //�õ���һ��Բ�İ뾶
			dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,
				       mPointOrign.x+r,mPointOrign.y+r); //�ػ���������һ��Բ

			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2) +
				pow((float)(mPointOrign.y-point.y),2));  //�õ���ǰ�ƶ�������Բ�İ뾶

			dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,
					   mPointOrign.x+r,mPointOrign.y+r); //����һ��������ǰ����ƶ���Բ
			mPointOld=point;  //��¼��ǰ����ƶ�����Ϊ��һ���ƶ�ʱ����һ��
		}

	}
	else if (m_DrwaCurrent==6)  //���ڻ���Բ������
	{
		if (PushNumb==2 && mPointOld!=point)
		{
			//������¶������ҵ�ǰ����ƶ������ϸ��ƶ��㲻ͬ
			if (DrawArcYes>0) //����Ѿ�����ͼ�л�����m_Arc1����洢��Բ��
			{
				m_Arc1.Draw(&dc,1,0,m_brColor); //�ػ��Բ���Բ�� 
			}

			pb=jsarc(mPointOrign1,mPointOrign,point,&m_CircleX,&m_CircleY,&m_CircleR,
				&m_Angle1,&m_Angle2);  //���㾭����ǰ����ƶ����Բ���ļ���Ҫ��
			if (pb)  //����ܼ���ĵ�Բ���ļ���Ҫ�أ���ʼ��	m_Arc1���󲢻������Բ��
			{
				m_Arc1.Init(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,0,
					m_CircleX,m_CircleY,m_CircleR,0,m_Angle1,m_Angle2);
				m_Arc1.Draw(&dc,1,0,m_bColor);
			}
			
			DrawArcYes=pb; //�ж�����Ƿ������m_Arc1 ����
			mPointOld=point;
		}
	}
	else if (m_DrwaCurrent==8 && PushNumb>0)   //���ڻ�������������
	{

		dc.SetROP2(R2_COPYPEN);
		
		CPen pen;
		pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
		CPen *pOldPen=dc.SelectObject(&pen);
		dc.MoveTo(mPointOrign);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		pen.DeleteObject();
				
		pDoc->msg.type=30;
		pDoc->msg.m_DrawCurrent=1;
		pDoc->msg.m_nPenWide=m_nPenWide;
		pDoc->msg.color=m_clorDraw;
		pDoc->msg.m_PointNumber=2;
		pDoc->msg.m_HvaePN[0]=mPointOrign;
		pDoc->msg.m_HvaePN[1]=point;
		pDoc->SendMsg();

		mPointOrign=point;
	
		
		PushNumb++;

	}

}

void CWhiteBoard::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//�õ�ָ��ǰ�ĵ���ָ��
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                 AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	CPen pen(0,0,RGB(0,0,0));     //����CPen����
	CPen *pOldPen=dc.SelectObject(&pen); //�ڵ�ǰ��ͼ������ѡ��CPen����.
	dc.SetROP2(R2_NOT);   //ѡ��ɫ�Ļ���ģʽ
	
	if (m_DrwaCurrent==1 && PushNumb==1) //������ڻ���ֱ�߲����Ѿ�������ֱ�ߵ����
	{
		dc.MoveTo(mPointOrign);
		dc.LineTo(mPointOld);  //������ͼ��Ļ���϶�����Ƥ��

		PushNumb=0;
		ReleaseCapture();  //�ͷŲ�׽�����
	}
	else if ((m_DrwaCurrent==2 || m_DrwaCurrent==3) && PushNumb>0)
	{
		//���ڻ�������ֱ�߻�������������������Ѿ����¶���һ������������

		//�������һ���϶�����Ƥ��
		dc.MoveTo(mPointOrign);
		dc.LineTo(mPointOld);
		if (m_DrwaCurrent==2 && PushNumb>1) //������ڻ�������ֱ�ߣ����Ҷ���������2
		{
		   ReleaseCapture();
		}
		PushNumb=0;  //�����������Ĵ���Ϊ0
		ReleaseCapture(); //�ͷŲ�׽�����
	}
	else if ( (m_DrwaCurrent==4 || m_DrwaCurrent==5) && PushNumb>0  )
		//������ڻ���Բ��Բ�����򣬲����Ѿ����µ�һ��
	{
		if (m_DrwaCurrent==4)  //�����Բ�����ò����״̬
		{
			dc.SelectStockObject(NULL_BRUSH);
		}
		float r;
		r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2) +
			   pow((float)(mPointOrign.y-mPointOld.y),2) ); //�õ���һ��Բ�İ뾶
		//�ػ�������������һ�����Բ
		dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
		ReleaseCapture(); //�ͷŲ�׽�����
		PushNumb=0;       //�����������Ĵ���Ϊ0

	}
	else if (m_DrwaCurrent==6 && PushNumb>0)  //���ڻ���Բ������
	{
		if (PushNumb==2)  //�Ѿ����������㣬�����϶�Բ��
		{
			m_Arc1.Draw(&dc,1,0,m_bColor); //�����϶���Բ��
		}
		PushNumb=0;
		ReleaseCapture();  //�ͷŲ�׽�����
		
	}
	else if (m_DrwaCurrent==8 && PushNumb >0)
	{
	
		ReleaseCapture();
	
		PushNumb=0;

	}

	dc.SelectObject(pOldPen);  //�ָ�ԭ���Ļ���
}

CWhiteBoard::~CWhiteBoard()
{
	delete PointXyz;

	delete m_Text1;
}

BOOL CWhiteBoard::jsarc( CPoint p1,CPoint p2,CPoint p3,float *CircleX,float *CircleY, float *CircleR,float *Angle1, float *Angle2 )
{
	float an1,an2,an3,k1,k2;
	float x1,y1,x2,y2,x3,y3,xx1,xx2,yy1,yy2,xx,yy,rr;
	//������������긳���������
	x1=(float)p1.x;
	y1=(float)p1.y;
	x2=(float)p2.x;
	y2=(float)p2.y;
	x3=(float)p3.x;
	y3=(float)p3.y;

	if (x1==x2 && y1==y2 || x1==x3 && y1==y3 || x2==x3 && y2==y3)
	{
		//������������������ͬ���������ɹ�������FALSE
		return FALSE;
	}

	//�õ�˳���㷽�������ֱ�߶��еĵ�����
	xx1=(x1+x2)/2;
	yy1=(y1+y2)/2;
	xx2=(x2+x3)/2;
	yy2=(y2+y3)/2;

	if (fabs(y2-y1)>0.5)		//�����һ��ֱ�߶εĴ��߲�����ֱ��
	{
		k1=-(x2-x1)/(y2-y1);   //�õ���һ��ֱ�߶δ��ߵ�б��
	}

	if (fabs(y3-y2)>0.5)       //����ڶ���ֱ�߶εĴ��߲�����ֱ��
	{
		k2=-(x3-x2)/(y3-y2);   //�õ��ڶ���ֱ�߶δ��ߵ�б��
	}

	if (k1==k2 && k1==0.0)	
	{
		return 0;
	}

	if (fabs(y2-y1)<0.5)			//	//�����һ��ֱ�߶���ˮƽ�ߣ�����һ��ֱ�߶εĴ�������ֱ��)
	{
		xx=xx1;
		if (fabs(y3-y2)<0.5)       //����ڶ���ֱ�߶�Ҳ��ˮƽ��
		{
			yy=y2+10000;			//����Բ���İ뾶Ϊ10000
			rr=10000;
		}
		else		//����ڶ���ֱ�߶β���ˮƽ�ߣ����ڶ���ֱ�߶εĴ��߲�����ֱ�ߣ�
		{
			yy=yy2+k2*(xx2-xx);	//���Բ�ĵ�������
			rr=yy-y2;
			if (rr<0)
			{
				rr=-rr; //�õ�Բ�İ뾶
			}
		}
	}
	else if (fabs(y2-y3)<0.5)	//����ڶ���ֱ��ʽˮƽ�ߣ�����һ��ֱ�߲���ˮƽ��
	{
		yy=yy1+k1*(xx1-xx);		//���Բ�ĵ�Y����
		rr=yy-y2;
		if (rr<0)
		{
			rr=-rr;    //�õ�Բ�İ뾶
		}
	}
	else			//�������ֱ�߶ζ�����ˮƽ�ߣ�������ֱ�߶εĴ��߶�������ֱ�ߣ�
	{
		if (k1==k2) //�������ֱ�߶�ƽ�У�����������һ��ֱ����)
		{
			//һ�¼ٶ����Բ���İ뾶Ϊ10000�����Բ������
			xx=x2+(float)(10000/sqrt(1+k1*k1));	//Բ�ĺ�����
			yy=y2+(float)(10000/sqrt(1+k1*k1)/(k1*k1)); //Բ��������
			rr=10000;		//Բ�İ뾶
		}
		else	//�������ֱ�߶β�ƽ��
		{
			//�������ֱ�߶εĴ��ߵĽ��㣬��Բ�ĵ�����
			xx=(yy2-yy1+k1*xx1-k2*xx2)/(k1-k2);	//Բ�ĺ�����
			yy=yy1+k1*(xx-xx1);	//Բ��������
			rr=(float)sqrt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1));//Բ�İ뾶

		}
	}


	//��Բ�ĺͰ뾶��ת��ʵ������
	*CircleX=xx;
	*CircleY=yy;
	*CircleR=rr;
	float pi=3.414;


	an1=(float)acos((x1-xx)/rr);	//�õ���һ�����൱��Բ�ĵĻ���
	if (y1-yy >0 )		//
	{
		an1=(float)(pi*2-an1);
	}


	an2=(float)acos((x2-xx)/rr);	//�õ��ڶ����������Բ�ĵĻ���
	if (y2-yy >0)
	{
		an2=(float)(pi*2-an2);
	}

	an3=(float)acos((x3-xx)/rr);	//�õ����������൱��Բ�ĵĻ���
	if (y3-yy >0)
	{
		an3=(float)(pi*2-an3);
	}

	if (an2>an1 && an2<an1+pi || an2<an1 && an2+pi<an1)	//���Բ������ʱ�뷽�򻭵�
	{
		*Angle1=an1;	//�õ�Բ������ʼ����
		*Angle2=an3;	//�õ�Բ���Ľ�������
	} 
	else			//���Բ����˳ʱ��
	{
		*Angle1=an3;
		*Angle2=an1;
	}

	return TRUE; //�����ɹ�

}

void CWhiteBoard::DrawText()
{
	CClientDC dc(this);  // ����һ����ͼ����
	//���´ӱ�ע���ֶԻ����еõ��������
	m_TextString=pTextDlg->m_Text;
	m_FontHeight=pTextDlg->m_FontHeight;
	m_FontWide=pTextDlg->m_FontWide;
	m_TextAngle=pTextDlg->m_Angle1;
	m_FontAngle=pTextDlg->m_Angle2;
	m_FontBetween=pTextDlg->m_FontBetween;



}

void CWhiteBoard::DrawTextOnOk()
{
	//�õ�ָ��ǰ�ĵ���ָ��
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this); //����һ����ͼ����
	int TextLong;
	PushNumb=0;
	m_TextString=pTextDlg->m_Text; //�õ���ע�ı�����
	TextLong=m_TextString.GetLength();  //��ע�ı��ַ��ĳ���
	if (TextLong>0)  //����б�ע�ı�
	{
		int id_only=pDoc->GetGraphID(5);  //�õ�Ҫ���ӵı��ע�ı������ʶ���
		pDoc->AddText(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,id_only,
					  m_TextX,m_TextY,m_TextAngle,m_FontAngle,m_FontHeight,
					  m_FontWide,m_FontBetween,0,TextLong,m_TextString)->Draw(&dc,0,0,m_bColor);
		pTextDlg->m_Text.Empty();  //����ַ���m_Text������
		pTextDlg->SendMessage(WM_INITDIALOG);  //������Ϣ���öԻ����OnInitDialog����

	}
}

void CWhiteBoard::DrawTextOnCancel()
{
	pTextDlg->m_Text.Empty();
	pTextDlg->SendMessage(WM_INITDIALOG);
}


void CWhiteBoard::OnDrawCrcleline() 
{
	// TODO: Add your command handler code here
	PushNumb=0;
	m_DrwaCurrent=8;
	m_wndStatusBar.SetPaneText(0,"��������");
}

void CWhiteBoard::Display()
{
	//�õ�ָ��ǰ�ĵ���ָ��
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	m_clorDraw=pDoc->msg.color;
	m_nBrushStye=pDoc->msg.m_nBrushStye;
    m_nPenWide=pDoc->msg.m_nPenWide;
	
	if (pDoc->msg.m_DrawCurrent==1)  //�����ֱ�߻�����ֱ��
	{
		CPen pen;
		
		
		pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
		CPen *pOldPen=dc.SelectObject(&pen);
		CPoint point1=pDoc->msg.m_HvaePN[0];
		CPoint point2=pDoc->msg.m_HvaePN[1];
		dc.MoveTo(point1);
		dc.LineTo(point2);
		dc.SelectObject(pOldPen);
		pen.DeleteObject();
	
		return;
	}

	if (pDoc->msg.m_DrawCurrent==4)     //�����Բ��Բ������
	{
		float r;
		CPoint point1=pDoc->msg.m_HvaePN[0];
		CPoint point2=pDoc->msg.m_HvaePN[1];
		r=(float)sqrt(pow((float)(point1.x-point2.x),2) +
				pow((float)(point1.y-point2.y),2)); 


		CPen pen;
		pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
		CPen *pOldPen=dc.SelectObject(&pen);

		if (! pDoc->msg.b_Fill)
		{
			dc.Ellipse(point1.x-r,point1.y-r,point1.x+r,point1.y+r);
		}
		else
		{
			CBrush brush;
			CBrush *pOldBrush;
			if (m_nBrushStye ==7)
			{
				brush.CreateSolidBrush(m_clorDraw);
			}
			else
			{
				brush.CreateHatchBrush(m_nBrushStye,m_clorDraw);
			}
			
			pOldBrush=dc.SelectObject(&brush);
			dc.Ellipse(point1.x-r,point1.y-r,point1.x+r,point1.y+r);
			dc.SelectObject(pOldBrush);
			brush.DeleteObject();
		}


		 dc.SelectObject(pOldPen);
		 pen.DeleteObject();

		 return;
	}

}

void CWhiteBoard::OnLinewideOne() 
{
	// TODO: Add your command handler code here
	m_nPenWide=2;
}

void CWhiteBoard::OnLinewideTwo() 
{
	// TODO: Add your command handler code here
	m_nPenWide=4;
}

void CWhiteBoard::OnLinewideThree() 
{
	// TODO: Add your command handler code here
	m_nPenWide=6;
}

void CWhiteBoard::OnHsVertical() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_VERTICAL;
}

void CWhiteBoard::OnHsSolid() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=7;
}

void CWhiteBoard::OnHsHorziontal() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_HORIZONTAL;
}

void CWhiteBoard::OnHsFdiagonal() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_FDIAGONAL;
}

void CWhiteBoard::OnHsDiagcross() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_DIAGCROSS;
}

void CWhiteBoard::OnHsCross() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_CROSS;
}

void CWhiteBoard::OnHsBdiagonal() 
{
	// TODO: Add your command handler code here
	m_nBrushStye=HS_BDIAGONAL;
}
