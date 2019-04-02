// ChangeRTSPAddrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserPowerManageDlg.h"
#include "afxdialogex.h"
#include "XUserManage.h"
#include "XDelegateUserManage.h"
#include "..\XConstant.h"
#include "XUserInfo.h"
#include "HYXGridItem.h"

// CUserPowerManageDlg 对话框

IMPLEMENT_DYNAMIC(CUserPowerManageDlg, CDialogEx)

CUserPowerManageDlg::CUserPowerManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserPowerManageDlg::IDD, pParent)
{
	m_UserManage = NULL;

	m_UserInfo = NULL;
}

CUserPowerManageDlg::~CUserPowerManageDlg()
{
}

void CUserPowerManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserPowerManageDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserPowerManageDlg 消息处理程序

BOOL CUserPowerManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgRect();

	InitGrid();

	InitNoticeText();

	InitInputNodes();

	InitOutputNodes();

	ReloadInterface();

	return FALSE;  
}

void CUserPowerManageDlg::ReloadInterface()
{
	XDelegateUserManage* pDelegate = m_UserManage->GetDelegate();

	SetWindowText(pDelegate->GetTranslationString(_T("372"), _T("用户权限管理")) + _T(" - ") + m_UserInfo->GetAccount());

	GetDlgItem(IDC_STATIC_NOTICE1)->SetWindowText(pDelegate->GetTranslationString(_T("239"), _T("提示")) + _T(":"));

	GetDlgItem(IDC_STATIC_NOTICE2)->SetWindowText(pDelegate->GetTranslationString(_T("375"), _T("红色方格代表没有权限")));

	GetDlgItem(IDC_STATIC_NOTICE3)->SetWindowText(pDelegate->GetTranslationString(_T("376"), _T("绿色方格代表有权限")));
}

void CUserPowerManageDlg::SetUserManage(XUserManage* p)
{
	m_UserManage = p;
}

void CUserPowerManageDlg::SetUserInfo(XUserInfo* p)
{
	m_UserInfo = p;
}

void CUserPowerManageDlg::OnOK()
{

}

BOOL CUserPowerManageDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CBrush bruDB;
	bruDB.CreateSolidBrush(RGB(244, 249, 252));
	pDC->FillRect(&rt, &bruDB);

	return TRUE;
}

void CUserPowerManageDlg::SetDlgRect()
{
	RECT rc; 
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &rc, 0); 

	int nWidth = rc.right - rc.left;
	int nHeight = rc.bottom - rc.top;

	MoveWindow(0, 0, nWidth, nHeight);
}

void CUserPowerManageDlg::InitNoticeText()
{
	XDelegateUserManage* pDelegate = m_UserManage->GetDelegate();

	CRect rt;
	GetClientRect(&rt);

	CRect rtOutput;
	rtOutput.left = 4;
	rtOutput.top =  NOTICETEXT_HEIGHT + INPUTNODERECT_HEIGHT;
	rtOutput.right = NOTICETEXT_HEIGHT - 2;
	rtOutput.bottom = rt.bottom - 4;
	m_NoticeOutputNode.Create(WS_CHILD|WS_VISIBLE, rtOutput, this, 0);
	m_NoticeOutputNode.SetFillColor(RGB(192, 192, 192));;
	m_NoticeOutputNode.SetText(pDelegate->GetTranslationString(_T("374"), _T("输出")));
	
	m_NoticeOutputNode.ShowWindow(SW_SHOW);
	m_NoticeOutputNode.UpdateWindow();

	CRect rtInput;
	rtInput.left = NOTICETEXT_HEIGHT + OUTPUTNODERECT_WIDTH;
	rtInput.top =  2;
	rtInput.right = rt.right - 4;
	rtInput.bottom = NOTICETEXT_HEIGHT - 2;
	m_NoticeInputNode.Create(WS_CHILD|WS_VISIBLE, rtInput, this, 0);
	m_NoticeInputNode.SetFillColor(RGB(192, 192, 192));
	m_NoticeInputNode.SetText(pDelegate->GetTranslationString(_T("373"), _T("输入")));
	
	m_NoticeInputNode.ShowWindow(SW_SHOW);
	m_NoticeInputNode.UpdateWindow();
}

