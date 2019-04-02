#pragma once

class XPaneNetInfo
{
public:

	XPaneNetInfo();
	~XPaneNetInfo();

public:

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

private:

	CString m_szUseName;

	CString m_szPassWd;

	int m_nModel;

	int m_nSelect;

	CString m_szIPAddr;

	CString m_szMaskAddr;

	CString m_szGateWayAddr;

	CString m_szMACAddr;


};