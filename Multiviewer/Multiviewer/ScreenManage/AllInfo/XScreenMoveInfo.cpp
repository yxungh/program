#include "stdafx.h"
#include "XScreenMoveInfo.h"
#include "XConstantIM.h"

#define SCREENMOVEINFOVERSION 1

XScreenMoveInfo::XScreenMoveInfo()
{
	m_Type=1;

	m_Width=256;

	m_Height=64;

	m_Frequency=255;

	m_Speed=1;

	m_Space=1;

	m_Color=RGB(255, 0, 0);

	m_BkColor=RGB(255,0,0);

	m_Text=_T("");

	m_FontSize=24;

	m_Font=APP_FONT;

	m_MutrixData=NULL;

	m_MutrixDataLen=0;

	m_BeginH=0;

	m_ComboBeginX=0;

	m_ComboBeginY=0;

	m_ComboLong=0;

	m_ComboWidth=0;

	m_SendSpace=0;

	m_ScreenResulationH=1920;

	m_ScreenResulationV=1080;
}

XScreenMoveInfo::~XScreenMoveInfo()
{
	ClearMutrixData();
}

void XScreenMoveInfo::ClearMutrixData()
{
	if (NULL != m_MutrixData)
	{
		delete[] m_MutrixData;

		m_MutrixData = NULL;
	}

	m_MutrixDataLen = 0;
}

char* XScreenMoveInfo::GetMutrixData()
{
	return m_MutrixData;
}

unsigned int XScreenMoveInfo::GetMutrixDataLen()
{
	return m_MutrixDataLen;
}

void XScreenMoveInfo::Init()
{
	InitMutrixData();
}

void XScreenMoveInfo::InitMutrixData()
{
	m_MutrixDataLen=m_Width/8*m_Height;

	m_MutrixData=new char[m_MutrixDataLen];

	ZeroMemory(m_MutrixData, m_MutrixDataLen);
}

void XScreenMoveInfo::reSetData(char* pData)
{
	if (NULL != m_MutrixData)
	{
		delete[] m_MutrixData;

		m_MutrixData = NULL;
	}

	m_MutrixData=pData;
}


unsigned short XScreenMoveInfo::GetType()
{
	return m_Type;
}
void XScreenMoveInfo::SetType(unsigned short n)
{
	m_Type=n;
}
unsigned short XScreenMoveInfo::GetFrequency()
{
	return m_Frequency;
}
void XScreenMoveInfo::SetFrequency(unsigned short n)
{
	m_Frequency=n;
}
unsigned short XScreenMoveInfo::GetSpeed()
{
	return m_Speed;
}
void XScreenMoveInfo::SetSpeed(unsigned short n)
{
	m_Speed=n;
}

unsigned short XScreenMoveInfo::GetSpace()
{
	return m_Space;
}
void XScreenMoveInfo::SetSpace(unsigned short n)
{
	m_Space=n;
}
COLORREF XScreenMoveInfo::GetColor()
{
	return m_Color;
}
void XScreenMoveInfo::SetColor(COLORREF c)
{
	m_Color=c;
}
COLORREF XScreenMoveInfo::GetBkColor()
{
	return m_BkColor;
}
void XScreenMoveInfo::SetBkColor(COLORREF c)
{
	m_BkColor=c;
}
unsigned short XScreenMoveInfo::GetWidth()
{
	return m_Width;
}
void XScreenMoveInfo::SetWidth(unsigned short n)
{
	m_Width=n;
}
unsigned short XScreenMoveInfo::GetHight()
{
	return m_Height;
}
void XScreenMoveInfo::SetHight(unsigned short n)
{
	m_Height=n;
}
CString XScreenMoveInfo::GetText()
{
	return m_Text;
}
void XScreenMoveInfo::SetText(CString s)
{
	m_Text=s;
}
CString XScreenMoveInfo::GetFont()
{
	return m_Font;
}

void XScreenMoveInfo::SetFont(CString s)
{
	m_Font=s;
}
unsigned short XScreenMoveInfo::GetFontSize()
{
	return m_FontSize;
}
void XScreenMoveInfo::SetFontSize(unsigned short n)
{
	m_FontSize=n;
}

unsigned short XScreenMoveInfo::GetBeginX()
{
	return m_BeginX;
}

void XScreenMoveInfo::SetBeginX(unsigned short n)
{
	m_BeginX=n;
}

unsigned short XScreenMoveInfo::GetBeginY()
{
	return m_BeginY;
}

void XScreenMoveInfo::SetBeginY(unsigned short n)
{
	m_BeginY=n;
}

unsigned short XScreenMoveInfo::GetLong()
{
	return m_Long;
}

void XScreenMoveInfo::SetLong(unsigned short n)
{
	m_Long=n;
}

