#pragma once
#include "../resource.h"
#include "XDelegateChangeScreen.h"
#include "XConstantIM.h"

class XScreenManage;
class XScreen;

class XChangeScreen : public CDialogEx
{
	DECLARE_DYNAMIC(XChangeScreen)

public:
	XChangeScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XChangeScreen();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_CHANGEASCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateChangeScreen* p);

	void SetScreenMange(XScreenManage* p);

	void SetScreen(XScreen* p);

	void ReloadInterface();

	void InitData();

	void InitCombo();

	int GetComboIndex();

	int GetScreenIndex();

	void SetScreenIndex(int n);

private:

	XDelegateChangeScreen *m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	CComboBox m_ComboBox_After;

	int m_ComboIndex;

	int m_ScreenIndex;
	
};