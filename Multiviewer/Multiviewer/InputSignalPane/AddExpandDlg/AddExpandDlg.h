#pragma once

#include "../resource.h"
#include "XExpandInfo.h"

class XDelegateAddExpandDlg;
class XInputSignal;
class XInputSignalPane;

// CAddExpandDlg 对话框

class CAddExpandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddExpandDlg)

public:
	CAddExpandDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddExpandDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ADDEXPAND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateAddExpandDlg* p);

	//设置输入信号
	void SetInputSignal(XInputSignal* p);

	void SetInputSignalPan(XInputSignalPane* p);

	//设置输入信号名称
	void SetInputSignalName(CString s);

	CString GetName();

	XExpandInfo* GetExpandInfo();

private:

	//重载界面
	void ReloadInterface();

	void InitData();

private:

	//委托
	XDelegateAddExpandDlg* m_pDelegate;

	//输入信号
	XInputSignal* m_InputSignal;

	XInputSignalPane* m_InputSIgnalPan;

	CString m_szName;

	XExpandInfo m_ExpandInfo;

	//输入信号名称
	CString m_InputSignalName;
};
