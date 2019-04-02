#pragma once

#include <vector>

enum status 
{
	STATUS_NORMAL = -1,
	STATUS_FOCUS,
	STATUS_PRESS
};

struct item 
{
	CStringW ico;
	CStringW text;
	CStringW textkey;
	CRect rt;
	CRect rttext;
	BOOL chk;
	status sta;
	DWORD data;
};

class XToolBar : public CWnd
{
	DECLARE_DYNAMIC(XToolBar)

public:
	XToolBar();
	virtual ~XToolBar();

protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(UINT nItemWidth, UINT nItemHeight, UINT nDistance, DWORD dwStyle, 
		const RECT& rect, CWnd* pParentWnd, UINT nID);

	void SetCurSel(size_t nSelect);

	void InsertItem(LPCWSTR szIco, LPCTSTR szTextKey,  LPCTSTR szDefaultText, DWORD dwData = 0);

	void SetTextColor(COLORREF color);

	void ClearAllItem();

	void ReloadInterface();

private:

	void CalcItemRect(item &it, size_t nIdx);

private:

	//保存窗口子按钮属性
	std::vector<item> m_vtItem;

	//判断鼠标是否离开窗口
	BOOL m_bMouseLeave;

	//按钮高度
	UINT m_nItemHeight;

	//按钮宽度
	UINT m_nItemWidth;

	//按键间隔
	UINT m_nDistance;

	//文字颜色
	COLORREF m_textColor;

	//文字高度
	UINT m_nTextHeight;
};


