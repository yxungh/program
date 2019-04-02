#pragma once

class XScreenRetInfo
{
public:
	XScreenRetInfo();
	~XScreenRetInfo();

public:
	void SetBoardIndex(int n);
	int GetBoardIndex();

	void SetStatus(int n);
	int GetStatus();

private:

	int m_nBoardIndex;
	int m_nStatus;

};