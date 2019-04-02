#include "StdAfx.h"
#include "HYXGridRow.h"
#include "HYXGridItem.h"
#include "HYXTreeNodeItem.h"
#include "HYXVTreeNodeItem.h"

HYXGridRow::HYXGridRow(void)
{
	m_VNodeItem = NULL;

	m_Show = FALSE;
}

HYXGridRow::~HYXGridRow(void)
{
	ClearVecItem();
}

void HYXGridRow::ClearVecItem()
{
	for (HYVEC_GRIDITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		delete *iter;
	}

	m_VecItem.clear();
}

HYXGridItem* HYXGridRow::GetItem(HYXTreeNodeItem* pNodeItem)
{
	HYXGridItem* pItem = NULL;

	DWORD key = (DWORD)pNodeItem;

	HYMAP_GRIDITEM::iterator iter = m_MapItem.find(key);

	if (m_MapItem.end() == iter)
	{
		pItem = new HYXGridItem();

		pItem->SetHNodeItem(pNodeItem);
		pItem->SetVNodeItem(m_VNodeItem);
		pItem->SetGridRow(this);

		m_MapItem.insert(std::pair<DWORD, HYXGridItem*>(key, pItem));

		m_VecItem.push_back(pItem);
	}
	else
	{
		pItem = iter->second;
	}

	return pItem;
}

HYVEC_GRIDITEM& HYXGridRow::GetVecItem()
{
	return m_VecItem;
}

void HYXGridRow::SetVNodeItem(HYXVTreeNodeItem* p)
{
	m_VNodeItem = p;
}

BOOL HYXGridRow::GetShow()
{
	return m_Show;
}

void HYXGridRow::SetShow(BOOL b)
{
	m_Show = b;
}

void HYXGridRow::SetItemShow(BOOL b)
{
	for (HYVEC_GRIDITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		(*iter)->SetShow(b);
	}
}

HYXVTreeNodeItem* HYXGridRow::GetVNodeItem()
{
	return m_VNodeItem;
}

int HYXGridRow::GetOutputIndex()
{
	return m_VNodeItem->GetOutputIndex();
}

HYXGridItem* HYXGridRow::GetItem(int nInputID)
{
	for (HYVEC_GRIDITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXGridItem* pItem = *iter;

		if (pItem->GetInputIndex() == nInputID)
		{
			return pItem;
		}
	}

	return NULL;
}