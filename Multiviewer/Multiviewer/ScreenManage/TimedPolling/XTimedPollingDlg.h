#pragma once

#include "../resource.h"

class XDelegateTimedPollingDlg;
class XScreen;
class XScreenManage;

class XTimedPollingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XTimedPollingDlg)

public:
	XTimedPollingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XTimedPollingDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_TIMEDPOLLING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateTimedPollingDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateTimedPollingDlg* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

};