#include "StdAfx.h"
#include "HYXTreeNodeItem.h"
#include "HYXTreeNode.h"

HYXTreeNodeItem::HYXTreeNodeItem(void)
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

	m_InputIndex = 0;
}

HYXTreeNodeItem::~HYXTreeNodeItem(void)
{
	ClearVecItem();

	ClearData();
}

void HYXTreeNodeItem::ClearData()
{
	
}

void HYXTreeNodeItem::ClearVecItem()
{
	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		delete *iter;
	}

	m_VecItem.clear();
}

void* HYXTreeNodeItem::GetData()
{
	return m_Data;
}

int HYXTreeNodeItem::GetType()
{
	return m_Type;
}

CString HYXTreeNodeItem::GetName()
{
	return m_Name;
}

void HYXTreeNodeItem::SetData(void* p)
{
	m_Data = p;
}

void HYXTreeNodeItem::SetGetChildInfo(BOOL b)
{
	m_GetChildInfo = b;
}

void HYXTreeNodeItem::SetType(int nType)
{
	m_Type = nType;
}

void HYXTreeNodeItem::SetName(CString s)
{
	m_Name = s;

	m_TextSize = m_TreeNode->GetTextSize(s);
}

void HYXTreeNodeItem::SetTreeNode(HYXTreeNode* p)
{
	m_TreeNode = p;
}

void HYXTreeNodeItem::SetHaveChildInfo(BOOL b)
{
	m_HaveChildInfo = b;
}

void HYXTreeNodeItem::SetExpand(BOOL b)
{
	 m_Expand = b;
}

void HYXTreeNodeItem::SetParentItem(HYXTreeNodeItem* p)
{
	m_ParentItem = p;
}

void HYXTreeNodeItem::SetRoot(BOOL b)
{
	m_Root = b;
}
CRect HYXTreeNodeItem::GetFrameRect()
{
	return m_FrameRect;
}

BOOL HYXTreeNodeItem::GetExpand()
{
	return m_Expand;
}

HYVEC_TREENODEITEM& HYXTreeNodeItem::GetVecItem()
{
	return m_VecItem;
}

HYXTreeNodeItem* HYXTreeNodeItem::GetRootItem()
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

void HYXTreeNodeItem::AddItem(HYXTreeNodeItem* p)
{
	m_VecItem.push_back(p);
}

void HYXTreeNodeItem::Draw(CDC* pDC, CRect rt)
{	
	//背景颜色
	//CBrush bru;
	//bru.CreateSolidBrush(RGB(192, 192, 192));
	//pDC->FillRect(&m_FrameRect, &bru);

	//文字
	COLORREF textColor = m_TreeNode->GetTreeNodeItemTextColor(this);

	pDC->SetTextColor(textColor);

	pDC->DrawText(m_Name, m_TextRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	//扩展按钮
	DrawExpandBtn(pDC);

	//绘制直线
	DrawLine(pDC, rt);

	//绘制子项
	DrawChildItem(pDC, rt);
}

void HYXTreeNodeItem::DrawExpandBtn(CDC* pDC)
{
	if (!m_HaveChildInfo)
	{
		return;
	}

	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	CBrush* pOldBru = pDC->SelectObject(pBrush);

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
}

void HYXTreeNodeItem::DrawLine(CDC* pDC, CRect rt)
{
	//return;

	if (!m_HaveChildInfo)
	{
		return;
	}

	if (!m_Expand)
	{
		return;
	}

	//连接虚线
	int nItemCount = m_VecItem.size();

	if (nItemCount > 0)
	{
		LOGBRUSH logBrush;
		memset(&logBrush, 0, sizeof(logBrush));
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = RGB(0, 0, 0);
		DWORD dwF[] = {1};

		CPen pen;
		pen.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_FLAT, 1, &logBrush,1,dwF);

		CPen* pOldPen = pDC->SelectObject(&pen);

		int nLineY = 0;
		int nLineX = 0;
		int nLineHeight = TREE_ITEM_CHILDDISTANCEY / 2;

		CPoint ExpandCenterPoint = m_ExpandBtnRect.CenterPoint();

		nLineX = ExpandCenterPoint.x;
		pDC->MoveTo(nLineX, m_ExpandBtnRect.bottom + 3);

		nLineY = m_ExpandBtnRect.bottom + nLineHeight;
		pDC->LineTo(nLineX, nLineY);
		nLineY += 1;

		int nItemIndex = 0;

		for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
		{
			HYXTreeNodeItem* pItem = *iter;

			CRect frameRect = pItem->GetFrameRect();

			CPoint centerPoint = frameRect.CenterPoint();

			if (centerPoint.x != nLineX)
			{
				pDC->MoveTo(centerPoint.x, nLineY);

				if (pItem->m_Type == HYITEMTYPE_DEVICE)
				{
					pDC->LineTo(centerPoint.x, rt.bottom);
				}
				else
				{
					pDC->LineTo(centerPoint.x, nLineY + nLineHeight);
				}

				if(nItemIndex == 0 || nItemIndex == nItemCount - 1)
				{
					pDC->MoveTo(centerPoint.x, nLineY);
					pDC->LineTo(nLineX, nLineY);
				}
			}
			else
			{
				pDC->MoveTo(nLineX, nLineY);

				if (pItem->m_Type == HYITEMTYPE_DEVICE)
				{
					pDC->LineTo(nLineX, rt.bottom);
				}
				else
				{
					pDC->LineTo(nLineX, nLineY + nLineHeight);
				}
			}

			nItemIndex++;
		}

		pDC->SelectObject(pOldPen);

		pen.DeleteObject();
	}
}

