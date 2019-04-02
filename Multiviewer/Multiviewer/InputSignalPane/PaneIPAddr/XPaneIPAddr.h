#pragma once

#include "../resource.h"
#include "..\XConstantIM.h"

class XInputSignal;
class XInputSignalPane;


class XDelegatePaneIPAddr;


class XPaneIPAddr : public CDialogEx
{
	DECLARE_DYNAMIC(XPaneIPAddr)

public:
	XPaneIPAddr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XPaneIPAddr();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_PANEIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBnClickedOk();
		afx_msg void OnBtnRead();
		afx_msg void OnIpnFieldchangedIp(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegatePaneIPAddr* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	void InitData();

	void InitCombo();

	//设置输入信号名称
	void SetInputSignalName(CString s);

	//设置IP地址
	void SetIP(CString szIP);
	CString GetIP();

	//设置掩码
	void SetMask(CString szMask);
	CString GetMask();

	//设置网关
	void SetGateWay(CString szGateWay);
	CString GetGateWay();

	//设置模式
	void SetModel(int n);
	int GetModel();


	//设置MAC
	void SetMAC(CString szMAC);

	void SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr);

	void ResetNet();

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
	XDelegatePaneIPAddr* m_pDelegate;

	CIPAddressCtrl m_IP;

	CIPAddressCtrl m_Mask;

	CIPAddressCtrl m_GateWay;

	//输入信号名称
	CString m_InputSignalName;

	//IP地址
	CString m_szIP;

	//子网掩码
	CString m_szMask;

	//网关
	CString m_szGateWay;

	//MAC地址
	CString m_szMAC;

	//文字
	CString m_Text;

	//计数
	int m_Index;

	int m_nReadIndex;

	//开始读取时间
	DWORD m_dBeginTime;

	CString m_szReadIndex;

	CComboBox m_Combo_Model;

	int m_nModel;
};