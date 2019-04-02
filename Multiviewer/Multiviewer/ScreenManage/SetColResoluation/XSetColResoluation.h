#pragma once
#include "..\resource.h"

class XDelegateSetColResoluation;
class XScreenManage;
class XScreen;

// CAboutDlg 对话框

class XSetColResoluation : public CDialogEx
{
	DECLARE_DYNAMIC(XSetColResoluation)

public:
	XSetColResoluation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetColResoluation();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_COLRESOLUATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnClickedOk();
	afx_msg void OnSelDpiChange();

	DECLARE_MESSAGE_MAP()

public:

	inline void SetScreenManage(XScreenManage* p){m_pScreenManage=p;} 

	inline void SetScreen(XScreen* p){m_pScreen=p;}

public:

	void SetDelegate(XDelegateSetColResoluation* p);

	void Init();

	void InitData();

	void ReloadInterface();

private:

	XDelegateSetColResoluation* m_Delegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;
};
