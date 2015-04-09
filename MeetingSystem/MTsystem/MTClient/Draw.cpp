// Draw.cpp: implementation of the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chatclient.h"
#include "Draw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDraw::CDraw()
{
	
}

CDraw::CDraw( short ColorPen, short ColorBrush, short LineWide, short LineType, short Layer, int id_only, BOOL Delete )
{
	m_ColorPen=ColorPen;
	m_ColorBrush=ColorBrush;
	m_LineWide=LineWide;
	m_LineType=LineType;
	m_Layer=Layer;
	b_Delete=Delete;
	m_id_only=id_only;
}

CDraw::~CDraw()
{

}

void CDraw::Draw( CDC *pDC, int m_DrwaMode, int m_DrwaMode1, short BackColor )
{
	
}

int CDraw::GetID()
{
	//得到一个图形元素对象的识别号--m_id_only
	return m_id_only;
}
