#include "StdAfx.h"
#include "XExpandInfo.h"

XExpandInfo::XExpandInfo()
{
	m_ExpandX1 = 0;

	m_ExpandY1 = 0;

	m_ExpandX2 = 0;

	m_ExpandY2 = 0;
}

XExpandInfo::~XExpandInfo(void)
{
	
}

void XExpandInfo::SetExpand(unsigned short nX1, unsigned short nY1, unsigned short nX2, unsigned short nY2)
{
	m_ExpandX1 = nX1;

	m_ExpandY1 = nY1;

	m_ExpandX2 = nX2;

	m_ExpandY2 = nY2;
}

unsigned short XExpandInfo::GetExpandX1()
{
	return m_ExpandX1;
}

unsigned short XExpandInfo::GetExpandY1()
{
	return m_ExpandY1;
}

unsigned short XExpandInfo::GetExpandX2()
{
	return m_ExpandX2;
}

unsigned short XExpandInfo::GetExpandY2()
{
	return m_ExpandY2;
}

void XExpandInfo::Reset()
{
	m_ExpandX1 = 0;

	m_ExpandY1 = 0;

	m_ExpandX2 = 0;

	m_ExpandY2 = 0;
}

void XExpandInfo::GetData(CArchive& arch)
{
	arch>>m_ExpandX1
		>>m_ExpandY1
		>>m_ExpandX2
		>>m_ExpandY2;
}

void XExpandInfo::SaveData(CArchive& arch)
{
	arch<<m_ExpandX1
		<<m_ExpandY1
		<<m_ExpandX2
		<<m_ExpandY2;
}