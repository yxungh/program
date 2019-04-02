// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MultiviewerView.cpp : CMultiviewerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Multiviewer.h"
#endif

#include "MultiviewerDoc.h"
#include "MultiviewerView.h"
#include "MainFrm.h"
#include "XDelegateView.h"
#include "XBaseScreenManage.h"
#include "XInternalManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultiviewerView

IMPLEMENT_DYNCREATE(CMultiviewerView, CScrollView)

BEGIN_MESSAGE_MAP(CMultiviewerView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMultiviewerView 构造/析构

CMultiviewerView::CMultiviewerView()
{
	//m_pDelegate = nullptr;

	m_bMouseLeave=TRUE;

	m_pScreenManage=NULL;

}

CMultiviewerView::~CMultiviewerView()
{
}

BOOL CMultiviewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	//cs.style &=~ WS_BORDER;

	return CScrollView::PreCreateWindow(cs);
}

void CMultiviewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMultiviewerView 诊断

#ifdef _DEBUG
void CMultiviewerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMultiviewerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMultiviewerDoc* CMultiviewerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiviewerDoc)));
	return (CMultiviewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultiviewerView 消息处理程序

void CMultiviewerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	Init();
}

void CMultiviewerView::Init()
{
	SetDelegate();

	ResetSize();
}

void CMultiviewerView::SetDelegate()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	m_pDelegate = (XDelegateView*)pMainFrame;
}

void CMultiviewerView::SetScreenManage(XBaseScreenManage* p)
{
	m_pScreenManage=p;
}

XBaseScreenManage* CMultiviewerView::GetScreenManage()
{
	return m_pScreenManage;
}

BOOL CMultiviewerView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CMultiviewerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return TRUE;
}

void CMultiviewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nullptr != m_pScreenManage)
	{
		SetCapture();

		CRect rect;
		GetClientRect(rect);

		m_pScreenManage->ViewLButtonDown(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CMultiviewerView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (nullptr != m_pScreenManage)
	{
		//SetCapture();

		CRect rect;
		GetClientRect(rect);

		m_pScreenManage->ViewLBDClick(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CMultiviewerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (nullptr != m_pScreenManage)
	{
		if(GetCapture() == this)
		{
			ReleaseCapture();

			CRect rect;
			GetClientRect(rect);

			m_pScreenManage->ViewLButtonUp(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
		}
	}
}

void CMultiviewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nullptr != m_pScreenManage)
	{
		if (m_bMouseLeave)
		{
			TRACKMOUSEEVENT evt = {0};
			evt.cbSize = sizeof(evt);
			evt.dwFlags = TME_LEAVE;
			evt.hwndTrack = m_hWnd;

			TrackMouseEvent(&evt);

			m_bMouseLeave = FALSE;
		}

		CRect rect;
		GetClientRect(rect);

		m_pScreenManage->ViewMouseMove(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

BOOL CMultiviewerView::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{	
	CRect rect;
	GetWindowRect(&rect);

	if (!rect.PtInRect(point))
	{
		return __super::OnMouseWheel(fFlags,zDelta,point);
	}

	if(fFlags==MK_CONTROL)
	{
		if(NULL!=m_pScreenManage)
		{
			return m_pScreenManage->AddScalingByMouseWheel(zDelta);
		}
		
		return FALSE;
	}
	else
	{
		return __super::OnMouseWheel(fFlags,zDelta,point);
	}	
}

void CMultiviewerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nullptr != m_pScreenManage)
	{
		m_pScreenManage->ViewKeyUp(nChar);
	}
}

void CMultiviewerView::ResetSize()
{
	if (nullptr != m_pScreenManage)
	{
		CSize size = m_pScreenManage->ViewGetSize();

		//减1因为size是设置滚动最大值,从0到(宽度-1)
		size.cx -= 1;
		size.cy -= 1;

		//因为小于0会出现异常,所以加上判断
		size.cx = size.cx < 0 ? 0 : size.cx;
		size.cy = size.cy < 0 ? 0 : size.cy;

		SetScrollSizes(MM_TEXT, size);
	}
	else
	{
		SetScrollSizes(MM_TEXT, CSize(0,0));
	}
}

void CMultiviewerView::OnMouseLeave()
{
	if (nullptr != m_pScreenManage)
	{
		m_bMouseLeave = TRUE;

		m_pScreenManage->ViewMouseLeave();
	}
}

void CMultiviewerView::OnDraw(CDC* pDC)
{
	CMultiviewerDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(nullptr!=m_pScreenManage)
	{
		CRect rect;
		GetClientRect(rect);

		//m_pScreenManage->ViewDraw(pDC, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CMultiviewerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (nullptr != m_pScreenManage)
	{
		CRect rect;
		GetClientRect(rect);

		m_pScreenManage->ViewRButtonUp(this, nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CMultiviewerView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (nullptr != m_pScreenManage)
	{
		m_pScreenManage->AdjustMultiVideoWindowSize();
	}
}


