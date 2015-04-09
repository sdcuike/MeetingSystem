// Circle.cpp: implementation of the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Circle.h"
#include "GraphPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{

}

CCircle::CCircle( short ColorPen, short ColorBrush, short LineWide, 
				 short LineType, short Layer, int id_only, BOOL Delete,
				 float CirleX, float CircleY, float CirleR, BOOL Fill )
 :CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_CircleX=CirleX;
	m_CircleY=CircleY;
	m_CirleR=CirleR;
	b_Fill=Fill;
}

CCircle::~CCircle()
{

}

void CCircle::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//图形绘制函数
	if (b_Delete)		//如果图形元素对象处于删除状态，函数退出
	{
		return;
	}
	int x,y,r;
	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	short ColorBrush=m_ColorBrush;
	if (m_DrwaMode1==1)			//如果图形元素需要特殊显示
	{
		if (m_LineType!=2)		//如果图形元素利用的不是第二种线型（虚线），则采用第二种线型
		{
			LineType=2;
		} 
		else					//如果图形元素采用的是第二种线型（虚线），则采用第三种线型
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)		//如果需要用指定颜色绘制圆或圆形区域，将笔色和填充色
										//设置为屏幕底色BackColor
	{
		ColorPen=BackColor;
		ColorBrush=BackColor;
	}

		//创建并初始化一个CPen对象

		extern CGraphPara *p_GraphPara;
		CPen pen((int)LineType, (int)m_LineWide,p_GraphPara->GetColor(ColorPen ));
		CPen *pOldPen=pDC->SelectObject(&pen);
		CBrush brush(p_GraphPara->GetColor(m_ColorBrush));
		CBrush *pOldBrush=pDC->SelectObject(&brush);
		if (m_DrwaMode==0)			//如果采用第0种绘制模式
		{
			pDC->SetROP2(R2_COPYPEN); //设定覆盖模式
		}
		else if (m_DrwaMode==1)		//如果采用第1种绘制模式
		{
			pDC->SetROP2(R2_NOT);  //设置反写的绘制模式
		}

		if (!b_Fill)				//如果是普通圆，设置不填充模式
		{
			pDC->SelectStockObject(NULL_BRUSH);
		}

		x=(int)m_CircleX;
		y=(int)m_CircleY;
		r=(int)m_CirleR;
		pDC->Ellipse(x-r,y-r,x+r,y+r);  //绘制圆
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
