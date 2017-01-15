

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CListenSocket ÃüÁîÄ¿±ê
#include "CNewSocket.h"
#include "afxsock.h"
#include <vector>
class CSocketServerDlgDlg;

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket(void);
	virtual ~CListenSocket(void);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CNewSocket* m_pSocket;

	std::vector<CNewSocket*> m_vectorSocket;
};


