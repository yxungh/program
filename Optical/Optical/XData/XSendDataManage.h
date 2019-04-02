#pragma once
#include "XConstant.h"

class XDelegateSendDataManage;

class XSendDataManage
{
private:
	XSendDataManage();
	~XSendDataManage();

public:

	static XSendDataManage* GetInstance();

	static void Release();

	void SetDelegate(XDelegateSendDataManage* p);

private:

	BOOL SendData(char* pData, int nDataLen);

	void AddFullSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,PROTOCOLTYPE ProtocolType);

	void AddPackSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,PROTOCOLTYPE ProtocolType);

	void AddData(CString szData,PROTOCOLTYPE nType);

	unsigned short CheckSum(unsigned char *pData,int nLen);

public:

	void SendDataOfHeart(DWORD dHeartTime);

	void AddSendDataOfLogin(CString szUserName,CString szPassWd);

	void AddSendDataOfLoginOut(CString szUserName);

	void SendDataOfAddUser();



private:

	static XSendDataManage* m_pSendDataManage;

	XDelegateSendDataManage* m_pDelegate;

	unsigned short m_nTotalPacket;

	unsigned short m_nCurPacket;

	unsigned short m_nPacketLen;
};