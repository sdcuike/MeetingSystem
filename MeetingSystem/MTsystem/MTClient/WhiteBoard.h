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


	//以下为当前绘图对象的一些参数
	COLORREF  m_clorDraw; //当前绘图对象的颜色,即画笔或画刷的颜色
	int m_nPenWide; //画笔粗细
	int m_nBrushStye; //画刷的类型
    
	//////////////////////////////////////////////////////////////////////////
	CPoint m_TotalPointNum[10]; //用于一次传输的最多点的数组

// Dialog Data
	//{{AFX_DATA(CWhiteBoard)
	enum { IDD = IDD_DIgWhiteborad };
	CRichEditCtrl	m_displaySCLOR;
	CColorPicker	m_colorDraw;  //选择颜色调色板按钮控件对应变量
	CEdit	m_editclor;//与m_btnColor组合，显示当前选择的颜色,他们合起来
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
		CPoint mPointOrign,mPointOrign1,mPointOld; //记录鼠标移动是的鼠标点的坐标
		short m_pColor;   //当前画笔颜色的序号
		short m_bColor;   //当前屏幕颜色的序号
		short m_brColor;  //当前画刷颜色的序号
		short m_LineType;  //当前线型
		short m_LineWide;  //当前直线宽度（像素）
		short m_Layer; //当前图层

		float m_CircleX,m_CircleY,m_CircleR,m_Angle1,m_Angle2;
		CArc m_Arc1;      //定义一个圆弧类指针
		BOOL DrawArcYes;

public:
	void Display();

protected:
    
	int m_DrwaCurrent; //用来记录现在的操作类别
	int PushNumb;      //用来记录按下鼠标左键的次数
	PontStruct  *PointXyz;

	CTextWriteDlg *pTextDlg;  //标注文本的对话框类指针
	float m_FontHeight,m_FontWide,m_FontBetween,m_TextAngle,m_FontAngle;
	float m_TextX,m_TextY; //标注文本的起点位置
	CString m_TextString;  //存储标注文本的字符串
	CText *m_Text1;  //定义一个标注文本类指针
	

/*计算得到由三点（p1,p2,p3）确定的圆弧的几何要素，通过指针变量返回圆弧的圆心（*CircleX，
 * *CircleY）、半径（*CircleR）和起终弧度（*Angle1,*Angle2),计算成功时函数返回TRUE,否则
 * 返回FALSE。
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
	afx_msg void DrawText();//在对话框编辑框中内容变化时被调用，在屏幕上绘制文本
	afx_msg void DrawTextOnOk();//按“确定"按钮退出标注文本对话框时被调用
	afx_msg void DrawTextOnCancel();//按“放弃”按钮退出标注文本对话框时被调用
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
