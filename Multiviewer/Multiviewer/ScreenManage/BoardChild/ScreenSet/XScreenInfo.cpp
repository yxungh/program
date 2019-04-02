#include "stdafx.h"
#include "XScreenInfo.h"

XScreenInfo::XScreenInfo()
{
	m_nScreenIndex=0;

	m_nBoardIndex=0;

	m_nLBDclick=0;

	m_bIsTwoScreen=FALSE;

	m_nNumOfScreen=0;

	m_nCurBoardIndex=0;

	//m_bFlag=FALSE;

	m_nScreenModel=0;

}

XScreenInfo::~XScreenInfo()
{

}


void XScreenInfo::SetScreenIndex(int n)
{
	m_nScreenIndex=n;	
}

int XScreenInfo::GetScreenIndex()
{
	return m_nScreenIndex;
}

void XScreenInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XScreenInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XScreenInfo::SetLBDclick(int n)
{
	m_nLBDclick=n;
}

int XScreenInfo::GetLBDclick()
{
	return m_nLBDclick;
}

void XScreenInfo::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

BOOL XScreenInfo::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

void XScreenInfo::SetNumOfScreen(int n)
{
	m_nNumOfScreen=n;
}

int XScreenInfo::GetNumOfScreen()
{
	return m_nNumOfScreen;
}

void XScreenInfo::SetCurBoardIndex(int n)
{
	m_nCurBoardIndex=n;
}

int XScreenInfo::GetCurBoardIndex()
{
	return m_nCurBoardIndex;
}

//void XScreenInfo::SetFlag(BOOL b)
//{
//	m_bFlag=b;
//}
//
//BOOL XScreenInfo::GetFlag()
//{
//	return m_bFlag;
//}