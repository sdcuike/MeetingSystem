// Draw.h: interface for the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_)
#define AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:15
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Draw.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Draw
	file ext:	h
	author:		风云
	
	purpose:	对各种图形元素进行分析，可以发现各类图形元素具有一些
	相同的属性和操作功能，如图形元素的颜色、线型、线宽等属性和得到一
	个图形元素是否做了删除标志等操作。把这些图形元素中共性的东西(属性
	和操作)组织存放在一个图形元素基类中，具体的图形元素类由这个类派生。
	此类的设计如下：
*********************************************************************/
class CDraw :public CObject
{
	//图形元素基类，用于存储图形的颜色，线性等消息
public:
	CDraw();
	CDraw(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete);
	
	virtual ~CDraw();

public:

	//进行绘制操作的虚函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor)=0;
	int GetID();  //得到一个图形元素对象的识别号--m_id_only
protected:
	short m_ColorPen;      //颜色
	short m_ColorBrush;    //填充颜色
	short m_LineWide;      //线宽(像素)
	short m_LineType;      //线型
	short m_Layer;        // 所在图层

	BOOL b_Delete;       //是否处于删除状态

	int  m_id_only;      //图形元素唯一的识别号



};

#endif // !defined(AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_)
