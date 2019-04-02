#include "stdafx.h"
#include "XAttributeDlg.h"
#include "afxdialogex.h"
#include "XDelegateAttributeDlg.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XAttributeDlg, CDialogEx)

	XAttributeDlg::XAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XAttributeDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

}

XAttributeDlg::~XAttributeDlg()
{

}

void XAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(XAttributeDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XAttributeDlg::SetDelegate(XDelegateAttributeDlg* p)
{
	m_pDelegate = p;
}

void XAttributeDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XAttributeDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void XAttributeDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

BOOL XAttributeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XAttributeDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("456"),_T("属性"))+_T("-")+m_InputSignalName);

	GetDlgItem(IDC_STATIC_REFRESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("416"), _T("刷新频率")) + _T(":"));
	GetDlgItem(IDC_STATIC_AUDIO)->SetWindowText(m_pDelegate->GetTranslationString(_T("457"), _T("音频选择")) + _T(":"));

	GetDlgItem(IDC_STATIC_RESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("402"), _T("水平分辨率")) + _T(":"));
	GetDlgItem(IDC_STATIC_RESV)->SetWindowText(m_pDelegate->GetTranslationString(_T("403"), _T("垂直分辨率")) + _T(":"));

	GetDlgItem(IDC_STATIC_DEVICE)->SetWindowText(m_pDelegate->GetTranslationString(_T("459"), _T("设备类型")) + _T(":"));
	GetDlgItem(IDC_STATIC_SIGNAL)->SetWindowText(m_pDelegate->GetTranslationString(_T("463"), _T("信号")) + _T(":"));
}

void XAttributeDlg::InitData()
{
	int nIndex=m_InputSignal->GetInputIndex();

	VEC_INPUTSIGNAL& VecInput=m_InputSignalPane->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal* pInput=*iter;

		if(pInput->GetInputIndex()==nIndex)
		{
			if(!m_InputSignalPane->IsHavePan(nIndex))
			{
				GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("541"),_T("无设备")));
				GetDlgItem(IDC_STATIC_SIG)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));

				CString szTemp = _T("");
				szTemp.Format(_T("%d"), pInput->GetReResulationH());
				GetDlgItem(IDC_STATIC_H)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReResulationV());
				GetDlgItem(IDC_STATIC_V)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReRefresh());
				GetDlgItem(IDC_STATIC_FRESH)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReVideoSelect());
				GetDlgItem(IDC_STATIC_VIDEO)->SetWindowText(szTemp);
			}
			else if(m_InputSignalPane->IsHavePan(nIndex)
				&&!m_InputSignalPane->IsHaveSignal(nIndex))
			{
				if(pInput->GetReStatus()==0x00)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("542"),_T("2K HDMI/DVI")));
				}
				else if(pInput->GetReStatus()==0x20)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("544"),_T("VGA")));
				}
				else if(pInput->GetReStatus()==0x30)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("545"),_T("SDI")));
				}
				else if(pInput->GetReStatus()==0x40)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("546"),_T("AV")));
				}
				else if(pInput->GetReStatus()==0x50)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("627"),_T("IP卡")));
				}

				GetDlgItem(IDC_STATIC_SIG)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));

				int i=0;
				CString szTemp = _T("");
				szTemp.Format(_T("%d"), i);
				GetDlgItem(IDC_STATIC_H)->SetWindowText(szTemp);
				GetDlgItem(IDC_STATIC_V)->SetWindowText(szTemp);
				GetDlgItem(IDC_STATIC_FRESH)->SetWindowText(szTemp);			
				GetDlgItem(IDC_STATIC_VIDEO)->SetWindowText(szTemp);
			}
			else if(m_InputSignalPane->IsHavePan(nIndex)
				&&m_InputSignalPane->IsHaveSignal(nIndex))
			{
				if(pInput->GetReStatus()==0x01)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("542"),_T("2K HDMI/DVI")));
				}
				else if(pInput->GetReStatus()==0x21)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("544"),_T("VGA")));
				}
				else if(pInput->GetReStatus()==0x31)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("545"),_T("SDI")));
				}
				else if(pInput->GetReStatus()==0x41)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("546"),_T("AV")));
				}
				else if(pInput->GetReStatus()==0x51)
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("627"),_T("IP预览卡")));
				}

				GetDlgItem(IDC_STATIC_SIG)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));

				CString szTemp = _T("");
				szTemp.Format(_T("%d"), pInput->GetReResulationH());
				GetDlgItem(IDC_STATIC_H)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReResulationV());
				GetDlgItem(IDC_STATIC_V)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReRefresh());
				GetDlgItem(IDC_STATIC_FRESH)->SetWindowText(szTemp);

				szTemp.Format(_T("%d"), pInput->GetReVideoSelect());
				GetDlgItem(IDC_STATIC_VIDEO)->SetWindowText(szTemp);
			}
		}
	}
}