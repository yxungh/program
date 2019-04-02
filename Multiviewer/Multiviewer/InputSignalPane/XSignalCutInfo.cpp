#include "StdAfx.h"
#include "XSignalCutInfo.h"

#define SIGNALCUT_VERSION 1

XSignalCutInfo::XSignalCutInfo()
{
	m_SignalCutX1 = 0;

	m_SignalCutY1 = 0;

	m_SignalCutX2 = 0;

	m_SignalCutY2 = 0;
}

XSignalCutInfo::~XSignalCutInfo(void)
{

}

void XSignalCutInfo::SetSignalCut(unsigned short nX1, unsigned short nY1, unsigned short nX2, unsigned short nY2)
{
	m_SignalCutX1 = nX1;

	m_SignalCutY1 = nY1;

	m_SignalCutX2 = nX2;

	m_SignalCutY2 = nY2;
}

unsigned short XSignalCutInfo::GetSignalCutX1()
{
	return m_SignalCutX1;
}

unsigned short XSignalCutInfo::GetSignalCutY1()
{
	return m_SignalCutY1;
}

unsigned short XSignalCutInfo::GetSignalCutX2()
{
	return m_SignalCutX2;
}

unsigned short XSignalCutInfo::GetSignalCutY2()
{
	return m_SignalCutY2;
}

void XSignalCutInfo::Reset()
{
	m_SignalCutX1 = 0;

	m_SignalCutY1 = 0;

	m_SignalCutX2 = 0;

	m_SignalCutY2 = 0;
}

void XSignalCutInfo::GetData(CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	arch>>m_SignalCutX1
		>>m_SignalCutY1
		>>m_SignalCutX2
		>>m_SignalCutY2;
}

void XSignalCutInfo::SaveData(CArchive& arch)
{
	arch<<SIGNALCUT_VERSION
		<<m_SignalCutX1
		<<m_SignalCutY1
		<<m_SignalCutX2
		<<m_SignalCutY2;
}