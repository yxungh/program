#include "StdAfx.h"
#include "XDataUserManage.h"
#include "XUserManage.h"
#include "XConstantIM.h"
#include "XUserInfo.h"

#define KEYLEN 1024

XDataUserManage::XDataUserManage(void)
{
}


XDataUserManage::~XDataUserManage(void)
{
}

void XDataUserManage::SaveStringData(CArchive& arch, unsigned char* pKey, CString s)
{
	int nLen = s.GetLength();

	arch<<nLen;

	for (int i = 0; i < nLen; i++)
	{
		TCHAR c = s.GetAt(i);

		TCHAR temp = c ^ pKey[i];

		arch<<temp;
	}
}

void XDataUserManage::SaveIntData(CArchive& arch, unsigned char* pKey, int n)
{
	CString szTemp = _T("");

	szTemp.Format(_T("%d"), n);

	SaveStringData(arch, pKey, szTemp);
}

CString XDataUserManage::GetStringData(CArchive& arch, unsigned char* pKey)
{
	CString szTemp = _T("");

	int nLen = 0;
	arch>>nLen;

	if (0 < nLen)
	{
		TCHAR* pData = new TCHAR[nLen + 1];

		for (int i = 0; i < nLen; i++)
		{
			TCHAR c = 0;

			arch>>c;

			pData[i] = c ^ pKey[i];
		}

		pData[nLen] = '\0';

		szTemp = pData;

		delete[] pData;
	}

	return szTemp;
}

int XDataUserManage::GetIntData(CArchive& arch, unsigned char* pKey)
{
	CString szTemp = GetStringData(arch, pKey);

	return _ttoi(szTemp);
}

void XDataUserManage::GetData(XUserManage* pManage, CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	switch(nVersion)
	{
	case 1:
		{
			GetDataOfVersion1(pManage, arch);
		}
		break;
	default:
		break;
	}
}

void XDataUserManage::GetDataOfVersion1(XUserManage* pManage, CArchive& arch)
{
	CString szNotice=_T("");
	arch>>szNotice;

	pManage->SetNotice(szNotice);
	//////////////////////////////////////////////////////////
	int nKeyLen = 0;
	arch>>nKeyLen;

	unsigned char* pKey = new unsigned char[nKeyLen];

	for (int i = 0; i < nKeyLen; i++)
	{
		arch>>pKey[i];
	}
	//////////////////////////////////////////////////////////
	VEC_USERINFO& VecUserInfo = pManage->GetVecUserInfo();

	int nUserInfoCount;
	arch>>nUserInfoCount;

	for (int i = 0; i < nUserInfoCount; i++)
	{
		XUserInfo* pInfo = new XUserInfo;

		pInfo->GetData(arch, pKey);

		VecUserInfo.push_back(pInfo);
	}
	//////////////////////////////////////////////////////////
	delete[] pKey;
}

void XDataUserManage::SaveData(XUserManage* pManage, CArchive& arch)
{
	arch<<USERMANAGE_DATAVERSION;

	arch<<pManage->GetNotice();
	//////////////////////////////////////////////////////////////
	int nKeyLen = KEYLEN + rand() % 0xFF + rand() % 0xFF + rand() % 0xFF;

	unsigned char* pKey = new unsigned char[nKeyLen];

	arch<<nKeyLen;

	for (int i = 0; i < nKeyLen; i++)
	{
		pKey[i] = rand()%0xFF;

		arch<<pKey[i];
	}
	//////////////////////////////////////////////////////////////
	VEC_USERINFO& VecUserInfo = pManage->GetVecUserInfo();

	arch<<VecUserInfo.size();

	for (VEC_USERINFO::iterator iter = VecUserInfo.begin(); iter != VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo = *iter;

		pInfo->SaveData(arch, pKey);
	}
	//////////////////////////////////////////////////////////////
	delete[] pKey;
}

