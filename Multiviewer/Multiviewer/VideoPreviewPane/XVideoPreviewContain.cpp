// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XVideoPreviewContain.h"
#include <atlconv.h>
#include "XVideoPreviewPane.h"
#include "HandlePath.h"

#define SCROOL_TIME_ELAPSE  200


// XVideoPreviewContain

IMPLEMENT_DYNAMIC(XVideoPreviewContain, CWnd)

XVideoPreviewContain::XVideoPreviewContain()
{
	m_bScrollTimerV = FALSE;

	m_nScrollPosV = 0;

	m_nScrollTimerV = 0;

	m_ScrollPosV = 0;

	m_bScrollTimerH = FALSE;

	m_nScrollPosH = 0;

	m_nScrollTimerH = 0;

	m_ScrollPosH = 0;

	m_Pane = NULL;
}

XVideoPreviewContain::~XVideoPreviewContain()
{

}

BEGIN_MESSAGE_MAP(XVideoPreviewContain, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// XVideoPreviewContain 消息处理程序

BOOL XVideoPreviewContain::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void XVideoPreviewContain::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

BOOL XVideoPreviewContain::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	pDC->FillRect(&rt, &bruDB);

	return TRUE;
}

void XVideoPreviewContain::Init()
{

}

void XVideoPreviewContain::SetPane(XVideoPreviewPane* p)
{
	m_Pane = p;
}

void XVideoPreviewContain::AdjustScrollV()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollHeight = m_Pane->GetContainScrollHeight();

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);

	int nPos = si.nPos;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollHeight;
	si.nPage = rt.Height();
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	ScrollWindow(0, m_ScrollPosV, NULL, NULL);

	m_ScrollPosV = 0;
}

void XVideoPreviewContain::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;

	GetScrollInfo(SB_VERT, &si);

	int pos = si.nPos;

	switch (nSBCode)
	{
	case SB_TOP:
		si.nPos = si.nMin;
		break;

	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;

	case SB_LINEUP:
		si.nPos -= 20;
		break;

	case SB_LINEDOWN:
		si.nPos += 20;
		break;

	case SB_PAGEUP:
		si.nPos -= si.nPage ;
		break ;

	case SB_PAGEDOWN:
		si.nPos += si.nPage ;
		break ;

	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos ;
		break ;

	default:
		break ;         
	}

	si.fMask = SIF_POS ;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (si.nPos != pos)
	{                    
		if (!m_bScrollTimerV)
		{
			SetTimer(2, SCROOL_TIME_ELAPSE, NULL);

			m_bScrollTimerV = TRUE;

			m_nScrollPosV = pos;
		}
	}

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

void XVideoPreviewContain::AdjustScrollH()
{
	CRect rt;
	GetClientRect(rt);

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);

	int nPos = si.nPos;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE| SIF_POS;
	si.nMin = m_nScrollHMin;
	si.nMax = m_nScrollHMax;
	si.nPage = rt.Width();
	si.nPos = 0;

	SetScrollInfo(SB_HORZ, &si, TRUE);

	ScrollWindow(0, m_ScrollPosH, NULL, NULL);

	m_ScrollPosH = 0;
}

void XVideoPreviewContain::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si) ;
	si.fMask = SIF_ALL ;

	GetScrollInfo(SB_HORZ, &si) ;

	int pos = si.nPos;

	switch (nSBCode)
	{
	case SB_TOP:
		si.nPos = si.nMin ;
		break ;

	case SB_BOTTOM:
		si.nPos = si.nMax ;
		break ;

	case SB_LINEUP:
		si.nPos -= 20;
		break ;

	case SB_LINEDOWN:
		si.nPos += 20 ;
		break ;

	case SB_PAGEUP:
		si.nPos -= si.nPage ;
		break ;

	case SB_PAGEDOWN:
		si.nPos += si.nPage ;
		break ;

	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos ;
		break ;

	default:
		break ;         
	}

	si.fMask = SIF_POS ;

	SetScrollInfo(SB_HORZ, &si, TRUE);

	GetScrollInfo(SB_HORZ, &si) ;

	if (si.nPos != pos)
	{                    
		if (!m_bScrollTimerH)
		{
			SetTimer(1, SCROOL_TIME_ELAPSE, NULL);

			m_bScrollTimerH = TRUE;

			m_nScrollPosH = pos;
		}
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void XVideoPreviewContain::OnTimer(UINT_PTR nIDEvent)
{
	if(1==nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_HORZ, &si);

		int nPos = si.nPos;

		//TRACE("XOSDGrid::ScrollH Pos:%d\n", nPos);

		if (nPos != m_nScrollPosH)
		{
			ScrollWindow(m_nScrollPosH - nPos, 0, NULL, NULL);

			m_nScrollPosH = nPos;

			m_nScrollTimerH = 0;

			Invalidate(FALSE);
		}
		else
		{
			m_nScrollTimerH++;

			if (m_nScrollTimerH >= 5)
			{
				KillTimer(1);

				m_bScrollTimerH = FALSE;
			}
		}
	}else if (2 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_VERT, &si) ;

		int nPos = si.nPos;

		if (nPos != m_nScrollPosV)
		{
			ScrollWindow(0, m_nScrollPosV - nPos, NULL, NULL);

			m_ScrollPosV = nPos;

			m_nScrollPosV = nPos;

			m_nScrollTimerV = 0;

			Invalidate(FALSE);
		}
		else
		{
			m_nScrollTimerV++;

			if (m_nScrollTimerV >= 5)
			{
				KillTimer(2);

				m_bScrollTimerV = FALSE;
			}
		}
	}

	CWnd::OnTimer(nIDEvent);
}

