#pragma once

#include "XRTSPInfo.h"

class XRTSPHWND;
class XVideoPreviewPane;


class XRTSPInfoDragWnd : public CWnd
{
	DECLARE_DYNAMIC(XRTSPInfoDragWnd)

public:
	XRTSPInfoDragWnd();
	virtual ~XRTSPInfoDragWnd();

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

	void SetVideoPreviewPan(XVideoPreviewPane* p);

	XRTSPInfo* GetRTSPInfo();

	XRTSPHWND* GetRTSPHWND();

	void SetRTSPHWND(XRTSPHWND* p);

	void Show(XRTSPInfo* pInfo);

	void Hide();

	void Move(CPoint point);

	void AddUltraFrame();

	void AddCommFrame();

	void SetRectToFoure(RECTF rect,VEC_RECTF& VecRect);

	void ClearFrame();

private:

	XVideoPreviewPane* m_Pan;

	XRTSPInfo m_RTSPInfo;

	XRTSPHWND* m_RTSPHWND;

	XMultiVideoWindow* m_pMultiVideoWindow;
};


