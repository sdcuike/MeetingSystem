// PLine.cpp: implementation of the CPLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "PLine.h"
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

CPLine::CPLine()
{
	m_Numble=0;
}

CPLine::CPLine( short ColorPen, short ColorBrush, short LineWide, 
			   short LineType, short Layer, int id_only, BOOL Delete,
			   int Numble, PontStruct *PointList, BOOL Fill )
 :CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_Numble=Numble;
	b_Fill=Fill;

	m_PiontList=new PontStruct[m_Numble+1];//动态分配存储顶点坐标的结构数组

	if (m_Numble>0)
	{
		for (int i=0; i<m_Numble; ++i )
		{
			m_PiontList[i]=PointList[i];
		}
	}
}

CPLine::~CPLine()
{
	if (m_Numble>0)
	{
		delete m_PiontList;
	}
}

void CPLine::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//图形绘制函数
	
	if (b_Delete)		//如果已经处于删除状态
	{
		return;
	}

	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	short ColorBrush=m_ColorBrush;
	if (m_DrwaMode1==1)	//如果图形元素需要特殊显示
	{
		if (m_LineType!=2)//如果图形元素采用的不是第二种线型（虚线），则采用第二种线型
		{
			LineType=2;
		}
		else			//如果图形元素采用的是第二种线型（虚线），则采用第三种线型
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)//如果需要用指定颜色绘制连续直线或多边形区域，
							//将笔色和填充色设置屏幕底色BackColor
	{	
		ColorPen=BackColor;
		ColorBrush=BackColor;
	}

	//创建并初始化一个CPen对象
	extern CGraphPara *p_GraphPara;
	CPen pen((int)LineType, (int)m_LineWide, p_GraphPara->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush brush(p_GraphPara->GetColor(m_ColorBrush));
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	
	POINT *ppoint;
	CRgn rgn;
	if(m_DrwaMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if( m_DrwaMode==1)
		pDC->SetROP2(R2_NOT);
	ppoint=new POINT[m_Numble+1];
	for (int i=0; i<m_Numble; ++i)
	{
		ppoint[i].x=(long)m_PiontList[i].x;
		ppoint[i].y=(long)m_PiontList[i].y;
	}

	if (!b_Fill)		// 如果是连续直线，则依次绘制各个线段
	{
		ppoint[m_Numble]=ppoint[0];
		pDC->MoveTo(ppoint[0].x, ppoint[0].y);
		for (i=0; i<m_Numble; ++i)
		{
			pDC->LineTo(ppoint[i].x, ppoint[i].y);
		}
	}
	else			//如果是多边形
	{
		if (m_DrwaMode1==0 || m_DrwaMode1==2)  //如果是正常显示
		{
			pDC->Polyline(ppoint,m_Numble);
		}
		else if (m_DrwaMode1==1)      //如果是反色显示
		{
			rgn.CreatePolygonRgn(ppoint,m_Numble,0);  //创建一个CRgn对象
			pDC->InvertRgn(&rgn);		//将CRgn对象确定的区域反色显示
		}

	}

	delete ppoint;			//删除动态分配的结构数组
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}