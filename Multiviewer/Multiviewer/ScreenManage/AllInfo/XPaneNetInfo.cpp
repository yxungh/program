#include "stdafx.h"
#include "XPaneNetInfo.h"

XPaneNetInfo::XPaneNetInfo()
{

}
XPaneNetInfo::~XPaneNetInfo()
{

}


CString XPaneNetInfo::GetUseName()
{
	return m_szUseName;
}

void XPaneNetInfo::SetUseName(CString szName)
{
	m_szUseName=szName;
}

CString XPaneNetInfo::GetPassWd()
{
	return m_szPassWd;
}

void XPaneNetInfo::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

int XPaneNetInfo::GetModel()
{
	return m_nModel;
}

void XPaneNetInfo::SetModel(int n)
{
	m_nModel=n;
}

int XPaneNetInfo::GetSelect()
{
	return m_nSelect;
}

void XPaneNetInfo::SetSelect(int n)
{
	m_nSelect=n;
}

CString XPaneNetInfo::GetIPAddr()
{
	return m_szIPAddr;
}

void XPaneNetInfo::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XPaneNetInfo::GetMaskAddr()
{
	return m_szMaskAddr;
}

void XPaneNetInfo::SetMaskAddr(CString szMask)
{
	m_szMaskAddr=szMask;
}

CString XPaneNetInfo::GetGateWayAddr()
{
	return m_szGateWayAddr;
}

void XPaneNetInfo::SetGateWayAddr(CString szGateWay)
{
	m_szGateWayAddr=szGateWay;
}

CString XPaneNetInfo::GetMACAddr()
{
	return m_szMACAddr;
}

void XPaneNetInfo::SetMACAddr(CString szMAC)
{
	m_szMACAddr=szMAC;
}