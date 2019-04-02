#pragma once


// XChildDialog 对话框

class XChildDialog : public CDialogEx
{
	DECLARE_DYNAMIC(XChildDialog)

public:
	XChildDialog(UINT nIDD,CWnd *pParent);   // 标准构造函数
	virtual ~XChildDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

protected:

	//绘制对话框
	virtual void DrawDlg(CDC* pDC);

protected:

	//VK_RETURN状态
	BOOL m_bEnableVK_RETURN;

	//VK_ESCAPE状态
	BOOL m_bEnableVK_ESCAPE;
};
