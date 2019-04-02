#include "stdafx.h"
#include "XBorderOverlayDlg.h"
#include "afxdialogex.h"
#include "XDelegateBorderOverlayDlg.h"
#include "XBorderOverlay.h"
#include "XInputSignal.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XBorderOverlayDlg, CDialogEx)

	XBorderOverlayDlg::XBorderOverlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XBorderOverlayDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

}

XBorderOverlayDlg::~XBorderOverlayDlg()
{

}

void XBorderOverlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_BORDER, m_BorderColor);
}


BEGIN_MESSAGE_MAP(XBorderOverlayDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XBorderOverlayDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XBorderOverlayDlg::SetDelegate(XDelegateBorderOverlayDlg* p)
{
	m_pDelegate = p;
}

void XBorderOverlayDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XBorderOverlayDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XBorderOverlayDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

BOOL XBorderOverlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XBorderOverlayDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("440"),_T("设置边框叠加参数")) + _T(" - ") + m_InputSignalName);

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("214"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_WITH)->SetWindowText(m_pDelegate->GetTranslationString(_T("441"), _T("宽度")) + _T(":"));
	GetDlgItem(IDC_STATIC_COLOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("442"), _T("颜色")) + _T(":"));

	GetDlgItem(IDC_STATIC_NOTICE)->SetWindowText(m_pDelegate->GetTranslationString(_T("443"), _T("(提示:宽度为0时，不使用边框叠加！)")));
}

void XBorderOverlayDlg::InitData()
{
	CString szTemp = _T("");

	XBorderOverlay* pBorder=m_InputSignal->GetBorderOverLay();

	szTemp.Format(_T("%d"), pBorder->GetBorderWith());
	GetDlgItem(IDC_EDIT_WITH)->SetWindowText(szTemp);

	m_BorderColor.SetColor(pBorder->GetBorderColor());
}


void XBorderOverlayDlg::OnBnClickedOk()
{
	CMFCColorButton* pBtnColor = (CMFCColorButton*)GetDlgItem(IDC_COLOR_BORDER);

	COLORREF Color = pBtnColor->GetColor();

	CString szWith = _T("");
	GetDlgItem(IDC_EDIT_WITH)->GetWindowText(szWith);
	szWith.Trim();
	if (_T("") == szWith)
	{
		m_pDelegate->MessageBoxFromKey(_T("288"), _T("宽度不能为空,请输入!"), MB_OK);
		GetDlgItem(IDC_EDIT_WITH)->SetFocus();
		return;
	}
	int nBorderWith=_ttoi(szWith);
	//************************************

	XBorderOverlay* pBorder=m_InputSignal->GetBorderOverLay();

	pBorder->SetBorderWith(nBorderWith);
	pBorder->SetBorderColor(Color);

	CDialogEx::OnOK();
}