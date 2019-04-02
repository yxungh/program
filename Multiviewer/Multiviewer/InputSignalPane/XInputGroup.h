#pragma once
#include "XConstantIM.h"

class XInputInfoInGroup;

class XInputGroup
{
public:

	XInputGroup();
	~XInputGroup();

public:

	VEC_INPUTINFOINGROUP& GetVecInputInGroup();

	void SetVecInputInGroup(VEC_INPUTINFOINGROUP Vec);

	void AddVecInputGroup(XInputInfoInGroup* pInput);

	void SetGroupName(CString szName);

	CString GetGroupName();

	int GetType();

	void SetType(int nType);

	void SetTreeItem(HTREEITEM h);

	HTREEITEM GetTreeItem();

	void ClearVecInput();

private:

	CString m_szGroupName;

	VEC_INPUTINFOINGROUP m_VecInputInGroup;

	int m_nType;

	HTREEITEM m_TreeItem;
};