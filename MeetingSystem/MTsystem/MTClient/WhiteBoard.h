#if !defined(AFX_WHITEBOARD_H__036D1F43_9180_49C0_9F27_C8BC81B0102D__INCLUDED_)
#define AFX_WHITEBOARD_H__036D1F43_9180_49C0_9F27_C8BC81B0102D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WhiteBoard.h : header file
//
#include "ColorPicker.h"
#include "PLine.h"
#include "Arc.h"


/////////////////////////////////////////////////////////////////////////////
// CWhiteBoard dialog
class CText;
class CTextWriteDlg;

class CWhiteBoard : public CDialog
{
// Construction
public:
	CWhiteBoard(CWnd* pParent = NULL);   // standard constructor

	virtual ~CWhiteBoard();


	//����Ϊ��ǰ��ͼ�����һЩ����
	COLORREF  m_clorDraw; //��ǰ��ͼ�������ɫ,�����ʻ�ˢ����ɫ
	int m_nPenWide; //���ʴ�ϸ
	int m_nBrushStye; //��ˢ������
    
	//////////////////////////////////////////////////////////////////////////
	CPoint m_TotalPointNum[10]; //����һ�δ�������������

// Dialog Data
	//{{AFX_DATA(CWhiteBoard)
	enum { IDD = IDD_DIgWhiteborad };
	CRichEditCtrl	m_displaySCLOR;
	CColorPicker	m_colorDraw;  //ѡ����ɫ��ɫ�尴ť�ؼ���Ӧ����
	CEdit	m_editclor;//��m_btnColor��ϣ���ʾ��ǰѡ�����ɫ,���Ǻ�����
	//}}AFX_DATA
   
	     
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhiteBoard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation

private:
		CPoint mPointOrign,mPointOrign1,mPointOld; //��¼����ƶ��ǵ����������
		short m_pColor;   //��ǰ������ɫ�����
		short m_bColor;   //��ǰ��Ļ��ɫ�����
		short m_brColor;  //��ǰ��ˢ��ɫ�����
		short m_LineType;  //��ǰ����
		short m_LineWide;  //��ǰֱ�߿�ȣ����أ�
		short m_Layer; //��ǰͼ��

		float m_CircleX,m_CircleY,m_CircleR,m_Angle1,m_Angle2;
		CArc m_Arc1;      //����һ��Բ����ָ��
		BOOL DrawArcYes;

public:
	void Display();

protected:
    
	int m_DrwaCurrent; //������¼���ڵĲ������
	int PushNumb;      //������¼�����������Ĵ���
	PontStruct  *PointXyz;

	CTextWriteDlg *pTextDlg;  //��ע�ı��ĶԻ�����ָ��
	float m_FontHeight,m_FontWide,m_FontBetween,m_TextAngle,m_FontAngle;
	float m_TextX,m_TextY; //��ע�ı������λ��
	CString m_TextString;  //�洢��ע�ı����ַ���
	CText *m_Text1;  //����һ����ע�ı���ָ��
	

/*����õ������㣨p1,p2,p3��ȷ����Բ���ļ���Ҫ�أ�ͨ��ָ���������Բ����Բ�ģ�*CircleX��
 * *CircleY�����뾶��*CircleR�������ջ��ȣ�*Angle1,*Angle2),����ɹ�ʱ��������TRUE,����
 * ����FALSE��
 *	
 */
	BOOL jsarc(CPoint p1,CPoint p2,CPoint p3,float *CircleX,float *CircleY,
				float *CircleR,float *Angle1, float *Angle2);




	CToolBar m_wndToolBar;
	CToolBar m_wndStyleSel;
	CStatusBar m_wndStatusBar;

	//afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	
	// Generated message map functions
	//{{AFX_MSG(CWhiteBoard)	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnwcolossel();
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPline();
	afx_msg void OnDrawRgn();
	afx_msg void OnDrawArc();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawCirclel();
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawArc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCirclel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRgn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawText(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void DrawText();//�ڶԻ���༭�������ݱ仯ʱ�����ã�����Ļ�ϻ����ı�
	afx_msg void DrawTextOnOk();//����ȷ��"��ť�˳���ע�ı��Ի���ʱ������
	afx_msg void DrawTextOnCancel();//������������ť�˳���ע�ı��Ի���ʱ������
	afx_msg void OnDrawCrcleline();
	afx_msg void OnLinewideOne();
	afx_msg void OnLinewideTwo();
	afx_msg void OnLinewideThree();
	afx_msg void OnHsVertical();
	afx_msg void OnHsSolid();
	afx_msg void OnHsHorziontal();
	afx_msg void OnHsFdiagonal();
	afx_msg void OnHsDiagcross();
	afx_msg void OnHsCross();
	afx_msg void OnHsBdiagonal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHITEBOARD_H__036D1F43_9180_49C0_9F27_C8BC81B0102D__INCLUDED_)
