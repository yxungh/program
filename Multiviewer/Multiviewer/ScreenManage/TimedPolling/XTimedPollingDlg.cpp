#include "stdafx.h"
#include "XTimedPollingDlg.h"
#include "afxdialogex.h"
#include "XDelegateTimedPollingDlg.h"
#include "XScreen.h"
#include "XScreenManage.h"


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XTimedPollingDlg, CDialogEx)

	XTimedPollingDlg::XTimedPollingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XTimedPollingDlg::IDD, pParent)
{
	m_pDelegate = NULL;

}

XTimedPollingDlg::~XTimedPollingDlg()
{

}

void XTimedPollingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(XTimedPollingDlg, CDialogEx)
	ON_BN_CLICKED( IDOK, &XTimedPollingDlg::OnBtnOK)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XTimedPollingDlg::SetDelegate(XDelegateTimedPollingDlg* p)
{
	m_pDelegate = p;
}

void XTimedPollingDlg::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XTimedPollingDlg::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

BOOL XTimedPollingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XTimedPollingDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("464"),_T("定时轮询间隔")));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("208"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("209"),_T("取消")));

	GetDlgItem(IDC_STATIC_TIMEDPOLLING)->SetWindowText(m_pDelegate->GetTranslationString(_T("465"),_T("时间间隔"))+_T(":"));
	GetDlgItem(IDC_STATIC_TIMEDTIPS)->SetWindowText(m_pDelegate->GetTranslationString(_T("466"),_T("提示:单位为毫秒，最小时间间隔为50毫秒！")));
}

void XTimedPollingDlg::InitData()
{
	XTimedPollingInfo* pPollingInfo=m_pScreenManage->GetTimedPollingInfo();

	CString szTemp;

	szTemp.Format(_T("%d"), pPollingInfo->GetTimedPolling());
	GetDlgItem(IDC_EDIT_TIMEDPOLLING)->SetWindowText(szTemp);
}

void XTimedPollingDlg::OnBtnOK()
{
	CString szTimedPolling;
	GetDlgItem(IDC_EDIT_TIMEDPOLLING)->GetWindowText(szTimedPolling);
	szTimedPolling.Trim();
	if(szTimedPolling==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("417"),_T("水平分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_TIMEDPOLLING)->SetFocus();
		return;
	}
	int nTimedPolling=_ttoi(szTimedPolling);

	if(nTimedPolling<50)
	{
		m_pDelegate->MessageBoxFromKey(_T("467"),_T("定时轮询时间间隔不能小于50毫秒！"),MB_OK);
		return;
	}

	XTimedPollingInfo* pPollingInfo=m_pScreenManage->GetTimedPollingInfo();
	pPollingInfo->SetTimePolling(nTimedPolling);

	CDialogEx::OnOK();
}