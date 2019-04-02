#include "stdafx.h"
#include "XScreenRetInfo.h"


XScreenRetInfo::XScreenRetInfo()
{
	m_nBoardIndex=0;
	m_nStatus=0;
}

XScreenRetInfo::~XScreenRetInfo()
{

}


void XScreenRetInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}
int XScreenRetInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}
void XScreenRetInfo::SetStatus(int n)
{
	m_nStatus=n;
}
int XScreenRetInfo::GetStatus()
{
	return m_nStatus;
}