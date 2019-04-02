#pragma once


class XMyTabCtrl:public CMFCTabCtrl
{
	DECLARE_DYNCREATE(XMyTabCtrl)

public:
	XMyTabCtrl();
	virtual ~XMyTabCtrl();

	virtual CWnd* FindTargetWnd(const CPoint& pt);

protected:

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

};