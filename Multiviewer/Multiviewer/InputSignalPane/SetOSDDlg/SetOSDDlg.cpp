// EditExpandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetOSDDlg.h"
#include "afxdialogex.h"
#include "XDelegateSetOSDDlg.h"
#include "XInputSignal.h"
#include "XSendDataInputSignal.h"
#include "HandleMutrix.h"

// CSetOSDDlg 对话框

#define NTYPEZERO 0
#define NTYPEONE 1

IMPLEMENT_DYNAMIC(CSetOSDDlg, CDialogEx)

CSetOSDDlg::CSetOSDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetOSDDlg::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal = NULL;

	m_InputSignalName = _T("");

	m_InputSignalPane = NULL;

	m_InitDlg = FALSE;
}

CSetOSDDlg::~CSetOSDDlg()
{

}

void CSetOSDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR, m_Color);
	DDX_Control(pDX, IDC_COMBO_FONT, m_ComboBox_Font);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ComboBox_Type);
	DDX_Control(pDX, IDC_COLOR_BK, m_Color_Bk);
	DDX_Control(pDX, IDC_COMBO_CENTER, m_ComboBox_Center);
}


BEGIN_MESSAGE_MAP(CSetOSDDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetOSDDlg::OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSetOSDDlg::OnBtnSend)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CSetOSDDlg::OnEnChangeEditText)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CSetOSDDlg 消息处理程序

void CSetOSDDlg::SetDelegate(XDelegateSetOSDDlg* p)
{
	m_pDelegate = p;
}

void CSetOSDDlg::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void CSetOSDDlg::SetInputSignalName(CString s)
{
	m_InputSignalName = s;
}

void CSetOSDDlg::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

BOOL CSetOSDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateOSDGrid();

	InitComboBoxType();

	InitComboBoxFont();

	InitShowData();

	ReloadInterface();

	AdjustPos();

	m_Grid.Init();

	GetWindowRect(&m_DlgMinRect);

	m_InitDlg = TRUE;

	return FALSE;  
}

int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe,
	NEWTEXTMETRICEX *lpntme,
	DWORD FontType,
	LPARAM lParam)                                      
{
	CSetOSDDlg *pDlg = (CSetOSDDlg*)lParam;

	pDlg->AddFont(lpelfe->elfLogFont.lfFaceName);

	return 1;
}

void CSetOSDDlg::AddFont(CString s)
{
	m_ComboBox_Font.AddString(s);

	m_ComboBox_Font.SetDroppedWidth(190);
}

void CSetOSDDlg::InitComboBoxFont()
{
	CClientDC dc(this);

	::EnumFontFamilies(dc.GetSafeHdc(), NULL, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)this);
}

void CSetOSDDlg::InitComboBoxType()
{
	m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("243"), _T("1")));
	m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("242"), _T("2")));
	m_ComboBox_Type.AddString(m_pDelegate->GetTranslationString(_T("398"), _T("3")));


	m_ComboBox_Center.AddString(m_pDelegate->GetTranslationString(_T("462"), _T("否")));
	m_ComboBox_Center.AddString(m_pDelegate->GetTranslationString(_T("461"), _T("是")));
	
	m_ComboBox_Center.SetCurSel(0);
}

