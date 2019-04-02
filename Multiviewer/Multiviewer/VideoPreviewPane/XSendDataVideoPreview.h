#pragma once
#include "XVideoPreviewPane.h"

class XInternalManage;

class XSendDataVideoPreview
{
private:

	XSendDataVideoPreview();
	~XSendDataVideoPreview();

public:

	static void AddSendDataOfCorrBoardChenal(XVideoPreviewPane* pPane,int nInput,int nBoardChenal);

private:

	//添加发送数据-协议
	static void AddSendDataByProtocol(XVideoPreviewPane* pPane, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType);

	static unsigned short CheckNum(unsigned char *pData,int nLen);

public:

	static int m_nIndex;
	static int m_nChenal;

};