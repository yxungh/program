#include "stdafx.h"
#include "XBoardNet.h"
#include "afxdialogex.h"
#include "XDelegateBoardNet.h"
#include "XSendDataOfPreviewBoard.h"
#include "XScreen.h"
#include "XScreenRetInfo.h"
#include "HandleVerification.h"
#include "XBoardNetInfo.h"
#include "XInternalManage.h"
#include "XSelectBoardInfo.h"


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XBoardNet, CDialogEx)

	XBoardNet::XBoardNet(CWnd* pParent /*=NULL*/)
	: CDialogEx(XBoardNet::IDD, pParent)
{
	m_pManage = NULL;

	m_pDelegate=NULL;

	m_szUseName=_T("");

	m_szPassWd=_T("");

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

	m_nSecret=-1;

	m_nSetTime=0;

	m_nSecretSelect=0;

	m_nBoardIndex=0;

	m_nModelSel=0;

	m_szVersion=_T("");
}

XBoardNet::~XBoardNet()
{

}

void XBoardNet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_IPADDR, m_IP);
	DDX_Control(pDX, IDC_IPADDRESS_MASKADDR, m_Mask);
	DDX_Control(pDX, IDC_IPADDRESS_GATEWAYADDR, m_GateWay);
	DDX_Control(pDX, IDC_COMBO_MODEL, m_Combo_Model);
	DDX_Control(pDX, IDC_COMBO_MI, m_Combo_PassWd);
	DDX_Control(pDX, IDC_EDIT_USENAME, m_Edit_Name);
	DDX_Control(pDX, IDC_EDIT_PASSWD, m_Edit_PassWd);
}

BEGIN_MESSAGE_MAP(XBoardNet, CDialogEx)
	ON_BN_CLICKED(IDOK, &XBoardNet::OnBnClickedOk)
	ON_BN_CLICKED(ID_OK2,&XBoardNet::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_BUTTON_READ, &XBoardNet::OnBnClickedRead)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_IPADDR, &XBoardNet::OnIpnFieldchangedIp)
	ON_WM_TIMER()
	
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XBoardNet::SetDelegate(XDelegateBoardNet* p)
{
	m_pDelegate = p;
}

void XBoardNet::SetInternalManage(XInternalManage* p)
{
	m_pManage=p;
}

void XBoardNet::SetUseName(CString szName)
{
	m_szUseName=szName;
}

CString XBoardNet::GetUseName()
{
	return m_szUseName;
}

void XBoardNet::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

CString XBoardNet::GetPassWd()
{
	return m_szPassWd;
}

void XBoardNet::SetIP(CString szIP)
{
	m_szIP=szIP;
}

CString XBoardNet::GetIP()
{
	return m_szIP;
}

void XBoardNet::SetMask(CString szMask)
{
	m_szMask=szMask;
}

void XBoardNet::SetGateWay(CString szGateWay)
{
	m_szGateWay=szGateWay;
}

void XBoardNet::SetMAC(CString szMAC)
{
	m_szMAC=szMAC;
}

void XBoardNet::SetModel(int n)
{
	m_nModel=n;

	if(m_nModel==1)
	{
		m_nModelSel=0;
	}
	else if(m_nModel==2)
	{
		m_nModelSel=1;
	}
	else if(m_nModel==0)
	{
		m_nModelSel=2;
	}
}

int XBoardNet::GetModel()
{
	return m_nModel;
}

void XBoardNet::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XBoardNet::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XBoardNet::SetSecret(int n)
{
	m_nSecret=n;

	if(n==0)
	{
		m_nSecretSelect=1;
	}
	else if(n==1)
	{
		m_nSecretSelect=0;
	}
}

int XBoardNet::GetSecret()
{
	return m_nSecret;
}

void XBoardNet::SetVersion(CString szVer)
{
	m_szVersion=szVer;
}

