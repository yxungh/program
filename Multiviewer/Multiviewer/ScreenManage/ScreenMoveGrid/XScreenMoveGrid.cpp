#include "stdafx.h"
#include "XScreenMoveGrid.h"
#include "XScreenMoveInfo.h"

#define SCROOL_TIME_ELAPSE 200

IMPLEMENT_DYNAMIC(XScreenMoveGrid, CWnd)

	XScreenMoveGrid::XScreenMoveGrid()
{
	m_bScrollTimerH = FALSE;

	m_nScrollPosH = 0;

	m_nScrollTimerH = 0;

	m_bScrollTimerV = FALSE;

	m_nScrollPosV = 0;

	m_nScrollTimerV = 0;

	m_bDown = FALSE;

	m_pDelegate = NULL;

	m_MoveInfo=NULL;

	m_GridCountH = -1;

	m_GridCountV = -1;

	m_GridRectArr = NULL;

	m_GridWidth = 0;

	m_GridHeight = 0;
}

XScreenMoveGrid::~XScreenMoveGrid()
{
	ClearGridRectArr();
}

void XScreenMoveGrid::ClearGridRectArr()
{
	if (NULL != m_GridRectArr)
	{
		delete[] m_GridRectArr;

		m_GridRectArr = NULL;
	}
}

BEGIN_MESSAGE_MAP(XScreenMoveGrid, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL XScreenMoveGrid::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

ULONG XScreenMoveGrid::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XScreenMoveGrid::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void XScreenMoveGrid::SetDelegate(XDelegateScreenMoveGrid* p)
{
	m_pDelegate = p;
}

void XScreenMoveGrid::SetScreenMoveInfo(XScreenMoveInfo* pInfo)
{
	m_MoveInfo=pInfo;
}

void XScreenMoveGrid::Init()
{
	SetGridRectArr();

	AdustGridRectPos();

	AdjustScroll();
}

void XScreenMoveGrid::ResetByDlgSizeChange()
{
	AdustGridRectPos();

	AdjustScroll();
}

BOOL XScreenMoveGrid::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CDC Memdc;
	Memdc.CreateCompatibleDC(pDC);

	CBitmap Membmp;
	Membmp.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());

	CBitmap* pOldbmp = Memdc.SelectObject(&Membmp);

	////////////////////////////////////////////////

	Draw(&Memdc, rt);

	////////////////////////////////////////////////

	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &Memdc, 0, 0, SRCCOPY);

	Memdc.SelectObject(pOldbmp);

	Memdc.DeleteDC();

	Membmp.DeleteObject();

	return TRUE;
}

void XScreenMoveGrid::Draw(CDC* pDC, CRect rt)
{
	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	pDC->FillRect(&rt, &bruDB);

	//设置偏移位置
	pDC->SetWindowOrg(m_nScrollPosH, m_nScrollPosV);

	//绘图区域,节点在绘图区域才进行绘制
	CRect drawRect(CPoint(m_nScrollPosH, m_nScrollPosV), CSize(rt.Width(), rt.Height()));

	//绘制表格
	DrawGrid(pDC, drawRect);

	//还原偏移位置
	pDC->SetWindowOrg(0, 0);
}

void XScreenMoveGrid::DrawGrid(CDC* pDC, CRect drawRect)
{
	if (m_GridCountH <= 0 || m_GridCountV <= 0 || NULL == m_GridRectArr)
	{
		return;
	}

	CBrush bru;
	bru.CreateSolidBrush(m_MoveInfo->GetColor());

	CBrush BKbru;
	BKbru.CreateSolidBrush(m_MoveInfo->GetBkColor());

	CRect* pRect;

	CRect tempRect;

	int nCount = m_GridCountH * m_GridCountV;

	char* pMutrixData = m_MoveInfo->GetMutrixData();

	int nMutrixBitPos = 0;

	int nIndex = 1;

	for (int i = 0; i < nCount; i++)
	{
		pRect = m_GridRectArr + i;

		if (tempRect.IntersectRect(&drawRect, pRect))
		{
			if ((*pMutrixData) & (0x80>>nMutrixBitPos))
			{
				pDC->FillRect(m_GridRectArr[i], &bru);
			}
			else
			{
				if(m_MoveInfo->GetType()==1)
				{
					pDC->FillRect(m_GridRectArr[i], &BKbru);
				}
			}

			pDC->DrawEdge(m_GridRectArr[i], BDR_SUNKENOUTER, BF_TOPLEFT);
		}

		if ((nIndex%8) == 0)
		{
			pMutrixData += 1;
		}

		nMutrixBitPos = (nMutrixBitPos + 1)%8;

		nIndex++;
	}
}

void XScreenMoveGrid::SetGridRectArr()
{
	m_GridCountH = m_MoveInfo->GetWidth();

	m_GridCountV = m_MoveInfo->GetHight();

	m_GridRectArr = new CRect[m_GridCountH * m_GridCountV];
}

