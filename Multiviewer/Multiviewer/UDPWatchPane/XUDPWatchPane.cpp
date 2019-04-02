// InputSignal.cpp : 实现文件
//

#include "stdafx.h"
#include "XUDPWatchPane.h"
#include "XDelegateUDPWatchPane.h"
#include "..\MainFrm.h"
#include "..\resource.h"

IMPLEMENT_DYNAMIC(XUDPWatchPane, CDockablePane)

XUDPWatchPane::XUDPWatchPane()
{
	m_pDelegate = NULL;

	m_InfoIndex = 1;

	m_bDisableAnimation = TRUE;

	m_nSlideSteps = 1;
}

XUDPWatchPane::~XUDPWatchPane()
{
	m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(XUDPWatchPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLEAR, OnClear)
END_MESSAGE_MAP()



// XUDPWatchPane 消息处理程序

void XUDPWatchPane::SetDelegate(XDelegateUDPWatchPane* pDelegate)
{
	m_pDelegate = pDelegate;
}

void XUDPWatchPane::Init()
{
	CreatePane();

	InitFont();

	m_ListBox_Info.SetFont(&m_Font);
}

void XUDPWatchPane::CreatePane()
{
	CWnd* pWnd = m_pDelegate->GetCWND();

	CMainFrame* pMainFrame = (CMainFrame*)pWnd;

	CString szTitle = m_pDelegate->GetTranslationString(_T("327"), _T("监视窗口"));

	if (!Create(szTitle, pMainFrame, CRect(0, 0, 400, 200), TRUE, 
		ID_UDPWATCHPANE, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		return; 
	}

	EnableDocking(CBRS_ALIGN_RIGHT);

	pMainFrame->DockPane(this);

	SetAutoHideMode(TRUE, CBRS_ALIGN_RIGHT);
}

void XUDPWatchPane::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("327"), _T("监视窗口")));
}

int XUDPWatchPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!InitToolBar())
	{
		return -1;
	}

	if (!InitListBoxInfo())
	{
		return -1;
	}

	return 0;
}

void XUDPWatchPane::InitFont()
{
	m_Font.CreateFont(   
		20,                
		0,                
		0,                
		0,                                   
		0,                                 
		FALSE,                           
		FALSE,                            
		FALSE,               
		DEFAULT_CHARSET,         
		OUT_DEFAULT_PRECIS,   
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,      
		DEFAULT_PITCH,             
		APP_FONT);
}

BOOL XUDPWatchPane::InitToolBar()
{
	m_wndToolBar.SetPane(this);

	if(m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, 0))
	{
		m_wndToolBar.LoadToolBar(ID_TOOLBAR_UDPWATCHPANE, 0, 0, TRUE);

		m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

		m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

		m_wndToolBar.SetOwner(this);

		// 所有命令将通过此控件路由，而不是通过主框架路由:
		m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL XUDPWatchPane::InitListBoxInfo()
{
	if (!m_ListBox_Info.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOINTEGRALHEIGHT , CRect(0, 0, 0, 0), this, 0))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

CString XUDPWatchPane::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

void XUDPWatchPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void XUDPWatchPane::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rect, &bruDB);

	CRect rectBox;
	m_ListBox_Info.GetWindowRect(&rectBox);
	ScreenToClient(&rectBox);
	rectBox.InflateRect(1, 1);
	dc.Draw3dRect(rectBox, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void XUDPWatchPane::AdjustLayout()
{
	if (nullptr == GetSafeHwnd())
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	CRect rectListBox = rectClient;
	rectListBox.top = cyTlb;
	rectListBox.InflateRect(-1, -1);
	m_ListBox_Info.SetWindowPos(NULL, rectListBox.left, rectListBox.top, rectListBox.Width(), rectListBox.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}


void XUDPWatchPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_ListBox_Info.SetFocus();
}

void XUDPWatchPane::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}

void XUDPWatchPane::AddUDPInfo(unsigned char* pData, int nDataLen)
{
	//USES_CONVERSION;

	CString szTemp = _T("");

	CString szStr = _T("");

	for (int i = 0; i< nDataLen; i++)
	{
		szTemp.Format(_T("%02X "), pData[i]);

		szStr += szTemp;
	}

	//CString szData=_T(""); 
	//szData.Format(_T("%d(%d):  %s"), m_InfoIndex++, nDataLen, szStr);

	AddInfo(szStr);
}

void XUDPWatchPane::AddInfo(CString szInfo)
{
	m_ListBox_Info.SetRedraw(FALSE);

	int iCurIndex = m_ListBox_Info.GetCurSel();

	m_ListBox_Info.AddString(szInfo);

	int iCount = m_ListBox_Info.GetCount();
	BOOL bCurLast = (iCurIndex == LB_ERR || iCurIndex + 1 == iCount - 1);

	int iDec = 0;
	while(m_ListBox_Info.GetCount() > 200)
	{
		m_ListBox_Info.DeleteString(0);
		++iDec;
	}

	if(bCurLast)
	{
		iCurIndex = iCount - iDec - 1;
		m_ListBox_Info.SetCurSel(iCurIndex);
	}
	else if(iCurIndex < iDec)
	{
		iCurIndex = 0;
		m_ListBox_Info.SetCurSel(iCurIndex);
	}
	else
	{
		iCurIndex = m_ListBox_Info.GetCurSel();
	}

	m_ListBox_Info.SetAnchorIndex(iCurIndex);

	m_ListBox_Info.SetRedraw(TRUE);
}

void XUDPWatchPane::OnClear()
{
	m_ListBox_Info.ResetContent();

	m_InfoIndex = 1;
}