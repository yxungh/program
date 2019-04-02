#pragma once

#include "../resource.h"

class XDelegateRunOldOrderDlg;
class XScreen;
class XScreenManage;

class XRunOldOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XRunOldOrderDlg)

public:
	XRunOldOrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XRunOldOrderDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_OLDORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateRunOldOrderDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();



private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateRunOldOrderDlg* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

};