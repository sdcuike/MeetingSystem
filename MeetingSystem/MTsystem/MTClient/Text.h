// Text.h: interface for the CText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_)
#define AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:58
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Text.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Text
	file ext:	h
	author:		风云
	
	purpose:	图形中可以有大量的标注文本，标注文本除了具有图形元素
	的基本特征外，还具有位置、宇体及标注内容等自身的信息。定义标注文
	本类Ctext如下
*********************************************************************/
#include "Draw.h"

class CText : public CDraw  
{
public:
	CText();
	CText(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete,
		  float StartX, float StartY, float Angle1, float Angle2,
		  float TextHeight, float TextWinde, float OffWide, 
		  unsigned char TextFont ,int TextLong, CString Text);

	virtual ~CText();

public:
	//进行绘制操作的虚函数
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);

	void Init(short ColorPen,short ColorBrush,short LineWide,short LineType,
		      short Layer,float StartX,float StartY,float Angle1,float Angle2,
			  float TextHeight,float TextWide,float OffWide,unsigned char TextFont,
			  CString Text);
protected:
	float m_StartX;//标注文本起点横坐标
	float  m_StartY;//标注文本起点纵坐标

	float m_Angle1; //标注角度
	float m_Angle2; //字体旋转角度
	float m_TextHeight;//字体高度
	float m_TextWide; //字体宽度
	float m_OffWide; //字体标注间隔

	unsigned char m_TextFont; //字体
	CString c_Text; //标注文本内容
	int m_TextLong;   //标注文本的字符长度


};

#endif // !defined(AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_)
