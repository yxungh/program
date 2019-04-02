#include "stdafx.h"
#include "XSendDataVideoPreview.h"
//#include "XInternalManage.h"
#include "XVideoPreviewFrame.h"


int XSendDataVideoPreview::m_nIndex=0;
int XSendDataVideoPreview::m_nChenal=0;

#define GETPREVIEWNET  53
#define GETBITRATE     24

XSendDataVideoPreview::XSendDataVideoPreview()
{

}

XSendDataVideoPreview::~XSendDataVideoPreview()
{

}


void XSendDataVideoPreview::AddSendDataByProtocol(XVideoPreviewPane* pPane, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType)
{
	int nLen=nSrcDataLen+10;

	unsigned char* pData=new unsigned char[nLen];

	//*******************************************************
	pData[0]=0xFF;
	pData[1]=0xFE;
	pData[2]=m_nIndex;
	pData[3]=m_nChenal;
	pData[4]=0x00;

	//*******************************************************
	switch(orderNum)
	{
	case ORDERNUM_OLDORDER:
		{
			pData[5]=0x0A;
		}
		break;
	case ORDERNUM_SETPREVIEWNET:
		{
			pData[5]=0x12;
		}
		break;
	case ORDERNUM_GETPREVIEWNET:
		{
			pData[5]=0x92;
		}
		break;
	case ORDERNUM_SETBITRATE:
		{
			pData[5]=0x22;
		}
		break;
	case ORDERNUM_GETBITRATE:
		{
			pData[5]=0xA2;
		}
		break;
	case ORDERNUM_MATRIX:
		{
			pData[5]=0x24;
		}
		break;
	default:
		break;
	}

	//*******************************************************

	switch(orderType)
	{
	case ORDERTYPE_GETPREVIEWNET:
		{
			unsigned short nTempSrcDataLen = GETPREVIEWNET;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &nSum, 2);
		}
		break;
	case ORDERTYPE_SETPREVIEWNET:
		{
			unsigned short nTempSrcDataLen=nSrcDataLen;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			memcpy(pData + 8, pSrcData, nSrcDataLen);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8+nSrcDataLen,&nSum,2);
		}
		break;
	case ORDERTYPE_OUTPUT:
		{
			unsigned short nTempSrcDataLen = nSrcDataLen;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			memcpy(pData + 8, pSrcData, nSrcDataLen);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8+nSrcDataLen, &sum, 2);
		}
		break;
	case ORDERTYPE_SETBITRATE:
		{
			unsigned short nTempSrcDataLen = nSrcDataLen;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			memcpy(pData + 8, pSrcData, nSrcDataLen);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8+nSrcDataLen, &sum, 2);
		}
		break;
	case ORDERTYPE_GETBITRATE:
		{
			unsigned short nTempSrcDataLen = GETBITRATE;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short nSum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &nSum, 2);
		}
		break;
	default:
		break;
	}
	//************************************
	pPane->SendData((char*)pData, nLen);

	delete[] pData;
}

unsigned short XSendDataVideoPreview::CheckNum(unsigned char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
		nSum=nSum&0xFFFF;
	}

	return nSum;
}

void XSendDataVideoPreview::AddSendDataOfCorrBoardChenal(XVideoPreviewPane*pPane,int nInput,int nBoardChenal)
{
	CString str;
	str.Format(_T("%dV%d."),nInput,nBoardChenal);
	TRACE(_T("%s\n"),str);

	m_nIndex=0xEE;
	m_nChenal=0xEE;

	int nLen=2;
	unsigned char pOrderData[2]={0};
	pOrderData[0]=nInput;
	pOrderData[1]=nBoardChenal;

	AddSendDataByProtocol(pPane,pOrderData,nLen,ORDERNUM_MATRIX,ORDERTYPE_OUTPUT);

	//////////////////////////////////////////////////////////////////////////

	//CString szOrder;
	//szOrder.Format(_T("%dV%d."),nInput,nBoardChenal);

	//USES_CONVERSION;
	//char* pData=W2A(szOrder);
	//int nRealDataLen=strlen(pData)+1;
	//pData[nRealDataLen]='\0';

	//unsigned char* pOrderData=new unsigned char[nRealDataLen];

	//memcpy(pOrderData,pData,nRealDataLen);

	//AddSendDataByProtocol(pPane,pOrderData,nRealDataLen,ORDERNUM_OLDORDER,ORDERTYPE_OUTPUT);

	//delete []pOrderData;
}
