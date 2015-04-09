// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_)
#define AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:39
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Line.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Line
	file ext:	h
	author:		����
	
	purpose:	ֱ�����ͼ��Ԫ�ػ���CDrew����������ֱ�ߵ�һЩ����
	            ����(�����͡��߿���ɫ��ɾ����־��)��CDrew���м�
				�ж�����������ֱ�ߵ���������(��ֱ�ߵ������յ���
				��)����ֱ�����ж��塣ֱ����CLine�Ķ������£�
*********************************************************************/
class CLine : public CDraw  
{
	//ֱ����
public:
	CLine();
	CLine(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete, 
		  float X1, float X2, float Y1, float Y2);
		  
	virtual ~CLine();

public:
	//ͼ�λ��ƺ���
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	float m_X1;
	float m_x2; //ֱ�ߵ��������
	float m_Y1;
	float m_Y2; //ֱ�ߵ��յ�����

};

#endif // !defined(AFX_LINE_H__BB7BEF9F_E3C3_40FF_9A8D_2AB62AD06F7A__INCLUDED_)
