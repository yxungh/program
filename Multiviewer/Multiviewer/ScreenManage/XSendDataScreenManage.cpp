#include "StdAfx.h"
#include "XSendDataScreenManage.h"
#include "XScreenManage.h"
#include "XScreen.h"
#include "XSignal.h"
#include "XCalculateScreenManage.h"
#include "XInputSignal.h"
#include "XScreenMoveInfo.h"
#include "XTimedPollingInfo.h"
#include "XOldOrderInfo.h"
#include "HandleShearPlate.h"



int XSendDataScreenManage::m_Index=0;
int XSendDataScreenManage::m_Chenal=0;

int XSendDataScreenManage::m_Index2=0;
int XSendDataScreenManage::m_Chenal2=0;

int XSendDataScreenManage::m_nScreenNumOfTwo=0;

VEC_UCHAR VecChar;

#define GETSIGNALOREDRLEN 28
#define GETSCREENOREDRLEN  7
#define GETWINDOWORDERLEN 136
#define GETSCENEINDEX 4
#define GETDEVICESTATUS 4
#define GETSIGNALNUM 5
#define GETMATRIXWINDOWS 0


XSendDataScreenManage::XSendDataScreenManage(void)
{
}

XSendDataScreenManage::~XSendDataScreenManage(void)
{
}

