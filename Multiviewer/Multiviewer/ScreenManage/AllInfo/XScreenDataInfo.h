#pragma once
#include "..\XConstantIM.h"


class XScreenDataInfo
{
public:
	XScreenDataInfo();
	~XScreenDataInfo();

public:

	void SetScreenIndex(int n);

	int GetScreenIndex();

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetPaneNumIndex(int n);

	int GetPaneNumIndex();

	void SetIsTwoScreen(BOOL b);

	BOOL GetIsTwoScreen();

	void SetScreenRect(RECTF rect);

	RECTF GetScreenRect();

private:

	int m_nScreenIndex;

	int m_nBoardIndex;

	int m_nPaneNumIndex;

	BOOL m_bIsTwoScreen;

	RECTF m_rScreen;
};