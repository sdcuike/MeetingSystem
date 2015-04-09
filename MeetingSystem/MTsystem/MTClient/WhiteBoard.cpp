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
	ID_INDICATOR_DRAWTYPE,//绘图类型指示器
	ID_INDICATOR_CAPS,//显示Caps Lock键状态
    ID_INDICATOR_NUM,//显示Num Lock 键状态
};


CWhiteBoard::CWhiteBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CWhiteBoard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWhiteBoard)
	//}}AFX_DATA_INIT
	m_pColor=1;  //设置笔色
	m_brColor=1; //设置填充色
	m_bColor=0; //当前底色的序号
	m_LineType=0; //设置线型
	m_LineWide=1; //设置线宽

	m_Layer=1; //选择当前图层

	PointXyz=new PontStruct[3000]; //动态存储连续直线顶点的结构数组
	m_DrwaCurrent=100;

	pTextDlg=NULL;
	//以下设置初始字体大小
	m_FontHeight=20;
	m_FontWide=10;
	m_TextAngle=0;
	m_FontAngle=0;
	m_FontBetween=1;
	m_TextString.Empty();
	m_Text1=new CText();  //创建一个标注文本对象


    m_clorDraw=RGB(233,125,244); //当前绘图对象的颜色,即画笔或画刷的颜色
	m_nPenWide=1; //画笔粗细
	m_nBrushStye=HS_CROSS; //画刷的类型

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

	//得到指向当前文档的指针
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                  AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	
	CClientDC dc(this);
	float r;
	float xx1,yy1,xx2,yy2;
	int x1,x2,y1,y2,Lb,Index,id_only;
	BOOL m_Fill;

	if (m_DrwaCurrent==1)   //如果正在绘制直线
	{
		if (PushNumb==0)   //如果是第一次按下鼠标左键
		{
			PushNumb++;    //按下鼠标左键的次数加1次
			mPointOrign=point;  //直线的起点等于按中点
			mPointOld=point;    //记录本次按中点
			SetCapture();      //捕捉鼠标输入
		}
		else if (PushNumb==1)      //第二次按下鼠标左键(即按下直线的结束点)
		{
			
			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
			dc.MoveTo(mPointOrign);
			dc.LineTo(point);
			dc.SelectObject(pOldPen);
			pen.DeleteObject();
			PushNumb=0;   //鼠标左键按下次数为0，重新进行直线的绘制
			ReleaseCapture();  //释放捕捉的光标

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
	else if (m_DrwaCurrent==2 || m_DrwaCurrent==3) //正在进行交互绘制连线直线或多边形区域
	{
		if (PushNumb==0)     //如果是第一次按下左鼠标键
		{
			SetCapture();   //捕捉鼠标
			mPointOrign=point;//原点等于鼠标按中点
			mPointOld=point; //将鼠标按中点作为鼠标移动时的上一个点
		}
		else          //二次以上按下鼠标左键时
		{
			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
			dc.MoveTo(mPointOrign);
			dc.LineTo(point);
			dc.SelectObject(pOldPen);
			pen.DeleteObject();

			pDoc->msg.type=30;                  //消息类型为电子白板的传输消息
			pDoc->msg.m_DrawCurrent=1;          //当前正在绘制的线型
			pDoc->msg.m_nPenWide=m_nPenWide;    //画笔宽度
			pDoc->msg.color=m_clorDraw;         //画笔颜色
			pDoc->msg.m_PointNumber=2;          //传输的点的个数
			pDoc->msg.m_HvaePN[0]=mPointOrign;  //起点
			pDoc->msg.m_HvaePN[1]=point;        //终点
			pDoc->SendMsg();
	

			mPointOrign=mPointOld; //将上一个点设为原点
			mPointOld=point;   //将鼠标按中点作为鼠标移动时的上一个点
		}
		PushNumb++;   //记录按下鼠标左键的次数
	}
	else if (m_DrwaCurrent==4 || m_DrwaCurrent==5)//如果正在绘制圆或圆形区域
	{
		if (PushNumb==0)         //如果是第一次按下鼠标左键
		{
			mPointOrign=point;  //原点等于按中点
			mPointOld=point;   //上一个点也等于按中点
			PushNumb++;			//按下鼠标左键的次数加1
			SetCapture();      //捕捉鼠标
		}
		else             //如果二次以上按下鼠标左键
		{
			
			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2) +
				pow((float)(mPointOrign.y-point.y),2)); //计算得到圆的半径

			CPen pen;
			pen.CreatePen(PS_SOLID,m_nPenWide,m_clorDraw);
			CPen *pOldPen=dc.SelectObject(&pen);
				

			if (m_DrwaCurrent==4)  //如果是在绘制圆
			{
				m_Fill=FALSE;
				dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
			}
			else         //如果是在绘制圆形区域
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
			PushNumb=0;      //鼠标按键次数为0，重新进行圆的交互绘制操作
			ReleaseCapture(); //释放捕捉的鼠标

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
	else if (m_DrwaCurrent==6)  //正在绘制圆弧
	{
		if(PushNumb==0)   // 第一次按下鼠标左键
		{
			SetCapture();
			DrawArcYes=0;
			mPointOrign1=point; //记录圆弧第一点
			PushNumb++;
		}
		else if (PushNumb==1)  //第二次按下鼠标左键
		{
			mPointOrign=point; //记录下圆弧的第二点
			PushNumb++;
		}
		else			//第三次按下鼠标左键
		{
			jsarc(mPointOrign1,mPointOrign,point,&m_CircleX,&m_CircleY,&m_CircleR,
				  &m_Angle1,&m_Angle2);   //计算圆弧的几何要素
			id_only=pDoc->GetGraphID(4); //得到要增加圆弧的唯一识别号
			pDoc->AddArc(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,id_only,
				m_CircleX,m_CircleY,m_CircleR,m_Fill,m_Angle1,m_Angle2)
				->Draw(&dc,0,0,m_brColor);   //增加一个圆并重新绘制圆弧
			PushNumb=0;		// 按下鼠标左键次数为0，重新进行圆弧的绘制
			ReleaseCapture();  //释放捕捉的鼠标
		}
	}
	else if (m_DrwaCurrent==7)  //正在进行标注文本的交互绘制操作
	{
		//得到按中点的实际坐标
		m_TextX=point.x;
		m_TextY=point.y;

		if (!pTextDlg)
		{
			//如果标注文本对话框对象不存在，创建对话框对象
			pTextDlg=new CTextWriteDlg(this,m_TextString,m_FontHeight,m_FontWide,
				m_TextAngle,m_FontAngle,m_FontBetween); //创建标注文本对话框对象

			ASSERT(pTextDlg);
		}
		if (!(pTextDlg->IsOpen()))  //如果对话框窗口没有建立，建立对话框窗口
		{
			pTextDlg->Create(IDD_WRITE_TEXT,this);
		}
		if (!(pTextDlg->IsVisible()))  //如果对话框窗口当前不可见
		{
			pTextDlg->ShowWindow(SW_SHOW);  //使标注文本对话框可见
		}
	}
	else if (m_DrwaCurrent==8 )   //正在绘制任意曲边形状
	{  
		mPointOrign=point;  //直线的起点等于按中点
		mPointOld=mPointOrign;
		SetCapture();  //捕捉鼠标输入
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
		
	//创建状态栏
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


	m_colorDraw.SetBuddy(m_editclor);//绑定到编辑框
	 
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
	PushNumb=0;		//标识左键按下次数
	m_DrwaCurrent=1; //标识进行直线绘制操作
	m_wndStatusBar.SetPaneText(0,"直线");
}

void CWhiteBoard::OnDrawPline() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=2;//标识进行多边形绘制操作
	m_wndStatusBar.SetPaneText(0,"多边形");
}

void CWhiteBoard::OnDrawRgn() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=3;//标识进行多边形区域操作
	m_wndStatusBar.SetPaneText(0,"多边形区域");
}

