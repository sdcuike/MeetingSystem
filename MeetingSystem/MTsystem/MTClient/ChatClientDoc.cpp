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
	//�ĵ��ĳ�ʼ��
	m_bConnected = FALSE;
	m_pSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	m_bFilter = FALSE;

	p_GraphPara=&m_GraphPara; //��ȫ��GraphPara��ָ��ָ��ǰ�ĵ�����
                              //GraphPara����
	m_Index=new int[20000];

}

CChatClientDoc::~CChatClientDoc()
{
	msg.type = -2;
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "������";
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

	//��ε���ReceiveMsg����ֱ��������Ϊ��
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

	//ͨ�ŵĳ�ʼ���ں���ConnectSocket�н��У�����ɶ�����ƺ������ã��������Է���
    //�������ӣ������������������Ϣ��
	if(m_bConnected)
		return FALSE;
	m_strHandle = lpszHandle;//��������ƺ�

//�ͷ��ϴε��׽��ֶ���

	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);

	if(m_pSocket == NULL){
		m_pSocket = new CChatSocket(this);//���µ�CChatSocket����
		ASSERT(m_pSocket != NULL);
	}

	if (!m_pSocket->Create())     //�����׽���
	{
		delete m_pSocket;
		m_pSocket = NULL;
		TRACE("Create Socket Error!\n");
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))    //���ӷ�����
	{
		if (AfxMessageBox(IDS_RETRYCONNECT,MB_YESNO) == IDNO)
		{
			delete m_pSocket;
			m_pSocket = NULL;
			return FALSE;
		}
	}


    //���ӳɹ�����ʼ���ļ�����
	m_pFile = new CSocketFile(m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
	
   //����������͵�һ����Ϣ��ĳ��(����ƺ�)����˵��hello "
	msg.type = -1;
	msg.m_bClose = FALSE;
	msg.from = m_strHandle;
	msg.to = "������"; //����
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); //��ɫ����
	msg.image = atoi(m_strImage);///ͷ��

	SendMsg();//������Ϣ
	m_bConnected = TRUE;
	GetView()->GetParent()->SetWindowText(m_strHandle);//����Ӧ�ó������
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

	// ��������Կ�������Ϣ�ķ��ͷǳ��򵥣�ֻ��򵥵ص���CMsg�����Serialize������
    // �ɣ�
}


//����ͼ��Э����������ʾ��������������Ϣ
void CChatClientDoc::DisplayMsg(LPCTSTR lpszText)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(pView != NULL)
		pView->TextOut(lpszText, RGB(128,0,0));
}


//�������ݵĹ���
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
			DisplayMsg("���û����Ѿ�����ʹ�ã���������µ�¼!\n");
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


//����ͼ��Э����������ʾ��Ϣ
void CChatClientDoc::DisplayRecMsg(int type, CString from, CString to,
		BOOL sec, CString str, COLORREF clr)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(type == -7){
		pView->TextOut(_T("ϵͳ����������������һ��'��ɽ��Ӱ��',��"),RGB(0,0,0));
		if(from == m_strHandle){
			pView->TextOut(_T("��"),RGB(0,0,255));
		}
		else
			pView->TextOut(from,RGB(0,0,255));
		pView->TextOut(_T("�߳�����\r\n"),RGB(0,0,0));
	}   
	if(type == -5){
		return;	
	}
	if(type == -3){
		pView->TextOut(_T("ϵͳ���������ѹر�!"),RGB(0,0,0));
		return;
	}
	if(type == -1 ){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("������˻���ϵͳ\r\n"),RGB(255,0,0));
	}
	if(type == -2){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("�뿪����ϵͳ\r\n"),RGB(255,0,0));
	}
	if (type==30)
	{
	pView->whiteboard->Display();
		
	}
	if(type >= 0 && type!=30){
		if(from == m_strHandle || to == m_strHandle || sec == FALSE || to =="������")
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
			second += "��";
		}
		else{
			second="��";
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
		second="�� ";
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
	msg.to = "������";
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
	//����һ��ֱ�߶���
	CLine *p_Line=new CLine(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,X1,Y1,X2,Y2);     //��̬��������ʼ��һ��CLine����
	m_LineArray.Add(p_Line); //��ָ���½�CLine�����ָ�����ӵ�m_LineArray������
	return p_Line;           //����ָ������CLine�����ָ��
}

CPLine* CChatClientDoc::AddPline( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only,int Numble, PontStruct *PointList, BOOL Fill )
{
	//����һ������ֱ�߻������������
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
	//����һ����ע�ı���
	CText *p_Text=new CText(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,0,
		StartX,StartY,Angle1,Angle2,TextHeight,TextWinde,OffWide,TextFont,TextLong,Text);

	m_TextArray.Add(p_Text);

	return p_Text;
}

