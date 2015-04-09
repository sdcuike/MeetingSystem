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
	author:		风云
	
	purpose:	在其他定义的图形圆基类CDraw中，成员变量m_ColorPen的
	存储的是在颜色列表的序列号，m_Layer中存储的也是在图层列表中的
	序列号。现在建立一个来管理诸如颜色、图层等方面的信息。图形参数
	类定义如下
*********************************************************************/
typedef struct         //用来存储图层的信息结构
{
	char m_Name[21]; //图层的名称
	BOOL b_Display;  //是否显示，1--显示，0--隐藏
	int reserved;   //备用
}LayerStruct;


class CGraphPara  
{
public:
	CGraphPara();
	COLORREF GetColor(int n);  //得到第N中颜色的实际颜色
	BOOL GetDisplayState(int n); //得到第N层的显示状态
	virtual ~CGraphPara();

protected:
	int n_ColorNumbAll; //总的颜色数
	int n_LayerNumbALL; //总的图层数
	int n_ColorNumb;    //系统当前具有的颜色数
	int n_LayerNumb;    //系统当前具有的图层数
	long* m_ColrList;   //用来存储颜色列表的数组
	LayerStruct* m_LayerList; //用来存储图层列表的结构数组


};

#endif // !defined(AFX_GRAPHPARA_H__D38D4020_0769_4D04_A346_0E3951DC6F2C__INCLUDED_)
