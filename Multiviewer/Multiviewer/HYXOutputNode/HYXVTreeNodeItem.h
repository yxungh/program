#pragma once

#include "XConstantIM.h"
#include "HYXTreeNode.h"

class HYXVTreeNode;

class HYXVTreeNodeItem
{
public:
	HYXVTreeNodeItem(void);
	~HYXVTreeNodeItem(void);

public:

	//设置数据
	void SetData(void* p);

	//设置名称
	void SetName(CString s);

	//设置树节点
	void SetTreeNode(HYXVTreeNode* p);
	
	//设置类型
	void SetType(int nType);

	//设置是否有子信息
	void SetHaveChildInfo(BOOL b);

	//设置是否获取子信息
	void SetGetChildInfo(BOOL b);

	//设置扩展
	void SetExpand(BOOL b);

	//设置父节点
	void SetParentItem(HYXVTreeNodeItem* p);

	//设置是否根据
	void SetRoot(BOOL b);

	void SetOutputIndex(int n);

	int GetOutputIndex();

	//获取数据
	void* GetData();

	//获取名称
	CString GetName();

	//获取类型
	int GetType();

	//获取是否展开
	BOOL GetExpand();

	//获取展开按钮区域
	CRect GetExpandBtnRect();

	//获取根项
	HYXVTreeNodeItem* GetRootItem();

	//获取项集合
	HYVEC_VTREENODEITEM& GetVecItem();

	//绘制
	void Draw(CDC* pDC, CRect rect);

	//获取边框区域
	CRect GetFrameRect();

	//调整布局
	void AdjustLayout(int x, int y);

	//处理鼠标左键提起
	void HandleLButtonUP(CPoint p);

	//添加项
	void AddItem(HYXVTreeNodeItem* p);

	//计算总区域大小
	void CalculateTotalSize();

	//清除项集合
	void ClearVecItem();

private:

	//调整文字区域
	void AdjustTextRect(int x, int y);

	//调整展开按钮区域区域
	void AdjustExpandBtnRect(int x, int y);

	//调整子项区域
	void AdjustItemRect(int x, int y);

	//调整边框区域
	void AdjustFrameRect(int x, int y);

	//清除数据
	void ClearData();

	//绘制扩展按钮
	void DrawExpandBtn(CDC* pDC);

	//绘制子项
	void DrawChildItem(CDC* pDC, CRect rect);
	
	//绘制直线
	void DrawLine(CDC* pDC, CRect rect);

	//设置项总区域大小
	CSize GetItemTotalSize();

	//计算子项总区域大小
	void CalculateItemTotalSize();

private:

	//树节点
	HYXVTreeNode* m_TreeNode;

	//父节点
	HYXVTreeNodeItem* m_ParentItem;

	//节点类型
	int m_Type;

	//数据
	void* m_Data;

	//名称
	CString m_Name;

	//是否获取子信息
	BOOL m_GetChildInfo;

	//是否展开
	BOOL m_Expand;

	//是否有子信息
	BOOL m_HaveChildInfo;

	//是否根项
	BOOL m_Root;

	//项高度
	int m_ItemHeight;

	//文字大小
	CSize m_TextSize;

	//总区域大小
	CSize m_TotalSize;

	//子项宽度
	CSize m_ItemTotalSize;

	//展开按钮区域
	CRect m_ExpandBtnRect;

	//文字区域
	CRect m_TextRect;

	//边框区域
	CRect m_FrameRect;

	//项集合
	HYVEC_VTREENODEITEM m_VecItem;

	int m_OutputIndex;
};