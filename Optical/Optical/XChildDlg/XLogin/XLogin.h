#pragma once

#include "..\resource.h"
#include "XDialog.h"
#include "XBtn.h"

class XDelegateLogin;


class XLogin : public XDialog
{
	DECLARE_DYNAMIC(XLogin)

public:
	XLogin(CWnd* pParent = NULL,CString szPhotoPath=_T(""));   // 标准构造函数
	virtual ~XLogin();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:

	void Init();

	void InitBtn();

	void InitUserName();

	void ReloadInterface();

	void OnBtnClickedOk();

	void SaveUserName(CString szUserName);

	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

public:

	void SetDelegate(XDelegateLogin* p);

private:

	XDelegateLogin* m_pDelegate;

	XBtn m_Btn_Close;

	XBtn m_Btn_Ok;

	XBtn m_Btn_Cancel;

	CString m_szUserName;
};
