#pragma once

#include "XConstantIM.h"
#include "HYXTreeNode.h"

class HYXDelegateInputNode;

class HYXInputNode : public CWnd
{
	DECLARE_DYNAMIC(HYXInputNode)

public:
	HYXInputNode();
	virtual ~HYXInputNode();

	virtual void PreSubclassWindow();

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	
public:

	//初始化
	void Init();

	//清除数据
	void ClearData();

	//设置委托
	void SetDelegate(HYXDelegateInputNode* p);

	//获取滚动宽度
	int GetScrollWidth();

	//滚动
	void Scroll(int nPos);

	//刷新区域
	void InvalidateRect();

	//获取CWnd
	CWnd* GetWnd();

	//扩展按钮点击
	void ExpandBtnClick(int nType, void* pData);

	//设置输入信息
	void SetInputInfo(int nInputCount);

	//节点改变
	void NodeItemChange();

	//获取展开设备项集合
	void GetExpandDeviceItem(HYVEC_TREENODEITEM& VecItem);

	//获取项文字颜色
	virtual COLORREF GetTreeNodeItemTextColor(HYXTreeNodeItem* pItem);

private:

	//绘制
	void Draw(CDC* pDC, CRect rt);

private:

	//委托
	HYXDelegateInputNode* m_Delegate;

	//滚动位置
	int m_ScrollPos;

	//是否按下
	BOOL m_bDown;

	//节点
	HYXTreeNode m_TreeNode;
};


