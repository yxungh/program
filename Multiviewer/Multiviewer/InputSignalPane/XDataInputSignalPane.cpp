#include "StdAfx.h"
#include "XDataInputSignalPane.h"
#include "XInputSignalPane.h"
#include "XDataInputSignalPane.h"
#include "XConstantIM.h"
#include "XInputSignalExpand.h"
#include "XInputSignal.h"
#include "XInputGroup.h"
#include "XInputInfoInGroup.h"

XDataInputSignalPane::XDataInputSignalPane(void)
{
}


XDataInputSignalPane::~XDataInputSignalPane(void)
{
}

void XDataInputSignalPane::GetData(XInputSignalPane* pPane, CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	switch(nVersion)
	{
	case 1:
		{
			GetDataOfVersion1(pPane, arch);
		}
		break;
	default:
		break;
	}
}

void XDataInputSignalPane::GetDataOfVersion1(XInputSignalPane* pPane, CArchive& arch)
{
	GetVecInputSignal(pPane,arch);

	GetMapInputGroup(pPane,arch);
}

void XDataInputSignalPane::GetVecInputSignal(XInputSignalPane* pPane,CArchive& arch)
{
	int nInput = 0;
	arch>>nInput;

	pPane->SetInputCount(nInput);

	//BOOL bTreeStatus;
	//arch>>bTreeStatus;
	//pPane->SetTreeStatus(bTreeStatus);
	//////////////////////////////////////////////////////////////
	VEC_INPUTSIGNAL& VecInputSignal = pPane->GetVecInputSignal();

	int nInputSignalCount;
	arch>>nInputSignalCount;

	for (int i = 0; i < nInputSignalCount; i++)
	{
		XInputSignal* pInputSignal = new XInputSignal;

		GetVecInput(pInputSignal,arch);

		VecInputSignal.push_back(pInputSignal);
	}
}

void XDataInputSignalPane::GetMapInputGroup(XInputSignalPane* pPane,CArchive& arch)
{
	MAP_GROUP& MapInputGroup=pPane->GetMapGroup();

	int nGroupSize=0;
	arch>>nGroupSize;

	for(int i=0;i<nGroupSize;i++)
	{
		CString szName=_T("");
		arch>>szName;

		CString szGroupName=_T("");
		arch>>szGroupName;

		int nType=-1;
		arch>>nType;

		//HTREEITEM h;
		//arch>>h;

		MAP_GROUP::iterator iter=MapInputGroup.find(szName);

		XInputGroup* pGroup=NULL;

		if(iter==MapInputGroup.end())
		{
			pGroup=new XInputGroup;
		}
		else
		{
			pGroup=iter->second;
		}


		pGroup->SetGroupName(szGroupName);
		pGroup->SetType(nType);
		//pGroup->SetTreeItem(h);
		//////////////////////////////////////////////////////////////////////////

		VEC_INPUTINFOINGROUP& VecInputSignal=pGroup->GetVecInputInGroup();

		int nInputSignalSize=0;
		arch>>nInputSignalSize;

		for(int j=0;j<nInputSignalSize;j++)
		{
			XInputInfoInGroup* pInputSignal = new XInputInfoInGroup;

			int nIndex=0;
			arch>>nIndex;

			CString szAnotherName;
			arch>>szAnotherName;

			CString szGroupName;
			arch>>szGroupName;

			pInputSignal->SetIndex(nIndex);
			pInputSignal->SetAnotherName(szAnotherName);
			pInputSignal->SetGroupName(szGroupName);

			VecInputSignal.push_back(pInputSignal);
		}

		MapInputGroup.insert(std::pair<CString,XInputGroup*>(szName,pGroup));
	}
}

