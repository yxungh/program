#pragma once

#include "XConstantIM.h"

class XDelegateDataManage
{
public:
	XDelegateDataManage(void);
	~XDelegateDataManage(void);

	//发送数据
	virtual BOOL SendData(char* pData, int nDataLen) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;
};

