#include "stdafx.h"
#include "XPaneIPAddr.h"
#include "afxdialogex.h"
#include "XDelegatePaneIPAddr.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"
#include "XPaneIPAddrInfo.h"
#include "XSendDataInputSignal.h"

// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XPaneIPAddr, CDialogEx)

	XPaneIPAddr::XPaneIPAddr(CWnd* pParent /*=NULL*/)
	: CDialogEx(XPaneIPAddr::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

	m_szIP=_T("");

	m_szMask=_T("");

	m_szGateWay=_T("");

	m_szMAC=_T("");

	m_Index = 0;

	m_Text = _T("");

	m_dBeginTime=0;

	m_nReadIndex=1;

	m_szReadIndex=_T("");

	m_nModel=-1;

}

XPaneIPAddr::~XPaneIPAddr()
{

}

void XPaneIPAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_IPADDRESS_IP, m_IP);
	DDX_Control(pDX, IDC_IPADDRESS_MASK, m_Mask);
	DDX_Control(pDX, IDC_IPADDRESS_GATEWAY, m_GateWay);

	DDX_Control(pDX, IDC_COMBO_MODEL, m_Combo_Model);
}


BEGIN_MESSAGE_MAP(XPaneIPAddr, CDialogEx)
	ON_BN_CLICKED(IDOK, &XPaneIPAddr::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_READ2,&XPaneIPAddr::OnBtnRead)

	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_IP, &XPaneIPAddr::OnIpnFieldchangedIp)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XPaneIPAddr::SetDelegate(XDelegatePaneIPAddr* p)
{
	m_pDelegate = p;
}

void XPaneIPAddr::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XPaneIPAddr::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void XPaneIPAddr::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XPaneIPAddr::SetIP(CString szIP)
{
	m_szIP=szIP;
}

void XPaneIPAddr::SetMask(CString szMask)
{
	m_szMask=szMask;
}

void XPaneIPAddr::SetGateWay(CString szGateWay)
{
	m_szGateWay=szGateWay;
}

void XPaneIPAddr::SetMAC(CString szMAC)
{
	m_szMAC=szMAC;
}

void XPaneIPAddr::SetModel(int n)
{
	m_nModel=n;
}

int XPaneIPAddr::GetModel()
{
	return m_nModel;
}

BOOL XPaneIPAddr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	InitCombo();

	m_Text = m_pDelegate->GetTranslationString(_T("636"), _T("未读取"));

	//SetTimer(1, 500, NULL);

	UpdateText();

	//m_Combo_Model.EnableWindow(FALSE);

	return FALSE;  
}

void XPaneIPAddr::ReloadInterface()
{

	int nTempIndex=m_InputSignal->GetInputIndex();

	int nIndex=(nTempIndex-1)/4+1;

	CString szPane=_T("");

	szPane.Format(_T("%d"),nIndex);

	CString szPaneName=m_pDelegate->GetTranslationString(_T("505"),_T("板卡"))+szPane;


	SetWindowText(m_pDelegate->GetTranslationString(_T("626"),_T("板卡网络配置"))+_T("-")+szPaneName);

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDC_BTN_READ2)->SetWindowText(m_pDelegate->GetTranslationString(_T("630"), _T("读取")));

	GetDlgItem(IDC_STATIC_IP)->SetWindowText(m_pDelegate->GetTranslationString(_T("616"), _T("IP地址")) + _T(":"));
	GetDlgItem(IDC_STATIC_MASK)->SetWindowText(m_pDelegate->GetTranslationString(_T("617"), _T("子网掩码")) + _T(":"));

	GetDlgItem(IDC_STATIC_MAC)->SetWindowText(m_pDelegate->GetTranslationString(_T("619"), _T("MAC地址")) + _T(":"));
	GetDlgItem(IDC_STATIC_GATEWAY)->SetWindowText(m_pDelegate->GetTranslationString(_T("618"), _T("默认网关")) + _T(":"));

	GetDlgItem(IDC_STATIC_TIP30)->SetWindowText(m_pDelegate->GetTranslationString(_T("634"),_T("例如"))+_T(":"));

	GetDlgItem(IDC_STATIC_READSTATUS)->SetWindowText(m_pDelegate->GetTranslationString(_T("637"),_T("读取状态"))+ _T(":"));
}

