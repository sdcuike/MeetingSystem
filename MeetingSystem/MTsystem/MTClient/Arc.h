// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_)
#define AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:41
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Arc.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Arc
	file ext:	h
	author:		风云
	
	  purpose:	圆是圆弧的特例，当一个圆弧的弧度等于2 时就一个圆。
	  所以可以从圆类派生而得到一个圆弧类：
*********************************************************************/
#include "Circle.h"

class CArc : public CCircle  
{
	//圆弧类的定义
public:
	CArc();
	CArc(short ColorPen, short ColorBrush, short LineWide,
		 short LineType, short Layer, int id_only, BOOL Delete,
		 float CirleX, float CircleY, float CirleR, BOOL Fill,
		 float Angle1, float Angle2);
	virtual ~CArc();

public:
	//进行绘制操作的虚函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);

	void Init(short ColorPen, short ColorBrush, short LineWinde, short LineType,
		      short Layer, BOOL Delete, float CircleX,float CircleY,float CircleR,
			  BOOL Fill, float Angle1, float Angle2);//圆弧对象成员变量初始化
protected:
	float m_Anglel;
	float m_Angle2;//圆弧的起点和终点角度(用弧度表示）

};



#endif // !defined(AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_)

