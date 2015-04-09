// Circle.h: interface for the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_)
#define AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:20
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Circle.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Circle
	file ext:	h
	author:		����
	
	purpose:	��Բ��Ķ��巽����ֱ����CPLine���ơ�Բ���˾���ͼ��Ԫ��
	�Ļ��������⣬��������ļ������������������ĺͰ뾶��Ϊ����������ʾ
	Բ�ļ�������(��ȻҲ���Բ��������ķ�������߽���Ρ�Բ��ֱ������)��
	Բ��CCircle����
*********************************************************************/
#include "Draw.h"

class CCircle : public CDraw  
{
public:
	CCircle();
	CCircle(short ColorPen, short ColorBrush, short LineWide,
		    short LineType, short Layer, int id_only, BOOL Delete,
		    float CirleX, float CircleY, float CirleR, BOOL Fill);
	virtual ~CCircle();

public:
	//ͼ�λ��ƺ���
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	float m_CircleX;
	float m_CircleY;
	float m_CirleR; //��¼Բ�����꼰�뾶�ı���
	BOOL b_Fill;   //��ʾ�Ƿ���䣬1--Բ������0---��ͨԲ
};

#endif // !defined(AFX_CIRCLE_H__5FE446FF_DCDC_4C3E_9043_90D130627AE6__INCLUDED_)
