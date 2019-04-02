#include "StdAfx.h"
#include "XDataManage.h"
#include "XDelegateDataManage.h"
#include "XScreenManage.h"
#include "XSendDataScreenManage.h"


XDataManage::XDataManage(void)
{
	m_pDelegate = NULL;

	m_TemperatureTime = 0;

	m_szTemperature = _T("");
}

XDataManage::~XDataManage(void)
{
	
}

void XDataManage::SetDelegate(XDelegateDataManage* p)
{
	m_pDelegate = p;
}

void XDataManage::Init()
{
	
}

void XDataManage::CheckTemperature()
{
	if (_T("") == m_szTemperature)
	{
		return;
	}

	DWORD now = GetTickCount();

	if ((now - m_TemperatureTime) > 3000)
	{
		m_szTemperature = _T("");

		m_pDelegate->Operate(OPERATETYPE_SETTEMPERATURE, &m_szTemperature);
	}
}

void XDataManage::ResetTemperature()
{
	if (_T("") == m_szTemperature)
	{
		return;
	}

	m_szTemperature = _T("");

	m_pDelegate->Operate(OPERATETYPE_SETTEMPERATURE, &m_szTemperature);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BOOL XDataManage::HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr)
{
	//输入信号参数信息
	DecodeInput(pData,nDataLen);

	DecodeOutput(pData,nDataLen);

	DecodeWindowParamater(pData,nDataLen);

	DecodeAsk(pData,nDataLen);

	DecodeSceneIndex(pData,nDataLen);

	DecodeDeviceStatus(pData,nDataLen);

	DecodeSignalNum(pData,nDataLen);

	DecodePaneIP(pData,nDataLen);

	DecodeStreamAddr(pData,nDataLen);

	DecodeBitRate(pData,nDataLen);

	DecodeMatrixWindowParamater(pData,nDataLen);

	return TRUE;
}

void XDataManage::DecodeInput(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE))
		{
			if((pData[i+3]==0xEE)
				&&(pData[i+4]==0x00)
				&&(pData[i+5]==0x8D)
				&&(pData[i+6]==0x00)
				&&(pData[i+7]==0x00))
			{
				int nLen=38;
				unsigned char Data[38]={0};

				for(int j=0;j<8;j++)
				{
					Data[j]=pData[j+i];
				}

				for(int k=8;k<36;k++)
				{
					Data[k]=0;
				}

				Data[36]=pData[i+8];
				Data[37]=pData[i+9];

				m_pDelegate->Operate(OPERATETYPE_SETSIGNALPARAMATER,Data);
			}
			else if((pData[i+3]==0xEE)
				&&(pData[i+4]==0x00)
				&&(pData[i+5]==0x8D)
				&&(pData[i+6]==0x1C)
				&&(pData[i+7]==0x00))
			{
				int nLen=38;
				unsigned char Data[38]={0};

				for(int j=0;j<38;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_SETSIGNALPARAMATER,Data);
			}
		}
	}
}

void XDataManage::DecodeOutput(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)&&(pData[i+1]==0xFE))
		{
			if((pData[i+3]==0xEE)
				&&(pData[i+4]==0x00)
				&&(pData[i+5]==0x8E)
				&&(pData[i+6]==0x00)
				&&(pData[i+7]==0x00))
			{
				int nLen=17;
				unsigned char *Data=new unsigned char[nLen];

				Data[0]=pData[i];

				for(int j=1;j<8;j++)
				{
					Data[j]=pData[j+i];
				}

				Data[8]=0;
				Data[9]=0;
				Data[10]=0;
				Data[11]=0;
				Data[12]=0;
				Data[13]=0;
				Data[14]=0;
				Data[15]=pData[i+8];
				Data[16]=pData[i+9];

				m_pDelegate->Operate(OPERATETYPE_SETSCREENPARAMATER,Data);
				delete []Data;
			}
			else if((pData[i+3]==0xEE)
				&&(pData[i+4]==0x00)
				&&(pData[i+5]==0x8E)
				&&(pData[i+6]==0x07)
				&&(pData[i+7]==0x00))
			{
				int nLen=17;
				unsigned char *Data=new unsigned char[nLen];

				for(int j=0;j<17;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_SETSCREENPARAMATER,Data);
				delete []Data;
			}
			else if((pData[i+3]==0xEE)
				&&(pData[i+4]==0x00)
				&&(pData[i+5]==0x8E)
				&&(pData[i+6]==0x19)
				&&(pData[i+7]==0x00))
			{
				int nLen=35;
				unsigned char *Data=new unsigned char[nLen];

				for(int j=0;j<35;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_SETSCREENPARAMATEROFMATRIX,Data);
				delete []Data;
			}
		}
	}
}

