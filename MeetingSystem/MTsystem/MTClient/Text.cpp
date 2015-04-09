// Text.cpp: implementation of the CText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "chatclient.h"
#include "Text.h"
#include "GraphPara.h"
#include <cmath>
#include "stdlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText()
{

}

CText::CText( short ColorPen, short ColorBrush, short LineWide, 
			 short LineType, short Layer, int id_only, BOOL Delete,
			 float StartX, float StartY, float Angle1, float Angle2,
			 float TextHeight, float TextWinde, float OffWide, 
			 unsigned char TextFont ,int TextLong, CString Text )
			 :CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_StartX=StartX;
	m_StartX=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWinde;
	m_OffWide=OffWide;
	m_TextLong=Text.GetLength();//计算字符长度
	c_Text=Text;

}

CText::~CText()
{

}

void CText::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//进行绘制操作的虚函数
	if (b_Delete)			//如果图形元素处于删除状态，函数退出
	{
		return;
	}
	
	short ColorPen=m_ColorPen;
	if (m_DrwaMode1==2)		//如果指定颜色绘制，将笔色设置为参数BackColor指定的颜色号
	{
		ColorPen=BackColor;
	}

	CFont cjcf;      //定义一个字模
	int high,wide,cc1,cc2,cd,angg;
	unsigned char c1,c2;
	float x1,y1,ang1;

	char hz[4];
	const char *ls1;

	if (m_DrwaMode==0)	//如果采用第0种绘制模式
	{
		pDC->SetROP2(R2_COPYPEN); //设定覆盖的绘制模式
	}
	else if (m_DrwaMode==1)  //如果采用第一种绘制模式
	{
		pDC->SetROP2(R2_NOT);  //设置反写的绘制模式
	}
	pDC->SetBkMode(TRANSPARENT);


	high=(int)m_TextHeight;
	double pi=3.14159;
	ang1=(float)(m_Angle1*pi/180); //得到标注行与X轴正向的弧度

	if (high<3 || high>200)
	{
		return;   //字体太小或太大，将不显示
	}
	x1=m_StartX-m_TextHeight*(float)sin(ang1); //标注起点的实际横坐标
	y1=m_StartY+m_TextHeight*(float)cos(ang1); //标注点的实际纵坐标

	angg=(int)(m_Angle2*10);


	wide=(int)m_TextWide;
	cc1=(int)x1;
	cc2=(int)y1;
	extern CGraphPara *p_GraphPara;

	cjcf.CreateFont(high,wide,angg,0,50,0,0,0,255,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,
					DEFAULT_QUALITY,FIXED_PITCH,"cjc"); //创建字模

	CFont *cjcbakf=pDC->SelectObject(&cjcf);          //选人字模
	pDC->SetBkMode(TRANSPARENT);                      //设置绘制方式
	pDC->SetTextColor(p_GraphPara->GetColor(ColorPen));  //设置标注文本颜色
	ls1=(const char *)c_Text; //字符指针ls1指向标注文本的内容
	cd=strlen(ls1);           //标注文本的字符长度
	while(cd>0)            //绘制标注文本的所有字符
	{
		c1=*ls1;
		c2=*(ls1+1);

		if (c1>127 && c2>127)  //如果下一个字符是一个汉字
		{
			strncpy(hz,ls1,2);  //拷贝一个汉字到字符串hz中
			hz[2]=0;
			ls1=ls1+2;         //跳过汉字指向下一个字符
			pDC->TextOut(cc1,cc2,hz);//在屏幕上绘制这个汉字
			cd=cd-2;     //字符串长度减2
			//下一个字符的实际显示位置
			x1=x1+(m_TextWide*2+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*2+m_OffWide)*(float)sin(ang1);

			cc1=(int)x1;
			cc2=(int)y1;
		}
		else					//如果是一个西文字符
		{
			strncpy(hz,ls1,1);  //拷贝一个字符到字符串hz中
			hz[1]=0;
			ls1++;				 //指向字符串中的下一个字符
			pDC->TextOut(cc1,cc2,hz); //在屏幕上绘制字符
			cd=cd-1;			 //字符串长度减1
		
			//下一个字符显示位置的实际坐标
			x1=x1+(m_TextWide+m_OffWide/2)*(float)cos(ang1);
			y1=y1+(m_TextWide+m_OffWide/2)*(float)sin(ang1);

			cc1=(int)x1;
			cc2=(int)y1;
		}
	}

	pDC->SelectObject(cjcbakf);		//恢复字模

}

void CText::Init( short ColorPen,short ColorBrush,short LineWide,short LineType, short Layer,float StartX,float StartY,float Angle1,float Angle2, float TextHeight,float TextWide,float OffWide,unsigned char TextFont, CString Text )
{
	m_ColorPen=ColorPen;
	m_ColorBrush=ColorBrush;
	m_LineType=LineType;
	m_LineWide=LineWide;
	m_Layer=Layer;
	m_StartX=StartX;
	m_StartY=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWide;
	m_OffWide=OffWide;
	m_TextLong=c_Text.GetLength();
	m_TextFont=TextFont;
	c_Text=Text;
}
