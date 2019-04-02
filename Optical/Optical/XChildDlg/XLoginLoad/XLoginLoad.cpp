// XLoginLoad.cpp : 实现文件
//

#include "stdafx.h"
#include "XLoginLoad.h"
#include "XConstant.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XTranslationManage.h"

// XLoginLoad 对话框

IMPLEMENT_DYNAMIC(XLoginLoad, XDialog)

	XLoginLoad::XLoginLoad(CWnd* pParent,CString szPhotoPath)
	: XDialog(XLoginLoad::IDD, pParent,szPhotoPath),
	m_nIndex(0),
	m_szText(_T(""))
{
	m_bEnableVK_RETURN = FALSE;
	m_bEnableVK_ESCAPE = FALSE;
}

XLoginLoad::~XLoginLoad()
{
}

void XLoginLoad::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XLoginLoad, XDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void XLoginLoad::OnOK()
{
	__super::OnOK();
}

void XLoginLoad::OnCancel()
{
	__super::OnCancel();
}

// XLoginLoad 消息处理程序
BOOL XLoginLoad::OnInitDialog()
{
	XDialog::OnInitDialog();

	Init();

	return TRUE;
}

void XLoginLoad::Init()
{
	m_szText=XTranslationManage::GetInstance()->GetTranslationString(_T("44"));

	UpdateText();

	SetTimer(1, 500, NULL);
}

void XLoginLoad::OnTimer(UINT_PTR nIDEvent)
{
	UpdateText();
	__super::OnTimer(nIDEvent);
}

void XLoginLoad::UpdateText()
{
	m_nIndex++;

	CString szText=m_szText;

	for(int i=0;i<6;i++)
	{
		if (i<m_nIndex)
		{
			szText+=_T("．");
		}
		else
		{
			szText+=_T("　");
		}
	}

	if (m_nIndex>=6)
	{
		m_nIndex=0;
	}

	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(szText);

	CRect rectText;
	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(&rectText);
	ScreenToClient(&rectText);

	InvalidateRect(&rectText);
}


