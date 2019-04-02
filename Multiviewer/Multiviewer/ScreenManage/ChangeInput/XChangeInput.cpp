#include "stdafx.h"
#include "XChangeInput.h"
#include "..\resource.h"
#include "XSignal.h"
#include "XScreenManage.h"
#include "XInputSignal.h"

IMPLEMENT_DYNAMIC(XChangeInput, CDialogEx)

	XChangeInput::XChangeInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(XChangeInput::IDD, pParent)
{
	m_IsUltra=FALSE;
}

XChangeInput::~XChangeInput()
{
}

void XChangeInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INPUT, m_Combo_Input);
}

BEGIN_MESSAGE_MAP(XChangeInput, CDialogEx)
	ON_BN_CLICKED( IDOK, &XChangeInput::OnBtnOK)
END_MESSAGE_MAP()

void XChangeInput::SetDelegate(XDelegateChangeInput* p)
{
	m_pDelegate=p;
}

void XChangeInput::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

BOOL XChangeInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitCombo();

	InitData();

	return FALSE; 
}

void XChangeInput::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("437"), _T("切换输入源")));

	GetDlgItem(IDC_STATIC_INPUT)->SetWindowText(m_pDelegate->GetTranslationString(_T("514"),_T("输入源"))+_T(":"));
	GetDlgItem(IDC_STATIC_CURINPUT)->SetWindowText(m_pDelegate->GetTranslationString(_T("438"),_T("输入源"))+_T(":"));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("208"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("209"),_T("取消")));
}

void XChangeInput::InitData()
{
	CString szStr;

	szStr.Format(_T("%d"),m_InputIndex);

	GetDlgItem(IDC_EDIT_CURINPUT)->SetWindowText(szStr);
}

void XChangeInput::InitCombo()
{
	VEC_INPUTSIGNAL& VecInput=m_pScreenManage->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nIndex=pInput->GetInputIndex();

		if(m_InputIndex==nIndex)
		{
			continue;
		}

		if(pInput->GetReStatus()==0x11
			||pInput->GetReStatus()==0x1A
			||pInput->GetReStatus()==0x13
			||pInput->GetReStatus()==0x1B
			||pInput->GetReStatus()==0x01
			||pInput->GetReStatus()==0x21
			||pInput->GetReStatus()==0x31
			||pInput->GetReStatus()==0x41
			||pInput->GetReStatus()==0x51)
		{
			int n=pInput->GetInputIndex();

			CString str=_T("");
			str.Format(_T("%d"),n);
			m_Combo_Input.AddString(str);
		}
	}

	m_Combo_Input.SetCurSel(0);
}

int XChangeInput::GetComboIndex()
{
	return m_ComboIndex;
}

void XChangeInput::SetInputIndex(int n)
{
	m_InputIndex=n;
}

void XChangeInput::SetIsUltra(BOOL IsUltra)
{
	m_IsUltra=IsUltra;
}

void XChangeInput::OnBtnOK()
{
	int nTemp=m_Combo_Input.GetCurSel();

	if(nTemp==-1)
	{
		m_pDelegate->MessageBoxFromKey(_T("554"),_T("当前没有可切换信号！"),MB_OK);

		CDialogEx::OnOK();

		return;
	}

	CString szStr;

	m_Combo_Input.GetLBText(nTemp,szStr);

	szStr.Trim();

	if(szStr==_T(""))
	{
		m_pDelegate->GetTranslationString(_T("554"),_T("当前没有可切换信号！"));
		return;
	}

	m_ComboIndex=_ttoi(szStr);

	CDialogEx::OnOK();
}