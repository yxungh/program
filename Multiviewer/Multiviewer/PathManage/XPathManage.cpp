#include "StdAfx.h"
#include "XPathManage.h"


XPathManage::XPathManage(void)
{
}


XPathManage::~XPathManage(void)
{
}

void XPathManage::Init()
{
	m_szAppFolderPath = GetAppFolderPath();
}

CString XPathManage::GetAppFolderPath()
{
	CString temp = _T("");

	TCHAR path[MAX_PATH];

	if (GetModuleFileName(NULL, path, MAX_PATH) != 0)
	{
		PathRemoveFileSpec(path);

		temp = path;
	}

	return temp;
}

CString XPathManage::GetTranslationFilePath(CString szName)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Translation\\%s"), m_szAppFolderPath, szName);

	return temp;
}

CString XPathManage::GetDataFilePath(CString szName)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Data\\%s"), m_szAppFolderPath, szName);

	return temp;
}

CString XPathManage::GetSceneFilePath(int nSceneIndex, CString szSceneName)
{
	CString temp;

	temp.Format(_T("%s\\%d.%s.sce"), GetSceneFolderPath(), nSceneIndex, szSceneName);

	return temp;
}

CString XPathManage::GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex)
{
	CString temp;

	temp.Format(_T("%s\\%d.%d-%s.sce"), GetSceneFolderPath(), nSceneIndex, nIndex,szSceneName);

	return temp;
}

CString XPathManage::GetSceneFolderPath()
{
	CString temp;

	temp.Format(_T("%s\\Data\\Scene"), m_szAppFolderPath);

	return temp;
}

CString XPathManage::GetDumpFilePath()
{
	CString temp;

	temp.Format(_T("%s\\dump.dmp"), m_szAppFolderPath);

	return temp;
}