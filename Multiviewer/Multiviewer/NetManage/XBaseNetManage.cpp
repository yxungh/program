#include "StdAfx.h"
#include "XBaseNetManage.h"


XBaseNetManage::XBaseNetManage(void)
{
}


XBaseNetManage::~XBaseNetManage(void)
{
}

void XBaseNetManage::SetDelegate(XDelegateNetManage* p)
{
	m_pDelegate = p;
}
