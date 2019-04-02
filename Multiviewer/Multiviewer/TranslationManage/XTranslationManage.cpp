#include "StdAfx.h"
#include "XTranslationManage.h"
#include "XDelegateTranslationManage.h"
#include "HandleIni.h"
#include "HandlePath.h"

XTranslationManage::XTranslationManage(void)
{
	m_LanguageType = LANGUAGETYPE_NULL;

	m_szTranslationFilePath = _T("");
}

XTranslationManage::~XTranslationManage(void)
{
}

void XTranslationManage::Init()
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	LANGUAGETYPE type = (LANGUAGETYPE)HandleIni::GetInt(_T("Info"), _T("Language"), LANGUAGETYPE_ZH_CN, szIniPath);

	SetLanguageType(type);
}

void XTranslationManage::SaveLanguageType(LANGUAGETYPE type)
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	CString szTemp = _T("");
	szTemp.Format(_T("%d"), type);

	HandleIni::WriteData(_T("Info"), _T("Language"), szTemp, szIniPath);
}

void XTranslationManage::SetLanguageType(LANGUAGETYPE type)
{
	m_LanguageType = type;

	m_szTranslationFilePath = GetTranslationFilePath(type);
}

CString XTranslationManage::GetTranslationString(CString szKey, CString szDefault)
{
	CString szData = HandleIni::GetString(_T("Info"), szKey, _T(""), m_szTranslationFilePath);

	if (_T("") == szData)
	{
		return szDefault;
	}
	else
	{
		return szData;
	}
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

	return HandlePath::GetTranslationFilePath(szFileName);
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
			szName = GetTranslationString(_T("245"), _T("中文(简体)"));
		}
		break;
	case LANGUAGETYPE_ZH_TW:
		{
			szName = GetTranslationString(_T("246"), _T("中文(繁体)"));
		}
		break;
	case LANGUAGETYPE_EN:
		{
			szName = GetTranslationString(_T("244"), _T("英文"));
		}
		break;
	default:
		break;
	}

	return szName;
}

LANGUAGETYPE XTranslationManage::GetLanguageType()
{
	return m_LanguageType;
}

CString XTranslationManage::GetLanguagetype()
{
	CString szTemp;

	szTemp.Format(_T("%d"), m_LanguageType);

	return szTemp;
}

void XTranslationManage::SetLanguagetype(CString type)
{
	int nType=_ttoi(type);

	LANGUAGETYPE Type=(LANGUAGETYPE)nType;

	m_LanguageType = Type;

	m_szTranslationFilePath = GetTranslationFilePath(Type);
}

void XTranslationManage::ReLoadInterface()
{
	m_pDelegate->Operate(OPERATETYPE_RELOADINTERFACE, NULL);
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void XTranslationManage::UpdateControlDataShowOfLanguageName(CMFCRibbonComboBox* pCombox)
{
	if (nullptr != pCombox)
	{
		pCombox->RemoveAllItems();

		pCombox->AddItem(GetLanguageName(LANGUAGETYPE_ZH_CN));

		pCombox->AddItem(GetLanguageName(LANGUAGETYPE_ZH_TW));

		pCombox->AddItem(GetLanguageName(LANGUAGETYPE_EN));

		pCombox->SelectItem(GetLanguageName(m_LanguageType));
	}
}

void XTranslationManage::ControlDataChangeOfLanguageName(CMFCRibbonComboBox* pCombox)
{
	CString szData = pCombox->GetItem(pCombox->GetCurSel());

	LANGUAGETYPE type = GetLanguageType(szData);

	if (type != m_LanguageType)
	{
		//m_LanguageType=type;

		SaveLanguageType(type);

		SetLanguageType(type);

		m_pDelegate->Operate(OPERATETYPE_RELOADINTERFACE, NULL);
	}
}

void XTranslationManage::UpdateControlDataShow(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_LANGUAGENAME:
		{
			UpdateControlDataShowOfLanguageName((CMFCRibbonComboBox*)pControl);
		}
		break;
	default:
		break;
	}
}

void XTranslationManage::ControlDataChange(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_LANGUAGENAME:
		{
			ControlDataChangeOfLanguageName((CMFCRibbonComboBox*)pControl);
		}
		break;
	default:
		break;
	}
}