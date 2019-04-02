#pragma once

#include "..\resource.h"
#include "XDialog.h"
#include "XBtn.h"

// CAboutDlg 对话框

class XLoginLoad : public XDialog
{
	DECLARE_DYNAMIC(XLoginLoad)

public:
	XLoginLoad(CWnd* pParent = NULL,CString szPhotoPath=_T(""));   // 标准构造函数
	virtual ~XLoginLoad();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// 对话框数据
	enum { IDD = IDD_DIALOG_LOGINLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:

	void Init();

	void UpdateText();

private:

	CString m_szText;

	int m_nIndex;
};
