#pragma once


class XSceneGroupInfo
{
public:
	XSceneGroupInfo();
	~XSceneGroupInfo();

public:

	inline CString GetGroupName(){return m_szGroupName;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}

	inline int GetSceneIndex(){return m_nSceneIndex;}

	inline void SetSceneIndex(int n){m_nSceneIndex=n;}

	inline CString GetSceneName(){return m_szSceneName;}

	inline void SetSceneName(CString szName){m_szSceneName=szName;}

	inline int GetSceneType(){return m_nSceneType;}

	inline void SetSceneType(int nType){m_nSceneType=nType;}


private:

	CString m_szGroupName;

	int m_nSceneIndex;

	CString m_szSceneName;

	int m_nSceneType;
};