#include "stdafx.h"
#include "XStreamAddrInfo.h"

#define EDID_VERSION 1

XStreamAddrInfo::XStreamAddrInfo()
{
	m_Len=0;
}

XStreamAddrInfo::~XStreamAddrInfo()
{

}

CString XStreamAddrInfo::GetText()
{
	return szText;
}

void XStreamAddrInfo::SetText(CString str)
{
	szText=str;
}

void XStreamAddrInfo::SetDataLen(int n)
{
	m_Len=n;
}

int XStreamAddrInfo::GetDataLen()
{
	return m_Len;
}

void XStreamAddrInfo::GetData(CArchive& arch)
{
	int nVersion=0;
	arch>>nVersion;
	arch>>szText;
}

void XStreamAddrInfo::SaveData(CArchive& arch)
{
	arch<<EDID_VERSION
		<<szText;		
}