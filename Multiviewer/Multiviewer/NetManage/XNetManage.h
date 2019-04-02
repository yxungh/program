#pragma once

#include "XBaseNetManage.h"

class XSocketUDP;

class XNetManage : public XBaseNetManage
{
public:
	XNetManage(void);
	~XNetManage(void);

	//初始化
	virtual void Init();

	//获取状态
	virtual BOOL GetState();

	//发送串口数据
	virtual BOOL SendData(CString szIP, int nPort, const char* pData, const int nLen);

	//操作
	virtual void Operate(OPERATETYPE type, void* pData);

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam, LPARAM lParam);

public:

	//处理UDP数据
	void HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

private:

	//根据状态更新控件UI
	void UpdateControlUIByState(CCmdUI* pCmdUI, BOOL bState);

	//打开
	void Open();

	//关闭
	void Close();

private:

	//Socket
	XSocketUDP* m_pSocketUDP;
};

