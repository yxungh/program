// XMessageBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "XMessageBoxDlg.h"
#include "XHandlePath.h"
#include "XTranslationManage.h"

#define DLG_WIDTH	250
#define DLG_HEIGHT	150

#define BTN_WIDTH	75
#define BTN_HEIGHT	23

// XMessageBoxDlg 对话框

IMPLEMENT_DYNAMIC(XMessageBoxDlg, XDialog)

XMessageBoxDlg::XMessageBoxDlg(CString szText, CString szCaption, UINT uType, 
	CWnd* pParent,CString szPhotoPath) 
	: XDialog(XMessageBoxDlg::IDD, pParent,szPhotoPath)
{
	m_szText = szText;

	m_szCaption = szCaption;

	m_uType = uType;

	m_pStatic = nullptr;

	m_pBtnArr = nullptr;

	m_nBtnCount = 0;
}

XMessageBoxDlg::~XMessageBoxDlg()
{
	Clear();
}

void XMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XMessageBoxDlg, XDialog)
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
END_MESSAGE_MAP()


// XMessageBoxDlg 消息处理程序

BOOL XMessageBoxDlg::OnInitDialog()
{
	XDialog::OnInitDialog();

	SetWindowText(m_szCaption);

	InitControl();

	AdjustLayout();

	CenterWindow();

	return TRUE;
}

void XMessageBoxDlg::InitControl()
{
	InitControlOfStatic();

	InitControlOfButton();
}

void XMessageBoxDlg::InitControlOfStatic()
{
	m_pStatic = new CStatic();

	m_pStatic->Create(m_szText, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ID_STATIC_MESSAGEBOXDLG_TEXT);

	m_pStatic->SetFont(GetFont());
}

CString XMessageBoxDlg::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XMessageBoxDlg::InitControlOfButton()
{
	CString szCaption = _T("");

	CRect rect(0, 0, 0, 0);

	CFont* pFont = GetFont();

	switch(m_uType)
	{
	case MB_OK:
		{
			m_nBtnCount = 1;

			m_pBtnArr = new XBtn[m_nBtnCount];

			szCaption = GetTranslationString(_T("1"), _T("OK"));
			m_pBtnArr[0].Create(WS_CHILD | WS_VISIBLE, rect, this, ID_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);
			m_pBtnArr[0].SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
			m_pBtnArr[0].SetCaption(szCaption);
		}
		break;
	case MB_OKCANCEL:
		{
			m_nBtnCount = 2;

			m_pBtnArr = new XBtn[m_nBtnCount];

			szCaption = GetTranslationString(_T("2"), _T("Cancel"));
			m_pBtnArr[0].Create(WS_CHILD | WS_VISIBLE, rect, this, ID_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);
			m_pBtnArr[0].SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
			m_pBtnArr[0].SetCaption(szCaption);

			szCaption = GetTranslationString(_T("1"), _T("OK"));
			m_pBtnArr[1].Create(WS_CHILD | WS_VISIBLE, rect, this, ID_BTN_MESSAGEBOXDLG_2);
			m_pBtnArr[1].SetFont(pFont);
			m_pBtnArr[1].SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
			m_pBtnArr[1].SetCaption(szCaption);
		}
		break;
	case MB_YESNO:
		{
			m_nBtnCount = 2;

			m_pBtnArr = new XBtn[m_nBtnCount];

			szCaption = GetTranslationString(_T("5"), _T("NO"));
			m_pBtnArr[0].Create(WS_CHILD | WS_VISIBLE, rect, this, ID_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);
			m_pBtnArr[0].SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
			m_pBtnArr[0].SetCaption(szCaption);

			szCaption = GetTranslationString(_T("4"), _T("Yes"));
			m_pBtnArr[1].Create(WS_CHILD | WS_VISIBLE, rect, this, ID_BTN_MESSAGEBOXDLG_2);
			m_pBtnArr[1].SetFont(pFont);
			m_pBtnArr[1].SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
			m_pBtnArr[1].SetCaption(szCaption);
		}
		break;
	default:
		break;
	}
}

void XMessageBoxDlg::AdjustLayout()
{
	MoveWindow(0, 0, DLG_WIDTH, DLG_HEIGHT);

	CRect rect;
	GetClientRect(&rect);

	AdjustLayoutOfStatic(rect);

	AdjustLayoutOfButton(rect);
}

void XMessageBoxDlg::AdjustLayoutOfStatic(CRect& rectDlg)
{
	CRect rect(20, 40, rectDlg.Width() - 20, rectDlg.Height() - 50);

	m_pStatic->MoveWindow(rect);
}

void XMessageBoxDlg::AdjustLayoutOfButton(CRect& rectDlg)
{
	CRect rect;

	int nRight = rectDlg.right - 10;

	int nBottom = rectDlg.bottom - 10;

	for (int i = 0; i < m_nBtnCount; i++)
	{
		rect.SetRect(nRight - BTN_WIDTH, nBottom - BTN_HEIGHT, nRight, nBottom);

		nRight = nRight - BTN_WIDTH - 10;

		m_pBtnArr[i].MoveWindow(rect);
	}
}

void XMessageBoxDlg::Clear()
{
	if (nullptr != m_pStatic)
	{
		delete m_pStatic;

		m_pStatic = nullptr;
	}

	if (0 != m_nBtnCount)
	{
		delete[] m_pBtnArr;

		m_pBtnArr = nullptr;
	}
}

void XMessageBoxDlg::OnOK()
{
	switch(m_uType)
	{
	case MB_OK:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_OKCANCEL:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_YESNO:
		{
			EndDialog(IDYES);
		}
		break;
	default:
		break;
	}
}

void XMessageBoxDlg::OnCancel()
{
	switch(m_uType)
	{
	case MB_OK:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_OKCANCEL:
		{
			EndDialog(IDCANCEL);
		}
		break;
	case MB_YESNO:
		{
			EndDialog(IDNO);
		}
		break;
	default:
		break;
	}
}

LRESULT XMessageBoxDlg::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if(wParam == ID_BTN_MESSAGEBOXDLG_1)
	{
		OnBnClickedBtn1();
	}
	else if(wParam == ID_BTN_MESSAGEBOXDLG_2)
	{
			OnBnClickedBtn2();
	}
	else if(wParam == ID_BTN_MESSAGEBOXDLG_3)
	{
			OnBnClickedBtn3();
	}

	return 0;
}

void XMessageBoxDlg::OnBnClickedBtn1()
{
	switch(m_uType)
	{
	case MB_OK:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_OKCANCEL:
		{
			EndDialog(IDCANCEL);
		}
		break;
	case MB_YESNO:
		{
			EndDialog(IDNO);
		}
		break;
	default:
		break;
	}
}

void XMessageBoxDlg::OnBnClickedBtn2()
{
	switch(m_uType)
	{
	case MB_OK:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_OKCANCEL:
		{
			EndDialog(IDOK);
		}
		break;
	case MB_YESNO:
		{
			EndDialog(IDYES);
		}
		break;
	default:
		break;
	}
}

void XMessageBoxDlg::OnBnClickedBtn3()
{

}

