#pragma once

#include "../resource.h"

class XInputSignal;
class XInputSignalPane;


class XDelegateStreamAddr;


class XStreamAddr : public CDialogEx
{
	DECLARE_DYNAMIC(XStreamAddr)

public:
	XStreamAddr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XStreamAddr();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_IPSTREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBnClickedOk();
		afx_msg void OnBtnRead();
		afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateStreamAddr* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	void InitData();

	//设置输入信号名称
	void SetInputSignalName(CString s);

	//设置视频流地址
	void SetStreamAddr(CString szStream);

	void ResetStream();

	void UpdateText();

	void ReRead();

private:

	//重载界面
	void ReloadInterface();

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

private:

	//委托
	XDelegateStreamAddr* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	//视频流地址
	CString m_szStreamAddr;

	//文字
	CString m_Text;

	//计数
	int m_Index;

	int m_nReadIndex;

	//开始读取时间
	DWORD m_dBeginTime;

	CString m_szReadIndex;

};