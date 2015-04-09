// Draw.h: interface for the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_)
#define AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/25
	created:	25:4:2010   17:15
	filename: 	F:\MeetingSystem\MTsystem\MTClient\Draw.h
	file path:	F:\MeetingSystem\MTsystem\MTClient
	file base:	Draw
	file ext:	h
	author:		����
	
	purpose:	�Ը���ͼ��Ԫ�ؽ��з��������Է��ָ���ͼ��Ԫ�ؾ���һЩ
	��ͬ�����ԺͲ������ܣ���ͼ��Ԫ�ص���ɫ�����͡��߿�����Ժ͵õ�һ
	��ͼ��Ԫ���Ƿ�����ɾ����־�Ȳ���������Щͼ��Ԫ���й��ԵĶ���(����
	�Ͳ���)��֯�����һ��ͼ��Ԫ�ػ����У������ͼ��Ԫ�����������������
	�����������£�
*********************************************************************/
class CDraw :public CObject
{
	//ͼ��Ԫ�ػ��࣬���ڴ洢ͼ�ε���ɫ�����Ե���Ϣ
public:
	CDraw();
	CDraw(short ColorPen, short ColorBrush, short LineWide,
		  short LineType, short Layer, int id_only, BOOL Delete);
	
	virtual ~CDraw();

public:

	//���л��Ʋ������麯��
	virtual void Draw(CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor)=0;
	int GetID();  //�õ�һ��ͼ��Ԫ�ض����ʶ���--m_id_only
protected:
	short m_ColorPen;      //��ɫ
	short m_ColorBrush;    //�����ɫ
	short m_LineWide;      //�߿�(����)
	short m_LineType;      //����
	short m_Layer;        // ����ͼ��

	BOOL b_Delete;       //�Ƿ���ɾ��״̬

	int  m_id_only;      //ͼ��Ԫ��Ψһ��ʶ���



};

#endif // !defined(AFX_DRAW_H__26370BD0_E776_41FA_AE0D_AC043F3A2C10__INCLUDED_)
