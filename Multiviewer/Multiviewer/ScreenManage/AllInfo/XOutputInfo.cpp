#include "stdafx.h"
#include "XOutputInfo.h"


XOutputInfo::XOutputInfo()
{

}

XOutputInfo::~XOutputInfo()
{

}

void XOutputInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XOutputInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XOutputInfo::SetInputName(CString szName)
{
	m_szInputName=szName;
}

CString XOutputInfo::GetInputName()
{
	return m_szInputName;
}

void XOutputInfo::SetIsFirstPan(BOOL b)
{
	m_bIsFirstPan=b;
}

BOOL XOutputInfo::GetIsFirstPan()
{
	return m_bIsFirstPan;
}

void XOutputInfo::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

BOOL XOutputInfo::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

void XOutputInfo::SetScreenIndex1(int n)
{
	m_nScreenIndex1=n;
}

int XOutputInfo::GetScreenIndex1()
{
	return m_nScreenIndex1;
}

void XOutputInfo::SetScreenIndex2(int n)
{
	m_nScreenIndex2=n;
}

int XOutputInfo::GetScreenIndex2()
{
	return m_nScreenIndex2;
}

void XOutputInfo::SetCheckNum(int n)
{
	m_nCheckNum=n;
}

int XOutputInfo::GetCheckNum()
{
	return m_nCheckNum;
}

void XOutputInfo::SetMapScreenNum(MAP_NUMOFSCREEN MapNumOfScreen)
{
	m_MapNumOfScreen=MapNumOfScreen;
}

MAP_NUMOFSCREEN& XOutputInfo::GetMapScreenNum()
{
	return m_MapNumOfScreen;
}