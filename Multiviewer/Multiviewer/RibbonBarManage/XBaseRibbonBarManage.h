#pragma once

#include "XConstantIM.h"

class XDelegateRibbonBarManage;

class XBaseRibbonBarManage
{
public:
	XBaseRibbonBarManage(void);
	virtual ~XBaseRibbonBarManage(void);

public:

	//初始化
	virtual void Init() = 0;

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type) = 0;

	//重载界面
	virtual void ReloadInterface() = 0;

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;
	
public:

	//设置委托
	void SetDelegate(XDelegateRibbonBarManage* p);

protected:

	//委托
	XDelegateRibbonBarManage* m_pDelegate;
};

