#pragma once

#include "../resource.h"


class XDelegateSetScreenName;


class XSetScreenName : public CDialogEx
{
	DECLARE_DYNAMIC(XSetScreenName)

public:
	XSetScreenName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetScreenName();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCREENNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSetScreenName* p);

	void InitData();

	CString GetScreenName();

	void SetTitle(CString szTitle);

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateSetScreenName* m_pDelegate;

	//别名
	CString m_szScreenName;

	CString m_szTitle;

};