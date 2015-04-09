// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
#define AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/15
	created:	15:4:2010   18:22
	filename: 	F:\MeetingSystem\MTClient\Message.h
	file path:	F:\MeetingSystem\MTClient
	file base:	Message
	file ext:	h
	author:		风云
	
	purpose:	CSocket类的串行化技术使得发送和接收网络数据就像普通的数据串
	  行化一样简单。因此封装一个可以串行化的消息类是必要的，有了这个类，消
	  息的发送和接收只需使用流操作符对缓冲区进行存取就可以了。并且这样做将
	  使程序具有很好的扩展性，例如假如应用程序要在原来的基础上增加一些消息，
	  那么程序员所要作的只是把相应的消息项加入类中，再在服务器和客户两端进
	  行相应解释即可。根据这个系统程序的需要，消息类CMessage的定义如下:
*********************************************************************/
class CMessage : public CObject  
{
public:
	void Serialize(CArchive& ar);//重载
	CMessage();
	virtual ~CMessage();
public:
	void Reset();        //用于使消息采用默认的设置

	CString m_strText;   //用于存放客户向服务器发送的信息
	CString from;        //为消息发送方的名称
	CString to;          //为消息的接收方名称

	COLORREF color;     //为字体颜色
	BOOL secret;        //用于标识消息是否为“悄悄话”
	BOOL m_bClose;      //用于表示客户是否结束运行
	int type;           //用于标识动作
	WORD image;         //用于标识头像的ID


	

	
	/////////////简易电子白板数据///////////////////
	//--基类Draw的数据
	short m_ColorPen;      //颜色
	short m_ColorBrush;    //填充颜色
	short m_LineWide;      //线宽(像素)
	short m_LineType;      //线型
	short m_Layer;        // 所在图层
	
	BOOL b_Delete;       //是否处于删除状态
	
	int  m_id_only;      //图形元素唯一的识别号
    
	//////派生类特有数据成员/////////////

	int m_DrawCurrent;   //用于区别传输的是哪类线条
	int m_PointNumber; //一次传输几个点
	CPoint m_HvaePN[100];//假定一次传输的点不超过100，用来保存传输的点的坐标

	//---连续直线或多边形，及任意曲边线的特有数据成员
	BOOL b_Fill;  //表示是否填充，1--多边形区域，0--连续直线或任意曲线条


	BYTE  m_byRed; //当前绘图对象的颜色,即画笔或画刷的颜色
	BYTE  m_byGreen;
	BYTE  m_byBlue;
	int m_nPenWide; //画笔粗细
	int m_nBrushStye; //画刷的类型
	

};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
