// ChatSocket.cpp: implementation of the CChatSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{

}

CChatSocket::CChatSocket(CChatClientDoc* pDoc)
{
	ASSERT(pDoc != NULL);
	m_pDoc = pDoc; //使套接字与文档联系起来
}



/* 重载OnReceive函数以通知程序“收到消息，请进行处理”，
  而发送消息的动作则直接通过套接字进行，并不需要用户界面
  响应，
*/
void CChatSocket::OnReceive(int nErrorCode)  
{
	CSocket::OnReceive(nErrorCode);           

	m_pDoc->ProcessPendingRead();

	/*当套接字接收到数据时，就调用文档类的
	ProcessPendingRead函数进行处理
    
    */
}
