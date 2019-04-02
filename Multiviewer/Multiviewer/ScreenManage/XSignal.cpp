#include "StdAfx.h"
#include "XSignal.h"
#include "XMultiVideoWindowFrame.h"

XSignal::XSignal(void)
{
	m_Screen = NULL;

	m_nSignalID=0;

	m_nSingalGroupID=0;

	m_SignalHdpi=0;

	m_SignalVdpi=0;

	m_IsHide=FALSE;

	m_SignalLevel=-1;

	m_szIPAddr=_T("");

	m_szRTSPAddr=_T("");

	m_pFrame=NULL;

	m_bIs4kTo2k=FALSE;

	m_nSignalNum=0;

	m_szUseName=_T("");

	m_szPassWd=_T("");

	m_bIsSelected=FALSE;
}

XSignal::~XSignal(void)
{
	
}

void XSignal::SetInputIndex(int n)
{
	m_InputIndex = n;
}

void XSignal::SetExpand(XExpandInfo* pInfo)
{
	m_ExpandInfo = *pInfo;
}

void XSignal::SetCutInfo(XSignalCutInfo* pCutInfo)
{
	m_CutInfo=*pCutInfo;
}

XExpandInfo* XSignal::GetExpandInfo()
{
	return &m_ExpandInfo;
}

XSignalCutInfo* XSignal::GetCutInfo()
{
	return &m_CutInfo;
}

int XSignal::GetInputIndex()
{
	return m_InputIndex;
}

void XSignal::SetRect(RECTF r)
{
	m_Rect = r;
}

RECTF XSignal::GetRect()
{
	return m_Rect;
}

XScreen* XSignal::GetScreen()
{
	return m_Screen;
}

void XSignal::SetScreen(XScreen* p)
{
	m_Screen = p;
}

unsigned int XSignal::GetSignalID()
{
	return m_nSignalID;
}

void XSignal::SetSignalID(unsigned int ID)
{
	m_nSignalID=ID;
}

unsigned int XSignal::GetSignalGroupID()
{
	return m_nSingalGroupID;
}

void XSignal::SetSignalGroupID(unsigned int ID)
{
	m_nSingalGroupID=ID;
}

void XSignal::SetSignalLevel(int n)
{
	m_SignalLevel=n;
}

int XSignal::GetSignalLevel()
{
	return m_SignalLevel;
}

BOOL XSignal::GetSignalHide()
{
	return m_IsHide;
}

void XSignal::SetSignalHide(BOOL b)
{
	m_IsHide=b;
}

int XSignal::GetSignalHdpi()
{
	return m_SignalHdpi;
}

int XSignal::GetSignalVdpi()
{
	return m_SignalVdpi;
}

void XSignal::SetSignalHdpi(int n)
{
	m_SignalHdpi=n;
}

void XSignal::SetSignalVdpi(int n)
{
	m_SignalVdpi=n;
}

void XSignal::SetAnotherName(CString szName)
{
	m_szAnotherName=szName;
}

CString XSignal::GetAnotherName()
{
	return m_szAnotherName;
}

BOOL XSignal::GetIsUltra()
{
	return m_IsUltra;
}

void XSignal::SetIsUltra(BOOL b)
{
	m_IsUltra=b;
}

CString XSignal::GetIPAddr()
{
	return m_szIPAddr;
}

void XSignal::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XSignal::GetUseName()
{
	return m_szUseName;
}

void XSignal::SetUseName(CString szUseName)
{
	m_szUseName=szUseName;
}

CString XSignal::GetPassWd()
{
	return m_szPassWd;
}

void XSignal::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

CString XSignal::GetRTSPAddr()
{
	return m_szRTSPAddr;
}

void XSignal::SetRTSPAddr(CString szRTSPAddr)
{
	m_szRTSPAddr=szRTSPAddr;
}

XMultiVideoWindowFrame* XSignal::GetPreviewFrame()
{
	return m_pFrame;
}

void XSignal::SetPreviewFrame(XMultiVideoWindowFrame* p)
{
	m_pFrame=p;
}

BOOL XSignal::GetIs4kTo2k()
{
	return m_bIs4kTo2k;
}

void XSignal::SetIs4kTo2k(BOOL b)
{
	m_bIs4kTo2k=b;
}

int XSignal::GetSignalNum()
{
	return m_nSignalNum;
}

void XSignal::SetSignalNum(int n)
{
	m_nSignalNum=n;
}
