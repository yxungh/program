#include "StdAfx.h"
#include "XReciveDataManage.h"
#include "XDelegateReciveDataManage.h"


XReciveDataManage::XReciveDataManage(void)
{
	m_pDelegate = NULL;
}

XReciveDataManage::~XReciveDataManage(void)
{
	
}

void XReciveDataManage::SetDelegate(XDelegateReciveDataManage* p)
{
	m_pDelegate = p;
}

void XReciveDataManage::Init()
{
	
}

//////////////////////////////////////////////////////////////////////////
BOOL XReciveDataManage::HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr)
{
	DecodeLogin(pData,nDataLen);

	DecodeHeart(pData,nDataLen);

	DecodeLoginOut(pData,nDataLen);
	
	return TRUE;
}

void XReciveDataManage::DecodeLogin(unsigned char* pData,int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if(pData[i]==0xFF&&
			pData[1+i]==0x00&&
			pData[4+i]==0x01&&
			pData[5+i]==0x07)
		{

			CString szTemp=_T("");
			CString szStr=_T("");
			for (int i=0;i<nDataLen;i++)
			{
				szTemp.Format(_T("%02X "),pData[i]);
				szStr+=szTemp;
			}

			TRACE(_T("Re=%s\n"),szStr);


			int nLen=nDataLen-8;

			unsigned char* pTemp=new unsigned char[nLen];
			memset(pTemp,0,nLen);

			memcpy(pTemp,pData+6,nLen);
			m_pDelegate->Operate(OPERATETYPE_LOGIN,(char*)pTemp);

			delete pTemp;
		}
	}
}

void XReciveDataManage::DecodeHeart(unsigned char* pData,int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if(pData[i]==0xFF&&
			pData[1+i]==0x00&&
			pData[4+i]==0x04&&
			pData[5+i]==0x07)
		{
			int nLen=nDataLen-8;

			unsigned char* pTemp=new unsigned char[nLen];
			memset(pTemp,0,nLen);

			memcpy(pTemp,pData+6,nLen);
			m_pDelegate->Operate(OPERATETYPE_HEART,(char*)pTemp);

			delete pTemp;	
		}
	}
}

void XReciveDataManage::DecodeLoginOut(unsigned char* pData,int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if(pData[i]==0xFF&&
			pData[1+i]==0x00&&
			pData[4+i]==0x05&&
			pData[5+i]==0x07)
		{
			int nLen=nDataLen-8;

			unsigned char* pTemp=new unsigned char[nLen];
			memset(pTemp,0,nLen);

			memcpy(pTemp,pData+6,nLen);
			m_pDelegate->Operate(OPERATETYPE_LOGINOUT,(char*)pTemp);

			delete pTemp;	
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void XReciveDataManage::Operate(OPERATETYPE type, void* pData)
{
	//switch(type)
	//{
	//case OPERATETYPE_RESETTEMPERATURE:
	//	{
	//		ResetTemperature();
	//	}
	//	break;
	//default:
	//	break;
	//}
}
