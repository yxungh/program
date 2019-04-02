#pragma once

#include "../resource.h"

class XDelegateEditExpandDlg;
class XInputSignalExpand;
class XInputSignalPane;

// CEditExpandDlg 对话框

class CEditExpandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditExpandDlg)

public:
	CEditExpandDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditExpandDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_EDITEXPAND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateEditExpandDlg* p);

	//设置输入信号局部放大
	void SetInputSignalExpand(XInputSignalExpand* p);

	void SetInputSignalPan(XInputSignalPane* p);

private:

	//重载界面
	void ReloadInterface();

	//初始化显示数据
	void InitShowData();

private:

	//委托
	XDelegateEditExpandDlg* m_pDelegate;

	//输入信号局部放大
	XInputSignalExpand* m_InputSignalExpand;

	XInputSignalPane* m_InputSignalPan;
};
