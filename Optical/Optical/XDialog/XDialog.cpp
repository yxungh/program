// XDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "XDialog.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XConstant.h"
#include "XBtn.h"

// XDialog 对话框

IMPLEMENT_DYNAMIC(XDialog, CDialogEx)

XDialog::XDialog(UINT nIDD,CWnd *pParent,CString szPhotoPath)  
	: CDialogEx(nIDD,pParent),
	m_szPhotoPath(szPhotoPath),
	m_bEnableVK_RETURN(FALSE),
	m_bEnableVK_ESCAPE(FALSE),
	m_bNcHitTest(TRUE)
{
}

XDialog::~XDialog()
{
}

void XDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XDialog, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// XDialog 消息处理程序

BOOL XDialog::OnEraseBkgnd(CDC* pDC)
{
	DrawDlg(pDC);
	return TRUE;
}

void XDialog::DrawDlg(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());

	CBitmap* pOldBitmap;
	pOldBitmap = tempDC.SelectObject(&bitmap);

	///////////////////////////////////////////////////////////////
	Gdiplus::Graphics graphics(tempDC);
	graphics.Clear(Color(232, 239, 242));
	
	//绘制标题栏背景
	Gdiplus::Image titlebg(XHandlePath::GetPhotoPath(_T("TitleBarbg.png")));
	graphics.DrawImage(&titlebg, 0, 0, rt.Width(), TITLEBAR_HEIGHT);

	//绘制窗口背景
	if(m_szPhotoPath!=_T(""))
	{
		Gdiplus::Image background(m_szPhotoPath);
		graphics.DrawImage(&background, 0, 0, rt.Width(), rt.Height());
	}

	//绘制标题文字
	CString strText=_T("");
	GetWindowText(strText);
	if (_T("")!=strText)
	{
		FontFamily fontfamily(APP_FONT);
		Gdiplus::Font font(&fontfamily, (Gdiplus::REAL)FONT_SIZE, FontStyleBold, UnitPoint);

		SolidBrush whitebrush(Color(254,254,254));

		Gdiplus::StringFormat stringformat;
		stringformat.SetAlignment(StringAlignmentCenter);
		stringformat.SetLineAlignment(StringAlignmentCenter);

		Gdiplus::RectF reF(2.0f, 0.0f, (Gdiplus::REAL)rt.Width(),(Gdiplus::REAL)titlebg.GetHeight());

		graphics.DrawString(strText, -1, &font, reF, &stringformat, &whitebrush);
	}

	//绘制边框颜色
	Pen pen(Color(0,99,177),1);
	CRect rtTemp = rt;
	rtTemp.DeflateRect(0,0,1,1);
	graphics.DrawRectangle(&pen, Rect(rtTemp.left,rtTemp.top,rtTemp.Width(), rtTemp.Height()));

	///////////////////////////////////////////////////////////////
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &tempDC, 0, 0, SRCCOPY);
	tempDC.SelectObject(pOldBitmap);
	tempDC.DeleteDC();
	bitmap.DeleteObject();
}

HBRUSH XDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr=CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
		break;
	case CTLCOLOR_EDIT:
		{
			if(pWnd->IsWindowEnabled())
			{
				pDC->SetBkMode(TRANSPARENT);
				HBRUSH b=CreateSolidBrush(RGB(255,255,255));
				return b;
			}
		}
		break;
	default:
		break;
	}

	return hbr;
}

LRESULT XDialog::OnNcHitTest(CPoint point)
{
	if(m_bNcHitTest)
	{
		CPoint pt(point);

		ScreenToClient(&pt);

		if(pt.y<30)
		{
			return HTCAPTION;
		}
	}

	return CDialogEx::OnNcHitTest(point);
}

BOOL XDialog::PreTranslateMessage(MSG* pMsg)
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

BOOL XDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}

void XDialog::CreateBtn(CWnd* pParent, XBtn* pBtn, CRect rect,
	UINT nID, CString szPhotoPath)
{
	pBtn->Create(WS_CHILD|WS_VISIBLE, rect, pParent, nID);
	pBtn->ShowWindow(SW_SHOW);
	pBtn->UpdateWindow();
	pBtn->SetImage(szPhotoPath);
}