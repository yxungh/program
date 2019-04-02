
// OpticalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Optical.h"
#include "OpticalDlg.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XHandleIni.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "AboutDlg.h"
#include "XNetManage.h"
#include "XReciveDataManage.h"
#include "XSendDataManage.h"
#include "XStatusBar.h"
#include "XToolBar.h"
#include "XSetNet.h"
#include "XJsonManage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DIG_WIDTH 920;
#define DIG_HIGHT 600;

// COpticalDlg 对话框
COpticalDlg::COpticalDlg(CWnd* pParent)
	: XDialog(COpticalDlg::IDD, pParent,_T("")/*XHandlePath::GetPhotoPath(_T("Login.png"))*/),
	m_pNetManage(NULL),
	m_pReciveDataManage(NULL),
	m_pStatusBar(NULL),
	m_pToolBar(NULL),
	m_szIP(_T("")),
	m_nPort(0),
	m_bIsLogin(FALSE),
	m_szCurUserName(_T("")),
	m_dHeartTime(0),
	m_nHeartTimerID(0),
	m_bIsOnline(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpticalDlg::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpticalDlg, XDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
	ON_MESSAGE(MSG_UDP,OnUDP)
	ON_MESSAGE(MSG_TOOBAR_ITEMLCLICK,OnToolBarClicked)
	ON_COMMAND(ID_ABOUT,OnAbout)
	ON_COMMAND(ID_LANGUAGE_ZH_CN,OnLanguageZHCN)
	ON_COMMAND(ID_LANGUAGE_ZH_TW,OnLanguageZHTW)
	ON_COMMAND(ID_LANGUAGE_EN,OnLanguageEN)
	ON_COMMAND(ID_SETNET,OnSetNet)
	
END_MESSAGE_MAP()


// COpticalDlg 消息处理程序

void COpticalDlg::OnCancel()
{
	ClearData();
	__super::OnCancel();
}

void COpticalDlg::ClearData()
{
	m_bIsLogin=FALSE;
	m_szCurUserName=_T("");

	XMessageBox::GetInstance()->Release();
	XSendDataManage::GetInstance()->Release();
	XTranslationManage::GetInstance()->Release();
	XJsonManage::GetInstance()->Relase();

	RELEASE(m_pNetManage);
	RELEASE(m_pReciveDataManage);
	RELEASE(m_pToolBar);
	RELEASE(m_pStatusBar);
}

BOOL COpticalDlg::OnInitDialog()
{
	XDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COpticalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpticalDlg::DrawDlg(CDC* pDC)
{
	HDC hdc=pDC->GetSafeHdc();

	CRect rt;
	GetClientRect(&rt);

	HDC hMemdc=CreateCompatibleDC(hdc);

	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,rt.Width(),rt.Height());
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
	///////////////////////////////////////////////////////////////////////
	Gdiplus::Graphics graphics(hMemdc);
	graphics.Clear(Gdiplus::Color(232, 239, 242));

	Gdiplus::Image topImage(XHandlePath::GetPhotoPath(_T("maintitlebg.png")));
	graphics.DrawImage(&topImage, 0, 0, rt.Width(), MAIN_TOPHEIGHT);

	//Gdiplus::Image topHightLightLImage(XHandlePath::GetPhotoPath(_T("maintitlebg1.png")));
	//graphics.DrawImage(&topHightLightLImage, 0, 0, rt.Width(), 30);

	//图标
	Gdiplus::Image ico(XHandlePath::GetPhotoPath(_T("ico.png")));
	graphics.DrawImage(&ico, 4, 3, ico.GetWidth(), ico.GetHeight());

	FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font( &fontfamily, 9, FontStyleBold, UnitPoint);
	SolidBrush whitebrush(Color(254, 255, 255, 255));
	CStringW strText;
	GetWindowText(strText);
	graphics.DrawString(strText, -1, &font, PointF((Gdiplus::REAL)(6 + ico.GetWidth()), 7.0f), 0, &whitebrush);

	Gdiplus::Pen pen(Color(255, 5, 122, 252), 1);

	CRect rtTemp = rt;
	rtTemp.DeflateRect(0, 0, 1, 1);
	graphics.DrawRectangle(&pen, Rect(rtTemp.left,rtTemp.top,rtTemp.Width(), rtTemp.Height()));
	///////////////////////////////////////////////////////////////////////
	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC(hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);
}

void COpticalDlg::Init()
{
	ReSize();
	InitManage();
	InitData();
	InitBtn();
	InitToolBar();
	InitStatusBar();
	InitDlg();

	ShowPowerManageDlg();
	ReloadInterface();
	BeginTimer();
}

void COpticalDlg::InitData()
{
	CString szIniPath=XHandlePath::GetIniPath(APP_ININAME);

	m_nPort=XHandleIni::GetInt(_T("Info"),_T("DevicePort"),48000,szIniPath);
	m_szIP=XHandleIni::GetString(_T("Info"),_T("DeviceIP"),_T("127.0.0.1"),szIniPath);
}

void COpticalDlg::SetDeviceIPAndPort(CString szIP,int nPort)
{
	m_szIP=szIP;
	m_nPort=nPort;
}

void COpticalDlg::SaveDeviceIPAndPort(CString szIP,int nPort)
{
	CString szIniPath=XHandlePath::GetIniPath(APP_ININAME);
	XHandleIni::WriteData(_T("Info"),_T("DeviceIP"),szIP,szIniPath);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"), nPort);
	XHandleIni::WriteData(_T("Info"),_T("DevicePort"),szTemp,szIniPath);
}

void COpticalDlg::ReSize()
{
	int nWidth=DIG_WIDTH;
	int nHight=DIG_HIGHT;
	MoveWindow(0,0,nWidth,nHight);
}

void COpticalDlg::InitToolBar()
{
	CRect rt;
	GetClientRect(&rt);

	int nItemWidth = 90;
	int nItemHeight = 90;
	int nItemDistance = 5;
	int nItemCount = 5;

	m_pToolBar->Create(nItemWidth, nItemHeight, nItemDistance, WS_CHILD|WS_VISIBLE, CRect(CPoint(10, 35), 
		CSize((nItemWidth + nItemDistance) * nItemCount + 10, nItemHeight)), this, ID_TOOLBAR);
	m_pToolBar->ShowWindow(SW_SHOW);
	m_pToolBar->UpdateWindow();

	addToolBar();
}

void COpticalDlg::addToolBar()
{
	m_pToolBar->ClearAllItem();
	m_pToolBar->InsertItem(XHandlePath::GetPhotoPath(_T("locked_64px.png")),_T("13"),_T("权限管理"),(DWORD)DLGTYPE_POWERMANAGE);
	m_pToolBar->InsertItem(XHandlePath::GetPhotoPath(_T("tools_64px.png")),_T("14"),_T("主机配置"),(DWORD)DLGTYPE_HOSTCONFIG);
}

void COpticalDlg::InitStatusBar()
{
	CRect rt;
	GetClientRect(&rt);

	CRect rtStatusbar(2,rt.bottom-MAIN_STATUSBARHEIGHT-2,rt.right-2,rt.bottom-2);
	m_pStatusBar->Create(WS_CHILD|WS_VISIBLE,rtStatusbar,this,ID_STATUSBAR);
	m_pStatusBar->ShowWindow(SW_SHOW);
	m_pStatusBar->UpdateWindow();
}

void COpticalDlg::InitManage()
{
	XTranslationManage::GetInstance()->Init();
	XSendDataManage::GetInstance()->SetDelegate(this);
	XMessageBox::GetInstance();
	XJsonManage::GetInstance();

	m_pToolBar=new XToolBar;
	m_pStatusBar=new XStatusBar;

	m_pNetManage=new XNetManage;
	m_pNetManage->SetDelegate(this);
	m_pNetManage->Init();

	m_pReciveDataManage=new XReciveDataManage;
	m_pReciveDataManage->SetDelegate(this);
	m_pReciveDataManage->Init();
}

void COpticalDlg::InitBtn()
{
	CRect rt;
	GetClientRect(&rt);

	int nBtnWidth=42;
	int nBtnHeight=26;
	int nLeft=0;

	nLeft=rt.right-nBtnWidth-1;
	CRect rtClose(nLeft,1,nLeft+nBtnWidth,nBtnHeight);
	CreateBtn(&m_Btn_Close,&rtClose,ID_BTN_CLOSE,_T("close.png"));

	nLeft-=nBtnWidth;
	CRect rtMin(nLeft,1,nLeft+nBtnWidth,nBtnHeight);
	CreateBtn(&m_Btn_Min, &rtMin,ID_BTN_MIN,_T("min.png"));

	nLeft-=nBtnWidth;
	CRect rtSet(nLeft,1,nLeft+nBtnWidth,nBtnHeight);
	CreateBtn(&m_Btn_Set,&rtSet,ID_BTN_SET,_T("set.png"));
}

void COpticalDlg::CreateBtn(XBtn* pBtn,CRect rect,UINT nID,CString szPhotoName)
{
	pBtn->Create(WS_CHILD|WS_VISIBLE,rect,this,nID);
	pBtn->ShowWindow(SW_SHOW);
	pBtn->UpdateWindow();
	pBtn->SetImage(XHandlePath::GetPhotoPath(szPhotoName));
}

LRESULT COpticalDlg::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if(wParam==ID_BTN_CLOSE)
	{
		OnCancel();
	}
	else if(wParam==ID_BTN_SET)
	{
		OnSet();
	}
	else if(wParam==ID_BTN_MIN)
	{
		ShowWindow(SW_MINIMIZE);
	}

	return 0;
}

