#pragma once

class XScreenManage;
class XScreen;
class XSignal;
class XScreenDataInfo;

class XDataScreenManage
{
private:
	XDataScreenManage(void);
	~XDataScreenManage(void);

public:

	//获取数据
	static BOOL GetData(XScreenManage* p, CString szPath);

	//获取数据
	static void GetData(XScreenManage* p, CArchive& arch);

	//获取版本1数据
	static void GetDataOfVersion1(XScreenManage* p, CArchive& arch);

	//获取屏幕集合数据
	static void GetDataOfVecScreen(XScreenManage* p, CArchive& arch);

	//获取屏幕数据
	static void GetDataOfScreen(XScreen* p, CArchive& arch);

	static void GetDataOfRowColInfo(XScreenManage* p, CString szPath);
public:

	//保存数据
	static void SaveData(XScreenManage* p, CArchive& arch);

	//保存数据
	static BOOL SaveData(XScreenManage* p, CString szPath);

	//保存屏幕数据
	static void SaveDataOfScreen(XScreen* p, CArchive& arch);

	static void SaveDataOfRowColInfo(XScreenManage* p, CString szPath);

};



