#include "stdafx.h"
#include "XInputInfoInGroup.h"


XInputInfoInGroup::XInputInfoInGroup()
{
	m_nIndex=0;

	m_szGroupName=_T("");

	m_szAnotherName=_T("");
}

XInputInfoInGroup::~XInputInfoInGroup()
{

}

void XInputInfoInGroup::SetIndex(int n)
{
	m_nIndex=n;
}

int XInputInfoInGroup::GetIndex()
{
	return m_nIndex;
}

void XInputInfoInGroup::SetGroupName(CString szName)
{
	m_szGroupName=szName;
}

CString XInputInfoInGroup::GetGroupName()
{
	return m_szGroupName;
}

void XInputInfoInGroup::SetAnotherName(CString szName)
{
	m_szAnotherName=szName;
}

CString XInputInfoInGroup::GetAnotherName()
{
	return m_szAnotherName;
}