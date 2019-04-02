#pragma once

class XBtn;

// XDialog 对话框

class XDialog : public CDialogEx
{
	DECLARE_DYNAMIC(XDialog)

public:
	XDialog(UINT nIDD,CWnd *pParent,CString szPhotoPath);   // 标准构造函数
	virtual ~XDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

protected:

	//绘制对话框
	virtual void DrawDlg(CDC* pDC);

	//创建按钮
	void CreateBtn(CWnd* pParent, XBtn* pBtn, CRect rect, 
		UINT nID, CString szPhotoPath);

protected:

	//VK_RETURN状态
	BOOL m_bEnableVK_RETURN;

	//VK_ESCAPE状态
	BOOL m_bEnableVK_ESCAPE;

	//是否有标题栏
	BOOL m_bNcHitTest;

	//图片
	CString m_szPhotoPath;

};
