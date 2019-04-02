#include "stdafx.h"
#include "XChangeScreen.h"
#include "..\resource.h"
#include "XScreen.h"
#include "XScreenManage.h"

IMPLEMENT_DYNAMIC(XChangeScreen, CDialogEx)

	XChangeScreen::XChangeScreen(CWnd* pParent /*=NULL*/)
	: CDialogEx(XChangeScreen::IDD, pParent)
{
}

XChangeScreen::~XChangeScreen()
{
}

void XChangeScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_AFTER, m_ComboBox_After);
}

BEGIN_MESSAGE_MAP(XChangeScreen, CDialogEx)
	ON_BN_CLICKED( IDOK, &XChangeScreen::OnBtnOK)

END_MESSAGE_MAP()

void XChangeScreen::SetDelegate(XDelegateChangeScreen* p)
{
	m_pDelegate=p;
}

void XChangeScreen::SetScreenMange(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XChangeScreen::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

BOOL XChangeScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitCombo();

	InitData();

	return FALSE; 
}

void XChangeScreen::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("490"), _T("½»»»ÆÁÄ»")));

	GetDlgItem(IDC_STATIC_BEFOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("491"),_T("µ±Ç°ÆÁÄ»"))+_T(":"));

	GetDlgItem(IDC_STATIC_AFTER)->SetWindowText(m_pDelegate->GetTranslationString(_T("492"),_T("½»»»ºóÆÁÄ»"))+_T(":"));

}

void XChangeScreen::InitData()
{
	CString szStr;

	szStr.Format(_T("%d"),m_ScreenIndex);

	GetDlgItem(IDC_EDIT_BEFOR)->SetWindowText(szStr);
}

void XChangeScreen::InitCombo()
{
	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();iter++)
	{
		XScreen* pScreen=*iter;

		int nIndex=pScreen->GetIndex();

		if(m_ScreenIndex==nIndex)
		{
			continue;
		}

		CString szStr;
		szStr.Format(_T("%d"),nIndex);
		m_ComboBox_After.AddString(szStr);
	}
	m_ComboBox_After.SetCurSel(0);
}

int XChangeScreen::GetComboIndex()
{
	return m_ComboIndex;
}

int XChangeScreen::GetScreenIndex()
{
	return m_ScreenIndex;
}

void XChangeScreen::SetScreenIndex(int n)
{
	m_ScreenIndex=n;
}

void XChangeScreen::OnBtnOK()
{
	CString szStr;

	m_ComboBox_After.GetLBText(m_ComboBox_After.GetCurSel(),szStr);

	m_ComboIndex=_ttoi(szStr);

	CDialogEx::OnOK();
}