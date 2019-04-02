#pragma once

#include "XConstantIM.h"

class XDelegateNetManage;

class XBaseNetManage
{
public:
	XBaseNetManage(void);
	virtual ~XBaseNetManage(void);

	//初始化
	virtual void Init() = 0;

	//获取状态
	virtual BOOL GetState() = 0;

	//发送串口数据
	virtual BOOL SendData(CString szIP, int nPort, const char* pData, const int nLen) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI) = 0;

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam, LPARAM lParam) = 0;

public:

	//设置委托
	void SetDelegate(XDelegateNetManage* p);

protected:

	//委托
	XDelegateNetManage* m_pDelegate;
};

