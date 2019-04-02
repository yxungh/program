#include "stdafx.h"
#include "XMyTabCtrl.h"



IMPLEMENT_DYNAMIC(XMyTabCtrl, CMFCTabCtrl)

XMyTabCtrl::XMyTabCtrl()
{
}

XMyTabCtrl::~XMyTabCtrl()
{

}

BEGIN_MESSAGE_MAP(XMyTabCtrl, CMFCTabCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL XMyTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

CWnd* XMyTabCtrl::FindTargetWnd(const CPoint& point)
{
	//这里不用实现，调用基类FindTargetWnd

	//if (point.y < m_nTabsHeight)
	//{
	//	return NULL;
	//}

	//for (int i = 0; i < m_iTabsNum; i ++)
	//{
	//	CMFCTabInfo* pTab = (CMFCTabInfo*) m_arTabs [i];
	//	ASSERT_VALID(pTab);

	//	if (!pTab->GetVisible())
	//		continue;

	//	if (pTab->GetRect().PtInRect(point))
	//	{
	//		return NULL;
	//	}
	//}

	//CWnd* pWndParent = GetParent();
	//ASSERT_VALID(pWndParent);

	return NULL;
}

void XMyTabCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnLButtonDblClk(nFlags, point);
}

