#pragma once
#include "../resource.h"
#include "XDelegateSaveAllScence.h"
#include "XListCtrl.h"

class XInternalManage;
// XResolution 对话框

class XSaveAllScence : public CDialogEx
{
	DECLARE_DYNAMIC(XSaveAllScence)

public:
	XSaveAllScence(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSaveAllScence();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SAVEALLSCENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg void OnSelchangeCombo();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateSaveAllScence* p);

	void SetManage(XInternalManage* pManage);

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

	void InitList();

	void ReloadListInterface();

	void InitListData();

	int AddInfo(CString szInput);

	void ClearMapSelScene();

	MAP_SELSCENE& GetMapSelScene();

private:

	XDelegateSaveAllScence* m_pDelegate;

	XInternalManage* m_pManege;

	//场景名称
	CString m_szSceneName;

	//场景序号
	int m_nSceneIndex;

	CString m_szSceneGroup;

	int m_Index[32];

	CComboBox m_ComboBox_Index;

	CComboBox m_ComboBox_Group;

	XListCtrl m_List_ScreenManage;

	MAP_SELSCENE m_MapSelSceen;
};
