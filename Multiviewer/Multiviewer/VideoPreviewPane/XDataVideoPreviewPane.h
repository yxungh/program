#pragma once


class XVideoPreviewPane;

class XDataVideoPreviewPane
{
private:
	XDataVideoPreviewPane(void);
	~XDataVideoPreviewPane(void);

public:

	//获取数据
	static void GetData(XVideoPreviewPane* pPane, CArchive& arch);

	//保存数据
	static void SaveData(XVideoPreviewPane* pPane, CArchive& arch);

private:

	//获取版本1数据
	static void GetDataOfVersion1(XVideoPreviewPane* pPane, CArchive& arch);
	//////////////////////////////////////////////////////////////////////////

	//获取窗口信息
	static void GetVecFrame(XVideoPreviewPane* pPane, CArchive& arch);

	//获取前向设备信息
	static void GetForntVecDeviceInfo(XVideoPreviewPane* pPane, CArchive& arch);

	//获取后向设备信息
	static void GetBackVecDeviceInfo(XVideoPreviewPane* pPane, CArchive& arch);

	//获取预览卡网络集合
	static void GetMapBoardNetInfo(XVideoPreviewPane* pPane,CArchive& arch);

	//////////////////////////////////////////////////////////////////////////

	//保存窗口信息
	static void SaveVecFrame(XVideoPreviewPane* pPane, CArchive& arch);

	//保存前向设备信息
	static void SaveForntVecDeviceInfo(XVideoPreviewPane* pPane, CArchive& arch);

	//保存后向设备信息
	static void SaveBackVecDeviceInfo(XVideoPreviewPane* pPane, CArchive& arch);

	//保存预览卡网络集合
	static void SaveMapBoardNetInfo(XVideoPreviewPane* pPane,CArchive& arch);

	//保存预览卡网络参数
	//static void SaveBoardNetInfo(XBoardNetInfo* pInfo,CArchive& arch);
};

