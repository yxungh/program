#pragma once


class XSelectBoardInfo
{
public:
	XSelectBoardInfo();
	~XSelectBoardInfo();

public:

	int GetIndex();

	void SetIndex(int n);

	int GetBoardIndex();

	void SetBoardIndex(int n);

	CString GetUserName();

	void SetUserName(CString szName);

	CString GetPassWd();

	void SetPassWd(CString szPassWd);

	CString GetszIP();

	void SetIP(CString szIP);

	void SetMask(CString szMask);

	CString GetMask();

	void SetGateWay(CString szGateWay);

	CString GetGateWay();

	void SetMAC(CString szMAC);

	CString GetMAC();

	void SetModelSel(int n);

	int GetModelSel();

	void SetSecretSel(int n);

	int GetSecretSel();

	void SetSelected(BOOL b);

	BOOL GetSelected();



private:

	int m_nIndex;

	int m_nBoardIndex;

	BOOL m_bSelected;

	int m_nSecretSel;

	CString m_szUserName;

	CString m_szPassWd;

	int m_nModelSel;

	CString m_szIP;

	CString m_szMask;

	CString m_szGateWay;

	CString m_szMAC;
};