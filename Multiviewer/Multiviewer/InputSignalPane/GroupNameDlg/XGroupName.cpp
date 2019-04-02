#include "stdafx.h"
#include "XGroupName.h"
#include "afxdialogex.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"



// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XGroupName, CDialogEx)

	XGroupName::XGroupName(CWnd* pParent /*=NULL*/)
	: CDialogEx(XGroupName::IDD, pParent)
{

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;
}

XGroupName::~XGroupName()
{

}

void XGroupName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XGroupName, CDialogEx)
	ON_BN_CLICKED(IDOK, &XGroupName::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

//void XGroupName::SetDelegate(XDelegateSetAnotherNameDlg* p)
//{
//	m_pDelegate = p;
//}

void XGroupName::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XGroupName::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XGroupName::SetInputSignalName(CString s)
{
	m_InputSignalName=s;
}

BOOL XGroupName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	GetDlgItem(IDC_EDIT_GNAME)->SetFocus();

	return FALSE;  
}

void XGroupName::ReloadInterface()
{
	SetWindowText(m_InputSignalPane->GetTranslationString(_T("670"), _T("设置分组名称")));
	GetDlgItem(IDOK)->SetWindowText(m_InputSignalPane->GetTranslationString(_T("240"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_InputSignalPane->GetTranslationString(_T("241"), _T("取消")));
	GetDlgItem(IDC_STATIC_GROUPNAME)->SetWindowText(m_InputSignalPane->GetTranslationString(_T("671"),_T("分组名称"))+_T(":"));
}

void XGroupName::InitData()
{
	//GetDlgItem(IDC_EDIT_ANOTHERNAME)->SetWindowText(m_InputSignal->GetAnotherName());
}

CString XGroupName::GetAnotherName()
{
	return m_AnotherName;
}

void XGroupName::OnBnClickedOk()
{
	CString szName = _T("");
	GetDlgItem(IDC_EDIT_GNAME)->GetWindowText(szName);
	szName.Trim();
	if (_T("") == szName)
	{
		m_InputSignalPane->MessageBoxFromKey(_T("217"), _T("名称不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_GNAME)->SetFocus();

		return;
	}

	m_AnotherName=szName;

	if(m_InputSignalPane->IsNameHas(szName))
	{
		m_InputSignalPane->MessageBoxFromKey(_T("672"),_T("组名称已存在！"),MB_OK);

		return;
	}

	CDialogEx::OnOK();
}