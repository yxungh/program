#pragma once

#include "XDragInfo.h"

class XInputSignalPane;

class XDragWnd : public CWnd
{
	DECLARE_DYNAMIC(XDragWnd)

public:
	XDragWnd();
	virtual ~XDragWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:

	void SetInputSignalPan(XInputSignalPane* p);

	XDragInfo* GetDragInfo();

	void Show(XDragInfo* pInfo);

	void Hide();

	void Move(CPoint point);

	void ClearMultiVideoWindow();

	void AddUltraFrame();

	void AddCommFrame();

	void SetRectToFoure(RECTF rect,VEC_RECTF& VecRect);

	void ClearFrame();

private:

	XDragInfo m_DragInfo;

	XInputSignalPane* m_Pan;

	XMultiVideoWindow* m_pMultiVideoWindow;

};


