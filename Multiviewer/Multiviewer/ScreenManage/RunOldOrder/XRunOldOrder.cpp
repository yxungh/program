#include "stdafx.h"
#include "XRunOldOrder.h"
#include "afxdialogex.h"
#include "XDelegateRunOldOrder.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "XOldOrderInfo.h"


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XRunOldOrderDlg, CDialogEx)

	XRunOldOrderDlg::XRunOldOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XRunOldOrderDlg::IDD, pParent)
{
	m_pDelegate = NULL;
}

XRunOldOrderDlg::~XRunOldOrderDlg()
{

}

void XRunOldOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XRunOldOrderDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XRunOldOrderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XRunOldOrderDlg::SetDelegate(XDelegateRunOldOrderDlg* p)
{
	m_pDelegate = p;
}

void XRunOldOrderDlg::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XRunOldOrderDlg::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

BOOL XRunOldOrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XRunOldOrderDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("500"),_T("执行旧指令")));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("502"), _T("执行")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_OLDORDER)->SetWindowText(m_pDelegate->GetTranslationString(_T("503"), _T("旧指令内容")) + _T(":"));

}

void XRunOldOrderDlg::InitData()
{
	XOldOrderInfo* pInfo=m_pScreenManage->GetOldOrderInfo();

	GetDlgItem(IDC_EDIT_OLDORDER)->SetWindowText(pInfo->GetText());
}

void XRunOldOrderDlg::OnBnClickedOk()
{
	CString szText;

	GetDlgItem(IDC_EDIT_OLDORDER)->GetWindowText(szText);

	int nLen=szText.GetLength();

	XOldOrderInfo* pInfo=m_pScreenManage->GetOldOrderInfo();

	pInfo->SetText(szText);

	pInfo->SetDataLen(nLen);

	CDialogEx::OnOK();
}