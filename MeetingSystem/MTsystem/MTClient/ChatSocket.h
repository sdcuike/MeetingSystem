// ChatSocket.h: interface for the CChatSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_)
#define AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "chatclientDoc.h"
/********************************************************************
	created:	2010/04/15
	created:	15:4:2010   18:39
	filename: 	F:\MeetingSystem\MTClient\ChatSocket.h
	file path:	F:\MeetingSystem\MTClient
	file base:	ChatSocket
	file ext:	h
	author:		����
	
	purpose:Ϊʹ�׽��ִ����첽ģʽ����Ҫ��CSocket������һ���Լ���WinSock��CChatSocket
	        �࣬�������Ψһ�Ĳ�ͬ����������OnReceive�����������ڵ��׽��ֽ��յ�����ʱ
			����Ϣ���д�������Ķ���Ϊ:
*********************************************************************/
class CChatSocket : public CSocket  
{
public:
	CChatSocket(CChatClientDoc* pDoc);
	CChatSocket();
	virtual ~CChatSocket();

private:
	CChatClientDoc* m_pDoc;
protected:
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_CHATSOCKET_H__A172A9D8_0219_49EE_A8BA_CFE23597C36D__INCLUDED_)
