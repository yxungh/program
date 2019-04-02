#pragma once

#include "XBasePathManage.h"

class XPathManage : public XBasePathManage
{
public:
	XPathManage(void);
	~XPathManage(void);

	//初始化
	virtual void Init();

	//获取翻译文件路径
	CString GetTranslationFilePath(CString szName);

	//获取数据文件路径
	CString GetDataFilePath(CString szName);

	//获取场景文件路径
	CString GetSceneFilePath(int nSceneIndex, CString szSceneName);

	CString GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex);

	//获取场景文件夹路径
	CString GetSceneFolderPath();

	//获取DUMP文件路径
	CString GetDumpFilePath();

private:

	//获取应用程序文件夹路径
	CString GetAppFolderPath();

private:

	//应用程序文件夹路径 
	CString m_szAppFolderPath;
};