void CWhiteBoard::OnDrawArc() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=6;//标识进行圆弧绘制操作
	m_wndStatusBar.SetPaneText(0,"圆弧");
}

void CWhiteBoard::OnDrawCircle() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=4;//标识进行圆绘制的操作
	m_wndStatusBar.SetPaneText(0,"圆");
}

void CWhiteBoard::OnDrawCirclel() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=5;//标识进行圆区域的操作
	m_wndStatusBar.SetPaneText(0,"圆形区域");

}

void CWhiteBoard::OnDrawText() 
{
	// TODO: Add your command handler code here
	PushNumb=0;    //标识左键按下次数
	m_DrwaCurrent=7;//标识进行文本绘制的操作
	m_wndStatusBar.SetPaneText(0,"文本");
}

BOOL CWhiteBoard::OnToolTipText( UINT, NMHDR* pNMHDR, LRESULT* pResult )
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	// UNICODE消息
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	//TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom为工具条的HWND 
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	
	if (nID != 0) //不为分隔符
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
		
		// 使工具条提示窗口在最上面
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
   

	//得到指向当前文档的指针
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                 AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	CPen pen(0,0,RGB(0,0,0));     //创建CPen对象
	CPen *pOldPen=dc.SelectObject(&pen); //在当前绘图对象中选择CPen对象.
	dc.SetROP2(R2_NOT);   //选择反色的绘制模式

	BOOL pb;

	if (m_DrwaCurrent==1 && PushNumb==1) //如果是绘制直线并且已经按下了直线的起点
	{
		if (mPointOld!=point) //如果鼠标的现在移动点于上一个点不相同，将起点到上
		{		              //一个移动点的直线擦除，绘制从起点到现在移动点的直线
			 dc.MoveTo(mPointOrign);
			 dc.LineTo(mPointOld); //擦除上一条直线
			 dc.MoveTo(mPointOrign);
			 dc.LineTo(point);  //绘制直线起点到鼠标移动点的连线
			 mPointOld=point; //将当前鼠标点记录为下次移动操作的上一个移动点
			
		}
	}
	else if ((m_DrwaCurrent==2||m_DrwaCurrent==3) &&PushNumb>=1) 
		//如果正在绘制连线直线或多边形，并且按下第一点
	{
		if (mPointOld!=point)  //如果当前鼠标移动点与上一个移动点不同，将上个顶点到上个
							//移动点的连线擦除，绘制从上个移动点到当前鼠标移动点的连线
		{
			dc.MoveTo(mPointOrign);
			dc.LineTo(mPointOld); //擦除原来的直线
			dc.MoveTo(mPointOrign); 
			dc.LineTo(point);   //绘制上个顶点到当前鼠标移动点的直线
			mPointOld=point;

		}
	}
	else if ((m_DrwaCurrent==4 || m_DrwaCurrent==5) && PushNumb>=1)
		// 如果正在绘制圆或圆形区域，并已经按下圆形点
	{
		
		if (mPointOld!=point) //如果当前鼠标移动点与上一个移动点不同，将经过原来移动点
			                  //的圆擦掉，绘制经过当前点的圆
		{
			if (m_DrwaCurrent==4)  //如果是普通圆，设置不填充状态
			{
				dc.SelectStockObject(NULL_BRUSH);
			}
			float r;
			r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2) +
			   pow((float)(mPointOrign.y-mPointOld.y),2) ); //得到上一个圆的半径
			dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,
				       mPointOrign.x+r,mPointOrign.y+r); //重画而擦除上一个圆

			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2) +
				pow((float)(mPointOrign.y-point.y),2));  //得到当前移动点所在圆的半径

			dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,
					   mPointOrign.x+r,mPointOrign.y+r); //绘制一个经过当前鼠标移动的圆
			mPointOld=point;  //记录当前鼠标移动点作为下一次移动时的上一点
		}

	}
	else if (m_DrwaCurrent==6)  //正在绘制圆弧操作
	{
		if (PushNumb==2 && mPointOld!=point)
		{
			//如果按下二个点且当前鼠标移动点与上个移动点不同
			if (DrawArcYes>0) //如果已经在视图中绘制了m_Arc1对象存储的圆弧
			{
				m_Arc1.Draw(&dc,1,0,m_brColor); //重画以擦除圆弧 
			}

			pb=jsarc(mPointOrign1,mPointOrign,point,&m_CircleX,&m_CircleY,&m_CircleR,
				&m_Angle1,&m_Angle2);  //计算经过当前鼠标移动点的圆弧的几何要素
			if (pb)  //如果能计算的到圆弧的几何要素，初始化	m_Arc1对象并绘制这个圆弧
			{
				m_Arc1.Init(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,0,
					m_CircleX,m_CircleY,m_CircleR,0,m_Angle1,m_Angle2);
				m_Arc1.Draw(&dc,1,0,m_bColor);
			}
			
			DrawArcYes=pb; //判断这次是否绘制了m_Arc1 对象
			mPointOld=point;
		}
	}
	else if (m_DrwaCurrent==8 && PushNumb>0)   //正在绘制任意曲边形
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
	
	//得到指向当前文档的指针
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)
		                 AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	CPen pen(0,0,RGB(0,0,0));     //创建CPen对象
	CPen *pOldPen=dc.SelectObject(&pen); //在当前绘图对象中选择CPen对象.
	dc.SetROP2(R2_NOT);   //选择反色的绘制模式
	
	if (m_DrwaCurrent==1 && PushNumb==1) //如果正在绘制直线并且已经按下了直线的起点
	{
		dc.MoveTo(mPointOrign);
		dc.LineTo(mPointOld);  //擦除视图屏幕上拖动的橡皮线

		PushNumb=0;
		ReleaseCapture();  //释放捕捉的鼠标
	}
	else if ((m_DrwaCurrent==2 || m_DrwaCurrent==3) && PushNumb>0)
	{
		//正在绘制连线直线或多边形区域操作，并且已经按下而来一次以上鼠标左键

		//擦除最后一段拖动的橡皮线
		dc.MoveTo(mPointOrign);
		dc.LineTo(mPointOld);
		if (m_DrwaCurrent==2 && PushNumb>1) //如果正在绘制连线直线，并且顶点数大于2
		{
		   ReleaseCapture();
		}
		PushNumb=0;  //按下鼠标左键的次数为0
		ReleaseCapture(); //释放捕捉的鼠标
	}
	else if ( (m_DrwaCurrent==4 || m_DrwaCurrent==5) && PushNumb>0  )
		//如果正在绘制圆或圆形区域，并且已经按下第一点
	{
		if (m_DrwaCurrent==4)  //如果是圆，设置不填充状态
		{
			dc.SelectStockObject(NULL_BRUSH);
		}
		float r;
		r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2) +
			   pow((float)(mPointOrign.y-mPointOld.y),2) ); //得到上一个圆的半径
		//重画并擦除经过上一个点的圆
		dc.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
		ReleaseCapture(); //释放捕捉的鼠标
		PushNumb=0;       //按下鼠标左键的次数为0

	}
	else if (m_DrwaCurrent==6 && PushNumb>0)  //正在绘制圆弧操作
	{
		if (PushNumb==2)  //已经按下两个点，正在拖动圆弧
		{
			m_Arc1.Draw(&dc,1,0,m_bColor); //擦掉拖动的圆弧
		}
		PushNumb=0;
		ReleaseCapture();  //释放捕捉的鼠标
		
	}
	else if (m_DrwaCurrent==8 && PushNumb >0)
	{
	
		ReleaseCapture();
	
		PushNumb=0;

	}

	dc.SelectObject(pOldPen);  //恢复原来的画笔
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
	//将三个点的坐标赋给浮点变量
	x1=(float)p1.x;
	y1=(float)p1.y;
	x2=(float)p2.x;
	y2=(float)p2.y;
	x3=(float)p3.x;
	y3=(float)p3.y;

	if (x1==x2 && y1==y2 || x1==x3 && y1==y3 || x2==x3 && y2==y3)
	{
		//如果有两个点的坐标相同，操作不成功，返回FALSE
		return FALSE;
	}

	//得到顺三点方向的两条直线段中的的坐标
	xx1=(x1+x2)/2;
	yy1=(y1+y2)/2;
	xx2=(x2+x3)/2;
	yy2=(y2+y3)/2;

	if (fabs(y2-y1)>0.5)		//如果第一条直线段的垂线不是竖直线
	{
		k1=-(x2-x1)/(y2-y1);   //得到第一条直线段垂线的斜率
	}

	if (fabs(y3-y2)>0.5)       //如果第二条直线段的垂线不是竖直线
	{
		k2=-(x3-x2)/(y3-y2);   //得到第二条直线段垂线的斜率
	}

	if (k1==k2 && k1==0.0)	
	{
		return 0;
	}

	if (fabs(y2-y1)<0.5)			//	//如果第一条直线段是水平线（即第一条直线段的垂线是竖直线)
	{
		xx=xx1;
		if (fabs(y3-y2)<0.5)       //如果第二条直线段也是水平线
		{
			yy=y2+10000;			//给定圆弧的半径为10000
			rr=10000;
		}
		else		//如果第二条直线段不是水平线（即第二条直线段的垂线不是竖直线）
		{
			yy=yy2+k2*(xx2-xx);	//求的圆心的纵坐标
			rr=yy-y2;
			if (rr<0)
			{
				rr=-rr; //得到圆的半径
			}
		}
	}
	else if (fabs(y2-y3)<0.5)	//如果第二条直线式水平线，而第一条直线不是水平线
	{
		yy=yy1+k1*(xx1-xx);		//解得圆心的Y坐标
		rr=yy-y2;
		if (rr<0)
		{
			rr=-rr;    //得到圆的半径
		}
	}
	else			//如果两条直线段都不是水平线（即两条直线段的垂线都不是竖直线）
	{
		if (k1==k2) //如果两条直线段平行（即三个点在一条直线上)
		{
			//一下假定这个圆弧的半径为10000，求的圆心坐标
			xx=x2+(float)(10000/sqrt(1+k1*k1));	//圆心横坐标
			yy=y2+(float)(10000/sqrt(1+k1*k1)/(k1*k1)); //圆心纵坐标
			rr=10000;		//圆心半径
		}
		else	//如果两条直线段不平行
		{
			//解得两条直线段的垂线的交点，即圆心的坐标
			xx=(yy2-yy1+k1*xx1-k2*xx2)/(k1-k2);	//圆心横坐标
			yy=yy1+k1*(xx-xx1);	//圆心纵坐标
			rr=(float)sqrt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1));//圆的半径

		}
	}


	//将圆心和半径都转成实际坐标
	*CircleX=xx;
	*CircleY=yy;
	*CircleR=rr;
	float pi=3.414;


	an1=(float)acos((x1-xx)/rr);	//得到第一个点相当于圆心的弧度
	if (y1-yy >0 )		//
	{
		an1=(float)(pi*2-an1);
	}


	an2=(float)acos((x2-xx)/rr);	//得到第二个点相对于圆心的弧度
	if (y2-yy >0)
	{
		an2=(float)(pi*2-an2);
	}

	an3=(float)acos((x3-xx)/rr);	//得到第三个点相当于圆心的弧度
	if (y3-yy >0)
	{
		an3=(float)(pi*2-an3);
	}

	if (an2>an1 && an2<an1+pi || an2<an1 && an2+pi<an1)	//如果圆弧是逆时针方向画的
	{
		*Angle1=an1;	//得到圆弧的起始弧度
		*Angle2=an3;	//得到圆弧的结束弧度
	} 
	else			//如果圆弧是顺时针
	{
		*Angle1=an3;
		*Angle2=an1;
	}

	return TRUE; //操作成功

}

