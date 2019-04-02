#pragma once
#include "XConstant.h"

class XDelegateReciveDataManage;

class XReciveDataManage
{
public:
	XReciveDataManage(void);
	~XReciveDataManage(void);

public:

	void Init();

	void SetDelegate(XDelegateReciveDataManage* p);

	void Operate(OPERATETYPE type, void* pData);

	BOOL HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

private:

	void DecodeLogin(unsigned char* pData,int nDataLen);

	void DecodeLoginOut(unsigned char* pData,int nDataLen);

	void DecodeHeart(unsigned char* pData,int nDataLen);

private:

	XDelegateReciveDataManage* m_pDelegate;
};

