#include "stdafx.h"
#include "XBoardNetInfo.h"


#define BOARDNET_VERSION 1

XBoardNetInfo::XBoardNetInfo()
{
	m_szUseName=_T("");

	m_szPassWd=_T("");

	m_szIPAddr=_T("");

	m_szMACAddr=_T("255.255.255.0");

	m_szGateWayAddr=_T("192.168.1.1");

	m_szMACAddr=_T("");

	m_pMAC=NULL;

	m_nModel=0;

	m_nSelect=0;

	m_nBoardIndex=0;

	m_nSecretSelect=0;

	m_nSecret=0;
}

XBoardNetInfo::~XBoardNetInfo()
{
	ClearMACAddr();
}

void XBoardNetInfo::ClearMACAddr()
{
	if(m_pMAC!=NULL)
	{
		delete m_pMAC;

		m_pMAC=NULL;
	}
}

CString XBoardNetInfo::GetUseName()
{
	return m_szUseName;
}

void XBoardNetInfo::SetUseName(CString szName)
{
	m_szUseName=szName;
}

CString XBoardNetInfo::GetPassWd()
{
	return m_szPassWd;
}

void XBoardNetInfo::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

int XBoardNetInfo::GetModel()
{
	return m_nModel;
}

void XBoardNetInfo::SetModel(int n)
{
	m_nModel=n;
}

int XBoardNetInfo::GetSelect()
{
	return m_nSelect;
}

void XBoardNetInfo::SetSelect(int n)
{
	m_nSelect=n;
}

CString XBoardNetInfo::GetIPAddr()
{
	return m_szIPAddr;
}

void XBoardNetInfo::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XBoardNetInfo::GetMaskAddr()
{
	return m_szMaskAddr;
}

void XBoardNetInfo::SetMaskAddr(CString szMask)
{
	m_szMaskAddr=szMask;
}

CString XBoardNetInfo::GetGateWayAddr()
{
	return m_szGateWayAddr;
}

void XBoardNetInfo::SetGateWayAddr(CString szGateWay)
{
	m_szGateWayAddr=szGateWay;
}

CString XBoardNetInfo::GetMACAddr()
{
	return m_szMACAddr;
}

void XBoardNetInfo::SetMACAddr(CString szMAC)
{
	m_szMACAddr=szMAC;
}

int XBoardNetInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XBoardNetInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

void XBoardNetInfo::SetArrMAC(int* p)
{
	m_pMAC=new int[6];

	memcpy(m_pMAC,p,6*sizeof(p));
}

int* XBoardNetInfo::GetArrMAC()
{
	return m_pMAC;
}

void XBoardNetInfo::SerSecretSelect(int n)
{
	m_nSecretSelect=n;
}

int XBoardNetInfo::GetSecretSelect()
{
	return m_nSecretSelect;
}

void XBoardNetInfo::SetSecret(int n)
{
	m_nSecret=n;
}

int XBoardNetInfo::GetSecret()
{
	return m_nSecret;
}

void XBoardNetInfo::GetData(CArchive& arch)
{


}

void XBoardNetInfo::SaveData(CArchive& arch)
{

}