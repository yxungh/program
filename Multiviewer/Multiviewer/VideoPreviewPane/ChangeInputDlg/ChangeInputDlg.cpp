// ChangeRTSPAddrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChangeInputDlg.h"
#include "afxdialogex.h"
#include "ChangeRTSPAddrDlg.h"
#include "HandleCalculate.h"
#include "XVideoPreviewFrame.h"
#include "XVideoPreviewPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "XConstantIM.h"
#include "XInputSignal.h"

// CChangeInputDlg 对话框

IMPLEMENT_DYNAMIC(CChangeInputDlg, CDialogEx)

CChangeInputDlg::CChangeInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeInputDlg::IDD, pParent)
{
	m_nInputIndex = 0;
}

CChangeInputDlg::~CChangeInputDlg()
{

}

void CChangeInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_Combo_Input);
}


BEGIN_MESSAGE_MAP(CChangeInputDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangeInputDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChangeInputDlg 消息处理程序

BOOL CChangeInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitComboInput();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void CChangeInputDlg::ReloadInterface()
{
	SetWindowText(m_Frame->GetPane()->GetDelegate()->GetTranslationString(_T("538"), _T("修改输入")));

	GetDlgItem(IDOK)->SetWindowText(m_Frame->GetPane()->GetDelegate()->GetTranslationString(_T("214"), _T("确定")));

	GetDlgItem(IDCANCEL)->SetWindowText(m_Frame->GetPane()->GetDelegate()->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_OUTPUT)->SetWindowText(m_Frame->GetPane()->GetDelegate()->GetTranslationString(_T("437"), _T("切换输入源")) + _T(":"));

	GetDlgItem(IDC_STATIC_OUTPUT2)->SetWindowText(m_Frame->GetPane()->GetDelegate()->GetTranslationString(_T("438"), _T("当前输入源")) + _T(":"));
}

void CChangeInputDlg::SetInputIndex(int n)
{
	m_nInputIndex = n;
}

int CChangeInputDlg::GetInputIndex()
{
	return m_nInputIndex;
}

int CChangeInputDlg::GetSelectIndex()
{
	return m_nSelectIndex;
}

void CChangeInputDlg::SetFrame(XVideoPreviewFrame* p)
{
	m_Frame = p;
}

void CChangeInputDlg::InitData()
{
	CString szCurInput;

	if(m_nInputIndex!=0)
	{
		szCurInput.Format(_T("%d"),m_nInputIndex);

		GetDlgItem(IDC_EDIT_CURINPUT)->SetWindowText(szCurInput);
	}
}

void CChangeInputDlg::InitComboInput()
{
	BOOL bIsUltra=GetIsUltra(m_nInputIndex);

	CString szTemp = _T("");
	int nInputCount = m_Frame->GetPane()->GetDelegate()->GetInputCount();
	for (int i = 1; i <= nInputCount; i++)
	{
		if(i==m_nInputIndex)
		{
			continue;
		}

		if(bIsUltra)
		{
			BOOL bNewIsUltra=GetIsUltra(i);
			if(bNewIsUltra)
			{
				int nTemp=(i-1)%4;
				if(nTemp==0)
				{
					szTemp.Format(_T("%d"), i);
					m_Combo_Input.AddString(szTemp);
				}
			}
		}
		else
		{
			BOOL bNewIsUltra=GetIsUltra(i);
			if(!bNewIsUltra)
			{
				szTemp.Format(_T("%d"), i);
				m_Combo_Input.AddString(szTemp);
			}
		}
	}

	m_Combo_Input.SetCurSel(0);
}

BOOL CChangeInputDlg::GetIsUltra(int nIndex)
{
	m_Frame->GetPane()->GetDelegate()->IsUltra(nIndex);
	XInputSignal* pInput=m_Frame->GetPane()->GetDelegate()->GetInputByIndex(nIndex);
	if(pInput==NULL)
	{
		return FALSE;
	}
	return pInput->GetIsUltra();
}

void CChangeInputDlg::OnBnClickedOk()
{
	CString szSelect=_T("");
		
	m_Combo_Input.GetLBText(m_Combo_Input.GetCurSel(),szSelect);

	m_nSelectIndex=_ttoi(szSelect);

	CDialogEx::OnOK();
}
