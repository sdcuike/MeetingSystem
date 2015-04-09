// ChatClientDoc.h : interface of the CChatClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
#define AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "message.h"
#include "Line.h"
#include "PLine.h"
#include "Text.h"
#include "Circle.h"
#include "Arc.h"
#include "GraphPara.h"
class CChatSocket;
/********************************************************************
	created:	2010/04/15
	created:	15:4:2010   18:47
	filename: 	F:\MeetingSystem\MTClient\ChatClientDoc.h
	file path:	F:\MeetingSystem\MTClient
	file base:	ChatClientDoc
	file ext:	h
	author:		风云
	
	purpose:	负责数据的接收和发送，以及套接字通信的初始化。
*********************************************************************/
class CChatClientDoc : public CRichEditDoc
{
protected: // create from serialization only
	CChatClientDoc();
	DECLARE_DYNCREATE(CChatClientDoc)

// Attributes
public:
	CMessage msg;
	int *m_Index;
	int GetGraphID(short Lb);//用来得到要增加的给类图形元素的唯一识别号
private:
	CTypedPtrArray<CObArray,CLine*>   m_LineArray;	//管理直线对象指针
	CTypedPtrArray<CObArray,CPLine*>   m_PLineArray;	//管理连续直线对象指针的对象
	CTypedPtrArray<CObArray,CCircle*>   m_CircleArray;//管理圆对象指针的对象
	CTypedPtrArray<CObArray,CArc*>    m_ArcArray;		//管理圆弧对象指针的对象
	CTypedPtrArray<CObArray,CText*>   m_TextArray;	//管理标注文字对象指针的对象

protected:
	CGraphPara m_GraphPara;   //定义管理一个圆形参数的对象

// Operations
public:

 /*这五个函数分别用来实现增加一条直线、一条连续直线或封闭多边形区域、
 一个圆或圆形区城、一个圆弧、一个标注文本等的功能。函数返回指向新增
 图形元素对象的指针。

 */
	CLine* AddLine(short ColorPen, short ColorBrush, short LineWide,
	               short LineType, short Layer, int id_only, float X1, 
				   float X2, float Y1, float Y2);
	CPLine* AddPline(short ColorPen, short ColorBrush, short LineWide,
		             short LineType, short Layer, int id_only,int Numble,
					 PontStruct *PointList, BOOL Fill);
	CCircle* AddCicle(short ColorPen, short ColorBrush, short LineWide,
		              short LineType, short Layer, int id_only,
		              float CirleX, float CircleY, float CirleR, BOOL Fill);
    CArc*  AddArc(short ColorPen, short ColorBrush, short LineWide,
		          short LineType, short Layer, int id_only,float CirleX,
				  float CircleY, float CirleR, BOOL Fill,float Angle1,
				  float Angle2);
	CText* AddText(short ColorPen, short ColorBrush, short LineWide,
		           short LineType, short Layer, int id_only,float StartX, 
				   float StartY, float Angle1, float Angle2,float TextHeight,
				   float TextWinde, float OffWide,unsigned char TextFont,int TextLong,
				   CString Text);

	/************************************************************************/
	/*获得指向某个图形元素对象的CDraw类指针。参数Lb用来表示要返回的图形类别:
	1一直线.2-连续直线或多边形区域，3-~圆或圆形区域，4—圆弧，5-标注文本。
	参数Index是要得到的图形元家对象指针在相应CObArray对象中的0基序号(数组的下标)                                                                      */
	/************************************************************************/
	CDraw* GetGraph(short Lb, int Index);

	void DeleteGraph(short Lb, int Index);  //从CObArray对象中删除一个指定图形元素对象指针

	int GetGraphNumb(short Lb);   //得到文档中各种图形元素对象的数目

	int GerGraphUpperBound(short Lb );//得到存储在各个CObArray对象中的最大数组下标
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	void Disconnect();
	BOOL m_bFilter;//标识是否屏蔽消息
	void ReceiveMsg();
	void SendMsg();
	BOOL ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress, LPCTSTR m_strImage, UINT nPort);
	void ProcessPendingRead();
	BOOL m_bConnected;//标识套接字是否已经连接。
	virtual ~CChatClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CChatSocket* m_pSocket; //客户套接字对象
	CSocketFile* m_pFile; //套接字文件对象
	CArchive* m_pArchiveIn; //套接字归档对象
	CArchive* m_pArchiveOut; //套接字归档对象

	CString  m_strHandle; //用户所用的聊天称呼，该变量由用户指定
	void talk(int type, CString from, CString to, CString str,COLORREF clr);
	void DisplayRecMsg(int type, CString from, CString to,BOOL sec, CString str, COLORREF clr);
	void DisplayMsg(LPCTSTR lpszText);
	void DisplayWhiteBoardMsg(CPoint ptdown, CPoint pudown);
// Generated message map functions
protected:
	//{{AFX_MSG(CChatClientDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
