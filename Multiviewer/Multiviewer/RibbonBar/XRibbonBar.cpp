#include "StdAfx.h"
#include "XRibbonBar.h"
#include "XDelegateRibbonBar.h"

IMPLEMENT_DYNAMIC(XRibbonBar, CMFCRibbonBar)

BEGIN_MESSAGE_MAP(XRibbonBar, CMFCRibbonBar)
END_MESSAGE_MAP()


XRibbonBar::XRibbonBar(void)
{
	m_pDelegate = NULL;
}

XRibbonBar::~XRibbonBar(void)
{
}

/***********************************************************
** 功能描述: 设置委托
************************************************************/
void XRibbonBar::SetDelegate(XDelegateRibbonBar* p)
{
	m_pDelegate = p;
}

/***********************************************************
** 功能描述: 禁用工具栏上的小图标，防止点击弹出菜单
************************************************************/
BOOL XRibbonBar::OnShowRibbonContextMenu(CWnd* pWnd, int x, int y, CMFCRibbonBaseElement* pHit)
{
	return FALSE;
}

BOOL XRibbonBar::SetActiveCategory(CMFCRibbonCategory* pCategory, BOOL bForceRestore)
{
	CMFCRibbonBar::SetActiveCategory(pCategory,bForceRestore);

	if (NULL != m_pDelegate)
	{
		//获取显示页面名称
		LPCTSTR lpName = pCategory->GetName();

		m_pDelegate->RibbonBarShowCategory(lpName);
	}

	return true;
}
