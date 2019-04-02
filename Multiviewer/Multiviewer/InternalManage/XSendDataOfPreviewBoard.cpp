#include "stdafx.h"
#include "XSendDataOfPreviewBoard.h"
#include "XInternalManage.h"



int XSendDataPreviewBoard::m_nIndex=0;
int XSendDataPreviewBoard::m_nChenal=0;

#define GETPREVIEWNET  53+8
#define GETBITRATE     24

XSendDataPreviewBoard::XSendDataPreviewBoard()
{

}

XSendDataPreviewBoard::~XSendDataPreviewBoard()
{

}


void XSendDataPreviewBoard::AddSendDataByProtocol(XInternalManage* pManage, unsigned char* pSrcData, unsigned short nSrcDataLen,ORDERNUM orderNum,ORDERTYPE orderType)
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
	case ORDERNUM_SAVESCENE:
		{
			pData[5]=0x0B;
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
	pManage->SendData((char*)pData, nLen);

	CString szTemp=_T("");
	CString szStr=_T("");
	for (int i=0;i<nLen;i++)
	{
		szTemp.Format(_T("%02X "),pData[i]);
		szStr += szTemp;
	}
	TRACE(_T("X=%s\n"),szStr);

	delete[] pData;
}

unsigned short XSendDataPreviewBoard::CheckNum(unsigned char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];

		nSum=nSum&0xFFFF;
	}

	return nSum;
}

void XSendDataPreviewBoard::SendDataOfSetPreviewNet(XInternalManage* pManage)
{
	XBoardNetInfo* pInfo=pManage->GetBoardInfo();
	int nBoardIndex=pInfo->GetBoardIndex();

	int nSecret=pInfo->GetSecret();

	m_nIndex=nBoardIndex-1+128;
	m_nChenal=0xEE;

	int nModel=pInfo->GetModel();

	USES_CONVERSION;
	CString szUseName=pInfo->GetUseName();
	szUseName.Trim();
	char* pUseName=W2A(szUseName);
	int nUseNameLen=strlen(pUseName)+1;
	pUseName[nUseNameLen]='\0';

	CString szPassWd=pInfo->GetPassWd();
	szPassWd.Trim();
	char* pPassWd=W2A(szPassWd);
	int nPassWdLen=strlen(pPassWd)+1;
	pPassWd[nPassWdLen]='\0';
	//*********************************
	CString szPaneIP=pInfo->GetIPAddr();
	char* pIP=W2A(szPaneIP);
	unsigned long nIP=inet_addr(pIP);

	CString szPaneMask=pInfo->GetMaskAddr();
	char* pMask=W2A(szPaneMask);
	unsigned long nMask=inet_addr(pMask);

	CString szPaneGateWay=pInfo->GetGateWayAddr();
	char* pGateWay=W2A(szPaneGateWay);
	unsigned long nGateWay=inet_addr(pGateWay);

	int* pMAC=pInfo->GetArrMAC();
	//*********************************
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

	memcpy(pData+19,pUseName,16);
	memcpy(pData+35,pPassWd,16);

	pData[51]=nSecret;

	pData[52]=1;

	AddSendDataByProtocol(pManage,pData,nDataLen,ORDERNUM_SETPREVIEWNET,ORDERTYPE_SETPREVIEWNET);
}

void XSendDataPreviewBoard::SendDataOfGetPreviewNet(XInternalManage* pManage)
{
	XBoardNetInfo* pInfo=pManage->GetBoardInfo();

	int nBoardIndex=pInfo->GetBoardIndex();

	m_nIndex=nBoardIndex-1+128;

	m_nChenal=0xEE;

	int nDatalen=0;

	unsigned char *pData=new unsigned char[nDatalen];

	AddSendDataByProtocol(pManage,pData,nDatalen,ORDERNUM_GETPREVIEWNET,ORDERTYPE_GETPREVIEWNET);

	delete []pData;
}

