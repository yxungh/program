#pragma once

class XStreamAddrInfo
{
public:
	XStreamAddrInfo(void);
	~XStreamAddrInfo(void);

	void SetDataLen(int n);

	int GetDataLen();

	CString GetText();

	void SetText(CString str);

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	CString szText;

	int m_Len;
};