void CUserPowerManageDlg::InitInputNodes()
{
	CRect rt;
	GetClientRect(&rt);

	CRect rtTemp;
	rtTemp.left = NOTICETEXT_HEIGHT + OUTPUTNODERECT_WIDTH;
	rtTemp.top = NOTICETEXT_HEIGHT;
	rtTemp.right = rt.right - 4;
	rtTemp.bottom = NOTICETEXT_HEIGHT + INPUTNODERECT_HEIGHT;

	m_InputNode.SetDelegate(this);
	m_InputNode.Create(WS_CHILD|WS_VISIBLE, rtTemp, this, 0);
	m_InputNode.ShowWindow(SW_SHOW);
	m_InputNode.UpdateWindow();
	m_InputNode.Init();
	m_InputNode.SetInputInfo(m_UserManage->GetDelegate()->GetInputCount());
}

void CUserPowerManageDlg::InitOutputNodes()
{
	CRect rt;
	GetClientRect(&rt);

	CRect rtTemp;
	rtTemp.left = NOTICETEXT_HEIGHT;
	rtTemp.top =  NOTICETEXT_HEIGHT + INPUTNODERECT_HEIGHT;
	rtTemp.right = NOTICETEXT_HEIGHT + OUTPUTNODERECT_WIDTH;
	rtTemp.bottom = rt.bottom - 4;

	m_OutputNode.SetDelegate(this);
	m_OutputNode.Create(WS_CHILD|WS_VISIBLE, rtTemp, this, 0);
	m_OutputNode.ShowWindow(SW_SHOW);
	m_OutputNode.UpdateWindow();
	m_OutputNode.Init();
	m_OutputNode.SetOutputInfo(m_UserManage->GetDelegate()->GetOutputCount());
}

void CUserPowerManageDlg::InitGrid()
{
	CRect rt;
	GetClientRect(&rt);

	CRect rtGrid;
	rtGrid.left = NOTICETEXT_HEIGHT + OUTPUTNODERECT_WIDTH;
	rtGrid.top = NOTICETEXT_HEIGHT + INPUTNODERECT_HEIGHT;
	rtGrid.right = rt.right - 4;
	rtGrid.bottom = rt.bottom - 4;
	m_Grid.SetDelegate(this);
	m_Grid.Create(WS_CHILD|WS_VISIBLE, rtGrid, this, 0);
	m_Grid.ShowWindow(SW_SHOW);
	m_Grid.UpdateWindow();
	m_Grid.Init();
}

CString CUserPowerManageDlg::GetTranslationString(CString szKey, CString szDefault)
{
	return m_UserManage->GetDelegate()->GetTranslationString(szKey, szDefault);
}

void CUserPowerManageDlg::AdjustGrid()
{
	m_Grid.AdjustGrid();
}

void CUserPowerManageDlg::AdjustScrollH()
{
	m_Grid.AdjustScrollH();
}

void CUserPowerManageDlg::AdjustScrollV()
{
	m_Grid.AdjustScrollV();
}

int CUserPowerManageDlg::GetScrollWidth()
{
	return m_InputNode.GetScrollWidth();
}

int CUserPowerManageDlg::GetScrollHeight()
{
	return m_OutputNode.GetScrollHeight();
}

void CUserPowerManageDlg::ScrollH(int nPos)
{
	m_InputNode.Scroll(nPos);
}

void CUserPowerManageDlg::ScrollV(int nPos)
{
	m_OutputNode.Scroll(nPos);
}

void CUserPowerManageDlg::GetInputExpandDeviceItem(HYVEC_TREENODEITEM& VecItem)
{
	m_InputNode.GetExpandDeviceItem(VecItem);
}

void CUserPowerManageDlg::GetOutputExpandDeviceItem(HYVEC_VTREENODEITEM& VecItem)
{
	m_OutputNode.GetExpandDeviceItem(VecItem);
}

void CUserPowerManageDlg::GridRectClick(HYXGridItem* pItem)
{
	if (!m_UserManage->IsAdminUser())
	{
		return;
	}

	int nInputIndex = pItem->GetInputIndex();
	
	int nOutputIndex = pItem->GetOutputIndex();

	BOOL bPower = GetNodePower(nInputIndex, nOutputIndex);

	m_UserInfo->SetNodePowerInfo(nInputIndex, nOutputIndex, !bPower);

	m_Grid.Invalidate();
}

void CUserPowerManageDlg::GridRButtonUp()
{

}

BOOL CUserPowerManageDlg::GetNodePower(int nInputIndex, int nOutputIndex)
{
	return m_UserInfo->GetNodePower(nInputIndex, nOutputIndex);
}

HBRUSH CUserPowerManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC) 
	{
		pDC-> SetBkMode(TRANSPARENT);

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}
