#include "stdafx.h"
#include "XSelectBoardInfo.h"


XSelectBoardInfo::XSelectBoardInfo()
{
	m_nIndex=0;

	m_nBoardIndex=0;

	m_szUserName=_T("");

	m_szPassWd=_T("");

	m_szIP=_T("");

	m_bSelected=FALSE;

	m_nSecretSel=0;

	m_nModelSel=0;

	m_szMask=_T("");

	m_szMAC=_T("");

	m_szGateWay=_T("");

}

XSelectBoardInfo::~XSelectBoardInfo()
{

}

int XSelectBoardInfo::GetIndex()
{
	return m_nIndex;
}

void XSelectBoardInfo::SetIndex(int n)
{
	m_nIndex=n;
}

int XSelectBoardInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XSelectBoardInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

CString XSelectBoardInfo::GetUserName()
{
	return m_szUserName;
}

void XSelectBoardInfo::SetUserName(CString szName)
{
	m_szUserName=szName;
}

CString XSelectBoardInfo::GetPassWd()
{
	return m_szPassWd;
}

void XSelectBoardInfo::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

CString XSelectBoardInfo::GetszIP()
{
	return m_szIP;
}

void XSelectBoardInfo::SetIP(CString szIP)
{
	m_szIP=szIP;
}

void XSelectBoardInfo::SetMask(CString szMask)
{
	m_szMask=szMask;
}

CString XSelectBoardInfo::GetMask()
{
	return m_szMask;
}

void XSelectBoardInfo::SetGateWay(CString szGateWay)
{
	m_szGateWay=szGateWay;
}

CString XSelectBoardInfo::GetGateWay()
{
	return m_szGateWay;
}

void XSelectBoardInfo::SetMAC(CString szMAC)
{
	m_szMAC=szMAC;
}

CString XSelectBoardInfo::GetMAC()
{
	return m_szMAC;
}

void XSelectBoardInfo::SetModelSel(int n)
{
	m_nModelSel=n;
}

int XSelectBoardInfo::GetModelSel()
{
	return m_nModelSel;
}

void XSelectBoardInfo::SetSecretSel(int n)
{
	m_nSecretSel=n;
}

int XSelectBoardInfo::GetSecretSel()
{
	return m_nSecretSel;
}

void XSelectBoardInfo::SetSelected(BOOL b)
{
	m_bSelected=b;
}

BOOL XSelectBoardInfo::GetSelected()
{
	return m_bSelected;
}
