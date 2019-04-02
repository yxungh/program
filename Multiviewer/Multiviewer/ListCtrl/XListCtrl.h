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
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:

	void EnableToolTips(BOOL b);

private:

	CToolTipCtrl m_ToolTip; 

	int m_nSubItem;

	int m_nItem;

	BOOL m_bEnableTips;
};


