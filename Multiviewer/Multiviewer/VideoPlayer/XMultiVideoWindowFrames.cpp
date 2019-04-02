#include "StdAfx.h"
#include "XMultiVideoWindowFrames.h"
#include "XMultiVideoWindowFrame.h"
#include "XMultiVideoWindow.h"
#include "XScreenManage.h"
#include "XVideoPlayer.h"

XMultiVideoWindowFrames::XMultiVideoWindowFrames(void)
{

	m_MultiVideoWindow = NULL;

	m_ReDataLen=0;

	m_ReStatus=0;

	m_ReScreenHdpi=0;

	m_ReScreenVdpi=0;

	m_ReDpiIndex=0;

	m_ReRefresh=0;

	m_ColorText.r = 255; 
	m_ColorText.g = 255; 
	m_ColorText.b = 255; 
	m_ColorText.a = 255; 

	m_szText=_T("");

	m_textureText = NULL;

	m_nReScreenIndex=0;

	m_ReDataLen=0;

	m_ReStatus=0;

	m_ReScreenHdpi=0;

	m_ReScreenVdpi=0;

	m_ReDpiIndex=0;

	m_ReRefresh=0;

}


XMultiVideoWindowFrames::~XMultiVideoWindowFrames(void)
{
	ClearVecFrame();
}

void XMultiVideoWindowFrames::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_MultiVideoWindow = p;
}

XVideoPlayer* XMultiVideoWindowFrames::GetVideoPlayer()
{
	return m_MultiVideoWindow->GetVideoPlayer();
}

SDL_Renderer* XMultiVideoWindowFrames::GetRenderer()
{
	return m_MultiVideoWindow->GetRenderer();
}

void XMultiVideoWindowFrames::ClearVecFrame()
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); ++iter)
	{
		delete *iter;
	}

	m_VecFrame.clear();
}

VEC_MULTIVIDEOWINDOWFRAME& XMultiVideoWindowFrames::GetVecFrame()
{
	return m_VecFrame;
}

int XMultiVideoWindowFrames::GetScreenIndex()
{
	return m_nScreenIndex;
}
void XMultiVideoWindowFrames::SetScreenIndex(int n)
{
	m_nScreenIndex=n;
}

int XMultiVideoWindowFrames::GetBoardIndex()
{
	return m_nBoardIndex;
}
void XMultiVideoWindowFrames::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

RECTF XMultiVideoWindowFrames::GetScreenRect()
{
	return m_ScreenRect;
}
void XMultiVideoWindowFrames::SetScreenRect(RECTF rect)
{
	m_ScreenRect=rect;
}

int XMultiVideoWindowFrames::GetPaneNum()
{
	return m_nPaneNum;
}
void XMultiVideoWindowFrames::SetPaneNum(int n)
{
	m_nPaneNum=n;
}

BOOL XMultiVideoWindowFrames::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}
void XMultiVideoWindowFrames::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

void XMultiVideoWindowFrames::SetFrameSelectByGroupID(unsigned int nGroupID)
{
	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XMultiVideoWindowFrame* pFrame=*iter;

		if(pFrame->GetFrameGroupID()==nGroupID)
			pFrame->SetFrameSelected(TRUE);
		else
			pFrame->SetFrameSelected(FALSE);
	}
}

//////////////////////////////////////////////////////////////////////////

XMultiVideoWindowFrame* XMultiVideoWindowFrames::AddFrame(CString szRTSPAddr, RECTF rFrame, RECTF rImage, 
	BOOL bShow)
{
	XMultiVideoWindowFrame* pFrame = new XMultiVideoWindowFrame;

	pFrame->SetMultiVideoWindowFrames(this);

	pFrame->SetRTSPAddr(szRTSPAddr);

	pFrame->SetRect(rFrame);

	pFrame->SetRectImage(rImage);

	pFrame->Show(bShow);

	m_VecFrame.push_back(pFrame);

	return pFrame;
}

XMultiVideoWindowFrame* XMultiVideoWindowFrames::GetFrame(unsigned int nSignalID)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		unsigned int nID=pTemp->GetFrameID();

		if(nID==nSignalID)
		{
			return pTemp;
		}
	}

	return NULL;
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame, RECTF rFrame, RECTF rImage)
{
	if (pFrame != NULL)
	{
		pFrame->SetRect(rFrame);

		pFrame->SetRectImage(rImage);
	}
}


void XMultiVideoWindowFrames::SetFrameID(XMultiVideoWindowFrame* pFrame,unsigned int nFrameID)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameID(nFrameID);
	}
}

void XMultiVideoWindowFrames::SetFrameGroupID(XMultiVideoWindowFrame* pFrame,unsigned int nFrameGroupID)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameGroupID(nFrameGroupID);
	}
}

void XMultiVideoWindowFrames::SetFrameIsUltra(XMultiVideoWindowFrame* pFrame,BOOL b)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameIsUltra(b);
	}
}

