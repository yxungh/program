#pragma once


class XDelegatePowerManage
{
public:
	XDelegatePowerManage();
	~XDelegatePowerManage();

public:

	virtual BOOL IsLogin()=0;

	virtual CString GetCurUserName()=0;

	virtual void SetCurUserName(CString szUserName)=0;

	virtual void SetLogin(BOOL b)=0;
};