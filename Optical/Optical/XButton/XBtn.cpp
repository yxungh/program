// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XBtn.h"
#include "XConstant.h"

#pragma comment( lib, "UxTheme.lib")

// XBtn

IMPLEMENT_DYNAMIC(XBtn, CWnd)

XBtn::XBtn()
{
	m_dwState = State_Normal;

	m_bMouseLeave = TRUE;

	m_bDowned = FALSE;

	m_bFocus = FALSE;

	m_bFillColor = FALSE;

	m_strText = _T("");

	m_strImg = _T("");
}

XBtn::~XBtn()
{

}

BEGIN_MESSAGE_MAP(XBtn, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
END_MESSAGE_MAP()



// XBtn 消息处理程序

BOOL XBtn::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

BOOL XBtn::DrawItem( CDC *pDC )
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc = pDC->GetSafeHdc();

	HDC hMemdc = CreateCompatibleDC(hdc);

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject( hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	if (m_bFillColor)
	{
		graphics.Clear(m_FillColor);
	}
	else
	{
		DrawThemeParentBackground(m_hWnd, hMemdc, &rt);
	}

	DrawImg(graphics, rt);

	DrawText(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC( hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);

	return TRUE;
}

void XBtn::DrawImg(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_strImg)
		return;

	Gdiplus::Image* pImage = Gdiplus::Image::FromFile(m_strImg);	

	if (pImage->GetLastStatus() == Gdiplus::Ok)
	{
		UINT nImageWidth = pImage->GetWidth();

		UINT nImageHeight = pImage->GetHeight();

		graphics.DrawImage(pImage,
			RectF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height()), 
			m_dwState * nImageWidth/4.0f, 
			0, 
			nImageWidth/4.0f, 
			(Gdiplus::REAL)nImageHeight, 
			UnitPixel);
	}

	delete pImage;
}

void XBtn::DrawText(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_strText)
		return;

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, 9, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(Color(254, 254, 254));

	Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());

	graphics.DrawString(m_strText, -1, &font, reF, &stringformat, &brush);
}

void XBtn::SetImage(CString szImg )
{
	m_strImg = szImg;
}

void XBtn::OnPaint()
{
	CPaintDC dc(this); 

	DrawItem( &dc);
}

void XBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseLeave)
	{
		TRACKMOUSEEVENT evt = {0};
		evt.cbSize = sizeof(evt);
		evt.dwFlags = TME_LEAVE;
		evt.hwndTrack = m_hWnd;

		TrackMouseEvent( &evt);

		m_bMouseLeave = FALSE;

		m_dwState = State_Focus;

		Invalidate(FALSE);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void XBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;

		Invalidate(FALSE);

		PostLClickMsg();

		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XBtn::PostLClickMsg()
{
	GetParent()->PostMessage(MSG_BTN_LCLICK, GetDlgCtrlID(), 0);
}

void XBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;

	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);

	CWnd::OnLButtonDown(nFlags, point);
}

void XBtn::SetCaption(CString szText)
{
	m_strText = szText;

	Invalidate(FALSE);
}

LRESULT XBtn::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;

		Invalidate(FALSE);
	}

	return 0;
}

void XBtn::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;

	Invalidate(FALSE);
}

void XBtn::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;

	Invalidate(FALSE);
}


BOOL XBtn::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XBtn::SetFillColor(Gdiplus::Color col)
{
	m_FillColor = col;

	m_bFillColor = TRUE;
}

void XBtn::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	if (bEnable)
	{
		m_dwState = State_Normal;
	}
	else
	{
		m_dwState = State_Disable;
	}

	Invalidate(FALSE);
}