void XSendDataPreviewBoard::AddSendDataOfReadBitRateInfo(XInternalManage* pManage,int nBoardIndex)
{
	m_nIndex=nBoardIndex-1+128;

	m_nChenal=0xEE;

	int nDatalen=0;

	unsigned char *pData=new unsigned char[nDatalen];

	AddSendDataByProtocol(pManage,pData,nDatalen,ORDERNUM_GETBITRATE,ORDERTYPE_GETBITRATE);

	delete []pData;
}

void XSendDataPreviewBoard::AddSendDataOfBitRate(XInternalManage* pManage,int nBoardIndex)
{
	m_nIndex=nBoardIndex-1+128;
	m_nChenal=0xEE;

	XBitRateInfo* pInfo=pManage->GetBitRateInfo();

	int nMainDpi1=pInfo->GetMainDpi1();
	int nMainBitRate1=pInfo->GetMainBitRate1();
	int nSubDpi1=pInfo->GetSubDpi1();
	int nSubBitRate1=pInfo->GetSubBitRate1();
	int nFlag1=pInfo->GetFlag1();
	//////////////////////////////////////////////////////////////////////////
	int nMainDpi2=pInfo->GetMainDpi2();
	int nMainBitRate2=pInfo->GetMainBitRate2();
	int nSubDpi2=pInfo->GetSubDpi2();
	int nSubBitRate2=pInfo->GetSubBitRate2();
	int nFlag2=pInfo->GetFlag2();
	//////////////////////////////////////////////////////////////////////////
	int nMainDpi3=pInfo->GetMainDpi3();
	int nMainBitRate3=pInfo->GetMainBitRate3();
	int nSubDpi3=pInfo->GetSubDpi3();
	int nSubBitRate3=pInfo->GetSubBitRate3();
	int nFlag3=pInfo->GetFlag3();
	//////////////////////////////////////////////////////////////////////////
	int nMainDpi4=pInfo->GetMainDpi4();
	int nMainBitRate4=pInfo->GetMainBitRate4();
	int nSubDpi4=pInfo->GetSubDpi4();
	int nSubBitRate4=pInfo->GetSubBitRate4();
	int nFlag4=pInfo->GetFlag4();
	////////////////////////////////////////////////////////////////////////////
	int nDataLen=24;
	unsigned char pData[24]={0};

	pData[0]=nMainDpi1;
	pData[1]=nMainBitRate1;
	pData[2]=nFlag1;
	pData[3]=nSubDpi1;
	pData[4]=nSubBitRate1;
	pData[5]=nFlag1;
	//////////////////////////////////////////////////////////////////////////
	pData[6]=nMainDpi2;
	pData[7]=nMainBitRate2;
	pData[8]=nFlag2;
	pData[9]=nSubDpi2;
	pData[10]=nSubBitRate2;
	pData[11]=nFlag2;
	//////////////////////////////////////////////////////////////////////////
	pData[12]=nMainDpi3;
	pData[13]=nMainBitRate3;
	pData[14]=nFlag3;
	pData[15]=nSubDpi3;
	pData[16]=nSubBitRate3;
	pData[17]=nFlag3;
	/////////////////////////////////////////////////////////////////////////
	pData[18]=nMainDpi4;
	pData[19]=nMainBitRate4;
	pData[20]=nFlag4;
	pData[21]=nSubDpi4;
	pData[22]=nSubBitRate4;
	pData[23]=nFlag4;

	AddSendDataByProtocol(pManage,pData,nDataLen,ORDERNUM_SETBITRATE,ORDERTYPE_SETBITRATE);
}

void XSendDataPreviewBoard::SendDataBySaveScene(XInternalManage* pMagage,int nSceneIndex)
{
	m_nIndex=0xFF;
	m_nChenal=0xEE;

	int nDataLen=1;

	unsigned char Data[1]={0};
	Data[0]=nSceneIndex;

	AddSendDataByProtocol(pMagage,Data,nDataLen,ORDERNUM_SAVESCENE,ORDERTYPE_SETBITRATE);
}