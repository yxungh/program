#pragma once

class XVideoPreviewTextWnd : public CWnd
{
	DECLARE_DYNAMIC(XVideoPreviewTextWnd)

public:
	XVideoPreviewTextWnd();
	virtual ~XVideoPreviewTextWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:

	void SetFont(CFont* p);

	void SetText(CString s);

	CString GetText();

	void InvalidateView();

	void SetTextSize(int n);

protected:

	CString m_Text;

	int m_TextSize;

	CFont* m_Font;
};


