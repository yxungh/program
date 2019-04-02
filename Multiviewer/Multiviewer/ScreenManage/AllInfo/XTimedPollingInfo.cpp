#include "stdafx.h"
#include "XTimedPollingInfo.h"

#define XTIMEDPOLLING_VERSION 1

XTimedPollingInfo::XTimedPollingInfo()
{
	m_Time=0;
}

XTimedPollingInfo::~XTimedPollingInfo()
{

}

int XTimedPollingInfo::GetTimedPolling()
{
	return m_Time;
}

void XTimedPollingInfo::SetTimePolling(int n)
{
	m_Time=n;
}

void XTimedPollingInfo::GetData(CArchive& arch)
{
	int nVersoin;
	arch>>nVersoin;

	arch>>m_Time;
}

void XTimedPollingInfo::SaveData(CArchive& arch)
{
	arch<<XTIMEDPOLLING_VERSION
		<<m_Time;
}