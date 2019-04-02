#pragma once

#include "XConstantIM.h"

class XDelegateDataManage;

class XDataManage
{
public:
	XDataManage(void);
	~XDataManage(void);

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateDataManage* p);

	//操作
	void Operate(OPERATETYPE type, void* pData);

	//处理UDP数据
	BOOL HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

private:

	//检查温度
	void CheckTemperature();

	//重置温度
	void ResetTemperature();


private:

	XDelegateDataManage* m_pDelegate;

private:

	//温度
	CString m_szTemperature;

	//设置温度时间
	DWORD m_TemperatureTime;

private:

	//屏幕同步信息集合
	MAP_SCREENSYNINFO m_MapScreenSynInfo;

private:

	void DecodeInput(unsigned char* pData, int nDataLen);

	void DecodeOutput(unsigned char* pData, int nDataLen);

	void DecodeWindowParamater(unsigned char* pData, int nDataLen);

	void DecodeAsk(unsigned char* pData, int nDataLen);

	void DecodeSceneIndex(unsigned char* pData, int nDataLen);
	
	void DecodeDeviceStatus(unsigned char* pData, int nDataLen);

	void DecodeSignalNum(unsigned char* pData, int nDataLen);

	void DecodePaneIP(unsigned char* pData,int nDataLen);

	void DecodeStreamAddr(unsigned char* pData,int nDataLen);

	void DecodeBitRate(unsigned char* pData, int nDataLen);

	void DecodeMatrixWindowParamater(unsigned char* pData, int nDataLen);
};

