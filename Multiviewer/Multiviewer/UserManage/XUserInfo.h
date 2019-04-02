#pragma once

#include "XUserManage.h"

class XUserInfo
{
public:
	XUserInfo(void);
	~XUserInfo(void);

public:

	void SetAccount(CString s);

	void SetPassword(CString s);

	void SetPower(POWERTYPE n);

	CString GetAccount();

	CString GetPassword();

	char GetPower();

	//获取节点权限
	BOOL GetNodePower(int nInputIndex, int nOutputIndex);

	//获取节点权限信息
	XNodePowerInfo* GetNodePowerInfo(int nInputIndex, int nOutputIndex);

	//设置节点权限信息
	void SetNodePowerInfo(int nInputIndex, int nOutputIndex, BOOL bPower);

	//清除节点权限信息集合
	void ClearMapNodePowerInfo();

	MAP_NODEPOWERINFO& GetMapPowerInfo();

public:

	void GetData(CArchive& arch, unsigned char* pKey);

	void SaveData(CArchive& arch, unsigned char* pKey);

	void GetNodePowerInfoData(CArchive& arch, unsigned char* pKey);

	void SaveNodePowerInfoData(CArchive& arch, unsigned char* pKey);

private:

	//清除数据
	void ClearData();
	
private:

	CString m_Account;

	CString m_Password;

	char m_Power;

	MAP_NODEPOWERINFO m_MapNodePowerInfo;
};

