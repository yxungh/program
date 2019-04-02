#pragma once
#include "XDialog.h"

// XResizingDialog 对话框

class XResizingDialog : public XDialog
{
	DECLARE_DYNAMIC(XResizingDialog)

public:
	XResizingDialog(UINT nIDD, CWnd *pParent,CString szPtotoPath);   // 标准构造函数
	virtual ~XResizingDialog();

protected:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

protected:

	//对话框最小宽度
	int m_DlgMinWidth;

	//对话框最小高度
	int m_DlgMinHeight;

	CString m_szPtotoPath;
};
