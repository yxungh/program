#pragma once

#include "../resource.h"
#include "XListCtrl.h"
#include "XConstantIM.h"

class XUserManage;

// CUserManageDlg 对话框

class CUserManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManageDlg)

public:
	CUserManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserManageDlg();

	virtual BOOL OnInitDialog();

	virtual void OnOK();

// 对话框数据
	enum { IDD = IDD_DLG_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnClickedAdd();
	afx_msg void OnBtnClickedEdit();
	afx_msg void OnBtnClickedDel();
	afx_msg void OnBtnClickedSave();
	afx_msg void OnBtnClickedCancel();
	afx_msg void OnBtnClickedCopy();
	afx_msg void OnNMDblclkListCtrlUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditNoticeChange();
	DECLARE_MESSAGE_MAP()

public:

	void SetUserManage(XUserManage* p);

private:

	//重载界面
	void ReloadInterface();

	//重载列表界面
	void ReloadListInterface();

	//初始化列表
	void InitList();

	//初始化列表数据
	void InitListData();

	void InitNotice();

	//添加信息
	int AddInfo(CString szAccount);

	//设置信息
	void SetInfo(int n, CString szAccount);

	//显示操作类型界面
	void ShowOperateInterface(char type);

	//保存添加
	void SaveAdd();

	//保存编辑
	void SaveEdit();

	void SaveCopy();

	//获取选择的权限类型
	POWERTYPE GetSelectPower();

	//选择权限类型
	void SelectPower(POWERTYPE type);

	//设置权限
	void SetPower();

private:

	XUserManage* m_UserManage;

	XListCtrl m_ListCtrl_User;

	//帐号
	CEdit m_Edit_Account;

	//密码
	CEdit m_Edit_PSW;

	//操作类型
	char m_OperateType;

	//编辑的用户信息
	XUserInfo* m_EditUserInfo;

	XUserInfo* m_CopyUserInfo;

	//编辑所在项
	int m_EditListItem;
};
