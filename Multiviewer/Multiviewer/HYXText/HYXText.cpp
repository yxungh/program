// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "HYXText.h"
#include "XConstantIM.h"

// HYXText

IMPLEMENT_DYNAMIC(HYXText, CWnd)

HYXText::HYXText()
{
	m_FillColor = RGB(240, 240, 240);

	m_TextColor = RGB(0, 0, 0);

	m_Text = _T("");

	m_Vertical = FALSE;
}

HYXText::~HYXText()
{

}

BEGIN_MESSAGE_MAP(HYXText, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// HYXText 消息处理程序

BOOL HYXText::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void HYXText::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void HYXText::SetText(CString szText)
{
	m_Text = szText;

	InvalidateRect(NULL);
}

void HYXText::SetFillColor(COLORREF color)
{
	m_FillColor = color;
}

void HYXText::SetTextColor(COLORREF color)
{
	m_TextColor = color;
}

void HYXText::SetVertical(BOOL b)
{
	m_Vertical = b;
}

BOOL HYXText::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc = pDC->GetSafeHdc();

	HDC hMemdc = CreateCompatibleDC(hdc);

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject( hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	Gdiplus::Color color(GetRValue(m_FillColor), GetGValue(m_FillColor), GetBValue(m_FillColor));

	graphics.Clear(color);

	DrawText(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC( hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);

	return TRUE;
}

void HYXText::DrawText(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_Text)
		return;

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, 10, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	if (m_Vertical)
	{
		stringformat.SetFormatFlags(StringFormatFlagsDirectionVertical);
	}

	Gdiplus::Color color(GetRValue(m_TextColor), GetGValue(m_TextColor), GetBValue(m_TextColor));

	Gdiplus::SolidBrush brush(color);

	Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());

	graphics.DrawString(m_Text, -1, &font, reF, &stringformat, &brush);
}

void HYXText::OnPaint()
{
	CPaintDC dc(this); 

	//CRect rt;
	//GetClientRect(&rt);

	//CBrush bruDB;
	//bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	//dc.FillRect(&rt, &bruDB);

	//Graphics graphics(dc.GetSafeHdc());

	//graphics.Clear(Gdiplus::Color(90, 198, 149));

	//Gdiplus::Pen pen(Color(0, 0, 0), 1);
	//graphics.DrawRectangle(&pen, Rect(rt.left,rt.top,rt.Width() - 1, rt.Height() - 1));

	//Gdiplus::FontFamily fontfamily(APP_FONT);

	//Gdiplus::Font font(&fontfamily, 12, FontStyleRegular, UnitPoint);

	//Gdiplus::StringFormat stringformat;
	//stringformat.SetAlignment(StringAlignmentNear);
	//stringformat.SetLineAlignment(StringAlignmentNear);

	//Gdiplus::SolidBrush brush(Color(0, 0, 255));

	//Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());
}