void COpticalDlg::OnSet()
{
	CMenu menu; 
	menu.CreatePopupMenu();
	/////////////////////////////////////////////////////////////////////////////////////
	CMenu menuLanguage;
	menuLanguage.CreatePopupMenu();

	menuLanguage.AppendMenu(MF_STRING, ID_LANGUAGE_ZH_CN, GetTranslationString(_T("6"), _T("中文简体")));
	menuLanguage.AppendMenu(MF_STRING, ID_LANGUAGE_ZH_TW, GetTranslationString(_T("7"), _T("中文繁体"))); 
	menuLanguage.AppendMenu(MF_STRING, ID_LANGUAGE_EN, GetTranslationString(_T("8"), _T("英文"))); 

	LANGUAGETYPE type = XTranslationManage::GetInstance()->GetLanguageType();
	if (LANGUAGETYPE_ZH_CN==type)
	{
		menuLanguage.CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
	}
	else if(LANGUAGETYPE_ZH_TW==type)
	{
		menuLanguage.CheckMenuItem(1, MF_BYPOSITION | MF_CHECKED);
	}
	else if (LANGUAGETYPE_EN==type)
	{
		menuLanguage.CheckMenuItem(2, MF_BYPOSITION | MF_CHECKED);
	} 

	menu.InsertMenu(0, MF_BYPOSITION|MF_POPUP, (UINT)menuLanguage.m_hMenu, GetTranslationString(_T("9"), _T("语言"))); 
	
	/////////////////////////////////////////////////////////////////////////////////////
	menu.AppendMenu(MF_STRING, ID_SETNET, GetTranslationString(_T("15"), _T("网络设置")));
	menu.AppendMenu(MF_STRING, ID_ABOUT, GetTranslationString(_T("10"), _T("关于"))); 

	CRect rtSet;
	m_Btn_Set.GetWindowRect(&rtSet);

	menu.TrackPopupMenu(TPM_LEFTALIGN, rtSet.left + 1, rtSet.bottom - 1, this); 
	menu.DestroyMenu(); 
}

