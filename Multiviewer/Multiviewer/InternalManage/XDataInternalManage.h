#pragma once

class XInternalManage;
class XScreenManage;
class XScreen;

class XDataInternalManage
{
private:
	XDataInternalManage(void);
	~XDataInternalManage(void);

public:

	//获取数据
	static void GetData(XInternalManage* pManage, CArchive& arch);

	//保存数据
	static void SaveData(XInternalManage* pManage, CArchive& arch);

private:

	static void GetVecScreenManage(XInternalManage* pManage, CArchive& arch);

	static void GetVecPreviewPane(XInternalManage* pManage, CArchive& arch);

	static void GetSelectBoardInfo(XInternalManage* pManage, CArchive& arch);

	static void GetPreviewTemp(XInternalManage* pManage, CArchive& arch);

	static void GetMapBottomTabLable(XInternalManage* pManage, CArchive& arch);


	static void SaveVecScreenManage(XInternalManage* pManage, CArchive& arch);

	static void SaveVecPreviewPane(XInternalManage* pManage, CArchive& arch);

	static void SaveSelectBoardInfo(XInternalManage* pManage, CArchive& arch);

	static void SavePreviewTemp(XInternalManage* pManage, CArchive& arch);

	static void SaveMapBottomTabLable(XInternalManage* pManage, CArchive& arch);


};

