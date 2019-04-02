#pragma once


class XScreenNumInfo
{
public:

	XScreenNumInfo();

	~XScreenNumInfo();

public:

	int GetScreenIndex();

	void SetScreenIndex(int n);

	int GetScreenNum();

	void SetScreenNum(int n);

private:

	int m_nScreenIndex;

	int m_nScreenNum;

};