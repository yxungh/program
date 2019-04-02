#pragma once

class HandlePath
{
private:
	HandlePath(void);
	~HandlePath(void);

public:

	//初始化
	static void Init();

	//获取应用程序文件夹路径
	static CString GetAppFolderPath();

	//判断文件路径是否存在
	static BOOL	PathExists(CString szPath);

	//获取翻译文件路径
	static CString GetTranslationFilePath(CString szName);

	//获取数据文件路径
	static CString GetDataFilePath(CString szName);

	//获取场景文件夹路径
	static CString GetSceneFolderPath();

	//获取DUMP文件夹路径
	static CString GetDumpFolderPath();

	//获取Ini路径
	static CString GetIniPath(CString name);

	//获取图片路径
	static CString GetPhotoPath(CString szPhotoName);

	//获取文字路径
	static CString GetFontPath(CString szFont);

private:

	//应用程序文件夹路径 
	static CString m_szAppFolderPath;
};

