// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_)
#define AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:39
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Line.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Line
	file ext:	h
	author:		风云
	
	purpose:	直线类从图形元素基类CDrew派生而来，直线的一些基本
	            参数(如线型、线宽、颇色、删除标志等)从CDrew类中继
				承而来，而对于直线的特殊性质(如直线的起点和终点坐
				标)则在直线类中定义。直线类CLine的定义如下：
*********************************************************************/
class CLine : public CDraw  
{
	//直线类
public:
	CLine();
	CLine(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete, 
		  float X1, float X2, float Y1, float Y2);
		  
	virtual ~CLine();

public:
	//图形绘制函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	float m_X1;
	float m_x2; //直线的起点坐标
	float m_Y1;
	float m_Y2; //直线的终点坐标

};

#endif // !defined(AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_)
