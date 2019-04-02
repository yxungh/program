#pragma once

#include "../resource.h"

class XDelegateMatrixScreenAttributesDlg;
class XScreen;
class XScreenManage;

class XScreenMatrixAttributesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XScreenMatrixAttributesDlg)

public:
	XScreenMatrixAttributesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XScreenMatrixAttributesDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_MATRIXSCREENATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateMatrixScreenAttributesDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();

	//设置输入信号名称
	void SetInputSignalName(CString s);

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateMatrixScreenAttributesDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

};