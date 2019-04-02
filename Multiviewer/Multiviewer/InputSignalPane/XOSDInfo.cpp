#include "StdAfx.h"
#include "XOSDInfo.h"
#include "XConstantIM.h"

#define OSDINFO_VERSION 1

XOSDInfo::XOSDInfo()
{
	m_X = 1;

	m_Y = 1;

	m_Width = 512;

	m_Height = 64;

	m_Color = RGB(255, 0, 0);

	m_BkColor=RGB(255,0,0);

	m_Transparent = 0;

	m_Text = _T("");

	m_TextSize = 32;

	m_Font = APP_FONT;

	m_MutrixData = NULL;

	m_MutrixDataLen = 0;

	m_Type=1;
}

XOSDInfo::~XOSDInfo(void)
{
	ClearMutrixData();
}

void XOSDInfo::ClearMutrixData()
{
	if (NULL != m_MutrixData)
	{
		delete[] m_MutrixData;

		m_MutrixData = NULL;
	}

	m_MutrixDataLen = 0;
}

void XOSDInfo::Init()
{
	InitMutrixData();
}

void XOSDInfo::SetColor(COLORREF c)
{
	m_Color = c;
}

void XOSDInfo::SetBkColor(COLORREF c)
{
	m_BkColor = c;
}

void XOSDInfo::SetText(CString s)
{
	m_Text = s;
}

void XOSDInfo::SetFont(CString s)
{
	m_Font = s;
}

void XOSDInfo::SetTextSize(unsigned short n)
{
	m_TextSize = n;
}

void XOSDInfo::SetCoordinate(unsigned short nX, unsigned short nY, unsigned short nWidth, unsigned short nHeight)
{
	m_X = nX;

	m_Y = nY;

	m_Width = nWidth;

	m_Height = nHeight;
}

unsigned short XOSDInfo::GetX()
{
	return m_X;
}

unsigned short XOSDInfo::GetY()
{
	return m_Y;
}

unsigned short XOSDInfo::GetWidth()
{
	return m_Width;
}

unsigned short XOSDInfo::GetHeight()
{
	return m_Height;
}

COLORREF XOSDInfo::GetColor()
{
	return m_Color;
}

COLORREF XOSDInfo::GetBkColor()
{
	return m_BkColor;
}

CString XOSDInfo::GetText()
{
	return m_Text;
}

unsigned short XOSDInfo::GetTextSize()
{
	return m_TextSize;
}

CString XOSDInfo::GetFont()
{
	return m_Font;
}

char* XOSDInfo::GetMutrixData()
{
	return m_MutrixData;
}

int XOSDInfo::GetMutrixDataLen()
{
	return m_MutrixDataLen;
}

void XOSDInfo::SetType(int n)
{
	m_Type=n;
}

int XOSDInfo::GetType()
{
	return m_Type;
}

void XOSDInfo::SetCenterType(int n)
{
	m_CenterType=n;
}

int XOSDInfo::GetCenterType()
{
	return m_CenterType;
}

void XOSDInfo::InitMutrixData()
{
	//1Bit为一个点
	m_MutrixDataLen = m_Width / 8 * m_Height;

	m_MutrixData = new char[m_MutrixDataLen];

	ZeroMemory(m_MutrixData, m_MutrixDataLen);
}

void XOSDInfo::reSetData(char* pData)
{
	if (NULL != m_MutrixData)
	{
		delete[] m_MutrixData;

		m_MutrixData = NULL;
	}

	m_MutrixData=pData;
}

void XOSDInfo::GetData(CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	arch>>m_Type
		>>m_CenterType
		>>m_BkColor
		>>m_Color
		>>m_X
		>>m_Y
		>>m_Width
		>>m_Height
		>>m_Text
		>>m_TextSize
		>>m_Font
		>>m_MutrixDataLen;

	m_MutrixData = new char[m_MutrixDataLen];
	for (int i = 0; i < m_MutrixDataLen; i++)
	{
		arch>>m_MutrixData[i];
	}
}

void XOSDInfo::SaveData(CArchive& arch)
{
	arch<<OSDINFO_VERSION
		<<m_Type
		<<m_CenterType
		<<m_BkColor
		<<m_Color
		<<m_X
		<<m_Y
		<<m_Width
		<<m_Height
		<<m_Text
		<<m_TextSize
		<<m_Font
		<<m_MutrixDataLen;

	for (int i = 0; i < m_MutrixDataLen; i++)
	{
		arch<<m_MutrixData[i];
	}
}