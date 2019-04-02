// ControlTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XSceneTree.h"
#include "XSceneTree.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XConstantIM.h"
#include "XScenePane.h"


// XSceneTree

#define   DRAG_DELAY   60

IMPLEMENT_DYNAMIC(XSceneTree, CTreeCtrl)

XSceneTree::XSceneTree()
{
	m_pScenePane = NULL;

	m_bDragging=FALSE;
}

XSceneTree::~XSceneTree()
{

}

BEGIN_MESSAGE_MAP(XSceneTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &XSceneTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_GESTURE, OnGesture)
	ON_WM_TIMER()
END_MESSAGE_MAP()


ULONG XSceneTree::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XSceneTree::SetScenePane(XScenePane* p)
{
	m_pScenePane = p;
}

void XSceneTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;

	if((GetTickCount()-m_dwDragStart)<DRAG_DELAY)
	{
		return;
	}

	HTREEITEM item=pNMTreeView->itemNew.hItem;

	DWORD dwData=GetItemData(item);

	if(dwData==ITEM_DEV
		||dwData==ITEM_SIGNAL
		||dwData==ITEM_SCENEGROUP
		||dwData==ITEM_SCENEVIEWNAME)
	{
		return;
	}
	else if(ITEM_SCENE)
	{
		m_hItemDragS=item;

		m_hItemDragD=NULL;

		m_pDragImage=CreateDragImage(m_hItemDragS);

		if(!m_pDragImage)
		{
			return;
		}

		m_bDragging=TRUE;

		m_pDragImage->BeginDrag(0,CPoint(10,10));

		CPoint pt=pNMTreeView->ptDrag;

		ClientToScreen(&pt);

		m_pDragImage->DragEnter(this,pt);

		m_nScrollTimerID=SetTimer(2,40,NULL);
	}
}

void XSceneTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_dwDragStart = GetTickCount();

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void XSceneTree::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM hItem;
	UINT flags;

	//m_HoverPoint=point;

	CRect rect;
	GetClientRect(&rect);

	if(point.x<rect.right)
	{
		if(m_bDragging)
		{
			CPoint pt=point;
			CImageList::DragMove(pt);
			CImageList::DragShowNolock(FALSE);
			if((hItem=HitTest(point,&flags))!=NULL)
			{
				SelectDropTarget(hItem);
				m_hItemDragD=hItem;

				//TRACE(_T("m_hItemDragD\n"));
			}
			CImageList::DragShowNolock(TRUE);
		}
	}	
	else
	{
		if(m_bDragging)
		{
			m_bDragging=FALSE;
			CImageList::DragLeave(this);
			CImageList::EndDrag();
			//ReleaseCapture();
			delete m_pDragImage;
			SelectDropTarget(NULL);
			KillTimer(m_nScrollTimerID);
		}

		if(this == GetCapture())
		{
			ReleaseCapture();
		}
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}


void XSceneTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	if(point.x<rect.right)
	{
		if(m_bDragging)
		{
			m_bDragging=FALSE;
			CImageList::DragLeave(this);
			CImageList::EndDrag();
			ReleaseCapture();
			delete m_pDragImage;
			SelectDropTarget(NULL);
			KillTimer(m_nScrollTimerID);

			Expand(m_hItemDragD,TVE_EXPAND);

			//添加组
			m_pScenePane->AddSceneIntoGroup(m_hItemDragS,m_hItemDragD);
		}
	}
	else
	{
		if(this == GetCapture())
		{
			ReleaseCapture();
		}
	}
	
}

void XSceneTree::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==m_nScrollTimerID)
	{
		m_TimerTicks++;

		CPoint pt;

		GetCursorPos(&pt);

		CRect rect;

		GetClientRect(&rect);

		ClientToScreen(&rect);

		HTREEITEM hItem=GetFirstVisibleItem();

		if(pt.y<rect.top+10)
		{
			//向上滚动
			int slowscroll=6-(rect.top+10-pt.y)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{

				CImageList::DragShowNolock(FALSE);

				SendMessage(WM_VSCROLL,SB_LINEUP);

				SelectDropTarget(hItem);

				m_hItemDragD=hItem;

				CImageList::DragShowNolock(TRUE);
			}
		}
		else if(pt.y>rect.bottom-10)
		{
			//向下滚动
			int slowscroll=6-(pt.y-rect.bottom+10)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{
				CImageList::DragShowNolock(FALSE);

				SendMessage(WM_VSCROLL,SB_LINEDOWN);

				int nCount=GetVisibleCount();

				for(int i=0;i<nCount-1;i++)
				{
					hItem=GetNextVisibleItem(hItem);
				}

				if(hItem)
				{
					SelectDropTarget(hItem);
				}

				m_hItemDragD=hItem;

				CImageList::DragShowNolock(true);
			}
		}
	}

	CTreeCtrl::OnTimer(nIDEvent);
}

//HTREEITEM XSceneTree::ExpandGroupItem()
//{
//	DWORD_PTR tempData;
//
//	HTREEITEM root;
//
//	root = GetRootItem();
//
//	while (root != NULL)
//	{
//		tempData = GetItemData(root);
//
//		if(tempData==(DWORD_PTR)ITEMTYPE_INPUTGROUP)
//		{
//			return root;
//		}
//
//		root = GetNextItem(root, TVGN_NEXT);
//	}
//
//	return NULL;
//}