void CWhiteBoard::DrawText()
{
	CClientDC dc(this);  // 创建一个绘图对象
	//以下从标注文字对话框中得到字体参数
	m_TextString=pTextDlg->m_Text;
	m_FontHeight=pTextDlg->m_FontHeight;
	m_FontWide=pTextDlg->m_FontWide;
	m_TextAngle=pTextDlg->m_Angle1;
	m_FontAngle=pTextDlg->m_Angle2;
	m_FontBetween=pTextDlg->m_FontBetween;



}

void CWhiteBoard::DrawTextOnOk()
{
	//得到指向当前文档的指针
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this); //创建一个绘图对象
	int TextLong;
	PushNumb=0;
	m_TextString=pTextDlg->m_Text; //得到标注文本内容
	TextLong=m_TextString.GetLength();  //标注文本字符的长度
	if (TextLong>0)  //如果有标注文本
	{
		int id_only=pDoc->GetGraphID(5);  //得到要增加的标标注文本对象的识别号
		pDoc->AddText(m_pColor,m_brColor,m_LineWide,m_LineType,m_Layer,id_only,
					  m_TextX,m_TextY,m_TextAngle,m_FontAngle,m_FontHeight,
					  m_FontWide,m_FontBetween,0,TextLong,m_TextString)->Draw(&dc,0,0,m_bColor);
		pTextDlg->m_Text.Empty();  //清空字符串m_Text的内容
		pTextDlg->SendMessage(WM_INITDIALOG);  //激发消息调用对话框的OnInitDialog函数

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
	m_wndStatusBar.SetPaneText(0,"任意曲线");
}

void CWhiteBoard::Display()
{
	//得到指向当前文档的指针
	CChatClientDoc *pDoc=(CChatClientDoc *)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CClientDC dc(this);
	m_clorDraw=pDoc->msg.color;
	m_nBrushStye=pDoc->msg.m_nBrushStye;
    m_nPenWide=pDoc->msg.m_nPenWide;
	
	if (pDoc->msg.m_DrawCurrent==1)  //如果是直线或连续直线
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

	if (pDoc->msg.m_DrawCurrent==4)     //如果是圆或圆形区域
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
