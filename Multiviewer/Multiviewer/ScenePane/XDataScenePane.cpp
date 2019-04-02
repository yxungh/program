#include "Stdafx.h"
#include "XDataScenePane.h"
#include "XConstantIM.h"
#include "XScenePane.h"
#include "XSceneInfo.h"
#include "XSceneGroupInfo.h"

XDataScenePane::XDataScenePane()
{

}

XDataScenePane::~XDataScenePane()
{

}

void XDataScenePane::GetData(XScenePane* pPane, CArchive& arch)
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

void XDataScenePane::GetDataOfVersion1(XScenePane* pPane, CArchive& arch)
{
	//pPane->ClearMapScene();

	int nSize=0;

	arch>>nSize;

	MAP_SCENE& MapScene=pPane->GetMapScene();

	for(int i=0;i<nSize;i++)
	{
		CString szSceneName=_T("");
		arch>>szSceneName;

		int nType=0;
		arch>>nType;

		int nSceneIndex=0;
		arch>>nSceneIndex;

		BOOL bIsInGroup=FALSE;
		arch>>bIsInGroup;

		CString szSceneName2=_T("");
		arch>>szSceneName2;

		CString szGroupName=_T("");
		arch>>szGroupName;


		XSceneInfo* pInfo=new XSceneInfo;

		pInfo->SetType(nType);

		pInfo->SetSceneIndex(nSceneIndex);

		pInfo->SetIsInGroup(bIsInGroup);
	
		pInfo->SetSceneName(szSceneName2);

		pInfo->SetGroupName(szGroupName);

		MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();
		int nCount=0;
		arch>>nCount;

		for(int n=0;n<nCount;n++)
		{
			int nIndex=0;
			arch>>nIndex;

			CString szViewName;
			arch>>szViewName;
			
			MapSelScene.insert(std::pair<int,CString>(nIndex,szViewName));

		}

		MAP_SCENE::iterator iter=MapScene.find(szSceneName);

		if(iter==MapScene.end())
		{
			MapScene.insert(std::pair<CString,XSceneInfo*>(szSceneName,pInfo));
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//pPane->ClearSceneGroup();

	MAP_SCENEGROUP& MapGroup=pPane->GetMapSceneGroup();

	int nCount=0;
	
	arch>>nCount;

	for(int i=0;i<nCount;i++)
	{
		CString szGroupName=_T("");

		arch>>szGroupName;

		CString szGroupName2=_T("");
		arch>>szGroupName2;

		int nSceneIndex=0;
		arch>>nSceneIndex;

		CString szSceenName=_T("");
		arch>>szSceenName;

		int nSceenType=0;
		arch>>nSceenType;

		XSceneGroupInfo* pInfo=new XSceneGroupInfo;

		pInfo->SetGroupName(szGroupName2);
		pInfo->SetSceneIndex(nSceneIndex);
		pInfo->SetSceneName(szSceenName);
		pInfo->SetSceneType(nSceenType);

		MapGroup.insert(std::pair<CString,XSceneGroupInfo*>(szGroupName,pInfo));
	}
}

//////////////////////////////////////////////////////////////////////////

void XDataScenePane::SaveData(XScenePane* pPane, CArchive& arch)
{
	arch<<SCENEPANE_DATAVERSION;

	MAP_SCENE& MapScene=pPane->GetMapScene();

	arch<<MapScene.size();

	for(MAP_SCENE::iterator iter=MapScene.begin();iter!=MapScene.end();++iter)
	{
		CString szSceneName=iter->first;

		arch<<szSceneName;

		XSceneInfo* pInfo=iter->second;

		arch<<pInfo->GetType();

		arch<<pInfo->GetSceneIndex();

		arch<<pInfo->GetIsInGroup();

		arch<<pInfo->GetSceneName();

		arch<<pInfo->GetGroupName();

		MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();

		arch<<MapSelScene.size();

		for(MAP_SELSCENE::iterator iterMap=MapSelScene.begin();iterMap!=MapSelScene.end();++iterMap)
		{
			int nIndex=iterMap->first;
			arch<<nIndex;

			CString szViewName=iterMap->second;
			arch<<szViewName;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	MAP_SCENEGROUP& MapGroup=pPane->GetMapSceneGroup();

	arch<<MapGroup.size();

	for(MAP_SCENEGROUP::iterator iter=MapGroup.begin();iter!=MapGroup.end();++iter)
	{
		CString szGroupName=iter->first;

		arch<<szGroupName;

		XSceneGroupInfo* pInfo=iter->second;

		arch<<pInfo->GetGroupName()
			<<pInfo->GetSceneIndex()
			<<pInfo->GetSceneName()
			<<pInfo->GetSceneType();
	}
}