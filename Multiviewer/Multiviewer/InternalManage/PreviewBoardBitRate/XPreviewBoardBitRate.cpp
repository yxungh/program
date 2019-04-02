#include "stdafx.h"
#include "afxdialogex.h"
#include "XPreviewBoardBitRate.h"
#include "XVideoPreviewFrame.h"
#include "XInternalManage.h"
#include "XSendDataOfPreviewBoard.h"

// XPreviewBoardBitRate 对话框

IMPLEMENT_DYNAMIC(XPreviewBoardBitRate, CDialogEx)

	XPreviewBoardBitRate::XPreviewBoardBitRate(CWnd* pParent /*=NULL*/)
	: CDialogEx(XPreviewBoardBitRate::IDD, pParent)
{

	m_pManage=NULL;

	m_nBoardIndex=0;

	m_nMainDpi=0;
	m_nMainBitRate=0;
	m_nMainDpi=0;
	m_nSubBitRate=0;

	m_nMainDpi2=0;
	m_nMainBitRate2=0;
	m_nMainDpi2=0;
	m_nSubBitRate2=0;

	m_nMainDpi3=0;
	m_nMainBitRate3=0;
	m_nMainDpi3=0;
	m_nSubBitRate3=0;

	m_nMainDpi4=0;
	m_nMainBitRate4=0;
	m_nMainDpi4=0;
	m_nSubBitRate4=0;
}

XPreviewBoardBitRate::~XPreviewBoardBitRate()
{

}

void XPreviewBoardBitRate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_MAINDPI, m_Combo_MainDpi);
	DDX_Control(pDX, IDC_COMBO_SUBDPI, m_Combo_SubDpi);
	DDX_Control(pDX, IDC_COMBO_MAINBITRATE, m_Combo_MainBitRate);
	DDX_Control(pDX, IDC_COMBO_SUBBITRATE, m_Combo_SubBitRate);

	DDX_Control(pDX, IDC_COMBO_MAINDPI2, m_Combo_MainDpi2);
	DDX_Control(pDX, IDC_COMBO_SUBDPI2, m_Combo_SubDpi2);
	DDX_Control(pDX, IDC_COMBO_MAINBITRATE2, m_Combo_MainBitRate2);
	DDX_Control(pDX, IDC_COMBO_SUBBITRATE2, m_Combo_SubBitRate2);

	DDX_Control(pDX, IDC_COMBO_MAINDPI3, m_Combo_MainDpi3);
	DDX_Control(pDX, IDC_COMBO_SUBDPI3, m_Combo_SubDpi3);
	DDX_Control(pDX, IDC_COMBO_MAINBITRATE3, m_Combo_MainBitRate3);
	DDX_Control(pDX, IDC_COMBO_SUBBITRATE3, m_Combo_SubBitRate3);

	DDX_Control(pDX, IDC_COMBO_MAINDPI4, m_Combo_MainDpi4);
	DDX_Control(pDX, IDC_COMBO_SUBDPI4, m_Combo_SubDpi4);
	DDX_Control(pDX, IDC_COMBO_MAINBITRATE4, m_Combo_MainBitRate4);
	DDX_Control(pDX, IDC_COMBO_SUBBITRATE4, m_Combo_SubBitRate4);
}


BEGIN_MESSAGE_MAP(XPreviewBoardBitRate, CDialogEx)
	ON_BN_CLICKED(IDOK,OnBnClickedOk)
	ON_BN_CLICKED(ID_READ,OnBnClickedRead)
END_MESSAGE_MAP()


// XPreviewBoardBitRate 消息处理程序



void XPreviewBoardBitRate::SetManage(XInternalManage* p)
{
	m_pManage=p;
}

BOOL XPreviewBoardBitRate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitComboBox();

	return FALSE;  
}

