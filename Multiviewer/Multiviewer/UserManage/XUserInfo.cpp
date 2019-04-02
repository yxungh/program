#include "StdAfx.h"
#include "XUserInfo.h"
#include "XDataUserManage.h"
#include "XNodePowerInfo.h"

XUserInfo::XUserInfo(void)
{
	
}

XUserInfo::~XUserInfo(void)
{
	ClearData();
}

void XUserInfo::ClearData()
{
	ClearMapNodePowerInfo();
}

CString XUserInfo::GetAccount()
{
	return m_Account;
}

CString XUserInfo::GetPassword()
{
	return m_Password;
}

char XUserInfo::GetPower()
{
	return m_Power;
}

void XUserInfo::SetAccount(CString s)
{
	m_Account = s;
}

void XUserInfo::SetPassword(CString s)
{
	m_Password = s;
}

void XUserInfo::SetPower(POWERTYPE n)
{
	m_Power = n;
}

void XUserInfo::GetData(CArchive& arch, unsigned char* pKey)
{
	m_Account = XDataUserManage::GetStringData(arch, pKey);

	m_Password = XDataUserManage::GetStringData(arch, pKey);

	m_Power = (char)(XDataUserManage::GetIntData(arch, pKey));

	GetNodePowerInfoData(arch, pKey);
}

void XUserInfo::GetNodePowerInfoData(CArchive& arch, unsigned char* pKey)
{
	int nCount = XDataUserManage::GetIntData(arch, pKey);

	for (int i = 0; i < nCount; i++)
	{
		unsigned int nKey = XDataUserManage::GetIntData(arch, pKey);

		XNodePowerInfo* pInfo = new XNodePowerInfo;

		pInfo->GetData(arch, pKey);

		m_MapNodePowerInfo.insert(std::pair<unsigned int, XNodePowerInfo*>(nKey, pInfo));
	}
}

void XUserInfo::SaveData(CArchive& arch, unsigned char* pKey)
{
	XDataUserManage::SaveStringData(arch, pKey, m_Account);

	XDataUserManage::SaveStringData(arch, pKey, m_Password);

	XDataUserManage::SaveIntData(arch, pKey, m_Power);

	SaveNodePowerInfoData(arch, pKey);
}

void XUserInfo::SaveNodePowerInfoData(CArchive& arch, unsigned char* pKey)
{
	XDataUserManage::SaveIntData(arch, pKey, m_MapNodePowerInfo.size());

	for (MAP_NODEPOWERINFO::iterator iter = m_MapNodePowerInfo.begin(); iter != m_MapNodePowerInfo.end(); iter++)
	{
		unsigned int nKey = iter->first;

		XDataUserManage::SaveIntData(arch, pKey, nKey);

		XNodePowerInfo* pInfo = iter->second;

		pInfo->SaveData(arch, pKey);
	}
}

BOOL XUserInfo::GetNodePower(int nInputIndex, int nOutputIndex)
{
	if (m_Power == POWERTYPE_ADMIN)
	{
		return TRUE;
	}

	XNodePowerInfo* pNodePowerInfo = GetNodePowerInfo(nInputIndex, nOutputIndex);

	if (NULL == pNodePowerInfo)
	{
		return FALSE;
	}
	else
	{
		return pNodePowerInfo->GetPower();
	}
}

XNodePowerInfo* XUserInfo::GetNodePowerInfo(int nInputIndex, int nOutputIndex)
{
	unsigned int nKey = (nInputIndex<<16) | nOutputIndex;

	MAP_NODEPOWERINFO::iterator iter = m_MapNodePowerInfo.find(nKey);

	if (m_MapNodePowerInfo.end() == iter)
	{
		return NULL;
	}
	else
	{
		return iter->second;
	}
}

void XUserInfo::SetNodePowerInfo(int nInputIndex, int nOutputIndex, BOOL bPower)
{
	XNodePowerInfo* pInfo = NULL;

	unsigned int nKey = (nInputIndex<<16) | nOutputIndex;

	MAP_NODEPOWERINFO::iterator iter = m_MapNodePowerInfo.find(nKey);

	if (m_MapNodePowerInfo.end() == iter)
	{
		pInfo = new XNodePowerInfo;

		pInfo->SetInputIndex(nInputIndex);

		pInfo->SetOutputIndex(nOutputIndex);

		m_MapNodePowerInfo.insert(std::pair<unsigned int, XNodePowerInfo*>(nKey, pInfo));
	}
	else
	{
		pInfo = iter->second;
	}

	pInfo->SetPower(bPower);
}

void XUserInfo::ClearMapNodePowerInfo()
{
	for (MAP_NODEPOWERINFO::iterator iter = m_MapNodePowerInfo.begin(); iter != m_MapNodePowerInfo.end(); iter++)
	{
		delete iter->second;
	}

	m_MapNodePowerInfo.clear();
}

MAP_NODEPOWERINFO& XUserInfo::GetMapPowerInfo()
{
	return m_MapNodePowerInfo;
}