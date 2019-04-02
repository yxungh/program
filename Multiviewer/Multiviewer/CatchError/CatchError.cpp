#include "stdafx.h"
#include "CatchError.h"

#include "DbgHelp.h"
#pragma comment(lib,"DbgHelp.Lib") 

CString CatchError::m_DumpFolderPath = _T("");

/***********************************************************
** 功能描述: 创建Dump文件   	
************************************************************/
void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS* pException)  
{  
	// 创建Dump文件     
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  

	// Dump信息   
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;  
	dumpInfo.ExceptionPointers = pException;  
	dumpInfo.ThreadId = GetCurrentThreadId();  
	dumpInfo.ClientPointers = TRUE;  

	// 写入Dump文件内容   
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);  

	CloseHandle(hDumpFile);  
}  

/***********************************************************
** 功能描述: 应用程序异常调用函数	
************************************************************/
LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException)  
{     
	CreateDumpFile(CatchError::DumpPath(), pException);  

	FatalAppExit(-1, _T("The Application Error!"));  

	return EXCEPTION_EXECUTE_HANDLER;  
}

void CatchError::SetCatchError(CString folderPath)
{
	m_DumpFolderPath = folderPath;

	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}

CString CatchError::DumpPath()
{
	CString szTemp = _T("");

	CTime t = CTime::GetCurrentTime();

	szTemp.Format(_T("%s\\%d-%02d-%02d %02d-%02d.dmp"), m_DumpFolderPath, 
		t.GetYear(), 
		t.GetMonth(), 
		t.GetDay(), 
		t.GetHour(), 
		t.GetMinute(), 
		t.GetSecond());

	return szTemp;
}