#include "stdafx.h"
#include "XSendDataManage.h"
#include "XDelegateSendDataManage.h"
#include "XJsonManage.h"

XSendDataManage* XSendDataManage::m_pSendDataManage=NULL;
XSendDataManage::XSendDataManage()
	:m_pDelegate(NULL),
	m_nTotalPacket(0),
	m_nCurPacket(0),
	m_nPacketLen(0)
{

}

XSendDataManage::~XSendDataManage()
{
	//TRACE(_T("~XSendDataManage\n"));
}

void XSendDataManage::SetDelegate(XDelegateSendDataManage* p)
{
	m_pDelegate=p;
}

XSendDataManage* XSendDataManage::GetInstance()
{
	if(NULL==m_pSendDataManage)
	{
		m_pSendDataManage=new XSendDataManage;
	}

	return m_pSendDataManage;
}

void XSendDataManage::Release()
{
	if(NULL!=m_pSendDataManage)
	{
		delete m_pSendDataManage;
		m_pSendDataManage=NULL;
	}
}

BOOL XSendDataManage::SendData(char* pData, int nDataLen)
{
	return m_pDelegate->SendData(pData,nDataLen);
}

//////////////////////////////////////////////////////////////////////////
void XSendDataManage::AddFullSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,PROTOCOLTYPE ProtocolType)
{
	int nLen=nSrcDataLen+8;
	unsigned char* pData=new unsigned char[nLen];
	memset(pData,0,nLen);

	//包头
	pData[0]=0xFF;
	pData[1]=0x00;	

	//包长
	int nPackLen=nSrcDataLen+2;
	memcpy(pData+2,&nPackLen,2);

	//协议号
	switch(ProtocolType)
	{
	case PROTOCOLTYPE_USERLIST:
		{
			pData[4]=0x00;
			pData[5]=0x07;
		}
		break;
	case PROTOCOLTYPE_LOGIN:
		{
			pData[4]=0x01;
			pData[5]=0x07;
		}
		break;
	case PACKERHEAD_HEART:
		{
			pData[4]=0x04;
			pData[5]=0x07;
		}
		break;
	case PROTOCOLTYPE_LOGINOUT:
		{
			pData[4]=0x05;
			pData[5]=0x07;
		}
		break;
	default:
		break;
	}

	if(NULL!=pSrcData)
	{
		memcpy(pData+6,pSrcData,nSrcDataLen);

		unsigned char* pTemp=pData;
		unsigned short nSum=CheckSum(pTemp+4,nSrcDataLen+4);
		memcpy(pData+6+nSrcDataLen,&nSum,2);
	}
	else
	{
		unsigned short nSum=CheckSum(pData,4);
		memcpy(pData,&nSum,2);
	}

	SendData((char*)pData,nLen);
	//////////////////////////////////////////////////////////////////////////
	CString szTemp=_T("");
	CString szStr=_T("");
	for (int i=0;i<nLen;i++)
	{
		szTemp.Format(_T("%02X "),pData[i]);
		szStr+=szTemp;
	}

	TRACE(_T("STR=%s\n"),szStr);
	//////////////////////////////////////////////////////////////////////////
	delete pData;
}

unsigned short XSendDataManage::CheckSum(unsigned char* pData,int nLen)
{
	unsigned short nSum=0;
	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
	}
	return nSum;
}

void XSendDataManage::AddData(CString szData,PROTOCOLTYPE nType)
{
	USES_CONVERSION;
	char* pData=W2A(szData);
	int nDataLen=strlen(pData)+1;

	int nTempLen=0;
	if(nDataLen%2!=0)
		nTempLen=nDataLen+1;
	else
		nTempLen=nDataLen;

	unsigned char* pTemp=new unsigned char[nTempLen];
	memset(pTemp,0,nTempLen);
	memcpy(pTemp,pData,nDataLen);

	AddFullSendDataByProtocol(pTemp,nTempLen,nType);
	delete pTemp;
}

void XSendDataManage::SendDataOfHeart(DWORD dHeartTime)
{
	int nLen=4;
	unsigned char pData[4]={0};

	memcpy(pData,&dHeartTime,4);

	AddFullSendDataByProtocol(pData,nLen,PACKERHEAD_HEART);
}

void XSendDataManage::AddSendDataOfLogin(CString szUserName,CString szPassWd)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToLogin(szUserName,szPassWd,szData);

	AddData(szData,PROTOCOLTYPE_LOGIN);
}

void XSendDataManage::AddSendDataOfLoginOut(CString szUserName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToLoginOut(szUserName,szData);

	AddData(szData,PROTOCOLTYPE_LOGINOUT);
}

void XSendDataManage::SendDataOfAddUser()
{

}

