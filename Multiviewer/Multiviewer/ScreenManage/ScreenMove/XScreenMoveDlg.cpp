#include "stdafx.h"
#include "afxdialogex.h"
#include "XScreenMoveDlg.h"
#include "XDelegateScreenMoveDlg.h"
#include "XScreenManage.h"
#include "XScreenMoveInfo.h"
#include "HandleMutrix.h"
#include "XSendDataScreenManage.h"
#include "XScreen.h"
#include "XCalculateScreenManage.h"
#include "XScreenMoveChangeDlg.h"
#include "XConstantIM.h"


#define TIMER_SENDMUTRIXDATA         1
#define TIMERSPACE_SENDMUTRIXDATA    200

IMPLEMENT_DYNAMIC(XScreenMoveDlg, CDialogEx)

	XScreenMoveDlg::XScreenMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XScreenMoveDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InitDlg = FALSE;

	m_pScreenManage=NULL;

	m_pMutrixData=NULL;

	m_MutrixDataLen=0;

	m_SendDataIndex=0;

	m_Time=12;

	m_IsOneTime=FALSE;

	m_IsLastTime=FALSE;

	m_Pos=0;

	m_dReTime=0;

	m_UpdataTime=0;

	m_pScreen=NULL;
}

XScreenMoveDlg::~XScreenMoveDlg()
{
	ClearMutrixData();
}

void XScreenMoveDlg::ClearMutrixData()
{
	if(NULL!=m_pMutrixData)
	{
		delete []m_pMutrixData;

		m_pMutrixData=NULL;
	}
}

void XScreenMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MFONT, m_ComboBox_Font);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ComboBox_Type);
	DDX_Control(pDX, IDC_FCOLOR, m_FColor);
	DDX_Control(pDX, IDC_BKCOLOR, m_BKColor);
	DDX_Control(pDX, IDC_COMBO_LONG, m_ComboBox_Long);
	DDX_Control(pDX, IDC_COMBO_WIDTH, m_ComboBox_Width);
	DDX_Control(pDX, IDC_COMBO_BEGINX, m_ComboBox_BeginX);
	DDX_Control(pDX, IDC_COMBO_BEGINY, m_ComboBox_BeginY);
	DDX_Control(pDX, IDC_COMBO_CENTER2, m_ComboBox_Center);
}

BEGIN_MESSAGE_MAP(XScreenMoveDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SET, &XScreenMoveDlg::OnBtnSet)
	ON_BN_CLICKED(IDOK, &XScreenMoveDlg::OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &XScreenMoveDlg::OnBtnClose)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE,&XScreenMoveDlg::OnBtnChange)
	ON_BN_CLICKED(IDC_BUTTON_MOVECLOSE,&XScreenMoveDlg::OnBtnCencel)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_EN_CHANGE(IDC_EDIT_TEXTINFO, &XScreenMoveDlg::OnEnChangeEditText)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_BEGINX, &XScreenMoveDlg::OnSelchangeBeginX)
	ON_CBN_SELCHANGE(IDC_COMBO_LONG, &XScreenMoveDlg::OnSelchangeLong)
	ON_MESSAGE(MSG_UPDATESHOW,&XScreenMoveDlg::OnUpdataShowData)
END_MESSAGE_MAP()


void XScreenMoveDlg::SetDelegate(XDelegateScreenMoveDlg* p)
{
	m_pDelegate = p;
}

void XScreenMoveDlg::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

BOOL XScreenMoveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return FALSE;  
}

void XScreenMoveDlg::Init()
{
	CreateScreenMoveGrid();

	InitCombo();

	InitComboFont();

	InitShowData();

	InitProgress();

	AdjustPos();

	ReloadInterface();

	m_Grid.Init();

	GetWindowRect(&m_DlgMinRect);

	m_InitDlg=TRUE;

	gHandle=this->GetSafeHwnd();
}

void XScreenMoveDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("446"),_T("设置滚动画面")));

	GetDlgItem(IDC_BTN_SET)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("269"), _T("发送")));
	GetDlgItem(IDC_BTN_CLOSE)->SetWindowText(m_pDelegate->GetTranslationString(_T("529"), _T("关闭")));
	GetDlgItem(IDC_BUTTON_MOVECLOSE)->SetWindowText(m_pDelegate->GetTranslationString(_T("356"), _T("取消")));

	GetDlgItem(IDC_BUTTON_CHANGE)->SetWindowText(m_pDelegate->GetTranslationString(_T("603"),_T("更改")));

	GetDlgItem(IDC_STATIC_RATE)->SetWindowText(_T("0%"));

	GetDlgItem(IDC_STATIC_MOVEPARA)->SetWindowText(m_pDelegate->GetTranslationString(_T("449"), _T("滚动参数")));
	GetDlgItem(IDC_STATIC_TYPE)->SetWindowText(m_pDelegate->GetTranslationString(_T("396"), _T("样式"))+ _T(":"));
	GetDlgItem(IDC_STATIC_SPACE)->SetWindowText(m_pDelegate->GetTranslationString(_T("482"), _T("滚动间隔"))+ _T(":"));
	GetDlgItem(IDC_STATIC_SPEED2)->SetWindowText(m_pDelegate->GetTranslationString(_T("448"), _T("滚动速度"))+ _T(":"));
	GetDlgItem(IDC_STATIC_FCOLOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("260"), _T("文字颜色")) + _T(":"));
	GetDlgItem(IDC_STATIC_BCOLOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("397"), _T("背景颜色"))+ _T(":"));
	GetDlgItem(IDC_STATIC_WIDTH)->SetWindowText(m_pDelegate->GetTranslationString(_T("517"), _T("宽度")) + _T(":"));
	GetDlgItem(IDC_STATIC_HIGHT)->SetWindowText(m_pDelegate->GetTranslationString(_T("518"), _T("高度")) + _T(":"));
	GetDlgItem(IDC_STATIC_FONT)->SetWindowText(m_pDelegate->GetTranslationString(_T("266"), _T("字体类型")) + _T(":"));
	GetDlgItem(IDC_STATIC_FONTSIZE)->SetWindowText(m_pDelegate->GetTranslationString(_T("267"), _T("字体大小")) + _T(":"));

	GetDlgItem(IDC_STATIC_BEGINX)->SetWindowText(m_pDelegate->GetTranslationString(_T("470"), _T("起始坐标X"))+ _T(":"));
	GetDlgItem(IDC_STATIC_BEGINY)->SetWindowText(m_pDelegate->GetTranslationString(_T("471"), _T("起始坐标Y")) + _T(":"));
	GetDlgItem(IDC_STATIC_LONG)->SetWindowText(m_pDelegate->GetTranslationString(_T("472"), _T("区域长度")) + _T(":"));
	GetDlgItem(IDC_STATIC_BEGINH)->SetWindowText(m_pDelegate->GetTranslationString(_T("534"), _T("起始高度")) + _T(":"));

	GetDlgItem(IDC_STATIC_CENTER)->SetWindowText(m_pDelegate->GetTranslationString(_T("519"), _T("是否居中")) + _T(":"));
	GetDlgItem(IDC_STATIC_SENDSPACE)->SetWindowText(m_pDelegate->GetTranslationString(_T("532"), _T("发送间隔")) + _T(":"));
	GetDlgItem(IDC_STATIC_SHOWTEXT)->SetWindowText(m_pDelegate->GetTranslationString(_T("483"), _T("显示内容")) + _T(":"));
	GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText(m_pDelegate->GetTranslationString(_T("484"), _T("发送进度")) + _T(":"));

	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(m_pDelegate->GetTranslationString(_T("478"), _T("提示:从横向第几块屏幕开始")));
	GetDlgItem(IDC_STATIC_TIPS2)->SetWindowText(m_pDelegate->GetTranslationString(_T("479"), _T("提示:相对于屏幕顶部的高度")));
	GetDlgItem(IDC_STATIC_TIPS3)->SetWindowText(m_pDelegate->GetTranslationString(_T("480"), _T("提示:滚动区域长度占横向屏幕个数")));
	GetDlgItem(IDC_STATIC_TIPS4)->SetWindowText(m_pDelegate->GetTranslationString(_T("481"), _T("提示:字模所占横向屏幕个数，应大于等于区域长度")));
	GetDlgItem(IDC_STATIC_TIPS5)->SetWindowText(m_pDelegate->GetTranslationString(_T("485"), _T("提示:从纵向第几块屏幕开始")));
	GetDlgItem(IDC_STATIC_TIPS6)->SetWindowText(m_pDelegate->GetTranslationString(_T("486"), _T("提示:滚动区域以及字模的高度")));
	GetDlgItem(IDC_STATIC_TIPS8)->SetWindowText(m_pDelegate->GetTranslationString(_T("507"), _T("提示:相对于背景居中")));
	GetDlgItem(IDC_STATIC_TIPS9)->SetWindowText(m_pDelegate->GetTranslationString(_T("525"), _T("提示:文字大小范围为10-600")));
	GetDlgItem(IDC_STATIC_TIPS7)->SetWindowText(m_pDelegate->GetTranslationString(_T("530"), _T("提示:设置按钮用于设置全部参数，更改按钮用于发送完成后再更改个别参数，关闭按钮用于关闭滚动画面!")));
	GetDlgItem(IDC_STATIC_TIPS10)->SetWindowText(m_pDelegate->GetTranslationString(_T("531"), _T("提示:每次发送数据等待间隔，单位毫秒")));
}


LRESULT XScreenMoveDlg::OnUpdataShowData(WPARAM wParam,LPARAM lParam)
{
	CString szTemp = _T("");
	XScreenMoveInfo* pMoveInfo = m_pScreenManage->GetScreenMoveInfo();
	
	m_FColor.SetColor(pMoveInfo->GetColor());
	m_BKColor.SetColor(pMoveInfo->GetBkColor());

	szTemp.Format(_T("%d"), pMoveInfo->GetSpeed());
	GetDlgItem(IDC_EDIT_SPEED)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pMoveInfo->GetSpace());
	GetDlgItem(IDC_EDIT_SPACE)->SetWindowText(szTemp);

	m_ComboBox_Type.SetCurSel(pMoveInfo->GetType());
	m_ComboBox_BeginX.SetCurSel(pMoveInfo->GetComboShowBeginX());
	m_ComboBox_BeginY.SetCurSel(pMoveInfo->GetComboShowBeginY());

	szTemp.Format(_T("%d"), pMoveInfo->GetBeginH());
	GetDlgItem(IDC_EDIT_BEGINH)->SetWindowText(szTemp);

	return 0;
}

