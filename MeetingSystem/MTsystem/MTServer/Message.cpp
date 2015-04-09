// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatSrvr.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");

	
	m_ColorPen=0.0;      //颜色
	m_ColorBrush=0.0;    //填充颜色
	m_LineWide=0.0;      //线宽(像素)
	m_LineType=0.0;      //线型
	m_Layer=0.0;        // 所在图层
	
   	b_Delete=FALSE;       //是否处于删除状态
	
	m_id_only=0;      //图形元素唯一的识别号
	
	
	//////派生类特有数据成员/////////////
	
    m_DrawCurrent=100;   //用于区别传输的是哪类线条
    m_PointNumber=0; //一次传输几个点
	
	//---连续直线或多边形，及任意曲边线的特有数据成员
	b_Fill=FALSE;  //表示是否填充，1--多边形区域，0--连续直线或任意曲线条
}

CMessage::~CMessage()
{
}

void CMessage::Serialize(CArchive &ar)
{
	
	if (ar.IsStoring()){
		ar << type;
		ar << (WORD)m_bClose;
		ar << m_strText;
		ar << (WORD)secret;
		ar << from;
		ar << to;
		ar << (DWORD)color;
		ar << image;
		
		ar<<m_ColorPen;
		ar<<m_ColorBrush;
		ar<<m_LineWide;
		ar<<m_LineType;
		ar<<m_Layer;
		ar<<b_Delete;
		ar<<m_id_only;
		
		ar<<m_DrawCurrent;
		ar<<m_PointNumber;
		ar<<b_Fill;
		for (int i=0;i<m_PointNumber;++i)
		{
			ar<<m_HvaePN[i];
		}


		ar<<m_byRed; //当前绘图对象的颜色,即画笔或画刷的颜色
		ar<<m_byGreen;
		ar<<m_byBlue;
		ar<<m_nPenWide; //画笔粗细
	    ar<<m_nBrushStye; //画刷的类型
	}
	else{
		WORD wd;
		DWORD dwTmp;
		
		ar >> type;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
		ar >> wd;
		secret = (BOOL)wd;
		ar >> from;
		ar >> to;
		ar >> dwTmp;
		color = (COLORREF)dwTmp;
		ar >> image;
		
		
		ar>>m_ColorPen;
		ar>>m_ColorBrush;
		ar>>m_LineWide;
		ar>>m_LineType;
		ar>>m_Layer;
		ar>>b_Delete;
		ar>>m_id_only;
		
		
		ar>>m_DrawCurrent;
		ar>>m_PointNumber;
		ar>>b_Fill;
		for (int i=0;i<m_PointNumber;++i)
		{
			ar>>m_HvaePN[i];
		}


		ar>>m_byRed; //当前绘图对象的颜色,即画笔或画刷的颜色
		ar>>m_byGreen;
		ar>>m_byBlue;
		ar>>m_nPenWide; //画笔粗细
	    ar>>m_nBrushStye; //画刷的类型
	}
}

void CMessage::Reset()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");

	
	
	m_ColorPen=0.0;      //颜色
	m_ColorBrush=0.0;    //填充颜色
	m_LineWide=0.0;      //线宽(像素)
	m_LineType=0.0;      //线型
	m_Layer=0.0;        // 所在图层
	
   	b_Delete=FALSE;       //是否处于删除状态
	
	m_id_only=0;      //图形元素唯一的识别号
	
	
	//////派生类特有数据成员/////////////
	
    m_DrawCurrent=100;   //用于区别传输的是哪类线条
    m_PointNumber=0; //一次传输几个点
	
	//---连续直线或多边形，及任意曲边线的特有数据成员
	b_Fill=FALSE;  //表示是否填充，1--多边形区域，0--连续直线或任意曲线条
}
