#pragma once

#include "XConstantIM.h"

class XDelegateIniManage
{
public:
	XDelegateIniManage(void);
	~XDelegateIniManage(void);

	//重设视图大小
	virtual void ResetViewSize() = 0;

	//刷新视图
	virtual void InvalidateView() = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	virtual void SetMultiScale(float f)=0;
};

