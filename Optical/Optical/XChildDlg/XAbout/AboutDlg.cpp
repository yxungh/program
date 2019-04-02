// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XTranslationManage.h"

// CAboutDlg 对话框

IMPLEMENT_DYNAMIC(CAboutDlg, XDialog)

CAboutDlg::CAboutDlg(CWnd* pParent,CString szPhotoPath)
	: XDialog(CAboutDlg::IDD, pParent,szPhotoPath)
{

}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, XDialog)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
	ON_STN_DBLCLK(IDC_STATIC4, OnStnDblclickStatic4)
	ON_STN_DBLCLK(IDC_STATIC_ABOUT, OnStnDblclickStatic4)
END_MESSAGE_MAP()


// CAboutDlg 消息处理程序


BOOL CAboutDlg::OnInitDialog()
{
	XDialog::OnInitDialog();

	SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("10"), _T("关于")));

	//GetDlgItem(IDOK)->SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("1"), _T("确定")));

	GetDlgItem(IDC_STATIC1)->SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("11"), _T("版本")) + _T(":") + APP_VERSION);

	GetDlgItem(IDC_STATIC2)->SetWindowText(_T("广州魅视电子科技有限公司　版权所有"));

	GetDlgItem(IDC_STATIC3)->SetWindowText(_T("Copyright© 2018-2019 AVCIT"));
	
	GetDlgItem(IDC_STATIC4)->SetWindowText(_T("http://www.avcit.com.cn"));

	CreateBtn();

	return TRUE;
}

void CAboutDlg::CreateBtn()
{
	CRect rect;
	GetClientRect(&rect);

	int nLeft=rect.right-47;

	CRect rtClose(nLeft,1,nLeft+46,29);
	m_Btn_Close.Create(WS_CHILD|WS_VISIBLE,rtClose,this,ID_BTN_CLOSE);
	m_Btn_Close.ShowWindow(SW_SHOW);
	m_Btn_Close.UpdateWindow();
	m_Btn_Close.SetImage(XHandlePath::GetPhotoPath(_T("close.png")));
}

LRESULT CAboutDlg::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if (ID_BTN_CLOSE==wParam)
	{
		OnCancel();
	}

	return 0;
}

void CAboutDlg::OnStnDblclickStatic4()
{
	ShellExecute(NULL, _T("open"), _T("http://www.avcit.com.cn"), NULL, NULL, SW_SHOWNORMAL); 
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = XDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (IDC_STATIC4==pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(87, 160, 241));
	}

	return hbr;
}