void XMultiVideoWindowFrames::SetFrameUltraIndex(XMultiVideoWindowFrame* pFrame,int nUltraFrameIndex)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameUltraIndex(nUltraFrameIndex);
	}
}

void XMultiVideoWindowFrames::SetFrameIndex(XMultiVideoWindowFrame* pFrame,int nFrameIndex)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameIndex(nFrameIndex);
	}
}

void XMultiVideoWindowFrames::SetFrameAnotherName(XMultiVideoWindowFrame* pFrame,CString szAnotherName)
{
	if(NULL!=pFrame)
	{
		pFrame->SetFrameAnotherName(szAnotherName);
	}
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame, CString szRTSPAddr)
{
	if (pFrame != NULL)
	{
		pFrame->SetRTSPAddr(szRTSPAddr);
	}
}

void XMultiVideoWindowFrames::SetFrameText(XMultiVideoWindowFrame* pFrame, CString text)
{
	if (pFrame != NULL)
	{
		pFrame->SetText(text);
	}
}

void XMultiVideoWindowFrames::SetFrameText(XMultiVideoWindowFrame* pFrame, COLORREF nTextColor, int nTextSize)
{
	if (pFrame != NULL)
	{
		pFrame->SetText(nTextColor, nTextSize);
	}
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame, RECTF rFrame)
{
	if (pFrame != NULL)
	{
		pFrame->SetRect(rFrame);
	}
}

void XMultiVideoWindowFrames::SetFrameImage(XMultiVideoWindowFrame* pFrame, RECTF rImage)
{
	if (pFrame != NULL)
	{
		pFrame->SetRectImage(rImage);
	}
}

void XMultiVideoWindowFrames::DeleteFrame(XMultiVideoWindowFrame* pFrame)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		if (pTemp == pFrame)
		{
			delete pFrame;

			m_VecFrame.erase(iter);

			break;
		}
	}
}

void XMultiVideoWindowFrames::ShowFrame(XMultiVideoWindowFrame* pFrame, BOOL bShow)
{
	if (pFrame != NULL)
	{
		pFrame->Show(bShow);
	}
}

void XMultiVideoWindowFrames::ShowFrame(unsigned int nGroup, BOOL bShow)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pFrame=*iter;

		unsigned int nFrameGroupID=pFrame->GetFrameGroupID();

		if(nFrameGroupID==nGroup)
		{
			pFrame->Show(bShow);
		}
	}
}

void XMultiVideoWindowFrames::SetFrameTop(XMultiVideoWindowFrame* pFrame)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		//unsigned int nFrameGroupID=pTemp->GetFrameGroupID();

		if (pTemp == pFrame)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.push_back(pFrame);

			break;
		}
	}
}

void XMultiVideoWindowFrames::SetFrameTopByGroupID(unsigned int nGroupID)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		unsigned int nFrameGroupID=pTemp->GetFrameGroupID();

		if (nFrameGroupID==nGroupID)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.push_back(pTemp);

			break;
		}
	}
}

void XMultiVideoWindowFrames::SetFrameBottom(XMultiVideoWindowFrame* pFrame)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		if (pTemp == pFrame)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.insert(m_VecFrame.begin(), pTemp);

			break;
		}
	}
}

void XMultiVideoWindowFrames::SetFrameBottomByGroupID(unsigned int nGroupID)
{
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp = *iter;

		unsigned int nFrameGroupID=pTemp->GetFrameGroupID();

		if (nFrameGroupID==nGroupID)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.insert(m_VecFrame.begin(), pTemp);

			break;
		}
	}
}

void XMultiVideoWindowFrames::SetFrameUp(XMultiVideoWindowFrame* pFrame)
{
	int nSize=m_VecFrame.size();

	if(nSize>1)
	{
		for(int i=0;i<nSize;i++)
		{
			if(m_VecFrame[i]==pFrame)
			{
				if(i!=(nSize-1))
				{
					XMultiVideoWindowFrame* pTemp=NULL;

					pTemp=m_VecFrame[i];

					m_VecFrame[i]=m_VecFrame[i+1];

					m_VecFrame[i+1]=pTemp;

					break;
				}
			}
		}
	}
}

void XMultiVideoWindowFrames::SetFrameUpByGroupID(unsigned int nGroupID)
{
	int nSize=m_VecFrame.size();

	if(nSize>1)
	{
		for(int i=0;i<nSize;i++)
		{
			unsigned int nFrameGroupID=m_VecFrame[i]->GetFrameGroupID();

			if(nFrameGroupID==nGroupID)
			{
				if(i!=(nSize-1))
				{
					XMultiVideoWindowFrame* pTemp=NULL;

					pTemp=m_VecFrame[i];

					m_VecFrame[i]=m_VecFrame[i+1];

					m_VecFrame[i+1]=pTemp;

					break;
				}
			}
		}
	}
}

