#pragma once

class XOldOrderInfo
{
public:
	XOldOrderInfo(void);
	~XOldOrderInfo(void);

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