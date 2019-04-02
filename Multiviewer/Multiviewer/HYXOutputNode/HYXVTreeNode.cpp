#include "StdAfx.h"
#include "HYXVTreeNode.h"
#include "HYXVTreeNodeItem.h"
#include "HYXOutputNode.h"

HYXVTreeNode::HYXVTreeNode(void)
{
	m_Node = NULL;
}

HYXVTreeNode::~HYXVTreeNode(void)
{
	ClearData();

	m_Font.DeleteObject();
}

void HYXVTreeNode::ClearData()
{
	ClearVecNode();
}

void HYXVTreeNode::SetNodes(HYXOutputNode* p)
{
	m_Node = p;
}

void HYXVTreeNode::ExpandBtnClick(int nType, void* pData)
{
	m_Node->ExpandBtnClick(nType, pData);
}

void HYXVTreeNode::NodeItemChange(HYXVTreeNodeItem* pItem)
{
	m_Node->NodeItemChange();
}

void HYXVTreeNode::Init()
{
	InitFont();
}

void HYXVTreeNode::InitFont()
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

void HYXVTreeNode::Draw(CDC* pDC, CRect rect, CRect drawRect)
{
	CFont* pOldFont = pDC->SelectObject(&m_Font);

	pDC->SetBkColor(RGB(244, 249, 252));

	/////////////////////////////////////////////
	//int nDrawCount = 0;

	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		CRect rectItem = pItem->GetFrameRect();

		if (rectItem.IntersectRect(drawRect, rectItem))
		{
			pItem->Draw(pDC, rect);

			//nDrawCount++;
		}
	}

	//TRACE("HYXVTreeNode::Draw nDrawCount:%d\n", nDrawCount);

	/////////////////////////////////////////////
	pDC->SelectObject(pOldFont);
}

CSize HYXVTreeNode::GetTextSize(CString s)
{
	CClientDC dc(m_Node->GetWnd());

	CFont* pOldFont = dc.SelectObject(&m_Font);

	CSize textExtent = dc.GetTextExtent(s);

	dc.SelectObject(pOldFont);

	return textExtent;
}

void HYXVTreeNode::ClearVecNode()
{
	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		delete *iter;
	}

	m_VecItem.clear();
}

void HYXVTreeNode::HandleLButtonUP(CPoint p)
{
	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		CRect rect = pItem->GetFrameRect();

		if (rect.PtInRect(p))
		{
			pItem->HandleLButtonUP(p);

			break;
		}
	}
}

int HYXVTreeNode::GetScrollHeight()
{
	int nHeight = 0;

	int nCount = m_VecItem.size();

	if (nCount > 0)
	{
		HYXVTreeNodeItem* pItem = m_VecItem[nCount - 1];

		CRect rect = pItem->GetFrameRect();

		nHeight = rect.bottom + TREE_ITEM_DISTANCEX;

		//TRACE("GetScrollHeight: nHeight:%d\n", nHeight);
	}

	return nHeight;
}

HYXVTreeNodeItem* HYXVTreeNode::AddItem(int nType, CString szName, void* pData,
	HYXVTreeNodeItem* pParent)
{
	HYXVTreeNodeItem* pItem = new HYXVTreeNodeItem;

	pItem->SetTreeNode(this);
	pItem->SetParentItem(pParent);
	pItem->SetData(pData);
	pItem->SetName(szName);
	pItem->SetType(nType);

	if (NULL == pParent)
	{
		m_VecItem.push_back(pItem);
	}
	else
	{
		pParent->AddItem(pItem);
	}

	return pItem;
}

void HYXVTreeNode::AdjustLayout()
{
	int nX = 2;

	int nY = 10;

	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		pItem->AdjustLayout(nX, nY);

		CRect rectItem = pItem->GetFrameRect();

		nY = HTREE_ITEM_DISTANCEY + rectItem.bottom;
	}
}

HYVEC_VTREENODEITEM& HYXVTreeNode::GetVecItem()
{
	return m_VecItem;
}

COLORREF HYXVTreeNode::GetTreeNodeItemTextColor(HYXVTreeNodeItem* pItem)
{
	return m_Node->GetTreeNodeItemTextColor(pItem);
}