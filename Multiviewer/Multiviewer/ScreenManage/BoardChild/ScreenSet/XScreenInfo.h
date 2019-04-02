#pragma once


class XScreenInfo
{
public:

	XScreenInfo();

	~XScreenInfo();

public:

	void SetScreenIndex(int n);

	int GetScreenIndex();

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetLBDclick(int n);

	int GetLBDclick();

	void SetIsTwoScreen(BOOL b);

	BOOL GetIsTwoScreen();

	void SetNumOfScreen(int n);

	int GetNumOfScreen();

	//void SetFlag(BOOL b);

	//BOOL GetFlag();

	void SetCurBoardIndex(int n);

	int GetCurBoardIndex();

public:


	inline void SetScreenModel(int n){m_nScreenModel=n;}

	inline int GetScreenModel(){return m_nScreenModel;}

private:

	int m_nScreenIndex;

	int m_nBoardIndex;

	int m_nLBDclick;

	BOOL m_bIsTwoScreen;

	int m_nNumOfScreen;

	//BOOL m_bFlag;

	int m_nCurBoardIndex;

	int m_nScreenModel;

};