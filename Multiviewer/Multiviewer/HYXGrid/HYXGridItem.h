#pragma once

class HYXVTreeNodeItem;
class HYXTreeNodeItem;
class HYXGridRow;
class PROTOCOL_DeviceInfo;

#define ITEM_SECECTWIDTH		20
#define ITEM_SECECTHEIGHT		20
#define ITEM_SECECTDISTANCEX	3

class HYXGridItem
{
public:
	HYXGridItem(void);
	~HYXGridItem(void);

	//设置垂直结点项
	void SetVNodeItem(HYXVTreeNodeItem* p);

	//设置水平结点项
	void SetHNodeItem(HYXTreeNodeItem* p);

	void SetGridRow(HYXGridRow* p);

	//获取垂直结点项
	HYXVTreeNodeItem* GetVNodeItem();

	//获取水平结点项
	HYXTreeNodeItem* GetHNodeItem();

	HYXGridRow* GetGridRow();

	//获取是否显示
	BOOL GetShow();

	//设置是否显示
	void SetShow(BOOL b);

	//调整区域
	void AdjustRect();

	//获取区域
	CRect GetRect();

	//获取输入序号
	int GetInputIndex();

	//获取输出序号
	int GetOutputIndex();

private:

	HYXVTreeNodeItem* m_VNodeItem;

	HYXTreeNodeItem* m_HNodeItem;

	HYXGridRow* m_GridRow;

	//是否显示
	BOOL m_Show;

	//区域
	CRect m_Rect;
};

