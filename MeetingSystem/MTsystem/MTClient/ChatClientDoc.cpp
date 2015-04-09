// ChatClientDoc.cpp : implementation of the CChatClientDoc class
//

#include "stdafx.h"
#include "ChatClient.h"

#include "ChatClientDoc.h"
#include "CntrItem.h"
#include "ChatSocket.h"
#include "chatclientview.h"
#include "WhiteBoard.h"
#include "MainFrm.h"
#include "ChatClientView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SAFEDELETE(x) if(x!=NULL){delete x;x=NULL;}
#define WM_ADDLIST    WM_USER + 1001

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc

IMPLEMENT_DYNCREATE(CChatClientDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CChatClientDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CChatClientDoc)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc construction/destruction

CGraphPara *p_GraphPara;

CChatClientDoc::CChatClientDoc()
{
	//文档的初始化
	m_bConnected = FALSE;
	m_pSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	m_bFilter = FALSE;

	p_GraphPara=&m_GraphPara; //将全局GraphPara类指针指向当前文档对象
                              //GraphPara对象
	m_Index=new int[20000];

}

CChatClientDoc::~CChatClientDoc()
{
	msg.type = -2;
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); 
	SendMsg();

	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);

	delete m_Index;
}

BOOL CChatClientDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CChatClientDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CChatClientCntrItem(preo, (CChatClientDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc serialization

void CChatClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc diagnostics

#ifdef _DEBUG
void CChatClientDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CChatClientDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc commands

void CChatClientDoc::ProcessPendingRead()
{

	//多次调用ReceiveMsg函数直到缓冲区为空
	do
	{
		ReceiveMsg();
		if (m_pSocket == NULL)
			return;
	}
	while(!m_pArchiveIn->IsBufferEmpty());
}

BOOL CChatClientDoc::ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress, LPCTSTR m_strImage, UINT nPort)
{

	//通信的初始化在函数ConnectSocket中进行，它完成对聊天称呼的设置，并建立对服务
    //器的连接，向服务器发送连接消息，
	if(m_bConnected)
		return FALSE;
	m_strHandle = lpszHandle;//设置聊天称呼

//释放上次的套接字对象

	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);

	if(m_pSocket == NULL){
		m_pSocket = new CChatSocket(this);//建新的CChatSocket对象
		ASSERT(m_pSocket != NULL);
	}

	if (!m_pSocket->Create())     //创建套接字
	{
		delete m_pSocket;
		m_pSocket = NULL;
		TRACE("Create Socket Error!\n");
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))    //连接服务器
	{
		if (AfxMessageBox(IDS_RETRYCONNECT,MB_YESNO) == IDNO)
		{
			delete m_pSocket;
			m_pSocket = NULL;
			return FALSE;
		}
	}


    //连接成功，初始化文件对象
	m_pFile = new CSocketFile(m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
	
   //向服务器发送第一条消息，某人(聊天称呼)向大家说“hello "
	msg.type = -1;
	msg.m_bClose = FALSE;
	msg.from = m_strHandle;
	msg.to = "所有人"; //公开
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); //红色字体
	msg.image = atoi(m_strImage);///头像

	SendMsg();//发送消息
	m_bConnected = TRUE;
	GetView()->GetParent()->SetWindowText(m_strHandle);//设置应用程序标题
	return TRUE;
}

void CChatClientDoc::SendMsg()
{
	msg.from = m_strHandle;
	if (m_pArchiveOut != NULL)
	{
		TRY
		{
			msg.Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
		}
		CATCH(CFileException, e)
		{
			m_pArchiveOut->Abort();
			delete m_pArchiveOut;
			m_pArchiveOut = NULL;
		
			CString strTemp;
			if (strTemp.LoadString(IDS_SERVERRESET))
				DisplayMsg(strTemp);
		}
		END_CATCH
	}

	// 从上面可以看出，消息的发送非常简单，只需简单地调用CMsg对象的Serialize函数即
    // 可，
}


