#pragma once

#include "XConstantIM.h"

class XDelegateUserManage;
class XUserInfo;

#define DEFAULTACCOUNT _T("admin")//默认帐号

class XUserManage
{
public:
	XUserManage(void);
	~XUserManage(void);

public:

	//初始化
	void Init();

	void SetDelegate(XDelegateUserManage* p);

	//重置数据
	void ResetData();

	//获取数据
	void GetData(CArchive& arch);

	//保存数据
	void SaveData(CArchive& arch);

	//判断帐号是否存在
	BOOL DecideAccountExist(CString name);

	//获取帐号信息
	XUserInfo* GetAccountInfo(CString name);

	//判断用户名和密码
	XUserInfo* DecideAccountAndPsw(CString name, CString psw);

	//添加用户信息
	XUserInfo* AddUserInfo(CString szAccount, CString szPSW, POWERTYPE type);

	//删除帐号
	void DeleteAccount(CString name);

	//获取普通用户
	void GetNormalUser(VEC_USERINFO& VecUesrInfo);

	//获取用户信息集合
	VEC_USERINFO& GetVecUserInfo();

	//获取用户个数
	int GetUserCount();

	//操作
	void Operate(OPERATETYPE type, void* pData);

	//更新控件UI
	void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);

	//是否登录
	BOOL IsLogin();

	//获取用户节点权限
	BOOL GetUserNodePower(int nInputIndex, int nOutputIndex);

	//是否管理员用户
	BOOL IsAdminUser();

	inline CString GetNotice(){return m_szNotice;}

	inline void SetNotice(CString szNotice){m_szNotice=szNotice;}

public:

	XDelegateUserManage* GetDelegate();

	//设置当前用户信息
	void SetCurUserInfo(XUserInfo* p);

	//获取当前用户信息
	XUserInfo* GetCurUserInfo();

private:

	void OperateOfLogin();

	void OperateOfUserManage();

	void OperateOfPowerManage();

	void OperateOfResetUserNodePower();

	void UpdateControlUIByAdmin(CCmdUI* pCmdUI);

private:

	//清除数据
	void ClearData();

private:

	XDelegateUserManage* m_pDelegate;

	//用户信息集合
	VEC_USERINFO m_VecUserInfo;

	//当前用户信息
	XUserInfo* m_CurUserInfo;

	CString m_szNotice;
};

