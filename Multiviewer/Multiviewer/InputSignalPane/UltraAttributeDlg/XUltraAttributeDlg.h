#pragma once

#include "../resource.h"

class XInputSignal;
class XInputSignalPane;


class XDelegateUltraAttributeDlg;


class XUltraAttributeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XUltraAttributeDlg)

public:
	XUltraAttributeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XUltraAttributeDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SIGNALULTRAATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateUltraAttributeDlg* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	void InitData();

	//设置输入信号名称
	void SetInputSignalName(CString s);

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	XDelegateUltraAttributeDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;
};