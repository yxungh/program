#pragma once

#include "XConstantIM.h"

#define HTREE_EXPANDBTN_WIDTH			20					//扩展按钮宽度
#define HTREE_EXPANDBTN_HEIGHT			20					//扩展按钮高度
#define HTREE_LEFTWIDTH					27					//项左边宽度
#define HTREE_CHILDITEM_INDENTATION		20					//子项缩进间隔
#define HTREE_ITEM_DISTANCEY			15					//项垂直间隔

class HYXOutputNode;

class HYXVTreeNode
{
public:
	HYXVTreeNode(void);
	~HYXVTreeNode(void);

public:

	//初始化
	void Init();

	//清除数据
	void ClearData();

	//设置节点
	void SetNodes(HYXOutputNode* p);

	//绘制
	void Draw(CDC* pDC, CRect rect, CRect drawRect);

	//处理鼠标左键提起
	void HandleLButtonUP(CPoint p);

	//获取滚动高度
	int GetScrollHeight();

	//获取文字大小
	CSize GetTextSize(CString s);

	//获取楼层项
	HYXVTreeNodeItem* GetLayerItem(CString szID);

	//获取设备项
	HYXVTreeNodeItem* GetClassItem(CString szID);

	//添加项
	HYXVTreeNodeItem* AddItem(int nType, CString szName, void* pData,
		HYXVTreeNodeItem* pParent = NULL);

	//调整布局
	void AdjustLayout();

	//扩展按钮点击
	void ExpandBtnClick(int nType, void* pData);

	//节点改变
	void NodeItemChange(HYXVTreeNodeItem* pItem);

	//获取项集合
	HYVEC_VTREENODEITEM& GetVecItem();

	//获取项文字颜色
	COLORREF GetTreeNodeItemTextColor(HYXVTreeNodeItem* pItem);

private:

	//清除节点集合
	void ClearVecNode();

	//初始化字体
	void InitFont();

private:

	//节点
	HYXOutputNode* m_Node;

	//字体
	CFont m_Font;

	//项集合
	HYVEC_VTREENODEITEM m_VecItem;
};

