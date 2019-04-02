#include "stdafx.h"
#include "XEDIDDlg.h"
#include "afxdialogex.h"
#include "XDelegateEDIDDlg.h"
#include "XInputSignal.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XEDIDDlg, CDialogEx)

	XEDIDDlg::XEDIDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XEDIDDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;
}

XEDIDDlg::~XEDIDDlg()
{

}

void XEDIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XEDIDDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XEDIDDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XEDIDDlg::SetDelegate(XDelegateEDIDDlg* p)
{
	m_pDelegate = p;
}

void XEDIDDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XEDIDDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XEDIDDlg::SetInputSignalName(CString s)
{
	m_InputSignalName=s;
}

BOOL XEDIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XEDIDDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("455"), _T("设置EDID"))+_T("-")+m_InputSignalName);

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_EDID)->SetWindowText(m_pDelegate->GetTranslationString(_T("458"), _T("EDID参数内容")) + _T(":"));
}

void XEDIDDlg::InitData()
{
	XEDIDInfo* pInfo=m_InputSignal->GetEDIDInfo();

	GetDlgItem(IDC_EDIT_EDID)->SetWindowText(pInfo->GetText());
}

void XEDIDDlg::OnBnClickedOk()
{
	CString szText;
	GetDlgItem(IDC_EDIT_EDID)->GetWindowText(szText);

	int nLen=szText.GetLength();

	XEDIDInfo* pInfo=m_InputSignal->GetEDIDInfo();

	pInfo->SetText(szText);
	pInfo->SetDataLen(nLen);

	CDialogEx::OnOK();
}