void XSendDataScreenManage::AddSendDataByProtocol(XScreenManage* pScreenManage, unsigned char* pSrcData, unsigned short nSrcDataLen,ADDRESSTYPE addressType,
	ORDERNUM orderNum,ORDERTYPE orderType)
{
	int nLen = nSrcDataLen + 10;

	unsigned char* pData = new unsigned char[nLen];

	//************************************
	pData[0]=0XFF;
	pData[1]=0XFE;

	switch(addressType)
	{
	case ADDRESSTYPE_INPUT:
		{
			pData[2]=m_Index2;
			pData[3]=m_Chenal2;
		}
		break;
	case ADDRESSTYPE_OUTPUT:
		{
			pData[2]=m_Index;
			pData[3]=0xEE;
		}
		break;
	case ADDRESSTYPE_WINDOW:
		{
			pData[2]=m_Index;
			pData[3]=m_nScreenNumOfTwo;
		}
		break;
	case ADDRESSTYPE_OPERATOR:
		{
			pData[2]=m_Index;
			pData[3]=0xEE;
		}
		break;	
	case ADDRESSTYPE_TWOOPERATOR:
		{
			pData[2]=m_Index;
			pData[3]=m_nScreenNumOfTwo;
		}
		break;
	case ADDRESSTYPE_PANEL:
		{
			pData[2]=0xEE;
			pData[3]=0xEE;
		}
		break;
	case ADDRESSTYPE_BROADCAST:
		{
			pData[2]=0xFF;
			pData[3]=0xEE;
		}
		break;
	default:
		break;
	}

	pData[4]=0x00;

	switch(orderNum)
	{
	case ORDERNUM_OLDORDER:
		{
			pData[5]=0x0A;
		}
		break;
	case ORDERNUM_SAVESCENE:
		{
			pData[5]=0x0B;
		}
		break;
	case ORDERNUM_OPENSCENE:
		{
			pData[5]=0x0C;
		}
		break;
	case ORDERNUM_GETINPUT:
		{
			pData[5]=0x8D;
		}
		break;
	case ORDERNUM_GETOUTPUT:
		{
			pData[5]=0x8E;
		}
		break;
	case ORDERNUM_SETOUTPUT:
		{
			pData[5]=0x0E;
		}
		break;
	case ORDERNUM_TIMEDPOLLING:
		{
			pData[5]=0x0F;
		}
		break;
	case ORDERNUM_SIGNAL:
		{
			pData[5]=0x14;
		}
		break;
	case ORDERNUM_RESIGNAL:
		{
			pData[5]=0x94;
		}
		break;
	case ORDERNUM_DELETEALL:
		{
			pData[5]=0x15;
		}
		break;
	case ORDERNUM_OPERATOR:
		{
			pData[5]=0x16;
		}
		break;
	case ORDERNUM_SCREENMOVEASK:
		{
			pData[5]=0x18;
		}
		break;
	case ORDERNUM_SCREENMOVE:
		{
			pData[5]=0x19;
		}
		break;
	case ORDERNUM_MATRIXRESULATION:
		{
			pData[5]=0x21;
		}
		break;
	case ORDERNUM_CLOSEMATRIX:
		{
			pData[5]=0x24;
		}
		break;
	case ORDERNUM_DATATRANS:
		{
			pData[5]=0x1A;
		}
		break;
	case ORDERNUM_FINISH:
		{
			pData[5]=0x7F;
		}
		break;
	case ORDERNUM_SCENEINDEX:
		{
			pData[5]=0x9C;
		}
		break;
	case ORDERNUM_DELETESCENE:
		{
			pData[5]=0x1D;
		}
		break;
	case ORDERNUM_DEVICESTATUS:
		{
			pData[5]=0x9F;
		}
		break;
	case ORDERNUM_GETSIGNALNUM:
		{
			pData[5]=0xA3;
		}
		break;
	case ORDERNUM_GETMTRIXPARA:
		{
			pData[5]=0xA4;
		}
		break;
	default:
		break;
	}
	
	switch(orderType)
	{
	case ORDERTYPE_DEVICESTATUS:
		{
			unsigned short nTempSrcDataLen = GETDEVICESTATUS;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case ORDERTYPE_WINDOWS:
		{
			unsigned short nTempSrcDataLen = GETWINDOWORDERLEN;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case ORDERTYPE_MATRIXWINDOWS:
		{
			unsigned short nTempSrcDataLen = GETMATRIXWINDOWS;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case OEDERTYPE_SCENE:
		{
			unsigned short nTempSrcDataLen = GETSCENEINDEX;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case ORDERTYPE_INPUT:
		{
			unsigned short nTempSrcDataLen = GETSIGNALOREDRLEN;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case OEDERTYPE_SCREEN:
		{
			unsigned short nTempSrcDataLen = GETSCREENOREDRLEN;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
		}
		break;
	case ORDERTYPE_SIGNALNUM:
		{
			unsigned short nTempSrcDataLen = GETSIGNALNUM;
			memcpy(pData + 6, &nTempSrcDataLen, 2);

			unsigned short sum=CheckNum(pData,nLen-2);
			memcpy(pData+8, &sum, 2);
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
	default:
		break;
	}
	//************************************
	//CString szTemp=_T("");
	//CString szStr=_T("");
	//for (int i=0;i<nLen;i++)
	//{
	//	szTemp.Format(_T("%02X "),pData[i]);
	//	szStr+=szTemp;
	//}

	//TRACE(_T("STR=%s\n"),szStr);
	//************************************

	pScreenManage->SendData((char*)pData, nLen);
	delete []pData;
}

unsigned short XSendDataScreenManage::CheckNum(unsigned char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];

		nSum=nSum&0xFFFF;
	}
	return nSum;
}

//************************************
void XSendDataScreenManage::AddSendDataOfGetSignalParamater(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage,NULL,0,ADDRESSTYPE_PANEL,ORDERNUM_GETINPUT,ORDERTYPE_INPUT);	
}

void XSendDataScreenManage::AddSendDataOfGetScreenParamater(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage,NULL,0,ADDRESSTYPE_PANEL,ORDERNUM_GETOUTPUT,OEDERTYPE_SCREEN);
}

void XSendDataScreenManage::AddSendDataOfGetWindowParamater(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage,NULL,0,ADDRESSTYPE_PANEL,ORDERNUM_RESIGNAL,ORDERTYPE_WINDOWS);
}

void XSendDataScreenManage::AddSendDataOfSignal(XScreenManage* pScreenManage, XSignal*& pSignal,RECTF& rect)
{
	XScreen* pScreen = pSignal->GetScreen();
	int nScreenIndex=pScreen->GetIndex();

	//板卡号
	int nPaneIndex=pScreen->GetBoardIndex();
	//是否为4k
	BOOL bIsUltra=pSignal->GetIsUltra();

	pScreenManage->IsTwoScreen(nPaneIndex);
	
	BOOL bIsTwoScreen=pScreen->GetIsTwoSignal();

	//屏幕序号
	//FPGA号-1，16进制+80
	m_Index=nPaneIndex-1+128;

	//两个屏幕中第几个
	m_nScreenNumOfTwo=pScreen->GetNumOfTwoScreen()-1;
	//***************************
	//屏幕分辨率
	int nHdpi=0;
	int nVdpi=0;
	if(!GetReScreenResulation(pScreenManage,pScreen,nHdpi,nVdpi))
	{
		nHdpi=pScreen->GetScreenHdpi();
		nVdpi=pScreen->GetScreenVdpi();	
	}
	//***************************
	RECTF rectSignal=pSignal->GetRect();
	RECTF rectScreen=pScreen->GetRect();

	//每块屏幕的左右坐标（左上角（0，0）
	float nBeginX=rectSignal.X-rectScreen.X;
	float nBeginY=rectSignal.Y-rectScreen.Y;

	//通道显示在FPGA上的实际位置
	float nTempX=(float)1.0*nBeginX*nHdpi/rectScreen.Width;
	float nTempY=(float)1.0*nBeginY*nVdpi/rectScreen.Height;
	float nTempWidth=(float)1.0*rectSignal.Width*nHdpi/rectScreen.Width;
	float nTempHight=(float)1.0*rectSignal.Height*nVdpi/rectScreen.Height;
	float nTempX1=nTempX+nTempWidth-1;
	float nTempY1=nTempY+nTempHight-1;

	unsigned int nShowBeginX=XCalculateScreenManage::GetIntFromFloat(nTempX);
	if(nShowBeginX%2!=0)
		nShowBeginX+=1;

	unsigned int nShowBeginY=XCalculateScreenManage::GetIntFromFloat(nTempY);
	if(nShowBeginY%2!=0)
		nShowBeginY+=1;

	unsigned int nShowEndX=0;
	if(fabs(nTempX1-(nHdpi-1))<0.00001)
		nShowEndX=nHdpi-1;
	else
	{
		unsigned int nTemp=XCalculateScreenManage::GetIntFromFloat(nTempX1);
		if(nTemp%2==0)
			nTemp+=1;
		nShowEndX=nTemp;
	}
	unsigned int nShowEndY=0;
	if(fabs(nTempY1-(nVdpi-1))<0.00001)
		nShowEndY=nVdpi-1;
	else
	{
		unsigned int nTemp=XCalculateScreenManage::GetIntFromFloat(nTempY1);
		if(nTemp%2==0)
			nTemp+=1;
		nShowEndY=nTemp;
	}
	//局部放大坐标
	XExpandInfo* pExpandInfo=pSignal->GetExpandInfo();
	unsigned short nExpandX1=pExpandInfo->GetExpandX1();
	unsigned short nExpandY1=pExpandInfo->GetExpandY1();
	unsigned short nExpandX2=pExpandInfo->GetExpandX2();
	unsigned short nExpandY2=pExpandInfo->GetExpandY2();

	////////////////////
	//返回信号分辨率
	int nResH=0;
	int nResV=0;
	if(!GetReSignalResulation(pScreenManage,pSignal,nResH,nResV))
	{
		nResH=pSignal->GetSignalHdpi();
		nResV=pSignal->GetSignalVdpi();
	}

	//局部放大后信号源分辨率
	int nResHdpi=0;
	int nResVdpi=0;
	if ((0==nExpandX1)
		&&(0==nExpandY1)
		&&(0==nExpandX2)
		&&(0==nExpandY2))
	{
		nResHdpi=nResH;
		nResVdpi=nResV;
	}
	else
	{
		nResHdpi=nExpandX2-nExpandX1+1;
		nResVdpi=nExpandY2-nExpandY1+1;
	}

	//目标源的FPGA显示区
	float nResBeginX=(rectSignal.X-rect.X)*nResHdpi/rect.Width+nExpandX1;
	float nResBeginY=(rectSignal.Y-rect.Y)*nResVdpi/rect.Height+nExpandY1;
	float nTempResWidth=rectSignal.Width*nResHdpi/rect.Width;
	float nTempResHight=rectSignal.Height*nResVdpi/rect.Height;
	float nResEndX=nResBeginX+nTempResWidth-1+nExpandX1;
	float nResEndY=nResBeginY+nTempResHight-1+nExpandY1;

	//TRACE(_T("nResBeginX=%f\n"),nResBeginX);
	//TRACE(_T("nResBeginY=%f\n"),nResBeginY);
	//TRACE(_T("nTempResWidth=%f\n"),nTempResWidth);
	//TRACE(_T("nTempResHight=%f\n"),nTempResHight);
	//TRACE(_T("nResEndX=%f\n"),nResEndX);
	//TRACE(_T("nResEndY=%f\n"),nResEndY);
	//
	//TRACE(_T("---------------------------"));
	//目标源显示百分比
	float nTempRateX1=(float)1.0*(nResBeginX/(nResH-1))*0x800000;
	float nTempRateY1=(float)1.0*(nResBeginY/(nResV-1))*0x800000;
	float nTempRateX2=(float)1.0*(nResEndX/(nResH-1))*0x800000;
	float nTempRateY2=(float)1.0*(nResEndY/(nResV-1))*0x800000;

	unsigned int nRateX1=XCalculateScreenManage::GetIntFromFloat(nTempRateX1);
	unsigned int nRateY1=XCalculateScreenManage::GetIntFromFloat(nTempRateY1);
	unsigned int nRateX2=XCalculateScreenManage::GetIntFromFloat(nTempRateX2);
	unsigned int nRateY2=XCalculateScreenManage::GetIntFromFloat(nTempRateY2);

	//TRACE(_T("nRateX1=%d\n"),nRateX1);
	//TRACE(_T("nRateY1=%d\n"),nRateY1);
	//TRACE(_T("nRateX2=%d\n"),nRateX2);
	//TRACE(_T("nRateY2=%d\n"),nRateY2);
	//TRACE(_T("---------------------------"));
	//************************************
	//信号ID
	unsigned int nSignalID=pSignal->GetSignalID();

	unsigned int nInPutIndex=pSignal->GetInputIndex();

	int nDatalen=33;
	unsigned char data[33]={0};
	//************************************
	unsigned short nShowX1=nShowBeginX;
	memcpy(data,&nShowX1,2);
	unsigned short nShowX2=nShowEndX;
	memcpy(data+2,&nShowX2,2);
	unsigned short nShowY1=nShowBeginY;
	memcpy(data+4,&nShowY1,2);
	unsigned short nShowY2=nShowEndY;
	memcpy(data+6,&nShowY2,2);
	//************************************	
	memcpy(data+8,&nRateX1,3);
	memcpy(data+11,&nRateX2,3);
	memcpy(data+14,&nRateY1,3);
	memcpy(data+17,&nRateY2,3);
	//************************************
	memcpy(data+20, &nSignalID,4);
	data[24]=nInPutIndex;
	//************************************	
	memcpy(data+25,&nExpandX1,2);
	memcpy(data+27,&nExpandY1,2);
	memcpy(data+29,&nExpandX2,2);
	memcpy(data+31,&nExpandY2,2);
	//************************************
	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage, data, nDatalen,ADDRESSTYPE_WINDOW,ORDERNUM_SIGNAL,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage, data, nDatalen,ADDRESSTYPE_OUTPUT,ORDERNUM_SIGNAL,ORDERTYPE_OUTPUT);

		//CString szTemp=_T("");
		//CString szStr=_T("");
		//for (int i=0;i<nDatalen;i++)
		//{
		//	szTemp.Format(_T("%02X "),data[i]);
		//	szStr+=szTemp;
		//}

		////TRACE(_T("STR=%s\n"),szStr);

		//HandleShearPlate::CopyOrderToSharePlate(szStr);
	}

	//************************************
	//更新信号区域
	float nAdjustX=(float)1.0*nShowX1*rectScreen.Width/nHdpi+rectScreen.X;
	float nAdjustY=(float)1.0*nShowY1*rectScreen.Height/nVdpi+rectScreen.Y;
	float nSignalWidth=(float)nShowX2-nShowX1+1;
	float nSignalHeight=(float)nShowY2-nShowY1+1;
	float nAdjustSignalWidth=(float)1.0*nSignalWidth*rectScreen.Width/nHdpi;
	float nAdjustSignalHight=(float)1.0*nSignalHeight*rectScreen.Height/nVdpi;

	RECTF adjustSignalRect;
	if(bIsUltra)
	{
		adjustSignalRect.X=nAdjustX;
		adjustSignalRect.Y=nAdjustY;
		adjustSignalRect.Width=nAdjustSignalWidth;
		adjustSignalRect.Height=nAdjustSignalHight;
	}
	else
	{
		int nTempAdjustX=XCalculateScreenManage::GetIntFromFloat(nAdjustX);
		int nTempAdjustY=XCalculateScreenManage::GetIntFromFloat(nAdjustY);
		int nTempAdjustW=XCalculateScreenManage::GetIntFromFloat(nAdjustSignalWidth);
		int nTempAdjustH=XCalculateScreenManage::GetIntFromFloat(nAdjustSignalHight);

		adjustSignalRect.X=nTempAdjustX;
		adjustSignalRect.Y=nTempAdjustY;
		adjustSignalRect.Width=nTempAdjustW;
		adjustSignalRect.Height=nTempAdjustH;
	}

	pSignal->SetRect(adjustSignalRect);
}

