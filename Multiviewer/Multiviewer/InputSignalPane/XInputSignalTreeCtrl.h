#pragma once

#include "XDragInfo.h"

class XInputSignalPane;
class XDragWnd;

class XInputSignalTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(XInputSignalTreeCtrl)

public:
	XInputSignalTreeCtrl();
	virtual ~XInputSignalTreeCtrl();

	virtual ULONG GetGestureStatus(CPoint ptTouch);

protected:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:

	void SetInputSignalPane(XInputSignalPane* p);

private:

	//显示菜单
	void ShowMenu();

	//创建拖动窗口
	void CreateDragWnd();

	//移动拖动窗口
	void MoveDragWnd(CPoint& point);

	//移动拖动窗口结束
	void MoveDragWndEnd();

	void SetVecInputSignalIndexAndID(int nIndex);

	void CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd);

public:

	void DragDataInfo(HTREEITEM hItem);

private:

	XInputSignalPane* m_InputSignalPane;

private:

	BOOL m_Drag;

	CPoint m_DragPoint;

	XDragWnd* m_DragWnd;

	//拖动信息
	XDragInfo m_DragInfo;

	CRect rect;

private:

	UINT m_TimerTicks;      //处理滚动的定时器所经过的时间

	UINT m_nScrollTimerID;  //处理滚动的定时器

	CPoint m_HoverPoint;      //鼠标位置

	UINT m_nHoverTimerID;   //鼠标敏感定时器

	//DWORD m_dwDragStart;     //按下鼠标左键那一刻的时间

	BOOL m_bDragging;       //标识是否正在拖动过程中

	CImageList* m_pDragImage;      //拖动时显示的图象列表

	HTREEITEM m_hItemDragS;      //被拖动的标签

	HTREEITEM m_hItemDragD;      //接受拖动的标签
};


