#include "StdAfx.h"
#include "XRTSPInfo.h"
#include "XConstantIM.h"


XRTSPInfo::XRTSPInfo(void)
{
	m_RTSPAddr = _T("");

	m_RTSPHDAddr = _T("");

	m_szAnotherName = _T("");

	m_nPreviewIndex=0;

	m_nPreviewID=0;

	m_nPreviewGroupID=0;

	m_bIsUltra=FALSE;

	m_pMultiVideoWindow=NULL;

	m_szIPAddr=_T("");

	m_szUseName=_T("");

	m_szPassWd=_T("");

	m_bIsHaveSignal=FALSE;

	m_bIsHavePane=FALSE;
}

XRTSPInfo::~XRTSPInfo(void)
{
	
}

void XRTSPInfo::Init(CString szRTSPAddr, CString szRTSPHDAddr, CString szAnotherName)
{
	m_RTSPAddr=szRTSPAddr;

	m_RTSPHDAddr=szRTSPHDAddr;

	m_szAnotherName=szAnotherName;
}

void XRTSPInfo::ClearData()
{
	m_RTSPAddr=_T("");

	m_RTSPHDAddr=_T("");

	m_szAnotherName=_T("");

	m_szIPAddr=_T("");
}

CString XRTSPInfo::GetRTSPAddr()
{
	return m_RTSPAddr;
}

CString XRTSPInfo::GetRTSPHDAddr()
{
	return m_RTSPHDAddr;
}

CString XRTSPInfo::GetAnotherName()
{
	return m_szAnotherName;
}

int XRTSPInfo::GetPreviewIndex()
{
	return m_nPreviewIndex;
}

unsigned int XRTSPInfo::GetPreviewID()
{
	return m_signalID;
}

void XRTSPInfo::SetRTSPAddr(CString s)
{
	m_RTSPAddr = s;
}

void XRTSPInfo::SetAnotherName(CString s)
{
	m_szAnotherName = s;
}

void XRTSPInfo::SetRTSPHDAddr(CString s)
{
	m_RTSPHDAddr = s;
}

void XRTSPInfo::SetPreviewIndex(int n)
{
	m_nPreviewIndex=n;
}

void XRTSPInfo::SetPreviewID(unsigned int nID)
{
	m_signalID=nID;
}

unsigned int XRTSPInfo::GetPreviewGroupID()
{
	return m_signalGroupID;
}

void XRTSPInfo::SetPreviewGroupID(unsigned int nGroupID)
{
	m_signalGroupID=nGroupID;
}

BOOL XRTSPInfo::GetIsUltra()
{
	return m_bIsUltra;
}

void XRTSPInfo::SetIsUltra(BOOL IsUltra)
{
	m_bIsUltra=IsUltra;
}

XExpandInfo* XRTSPInfo::GetExpandInfo()
{
	return &m_ExpandInfo;
}

void XRTSPInfo::SetExpandInfo(XExpandInfo* p)
{
	m_ExpandInfo=*p;
}

VEC_UNINT& XRTSPInfo::GetVecPreviewID()
{
	return m_VecPreviewID;
}

void XRTSPInfo::SetVecPreviewID(VEC_UNINT& VecInt)
{
	m_VecPreviewID=VecInt;
}


HYVEC_NUM& XRTSPInfo::GetVecPreviewIndex()
{
	return m_VecPreviewIndex;
}

void XRTSPInfo::SetVecPreviewIndex(HYVEC_NUM& VecIndex)
{
	m_VecPreviewIndex=VecIndex;
}

VEC_CSTRING& XRTSPInfo::GetVecRTSPAddr()
{
	return m_VecRTSPAddr;
}

void XRTSPInfo::SetVecRTSPAddr(VEC_CSTRING& VecStr)
{
	m_VecRTSPAddr=VecStr;
}

void XRTSPInfo::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_pMultiVideoWindow=p;
}

XMultiVideoWindow* XRTSPInfo::GetMultiVideoWindow()
{
	return m_pMultiVideoWindow;
}

void XRTSPInfo::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XRTSPInfo::GetIPAddr()
{
	return m_szIPAddr;
}

void XRTSPInfo::SetUseName(CString szUseName)
{
	m_szUseName=szUseName;
}

CString XRTSPInfo::GetUseName()
{
	return m_szUseName;
}

void XRTSPInfo::SetPassWd(CString szPssWd)
{
	m_szPassWd=szPssWd;
}

CString XRTSPInfo::GetPassWd()
{
	return m_szPassWd;
}

void XRTSPInfo::SetIsHaveSignal(BOOL b)
{
	m_bIsHaveSignal=b;
}

BOOL XRTSPInfo::GetIsHaveSignal()
{
	return m_bIsHaveSignal;
}

void XRTSPInfo::SetIsHavePane(BOOL b)
{
	m_bIsHavePane=b;
}

BOOL XRTSPInfo::GetIsHavePane()
{
	return m_bIsHavePane;
}