unsigned short XScreenMoveInfo::GetBeginH()
{
	return m_BeginH;
}
void XScreenMoveInfo::SetBeginH(unsigned short n)
{
	m_BeginH=n;
}
unsigned short XScreenMoveInfo::GetComboBeginX()
{
	return m_ComboBeginX;
}
void XScreenMoveInfo::SetComboBeginX(unsigned short n)
{
	m_ComboBeginX=n;
}
unsigned short XScreenMoveInfo::GetComboBeginY()
{
	return m_ComboBeginY;
}
void XScreenMoveInfo::SetComboBeginY(unsigned short n)
{
	m_ComboBeginY=n;
}
unsigned short XScreenMoveInfo::GetComboLong()
{
	return m_ComboLong;
}
void XScreenMoveInfo::SetComboLong(unsigned short n)
{
	m_ComboLong=n;
}
unsigned short XScreenMoveInfo::GetComboWidth()
{
	return m_ComboWidth;
}
void XScreenMoveInfo::SetComboWidth(unsigned short n)
{
	m_ComboWidth=n;
}

RECTF& XScreenMoveInfo::GetAreaRect()
{
	return m_AreaRect;
}
void XScreenMoveInfo::SetAreaRect(RECTF& rect)
{
	m_AreaRect=rect;
}

RECTF& XScreenMoveInfo::GetInfoRect()
{
	return m_InfoRect;
}

void XScreenMoveInfo::SetInfoRect(RECTF& rect)
{
	m_InfoRect=rect;
}

int XScreenMoveInfo::GetCenter()
{
	return m_Center;
}

void XScreenMoveInfo::SetCenter(int n)
{
	m_Center=n;
}

unsigned short XScreenMoveInfo::GetComboShowBeginX()
{
	return m_ComboShowBeginX;
}

void XScreenMoveInfo::SetComboShowBeginX(unsigned short n)
{
	m_ComboShowBeginX=n;
}

unsigned short XScreenMoveInfo::GetComboShowBeginY()
{
	return m_ComboShowBeginY;
}
void XScreenMoveInfo::SetComboShowBeginY(unsigned short n)
{
	m_ComboShowBeginY=n;
}
unsigned short XScreenMoveInfo::GetComboShowLong()
{
	return m_ComboShowLong;
}
void XScreenMoveInfo::SetComboShowLong(unsigned short n)
{
	m_ComboShowLong=n;
}
unsigned short XScreenMoveInfo::GetComboShowWidth()
{
	return m_ComboShowWidth;
}
void XScreenMoveInfo::SetComboShowWidth(unsigned short n)
{
	m_ComboShowWidth=n;
}

int XScreenMoveInfo::GetSendSpace()
{
	return m_SendSpace;
}

void XScreenMoveInfo::SetSendSpace(int n)
{
	m_SendSpace=n;
}

int XScreenMoveInfo::GetScreenResulationH()
{
	return m_ScreenResulationH;
}

void XScreenMoveInfo::SetScreenResulationH(int n)
{
	m_ScreenResulationH=n;
}
int XScreenMoveInfo::GetScreenResulationV()
{
	return m_ScreenResulationV;
}
void XScreenMoveInfo::SetScreenResulationV(int n)
{
	m_ScreenResulationV=n;
}

void XScreenMoveInfo::GetData(CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	arch>>m_Type
		>>m_Center
		>>m_Frequency
		>>m_Speed
		>>m_Space
		>>m_Color
		>>m_BkColor
		>>m_BeginH
		>>m_BeginX
		>>m_BeginY
		>>m_Height
		>>m_Width
		>>m_ComboShowBeginX
		>>m_ComboShowBeginY
		>>m_ComboShowWidth
		>>m_ComboShowLong
		>>m_Text
		>>m_FontSize
		>>m_Font
		>>m_MutrixDataLen;

	m_MutrixData=new char[m_MutrixDataLen];
	for (int i=0;i<m_MutrixDataLen;i++)
	{
		arch>>m_MutrixData[i];
	}
}

void XScreenMoveInfo::SaveData(CArchive& arch)
{
	arch<<SCREENMOVEINFOVERSION
		<<m_Type
		<<m_Center
		<<m_Frequency
		<<m_Speed
		<<m_Space
		<<m_Color
		<<m_BkColor
		<<m_BeginH
		<<m_BeginX
		<<m_BeginY
		<<m_Height
		<<m_Width
		<<m_ComboShowBeginX
		<<m_ComboShowBeginY
		<<m_ComboShowWidth
		<<m_ComboShowLong
		<<m_Text
		<<m_FontSize
		<<m_Font
		<<m_MutrixDataLen;

	for (int i=0;i<m_MutrixDataLen;i++)
	{
		arch<<m_MutrixData[i];
	}
}
