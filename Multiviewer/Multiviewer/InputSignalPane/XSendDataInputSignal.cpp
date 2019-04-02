#include "StdAfx.h"
#include "XSendDataInputSignal.h"
#include "XInputSignalPane.h"
#include "XOSDInfo.h"
#include "XInputSignal.h"
#include "XEDIDInfo.h"
#include "XStreamAddrInfo.h"


int XSendDataInputSignal::m_nIndex=0;
int XSendDataInputSignal::m_nChenal=0;

#define GETSIGNALCUT 8
#define GetPANEIP    53
#define GETSTREAM    128

XSendDataInputSignal::XSendDataInputSignal(void)
{
}

XSendDataInputSignal::~XSendDataInputSignal(void)
{
}

//************************************
// Method:    AddSendDataByProtocol
// FullName:  XSendDataInputSignal::AddSendDataByProtocol
// Access:    private static 
// Returns:   void
// Qualifier:
// Parameter: XInputSignalPane * pPane
// Parameter: unsigned char * pSrcData
// Parameter: unsigned short nSrcDataLen
// Parameter: ORDERNUM orderNum
// Parameter: ORDERTYPE orderType
//************************************
void XSendDataInputSignal::AddSendDataByProtocol(XInputSignalPane* pPane, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType)
{
	int nLen = nSrcDataLen + 10;

	unsigned char* pData = new unsigned char[nLen];

	//************************************
	pData[0]=0xFF;
	pData[1]=0xFE;
	pData[2]=m_nIndex;
	pData[3]=m_nChenal;
	pData[4]=0x00;

	switch(orderNum)
	{
	case ORDERNUM_DATATRANS:
		{
			pData[5]=0x1A;
		}
		break;
	case ORDERNUM_OSD:
		{
			pData[5]=0x17;
		}
		break;
	case ORDERNUM_SETSIGNALCUT:
		{
			pData[5]=0x10;
		}
		break;
	case ORDERNUM_GETSIGNALCUT:
		{
			pData[5]=0x90;
		}
		break;
	case ORDERNUM_BORDEROVERLAY:
		{
			pData[5]=0x11;
		}
		break;
	case ORDERNUM_CHANGECHENAL:
		{
			pData[5]=0x20;
		}
		break;
	case ORDERNUM_IPSTREAM:
		{
			pData[5]=0x13;
		}
		break;
	case ORDERNUM_PANEIPSET:
		{
			pData[5]=0x12;
		}
		break;
	case ORDERNUM_GETPANEIP:
		{
			pData[5]=0x92;
		}
		break;
	case ORDERNUM_GETSTREAMADDR:
		{
			pData[5]=0x93;
		}
		break;
	default:
		break;
	}

	switch(orderType)
	{
	case ORDERTYPE_INPUT:
		{
			unsigned short nTempSrcDataLen = GETSIGNALCUT;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &nSum, 2);
		}
		break;
	case ORDERTYPE_GETPANEIP:
		{
			unsigned short nTempSrcDataLen = GetPANEIP;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &nSum, 2);
		}
		break;
	case ORDERTYPE_GETSTREAMADDR:
		{
			unsigned short nTempSrcDataLen = GETSTREAM;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &nSum, 2);
		}
		break;
	case ORDERTYPE_OUTPUT:
		{
			unsigned short nTempSrcDataLen=nSrcDataLen;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			memcpy(pData + 8, pSrcData, nSrcDataLen);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8+nSrcDataLen,&nSum,2);
		}
		break;
	default:
		break;
	}

	//************************************
	pPane->SendData((char*)pData, nLen);

	delete[] pData;
}

unsigned short XSendDataInputSignal::CheckNum(unsigned char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];

		nSum=nSum&0xFFFF;
	}
	return nSum;
}