void XBoardNet::ResetNet()
{
	m_IP.ClearAddress();
	m_Mask.ClearAddress();
	m_GateWay.ClearAddress();

	BOOL bSecret=FALSE;
	BOOL bModel=FALSE;
	BOOL bUseName=FALSE;
	BOOL bPassWd=FALSE;
	BOOL bIP=FALSE;
	BOOL bMask=FALSE;
	BOOL bGateWay=FALSE;
	BOOL bMAC=FALSE;

	if(m_nSecret!=-1)
	{
		m_Combo_PassWd.SetCurSel(m_nSecretSelect);
		bSecret=TRUE;
	}

	if(m_nModel!=-1)
	{
		m_Combo_Model.SetCurSel(m_nModelSel);
		bModel=TRUE;
	}

	if(m_szUseName!=_T(""))
	{
		GetDlgItem(IDC_EDIT_USENAME)->SetWindowText(m_szUseName);
		bUseName=TRUE;
	}

	if(m_szPassWd!=_T(""))
	{
		GetDlgItem(IDC_EDIT_PASSWD)->SetWindowText(m_szPassWd);
		bPassWd=TRUE;
	}

	if(m_szIP!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_IPADDR)->SetWindowText(m_szIP);
		bIP=TRUE;
	}

	if(m_szMask!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetWindowText(m_szMask);
		bMask=TRUE;
	}

	if(m_szGateWay!=_T(""))
	{
		GetDlgItem(IDC_IPADDRESS_GATEWAYADDR)->SetWindowText(m_szGateWay);
		bGateWay=TRUE;
	}

	if(m_szMAC!=_T(""))
	{
		GetDlgItem(IDC_EDIT_MACADDR)->SetWindowText(m_szMAC);
		bMAC=TRUE;
	}

	GetDlgItem(IDC_EDIT_VERSION)->SetWindowText(m_szVersion);

	//****************************************************
	XBoardNetInfo* pInfo=m_pManage->GetBoardInfo();

	pInfo->SetSecret(m_nSecret);
	pInfo->SerSecretSelect(m_nSecretSelect);
	pInfo->SetUseName(m_szUseName);
	pInfo->SetPassWd(m_szPassWd);
	pInfo->SetModel(m_nModel);
	pInfo->SetSelect(m_nModelSel);
	pInfo->SetIPAddr(m_szIP);
	pInfo->SetMaskAddr(m_szMask);
	pInfo->SetGateWayAddr(m_szGateWay);
	pInfo->SetMACAddr(m_szMAC);
	//pInfo->SetArrMAC(NULL);
	//****************************************************
	if(bSecret&&bModel&&bUseName&&bPassWd&&bMask&&bMAC&&bGateWay&&bIP)
	{
		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(TRUE);

		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_STATIC_ING1)->SetWindowText(m_pManage->GetTranslationString(_T("631"),_T("读取成功！")));
	}
}

BOOL XBoardNet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitComboModel();

	InitComboPassWd();

	m_Text = m_pManage->GetTranslationString(_T("636"), _T("未读取"));

	UpdateText();

	m_Edit_Name.SetLimitText(16);

	m_Edit_PassWd.SetLimitText(16);

	//InitData();

	return FALSE;  
}