void XScreenMoveDlg::InitShowData()
{
	CString szTemp = _T("");

	XScreenMoveInfo* pMoveInfo = m_pScreenManage->GetScreenMoveInfo();

	m_ComboBox_Type.SetCurSel(pMoveInfo->GetType());
	m_ComboBox_BeginX.SetCurSel(pMoveInfo->GetComboShowBeginX());
	m_ComboBox_BeginY.SetCurSel(pMoveInfo->GetComboShowBeginY());
	m_ComboBox_Long.SetCurSel(pMoveInfo->GetComboShowLong());
	m_ComboBox_Width.SetCurSel(pMoveInfo->GetComboShowWidth());
	m_ComboBox_Center.SetCurSel(pMoveInfo->GetCenter());

	szTemp.Format(_T("%d"), pMoveInfo->GetSpeed());
	GetDlgItem(IDC_EDIT_SPEED)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pMoveInfo->GetSpace());
	GetDlgItem(IDC_EDIT_SPACE)->SetWindowText(szTemp);

	m_FColor.SetColor(pMoveInfo->GetColor());
	m_BKColor.SetColor(pMoveInfo->GetBkColor());

	m_ComboBox_Font.SetCurSel(m_ComboBox_Font.FindStringExact(-1, pMoveInfo->GetFont()));

	szTemp.Format(_T("%d"), pMoveInfo->GetFontSize());
	GetDlgItem(IDC_EDIT_FONTSIZE)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pMoveInfo->GetHight());
	GetDlgItem(IDC_EDIT_HIGHT)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pMoveInfo->GetBeginH());
	GetDlgItem(IDC_EDIT_BEGINH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pMoveInfo->GetSendSpace());
	GetDlgItem(IDC_EDIT_SENDSPACE)->SetWindowText(szTemp);

	GetDlgItem(IDC_EDIT_TEXTINFO)->SetWindowText(pMoveInfo->GetText());
}

void XScreenMoveDlg::InitCombo()
{
	//初始化样式
	//m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("243"), _T("1")));
	m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("242"), _T("2")));
	m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("398"), _T("3")));

	int nScreenHNum=m_pScreenManage->GetScreenCountH();
	int nScreenVNum=m_pScreenManage->GetScreenCountV();
	//初始化
	CString str=_T("");
	for(int i=1;i<=nScreenHNum;i++)
	{
		str.Format(_T("%d"),i);
		m_ComboBox_BeginX.AddString(str);
		m_ComboBox_Long.AddString(str);
	}

	for(int i=1;i<=16;i++)
	{
		str.Format(_T("%d"),i);
		m_ComboBox_Width.AddString(str);
	}

	m_ComboBox_BeginX.SetCurSel(0);
	m_ComboBox_Long.SetCurSel(0);
	m_ComboBox_Width.SetCurSel(0);

	for(int i=1;i<=nScreenVNum;i++)
	{
		str.Format(_T("%d"),i);
		m_ComboBox_BeginY.AddString(str);
	}
	m_ComboBox_BeginY.SetCurSel(0);

	m_ComboBox_Center.AddString(m_pDelegate->GetTranslationString(_T("462"), _T("否")));
	m_ComboBox_Center.AddString(m_pDelegate->GetTranslationString(_T("461"), _T("是")));

	m_ComboBox_Center.SetCurSel(0);
}

int CALLBACK EnumFontFamEx(ENUMLOGFONTEX *lpelfe,
	NEWTEXTMETRICEX *lpntme,
	DWORD FontType,
	LPARAM lParam)                                      
{
	XScreenMoveDlg *pDlg = (XScreenMoveDlg*)lParam;

	pDlg->AddFont(lpelfe->elfLogFont.lfFaceName);

	return 1;
}

void XScreenMoveDlg::InitComboFont()
{
	CClientDC dc(this);

	::EnumFontFamilies(dc.GetSafeHdc(), NULL, (FONTENUMPROC)EnumFontFamEx, (LPARAM)this);
}

void XScreenMoveDlg::AddFont(CString s)
{
	m_ComboBox_Font.AddString(s);

	m_ComboBox_Font.SetDroppedWidth(190);
}

void XScreenMoveDlg::CreateScreenMoveGrid()
{
	m_Grid.SetDelegate(this);
	m_Grid.SetScreenMoveInfo(m_pScreenManage->GetScreenMoveInfo());
	m_Grid.Create(WS_CHILD|WS_VISIBLE,CRect(0, 0, 0, 0),this,0);
	m_Grid.ShowWindow(SW_SHOW);
	m_Grid.UpdateWindow();
}

