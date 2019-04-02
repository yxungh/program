#include "stdafx.h"
#include "XNewViewDlg.h"
#include "afxdialogex.h"
#include "XDelegateNewViewDlg.h"
#include "XInternalManage.h"
#include "XBaseScreenManage.h"
#include "XMenuScreenSetInfo.h"


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XNewViewDlg, CDialogEx)

	XNewViewDlg::XNewViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XNewViewDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_BeginIndex=1;

	m_nScreenModel=0;
}

XNewViewDlg::~XNewViewDlg()
{

}

void XNewViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCREENMODEL, m_Combox_Model);
}


BEGIN_MESSAGE_MAP(XNewViewDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XNewViewDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XNewViewDlg::SetDelegate(XDelegateNewViewDlg* p)
{
	m_pDelegate = p;
}

void XNewViewDlg::SetBaseManage(XInternalManage* p)
{
	m_pBaseManage=p;
}

void XNewViewDlg::SetViewName(CString s)
{
	m_ViewName=s;
}

CString XNewViewDlg::GetViewName()
{
	return m_ViewName;
}

int XNewViewDlg::GetBeginIndex()
{
	return m_BeginIndex;
}

int XNewViewDlg::GetScreenModel()
{
	return m_nScreenModel;
}

BOOL XNewViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitCombo();

	InitData();

	return FALSE;  
}

void XNewViewDlg::InitData()
{
	CString szIndex;
	szIndex.Format(_T("%d"),1);
	GetDlgItem(IDC_EDIT_SCREENINDEX)->SetWindowText(szIndex);
}

void XNewViewDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("498"), _T("新建拼接屏")));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));
	GetDlgItem(IDC_STATIC_SCREENINDEX)->SetWindowText(m_pDelegate->GetTranslationString(_T("539"), _T("屏幕开始序号")) + _T(":"));
	GetDlgItem(IDC_STATIC_VIEWNAME)->SetWindowText(m_pDelegate->GetTranslationString(_T("390"), _T("名称")) + _T(":"));
}

void XNewViewDlg::InitCombo()
{
	m_Combox_Model.AddString(m_pBaseManage->GetTranslationString(_T("697"),_T("拼接模式")));
	m_Combox_Model.AddString(m_pBaseManage->GetTranslationString(_T("696"),_T("矩阵模式")));
	
	m_Combox_Model.SetCurSel(0);
}

void XNewViewDlg::OnBnClickedOk()
{
	int nSelect=m_Combox_Model.GetCurSel();

	if(nSelect==0)
	{	
		m_nScreenModel=SCREENMODEL_SPLIC;
	}
	else if(nSelect==1)
	{
		m_nScreenModel=SCREENMODEL_MATRIX;
	}

	//保存屏幕模式
	XMenuScreenSetInfo* pInfo=m_pDelegate->GetMenuScreenSetInfo();
	pInfo->SetScreenModel(m_nScreenModel);
	//*******************
	CString szName = _T("");
	GetDlgItem(IDC_EDIT_VIEWNAME)->GetWindowText(szName);
	szName.Trim();
	if (_T("")==szName)
	{
		m_pDelegate->MessageBoxFromKey(_T("521"), _T("视图名称不能为空,请输入!"), MB_OK);
		GetDlgItem(IDC_EDIT_VIEWNAME)->SetFocus();
		return;
	}

	VEC_BASESCREENMANAGE& VecBaseManage=m_pBaseManage->GetBaseManage();

	for(VEC_BASESCREENMANAGE::iterator iter=VecBaseManage.begin();iter!=VecBaseManage.end();iter++)
	{
		XBaseScreenManage* pBase=*iter;

		if(szName==pBase->GetViewName())
		{
			m_pDelegate->MessageBoxFromKey(_T("526"), _T("视图名称不能重复,请重新输入!"), MB_OK);
			GetDlgItem(IDC_EDIT_VIEWNAME)->SetFocus();
			return;
		}
	}

	m_ViewName=szName;
	//*******************
	CString szIndex;
	GetDlgItem(IDC_EDIT_SCREENINDEX)->GetWindowText(szIndex);
	szIndex.Trim();
	if (_T("")==szIndex)
	{
		m_pDelegate->MessageBoxFromKey(_T("523"), _T("屏幕开始序号不能为空，请输入！"), MB_OK);
		GetDlgItem(IDC_EDIT_SCREENINDEX)->SetFocus();
		return;
	}
	m_BeginIndex=_ttoi(szIndex);

	CDialogEx::OnOK();
}