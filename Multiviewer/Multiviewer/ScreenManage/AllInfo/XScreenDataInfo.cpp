#include "Stdafx.h"
#include "XScreenDataInfo.h"

XScreenDataInfo::XScreenDataInfo()
{
	m_nScreenIndex=0;

	m_nBoardIndex=0;

	m_nPaneNumIndex=0;

	m_bIsTwoScreen=FALSE;

	m_nPaneNumIndex=0;

}

XScreenDataInfo::~XScreenDataInfo()
{

}

void XScreenDataInfo::SetScreenIndex(int n)
{
	m_nScreenIndex=n;
}

int XScreenDataInfo::GetScreenIndex()
{
	return m_nScreenIndex;
}

void XScreenDataInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XScreenDataInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XScreenDataInfo::SetPaneNumIndex(int n)
{
	m_nPaneNumIndex=n;
}

int XScreenDataInfo::GetPaneNumIndex()
{
	return m_nPaneNumIndex;
}

void XScreenDataInfo::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

BOOL XScreenDataInfo::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

void XScreenDataInfo::SetScreenRect(RECTF rect)
{
	m_rScreen=rect;
}

RECTF XScreenDataInfo::GetScreenRect()
{
	return m_rScreen;
}