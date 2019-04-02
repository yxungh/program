#include "StdAfx.h"
#include "XHandlePath.h"

CString XHandlePath::m_szAppFolderPath = _T("");

XHandlePath::XHandlePath(void)
{
}


XHandlePath::~XHandlePath(void)
{
}

void XHandlePath::Init()
{
	m_szAppFolderPath = GetAppFolderPath();
}

CString XHandlePath::GetAppFolderPath()
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

BOOL XHandlePath::PathExists(CString szPath)
{
	return PathFileExists(szPath);
}

CString XHandlePath::GetPhotoPath(CString name)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Photo\\%s"), m_szAppFolderPath, name);

	return temp;
}

CString XHandlePath::GetDumpFolderPath()
{
	CString temp;

	temp.Format(_T("%s\\Data\\Dump"), m_szAppFolderPath);

	return temp;
}

CString XHandlePath::GetIniPath(CString name)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Ini\\%s"), m_szAppFolderPath, name);

	return temp;
}

CString XHandlePath::GetTranslationFilePath(CString name)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Translation\\%s"), m_szAppFolderPath, name);

	return temp;
}