void XScreenMoveDlg::OnBtnSet()
{
	unsigned short nType=m_ComboBox_Type.GetCurSel();

	CMFCColorButton* pBtnColor=(CMFCColorButton*)GetDlgItem(IDC_FCOLOR);

	COLORREF color=pBtnColor->GetColor();

	CMFCColorButton* pBtnBkColor=(CMFCColorButton*)GetDlgItem(IDC_BKCOLOR);

	COLORREF Bkcolor=pBtnBkColor->GetColor();
	//*****************************************
	CString szFont=_T("");
	GetDlgItem(IDC_COMBO_MFONT)->GetWindowText(szFont);
	//*****************************************
	CString szFontSize=_T("");
	GetDlgItem(IDC_EDIT_FONTSIZE)->GetWindowText(szFontSize);
	szFontSize.Trim();
	if (_T("")==szFontSize)
	{
		m_pDelegate->MessageBoxFromKey(_T("288"), _T("文字大小不能为空,请输入!"), MB_OK);
		GetDlgItem(IDC_EDIT_FONTSIZE)->SetFocus();
		return;
	}

	int nFontSize=_ttoi(szFontSize);
	if (nFontSize<10)
	{
		m_pDelegate->MessageBoxFromKey(_T("524"), _T("请输入正确的文字大小,10~600!"), MB_OK);
		GetDlgItem(IDC_EDIT_FONTSIZE)->SetFocus();
		return;
	}
	//*****************************************
	CString szSPeed=_T("");
	GetDlgItem(IDC_EDIT_SPEED)->GetWindowText(szSPeed);
	szSPeed.Trim();
	if (_T("")==szSPeed)
	{
		m_pDelegate->MessageBoxFromKey(_T("474"), _T("滚动速度不能为空,请输入！"), MB_OK);
		GetDlgItem(IDC_EDIT_SPEED)->SetFocus();
		return;
	}
	int nSpeed=_ttoi(szSPeed);
	//*****************************************
	CString szSPace=_T("");
	GetDlgItem(IDC_EDIT_SPACE)->GetWindowText(szSPace);
	szSPace.Trim();
	if (_T("")==szSPace)
	{
		m_pDelegate->MessageBoxFromKey(_T("475"), _T("滚动间隔不能为空,请输入！"), MB_OK);
		GetDlgItem(IDC_EDIT_SPACE)->SetFocus();
		return;
	}
	int nSpace=_ttoi(szSPace);
	if (nSpace<=0)
	{
		m_pDelegate->MessageBoxFromKey(_T("537"), _T("滚动间隔大于等于0，请重新输入!"), MB_OK);
		GetDlgItem(IDC_EDIT_SPACE)->SetFocus();
		return;
	}
	//*****************************************

	CString szSendSPace=_T("");
	GetDlgItem(IDC_EDIT_SENDSPACE)->GetWindowText(szSendSPace);
	szSPace.Trim();
	if (_T("")==szSendSPace)
	{
		m_pDelegate->MessageBoxFromKey(_T("533"), _T("发送间隔不能为空,请输入！"), MB_OK);
		GetDlgItem(IDC_EDIT_SENDSPACE)->SetFocus();
		return;
	}
	int nSendSpace=_ttoi(szSendSPace);

	//*****************************************
	CString nSelectStr=_T("");
	int nComboBeginX=m_ComboBox_BeginX.GetCurSel();
	int nComboBeginY=m_ComboBox_BeginY.GetCurSel();
	int nComboLong=m_ComboBox_Long.GetCurSel();
	int nComboWidth=m_ComboBox_Width.GetCurSel();

	m_ComboBox_BeginX.GetLBText(nComboBeginX,nSelectStr);
	int nComboBoxBeginX=_ttoi(nSelectStr);

	m_ComboBox_BeginY.GetLBText(nComboBeginY,nSelectStr);
	int nComboBoxBeginY=_ttoi(nSelectStr);

	m_ComboBox_Long.GetLBText(nComboLong,nSelectStr);
	int nComboBoxLong=_ttoi(nSelectStr);

	m_ComboBox_Width.GetLBText(nComboWidth,nSelectStr);
	int nComboBoxWidth=_ttoi(nSelectStr);

	int nScreenCountH=m_pScreenManage->GetScreenCountH();
	//屏幕序号
	int nBeginIndex=m_pScreenManage->GetBeginIndex();

	int nScreenIndex=0;
	if(nComboBoxBeginY==1)
	{
		nScreenIndex=nComboBoxBeginX+(nBeginIndex-1);
	}
	else
	{
		nScreenIndex=nComboBoxBeginX+(nBeginIndex-1)+(nComboBoxBeginY-1)*nScreenCountH;
	}
    //根据序号获取屏幕
	XScreen* pScreen=GetScreenByIndex(nScreenIndex);
	if(NULL==pScreen)
	{
		return;
	}
	else
	{
		m_pScreen=pScreen;
	}


	int nScreenResulationH=0;
	int nScreenResulationV=0;
	if(pScreen->GetReScreenHdpi()!=0
		&&pScreen->GetReScreenVdpi()!=0)
	{
		nScreenResulationH=pScreen->GetReScreenHdpi();
		nScreenResulationV=pScreen->GetReScreenVdpi();
	}
	else
	{
		nScreenResulationH=pScreen->GetScreenHdpi();
		nScreenResulationV=pScreen->GetScreenVdpi();
	}

	//*****************************************
	CString szBeginH=_T("");
	GetDlgItem(IDC_EDIT_BEGINH)->GetWindowText(szBeginH);
	szBeginH.Trim();
	if (_T("")==szBeginH)
	{
		m_pDelegate->MessageBoxFromKey(_T("487"), _T("起始高度不能为空,请输入！"), MB_OK);
		GetDlgItem(IDC_EDIT_BEGINH)->SetFocus();
		return;
	}
	int nBeginH=_ttoi(szBeginH);
	if(nBeginH<0||nBeginH>nScreenResulationV)
	{
		m_pDelegate->MessageBoxFromKey(_T("488"), _T("起始高度不能滚动区域超过所占屏幕分辨率！"), MB_OK);
		GetDlgItem(IDC_EDIT_BEGINH)->SetFocus();
		return;
	}
	//*****************************************
	int nBeginX=(nComboBoxBeginX-1)*nScreenResulationH;
	if ((nBeginX%8)!=0)
	{
		nBeginX=(nBeginX/8+1)*8;
	}

	int nBeginY=0;
	if(nComboBoxBeginY==1)
	{
		nBeginY=nBeginH;
	}
	else
	{
		nBeginY=(nComboBoxBeginY-1)*nScreenResulationV+nBeginH;
	}
	//*****************************************
	int nWidth=nComboBoxWidth*nScreenResulationH;

	if ((nWidth%8)!=0)
	{
		nWidth=(nWidth/8+1)*8;	
	}

	int nLong=nComboBoxLong*nScreenResulationH;
	//*****************************************
	CString szHeight=_T("");
	GetDlgItem(IDC_EDIT_HIGHT)->GetWindowText(szHeight);
	szHeight.Trim();
	if (_T("")==szHeight)
	{
		m_pDelegate->MessageBoxFromKey(_T("302"), _T("高度不能为空,请输入!"), MB_OK);
		GetDlgItem(IDC_EDIT_HIGHT)->SetFocus();
		return;
	}
	int nHeight=_ttoi(szHeight);

	//*****************************************
	int nMaxArea=20736000;

	if ((nWidth*nHeight)>nMaxArea)
	{
		nHeight=nMaxArea/nWidth;

		m_pDelegate->MessageBoxFromKey(_T("290"), _T("区域大小超出最大区域将自动调整区域!"), MB_OK);

		CString szTemp;
		szTemp.Format(_T("%d"), nHeight);

		GetDlgItem(IDC_EDIT_HIGHT)->SetWindowText(szTemp);
	}
    //*****************************************
	if (nFontSize>nHeight)
	{
		nFontSize=nHeight;

		CString szTemp;
		szTemp.Format(_T("%d"), nFontSize);

		GetDlgItem(IDC_EDIT_FONTSIZE)->SetWindowText(szTemp);
	}
	//*****************************************
	CString szText;
	GetDlgItem(IDC_EDIT_TEXTINFO)->GetWindowText(szText);
	//*****************************************
	unsigned int nCenter=m_ComboBox_Center.GetCurSel();
	//*****************************************
	//内容区域
	RECTF rect((Gdiplus::REAL)nBeginX,(Gdiplus::REAL)nBeginY,(Gdiplus::REAL)nWidth,(Gdiplus::REAL)nHeight);
	//显示区域
	RECTF rectInfo((Gdiplus::REAL)nBeginX,(Gdiplus::REAL)nBeginY,(Gdiplus::REAL)nLong,(Gdiplus::REAL)nHeight);
	//*****************************************
	XScreenMoveInfo* pInfo=m_pScreenManage->GetScreenMoveInfo();
	pInfo->SetType(nType);
	pInfo->SetSpeed(nSpeed);
	pInfo->SetSpace(nSpace);
	pInfo->SetColor(color);
	pInfo->SetBkColor(Bkcolor);
	pInfo->SetFont(szFont);
	pInfo->SetFontSize(nFontSize);
	pInfo->SetWidth(nWidth);
	pInfo->SetHight(nHeight);
	pInfo->SetText(szText);
	pInfo->SetBeginX(nBeginX);
	pInfo->SetBeginY(nBeginY);
	pInfo->SetLong(nLong);
	pInfo->SetBeginH(nBeginH);
	pInfo->SetCenter(nCenter);
	pInfo->SetSendSpace(nSendSpace);

	pInfo->SetScreenResulationH(nScreenResulationH);
	pInfo->SetScreenResulationV(nScreenResulationV);

	//内容区域
	pInfo->SetAreaRect(rect);
	//显示区域
	pInfo->SetInfoRect(rectInfo);

	pInfo->SetComboBeginX(nComboBoxBeginX);
	pInfo->SetComboBeginY(nComboBoxBeginY);
	pInfo->SetComboLong(nComboBoxLong);
	pInfo->SetComboWidth(nComboBoxWidth);

	pInfo->SetComboShowBeginX(nComboBeginX);
	pInfo->SetComboShowBeginY(nComboBeginY);
	pInfo->SetComboShowLong(nComboLong);
	pInfo->SetComboShowWidth(nComboWidth);

	//////////////////////////////////////////////////////////////////////////
	//判断是否为双路拼接卡
	//显示区域
	RECTF rectInfo2=pInfo->GetInfoRect();
	RECTF rectArea2=pInfo->GetAreaRect();
	RECTF rectScreen=pScreen->GetRect();

	float nX=1.0*rectInfo2.X*rectScreen.Width/nScreenResulationH;
	float nY=1.0*rectInfo2.Y*rectScreen.Height/nScreenResulationV;
	float nWidth2=1.0*rectInfo2.Width*rectScreen.Width/nScreenResulationH;
	float nHeight2=1.0*rectInfo2.Height*rectScreen.Height/nScreenResulationV;

	RECTF rectReal(nX,nY,nWidth2,nHeight2);

	VEC_SCREEN VecScreen;
	VEC_SCREEN& VecScr=m_pScreenManage->GetVecScreen();
	for(VEC_SCREEN::iterator iter=VecScr.begin();iter!=VecScr.end();++iter)
	{
		XScreen* pScreen=*iter;
		RECTF rectF=pScreen->GetRect();

		if(rectF.Intersect(rectReal))
		{
			VecScreen.push_back(pScreen);
		}
	}

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nBoardIndex=pScreen->GetBoardIndex();
		MAP_BOARDTYPE& MapBoardType=m_pScreenManage->GetMapBoardType();
		MAP_BOARDTYPE::iterator iter1=MapBoardType.find(nBoardIndex);
		if(iter1!=MapBoardType.end())
		{
			int nType=iter1->second;
			if(nType==BOARDTYPE_MULTISPLICE)
			{
				m_pDelegate->MessageBoxFromKey(_T("756"), _T("双路拼接卡不支持该功能！"), MB_OK);
				return;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	pInfo->ClearMutrixData();
	pInfo->Init();

	SetScreenMoveMutrix();
}

void XScreenMoveDlg::SetScreenMoveMutrix()
{
	CClientDC dc(this);

	BOOL bExceed = FALSE;

	BOOL bSetOSDMutrix = HandleMutrix::SetScreenMoveMutrix(dc, m_pScreenManage->GetScreenMoveInfo(), bExceed);

	m_Grid.Reset();

	if(!bSetOSDMutrix)
	{
		m_pDelegate->MessageBoxFromKey(_T("291"), _T("获取文字字模数据失败,请重新尝试!"), MB_OK);
	}
	else if(bExceed)
	{
		m_pDelegate->MessageBoxFromKey(_T("292"), _T("文字超出OSD区域，文字截取显示!"), MB_OK);
	}
}

void XScreenMoveDlg::UpdateTime()
{
	m_UpdataTime=GetTickCount();
}

void XScreenMoveDlg::OnBtnChange()
{
	OnBtnSet();

	XChangeMoveScreenDlg dlg;

	dlg.SetDelegate(m_pScreenManage);

	dlg.SetScreenManage(m_pScreenManage);

	if(IDOK==dlg.DoModal())
	{
		OnBtnSet();

		XSendDataScreenManage::AddSendDataOfScreenMoveOff(m_pScreenManage);

		XSendDataScreenManage::AddSendDataOfScreenMoveZero(m_pScreenManage);

		XSendDataScreenManage::SendDataOfScreenMove(m_pScreenManage,m_pScreen);

		//XSendDataScreenManage::AddSendDataOfChangeMoveParamater(m_pScreenManage);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);
	}
}

void XScreenMoveDlg::OnBtnClose()
{
	XSendDataScreenManage::AddSendDataOfScreenMoveOff(m_pScreenManage);
}

void XScreenMoveDlg::OnBtnSend()
{
	m_Pos=0;

	m_SendDataIndex=0;

	ResetProgress();

	InitSendData();

	XSendDataScreenManage::AddSendDataOfScreenMoveOff(m_pScreenManage);

	if(m_pScreen==NULL)
	{
		return;
	}

	XSendDataScreenManage::AddSendDataOfScreenMoveZero(m_pScreenManage);

	Sleep(500);

	CButton* pBtn=(CButton*)GetDlgItem(IDOK);
	pBtn->EnableWindow(FALSE);

	SendData(m_SendDataIndex);
}

void XScreenMoveDlg::InitSendData()
{
	XScreenMoveInfo* pInfo=m_pScreenManage->GetScreenMoveInfo();
	unsigned int nDataLen=pInfo->GetMutrixDataLen();
	char* pData=pInfo->GetMutrixData();

	int nPreDataLen=4*1024;
	if(nDataLen%nPreDataLen==0)
	{
		m_MutrixDataLen=nDataLen;
		m_pMutrixData=new unsigned char[m_MutrixDataLen];
		memset(m_pMutrixData,0,m_MutrixDataLen);
		memcpy(m_pMutrixData,pData,nDataLen);
	}
	else
	{
		m_MutrixDataLen=nPreDataLen*(nDataLen/nPreDataLen+1);
		m_pMutrixData=new unsigned char[m_MutrixDataLen];
		memset(m_pMutrixData,0,m_MutrixDataLen);
		memcpy(m_pMutrixData,pData,nDataLen);
	}

	TRACE(_T("m_MutrixDataLen=%d\n"),m_MutrixDataLen);
}

void XScreenMoveDlg::InitProgress()
{
	CString szRate;

	szRate.Format(_T("%d"),0);

	SetDlgItemText(IDC_STATIC_RATE,szRate+_T("%"));
}

void XScreenMoveDlg::SendData(int& nSendDataIndex)
{
	SendMutrixData(nSendDataIndex);

	if(m_IsOneTime)
	{
		m_IsOneTime=FALSE;

		XSendDataScreenManage::SendDataOfScreenMove(m_pScreenManage,m_pScreen);

		Sleep(500);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);

		m_pDelegate->MessageBoxFromKey(_T("469"),_T("发送完成！"),MB_OK);

		return;
	}
	else
	{
		BeginSendTimer();
	}
}

void XScreenMoveDlg::SendMutrixData(int nSendDataIndex)
{
	//TRACE("m_SendDataIndex=%d\n",m_SendDataIndex);

	//每次最大发送1024
	int nMaxSendData=1024;

	//最大发送次数12次
	int nPreSendData=nMaxSendData*m_Time;

	//数据每次偏移
	unsigned char* pTempData=m_pMutrixData;
	pTempData+=nSendDataIndex*nPreSendData;

	//减去偏移剩余数据长度
	int nLeftDataLen=m_MutrixDataLen-nSendDataIndex*nPreSendData;

	//TRACE("nLeftDataLen=%d\n",nLeftDataLen);

	//是否小于12KB
	int nIndex=nLeftDataLen/nPreSendData;

	//循环次数
	int nTime=0;

	//第一次并且小于12KB
	if(nSendDataIndex==0&&nIndex==0)
	{
		nTime=m_MutrixDataLen/nMaxSendData;

		//TRACE("nTime1=%d\n",nTime);

		m_IsOneTime=TRUE;

		//TRACE(_T("m_IsOneTime=%d\n"),1);
	}
	else if(nSendDataIndex>=0)
	{	
		int n=nLeftDataLen/nMaxSendData;

		//TRACE("n=%d\n",n);

		if(n>m_Time)
		{
			nTime=m_Time;

			//TRACE("nTime2=%d\n",nTime);
		}
		else
		{
			//最后一次执行
			m_IsLastTime=TRUE;

			nTime=n;

			StopSendTimer();

			//TRACE("nTime3=%d\n",nTime);
		}	
	}

	//每次循环的起始地址
	for(int i=0;i<nTime;i++)
	{	
		if(IsNULL((char*)pTempData,nMaxSendData))
		{
			int nLen=5;
			unsigned char* pData=new unsigned char[nLen];
			pData[0]=0x03;
			memcpy(pData+1,&m_Pos,4);
			XSendDataScreenManage::SendDataOfScreenMoveData(m_pScreenManage,pData,nLen);
			delete []pData;
		}
		else
		{
			int nLen=5+nMaxSendData;
			unsigned char* pData=new unsigned char[nLen];
			pData[0]=0x03;
			memcpy(pData+1,&m_Pos,4);
			memcpy(pData+5,pTempData,nMaxSendData);
			XSendDataScreenManage::SendDataOfScreenMoveData(m_pScreenManage,pData,nLen);
			delete []pData;
		}

		pTempData+=nMaxSendData;
		m_Pos+=nMaxSendData;

		UpdataProgress();
	}

	if(!m_IsOneTime)
	{
		XSendDataScreenManage::SendDataOfScreenMoveAsk(m_pScreenManage);

		UpdateTime();
	}

	if(m_IsLastTime)
	{
		XSendDataScreenManage::SendDataOfScreenMove(m_pScreenManage,m_pScreen);

		Sleep(500);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);

		XSendDataScreenManage::AddSendDataOfScreenMoveOn(m_pScreenManage);

		m_pDelegate->MessageBoxFromKey(_T("469"),_T("发送完成！"),MB_OK);

		m_IsLastTime=FALSE;
	}
}

