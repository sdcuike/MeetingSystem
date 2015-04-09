// GraphPara.h: interface for the CGraphPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHPARA_H__D38D4020_0769_4D04_A346_0E3951DC6F2C__INCLUDED_)
#define AFX_GRAPHPARA_H__D38D4020_0769_4D04_A346_0E3951DC6F2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   19:16
	filename: 	F:\MeetingSystem\MTsystem\MTClient\GraphPara.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	GraphPara
	file ext:	h
	author:		����
	
	purpose:	�����������ͼ��Բ����CDraw�У���Ա����m_ColorPen��
	�洢��������ɫ�б�����кţ�m_Layer�д洢��Ҳ����ͼ���б��е�
	���кš����ڽ���һ��������������ɫ��ͼ��ȷ������Ϣ��ͼ�β���
	�ඨ������
*********************************************************************/
typedef struct         //�����洢ͼ�����Ϣ�ṹ
{
	char m_Name[21]; //ͼ�������
	BOOL b_Display;  //�Ƿ���ʾ��1--��ʾ��0--����
	int reserved;   //����
}LayerStruct;


class CGraphPara  
{
public:
	CGraphPara();
	COLORREF GetColor(int n);  //�õ���N����ɫ��ʵ����ɫ
	BOOL GetDisplayState(int n); //�õ���N�����ʾ״̬
	virtual ~CGraphPara();

protected:
	int n_ColorNumbAll; //�ܵ���ɫ��
	int n_LayerNumbALL; //�ܵ�ͼ����
	int n_ColorNumb;    //ϵͳ��ǰ���е���ɫ��
	int n_LayerNumb;    //ϵͳ��ǰ���е�ͼ����
	long* m_ColrList;   //�����洢��ɫ�б������
	LayerStruct* m_LayerList; //�����洢ͼ���б�Ľṹ����


};

#endif // !defined(AFX_GRAPHPARA_H__D38D4020_0769_4D04_A346_0E3951DC6F2C__INCLUDED_)