void XPreviewBoardBitRate::ReloadInterface()
{
	CString szTitle;
	szTitle.Format(_T("%s-%d"),m_pManage->GetTranslationString(_T("644"),_T("配置预览卡")),m_nBoardIndex);

	SetWindowText(szTitle);

	GetDlgItem(ID_READ)->SetWindowText(m_pManage->GetTranslationString(_T("630"), _T("读取")));
	GetDlgItem(IDOK)->SetWindowText(m_pManage->GetTranslationString(_T("268"), _T("设置")));

	GetDlgItem(IDC_STATIC_TONG1)->SetWindowText(m_pManage->GetTranslationString(_T("685"),_T("通道1")));
	GetDlgItem(IDC_STATIC_TONG2)->SetWindowText(m_pManage->GetTranslationString(_T("686"),_T("通道2")));
	GetDlgItem(IDC_STATIC_TONG3)->SetWindowText(m_pManage->GetTranslationString(_T("687"),_T("通道3")));
	GetDlgItem(IDC_STATIC_TONG4)->SetWindowText(m_pManage->GetTranslationString(_T("688"),_T("通道4")));

	GetDlgItem(IDC_STATIC_ZHUMA)->SetWindowText(m_pManage->GetTranslationString(_T("689"),_T("主码流")));
	GetDlgItem(IDC_STATIC_ZIMA)->SetWindowText(m_pManage->GetTranslationString(_T("690"),_T("子码流")));
	GetDlgItem(IDC_STATIC_ZHUMA2)->SetWindowText(m_pManage->GetTranslationString(_T("689"),_T("主码流")));
	GetDlgItem(IDC_STATIC_ZIMA2)->SetWindowText(m_pManage->GetTranslationString(_T("690"),_T("子码流")));
	GetDlgItem(IDC_STATIC_ZHUMA3)->SetWindowText(m_pManage->GetTranslationString(_T("689"),_T("主码流")));
	GetDlgItem(IDC_STATIC_ZIMA3)->SetWindowText(m_pManage->GetTranslationString(_T("690"),_T("子码流")));
	GetDlgItem(IDC_STATIC_ZHUMA4)->SetWindowText(m_pManage->GetTranslationString(_T("689"),_T("主码流")));
	GetDlgItem(IDC_STATIC_ZIMA4)->SetWindowText(m_pManage->GetTranslationString(_T("690"),_T("子码流")));

	GetDlgItem(IDC_STATIC_MAINDPI)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBDPI)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_MAINBITRATE)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBBITRATE)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));

	GetDlgItem(IDC_STATIC_MAINDPI2)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBDPI2)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_MAINBITRATE2)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBBITRATE2)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));

	GetDlgItem(IDC_STATIC_MAINDPI3)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBDPI3)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_MAINBITRATE3)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBBITRATE3)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));

	GetDlgItem(IDC_STATIC_MAINDPI4)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBDPI4)->SetWindowText(m_pManage->GetTranslationString(_T("415"),_T("分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_MAINBITRATE4)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));
	GetDlgItem(IDC_STATIC_SUBBITRATE4)->SetWindowText(m_pManage->GetTranslationString(_T("657"),_T("码率"))+_T(":"));
}

void XPreviewBoardBitRate::InitComboBox()
{
	m_Combo_MainDpi.AddString(_T("1920*1080(1080P)"));//19
	m_Combo_MainDpi.SetCurSel(0);

	m_Combo_MainDpi2.AddString(_T("1920*1080(1080P)"));//19
	m_Combo_MainDpi2.SetCurSel(0);

	m_Combo_MainDpi3.AddString(_T("1920*1080(1080P)"));//19
	m_Combo_MainDpi3.SetCurSel(0);

	m_Combo_MainDpi4.AddString(_T("1920*1080(1080P)"));//19
	m_Combo_MainDpi4.SetCurSel(0);
	//////////////////////////////////////////////////////////////////////////

	m_Combo_SubDpi.AddString(_T("360*288(CIF)"));//1
	m_Combo_SubDpi.AddString(_T("720*576(D1)"));//4
	m_Combo_SubDpi.SetCurSel(0);

	m_Combo_SubDpi2.AddString(_T("360*288(CIF)"));//1
	m_Combo_SubDpi2.AddString(_T("720*576(D1)"));//4
	m_Combo_SubDpi2.SetCurSel(0);

	m_Combo_SubDpi3.AddString(_T("360*288(CIF)"));//1
	m_Combo_SubDpi3.AddString(_T("720*576(D1)"));//4
	m_Combo_SubDpi3.SetCurSel(0);

	m_Combo_SubDpi4.AddString(_T("360*288(CIF)"));//1
	m_Combo_SubDpi4.AddString(_T("720*576(D1)"));//4
	m_Combo_SubDpi4.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////
	CString szTemp;
	int nBase=512;
	int nMainBase=1024;
	for(int i=1;i<=8;i++)
	{
		int nTemp=i*nBase;
		szTemp.Format(_T("%d"),nTemp);
		m_Combo_SubBitRate.AddString(szTemp);
		m_Combo_SubBitRate2.AddString(szTemp);
		m_Combo_SubBitRate3.AddString(szTemp);
		m_Combo_SubBitRate4.AddString(szTemp);
	}
	m_Combo_SubBitRate.SetCurSel(0);
	m_Combo_SubBitRate2.SetCurSel(0);
	m_Combo_SubBitRate3.SetCurSel(0);
	m_Combo_SubBitRate4.SetCurSel(0);
	//////////////////////////////////////////////////////////////////////////
	for(int j=4;j<=8;j++)
	{
		int nTemp=j*nMainBase;
		szTemp.Format(_T("%d"),nTemp);
		m_Combo_MainBitRate.AddString(szTemp);
		m_Combo_MainBitRate2.AddString(szTemp);
		m_Combo_MainBitRate3.AddString(szTemp);
		m_Combo_MainBitRate4.AddString(szTemp);
	}
	m_Combo_MainBitRate.SetCurSel(0);
	m_Combo_MainBitRate2.SetCurSel(0);
	m_Combo_MainBitRate3.SetCurSel(0);
	m_Combo_MainBitRate4.SetCurSel(0);
}

void XPreviewBoardBitRate::OnBnClickedOk()
{
	int nTemp=0;
	CString szTemp;

	nTemp=m_Combo_MainDpi.GetCurSel();

	int nMainDpi=0;
	if(nTemp==0)
	{
		nMainDpi=19;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainBitRate.GetCurSel();
	m_Combo_MainBitRate.GetLBText(nTemp,szTemp);
	int nTempMainBitRate=_ttoi(szTemp);

	int nMainBitRate=nTempMainBitRate/1024;
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubDpi.GetCurSel();

	int nSubDpi=0;
	if(nTemp==0)
	{
		nSubDpi=1;
	}
	else if(nTemp==1)
	{
		nSubDpi=4;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubBitRate.GetCurSel();
	m_Combo_SubBitRate.GetLBText(nTemp,szTemp);
	int nTempSubBitRate=_ttoi(szTemp);

	int nSubBitRate=nTempSubBitRate/512;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainDpi2.GetCurSel();

	int nMainDpi2=0;
	if(nTemp==0)
	{
		nMainDpi2=19;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainBitRate2.GetCurSel();
	m_Combo_MainBitRate2.GetLBText(nTemp,szTemp);
	int nTempMainBitRate2=_ttoi(szTemp);

	int nMainBitRate2=nTempMainBitRate2/1024;
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubDpi2.GetCurSel();

	int nSubDpi2=0;
	if(nTemp==0)
	{
		nSubDpi2=1;
	}
	else if(nTemp==1)
	{
		nSubDpi2=4;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubBitRate2.GetCurSel();
	m_Combo_SubBitRate2.GetLBText(nTemp,szTemp);
	int nTempSubBitRate2=_ttoi(szTemp);

	int nSubBitRate2=nTempSubBitRate2/512;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainDpi3.GetCurSel();

	int nMainDpi3=0;
	if(nTemp==0)
	{
		nMainDpi3=19;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainBitRate3.GetCurSel();
	m_Combo_MainBitRate3.GetLBText(nTemp,szTemp);
	int nTempMainBitRate3=_ttoi(szTemp);

	int nMainBitRate3=nTempMainBitRate3/1024;
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubDpi3.GetCurSel();

	int nSubDpi3=0;
	if(nTemp==0)
	{
		nSubDpi3=1;
	}
	else if(nTemp==1)
	{
		nSubDpi3=4;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubBitRate3.GetCurSel();
	m_Combo_SubBitRate3.GetLBText(nTemp,szTemp);
	int nTempSubBitRate3=_ttoi(szTemp);

	int nSubBitRate3=nTempSubBitRate3/512;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainDpi4.GetCurSel();

	int nMainDpi4=0;
	if(nTemp==0)
	{
		nMainDpi4=19;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_MainBitRate4.GetCurSel();
	m_Combo_MainBitRate4.GetLBText(nTemp,szTemp);
	int nTempMainBitRate4=_ttoi(szTemp);

	int nMainBitRate4=nTempMainBitRate4/1024;
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubDpi4.GetCurSel();

	int nSubDpi4=0;
	if(nTemp==0)
	{
		nSubDpi4=1;
	}
	else if(nTemp==1)
	{
		nSubDpi4=4;
	}
	//////////////////////////////////////////////////////////////////////////
	nTemp=m_Combo_SubBitRate4.GetCurSel();
	m_Combo_SubBitRate4.GetLBText(nTemp,szTemp);
	int nTempSubBitRate4=_ttoi(szTemp);

	int nSubBitRate4=nTempSubBitRate4/512;
	//////////////////////////////////////////////////////////////////////////
	XBitRateInfo* pInfo=m_pManage->GetBitRateInfo();

	pInfo->SetMainDpi1(nMainDpi);
	pInfo->SetMainBitRate1(nMainBitRate);
	pInfo->SetSubDpi1(nSubDpi);
	pInfo->SetSubBitRate1(nSubBitRate);

	if(m_nMainDpi!=nMainDpi
		||m_nMainBitRate!=nMainBitRate
		||m_nSubDpi!=nSubDpi
		||m_nSubBitRate!=nSubBitRate)
	{
		pInfo->SetFlag1(1);
	}
	else
	{
		pInfo->SetFlag1(0);
	}
	//////////////////////////////////////////////////////////////////////////
	pInfo->SetMainDpi2(nMainDpi2);
	pInfo->SetMainBitRate2(nMainBitRate2);
	pInfo->SetSubDpi2(nSubDpi2);
	pInfo->SetSubBitRate2(nSubBitRate2);

	if(m_nMainDpi2!=nMainDpi2
		||m_nMainBitRate2!=nMainBitRate2
		||m_nSubDpi2!=nSubDpi2
		||m_nSubBitRate2!=nSubBitRate2)
	{
		pInfo->SetFlag2(1);
	}
	else
	{
		pInfo->SetFlag2(0);
	}
	//////////////////////////////////////////////////////////////////////////
	pInfo->SetMainDpi3(nMainDpi3);
	pInfo->SetMainBitRate3(nMainBitRate3);
	pInfo->SetSubDpi3(nSubDpi3);
	pInfo->SetSubBitRate3(nSubBitRate3);

	if(m_nMainDpi3!=nMainDpi3
		||m_nMainBitRate3!=nMainBitRate3
		||m_nSubDpi3!=nSubDpi3
		||m_nSubBitRate3!=nSubBitRate3)
	{
		pInfo->SetFlag3(1);
	}
	else
	{
		pInfo->SetFlag3(0);
	}
	//////////////////////////////////////////////////////////////////////////
	pInfo->SetMainDpi4(nMainDpi4);
	pInfo->SetMainBitRate4(nMainBitRate4);
	pInfo->SetSubDpi4(nSubDpi4);
	pInfo->SetSubBitRate4(nSubBitRate4);

	if(m_nMainDpi4!=nMainDpi4
		||m_nMainBitRate4!=nMainBitRate4
		||m_nSubDpi4!=nSubDpi4
		||m_nSubBitRate4!=nSubBitRate4)
	{
		pInfo->SetFlag4(1);
	}
	else
	{
		pInfo->SetFlag4(0);
	}
	//////////////////////////////////////////////////////////////////////////
	XSendDataPreviewBoard::AddSendDataOfBitRate(m_pManage,m_nBoardIndex);

	CDialog::OnOK();
}

void XPreviewBoardBitRate::OnBnClickedRead()
{
	XSendDataPreviewBoard::AddSendDataOfReadBitRateInfo(m_pManage,m_nBoardIndex);
}

void XPreviewBoardBitRate::ResetDate()
{
	int nTemp=0;
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainDpi==0)
	{
		nTemp=0;
	}
	else if(m_nMainDpi==19)
	{
		nTemp=0;
	}
	m_Combo_MainDpi.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubDpi==0)
	{
		nTemp=0;
	}
	else if(m_nSubDpi==1)
	{
		nTemp=0;
	}
	else if(m_nSubDpi==4)
	{
		nTemp=1;
	}

	m_Combo_SubDpi.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainBitRate==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nMainBitRate-4;
	}
	m_Combo_MainBitRate.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubBitRate==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nSubBitRate-1;
	}
	m_Combo_SubBitRate.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainDpi2==0)
	{
		nTemp=0;
	}
	else if(m_nMainDpi2==19)
	{
		nTemp=0;
	}
	m_Combo_MainDpi2.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubDpi2==0)
	{
		nTemp=0;
	}
	else if(m_nSubDpi2==1)
	{
		nTemp=0;
	}
	else if(m_nSubDpi2==4)
	{
		nTemp=1;
	}

	m_Combo_SubDpi2.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainBitRate2==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nMainBitRate2-4;
	}
	m_Combo_MainBitRate2.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubBitRate2==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nSubBitRate2-1;
	}
	m_Combo_SubBitRate2.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainDpi3==0)
	{
		nTemp=0;
	}
	else if(m_nMainDpi3==19)
	{
		nTemp=0;
	}
	m_Combo_MainDpi3.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubDpi3==0)
	{
		nTemp=0;
	}
	else if(m_nSubDpi3==1)
	{
		nTemp=0;
	}
	else if(m_nSubDpi3==4)
	{
		nTemp=1;
	}

	m_Combo_SubDpi3.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainBitRate3==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nMainBitRate3-4;
	}
	m_Combo_MainBitRate3.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubBitRate3==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nSubBitRate3-1;
	}
	m_Combo_SubBitRate3.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainDpi4==0)
	{
		nTemp=0;
	}
	else if(m_nMainDpi4==19)
	{
		nTemp=0;
	}
	m_Combo_MainDpi4.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubDpi4==0)
	{
		nTemp=0;
	}
	else if(m_nSubDpi4==1)
	{
		nTemp=0;
	}
	else if(m_nSubDpi4==4)
	{
		nTemp=1;
	}

	m_Combo_SubDpi4.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nMainBitRate4==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nMainBitRate4-4;
	}
	m_Combo_MainBitRate4.SetCurSel(nTemp);
	//////////////////////////////////////////////////////////////////////////
	if(m_nSubBitRate4==0)
	{
		nTemp=0;
	}
	else
	{
		nTemp=m_nSubBitRate4-1;
	}
	m_Combo_SubBitRate4.SetCurSel(nTemp);

}

