// Text.h: interface for the CText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_)
#define AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   18:58
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Text.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Text
	file ext:	h
	author:		����
	
	purpose:	ͼ���п����д����ı�ע�ı�����ע�ı����˾���ͼ��Ԫ��
	�Ļ��������⣬������λ�á����弰��ע���ݵ��������Ϣ�������ע��
	����Ctext����
*********************************************************************/
#include "Draw.h"

class CText : public CDraw  
{
public:
	CText();
	CText(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete,
		  float StartX, float StartY, float Angle1, float Angle2,
		  float TextHeight, float TextWinde, float OffWide, 
		  unsigned char TextFont ,int TextLong, CString Text);

	virtual ~CText();

public:
	//���л��Ʋ������麯��
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);

	void Init(short ColorPen,short ColorBrush,short LineWide,short LineType,
		      short Layer,float StartX,float StartY,float Angle1,float Angle2,
			  float TextHeight,float TextWide,float OffWide,unsigned char TextFont,
			  CString Text);
protected:
	float m_StartX;//��ע�ı���������
	float  m_StartY;//��ע�ı����������

	float m_Angle1; //��ע�Ƕ�
	float m_Angle2; //������ת�Ƕ�
	float m_TextHeight;//����߶�
	float m_TextWide; //������
	float m_OffWide; //�����ע���

	unsigned char m_TextFont; //����
	CString c_Text; //��ע�ı�����
	int m_TextLong;   //��ע�ı����ַ�����


};

#endif // !defined(AFX_TEXT_H__F77748BB_5F03_4A97_8607_CB807E745794__INCLUDED_)
