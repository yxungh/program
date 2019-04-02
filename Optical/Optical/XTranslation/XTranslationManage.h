#pragma once
#include "XConstant.h"


class XTranslationManage
{
private:
	XTranslationManage();
	~XTranslationManage();

public:

	//获取单例
	static XTranslationManage* GetInstance();

	//释放单例
	static void Release();

public:

	//初始化
	void Init();

	//获取字符串
	CString GetTranslationString(CString szKey, CString szDefault=_T(""));

	//获取语言类型
	LANGUAGETYPE GetLanguageType();

	//根据名称获取语言类型
	LANGUAGETYPE GetLanguageType(CString szLanguageName);

	//设置语言类型
	void SetLanguageType(LANGUAGETYPE type);

	//根据类型获取语言名称
	CString GetLanguageName(LANGUAGETYPE type);

	//保存语言类型
	void SaveLanguageType();

private:

	//根据语言类型获取语言文件路径
	CString GetTranslationFilePath(LANGUAGETYPE type);

private:

	//语言类型
	LANGUAGETYPE m_LanguageType;

	//语言文件路径
	CString m_szTranslationFilePath;

private:

	static XTranslationManage* m_pTranslationManage;

	//单例回收释放
	//class GC
	//{
	//public:
	//	~GC();
	//};
	//static GC gc;
};