#pragma once

class XDelegateScreenMoveGrid;
class XScreenMoveInfo;

class XScreenMoveGrid:public CWnd
{
	DECLARE_DYNAMIC(XScreenMoveGrid)

public:
	XScreenMoveGrid();
	virtual ~XScreenMoveGrid();

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
	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	void SetDelegate(XDelegateScreenMoveGrid* p);

	void SetScreenMoveInfo(XScreenMoveInfo* pInfo);

	//重置
	void Reset();

	//调整网格区域位置
	void AdustGridRectPos();

	//重置-对话框大小改变
	void ResetByDlgSizeChange();

protected:

	//调整滚动条
	void AdjustScroll();

	//调整水平滚动条
	void AdjustScrollH();

	//调整垂直滚动条
	void AdjustScrollV();

	//绘制
	void Draw(CDC* pDC, CRect rt);

	//绘制网格
	void DrawGrid(CDC* pDC, CRect drawRect);

	//清除网格区域数组
	void ClearGridRectArr();

	//设置网格区域数组
	void SetGridRectArr();

	//重置滚动条
	void ResetScroll();

private:

	BOOL m_bScrollTimerH;

	int m_nScrollPosH;

	int m_nScrollTimerH;

private:

	BOOL m_bScrollTimerV;

	int m_nScrollPosV;

	int m_nScrollTimerV;

protected:

	XDelegateScreenMoveGrid* m_pDelegate;

	XScreenMoveInfo* m_MoveInfo;

	int m_GridCountH;

	int m_GridCountV;

	int m_GridWidth;

	int m_GridHeight;

	//网格区域数组
	CRect* m_GridRectArr;

	//是否按下
	BOOL m_bDown;
};