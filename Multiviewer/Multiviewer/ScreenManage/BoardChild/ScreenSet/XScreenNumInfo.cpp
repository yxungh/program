#include "stdafx.h"
#include "XScreenNumInfo.h"

XScreenNumInfo::XScreenNumInfo()
{
	m_nScreenIndex=0;

	m_nScreenNum=0;
}

XScreenNumInfo::~XScreenNumInfo()
{

}



int XScreenNumInfo::GetScreenIndex()
{
	return m_nScreenIndex;
}

void XScreenNumInfo::SetScreenIndex(int n)
{
	m_nScreenIndex=n;
}

int XScreenNumInfo::GetScreenNum()
{
	return m_nScreenNum;
}

void XScreenNumInfo::SetScreenNum(int n)
{
	m_nScreenNum=n;
}