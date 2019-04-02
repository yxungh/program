#pragma once



class XPreviewRTSPInfo
{
public:

	XPreviewRTSPInfo();
	~XPreviewRTSPInfo();

public:

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetRTAPAddr(CString szRTSPAddr);

	CString GetRTSPAddr();

private:

	int m_nBoardIndex;

	CString m_szRTSPAddr;
};