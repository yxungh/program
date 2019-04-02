#include "stdafx.h"
#include "XOldOrderInfo.h"

#define EDID_VERSION 1

XOldOrderInfo::XOldOrderInfo()
{
	m_Len=0;
}

XOldOrderInfo::~XOldOrderInfo()
{

}


CString XOldOrderInfo::GetText()
{
	return szText;
}

void XOldOrderInfo::SetText(CString str)
{
	szText=str;
}

void XOldOrderInfo::SetDataLen(int n)
{
	m_Len=n;
}

int XOldOrderInfo::GetDataLen()
{
	return m_Len;
}

void XOldOrderInfo::GetData(CArchive& arch)
{
	int nVersion=0;
	arch>>nVersion;
	arch>>szText;
}

void XOldOrderInfo::SaveData(CArchive& arch)
{
	arch<<EDID_VERSION
		<<szText;		
}