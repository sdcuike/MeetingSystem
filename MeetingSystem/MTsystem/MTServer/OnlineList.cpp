// OnlineList.cpp : implementation file
//

#include "stdafx.h"
#include "chatsrvr.h"
#include "OnlineList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnlineList

COnlineList::COnlineList()
{
}

COnlineList::~COnlineList()
{
}


BEGIN_MESSAGE_MAP(COnlineList, CListCtrl)
	//{{AFX_MSG_MAP(COnlineList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnlineList message handlers
int COnlineList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void COnlineList::Remove( char* name )
{
	CString str;
	for(int i = 0; i < GetItemCount(); i++){
		str = GetItemText(i,0);
		if(strcmp(str, name) == 0){
			DeleteItem(i);
			break;
		}
	}
}

void COnlineList::AddItem( short i, char* name, char* text )
{
	LVITEM			lvi;
	
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = GetItemCount();
    lvi.iImage = i;
	lvi.iSubItem = 0;
	lvi.pszText = name;
	lvi.cchTextMax = 64;
	lvi.lParam = 0;
	InsertItem(&lvi);
	
	lvi.mask = LVIF_TEXT;
	lvi.pszText = text;
	lvi.cchTextMax = 32;
	lvi.iSubItem = 1;
	SetItem(&lvi);
}

