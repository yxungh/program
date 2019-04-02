#include "stdafx.h"
#include "XAnotherNameInfo.h"

XAnotherNameInfo::XAnotherNameInfo()
{

}

XAnotherNameInfo::~XAnotherNameInfo()
{

}


CString XAnotherNameInfo::GetAnotherName()
{
	return m_szANotherName;
}

void XAnotherNameInfo::SetAnotherName(CString szName)
{
	m_szANotherName=szName;
}

int XAnotherNameInfo::GetInputIndex()
{
	return m_nInputIndex;
}

void XAnotherNameInfo::SetInputIndex(int n)
{
	m_nInputIndex=n;
}