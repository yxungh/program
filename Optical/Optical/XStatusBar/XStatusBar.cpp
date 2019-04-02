// lrStatusBar.cpp : 实现文件
//

#include "stdafx.h"
#include "XStatusBar.h"
#include "XTranslationManage.h"
// XStatusBar

IMPLEMENT_DYNAMIC(XStatusBar, CWnd)

XStatusBar::XStatusBar():
	m_dDlgType(DLGTYPE_POWERMANAGE),
	m_szVersion(_T("")),
	m_szInfo(_T(""))
{

}

XStatusBar::~XStatusBar()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(XStatusBar, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// XStatusBar 消息处理程序

BOOL XStatusBar::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void XStatusBar::SetVersion(CString szVersion)
{
	m_szVersion = szVersion;

	Invalidate(FALSE);
}

void XStatusBar::SetInfo(CString szInfo)
{
	m_szInfo=szInfo;

	Invalidate(TRUE);
}

void XStatusBar::OnPaint()
{
	CPaintDC dc(this); 
}

BOOL XStatusBar::OnEraseBkgnd(CDC* pDC)
{
	HDC hdc = pDC->GetSafeHdc();

	CRect rt;
	GetClientRect(&rt);

	HDC hMemdc = CreateCompatibleDC( hdc);
	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject(hMemdc, hMembmp);

	Gdiplus::Graphics graphics( hMemdc);
	graphics.Clear(Color(230, 230, 230));

	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily, 9, FontStyleRegular, UnitPoint);
	SolidBrush brush(Color(254,87,87,87));

	if (m_szVersion != _T(""))
	{
		Gdiplus::StringFormat stringformatfar;

		stringformatfar.SetAlignment(StringAlignmentFar);
		stringformatfar.SetLineAlignment(StringAlignmentCenter);

		graphics.DrawString(m_szVersion, -1, &font, Gdiplus::RectF(0.0f, 0.0f, (Gdiplus::REAL)(rt.Width() - 5), 
			(Gdiplus::REAL)(rt.Height())), &stringformatfar, &brush);
	}
	
	if (m_szInfo != _T(""))
	{
		Gdiplus::StringFormat stringformatfar1;

		stringformatfar1.SetAlignment(StringAlignmentNear);
		stringformatfar1.SetLineAlignment(StringAlignmentCenter);

		graphics.DrawString(m_szInfo, -1, &font, Gdiplus::RectF(5.0f, 0.0f, (Gdiplus::REAL)(rt.Width()), 
			(Gdiplus::REAL)(rt.Height())), &stringformatfar1, &brush);
	}

	BitBlt(hdc, 0,0,rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC(hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject( hMembmp);
	
	return TRUE;
}

void XStatusBar::SetDlgType(DWORD dType)
{
	m_dDlgType=dType;

	SetTextInfo();

	Invalidate(TRUE);
}

void XStatusBar::SetTextInfo()
{
	switch(m_dDlgType)
	{
	case DLGTYPE_POWERMANAGE:
		{
			m_szInfo=XTranslationManage::GetInstance()->GetTranslationString(_T("13"));
		}
		break;
	case DLGTYPE_HOSTCONFIG:
		{
			m_szInfo=XTranslationManage::GetInstance()->GetTranslationString(_T("14"));
		}
		break;
	default:
		break;
	}	
}

void XStatusBar::ReloadInterface()
{
	m_szVersion=XTranslationManage::GetInstance()->GetTranslationString(_T("11"))+"："+ APP_VERSION;

	SetTextInfo();

	Invalidate(TRUE);
}