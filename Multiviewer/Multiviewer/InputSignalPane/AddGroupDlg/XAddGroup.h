#pragma once

#include "../resource.h"


class XInputSignal;
class XInputSignalPane;


class XDelegateAddGroup;


class XAddGroup : public CDialogEx
{
	DECLARE_DYNAMIC(XAddGroup)

public:
	XAddGroup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XAddGroup();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_INPUTGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnAddGroup();
	afx_msg void OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	afx_msg void OnChange();
	afx_msg void OnAddInGroup();

	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateAddGroup* p);

	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	void Init();

	void InitData();

	void SetGroupName(CString s);

	CString GetGroupName();

	void InitTreeImageList();

	

private:

	//重载界面
	void ReloadInterface();

	HTREEITEM AddRoot(CString szRoot);

	HTREEITEM AddChild(CString szChild);

	HTREEITEM AddChildChild(CString szChildChild);

	void SetItemRoot(HTREEITEM h);

	HTREEITEM GetItemRoot();

	void SetItemChild(HTREEITEM h);

	HTREEITEM GetItemCHild();

	void ShowMenu();


private:

	//委托
	XDelegateAddGroup* m_pDelegate;

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

	//选中分组名称
	CString m_szGroupName;

	//分组树
	CTreeCtrl m_TreeGroup;

	CImageList m_TreeImageList;

	HTREEITEM m_ItemRoot;

	HTREEITEM m_ItemChild;

	CString m_szRoot;

	CString m_szNewGroupName;

	CString m_szRbGroupName;

	int m_nType;

	HTREEITEM m_RbItem;

};