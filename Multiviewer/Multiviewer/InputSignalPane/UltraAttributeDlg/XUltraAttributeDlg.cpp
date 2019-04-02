#include "stdafx.h"
#include "XUltraAttributeDlg.h"
#include "afxdialogex.h"
#include "XDelegateUltraAttributeDlg.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XUltraAttributeDlg, CDialogEx)

	XUltraAttributeDlg::XUltraAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XUltraAttributeDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;
}

XUltraAttributeDlg::~XUltraAttributeDlg()
{
}

void XUltraAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XUltraAttributeDlg, CDialogEx)

END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XUltraAttributeDlg::SetDelegate(XDelegateUltraAttributeDlg* p)
{
	m_pDelegate = p;
}

void XUltraAttributeDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XUltraAttributeDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void XUltraAttributeDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

BOOL XUltraAttributeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	return FALSE;  
}

void XUltraAttributeDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("456"),_T("属性"))+_T("-")+m_InputSignalName);

	GetDlgItem(IDC_STATIC_REFRESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("416"), _T("刷新频率")) + _T(":"));
	GetDlgItem(IDC_STATIC_AUDIO)->SetWindowText(m_pDelegate->GetTranslationString(_T("457"), _T("音频选择")) + _T(":"));

	GetDlgItem(IDC_STATIC_RESH)->SetWindowText(m_pDelegate->GetTranslationString(_T("402"), _T("水平分辨率")) + _T(":"));
	GetDlgItem(IDC_STATIC_RESV)->SetWindowText(m_pDelegate->GetTranslationString(_T("403"), _T("垂直分辨率")) + _T(":"));

	GetDlgItem(IDC_STATIC_DEVICE)->SetWindowText(m_pDelegate->GetTranslationString(_T("459"), _T("设备类型")) + _T(":"));

	GetDlgItem(IDC_STATIC_CHENAL1)->SetWindowText(m_pDelegate->GetTranslationString(_T("463"), _T("是否有信号")) + _T(":"));
	GetDlgItem(IDC_STATIC_SELECTEDCHENAL)->SetWindowText(m_pDelegate->GetTranslationString(_T("549"), _T("所选通道")) + _T(":"));
}

void XUltraAttributeDlg::InitData()
{
	int nIndex=m_InputSignal->GetInputIndex();

	VEC_INPUTSIGNAL& VecInput=m_InputSignalPane->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal* pInput=*iter;

		if(pInput->GetInputIndex()==nIndex)
		{
			if(m_InputSignalPane->IsHavePan(nIndex)
				&&!m_InputSignalPane->IsHaveSignal(nIndex))
			{
				if(pInput->GetReStatus()==0x10) 
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));

					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("462"),_T("否")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("551"),_T("无")));
				}
				else if(pInput->GetReStatus()==0x18)   
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("462"),_T("无")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("548"),_T("通道2")));
				}

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
				if(pInput->GetReStatus()==0x11)     //有信号通道1
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("547"),_T("通道1")));
				}
				else if(pInput->GetReStatus()==0x1A)   //有信号通道2
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					//GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("548"),_T("通道2")));
				}
				else if(pInput->GetReStatus()==0x13)   //有信号双通道-选中1
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("547"),_T("通道1")));

				}
				else if(pInput->GetReStatus()==0x1B)   //有信号双通道-选中2
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("548"),_T("通道2")));
				}
				else if(pInput->GetReStatus()==0x19)   //有信号通道1-选中2
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("550"),_T("无信号")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("548"),_T("通道2")));
				}
				else if(pInput->GetReStatus()==0x12)   //有信号通道2-选中1
				{
					GetDlgItem(IDC_STATIC_DEV)->SetWindowText(m_pDelegate->GetTranslationString(_T("543"),_T("4K HDMI/DVI")));
					//GetDlgItem(IDC_STATIC_CHE2)->SetWindowText(m_pDelegate->GetTranslationString(_T("552"),_T("有信号")));
					GetDlgItem(IDC_STATIC_CHE1)->SetWindowText(m_pDelegate->GetTranslationString(_T("461"),_T("是")));
					GetDlgItem(IDC_STATIC_SELECTEDCHE)->SetWindowText(m_pDelegate->GetTranslationString(_T("547"),_T("通道1")));
				}



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