//////////////////////////////////////////////////////////////////////////

void XPreviewBoardBitRate::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XPreviewBoardBitRate::GetBoardIndex()
{
	return m_nBoardIndex;
}
//////////////////////////////////////////////////////////////////////////
void XPreviewBoardBitRate::SetMainDpi(int n)
{
	m_nMainDpi=n;
}

int XPreviewBoardBitRate::GetMianDpi()
{
	return m_nMainDpi;
}

void XPreviewBoardBitRate::SetMainBitRate(int n)
{
	m_nMainBitRate=n;
}

int XPreviewBoardBitRate::GetMainBitRate()
{
	return m_nMainBitRate;
}

void XPreviewBoardBitRate::SetSubDpi(int n)
{
	m_nSubDpi=n;
}

int XPreviewBoardBitRate::GetSubDpi()
{
	return m_nSubDpi;
}

void XPreviewBoardBitRate::SetSubBitRate(int n)
{
	m_nSubBitRate=n;
}

int XPreviewBoardBitRate::GetSunBitRate()
{
	return m_nSubBitRate;
}
//////////////////////////////////////////////////////////////////////////
void XPreviewBoardBitRate::SetMainDpi2(int n)
{
	m_nMainDpi2=n;
}

int XPreviewBoardBitRate::GetMianDpi2()
{
	return m_nMainDpi2;
}

