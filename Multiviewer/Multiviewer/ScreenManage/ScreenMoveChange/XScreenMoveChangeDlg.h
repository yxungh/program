#pragma once

#include "../resource.h"

class XDelegateScreenMoveChangeDlg;
class XScreen;
class XScreenManage;

class XChangeMoveScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XChangeMoveScreenDlg)

public:
	XChangeMoveScreenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XChangeMoveScreenDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_MOVECHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBtnSet();

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateScreenMoveChangeDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();

	//设置输入信号名称
	void SetInputSignalName(CString s);

private:

	//重载界面
	void ReloadInterface();

	void InitCombo();

private:

	//委托
	XDelegateScreenMoveChangeDlg* m_pDelegate;

	//输入信号名称
	CString m_InputSignalName;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

private:

	CMFCColorButton m_FColor_Change;

	CMFCColorButton m_BColor_Change;

	int m_Space;

	int m_Speed;
public:
	CComboBox m_ComboBox_BeginX;
	CComboBox m_ComboBox_BeginY;
	CComboBox m_ComboBox_Type;
};