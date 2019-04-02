#pragma once

class XInputSignalPane;
class XInputSignal;

class XDataInputSignalPane
{
private:
	XDataInputSignalPane(void);
	~XDataInputSignalPane(void);

public:

	//获取数据
	static void GetData(XInputSignalPane* pPane, CArchive& arch);

	//保存数据
	static void SaveData(XInputSignalPane* pPane, CArchive& arch);

private:

	//获取版本1数据
	static void GetDataOfVersion1(XInputSignalPane* pPane, CArchive& arch);

	static void SaveVecInputSignal(XInputSignalPane* pPane,CArchive& arch);

	static void SaveMapInputGroup(XInputSignalPane* pPane,CArchive& arch);

	static void GetVecInputSignal(XInputSignalPane* pPane,CArchive& arch);

	static void GetMapInputGroup(XInputSignalPane* pPane,CArchive& arch);

	static void SaveVecInput(XInputSignal* pInputSignal,CArchive& arch);

	static void GetVecInput(XInputSignal* pInputSignal,CArchive& arch);
};

