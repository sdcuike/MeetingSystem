// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_)
#define AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:41
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Arc.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Arc
	file ext:	h
	author:		����
	
	  purpose:	Բ��Բ������������һ��Բ���Ļ��ȵ���2 ʱ��һ��Բ��
	  ���Կ��Դ�Բ���������õ�һ��Բ���ࣺ
*********************************************************************/
#include "Circle.h"

class CArc : public CCircle  
{
	//Բ����Ķ���
public:
	CArc();
	CArc(short ColorPen, short ColorBrush, short LineWide,
		 short LineType, short Layer, int id_only, BOOL Delete,
		 float CirleX, float CircleY, float CirleR, BOOL Fill,
		 float Angle1, float Angle2);
	virtual ~CArc();

public:
	//���л��Ʋ������麯��
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);

	void Init(short ColorPen, short ColorBrush, short LineWinde, short LineType,
		      short Layer, BOOL Delete, float CircleX,float CircleY,float CircleR,
			  BOOL Fill, float Angle1, float Angle2);//Բ�������Ա������ʼ��
protected:
	float m_Anglel;
	float m_Angle2;//Բ���������յ�Ƕ�(�û��ȱ�ʾ��

};



#endif // !defined(AFX_ARC_H__6259BD85_8BE3_49AA_B4CA_79941AC9FDE9__INCLUDED_)

