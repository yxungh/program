#pragma once

class XOSDInfo
{
public:
	XOSDInfo(void);
	~XOSDInfo(void);

	void Init();

	void SetCoordinate(unsigned short nX, unsigned short nY, unsigned short nWidth, unsigned short nHeight);

	void SetColor(COLORREF c);

	void SetBkColor(COLORREF c);

	void SetText(CString s);

	void SetTextSize(unsigned short n);

	void SetFont(CString s);

	unsigned short GetX();

	unsigned short GetY();

	unsigned short GetWidth();

	unsigned short GetHeight();

	COLORREF GetColor();

	COLORREF GetBkColor();

	CString GetText();

	unsigned short GetTextSize();

	CString GetFont();

	char* GetMutrixData();

	int GetMutrixDataLen();

	void SetType(int n);

	int GetType();

	void SetCenterType(int n);

	int GetCenterType();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

	void InitMutrixData();

	void ClearMutrixData();

	void reSetData(char* pData);

private:

	COLORREF m_Color;

	COLORREF m_BkColor;

	unsigned char m_Transparent;

	unsigned short m_X;

	unsigned short m_Y;

	unsigned short m_Width;

	unsigned short m_Height;

	CString m_Text;

	unsigned short m_TextSize;

	CString m_Font;

	char* m_MutrixData;

	int m_MutrixDataLen;

	int m_Type;

	int m_CenterType;
};

