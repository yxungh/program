// ChangeRTSPAddrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "XUserManage.h"
#include "XDelegateUserManage.h"
#include "..\XConstant.h"
#include "HandlePath.h"
#include "HandleIni.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_UserManage = NULL;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetLimitText(18);
	((CEdit*)GetDlgItem(IDC_EDIT_PSW))->SetLimitText(18);

	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);
	CString szAccount = HandleIni::GetString(_T("Info"), _T("Account"), _T(""), szIniPath);
	GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(szAccount);

	return FALSE;  
}

void CLoginDlg::ReloadInterface()
{
	XDelegateUserManage* pDelegate = m_UserManage->GetDelegate();

	SetWindowText(pDelegate->GetTranslationString(_T("344"), _T("登陆")));

	GetDlgItem(IDOK)->SetWindowText(pDelegate->GetTranslationString(_T("214"), _T("确定")));

	GetDlgItem(IDCANCEL)->SetWindowText(pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_ACCOUNT)->SetWindowText(pDelegate->GetTranslationString(_T("348"), _T("帐号")) + _T(":"));

	GetDlgItem(IDC_STATIC_PSW)->SetWindowText(pDelegate->GetTranslationString(_T("349"), _T("密码")) + _T(":"));
}

void CLoginDlg::SetUserManage(XUserManage* p)
{
	m_UserManage = p;
}

void CLoginDlg::OnBnClickedOk()
{
	CString szAccount = _T("");
	GetDlgItem(IDC_EDIT_ACCOUNT)->GetWindowText(szAccount);
	szAccount.Trim();
	if (_T("") == szAccount)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("350"), _T("帐号不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();

		return;
	}

	CString szPSW = _T("");
	GetDlgItem(IDC_EDIT_PSW)->GetWindowText(szPSW);
	szPSW.Trim();
	if (_T("") == szPSW)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("21"), _T("密码不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_PSW)->SetFocus();

		return;
	}

	//保存到INI
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);
	HandleIni::WriteData(_T("Info"), _T("Account"), szAccount, szIniPath);

	XUserInfo* pUserInfo = m_UserManage->DecideAccountAndPsw(szAccount, szPSW);

	if (NULL == pUserInfo)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("352"), _T("帐号或密码错误，请重新输入!"), MB_OK);
	}
	else
	{
		m_UserManage->SetCurUserInfo(pUserInfo);

		CDialogEx::OnOK();
	}
}
