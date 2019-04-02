#pragma once

class CMyButton:public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();


	DECLARE_MESSAGE_MAP()


public:

	void SetCheckBoxNum(int n);

	int GetCheckBoxNum();


private:

	int m_nCheckBocNum;
};