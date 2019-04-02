#include "stdafx.h"
#include "XDeviceInfo.h"

XDeviceInfo::XDeviceInfo()
{
	m_nInputIndex=0;

	m_szAnotherName=_T("");

	m_szRTSPAddr=_T("");

	m_szIP=_T("");

	m_bIsHavePane=FALSE;

	m_bIsHaveSignal=FALSE;

	m_bIsUltra=FALSE;
}

XDeviceInfo::~XDeviceInfo()
{

}

void XDeviceInfo::SetInputIndex(int n)
{
	m_nInputIndex=n;
}

int XDeviceInfo::GetInputIndex()
{
	return m_nInputIndex;
}

void XDeviceInfo::SetAnotherName(CString szAnotherName)
{
	m_szAnotherName=szAnotherName;
}

CString XDeviceInfo::GetAnotherName()
{
	return m_szAnotherName;
}

void XDeviceInfo::SetRTSPAddr(CString szAddr)
{
	m_szRTSPAddr=szAddr;
}

CString XDeviceInfo::GetRTSPAddr()
{
	return m_szRTSPAddr;
}

void XDeviceInfo::SetIP(CString szIP)
{
	m_szIP=szIP;
}

CString XDeviceInfo::GetIP()
{
	return m_szIP;
}

void XDeviceInfo::SetIsHaveSignal(BOOL b)
{
	m_bIsHaveSignal=b;
}

BOOL XDeviceInfo::GetIsHaveSignal()
{
	return m_bIsHaveSignal;
}

void XDeviceInfo::SetIsHavePane(BOOL b)
{
	m_bIsHavePane=b;
}

BOOL XDeviceInfo::GetIsHavePane()
{
	return m_bIsHavePane;
}

void XDeviceInfo::SetIsUltra(BOOL b)
{
	m_bIsUltra=b;
}

BOOL XDeviceInfo::GetIsUltra()
{
	return m_bIsUltra;
}