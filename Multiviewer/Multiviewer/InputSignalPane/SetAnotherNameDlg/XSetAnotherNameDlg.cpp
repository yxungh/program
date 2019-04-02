#include "stdafx.h"
#include "XSetAnotherNameDlg.h"
#include "afxdialogex.h"
#include "XSetAnotherNameDlg.h"
#include "XInputSignal.h"
#include "XDelegateSetAnotherNameDlg.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XSetAnotherNameDlg, CDialogEx)

	XSetAnotherNameDlg::XSetAnotherNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetAnotherNameDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

	m_szTitle=_T("");
}

XSetAnotherNameDlg::~XSetAnotherNameDlg()
{

}

void XSetAnotherNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSetAnotherNameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XSetAnotherNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XSetAnotherNameDlg::SetDelegate(XDelegateSetAnotherNameDlg* p)
{
	m_pDelegate = p;
}

void XSetAnotherNameDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XSetAnotherNameDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XSetAnotherNameDlg::SetInputSignalName(CString s)
{
	m_InputSignalName=s;
}

BOOL XSetAnotherNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XSetAnotherNameDlg::ReloadInterface()
{
	SetWindowText(m_szTitle+_T("-")+m_InputSignalName);
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));
	GetDlgItem(IDC_STATIC_ANOTHERNAME)->SetWindowText(m_pDelegate->GetTranslationString(_T("390"), _T("名称"))+ _T(":"));
	GetDlgItem(IDC_STATIC_TIPS49)->SetWindowText(m_pDelegate->GetTranslationString(_T("660"),_T("提示:备注为空时取消备注")));
}

void XSetAnotherNameDlg::InitData()
{
	GetDlgItem(IDC_EDIT_ANOTHERNAME)->SetWindowText(m_InputSignal->GetAnotherName());
}

CString XSetAnotherNameDlg::GetAnotherName()
{
	return m_AnotherName;
}

void XSetAnotherNameDlg::SetTitle(CString szStr)
{
	m_szTitle=szStr;
}

void XSetAnotherNameDlg::OnBnClickedOk()
{
	CString szName = _T("");
	GetDlgItem(IDC_EDIT_ANOTHERNAME)->GetWindowText(szName);
	szName.Trim();
	//if (_T("") == szName)
	//{
	//	m_pDelegate->MessageBoxFromKey(_T("217"), _T("名称不能为空,请输入!"), MB_OK);

	//	GetDlgItem(IDC_EDIT_ANOTHERNAME)->SetFocus();

	//	return;
	//}

	m_AnotherName=szName;

	CDialogEx::OnOK();
}