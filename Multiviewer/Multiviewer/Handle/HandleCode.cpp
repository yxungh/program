#include "stdafx.h"
#include "HandleCode.h"

CString HandleCode::ConvertAsciitoUnicode(char* pData)
{
	int unicodeLen = MultiByteToWideChar(CP_ACP, 0, pData, -1, NULL, 0);  

	TCHAR* pUnicode;  
	pUnicode = new TCHAR[unicodeLen];  

	MultiByteToWideChar(CP_ACP, 0, pData, -1, (LPWSTR)pUnicode, unicodeLen);  

	CString szTemp;
	szTemp.Format(_T("%s"), pUnicode);

	delete []pUnicode; 

	pUnicode = NULL;

	return szTemp;
}

void HandleCode::ConvertUnicodeToAscii(const CString &szData, char*& pData, int& nDataLen)
{
	int nDataLength;

	nDataLength = WideCharToMultiByte(CP_ACP, 0, szData, -1 ,NULL, 0, NULL, FALSE);

	pData = new char[nDataLength];

	WideCharToMultiByte(CP_ACP, 0, szData, -1, pData, nDataLength, NULL, 0);     

	pData[nDataLength - 1] = '\0';

	nDataLen =  nDataLength - 1;
}

void HandleCode::GetUTF8FromUnicode(const CString& szSrc,char* pDes)
{
	int len=0;

	len=WideCharToMultiByte(CP_UTF8,0,szSrc,-1,NULL,0,NULL,NULL);

	pDes=new char[len+1];
	//pDes=(char*)malloc(len+1);

	memset(pDes,0,len+1);

	WideCharToMultiByte(CP_UTF8,0,szSrc,-1,pDes,len,NULL,NULL);
}