void XSendDataScreenManage::AddSendDataOfMatrixSignal(XScreenManage* pScreenManage,XSignal* pSignal,XScreen* pScreen)
{
	int nSignalIndex=pSignal->GetInputIndex();

	int nBoardIndex=pScreen->GetBoardIndex();

	int nBoardChenal=pScreen->GetNumOfTwoScreen();

	int nScreenIndex=(nBoardIndex-1)*4+nBoardChenal;

	//CString szTemp1;
	//szTemp1.Format(_T("%d"),nSignalIndex);

	//CString szTemp2;
	//szTemp2.Format(_T("%d"),nScreenIndex);

	//CString szOrder;
	//szOrder=szTemp1+_T("V")+szTemp2+_T(".");

	//int nLen=szOrder.GetLength();

	//unsigned char* pOrderData=new unsigned char[nLen+1];
	//memset(pOrderData,'\0',nLen+1);

	//int i=0;
	//for(;i<nLen;i++)
	//{
	//	pOrderData[i]=(char)szOrder.GetAt(i);
	//}
	//pOrderData[i]='\0';

	int nLen=2;

	unsigned char pOrderData[2]={0};

	pOrderData[0]=nSignalIndex;
	pOrderData[1]=nScreenIndex;

	//AddSendDataByProtocol(pScreenManage,pOrderData,nLen,ADDRESSTYPE_PANEL,ORDERNUM_OLDORDER,ORDERTYPE_OUTPUT);

	AddSendDataByProtocol(pScreenManage,pOrderData,nLen,ADDRESSTYPE_PANEL,ORDERNUM_CLOSEMATRIX,ORDERTYPE_OUTPUT);
}

BOOL XSendDataScreenManage::GetReScreenResulation(XScreenManage* pScreenManage,XScreen*& pScreen,int& nHdpi,int& nVdpi)
{
	if(NULL==pScreen)
	{
		return FALSE;
	}
	int nIndex=pScreen->GetIndex();
	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		if(nIndex==pScreen->GetIndex())
		{
			if(pScreen->GetReScreenHdpi()!=0
				&&pScreen->GetReScreenVdpi()!=0)
			{
				nHdpi=pScreen->GetReScreenHdpi();
				nVdpi=pScreen->GetReScreenVdpi();
				return TRUE;
			}
			else
			{
				nHdpi=pScreen->GetScreenHdpi();
				nVdpi=pScreen->GetScreenVdpi();
				return TRUE;
			}		
		}
	}
	return FALSE;
}

BOOL XSendDataScreenManage::GetReSignalResulation(XScreenManage* pScreenManage,XSignal*& pSignal,int& nResH,int& nResV)
{
	if(NULL==pSignal)
	{
		return FALSE;
	}

	int nSignalIndex=pSignal->GetInputIndex();

	VEC_INPUTSIGNAL& VecInputSignal=pScreenManage->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
	{
		XInputSignal *pInputSignal=*iter;
		if(nSignalIndex==pInputSignal->GetInputIndex())
		{
			if(pInputSignal->GetReResulationH()!=0
				&&pInputSignal->GetReResulationV()!=0)
			{
				nResH=pInputSignal->GetReResulationH();
				nResV=pInputSignal->GetReResulationV();
				return TRUE;
			}
			else
			{
				nResH=pSignal->GetSignalHdpi();
				nResV=pSignal->GetSignalVdpi();
				return TRUE;
			}
		}
	}
	return FALSE;
}

