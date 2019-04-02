#include "stdafx.h"
#include "XInputGroup.h"
#include "XInputSignal.h"
#include "XInputInfoInGroup.h"

XInputGroup::XInputGroup()
{
	m_szGroupName=_T("");

	m_TreeItem=NULL;

	m_nType=-1;
}

XInputGroup::~XInputGroup()
{
	ClearVecInput();
}

void XInputGroup::ClearVecInput()
{
	for(VEC_INPUTINFOINGROUP::iterator iter=m_VecInputInGroup.begin();iter!=m_VecInputInGroup.end();++iter)
	{
		delete *iter;
	}

	m_VecInputInGroup.clear();
}

VEC_INPUTINFOINGROUP& XInputGroup::GetVecInputInGroup()
{
	return m_VecInputInGroup;
}

void XInputGroup::SetVecInputInGroup(VEC_INPUTINFOINGROUP Vec)
{
	m_VecInputInGroup=Vec;
}

void XInputGroup::AddVecInputGroup(XInputInfoInGroup* pInput)
{
	if(pInput!=NULL)
	{
		m_VecInputInGroup.push_back(pInput);
	}
}


void XInputGroup::SetGroupName(CString szName)
{
	m_szGroupName=szName;
}

CString XInputGroup::GetGroupName()
{
	return m_szGroupName;
}

int XInputGroup::GetType()
{
	m_nType=ITEMTYPE_INPUTGROUP;

	return m_nType;
}

void XInputGroup::SetType(int nType)
{
	m_nType=nType;
}

void XInputGroup::SetTreeItem(HTREEITEM h)
{
	m_TreeItem=h;
}

HTREEITEM XInputGroup::GetTreeItem()
{
	return m_TreeItem;
}