void XPaneIPAddr::InitData()
{
	XPaneIPAddrInfo* pInfo=m_InputSignal->GetPaneIPAddrInfo();

	m_Combo_Model.SetCurSel(pInfo->GetSelect());

	GetDlgItem(IDC_IPADDRESS_IP)->SetWindowText(pInfo->GetPaneIP());

	GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(pInfo->GetPaneMask());

	GetDlgItem(IDC_IPADDRESS_GATEWAY)->SetWindowText(pInfo->GetPaneGateWay());

	GetDlgItem(IDC_EDIT_MAC)->SetWindowText(pInfo->GetPaneMAC());
}

void XPaneIPAddr::InitCombo()
{
	m_Combo_Model.AddString(m_pDelegate->GetTranslationString(_T("640"),_T("2K")));

	m_Combo_Model.AddString(m_pDelegate->GetTranslationString(_T("641"),_T("4K")));

	m_Combo_Model.AddString(m_pDelegate->GetTranslationString(_T("642"),_T("关闭")));

	m_Combo_Model.SetCurSel(0);
}

void XPaneIPAddr::ResetNet()
{
	m_IP.ClearAddress();
	m_Mask.ClearAddress();
	m_GateWay.ClearAddress();

	BOOL bIP=FALSE;
	BOOL bMask=FALSE;
	BOOL bGatewat=FALSE;
	BOOL bMAC=FALSE;
	BOOL bModel=FALSE;

	if(m_szIP!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_IP)->SetWindowText(m_szIP);
		bIP=TRUE;
	}

	if(m_szMask!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(m_szMask);
		bMask=TRUE;
	}

	if(m_szGateWay!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_GATEWAY)->SetWindowText(m_szGateWay);
		bGatewat=TRUE;
	}

	if(m_szMAC!=_T(""))
	{
		GetDlgItem(IDC_EDIT_MAC)->SetWindowText(m_szMAC);
		bMAC=TRUE;
	}

	//************************************
	if(m_nModel!=-1)
	{
		m_Combo_Model.SetCurSel(m_nModel);
		bModel=TRUE;
	}

	//************************************
	if(bIP&&bMask&&bGatewat&&bMAC&&bModel)
	{
		GetDlgItem(IDC_BTN_READ2)->EnableWindow(TRUE);

		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_STATIC_ING)->SetWindowText(m_pDelegate->GetTranslationString(_T("631"),_T("读取成功！")));
	}
}

