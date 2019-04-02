#pragma once

#include "XConstantIM.h"
#include "HYXVTreeNode.h"

class HYXDelegateOutputNode;

class HYXOutputNode : public CWnd
{
	DECLARE_DYNAMIC(HYXOutputNode)

public:
	HYXOutputNode();
	virtual ~HYXOutputNode();

	virtual void PreSubclassWindow();

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	
public:

	//初始化
	void Init();

	//清除数据
	void ClearData();

	//设置委托
	void SetDelegate(HYXDelegateOutputNode* p);

	//获取滚动高度
	int GetScrollHeight();

	//滚动
	void Scroll(int nPos);

	//刷新区域
	void InvalidateRect();

	//获取CWnd
	CWnd* GetWnd();

	//扩展按钮点击
	void ExpandBtnClick(int nType, void* pData);

	//设置输出信息
	void SetOutputInfo(int nOutputCount);

	//节点改变
	void NodeItemChange();

	//获取展开设备项集合
	void GetExpandDeviceItem(HYVEC_VTREENODEITEM& VecItem);

	//获取项文字颜色
	virtual COLORREF GetTreeNodeItemTextColor(HYXVTreeNodeItem* pItem);

private:

	//绘制
	void Draw(CDC* pDC, CRect rt);

	//获取楼层项
	HYXVTreeNodeItem* GetLayerItem(CString szID);

	//获取设备项
	HYXVTreeNodeItem* GetClassItem(CString szID);

private:

	//委托
	HYXDelegateOutputNode* m_Delegate;

	//滚动位置
	int m_ScrollPos;

	//是否按下
	BOOL m_bDown;

	//节点
	HYXVTreeNode m_TreeNode;
};


