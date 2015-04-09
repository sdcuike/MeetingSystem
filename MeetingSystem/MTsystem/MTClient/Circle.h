// Circle.h: interface for the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_)
#define AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:20
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Circle.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Circle
	file ext:	h
	author:		风云
	
	purpose:	对圆类的定义方法与直线类CPLine类似。圆除了具有图形元素
	的基本特征外，还有自身的集合特征，可以用团心和半径作为特征参数表示
	圆的几何特征(当然也可以采用其他的方法，如边界矩形、圆心直径法等)。
	圆类CCircle如下
*********************************************************************/
#include "Draw.h"

class CCircle : public CDraw  
{
public:
	CCircle();
	CCircle(short ColorPen, short ColorBrush, short LineWide,
		    short LineType, short Layer, int id_only, BOOL Delete,
		    float CirleX, float CircleY, float CirleR, BOOL Fill);
	virtual ~CCircle();

public:
	//图形绘制函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	float m_CircleX;
	float m_CircleY;
	float m_CirleR; //记录圆心坐标及半径的变量
	BOOL b_Fill;   //表示是否填充，1--圆形区域，0---普通圆
};

#endif // !defined(AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_)
