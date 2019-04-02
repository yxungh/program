#pragma once

class XLoginInfo;
class XResult;

class XJsonManage
{
public:
	XJsonManage();
	~XJsonManage();

public:

	static XJsonManage* GetInstance();

	static void Relase();

public:

	void ParseJsonToLogin(const char* pData,XLoginInfo& userInfo);

	void ParseJsonToLoginOut(const char* pData,XResult& result);

public:

	void WriteJsonToLogin(CString& szUserName,CString& szPassWd,CString& szResult);

	void WriteJsonToLoginOut(CString& szUserName,CString& szResult);

private:

	static XJsonManage* m_pJsomManage;
};