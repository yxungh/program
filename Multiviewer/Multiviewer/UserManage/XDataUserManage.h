#pragma once

class XUserManage;

class XDataUserManage
{
private:
	XDataUserManage(void);
	~XDataUserManage(void);

public:

	//获取数据
	static void GetData(XUserManage* pManage, CArchive& arch);

	//保存数据
	static void SaveData(XUserManage* pManage, CArchive& arch);

public:

	static void SaveStringData(CArchive& arch, unsigned char* pKey, CString s);

	static void SaveIntData(CArchive& arch, unsigned char* pKey, int n);

	static CString GetStringData(CArchive& arch, unsigned char* pKey);

	static int GetIntData(CArchive& arch, unsigned char* pKey);

private:

	//获取版本1数据
	static void GetDataOfVersion1(XUserManage* pManage, CArchive& arch);
};

