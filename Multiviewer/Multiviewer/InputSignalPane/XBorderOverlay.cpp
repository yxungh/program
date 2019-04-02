
#include "stdafx.h"
#include "XBorderOverlay.h"

#define BORDER_VERSION 1

XBorderOverlay::XBorderOverlay()
{
	m_BorderWith=0;

	m_BorderColor=RGB(255,0,0);
}

XBorderOverlay::~XBorderOverlay()
{

}

void XBorderOverlay::SetBorderColor(COLORREF c)
{
	m_BorderColor=c;
}

COLORREF XBorderOverlay::GetBorderColor()
{
	return m_BorderColor;
}

void XBorderOverlay::SetBorderWith(int n)
{
	m_BorderWith=n;
}

int XBorderOverlay::GetBorderWith()
{
	return m_BorderWith;
}

void XBorderOverlay::GetData(CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	arch>>m_BorderColor
		>>m_BorderWith;
}

void XBorderOverlay::SaveData(CArchive& arch)
{
	arch<<BORDER_VERSION
		<<m_BorderColor
		<<m_BorderWith;
}