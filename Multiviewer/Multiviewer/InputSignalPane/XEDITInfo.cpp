#include "stdafx.h"
#include "XEDIDInfo.h"

#define EDID_VERSION 1

XEDIDInfo::XEDIDInfo()
{
	m_Len=0;
}

XEDIDInfo::~XEDIDInfo()
{
	
}


CString XEDIDInfo::GetText()
{
	return szText;
}

void XEDIDInfo::SetText(CString str)
{
	szText=str;
}

void XEDIDInfo::SetDataLen(int n)
{
	m_Len=n;
}

int XEDIDInfo::GetDataLen()
{
	return m_Len;
}

void XEDIDInfo::GetData(CArchive& arch)
{
	int nVersion=0;
	arch>>nVersion;
	arch>>szText;
}

void XEDIDInfo::SaveData(CArchive& arch)
{
	arch<<EDID_VERSION
		<<szText;		
}