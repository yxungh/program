#include "StdAfx.h"
#include "XScreen.h"
#include "XSignal.h"
#include "XScreenManage.h"
#include "XCalculateScreenManage.h"
#include "XSendDataScreenManage.h"
#include "XMultiVideoWindowFrame.h"
#include "XMultiVideoWindow.h"
#include "XDelegateScreenManage.h"


XScreen::XScreen(void)
{
	m_nIndex = 0;

	m_nBoardIndex=0;

	m_pManage = NULL;

	m_Hdpi=1920;

	m_Vdpi=1080;

	m_ScreenIndex=0;

	m_ReDataLen=0;

	m_ReStatus=0;

	m_ReScreenHdpi=0;

	m_ReScreenVdpi=0;

	m_ReDpiIndex=0;

	m_ReRefresh=0;

	m_nAddSignalNum=0;

	m_nMaxSignalNum=4;

	m_bIsTwoSignal=FALSE;

	m_nNumOfTwoScreen=0;

	m_bIsPreview=FALSE;

	m_bIsHasSignalOfMatrix=FALSE;

	m_nScreenType=0;

	m_szScreenName=_T("");

	m_bIsRight=FALSE;

	m_bIsBottom=FALSE;

	m_nCol=0;

	m_nRow=0;
}

XScreen::~XScreen(void)
{
	ClearVecSignal();
}

void XScreen::ClearVecSignal()
{
	for (VEC_SIGNAL::iterator iter = m_VecSignal.begin(); iter != m_VecSignal.end(); iter++)
	{
		delete *iter;
	}

	m_VecSignal.clear();
}

void XScreen::SetManage(XScreenManage* p)
{
	m_pManage = p;
}

XScreenManage* XScreen::GetManage()
{
	return m_pManage;
}

XResulationInfo* XScreen::GetResulationInfo()
{
	return &m_ResulationInfo;
}

XAllResulationInfo* XScreen::GetAllResulationInfo()
{
	return &m_AllResulationInfo;
}

VEC_SIGNAL& XScreen::GetVecSignal()
{
	return m_VecSignal;
}

int XScreen::GetIndex()
{
	return m_nIndex;
}

void XScreen::SetIndex(int n)
{
	m_nIndex=n;
}

RECTF XScreen::GetRect()
{
	return m_Rect;
}

void XScreen::SetRect(RECTF r)
{
	m_Rect = r;
}

void XScreen::SetReScreenIndex(int n)
{
	m_ScreenIndex=n;
}

int XScreen::GetReScreenIndex()
{
	return m_ScreenIndex;
}

int XScreen::GetScreenHdpi()
{
	return m_Hdpi;
}

int XScreen::GetScreenVdpi()
{
	return m_Vdpi;
}

void XScreen::SetScreenHdpi(int n)
{
	m_Hdpi=n;
}

void XScreen::SetScreenVdpi(int n)
{
	m_Vdpi=n;
}

void XScreen::SetAddSignalNumInScreen(int n)
{
	m_nAddSignalNum=n;
}

int XScreen::GetAddSignalNumInScreen()
{
	return m_nAddSignalNum;
}

void XScreen::SetMaxSignalNumInScreen(int n)
{
	m_nMaxSignalNum=n;
}

int XScreen::GetMaxSignalNumInScreen()
{
	return m_nMaxSignalNum;
}

void XScreen::ResetMaxSignalInScreen()
{
	if(m_bIsTwoSignal)
	{
		m_nMaxSignalNum=2;
	}
	else
	{
		m_nMaxSignalNum=4;
	}
}

void XScreen::SetIsTwoSignal(BOOL b)
{
	m_bIsTwoSignal=b;
}

BOOL XScreen::GetIsTwoSignal()
{
	return m_bIsTwoSignal;
}

void XScreen::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XScreen::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XScreen::SetNumOfTwoScreen(int n)
{
	m_nNumOfTwoScreen=n;
}

int XScreen::GetNumOfTwoScreen()
{
	return m_nNumOfTwoScreen;
}

void XScreen::SetIsPreview(BOOL b)
{
	m_bIsPreview=b;
}

BOOL XScreen::GetIsPreview()
{
	return m_bIsPreview;
}

void XScreen::SetSignalTopByID(int nScreenIndex,unsigned int nID)
{
	BOOL bISTwoScreen=GetIsTwoSignal();

	int nNum=GetNumOfTwoScreen();

	for(VEC_SIGNAL::iterator iter=m_VecSignal.begin();iter!=m_VecSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();

		if(pSignal->GetSignalID()==nID)
		{
			m_pManage->GetMultiVideoWIndow()->SetFrameTop(GetIndex(),pFrame);

			XSendDataScreenManage::AddSendDataOfSetSignalTop(m_pManage,nScreenIndex,nID,nNum,bISTwoScreen);

			m_VecSignal.erase(iter);

			m_VecSignal.push_back(pSignal);

			break;
		}
	}
}


