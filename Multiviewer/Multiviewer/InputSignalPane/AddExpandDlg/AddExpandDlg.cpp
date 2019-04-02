// AddExpandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AddExpandDlg.h"
#include "afxdialogex.h"
#include "XDelegateAddExpandDlg.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(CAddExpandDlg, CDialogEx)

CAddExpandDlg::CAddExpandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddExpandDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal = NULL;
}

CAddExpandDlg::~CAddExpandDlg()
{
}

void CAddExpandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddExpandDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddExpandDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void CAddExpandDlg::SetDelegate(XDelegateAddExpandDlg* p)
{
	m_pDelegate = p;
}

void CAddExpandDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void CAddExpandDlg::SetInputSignalPan(XInputSignalPane* p)
{
	m_InputSIgnalPan=p;
}

void CAddExpandDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

CString CAddExpandDlg::GetName()
{
	return m_szName;
}

XExpandInfo* CAddExpandDlg::GetExpandInfo()
{
	return &m_ExpandInfo;
}

BOOL CAddExpandDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetLimitText(5);

	InitData();

	return FALSE;  
}

void CAddExpandDlg::InitData()
{
	VEC_INPUTSIGNAL& VecInputSignal=m_InputSIgnalPan->GetVecInputSignal();

	int nIndex=m_InputSignal->GetInputIndex();

	for(VEC_INPUTSIGNAL::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
	{
		XInputSignal* pInputSignal=*iter;

		if(nIndex==pInputSignal->GetInputIndex())
		{
			CString szTemp=_T("");

			szTemp.Format(_T("%d"), pInputSignal->GetReResulationH());
			GetDlgItem(IDC_EDIT_H)->SetWindowText(szTemp);

			szTemp.Format(_T("%d"), pInputSignal->GetReResulationV());
			GetDlgItem(IDC_EDIT_V)->SetWindowText(szTemp);
		}
	}
}

void CAddExpandDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("205"), _T("添加局部放大")) + _T(" - ") + m_InputSignalName);

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("214"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_pDelegate->GetTranslationString(_T("216"), _T("名称")) + _T(":"));
	GetDlgItem(IDC_STATIC_LEFT)->SetWindowText(m_pDelegate->GetTranslationString(_T("210"), _T("左上角X")) + _T(":"));
	GetDlgItem(IDC_STATIC_TOP)->SetWindowText(m_pDelegate->GetTranslationString(_T("211"), _T("左上角Y")) + _T(":"));
	GetDlgItem(IDC_STATIC_RIGHT)->SetWindowText(m_pDelegate->GetTranslationString(_T("212"), _T("右下角X")) + _T(":"));
	GetDlgItem(IDC_STATIC_BOTTOM)->SetWindowText(m_pDelegate->GetTranslationString(_T("213"), _T("右下角Y")) + _T(":"));
	
	GetDlgItem(IDC_STATIC_NOTICE)->SetWindowText(m_pDelegate->GetTranslationString(_T("321"), _T("(提示:全屏类型数值全为0;其它类型数值从1开始)")));

	GetDlgItem(IDC_STATIC_RESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("402"), _T("水平分辨率")) + _T(":"));
	GetDlgItem(IDC_STATIC_RESV)->SetWindowText(m_pDelegate->GetTranslationString(_T("403"), _T("垂直分辨率")) + _T(":"));
}

