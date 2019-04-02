// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XEquipmentInputWnd.h"
#include "XConstantIM.h"
#include "XDelegateSelectEquipment.h"

#pragma comment( lib, "UxTheme.lib")

// XEquipmentInputWnd

IMPLEMENT_DYNAMIC(XEquipmentInputWnd, CWnd)

XEquipmentInputWnd::XEquipmentInputWnd()
{
	m_dwState = State_Normal;

	m_bMouseLeave = TRUE;

	m_bDowned = FALSE;

	m_bFocus = FALSE;

	m_bFillColor = FALSE;

	m_strText = _T("");

	m_strImg = _T("");

	m_EquipmentInput=NULL;

}

XEquipmentInputWnd::~XEquipmentInputWnd()
{

}

BEGIN_MESSAGE_MAP(XEquipmentInputWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave)

	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()


	ON_WM_LBUTTONDBLCLK()

	//ON_COMMAND(ID_SETINPUTURTAL,XEquipmentInputWnd::OnSetUltra)
	ON_COMMAND(ID_SETINPUTOSD,XEquipmentInputWnd::OnSetOSD)
END_MESSAGE_MAP()



// XEquipmentInputWnd 消息处理程序

BOOL XEquipmentInputWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);
}

void XEquipmentInputWnd::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

BOOL XEquipmentInputWnd::DrawItem( CDC *pDC )
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

void XEquipmentInputWnd::DrawImg(Graphics& graphics, CRect& rt)
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
			m_dwState * nImageWidth/2.0f, 
			0, 
			nImageWidth/2.0f, 
			(Gdiplus::REAL)nImageHeight, 
			UnitPixel);
	}

	delete pImage;
}

void XEquipmentInputWnd::DrawText(Graphics& graphics, CRect& rt)
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

void XEquipmentInputWnd::SetImage(CString szImg )
{
	m_strImg = szImg;
}

void XEquipmentInputWnd::OnPaint()
{
	CPaintDC dc(this); 

	DrawItem( &dc);
}

void XEquipmentInputWnd::OnMouseMove(UINT nFlags, CPoint point)
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

void XEquipmentInputWnd::PostLClickMsg()
{
	GetParent()->PostMessage(MSG_BTN_LCLICK, GetDlgCtrlID(), 0);
}


void XEquipmentInputWnd::SetCaption(CString szText)
{
	m_strText = szText;
}

LRESULT XEquipmentInputWnd::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	//if (m_dwState != State_Disable)
	//{
		m_dwState = State_Normal;

		Invalidate(FALSE);
	//}

	return 0;
}


void XEquipmentInputWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnSetOSD();
}

void XEquipmentInputWnd::SetEquipmentInput(XEquipmentInput* p)
{
	m_EquipmentInput=p;
}

void XEquipmentInputWnd::OnSetOSD()
{
	m_EquipmentInput->GetInputBoardChild()->SetOSD(m_EquipmentInput);
}

void XEquipmentInputWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;

	Invalidate(FALSE);
}

void XEquipmentInputWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;

	Invalidate(FALSE);
}


BOOL XEquipmentInputWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XEquipmentInputWnd::SetFillColor(Gdiplus::Color col)
{
	m_FillColor = col;

	m_bFillColor = TRUE;
}

void XEquipmentInputWnd::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	//if (bEnable)
	//{
		m_dwState = State_Normal;
	//}
	//else
	//{
	//	m_dwState = State_Disable;
	//}

	Invalidate(FALSE);
}

