
// OpticalDlg.h : 头文件
//

#pragma once
#include "XDialog.h"
#include "XBtn.h"
#include "XConstant.h"
#include "XDelegateNetManage.h"
#include "XDelegateReciveDataManage.h"
#include "XDelegateSendDataManage.h"
#include "XDelegatePowerManage.h"
#include "XDelegateHostConfig.h"
#include "XDelegateSetNet.h"
#include "XPowerManage.h"
#include "XHostConfig.h"


class XNetManage;
class XStatusBar;
class XToolBar;
class XPowerManage;
class XReciveDataManage;
class XPowerManage;
class XHostConfig;

// COpticalDlg 对话框
class COpticalDlg : public XDialog,
					public XDelegateNetManage,
					public XDelegateReciveDataManage,
					public XDelegatePowerManage,
					public XDelegateHostConfig,
					public XDelegateSetNet,
					public XDelegateSendDataManage
{
// 构造
public:
	COpticalDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPTICAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void OnCancel();
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUDP(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnToolBarClicked(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAbout();
	afx_msg void OnLanguageZHCN();
	afx_msg void OnLanguageZHTW();
	afx_msg void OnLanguageEN();
	afx_msg void OnSetNet();

	DECLARE_MESSAGE_MAP()

public:

	virtual void DrawDlg(CDC* pDC);

	virtual HWND GetHWND();

	virtual void HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

	virtual void Operate(OPERATETYPE type, void* pData);

	virtual void SetDeviceIPAndPort(CString szIP,int nPort);

	virtual void SaveDeviceIPAndPort(CString szIP,int nPort);

	virtual CString GetIP();

	virtual int GetPort();

	virtual BOOL IsLogin();

	virtual void SetLogin(BOOL b);

	virtual void SetCurUserName(CString szUserName);

	virtual CString GetCurUserName();

	virtual BOOL SendData(char* pData, int nDataLen);

	virtual void SendHeart();

private:

	void Init();

	void ReSize();

	void InitBtn();

	void InitStatusBar();

	void InitToolBar();

	void addToolBar();

	void InitDlg();

	void InitData();

	void OnSet();

	void InitManage();

	void CreateBtn(XBtn* pBtn,CRect rect,UINT nID,CString szPhotoName);

	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	void SetLanguageType(LANGUAGETYPE type);

	void ClearData();

	void ReloadInterface();

	void BeginTimer();

	

private:

	void ShowPowerManageDlg();

	void ShowHostConfigDlg();

private:

	void InitHostConfigDlg();

	void InitPowerManageDlg();

private:

	void OperateOfHeart(char* pData);

private:

	CString m_szIP;

	int m_nPort;

	BOOL m_bIsLogin;

	BOOL m_bIsOnline;

	CString m_szCurUserName;

	DWORD m_dHeartTime;

	int m_nHeartTimerID;

private:

	XBtn m_Btn_Close;

	XBtn m_Btn_Set;

	XBtn m_Btn_Min;

private:

	XToolBar* m_pToolBar;

	XStatusBar* m_pStatusBar;

	XNetManage* m_pNetManage;

	XReciveDataManage* m_pReciveDataManage;

private:

	XPowerManage m_PowerManageDlg;

	XHostConfig m_HostConfigDlg;
};
