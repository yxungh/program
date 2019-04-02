#pragma once

#include "../resource.h"

class XInputSignal;
class XInputSignalPane;


class XDelegateSetAnotherNameDlg;


class XSetAnotherNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XSetAnotherNameDlg)

public:
	XSetAnotherNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetAnotherNameDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_ANOTHERNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSetAnotherNameDlg* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	//设置输入信号名称
	void SetInputSignalName(CString s);

	void InitData();

	CString GetAnotherName();

	void SetTitle(CString szStr);

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	XDelegateSetAnotherNameDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	//别名
	CString m_AnotherName;

	//标题
	CString m_szTitle;

};