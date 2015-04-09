// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
#define AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/********************************************************************
	created:	2010/04/15
	created:	15:4:2010   18:22
	filename: 	F:\MeetingSystem\MTClient\Message.h
	file path:	F:\MeetingSystem\MTClient
	file base:	Message
	file ext:	h
	author:		����
	
	purpose:	CSocket��Ĵ��л�����ʹ�÷��ͺͽ����������ݾ�����ͨ�����ݴ�
	  �л�һ���򵥡���˷�װһ�����Դ��л�����Ϣ���Ǳ�Ҫ�ģ���������࣬��
	  Ϣ�ķ��ͺͽ���ֻ��ʹ�����������Ի��������д�ȡ�Ϳ����ˡ�������������
	  ʹ������кܺõ���չ�ԣ��������Ӧ�ó���Ҫ��ԭ���Ļ���������һЩ��Ϣ��
	  ��ô����Ա��Ҫ����ֻ�ǰ���Ӧ����Ϣ��������У����ڷ������Ϳͻ����˽�
	  ����Ӧ���ͼ��ɡ��������ϵͳ�������Ҫ����Ϣ��CMessage�Ķ�������:
*********************************************************************/
class CMessage : public CObject  
{
public:
	void Serialize(CArchive& ar);//����
	CMessage();
	virtual ~CMessage();
public:
	void Reset();        //����ʹ��Ϣ����Ĭ�ϵ�����

	CString m_strText;   //���ڴ�ſͻ�����������͵���Ϣ
	CString from;        //Ϊ��Ϣ���ͷ�������
	CString to;          //Ϊ��Ϣ�Ľ��շ�����

	COLORREF color;     //Ϊ������ɫ
	BOOL secret;        //���ڱ�ʶ��Ϣ�Ƿ�Ϊ�����Ļ���
	BOOL m_bClose;      //���ڱ�ʾ�ͻ��Ƿ��������
	int type;           //���ڱ�ʶ����
	WORD image;         //���ڱ�ʶͷ���ID


	

	
	/////////////���׵��Ӱװ�����///////////////////
	//--����Draw������
	short m_ColorPen;      //��ɫ
	short m_ColorBrush;    //�����ɫ
	short m_LineWide;      //�߿�(����)
	short m_LineType;      //����
	short m_Layer;        // ����ͼ��
	
	BOOL b_Delete;       //�Ƿ���ɾ��״̬
	
	int  m_id_only;      //ͼ��Ԫ��Ψһ��ʶ���
    
	//////�������������ݳ�Ա/////////////

	int m_DrawCurrent;   //���������������������
	int m_PointNumber; //һ�δ��伸����
	CPoint m_HvaePN[100];//�ٶ�һ�δ���ĵ㲻����100���������洫��ĵ������

	//---����ֱ�߻����Σ������������ߵ��������ݳ�Ա
	BOOL b_Fill;  //��ʾ�Ƿ���䣬1--���������0--����ֱ�߻�����������


	BYTE  m_byRed; //��ǰ��ͼ�������ɫ,�����ʻ�ˢ����ɫ
	BYTE  m_byGreen;
	BYTE  m_byBlue;
	int m_nPenWide; //���ʴ�ϸ
	int m_nBrushStye; //��ˢ������
	

};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
