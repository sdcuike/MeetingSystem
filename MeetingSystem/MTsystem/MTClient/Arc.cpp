// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Arc.h"
#include "GraphPara.h"
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CArc::CArc()
{

}

CArc::CArc( short ColorPen, short ColorBrush, short LineWide, 
		   short LineType, short Layer, int id_only, BOOL Delete, 
		   float CirleX, float CircleY, float CirleR, BOOL Fill, 
		   float Angle1, float Angle2 )
		   :CCircle(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete,
		   CirleX,CircleY,CirleR,Fill)
{
	m_Anglel=Angle1;
	m_Angle2=Angle2;
}

CArc::~CArc()
{

}

void CArc::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//���л��Ʋ������麯��
	if(b_Delete)		//���ͼ��Ԫ�ش���ɾ��״̬�������˳�
		return;
	int x,y,rr;
	int x1,x2,y1,y2;
	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	if (m_DrwaMode1==1)		//���ͼ��Ԫ����Ҫ������ʾ
	{
		if (m_LineType!=2)	//���ͼ��Ԫ�ز��õĲ��ǵڶ������ͣ����ߣ�������õڶ�������
		{
			LineType=2;
		}
		else				//���ͼ��Ԫ�ز��õ��ǵڶ������ͣ����ߣ�������õ���������
		{
			++LineType;
		}

	}
	else if (m_DrwaMode1==2) //�����Ҫ��ָ������ɫ����Բ��
	{
		ColorPen=BackColor;
	}
	
	extern  CGraphPara *p_GraphPara;

	CPen pen((int)LineType, (int)m_LineWide, p_GraphPara->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);
	if (m_DrwaMode==0)		//������õ�0�ֻ���ģʽ
	{
		pDC->SetROP2(R2_COPYPEN); //�趨���ǵĻ���ģʽ
	}
	else if (m_DrwaMode==1)
	{
		pDC->SetROP2(R2_NOT);
	}

	x=(int)m_CircleX;
	y=(int)m_CircleY;
	rr=(int)m_CirleR;

	//���¼���Բ����������
	x1=(int)(x+m_CirleR*cos(m_Anglel) );
	y1=(int)(y-m_CirleR*sin(m_Anglel) );
	//���µõ�Բ���յ������
	x2=(int)(x+m_CirleR*cos(m_Angle2) );
	y2=(int)(y-m_CirleR*sin(m_Angle2) );

	pDC->Arc(x-rr,y-rr,x+rr,y+rr,x1,y1,x2,y2);  //����Բ

	pDC->SelectObject(pOldPen);  //�ָ�ԭ���Ļ���

}

void CArc::Init( short ColorPen, short ColorBrush, short LineWinde, short LineType, short Layer, BOOL Delete, float CircleX,float CircleY,float CircleR, BOOL Fill, float Angle1, float Angle2 )
{
	//Բ�������Ա������ʼ��
	m_ColorPen=ColorPen;
	m_ColorBrush=ColorBrush;
	m_LineWide=LineWinde;
	m_LineType=LineType;
	m_Layer=Layer;
	m_CircleX=CircleX;
	m_CircleY=CircleY;
	m_CirleR=CircleR;
	b_Fill=Fill;
	m_Anglel=Angle1;
	m_Angle2=Angle2;
	b_Delete=Delete;


}


