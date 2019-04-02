#include "StdAfx.h"
#include "HYXGridItem.h"
#include "HYXTreeNodeItem.h"
#include "HYXVTreeNodeItem.h"

HYXGridItem::HYXGridItem(void)
{
	m_HNodeItem = NULL;

	m_VNodeItem = NULL;

	m_GridRow = NULL;

	m_Show = FALSE;
}

HYXGridItem::~HYXGridItem(void)
{
	
}

void HYXGridItem::SetVNodeItem(HYXVTreeNodeItem* p)
{
	m_VNodeItem = p;
}

void HYXGridItem::SetHNodeItem(HYXTreeNodeItem* p)
{
	m_HNodeItem = p;
}

HYXVTreeNodeItem* HYXGridItem::GetVNodeItem()
{
	return m_VNodeItem;
}

HYXTreeNodeItem* HYXGridItem::GetHNodeItem()
{
	return m_HNodeItem;
}

void HYXGridItem::SetGridRow(HYXGridRow* p)
{
	m_GridRow = p;
}

HYXGridRow* HYXGridItem::GetGridRow()
{
	return m_GridRow;
}

BOOL HYXGridItem::GetShow()
{
	return m_Show;
}

void HYXGridItem::SetShow(BOOL b)
{
	m_Show = b;
}

void HYXGridItem::AdjustRect()
{
	CRect HFrameRect = m_HNodeItem->GetFrameRect();

	int nY = m_VNodeItem->GetExpandBtnRect().CenterPoint().y - ITEM_SECECTWIDTH / 2;

	int nX = HFrameRect.CenterPoint().x - ITEM_SECECTWIDTH / 2;

	m_Rect = CRect(nX, nY, nX + ITEM_SECECTWIDTH, nY + ITEM_SECECTHEIGHT);
}

CRect HYXGridItem::GetRect()
{
	return m_Rect;
}

int HYXGridItem::GetInputIndex()
{
	return m_HNodeItem->GetInputIndex();
}

int HYXGridItem::GetOutputIndex()
{
	return m_VNodeItem->GetOutputIndex();
}