void COpticalDlg::OnSetNet()
{
	XSetNet dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();
}

CString COpticalDlg::GetIP()
{
	return m_szIP;
}

int COpticalDlg::GetPort()
{
	return m_nPort;
}

BOOL COpticalDlg::IsLogin()
{
	return m_bIsLogin;
}

void COpticalDlg::SetLogin(BOOL b)
{
	m_bIsLogin=b;
}

void COpticalDlg::SetCurUserName(CString szUserName)
{
	m_szCurUserName=szUserName;
}

CString COpticalDlg::GetCurUserName()
{
	return m_szCurUserName;
}

void COpticalDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void COpticalDlg::OnLanguageZHCN()
{
	SetLanguageType(LANGUAGETYPE_ZH_CN);
}

void COpticalDlg::OnLanguageZHTW()
{
	SetLanguageType(LANGUAGETYPE_ZH_TW);
}

void COpticalDlg::OnLanguageEN()
{
	SetLanguageType(LANGUAGETYPE_EN);
}

void COpticalDlg::SetLanguageType(LANGUAGETYPE type)
{
	LANGUAGETYPE nowType=XTranslationManage::GetInstance()->GetLanguageType();

	if (nowType!=type)
	{
		XTranslationManage::GetInstance()->SetLanguageType(type);

		XTranslationManage::GetInstance()->SaveLanguageType();

		ReloadInterface();
	}
}

void COpticalDlg::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("12")));

	if(NULL!=m_pStatusBar)
	{
		m_pStatusBar->ReloadInterface();
	}

	if(NULL!=m_pToolBar)
	{
		m_pToolBar->ReloadInterface();
	}

	m_PowerManageDlg.ReloadInterface();
}

CString COpticalDlg::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

HWND COpticalDlg::GetHWND()
{
	return GetSafeHwnd();
}

void COpticalDlg::HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr)
{
	if(m_pReciveDataManage->HandleUDPData(pData, nDataLen, addr))
		return;
}

LRESULT COpticalDlg::OnUDP(WPARAM wParam, LPARAM lParam)
{
	m_pNetManage->HandleUDPMsg(wParam, lParam);
	return 0;
}

BOOL COpticalDlg::SendData(char* pData,int nDataLen)
{
	BOOL bResult=FALSE;

	if((nullptr!=pData)&&(nDataLen>0))
		bResult=m_pNetManage->SendData(GetIP(),GetPort(),pData,nDataLen);

	return bResult;
}

