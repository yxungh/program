// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "HYXOutputNode.h"
#include "HYXDelegateOutputNode.h"
#include "HYXVTreeNodeItem.h"

// HYXOutputNode

IMPLEMENT_DYNAMIC(HYXOutputNode, CWnd)

HYXOutputNode::HYXOutputNode()
{
	m_ScrollPos = 0;

	m_bDown = FALSE;

	m_Delegate = NULL;
}

HYXOutputNode::~HYXOutputNode()
{

}

BEGIN_MESSAGE_MAP(HYXOutputNode, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// HYXOutputNode 消息处理程序

BOOL HYXOutputNode::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx(0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

void HYXOutputNode::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void HYXOutputNode::SetDelegate(HYXDelegateOutputNode* p)
{
	m_Delegate = p;
}

void HYXOutputNode::ClearData()
{
	m_TreeNode.ClearData();
}

BOOL HYXOutputNode::OnEraseBkgnd(CDC* pDC)
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

void HYXOutputNode::Draw(CDC* pDC, CRect rt)
{
	//填充背景颜色
	CBrush bruDB;
	bruDB.CreateSolidBrush(RGB(244, 249, 252));

	pDC->FillRect(&rt, &bruDB);

	//设置偏移位置
	pDC->SetWindowOrg(0, m_ScrollPos);

	//绘图区域,节点在绘图区域才进行绘制
	CRect drawRect(CPoint(0, m_ScrollPos), CSize(rt.Width(), rt.Height()));

	//绘制节点
	m_TreeNode.Draw(pDC, rt, drawRect);

	//还原偏移位置
	pDC->SetWindowOrg(0, 0);
}

void HYXOutputNode::Init()
{
	m_TreeNode.SetNodes(this);
	m_TreeNode.Init();
}

CWnd* HYXOutputNode::GetWnd()
{
	return this;
}

void HYXOutputNode::InvalidateRect()
{
	Invalidate(TRUE);
}

void HYXOutputNode::Scroll(int nPos)
{
	m_ScrollPos = nPos;

	InvalidateRect();
}

void HYXOutputNode::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;

	CWnd::OnLButtonDown(nFlags, point);
}

int HYXOutputNode::GetScrollHeight()
{
	return m_TreeNode.GetScrollHeight();
}

void HYXOutputNode::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		CPoint temp;
		temp.x = point.x;
		temp.y = point.y + m_ScrollPos;

		m_TreeNode.HandleLButtonUP(temp);

		m_bDown = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void HYXOutputNode::ExpandBtnClick(int nType, void* pData)
{
}

void HYXOutputNode::GetExpandDeviceItem(HYVEC_VTREENODEITEM& VecItem)
{
	HYVEC_VTREENODEITEM& VecTreeItem = m_TreeNode.GetVecItem();

	for (HYVEC_VTREENODEITEM::iterator iter = VecTreeItem.begin(); iter != VecTreeItem.end(); iter++)
	{
		HYXVTreeNodeItem* pItem = *iter;

		if (!pItem->GetExpand())
		{
			continue;
		}

		VecItem.push_back(pItem);
	}
}

void HYXOutputNode::SetOutputInfo(int nOutputCount)
{
	for (int i = 1; i <= nOutputCount; i++)
	{
		CString szTemp;
		szTemp.Format(_T("%s %d"), m_Delegate->GetTranslationString(_T("374"), _T("输出")), i);
	
		HYXVTreeNodeItem* pItem = m_TreeNode.AddItem(HYITEMTYPE_DEVICE, szTemp, NULL);

		pItem->SetOutputIndex(i);

		pItem->SetRoot(TRUE);

		pItem->CalculateTotalSize();
	}

	NodeItemChange();
}

void HYXOutputNode::NodeItemChange()
{
	m_TreeNode.AdjustLayout();

	m_Delegate->AdjustScrollV();

	m_Delegate->AdjustGrid();

	InvalidateRect();
}


COLORREF HYXOutputNode::GetTreeNodeItemTextColor(HYXVTreeNodeItem* pItem)
{
	return RGB(0, 0, 0);
}