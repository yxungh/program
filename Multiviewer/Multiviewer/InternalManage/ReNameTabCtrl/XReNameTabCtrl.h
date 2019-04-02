#pragma once
#include "../resource.h"

class XInternalManage;

class XReNameTabCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(XReNameTabCtrl)

public:
	XReNameTabCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XReNameTabCtrl();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_RENAMETABCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	void SetManage(XInternalManage* pManage);

	void ReloadInterface();

	void InitData();

public:

	inline void SetOldName(CString szOldName){m_szOldName=szOldName;}

	inline CString GetOldName(){return m_szOldName;}

	inline void SetNewName(CString szNewName){m_szNewName=szNewName;}

	inline CString GetNewName(){return m_szNewName;}

	inline void SetTitle(CString szTitle){m_szTitle=szTitle;}

	inline CString GetTitle(){return m_szTitle;}

private:

	XInternalManage* m_pManage;

	CString m_szOldName;

	CString m_szNewName;

	CString m_szTitle;
};