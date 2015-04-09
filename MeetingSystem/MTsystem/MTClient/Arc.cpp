// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Arc.h"
#include "GraphPara.h"
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CArc::CArc()
{

}

CArc::CArc( short ColorPen, short ColorBrush, short LineWide, 
		   short LineType, short Layer, int id_only, BOOL Delete, 
		   float CirleX, float CircleY, float CirleR, BOOL Fill, 
		   float Angle1, float Angle2 )
		   :CCircle(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete,
		   CirleX,CircleY,CirleR,Fill)
{
	m_Anglel=Angle1;
	m_Angle2=Angle2;
}

CArc::~CArc()
{

}

void CArc::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//进行绘制操作的虚函数
	if(b_Delete)		//如果图形元素处于删除状态，函数退出
		return;
	int x,y,rr;
	int x1,x2,y1,y2;
	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	if (m_DrwaMode1==1)		//如果图形元素需要特殊显示
	{
		if (m_LineType!=2)	//如果图形元素采用的不是第二种线型（虚线），则采用第二种线型
		{
			LineType=2;
		}
		else				//如果图形元素采用的是第二种线型（虚线），则采用第三种线型
		{
			++LineType;
		}

	}
	else if (m_DrwaMode1==2) //如果需要用指定的颜色绘制圆弧
	{
		ColorPen=BackColor;
	}
	
	extern  CGraphPara *p_GraphPara;

	CPen pen((int)LineType, (int)m_LineWide, p_GraphPara->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);
	if (m_DrwaMode==0)		//如果采用第0种绘制模式
	{
		pDC->SetROP2(R2_COPYPEN); //设定覆盖的绘制模式
	}
	else if (m_DrwaMode==1)
	{
		pDC->SetROP2(R2_NOT);
	}

	x=(int)m_CircleX;
	y=(int)m_CircleY;
	rr=(int)m_CirleR;

	//以下计算圆弧起点的坐标
	x1=(int)(x+m_CirleR*cos(m_Anglel) );
	y1=(int)(y-m_CirleR*sin(m_Anglel) );
	//以下得到圆弧终点的坐标
	x2=(int)(x+m_CirleR*cos(m_Angle2) );
	y2=(int)(y-m_CirleR*sin(m_Angle2) );

	pDC->Arc(x-rr,y-rr,x+rr,y+rr,x1,y1,x2,y2);  //绘制圆

	pDC->SelectObject(pOldPen);  //恢复原来的画笔

}

void CArc::Init( short ColorPen, short ColorBrush, short LineWinde, short LineType, short Layer, BOOL Delete, float CircleX,float CircleY,float CircleR, BOOL Fill, float Angle1, float Angle2 )
{
	//圆弧对象成员变量初始化
	m_ColorPen=ColorPen;
	m_ColorBrush=ColorBrush;
	m_LineWide=LineWinde;
	m_LineType=LineType;
	m_Layer=Layer;
	m_CircleX=CircleX;
	m_CircleY=CircleY;
	m_CirleR=CircleR;
	b_Fill=Fill;
	m_Anglel=Angle1;
	m_Angle2=Angle2;
	b_Delete=Delete;


}


