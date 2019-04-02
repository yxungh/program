// XResizingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "XResizingDialog.h"
#include "afxDialogex.h"
#include "XConstant.h"

// XResizingDialog 对话框

IMPLEMENT_DYNAMIC(XResizingDialog, XDialog)

XResizingDialog::XResizingDialog(UINT nIDD,CWnd *pParent,CString szPtotoPath)  
	: XDialog(nIDD,pParent,szPtotoPath),m_szPtotoPath(szPtotoPath)
{
	m_DlgMinWidth = DLG_MINWIDTH;

	m_DlgMinHeight = DLG_MINHIGHT;
}

XResizingDialog::~XResizingDialog()
{
}

BEGIN_MESSAGE_MAP(XResizingDialog, XDialog)
	ON_WM_NCHITTEST()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// XResizingDialog 消息处理程序

LRESULT XResizingDialog::OnNcHitTest(CPoint point)
{
	CRect rectWindow;
	GetWindowRect(&rectWindow);

	if (point.x <= rectWindow.left + 3)
	{
		return HTLEFT;
	}
	else if (point.x >= rectWindow.right - 3)
	{
		return HTRIGHT;
	}
	else if (point.y <= rectWindow.top + 3)
	{
		return HTTOP;
	}
	else if (point.y >= rectWindow.bottom - 3)
	{
		return HTBOTTOM;
	}
	else if ((point.x <= rectWindow.left + 10) && (point.y <= rectWindow.top + 10))
	{
		return HTTOPLEFT;
	}
	else if ((point.x >= rectWindow.right - 10) && (point.y <= rectWindow.top + 10))
	{
		return HTTOPRIGHT;
	}
	else if ((point.x <= rectWindow.left + 10) && (point.y >= rectWindow.bottom - 10))
	{
		return HTBOTTOMLEFT;
	}
	else if ((point.x >= rectWindow.right - 10) && (point.y >= rectWindow.bottom - 10))
	{
		return HTBOTTOMRIGHT;
	}
	else if (point.y <= rectWindow.top + TITLEBAR_HEIGHT)
	{
		return HTCAPTION;
	}
	else 
	{
		return XDialog::OnNcHitTest(point);
	}
}

void XResizingDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	XDialog::OnNcLButtonDown(nHitTest, point);

	if (nHitTest == HTTOP)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_TOP, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTBOTTOM)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTLEFT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_LEFT, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTRIGHT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTTOPLEFT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTTOPRIGHT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTBOTTOMLEFT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTBOTTOMRIGHT)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
	}
}

void XResizingDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = m_DlgMinWidth;

	lpMMI->ptMinTrackSize.y = m_DlgMinHeight;

	XDialog::OnGetMinMaxInfo(lpMMI);
}

void XResizingDialog::OnSize(UINT nType, int cx, int cy)
{
	XDialog::OnSize(nType, cx, cy);

	Invalidate(TRUE);
}