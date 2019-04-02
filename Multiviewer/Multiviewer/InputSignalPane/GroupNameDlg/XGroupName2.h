#pragma once

#include "../resource.h"

class XInputSignal;
class XInputSignalPane;


class XGroupName2 : public CDialogEx
{
	DECLARE_DYNAMIC(XGroupName2)

public:
	XGroupName2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XGroupName2();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_ADDGROUP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	//void SetDelegate(XDelegateSetAnotherNameDlg* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	//设置输入信号名称
	void SetInputSignalName(CString s);

	void InitData();

	CString GetAnotherName();

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	//XDelegateSetAnotherNameDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	//别名
	CString m_AnotherName;

};