#pragma once

#include "../resource.h"


class XDelegateReName;

class XReName : public CDialogEx
{
	DECLARE_DYNAMIC(XReName)

public:
	XReName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XReName();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCENERENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateReName* p);

	void InitData();

	CString GetScreenName();

	void SetTitle(CString szTitle);

	void SetName(CString szName);

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateReName* m_pDelegate;

	//别名
	CString m_szScreenName;

	CString m_szTitle;

	CString m_szName;

};