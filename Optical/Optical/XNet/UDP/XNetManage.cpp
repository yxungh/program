#include "StdAfx.h"
#include "XNetManage.h"
#include "XSocketUDP.h"
#include "XDelegateNetManage.h"

XNetManage::XNetManage(void)
{
	m_pSocketUDP=nullptr;
	m_pDelegate=nullptr;
}

XNetManage::~XNetManage(void)
{
	if (nullptr != m_pSocketUDP)
	{
		delete m_pSocketUDP;

		m_pSocketUDP = nullptr;
	}
}

void XNetManage::SetDelegate(XDelegateNetManage* p)
{
	m_pDelegate=p;
}

void XNetManage::Init()
{
	m_pSocketUDP = new XSocketUDP;
	m_pSocketUDP->SetNetManage(this);
	m_pSocketUDP->SetHWND(m_pDelegate->GetHWND());
	m_pSocketUDP->Open();
}

BOOL XNetManage::GetState()
{
	return m_pSocketUDP->GetState();
}

void XNetManage::Close()
{
	m_pSocketUDP->Close();
}

BOOL XNetManage::SendData(CString szIP, int nPort, const char* pData, const int nLen)
{
	if (GetState())
	{
		USES_CONVERSION;
		char* pIP = W2A(szIP);

		return m_pSocketUDP->SendData(pData, nLen, pIP, nPort);
	}
	else
	{
		return FALSE;
	}
}

void XNetManage::HandleUDPMsg(WPARAM wParam, LPARAM lParam)
{
	m_pSocketUDP->HandleMsg(wParam, lParam);
}

void XNetManage::HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr)
{
	m_pDelegate->HandleUDPData(pData, nDataLen, addr);
}
