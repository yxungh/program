#pragma once

class XDelegateNetManage
{
public:
	XDelegateNetManage(void);
	~XDelegateNetManage(void);

	//获取窗口句柄
	virtual HWND GetHWND() = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//处理UDP数据
	virtual void HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr) = 0;
};

