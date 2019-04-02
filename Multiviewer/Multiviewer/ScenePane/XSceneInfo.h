#pragma once
#include "XConstantIM.h"

class XSceneInfo
{
public:

	XSceneInfo();
	~XSceneInfo();

public:

	void SetType(int n);

	int GetType();

	void SetSceneIndex(int n);

	int GetSceneIndex();

	void InsertMapSelScene(CString szViewName,int nIndex);

	void CopyMapSelScene(MAP_SELSCENE& MapSelScene);

	MAP_SELSCENE& GetMapSelScene();

	void ClearMapSelScene();

	inline void SetIsInGroup(BOOL b){m_bIsInGroup=b;}

	inline BOOL GetIsInGroup(){return m_bIsInGroup;}

	inline void SetSceneName(CString szName){m_szSceneName=szName;}

	inline CString GetSceneName(){return m_szSceneName;}

	inline void SetGroupName(CString szGroup){m_szGroupName=szGroup;}

	inline CString GetGroupName(){return m_szGroupName;}

private:

	int m_nType;

	int m_nSceneIndex;

	BOOL m_bIsInGroup;

	CString m_szSceneName;

	CString m_szGroupName;

	MAP_SELSCENE m_MapSelScene;
};