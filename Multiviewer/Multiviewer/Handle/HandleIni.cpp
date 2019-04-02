#include "StdAfx.h"
#include "HandleIni.h"

HandleIni::HandleIni(void)
{
}


HandleIni::~HandleIni(void)
{
}

int HandleIni::GetInt(CString szAppName, CString szKeyName, int nDefault, 
	CString szPath)
{
	return GetPrivateProfileInt(szAppName, szKeyName, nDefault, szPath);
}

CString HandleIni::GetString(CString szAppName, CString szKeyName, CString szDefault, 
	CString szPath)
{
	TCHAR data[MAX_PATH];

	GetPrivateProfileString(szAppName, szKeyName, szDefault, data, MAX_PATH, szPath);

	return data;
}

BOOL HandleIni::WriteData(CString szAppName, CString szKeyName, CString szData, 
	CString szPath)
{
	return WritePrivateProfileString(szAppName, szKeyName, szData, szPath);
}