void CSetOSDDlg::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("258"), _T("设置OSD")) + _T(" - ") + m_InputSignalName);

	GetDlgItem(IDC_BTN_SET)->SetWindowText(m_pDelegate->GetTranslationString(_T("268"), _T("设置")));
	GetDlgItem(IDC_BTN_SEND)->SetWindowText(m_pDelegate->GetTranslationString(_T("269"), _T("发送")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));

	GetDlgItem(IDC_STATIC_X)->SetWindowText(m_pDelegate->GetTranslationString(_T("210"), _T("左上角X")) + _T(":"));
	GetDlgItem(IDC_STATIC_Y)->SetWindowText(m_pDelegate->GetTranslationString(_T("211"), _T("左上角Y")) + _T(":"));
	GetDlgItem(IDC_STATIC_NOTICEWIDTH)->SetWindowText(m_pDelegate->GetTranslationString(_T("315"), _T("提示:宽度为8的倍数")));
	GetDlgItem(IDC_STATIC_WIDTH)->SetWindowText(m_pDelegate->GetTranslationString(_T("295"), _T("宽度")) + _T(":"));
	GetDlgItem(IDC_STATIC_HEIGHT)->SetWindowText(m_pDelegate->GetTranslationString(_T("296"), _T("高度")) + _T(":"));
	GetDlgItem(IDC_STATIC_OSDPARAMETER)->SetWindowText(m_pDelegate->GetTranslationString(_T("259"), _T("OSD参数")));
	GetDlgItem(IDC_STATIC_COLOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("260"), _T("文字颜色")) + _T(":"));
	GetDlgItem(IDC_STATIC_FONT)->SetWindowText(m_pDelegate->GetTranslationString(_T("266"), _T("文字字体")) + _T(":"));
	GetDlgItem(IDC_STATIC_TEXTSIZE)->SetWindowText(m_pDelegate->GetTranslationString(_T("267"), _T("文字大小")) + _T(":"));
	GetDlgItem(IDC_STATIC_TYPE)->SetWindowText(m_pDelegate->GetTranslationString(_T("396"), _T("样式"))+ _T(":"));
	GetDlgItem(IDC_STATIC_CENTER)->SetWindowText(m_pDelegate->GetTranslationString(_T("513"), _T("居中"))+ _T(":"));
	GetDlgItem(IDC_STATIC_BKCOLOR)->SetWindowText(m_pDelegate->GetTranslationString(_T("397"), _T("背景颜色"))+ _T(":"));
	GetDlgItem(IDC_STATIC_TEXTINFO)->SetWindowText(m_pDelegate->GetTranslationString(_T("508"), _T("显示内容"))+ _T(":"));

	GetDlgItem(IDC_STATIC_TIPS5)->SetWindowText(m_pDelegate->GetTranslationString(_T("507"), _T("提示:相对于背景居中")));
	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(m_pDelegate->GetTranslationString(_T("509"), _T("提示:文字大小范围为10-200")));
	GetDlgItem(IDC_STATIC_TIPS2)->SetWindowText(m_pDelegate->GetTranslationString(_T("510"), _T("提示:左上角X范围为1-1920")));
	GetDlgItem(IDC_STATIC_TIPS3)->SetWindowText(m_pDelegate->GetTranslationString(_T("511"), _T("提示:左上角Y范围为1-1200")));
	GetDlgItem(IDC_STATIC_TIPS4)->SetWindowText(m_pDelegate->GetTranslationString(_T("512"), _T("提示:宽度不能超过255")));
}

void CSetOSDDlg::InitShowData()
{
	CString szTemp = _T("");

	XOSDInfo* pInfo = m_InputSignal->GetOSDInfo();

	szTemp.Format(_T("%d"), pInfo->GetX());
	GetDlgItem(IDC_EDIT_X)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetY());
	GetDlgItem(IDC_EDIT_Y)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetWidth());
	GetDlgItem(IDC_EDIT_WIDTH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHeight());
	GetDlgItem(IDC_EDIT_HEIGHT)->SetWindowText(szTemp);

	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(pInfo->GetText());

	m_Color.SetColor(pInfo->GetColor());
	m_Color_Bk.SetColor(pInfo->GetBkColor());

	m_ComboBox_Font.SetCurSel(m_ComboBox_Font.FindStringExact(-1, pInfo->GetFont()));
	m_ComboBox_Type.SetCurSel(pInfo->GetType());
	m_ComboBox_Center.SetCurSel(pInfo->GetCenterType());

	szTemp.Format(_T("%d"), pInfo->GetTextSize());
	GetDlgItem(IDC_EDIT_TEXTSIZE)->SetWindowText(szTemp);
}