BOOL XScreenMoveDlg::IsNULL(char* pData,int& nLen)
{
	for(int i=0;i<nLen;i++)
	{
		if(pData[i]!=0)
		{
			return FALSE;
		}
	}
	return TRUE;
}


void XScreenMoveDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMER_SENDMUTRIXDATA:
		{
			UpdataSendData();
		}
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void XScreenMoveDlg::SetReTime(DWORD& dWTime)
{
	m_dReTime=dWTime;
}

void XScreenMoveDlg::UpdataSendData()
{
	DWORD dNowTime=GetTickCount();

	if(abs((long)dNowTime-(long)m_dReTime)<4000)
	{
		XScreenMoveInfo* pInfo=m_pScreenManage->GetScreenMoveInfo();

		int nSendSpace=pInfo->GetSendSpace();

		if(nSendSpace!=0)
		{
			Sleep(nSendSpace);
		}

		SendMutrixData(++m_SendDataIndex);

		m_dReTime=0;
	}
	else
	{
		if(abs((long)dNowTime-(long)m_UpdataTime)>5000)
		{
			StopSendTimer();

			CButton* pBtn=(CButton*)GetDlgItem(IDOK);

			pBtn->EnableWindow(TRUE);

			m_pDelegate->MessageBoxFromKey(_T("493"),_T("发送失败！"),MB_OK);

			ResetProgress();

			return;
		}
	}
}

