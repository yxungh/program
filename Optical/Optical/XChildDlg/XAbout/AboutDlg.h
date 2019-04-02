#pragma once

#include "..\resource.h"
#include "XDialog.h"
#include "XBtn.h"

class XDelegateAboutDlg;

// CAboutDlg 对话框

class CAboutDlg : public XDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL,CString szPhotoPath=_T(""));   // 标准构造函数
	virtual ~CAboutDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStnDblclickStatic4();
	DECLARE_MESSAGE_MAP()

private:

	//创建按钮
	void CreateBtn();

private:

	//关闭按钮
	XBtn m_Btn_Close;
};
