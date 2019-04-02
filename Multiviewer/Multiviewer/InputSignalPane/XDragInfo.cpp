#include "StdAfx.h"
#include "XDragInfo.h"
#include "XMultiVideoWindowFrame.h"

XDragInfo::XDragInfo()
{
	m_InputIndex = 0;

	m_Text = _T("");

	m_IsUltra=FALSE;

	m_szScreenIP=_T("");

	m_szRTSPAddr=_T("");

	m_pFrame=NULL;

	m_SignalresulationH=0;

	m_SignalresulationV=0;

	m_nInputNum=0;

	m_pMultiVideoWindow=NULL;

	m_szIPAddr=_T("");

	m_szUseName=_T("");

	m_szPassWd=_T("");

	m_bIsHavePane=FALSE;

	m_bIsHaveSignal=FALSE;
}

XDragInfo::~XDragInfo(void)
{

}

int XDragInfo::GetInputIndex()
{
	return m_InputIndex;
}

void XDragInfo::SetInputIndex(int n)
{
	m_InputIndex = n;
}

void XDragInfo::SetExpand(XExpandInfo* pInfo)
{
	m_ExpandInfo = *pInfo;
}

XExpandInfo* XDragInfo::GetExpandInfo()
{
	return &m_ExpandInfo;
}


CString XDragInfo::GetText()
{
	return m_Text;
}

void XDragInfo::SetText(CString s)
{
	m_Text = s;
}

unsigned int XDragInfo::GetSignalID()
{
	return m_signalID;
}

void XDragInfo::SetSignalID(unsigned int ID)
{
	m_signalID=ID;
}

unsigned int XDragInfo::GetSignalGroupID()
{
	return m_signalGroupID;
}

void XDragInfo::SetSignalGroupID(unsigned int ID)
{
	m_signalGroupID=ID;
}

unsigned int XDragInfo::GetDragSignalID()
{
	return m_nDragSignalID;
}

void XDragInfo::SetDragSignalID(unsigned int SignalID)
{
	m_nDragSignalID=SignalID;
}

unsigned int XDragInfo::GetDragSignalGroupID()
{
	return m_nDragSignalGroupID;
}

void XDragInfo::SetDragSignalGroupID(unsigned int SignalID)
{
	m_nDragSignalGroupID=SignalID;
}

void XDragInfo::SetSignalResulationH(int n)
{
	m_SignalresulationH=n;
}

int XDragInfo::GetSignalResulationH()
{
	return m_SignalresulationH;
}

void XDragInfo::SetSignalResulationV(int n)
{
	m_SignalresulationV=n;
}

int XDragInfo::GetSignalResulationV()
{
	return m_SignalresulationV;
}

void XDragInfo::SetAnotherName(CString szName)
{
	m_AnotherName=szName;
}

CString XDragInfo::GetAnotherName()
{
	return m_AnotherName;
}

BOOL XDragInfo::GetIsUltra()
{
	return m_IsUltra;
}

void XDragInfo::SetIsUltra(BOOL b)
{
	m_IsUltra=b;
}

VEC_UNINT& XDragInfo::GetVecSignalID()
{
	return m_VecSignalID;
}

void XDragInfo::SetVecSignalID(VEC_UNINT& VecInt)
{
	m_VecSignalID=VecInt;
}

HYVEC_NUM& XDragInfo::GetVecSignalIndex()
{
	return m_VecSignalIndex;
}

void XDragInfo::SetVecSignalIndex(HYVEC_NUM& VecIndex)
{
	m_VecSignalIndex=VecIndex;
}

VEC_UNINT& XDragInfo::GetVecDragSignalID()
{
	return m_VecDragSignalID;
}
void XDragInfo::SetVecDragSignalID(VEC_UNINT& VecInt)
{
	m_VecDragSignalID=VecInt;
}

HYVEC_NUM& XDragInfo::GetVecDragSignalIndex()
{
	return m_VecDragSignalIndex;
}
void XDragInfo::SetVecDragSignalIndex(HYVEC_NUM& VecIndex)
{
	m_VecDragSignalIndex=VecIndex;
}

VEC_UNINT& XDragInfo::GetVecExpandSignalID()
{
	return m_VecExpandSignalID;
}

void XDragInfo::SetVecExpandSignalID(VEC_UNINT& VecInt)
{
	m_VecExpandSignalID=VecInt;
}

HYVEC_NUM& XDragInfo::GetVecExpandSignalIndex()
{
	return m_VecExpandSignalIndex;
}

void XDragInfo::SetVecExpandSignalIndex(HYVEC_NUM& VecIndex)
{
	m_VecExpandSignalIndex=VecIndex;
}

VEC_UNINT& XDragInfo::GetVecChangeInputID()
{
	return m_VecChangeInputID;
}

void XDragInfo::SetVecChangeInputID(VEC_UNINT& VecInt)
{
	m_VecChangeInputID=VecInt;
}

CString XDragInfo::GetRTSPAddr()
{
	return m_szRTSPAddr;
}

void XDragInfo::SetRTSPAddr(CString s)
{
	m_szRTSPAddr=s;
}

void XDragInfo::ClearRTSPData()
{
	m_szRTSPAddr=_T("");
}

CString XDragInfo::GetScreenIP()
{
	return m_szScreenIP;
}

void XDragInfo::SetScreenIP(CString szIP)
{
	m_szScreenIP=szIP;
}

XMultiVideoWindowFrame* XDragInfo::GetPreviewFrame()
{
	return m_pFrame;
}

void XDragInfo::SetPreviewFrame(XMultiVideoWindowFrame* p)
{
	m_pFrame=p;
}

int XDragInfo::GetInputNum()
{
	return m_nInputNum;
}

void XDragInfo::SetInputNum(int n)
{
	m_nInputNum=n;
}

VEC_CSTRING& XDragInfo::GetVecRTSPAddr()
{
	return m_VecRTSPAddr;
}

void XDragInfo::SetVecRTSPAddr(VEC_CSTRING& VecStr)
{
	m_VecRTSPAddr=VecStr;
}

XMultiVideoWindow* XDragInfo::GetMultiVideoWindow()
{
	return m_pMultiVideoWindow;
}

void XDragInfo::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_pMultiVideoWindow=p;
}

CString XDragInfo::GetIPAddr()
{
	return m_szIPAddr;
}

void XDragInfo::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XDragInfo::GetUseName()
{
	return m_szUseName;
}

void XDragInfo::SetUseName(CString szUseName)
{
	m_szUseName=szUseName;
}

CString XDragInfo::GetPassWd()
{
	return m_szPassWd;
}

void XDragInfo::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

BOOL XDragInfo::GetIsHaveSignal()
{
	return m_bIsHaveSignal;
}

void XDragInfo::SetIsHaveSignal(BOOL b)
{
	m_bIsHaveSignal=b;
}

BOOL XDragInfo::GetIsHavePane()
{
	return m_bIsHavePane;
}

void XDragInfo::SetIsHavePane(BOOL b)
{
	m_bIsHavePane=b;
}