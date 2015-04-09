// ChatClientDoc.h : interface of the CChatClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
#define AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "message.h"
#include "Line.h"
#include "PLine.h"
#include "Text.h"
#include "Circle.h"
#include "Arc.h"
#include "GraphPara.h"
class CChatSocket;
/********************************************************************
	created:	2010/04/15
	created:	15:4:2010   18:47
	filename: 	F:\MeetingSystem\MTClient\ChatClientDoc.h
	file path:	F:\MeetingSystem\MTClient
	file base:	ChatClientDoc
	file ext:	h
	author:		����
	
	purpose:	�������ݵĽ��պͷ��ͣ��Լ��׽���ͨ�ŵĳ�ʼ����
*********************************************************************/
class CChatClientDoc : public CRichEditDoc
{
protected: // create from serialization only
	CChatClientDoc();
	DECLARE_DYNCREATE(CChatClientDoc)

// Attributes
public:
	CMessage msg;
	int *m_Index;
	int GetGraphID(short Lb);//�����õ�Ҫ���ӵĸ���ͼ��Ԫ�ص�Ψһʶ���
private:
	CTypedPtrArray<CObArray,CLine*>   m_LineArray;	//����ֱ�߶���ָ��
	CTypedPtrArray<CObArray,CPLine*>   m_PLineArray;	//��������ֱ�߶���ָ��Ķ���
	CTypedPtrArray<CObArray,CCircle*>   m_CircleArray;//����Բ����ָ��Ķ���
	CTypedPtrArray<CObArray,CArc*>    m_ArcArray;		//����Բ������ָ��Ķ���
	CTypedPtrArray<CObArray,CText*>   m_TextArray;	//�����ע���ֶ���ָ��Ķ���

protected:
	CGraphPara m_GraphPara;   //�������һ��Բ�β����Ķ���

// Operations
public:

 /*����������ֱ�����ʵ������һ��ֱ�ߡ�һ������ֱ�߻��ն��������
 һ��Բ��Բ�����ǡ�һ��Բ����һ����ע�ı��ȵĹ��ܡ���������ָ������
 ͼ��Ԫ�ض����ָ�롣

 */
	CLine* AddLine(short ColorPen, short ColorBrush, short LineWide,
	               short LineType, short Layer, int id_only, float X1, 
				   float X2, float Y1, float Y2);
	CPLine* AddPline(short ColorPen, short ColorBrush, short LineWide,
		             short LineType, short Layer, int id_only,int Numble,
					 PontStruct *PointList, BOOL Fill);
	CCircle* AddCicle(short ColorPen, short ColorBrush, short LineWide,
		              short LineType, short Layer, int id_only,
		              float CirleX, float CircleY, float CirleR, BOOL Fill);
    CArc*  AddArc(short ColorPen, short ColorBrush, short LineWide,
		          short LineType, short Layer, int id_only,float CirleX,
				  float CircleY, float CirleR, BOOL Fill,float Angle1,
				  float Angle2);
	CText* AddText(short ColorPen, short ColorBrush, short LineWide,
		           short LineType, short Layer, int id_only,float StartX, 
				   float StartY, float Angle1, float Angle2,float TextHeight,
				   float TextWinde, float OffWide,unsigned char TextFont,int TextLong,
				   CString Text);

	/************************************************************************/
	/*���ָ��ĳ��ͼ��Ԫ�ض����CDraw��ָ�롣����Lb������ʾҪ���ص�ͼ�����:
	1һֱ��.2-����ֱ�߻���������3-~Բ��Բ������4��Բ����5-��ע�ı���
	����Index��Ҫ�õ���ͼ��Ԫ�Ҷ���ָ������ӦCObArray�����е�0�����(������±�)                                                                      */
	/************************************************************************/
	CDraw* GetGraph(short Lb, int Index);

	void DeleteGraph(short Lb, int Index);  //��CObArray������ɾ��һ��ָ��ͼ��Ԫ�ض���ָ��

	int GetGraphNumb(short Lb);   //�õ��ĵ��и���ͼ��Ԫ�ض������Ŀ

	int GerGraphUpperBound(short Lb );//�õ��洢�ڸ���CObArray�����е���������±�
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	void Disconnect();
	BOOL m_bFilter;//��ʶ�Ƿ�������Ϣ
	void ReceiveMsg();
	void SendMsg();
	BOOL ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress, LPCTSTR m_strImage, UINT nPort);
	void ProcessPendingRead();
	BOOL m_bConnected;//��ʶ�׽����Ƿ��Ѿ����ӡ�
	virtual ~CChatClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CChatSocket* m_pSocket; //�ͻ��׽��ֶ���
	CSocketFile* m_pFile; //�׽����ļ�����
	CArchive* m_pArchiveIn; //�׽��ֹ鵵����
	CArchive* m_pArchiveOut; //�׽��ֹ鵵����

	CString  m_strHandle; //�û����õ�����ƺ����ñ������û�ָ��
	void talk(int type, CString from, CString to, CString str,COLORREF clr);
	void DisplayRecMsg(int type, CString from, CString to,BOOL sec, CString str, COLORREF clr);
	void DisplayMsg(LPCTSTR lpszText);
	void DisplayWhiteBoardMsg(CPoint ptdown, CPoint pudown);
// Generated message map functions
protected:
	//{{AFX_MSG(CChatClientDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDOC_H__D98CD206_1703_4132_8F85_BEFFFBC9BD41__INCLUDED_)
