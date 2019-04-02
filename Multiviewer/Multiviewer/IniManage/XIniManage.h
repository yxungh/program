#pragma once

#include "XConstantIM.h"

class XDelegateIniManage;

class XIniManage
{
public:
	XIniManage(void);
	~XIniManage(void);

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateIniManage* p);

	//更新控件数据显示
	void UpdateControlDataShow(XDATATYPE type, void* pControl);

	//控件数据改变
	void ControlDataChange(XDATATYPE type, void* pControl);

public:

	//获取设备IP
	CString GetDeviceIP();

	//设置设备IP
	void SetDeviceIP(CString str);

	//获取设备端口
	int GetDevicePort();

	//设置设备端口号
	void SetDevicePort(int n);

private:

	//获取Ini数据
	void GetIniData();

private:

	//更新设备IP显示
	void UpdateControlDataShowOfDeviceIP(CMFCRibbonEdit* pCombox);

	//设备IP改变
	void ControlDataChangeOfDeviceIP(CMFCRibbonEdit* pCombox);

	//更新设备端口显示
	void UpdateControlDataShowOfDevicePort(CMFCRibbonEdit* pCombox);

	//设备端口改变
	void ControlDataChangeOfDevicePort(CMFCRibbonEdit* pCombox);
	
private:

	//保存设备IP
	void SaveDataOfDeviceIP(CString s);

	//保存设备端口
	void SaveDataOfDevicePort(int n);

private:

	XDelegateIniManage* m_pDelegate;

private:

	//缩放比例
	int m_Scale;

	//设备IP
	CString m_DeviceIP;

	//设备端口
	int m_DevicePort;
};