void XScreenMoveDlg::ResetProgress()
{
	CString szRate;

	szRate.Format(_T("%d"),0);

	SetDlgItemText(IDC_STATIC_RATE,szRate+_T("%"));
}

void XScreenMoveDlg::UpdataProgress()
{
	unsigned int nProgressPos=m_Pos;

	//TRACE("nProgressPos=%d\n",nProgressPos);

	//****************
	int nRate=nProgressPos*100/m_MutrixDataLen;

	CString szRate;

	szRate.Format(_T("%d"),nRate);

	SetDlgItemText(IDC_STATIC_RATE,szRate+_T("%"));

	if(nRate==100)
	{
		CButton* pBtn=(CButton*)GetDlgItem(IDOK);

		pBtn->EnableWindow(TRUE);
	}
}

void XScreenMoveDlg::OnSelchangeBeginX()
{
	m_ComboBox_Long.ResetContent();

	int nScreenHNum=m_pScreenManage->GetScreenCountH();

	CString nSelectStr=_T("");
	m_ComboBox_BeginX.GetLBText(m_ComboBox_BeginX.GetCurSel(),nSelectStr);
	int nComboBeginX=_ttoi(nSelectStr);

	for(int i=1;i<=nScreenHNum-nComboBeginX+1;i++)
	{
		CString str;
		str.Format(_T("%d"),i);

		m_ComboBox_Long.AddString(str);
	}
	m_ComboBox_Long.SetCurSel(0);
}

