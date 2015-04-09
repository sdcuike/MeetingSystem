// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
#define AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessage : public CObject  
{
public:
	void Serialize(CArchive& ar);
	CMessage();
	virtual ~CMessage();
public:
	void Reset();
	CString m_strText;
	CString from;
	CString to;

	COLORREF color;
	BOOL secret;
	BOOL m_bClose;
	int type;
	WORD image;


	
	
	
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
