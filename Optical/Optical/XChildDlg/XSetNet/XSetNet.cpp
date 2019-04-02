// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XSetNet.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XDelegateSetNet.h"

// XSetNet 对话框

IMPLEMENT_DYNAMIC(XSetNet, XDialog)

	XSetNet::XSetNet(CWnd* pParent,CString szPhotoPath)
	: XDialog(XSetNet::IDD, pParent,szPhotoPath),
	m_pDelegate(NULL)
{

}

XSetNet::~XSetNet()
{
}

void XSetNet::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
	DDX_Control(pDX,ID_BTN_OK,m_Btn_OK);
	DDX_Control(pDX,ID_BTN_CANCEL,m_Btn_Cancel);	
}


BEGIN_MESSAGE_MAP(XSetNet, XDialog)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)

END_MESSAGE_MAP()


// XSetNet 消息处理程序
void XSetNet::SetDelegate(XDelegateSetNet* p)
{
	m_pDelegate=p;
}

BOOL XSetNet::OnInitDialog()
{
	XDialog::OnInitDialog();

	Init();

	return TRUE;
}

void XSetNet::Init()
{
	InitBtn();
	InitShowData();
	ReloadInterface();
}

void XSetNet::InitShowData()
{
	GetDlgItem(IDC_IPADDRESS_IP)->SetWindowText(m_pDelegate->GetIP());

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),m_pDelegate->GetPort());
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(szTemp);
}

void XSetNet::ReloadInterface()
{
	SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("15"), _T("网络设置")));

	GetDlgItem(IDC_STATIC_IP)->SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("16"), _T("IP地址"))+_T(":"));
	GetDlgItem(IDC_STATIC_PORT)->SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("17"), _T("端口号"))+_T(":"));

	m_Btn_OK.SetCaption(XTranslationManage::GetInstance()->GetTranslationString(_T("1"), _T("确定")));
	m_Btn_Cancel.SetCaption(XTranslationManage::GetInstance()->GetTranslationString(_T("2"), _T("取消")));
}

void XSetNet::InitBtn()
{
	m_Btn_OK.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_Cancel.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));

	CRect rect;
	GetClientRect(&rect);

	int nLeft=rect.right-47;
	CRect rtClose(nLeft,1,nLeft+46,29);
	m_Btn_Close.Create(WS_CHILD|WS_VISIBLE,rtClose,this,ID_BTN_CLOSE);
	m_Btn_Close.ShowWindow(SW_SHOW);
	m_Btn_Close.UpdateWindow();
	m_Btn_Close.SetImage(XHandlePath::GetPhotoPath(_T("close.png")));
}

void XSetNet::OnBtnClickedOk()
{
	CString szIP=_T("");
	GetDlgItem(IDC_IPADDRESS_IP)->GetWindowText(szIP);

	CString szPort=_T("");
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(szPort);

	if (_T("")==szPort)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("17"), _T("端口不能为空,请重新输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_PORT)->SetFocus();

		return;
	}

	int nPort=_ttoi(szPort);

	m_pDelegate->SetDeviceIPAndPort(szIP,nPort);

	m_pDelegate->SaveDeviceIPAndPort(szIP,nPort);

	//发送心跳
	m_pDelegate->SendHeart();

	XDialog::OnOK();
}

LRESULT XSetNet::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if(wParam==ID_BTN_CLOSE)
	{
		OnCancel();
	}
	else if(wParam==ID_BTN_OK)
	{
		OnBtnClickedOk();
	}
	else if(wParam==ID_BTN_CANCEL)
	{
		OnCancel();
	}

	return 0;
}

