#pragma once

#include "..\resource.h"
#include "XChildDialog.h"
#include "XBtn.h"

class XDelegateHostConfig;

// CAboutDlg 对话框

class XHostConfig : public XChildDialog
{
	DECLARE_DYNAMIC(XHostConfig)

public:
	XHostConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XHostConfig();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_HOSTCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateHostConfig* p);

private:

	XDelegateHostConfig* m_pDelegate;

};