void XSendDataInputSignal::AddSendDataOfOSDData(XInputSignalPane* pPane, XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	XOSDInfo* pOSDInfo = pInputSignal->GetOSDInfo();

	int nMutrixDataLen = pOSDInfo->GetMutrixDataLen();

	char* pMutrixData = pOSDInfo->GetMutrixData();

	int nMaxSendData = 1024;

	int nPos = 0;

	while (nMutrixDataLen > 0)
	{
		int nSendMutrixDataLen = 0;

		if (nMutrixDataLen > nMaxSendData)
		{
			nSendMutrixDataLen = nMaxSendData;
		}
		else
		{
			nSendMutrixDataLen = nMutrixDataLen;
		}

		nMutrixDataLen -= nSendMutrixDataLen;

		int nOSDDataLen=5+nSendMutrixDataLen;
		unsigned char* OSDData = new unsigned char[nOSDDataLen];

		OSDData[0]=0x02;
		memcpy(OSDData+1,&nPos,4);

		memcpy(OSDData+5, pMutrixData, nSendMutrixDataLen);

		AddSendDataByProtocol(pPane,OSDData,nOSDDataLen,ORDERNUM_DATATRANS,ORDERTYPE_OUTPUT);

		pMutrixData += nSendMutrixDataLen;

		nPos += nSendMutrixDataLen;

		delete []OSDData;
	}
}

void XSendDataInputSignal::AddSendDataOfOSD(XInputSignalPane* pPane, XInputSignal* pInputSignal,int n)
{
	XOSDInfo* pOSDInfo = pInputSignal->GetOSDInfo();

	//样式序号
	int nType=pOSDInfo->GetType();

	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	unsigned short nX1 = pOSDInfo->GetX();
	unsigned short nY1 = pOSDInfo->GetY();
	unsigned short nX2 = pOSDInfo->GetWidth();
	unsigned char nY2 = (unsigned char)pOSDInfo->GetHeight();

	//字体颜色
	COLORREF color = pOSDInfo->GetColor();
	unsigned char colorR = GetRValue(color);
	unsigned char colorG = GetGValue(color);
	unsigned char colorB = GetBValue(color);

	unsigned char colorCR=(unsigned char)(0.439*colorR-0.368*colorG-0.071*colorB+128);
	unsigned char colorY=(unsigned char)(0.257*colorR+0.564*colorG+0.098*colorB+16);
	unsigned char colorCB=(unsigned char)(-0.148*colorR-0.291*colorG+0.439*colorB+128);

	//背景色
	COLORREF Bkcolor = pOSDInfo->GetBkColor();
	unsigned char BkcolorR = GetRValue(Bkcolor);
	unsigned char BkcolorG = GetGValue(Bkcolor);
	unsigned char BkcolorB = GetBValue(Bkcolor);

	unsigned char BKcolorCR=(unsigned char)(0.439*BkcolorR-0.368*BkcolorG-0.071*BkcolorB+128);
	unsigned char BKcolorY=(unsigned char)(0.257*BkcolorR+0.564*BkcolorG+0.098*BkcolorB+16);
	unsigned char BKcolorCB=(unsigned char)(-0.148*BkcolorR-0.291*BkcolorG+0.439*BkcolorB+128);

	//************************************
	int nSendDataLen = 13;
	unsigned char* sendData = new unsigned char[nSendDataLen];

	if(n==0)
	{
		sendData[0]=0;
	}
	else
	{
		sendData[0]=nType;
	}
	
	sendData[1]=colorCB;
	sendData[2]=colorY;
	sendData[3]=colorCR;

	sendData[4]=BKcolorCB;
	sendData[5]=BKcolorY;
	sendData[6]=BKcolorCR;

	unsigned short nTempX1=nX1;
	memcpy(sendData+7,&nTempX1,2);
	unsigned short nTempY1=nY1;
	memcpy(sendData+9,&nTempY1,2);
	sendData[11]=nX2/8;
	sendData[12]=nY2;

	AddSendDataByProtocol(pPane, sendData, nSendDataLen,ORDERNUM_OSD,ORDERTYPE_OUTPUT);

	delete[] sendData;
}

