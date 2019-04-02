#pragma once

class XScreenData
{
public:
	XScreenData();

	~XScreenData();

public:

	void SetScreenIndex(int n);

	void SetBoardIndex(int n);

	void SetIsTwoScreen(BOOL b);

	void SetNumOfTwoScreen(int n);

	int GetScreenIndex();

	int GetBoardIndex();

	BOOL GetIsTwoScreen();

	int GetNumOfTwoScreen();


private:

	int m_nScreenIndex;

	int m_nBoardIndex;

	BOOL m_bIsTwoScreen;

	int m_nNumOfTwoScreen;
};