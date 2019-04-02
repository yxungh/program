// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "HYXInputNode.h"
#include "HYXTreeNodeItem.h"
#include "HYXDelegateInputNode.h"

// HYXInputNode

IMPLEMENT_DYNAMIC(HYXInputNode, CWnd)

HYXInputNode::HYXInputNode()
{
	m_ScrollPos = 0;

	m_bDown = FALSE;

	m_Delegate = NULL;
}

HYXInputNode::~HYXInputNode()
{

}

BEGIN_MESSAGE_MAP(HYXInputNode, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// HYXInputNode 消息处理程序

BOOL HYXInputNode::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx(0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void HYXInputNode::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void HYXInputNode::SetDelegate(HYXDelegateInputNode* p)
{
	m_Delegate = p;
}

void HYXInputNode::ClearData()
{
	m_TreeNode.ClearData();
}

BOOL HYXInputNode::OnEraseBkgnd(CDC* pDC)
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

void HYXInputNode::Draw(CDC* pDC, CRect rt)
{
	//填充背景颜色
	CBrush bruDB;
	bruDB.CreateSolidBrush(RGB(244, 249, 252));

	pDC->FillRect(&rt, &bruDB);

	//设置偏移位置
	pDC->SetWindowOrg(m_ScrollPos, 0);

	//绘图区域,节点在绘图区域才进行绘制
	CRect drawRect(CPoint(m_ScrollPos, 0), CSize(rt.Width(), rt.Height()));

	//绘制节点
	m_TreeNode.Draw(pDC, rt, drawRect);

	//还原偏移位置
	pDC->SetWindowOrg(0, 0);
}

void HYXInputNode::Init()
{
	m_TreeNode.SetNodes(this);
	m_TreeNode.Init();
}

CWnd* HYXInputNode::GetWnd()
{
	return this;
}

void HYXInputNode::InvalidateRect()
{
	Invalidate(TRUE);
}

void HYXInputNode::Scroll(int nPos)
{
	m_ScrollPos = nPos;

	InvalidateRect();
}

void HYXInputNode::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;

	CWnd::OnLButtonDown(nFlags, point);
}

int HYXInputNode::GetScrollWidth()
{
	return m_TreeNode.GetScrollWidth();
}

void HYXInputNode::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		CPoint temp;
		temp.x = point.x + m_ScrollPos;
		temp.y = point.y;

		m_TreeNode.HandleLButtonUP(temp);

		m_bDown = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void HYXInputNode::ExpandBtnClick(int nType, void* pData)
{

}

void HYXInputNode::GetExpandDeviceItem(HYVEC_TREENODEITEM& VecItem)
{
	HYVEC_TREENODEITEM& VecTreeItem = m_TreeNode.GetVecItem();

	for (HYVEC_TREENODEITEM::iterator iter = VecTreeItem.begin(); iter != VecTreeItem.end(); iter++)
	{
		HYXTreeNodeItem* pItem = *iter;

		if (!pItem->GetExpand())
		{
			continue;
		}

		VecItem.push_back(pItem);
	}
}

void HYXInputNode::SetInputInfo(int nInputCount)
{
	for (int i = 1; i <= nInputCount; i++)
	{
		CString szTemp;
		szTemp.Format(_T("%s %d"), m_Delegate->GetTranslationString(_T("373"), _T("输入")), i);

		HYXTreeNodeItem* pItem = m_TreeNode.AddItem(HYITEMTYPE_DEVICE, szTemp, NULL);

		pItem->SetRoot(TRUE);

		pItem->SetInputIndex(i);

		pItem->CalculateTotalSize();
	}

	NodeItemChange();
}

void HYXInputNode::NodeItemChange()
{
	m_TreeNode.AdjustLayout();

	m_Delegate->AdjustScrollH();

	m_Delegate->AdjustGrid();

	InvalidateRect();
}

COLORREF HYXInputNode::GetTreeNodeItemTextColor(HYXTreeNodeItem* pItem)
{
	return RGB(0, 0, 0);
}