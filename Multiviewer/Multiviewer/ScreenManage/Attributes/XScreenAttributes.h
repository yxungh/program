#pragma once

#include "../resource.h"

class XDelegateScreenAttributesDlg;
class XScreen;
class XScreenManage;

class XScreenAttributesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XScreenAttributesDlg)

public:
	XScreenAttributesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XScreenAttributesDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCREENATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateScreenAttributesDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();

	//设置输入信号名称
	void SetInputSignalName(CString s);

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateScreenAttributesDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

};