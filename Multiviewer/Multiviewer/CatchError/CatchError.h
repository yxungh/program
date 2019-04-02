#pragma once

class CatchError
{
public:

	//设置捕获应用程序异常消息
	static void	SetCatchError(CString folderPath);

	//获取DUMP文件路径
	static CString DumpPath();

private:

	//DUMP文件夹路径
	static CString m_DumpFolderPath;
};



