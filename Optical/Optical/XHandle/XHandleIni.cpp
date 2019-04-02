#include "StdAfx.h"
#include "XHandleIni.h"

XHandleIni::XHandleIni(void)
{
}


XHandleIni::~XHandleIni(void)
{
}

int XHandleIni::GetInt(CString szAppName, CString szKeyName, int nDefault, 
	CString szPath)
{
	return GetPrivateProfileInt(szAppName, szKeyName, nDefault, szPath);
}

CString XHandleIni::GetString(CString szAppName, CString szKeyName, CString szDefault, 
	CString szPath)
{
	TCHAR data[MAX_PATH];

	GetPrivateProfileString(szAppName, szKeyName, szDefault, data, MAX_PATH, szPath);

	return data;
}

BOOL XHandleIni::WriteData(CString szAppName, CString szKeyName, CString szData, 
	CString szPath)
{
	return WritePrivateProfileString(szAppName, szKeyName, szData, szPath);
}