void XSendDataInputSignal::AddSendDataOfSignalCut(XInputSignalPane* pPane, XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	XSignalCutInfo* pInfo=pInputSignal->GetDefaultCutInfo();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	int nDataLen=8;

	unsigned char Data[8]={0};

	unsigned short nLTX=pInfo->GetSignalCutX1();
	memcpy(Data,&nLTX,2);
	unsigned short nLTY=pInfo->GetSignalCutY1();
	memcpy(Data+2,&nLTY,2);
	unsigned short nRBX=pInfo->GetSignalCutX2();
	memcpy(Data+4,&nRBX,2);
	unsigned short nRBY=pInfo->GetSignalCutY2();
	memcpy(Data+6,&nRBY,2);

	AddSendDataByProtocol(pPane, Data, nDataLen,ORDERNUM_SETSIGNALCUT,ORDERTYPE_OUTPUT);
}

void XSendDataInputSignal::AddSendDataOfBorderOverlay(XInputSignalPane* pPane, XInputSignal* pInputSignal)
{
	XBorderOverlay* pBorder=pInputSignal->GetBorderOverLay();

	int nWidth=pBorder->GetBorderWith();

	COLORREF color=pBorder->GetBorderColor();

	unsigned char colorR = GetRValue(color);
	unsigned char colorG = GetGValue(color);
	unsigned char colorB = GetBValue(color);

	unsigned char colorCR=(unsigned char)(0.439*colorR-0.368*colorG-0.071*colorB+128);
	unsigned char colorY=(unsigned char)(0.257*colorR+0.564*colorG+0.098*colorB+16);
	unsigned char colorCB=(unsigned char)(-0.148*colorR-0.291*colorG+0.439*colorB+128);

	int nIndex=pInputSignal->GetInputIndex();

	m_nIndex=(nIndex-1)/4;
	m_nChenal=(nIndex-1)%4;

	int nDataLen=4;

	unsigned char *data=new unsigned char[nDataLen];

	data[0]=nWidth;
	data[1]=colorCB;
	data[2]=colorY;
	data[3]=colorCR;

	AddSendDataByProtocol(pPane, data, nDataLen,ORDERNUM_BORDEROVERLAY,ORDERTYPE_OUTPUT);

	delete []data;	
}

void XSendDataInputSignal::AddSendDataOfEDID(XInputSignalPane* pPane, XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	XEDIDInfo* pInfo = pInputSignal->GetEDIDInfo();

	CString szText=pInfo->GetText();
	int nEDIDDataLen = pInfo->GetDataLen();
	char* pEDIDData=new char[nEDIDDataLen+1];
	memset(pEDIDData,'\0',nEDIDDataLen+1);

	int i=0;
	for(i=0;i<nEDIDDataLen;i++)
	{
		pEDIDData[i]=(char)szText.GetAt(i);
	}
	pEDIDData[i]='\0';

	int nMaxSendData = 1024;
	int nPos = 0;
	while (nEDIDDataLen > 0)
	{
		int nSendDataLen = 0;

		if (nEDIDDataLen > nMaxSendData)
		{
			nSendDataLen = nMaxSendData;
		}
		else
		{
			nSendDataLen = nEDIDDataLen;
		}

		nEDIDDataLen -= nSendDataLen;

		int nDataLen=5+nSendDataLen;

		char* pTemp=pEDIDData;
		unsigned char* pData = new unsigned char[nDataLen];

		pData[0]=0x01;
		memcpy(pData+1,&nPos,4);

		memcpy(pData+5, pTemp, nSendDataLen);

		AddSendDataByProtocol(pPane,pData,nSendDataLen,ORDERNUM_DATATRANS,ORDERTYPE_OUTPUT);

		pTemp += nSendDataLen;

		nPos += nSendDataLen;

		delete []pData;
	}

	delete []pEDIDData;
}

void XSendDataInputSignal::AddSendDataOfChangeChenal(XInputSignalPane* pPane,XInputSignal* pInputSignal,int& nCurChe,int& nSelectedChe)
{
	if((nCurChe-1)==nSelectedChe)
	{
		return;
	}

	int nInputIndex=pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	int nDataLen=1;

	unsigned char *data=new unsigned char[nDataLen];

	data[0]=nSelectedChe;

	AddSendDataByProtocol(pPane,data,nDataLen,ORDERNUM_CHANGECHENAL,ORDERTYPE_OUTPUT);

	delete []data;	
}

