#include "stdafx.h"
#include "XMatrixScreenAttributes.h"
#include "afxdialogex.h"
#include "XDelegateMatrixScreenAttributes.h"
#include "XScreen.h"
#include "XScreenManage.h"


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XScreenMatrixAttributesDlg, CDialogEx)

	XScreenMatrixAttributesDlg::XScreenMatrixAttributesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XScreenMatrixAttributesDlg::IDD, pParent)
{
	m_pDelegate = NULL;

}

XScreenMatrixAttributesDlg::~XScreenMatrixAttributesDlg()
{

}

void XScreenMatrixAttributesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(XScreenMatrixAttributesDlg, CDialogEx)

END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XScreenMatrixAttributesDlg::SetDelegate(XDelegateMatrixScreenAttributesDlg* p)
{
	m_pDelegate = p;
}

void XScreenMatrixAttributesDlg::SetInputSignalName(CString s)
{
	m_InputSignalName=s;
}

void XScreenMatrixAttributesDlg::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XScreenMatrixAttributesDlg::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

BOOL XScreenMatrixAttributesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XScreenMatrixAttributesDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("456"),_T("属性")));

	GetDlgItem(IDC_STATIC_EQUSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("557"), _T("设备类型")) + _T(":"));

	GetDlgItem(IDC_STATIC_RESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("402"), _T("水平分辨率")) + _T(":"));
	GetDlgItem(IDC_STATIC_RESV)->SetWindowText(m_pDelegate->GetTranslationString(_T("403"), _T("垂直分辨率")) + _T(":"));
	GetDlgItem(IDC_STATIC_REFRESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("416"), _T("刷新频率")) + _T(":"));
	GetDlgItem(IDC_STATIC_CHENALINDEX)->SetWindowText(m_pDelegate->GetTranslationString(_T("713"), _T("通道")) + _T(":"));

	GetDlgItem(IDC_STATIC_DEVICE)->SetWindowText(m_pDelegate->GetTranslationString(_T("714"), _T("是否有输出信号")) + _T(":"));

}

void XScreenMatrixAttributesDlg::InitData()
{
	int nBoardIndex=m_pScreen->GetBoardIndex();

	int nChenal=m_pScreen->GetNumOfTwoScreen();

	CString szTemp;

	if(nBoardIndex==0)
	{
		GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("541"),_T("无设备")));
		GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));

		int i=0;
		szTemp.Format(_T("%d"),i);
		GetDlgItem(IDC_STATIC_H)->SetWindowText(szTemp);
		GetDlgItem(IDC_STATIC_V)->SetWindowText(szTemp);
		GetDlgItem(IDC_STATIC_CHENALINDEX2)->SetWindowText(szTemp);
		GetDlgItem(IDC_STATIC_FRESH)->SetWindowText(szTemp);
	}
	else
	{
		if(m_pScreen->GetScreenType()==0x30)
		{
			GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("715"),_T("矩阵HDMI/DVI")));
		}
		else if(m_pScreen->GetScreenType()==0x40)
		{
			GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("716"),_T("矩阵VGA")));
		}
		else if(m_pScreen->GetScreenType()==0x50)
		{
			GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("717"),_T("矩阵SDI")));
		}
		else if(m_pScreen->GetScreenType()==0x60)
		{
			GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("718"),_T("矩阵AV")));
		}
		else
		{
			GetDlgItem(IDC_STATIC_DEVSTYLE)->SetWindowText(m_pDelegate->GetTranslationString(_T("541"),_T("无设备")));
		}

		if(m_pScreen->GetIsHasSignalOfMatrix())
		{
			GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));
		}
		else
		{
			GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));
		}

		szTemp.Format(_T("%d"), m_pScreen->GetReScreenHdpi());
		GetDlgItem(IDC_STATIC_H)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), m_pScreen->GetReScreenVdpi());
		GetDlgItem(IDC_STATIC_V)->SetWindowText(szTemp);

		if(nChenal!=0)
		{
			szTemp.Format(_T("%d"), nChenal);
			GetDlgItem(IDC_STATIC_CHENALINDEX2)->SetWindowText(szTemp);
		}
		else
		{
			GetDlgItem(IDC_STATIC_CHENALINDEX2)->SetWindowText(m_pDelegate->GetTranslationString(_T("551"),_T("无")));
		}


		szTemp.Format(_T("%d"), m_pScreen->GetReRefresh());
		GetDlgItem(IDC_STATIC_FRESH)->SetWindowText(szTemp);
	
	}
}
