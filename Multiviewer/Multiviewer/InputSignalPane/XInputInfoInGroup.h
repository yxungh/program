#pragma once

class XInputInfoInGroup
{
public:
	XInputInfoInGroup();
	~XInputInfoInGroup();

public:

	void SetIndex(int n);
	
	int GetIndex();

	void SetGroupName(CString szName);

	CString GetGroupName();

	void SetAnotherName(CString szName);

	CString GetAnotherName();

private:

	int m_nIndex;

	CString m_szGroupName;

	CString m_szAnotherName;
};