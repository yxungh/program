#include "StdAfx.h"
#include "XNodePowerInfo.h"
#include "XDataUserManage.h"

XNodePowerInfo::XNodePowerInfo(void)
{
	m_InputIndex = 0;

	m_OutputIndex = 0;

	m_Power = FALSE;
}

XNodePowerInfo::~XNodePowerInfo(void)
{

}

int XNodePowerInfo::GetInputIndex()
{
	return m_InputIndex;
}

int XNodePowerInfo::GetOutputIndex()
{
	return m_OutputIndex;
}

BOOL XNodePowerInfo::GetPower()
{
	return m_Power;
}

void XNodePowerInfo::SetInputIndex(int n)
{
	m_InputIndex = n;
}

void XNodePowerInfo::SetOutputIndex(int n)
{
	m_OutputIndex = n;
}

void XNodePowerInfo::SetPower(BOOL b)
{
	m_Power = b;
}

void XNodePowerInfo::GetData(CArchive& arch, unsigned char* pKey)
{
	m_InputIndex = XDataUserManage::GetIntData(arch, pKey);

	m_OutputIndex = XDataUserManage::GetIntData(arch, pKey);

	m_Power = XDataUserManage::GetIntData(arch, pKey);
}

void XNodePowerInfo::SaveData(CArchive& arch, unsigned char* pKey)
{
	XDataUserManage::SaveIntData(arch, pKey, m_InputIndex);

	XDataUserManage::SaveIntData(arch, pKey, m_OutputIndex);

	XDataUserManage::SaveIntData(arch, pKey, m_Power);
}