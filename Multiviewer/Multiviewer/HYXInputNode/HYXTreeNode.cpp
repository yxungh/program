#include "StdAfx.h"
#include "HYXTreeNode.h"
#include "HYXTreeNodeItem.h"
#include "HYXInputNode.h"

HYXTreeNode::HYXTreeNode(void)
{
	m_Node = NULL;
}

HYXTreeNode::~HYXTreeNode(void)
{
	ClearData();

	m_Font.DeleteObject();
}

void HYXTreeNode::ClearData()
{
	ClearVecNode();
}

void HYXTreeNode::SetNodes(HYXInputNode* p)
{
	m_Node = p;
}

void HYXTreeNode::ExpandBtnClick(int nType, void* pData)
{
	m_Node->ExpandBtnClick(nType, pData);
}

void HYXTreeNode::NodeItemChange(HYXTreeNodeItem* pItem)
{
	m_Node->NodeItemChange();
}

void HYXTreeNode::Init()
{
	InitFont();
}

void HYXTreeNode::InitFont()
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

void HYXTreeNode::Draw(CDC* pDC, CRect rt, CRect drawRect)
{
	CFont* pOldFont = pDC->SelectObject(&m_Font);

	pDC->SetBkColor(RGB(244, 249, 252));

	/////////////////////////////////////////////
	//int nDrawCount = 0;

	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		CRect rect = pItem->GetFrameRect();

		if (rect.IntersectRect(drawRect, rect))
		{
			pItem->Draw(pDC, rt);

			//nDrawCount++;
		}
	}

	//TRACE("HYXTreeNode::Draw nDrawCount:%d\n", nDrawCount);

	/////////////////////////////////////////////
	pDC->SelectObject(pOldFont);
}

CSize HYXTreeNode::GetTextSize(CString s)
{
	CClientDC dc(m_Node->GetWnd());

	CFont* pOldFont = dc.SelectObject(&m_Font);

	CSize textExtent = dc.GetTextExtent(s);

	dc.SelectObject(pOldFont);

	return textExtent;
}

void HYXTreeNode::ClearVecNode()
{
	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		delete *iter;
	}

	m_VecItem.clear();
}

void HYXTreeNode::HandleLButtonUP(CPoint p)
{
	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		CRect rect = pItem->GetFrameRect();

		if (rect.PtInRect(p))
		{
			pItem->HandleLButtonUP(p);

			break;
		}
	}
}

int HYXTreeNode::GetScrollWidth()
{
	int nWidth = 0;

	int nCount = m_VecItem.size();

	if (nCount > 0)
	{
		HYXTreeNodeItem* pItem = m_VecItem[nCount - 1];

		CRect rect = pItem->GetFrameRect();

		nWidth = rect.right + TREE_ITEM_DISTANCEX;

		//TRACE("GetScrollWidth: nWidth:%d\n", nWidth);
	}

	return nWidth;
}

HYXTreeNodeItem* HYXTreeNode::AddItem(int nType, CString szName, void* pData,
	HYXTreeNodeItem* pParent)
{
	HYXTreeNodeItem* pItem = new HYXTreeNodeItem;

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

void HYXTreeNode::AdjustLayout()
{
	int nX = 2;

	int nY = 2;

	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		pItem->AdjustLayout(nX, nY);

		CRect rectItem = pItem->GetFrameRect();

		nX = TREE_ITEM_DISTANCEX + rectItem.right;
	}
}

HYVEC_TREENODEITEM& HYXTreeNode::GetVecItem()
{
	return m_VecItem;
}

COLORREF HYXTreeNode::GetTreeNodeItemTextColor(HYXTreeNodeItem* pItem)
{
	return m_Node->GetTreeNodeItemTextColor(pItem);
}