#pragma once

class XHandlePath
{
private:
	XHandlePath(void);
	~XHandlePath(void);

public:

	//初始化
	static void Init();

	//获取应用程序文件夹路径
	static CString GetAppFolderPath();

	//判断文件路径是否存在
	static BOOL	PathExists(CString szPath);

	//获取图片路径
	static CString GetPhotoPath(CString szPhotoName);

	//获取Ini路径
	static CString GetIniPath(CString name);

	//获取翻译文件路径
	static CString GetTranslationFilePath(CString name);

	//获取Dump文件夹路径
	static CString GetDumpFolderPath();

private:

	//应用程序文件夹路径 
	static CString m_szAppFolderPath;
};

