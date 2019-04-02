#include "stdafx.h"
#include "XTranslationManage.h"
#include "XHandlePath.h"
#include "XHandleIni.h"
#include "XConstant.h"


XTranslationManage* XTranslationManage::m_pTranslationManage=NULL;

//程序退出时，全局变量释放会调用析构函数来释放单例
//XTranslationManage::GC XTranslationManage::gc;

XTranslationManage::XTranslationManage()
{
	m_LanguageType = LANGUAGETYPE_NULL;

	m_szTranslationFilePath = _T("");
}

XTranslationManage::~XTranslationManage()
{

}

//XTranslationManage::GC::~GC()
//{
//	if(NULL!=m_pTranslationManage)
//	{
//		delete m_pTranslationManage;
//
//		m_pTranslationManage=NULL;
//	}
//}

void XTranslationManage::Release()
{
	if(NULL!=m_pTranslationManage)
	{
		delete m_pTranslationManage;
		m_pTranslationManage=NULL;
	}
}

XTranslationManage* XTranslationManage::GetInstance()
{
	if(NULL==m_pTranslationManage)
	{
		m_pTranslationManage=new XTranslationManage;
	}

	return m_pTranslationManage;
}

void XTranslationManage::Init()
{
	CString szPath = XHandlePath::GetIniPath(APP_ININAME);

	LANGUAGETYPE type = (LANGUAGETYPE)XHandleIni::GetInt(_T("Info"),_T("Language"), LANGUAGETYPE_ZH_CN, szPath);

	SetLanguageType(type);
}

CString XTranslationManage::GetTranslationString(CString szKey, CString szDefault)
{
	CString szData=XHandleIni::GetString(_T("Info"),szKey,_T(""),m_szTranslationFilePath);

	if(_T("")==szData)
	{
		return szDefault;
	}
	else
	{
		return szData;
	}
}

LANGUAGETYPE XTranslationManage::GetLanguageType()
{
	return m_LanguageType;
}

void XTranslationManage::SetLanguageType(LANGUAGETYPE type)
{
	m_LanguageType=type;

	m_szTranslationFilePath=GetTranslationFilePath(type);
}

CString XTranslationManage::GetTranslationFilePath(LANGUAGETYPE type)
{
	CString szFileName = _T("");

	switch(type)
	{
	case LANGUAGETYPE_ZH_TW:
		{
			szFileName = _T("ZH_TW");
		}
		break;
	case LANGUAGETYPE_EN:
		{
			szFileName = _T("EN");
		}
		break;
	default:
		{
			szFileName = _T("ZH_CN");
		}
		break;
	}

	return XHandlePath::GetTranslationFilePath(szFileName);
}

void XTranslationManage::SaveLanguageType()
{
	CString szPath=XHandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");

	szTemp.Format(_T("%d"),m_LanguageType);

	XHandleIni::WriteData(_T("Info"), _T("Language"), szTemp, szPath);
}

LANGUAGETYPE XTranslationManage::GetLanguageType(CString szLanguageName)
{
	LANGUAGETYPE type = LANGUAGETYPE_NULL;

	if (szLanguageName == GetLanguageName(LANGUAGETYPE_EN))
	{
		type = LANGUAGETYPE_EN;
	}
	else if (szLanguageName == GetLanguageName(LANGUAGETYPE_ZH_CN))
	{
		type = LANGUAGETYPE_ZH_CN;
	}
	else if (szLanguageName == GetLanguageName(LANGUAGETYPE_ZH_TW))
	{
		type = LANGUAGETYPE_ZH_TW;
	}

	return type;
}

CString XTranslationManage::GetLanguageName(LANGUAGETYPE type)
{
	CString szName = _T("");

	switch(type)
	{
	case LANGUAGETYPE_ZH_CN:
		{
			szName = GetTranslationString(_T("10"), _T("中文(简体)"));
		}
		break;
	case LANGUAGETYPE_ZH_TW:
		{
			szName = GetTranslationString(_T("11"), _T("中文(繁体)"));
		}
		break;
	case LANGUAGETYPE_EN:
		{
			szName = GetTranslationString(_T("12"), _T("英文"));
		}
		break;
	default:
		break;
	}

	return szName;
}