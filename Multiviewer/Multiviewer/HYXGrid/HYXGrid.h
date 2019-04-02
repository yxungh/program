#pragma once

#include "XConstantIM.h"

class HYXDelegateGrid;

class HYXGrid : public CWnd
{
	DECLARE_DYNAMIC(HYXGrid)

public:
	HYXGrid();
	virtual ~HYXGrid();

	virtual void PreSubclassWindow();

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	virtual ULONG GetGestureStatus(CPoint ptTouch);
	
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	 
public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(HYXDelegateGrid* p);

	//调整水平滚动条
	void AdjustScrollH();

	//调整垂直滚动条
	void AdjustScrollV();

	//调整网格
	void AdjustGrid();

protected:

	//绘制
	void Draw(CDC* pDC, CRect rt);

	//绘制直线
	void DrawLine(CDC* pDC, CRect rect, CRect drawRect);

	//绘制表格
	virtual void DrawGrid(CDC* pDC, CRect drawRect);

	//清除表格行集合
	void ClearVecGridRow();

	//获取表格行
	HYXGridRow* GetGridRow(HYXVTreeNodeItem* pNodeItem);

	//获取表格行
	HYXGridRow* GetGridRow(int nOutputID);

	//设置表格行显示状态
	void SetGridRowShow(BOOL b);

	//初始化字体
	void InitFont();

	//清除节点权限信息集合
	void ClearMapNodePower();

	//处理鼠标左键提起
	void HandleLButtonUP(CPoint p);

private:

	//委托
	HYXDelegateGrid* m_Delegate;

	//字体
	CFont m_Font;

private:

	BOOL m_bScrollTimerH;

	int m_nScrollPosH;

	int m_nScrollTimerH;

	int m_ScrollPosH;

private:

	BOOL m_bScrollTimerV;

	int m_nScrollPosV;

	int m_nScrollTimerV;

	int m_ScrollPosV;

protected:

	//表格行集合，用于查找
	HYMAP_GRIDROW m_MapGridRow;

	//表格行集合
	HYVEC_GRIDROW m_VecGridRow;

	//水平直线集合
	HYVEC_NUM m_VecLineX;

	//垂直直线集合
	HYVEC_NUM m_VecLineY;

	//是否按下
	BOOL m_bDown;
};


