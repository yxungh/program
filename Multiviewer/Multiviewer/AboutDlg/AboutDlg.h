#pragma once

#include "..\resource.h"

class XDelegateAboutDlg;

// CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAboutDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_ABOUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnDblclickStatic4();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateAboutDlg* p);

private:

	XDelegateAboutDlg* m_Delegate;
};
