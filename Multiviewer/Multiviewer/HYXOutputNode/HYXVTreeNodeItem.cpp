#include "StdAfx.h"
#include "HYXVTreeNodeItem.h"
#include "HYXVTreeNode.h"

HYXVTreeNodeItem::HYXVTreeNodeItem(void)
{
	m_Data = NULL;

	m_Name = _T("");

	m_GetChildInfo = FALSE;

	m_Expand = TRUE;

	m_TreeNode = NULL;

	m_Type = HYITEMTYPE_NULL;

	m_HaveChildInfo = FALSE;

	m_ParentItem = NULL;

	m_Root = FALSE;

	m_OutputIndex = 0;
}

HYXVTreeNodeItem::~HYXVTreeNodeItem(void)
{
	ClearVecItem();

	ClearData();
}

void HYXVTreeNodeItem::ClearData()
{
}

void HYXVTreeNodeItem::ClearVecItem()
{
	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		delete *iter;
	}

	m_VecItem.clear();
}

void* HYXVTreeNodeItem::GetData()
{
	return m_Data;
}

int HYXVTreeNodeItem::GetType()
{
	return m_Type;
}

BOOL HYXVTreeNodeItem::GetExpand()
{
	return m_Expand;
}

CString HYXVTreeNodeItem::GetName()
{
	return m_Name;
}

void HYXVTreeNodeItem::SetData(void* p)
{
	m_Data = p;
}

void HYXVTreeNodeItem::SetGetChildInfo(BOOL b)
{
	m_GetChildInfo = b;
}

void HYXVTreeNodeItem::SetType(int nType)
{
	m_Type = nType;
}

void HYXVTreeNodeItem::SetName(CString s)
{
	m_Name = s;

	m_TextSize = m_TreeNode->GetTextSize(s);
}

void HYXVTreeNodeItem::SetTreeNode(HYXVTreeNode* p)
{
	m_TreeNode = p;
}

void HYXVTreeNodeItem::SetHaveChildInfo(BOOL b)
{
	m_HaveChildInfo = b;
}

void HYXVTreeNodeItem::SetExpand(BOOL b)
{
	 m_Expand = b;
}

void HYXVTreeNodeItem::SetParentItem(HYXVTreeNodeItem* p)
{
	m_ParentItem = p;
}

void HYXVTreeNodeItem::SetRoot(BOOL b)
{
	m_Root = b;
}
CRect HYXVTreeNodeItem::GetFrameRect()
{
	return m_FrameRect;
}

CRect HYXVTreeNodeItem::GetExpandBtnRect()
{
	return m_ExpandBtnRect;
}

HYVEC_VTREENODEITEM& HYXVTreeNodeItem::GetVecItem()
{
	return m_VecItem;
}

HYXVTreeNodeItem* HYXVTreeNodeItem::GetRootItem()
{
	if (m_Root)
	{
		return this;
	}
	else
	{
		if (NULL == m_ParentItem)
		{
			return NULL;
		}
		else
		{
			return m_ParentItem->GetRootItem();
		}
	}
}

void HYXVTreeNodeItem::AddItem(HYXVTreeNodeItem* p)
{
	m_VecItem.push_back(p);
}