void XDataManage::DecodeWindowParamater(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)&&(pData[i+1]==0xFE))
		{
			if((pData[i+4]==0x00)
				&&(pData[i+5]==0x94)
				&&(pData[i+6]==0x88)
				&&(pData[i+7]==0x00))
			{
				int nLen=146;
				unsigned char Data[146]={0};

				for(int j=0;j<146;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_SETWINDOWPARAMATER,(char*)Data);
			}
			else if(pData[i+4]==0x00
				&&pData[i+5]==0x94
				&&pData[i+6]==0x44
				&&pData[i+7]==0x00)
			{
				int nLen=146;
				unsigned char Data[146]={0};

				for(int j=0;j<76;j++)
				{
					Data[j]=pData[j+i];
				}

				for(int i=76;i<144;i++)
				{
					Data[i]=0;
				}

				Data[144]=pData[76];
				Data[145]=pData[77];

				m_pDelegate->Operate(OPERATETYPE_SETWINDOWPARAMATER,(char*)Data);
			}
		}
	}
}

void XDataManage::DecodeAsk(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+2]==0xEE)
			&&(pData[i+3]==0xEE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0x18)
			&&(pData[i+6]==0x04)
			&&(pData[i+7]==0x00))
		{
			int nLen=14;
			unsigned char Data[14]={0};

			for(int j=0;j<14;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_GETSCREENMOVEASK,(char*)Data);
		}
	}
}

void XDataManage::DecodeSceneIndex(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+2]==0xEE)
			&&(pData[i+3]==0xEE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0x9C)
			&&(pData[i+6]==0x04)
			&&(pData[i+7]==0x00))
		{

			int nLen=14;
			unsigned char Data[14]={0};

			for(int j=0;j<14;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_SETSCENEINDEX,(char*)Data);
			m_pDelegate->Operate(OPERATETYPE_SETSCENEINDEX1,(char*)Data);
		}
	}
}

void XDataManage::DecodeDeviceStatus(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+2]==0xEE)
			&&(pData[i+3]==0xEE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0x9F)
			&&(pData[i+6]==0x04)
			&&(pData[i+7]==0x00))
		{
			int nLen=14;
			unsigned char Data[14]={0};

			for(int j=0;j<14;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_SETDEVICESTATUS,(char*)Data);
		}
	}
}

void XDataManage::DecodeSignalNum(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+2]==0xEE)
			&&(pData[i+3]==0xEE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0xA3))
		{
			int nLen=nDataLen;
			unsigned char* Data=new unsigned char[nLen];

			for(int j=0;j<nLen;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_SETINPUTNUM,(char*)Data);
			delete []Data;
		}
	}
}

//输入和输出有区别吗
void XDataManage::DecodePaneIP(unsigned char* pData,int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0x92)
			&&(pData[i+7]==0x00))
		{
			int n=pData[2];

			if(n>=128)
			{
				int nLen=63+8;
				unsigned char Data[63+8]={0};

				for(int j=0;j<63+8;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_GETPREVIEWNET,(char*)Data);
			}
			else
			{
				int nLen=63;
				unsigned char Data[63]={0};

				for(int j=0;j<63;j++)
				{
					Data[j]=pData[j+i];
				}

				m_pDelegate->Operate(OPERATETYPE_GETPANEIPADDR,(char*)Data);
			}
		}
	}
}

void XDataManage::DecodeStreamAddr(unsigned char* pData,int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0x93)
			&&(pData[i+6]==0x80)
			&&(pData[i+7]==0x00))
		{
			int nLen=138;
			unsigned char Data[138]={0};

			for(int j=0;j<138;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_GETSTREAMADDR,(char*)Data);
		}
	}
}

void XDataManage::DecodeBitRate(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+4]==0x00)
			&&(pData[i+5]==0xA2)
			&&(pData[i+6]==0x18)
			&&(pData[i+7]==0x00))
		{
			int nLen=34;
			unsigned char Data[34]={0};

			for(int j=0;j<34;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_GETBITRATE,(char*)Data);
		}
	}
}

void XDataManage::DecodeMatrixWindowParamater(unsigned char* pData, int nDataLen)
{
	for(int i=0;i<nDataLen;i++)
	{
		if((pData[i]==0xFF)
			&&(pData[i+1]==0xFE)
			&&(pData[i+5]==0xA4))
		{
			//TRACE(_T("nDataLen=%d\n"),nDataLen);

			int nLen=nDataLen;
			unsigned char* Data=new unsigned char[nLen];

			for(int j=0;j<nLen;j++)
			{
				Data[j]=pData[j+i];
			}

			m_pDelegate->Operate(OPERATETYPE_GETMATRIXOUTPUT,(char*)Data);
			delete []Data;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void XDataManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_RESETTEMPERATURE:
		{
			ResetTemperature();
		}
		break;
	default:
		break;
	}
}
