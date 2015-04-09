// Circle.cpp: implementation of the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Circle.h"
#include "GraphPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{

}

CCircle::CCircle( short ColorPen, short ColorBrush, short LineWide, 
				 short LineType, short Layer, int id_only, BOOL Delete,
				 float CirleX, float CircleY, float CirleR, BOOL Fill )
 :CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_CircleX=CirleX;
	m_CircleY=CircleY;
	m_CirleR=CirleR;
	b_Fill=Fill;
}

CCircle::~CCircle()
{

}

void CCircle::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//ͼ�λ��ƺ���
	if (b_Delete)		//���ͼ��Ԫ�ض�����ɾ��״̬�������˳�
	{
		return;
	}
	int x,y,r;
	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	short ColorBrush=m_ColorBrush;
	if (m_DrwaMode1==1)			//���ͼ��Ԫ����Ҫ������ʾ
	{
		if (m_LineType!=2)		//���ͼ��Ԫ�����õĲ��ǵڶ������ͣ����ߣ�������õڶ�������
		{
			LineType=2;
		} 
		else					//���ͼ��Ԫ�ز��õ��ǵڶ������ͣ����ߣ�������õ���������
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)		//�����Ҫ��ָ����ɫ����Բ��Բ�����򣬽���ɫ�����ɫ
										//����Ϊ��Ļ��ɫBackColor
	{
		ColorPen=BackColor;
		ColorBrush=BackColor;
	}

		//��������ʼ��һ��CPen����

		extern CGraphPara *p_GraphPara;
		CPen pen((int)LineType, (int)m_LineWide,p_GraphPara->GetColor(ColorPen ));
		CPen *pOldPen=pDC->SelectObject(&pen);
		CBrush brush(p_GraphPara->GetColor(m_ColorBrush));
		CBrush *pOldBrush=pDC->SelectObject(&brush);
		if (m_DrwaMode==0)			//������õ�0�ֻ���ģʽ
		{
			pDC->SetROP2(R2_COPYPEN); //�趨����ģʽ
		}
		else if (m_DrwaMode==1)		//������õ�1�ֻ���ģʽ
		{
			pDC->SetROP2(R2_NOT);  //���÷�д�Ļ���ģʽ
		}

		if (!b_Fill)				//�������ͨԲ�����ò����ģʽ
		{
			pDC->SelectStockObject(NULL_BRUSH);
		}

		x=(int)m_CircleX;
		y=(int)m_CircleY;
		r=(int)m_CirleR;
		pDC->Ellipse(x-r,y-r,x+r,y+r);  //����Բ
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
