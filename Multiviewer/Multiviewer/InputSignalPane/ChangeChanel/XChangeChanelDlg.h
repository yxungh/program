#pragma once

#include "../resource.h"

class XInputSignal;
class XInputSignalPane;


class XDelegateChangeChenalDlg;


class XChangeChenalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XChangeChenalDlg)

public:
	XChangeChenalDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XChangeChenalDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_CHANGECHANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateChangeChenalDlg* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	void InitData();

	void InitCombo();

	//设置输入信号名称
	void SetInputSignalName(CString s);

	int GetCurChe();

	int GetSelectedChe();

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	XDelegateChangeChenalDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	int m_CurChe;

	int m_SelectedChe;

	CComboBox m_Combo_SelectedChe;
};

