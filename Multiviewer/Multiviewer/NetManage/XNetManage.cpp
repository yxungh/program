#include "StdAfx.h"
#include "XNetManage.h"
#include "XSocketUDP.h"
#include "XDelegateNetManage.h"

XNetManage::XNetManage(void)
{
	m_pSocketUDP = nullptr;
}

XNetManage::~XNetManage(void)
{
	if (nullptr != m_pSocketUDP)
	{
		delete m_pSocketUDP;

		m_pSocketUDP = nullptr;
	}
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

void XNetManage::Open()
{
	if (!m_pSocketUDP->Open())
	{
		m_pDelegate->MessageBoxFromKey(_T("200"), _T("ÍøÂç´ò¿ªÊ§°Ü!"), MB_OK);
	}
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

///////////////////////////////////////////////////////////////////////////////////////////////////
void XNetManage::UpdateControlUIByState(CCmdUI* pCmdUI, BOOL bState)
{
	if (GetState() != bState)
	{
		pCmdUI->Enable(FALSE);
	}
}

void XNetManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_OPENNET:
		{
			Open();
		}
		break;
	case OPERATETYPE_CLOSENET:
		{
			Close();
		}
		break;
	default:
		break;
	}
}

void XNetManage::UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)
{
	switch(type)
	{
	case CMDUITYPE_OPENNET:
		{
			UpdateControlUIByState(pCmdUI, FALSE);
		}
		break;
	case CMDUITYPE_CLOSENET:
		{
			UpdateControlUIByState(pCmdUI, TRUE);
		}
		break;
	default:
		break;
	}
}