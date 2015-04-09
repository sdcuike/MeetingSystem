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
	m_TextLong=Text.GetLength();//�����ַ�����
	c_Text=Text;

}

CText::~CText()
{

}

void CText::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//���л��Ʋ������麯��
	if (b_Delete)			//���ͼ��Ԫ�ش���ɾ��״̬�������˳�
	{
		return;
	}
	
	short ColorPen=m_ColorPen;
	if (m_DrwaMode1==2)		//���ָ����ɫ���ƣ�����ɫ����Ϊ����BackColorָ������ɫ��
	{
		ColorPen=BackColor;
	}

	CFont cjcf;      //����һ����ģ
	int high,wide,cc1,cc2,cd,angg;
	unsigned char c1,c2;
	float x1,y1,ang1;

	char hz[4];
	const char *ls1;

	if (m_DrwaMode==0)	//������õ�0�ֻ���ģʽ
	{
		pDC->SetROP2(R2_COPYPEN); //�趨���ǵĻ���ģʽ
	}
	else if (m_DrwaMode==1)  //������õ�һ�ֻ���ģʽ
	{
		pDC->SetROP2(R2_NOT);  //���÷�д�Ļ���ģʽ
	}
	pDC->SetBkMode(TRANSPARENT);


	high=(int)m_TextHeight;
	double pi=3.14159;
	ang1=(float)(m_Angle1*pi/180); //�õ���ע����X������Ļ���

	if (high<3 || high>200)
	{
		return;   //����̫С��̫�󣬽�����ʾ
	}
	x1=m_StartX-m_TextHeight*(float)sin(ang1); //��ע����ʵ�ʺ�����
	y1=m_StartY+m_TextHeight*(float)cos(ang1); //��ע���ʵ��������

	angg=(int)(m_Angle2*10);


	wide=(int)m_TextWide;
	cc1=(int)x1;
	cc2=(int)y1;
	extern CGraphPara *p_GraphPara;

	cjcf.CreateFont(high,wide,angg,0,50,0,0,0,255,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,
					DEFAULT_QUALITY,FIXED_PITCH,"cjc"); //������ģ

	CFont *cjcbakf=pDC->SelectObject(&cjcf);          //ѡ����ģ
	pDC->SetBkMode(TRANSPARENT);                      //���û��Ʒ�ʽ
	pDC->SetTextColor(p_GraphPara->GetColor(ColorPen));  //���ñ�ע�ı���ɫ
	ls1=(const char *)c_Text; //�ַ�ָ��ls1ָ���ע�ı�������
	cd=strlen(ls1);           //��ע�ı����ַ�����
	while(cd>0)            //���Ʊ�ע�ı��������ַ�
	{
		c1=*ls1;
		c2=*(ls1+1);

		if (c1>127 && c2>127)  //�����һ���ַ���һ������
		{
			strncpy(hz,ls1,2);  //����һ�����ֵ��ַ���hz��
			hz[2]=0;
			ls1=ls1+2;         //��������ָ����һ���ַ�
			pDC->TextOut(cc1,cc2,hz);//����Ļ�ϻ����������
			cd=cd-2;     //�ַ������ȼ�2
			//��һ���ַ���ʵ����ʾλ��
			x1=x1+(m_TextWide*2+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*2+m_OffWide)*(float)sin(ang1);

			cc1=(int)x1;
			cc2=(int)y1;
		}
		else					//�����һ�������ַ�
		{
			strncpy(hz,ls1,1);  //����һ���ַ����ַ���hz��
			hz[1]=0;
			ls1++;				 //ָ���ַ����е���һ���ַ�
			pDC->TextOut(cc1,cc2,hz); //����Ļ�ϻ����ַ�
			cd=cd-1;			 //�ַ������ȼ�1
		
			//��һ���ַ���ʾλ�õ�ʵ������
			x1=x1+(m_TextWide+m_OffWide/2)*(float)cos(ang1);
			y1=y1+(m_TextWide+m_OffWide/2)*(float)sin(ang1);

			cc1=(int)x1;
			cc2=(int)y1;
		}
	}

	pDC->SelectObject(cjcbakf);		//�ָ���ģ

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
