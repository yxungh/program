#include "StdAfx.h"
#include "XBaseInternalManage.h"


XBaseInternalManage::XBaseInternalManage(void)
{
}


XBaseInternalManage::~XBaseInternalManage(void)
{
}

void XBaseInternalManage::SetDelegate(XDelegateInternalManage* p)
{
	m_pDelegate = p;
}
