#include "Stdafx.h"
#include "XScreenData.h"


XScreenData::XScreenData()
{
	m_nScreenIndex=-1;

	m_nBoardIndex=0;

	m_bIsTwoScreen=FALSE;

	m_nNumOfTwoScreen=0;
}

XScreenData::~XScreenData()
{

}


void XScreenData::SetScreenIndex(int n)
{
	m_nScreenIndex=n;
}


void XScreenData::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

void XScreenData::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

void XScreenData::SetNumOfTwoScreen(int n)
{
	m_nNumOfTwoScreen=n;
}

int XScreenData::GetScreenIndex()
{
	return m_nScreenIndex;
}


int XScreenData::GetBoardIndex()
{
	return m_nBoardIndex;
}

BOOL XScreenData::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

int XScreenData::GetNumOfTwoScreen()
{
	return m_nNumOfTwoScreen;
}