void XMultiVideoWindowFrames::SetFrameDown(XMultiVideoWindowFrame* pFrame)
{
	int nSize=m_VecFrame.size();

	if(nSize>1)
	{
		for(int i=0;i<nSize;i++)
		{
			if(m_VecFrame[i]==pFrame)
			{
				if(i!=0)
				{
					XMultiVideoWindowFrame* pTemp=NULL;

					pTemp=m_VecFrame[i-1];

					m_VecFrame[i-1]=m_VecFrame[i];

					m_VecFrame[i]=pTemp;

					break;
				}
			}
		}
	}
}

void XMultiVideoWindowFrames::SetFrameDownByGroupID(unsigned int nGroupID)
{
	int nSize=m_VecFrame.size();

	if(nSize>1)
	{
		for(int i=0;i<nSize;i++)
		{
			unsigned int nFrameGroupID=m_VecFrame[i]->GetFrameGroupID();

			if(nFrameGroupID==nGroupID)
			{
				if(i!=0)
				{
					XMultiVideoWindowFrame* pTemp=NULL;

					pTemp=m_VecFrame[i-1];

					m_VecFrame[i-1]=m_VecFrame[i];

					m_VecFrame[i]=pTemp;

					break;
				}
			}
		}
	}
}

void XMultiVideoWindowFrames::SetFrameLevel(XMultiVideoWindowFrame* pFrame,int nLevel)
{
	if(NULL!=pFrame)
	{
		pFrame->SetLevel(nLevel);
	}
}

void XMultiVideoWindowFrames::SortFrame()
{
	int nCount=m_VecFrame.size();

	for(int i=0;i<nCount;i++)
	{
		for(int j=i+1;j<nCount;j++)
		{
			if(m_VecFrame[i]->GetLevel()>m_VecFrame[j]->GetLevel())
			{
				XMultiVideoWindowFrame* pTemp=NULL;

				pTemp=m_VecFrame[i];

				m_VecFrame[i]=m_VecFrame[j];

				m_VecFrame[j]=pTemp;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void XMultiVideoWindowFrames::SetFramesText(CString szText,int nTextSize)
{
	m_nTextSize=nTextSize;

	if (m_szText!=szText)
	{
		m_szText=szText;

		m_CreateTextureText=TRUE;
	}
}

BOOL XMultiVideoWindowFrames::GetCreateTextureText()
{
	return m_CreateTextureText;
}

void XMultiVideoWindowFrames::CreateScreenText(float f)
{
	ClearScreenText();

	if(m_szText!=_T(""))
	{
		SDL_Renderer* pRenderer=m_MultiVideoWindow->GetRenderer();

		XVideoPlayer* pVideoPlayer=m_MultiVideoWindow->GetVideoPlayer();

		pVideoPlayer->CreateTextureOfText(pRenderer, m_szText, 12*f, 
			m_ColorText, m_textureText, m_nTextureTextWidth, m_nTextureTextHeight);
	}

	m_CreateTextureText = FALSE;
}

void XMultiVideoWindowFrames::ClearScreenText()
{
	if(NULL!=m_textureText)
	{
		SDL_DestroyTexture(m_textureText);

		m_textureText = NULL;
	}
}

SDL_Texture* XMultiVideoWindowFrames::GetTextureText()
{
	return m_textureText;
}

int XMultiVideoWindowFrames::GetTextureTextWidth()
{
	return m_nTextureTextWidth;
}

int XMultiVideoWindowFrames::GetTextureTextHeight()
{
	return m_nTextureTextHeight;
}

//////////////////////////////////////////////////////////////////////////
void XMultiVideoWindowFrames::SetReDataLen(int n)
{
	m_ReDataLen=n;
}

void XMultiVideoWindowFrames::SetReScreenIndex(int n)
{
	m_nReScreenIndex=n;
}
void XMultiVideoWindowFrames::SetReStatus(int n)
{
	m_ReStatus=n;
}
void XMultiVideoWindowFrames::SetReScreenHdpi(int n)
{
	m_ReScreenHdpi=n;
}
void XMultiVideoWindowFrames::SetReScreenVdpi(int n)
{
	m_ReScreenVdpi=n;
}
void XMultiVideoWindowFrames::SetReDpiIndex(int n)
{
	m_ReDpiIndex=n;
}
void XMultiVideoWindowFrames::SetReRefresh(int n)
{
	m_ReRefresh=n;
}

int XMultiVideoWindowFrames::GeteDataLen()
{
	return m_ReDataLen;
}
int XMultiVideoWindowFrames::GetReScreenIndex()
{
	return m_nReScreenIndex;
}
int XMultiVideoWindowFrames::GetReStatus()
{
	return m_ReStatus;
}
int XMultiVideoWindowFrames::GetReScreenHdpi()
{
	return m_ReScreenHdpi;
}
int XMultiVideoWindowFrames::GetReScreenVdpi()
{
	return m_ReScreenVdpi;
}
int XMultiVideoWindowFrames::GetReDpiIndex()
{
	return m_ReDpiIndex;
}
int XMultiVideoWindowFrames::GetReRefresh()
{
	return m_ReRefresh;
}
