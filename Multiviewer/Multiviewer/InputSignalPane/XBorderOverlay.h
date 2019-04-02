#pragma once

class XBorderOverlay
{
public:
	XBorderOverlay();
	~XBorderOverlay();

	void SetBorderColor(COLORREF c);

	COLORREF GetBorderColor();

	void SetBorderWith(int n);

	int GetBorderWith();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	COLORREF m_BorderColor;

	int m_BorderWith;
};