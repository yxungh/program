#include "stdafx.h"
#include "XSaveAllScence.h"
#include "..\resource.h"
#include "HandleVerification.h"
#include "XSceneGroupInfo.h"
#include "XInternalManage.h"
#include "HandleListCtrl.h"
#include "XBaseScreenManage.h"

#define SCENEINDEX_BEGIN 1
#define SCENEINDEX_END   30


IMPLEMENT_DYNAMIC(XSaveAllScence, CDialogEx)

XSaveAllScence::XSaveAllScence(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSaveAllScence::IDD, pParent)
{
	m_pManege=NULL;

	m_pDelegate=NULL;

	InitIndex();
}

XSaveAllScence::~XSaveAllScence()
{
	ClearMapSelScene();
}

void XSaveAllScence::ClearMapSelScene()
{
	m_MapSelSceen.clear();
}

void XSaveAllScence::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_INDEX, m_ComboBox_Index);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_ComboBox_Group);
	DDX_Control(pDX, IDC_LIST_SCREENMANAGE, m_List_ScreenManage);
}

BEGIN_MESSAGE_MAP(XSaveAllScence, CDialogEx)

	ON_BN_CLICKED(IDOK, &XSaveAllScence::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, &XSaveAllScence::OnSelchangeCombo)
END_MESSAGE_MAP()



void XSaveAllScence::SetDelegate(XDelegateSaveAllScence* p)
{
	m_pDelegate=p;
}

void XSaveAllScence::SetManage(XInternalManage* pManage)
{
	m_pManege=pManage;
}

void XSaveAllScence::InitIndex()
{
	for(int i=0;i<32;i++)
	{
		m_Index[i]=0;
	}
}

void XSaveAllScence::SetData(char* pData)
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
}

BOOL XSaveAllScence::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitCombo();

	OnSelchangeCombo();

	InitList();

	ReloadListInterface();

	InitListData();
		
	return FALSE; 
}

void XSaveAllScence::ReloadInterface()
{
	SetWindowText(m_pManege->GetTranslationString(_T("740"), _T("多页面场景")));

	GetDlgItem(IDOK)->SetWindowText(m_pManege->GetTranslationString(_T("240"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pManege->GetTranslationString(_T("241"), _T("取消")));

	GetDlgItem(IDC_STATIC_INDEX)->SetWindowText(m_pManege->GetTranslationString(_T("389"), _T("序号"))+_T(":"));
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_pManege->GetTranslationString(_T("390"), _T("名称"))+_T(":"));
	GetDlgItem(IDC_STATIC_GROUP)->SetWindowText(m_pManege->GetTranslationString(_T("731"), _T("组名"))+_T(":"));
	GetDlgItem(IDC_STATIC_TIPS100)->SetWindowText(m_pManege->GetTranslationString(_T("753"), _T("选择拼接或矩阵页面")));
}

void XSaveAllScence::InitList()
{
	HandleListCtrl::InitList(&m_List_ScreenManage,1,TRUE);
}

void XSaveAllScence::ReloadListInterface()
{
	LVCOLUMN col;

	CString szTemp = _T("");

	szTemp = m_pManege->GetTranslationString(_T("743"), _T("拼接矩阵页面"));
	col.mask = LVCF_TEXT;
	col.pszText = szTemp.GetBuffer();
	m_List_ScreenManage.SetColumn(0, &col);

	szTemp.ReleaseBuffer();
}

void XSaveAllScence::InitListData()
{
	VEC_BASESCREENMANAGE& VecBaseManage=m_pManege->GetBaseManage();

	for(VEC_BASESCREENMANAGE::iterator iter=VecBaseManage.begin();iter!=VecBaseManage.end();++iter)
	{
		XBaseScreenManage* pBase=*iter;

		CString szViewName=pBase->GetViewName();

		AddInfo(szViewName);
	}
}

int XSaveAllScence::AddInfo(CString szInput)
{
	int n=m_List_ScreenManage.GetItemCount();

	m_List_ScreenManage.InsertItem(n,_T(""));

	m_List_ScreenManage.SetItemText(n,0,szInput);

	return n;
}

void XSaveAllScence::OnBnClickedOk()
{
	CString szStr=_T("");

	m_ComboBox_Index.GetLBText(m_ComboBox_Index.GetCurSel(),szStr);

	int nIndex=_ttoi(szStr);

	m_nSceneIndex=nIndex;

	if(nIndex==0)
	{
		m_pManege->MessageBoxFromKey(_T("724"),_T("场景保存个数上限，请删除无用场景！"),MB_OK);

		return;
	}
	//////////////////////////////////////////////////////////////////////////
	CString szTemp = _T("");

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szTemp);

	if (_T("") == szTemp)
	{
		m_pManege->MessageBoxFromKey(_T("391"), _T("场景名称不能为空！"), MB_OK);

		GetDlgItem(IDC_EDIT_NAME)->SetFocus();

		return;
	}

	if(!HandleVerification::VerificationString(szTemp))
	{
		m_pManege->MessageBoxFromKey(_T("725"), _T("场景名称包含非法字符！"), MB_OK);

		return;
	}

	m_szSceneName = szTemp;
	//////////////////////////////////////////////////////////////////////////
	CString szSceneGroup=_T("");
	m_ComboBox_Group.GetLBText(m_ComboBox_Group.GetCurSel(),szSceneGroup);
	m_szSceneGroup=szSceneGroup;

	if(szSceneGroup==m_pManege->GetTranslationString(_T("551"),_T("无")))
	{
		m_szSceneGroup=_T("");
	}

	//////////////////////////////////////////////////////////////////////////
	ClearMapSelScene();
	HandleListCtrl::GetListCheckItemText(&m_List_ScreenManage,m_MapSelSceen);

	CDialogEx::OnOK();
}

MAP_SELSCENE& XSaveAllScence::GetMapSelScene()
{
	return m_MapSelSceen;
}

CString XSaveAllScence::GetSceneName()
{
	return m_szSceneName;
}

int XSaveAllScence::GetSceneIndex()
{
	return m_nSceneIndex;
}

CString XSaveAllScence::GetSceneGroup()
{
	return m_szSceneGroup;
}

void XSaveAllScence::InitCombo()
{
	InitComboIndex();

	InitComboGroup();
}

void XSaveAllScence::InitComboIndex()
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
		CString szTemp=m_pManege->GetTranslationString(_T("551"),_T("无"));

		m_ComboBox_Index.AddString(szTemp);
	}

	m_ComboBox_Index.SetCurSel(0);
}

void XSaveAllScence::InitComboGroup()
{
	MAP_SCENEGROUP& MapSceneGroup=m_pManege->GetMapSceneGroup();

	int nScreenType=m_pManege->GetScreenType();

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

	m_ComboBox_Group.AddString(m_pManege->GetTranslationString(_T("551"),_T("无")));

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

void XSaveAllScence::OnSelchangeCombo()
{
	CString szTemp;

	m_ComboBox_Index.GetLBText(m_ComboBox_Index.GetCurSel(),szTemp);

	if(szTemp==m_pManege->GetTranslationString(_T("551"),_T("无")))
	{
		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(_T(""));
	}
	else
	{
		szTemp = _T("Scene") + szTemp;

		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(szTemp);
	}
}