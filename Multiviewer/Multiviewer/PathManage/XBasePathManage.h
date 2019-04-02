#pragma once

class XBasePathManage
{
public:
	XBasePathManage(void);
	virtual ~XBasePathManage(void);

	//初始化
	virtual void Init() = 0;

	//获取翻译文件路径
	virtual CString GetTranslationFilePath(CString szName) = 0;

	//获取数据文件路径
	virtual CString GetDataFilePath(CString szName) = 0;

	//获取场景文件路径
	virtual CString GetSceneFilePath(int nSceneIndex, CString szSceneName) = 0;

	virtual CString GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex) = 0;

	//获取场景文件夹路径
	virtual CString GetSceneFolderPath() = 0;

	//获取DUMP文件路径
	virtual CString GetDumpFilePath() = 0;
};

