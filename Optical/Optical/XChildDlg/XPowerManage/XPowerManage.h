#pragma once

#include "..\resource.h"
#include "XChildDialog.h"
#include "XConstant.h"
#include "XDelegateLogin.h"
#include "XDelegateUserManage.h"


#define TEXT_HIGHT  20;
#define DISTANCE    10;

class XBtn;
class XText;
class XLogin;
class XLoginLoad;
class XDelegatePowerManage;

class XPowerManage : public XChildDialog,
					 public XDelegateLogin,
					 public XDelegateUserManage
{
	DECLARE_DYNAMIC(XPowerManage)

public:
	XPowerManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XPowerManage();

	virtual BOOL OnInitDialog();

	

	// 对话框数据
	enum { IDD = IDD_DIALOG_POWERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
		afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	virtual void SetCurUserName(CString szUserName);

	virtual void SetLoginUser(CString szUserName,CString szPassWd);

	virtual void SetLoginLoad();

public:

	void SetDelegate(XDelegatePowerManage* p);

	void Operate(OPERATETYPE type, void* pData);

	void InsertItem(CString szFilePath,UINT nID,CString szText=_T(""));

	void InitSub();

	void ReloadInterface();

private:

	void InitRect();

	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	void InitLoginBtn();

	void InitLoginText();

	void UpdateText();

private:

	void ClearItem();

	void ClearLoginBtn();

	void ClearLoginText();

private:

	void UserManage();

	void Login();

	void LoginOut();

	BOOL IsLogin();

	CString GetCurUserName();

	void NodeManage();

	void HideLoginDlg();

	void ShowLoginLoadDlg();

	void HideLoginLoadDlg();

private:

	void OperateOfLogin(char* pData);

	void OperateOfLoginOut(char* pData);

private:

	XDelegatePowerManage* m_pDelegate;

private:

	VEC_POWERMANAGEITEM m_VecPowerManageItem;

	XBtn* m_pLoginBtn;

	XText* m_pLoginText;

	CRect m_rtBtn;

	CString m_szLoginUserName;

	CString m_szLoginPassWd;

private:

	XLogin* m_pLogin;

	XLoginLoad* m_pLoginLoad;

	DWORD m_dLoginTime;
};
