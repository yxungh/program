#pragma once

#include "../resource.h"
#include "..\XConstantIM.h"


class XDelegateBoardNet;
class XInternalManage;


class XBoardNet : public CDialogEx
{
	DECLARE_DYNAMIC(XBoardNet)

public:
	XBoardNet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XBoardNet();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_PANEIPOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedOk2();
		afx_msg void OnBnClickedRead();
		afx_msg void OnIpnFieldchangedIp(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateBoardNet* p);

	void SetInternalManage(XInternalManage* p);

	void InitData();

	void InitComboModel();

	void InitComboPassWd();

	void SetBoardIndex(int n);

	int GetBoardIndex();

	//设置用户名
	void SetUseName(CString szName);
	CString GetUseName();

	//设置密码
	void SetPassWd(CString szPassWd);
	CString GetPassWd();

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
	

	void SetSecret(int n);
	int GetSecret();

	//设置MAC
	void SetMAC(CString szMAC);

	//设置版本
	void SetVersion(CString szVer);

	void SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr);

	void ResetNet();

	void UpdateText();

	void ReRead();

	void SetDialog();

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateBoardNet* m_pDelegate;

	XInternalManage* m_pManage;

	CIPAddressCtrl m_IP;

	CIPAddressCtrl m_Mask;

	CIPAddressCtrl m_GateWay;

	CComboBox m_Combo_Model;

	CComboBox m_Combo_PassWd;

	CEdit m_Edit_Name;

	CEdit m_Edit_PassWd;

	CString m_szUseName;

	CString m_szPassWd;

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

	//版本信息
	CString m_szVersion;

	//计数
	int m_Index;

	int m_nReadIndex;

	//开始读取时间
	DWORD m_dBeginTime;

	CString m_szReadIndex;

	int m_nModel;

	int m_nModelSel;

	CRect m_Rect;

	CRect m_ExpaneRect;

	long m_nSetTime;

	int m_nSecret;

	int m_nSecretSelect;

	int m_nBoardIndex;


};