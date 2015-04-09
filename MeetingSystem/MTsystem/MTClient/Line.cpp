// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Line.h"
#include "GraphPara.h"
#include <afxwin.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{

}

CLine::CLine( short ColorPen, short ColorBrush, short LineWide, short LineType, 
			 short Layer, int id_only, BOOL Delete, float X1, float X2, 
			 float Y1, float Y2 )
:CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_X1=X1;
	m_x2=X2;
	m_Y1=Y1;
	m_Y2=Y2;

}

CLine::~CLine()
{

}

void CLine::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//图形绘制函数
	int x1;
	int y1;
	int x2;
	int y2;

	if (b_Delete)			//如果图形处于删除状态，退出函数
	{
		return;
	}

	short LineType=m_LineType;
	short ColorPen=m_ColorPen;

	if (m_DrwaMode1==1)			//如果图形元素需要特殊显示
	{
		if (m_LineType!=2)		//如果图形元素采用的不是第二种线性（虚线），则采用第二中线性
		{
			LineType=2;
		} 
		else					//如果图形元素采用的是第二种线性（虚线）,则采用第三种线性
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)	//如果需要采用指定颜色绘制，将笔色设置为屏幕底色BackColor
	{
		ColorPen=BackColor;
	}

	//创建并初始化一个CPen对象

	extern CGraphPara *p_GraphPara;
	CPen pen((int)LineType, (int)m_LineWide,p_GraphPara->GetColor(ColorPen) );
	CPen *pOldPen=pDC->SelectObject(&pen);	//在绘图对象中选人CPen对象
	if (m_DrwaMode==0)						//如果采用第0中绘图模式
	{
		pDC->SetROP2(R2_COPYPEN);			//设定覆盖的绘制模式
	}
	else if (m_DrwaMode==1)					//如果采用第一种绘制模式
	{	
		pDC->SetROP2(R2_NOT);
	}



	x1=(int)m_X1;
	x2=(int)m_x2;
	y1=(int)m_Y1;
	y2=(int)m_Y2;


	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);						//绘制直线
	pDC->SelectObject(pOldPen);				//恢复原来的画笔
}
