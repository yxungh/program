#pragma once

class XSocketUDP;
class XDelegateNetManage;

class XNetManage
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

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam, LPARAM lParam);

public:

	//处理UDP数据
	void HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

	void SetDelegate(XDelegateNetManage* p);

private:

	//打开
	void Open();

	//关闭
	void Close();

private:

	//Socket
	XSocketUDP* m_pSocketUDP;

	XDelegateNetManage* m_pDelegate;

};

