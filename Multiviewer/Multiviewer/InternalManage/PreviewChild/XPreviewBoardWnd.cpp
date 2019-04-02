// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XPreviewBoardWnd.h"
#include "XConstantIM.h"
#include "XCorrespondScreen.h"
#include "XPreviewBoard.h"
#include "XPreviewChild.h"



#pragma comment( lib, "UxTheme.lib")

// XPreviewBoardWnd

IMPLEMENT_DYNAMIC(XPreviewBoardWnd, CWnd)

XPreviewBoardWnd::XPreviewBoardWnd()
{
	m_dwState = State_Normal;
	m_bMouseLeave = TRUE;
	m_bDowned = FALSE;
	m_bFocus = FALSE;
	m_bFillColor = FALSE;
	m_strText = _T("");
	m_strImg = _T("");
	m_pParent=NULL;
}

XPreviewBoardWnd::~XPreviewBoardWnd()
{

}

BEGIN_MESSAGE_MAP(XPreviewBoardWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()


	//ON_COMMAND(ID_SETSCREENNUM,XPreviewBoardWnd::OnSetCorrespondScreenNum)

END_MESSAGE_MAP()


// XPreviewBoardWnd 消息处理程序

void XPreviewBoardWnd::SetParent(XPreviewBoard* p)
{
	m_pParent=p;
}

BOOL XPreviewBoardWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	//return CreateEx( 0, AfxRegisterWndClass(), 0, dwStyle, rect, pParentWnd, nID);

	return CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);

}

void XPreviewBoardWnd::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

BOOL XPreviewBoardWnd::DrawItem( CDC *pDC )
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

void XPreviewBoardWnd::DrawImg(Graphics& graphics, CRect& rt)
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

void XPreviewBoardWnd::DrawText(Graphics& graphics, CRect& rt)
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

void XPreviewBoardWnd::SetImage(CString szImg )
{
	m_strImg = szImg;

	Invalidate(FALSE);
}

void XPreviewBoardWnd::OnPaint()
{
	CPaintDC dc(this); 

	DrawItem( &dc);
}

void XPreviewBoardWnd::OnMouseMove(UINT nFlags, CPoint point)
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


void XPreviewBoardWnd::PostLClickMsg()
{
	GetParent()->PostMessage(MSG_BTN_LCLICK, GetDlgCtrlID(), 0);
}


void XPreviewBoardWnd::SetCaption(CString szText)
{
	m_strText = szText;

	Invalidate(FALSE);
}

LRESULT XPreviewBoardWnd::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;
	m_dwState = State_Normal;
	Invalidate(FALSE);
	
	return 0;
}

void XPreviewBoardWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	XPreviewChild* pPreviewChild=m_pParent->GetPreviewChild();

	VEC_PREVIEWBOARD& VecBoard=pPreviewChild->GetVecPreviewBoard();

	for(VEC_PREVIEWBOARD::iterator iter=VecBoard.begin();iter!=VecBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;

		if(pBoard==m_pParent)
		{
			pBoard->SetSelected(TRUE);
			pBoard->UpDateImage();
		}
	}
}

void XPreviewBoardWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	if(NULL!=m_pParent)
		m_pParent->OnShowMenu();
}

void XPreviewBoardWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	XPreviewChild* pPreviewChild=m_pParent->GetPreviewChild();

	VEC_PREVIEWBOARD& VecBoard=pPreviewChild->GetVecPreviewBoard();

	for(VEC_PREVIEWBOARD::iterator iter=VecBoard.begin();iter!=VecBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;

		if(pBoard==m_pParent)
		{
			pBoard->SetSelected(FALSE);
			pBoard->UpDateImage();
		}
	}
}

void XPreviewBoardWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	m_bFocus = TRUE;
	Invalidate(FALSE);
}

void XPreviewBoardWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	m_bFocus = FALSE;
	Invalidate(FALSE);
}


BOOL XPreviewBoardWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XPreviewBoardWnd::SetFillColor(Gdiplus::Color col)
{
	m_FillColor = col;

	m_bFillColor = TRUE;
}

void XPreviewBoardWnd::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	m_dwState = State_Normal;

	Invalidate(FALSE);
}