void XPaneIPAddr::OnBnClickedOk()
{
	CString szPaneIP=_T("");

	GetDlgItem(IDC_IPADDRESS_IP)->GetWindowText(szPaneIP);

	szPaneIP.Trim();

	if(szPaneIP==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("622"),_T("IP地址不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_IP)->SetFocus();

		return;
	}

	BYTE field1,field2,field3,field4;  
	m_IP.GetAddress(field1,field2,field3,field4);

	if(field1==0
		||field2==0
		||field3==0
		||field4==0)
	{
		m_pDelegate->MessageBoxFromKey(_T("633"),_T("IP地址错误！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_IP)->SetFocus();

		return;
	}

	///////////////////////////////////////////////////////////
	CString szPaneMask=_T("");

	GetDlgItem(IDC_IPADDRESS_MASK)->GetWindowText(szPaneMask);

	szPaneMask.Trim();

	if(szPaneMask==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("623"),_T("子网掩码不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_MASK)->SetFocus();

		return;
	}
	///////////////////////////////////////////////////////////

	CString szPaneGateWay=_T("");

	GetDlgItem(IDC_IPADDRESS_GATEWAY)->GetWindowText(szPaneGateWay);

	szPaneGateWay.Trim();

	if(szPaneGateWay==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("624"),_T("默认网关不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_GATEWAY)->SetFocus();

		return;
	}

	///////////////////////////////////////////////////////////

	CString szPaneMAC=_T("");

	GetDlgItem(IDC_EDIT_MAC)->GetWindowText(szPaneMAC);

	szPaneMAC.Trim();

	if(szPaneMAC==_T(""))
	{
		m_pDelegate->MessageBoxFromKey(_T("625"),_T("MAC地址不能为空！"),MB_OK);

		GetDlgItem(IDC_EDIT_MAC)->SetFocus();

		return;
	}

	VEC_CSTRING VecString;
	SpiltCString(szPaneMAC,_T("-"),VecString);

	if(VecString.size()!=6)
	{
		m_pDelegate->MessageBoxFromKey(_T("628"),_T("MAC地址格式错误！"),MB_OK);

		GetDlgItem(IDC_EDIT_MAC)->SetFocus();

		return;
	}

	USES_CONVERSION;
	char* pPanMAC=W2A(szPaneMAC);

	int nLen=strlen(pPanMAC);

	int* pMAC=new int[6];

	int n=sscanf_s(pPanMAC,"%x-%x-%x-%x-%x-%x",pMAC,pMAC+1,pMAC+2,pMAC+3,pMAC+4,pMAC+5);
	if(n!=6)
	{
		m_pDelegate->MessageBoxFromKey(_T("628"),_T("MAC地址格式错误！"),MB_OK);

		GetDlgItem(IDC_EDIT_MAC)->SetFocus();

		return;
	}

	///////////////////////////////////////////////////////

	int nSelect=m_Combo_Model.GetCurSel();

	int nModel=0;

	if(nSelect==0)
	{
		nModel=1;
	}
	else if(nSelect==1)
	{
		nModel=2;
	}
	else if(nSelect==2)
	{
		nModel=0;
	}

	///////////////////////////////////////////////////////

	XPaneIPAddrInfo* pInfo=m_InputSignal->GetPaneIPAddrInfo();

	pInfo->SetPaneIP(szPaneIP);

	pInfo->SetPaneMask(szPaneMask);

	pInfo->SetPaneGateWay(szPaneGateWay);

	pInfo->SetPaneMAC(szPaneMAC);

	pInfo->SetArrMAC(pMAC);

	pInfo->SetModel(nModel);

	pInfo->SetSelect(nSelect);

	delete []pMAC;

	CDialogEx::OnOK();
}

void XPaneIPAddr::OnBtnRead()
{
	m_dBeginTime=GetTickCount();

	GetDlgItem(IDC_BTN_READ2)->EnableWindow(FALSE);

	m_Text=m_pDelegate->GetTranslationString(_T("635"),_T("读取中"));

	SetTimer(1,500,NULL);

	SetTimer(2,2400,NULL);

	XSendDataInputSignal::AddSendDataOfGetPaneNet(m_InputSignalPane,m_InputSignal);
}

void XPaneIPAddr::SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr)
{
	CString szTemp;

	int nPos=0;

	szTemp=szSrc.Tokenize(ch,nPos);

	while(!szTemp.IsEmpty())
	{
		VecStr.push_back(szTemp);

		szTemp=szSrc.Tokenize(ch,nPos);
	}
}

void XPaneIPAddr::OnIpnFieldchangedIp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	if(pIPAddr->iField==0)
	{
		BYTE field1,field2,field3,field4;  
		m_IP.GetAddress(field1,field2,field3,field4);

		if (field1>=0&&field1<=127)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(_T("255.0.0.0"));
		}  
		else if(field1>=128&&field1<=191)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(_T("255.255.0.0"));
		}  
		else if (field1>=192&&field1<=223)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASK)->SetWindowText(_T("255.255.255.0"));
		}  
	}

	*pResult = 0;
}

void XPaneIPAddr::OnTimer(UINT_PTR nIDEvent)
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

void XPaneIPAddr::ReRead()
{
	DWORD dNowTime=GetTickCount();
	//********************************************************************

	if(m_nReadIndex==3)
	{
		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_BTN_READ2)->EnableWindow(TRUE);

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

		//XSendDataInputSignal::AddSendDataOfGetPaneNet(m_InputSignalPane,m_InputSignal);

		m_nReadIndex++;
	}
}

void XPaneIPAddr::UpdateText()
{
	CString szText=m_Text;

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

