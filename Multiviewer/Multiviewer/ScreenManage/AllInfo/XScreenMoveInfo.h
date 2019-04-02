#pragma once
#include "XConstantIM.h"

class XScreenMoveInfo
{
public:
	XScreenMoveInfo();
	~XScreenMoveInfo();

public:

	void Init();

	unsigned short GetType();

	void SetType(unsigned short n);

	unsigned short GetFrequency();

	void SetFrequency(unsigned short n);

	unsigned short GetSpeed();

	void SetSpeed(unsigned short n);

	unsigned short GetSpace();

	void SetSpace(unsigned short n);

	COLORREF GetColor();

	void SetColor(COLORREF c);

	COLORREF GetBkColor();

	void SetBkColor(COLORREF c);

	unsigned short GetWidth();

	void SetWidth(unsigned short n);

	unsigned short GetHight();

	void SetHight(unsigned short n);

	CString GetText();

	void SetText(CString s);

	CString GetFont();

	void SetFont(CString s);

	unsigned short GetFontSize();

	void SetFontSize(unsigned short n);

	unsigned short GetBeginX();

	void SetBeginX(unsigned short n);

	unsigned short GetBeginY();

	void SetBeginY(unsigned short n);

	unsigned short GetLong();

	void SetLong(unsigned short n);

	unsigned short GetBeginH();

	void SetBeginH(unsigned short n);

	unsigned short GetComboBeginX();

	void SetComboBeginX(unsigned short n);

	unsigned short GetComboBeginY();

	void SetComboBeginY(unsigned short n);

	unsigned short GetComboLong();

	void SetComboLong(unsigned short n);

	unsigned short GetComboWidth();

	void SetComboWidth(unsigned short n);

	unsigned short GetComboShowBeginX();

	void SetComboShowBeginX(unsigned short n);

	unsigned short GetComboShowBeginY();

	void SetComboShowBeginY(unsigned short n);

	unsigned short GetComboShowLong();

	void SetComboShowLong(unsigned short n);

	unsigned short GetComboShowWidth();

	void SetComboShowWidth(unsigned short n);

	char* GetMutrixData();

	unsigned int GetMutrixDataLen();

	RECTF& GetAreaRect();

	void SetAreaRect(RECTF& rect);

	RECTF& GetInfoRect();

	void SetInfoRect(RECTF& rect);

	int GetCenter();

	void SetCenter(int n);

	int GetSendSpace();

	void SetSendSpace(int n);

	int GetScreenResulationH();

	void SetScreenResulationH(int n);

	int GetScreenResulationV();

	void SetScreenResulationV(int n);


public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

	void InitMutrixData();

	void ClearMutrixData();

	void reSetData(char* pData);

private:

	unsigned short m_Type;

	unsigned short m_Frequency;

	unsigned short m_Speed;

	unsigned short m_Space;

	COLORREF m_Color;

	COLORREF m_BkColor;

	unsigned short m_Width;

	unsigned short m_Height;

	CString m_Text;

	unsigned short m_FontSize;

	CString m_Font;

	unsigned short m_BeginX;

	unsigned short m_BeginY;

	unsigned short m_Long;

	unsigned short m_BeginH;

	unsigned short m_ComboBeginX;

	unsigned short m_ComboBeginY;

	unsigned short m_ComboLong;

	unsigned short m_ComboWidth;

	unsigned short m_ComboShowBeginX;

	unsigned short m_ComboShowBeginY;

	unsigned short m_ComboShowLong;

	unsigned short m_ComboShowWidth;

	char* m_MutrixData;

	unsigned int m_MutrixDataLen;

	RECTF m_AreaRect;

	RECTF m_InfoRect;

	int m_Center;

	int m_SendSpace;

	int m_ScreenResulationH;

	int m_ScreenResulationV;


};