LRESULT COpticalDlg::OnToolBarClicked(WPARAM wParam, LPARAM lParam)
{
	TRACE(_T("OnToolBarClicked\n"));

	//手动设置状态栏激活对话框名称（由于个数有限，没有从工具栏获取）
	if(NULL!=m_pStatusBar)
		m_pStatusBar->SetDlgType(wParam);

	switch(wParam)
	{
	case DLGTYPE_POWERMANAGE:
		{
			ShowPowerManageDlg();	
		}
		break;
	case DLGTYPE_HOSTCONFIG:
		{
			ShowHostConfigDlg();		
		}
		break;
	default:
		break;
	}

	return 0;
}

void COpticalDlg::ShowPowerManageDlg()
{
	m_PowerManageDlg.ShowWindow(TRUE);
	m_HostConfigDlg.ShowWindow(FALSE);
}

void COpticalDlg::ShowHostConfigDlg()
{
	m_PowerManageDlg.ShowWindow(FALSE);
	m_HostConfigDlg.ShowWindow(TRUE);
}

void COpticalDlg::InitDlg()
{
	InitHostConfigDlg();
	InitPowerManageDlg();
}

void COpticalDlg::InitHostConfigDlg()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_MAIN)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_HostConfigDlg.SetDelegate(this);
	m_HostConfigDlg.Create(IDD_DIALOG_HOSTCONFIG,this);
	m_HostConfigDlg.MoveWindow(&rect);
	m_HostConfigDlg.ShowWindow(FALSE);
	m_HostConfigDlg.UpdateWindow();
}

void COpticalDlg::InitPowerManageDlg()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_MAIN)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_PowerManageDlg.SetDelegate(this);
	m_PowerManageDlg.Create(IDD_DIALOG_POWERMANAGE,this);
	m_PowerManageDlg.MoveWindow(&rect);
	m_PowerManageDlg.ShowWindow(TRUE);
	m_PowerManageDlg.UpdateWindow();

	//添加子对话框
	m_PowerManageDlg.InsertItem(XHandlePath::GetPhotoPath(_T("user.png")),(DWORD)SUBBTNTYPE_USERMANAGE,GetTranslationString(_T("18")));
	m_PowerManageDlg.InsertItem(XHandlePath::GetPhotoPath(_T("node.png")),(DWORD)SUBBTNTYPE_NODEMANAGE,GetTranslationString(_T("29")));
	m_PowerManageDlg.InitSub();
}

//////////////////////////////////////////////////////////////////////////
void COpticalDlg::BeginTimer()
{
	//欢迎文字
	m_PowerManageDlg.Operate(OPERATETYPE_WELCOMETEXT,NULL);
	SetTimer(TIMERID_WELCOMETEXT,TIMERELAPSE_WELCOMETEXT,NULL);

	//心跳
	m_dHeartTime=GetTickCount();
	XSendDataManage::GetInstance()->SendDataOfHeart(m_dHeartTime);
	m_nHeartTimerID=SetTimer(TIMERID_HEART,TIMESPACE_HEART,NULL);
}

void COpticalDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMERID_WELCOMETEXT:
		{
			m_PowerManageDlg.Operate(OPERATETYPE_WELCOMETEXT,NULL);
		}
		break;
	case TIMERID_HEART:
		{
			SendHeart();
		}
		break;
	default:
		break;
	}
}

void COpticalDlg::SendHeart()
{
	//if(!m_nHeartTimerID)
	//{
	//	m_nHeartTimerID=SetTimer(TIMERID_HEART,TIMESPACE_HEART,NULL);
	//}

	m_dHeartTime=GetTickCount();
	XSendDataManage::GetInstance()->SendDataOfHeart(m_dHeartTime);
}

void COpticalDlg::OperateOfHeart(char* pData)
{
	long dCurTime=GetTickCount();
	//TRACE(_T("dCurTime=%d\n"),dCurTime);

	long dHeartTime=0;
	memcpy(&dHeartTime,pData,4);

	//TRACE(_T("dHeartTime=%d\n"),dHeartTime);

	if(abs(dCurTime-dHeartTime)>=1000)
	{
		m_bIsOnline=FALSE;
	}
	else
	{
		m_bIsOnline=TRUE;
		TRACE(_T("Online\n"));
	}
}

//////////////////////////////////////////////////////////////////////////
void COpticalDlg::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_LOGIN:
	case OPERATETYPE_LOGINOUT:
		{
			m_PowerManageDlg.Operate(type,pData);
		}
		break;
	case OPERATETYPE_HEART:
		{
			OperateOfHeart((char*)pData);
		}
		break;
	default:
		break;
	}
}

