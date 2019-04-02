#pragma once

class XDelegateLogin
{
public:
	XDelegateLogin();
	~XDelegateLogin();

public:

	virtual void SetCurUserName(CString szUserName)=0;

	virtual void SetLoginUser(CString szUserName,CString szPassWd)=0;

	virtual void SetLoginLoad()=0;

};