void CSetOSDDlg::CreateOSDGrid()
{
	m_Grid.SetDelegate(this);
	m_Grid.SetOSDInfo(m_InputSignal->GetOSDInfo());
	m_Grid.Create(WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), this, 0);
	m_Grid.ShowWindow(SW_SHOW);
	m_Grid.UpdateWindow();
}

void CSetOSDDlg::OnBtnSet()
{
	CMFCColorButton* pBtnColor = (CMFCColorButton*)GetDlgItem(IDC_COLOR);

	COLORREF color = pBtnColor->GetColor();

	CMFCColorButton* pBtnBkColor = (CMFCColorButton*)GetDlgItem(IDC_COLOR_BK);

	COLORREF Bkcolor = pBtnBkColor->GetColor();
	//////////////////////////////////////////////////////////////////////////
	int nType=m_ComboBox_Type.GetCurSel();

	int nCenterType=m_ComboBox_Center.GetCurSel();
	////////////////////////////////////////////////////////
	CString szFont = _T("");
	GetDlgItem(IDC_COMBO_FONT)->GetWindowText(szFont);
	//////////////////////////////////////////////////////
	CString szTextSize = _T("");
	GetDlgItem(IDC_EDIT_TEXTSIZE)->GetWindowText(szTextSize);
	szTextSize.Trim();
	if (_T("") == szTextSize)
	{
		m_pDelegate->MessageBoxFromKey(_T("288"), _T("文字大小不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_TEXTSIZE)->SetFocus();

		return;
	}

	int nTextSize = _ttoi(szTextSize);
	if (nTextSize < 10 || nTextSize > 200)
	{
		m_pDelegate->MessageBoxFromKey(_T("289"), _T("请输入正确的文字大小,10-200!"), MB_OK);

		GetDlgItem(IDC_EDIT_TEXTSIZE)->SetFocus();

		return;
	}
	//////////////////////////////////////////////////////
	CString szX = _T("");
	GetDlgItem(IDC_EDIT_X)->GetWindowText(szX);
	szX.Trim();
	if (_T("") == szX)
	{
		m_pDelegate->MessageBoxFromKey(_T("299"), _T("X不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_X)->SetFocus();

		return;
	}

	int nX = _ttoi(szX);
	if(nX <= 0 || nX > 1920)
	{
		m_pDelegate->MessageBoxFromKey(_T("297"), _T("请输入正确的X,1-1920!"), MB_OK);

		if(nX<=0)
		{
			CString szTemp = _T("");

			szTemp.Format(_T("%d"), 1);

			GetDlgItem(IDC_EDIT_X)->SetWindowText(szTemp);
		}
		if(nX>1920)
		{
			CString szTemp = _T("");

			szTemp.Format(_T("%d"), 1920);

			GetDlgItem(IDC_EDIT_X)->SetWindowText(szTemp);
		}

		GetDlgItem(IDC_EDIT_X)->SetFocus();

		return;
	}
	//////////////////////////////////////////////////////
	CString szY = _T("");
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(szY);
	szY.Trim();
	if (_T("") == szY)
	{
		m_pDelegate->MessageBoxFromKey(_T("300"), _T("Y不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_Y)->SetFocus();

		return;
	}

	int nY = _ttoi(szY);
	if(nY <= 0 || nY > 1200)
	{
		m_pDelegate->MessageBoxFromKey(_T("298"), _T("请输入正确的Y,1-1200!"), MB_OK);

		if(nY<=0)
		{
			CString szTemp = _T("");

			szTemp.Format(_T("%d"), 1);

			GetDlgItem(IDC_EDIT_Y)->SetWindowText(szTemp);
		}
		if(nY>1200)
		{
			CString szTemp = _T("");

			szTemp.Format(_T("%d"), 1200);

			GetDlgItem(IDC_EDIT_Y)->SetWindowText(szTemp);
		}

		GetDlgItem(IDC_EDIT_Y)->SetFocus();

		return;
	}
	//////////////////////////////////////////////////////
	CString szWidth = _T("");
	GetDlgItem(IDC_EDIT_WIDTH)->GetWindowText(szWidth);
	szWidth.Trim();
	if (_T("") == szWidth)
	{
		m_pDelegate->MessageBoxFromKey(_T("301"), _T("宽度不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_WIDTH)->SetFocus();

		return;
	}

	int nWidth = _ttoi(szWidth);

	if ((nWidth%8) != 0)
	{
		nWidth = (nWidth/8+1)*8;

		CString szTemp;
		szTemp.Format(_T("%d"), nWidth);

		GetDlgItem(IDC_EDIT_WIDTH)->SetWindowText(szTemp);
	}
	//////////////////////////////////////////////////////
	CString szHeight = _T("");
	GetDlgItem(IDC_EDIT_HEIGHT)->GetWindowText(szHeight);
	szHeight.Trim();
	if (_T("") == szHeight)
	{
		m_pDelegate->MessageBoxFromKey(_T("302"), _T("高度不能为空,请输入!"), MB_OK);

		GetDlgItem(IDC_EDIT_HEIGHT)->SetFocus();

		return;
	}

	int nHeight = _ttoi(szHeight);
	if(nHeight<0||nHeight>255)
	{
		m_pDelegate->MessageBoxFromKey(_T("445"), _T("高度不能超过255!"), MB_OK);
		return;
	}
	//////////////////////////////////////////////////////
	int nMaxArea = 32*1024;

	if ((nWidth*nHeight)>nMaxArea)
	{
		nHeight=nMaxArea/nWidth;

		m_pDelegate->MessageBoxFromKey(_T("290"),_T("区域大小超出最大区域将自动调整区域!"),MB_OK);

		CString szTemp;
		szTemp.Format(_T("%d"),nHeight);

		GetDlgItem(IDC_EDIT_HEIGHT)->SetWindowText(szTemp);
	}
	//////////////////////////////////////////////////////
	if (nTextSize>nHeight)
	{
		nTextSize=nHeight;

		CString szTemp;
		szTemp.Format(_T("%d"),nTextSize);

		GetDlgItem(IDC_EDIT_TEXTSIZE)->SetWindowText(szTemp);
	}
	//////////////////////////////////////////////////////
	CString szText;
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(szText);
	//////////////////////////////////////////////////////
	XOSDInfo* pInfo = m_InputSignal->GetOSDInfo();

	pInfo->SetType(nType);
	pInfo->SetCenterType(nCenterType);
	pInfo->SetColor(color);
	pInfo->SetBkColor(Bkcolor);
	pInfo->SetFont(szFont);
	pInfo->SetTextSize(nTextSize);
	pInfo->SetCoordinate(nX, nY, nWidth, nHeight);
	pInfo->SetText(szText);

	pInfo->ClearMutrixData();

	pInfo->InitMutrixData();
	//****************************************************
	SetOSDMutrix();
}

void CSetOSDDlg::OnBtnSend()
{
	if (!m_pDelegate->GetNetState())
	{
		m_pDelegate->MessageBoxFromKey(_T("312"), _T("网络未打开!"), MB_OK);

		return;
	}

	XSendDataInputSignal::AddSendDataOfOSD(m_InputSignalPane, m_InputSignal,NTYPEZERO);

	if(0!=m_ComboBox_Type.GetCurSel())
	{
		XSendDataInputSignal::AddSendDataOfOSDData(m_InputSignalPane,m_InputSignal);
	}

	XSendDataInputSignal::AddSendDataOfOSD(m_InputSignalPane, m_InputSignal,NTYPEONE);

	m_pDelegate->MessageBoxFromKey(_T("311"), _T("发送完成!"), MB_OK);
}

void CSetOSDDlg::SetOSDMutrix()
{
	CClientDC dc(this);

	BOOL bExceed = FALSE;

	BOOL bSetOSDMutrix = HandleMutrix::SetOSDMutrix(dc, m_InputSignal->GetOSDInfo(), bExceed);

	m_Grid.Reset();

	if (!bSetOSDMutrix)
	{
		m_pDelegate->MessageBoxFromKey(_T("291"), _T("获取文字字模数据失败,请重新尝试!"), MB_OK);
	}
	else if (bExceed)
	{
		m_pDelegate->MessageBoxFromKey(_T("292"), _T("文字超出OSD区域，文字截取显示!"), MB_OK);
	}
}

void CSetOSDDlg::OnEnChangeEditText()
{
	XOSDInfo* pInfo = m_InputSignal->GetOSDInfo();

	CString szText;
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(szText);

	if (szText == pInfo->GetText())
	{
		return;
	}

	pInfo->SetText(szText);

	pInfo->ClearMutrixData();

	pInfo->InitMutrixData();

	SetOSDMutrix();
}

void CSetOSDDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (m_InitDlg)
	{
		lpMMI->ptMinTrackSize.x = m_DlgMinRect.Width();

		lpMMI->ptMinTrackSize.y = m_DlgMinRect.Height();
	}

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CSetOSDDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_InitDlg)
	{
		AdjustPos();
	}
}

void CSetOSDDlg::AdjustPos()
{
	CRect rect;
	GetClientRect(&rect);

	/////////////////////////////////////////////////////////////
	CRect rtParameter;
	GetDlgItem(IDC_STATIC_OSDPARAMETER)->GetWindowRect(&rtParameter);
	ScreenToClient(&rtParameter);
	rtParameter.right = rect.right - rtParameter.left;
	GetDlgItem(IDC_STATIC_OSDPARAMETER)->MoveWindow(&rtParameter);
	/////////////////////////////////////////////////////////////
	CRect rtEditText;
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowRect(&rtEditText);
	ScreenToClient(&rtEditText);
	int nEditWidth=rtEditText.Width();
	rtEditText.right=rect.right-40;
	GetDlgItem(IDC_EDIT_TEXT)->MoveWindow(&rtEditText);
	/////////////////////////////////////////////////////////////
	/*CRect rtBtnSet;
	GetDlgItem(IDC_BTN_SET)->GetWindowRect(&rtBtnSet);
	int nBtnWidth = rtBtnSet.Width();
	ScreenToClient(&rtBtnSet);
	rtBtnSet.left = rtEditText.left;
	rtBtnSet.right = rtBtnSet.left + nBtnWidth;
	GetDlgItem(IDC_BTN_SET)->MoveWindow(&rtBtnSet);
	
	CRect rtBtnSend;
	GetDlgItem(IDC_BTN_SEND)->GetWindowRect(&rtBtnSend);
	ScreenToClient(&rtBtnSend);
	rtBtnSend.left = rect.right-105;
	rtBtnSend.right = rtBtnSend.left + nBtnWidth;
	GetDlgItem(IDC_BTN_SEND)->MoveWindow(&rtBtnSend);

	CRect rtBtnCancel;
	GetDlgItem(IDCANCEL)->GetWindowRect(&rtBtnCancel);
	ScreenToClient(&rtBtnCancel);
	rtBtnCancel.right = rect.right-75;
	rtBtnCancel.left = rtBtnCancel.right-nBtnWidth;
	GetDlgItem(IDCANCEL)->MoveWindow(&rtBtnCancel);*/

	/////////////////////////////////////////////////////////////
	CRect rtStaticGrid = rtParameter;
	rtStaticGrid.top = rtParameter.bottom + rtParameter.left;
	rtStaticGrid.bottom = rect.bottom - rtParameter.left;
	GetDlgItem(IDC_STATIC_GRID)->MoveWindow(&rtStaticGrid);
	/////////////////////////////////////////////////////////////
	CRect rtGrid = rtStaticGrid;
	rtGrid.InflateRect(-10, -10);
	m_Grid.MoveWindow(&rtGrid);
	m_Grid.ResetByDlgSizeChange();
	/////////////////////////////////////////////////////////////
	Invalidate();
}