void HYXTreeNodeItem::DrawChildItem(CDC* pDC, CRect rt)
{
	if (!m_HaveChildInfo)
	{
		return;
	}

	if (!m_Expand)
	{
		return;
	}

	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		pItem->Draw(pDC, rt);
	}
}

void HYXTreeNodeItem::HandleLButtonUP(CPoint p)
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

			HYXTreeNodeItem* pRootItem = GetRootItem();
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
		for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
		{
			HYXTreeNodeItem* pItem = *iter;

			pItem->HandleLButtonUP(p);
		}
	}
}

void HYXTreeNodeItem::CalculateTotalSize()
{
	//先计算子项的总区域大小
	CalculateItemTotalSize();

	int nMaxWidth = m_TextSize.cx;

	int nHeight = m_TextSize.cy;

	//添加扩展按钮区域
	if (nMaxWidth < TREE_EXPANDBTN_WIDTH)
	{
		nMaxWidth = TREE_EXPANDBTN_WIDTH;
	}

	nHeight += TREE_ITEM_INSIDEDISTANCEY;
	nHeight += TREE_EXPANDBTN_HEIGHT;
		
	//添加子项区域
	if (m_Expand && m_VecItem.size() > 0)
	{
		m_ItemTotalSize = GetItemTotalSize();

		if (nMaxWidth < m_ItemTotalSize.cx)
		{
			nMaxWidth = m_ItemTotalSize.cx;
		}

		nHeight += TREE_ITEM_CHILDDISTANCEY;
		nHeight += m_ItemTotalSize.cy;
	}

	//设备项区域用来设置选择项的区域，所以需要限制
	if (m_Type == HYITEMTYPE_DEVICE)
	{
		if (nMaxWidth < TREE_ITEM_WIDTHMIN)
		{
			nMaxWidth = TREE_ITEM_WIDTHMIN;
		}
	}

	m_TotalSize.cx = nMaxWidth;

	m_TotalSize.cy = nHeight;
}

void HYXTreeNodeItem::CalculateItemTotalSize()
{
	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		pItem->CalculateTotalSize();
	}
}

CSize HYXTreeNodeItem::GetItemTotalSize()
{
	int nSumX = 0;

	int nMaxHeight = 0;

	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		CSize itemTotalSize = pItem->m_TotalSize;

		nSumX += itemTotalSize.cx;

		if (nMaxHeight < itemTotalSize.cy)
		{
			nMaxHeight = itemTotalSize.cy;
		}
	}

	//加上间隔宽度
	nSumX += ((m_VecItem.size() - 1) * TREE_ITEM_CHILDDISTANCEX);

	return CSize(nSumX, nMaxHeight);
}

void HYXTreeNodeItem::AdjustLayout(int x, int y)
{
	int nCenterX = x + m_TotalSize.cx / 2;

	AdjustTextRect(nCenterX, y);

	AdjustExpandBtnRect(nCenterX, y + m_TextSize.cy + TREE_ITEM_INSIDEDISTANCEY);

	AdjustItemRect(x, y + m_TextSize.cy + TREE_EXPANDBTN_HEIGHT + TREE_ITEM_INSIDEDISTANCEY + TREE_ITEM_CHILDDISTANCEY);

	AdjustFrameRect(x, y);
}

void HYXTreeNodeItem::AdjustTextRect(int centerX, int y)
{
	m_TextRect.left = centerX - m_TextSize.cx / 2;
	m_TextRect.right = m_TextRect.left + m_TextSize.cx;
	m_TextRect.top = y;
	m_TextRect.bottom = m_TextRect.top + m_TextSize.cy;
}

void HYXTreeNodeItem::AdjustExpandBtnRect(int centerX, int y)
{
	m_ExpandBtnRect.left = centerX - TREE_EXPANDBTN_WIDTH / 2;
	m_ExpandBtnRect.right = m_ExpandBtnRect.left + TREE_EXPANDBTN_WIDTH;
	m_ExpandBtnRect.top = y;
	m_ExpandBtnRect.bottom = m_ExpandBtnRect.top + TREE_EXPANDBTN_HEIGHT;
}

void HYXTreeNodeItem::AdjustItemRect(int x, int y)
{
	if (!m_Expand)
	{
		return;
	}

	if (m_ItemTotalSize.cx < m_TotalSize.cx)
	{
		if (((m_TotalSize.cx - m_ItemTotalSize.cx) % 2) == 0)
		{
			x += ((m_TotalSize.cx - m_ItemTotalSize.cx) / 2);
		}
		else
		{
			x += ((m_TotalSize.cx - m_ItemTotalSize.cx) / 2);

			x += 1;
		}
	}

	for (HYVEC_TREENODEITEM::iterator iter = m_VecItem.begin(); iter != m_VecItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		pItem->AdjustLayout(x, y);

		x = x + pItem->m_TotalSize.cx + TREE_ITEM_CHILDDISTANCEX;
	}
}

void HYXTreeNodeItem::AdjustFrameRect(int x, int y)
{
	m_FrameRect.left = x;
	m_FrameRect.right = x + m_TotalSize.cx;
	m_FrameRect.top = y;
	m_FrameRect.bottom = y + m_TotalSize.cy;
}

void HYXTreeNodeItem::SetInputIndex(int n)
{
	m_InputIndex = n;
}

int HYXTreeNodeItem::GetInputIndex()
{
	return m_InputIndex;
}