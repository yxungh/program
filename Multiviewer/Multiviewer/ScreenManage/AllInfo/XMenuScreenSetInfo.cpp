#include "stdafx.h"
#include "XMenuScreenSetInfo.h"
#include "XEquipmentOutput.h"
#include "XOutputInfo.h"

#define SCREENSET_VERSION 1

XMenuScreenSetInfo::XMenuScreenSetInfo()
{
	m_nCheck=0;

	m_nScreenCountH=2;

	m_nScreenCountV=2;

	m_nScreenModel=SCREENMODEL_SPLIC;
}

XMenuScreenSetInfo::~XMenuScreenSetInfo()
{
	ClearOutputInfo();
}

void XMenuScreenSetInfo::ClearOutputInfo()
{
	for(VEC_OUTPUTINFO::iterator iter=m_VecOutputInfo.begin();iter!=m_VecOutputInfo.end();++iter)
	{
		delete *iter;
	}

	m_VecOutputInfo.clear();
}

void XMenuScreenSetInfo::SetCheck(int n)
{
	m_nCheck=n;
}

int XMenuScreenSetInfo::GetCheck()
{
	return m_nCheck;
}

void XMenuScreenSetInfo::SetScreenCountH(int n)
{
	m_nScreenCountH=n;
}

int XMenuScreenSetInfo::GetScreenCountH()
{
	return m_nScreenCountH;
}

void XMenuScreenSetInfo::SetScreenCountV(int n)
{
	m_nScreenCountV=n;
}

int XMenuScreenSetInfo::GetScreenCountV()
{
	return m_nScreenCountV;
}

void XMenuScreenSetInfo::SetScreenModel(int nModel)
{
	m_nScreenModel=nModel;
}

int XMenuScreenSetInfo::GetScreenModel()
{
	return m_nScreenModel;
}


VEC_OUTPUTINFO XMenuScreenSetInfo::GetVecOutputInfo()
{
	return m_VecOutputInfo;
}

void XMenuScreenSetInfo::AddOutputInfo(XOutputInfo* pInfo)
{
	if(pInfo!=NULL)
	{
		m_VecOutputInfo.push_back(pInfo);
	}
}

void XMenuScreenSetInfo::GetData(CArchive& arch)
{
	int nVersion;
	arch>>nVersion
		>>m_nCheck
		>>m_nScreenCountH
		>>m_nScreenCountV;

	int nCount=0;
	arch>>nCount;

	for(int i=0;i<nCount;i++)
	{
		XOutputInfo* pNewOutput=new XOutputInfo;

		int nBoardIndex=0;
		arch>>nBoardIndex;
		pNewOutput->SetBoardIndex(nBoardIndex);

		CString szInputName=_T("");
		arch>>szInputName;
		pNewOutput->SetInputName(szInputName);

		BOOL bIsFirstPan;
		arch>>bIsFirstPan;
		pNewOutput->SetIsFirstPan(bIsFirstPan);

		BOOL bIsTwoScreen;
		arch>>bIsTwoScreen;
		pNewOutput->SetIsTwoScreen(bIsTwoScreen);

		int nScreenIndex1;
		arch>>nScreenIndex1;
		pNewOutput->SetScreenIndex1(nScreenIndex1);

		int nScreenIndex2;
		arch>>nScreenIndex2;
		pNewOutput->SetScreenIndex2(nScreenIndex2);

		int nScreenIndex3;
		arch>>nScreenIndex3;
		pNewOutput->SetScreenIndex3(nScreenIndex3);

		int nScreenIndex4;
		arch>>nScreenIndex4;
		pNewOutput->SetScreenIndex4(nScreenIndex4);

		int nCorrpScreenNum;
		arch>>nCorrpScreenNum;
		pNewOutput->SetCorrpScreenNum(nCorrpScreenNum);

		int nCheckNum=0;
		arch>>nCheckNum;
		pNewOutput->SetCheckNum(nCheckNum);

		MAP_NUMOFSCREEN MapNumOfScreen;

		int nSize=0;
		arch>>nSize;

		for(int j=0;j<nSize;j++)
		{
			int nScreenIndex=0;
			arch>>nScreenIndex;

			int nScreenNum=0;
			arch>>nScreenNum;

			MapNumOfScreen.insert(std::pair<int,int>(nScreenIndex,nScreenNum));
		}

		pNewOutput->SetMapScreenNum(MapNumOfScreen);

		m_VecOutputInfo.push_back(pNewOutput);
	}
}

void XMenuScreenSetInfo::SaveData(CArchive& arch)
{
	arch<<SCREENSET_VERSION
		<<m_nCheck
		<<m_nScreenCountH
		<<m_nScreenCountV;

	int nCount=m_VecOutputInfo.size();
	arch<<nCount;

	for(VEC_OUTPUTINFO::iterator iter=m_VecOutputInfo.begin();iter!=m_VecOutputInfo.end();++iter)
	{
		XOutputInfo* pOutput=*iter;

		arch<<pOutput->GetBoardIndex()
			<<pOutput->GetInputName()
			<<pOutput->GetIsFirstPan()
			<<pOutput->GetIsTwoScreen()
			<<pOutput->GetScreenIndex1()
			<<pOutput->GetScreenIndex2()
			<<pOutput->GetScreenIndex3()
			<<pOutput->GetScreenIndex4()
			<<pOutput->GetCorrpScreenNum()
			<<pOutput->GetCheckNum();

		MAP_NUMOFSCREEN& MapNumOfScreen=pOutput->GetMapScreenNum();

		int nSize=MapNumOfScreen.size();
		arch<<nSize;

		if(nSize>0)
		{
			for(MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.begin();iter!=MapNumOfScreen.end();++iter)
			{
				arch<<iter->first;

				arch<<iter->second;
			}
		}
	}
}







