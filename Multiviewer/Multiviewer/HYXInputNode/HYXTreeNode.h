#pragma once

#include "XConstantIM.h"

#define TREE_EXPANDBTN_WIDTH			20					//扩展按钮宽度
#define TREE_EXPANDBTN_HEIGHT			20					//扩展按钮高度
#define TREE_ITEM_DISTANCEX				25					//项水平间隔
#define TREE_ITEM_CHILDDISTANCEX		10					//项子项水平间隔
#define TREE_ITEM_CHILDDISTANCEY		20					//项子项垂直间隔
#define TREE_ITEM_INSIDEDISTANCEY		2					//项内部垂直间隔
#define TREE_TREE_ITEM_FONTSIZE			20					//项字体大小
#define TREE_ITEM_WIDTHMIN				43					//项最小宽度,因为表格项的选择宽度为20，有两个

class HYXInputNode;

class HYXTreeNode
{
public:
	HYXTreeNode(void);
	~HYXTreeNode(void);

public:

	//初始化
	void Init();

	//清除数据
	void ClearData();

	//设置节点
	void SetNodes(HYXInputNode* p);

	//绘制
	void Draw(CDC* pDC, CRect rt, CRect drawRect);

	//处理鼠标左键提起
	void HandleLButtonUP(CPoint p);

	//获取滚动宽度
	int GetScrollWidth();

	//获取文字大小
	CSize GetTextSize(CString s);

	//添加项
	HYXTreeNodeItem* AddItem(int nType, CString szName, void* pData,
		HYXTreeNodeItem* pParent = NULL);

	//调整布局
	void AdjustLayout();

	//扩展按钮点击
	void ExpandBtnClick(int nType, void* pData);

	//节点改变
	void NodeItemChange(HYXTreeNodeItem* pItem);

	//获取项集合
	HYVEC_TREENODEITEM& GetVecItem();

	//获取项文字颜色
	COLORREF GetTreeNodeItemTextColor(HYXTreeNodeItem* pItem);

private:

	//清除节点集合
	void ClearVecNode();

	//初始化字体
	void InitFont();

private:

	//节点
	HYXInputNode* m_Node;

	//字体
	CFont m_Font;

	//项集合
	HYVEC_TREENODEITEM m_VecItem;
};

