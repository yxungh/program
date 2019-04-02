#pragma once
#include "../resource.h"
#include "XDelegateAllMatrixResolution.h"
#include "XScreen.h"

// XMatrixAllResolution 对话框

class XScreenManage;

class XMatrixAllResolution : public CDialogEx
{
	DECLARE_DYNAMIC(XMatrixAllResolution)

public:
	XMatrixAllResolution(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XMatrixAllResolution();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_MATRIXALLRESALUTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	afx_msg void OnBtnCancle();
	afx_msg void OnClickedExpand();
	afx_msg void OnSelchangeIndex();
	afx_msg void OnSelchangeRefresh();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateAllMatrixResolution* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen*& p);

	void ReloadInterface();

	void SetDialog();

	void Init();

	void InitCombo();

	void InitShowData();

private:

	XDelegateAllMatrixResolution* m_Delegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	CRect m_Rect;

	CRect m_ExpaneRect;

	CComboBox m_Combo_Index;

	CComboBox m_Combo_Refresh;

	CComboBox m_Combo_Model;
};
