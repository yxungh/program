// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "HYXGrid.h"
#include "HYXGridRow.h"
#include "HYXGridItem.h"
#include "HYXTreeNodeItem.h"
#include "HYXVTreeNodeItem.h"
#include "HYXDelegateGrid.h"
#include <atlconv.h>

#define SCROOL_TIME_ELAPSE  200

// HYXGrid

IMPLEMENT_DYNAMIC(HYXGrid, CWnd)

HYXGrid::HYXGrid()
{
	m_Delegate = NULL;

	m_bScrollTimerH = FALSE;

	m_nScrollPosH = 0;

	m_nScrollTimerH = 0;

	m_bScrollTimerV = FALSE;

	m_nScrollPosV = 0;

	m_nScrollTimerV = 0;

	m_ScrollPosH = 0;

	m_ScrollPosV = 0;
}

HYXGrid::~HYXGrid()
{
	ClearVecGridRow();

	m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(HYXGrid, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// HYXGrid 消息处理程序

BOOL HYXGrid::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}


ULONG HYXGrid::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void HYXGrid::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void HYXGrid::Init()
{
	InitFont();
}

void HYXGrid::InitFont()
{
	m_Font.CreateFont(   
		TREE_TREE_ITEM_FONTSIZE,                
		0,                
		0,                
		0,                                   
		0,                                 
		FALSE,                           
		FALSE,                            
		FALSE,               
		DEFAULT_CHARSET,         
		OUT_DEFAULT_PRECIS,   
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,      
		DEFAULT_PITCH,             
		APP_FONT);
}

BOOL HYXGrid::OnEraseBkgnd(CDC* pDC)
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

void HYXGrid::Draw(CDC* pDC, CRect rt)
{
	CFont* pOldFont = pDC->SelectObject(&m_Font);

	CBrush bruDB;
	bruDB.CreateSolidBrush(RGB(244, 249, 252));
	pDC->FillRect(&rt, &bruDB);

	//设置偏移位置
	pDC->SetWindowOrg(m_ScrollPosH, m_ScrollPosV);

	//绘图区域,节点在绘图区域才进行绘制
	CRect drawRect(CPoint(m_ScrollPosH, m_ScrollPosV), CSize(rt.Width(), rt.Height()));

	//绘制直线
	DrawLine(pDC, rt, drawRect);

	//绘制表格
	DrawGrid(pDC, drawRect);

	//还原偏移位置
	pDC->SetWindowOrg(0, 0);

	pDC->SelectObject(pOldFont);
}

void HYXGrid::DrawLine(CDC* pDC, CRect rect, CRect drawRect)
{
	LOGBRUSH logBrush;
	memset(&logBrush, 0, sizeof(logBrush));
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(0, 0, 0);
	DWORD dwF[] = {1};

	CPen pen;
	pen.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_FLAT, 1, &logBrush,1,dwF);

	CPen* pOldPen = pDC->SelectObject(&pen);

	int nDrawCount = 0;

	////////////////////////////////////////////////////////////////////////
	for (HYVEC_NUM::iterator iter = m_VecLineY.begin(); iter != m_VecLineY.end(); iter++)
	{
		int nY = *iter;

		if (nY >= drawRect.top && nY <= drawRect.bottom)
		{
			//因为界面会滚动，所以需要加上滚动数值
			pDC->MoveTo(m_ScrollPosH, nY);
			pDC->LineTo(m_ScrollPosH + rect.right, nY);

			nDrawCount++;
		}
	}
	////////////////////////////////////////////////////////////////////////
	for (HYVEC_NUM::iterator iter = m_VecLineX.begin(); iter != m_VecLineX.end(); iter++)
	{
		int nX = *iter;

		if (nX >= drawRect.left && nX <= drawRect.right)
		{
			//因为界面会滚动，所以需要加上滚动数值
			pDC->MoveTo(nX, m_ScrollPosV);
			pDC->LineTo(nX, m_ScrollPosV + rect.bottom);

			nDrawCount++;
		}
	}
	////////////////////////////////////////////////////////////////////////
	pDC->SelectObject(pOldPen);

	pen.DeleteObject();

	//TRACE("HYXGrid::DrawLine drawCount:%d\n", nDrawCount);
}

