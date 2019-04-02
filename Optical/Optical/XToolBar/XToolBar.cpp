// lrToolBarCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XToolBar.h"
#include "XHandlePath.h"
#include <uxtheme.h>
#include "XConstant.h"
#include "XTranslationManage.h"

#pragma comment(lib, "uxtheme.lib")

// XToolBarCtrl

IMPLEMENT_DYNAMIC(XToolBar, CWnd)

XToolBar::XToolBar()
{
	m_bMouseLeave = TRUE;

	m_nItemHeight = 0;

	m_nItemWidth = 0;

	m_textColor = RGB(255, 255, 255);

	m_nTextHeight = 19;
}

XToolBar::~XToolBar()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XToolBar, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave) 
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// XToolBarCtrl 消息处理程序
BOOL XToolBar::Create(UINT nItemWidth, UINT nItemHeight, UINT nDistance, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nItemHeight = nItemHeight;

	m_nItemWidth = nItemWidth;

	m_nDistance = nDistance;

	return CWnd::CreateEx(0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void XToolBar::OnPaint()
{
	CPaintDC dc(this);
	
	CRect rt;
	GetClientRect(&rt);

	HDC hdc = dc.GetSafeHdc();
	HDC hMemdc = CreateCompatibleDC(hdc);

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject( hMemdc, hMembmp);

	///////////////////////////////////////////////////////////////
	DrawThemeParentBackground(m_hWnd, hMemdc, &rt);

	Gdiplus::Graphics graphics(hMemdc);

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, 9, FontStyleRegular, UnitPoint);

	Gdiplus::Font fontActive(&fontfamily, 10, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetLineAlignment(StringAlignmentCenter);
	stringformat.SetAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush textbrush(Color(254, GetRValue(m_textColor), GetGValue(m_textColor), GetBValue(m_textColor)));

	for(std::vector<item>::iterator iter = m_vtItem.begin(); iter != m_vtItem.end(); iter++)
	{
		Gdiplus::Image ico(iter->ico);

		CRect rtico = iter->rt;

		UINT nOffsetX = (iter->rt.Width() - ico.GetWidth()) / 2;

		UINT nOffsetY = (iter->rt.Height() - ico.GetHeight() - m_nTextHeight);

		rtico.DeflateRect(nOffsetX, nOffsetY, 0, 0);

		rtico.right = rtico.left + ico.GetWidth();

		rtico.bottom = rtico.top + ico.GetHeight();

		//////////////////////////////////////////////////////////////////////////
		CString szText = XTranslationManage::GetInstance()->GetTranslationString(iter->textkey, iter->text);

		if(!iter->chk)
		{
			if(iter->sta != STATUS_NORMAL)
			{
				Image icoframe(XHandlePath::GetPhotoPath(_T("frame_3.png")));

				graphics.DrawImage(&icoframe, Rect(iter->rt.left, iter->rt.top, iter->rt.Width(), iter->rt.Height()),
					icoframe.GetWidth()/2 * iter->sta, 0, icoframe.GetWidth()/2, icoframe.GetHeight(), UnitPixel);

				graphics.DrawString(szText, -1, &fontActive, 
					RectF((Gdiplus::REAL)iter->rttext.left, (Gdiplus::REAL)iter->rttext.top, (Gdiplus::REAL)iter->rttext.Width(), (Gdiplus::REAL)iter->rttext.Height()),
					&stringformat, &textbrush);
			}
			else
			{
				graphics.DrawString(szText, -1, &font, 
					RectF((Gdiplus::REAL)iter->rttext.left, (Gdiplus::REAL)iter->rttext.top, (Gdiplus::REAL)iter->rttext.Width(), (Gdiplus::REAL)iter->rttext.Height()),
					&stringformat, &textbrush);
			}
		}
		else
		{
			Image icoframe(XHandlePath::GetPhotoPath(_T("frame_3.png")));

			graphics.DrawImage(&icoframe, Rect(iter->rt.left, iter->rt.top, iter->rt.Width(), iter->rt.Height()),
				icoframe.GetWidth()/2 * 1, 0, icoframe.GetWidth()/2, icoframe.GetHeight(), UnitPixel);

			graphics.DrawString(szText, -1, &font, 
				RectF((Gdiplus::REAL)iter->rttext.left, (Gdiplus::REAL)iter->rttext.top, (Gdiplus::REAL)iter->rttext.Width(), (Gdiplus::REAL)iter->rttext.Height()),
				&stringformat, &textbrush);
		}

		//////////////////////////////////////////////////////////////////////////
		graphics.DrawImage(&ico, 
			Rect(rtico.left, rtico.top, rtico.Width(), rtico.Height()), 
			0, 0, ico.GetWidth(), ico.GetHeight(), UnitPixel);
	}
	///////////////////////////////////////////////////////////////

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);
	
	graphics.ReleaseHDC(hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);
}

void XToolBar::InsertItem(LPCWSTR szIco, LPCTSTR szTextKey,  LPCTSTR szDefaultText, DWORD dwData)
{
	item it;
	it.ico = szIco;
	it.textkey = szTextKey;
	it.text = szDefaultText;
	it.sta = STATUS_NORMAL;
	it.chk = FALSE;
	it.data = dwData;

	CalcItemRect(it, m_vtItem.size());

	m_vtItem.push_back(it);

	Invalidate(FALSE);
}

void XToolBar::CalcItemRect(item &it, size_t nIdx)
{
	CRect rt;
	GetClientRect(&rt);

	it.rt.left = (m_nItemWidth + m_nDistance ) * nIdx;
	it.rt.right = it.rt.left + m_nItemWidth;
	it.rt.top = (rt.Height() - m_nItemHeight) / 2;
	it.rt.bottom = it.rt.top + m_nItemHeight;

	it.rttext = it.rt;
	it.rttext.top = it.rt.bottom - m_nTextHeight;
}

void XToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseLeave)
	{
		TRACKMOUSEEVENT evt;
		evt.cbSize = sizeof( evt);
		evt.dwFlags = TME_LEAVE;
		evt.dwHoverTime = 0;
		evt.hwndTrack = m_hWnd;

		TrackMouseEvent( &evt);

		m_bMouseLeave = FALSE;
	}

	BOOL bInvalid = FALSE;

	for(std::vector<item>::iterator iter = m_vtItem.begin(); iter != m_vtItem.end(); iter++)
	{
		if(iter->rt.PtInRect( point))
		{
			if (iter->sta != STATUS_FOCUS)
			{
				iter->sta = STATUS_FOCUS;

				bInvalid = TRUE;
			}
		}
		else
		{
			if(iter->sta != STATUS_NORMAL)
			{
				iter->sta = STATUS_NORMAL;

				bInvalid = TRUE;
			}
		}
	}

	if(bInvalid)
	{
		Invalidate(FALSE);
	}

	CWnd::OnMouseMove(nFlags, point);
}

