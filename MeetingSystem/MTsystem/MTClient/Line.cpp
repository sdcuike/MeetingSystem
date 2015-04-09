// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Line.h"
#include "GraphPara.h"
#include <afxwin.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{

}

CLine::CLine( short ColorPen, short ColorBrush, short LineWide, short LineType, 
			 short Layer, int id_only, BOOL Delete, float X1, float X2, 
			 float Y1, float Y2 )
:CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_X1=X1;
	m_x2=X2;
	m_Y1=Y1;
	m_Y2=Y2;

}

CLine::~CLine()
{

}

void CLine::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//ͼ�λ��ƺ���
	int x1;
	int y1;
	int x2;
	int y2;

	if (b_Delete)			//���ͼ�δ���ɾ��״̬���˳�����
	{
		return;
	}

	short LineType=m_LineType;
	short ColorPen=m_ColorPen;

	if (m_DrwaMode1==1)			//���ͼ��Ԫ����Ҫ������ʾ
	{
		if (m_LineType!=2)		//���ͼ��Ԫ�ز��õĲ��ǵڶ������ԣ����ߣ�������õڶ�������
		{
			LineType=2;
		} 
		else					//���ͼ��Ԫ�ز��õ��ǵڶ������ԣ����ߣ�,����õ���������
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)	//�����Ҫ����ָ����ɫ���ƣ�����ɫ����Ϊ��Ļ��ɫBackColor
	{
		ColorPen=BackColor;
	}

	//��������ʼ��һ��CPen����

	extern CGraphPara *p_GraphPara;
	CPen pen((int)LineType, (int)m_LineWide,p_GraphPara->GetColor(ColorPen) );
	CPen *pOldPen=pDC->SelectObject(&pen);	//�ڻ�ͼ������ѡ��CPen����
	if (m_DrwaMode==0)						//������õ�0�л�ͼģʽ
	{
		pDC->SetROP2(R2_COPYPEN);			//�趨���ǵĻ���ģʽ
	}
	else if (m_DrwaMode==1)					//������õ�һ�ֻ���ģʽ
	{	
		pDC->SetROP2(R2_NOT);
	}



	x1=(int)m_X1;
	x2=(int)m_x2;
	y1=(int)m_Y1;
	y2=(int)m_Y2;


	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);						//����ֱ��
	pDC->SelectObject(pOldPen);				//�ָ�ԭ���Ļ���
}
