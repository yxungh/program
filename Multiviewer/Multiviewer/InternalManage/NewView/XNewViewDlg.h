#pragma once

#include "../resource.h"


class XDelegateNewViewDlg;
class XInternalManage;


class XNewViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XNewViewDlg)

public:
	XNewViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XNewViewDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateNewViewDlg* p);

	void SetBaseManage(XInternalManage* p);

	//设置输入信号名称
	void SetViewName(CString s);

	CString GetViewName();

	int GetBeginIndex();

	void InitData();

	void InitCombo();

	int GetScreenModel();

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateNewViewDlg* m_pDelegate;

	XInternalManage* m_pBaseManage;

	CComboBox m_Combox_Model;

	int m_nScreenModel;

	//输入信号名称
	CString m_ViewName;

	int m_BeginIndex;
};