LRESULT XToolBar::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bMouseLeave = TRUE;

	BOOL bInvalid = FALSE;

	for(std::vector<item>::iterator iter = m_vtItem.begin(); iter != m_vtItem.end(); iter++)
	{
		if(iter->sta != STATUS_NORMAL)
		{
			iter->sta = STATUS_NORMAL;

			bInvalid = TRUE;		
		}
	}

	if(bInvalid)
	{
		Invalidate( FALSE);
	}

	return 0;
}

void XToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bContinue = FALSE;

	for(std::vector<item>::iterator iter = m_vtItem.begin(); iter != m_vtItem.end(); iter++)
	{
		if(iter->rt.PtInRect(point))
		{	
			bContinue = TRUE;

			break;
		}
	}

	if(bContinue)
	{
		BOOL bInvalid = FALSE;

		for(std::vector<item>::iterator iter = m_vtItem.begin(); iter != m_vtItem.end(); iter++)
		{
			if(iter->rt.PtInRect(point))
			{
				GetParent()->PostMessage(MSG_TOOBAR_ITEMLCLICK, (WPARAM)iter->data, 0);

				if(!iter->chk)
				{
					//iter->chk = TRUE;

					//bInvalid = TRUE;
				}
			}
			else
			{
				if(iter->chk)
				{
					//GetParent()->PostMessage(MSG_TOOBAR_ITEMLCLICK, 0, (WPARAM)iter->data);

					//iter->chk = FALSE;

					//bInvalid = TRUE;
				}
			}
		}

		if(bInvalid)
		{
			Invalidate(FALSE);
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void XToolBar::SetTextColor(COLORREF color )
{
	m_textColor = color;

	Invalidate(FALSE);
}

void XToolBar::ClearAllItem()
{
	m_vtItem.clear();

	Invalidate(FALSE);
}

void XToolBar::SetCurSel(size_t nSelect )
{
	ASSERT(nSelect < m_vtItem.size());

	m_vtItem[nSelect].chk = TRUE;

	Invalidate(FALSE);
}

void XToolBar::ReloadInterface()
{
	Invalidate(FALSE);

}