void XBoardNet::ReloadInterface()
{
	CString szTitle;
	szTitle.Format(_T("%s-%d"),m_pManage->GetTranslationString(_T("644"),_T("配置预览卡")),m_nBoardIndex);

	SetWindowText(szTitle);

	GetDlgItem(IDOK)->SetWindowText(m_pManage->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDC_BUTTON_READ)->SetWindowText(m_pManage->GetTranslationString(_T("630"), _T("读取")));
	GetDlgItem(ID_OK2)->SetWindowText(m_pManage->GetTranslationString(_T("240"), _T("确定")));

	GetDlgItem(IDC_STATIC_MI)->SetWindowText(m_pManage->GetTranslationString(_T("652"),_T("加密"))+ _T(":"));
	GetDlgItem(IDC_STATIC_USENAME)->SetWindowText(m_pManage->GetTranslationString(_T("647"), _T("用户名")) + _T(":"));
	GetDlgItem(IDC_STATIC_MIMA)->SetWindowText(m_pManage->GetTranslationString(_T("349"), _T("密码")) + _T(":"));
	GetDlgItem(IDC_STATIC_MODEL)->SetWindowText(m_pManage->GetTranslationString(_T("643"), _T("模式选择")) + _T(":"));
	GetDlgItem(IDC_STATIC_IPADDR)->SetWindowText(m_pManage->GetTranslationString(_T("616"), _T("IP地址")) + _T(":"));
	GetDlgItem(IDC_STATIC_MASKADDR)->SetWindowText(m_pManage->GetTranslationString(_T("617"), _T("子网掩码")) + _T(":"));
	GetDlgItem(IDC_STATIC_GATEWAYADDR)->SetWindowText(m_pManage->GetTranslationString(_T("618"), _T("默认网关")) + _T(":"));
	GetDlgItem(IDC_STATIC_MACADDR)->SetWindowText(m_pManage->GetTranslationString(_T("619"), _T("MAC地址")) + _T(":"));
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(m_pManage->GetTranslationString(_T("774"), _T("版本")) + _T(":"));


	GetDlgItem(IDC_STATIC_TIP31)->SetWindowText(m_pManage->GetTranslationString(_T("634"),_T("例如"))+_T(":"));
	GetDlgItem(IDC_STATIC_READSTATUS1)->SetWindowText(m_pManage->GetTranslationString(_T("637"),_T("读取状态"))+ _T(":"));
}

void XBoardNet::InitData()
{
	MAP_SELECTBOARD& MapSelectBoardInfo=m_pManage->GetMapSelectBoard();

	MAP_SELECTBOARD::iterator iter=MapSelectBoardInfo.find(m_nBoardIndex);

	if(iter!=MapSelectBoardInfo.end())
	{
		XSelectBoardInfo* pInfo=iter->second;

		int n=pInfo->GetSelected();

		m_Combo_PassWd.SetCurSel(pInfo->GetSecretSel());

		m_Combo_Model.SetCurSel(pInfo->GetModelSel());

		GetDlgItem(IDC_EDIT_USENAME)->SetWindowText(pInfo->GetUserName());

		GetDlgItem(IDC_EDIT_PASSWD)->SetWindowText(pInfo->GetPassWd());

		GetDlgItem(IDC_IPADDRESS_IPADDR)->SetWindowText(pInfo->GetszIP());

		GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetWindowText(pInfo->GetMask());

		GetDlgItem(IDC_IPADDRESS_GATEWAYADDR)->SetWindowText(pInfo->GetGateWay());

		GetDlgItem(IDC_EDIT_MACADDR)->SetWindowText(pInfo->GetMAC());
	}
}

void XBoardNet::InitComboModel()
{
	m_Combo_Model.AddString(m_pManage->GetTranslationString(_T("640"),_T("2K")));

	m_Combo_Model.AddString(m_pManage->GetTranslationString(_T("641"),_T("4K")));

	m_Combo_Model.AddString(m_pManage->GetTranslationString(_T("642"),_T("关闭")));

	m_Combo_Model.SetCurSel(0);
}

void XBoardNet::InitComboPassWd()
{
	m_Combo_PassWd.AddString(m_pManage->GetTranslationString(_T("461"),_T("是")));

	m_Combo_PassWd.AddString(m_pManage->GetTranslationString(_T("462"),_T("否")));

	m_Combo_PassWd.SetCurSel(1);
}