void CAddExpandDlg::OnBnClickedOk()
{
	int nHdpi=m_InputSignal->GetReResulationH();
	CString szHdpi;
	szHdpi.Format(_T("%d"),nHdpi);

	int nVdpi=m_InputSignal->GetReResulationV();
	CString szVdpi;
	szVdpi.Format(_T("%d"),nVdpi);

	//////////////////////////////////////////////////////////////////////////
	CString szName = _T("");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szName);
	szName.Trim();
	if (_T("") == szName)
	{
		m_pDelegate->MessageBoxFromKey(_T("217"), _T("名称不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_NAME)->SetFocus();

		return;
	}

	if (m_InputSignal->DecideExpandNameExist(NULL, szName))
	{
		m_pDelegate->MessageBoxFromKey(_T("222"), _T("名称已存在,请重新输入!"), MB_OK);

		return;
	}
	////////////////////////////////////////////////////////////
	CString szLeft = _T("");
	GetDlgItem(IDC_EDIT_LEFT)->GetWindowText(szLeft);
	szLeft.Trim();
	if (_T("") == szLeft)
	{
		m_pDelegate->MessageBoxFromKey(_T("218"), _T("左上角X不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_LEFT)->SetFocus();

		return;
	}

	int nLeft = _ttoi(szLeft);
	if(nLeft < 0 || nLeft > nHdpi)
	{
		m_pDelegate->MessageBoxFromKey(_T("432"),_T("左上角X不能超过输入水平分辨率")+szHdpi+_T("!"), MB_OK);

		GetDlgItem(IDC_EDIT_LEFT)->SetFocus();

		return;
	}
	////////////////////////////////////////////////////////////
	CString szTop = _T("");
	GetDlgItem(IDC_EDIT_TOP)->GetWindowText(szTop);
	szTop.Trim();
	if (_T("") == szTop)
	{
		m_pDelegate->MessageBoxFromKey(_T("219"), _T("左上角Y不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_TOP)->SetFocus();

		return;
	}

	int nTop = _ttoi(szTop);
	if(nTop < 0 || nTop > nVdpi)
	{
		m_pDelegate->MessageBoxFromKey(_T("433"),_T("左上角Y不能超过输入垂直分辨率")+szVdpi+_T("!"), MB_OK);

		GetDlgItem(IDC_EDIT_TOP)->SetFocus();

		return;
	}
	////////////////////////////////////////////////////////////
	CString szRight = _T("");
	GetDlgItem(IDC_EDIT_RIGHT)->GetWindowText(szRight);
	szRight.Trim();
	if (_T("") == szRight)
	{
		m_pDelegate->MessageBoxFromKey(_T("220"), _T("右下角X不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_RIGHT)->SetFocus();

		return;
	}

	int nRight = _ttoi(szRight);
	if(nRight < 0 || nRight > nHdpi)
	{
		m_pDelegate->MessageBoxFromKey(_T("434"),_T("左上角X不能超过输入水平分辨率")+szHdpi+_T("!"), MB_OK);

		GetDlgItem(IDC_EDIT_RIGHT)->SetFocus();

		return;
	}
	////////////////////////////////////////////////////////////
	CString szBottom = _T("");
	GetDlgItem(IDC_EDIT_BOTTOM)->GetWindowText(szBottom);
	szBottom.Trim();
	if (_T("") == szBottom)
	{
		m_pDelegate->MessageBoxFromKey(_T("221"), _T("右下角Y不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_BOTTOM)->SetFocus();

		return;
	}

	int nBottom = _ttoi(szBottom);
	if(nBottom < 0 || nBottom > nVdpi)
	{
		m_pDelegate->MessageBoxFromKey(_T("435"),_T("左上角Y不能超过输入垂直分辨率")+szVdpi+_T("!"), MB_OK);

		GetDlgItem(IDC_EDIT_BOTTOM)->SetFocus();

		return;
	}
	////////////////////////////////////////////////////////////
	if ((nLeft != 0) 
		|| (nTop != 0)
		|| (nRight != 0)
		|| (nBottom != 0))
	{
		if ((nLeft <= 0)
			|| (nTop <= 0)
			|| (nRight <= 0)
			|| (nBottom <= 0)
			|| (nLeft >= nRight)
			|| (nTop >= nBottom))
		{
			m_pDelegate->MessageBoxFromKey(_T("225"), _T("请输入正确的数值!全屏类型数值全为0;其它类型数值从1开始。"), MB_OK);

			return;
		}
	}

	m_szName = szName;

	m_ExpandInfo.SetExpand(nLeft, nTop, nRight, nBottom);

	CDialogEx::OnOK();
}