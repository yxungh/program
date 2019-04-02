#pragma once

#include "../resource.h"
#include "XExpandInfo.h"
#include "XInputSignalPane.h"

class XDelegateInputSignalCutDlg;
class XInputSignal;


// CAddExpandDlg 对话框

class XInputSignalCutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XInputSignalCutDlg)

public:
	XInputSignalCutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XInputSignalCutDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_INPUTSIGNALCUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateInputSignalCutDlg* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	//设置输入信号名称
	void SetInputSignalName(CString s);

	void InitData();

	int GetCutLTX();

	int GetCutLTY();

	int GetCutRBX();

	int GetCutRBY();

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号名称
	CString m_InputSignalName;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	XDelegateInputSignalCutDlg* m_pDelegate;

	int m_LTX;

	int m_LTY;

	int m_RBX;

	int m_RBY;
};