void HYXVTreeNodeItem::Draw(CDC* pDC, CRect rect)
{	
	//背景颜色
	//CBrush bru;
	//bru.CreateSolidBrush(RGB(192, 192, 192));
	//pDC->FillRect(&m_FrameRect, &bru);

	//文字
	COLORREF textColor = m_TreeNode->GetTreeNodeItemTextColor(this);

	pDC->SetTextColor(textColor);

	pDC->DrawText(m_Name, m_TextRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	//绘制线
	DrawLine(pDC, rect);

	//扩展按钮
	DrawExpandBtn(pDC);

	//绘制子项
	DrawChildItem(pDC, rect);
}

void HYXVTreeNodeItem::DrawExpandBtn(CDC* pDC)
{
	if (!m_HaveChildInfo)
	{
		return;
	}

	CBrush bru;
	bru.CreateSolidBrush(RGB(244, 249, 252));

	CBrush* pOldBru = pDC->SelectObject(&bru);

	int nExpandLineLen = TREE_EXPANDBTN_WIDTH / 4 + 1;

	CPoint ExpandCenterPoint = m_ExpandBtnRect.CenterPoint();

	if (m_GetChildInfo)
	{
		if (m_VecItem.size() > 0)
		{
			pDC->Rectangle(&m_ExpandBtnRect);

			if (m_Expand)
			{
				pDC->MoveTo(ExpandCenterPoint.x - nExpandLineLen, ExpandCenterPoint.y);
				pDC->LineTo(ExpandCenterPoint.x + nExpandLineLen, ExpandCenterPoint.y);
			}
			else
			{
				pDC->MoveTo(ExpandCenterPoint.x - nExpandLineLen, ExpandCenterPoint.y);
				pDC->LineTo(ExpandCenterPoint.x + nExpandLineLen + 1, ExpandCenterPoint.y);

				pDC->MoveTo(ExpandCenterPoint.x, ExpandCenterPoint.y - nExpandLineLen);
				pDC->LineTo(ExpandCenterPoint.x, ExpandCenterPoint.y + nExpandLineLen + 1);
			}
		}
	}
	else
	{
		pDC->Rectangle(&m_ExpandBtnRect);

		pDC->MoveTo(ExpandCenterPoint.x - nExpandLineLen, ExpandCenterPoint.y);
		pDC->LineTo(ExpandCenterPoint.x + nExpandLineLen + 1, ExpandCenterPoint.y);

		pDC->MoveTo(ExpandCenterPoint.x, ExpandCenterPoint.y - nExpandLineLen);
		pDC->LineTo(ExpandCenterPoint.x, ExpandCenterPoint.y + nExpandLineLen + 1);
	}

	pDC->SelectObject(pOldBru);

	bru.DeleteObject();
}

void HYXVTreeNodeItem::DrawChildItem(CDC* pDC, CRect rect)
{
	if (!m_HaveChildInfo)
	{
		return;
	}

	if (!m_Expand)
	{
		return;
	}

	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		pItem->Draw(pDC, rect);
	}
}

void HYXVTreeNodeItem::DrawLine(CDC* pDC, CRect rect)
{
	//return;

	//绘制虚线
	LOGBRUSH logBrush;
	memset(&logBrush, 0, sizeof(logBrush));
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(0, 0, 0);
	DWORD dwF[] = {1};

	CPen pen;
	pen.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_FLAT, 1, &logBrush,1,dwF);

	CPen* pOldPen = pDC->SelectObject(&pen);

	CPoint point = m_ExpandBtnRect.CenterPoint();

	int nLineY = point.y;
	int nLineX = point.x;

	//pDC->MoveTo(m_ExpandBtnRect.right + 2, nLineY);
	//pDC->LineTo(m_TextRect.left - 2, nLineY);

	int nItemCount = m_VecItem.size();

	if (m_Expand && nItemCount > 0)
	{
		nLineY = m_ExpandBtnRect.bottom + 2;

		HYXVTreeNodeItem* pLastItem = m_VecItem[nItemCount - 1];
		int nLineLastY = pLastItem->m_TextRect.CenterPoint().y;

		pDC->MoveTo(nLineX, nLineY);
		pDC->LineTo(nLineX, nLineLastY);

		for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
		{
			HYXVTreeNodeItem* pItem = *iter;

			int nItemLineY = pItem->m_ExpandBtnRect.CenterPoint().y;

			int nItemLineX = 0;

			if (pItem->m_Type == HYITEMTYPE_DEVICE)
			{
				nItemLineX = rect.right;
			}
			else
			{
				nItemLineX = pItem->m_ExpandBtnRect.right;
			}
			
			pDC->MoveTo(nLineX, nItemLineY);

			pDC->LineTo(nItemLineX, nItemLineY);
		}
	}
	
	pDC->SelectObject(pOldPen);

	pen.DeleteObject();
}

void HYXVTreeNodeItem::HandleLButtonUP(CPoint p)
{
	if (!m_HaveChildInfo)
	{
		return;
	}

	if (m_ExpandBtnRect.PtInRect(p))
	{
		if (m_GetChildInfo)
		{
			m_Expand = !m_Expand;

			HYXVTreeNodeItem* pRootItem = GetRootItem();
			if (NULL != pRootItem)
			{
				pRootItem->CalculateTotalSize();
			}

			m_TreeNode->NodeItemChange(this);
		}
		else
		{
			m_TreeNode->ExpandBtnClick(m_Type, m_Data);
		}
	}
	else if (m_Expand)
	{
		for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
		{
			HYXVTreeNodeItem* pItem = *iter;

			pItem->HandleLButtonUP(p);
		}
	}
}

