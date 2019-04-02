#include "Stdafx.h"
#include "XPaneIPAddrInfo.h"


#define PAMEIP_VERSION  1

XPaneIPAddrInfo::XPaneIPAddrInfo()
{
	m_szPaneIP=_T("");

	m_szPaneMask=_T("255.255.255.0");

	m_szPaneGateWay=_T("192.168.1.1");

	m_szPaneMAC=_T("");

	pMAC=NULL;

	m_nModel=0;

	m_nSelect=0;
}

XPaneIPAddrInfo::~XPaneIPAddrInfo()
{
	ClearMACAddr();
}

void XPaneIPAddrInfo::ClearMACAddr()
{
	if(pMAC!=NULL)
	{
		delete pMAC;

		pMAC=NULL;
	}
}


void XPaneIPAddrInfo::SetPaneIP(CString szIP)
{
	m_szPaneIP=szIP;
}

CString XPaneIPAddrInfo::GetPaneIP()
{
	return m_szPaneIP;
}

void XPaneIPAddrInfo::SetPaneMask(CString szMask)
{
	m_szPaneMask=szMask;
}

CString XPaneIPAddrInfo::GetPaneMask()
{
	return m_szPaneMask;
}

void XPaneIPAddrInfo::SetPaneGateWay(CString szGateWay)
{
	m_szPaneGateWay=szGateWay;
}

CString XPaneIPAddrInfo::GetPaneGateWay()
{
	return m_szPaneGateWay;
}

void XPaneIPAddrInfo::SetPaneMAC(CString szMAC)
{
	m_szPaneMAC=szMAC;
}

CString XPaneIPAddrInfo::GetPaneMAC()
{
	return m_szPaneMAC;
}

void XPaneIPAddrInfo::SetArrMAC(int* p)
{
	pMAC=new int[6];

	memcpy(pMAC,p,6*sizeof(p));
}

int* XPaneIPAddrInfo::GetArrMAC()
{
	return pMAC;
}

int XPaneIPAddrInfo::GetModel()
{
	return m_nModel;
}

void XPaneIPAddrInfo::SetModel(int n)
{
	m_nModel=n;
}

int XPaneIPAddrInfo::GetSelect()
{
	return m_nSelect;
}

void XPaneIPAddrInfo::SetSelect(int n)
{
	m_nSelect=n;
}

void XPaneIPAddrInfo::GetData(CArchive& arch)
{
	int nVersion=0;
	arch>>nVersion;

	arch>>m_szPaneIP
		>>m_szPaneMask
		>>m_szPaneGateWay
		>>m_szPaneMAC
		>>m_nModel
		>>m_nSelect;
}

void XPaneIPAddrInfo::SaveData(CArchive& arch)
{
	arch<<PAMEIP_VERSION
		<<m_szPaneIP
		<<m_szPaneMask
		<<m_szPaneGateWay
		<<m_szPaneMAC
		<<m_nModel
		<<m_nSelect;
}