void XSendDataScreenManage::AddSendDataOfFinash(XScreenManage* pScreenManage)
{
	//TRACE(_T("AddSendDataOfFinash=%d-%s\n"),GetTickCount(),_T("AddSendDataOfFinash"));

	int nDatalen = 1;

	unsigned char data[1]={0};
	data[0]=1;

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_FINISH,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfSignalClose(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen)
{
	m_Index=nScreenIndex-1+128;

	m_nScreenNumOfTwo=nNum-1;

	int nDataLen=5;

	unsigned char Data[5]={0};

	unsigned int nTempID=ID;
	memcpy(Data,&nTempID,4);

	Data[4]=0x00;

	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_TWOOPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::AddSendDataOfDeleteMatrixSignal(XScreenManage* pScreenManage,XScreen* pScreen)
{
	int nBoardIndex=pScreen->GetBoardIndex();

	int nBoardChenal=pScreen->GetNumOfTwoScreen();

	int nScreenIndex=(nBoardIndex-1)*4+nBoardChenal;

	int nLen=2;

	unsigned char pOrderData[2]={0};

	pOrderData[0]=0;
	pOrderData[1]=nScreenIndex;

	AddSendDataByProtocol(pScreenManage,pOrderData,nLen,ADDRESSTYPE_PANEL,ORDERNUM_CLOSEMATRIX,ORDERTYPE_OUTPUT);

	//旧指令
	//int nBoardIndex=pScreen->GetBoardIndex();

	//int nBoardChenal=pScreen->GetNumOfTwoScreen();

	//int nScreenIndex=(nBoardIndex-1)*4+nBoardChenal;

	//CString szOrder=_T("");
	//CString szTemp=_T("V");

	//szOrder.Format(_T("%d%s%d."),0,szTemp,nScreenIndex);

	//int nOldOrderDataLen=szOrder.GetLength();
	//unsigned char* pOldOrderData=new unsigned char[nOldOrderDataLen+1];
	//memset(pOldOrderData,'\0',nOldOrderDataLen+1);

	//int i=0;
	//for(;i<nOldOrderDataLen;i++)
	//{
	//	pOldOrderData[i]=(char)szOrder.GetAt(i);
	//}
	//pOldOrderData[i]='\0';

	//AddSendDataByProtocol(pScreenManage,pOldOrderData,nOldOrderDataLen,ADDRESSTYPE_PANEL,ORDERNUM_OLDORDER,ORDERTYPE_OUTPUT);

	//delete []pOldOrderData;
}

void XSendDataScreenManage::AddSendDataOfDeleteAllSignal(XScreenManage* pScreenManage)
{
	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		int nIndex=pScreen->GetBoardIndex();

		m_Index=nIndex-1+128;

		int ch1,ch2,ch3,ch4;

		ch1=0;ch2=0;ch3=0;ch4=0;

		int nDatalen=4;
		unsigned char data[4]={0};

		data[0]=ch1;
		data[1]=ch2;
		data[2]=ch3;
		data[3]=ch4;

		AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_OPERATOR,ORDERNUM_DELETEALL,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::AddSendDataOfDeleteAllMatrixSignal(XScreenManage* pScreenManage)
{
	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nBoardIndex=pScreen->GetBoardIndex();

		int nBoardChenal=pScreen->GetNumOfTwoScreen();

		int nScreenIndex=(nBoardIndex-1)*4+nBoardChenal;

		int nLen=2;
		unsigned char pOrderData[2]={0};

		pOrderData[0]=0;
		pOrderData[1]=nScreenIndex;

		AddSendDataByProtocol(pScreenManage,pOrderData,nLen,ADDRESSTYPE_PANEL,ORDERNUM_CLOSEMATRIX,ORDERTYPE_OUTPUT);
	}

	//旧协议

	//CString szOrder=_T("all$.");

	//int nOldOrderDataLen=szOrder.GetLength();
	//unsigned char* pOldOrderData=new unsigned char[nOldOrderDataLen+1];
	//memset(pOldOrderData,'\0',nOldOrderDataLen+1);

	//int i=0;
	//for(;i<nOldOrderDataLen;i++)
	//{
	//	pOldOrderData[i]=(char)szOrder.GetAt(i);
	//}
	//pOldOrderData[i]='\0';

	//AddSendDataByProtocol(pScreenManage,pOldOrderData,nOldOrderDataLen,ADDRESSTYPE_PANEL,ORDERNUM_OLDORDER,ORDERTYPE_OUTPUT);

	//delete []pOldOrderData;
}

void XSendDataScreenManage::AddSendDataOfSetSignalTop(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen)
{
	m_Index=nScreenIndex-1+128;
	m_nScreenNumOfTwo=nNum-1;

	int nDataLen=5;

	unsigned char Data[5]={0};

	unsigned int nTempID=ID;
	memcpy(Data,&nTempID,4);
	Data[4]=0x01;

	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_TWOOPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::AddSendDataOfSetSignalBottom(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen)
{
	m_Index=nScreenIndex-1+128;
	m_nScreenNumOfTwo=nNum-1;

	int nDataLen=5;

	unsigned char Data[5]={0};

	unsigned int nTempID=ID;
	memcpy(Data,&nTempID,4);
	Data[4]=0x02;

	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_TWOOPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::AddSendDataOfSetSignalShiftUP(XScreenManage* pScreenManage, int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen)
{
	m_Index=nScreenIndex-1+128;
	m_nScreenNumOfTwo=nNum-1;

	int nDataLen=5;

	unsigned char Data[5]={0};

	unsigned int nTempID=ID;
	memcpy(Data,&nTempID,4);
	Data[4]=0x03;

	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_TWOOPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::AddSendDataOfSetSignalShiftDown(XScreenManage* pScreenManage, int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen)
{
	m_Index=nScreenIndex-1+128;
	m_nScreenNumOfTwo=nNum-1;

	int nDataLen=5;

	unsigned char Data[5]={0};

	unsigned int nTempID=ID;
	memcpy(Data,&nTempID,4);
	Data[4]=0x04;

	if(bIsTwoScreen)
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_TWOOPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
	else
	{
		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_OPERATOR,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::SendDataBySaveScene(XScreenManage* pScreenManage,int nSceneIndex)
{
	int nDataLen=1;

	unsigned char Data[1]={0};
	Data[0]=nSceneIndex;

	AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_BROADCAST,ORDERNUM_SAVESCENE,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::SendDataByOpenScene(XScreenManage* pScreenManage,int nSceneIndex)
{
	int nDataLen=1;

	unsigned char Data[1]={0};
	Data[0]=nSceneIndex;

	AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_BROADCAST,ORDERNUM_OPENSCENE,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfDeleteScene(XScreenManage* pScreenManage,int nSceneIndex)
{
	int nDataLen=1;

	unsigned char Data[1]={0};
	Data[0]=nSceneIndex;

	AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_BROADCAST,ORDERNUM_DELETESCENE,ORDERTYPE_OUTPUT);	
}

void XSendDataScreenManage::SendDataOfSetScreenResualtion(XScreenManage* pScreenManage,XScreen*& pScreen)
{
	int nScreenIndex=pScreen->GetBoardIndex();

	XResulationInfo* pResulationInfo=pScreen->GetResulationInfo();

	m_Index=nScreenIndex-1+128;

	int nDataLen=27;

	unsigned char Data[27]={0};

	Data[0]=pScreen->GetReStatus();

	unsigned short nTempResuH=pResulationInfo->GetResolutionH();
	memcpy(Data+1,&nTempResuH,2);

	unsigned short nTempResuV=pResulationInfo->GetResolutionV();
	memcpy(Data+3,&nTempResuV,2);

	Data[5]=pResulationInfo->GetComboIndex();
	Data[6]=pResulationInfo->GetComboRefresh();

	unsigned short nTempHFProch=pResulationInfo->GetHFPorch();
	memcpy(Data+7,&nTempHFProch,2);

	unsigned short nTempHPxiel=pResulationInfo->GetHpixel();
	memcpy(Data+9,&nTempHPxiel,2);

	unsigned short nTempHBProch=pResulationInfo->GetHBPorch();
	memcpy(Data+11,&nTempHBProch,2);

	unsigned short nTempHSyncTime=pResulationInfo->GetHSyncTime();
	memcpy(Data+13,&nTempHSyncTime,2);

	unsigned short nTempHSyncPolarity=pResulationInfo->GetHSyncPolarity();
	memcpy(Data+15,&nTempHSyncPolarity,2);

	unsigned short nTempVFPorch=pResulationInfo->GetVFPorch();
	memcpy(Data+17,&nTempVFPorch,2);

	unsigned short nTempVPxiel=pResulationInfo->GetVPixel();
	memcpy(Data+19,&nTempVPxiel,2);

	unsigned short nTempVBProch=pResulationInfo->GetVBProch();
	memcpy(Data+21,&nTempVBProch,2);

	unsigned short nTempVSyncTime=pResulationInfo->GetVSyncTime();
	memcpy(Data+23,&nTempVSyncTime,2);

	unsigned short nTempVSyncPolarity=pResulationInfo->GetVSyncPolarity();
	memcpy(Data+25,&nTempVSyncPolarity,2);

	AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_SETOUTPUT,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfResulationFront(XScreenManage* pScreenManage)
{
	//TRACE(_T("AddSendDataOfFinash=%d-%s\n"),GetTickCount(),_T("AddSendDataOfFinash"));

	int nDatalen = 1;

	unsigned char data[1]={0};
	data[0]=0;

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_FINISH,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::SendDataOfSetAllScreenResualtion(XScreenManage* pScreenManage)
{
	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nBoardIndex=pScreen->GetBoardIndex();

		m_Index=nBoardIndex-1+128;

		XResulationInfo* pResulationInfo=pScreen->GetResulationInfo();

		int nDataLen=27;

		unsigned char Data[27]={0};

		Data[0]=0;

		unsigned short nTempResuH=pResulationInfo->GetResolutionH();
		memcpy(Data+1,&nTempResuH,2);

		unsigned short nTempResuV=pResulationInfo->GetResolutionV();
		memcpy(Data+3,&nTempResuV,2);

		Data[5]=pResulationInfo->GetComboIndex();
		Data[6]=pResulationInfo->GetComboRefresh();

		unsigned short nTempHFProch=pResulationInfo->GetHFPorch();
		memcpy(Data+7,&nTempHFProch,2);

		unsigned short nTempHPxiel=pResulationInfo->GetHpixel();
		memcpy(Data+9,&nTempHPxiel,2);

		unsigned short nTempHBProch=pResulationInfo->GetHBPorch();
		memcpy(Data+11,&nTempHBProch,2);

		unsigned short nTempHSyncTime=pResulationInfo->GetHSyncTime();
		memcpy(Data+13,&nTempHSyncTime,2);

		unsigned short nTempHSyncPolarity=pResulationInfo->GetHSyncPolarity();
		memcpy(Data+15,&nTempHSyncPolarity,2);

		unsigned short nTempVFPorch=pResulationInfo->GetVFPorch();
		memcpy(Data+17,&nTempVFPorch,2);

		unsigned short nTempVPxiel=pResulationInfo->GetVPixel();
		memcpy(Data+19,&nTempVPxiel,2);

		unsigned short nTempVBProch=pResulationInfo->GetVBProch();
		memcpy(Data+21,&nTempVBProch,2);

		unsigned short nTempVSyncTime=pResulationInfo->GetVSyncTime();
		memcpy(Data+23,&nTempVSyncTime,2);

		unsigned short nTempVSyncPolarity=pResulationInfo->GetVSyncPolarity();
		memcpy(Data+25,&nTempVSyncPolarity,2);

		AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_SETOUTPUT,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::SendDataOfSetScreenRowResualtion(XScreenManage* pScreenManage)
{
	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nBoardIndex=pScreen->GetBoardIndex();

		m_Index=nBoardIndex-1+128;

		XResulationInfo* pResulationInfo=pScreen->GetResulationInfo();

		int nDataLen=27;

		unsigned char Data[27]={0};

		Data[0]=0;

		unsigned short nTempResuH=pResulationInfo->GetResolutionH();
		memcpy(Data+1,&nTempResuH,2);

		unsigned short nTempResuV=pResulationInfo->GetResolutionV();
		memcpy(Data+3,&nTempResuV,2);

		Data[5]=pResulationInfo->GetComboIndex();
		Data[6]=pResulationInfo->GetComboRefresh();

		unsigned short nTempHFProch=pResulationInfo->GetHFPorch();
		memcpy(Data+7,&nTempHFProch,2);

		unsigned short nTempHPxiel=pResulationInfo->GetHpixel();
		memcpy(Data+9,&nTempHPxiel,2);

		unsigned short nTempHBProch=pResulationInfo->GetHBPorch();
		memcpy(Data+11,&nTempHBProch,2);

		unsigned short nTempHSyncTime=pResulationInfo->GetHSyncTime();
		memcpy(Data+13,&nTempHSyncTime,2);

		unsigned short nTempHSyncPolarity=pResulationInfo->GetHSyncPolarity();
		memcpy(Data+15,&nTempHSyncPolarity,2);

		unsigned short nTempVFPorch=pResulationInfo->GetVFPorch();
		memcpy(Data+17,&nTempVFPorch,2);

		unsigned short nTempVPxiel=pResulationInfo->GetVPixel();
		memcpy(Data+19,&nTempVPxiel,2);

		unsigned short nTempVBProch=pResulationInfo->GetVBProch();
		memcpy(Data+21,&nTempVBProch,2);

		unsigned short nTempVSyncTime=pResulationInfo->GetVSyncTime();
		memcpy(Data+23,&nTempVSyncTime,2);

		unsigned short nTempVSyncPolarity=pResulationInfo->GetVSyncPolarity();
		memcpy(Data+25,&nTempVSyncPolarity,2);

		AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_OPERATOR,ORDERNUM_SETOUTPUT,ORDERTYPE_OUTPUT);
	}
}

void XSendDataScreenManage::SendDataOfScreenMoveData(XScreenManage* pScreenManage,unsigned char* pMutrixData,int nMutrixDataLen)
{
	AddSendDataByProtocol(pScreenManage,pMutrixData,nMutrixDataLen,ADDRESSTYPE_BROADCAST,ORDERNUM_DATATRANS,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::SendDataOfScreenMove(XScreenManage* pScreenManage,XScreen*& pScreen)
{
	TRACE(_T("SendDataOfScreenMove=%d\n"),29);

	XScreenMoveInfo* pInfo=pScreenManage->GetScreenMoveInfo();
	int nType=pInfo->GetType()+1;
	int nScrollTime=pInfo->GetFrequency();
	int nScrollSpeed=pInfo->GetSpeed();
	int nTempScrollSpace=pInfo->GetSpace();
	int nScrollSpace=nTempScrollSpace-1;

	COLORREF color = pInfo->GetColor();
	unsigned char colorR = GetRValue(color);
	unsigned char colorG = GetGValue(color);
	unsigned char colorB = GetBValue(color);

	unsigned char colorCR=0.439*colorR-0.368*colorG-0.071*colorB+128;
	unsigned char colorY=0.257*colorR+0.564*colorG+0.098*colorB+16;
	unsigned char colorCB=-0.148*colorR-0.291*colorG+0.439*colorB+128;

	COLORREF bKcolor = pInfo->GetBkColor();
	unsigned char bKcolorR = GetRValue(bKcolor);
	unsigned char bKcolorG = GetGValue(bKcolor);
	unsigned char bKcolorB = GetBValue(bKcolor);

	unsigned char bKcolorCR=0.439*bKcolorR-0.368*bKcolorG-0.071*bKcolorB+128;
	unsigned char bKcolorY=0.257*bKcolorR+0.564*bKcolorG+0.098*bKcolorB+16;
	unsigned char bKcolorCB=-0.148*bKcolorR-0.291*bKcolorG+0.439*bKcolorB+128;

	int nLong=pInfo->GetLong();
	int nBeginH=pInfo->GetBeginH();
	int nMixtureHeight=pInfo->GetHight();
	//*******************************
	RECTF rectScreen=pScreen->GetRect();

	int nScreenResulationH=0;
	int nScreenResulationV=0;
	if(pScreen->GetReScreenHdpi()!=0
		&&pScreen->GetReScreenVdpi()!=0)
	{
		nScreenResulationH=pScreen->GetReScreenHdpi();
		nScreenResulationV=pScreen->GetReScreenVdpi();
	}
	else
	{
		nScreenResulationH=pScreen->GetScreenHdpi();
		nScreenResulationV=pScreen->GetScreenVdpi();
	}

	//纵向所占屏幕个数
	int nRate=(nBeginH+nMixtureHeight)/nScreenResulationV;
	int nRem=(nBeginH+nMixtureHeight)%nScreenResulationV;
	int nScreenCountV=0;

	if(nRem!=0)
	{
		nScreenCountV=nRate+1;
	}
	else
	{
		nScreenCountV=nRate;
	}

	//显示区域
	RECTF rectInfo=pInfo->GetInfoRect();

	//内容区域
	RECTF rectArea=pInfo->GetAreaRect();

	float nX=1.0*rectInfo.X*rectScreen.Width/nScreenResulationH;
	float nY=1.0*rectInfo.Y*rectScreen.Height/nScreenResulationV;
	float nWidth=1.0*rectInfo.Width*rectScreen.Width/nScreenResulationH;
	float nHeight=1.0*rectInfo.Height*rectScreen.Height/nScreenResulationV;

	RECTF rectReal(nX,nY,nWidth,nHeight);

	//计算屏幕序号
	int nBeginCountH=pInfo->GetComboBeginX();
	int nBeginCountV=pInfo->GetComboBeginY();
	int nWidthH=pInfo->GetComboWidth();
	int nLongH=pInfo->GetComboLong();

	VEC_SCREEN VecScreen;
	VEC_SCREEN& VecScr=pScreenManage->GetVecScreen();
	for(VEC_SCREEN::iterator iter=VecScr.begin();iter!=VecScr.end();++iter)
	{
		XScreen* pScreen=*iter;
		RECTF rectF=pScreen->GetRect();

		if(rectF.Intersect(rectReal))
		{
			VecScreen.push_back(pScreen);
		}
	}
		
	//执行次数（按屏幕顺序）
	int nPos=0;
	//数组来保存上一行的高度
	unsigned int* pCountV=new unsigned int[nScreenCountV];
	for(int i=0;i<nScreenCountV;i++)
	{
		pCountV[i]=0;
	}

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		nPos+=1;

		XScreen* pScreen=*iter;
		RECTF rectScreen=pScreen->GetRect();

		int nIndex=pScreen->GetBoardIndex();
		m_Index=nIndex-1+128;

		RECTF rect;
		RECTF::Intersect(rect,rectReal,rectScreen);

		float nBeginX=1.0*rect.X*nScreenResulationH/rectScreen.Width;
		float nBeginY=1.0*rect.Y*nScreenResulationV/rectScreen.Height;
		float nBeginWidth=1.0*rect.Width*nScreenResulationH/rectScreen.Width;
		float nBeginHeight=1.0*rect.Height*nScreenResulationV/rectScreen.Height;

		//起始地址
		unsigned int nX1=XCalculateScreenManage::GetIntFromFloat(nBeginX);
		unsigned int nY1=XCalculateScreenManage::GetIntFromFloat(nBeginY);
		unsigned int nW=XCalculateScreenManage::GetIntFromFloat(nBeginWidth);
		unsigned int nH=XCalculateScreenManage::GetIntFromFloat(nBeginHeight);

		//显示范围
		//每块屏幕的左右坐标（左上角（0，0）
		float nTempBeginX=rect.X-rectScreen.X;
		float nTempBeginY=rect.Y-rectScreen.Y;
		float nBeginShowX=1.0*nTempBeginX*nScreenResulationH/rectScreen.Width;
		float nBeginShowY=1.0*nTempBeginY*nScreenResulationV/rectScreen.Height;

		unsigned int nShowX1=XCalculateScreenManage::GetIntFromFloat(nBeginShowX);
		unsigned int nShowY1=XCalculateScreenManage::GetIntFromFloat(nBeginShowY);
		unsigned int nShowX2=nShowX1+nW-1;
		unsigned int nShowY2=nShowY1+nH-1;

		int nDataLen=29;
		unsigned char Data[29]={0};

		Data[0]=nScrollSpeed;
		Data[1]=nScrollSpace;

		Data[2]=colorCB;
		Data[3]=colorY;
		Data[4]=colorCR;

		Data[5]=bKcolorCB;
		Data[6]=bKcolorY;
		Data[7]=bKcolorCR;

		int nInfoWidth=rectArea.Width/8;
		memcpy(Data+8,&nInfoWidth,2);

		int nInfoHight=rectArea.Height;
		memcpy(Data+10,&nInfoHight,2);

		Data[12]=nType;

		//内容结束地址
		int n=(nPos-1)/nLongH;
		
		//上一行高度
		pCountV[n]=nH;

		unsigned int nEndPos=0;
		if(n<nScreenCountV)
		{
			if(n==0)
			{
				nEndPos=nX1+(nWidthH-(nPos-1))*nScreenResulationH;
			}
			else
			{
				nEndPos=(nX1+(nWidthH-((nPos-n*nLongH)-1))*nScreenResulationH)*pCountV[n-1];
			}	
		}

		//内容起始利用结束来计算
		int nTempX1=(nEndPos-(nWidthH-((nPos-n*nLongH)-1))*nScreenResulationH)/8;  
		memcpy(Data+13,&nTempX1,4); 

		//TRACE(_T("nTempX1=%d\n"),nTempX1);

		unsigned int nTempEndPos=(nEndPos-1)/8;
		memcpy(Data+17,&nTempEndPos,4);

		//TRACE(_T("nTempEndPos=%d\n"),nTempEndPos);

		//显示范围
		memcpy(Data+21,&nShowX1,2);
		memcpy(Data+23,&nShowX2,2);
		memcpy(Data+25,&nShowY1,2);
		memcpy(Data+27,&nShowY2,2);

		AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_OUTPUT,ORDERNUM_SCREENMOVE,ORDERTYPE_OUTPUT);
	}
	delete []pCountV;
}

void XSendDataScreenManage::SendDataByTimedPolling(XScreenManage* pScreenManage)
{
	XTimedPollingInfo* pPollingInfo=pScreenManage->GetTimedPollingInfo();

	int nTimeInput=pPollingInfo->GetTimedPolling();
	int nTimeOutPut=nTimeInput*4;

	int nDataLen=4;
	unsigned char Data[4]={0};

	memcpy(Data,&nTimeInput,2);
	memcpy(Data+2,&nTimeOutPut,2);

	AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_PANEL,ORDERNUM_TIMEDPOLLING,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::SendDataOfScreenMoveAsk(XScreenManage* pScreenManage)
{
	DWORD dwNowTime=GetTickCount();

	//TRACE("dwNowTime=%d\n",dwNowTime);

	int nDataLen=4;
	unsigned char Data[4]={0};

	memcpy(Data,&dwNowTime,4);

	AddSendDataByProtocol(pScreenManage,Data,nDataLen,ADDRESSTYPE_PANEL,ORDERNUM_SCREENMOVEASK,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfGetSceneIndex(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage, NULL, 0,ADDRESSTYPE_PANEL,ORDERNUM_SCENEINDEX,OEDERTYPE_SCENE);	
}

void XSendDataScreenManage::SendDataByRunOldOrder(XScreenManage* pScreenManage)
{
	XOldOrderInfo* pInfo=pScreenManage->GetOldOrderInfo();

	CString szOldOrderText=pInfo->GetText();
	int nOldOrderDataLen=pInfo->GetDataLen();
	unsigned char* pOldOrderData=new unsigned char[nOldOrderDataLen+1];
	memset(pOldOrderData,'\0',nOldOrderDataLen+1);

	int i=0;
	for(;i<nOldOrderDataLen;i++)
	{
		pOldOrderData[i]=(char)szOldOrderText.GetAt(i);
	}
	pOldOrderData[i]='\0';

	AddSendDataByProtocol(pScreenManage,pOldOrderData,nOldOrderDataLen,ADDRESSTYPE_PANEL,ORDERNUM_OLDORDER,ORDERTYPE_OUTPUT);
	
	delete []pOldOrderData;
}

void XSendDataScreenManage::SendDataByDeviceStatus(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage, NULL, 0,ADDRESSTYPE_PANEL,ORDERNUM_DEVICESTATUS,ORDERTYPE_DEVICESTATUS);	
}

void XSendDataScreenManage::AddSendDataOfScreenMoveOff(XScreenManage* pScreenManage)
{
	TRACE(_T("AddSendDataOfScreenMoveOff=%d\n"),12);

	int nDatalen = 1;

	unsigned char data[1]={0};
	data[0]=0x12;

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_FINISH,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfScreenMoveZero(XScreenManage* pScreenManage)
{
	TRACE(_T("AddSendDataOfScreenMoveZero=%d\n"),0);

	int nDatalen = 13;

	unsigned char data[13]={0};
	for(int i=0;i<13;i++)
	{
		data[i]=0;
	}

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_SCREENMOVE,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfScreenMoveOn(XScreenManage* pScreenManage)
{
	TRACE(_T("AddSendDataOfScreenMoveOn=%d\n"),13);

	int nDatalen = 1;

	unsigned char data[1]={0};
	data[0]=0x13;

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_FINISH,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfChangeMoveParamater(XScreenManage* pScreenManage)
{
	XScreenMoveInfo* pChangeInfo=pScreenManage->GetScreenMoveInfo();

	COLORREF color = pChangeInfo->GetColor();
	unsigned char colorR = GetRValue(color);
	unsigned char colorG = GetGValue(color);
	unsigned char colorB = GetBValue(color);

	unsigned char colorCR=0.439*colorR-0.368*colorG-0.071*colorB+128;
	unsigned char colorY=0.257*colorR+0.564*colorG+0.098*colorB+16;
	unsigned char colorCB=-0.148*colorR-0.291*colorG+0.439*colorB+128;

	COLORREF bKcolor = pChangeInfo->GetBkColor();
	unsigned char bKcolorR = GetRValue(bKcolor);
	unsigned char bKcolorG = GetGValue(bKcolor);
	unsigned char bKcolorB = GetBValue(bKcolor);

	unsigned char bKcolorCR=0.439*bKcolorR-0.368*bKcolorG-0.071*bKcolorB+128;
	unsigned char bKcolorY=0.257*bKcolorR+0.564*bKcolorG+0.098*bKcolorB+16;
	unsigned char bKcolorCB=-0.148*bKcolorR-0.291*bKcolorG+0.439*bKcolorB+128;

	int nSpeed=pChangeInfo->GetSpeed();

	int nSpace=pChangeInfo->GetSpace();

	int nDatalen=8;

	unsigned char data[8]={0};

	data[0]=nSpeed;
	data[1]=nSpace;
	
	data[2]=colorCB;
	data[3]=colorY;
	data[4]=colorCR;

	data[5]=bKcolorCB;
	data[6]=bKcolorY;
	data[7]=bKcolorCR;

	AddSendDataByProtocol(pScreenManage,data,nDatalen,ADDRESSTYPE_BROADCAST,ORDERNUM_SCREENMOVE,ORDERTYPE_OUTPUT);
}

void XSendDataScreenManage::AddSendDataOfGetSignalNum(XScreenManage* pScreenManage)
{
	AddSendDataByProtocol(pScreenManage, NULL, 0,ADDRESSTYPE_PANEL,ORDERNUM_GETSIGNALNUM,ORDERTYPE_SIGNALNUM);
}

void XSendDataScreenManage::SendDataOfSetMatrixScreenResualtion(XScreenManage* pScreenManage,XScreen* pScreen)
{
	int nBoardIndex=pScreen->GetBoardIndex();

	int nChenal=pScreen->GetNumOfTwoScreen();

	m_Index2=nBoardIndex-1+128;

	m_Chenal2=nChenal-1;

	//////////////////////////////////////////////////////////////////////////
	XResulationInfo* pResulationInfo=pScreen->GetResulationInfo();

	int nModel=pResulationInfo->GetComboModel();

	switch(nModel)
	{
	case 0:
	case 1:
		{
			int nDataLen=20;
			unsigned char Data[20]={0};

			Data[0]=nModel;

			unsigned short nTempHFProch=pResulationInfo->GetHFPorch();
			memcpy(Data+1,&nTempHFProch,2);

			unsigned short nTempHPxiel=pResulationInfo->GetHpixel();
			memcpy(Data+3,&nTempHPxiel,2);

			unsigned short nTempHBProch=pResulationInfo->GetHBPorch();
			memcpy(Data+5,&nTempHBProch,2);

			unsigned short nTempHSyncTime=pResulationInfo->GetHSyncTime();
			memcpy(Data+7,&nTempHSyncTime,2);


			int nHSyncPolarity=pResulationInfo->GetHSyncPolarity();
			Data[9]=nHSyncPolarity;

			unsigned short nTempVFPorch=pResulationInfo->GetVFPorch();
			memcpy(Data+10,&nTempVFPorch,2);

			unsigned short nTempVPxiel=pResulationInfo->GetVPixel();
			memcpy(Data+12,&nTempVPxiel,2);

			unsigned short nTempVBProch=pResulationInfo->GetVBProch();
			memcpy(Data+14,&nTempVBProch,2);

			unsigned short nTempVSyncTime=pResulationInfo->GetVSyncTime();
			memcpy(Data+16,&nTempVSyncTime,2);

			int nVSyncPolarity=pResulationInfo->GetVSyncPolarity();
			Data[18]=nVSyncPolarity;

			Data[19]=pResulationInfo->GetRefreash();

			AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_INPUT,ORDERNUM_MATRIXRESULATION,ORDERTYPE_OUTPUT);
		}
		break;
	case 2:
		{
			int nDataLen=1;

			unsigned char Data[1]={0};

			int nResulationIndex=pResulationInfo->GetComboIndex();

			int nRefreash=pResulationInfo->GetComboRefresh();

			Data[0]=(nResulationIndex<<2)|nRefreash;

			AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_INPUT,ORDERNUM_MATRIXRESULATION,ORDERTYPE_OUTPUT);
		}
		break;
	default:
		break;
	}
}

void XSendDataScreenManage::SendDataOfSetMatrixAllScreenResualtion(XScreenManage* pScreenManage)
{
	XAllResulationInfo* pResulationInfo=pScreenManage->GetAllResulationInfo();

	int nModel=pResulationInfo->GetComboModel();

	VEC_SCREEN& VecScreen=pScreenManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nBoardIndex=pScreen->GetBoardIndex();

		int nChenal=pScreen->GetNumOfTwoScreen();

		m_Index2=nBoardIndex-1+128;

		m_Chenal2=nChenal-1;
		//////////////////////////////////////////////////////////////////////////

		switch(nModel)
		{
		case 0:
		case 1:
			{
				int nDataLen=20;
				unsigned char Data[20]={0};

				Data[0]=nModel;

				unsigned short nTempHFProch=pResulationInfo->GetHFPorch();
				memcpy(Data+1,&nTempHFProch,2);

				unsigned short nTempHPxiel=pResulationInfo->GetHpixel();
				memcpy(Data+3,&nTempHPxiel,2);

				unsigned short nTempHBProch=pResulationInfo->GetHBPorch();
				memcpy(Data+5,&nTempHBProch,2);

				unsigned short nTempHSyncTime=pResulationInfo->GetHSyncTime();
				memcpy(Data+7,&nTempHSyncTime,2);

				Data[9]=pResulationInfo->GetHSyncPolarity();

				unsigned short nTempVFPorch=pResulationInfo->GetVFPorch();
				memcpy(Data+10,&nTempVFPorch,2);

				unsigned short nTempVPxiel=pResulationInfo->GetVPixel();
				memcpy(Data+12,&nTempVPxiel,2);

				unsigned short nTempVBProch=pResulationInfo->GetVBProch();
				memcpy(Data+14,&nTempVBProch,2);

				unsigned short nTempVSyncTime=pResulationInfo->GetVSyncTime();
				memcpy(Data+16,&nTempVSyncTime,2);

				Data[18]=pResulationInfo->GetVSyncPolarity();

				Data[19]=pResulationInfo->GetRefreash();

				AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_INPUT,ORDERNUM_MATRIXRESULATION,ORDERTYPE_OUTPUT);
			}
			break;
		case 2:
			{
				int nDataLen=1;

				unsigned char Data[1]={0};

				int nResulationIndex=pResulationInfo->GetComboIndex();

				int nRefreash=pResulationInfo->GetComboRefresh();

				Data[0]=(nResulationIndex<<2)|nRefreash;

				AddSendDataByProtocol(pScreenManage, Data, nDataLen,ADDRESSTYPE_INPUT,ORDERNUM_MATRIXRESULATION,ORDERTYPE_OUTPUT);
			}
			break;
		default:
			break;
		}
	}
}

void XSendDataScreenManage::AddSendDataOfGetMatrix(XScreenManage* pScreenManage)
{
	int nDatalen=0;

	unsigned char *data=new unsigned char[nDatalen];

	AddSendDataByProtocol(pScreenManage, data, nDatalen,ADDRESSTYPE_PANEL,ORDERNUM_GETMTRIXPARA,ORDERTYPE_MATRIXWINDOWS);

	delete []data;
}