void XScreen::SetSignalTopByGroupID(int nScreenIndex,unsigned int nGroupID)
{
	BOOL bISTwoScreen=GetIsTwoSignal();

	int nNum=GetNumOfTwoScreen();

	for(VEC_SIGNAL::iterator iter=m_VecSignal.begin();iter!=m_VecSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();

		unsigned int nID=pSignal->GetSignalID();

		if(pSignal->GetSignalGroupID()==nGroupID)
		{
				m_pManage->GetMultiVideoWIndow()->SetFrameTop(GetIndex(),pFrame);

				//m_pManage->GetMultiVideoWIndow()->SetFrameTopByGroupID(GetIndex(),nGroupID);

				XSendDataScreenManage::AddSendDataOfSetSignalTop(m_pManage,nScreenIndex,nID,nNum,bISTwoScreen);

				m_VecSignal.erase(iter);

				m_VecSignal.push_back(pSignal);

				break;
		}
	}
}

void XScreen::SetSignalBottom(int nScreenIndex,unsigned int nGroupID)
{
	BOOL bISTwoScreen=this->GetIsTwoSignal();

	int nNum=this->GetNumOfTwoScreen();

	for(VEC_SIGNAL::iterator iter=m_VecSignal.begin();iter!=m_VecSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();

		unsigned int nID=pSignal->GetSignalID();

		if(pSignal->GetSignalGroupID()==nGroupID)
		{
			m_pManage->GetMultiVideoWIndow()->SetFrameBottom(GetIndex(),pFrame);

			//m_pManage->GetMultiVideoWIndow()->SetFrameBottomByGroupID(GetIndex(),nGroupID);

			XSendDataScreenManage::AddSendDataOfSetSignalBottom(m_pManage,nScreenIndex,nID,nNum,bISTwoScreen);

			m_VecSignal.erase(iter);

			m_VecSignal.insert(m_VecSignal.begin(),pSignal);

			break;
		}	
	}
}

void XScreen::SetSignalShiftUp(int nScreenIndex,unsigned int nGroupID)
{
	BOOL bISTwoScreen=GetIsTwoSignal();

	int nNum=GetNumOfTwoScreen();

	int nCount=m_VecSignal.size();

	if(nCount>1)
	{
		for(int i=0;i<nCount;i++)
		{
			unsigned int nID=m_VecSignal[i]->GetSignalID();

			if(m_VecSignal[i]->GetSignalGroupID()==nGroupID)
			{
				XSendDataScreenManage::AddSendDataOfSetSignalShiftUP(m_pManage,nScreenIndex,nID,nNum,bISTwoScreen);

				if(i!=(nCount-1))
				{
					//交换位置
					XSignal* pTemp=NULL;

					pTemp=m_VecSignal[i];

					m_VecSignal[i]=m_VecSignal[i+1];

					m_VecSignal[i+1]=pTemp;

					break;
				}
			}
		}
	}
}

void XScreen::SetSignalShiftDown(int nScreenIndex,unsigned int nGroupID)
{
	BOOL bISTwoScreen=GetIsTwoSignal();

	int nNum=GetNumOfTwoScreen();

	int nCount=m_VecSignal.size();

	if (nCount>1)
	{
		for (int i=0;i<nCount;i++)
		{
			unsigned int nID=m_VecSignal[i]->GetSignalID();

			if (m_VecSignal[i]->GetSignalGroupID()==nGroupID)
			{
				XSendDataScreenManage::AddSendDataOfSetSignalShiftDown(m_pManage,nScreenIndex,nID,nNum,bISTwoScreen);

				if (i!=0)
				{
					XSignal* pTemp=NULL;

					pTemp=m_VecSignal[i-1];

					m_VecSignal[i-1]=m_VecSignal[i];

					m_VecSignal[i]=pTemp;

					break;
				}
			}
		}
	}
}

void XScreen::DeleteSignalBySignalGroupID(XScreenManage *pManage,int nScreenIndex,unsigned int nGroupID)
{
	BOOL bISTwoScreen=GetIsTwoSignal();

	int nNum=GetNumOfTwoScreen();

	VEC_SIGNAL::iterator iter=m_VecSignal.begin();

	while(iter!=m_VecSignal.end())
	{
		XSignal *pSignal=*iter;

		//CString szIPAddr=pSignal->GetIPAddr();

		unsigned int nID=pSignal->GetSignalID();

		if(pSignal->GetSignalGroupID()==nGroupID)
		{
			//////////////////////////////////////////////////////////////////////////
			pManage->GetMultiVideoWIndow()->DeleteFrame(GetIndex(),pSignal->GetPreviewFrame());
			//如果该信号还剩余一个，则设置预览框中所有信号为该序号的流地址的RTSP个数为1;
			int nCount=pManage->GetSignalCountByIndex(pSignal->GetInputIndex());

			if(nCount==1)
			{
				pManage->SetFrameRTSPCountByIndex(pSignal->GetInputIndex());
			}
			else
			{
				pManage->GetDelegate()->SetRTSPAddrCountLess(pSignal->GetRTSPAddr());
			}

			
			//////////////////////////////////////////////////////////////////////////

			iter=m_VecSignal.erase(iter);

			delete pSignal;

			if(pManage->GetScreenModel()==SCREENMODEL_SPLIC)
			{
				XSendDataScreenManage::AddSendDataOfSignalClose(pManage,nScreenIndex,nID,nNum,bISTwoScreen);
			}
			else if(pManage->GetScreenModel()==SCREENMODEL_MATRIX)
			{
				XSendDataScreenManage::AddSendDataOfDeleteMatrixSignal(pManage,this);
			}
		}
		else
		{
			iter++;
		}
	}
}

