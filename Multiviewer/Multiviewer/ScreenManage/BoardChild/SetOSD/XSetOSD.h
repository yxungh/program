#pragma once

#include "../resource.h"

class XScreenManage;

class XSetOSD : public CDialogEx
{
	DECLARE_DYNAMIC(XSetOSD)

public:
	XSetOSD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetOSD();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCREENINDEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	void SetScreenManage(XScreenManage* p);

	void InitCombo();

	int GetOSDIndex();

	void SetInputIndex(int n);

	int GetInputIndex();

private:

	//重载界面
	void ReloadInterface();

private:

	XScreenManage* m_pScreenManage;

	CComboBox m_Combo_ScreenIndex;

	int m_nOSDIndex;

	int m_nInputIndex;
};