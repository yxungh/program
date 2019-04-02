#pragma once

class XDeviceInfo
{
public:
	XDeviceInfo();

	~XDeviceInfo();

public:

	void SetInputIndex(int n);

	int GetInputIndex();

	void SetAnotherName(CString szAnotherName);

	CString GetAnotherName();

	void SetRTSPAddr(CString szAddr);

	CString GetRTSPAddr();

	void SetIP(CString szIP);

	CString GetIP();

	void SetIsHaveSignal(BOOL b);

	BOOL GetIsHaveSignal();

	void SetIsHavePane(BOOL b);

	BOOL GetIsHavePane();

	void SetIsUltra(BOOL b);

	BOOL GetIsUltra();

private:

	int m_nInputIndex;

	CString m_szAnotherName;

	CString m_szRTSPAddr;
	
	CString m_szIP;

	BOOL m_bIsHavePane;

	BOOL m_bIsHaveSignal;

	BOOL m_bIsUltra;
};