void XBoardNet::OnBnClickedOk()
{
	//防止重复过快
	long dwTime=GetTickCount();

	if (abs(dwTime-m_nSetTime)<=1500)
	{
		return;
	}
	m_nSetTime=dwTime;
	//////////////////////////////////////////////////////////////////////////
	int nSecretSelect=m_Combo_PassWd.GetCurSel();
	int nSecret=0;
	if(nSecretSelect==0)
	{
		nSecret=1;
	}
	else if(nSecretSelect==1)
	{
		nSecret=0;
	}
	//////////////////////////////////////////////////////////////////////////
	CString szUseName=_T("");
	GetDlgItem(IDC_EDIT_USENAME)->GetWindowText(szUseName);
	szUseName.Trim();
	if(szUseName==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("645"),_T("用户名不能为空！"),MB_OK);

		GetDlgItem(IDC_EDIT_USENAME)->SetFocus();

		return;
	}
	//判断用户名密码合法性
	if (!HandleVerification::VerificationString(szUseName))
	{
		m_pManage->MessageBoxFromKey(_T("653"), _T("用户名包含非法字符，请重新输入!"), MB_OK);

		return;
	}
	
	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if(szPassWd==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("351"),_T("密码不能为空,请输入!"),MB_OK);

		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();

		return;
	}

	if (!HandleVerification::VerificationString(szPassWd))
	{
		m_pManage->MessageBoxFromKey(_T("654"), _T("密码包含非法字符，请重新输入!"), MB_OK);

		return;
	}
	///////////////////////////////////////////////////////////
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

	///////////////////////////////////////////////////////////
	CString szPaneIP=_T("");
	GetDlgItem(IDC_IPADDRESS_IPADDR)->GetWindowText(szPaneIP);
	szPaneIP.Trim();
	if(szPaneIP==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("622"),_T("IP地址不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_IPADDR)->SetFocus();

		return;
	}

	BYTE field1,field2,field3,field4;  
	m_IP.GetAddress(field1,field2,field3,field4);

	if(field1==0
		||field2==0
		||field3==0
		||field4==0)
	{
		m_pManage->MessageBoxFromKey(_T("633"),_T("IP地址错误！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_IPADDR)->SetFocus();

		return;
	}
	///////////////////////////////////////////////////////////

	CString szPaneMask=_T("");

	GetDlgItem(IDC_IPADDRESS_MASKADDR)->GetWindowText(szPaneMask);

	szPaneMask.Trim();

	if(szPaneMask==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("623"),_T("子网掩码不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetFocus();

		return;
	}
	///////////////////////////////////////////////////////////

	CString szPaneGateWay=_T("");

	GetDlgItem(IDC_IPADDRESS_GATEWAYADDR)->GetWindowText(szPaneGateWay);

	szPaneGateWay.Trim();

	if(szPaneGateWay==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("624"),_T("默认网关不能为空！"),MB_OK);

		GetDlgItem(IDC_IPADDRESS_GATEWAYADDR)->SetFocus();

		return;
	}
	///////////////////////////////////////////////////////////

	CString szPaneMAC=_T("");

	GetDlgItem(IDC_EDIT_MACADDR)->GetWindowText(szPaneMAC);

	szPaneMAC.Trim();

	if(szPaneMAC==_T(""))
	{
		m_pManage->MessageBoxFromKey(_T("625"),_T("MAC地址不能为空！"),MB_OK);

		GetDlgItem(IDC_EDIT_MACADDR)->SetFocus();

		return;
	}

	VEC_CSTRING VecString;
	SpiltCString(szPaneMAC,_T("-"),VecString);

	if(VecString.size()!=6)
	{
		m_pManage->MessageBoxFromKey(_T("628"),_T("MAC地址格式错误！"),MB_OK);

		GetDlgItem(IDC_EDIT_MACADDR)->SetFocus();

		return;
	}

	USES_CONVERSION;
	char* pPanMAC=W2A(szPaneMAC);

	int* pMAC=new int[6];

	int n=sscanf_s(pPanMAC,"%x-%x-%x-%x-%x-%x",pMAC,pMAC+1,pMAC+2,pMAC+3,pMAC+4,pMAC+5);
	if(n!=6)
	{
		m_pManage->MessageBoxFromKey(_T("628"),_T("MAC地址格式错误！"),MB_OK);

		GetDlgItem(IDC_EDIT_MACADDR)->SetFocus();

		return;
	}

	///////////////////////////////////////////////////////
	XBoardNetInfo* pInfo=m_pManage->GetBoardInfo();

	pInfo->SetSecret(nSecret);
	pInfo->SerSecretSelect(nSecretSelect);
	pInfo->SetUseName(szUseName);
	pInfo->SetPassWd(szPassWd);
	pInfo->SetModel(nModel);
	pInfo->SetSelect(nSelect);
	pInfo->SetIPAddr(szPaneIP);
	pInfo->SetMaskAddr(szPaneMask);
	pInfo->SetGateWayAddr(szPaneGateWay);
	pInfo->SetMACAddr(szPaneMAC);
	pInfo->SetArrMAC(pMAC);
	///////////////////////////////////////////////////////
	//m_pPane->SetMapBoardNetInfo();
	///////////////////////////////////////////////////////
	XSendDataPreviewBoard::SendDataOfSetPreviewNet(m_pManage);

	m_pManage->MessageBoxFromKey(_T("695"),_T("网络设置成功！"),MB_OK);
	
	delete []pMAC;
}

void XBoardNet::OnBnClickedOk2()
{

	CDialog::OnOK();
}

void XBoardNet::OnBnClickedRead()
{
	//选择板卡
	//////////////////////////////////////////////////////////////////////////
	XBoardNetInfo* pInfo=m_pManage->GetBoardInfo();
	pInfo->SetBoardIndex(m_nBoardIndex);
	//////////////////////////////////////////////////////////////////////////
	m_dBeginTime=GetTickCount();

	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(FALSE);

	m_Text=m_pManage->GetTranslationString(_T("635"),_T("读取中"));

	SetTimer(1,500,NULL);

	SetTimer(2,2400,NULL);

	XSendDataPreviewBoard::SendDataOfGetPreviewNet(m_pManage);
}

void XBoardNet::OnTimer(UINT_PTR nIDEvent)
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

void XBoardNet::ReRead()
{
	DWORD dNowTime=GetTickCount();
	//********************************************************************

	if(m_nReadIndex==3)
	{
		KillTimer(1);

		KillTimer(2);

		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(TRUE);

		m_Text=m_pManage->GetTranslationString(_T("639"),_T("读取失败！"));

		UpdateText();

		m_nReadIndex=1;
	}

	if(abs((long)dNowTime-(long)m_dBeginTime)>2500)
	{
		KillTimer(1);

		m_dBeginTime=GetTickCount();

		m_szReadIndex.Format(_T("%d"),m_nReadIndex);

		m_Text=m_pManage->GetTranslationString(_T("638"),_T("重新读取"))+m_szReadIndex;

		UpdateText();

		//*****************************************************************

		m_Text=m_pManage->GetTranslationString(_T("635"),_T("读取中"));

		SetTimer(1,500,NULL);

		//XSendDataVideoPreview::SendDataOfGetPreviewNet(m_pPane);

		m_nReadIndex++;
	}
}

void XBoardNet::UpdateText()
{
	CString szText=m_Text;

	if(szText==m_pManage->GetTranslationString(_T("635"),_T("读取中")))
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

	GetDlgItem(IDC_STATIC_ING1)->SetWindowText(szText);

	CRect rectText;
	GetDlgItem(IDC_STATIC_ING1)->GetWindowRect(&rectText);

	ScreenToClient(&rectText);

	InvalidateRect(&rectText);
}

void XBoardNet::OnIpnFieldchangedIp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	if(pIPAddr->iField==0)
	{
		BYTE field1,field2,field3,field4;  
		m_IP.GetAddress(field1,field2,field3,field4);

		if (field1>=0&&field1<=127)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetWindowText(_T("255.0.0.0"));
		}  
		else if(field1>=128&&field1<=191)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetWindowText(_T("255.255.0.0"));
		}  
		else if (field1>=192&&field1<=223)  
		{  
			GetDlgItem(IDC_IPADDRESS_MASKADDR)->SetWindowText(_T("255.255.255.0"));
		}  
	}

	*pResult = 0;
}

void XBoardNet::SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr)
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
