#include "StdAfx.h"
#include "XInputSignalExpand.h"

XInputSignalExpand::XInputSignalExpand()
{
	m_TreeItem = NULL;

	m_InputSignal = NULL;

	m_CanEdit = TRUE;

	m_ID = 0;
}

XInputSignalExpand::~XInputSignalExpand(void)
{
	
}

void XInputSignalExpand::SetExpand(XExpandInfo* pInfo)
{
	m_ExpandInfo = *pInfo;
}

void XInputSignalExpand::SetName(CString s)
{
	m_szName = s;
}

XExpandInfo* XInputSignalExpand::GetExpandInfo()
{
	return &m_ExpandInfo;
}

XSignalCutInfo* XInputSignalExpand::GetSignalCutInfo()
{
	return &m_CutInfo;
}

CString XInputSignalExpand::GetName()
{
	return m_szName;
}

void XInputSignalExpand::SetTreeItem(HTREEITEM h)
{
	m_TreeItem = h;
}

HTREEITEM XInputSignalExpand::GetTreeItem()
{
	return m_TreeItem;
}

XInputSignal* XInputSignalExpand::GetInputSignal()
{
	return m_InputSignal;
}

void XInputSignalExpand::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XInputSignalExpand::SetCanEdit(BOOL b)
{
	m_CanEdit = b;
}

BOOL XInputSignalExpand::GetCanEdit()
{
	return m_CanEdit;
}

void XInputSignalExpand::SetID(int n)
{
	m_ID = n;
}

int XInputSignalExpand::GetID()
{
	return m_ID;
}
