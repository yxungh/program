#include "StdAfx.h"
#include "XBaseTranslationManage.h"


XBaseTranslationManage::XBaseTranslationManage(void)
{
}


XBaseTranslationManage::~XBaseTranslationManage(void)
{
}

/***********************************************************
** 功能描述: 设置委托
************************************************************/
void XBaseTranslationManage::SetDelegate(XDelegateTranslationManage* p)
{
	m_pDelegate = p;
}