void XScreenMoveDlg::OnSelchangeLong()
{
	m_ComboBox_Width.ResetContent();

	CString nSelectStr=_T("");
	m_ComboBox_BeginX.GetLBText(m_ComboBox_BeginX.GetCurSel(),nSelectStr);
	int nComboBeginX=_ttoi(nSelectStr);

	m_ComboBox_Long.GetLBText(m_ComboBox_Long.GetCurSel(),nSelectStr);
	int nComboLong=_ttoi(nSelectStr);

	for(int i=nComboLong;i<=16;i++)
	{
		CString str;
		str.Format(_T("%d"),i);

		m_ComboBox_Width.AddString(str);
	}
	m_ComboBox_Width.SetCurSel(0);
}

void XScreenMoveDlg::BeginSendTimer()
{
	SetTimer(TIMER_SENDMUTRIXDATA,TIMERSPACE_SENDMUTRIXDATA,NULL);
}

void XScreenMoveDlg::StopSendTimer()
{
	KillTimer(TIMER_SENDMUTRIXDATA);
}

void XScreenMoveDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (m_InitDlg)
	{
		lpMMI->ptMinTrackSize.x = m_DlgMinRect.Width();

		lpMMI->ptMinTrackSize.y = m_DlgMinRect.Height();
	}

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void XScreenMoveDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_InitDlg)
	{
		AdjustPos();
	}
}

