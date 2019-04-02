#pragma once
#include "..\XConstantIM.h"



class XOutputInfo
{
public:

	XOutputInfo();

	~XOutputInfo();

public:

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetInputName(CString szName);

	CString GetInputName();

	void SetIsFirstPan(BOOL b);

	BOOL GetIsFirstPan();

	void SetIsTwoScreen(BOOL b);

	BOOL GetIsTwoScreen();

	void SetScreenIndex1(int n);

	int GetScreenIndex1();

	void SetScreenIndex2(int n);

	int GetScreenIndex2();

	void SetCheckNum(int n);

	int GetCheckNum();

	void SetMapScreenNum(MAP_NUMOFSCREEN MapNumOfScreen);

	MAP_NUMOFSCREEN& GetMapScreenNum();

public:

	inline void SetScreenIndex3(int n){m_nScreenIndex3=n;}

	inline int GetScreenIndex3(){return m_nScreenIndex3;}

	inline void SetScreenIndex4(int n){m_nScreenIndex4=n;}

	inline int GetScreenIndex4(){return m_nScreenIndex4;}

	inline void SetCorrpScreenNum(int n){m_nCorrpScreenNum=n;}

	inline int GetCorrpScreenNum(){return m_nCorrpScreenNum;}

private:

	int m_nBoardIndex;

	CString m_szInputName;

	BOOL m_bIsFirstPan;

	BOOL m_bIsTwoScreen;

	int m_nScreenIndex1;

	int m_nScreenIndex2;

	int m_nScreenIndex3;

	int m_nScreenIndex4;

	int m_nCorrpScreenNum;

	int m_nCheckNum;

	MAP_NUMOFSCREEN m_MapNumOfScreen;

};