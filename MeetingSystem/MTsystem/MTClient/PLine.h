// PLine.h: interface for the CPLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_)
#define AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:58
	filename: 	F:\MeetingSystem\MTsystem\MTClient\PLine.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	PLine
	file ext:	h
	author:		����
	
	purpose:	����ֱ�߳��˾���ͼ��Ԫ�ػ���CDraw�����е������⣬��ͼ
	�εļ��������ϣ�����ֱ�����ɺܶඥ����ɵģ��������Ŀ�ǲ�ȷ���ģ�
	��һ������ֱ����˵����ֻ�ж������㣬Ҳ�����м�ǧ�����㡣�����Ҫ
	����һ�����µĽṹ���洢����ֱ�ߵ�һ���������꣨���£���
	Ϊ�˽�ʡ�洢�ռ䣬��������ֱ�ߵĶ������꣬���ö�̬����洢�ռ��
	����������������ֱ�ߵĶ�����Ŀ����CPLne�����з�������ֱ�ߵĴ洢��
	�䡣����ֱ�߻������ඨ�����£�
*********************************************************************/
#include "Draw.h"
typedef struct
{
	float x; //����ĺ�����
	float y; //�����������
	float z;
}PontStruct;  //�洢ÿ����������Ľṹ

class CPLine : public CDraw  
{
	//����ֱ�߻�������,��������������
public:
	CPLine();
	CPLine(short ColorPen, short ColorBrush, short LineWide,
		   short LineType, short Layer, int id_only, BOOL Delete,
		  int Numble, PontStruct *PointList, BOOL Fill);
	virtual ~CPLine();

public:
	//ͼ�λ��ƺ���
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor);
protected:
	int m_Numble; //����ֱ�߻���������Ķ�����Ŀ
	BOOL b_Fill;  //��ʾ�Ƿ���䣬1--���������0--����ֱ��
	PontStruct* m_PiontList; //�洢�������������ָ��

};

#endif // !defined(AFX_PLINE_H__CAA6FBC7_10D8_40B5_BFF3_5E5DAD5FCFE0__INCLUDED_)