void XDataInputSignalPane::GetVecInput(XInputSignal* pInputSignal,CArchive& arch)
{
	int nIndex = 0;
	arch>>nIndex;

	int nDefaultExpandID;
	arch>>nDefaultExpandID;

	CString szAnotherName;
	arch>>szAnotherName;

	CString szGroupName=_T("");
	arch>>szGroupName;

	BOOL bIsInGroup;
	arch>>bIsInGroup;

	CString szIP;
	arch>>szIP;

	CString szUserName;
	arch>>szUserName;

	CString szPassWd;
	arch>>szPassWd;

	CString szRTSPAddr;
	arch>>szRTSPAddr;

	pInputSignal->SetIsInGroup(bIsInGroup);
	pInputSignal->SetGroupName(szGroupName);
	pInputSignal->SetAnotherName(szAnotherName);
	pInputSignal->SetIPAddr(szIP);
	pInputSignal->SetUseName(szUserName);
	pInputSignal->SetPassWd(szPassWd);
	pInputSignal->SetRTSPAddr(szRTSPAddr);

	pInputSignal->GetOSDInfo()->GetData(arch);
	pInputSignal->GetDefaultCutInfo()->GetData(arch);
	pInputSignal->GetBorderOverLay()->GetData(arch);
	pInputSignal->GetEDIDInfo()->GetData(arch);
	pInputSignal->SetInputIndex(nIndex);
	pInputSignal->SetDefaultExpandID(nDefaultExpandID);

	/////////////////////////////////////////////
	int nExpandCount;
	arch>>nExpandCount;

	for (int j = 0; j < nExpandCount; j++)
	{
		XInputSignalExpand* pExpand = new XInputSignalExpand;

		CString szName;
		arch>>szName;

		BOOL bCanEdit;
		arch>>bCanEdit;

		int nID;
		arch>>nID;

		pExpand->GetExpandInfo()->GetData(arch);
		pExpand->SetName(szName);
		pExpand->SetCanEdit(bCanEdit);
		pExpand->SetID(nID);
		pExpand->SetInputSignal(pInputSignal);

		pInputSignal->AddExpand(pExpand);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void XDataInputSignalPane::SaveData(XInputSignalPane* pPane, CArchive& arch)
{
	SaveVecInputSignal(pPane,arch);

	SaveMapInputGroup(pPane,arch);
}

void XDataInputSignalPane::SaveVecInputSignal(XInputSignalPane* pPane,CArchive& arch)
{
	arch<<INPUTSIGNALPANE_DATAVERSION
		<<pPane->GetInputCount();

	//BOOL bTreeModel=pPane->GetTreeStatus();
	//BOOL b=!bTreeModel;

	//arch<<b;

	VEC_INPUTSIGNAL& VecInputSignal = pPane->GetVecInputSignal();

	arch<<VecInputSignal.size();

	for (VEC_INPUTSIGNAL::iterator iter = VecInputSignal.begin(); iter != VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		SaveVecInput(pInputSignal,arch);
	}
}

void XDataInputSignalPane::SaveMapInputGroup(XInputSignalPane* pPane,CArchive& arch)
{
	MAP_GROUP& MapGroup=pPane->GetMapGroup();

	arch<<MapGroup.size();

	for(MAP_GROUP::iterator iter=MapGroup.begin();iter!=MapGroup.end();++iter)
	{
		XInputGroup* pInputGroup=iter->second;

		CString szName=iter->first;
		arch<<szName;

		arch<<pInputGroup->GetGroupName()
			<<pInputGroup->GetType();


		//////////////////////////////////////////////////////////////////////////
		VEC_INPUTINFOINGROUP& VecInputSignal=pInputGroup->GetVecInputInGroup();

		arch<<VecInputSignal.size();

		for(VEC_INPUTINFOINGROUP::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
		{
			XInputInfoInGroup* pInputSignal=*iter;

			arch<<pInputSignal->GetIndex()
				<<pInputSignal->GetAnotherName()
				<<pInputSignal->GetGroupName();

		}
	}
}


void XDataInputSignalPane::SaveVecInput(XInputSignal* pInputSignal,CArchive& arch)
{
	arch<<pInputSignal->GetInputIndex()
		<<pInputSignal->GetDefaultExpandID()
		<<pInputSignal->GetAnotherName()
		<<pInputSignal->GetGroupName()
		<<pInputSignal->GetIsInGroup()
		<<pInputSignal->GetIPAddr()
		<<pInputSignal->GetUseName()
		<<pInputSignal->GetPassWd()
		<<pInputSignal->GetRTSPAddr();

	pInputSignal->GetOSDInfo()->SaveData(arch);
	pInputSignal->GetDefaultCutInfo()->SaveData(arch);
	pInputSignal->GetBorderOverLay()->SaveData(arch);
	pInputSignal->GetEDIDInfo()->SaveData(arch);

	///////////////////////////////////////////////////
	VEC_INPUTSIGNALEXPAND& VecExpand = pInputSignal->GetVecExpand();
	arch<<VecExpand.size();

	for (VEC_INPUTSIGNALEXPAND::iterator iterExpand = VecExpand.begin(); iterExpand != VecExpand.end(); iterExpand++)
	{
		XInputSignalExpand* pExpand = *iterExpand;

		arch<<pExpand->GetName()
			<<pExpand->GetCanEdit()
			<<pExpand->GetID();

		pExpand->GetExpandInfo()->SaveData(arch);
	}
}
