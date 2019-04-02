// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XText.h"
#include "XConstant.h"

// XText
IMPLEMENT_DYNAMIC(XText, CWnd)

XText::XText()
{
	m_FillColor = RGB(232, 239, 242);

	m_TextColor = RGB(0, 0, 0);

	m_Text = _T("");

	m_Vertical = FALSE;

	m_Left=FALSE;

	m_nTextSize=10;
}

XText::~XText()
{
	
}

BEGIN_MESSAGE_MAP(XText, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// XText 消息处理程序

BOOL XText::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}


void XText::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void XText::SetText(CString szText)
{
	m_Text = szText;

	InvalidateRect(NULL);
}

void XText::SetFillColor(COLORREF color)
{
	m_FillColor = color;
}

void XText::SetTextColor(COLORREF color)
{
	m_TextColor = color;
}

void XText::SetVertical(BOOL b)
{
	m_Vertical = b;
}

void XText::SetLeft(BOOL b)
{
	m_Left=b;
}

void XText::SetTextSize(int nSize)
{
	m_nTextSize=nSize;
}

BOOL XText::OnEraseBkgnd(CDC* pDC)
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

void XText::DrawText(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_Text)
		return;

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, (Gdiplus::REAL)m_nTextSize, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;

	if(m_Left)
	{
		stringformat.SetAlignment(StringAlignmentNear);
		stringformat.SetLineAlignment(StringAlignmentNear);
	}
	else
	{
		stringformat.SetAlignment(StringAlignmentCenter);
		stringformat.SetLineAlignment(StringAlignmentCenter);
	}

	if (m_Vertical)
	{
		stringformat.SetFormatFlags(StringFormatFlagsDirectionVertical);
	}

	Gdiplus::Color color(GetRValue(m_TextColor), GetGValue(m_TextColor), GetBValue(m_TextColor));

	Gdiplus::SolidBrush brush(color);

	Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());

	graphics.DrawString(m_Text, -1, &font, reF, &stringformat, &brush);
}

void XText::OnPaint()
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