CArc* CChatClientDoc::AddArc( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only,float CirleX, float CircleY, float CirleR, BOOL Fill,float Angle1, float Angle2 )
{
	//����һ��Բ�������
	CArc *p_Arc=new CArc(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,CirleX,CircleY,CirleR,Fill,Angle1,Angle2);
	m_ArcArray.Add(p_Arc);

	return p_Arc;
}

CCircle* CChatClientDoc::AddCicle( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only, float CirleX, float CircleY, float CirleR, BOOL Fill )
{
	//����һ��Բ��Բ���������
	CCircle *p_Circle=new CCircle(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,
		0,CirleX,CircleY,CirleR,Fill);
	m_CircleArray.Add(p_Circle);
	
	return p_Circle;
}


//�õ�ָ��ĳ��ͼ��Ԫ�ض����ָ��
CDraw* CChatClientDoc::GetGraph( short Lb, int Index )
{
	switch(Lb)   //����ͼ����𣬽��в�ͬ�Ĳ���
	{
	case 1:      //�����ֱ��
		if (Index<0 || Index>m_LineArray.GetUpperBound())
		{
			return 0;
		}

		return m_LineArray.GetAt(Index);
		break;
	
	case 2:        //���������ֱ�߻���������
		if (Index<0 || Index>m_PLineArray.GetUpperBound())
		{
			return 0;
		}

		return m_PLineArray.GetAt(Index);
		break;

	case 3:       //�����Բ�λ�Բ������
		if (Index<0 || Index>m_CircleArray.GetUpperBound())
		{
			return 0;
		}

		return m_CircleArray.GetAt(Index);
		break;

	case 4:           //�����Բ��
		if (Index>0 || Index>m_ArcArray.GetUpperBound())
		{
			return 0;
		}

		return m_ArcArray.GetAt(Index);
		break;

	case 5:     //����Ǳ�ע�ı�
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
	//�ܹ���CObArray������ɾ��һ��ָ��ͼ��Ԫ�ض���ָ��
	switch(Lb)    //����ͼ����𣬽��в�ͬ�Ĳ���
	{
	case 1:     //�����ֱ��
		if (Index<0 || Index>m_LineArray.GetUpperBound())
		{
			return;
		}
		
	    m_LineArray.RemoveAt(Index);

		break;

	case 2:    //���������ֱ�߻���������
		if (Index<0 || Index>m_PLineArray.GetUpperBound())
		{
			return;
		}

		 m_PLineArray.RemoveAt(Index);

		break;

	case 3:		//�����Բ��Բ������
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
	//�õ��ĵ��и���ͼ��Ԫ�ض������Ŀ
	switch(Lb)		//����ͼ����𣬻�ø���ͼ��Ԫ�ص���Ŀ
	{
	case 1:		//�����ֱ��
		return m_LineArray.GetSize();

		break;

	case 2:		//���������ֱ�߻���������
		return m_PLineArray.GetSize();

		break;

	case 3:
		return m_CircleArray.GetSize();

		break;

	case 4:		//�����Բ��
		return m_ArcArray.GetSize();

		break;
	case 5:		//����Ǳ�ע�ı�
		return m_TextArray.GetSize();

		break;

	default:
		return 0;

	}

}

int CChatClientDoc::GerGraphUpperBound( short Lb )
{
	//�õ��洢�ڸ���CObArray�����е���������±�
	switch(Lb)		//���ݲ�ͬ��ͼ����𣬽��в�ͬ�Ĳ���
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
	//�����õ�Ҫ���ӵĸ���ͼ��Ԫ�ص�Ψһʶ���
	int nn=GerGraphUpperBound(Lb);//�����õ��洢��Lb��ͼ��Ԫ�ض���ָ�����������±�
	for (int i=0;i<20000;++i)    //����������m_Index��ǰ20000������Ϊ0
	{
		m_Index[i]=0;
	}

	for (i=0;i<=nn;++i)		//�Դ洢ͼ��Ԫ�ض���ָ���������������ѭ��
	{
		if (GetGraph(Lb,i))//�����������һ������ָ�룬�õ�ָ��ָ���ͼ��Ԫ�ص�Ψһʶ���
						     //����������m_Index�������ʶ���Ϊ�±��������Ϊ1
		{
			m_Index[GetGraph(Lb,i)->GetID()]=1;
		}

		
	}

	for (i=0;i<20000;++i)  //��m_Index������ѭ��
	{
		if (m_Index[i]==0) //������������0���������������±����Ҫ�ҵ�Ψһʶ���
		{
			return i;
		}
	}

	return -1;
}
