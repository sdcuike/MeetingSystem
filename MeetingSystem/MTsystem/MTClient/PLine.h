// PLine.h: interface for the CPLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_)
#define AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:58
	filename: 	F:\MeetingSystem\MTsystem\MTClient\PLine.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	PLine
	file ext:	h
	author:		风云
	
	purpose:	连续直线除了具有图形元素基类CDraw所具有的属性外，从图
	形的几何特征上，连续直线是由很多顶点组成的，顶点的数目是不确定的，
	对一条连续直线来说可能只有二个顶点，也可能有几千个顶点。这就需要
	定义一个如下的结构来存储连续直线的一个顶点坐标（如下）；
	为了节省存储空间，对于连续直线的顶点坐标，采用动态分配存储空间的
	方法，即根据连续直线的顶点数目，在CPLne对象中分配连续直线的存储空
	间。连续直线或多边形类定义如下：
*********************************************************************/
#include "Draw.h"
typedef struct
{
	float x; //顶点的横坐标
	float y; //顶点的纵坐标
	float z;
}PontStruct;  //存储每个顶点坐标的结构

class CPLine : public CDraw  
{
	//连续直线或多边形类,还有任意曲线类
public:
	CPLine();
	CPLine(short ColorPen, short ColorBrush, short LineWide,
		   short LineType, short Layer, int id_only, BOOL Delete,
		  int Numble, PontStruct *PointList, BOOL Fill);
	virtual ~CPLine();

public:
	//图形绘制函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	int m_Numble; //连续直线或多边形区域的顶点数目
	BOOL b_Fill;  //表示是否填充，1--多边形区域，0--连续直线
	PontStruct* m_PiontList; //存储顶点坐标的数组指针

};

#endif // !defined(AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_)
