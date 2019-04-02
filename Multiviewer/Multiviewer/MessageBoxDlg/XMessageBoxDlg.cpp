// XMessageBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XMessageBoxDlg.h"
#include "afxdialogex.h"
#include "XConstantIM.h"
#include "XDelegateMessageBoxDlg.h"

#define DLG_WIDTH	400
#define DLG_HEIGHT	150

#define BTN_WIDTH	80
#define BTN_HEIGHT	25

// XMessageBoxDlg 对话框

IMPLEMENT_DYNAMIC(XMessageBoxDlg, CDialogEx)

XMessageBoxDlg::XMessageBoxDlg(CString szText, CString szCaption, UINT uType, 
	CWnd* pParent) : CDialogEx(XMessageBoxDlg::IDD, pParent)
{
	m_szText = szText;

	m_szCaption = szCaption;

	m_uType = uType;

	m_pStatic = nullptr;

	m_pBtnArr = nullptr;

	m_pDelegate = nullptr;

	m_nBtnCount = 0;
}

XMessageBoxDlg::~XMessageBoxDlg()
{
	Clear();
}

void XMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XMessageBoxDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MESSAGEBOXDLG_1, &XMessageBoxDlg::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_MESSAGEBOXDLG_2, &XMessageBoxDlg::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_MESSAGEBOXDLG_3, &XMessageBoxDlg::OnBnClickedBtn3)
END_MESSAGE_MAP()


// XMessageBoxDlg 消息处理程序

BOOL XMessageBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_szCaption);

	InitControl();

	AdjustLayout();

	CenterWindow();

	return TRUE;
}

void XMessageBoxDlg::InitControl()
{
	InitControlOfStatic();

	InitControlOfButtn();
}

void XMessageBoxDlg::InitControlOfStatic()
{
	m_pStatic = new CStatic();

	m_pStatic->Create(m_szText, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_STATIC_MESSAGEBOXDLG_TEXT);

	m_pStatic->SetFont(GetFont());
}

void XMessageBoxDlg::InitControlOfButtn()
{
	CString szCaption = _T("");

	CRect rect(0, 0, 0, 0);

	CFont* pFont = GetFont();

	switch(m_uType)
	{
	case MB_OK:
		{
			m_nBtnCount = 1;

			m_pBtnArr = new CButton[m_nBtnCount];

			szCaption = m_pDelegate->GetTranslationString(_T("240"), _T("确定"));
			m_pBtnArr[0].Create(szCaption, WS_CHILD | WS_VISIBLE, rect, this, IDC_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);
		}
		break;
	case MB_OKCANCEL:
		{
			m_nBtnCount = 2;

			m_pBtnArr = new CButton[m_nBtnCount];

			szCaption = m_pDelegate->GetTranslationString(_T("241"), _T("取消"));
			m_pBtnArr[0].Create(szCaption, WS_CHILD | WS_VISIBLE, rect, this, IDC_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);

			szCaption = m_pDelegate->GetTranslationString(_T("240"), _T("确定"));
			m_pBtnArr[1].Create(szCaption, WS_CHILD | WS_VISIBLE, rect, this, IDC_BTN_MESSAGEBOXDLG_2);
			m_pBtnArr[1].SetFont(pFont);
		}
		break;
	case MB_YESNO:
		{
			m_nBtnCount = 2;

			m_pBtnArr = new CButton[m_nBtnCount];

			szCaption = m_pDelegate->GetTranslationString(_T("462"), _T("是"));
			m_pBtnArr[0].Create(szCaption, WS_CHILD | WS_VISIBLE, rect, this, IDC_BTN_MESSAGEBOXDLG_1);
			m_pBtnArr[0].SetFont(pFont);

			szCaption = m_pDelegate->GetTranslationString(_T("461"), _T("否"));
			m_pBtnArr[1].Create(szCaption, WS_CHILD | WS_VISIBLE, rect, this, IDC_BTN_MESSAGEBOXDLG_2);
			m_pBtnArr[1].SetFont(pFont);
		}
		break;
	default:
		break;
	}
}

void XMessageBoxDlg::SetDelegate(XDelegateMessageBoxDlg* p)
{
	m_pDelegate = p;
}

void XMessageBoxDlg::AdjustLayout()
{
	MoveWindow(0, 0, DLG_WIDTH, DLG_HEIGHT);

	CRect rect;
	GetClientRect(&rect);

	AdjustLayoutOfStatic(rect);

	AdjustLayoutOfButtn(rect);
}

void XMessageBoxDlg::AdjustLayoutOfStatic(CRect& rectDlg)
{
	CRect rect(20, 20, rectDlg.Width() - 20, rectDlg.Height() - 50);

	m_pStatic->MoveWindow(rect);
}

void XMessageBoxDlg::AdjustLayoutOfButtn(CRect& rectDlg)
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

