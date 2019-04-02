#pragma once

#include "XConstantIM.h"

class HYXTreeNodeItem;

class HYXGridRow
{
public:
	HYXGridRow(void);
	~HYXGridRow(void);

public:

	//获取项
	HYXGridItem* GetItem(HYXTreeNodeItem* pNodeItem);

	//获取项
	HYXGridItem* GetItem(int nInputID);

	//获取项集合
	HYVEC_GRIDITEM& GetVecItem();

	//设置垂直结点项
	void SetVNodeItem(HYXVTreeNodeItem* p);

	//获取是否显示
	BOOL GetShow();

	//设置是否显示
	void SetShow(BOOL b);

	//设置项显示状态
	void SetItemShow(BOOL b);

	//获取垂直结点项
	HYXVTreeNodeItem* GetVNodeItem();

	//获取输出序号
	int GetOutputIndex();

private:

	//清除项集合
	void ClearVecItem();

private:

	//项集合,用于查找
	HYMAP_GRIDITEM m_MapItem;

	//项集合
	HYVEC_GRIDITEM m_VecItem;

	//垂直结点项
	HYXVTreeNodeItem* m_VNodeItem;

	//是否显示
	BOOL m_Show;
};

