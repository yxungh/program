#pragma once

class XScenePane;

class XDataScenePane
{
private:
	XDataScenePane(void);
	~XDataScenePane(void);

public:

	//获取数据
	static void GetData(XScenePane* pPane, CArchive& arch);

	//保存数据
	static void SaveData(XScenePane* pPane, CArchive& arch);

	static void GetDataOfVersion1(XScenePane* pPane, CArchive& arch);

};