//与视图类协调。用于显示发送聊天内容信息
void CChatClientDoc::DisplayMsg(LPCTSTR lpszText)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(pView != NULL)
		pView->TextOut(lpszText, RGB(128,0,0));
}


//接收数据的工作
void CChatClientDoc::ReceiveMsg()
{
	TRY
	{
		msg.Serialize(*m_pArchiveIn);
		DisplayRecMsg(msg.type, msg.from, msg.to, msg.secret, 
				msg.m_strText, msg.color);
		if(msg.type == -7 || msg.type == -2 || msg.type == -9)
			m_bConnected = FALSE;
		if(msg.type == -9)
			DisplayMsg("该用户名已经有人使用，请更名重新登录!\n");
	}
	CATCH(CFileException, e)
	{
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
		
		CString strTemp;
		if (strTemp.LoadString(IDS_SERVERRESET))
			DisplayMsg(strTemp);
		if (strTemp.LoadString(IDS_CONNECTIONCLOSED))
			DisplayMsg(strTemp);
	}
	END_CATCH
		
	if(msg.m_bClose && (msg.from == m_strHandle)){
		SAFEDELETE(m_pArchiveIn);
		SAFEDELETE(m_pArchiveOut);
		SAFEDELETE(m_pFile);
		SAFEDELETE(m_pSocket);
		m_bConnected = FALSE;
	}
	if((msg.type == -1 && msg.from != m_strHandle) || (msg.type == -8))
	{
		GetView()->GetParent()->SendMessage(WM_ADDLIST, 
											(LPARAM)&(msg.from), msg.image);
	}
	if((msg.type == -7) || (msg.type == -2)){
		GetView()->GetParent()->SendMessage(WM_ADDLIST + 1,
											(LPARAM)&(msg.from), msg.image);
	}
}


//与视图类协调。用于显示信息
void CChatClientDoc::DisplayRecMsg(int type, CString from, CString to,
		BOOL sec, CString str, COLORREF clr)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(type == -7){
		pView->TextOut(_T("系统：聊天室掌门人以一招'佛山无影脚',将"),RGB(0,0,0));
		if(from == m_strHandle){
			pView->TextOut(_T("你"),RGB(0,0,255));
		}
		else
			pView->TextOut(from,RGB(0,0,255));
		pView->TextOut(_T("踢出门外\r\n"),RGB(0,0,0));
	}   
	if(type == -5){
		return;	
	}
	if(type == -3){
		pView->TextOut(_T("系统：服务器已关闭!"),RGB(0,0,0));
		return;
	}
	if(type == -1 ){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("进入多人会有系统\r\n"),RGB(255,0,0));
	}
	if(type == -2){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("离开会有系统\r\n"),RGB(255,0,0));
	}
	if (type==30)
	{
	pView->whiteboard->Display();
		
	}
	if(type >= 0 && type!=30){
		if(from == m_strHandle || to == m_strHandle || sec == FALSE || to =="所有人")
			talk(type, from, to, str, clr);			
	}
}

void CChatClientDoc::talk(int type, CString form, CString to,
						  CString str, COLORREF clr)
{
	CChatClientView* pView = (CChatClientView*)GetView();
	
	if(form != m_strHandle && to != m_strHandle && m_bFilter)
		return;
	CString temp,to2,first,second;
	
	if(type > 32 || type < 0) 
		return;  
	temp.LoadString(IDS_TALK0 + type);	
	int i=temp.Find(",");
	if(i != -1){
		first = temp.Left(i);
		if(i != temp.GetLength() - 1){
			second = temp.Mid(i + 1);
			second += "：";
		}
		else{
			second="：";
		}
		pView->TextOut((LPCTSTR)form, RGB(0,0,255));
		pView->TextOut((LPCTSTR)first, RGB(0,0,0));
		pView->TextOut((LPCTSTR)to, RGB(0,0,255));
		pView->TextOut((LPCTSTR)second, RGB(0,0,0));
		pView->TextOut((LPCTSTR)str,clr);
		pView->TextOut((LPCTSTR)"\r\n",clr);
	}
	else{
		first=temp;
		second="： ";
		pView->TextOut(form,RGB(0,0,255));
		pView->TextOut(first,RGB(0,0,0));
		pView->TextOut(second,RGB(0,0,0));
		pView->TextOut(str,clr);
		pView->TextOut("\r\n",clr);
	}
}

