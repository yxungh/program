#pragma once


class XAnotherNameInfo
{
public:
	XAnotherNameInfo();
	~XAnotherNameInfo();

public:

	CString GetAnotherName();

	void SetAnotherName(CString szName);

	int GetInputIndex();

	void SetInputIndex(int n);


private:

	CString m_szANotherName;

	int m_nInputIndex;
};