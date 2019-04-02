// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AboutDlg.h"
#include "XDelegateAboutDlg.h"
#include "../XConstant.h"

// CAboutDlg 对话框

IMPLEMENT_DYNAMIC(CAboutDlg, CDialogEx)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAboutDlg::IDD, pParent)
{
	m_Delegate = NULL;
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_STN_DBLCLK(IDC_STATIC4, OnStnDblclickStatic4)
	ON_STN_DBLCLK(IDC_STATIC_LOGO, OnStnDblclickStatic4)
END_MESSAGE_MAP()


// CAboutDlg 消息处理程序


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(APP_NAME + _T(" ") + APP_VERSION);

	//GetDlgItem(IDOK)->SetWindowText(m_Delegate->GetTranslationString(_T("208"), _T("确定")));

	GetDlgItem(IDC_STATIC1)->SetWindowText(APP_NAME + _T(" ") + APP_VERSION);

	//GetDlgItem(IDC_STATIC2)->SetWindowText(_T("广州魅视电子科技有限公司　版权所有"));

	//GetDlgItem(IDC_STATIC3)->SetWindowText(_T("Copyright© 2017-2018 AVCIT"));
	
	//GetDlgItem(IDC_STATIC4)->SetWindowText(_T("http://www.avcit.com.cn"));

	return TRUE;
}

void CAboutDlg::SetDelegate(XDelegateAboutDlg* p)
{
	m_Delegate = p;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (IDC_STATIC4 == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 0, 255));
	}

	return hbr;
}

void CAboutDlg::OnStnDblclickStatic4()
{
	ShellExecute(NULL, _T("open"), _T("http://www.avcit.com.cn"), NULL, NULL, SW_SHOWNORMAL); 
}