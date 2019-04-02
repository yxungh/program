#pragma once

#include "XConstantIM.h"

class HYXTreeNode;

class HYXTreeNodeItem
{
public:
	HYXTreeNodeItem(void);
	~HYXTreeNodeItem(void);

public:

	//设置数据
	void SetData(void* p);

	//设置名称
	void SetName(CString s);

	//设置树节点
	void SetTreeNode(HYXTreeNode* p);
	
	//设置类型
	void SetType(int nType);

	//设置是否有子信息
	void SetHaveChildInfo(BOOL b);

	//设置是否获取子信息
	void SetGetChildInfo(BOOL b);

	//设置扩展
	void SetExpand(BOOL b);

	//设置父节点
	void SetParentItem(HYXTreeNodeItem* p);

	//设置是否根据
	void SetRoot(BOOL b);

	void SetInputIndex(int n);

	int GetInputIndex();

	//获取数据
	void* GetData();

	//获取名称
	CString GetName();

	//获取类型
	int GetType();

	//获取是否展开
	BOOL GetExpand();

	//获取根项
	HYXTreeNodeItem* GetRootItem();

	//获取项集合
	HYVEC_TREENODEITEM& GetVecItem();

	//绘制
	void Draw(CDC* pDC, CRect rt);

	//获取边框区域
	CRect GetFrameRect();

	//调整布局
	void AdjustLayout(int x, int y);

	//处理鼠标左键提起
	void HandleLButtonUP(CPoint p);

	//添加项
	void AddItem(HYXTreeNodeItem* p);

	//计算总区域大小
	void CalculateTotalSize();

	//清除项集合
	void ClearVecItem();

private:

	//调整文字区域
	void AdjustTextRect(int centerX, int y);

	//调整展开按钮区域区域
	void AdjustExpandBtnRect(int centerX, int y);

	//调整子项区域
	void AdjustItemRect(int x, int y);

	//调整边框区域
	void AdjustFrameRect(int x, int y);

	//清除数据
	void ClearData();

	//绘制扩展按钮
	void DrawExpandBtn(CDC* pDC);

	//绘制子项
	void DrawChildItem(CDC* pDC, CRect rt);

	//绘制直线
	void DrawLine(CDC* pDC, CRect rt);

	//设置项总区域大小
	CSize GetItemTotalSize();

	//计算子项总区域大小
	void CalculateItemTotalSize();

private:

	//树节点
	HYXTreeNode* m_TreeNode;

	//父节点
	HYXTreeNodeItem* m_ParentItem;

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
	HYVEC_TREENODEITEM m_VecItem;

	int m_InputIndex;
};