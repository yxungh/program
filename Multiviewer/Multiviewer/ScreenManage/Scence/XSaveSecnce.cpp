#include "stdafx.h"
#include "XSaveScence.h"
#include "..\resource.h"
#include "HandleVerification.h"
#include "XSceneGroupInfo.h"

#define SCENEINDEX_BEGIN 1
#define SCENEINDEX_END   30


IMPLEMENT_DYNAMIC(XSaveScence, CDialogEx)

XSaveScence::XSaveScence(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSaveScence::IDD, pParent)
{
	m_pDelegate=NULL;

	InitIndex();
}

XSaveScence::~XSaveScence()
{
}

void XSaveScence::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_INDEX, m_ComboBox_Index);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_ComboBox_Group);
}

BEGIN_MESSAGE_MAP(XSaveScence, CDialogEx)

	ON_BN_CLICKED(IDOK, &XSaveScence::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, &XSaveScence::OnSelchangeCombo)
END_MESSAGE_MAP()



void XSaveScence::SetDelegate(XDelegateSaveScence* p)
{
	m_pDelegate=p;
}

void XSaveScence::InitIndex()
{
	for(int i=0;i<32;i++)
	{
		m_Index[i]=0;
	}
}

void XSaveScence::SetData(char* pData)
{
	int nIndex=0;
	memcpy(&nIndex,pData+8,4);

	for(int i=0;i<32;i++)
	{
		if(nIndex&(1<<i))
		{
			m_Index[i]=1;
		}
		else
		{
			m_Index[i]=0;
		}
	}	

	//for(int i=0;i<32;i++)
	//{
	//	TRACE(_T("nIndex=%d\n"),m_Index[i]);
	//}
}

BOOL XSaveScence::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	ReloadInterface();

	InitCombo();

	OnSelchangeCombo();
		
	return FALSE; 
}

void XSaveScence::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("388"), _T("场景")));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("240"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("241"), _T("取消")));

	GetDlgItem(IDC_STATIC_INDEX)->SetWindowText(m_pDelegate->GetTranslationString(_T("389"), _T("序号"))+_T(":"));
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_pDelegate->GetTranslationString(_T("390"), _T("名称"))+_T(":"));
	GetDlgItem(IDC_STATIC_GROUP)->SetWindowText(m_pDelegate->GetTranslationString(_T("731"), _T("添加到组"))+_T(":"));
}


void XSaveScence::OnBnClickedOk()
{
	CString szStr=_T("");

	m_ComboBox_Index.GetLBText(m_ComboBox_Index.GetCurSel(),szStr);

	int nIndex=_ttoi(szStr);

	m_nSceneIndex=nIndex;

	if(nIndex==0)
	{
		m_pDelegate->MessageBoxFromKey(_T("724"),_T("场景保存个数上限，请删除无用场景！"),MB_OK);

		return;
	}
	//////////////////////////////////////////////////////////////////////////
	CString szTemp = _T("");

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szTemp);

	if (_T("") == szTemp)
	{
		m_pDelegate->MessageBoxFromKey(_T("391"), _T("场景名称不能为空！"), MB_OK);

		GetDlgItem(IDC_EDIT_NAME)->SetFocus();

		return;
	}

	if(!HandleVerification::VerificationString(szTemp))
	{
		m_pDelegate->MessageBoxFromKey(_T("725"), _T("场景名称包含非法字符！"), MB_OK);

		return;
	}

	m_szSceneName = szTemp;
	//////////////////////////////////////////////////////////////////////////
	CString szSceneGroup=_T("");
	m_ComboBox_Group.GetLBText(m_ComboBox_Group.GetCurSel(),szSceneGroup);
	m_szSceneGroup=szSceneGroup;

	if(szSceneGroup==m_pDelegate->GetTranslationString(_T("551"),_T("无")))
	{
		m_szSceneGroup=_T("");
	}

	CDialogEx::OnOK();
}

CString XSaveScence::GetSceneName()
{
	return m_szSceneName;
}

int XSaveScence::GetSceneIndex()
{
	return m_nSceneIndex;
}

CString XSaveScence::GetSceneGroup()
{
	return m_szSceneGroup;
}

void XSaveScence::InitCombo()
{
	InitComboIndex();

	InitComboGroup();
}

void XSaveScence::InitComboIndex()
{
	BOOL bFlag=FALSE;

	CString szIndex;

	for(int i=0;i<32;i++)
	{
		if(m_Index[i]==0)
		{
			bFlag=TRUE;

			szIndex.Format(_T("%d"),i+1);

			m_ComboBox_Index.AddString(szIndex);
		}
		else if(m_Index[i]==1)
		{ 
			continue;
		}
	}

	if(!bFlag)
	{
		CString szTemp=m_pDelegate->GetTranslationString(_T("551"),_T("无"));

		m_ComboBox_Index.AddString(szTemp);
	}

	m_ComboBox_Index.SetCurSel(0);
}

void XSaveScence::InitComboGroup()
{
	MAP_SCENEGROUP& MapSceneGroup=m_pDelegate->GetMapSceneGroup();

	int nScreenType=m_pDelegate->GetScreenType();

	int nTempType=0;
	switch(nScreenType)
	{
	case SCREENMODEL_DEV:
		{
			nTempType=ITEM_DEV;
		}
		break;
	case SCREENMODEL_SPLIC:
		{
			nTempType=ITEM_SPLIC;
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			nTempType=ITEM_MATRIX;
		}
		break;
	default:
		break;
	}

	m_ComboBox_Group.AddString(m_pDelegate->GetTranslationString(_T("551"),_T("无")));

	for(MAP_SCENEGROUP::iterator iter=MapSceneGroup.begin();iter!=MapSceneGroup.end();++iter)
	{
		XSceneGroupInfo* pInfo=iter->second;

		CString szSceneName=iter->first;

		int nType=pInfo->GetSceneType();

		if(nType==nTempType)
		{
			m_ComboBox_Group.AddString(szSceneName);
		}
	}

	m_ComboBox_Group.SetCurSel(0);
}

void XSaveScence::OnSelchangeCombo()
{
	CString szTemp;

	m_ComboBox_Index.GetLBText(m_ComboBox_Index.GetCurSel(),szTemp);

	if(szTemp==m_pDelegate->GetTranslationString(_T("551"),_T("无")))
	{
		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(_T(""));
	}
	else
	{
		szTemp = _T("Scene") + szTemp;

		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(szTemp);
	}
}