void HYXGrid::DrawGrid(CDC* pDC, CRect drawRect)
{
	pDC->SetBkMode(TRANSPARENT);

	CBrush bruDB;
	bruDB.CreateSolidBrush(RGB(0, 255, 0));

	CBrush bruRed;
	bruRed.CreateSolidBrush(RGB(255, 0, 0));

	//int nDrawCount = 0;

	for (HYVEC_GRIDROW::iterator iterRow = m_VecGridRow.begin(); iterRow != m_VecGridRow.end(); iterRow++)
	{
		HYXGridRow* pRow = *iterRow;

		if (!pRow->GetShow())
		{
			continue;
		}

		HYVEC_GRIDITEM& VecItem = pRow->GetVecItem();

		for (HYVEC_GRIDITEM::iterator iterItem = VecItem.begin(); iterItem != VecItem.end(); iterItem++)
		{
			HYXGridItem* pItem = *iterItem;

			if (!pItem->GetShow())
			{
				continue;
			}

			CRect tempRect;

			CRect itemRect = pItem->GetRect();

			BOOL bDraw = tempRect.IntersectRect(itemRect, drawRect);

			if (bDraw)
			{
				CBrush* pOldBru = NULL;
				
				BOOL bPower = m_Delegate->GetNodePower(pItem->GetInputIndex(), pItem->GetOutputIndex());

				if (bPower)
				{
					pOldBru = pDC->SelectObject(&bruDB);
				}
				else
				{
					pOldBru = pDC->SelectObject(&bruRed);
				}

				pDC->Rectangle(&itemRect);

				pDC->SelectObject(pOldBru);

				//nDrawCount++;
			}
		}
	}

	//TRACE("HYXGrid::Draw nDrawCount:%d\n", nDrawCount);
}

void HYXGrid::SetDelegate(HYXDelegateGrid* p)
{
	m_Delegate = p;
}

void HYXGrid::AdjustScrollH()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollWidth = m_Delegate->GetScrollWidth();

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si) ;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollWidth;
	si.nPage = rt.Width();
	si.nPos = 0;

	SetScrollInfo(SB_HORZ, &si, TRUE);

	//TRACE("HYXGrid::AdjustScrollH Width:%d, nScrollWidth:%d, nPos:%d\n", rt.Width(), nScrollWidth, nPos);
}

void HYXGrid::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void HYXGrid::AdjustScrollV()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollHeight = m_Delegate->GetScrollHeight();

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si) ;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollHeight;
	si.nPage = rt.Height();
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	//TRACE("HYXGrid::AdjustScrollV Height:%d, nScrollHeight:%d, nPos:%d\n", rt.Height(), nScrollHeight);
}

void HYXGrid::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

			m_nScrollPosV = pos;
		}
	}

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

