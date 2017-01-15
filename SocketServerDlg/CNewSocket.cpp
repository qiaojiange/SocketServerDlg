// NewSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketServerDlg.h"
#include "CNewSocket.h"


// NewSocket

CNewSocket::CNewSocket()
{
	m_nLength = 0;
	memset(m_szBuffer,0,sizeof(m_szBuffer));
}

CNewSocket::~CNewSocket()
{
}


// NewSocket 成员函数


void CNewSocket::OnReceive(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_nLength = Receive(m_szBuffer,LENGTH);//接受数据
		m_szBuffer[m_nLength] = '\0';
		//接受消息后就给客户端发送相同的消息
	//	printf("%s\n",m_szBuffer);
		AsyncSelect(FD_WRITE);

	//	if (m_nLength != SOCKET_ERROR)
	//	{
	//			char m_sendBuf[513]={0};//消息缓冲

	///*strcpy(m_sendBuf,"server send:");
	//strcat(m_sendBuf,m_szBuffer);
	//strcat(m_sendBuf,"\n");*/

	//			sprintf_s(m_sendBuf,"echo:%s\n",m_szBuffer);
	//			Send(m_sendBuf,sizeof(m_sendBuf));
	//			memset(m_szBuffer,0,sizeof(m_szBuffer));
	//	}
	
	}
	 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CNewSocket::OnClose(int nErrorCode){
	if (0==nErrorCode)
	{
		char m_sendBuf[LENGTH]={0};//消息缓冲

		sprintf_s(m_sendBuf,"echo:close\n",m_szBuffer);
		
		Send(m_sendBuf,strlen(m_sendBuf));
		//AsyncSelect(FD_CLOSE);//先不加，之后加上进行测试
		
		TRACE("----CNewSocket---OnClose\n");
	}
	CAsyncSocket::Close();
}

void CNewSocket::OnSend(int nErrorCode)
{
	if (nErrorCode==0)
	{



		char m_sendBuf[LENGTH]={0};//消息缓冲
		/*strcpy(m_sendBuf,"server send:");
		strcat(m_sendBuf,m_szBuffer);
		strcat(m_sendBuf,"\n");*/

		sprintf_s(m_sendBuf,"echo:%s\n",m_szBuffer);
	//	TRACE("--------sendBuf:%s-----%d\n",m_sendBuf,strlen(m_sendBuf));
		
		Send(m_sendBuf,strlen(m_sendBuf));
		memset(m_sendBuf,0,sizeof(m_sendBuf));
		memset(m_szBuffer,0,sizeof(m_szBuffer));
		//触发OnReceive函数
		AsyncSelect(FD_READ);
	}
	
	CAsyncSocket::OnSend(nErrorCode);

}
