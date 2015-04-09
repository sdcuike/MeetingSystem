// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatSrvr.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");

	
	m_ColorPen=0.0;      //��ɫ
	m_ColorBrush=0.0;    //�����ɫ
	m_LineWide=0.0;      //�߿�(����)
	m_LineType=0.0;      //����
	m_Layer=0.0;        // ����ͼ��
	
   	b_Delete=FALSE;       //�Ƿ���ɾ��״̬
	
	m_id_only=0;      //ͼ��Ԫ��Ψһ��ʶ���
	
	
	//////�������������ݳ�Ա/////////////
	
    m_DrawCurrent=100;   //���������������������
    m_PointNumber=0; //һ�δ��伸����
	
	//---����ֱ�߻����Σ������������ߵ��������ݳ�Ա
	b_Fill=FALSE;  //��ʾ�Ƿ���䣬1--���������0--����ֱ�߻�����������
}

CMessage::~CMessage()
{
}

void CMessage::Serialize(CArchive &ar)
{
	
	if (ar.IsStoring()){
		ar << type;
		ar << (WORD)m_bClose;
		ar << m_strText;
		ar << (WORD)secret;
		ar << from;
		ar << to;
		ar << (DWORD)color;
		ar << image;
		
		ar<<m_ColorPen;
		ar<<m_ColorBrush;
		ar<<m_LineWide;
		ar<<m_LineType;
		ar<<m_Layer;
		ar<<b_Delete;
		ar<<m_id_only;
		
		ar<<m_DrawCurrent;
		ar<<m_PointNumber;
		ar<<b_Fill;
		for (int i=0;i<m_PointNumber;++i)
		{
			ar<<m_HvaePN[i];
		}


		ar<<m_byRed; //��ǰ��ͼ�������ɫ,�����ʻ�ˢ����ɫ
		ar<<m_byGreen;
		ar<<m_byBlue;
		ar<<m_nPenWide; //���ʴ�ϸ
	    ar<<m_nBrushStye; //��ˢ������
	}
	else{
		WORD wd;
		DWORD dwTmp;
		
		ar >> type;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
		ar >> wd;
		secret = (BOOL)wd;
		ar >> from;
		ar >> to;
		ar >> dwTmp;
		color = (COLORREF)dwTmp;
		ar >> image;
		
		
		ar>>m_ColorPen;
		ar>>m_ColorBrush;
		ar>>m_LineWide;
		ar>>m_LineType;
		ar>>m_Layer;
		ar>>b_Delete;
		ar>>m_id_only;
		
		
		ar>>m_DrawCurrent;
		ar>>m_PointNumber;
		ar>>b_Fill;
		for (int i=0;i<m_PointNumber;++i)
		{
			ar>>m_HvaePN[i];
		}


		ar>>m_byRed; //��ǰ��ͼ�������ɫ,�����ʻ�ˢ����ɫ
		ar>>m_byGreen;
		ar>>m_byBlue;
		ar>>m_nPenWide; //���ʴ�ϸ
	    ar>>m_nBrushStye; //��ˢ������
	}
}

void CMessage::Reset()
{
	image = 6;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");

	
	
	m_ColorPen=0.0;      //��ɫ
	m_ColorBrush=0.0;    //�����ɫ
	m_LineWide=0.0;      //�߿�(����)
	m_LineType=0.0;      //����
	m_Layer=0.0;        // ����ͼ��
	
   	b_Delete=FALSE;       //�Ƿ���ɾ��״̬
	
	m_id_only=0;      //ͼ��Ԫ��Ψһ��ʶ���
	
	
	//////�������������ݳ�Ա/////////////
	
    m_DrawCurrent=100;   //���������������������
    m_PointNumber=0; //һ�δ��伸����
	
	//---����ֱ�߻����Σ������������ߵ��������ݳ�Ա
	b_Fill=FALSE;  //��ʾ�Ƿ���䣬1--���������0--����ֱ�߻�����������
}
