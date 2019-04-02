#pragma once

#include "XConstantIM.h"

class XInputSignalPane;
class XInputSignal;

class XSendDataInputSignal
{
public:

	//添加发送数据-OSD
	static void AddSendDataOfOSDData(XInputSignalPane* pPane, XInputSignal* pInputSignal);

	//添加发送数据-OSD
	static void AddSendDataOfOSD(XInputSignalPane* pPane, XInputSignal* pInputSignal,int n);

	//添加发送数据-信号裁剪
	static void AddSendDataOfSignalCut(XInputSignalPane* pPane, XInputSignal* pInputSignal);

	static void AddSendDataOfBorderOverlay(XInputSignalPane* pPane, XInputSignal* pInputSignal);

	static void AddSendDataOfEDID(XInputSignalPane* pPane, XInputSignal* pInputSignal);

	static void AddSendDataOfChangeChenal(XInputSignalPane* pPan,XInputSignal* pInputSignal,int& nCurChe,int& nSelectedChe);

	static void AddSendDataOfStreamAddr(XInputSignalPane* pPane,XInputSignal* pInputSignal);

	static void AddSendDataOfPaneIPAddr(XInputSignalPane* pPane,XInputSignal* pInputSignal);

	//获取板卡网络设置
	static void AddSendDataOfGetPaneNet(XInputSignalPane* pPane,XInputSignal* pInputSignal);

	static void AddSendDataOfGetStreamAddr(XInputSignalPane* pPane,XInputSignal* pInputSignal);

private:
	//添加发送数据
	static void AddSendDataByProtocol(XInputSignalPane* pPane, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType);

	//校验和
	static unsigned short CheckNum(unsigned char *pData,int nLen);

private:
	XSendDataInputSignal(void);
	~XSendDataInputSignal(void);

public:

	static int m_nIndex;
	static int m_nChenal;
};