void XScreen::DeleteSignalBySignalID(XScreenManage *pManage,int nScreenIndex,unsigned int nID)
{
	BOOL bISTwoScreen=this->GetIsTwoSignal();

	int nNum=this->GetNumOfTwoScreen();

	for(VEC_SIGNAL::iterator iter=m_VecSignal.begin();iter!=m_VecSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		if(pSignal->GetSignalID()==nID)
		{
			pManage->GetMultiVideoWIndow()->DeleteFrame(GetIndex(),pSignal->GetPreviewFrame());

			m_VecSignal.erase(iter);

			delete pSignal;

			XSendDataScreenManage::AddSendDataOfSignalClose(pManage,nScreenIndex,nID,nNum,bISTwoScreen);

			break;
		}
	}
}

void XScreen::DeleteSignal(XSignal* p)
{
	for (VEC_SIGNAL::iterator iter = m_VecSignal.begin(); iter != m_VecSignal.end(); iter++)
	{
		XSignal* pSignal = *iter;

		if (pSignal == p)
		{
			m_VecSignal.erase(iter);

			delete pSignal;

			break;
		}
	}
}

XSignal* XScreen::AddSignal(
	RECTF& rect, 
	int& nLevel,
	int& nInputIndex, 
	CString szAnothgerName,
	unsigned int& signalID,
	unsigned int& signalGroupID,
	XExpandInfo* pExpandInfo,
	BOOL bIsUltra)
{
	XSignal* pSignal=new XSignal;

	pSignal->SetScreen(this);
	pSignal->SetRect(rect);
	pSignal->SetSignalLevel(nLevel);
	pSignal->SetInputIndex(nInputIndex);
	pSignal->SetAnotherName(szAnothgerName);
	pSignal->SetSignalID(signalID);
	pSignal->SetSignalGroupID(signalGroupID);
	pSignal->SetExpand(pExpandInfo);
	pSignal->SetIsUltra(bIsUltra);

	m_VecSignal.push_back(pSignal);

	return pSignal;
}

XSignal* XScreen::GetSignalByID(unsigned int nID)
{
	for(VEC_SIGNAL::iterator iter=m_VecSignal.begin();iter!=m_VecSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		if(pSignal->GetSignalID()==nID)
		{
			return pSignal;
		}
	}
	return NULL;
}

BOOL XScreen::CanAddSignal()
{
	int nNum=GetAddSignalNumInScreen();

	int nMaxNum=GetMaxSignalNumInScreen();

	if (nNum>nMaxNum)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


BOOL XScreen::CanAddSignal(int n)
{
	int nSize=m_VecSignal.size();

	if (nSize>=n)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void XScreen::SortSignal()
{
	int nCount=m_VecSignal.size();

	for(int i=0;i<nCount;i++)
	{
		for(int j=i+1;j<nCount;j++)
		{
			if(m_VecSignal[i]->GetSignalLevel()>m_VecSignal[j]->GetSignalLevel())
			{
				XSignal* pTemp=NULL;

				pTemp=m_VecSignal[i];

				m_VecSignal[i]=m_VecSignal[j];

				m_VecSignal[j]=pTemp;
			}
		}
	}
}

void XScreen::SeteDataLen(int n)
{
	m_ReDataLen=n;
}
void XScreen::SetReStatus(int n)
{
	m_ReStatus=n;
}
void XScreen::SetReScreenHdpi(int n)
{
	m_ReScreenHdpi=n;
}
void XScreen::SetReScreenVdpi(int n)
{
	m_ReScreenVdpi=n;
}
void XScreen::SetReDpiIndex(int n)
{
	m_ReDpiIndex=n;
}
void XScreen::SetReRefresh(int n)
{
	m_ReRefresh=n;
}

int XScreen::GeteDataLen()
{
	return m_ReDataLen;
}
int XScreen::GetReStatus()
{
	return m_ReStatus;
}
int XScreen::GetReScreenHdpi()
{
	return m_ReScreenHdpi;
}
int XScreen::GetReScreenVdpi()
{
	return m_ReScreenVdpi;
}
int XScreen::GetReDpiIndex()
{
	return m_ReDpiIndex;
}
int XScreen::GetReRefresh()
{
	return m_ReRefresh;
}


BOOL XScreen::GetIsHasSignalOfMatrix()
{
	return m_bIsHasSignalOfMatrix;
}

void XScreen::SetIsHasSignalOfMatrix(BOOL b)
{
	m_bIsHasSignalOfMatrix=b;
}

void XScreen::SetScreenType(int n)
{
	m_nScreenType=n;
}

int XScreen::GetScreenType()
{
	return m_nScreenType;
}