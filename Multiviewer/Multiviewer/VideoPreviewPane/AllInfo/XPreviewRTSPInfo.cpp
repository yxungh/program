#include "stdafx.h"
#include "XPreviewRTSPInfo.h"

XPreviewRTSPInfo::XPreviewRTSPInfo()
{
	m_szRTSPAddr=_T("");

	m_nBoardIndex=0;
}
XPreviewRTSPInfo::~XPreviewRTSPInfo()
{

}

void XPreviewRTSPInfo::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XPreviewRTSPInfo::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XPreviewRTSPInfo::SetRTAPAddr(CString szRTSPAddr)
{
	m_szRTSPAddr=szRTSPAddr;
}

CString XPreviewRTSPInfo::GetRTSPAddr()
{
	return m_szRTSPAddr;
}