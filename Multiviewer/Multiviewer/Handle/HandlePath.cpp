#include "StdAfx.h"
#include "HandlePath.h"

CString HandlePath::m_szAppFolderPath = _T("");

HandlePath::HandlePath(void)
{
}


HandlePath::~HandlePath(void)
{
}

void HandlePath::Init()
{
	m_szAppFolderPath = GetAppFolderPath();
}

CString HandlePath::GetAppFolderPath()
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

BOOL HandlePath::PathExists(CString szPath)
{
	return PathFileExists(szPath);
}

CString HandlePath::GetTranslationFilePath(CString szName)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Translation\\%s"), m_szAppFolderPath, szName);

	return temp;
}

CString HandlePath::GetDataFilePath(CString szName)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Data\\%s"), m_szAppFolderPath, szName);

	return temp;
}

CString HandlePath::GetSceneFolderPath()
{
	CString temp;

	temp.Format(_T("%s\\Data\\Scene"), m_szAppFolderPath);

	return temp;
}

CString HandlePath::GetDumpFolderPath()
{
	CString temp;

	temp.Format(_T("%s\\Data\\Dump"), m_szAppFolderPath);

	return temp;
}

CString HandlePath::GetIniPath(CString name)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Ini\\%s"), m_szAppFolderPath, name);

	return temp;
}

CString HandlePath::GetPhotoPath(CString szPhotoName)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Photo\\%s"), m_szAppFolderPath, szPhotoName);

	return temp;
}

CString HandlePath::GetFontPath(CString szFont)
{
	CString temp;

	temp.Format(_T("%s\\Data\\Font\\%s"), m_szAppFolderPath, szFont);

	return temp;
}