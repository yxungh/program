#pragma once

class XSendData
{
public:
	XSendData(void);
	~XSendData(void);

	//数据
	unsigned char* m_Data;

	//数据长度
	int m_DataLen;

	//IP地址
	//DWORD m_IP;

	//端口
	//int m_Port;

	//数据类型
	//int m_Type;

	//发送计数
	//int m_SendNum;
};
