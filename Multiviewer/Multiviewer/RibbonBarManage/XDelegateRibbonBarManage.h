#pragma once

#include "XConstantIM.h"

class XDelegateRibbonBarManage
{
public:
	XDelegateRibbonBarManage(void);
	~XDelegateRibbonBarManage(void);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl) = 0;

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(CString szName) = 0;
};

