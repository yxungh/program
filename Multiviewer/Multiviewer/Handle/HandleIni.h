#pragma once

class HandleIni
{
private:
	HandleIni(void);
	~HandleIni(void);

public:

	//获取int值
	static int GetInt(CString szAppName, CString szKeyName, int nDefault, 
		CString szPath);

	//获取字符串值
	static CString GetString(CString szAppName, CString szKeyName, CString szDefault, 
		CString szPath);

	//写入数据
	static BOOL WriteData(CString szAppName, CString szKeyName, CString szData, 
		CString szPath);
};