void HYXVTreeNodeItem::CalculateTotalSize()
{
	//先计算子项的总区域大小
	CalculateItemTotalSize();

	int nWidth = HTREE_LEFTWIDTH + m_TextSize.cx;

	int nHeight = m_TextSize.cy;

	if (nHeight < HTREE_EXPANDBTN_HEIGHT)
	{
		nHeight = HTREE_EXPANDBTN_HEIGHT;
	}

	m_ItemHeight = nHeight;

	//添加子项区域
	if (m_Expand && m_VecItem.size() > 0)
	{
		m_ItemTotalSize = GetItemTotalSize();

		if (nWidth < m_ItemTotalSize.cx)
		{
			nWidth = m_ItemTotalSize.cx;
		}

		nHeight += m_ItemTotalSize.cy;
	}

	m_TotalSize.cx = nWidth;

	m_TotalSize.cy = nHeight;
}

void HYXVTreeNodeItem::CalculateItemTotalSize()
{
	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		pItem->CalculateTotalSize();
	}
}

CSize HYXVTreeNodeItem::GetItemTotalSize()
{
	int nSumY = 0;

	int nMaxX = 0;

	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		CSize itemTotalSize = pItem->m_TotalSize;

		nSumY += itemTotalSize.cy;

		if (nMaxX < itemTotalSize.cx)
		{
			nMaxX = itemTotalSize.cx;
		}
	}

	//加上间隔高度
	nSumY += (m_VecItem.size() * HTREE_ITEM_DISTANCEY);

	//加上缩进间隔
	nMaxX += HTREE_CHILDITEM_INDENTATION;

	return CSize(nMaxX, nSumY);
}

void HYXVTreeNodeItem::AdjustLayout(int x, int y)
{
	int nCenterX = x + m_TotalSize.cx / 2;

	AdjustTextRect(x + HTREE_LEFTWIDTH, y);

	AdjustExpandBtnRect(x, y);

	AdjustItemRect(x + HTREE_CHILDITEM_INDENTATION, y + m_ItemHeight + HTREE_ITEM_DISTANCEY);

	AdjustFrameRect(x, y);
}

void HYXVTreeNodeItem::AdjustTextRect(int x, int y)
{
	m_TextRect.left = x;
	m_TextRect.right = m_TextRect.left + m_TextSize.cx;
	m_TextRect.top = y + (m_ItemHeight - m_TextSize.cy) / 2;
	m_TextRect.bottom = m_TextRect.top + m_TextSize.cy;
}

void HYXVTreeNodeItem::AdjustExpandBtnRect(int x, int y)
{
	m_ExpandBtnRect.left = x;
	m_ExpandBtnRect.right = m_ExpandBtnRect.left + HTREE_EXPANDBTN_HEIGHT;
	m_ExpandBtnRect.top = y + (m_ItemHeight - HTREE_EXPANDBTN_HEIGHT) / 2;
	m_ExpandBtnRect.bottom = m_ExpandBtnRect.top + HTREE_EXPANDBTN_HEIGHT;
}

void HYXVTreeNodeItem::AdjustItemRect(int x, int y)
{
	if (!m_Expand)
	{
		return;
	}

	for (HYVEC_VTREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		pItem->AdjustLayout(x, y);

		CRect rectItem = pItem->GetFrameRect();

		y = HTREE_ITEM_DISTANCEY + rectItem.bottom;
	}
}

void HYXVTreeNodeItem::AdjustFrameRect(int x, int y)
{
	m_FrameRect.left = x;
	m_FrameRect.right = x + m_TotalSize.cx;
	m_FrameRect.top = y;
	m_FrameRect.bottom = y + m_TotalSize.cy;
}


void HYXVTreeNodeItem::SetOutputIndex(int n)
{
	m_OutputIndex = n;
}

int HYXVTreeNodeItem::GetOutputIndex()
{
	return m_OutputIndex;
}