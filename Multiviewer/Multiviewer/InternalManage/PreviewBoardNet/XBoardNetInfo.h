#pragma once

class XBoardNetInfo
{
public:

	XBoardNetInfo();
	~XBoardNetInfo();

public:

	int GetBoardIndex();

	void SetBoardIndex(int n);

	CString GetUseName();

	void SetUseName(CString szName);

	CString GetPassWd();

	void SetPassWd(CString szPassWd);

	int GetModel();

	void SetModel(int n);

	int GetSelect();

	void SetSelect(int n);

	CString GetIPAddr();

	void SetIPAddr(CString szIP);

	CString GetMaskAddr();

	void SetMaskAddr(CString szMask);

	CString GetGateWayAddr();

	void SetGateWayAddr(CString szGateWay);

	CString GetMACAddr();

	void SetMACAddr(CString szMAC);

	void SetArrMAC(int* p);

	int* GetArrMAC();

	void ClearMACAddr();

	void SerSecretSelect(int n);

	int GetSecretSelect();

	void SetSecret(int n);

	int GetSecret();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:


	int m_nBoardIndex;

	CString m_szUseName;

	CString m_szPassWd;

	int m_nModel;

	int m_nSelect;

	CString m_szIPAddr;

	CString m_szMaskAddr;

	CString m_szGateWayAddr;

	CString m_szMACAddr;

	int* m_pMAC;

	int m_nSecretSelect;

	int m_nSecret;
};