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


	
	
	
	/////////////简易电子白板数据///////////////////
	//--基类Draw的数据
	short m_ColorPen;      //颜色
	short m_ColorBrush;    //填充颜色
	short m_LineWide;      //线宽(像素)
	short m_LineType;      //线型
	short m_Layer;        // 所在图层
	
	BOOL b_Delete;       //是否处于删除状态
	
	int  m_id_only;      //图形元素唯一的识别号
    
	//////派生类特有数据成员/////////////
	
	int m_DrawCurrent;   //用于区别传输的是哪类线条
	int m_PointNumber; //一次传输几个点
	CPoint m_HvaePN[100];//假定一次传输的点不超过100，用来保存传输的点的坐标
	
	//---连续直线或多边形，及任意曲边线的特有数据成员
	BOOL b_Fill;  //表示是否填充，1--多边形区域，0--连续直线或任意曲线条



	BYTE  m_byRed; //当前绘图对象的颜色,即画笔或画刷的颜色
	BYTE  m_byGreen;
	BYTE  m_byBlue;
	int m_nPenWide; //画笔粗细
	int m_nBrushStye; //画刷的类型
};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
