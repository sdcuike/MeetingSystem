// PLine.cpp: implementation of the CPLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "PLine.h"
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

CPLine::CPLine()
{
	m_Numble=0;
}

CPLine::CPLine( short ColorPen, short ColorBrush, short LineWide, 
			   short LineType, short Layer, int id_only, BOOL Delete,
			   int Numble, PontStruct *PointList, BOOL Fill )
 :CDraw(ColorPen,ColorBrush,LineWide,LineType,Layer,id_only,Delete)
{
	m_Numble=Numble;
	b_Fill=Fill;

	m_PiontList=new PontStruct[m_Numble+1];//��̬����洢��������Ľṹ����

	if (m_Numble>0)
	{
		for (int i=0; i<m_Numble; ++i )
		{
			m_PiontList[i]=PointList[i];
		}
	}
}

CPLine::~CPLine()
{
	if (m_Numble>0)
	{
		delete m_PiontList;
	}
}

void CPLine::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	//ͼ�λ��ƺ���
	
	if (b_Delete)		//����Ѿ�����ɾ��״̬
	{
		return;
	}

	short LineType=m_LineType;
	short ColorPen=m_ColorPen;
	short ColorBrush=m_ColorBrush;
	if (m_DrwaMode1==1)	//���ͼ��Ԫ����Ҫ������ʾ
	{
		if (m_LineType!=2)//���ͼ��Ԫ�ز��õĲ��ǵڶ������ͣ����ߣ�������õڶ�������
		{
			LineType=2;
		}
		else			//���ͼ��Ԫ�ز��õ��ǵڶ������ͣ����ߣ�������õ���������
		{
			++LineType;
		}
	}
	else if (m_DrwaMode1==2)//�����Ҫ��ָ����ɫ��������ֱ�߻���������
							//����ɫ�����ɫ������Ļ��ɫBackColor
	{	
		ColorPen=BackColor;
		ColorBrush=BackColor;
	}

	//��������ʼ��һ��CPen����
	extern CGraphPara *p_GraphPara;
	CPen pen((int)LineType, (int)m_LineWide, p_GraphPara->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush brush(p_GraphPara->GetColor(m_ColorBrush));
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	
	POINT *ppoint;
	CRgn rgn;
	if(m_DrwaMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if( m_DrwaMode==1)
		pDC->SetROP2(R2_NOT);
	ppoint=new POINT[m_Numble+1];
	for (int i=0; i<m_Numble; ++i)
	{
		ppoint[i].x=(long)m_PiontList[i].x;
		ppoint[i].y=(long)m_PiontList[i].y;
	}

	if (!b_Fill)		// ���������ֱ�ߣ������λ��Ƹ����߶�
	{
		ppoint[m_Numble]=ppoint[0];
		pDC->MoveTo(ppoint[0].x, ppoint[0].y);
		for (i=0; i<m_Numble; ++i)
		{
			pDC->LineTo(ppoint[i].x, ppoint[i].y);
		}
	}
	else			//����Ƕ����
	{
		if (m_DrwaMode1==0 || m_DrwaMode1==2)  //�����������ʾ
		{
			pDC->Polyline(ppoint,m_Numble);
		}
		else if (m_DrwaMode1==1)      //����Ƿ�ɫ��ʾ
		{
			rgn.CreatePolygonRgn(ppoint,m_Numble,0);  //����һ��CRgn����
			pDC->InvertRgn(&rgn);		//��CRgn����ȷ��������ɫ��ʾ
		}

	}

	delete ppoint;			//ɾ����̬����Ľṹ����
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}