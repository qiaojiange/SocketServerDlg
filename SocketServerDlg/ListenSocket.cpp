// ListenSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketServerDlg.h"
#include "ListenSocket.h"


// CListenSocket

CListenSocket::CListenSocket(void)
{
}

CListenSocket::~CListenSocket(void)
{
}


// CListenSocket 成员函数
 void CListenSocket::OnClose(int nErrorCode){
	 if (0 == nErrorCode)
	 {
	//	CNewSocket* pNewSocket;
		for (std::vector<CNewSocket*>::iterator it = m_vectorSocket.begin();it!=m_vectorSocket.end();it++)
		{
			(*it)->Close();
		}
		m_vectorSocket.clear();
	 }
	 CAsyncSocket::Close();
 }

void CListenSocket::OnAccept(int nErrorCode)
{
	if (0==nErrorCode)
	{
		//作为连接的客户端
		CNewSocket* pNewSocket = new CNewSocket();
		if (Accept(*pNewSocket))
		{
			m_vectorSocket.push_back(pNewSocket);
			pNewSocket->AsyncSelect(FD_READ);//触发通信socket的Read函数读数据
			m_pSocket = pNewSocket;
		}else{
			delete pNewSocket;
		}
	}
//	CAsyncSocket::OnAccept(nErrorCode);
}
