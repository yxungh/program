#include "stdafx.h"
#include "XReNameTabCtrl.h"
#include "XInternalManage.h"


IMPLEMENT_DYNAMIC(XReNameTabCtrl, CDialogEx)

	XReNameTabCtrl::XReNameTabCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(XReNameTabCtrl::IDD, pParent)
{
	m_pManage=NULL;

	m_szOldName=_T("");

	m_szNewName=_T("");

	m_szTitle=_T("");
}

XReNameTabCtrl::~XReNameTabCtrl()
{

}

void XReNameTabCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XReNameTabCtrl, CDialogEx)

	ON_BN_CLICKED(IDOK, &XReNameTabCtrl::OnBnClickedOk)
END_MESSAGE_MAP()

void XReNameTabCtrl::SetManage(XInternalManage* pManage)
{
	m_pManage=pManage;
}

BOOL XReNameTabCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE; 
}

void XReNameTabCtrl::ReloadInterface()
{
	SetWindowText(m_szTitle);
	GetDlgItem(IDC_STATIC_ANOTHERNAME)->SetWindowText(m_pManage->GetTranslationString(_T("390"),_T("名称")));
	GetDlgItem(IDC_STATIC_TIPS49)->SetWindowText(m_pManage->GetTranslationString(_T("660"),_T("提示:备注为空时取消备注")));
	GetDlgItem(IDOK)->SetWindowText(m_pManage->GetTranslationString(_T("240"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pManage->GetTranslationString(_T("241"),_T("取消")));
}

void XReNameTabCtrl::InitData()
{
	GetDlgItem(IDC_EDIT_ANOTHERNAME)->SetWindowText(GetOldName());
}

void XReNameTabCtrl::OnBnClickedOk()
{
	CString szTemp=_T("");
	GetDlgItem(IDC_EDIT_ANOTHERNAME)->GetWindowText(szTemp);

	m_szNewName=szTemp;

	CDialogEx::OnOK();
}