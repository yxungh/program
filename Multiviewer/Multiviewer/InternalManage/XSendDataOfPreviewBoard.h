
#pragma once
#include "XConstantIM.h"

class XInternalManage;

class XSendDataPreviewBoard
{
private:

	XSendDataPreviewBoard();
	~XSendDataPreviewBoard();

public:

	//设置预览卡参数
	static void SendDataOfSetPreviewNet(XInternalManage* pManage);

	//获取预览卡网络参数
	static void SendDataOfGetPreviewNet(XInternalManage* pManage);

	//读取板卡码率
	static void AddSendDataOfReadBitRateInfo(XInternalManage* pManage,int nBoardIndex);

	//设置码率
	static void AddSendDataOfBitRate(XInternalManage* pManage,int nBoardIndex);

	static void SendDataBySaveScene(XInternalManage* pMagage,int nSceneIndex);

private:

	//添加发送数据-协议
	static void AddSendDataByProtocol(XInternalManage* pManage, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType);

	static unsigned short CheckNum(unsigned char *pData,int nLen);

public:

	static int m_nIndex;
	static int m_nChenal;

};