void CChatClientDoc::Disconnect()
{
	msg.type = -2;
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); 

	SendMsg();
	m_bConnected = FALSE;
	msg.from = "DUMP";
	GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
}


void CChatClientDoc::DisplayWhiteBoardMsg( CPoint ptdown, CPoint pudown )
{
	CMainFrame* frm=(CMainFrame*)AfxGetApp()->GetMainWnd();
	CChatClientView* mtview=(CChatClientView*)frm->GetActiveView();
 //   mtview->whiteboard->Display(ptdown,pudown);
}

CLine* CChatClientDoc::AddLine( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only, float X1, float X2, float Y1, float Y2 )
{
	//增加一条直线对象
	CLine *p_Line=new CLine(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,X1,Y1,X2,Y2);     //动态创建并初始化一个CLine对象
	m_LineArray.Add(p_Line); //将指向新建CLine对象的指针增加到m_LineArray对象中
	return p_Line;           //返回指向新增CLine对象的指针
}

CPLine* CChatClientDoc::AddPline( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only,int Numble, PontStruct *PointList, BOOL Fill )
{
	//增加一个连续直线或多边形区域对象
	CPLine *p_PLine=new CPLine(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,Numble,PointList,Fill);
	m_PLineArray.Add(p_PLine);

	return p_PLine;
}

CText* CChatClientDoc::AddText( short ColorPen, short ColorBrush, short LineWide, 
							   short LineType, short Layer, int id_only,float StartX,
							   float StartY, float Angle1, float Angle2,float TextHeight,
							   float TextWinde, float OffWide,unsigned char TextFont ,
							   int TextLong, CString Text )
{
	//增加一个标注文本类
	CText *p_Text=new CText(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,0,
		StartX,StartY,Angle1,Angle2,TextHeight,TextWinde,OffWide,TextFont,TextLong,Text);

	m_TextArray.Add(p_Text);

	return p_Text;
}

CArc* CChatClientDoc::AddArc( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only,float CirleX, float CircleY, float CirleR, BOOL Fill,float Angle1, float Angle2 )
{
	//增加一个圆弧类对象
	CArc *p_Arc=new CArc(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,CirleX,CircleY,CirleR,Fill,Angle1,Angle2);
	m_ArcArray.Add(p_Arc);

	return p_Arc;
}

CCircle* CChatClientDoc::AddCicle( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only, float CirleX, float CircleY, float CirleR, BOOL Fill )
{
	//增加一个圆或圆形区域对象
	CCircle *p_Circle=new CCircle(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,CirleX,CircleY,CirleR,Fill);
	m_CircleArray.Add(p_Circle);
	
	return p_Circle;
}


//得到指向某类图形元素对象的指针
CDraw* CChatClientDoc::GetGraph( short Lb, int Index )
{
	switch(Lb)   //根据图形类别，进行不同的操作
	{
	case 1:      //如果是直线
		if (Index<0 || Index>m_LineArray.GetUpperBound())
		{
			return 0;
		}

		return m_LineArray.GetAt(Index);
		break;
	
	case 2:        //如果是连续直线或多边形区域
		if (Index<0 || Index>m_PLineArray.GetUpperBound())
		{
			return 0;
		}

		return m_PLineArray.GetAt(Index);
		break;

	case 3:       //如果是圆形或圆形区域
		if (Index<0 || Index>m_CircleArray.GetUpperBound())
		{
			return 0;
		}

		return m_CircleArray.GetAt(Index);
		break;

	case 4:           //如果是圆弧
		if (Index>0 || Index>m_ArcArray.GetUpperBound())
		{
			return 0;
		}

		return m_ArcArray.GetAt(Index);
		break;

	case 5:     //如果是标注文本
		if (Index>0 || Index>m_TextArray.GetUpperBound())
		{
			return 0;
		}
		
		return m_TextArray.GetAt(Index);
		break;

	default:
		return 0;

	}
}

