#pragma once

#include "../resource.h"

class XDelegateDeleteSceneDlg;
class XScreen;
class XScreenManage;

class XDeleteSceneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XDeleteSceneDlg)

public:
	XDeleteSceneDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XDeleteSceneDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_DELETESCENE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateDeleteSceneDlg* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void SetData(char* pData);

	void InitCombo();

	void SetDelIndex(int n);

	int GetDelIndex();
private:

	//重载界面
	void ReloadInterface();
	 
private:

	//委托
	XDelegateDeleteSceneDlg* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	int m_Index[32];

	CComboBox m_ComboBox_DelIndex;

	int m_DelIndex;
};