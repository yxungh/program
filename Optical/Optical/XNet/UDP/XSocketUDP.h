 #pragma once

class XNetManage;

class XSocketUDP
{
public:
	XSocketUDP(void);
	~XSocketUDP(void);

	//打开端口
	BOOL Open();

	//关闭端口
	void Close();

	//获取状态
	BOOL GetState();

	//发送数据
	BOOL SendData(const char* pData, const int nDataLen, char* pIp, 
		u_short nTargetPort);

	//设置网络管理
	void SetNetManage(XNetManage* p);

	//设置窗口句柄
	void SetHWND(HWND h);

	//处理消息
	void HandleMsg(WPARAM wParam, LPARAM lParam);

private:

	void HandleFD_READ();

protected:

	XNetManage* m_NetManage;

	//状态
	BOOL m_bState;

	//套接字
	SOCKET m_Socket;

	//窗口句柄
	HWND m_HWND;
	
	//接收数据缓存
	unsigned char m_Data[2048];
};

