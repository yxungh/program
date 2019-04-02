#pragma once
#include "XConstant.h"

class XDelegateReciveDataManage
{
public:
	XDelegateReciveDataManage(void);
	~XDelegateReciveDataManage(void);

	//²Ù×÷
	virtual void Operate(OPERATETYPE type, void* pData) = 0;
};

