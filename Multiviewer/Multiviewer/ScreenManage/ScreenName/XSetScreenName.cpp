#include "stdafx.h"
#include "XSetScreenName.h"
#include "afxdialogex.h"
#include "XDelegateSetScreenName.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XSetScreenName, CDialogEx)

	XSetScreenName::XSetScreenName(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetScreenName::IDD, pParent)
{
	m_pDelegate = NULL;

	m_szScreenName=_T("");

	m_szTitle=_T("");
}

XSetScreenName::~XSetScreenName()
{

}

void XSetScreenName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSetScreenName, CDialogEx)
	ON_BN_CLICKED(IDOK, &XSetScreenName::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XSetScreenName::SetDelegate(XDelegateSetScreenName* p)
{
	m_pDelegate = p;
}

BOOL XSetScreenName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XSetScreenName::SetTitle(CString szTitle)
{
	m_szTitle=szTitle;
}

void XSetScreenName::ReloadInterface()
{
	SetWindowText(m_szTitle);
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));
	GetDlgItem(IDC_STATIC_ANOTHERNAME)->SetWindowText(m_pDelegate->GetTranslationString(_T("390"), _T("名称"))+ _T(":"));
	GetDlgItem(IDC_STATIC_TIPS49)->SetWindowText(m_pDelegate->GetTranslationString(_T("660"),_T("提示:备注为空时取消备注")));
}

void XSetScreenName::InitData()
{
	//GetDlgItem(IDC_EDIT_ANOTHERNAME)->SetWindowText(m_InputSignal->GetAnotherName());
}

CString XSetScreenName::GetScreenName()
{
	return m_szScreenName;
}

void XSetScreenName::OnBnClickedOk()
{
	CString szName = _T("");
	GetDlgItem(IDC_EDIT_ANOTHERNAME)->GetWindowText(szName);
	szName.Trim();

	m_szScreenName=szName;

	CDialogEx::OnOK();
}