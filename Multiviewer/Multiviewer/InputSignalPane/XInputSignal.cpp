#include "StdAfx.h"
#include "XInputSignal.h"
#include "XInputSignalExpand.h"

XInputSignal::XInputSignal()
{
	m_InputIndex = -1;

	m_TreeItem = NULL;

	m_DefaultExpandID = 1;

	m_ReSignalIndex=-1;

	m_ReSignalChenal=-1;

	m_ReStatus=1;

	m_ReResulationH=1920;

	m_ReResulationV=1080;

	m_ReRefresh=0;

	m_ReVideoSelect=0;

	m_IsUltra=FALSE;

	m_AnotherName=_T("");

	m_szRTSPAddr=_T("");

	m_szIPAddr=_T("");

	m_szRTSPName=_T("");

	m_szRTSPPassWd=_T("");

	m_szGroupName=_T("");

	m_bIsInGroup=FALSE;
}

XInputSignal::~XInputSignal(void)
{
	ClearVecExpand();
}

void XInputSignal::ClearVecExpand()
{
	for (VEC_INPUTSIGNALEXPAND::iterator iter = m_VecExpand.begin(); iter != m_VecExpand.end(); iter++)
		delete *iter;

	m_VecExpand.clear();
}

void XInputSignal::SetInputIndex(int n)
{
	m_InputIndex = n;
}

int XInputSignal::GetInputIndex()
{
	return m_InputIndex;
}

CString XInputSignal::GetRTSPAddr()
{
	return m_szRTSPAddr;
}

void XInputSignal::SetRTSPAddr(CString szRTSP)
{
	m_szRTSPAddr=szRTSP;
}

CString XInputSignal::GetIPAddr()
{
	return m_szIPAddr;
}

void XInputSignal::SetIPAddr(CString szIP)
{
	m_szIPAddr=szIP;
}

CString XInputSignal::GetUseName()
{
	return m_szRTSPName;
}

void XInputSignal::SetUseName(CString szUseName)
{
	m_szRTSPName=szUseName;
}

CString XInputSignal::GetPassWd()
{
	return m_szRTSPPassWd;
}

void XInputSignal::SetPassWd(CString szPassWd)
{
	m_szRTSPPassWd=szPassWd;
}

void XInputSignal::SetTreeItem(HTREEITEM h)
{
	m_TreeItem = h;
}

HTREEITEM XInputSignal::GetTreeItem()
{
	return m_TreeItem;
}

void XInputSignal::SetGroupName(CString szName)
{
	m_szGroupName=szName;
}

CString XInputSignal::GetGroupName()
{
	return m_szGroupName;
}

void XInputSignal::SetIsInGroup(BOOL b)
{
	m_bIsInGroup=b;
}

BOOL XInputSignal::GetIsInGroup()
{
	return m_bIsInGroup;
}

void XInputSignal::AddExpand(XInputSignalExpand* p)
{
	m_VecExpand.push_back(p);
}

VEC_INPUTSIGNALEXPAND& XInputSignal::GetVecExpand()
{
	return m_VecExpand;
}

void XInputSignal::DeleteExpand(XInputSignalExpand* p)
{
	for (VEC_INPUTSIGNALEXPAND::iterator iter = m_VecExpand.begin(); iter != m_VecExpand.end(); iter++)
	{
		XInputSignalExpand* pExpand=*iter;

		if (pExpand==p)
		{
			m_VecExpand.erase(iter);
			delete pExpand;
			break;
		}
	}
}

BOOL XInputSignal::DecideExpandNameExist(XInputSignalExpand* pExpand, CString szName)
{
	for (VEC_INPUTSIGNALEXPAND::iterator iter = m_VecExpand.begin(); iter != m_VecExpand.end(); iter++)
	{
		XInputSignalExpand* pTemp = *iter;

		if (pTemp != pExpand)
		{
			if (pTemp->GetName() == szName)
				return TRUE;
		}
	}

	return FALSE;
}

XOSDInfo* XInputSignal::GetOSDInfo()
{
	return &m_OSDInfo;
}

XInputSignalExpand* XInputSignal::GetDefaultExpand()
{
	XInputSignalExpand* pExpand = GetExpandByID(m_DefaultExpandID);
	return pExpand;
}

XBorderOverlay* XInputSignal::GetBorderOverLay()
{
	return &m_Border;
}

XSignalCutInfo* XInputSignal::GetDefaultCutInfo()
{
	return &m_CutInfo;
}

XEDIDInfo* XInputSignal::GetEDIDInfo()
{
	return &m_EDIDInfo;
}

XStreamAddrInfo* XInputSignal::GetStreamInfo()
{
	return &m_StreamInfo;
}

XPaneIPAddrInfo* XInputSignal::GetPaneIPAddrInfo()
{
	return &m_PaneIPInfo;
}

void XInputSignal::SetDefaultExpandID(int nID)
{
	m_DefaultExpandID = nID;
}

int XInputSignal::GetNewExpandID()
{
	int nID = 1;

	for(VEC_INPUTSIGNALEXPAND::iterator iter=m_VecExpand.begin();iter!=m_VecExpand.end();iter++)
	{
		XInputSignalExpand* pTemp=*iter;

		if (pTemp->GetID()>nID)
			nID = pTemp->GetID();
	}

	return nID+1;
}

XInputSignalExpand* XInputSignal::GetExpandByID(int nID)
{
	for (VEC_INPUTSIGNALEXPAND::iterator iter = m_VecExpand.begin(); iter != m_VecExpand.end(); iter++)
	{
		XInputSignalExpand* pTemp = *iter;

		if (pTemp->GetID() == nID)
			return pTemp;
	}

	return NULL;
}


int XInputSignal::GetDefaultExpandID()
{
	return m_DefaultExpandID;
}

void XInputSignal::ResetDefaultExpandID()
{
	m_DefaultExpandID = 1;
}

void XInputSignal::SetAnotherName(CString szName)
{
	m_AnotherName=szName;
}

CString XInputSignal::GetAnotherName()
{
	return m_AnotherName;
}

BOOL XInputSignal::GetIsUltra()
{
	return m_IsUltra;
}

void XInputSignal::SetIsUltra(BOOL b)
{
	m_IsUltra=b;
}

void XInputSignal::SetReStatus(int n)
{
	m_ReStatus=n;
}

void XInputSignal::SetReResulationH(int n)
{
	m_ReResulationH=n;
}

void XInputSignal::SetReResulationV(int n)
{
	m_ReResulationV=n;
}
void XInputSignal::SetReRefresh(int n)
{
	m_ReRefresh=n;
}

void XInputSignal::SetReVideoSelect(int n)
{
	m_ReVideoSelect=n;
}

void XInputSignal::SetReDataLen(int n)
{
	m_ReDataLen=n;
}

void XInputSignal::SetChanel(int n)
{
	m_Chenal=n;
}

int XInputSignal::GetReSignalIndex()
{
	return m_ReSignalIndex;
}

int XInputSignal::GetReSignalChenal()
{
	return m_ReSignalChenal;
}

int XInputSignal::GetReStatus()
{
	return m_ReStatus;
}

int XInputSignal::GetReResulationH()
{
	return m_ReResulationH;
}

int XInputSignal::GetReResulationV()
{
	return m_ReResulationV;
}

int XInputSignal::GetReRefresh()
{
	return m_ReRefresh;
}

int XInputSignal::GetReVideoSelect()
{
	return m_ReVideoSelect;
}

int XInputSignal::GetReDataLen()
{
	return m_ReDataLen;
}

int XInputSignal::GetChanel()
{
	return m_Chenal;
}

