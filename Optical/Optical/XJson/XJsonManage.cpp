#include "stdafx.h"
#include "XJsonManage.h"
#include "XConstant.h"
#include "json.h"
#include "XLoginInfo.h"
#include "XResult.h"

XJsonManage* XJsonManage::m_pJsomManage=NULL;

XJsonManage::XJsonManage()
{

}

XJsonManage::~XJsonManage()
{

}

XJsonManage* XJsonManage::GetInstance()
{
	if(NULL==m_pJsomManage)
	{
		m_pJsomManage=new XJsonManage;
		return m_pJsomManage;
	}

	return m_pJsomManage;
}

void XJsonManage::Relase()
{
	RELEASE(m_pJsomManage);
}

void XJsonManage::ParseJsonToLogin(const char* pData,XLoginInfo& userInfo)
{
	Json::Reader reader;  
	Json::Value root;  
	if (reader.parse(pData,root)) 
	{  
		std::string UserName=root["user"].asCString();
		CString szUserName(UserName.c_str());

		std::string PassWd=root["key"].asCString();
		CString szPassWd(PassWd.c_str());

		int nResult=root["result"].asInt();
		
		userInfo.SetUserName(szUserName);
		userInfo.SetPassWd(szPassWd);
		userInfo.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToLoginOut(const char* pData,XResult& result)
{
	Json::Reader reader;  
	Json::Value root;  
	if (reader.parse(pData,root)) 
	{  
		int nResult=root["result"].asInt();

		result.SetResult(nResult);
	}
}

//////////////////////////////////////////////////////////////////////////
void XJsonManage::WriteJsonToLogin(CString& szUserName,CString& szPassWd,CString& szResult)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["user"]=Json::Value(W2A(szUserName));
	root["key"]=Json::Value(W2A(szPassWd));

	std::string str=write.write(root);
	szResult=str.c_str();
}

void XJsonManage::WriteJsonToLoginOut(CString& szUserName,CString& szResult)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["user"]=Json::Value(W2A(szUserName));

	std::string str=write.write(root);
	szResult=str.c_str();
}