void XPreviewBoardBitRate::SetMainBitRate2(int n)
{
	m_nMainBitRate2=n;
}

int XPreviewBoardBitRate::GetMainBitRate2()
{
	return m_nMainBitRate2;
}

void XPreviewBoardBitRate::SetSubDpi2(int n)
{
	m_nSubDpi2=n;
}

int XPreviewBoardBitRate::GetSubDpi2()
{
	return m_nSubDpi2;
}

void XPreviewBoardBitRate::SetSubBitRate2(int n)
{
	m_nSubBitRate2=n;
}

int XPreviewBoardBitRate::GetSunBitRate2()
{
	return m_nSubBitRate2;
}
//////////////////////////////////////////////////////////////////////////
void XPreviewBoardBitRate::SetMainDpi3(int n)
{
	m_nMainDpi3=n;	
}

int XPreviewBoardBitRate::GetMianDpi3()
{
	return m_nMainDpi3;
}

void XPreviewBoardBitRate::SetMainBitRate3(int n)
{
	m_nMainBitRate3=n;
}

int XPreviewBoardBitRate::GetMainBitRate3()
{
	return m_nMainBitRate3;
}

void XPreviewBoardBitRate::SetSubDpi3(int n)
{
	m_nSubDpi3=n;
}

int XPreviewBoardBitRate::GetSubDpi3()
{
	return m_nSubDpi3;
}

void XPreviewBoardBitRate::SetSubBitRate3(int n)
{
	m_nSubBitRate3=n;
}

int XPreviewBoardBitRate::GetSunBitRate3()
{
	return m_nSubBitRate3;
}
//////////////////////////////////////////////////////////////////////////
void XPreviewBoardBitRate::SetMainDpi4(int n)
{
	m_nMainDpi4=n;
}

int XPreviewBoardBitRate::GetMianDpi4()
{
	return m_nMainDpi4;
}

void XPreviewBoardBitRate::SetMainBitRate4(int n)
{
	m_nMainBitRate4=n;
}

int XPreviewBoardBitRate::GetMainBitRate4()
{
	return m_nMainBitRate4;
}

void XPreviewBoardBitRate::SetSubDpi4(int n)
{
	m_nSubDpi4=n;
}

int XPreviewBoardBitRate::GetSubDpi4()
{
	return m_nSubDpi4;
}

void XPreviewBoardBitRate::SetSubBitRate4(int n)
{
	m_nSubBitRate4=n;
}

int XPreviewBoardBitRate::GetSunBitRate4()
{
	return m_nSubBitRate4;
}