void XScreenMoveGrid::AdustGridRectPos()
{
	int nTop = 0;

	int nLeft = 0;

	int nGridLeft = 0;

	int nIndex = 0;

	int nDistance = 2;

	int nRectWidth = 5;

	m_GridWidth = (nRectWidth + nDistance) * m_GridCountH;
	m_GridHeight = (nRectWidth + nDistance) * m_GridCountV;

	////////////////////////////////////////////////////////居中
	CRect rect;
	GetClientRect(&rect);

	if (rect.Width() > m_GridWidth)
	{
		nGridLeft = (rect.Width() - m_GridWidth)/2;
	}

	if (rect.Height() > m_GridHeight)
	{
		nTop = (rect.Height() - m_GridHeight)/2;
	}
	///////////////////////////////////////////////////////
	for (int i = 0; i < m_GridCountV; i++)
	{
		nLeft = nGridLeft;

		for (int j = 0; j < m_GridCountH; j++)
		{
			m_GridRectArr[nIndex++].SetRect(nLeft, nTop, nLeft + nRectWidth, nTop + nRectWidth);

			nLeft = nLeft + nRectWidth + nDistance;
		}

		nTop = nTop + nRectWidth + nDistance;
	}
}

void XScreenMoveGrid::AdjustScroll()
{
	AdjustScrollH();

	AdjustScrollV();
}

void XScreenMoveGrid::AdjustScrollH()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollWidth = m_GridWidth;

	if (rt.Width() < m_GridWidth)
	{
		//当滚动条显示时，增大滚动条
		nScrollWidth += 30;
	}

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si) ;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollWidth;
	si.nPage = rt.Width();
	si.nPos = 0;

	SetScrollInfo(SB_HORZ, &si, TRUE);

	GetScrollInfo(SB_HORZ, &si) ;

	if (m_nScrollPosH > si.nPos)
	{
		m_nScrollPosH = si.nPos;
	}
	//TRACE("XOSDGrid::AdjustScrollH Width:%d, nScrollWidth:%d, nPos:%d\n", rt.Width(), nScrollWidth, nPos);
}

void XScreenMoveGrid::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		}
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void XScreenMoveGrid::AdjustScrollV()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollHeight = m_GridHeight;

	if (rt.Height() < m_GridHeight)
	{
		//当滚动条显示时，增大滚动条
		nScrollHeight += 30;
	}

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si) ;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollHeight;
	si.nPage = rt.Height();
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (m_nScrollPosV > si.nPos)
	{
		m_nScrollPosV = si.nPos;
	}

	//TRACE("XOSDGrid::AdjustScrollV Height:%d, nScrollHeight:%d, nPos:%d\n", rt.Height(), nScrollHeight);
}

void XScreenMoveGrid::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si) ;
	si.fMask = SIF_ALL ;

	GetScrollInfo(SB_VERT, &si) ;

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

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (si.nPos != pos)
	{                    
		if (!m_bScrollTimerV)
		{
			SetTimer(2, SCROOL_TIME_ELAPSE, NULL);

			m_bScrollTimerV = TRUE;
		}
	}

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}


void XScreenMoveGrid::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_HORZ, &si);

		int nPos = si.nPos;

		//TRACE("XOSDGrid::ScrollH Pos:%d\n", nPos);

		if (nPos != m_nScrollPosH)
		{
			//ScrollWindow(m_nScrollPosH - nPos, 0, NULL, NULL);

			m_nScrollPosH = nPos;

			m_nScrollTimerH = 0;

			Invalidate();
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
	}
	else if (2 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_VERT, &si) ;

		int nPos = si.nPos;

		//TRACE("XOSDGrid::ScrollV Pos:%d\n", nPos);

		if (nPos != m_nScrollPosV)
		{
			//ScrollWindow(m_nScrollPosV - nPos, 0, NULL, NULL);

			m_nScrollPosV = nPos;

			m_nScrollTimerV = 0;

			Invalidate();
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

void XScreenMoveGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;

	CWnd::OnLButtonDown(nFlags, point);
}

void XScreenMoveGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		m_bDown = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XScreenMoveGrid::ResetScroll()
{
	KillTimer(1);

	KillTimer(2);

	m_bScrollTimerH = FALSE;

	m_nScrollPosH = 0;

	m_nScrollTimerH = 0;

	m_bScrollTimerV = FALSE;

	m_nScrollPosV = 0;

	m_nScrollTimerV = 0;
}

void XScreenMoveGrid::Reset()
{
	int nNewGridCountH = m_MoveInfo->GetWidth();
	int nNewGridCountV = m_MoveInfo->GetHight();

	if (m_GridCountH != nNewGridCountH
		|| m_GridCountV != nNewGridCountV)
	{
		ResetScroll();

		ClearGridRectArr();

		SetGridRectArr();

		AdustGridRectPos();

		AdjustScroll();
	}

	Invalidate();
}