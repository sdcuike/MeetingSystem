// GraphPara.cpp: implementation of the CGraphPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cstring>
#include "chatclient.h"
#include "GraphPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphPara::CGraphPara()
{
	n_ColorNumb=100; //������100����ɫ
	n_LayerNumb=100; //������100��
	m_ColrList=new long[n_ColorNumb];
	m_LayerList=new LayerStruct[n_LayerNumb];

	n_ColorNumb=4; //��ǰ��������ɫ
	n_LayerNumb=1; //��ǰ��һ��ͼ��

	//���³�ʼ����ɫ��ͼ��
	m_ColrList[0]=RGB(0,0,0);
	m_ColrList[1]=RGB(255,0,0);
	m_ColrList[2]=RGB(0,255,0);
	m_ColrList[3]=RGB(0,0,255);
	m_LayerList[0].b_Display=1;

	strcpy(m_LayerList[0].m_Name,"Layer0");

}

CGraphPara::~CGraphPara()
{
	delete m_LayerList;
	delete m_ColrList;
}

COLORREF CGraphPara::GetColor( int n )
{
	return m_ColrList[n];//���ص�n����ɫֵ
}

BOOL CGraphPara::GetDisplayState( int n )
{
	return m_LayerList[n].b_Display; //���ص�n��ͼ�����ʾ״̬
}
