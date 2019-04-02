#pragma once
#include "..\resource.h"
#include "XConstant.h"
#include "XDialog.h"
#include "XBtn.h"
#include "XListCtrl.h"


class XDelegateUserManage;

class XUserManage : public XDialog
{
	DECLARE_DYNAMIC(XUserManage)

public:
	XUserManage(CWnd* pParent = NULL,CString szPhotoPath=_T(""));   // 标准构造函数
	virtual ~XUserManage();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:

	inline void SetDelegate(XDelegateUserManage* p){m_pDelegate=p;}

private:

	void Init();

	void InitBtn();

	void InitList();

	void ReloadListInterface();

	void ReLoadInterface();

	void SetEditLimit();

	void OnBtnClickedOk();

	void OnBtnClickedCancel();

	void OnBtnClickedAdd();

	void OnBtnClickedDel();

	void OnBtnClickedAlter();

	void UpdateOperateStatus();

	void SaveAdd();

	void SaveAlter();

public:

	inline void SetOperateType(USEROPERATE nType){m_OperateType=nType;}

private:

	int AddListInfo(CString szUserName,char cType);

	void SetListInfo(int nCount,CString szUserName,char cType);

	int GetListItem(CString szUserName);

	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

private:

	XDelegateUserManage* m_pDelegate;

private:

	XBtn m_Btn_Close;

	XBtn m_Btn_Ok;

	XBtn m_Btn_Cancel;

	XBtn m_Btn_AddUser;

	XBtn m_Btn_DelUser;

	XBtn m_Btn_UpdateUser;

	XListCtrl m_List_User;

	USEROPERATE m_OperateType;

	DWORD m_RefreshTime;

	CString m_szUserName;

	CString m_szPassWord;

	char m_Power;

};
