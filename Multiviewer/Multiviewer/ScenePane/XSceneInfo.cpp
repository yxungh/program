#include "stdafx.h"
#include "XSceneInfo.h"

XSceneInfo::XSceneInfo()
{
	m_nType=0;

	m_nSceneIndex=0;

	m_bIsInGroup=FALSE;

	m_szSceneName=_T("");

	m_szGroupName=_T("");
}

XSceneInfo::~XSceneInfo()
{
	ClearMapSelScene();
}

void XSceneInfo::ClearMapSelScene()
{
	m_MapSelScene.clear();
}

void XSceneInfo::SetType(int n)
{
	m_nType=n;
}

int XSceneInfo::GetType()
{
	return m_nType;
}

void XSceneInfo::SetSceneIndex(int n)
{
	m_nSceneIndex=n;
}

int XSceneInfo::GetSceneIndex()
{
	return m_nSceneIndex;
}

void XSceneInfo::InsertMapSelScene(CString szViewName,int nIndex)
{
	m_MapSelScene.insert(std::pair<int,CString>(nIndex,szViewName));
}

MAP_SELSCENE& XSceneInfo::GetMapSelScene()
{
	return m_MapSelScene;
}


void XSceneInfo::CopyMapSelScene(MAP_SELSCENE& MapSelScene)
{
	for(MAP_SELSCENE::iterator iter=MapSelScene.begin();iter!=MapSelScene.end();++iter)
	{
		int nIndex=iter->first;

		CString szViewName=iter->second;

		m_MapSelScene.insert(std::pair<int,CString>(nIndex,szViewName));
	}
}
