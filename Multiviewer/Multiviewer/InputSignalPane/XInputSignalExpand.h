#pragma once

#include "XExpandInfo.h"
#include "XSignalCutInfo.h"

class XInputSignal;

class XInputSignalExpand
{
public:
	XInputSignalExpand(void);
	~XInputSignalExpand(void);

	//设置输入信号
	void SetInputSignal(XInputSignal* p);

	void SetExpand(XExpandInfo* pInfo);

	void SetName(CString s);

	//设置树形控件所在项
	void SetTreeItem(HTREEITEM h);

	//设置是否能编辑
	void SetCanEdit(BOOL b);

	//设置ID
	void SetID(int n);

	XExpandInfo* GetExpandInfo();

	XSignalCutInfo* GetSignalCutInfo();

	CString GetName();

	//获取树形控件所在项
	HTREEITEM GetTreeItem();

	//获取输入信号
	XInputSignal* GetInputSignal();

	//获取是否能编辑
	BOOL GetCanEdit();

	//获取ID
	int GetID();

private:

	//输入信号
	XInputSignal* m_InputSignal;

	//树形控件所在项
	HTREEITEM m_TreeItem;

	XExpandInfo m_ExpandInfo;

	//输入裁剪
	XSignalCutInfo m_CutInfo;

	CString m_szName;

	//是否能编辑
	BOOL m_CanEdit;

	//ID
	int m_ID;

};

