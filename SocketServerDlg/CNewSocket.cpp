// NewSocket.cpp : ʵ���ļ�
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


// NewSocket ��Ա����


void CNewSocket::OnReceive(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_nLength = Receive(m_szBuffer,LENGTH);//��������
		m_szBuffer[m_nLength] = '\0';
		//������Ϣ��͸��ͻ��˷�����ͬ����Ϣ
	//	printf("%s\n",m_szBuffer);
		AsyncSelect(FD_WRITE);

	//	if (m_nLength != SOCKET_ERROR)
	//	{
	//			char m_sendBuf[513]={0};//��Ϣ����

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
		char m_sendBuf[LENGTH]={0};//��Ϣ����

		sprintf_s(m_sendBuf,"echo:close\n",m_szBuffer);
		
		Send(m_sendBuf,strlen(m_sendBuf));
		//AsyncSelect(FD_CLOSE);//�Ȳ��ӣ�֮����Ͻ��в���
		
		TRACE("----CNewSocket---OnClose\n");
	}
	CAsyncSocket::Close();
}

void CNewSocket::OnSend(int nErrorCode)
{
	if (nErrorCode==0)
	{



		char m_sendBuf[LENGTH]={0};//��Ϣ����
		/*strcpy(m_sendBuf,"server send:");
		strcat(m_sendBuf,m_szBuffer);
		strcat(m_sendBuf,"\n");*/

		sprintf_s(m_sendBuf,"echo:%s\n",m_szBuffer);
	//	TRACE("--------sendBuf:%s-----%d\n",m_sendBuf,strlen(m_sendBuf));
		
		Send(m_sendBuf,strlen(m_sendBuf));
		memset(m_sendBuf,0,sizeof(m_sendBuf));
		memset(m_szBuffer,0,sizeof(m_szBuffer));
		//����OnReceive����
		AsyncSelect(FD_READ);
	}
	
	CAsyncSocket::OnSend(nErrorCode);

}
