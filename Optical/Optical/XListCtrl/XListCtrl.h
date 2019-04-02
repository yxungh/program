#pragma once

// XListCtrl

class XListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(XListCtrl)

public:
	XListCtrl();
	virtual ~XListCtrl();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnMouseLeave();

public:

	inline void EnableToolTips(BOOL b);

	inline void SetOddItemBkColor(COLORREF color,BOOL bDraw){m_OddItemBkColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetEvenItemBkColor(COLORREF color,BOOL bDraw){m_EvenItemBkColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetHoverItemBkColor(COLORREF color,BOOL bDraw){m_HoverItemBkColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetSelectItemBkColor(COLORREF color,BOOL bDraw){m_SelectItemBkColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetOddItemTextColor(COLORREF color,BOOL bDraw){m_OddItemTextColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetEvenItemTextColor(COLORREF color,BOOL bDraw){m_EvenItemTextColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetHoverItemTextColor(COLORREF color,BOOL bDraw){m_HoverItemTextColor=color;if(bDraw)InvalidateRect(NULL);}

	inline void SetSelectItemTextColor(COLORREF color,BOOL bDraw){m_SelectItemTextColor=color;if(bDraw)InvalidateRect(NULL);}

private:

	CToolTipCtrl m_ToolTip; 

	int m_nSubItem;

	int m_nItem;

	BOOL m_bEnableTips;

	//奇数行颜色
	COLORREF m_OddItemBkColor;

	//偶数行颜色
	COLORREF m_EvenItemBkColor;

	//热点行颜色
	COLORREF m_HoverItemBkColor;

	//选中行
	COLORREF m_SelectItemBkColor;

	//奇数行文字
	COLORREF m_OddItemTextColor;

	//偶数行文字
	COLORREF m_EvenItemTextColor;

	//热点文字
	COLORREF m_HoverItemTextColor;

	//选中文字
	COLORREF m_SelectItemTextColor;

	int m_nHoverIndex;

	BOOL m_bTracking;
};


