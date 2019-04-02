#include "StdAfx.h"
#include "XBaseRibbonBarManage.h"


XBaseRibbonBarManage::XBaseRibbonBarManage(void)
{
}


XBaseRibbonBarManage::~XBaseRibbonBarManage(void)
{
}

void XBaseRibbonBarManage::SetDelegate(XDelegateRibbonBarManage* p)
{
	m_pDelegate = p;
}
