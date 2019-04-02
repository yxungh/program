#pragma once


class XPaneIPAddrInfo
{
public:

	XPaneIPAddrInfo();
	~XPaneIPAddrInfo();
		
public:

	void SetPaneIP(CString szIP);

	CString GetPaneIP();

	void SetPaneMask(CString szMask);

	CString GetPaneMask();

	void SetPaneGateWay(CString szGateWay);

	CString GetPaneGateWay();

	void SetPaneMAC(CString szMAC);

	CString GetPaneMAC();

	void SetArrMAC(int* p);

	int* GetArrMAC();

	void ClearMACAddr();

	int GetModel();

	void SetModel(int n);

	int GetSelect();

	void SetSelect(int n);


public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);


private:

	CString m_szPaneIP;

	CString m_szPaneMask;

	CString m_szPaneGateWay;

	CString m_szPaneMAC;

	int *pMAC;

	int m_nModel;

	int m_nSelect;


};