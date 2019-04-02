#pragma once

#include "..\resource.h"
#include "XConstant.h"
#include "XBtn.h"
#include "XDialog.h"

// XMessageBoxDlg 对话框

class XMessageBoxDlg : public XDialog
{
	DECLARE_DYNAMIC(XMessageBoxDlg)

public:
	XMessageBoxDlg(CString szText, CString szCaption, UINT uType, CWnd* pParent = NULL,CString szPhotoPath=_T(""));
	
	virtual ~XMessageBoxDlg();

	virtual BOOL OnInitDialog();

	virtual void OnOK();

	virtual void OnCancel();

// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:

	//初始化控件
	void InitControl();

	//初始化静态文本控件
	void InitControlOfStatic();

	//初始化按钮控件
	void InitControlOfButton();

	//调整布局
	void AdjustLayout();

	//调整静态文本布局
	void AdjustLayoutOfStatic(CRect& rectDlg);

	//调整按钮布局
	void AdjustLayoutOfButton(CRect& rectDlg);

	//清除
	void Clear();

	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	void OnBnClickedBtn1();

	void OnBnClickedBtn2();

	void OnBnClickedBtn3();

private:

	CString m_szText;
	
	CString m_szCaption;
	
	UINT m_uType;

	CStatic* m_pStatic;

	XBtn* m_pBtnArr;

	int m_nBtnCount;
};
