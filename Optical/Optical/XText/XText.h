#pragma once

class XText : public CWnd
{
	DECLARE_DYNAMIC(XText)

public:
	XText();
	virtual ~XText();

	virtual void PreSubclassWindow();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:

	void SetText(CString szText);

	void SetFillColor(COLORREF color);

	void SetTextColor(COLORREF color);

	void SetVertical(BOOL b);

	void SetTextSize(int nSize);

	void SetLeft(BOOL b);

private:

	void DrawText(Graphics& graphics, CRect& rt);

protected:
	
	//填充颜色
	COLORREF m_FillColor;

	//文字颜色
	COLORREF m_TextColor;

	//文字
	CString m_Text;

	//垂直
	BOOL m_Vertical;

	//居左
	BOOL m_Left;

	//字体大小
	int m_nTextSize;
};


