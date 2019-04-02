#include "StdAfx.h"
#include "XSocketUDP.h"
#include "XConstantIM.h"
#include "XNetManage.h"

XSocketUDP::XSocketUDP(void)
{
	m_bState = FALSE;

	m_Socket = INVALID_SOCKET;

	m_HWND = NULL;

	m_NetManage = NULL;
}


XSocketUDP::~XSocketUDP(void)
{
	Close();
}


void XSocketUDP::SetNetManage(XNetManage* p)
{
	m_NetManage = p;
}

void XSocketUDP::SetHWND(HWND h)
{
	m_HWND = h;
}

BOOL XSocketUDP::Open()
{
	Close();

	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_Socket == INVALID_SOCKET)
	{
		return FALSE;
	}

	int nBroadcast = 1;
	if (SOCKET_ERROR == setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, (const char*)&nBroadcast, sizeof(nBroadcast)))
	{
		return false;
	}

	
	//绑定地址
	//USES_CONVERSION;

	//SOCKADDR_IN addr;
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(8888);
	//addr.sin_addr.s_addr = INADDR_ANY;

	//if (bind(m_Socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	//{
	//	return FALSE;
	//}
	

	//设置接收数据缓冲区大小
	int nBufLen = 1024 * 500;

	int nOptlen = sizeof(int);

	int nErrCode = 0;

	nErrCode = setsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF,
		(char*)&nBufLen, nOptlen);
	if (SOCKET_ERROR == nErrCode)
	{
		return FALSE;
	}

	int uiNewRcvBuf;
	nErrCode = getsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &nOptlen);
	if(SOCKET_ERROR == nErrCode || uiNewRcvBuf != nBufLen)
	{
		return FALSE;
	}

	//设置写数据缓冲区大小
	nErrCode = setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF,
		(char*)&nBufLen, nOptlen);
	if (SOCKET_ERROR == nErrCode)
	{
		return FALSE;
	}

	int uiNewSendBuf;
	nErrCode = getsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF,(char*)&uiNewSendBuf, &nOptlen);
	if(SOCKET_ERROR == nErrCode || uiNewSendBuf != nBufLen)
	{
		return FALSE;
	}

	//注册事件
	if (WSAAsyncSelect(m_Socket, m_HWND, MSG_UDP, FD_READ) == SOCKET_ERROR)
	{
		return FALSE;
	}

	m_bState = TRUE;

	return TRUE;
}

BOOL XSocketUDP::SendData(const char* pData, const int nDataLen, char* pIp,
	u_short nTargetPort)
{
	BOOL bResult = FALSE;

	if(m_bState)
	{
		SOCKADDR_IN	addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(pIp);
		addr.sin_port = htons(nTargetPort);

		if (sendto(m_Socket, (const char *)pData, nDataLen, 0, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) != SOCKET_ERROR)
		{
			bResult = TRUE;
		}
	}

	return bResult;
}

void XSocketUDP::Close()
{
	m_bState = FALSE;

	if (m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);

		m_Socket = INVALID_SOCKET;
	}
}

BOOL XSocketUDP::GetState()
{
	return m_bState;
}

void XSocketUDP::HandleMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		int nError = WSAGETSELECTERROR(lParam);
		//TRACE("XUDPSocket::HandleMsg: WSAGETSELECTERROR:%d\n", nError);
	}
	else
	{
		switch(WSAGETSELECTEVENT(lParam))
		{
		case FD_READ:
			{
				HandleFD_READ();
			}
			break;
		default:
			break;
		}
	}
}

void XSocketUDP::HandleFD_READ()
{
	SOCKADDR_IN	addr;

	int nAddrLen = sizeof(SOCKADDR_IN);

	ZeroMemory(m_Data, 2048);

	int nRecvLen = recvfrom(m_Socket, (char*)m_Data, 2048, 0, (SOCKADDR*)&addr, &nAddrLen);

	if (nRecvLen > 0)
	{
		//afxDump<<"XUDPSocket::OnReceive:"<<nRecvLen<<"\n";
	
		m_NetManage->HandleUDPData(m_Data, nRecvLen, addr);
	}
}