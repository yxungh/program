#pragma once
#include "XResult.h"

class XLoginInfo:public XResult
{
public:
	XLoginInfo();
	~XLoginInfo();

public:

	inline void SetUserName(CString szUser){m_szUserName=szUser;}

	inline CString GetUserName(){return m_szUserName;}

	inline void SetPassWd(CString szPassWd){m_szPassWd=szPassWd;}

	inline CString GetPassWd(){return m_szPassWd;}


private:

	CString m_szUserName;

	CString m_szPassWd;

};