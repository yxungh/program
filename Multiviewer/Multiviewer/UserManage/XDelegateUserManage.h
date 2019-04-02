#pragma once

#include "XConstantIM.h"

class XDelegateUserManage
{
public:
	XDelegateUserManage(void);
	~XDelegateUserManage(void);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//获取输出个数
	virtual int GetOutputCount() = 0;

	//获取输入个数
	virtual int GetInputCount() = 0;
};

