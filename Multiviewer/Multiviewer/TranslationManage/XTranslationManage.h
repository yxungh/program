#pragma once

#include "XBaseTranslationManage.h"

class XTranslationManage : public XBaseTranslationManage
{
public:
	XTranslationManage(void);
	~XTranslationManage(void);

	//初始化
	virtual void Init();

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl);

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl);

	//获取语言类型
	virtual CString GetLanguagetype();

	//设置语言类型
	virtual void SetLanguagetype(CString type);

	//重置界面
	virtual void ReLoadInterface();

private:

	//获取语言类型
	LANGUAGETYPE GetLanguageType();

	//设置语言类型
	void SetLanguageType(LANGUAGETYPE type);

	//保存语言类型
	void SaveLanguageType(LANGUAGETYPE type);

	//根据语言类型获取语言文件路径
	CString GetTranslationFilePath(LANGUAGETYPE type);

	//根据语言名称获取语言类型
	LANGUAGETYPE GetLanguageType(CString szLanguageName);

	//根据语言类型获取语言名称
	CString GetLanguageName(LANGUAGETYPE type);

private:

	//更新语言名称显示
	void UpdateControlDataShowOfLanguageName(CMFCRibbonComboBox* pCombox);

	//语言类型改变
	void ControlDataChangeOfLanguageName(CMFCRibbonComboBox* pCombox);

private:

	//语言类型
	LANGUAGETYPE m_LanguageType;

	//语言文件路径
	CString m_szTranslationFilePath;
};

