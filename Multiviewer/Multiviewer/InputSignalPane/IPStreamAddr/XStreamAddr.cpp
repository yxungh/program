#include "stdafx.h"
#include "XStreamAddr.h"
#include "afxdialogex.h"
#include "XDelegateStreamAddr.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"
#include "XStreamAddrInfo.h"
#include "XSendDataInputSignal.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XStreamAddr, CDialogEx)

	XStreamAddr::XStreamAddr(CWnd* pParent /*=NULL*/)
	: CDialogEx(XStreamAddr::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

	m_Index = 0;

	m_Text = _T("");

	m_dBeginTime=0;

	m_nReadIndex=1;

	m_szReadIndex=_T("");
}

XStreamAddr::~XStreamAddr()
{

}

void XStreamAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(XStreamAddr, CDialogEx)
	ON_BN_CLICKED(IDOK, &XStreamAddr::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_READ,&XStreamAddr::OnBtnRead)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XStreamAddr::SetDelegate(XDelegateStreamAddr* p)
{
	m_pDelegate = p;
}

void XStreamAddr::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XStreamAddr::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void XStreamAddr::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XStreamAddr::SetStreamAddr(CString szStream)
{
	m_szStreamAddr=szStream;
}

BOOL XStreamAddr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	m_Text = m_pDelegate->GetTranslationString(_T("636"), _T("未读取"));

	//SetTimer(1, 500, NULL);

	//m_Text=m_pDelegate->GetTranslationString(_T("635"),_T("读取中"));

	//SetTimer(1, 500, NULL);

	UpdateText();

	return FALSE;  
}

void XStreamAddr::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("615"),_T("设置视频流地址"))+_T("-")+m_InputSignalName);

	GetDlgItem(IDC_STATIC_STREAM)->SetWindowText(m_pDelegate->GetTranslationString(_T("614"), _T("视频流地址")) + _T(":"));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDC_BTN_READ)->SetWindowText(m_pDelegate->GetTranslationString(_T("630"), _T("读取")));

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(m_pDelegate->GetTranslationString(_T("637"),_T("读取状态"))+ _T(":"));
}

void XStreamAddr::InitData()
{
	XStreamAddrInfo* pInfo=m_InputSignal->GetStreamInfo();

	GetDlgItem(IDC_EDIT_STREAM)->SetWindowText(pInfo->GetText());
}

void XStreamAddr::ResetStream()
{
	BOOL bIsRead=FALSE;

	//if(m_szStreamAddr!=_T(""))
	//{
		GetDlgItem(IDC_EDIT_STREAM)->SetWindowText(m_szStreamAddr);

		bIsRead=TRUE;
	//}

	if(bIsRead)
	{
		GetDlgItem(IDC_BTN_READ)->EnableWindow(TRUE);

		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_STATIC_ING)->SetWindowText(m_pDelegate->GetTranslationString(_T("631"),_T("读取成功！")));
	}
}

void XStreamAddr::OnBnClickedOk()
{
	CString szText;
	GetDlgItem(IDC_EDIT_STREAM)->GetWindowText(szText);

	szText.Trim();

	if(szText==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("621"),_T("视频流地址不能为空！"),MB_OK);

		GetDlgItem(IDC_EDIT_STREAM)->SetFocus();

		return;
	}

	int nLen=szText.GetLength();

	if(nLen>125)
	{
		m_pDelegate->MessageBoxFromKey(_T("629"),_T("视频流地址长度越界！"),MB_OK);

		GetDlgItem(IDC_EDIT_STREAM)->SetFocus();

		return;
	}


	XStreamAddrInfo* pInfo=m_InputSignal->GetStreamInfo();

	pInfo->SetText(szText);

	pInfo->SetDataLen(nLen);

	CDialogEx::OnOK();
}

void XStreamAddr::OnBtnRead()
{
	m_dBeginTime=GetTickCount();

	GetDlgItem(IDC_BTN_READ)->EnableWindow(FALSE);

	m_Text=m_pDelegate->GetTranslationString(_T("635"),_T("读取中"));

	SetTimer(1,500,NULL);

	SetTimer(2,2400,NULL);

	XSendDataInputSignal::AddSendDataOfGetStreamAddr(m_InputSignalPane,m_InputSignal);
}

void XStreamAddr::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
		{
			UpdateText();
		}
		break;
	case 2:
		{
			ReRead();
		}
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void XStreamAddr::ReRead()
{
	DWORD dNowTime=GetTickCount();
	//********************************************************************

	if(m_nReadIndex==3)
	{

		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_BTN_READ)->EnableWindow(TRUE);

		m_Text=m_pDelegate->GetTranslationString(_T("639"),_T("读取失败！"));

		UpdateText();

		m_nReadIndex=1;

	}


	if(abs((long)dNowTime-(long)m_dBeginTime)>2500)
	{
		KillTimer(1);

		m_dBeginTime=GetTickCount();

		m_szReadIndex.Format(_T("%d"),m_nReadIndex);

		m_Text=m_pDelegate->GetTranslationString(_T("638"),_T("重新读取"))+m_szReadIndex;

		UpdateText();

		//*****************************************************************

		m_Text=m_pDelegate->GetTranslationString(_T("635"),_T("读取中"));

		SetTimer(1,500,NULL);

		XSendDataInputSignal::AddSendDataOfGetStreamAddr(m_InputSignalPane,m_InputSignal);

		m_nReadIndex++;
	}
}

void XStreamAddr::UpdateText()
{

	CString szText = m_Text;

	if(szText==m_pDelegate->GetTranslationString(_T("635"),_T("读取中")))
	{
		m_Index++;

		for (int i = 0; i < 4; i++)
		{
			if (i < m_Index)
			{
				szText += _T("．");
			}
			else
			{
				szText += _T("　");
			}
		}

		if (m_Index >= 6)
		{
			m_Index = 0;
		}
	}

	GetDlgItem(IDC_STATIC_ING)->SetWindowText(szText);

	CRect rectText;
	GetDlgItem(IDC_STATIC_ING)->GetWindowRect(&rectText);

	ScreenToClient(&rectText);

	InvalidateRect(&rectText);
}