void XSendDataInputSignal::AddSendDataOfStreamAddr(XInputSignalPane* pPan,XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	XStreamAddrInfo* pInfo = pInputSignal->GetStreamInfo();

	CString szText=pInfo->GetText();
	int nDataLen = pInfo->GetDataLen();

	USES_CONVERSION;
	char* pData=W2A(szText);

	int nRealDataLen=strlen(pData)+1;
	pData[nRealDataLen]='\0';

	//地址长度<126
	int nStreamDataLen=126;
	char pStreamData[126]={0};

	if(nRealDataLen<nStreamDataLen)
	{
		//减去126剩余长度
		int nLen=nStreamDataLen-nRealDataLen;

		char* pTemp=pData;
		memcpy(pStreamData,pTemp,nRealDataLen);

		int n=0;
		memcpy(pStreamData+nRealDataLen,&n,nLen);
	}

	//////////////////////////////////////////////////////////////////////////

	int nSendDataLen=128;

	unsigned char pSendData[128]={0};

	pSendData[0]=nRealDataLen;

	char* pTempStreamData=pStreamData;

	memcpy(pSendData+1,pTempStreamData,126);

	pSendData[127]=1;

	AddSendDataByProtocol(pPan,pSendData,nSendDataLen,ORDERNUM_IPSTREAM,ORDERTYPE_OUTPUT);

	//delete []pData;
}

void XSendDataInputSignal::AddSendDataOfPaneIPAddr(XInputSignalPane* pPane,XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;

	m_nChenal=0xEE;

	XPaneIPAddrInfo* pInfo=pInputSignal->GetPaneIPAddrInfo();

	CString szPaneIP=pInfo->GetPaneIP();
	USES_CONVERSION;
	char* pIP=W2A(szPaneIP);
	unsigned long nIP=inet_addr(pIP);

	CString szPaneMask=pInfo->GetPaneMask();
	char* pMask=W2A(szPaneMask);
	unsigned long nMask=inet_addr(pMask);

	CString szPaneGateWay=pInfo->GetPaneGateWay();
	char* pGateWay=W2A(szPaneGateWay);
	unsigned long nGateWay=inet_addr(pGateWay);

	int* pMAC=pInfo->GetArrMAC();

	int nModel=pInfo->GetModel();
	
	/////////////////////////////////////////////////////

	int nDataLen=53;
	unsigned char pData[53]={0};

	pData[0]=nModel;

	memcpy(pData+1,&nIP,4);
	memcpy(pData+5,&nMask,4);
	memcpy(pData+9,&nGateWay,4);

	for(int i=0;i<6;i++)
	{
		pData[13+i]=pMAC[i];
	}

	int i=0;
	memcpy(pData+19,&i,16);
	memcpy(pData+35,&i,16);

	pData[51]=0;

	pData[52]=1;

	AddSendDataByProtocol(pPane,pData,nDataLen,ORDERNUM_PANEIPSET,ORDERTYPE_OUTPUT);
}

void XSendDataInputSignal::AddSendDataOfGetPaneNet(XInputSignalPane* pPane,XInputSignal* pInputSignal)
{
	int nInputIndex=pInputSignal->GetInputIndex();

	int nPaneIndex=(nInputIndex-1)/4;

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=0xEE;

	int nDatalen=0;

	unsigned char *data=new unsigned char[nDatalen];

	AddSendDataByProtocol(pPane,data,nDatalen,ORDERNUM_GETPANEIP,ORDERTYPE_GETPANEIP);

	delete []data;
}

void XSendDataInputSignal::AddSendDataOfGetStreamAddr(XInputSignalPane* pPane,XInputSignal* pInputSignal)
{
	int nInputIndex = pInputSignal->GetInputIndex();

	m_nIndex=(nInputIndex-1)/4;
	m_nChenal=(nInputIndex-1)%4;

	int nDatalen=0;

	unsigned char *data=new unsigned char[nDatalen];

	AddSendDataByProtocol(pPane,data,nDatalen,ORDERNUM_GETSTREAMADDR,ORDERTYPE_GETSTREAMADDR);

	delete []data;
}