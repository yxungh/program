#include "stdafx.h"
#include "XChangeChanelDlg.h"
#include "afxdialogex.h"
#include "XDelegateChangeChanelDlg.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XChangeChenalDlg, CDialogEx)

	XChangeChenalDlg::XChangeChenalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XChangeChenalDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;
}

XChangeChenalDlg::~XChangeChenalDlg()
{

}

void XChangeChenalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECTEDCHE, m_Combo_SelectedChe);
}


BEGIN_MESSAGE_MAP(XChangeChenalDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XChangeChenalDlg::OnBnClickedOk)

END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XChangeChenalDlg::SetDelegate(XDelegateChangeChenalDlg* p)
{
	m_pDelegate = p;
}

void XChangeChenalDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XChangeChenalDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void XChangeChenalDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

BOOL XChangeChenalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitCombo();

	InitData();

	return FALSE;  
}

void XChangeChenalDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("540"),_T("切换通道"))+_T("-")+m_InputSignalName);

	GetDlgItem(IDC_STATIC_CURCHANEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("553"), _T("当前通道")) + _T(":"));
	GetDlgItem(IDC_STATIC_SELECTEDCHANEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("540"), _T("切换通道")) + _T(":"));
}

void XChangeChenalDlg::InitCombo()
{
	CString szStr;
	for(int i=1;i<3;i++)
	{
		szStr.Format(_T("%d"),i);
		m_Combo_SelectedChe.AddString(szStr);
	}
}

void XChangeChenalDlg::InitData()
{
	CString szStr;

	if(m_InputSignal->GetReStatus()==0x11
		||m_InputSignal->GetReStatus()==0x13
		||m_InputSignal->GetReStatus()==0x2)
	{
		szStr.Format(_T("%d"),1);
		GetDlgItem(IDC_EDIT_CURCHANEL)->SetWindowText(szStr);
	}
	else if(m_InputSignal->GetReStatus()==0x1A
		||m_InputSignal->GetReStatus()==0x1B
		||m_InputSignal->GetReStatus()==0x19
		||m_InputSignal->GetReStatus()==0x18)
	{		
		szStr.Format(_T("%d"),2);
		GetDlgItem(IDC_EDIT_CURCHANEL)->SetWindowText(szStr);
	}

	int n=_ttoi(szStr);

	if(n==1)
	{
		m_Combo_SelectedChe.SetCurSel(1);
	}
	else
	{
		m_Combo_SelectedChe.SetCurSel(0);
	}

}

int XChangeChenalDlg::GetCurChe()
{
	return m_CurChe;
}

int XChangeChenalDlg::GetSelectedChe()
{
	return m_SelectedChe;
}

void XChangeChenalDlg::OnBnClickedOk()
{
	CString szCurChe;

	GetDlgItem(IDC_EDIT_CURCHANEL)->GetWindowText(szCurChe);

	szCurChe.Trim();
	if (_T("") == szCurChe)
	{
		m_pDelegate->MessageBoxFromKey(_T("217"), _T("名称不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_NAME)->SetFocus();

		return;
	}

	m_CurChe=_ttoi(szCurChe);

	m_SelectedChe=m_Combo_SelectedChe.GetCurSel();

	CDialogEx::OnOK();
}