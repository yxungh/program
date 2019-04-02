#include "stdafx.h"
#include "XLogin.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XHandleIni.h"
#include "XHandleVerification.h"
#include "XTranslationManage.h"
#include "XDelegateLogin.h"
#include "XMessageBox.h"
#include "XSendDataManage.h"



IMPLEMENT_DYNAMIC(XLogin, XDialog)

	XLogin::XLogin(CWnd* pParent,CString szPhotoPath)
	: XDialog(XLogin::IDD, pParent,szPhotoPath),
	m_pDelegate(NULL),
	m_szUserName(_T(""))
{
	m_bEnableVK_RETURN=FALSE;
}

XLogin::~XLogin()
{

}

void XLogin::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
	DDX_Control(pDX,ID_BTN_OK,m_Btn_Ok);
	DDX_Control(pDX,ID_BTN_CANCEL,m_Btn_Cancel);
}


BEGIN_MESSAGE_MAP(XLogin, XDialog)
	//ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
END_MESSAGE_MAP()


// XLogin 消息处理程序
void XLogin::OnOK()
{
	__super::OnOK();
}

void XLogin::OnCancel()
{
	__super::OnCancel();
}

BOOL XLogin::OnInitDialog()
{
	XDialog::OnInitDialog();
	
	Init();

	return TRUE;
}

void XLogin::SetDelegate(XDelegateLogin* p)
{
	m_pDelegate=p;
}

CString XLogin::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XLogin::Init()
{
	InitUserName();
	InitBtn();
	ReloadInterface();
}

void XLogin::InitUserName()
{
	CString szIniPath = XHandlePath::GetIniPath(APP_ININAME);
	m_szUserName=XHandleIni::GetString(_T("Info"), _T("UserName"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(m_szUserName);
}

void XLogin::InitBtn()
{
	m_Btn_Ok.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_Cancel.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	GetDlgItem(ID_BTN_OK)->SetFocus();

	CRect rect;
	GetClientRect(&rect);

	int nLeft=rect.right-47;
	CRect rtClose(nLeft,1,nLeft+46,29);
	m_Btn_Close.Create(WS_CHILD|WS_VISIBLE,rtClose,this,ID_BTN_CLOSE);
	m_Btn_Close.ShowWindow(SW_SHOW);
	m_Btn_Close.UpdateWindow();
	m_Btn_Close.SetImage(XHandlePath::GetPhotoPath(_T("close.png")));
}

void XLogin::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("20")));
	GetDlgItem(IDC_STATIC_USERNAME)->SetWindowText(GetTranslationString(_T("23"))+_T(":"));
	GetDlgItem(IDC_STATIC_PASSWD)->SetWindowText(GetTranslationString(_T("24"))+_T(":"));
	
	m_Btn_Ok.SetCaption(GetTranslationString(_T("1")));
	m_Btn_Cancel.SetCaption(GetTranslationString(_T("2")));
}

void XLogin::OnBtnClickedOk()
{
	CString szUserName=_T("");
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(szUserName);
	szUserName.Trim();
	if (_T("")==szUserName)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("25"),_T("用户名不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if (_T("")==szPassWd)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("26"),_T("密码不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}

	if (!XHandleVerification::VerificationString(szUserName))
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("27"),_T("用户名包含非法字符！"),MB_OK);
		return;
	}

	if (!XHandleVerification::VerificationString(szPassWd))
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("28"),_T("密码包含非法字符！"),MB_OK);
		return;
	}

	SaveUserName(szUserName);
	//////////////////////////////////////////////////////////////////////////
	//发送数据
	XSendDataManage::GetInstance()->AddSendDataOfLogin(szUserName,szPassWd);

	//设置现在登陆用户
	m_pDelegate->SetLoginUser(szUserName,szPassWd);
	m_pDelegate->SetLoginLoad();
	//m_pDelegate->SetCurUserName(szUserName);
}

void XLogin::SaveUserName(CString szUserName)
{
	CString szIniPath=XHandlePath::GetIniPath(APP_ININAME);
	XHandleIni::WriteData(_T("Info"),_T("UserName"),szUserName,szIniPath);
}

LRESULT XLogin::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if(ID_BTN_CLOSE==wParam)
	{
		OnCancel();
	}
	else if(ID_BTN_OK==wParam)
	{
		OnBtnClickedOk();
	}
	else if(ID_BTN_CANCEL==wParam)
	{
		OnCancel();
	}

	return 0;
}
