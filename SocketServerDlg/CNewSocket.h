

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSock.h : header file


#include "afxsock.h"
#define LENGTH 100
//作为连接后的客户端
class CNewSocket : public CAsyncSocket
{
public:
	CNewSocket();
	virtual ~CNewSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	UINT m_nLength;
	char m_szBuffer[LENGTH];
};