void XScreenMoveDlg::AdjustPos()
{
	CRect rect;
	GetClientRect(&rect);
	//********************************
	CRect rtParameter;
	GetDlgItem(IDC_STATIC_MOVEPARA)->GetWindowRect(&rtParameter);
	ScreenToClient(&rtParameter);
	rtParameter.right = rect.right - rtParameter.left;
	GetDlgItem(IDC_STATIC_MOVEPARA)->MoveWindow(&rtParameter);
	//********************************
	CRect rtEditText;
	GetDlgItem(IDC_EDIT_TEXTINFO)->GetWindowRect(&rtEditText);
	ScreenToClient(&rtEditText);
	int nTextWidth=rtEditText.Width();
	rtEditText.right=rect.right - 40;
	GetDlgItem(IDC_EDIT_TEXTINFO)->MoveWindow(&rtEditText);
	//********************************
	//CRect rtRate;
	//GetDlgItem(IDC_STATIC_RATE)->GetWindowRect(&rtRate);
	//ScreenToClient(&rtRate);
	//int rtRateWidth=rtRate.Width();
	//rtRate.left=rtEditText.right-rtRateWidth;

	//rtRate.right=rtRate.left+rtRateWidth;
	//GetDlgItem(IDC_STATIC_RATE)->MoveWindow(&rtRate);
	////********************************
	//CRect rtProcess;
	//GetDlgItem(IDC_PROGRESS_SEND)->GetWindowRect(&rtProcess);
	//ScreenToClient(&rtProcess);
	//rtProcess.left=rtEditText.left;
	//rtProcess.right=rtEditText.right-rtRate.Width()-5;
	//GetDlgItem(IDC_PROGRESS_SEND)->MoveWindow(&rtProcess);
	//********************************
	//CRect rtBtnSet;
	//GetDlgItem(IDC_BTN_SET)->GetWindowRect(&rtBtnSet);
	//ScreenToClient(&rtBtnSet);
	//int nWidth=rtBtnSet.Width();
	//rtBtnSet.left=rtEditText.left;
	//rtBtnSet.right=rtBtnSet.left+nWidth;
	//GetDlgItem(IDC_BTN_SET)->MoveWindow(&rtBtnSet);

	//CRect rtBtnSend;
	//GetDlgItem(IDOK)->GetWindowRect(&rtBtnSend);
	//ScreenToClient(&rtBtnSend);
	//rtBtnSend.left=rtEditText.right-nTextWidth/2-nWidth/2;
	//rtBtnSend.right=rtBtnSend.left+nWidth;
	//GetDlgItem(IDOK)->MoveWindow(&rtBtnSend);

	//CRect rtBtnCancel;
	//GetDlgItem(IDCANCEL)->GetWindowRect(&rtBtnCancel);
	//ScreenToClient(&rtBtnCancel);
	//rtBtnCancel.left=rtEditText.right-nWidth;
	//rtBtnCancel.right=rtBtnCancel.left+nWidth;
	//GetDlgItem(IDCANCEL)->MoveWindow(&rtBtnCancel);

	CRect rtTips;
	GetDlgItem(IDC_STATIC_TIPS105)->GetWindowRect(&rtTips);
	ScreenToClient(&rtTips);
	//********************************
	CRect rtStaticGrid = rtParameter;
	rtStaticGrid.top = rtParameter.bottom + rtParameter.left;
	//rtStaticGrid.bottom = rect.bottom - rtParameter.left;
	rtStaticGrid.bottom=rtTips.top-5;
	GetDlgItem(IDC_STATIC_MGRID)->MoveWindow(&rtStaticGrid);
	//********************************
	CRect rtGrid = rtStaticGrid;
	rtGrid.InflateRect(-10, -10);
	m_Grid.MoveWindow(&rtGrid);
	m_Grid.ResetByDlgSizeChange();
	//********************************
	Invalidate();
}

XScreen* XScreenMoveDlg::GetScreenByIndex(int nIndex)
{
	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nScreenIndex=pScreen->GetIndex();

		if(nScreenIndex==nIndex)
		{
			return pScreen;
		}
	}
	return NULL;
}

void XScreenMoveDlg::OnEnChangeEditText()
{
	XScreenMoveInfo* pMoveInfo = m_pScreenManage->GetScreenMoveInfo();

	CString szText;
	GetDlgItem(IDC_EDIT_TEXTINFO)->GetWindowText(szText);

	if (szText == pMoveInfo->GetText())
	{
		return;
	}

	pMoveInfo->SetText(szText);

	pMoveInfo->ClearMutrixData();

	pMoveInfo->InitMutrixData();

	SetScreenMoveMutrix();
}

void XScreenMoveDlg::OnBtnCencel()
{
	CDialogEx::OnCancel();
}