void HYXGrid::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_HORZ, &si) ;

		int nPos = si.nPos;

		//TRACE("HYXGrid::ScrollH Pos:%d\n", nPos);

		if (nPos != m_nScrollPosH)
		{
			//ScrollWindow(m_nScrollPosH - nPos, 0, NULL, NULL);

			m_ScrollPosH = nPos;

			m_Delegate->ScrollH(nPos);

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

		//TRACE("HYXGrid::ScrollV Pos:%d\n", nPos);

		if (nPos != m_nScrollPosV)
		{
			//ScrollWindow(m_nScrollPosV - nPos, 0, NULL, NULL);

			m_ScrollPosV = nPos;

			m_Delegate->ScrollV(nPos);

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

void HYXGrid::ClearVecGridRow()
{
	for (HYVEC_GRIDROW::iterator iter = m_VecGridRow.begin(); iter != m_VecGridRow.end(); iter++)
	{
		delete *iter;
	}

	m_VecGridRow.clear();
}

HYXGridRow* HYXGrid::GetGridRow(HYXVTreeNodeItem* pNodeItem)
{
	HYXGridRow* pRow = NULL;

	DWORD key = (DWORD)pNodeItem;

	HYMAP_GRIDROW::iterator iter = m_MapGridRow.find(key);

	if (m_MapGridRow.end() == iter)
	{
		pRow = new HYXGridRow();

		pRow->SetVNodeItem(pNodeItem);

		m_MapGridRow.insert(std::pair<DWORD, HYXGridRow*>(key, pRow));

		m_VecGridRow.push_back(pRow);
	}
	else
	{
		pRow = iter->second;
	}

	return pRow;
}

void HYXGrid::SetGridRowShow(BOOL b)
{
	for (HYVEC_GRIDROW::iterator iter = m_VecGridRow.begin(); iter != m_VecGridRow.end(); iter++)
	{
		(*iter)->SetShow(b);
	}
}

void HYXGrid::AdjustGrid()
{
	SetGridRowShow(FALSE);

	m_VecLineX.clear();

	m_VecLineY.clear();

	HYVEC_TREENODEITEM VecItemInput;
	m_Delegate->GetInputExpandDeviceItem(VecItemInput);

	HYVEC_VTREENODEITEM VecItemOutput;
	m_Delegate->GetOutputExpandDeviceItem(VecItemOutput);

	for (HYVEC_VTREENODEITEM::iterator iterOutput = VecItemOutput.begin(); iterOutput != VecItemOutput.end(); iterOutput++)
	{
		HYXVTreeNodeItem* pItemOutput = *iterOutput;

		HYXGridRow* pGridRow = GetGridRow(pItemOutput);

		pGridRow->SetShow(TRUE);

		pGridRow->SetItemShow(FALSE);

		for (HYVEC_TREENODEITEM::iterator iterInput = VecItemInput.begin(); iterInput != VecItemInput.end(); iterInput++)
		{
			HYXTreeNodeItem* pItemInput = *iterInput;

			HYXGridItem* pGridItem = pGridRow->GetItem(pItemInput);

			pGridItem->SetShow(TRUE);

			pGridItem->AdjustRect();
		}
	}

	for (HYVEC_VTREENODEITEM::iterator iterOutput = VecItemOutput.begin(); iterOutput != VecItemOutput.end(); iterOutput++)
	{
		HYXVTreeNodeItem* pItemOutput = *iterOutput;

		int nY = pItemOutput->GetExpandBtnRect().CenterPoint().y;

		m_VecLineY.push_back(nY);
	}

	for (HYVEC_TREENODEITEM::iterator iterInput = VecItemInput.begin(); iterInput != VecItemInput.end(); iterInput++)
	{
		HYXTreeNodeItem* pItemInput = *iterInput;

		int nX = pItemInput->GetFrameRect().CenterPoint().x;

		m_VecLineX.push_back(nX);
	}

	Invalidate();
}

HYXGridRow* HYXGrid::GetGridRow(int nOutputID)
{
	for (HYVEC_GRIDROW::iterator iter = m_VecGridRow.begin(); iter != m_VecGridRow.end(); iter++)
	{
		HYXGridRow* pRow = *iter;

		if (pRow->GetOutputIndex() == nOutputID)
		{
			return pRow;
		}
	}

	return NULL;
}

void HYXGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;

	CWnd::OnLButtonDown(nFlags, point);
}

void HYXGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		CPoint temp;
		temp.x = point.x + m_ScrollPosH;
		temp.y = point.y + m_ScrollPosV;

		HandleLButtonUP(temp);

		m_bDown = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void HYXGrid::HandleLButtonUP(CPoint p)
{
	for (HYVEC_GRIDROW::iterator iterRow = m_VecGridRow.begin(); iterRow != m_VecGridRow.end(); iterRow++)
	{
		HYXGridRow* pRow = *iterRow;

		if (!pRow->GetShow())
		{
			continue;
		}

		CRect rowRect = pRow->GetVNodeItem()->GetFrameRect();

		if(((rowRect.top - ITEM_SECECTWIDTH) > p.y)
			|| ((rowRect.bottom + ITEM_SECECTWIDTH) < p.y))
		{
			continue;
		}

		HYVEC_GRIDITEM& VecItem = pRow->GetVecItem();

		for (HYVEC_GRIDITEM::iterator iterItem = VecItem.begin(); iterItem != VecItem.end(); iterItem++)
		{
			HYXGridItem* pItem = *iterItem;

			if (!pItem->GetShow())
			{
				continue;
			}

			///////////////////////////////////////////
			CRect itemRect = pItem->GetRect();

			if (itemRect.PtInRect(p))
			{
				//USES_CONVERSION;
				//TRACE("HYXGrid::HandleLButtonUP out:%s, in:%s\n", W2A(pItem->GetVNodeItem()->GetName()), 
				//	W2A(pItem->GetHNodeItem()->GetName()));

				m_Delegate->GridRectClick(pItem);

				return;
			}
		}
	}
}

void HYXGrid::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_Delegate->GridRButtonUp();

	CWnd::OnRButtonUp(nFlags, point);
}
