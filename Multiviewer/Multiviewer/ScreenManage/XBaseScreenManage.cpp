#include "StdAfx.h"
#include "XBaseScreenManage.h"
#include "XMultiVideoWindow.h"


XBaseScreenManage::XBaseScreenManage(void)
{
	m_View=NULL;

	m_pMultiVideoWindow=NULL;

	m_szTitle=_T("");

}


XBaseScreenManage::~XBaseScreenManage(void)
{
}

void XBaseScreenManage::SetDelegate(XDelegateScreenManage* p)
{
	m_pDelegate = p;
}

XDelegateScreenManage* XBaseScreenManage::GetDelegate()
{
	return m_pDelegate;
}

CString XBaseScreenManage::GetTitle()
{
	return m_szTitle;
}

CMultiviewerView* XBaseScreenManage::GetView()
{
	return m_View;
}
void XBaseScreenManage::SetTitle(CString s)
{
	m_szTitle=s;
}
void XBaseScreenManage::SetView(CMultiviewerView* p)
{
	m_View=p;
}

void XBaseScreenManage::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_pMultiVideoWindow=p;
}

XMultiVideoWindow* XBaseScreenManage::GetMultiVideoWIndow()
{
	return m_pMultiVideoWindow;
}