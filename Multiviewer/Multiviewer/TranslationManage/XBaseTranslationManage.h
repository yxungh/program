#pragma once

#include "XConstantIM.h"

class XDelegateTranslationManage;

class XBaseTranslationManage
{
public:
	XBaseTranslationManage(void);
	virtual ~XBaseTranslationManage(void);

	//初始化
	virtual void Init() = 0;

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl) = 0;

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl) = 0;

	//获取语言类型
	virtual CString GetLanguagetype()=0;

	//设置语言类型
	virtual void SetLanguagetype(CString type)=0;

	//重置界面
	virtual void ReLoadInterface()=0;

public:

	//设置委托
	void SetDelegate(XDelegateTranslationManage* p);

protected:

	//委托
	XDelegateTranslationManage* m_pDelegate;
};

