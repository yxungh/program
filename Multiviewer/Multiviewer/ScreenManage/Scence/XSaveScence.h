#pragma once
#include "../resource.h"
#include "XDelegateSaveScence.h"


// XResolution 对话框

class XSaveScence : public CDialogEx
{
	DECLARE_DYNAMIC(XSaveScence)

public:
	XSaveScence(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSaveScence();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SAVESCENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg void OnSelchangeCombo();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateSaveScence* p);

	void SetData(char* pData);

	//重载界面
	void ReloadInterface();

	void InitCombo();

	void InitComboIndex();

	void InitComboGroup();

	//场景名称
	CString GetSceneName();

	//场景序号
	int GetSceneIndex();

	CString GetSceneGroup();

	void InitIndex();

private:

	XDelegateSaveScence* m_pDelegate;

	//场景名称
	CString m_szSceneName;

	//场景序号
	int m_nSceneIndex;

	CString m_szSceneGroup;

	int m_Index[32];

	CComboBox m_ComboBox_Index;

	CComboBox m_ComboBox_Group;
};