void CChatClientDoc::DeleteGraph( short Lb, int Index )
{
	//能够从CObArray对象中删除一个指定图形元素对象指针
	switch(Lb)    //根据图形类别，进行不同的操作
	{
	case 1:     //如果是直线
		if (Index<0 || Index>m_LineArray.GetUpperBound())
		{
			return;
		}
		
	    m_LineArray.RemoveAt(Index);

		break;

	case 2:    //如果是连续直线或多边形区域
		if (Index<0 || Index>m_PLineArray.GetUpperBound())
		{
			return;
		}

		 m_PLineArray.RemoveAt(Index);

		break;

	case 3:		//如果是圆或圆形区域
		if (Index<0 || Index>m_CircleArray.GetUpperBound())
		{
			return;
		}

		 m_CircleArray.RemoveAt(Index);

		break;

	case 4:
		if (Index<0 || Index>m_ArcArray.GetUpperBound())
		{
			return;
		}
	
		 m_ArcArray.RemoveAt(Index);

		break;

	case 5:
		if (Index<0 || Index>m_TextArray.GetUpperBound())
		{
			return;
		}

		 m_TextArray.RemoveAt(Index);

		break;

	default:
		return;
	}
}

int CChatClientDoc::GetGraphNumb( short Lb )
{
	//得到文档中各种图形元素对象的数目
	switch(Lb)		//根据图形类别，获得各种图形元素的数目
	{
	case 1:		//如果是直线
		return m_LineArray.GetSize();

		break;

	case 2:		//如果是连续直线或多边形区域
		return m_PLineArray.GetSize();

		break;

	case 3:
		return m_CircleArray.GetSize();

		break;

	case 4:		//如果是圆弧
		return m_ArcArray.GetSize();

		break;
	case 5:		//如果是标注文本
		return m_TextArray.GetSize();

		break;

	default:
		return 0;

	}

}

int CChatClientDoc::GerGraphUpperBound( short Lb )
{
	//得到存储在各个CObArray对象中的最大数组下标
	switch(Lb)		//根据不同的图形类别，进行不同的操作
	{
	case 1:		
		return m_LineArray.GetUpperBound();
		break;

	case 2:
		return m_PLineArray.GetUpperBound();
		break;

	case 3:
		return m_CircleArray.GetUpperBound();
		break;

	case 4:
		return m_ArcArray.GetUpperBound();
		break;
		
	case 5:
		return m_TextArray.GetUpperBound();
		break;
	default:
	         
		return 0;
	}
}

int CChatClientDoc::GetGraphID( short Lb )
{
	//用来得到要增加的给类图形元素的唯一识别号
	int nn=GerGraphUpperBound(Lb);//用来得到存储第Lb类图形元素对象指针数组的最大下标
	for (int i=0;i<20000;++i)    //将整数数组m_Index的前20000项设置为0
	{
		m_Index[i]=0;
	}

	for (i=0;i<=nn;++i)		//对存储图形元素对象指针数组的所有数组循环
	{
		if (GetGraph(Lb,i))//如果读到的是一个对象指针，得到指针指向的图形元素的唯一识别号
						     //将整数数组m_Index中以这个识别号为下标的项设置为1
		{
			m_Index[GetGraph(Lb,i)->GetID()]=1;
		}

		
	}

	for (i=0;i<20000;++i)  //对m_Index数组项循环
	{
		if (m_Index[i]==0) //如果数组项等于0，则这个数组项的下标就是要找的唯一识别号
		{
			return i;
		}
	}

	return -1;
}
