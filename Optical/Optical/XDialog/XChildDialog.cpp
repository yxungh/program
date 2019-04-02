// XChildDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "XChildDialog.h"
#include "XHandlePath.h"

// XChildDialog 对话框

IMPLEMENT_DYNAMIC(XChildDialog, CDialogEx)

XChildDialog::XChildDialog(UINT nIDD,CWnd *pParent)  
	: CDialogEx(nIDD,pParent)
{
	m_bEnableVK_RETURN = TRUE;

	m_bEnableVK_ESCAPE = TRUE;
}

XChildDialog::~XChildDialog()
{

}

void XChildDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XChildDialog, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// XChildDialog 消息处理程序


BOOL XChildDialog::OnEraseBkgnd(CDC* pDC)
{
	DrawDlg(pDC);

	return TRUE;
}

void XChildDialog::DrawDlg(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CBrush bru;
	bru.CreateSolidBrush(RGB(232/*100*/, 239, 242));

	pDC->FillRect(&rt, &bru);

	
	//CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	//CBrush* pOldBrush = pDC->SelectObject(pBrush);

	//pDC->Rectangle(&rt);

	//pDC->SelectObject(pOldBrush);
	
}

HBRUSH XChildDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC) 
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
		{
			/*
			if (pWnd->IsWindowEnabled())
			{
				pDC->SetBkMode(TRANSPARENT);

				return (HBRUSH)::GetStockObject(NULL_BRUSH);
			}
			*/
		}
		else
		{
			pDC-> SetBkMode(TRANSPARENT);

			return (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
	}

	return hbr;
}

BOOL XChildDialog::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_RETURN://屏蔽回车  
			{
				if (!m_bEnableVK_RETURN)
				{
					return TRUE;  
				}
			}
			break;
		case VK_ESCAPE://屏蔽Esc  
			{
				if (!m_bEnableVK_ESCAPE)
				{
					return TRUE;  
				}
			}
			break;
		}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

BOOL XChildDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}