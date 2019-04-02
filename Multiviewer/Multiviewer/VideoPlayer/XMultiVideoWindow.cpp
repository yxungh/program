#include "StdAfx.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrame.h"
#include "XMultiVideoWindowFrames.h"
#include "XRTSP.h"
#include "XVideoPlayer.h"
#include "HandleCode.h"
#include "XBaseScreenManage.h"
#include "..\MultiviewerView.h"
#include "XDrawScreenManage.h"
#include "XScreenManage.h"
#include "XCalculateScreenManage.h"
#include "XSignal.h"
#include "HandlePath.h"
#include "XScreenDataInfo.h"
#include "XScreenColInfo.h"
#include "XScreenRowInfo.h"


#define FONT_SIZE   12

XMultiVideoWindow::XMultiVideoWindow(void)
{
	m_CreateWindow = FALSE;

	m_CreateRender = FALSE;

	m_bResetVideoShow = FALSE;

	m_window = NULL;

	m_renderer = NULL;

	m_HWND = NULL;

	m_Row = 0;

	m_Column = 0;

	m_textureBGImage = NULL;

	m_textureText=NULL;

	m_szBGImagePath = _T("");

	m_VideoPlayer = NULL;

	m_MushHardCode = FALSE;

	m_ColorBG.r = 40; 
	m_ColorBG.g = 41; 
	m_ColorBG.b = 45; 
	m_ColorBG.a = 255; 

	m_ColorLine.r = 255; 
	m_ColorLine.g = 255; 
	m_ColorLine.b = 255; 
	m_ColorLine.a = 255; 

	m_TextColor.r = 255; 
	m_TextColor.g = 0; 
	m_TextColor.b = 0; 
	m_TextColor.a = 200; 

	m_nTextSize=12;

	m_nOrgX=0;

	m_nOrgY=0;

	m_nScreenModel=0;

	m_dwScale=0.0f;

	m_nFramesCountH=0;

	m_nFramesCountV=0;

	m_nFramesResolutionH=200;

	m_nFramesResolutionV=112;

	m_nRightResulationH=200;

	m_nBottomResulationV=112;

	m_bIsMainMultiVideo=FALSE;

	m_bIsDragFrame=FALSE;

	InitializeCriticalSection(&m_CS);

	InitializeCriticalSection(&m_CSBGImage);
}


XMultiVideoWindow::~XMultiVideoWindow(void)
{
	ClearData();

	ClearVecFrames();

	ClearRowInfo();

	ClearColInfo();

	DeleteCriticalSection(&m_CS);

	DeleteCriticalSection(&m_CSBGImage);
}

BOOL XMultiVideoWindow::CreateSDLWindow()
{
	WNDPROC wndproc = (WNDPROC) GetWindowLongPtr(m_HWND, GWLP_WNDPROC);	// 获取窗口处理函数

	SDL_Window* window = SDL_CreateWindowFrom(m_HWND);

	if (!window)
	{
		return FALSE;
	}

	//*
	WNDPROC sdlproc = (WNDPROC)GetWindowLongPtr(m_HWND, GWLP_WNDPROC);
	if (sdlproc != wndproc) 
	{
		SetWindowLongPtr(m_HWND, GWLP_WNDPROC, (LONG_PTR)wndproc);
	}
	//*/

	//::UnregisterTouchWindow(m_HWND);

	m_window = window;

	m_CreateWindow = TRUE;

	return TRUE;
}

BOOL XMultiVideoWindow::CreateSDLRenderer()
{
	if (!m_CreateWindow)
	{
		return FALSE;
	}

	SDL_Renderer* renderer = NULL;

	if (m_MushHardCode || (m_VideoPlayer != NULL && m_VideoPlayer->GetHardDecode()))
	{
		renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_ACCELERATED);
	}
	else
	{
		renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
	}

	if (!renderer) 
	{
		return FALSE;
	}

	m_renderer = renderer;

	m_CreateRender = TRUE;

	return TRUE;
}

void XMultiVideoWindow::ClearData()
{
	m_CreateWindow = FALSE;

	ClearTextureBGImage();

	ClearRenderer();
	
	if (NULL != m_window)
	{
		SDL_DestroyWindow(m_window);

		m_window = NULL;
	}

	if (NULL != m_HWND)
	{
		ShowWindow(m_HWND, SW_SHOW);
	}

	//ClearTextureText();
}

void XMultiVideoWindow::ClearRenderer()
{
	m_CreateRender = FALSE;

	if (m_renderer != NULL)
	{
		SDL_DestroyRenderer(m_renderer);

		m_renderer = NULL;
	}
}

BOOL XMultiVideoWindow::GetCreateSDLWindow()
{
	return m_CreateWindow;
}

BOOL XMultiVideoWindow::GetCreateSDLRenderer()
{
	return m_CreateRender;
}

HWND XMultiVideoWindow::GetHWND()
{
	return m_HWND;
}

void XMultiVideoWindow::SetMushHardCode(BOOL b)
{
	m_MushHardCode = b;
}

void XMultiVideoWindow::SetHWND(HWND h)
{
	m_HWND = h;
}

void XMultiVideoWindow::SetFrame(int nRow, int nColumn)
{
	m_Row = nRow;

	m_Column = nColumn;
}

void XMultiVideoWindow::SetVideoPlayer(XVideoPlayer* p)
{
	EnterCriticalSection(&m_CS);

	m_VideoPlayer = p;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::InitFont()
{
	//初始化字体
	m_VideoPlayer->SetFontPath(HandlePath::GetFontPath(_T("msyh.ttf")));
}

XVideoPlayer* XMultiVideoWindow::GetVideoPlayer()
{
	return m_VideoPlayer;
}

SDL_Renderer* XMultiVideoWindow::GetRenderer()
{
	return m_renderer;
}

void XMultiVideoWindow::SetIsMainMultiVideo(BOOL b)
{
	EnterCriticalSection(&m_CS);

	m_bIsMainMultiVideo=b;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetIsDragFrame(BOOL b)
{
	EnterCriticalSection(&m_CS);

	m_bIsDragFrame=b;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::Draw()
{
	EnterCriticalSection(&m_CS);

	if(m_CreateRender)
	{
		DrawBGColor();

		if(m_bIsMainMultiVideo)
		{
			DrawFrames();
		}

		DrawFrame();

		SDL_RenderPresent(m_renderer);
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DrawBGColor()
{
	SDL_SetRenderDrawColor(m_renderer, m_ColorBG.r, m_ColorBG.g, m_ColorBG.b, m_ColorBG.a);

	SDL_RenderClear(m_renderer);
}

void XMultiVideoWindow::DrawBGImage()
{
	EnterCriticalSection(&m_CSBGImage);

	//DWORD dwBegin = GetTickCount();

	if (m_textureBGImage != NULL)
	{
		SDL_RenderCopy(m_renderer, m_textureBGImage, NULL, NULL);
	}

	//DWORD dwEnd = GetTickCount();

	//TRACE("DrawBGImage:%d\n", dwEnd - dwBegin);

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::SetScreenModel(int n)
{
	EnterCriticalSection(&m_CS);

	m_nScreenModel=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetMultiScale(float f)
{
	EnterCriticalSection(&m_CS);

	m_dwScale=f;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesCountH(int n)
{
	EnterCriticalSection(&m_CS);

	m_nFramesCountH=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesCountV(int n)
{
	EnterCriticalSection(&m_CS);

	m_nFramesCountV=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesResulationH(int n)
{
	EnterCriticalSection(&m_CS);

	m_nFramesResolutionH=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesResulationV(int n)
{
	EnterCriticalSection(&m_CS);

	m_nFramesResolutionV=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesRightResulationH(int n)
{
	EnterCriticalSection(&m_CS);

	m_nRightResulationH=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesBottomResulationV(int n)
{
	EnterCriticalSection(&m_CS);

	m_nBottomResulationV=n;

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetMapRowInfo(MAP_ROWINFO& MapRowInfo)
{
	EnterCriticalSection(&m_CS);
	//先清空
	for(auto iter=m_MapRowInfo.begin();iter!=m_MapRowInfo.end();++iter)
	{
		delete iter->second;
	}
	m_MapRowInfo.clear();
	
	//////////////////////////////////////////////////////////////////////////
	for(auto iter=MapRowInfo.begin();iter!=MapRowInfo.end();++iter)
	{
		int nRow=iter->first;
		XScreenRowInfo* pRowInfo=iter->second;

		MAP_FRAMEROWINFO::iterator iterFrame=m_MapRowInfo.find(nRow);
		if(iterFrame!=m_MapRowInfo.end())
		{
			XScreenRowInfo* pFrameRowInfo=iterFrame->second;
			pFrameRowInfo->SetScreenHeight(pRowInfo->GetScreenHeight());
			pFrameRowInfo->SetResoluationV(pRowInfo->GetResoluationV());
		}
		else
		{
			XScreenRowInfo* pFrameRowInfo=new XScreenRowInfo;
			pFrameRowInfo->SetScreenHeight(pRowInfo->GetScreenHeight());
			pFrameRowInfo->SetResoluationV(pRowInfo->GetResoluationV());

			m_MapRowInfo.insert(std::pair<int,XScreenRowInfo*>(nRow,pFrameRowInfo));
		}
	}
	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetMapColInfo(MAP_COLINFO& MapColInfo)
{
	EnterCriticalSection(&m_CS);
	for(auto iter=m_MapColInfo.begin();iter!=m_MapColInfo.end();++iter)
	{
		delete iter->second;
	}
	m_MapColInfo.clear();
	//////////////////////////////////////////////////////////////////////////

	for(auto iter=MapColInfo.begin();iter!=MapColInfo.end();++iter)
	{
		int nCol=iter->first;
		XScreenColInfo* pColInfo=iter->second;

		MAP_FRAMECOLINFO::iterator iterCol=m_MapColInfo.find(nCol);
		if(iterCol!=m_MapColInfo.end())
		{
			XScreenColInfo* pFrameCol=iterCol->second;
			pFrameCol->SetScreenWidth(pColInfo->GetScreenWidth());
			pFrameCol->SetResoluationH(pColInfo->GetResoluationH());
		}
		else
		{
			XScreenColInfo* pFrameCol=new XScreenColInfo;
			pFrameCol->SetScreenWidth(pColInfo->GetScreenWidth());
			pFrameCol->SetResoluationH(pColInfo->GetResoluationH());

			m_MapColInfo.insert(std::pair<int,XScreenColInfo*>(nCol,pFrameCol));
		}
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameSelectByGroupID(unsigned int nGroupID)
{
	EnterCriticalSection(&m_CS);

	for(auto iter=m_MapFrames.begin();iter!=m_MapFrames.end();++iter)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		pFrames->SetFrameSelectByGroupID(nGroupID);
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DrawFrames()
{
	CRect rect;
	GetClientRect(m_HWND,&rect);

	CSize size=ViewGetSize();
	int nPosH=GetScrollPos(m_HWND,SB_HORZ);
	int nPosV=GetScrollPos(m_HWND,SB_VERT);

	CSize cOrgSize;
	XCalculateScreenManage::SetPreviewOrg(rect,nPosH,nPosV,size,m_dwScale,cOrgSize);

	//原点偏移
	m_nOrgX=cOrgSize.cx;
	m_nOrgY=cOrgSize.cy;

	//TRACE(_T("OrgSize X=%d,Y=%d\n"),m_nOrgX,m_nOrgY);

	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin();iter!=m_MapFrames.end();++iter)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		int nIndex=pFrames->GetScreenIndex();
		//TRACE(_T("nFrameIndex=%d\n"),nIndex);

		int nBoardIndex=pFrames->GetBoardIndex();
		BOOL bIsTwoScreen=pFrames->GetIsTwoScreen();
		//TRACE(_T("bIsTwoScreen=%d\n"),bIsTwoScreen);

		RECTF rectScreen=pFrames->GetScreenRect();

		SDL_Rect sdl_rect;
		sdl_rect.x=rectScreen.X*m_dwScale+m_nOrgX;
		sdl_rect.y=rectScreen.Y*m_dwScale+m_nOrgY;
		sdl_rect.w=rectScreen.Width*m_dwScale;
		sdl_rect.h=rectScreen.Height*m_dwScale;

		switch(m_nScreenModel)
		{
		case SCREENMODEL_SPLIC:
			{
				if(IsHaveDevice(nBoardIndex))
				{
					//TRACE(_T("HaveDevice\n"));
					SDL_SetRenderDrawColor(m_renderer,40, 41, 45,255);
					SDL_RenderFillRect(m_renderer,&sdl_rect);
				}
				else
				{
					//TRACE(_T("NOHaveDevice\n"));
					SDL_SetRenderDrawColor(m_renderer,60, 60, 45,255);
					SDL_RenderFillRect(m_renderer,&sdl_rect);
				}
			}
			break;
		case SCREENMODEL_MATRIX:
			{
				SDL_SetRenderDrawColor(m_renderer,40, 41, 45,255);
				SDL_RenderFillRect(m_renderer,&sdl_rect);
			}
			break;
		default:
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		switch(m_nScreenModel)
		{
		case SCREENMODEL_SPLIC:
			{
				//绘制分隔线
				if (!bIsTwoScreen)
				{
					//四周线条
					SDL_SetRenderDrawColor(m_renderer,255,255,255,150);
					DrawRect(rectScreen);
					//////////////////////////////////////////////////////////////////////////
					if(nBoardIndex!=0)
					{
						//内部分割线
						float X1,Y1,X2,Y2; 
						SDL_SetRenderDrawColor(m_renderer,180,184,184,50);

						X1=rectScreen.X*m_dwScale+m_nOrgX;
						X2=rectScreen.X*m_dwScale+rectScreen.Width*m_dwScale+m_nOrgX-1;
						Y1=Y2=rectScreen.Y*m_dwScale+rectScreen.Height*m_dwScale/2+m_nOrgY-1;
						SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);

						X1=X2=rectScreen.X*m_dwScale+rectScreen.Width*m_dwScale/2+m_nOrgX-1;
						Y1=rectScreen.Y*m_dwScale+m_nOrgY;
						Y2=rectScreen.Y*m_dwScale+rectScreen.Height*m_dwScale+m_nOrgY;
						SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);
					}
				}
				else
				{
					//四周线条
					SDL_SetRenderDrawColor(m_renderer,255,255,255,150);
					DrawRect(rectScreen);
					//////////////////////////////////////////////////////////////////////////
					if(nBoardIndex!=0)
					{
						float X1,Y1,X2,Y2;
						SDL_SetRenderDrawColor(m_renderer,180,184,184,50);

						X1=rectScreen.X*m_dwScale+m_nOrgX;
						X2=rectScreen.X*m_dwScale+rectScreen.Width*m_dwScale+m_nOrgX-1;
						Y1=Y2=rectScreen.Y*m_dwScale+rectScreen.Height*m_dwScale/2+m_nOrgY-1;
						SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);
					}
				}
			}
			break;
		case SCREENMODEL_MATRIX:
			{
				//四周线条
				SDL_SetRenderDrawColor(m_renderer,255,255,255,150);
				DrawRect(rectScreen);
			}
			break;
		default:
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		//绘制文字
		if(pFrames->GetCreateTextureText())
		{
			pFrames->CreateScreenText();
		}

		SDL_Texture* pTextureText = pFrames->GetTextureText();

		if (NULL!=pTextureText)
		{
			int nTextWidth = pFrames->GetTextureTextWidth();
			int nTextHeight = pFrames->GetTextureTextHeight();

			SDL_Rect rectText;
			rectText.x=sdl_rect.x+2;
			rectText.y=sdl_rect.y;
			rectText.w=nTextWidth;
			rectText.h=nTextHeight;

			SDL_RenderCopy(m_renderer, pTextureText, NULL, &rectText);
		}
	}
}

void XMultiVideoWindow::DrawRect(RECTF& rect)
{
	float X1,Y1,X2,Y2; 

	X1=rect.X*m_dwScale+m_nOrgX-1;
	X2=rect.X*m_dwScale+rect.Width*m_dwScale+m_nOrgX;
	Y1=Y2=rect.Y*m_dwScale+m_nOrgY-1;
	SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);

	X1=rect.X*m_dwScale+m_nOrgX-1;
	X2=rect.X*m_dwScale+rect.Width*m_dwScale+m_nOrgX;
	Y1=Y2=rect.Y*m_dwScale+rect.Height*m_dwScale+m_nOrgY;
	SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);

	X1=X2=rect.X*m_dwScale+m_nOrgX-1;
	Y1=rect.Y*m_dwScale+m_nOrgY-1;
	Y2=rect.Y*m_dwScale+rect.Height*m_dwScale+m_nOrgY;
	SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);

	X1=rect.X*m_dwScale+rect.Width*m_dwScale+m_nOrgX;
	X2=rect.X*m_dwScale+rect.Width*m_dwScale+m_nOrgX;
	Y1=rect.Y*m_dwScale+m_nOrgY;
	Y2=rect.Y*m_dwScale+rect.Height*m_dwScale+m_nOrgY;
	SDL_RenderDrawLine(m_renderer,X1,Y1,X2,Y2);
}

void XMultiVideoWindow::DrawFrame()
{
	SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);

	XMultiVideoWindowFrames* pFramesDrag = NULL;

	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		//对于拖动信号添加的序号为0，要特别处理
		if (pFrames->GetScreenIndex()==0)
		{
			pFramesDrag = pFrames;
		}
		else
		{
			DrawFrame(pFrames);
		}
	}

	///////////////////////////////////////////////////////
	if (pFramesDrag != NULL)
	{
		DrawFrame(pFramesDrag);
	}
}

void XMultiVideoWindow::SetFrameDraw(XMultiVideoWindowFrames* pFrames)
{
	VEC_RECT VecRect;

	VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

	for (VEC_MULTIVIDEOWINDOWFRAME::reverse_iterator iter = VecFrame.rbegin(); iter != VecFrame.rend(); iter++)
	{
		XMultiVideoWindowFrame* pFrame = *iter;

		pFrame->m_Draw = FALSE;

		if (!pFrame->GetShow())
		{
			continue;
		}

		SDL_Rect rectFrame = pFrame->GetRect();

		CRect crectFrame(rectFrame.x, rectFrame.y, rectFrame.x + rectFrame.w, rectFrame.y + rectFrame.h);

		if (!DecideRectInVecRect(VecRect, crectFrame))
		{
			VecRect.push_back(crectFrame);

			pFrame->m_Draw = TRUE;
		}
	}
}

void XMultiVideoWindow::DrawFrame(XMultiVideoWindowFrames* pFrames)
{
	SetFrameDraw(pFrames);

	MAP_RTSP& MapRTSP = m_VideoPlayer->GetMapRTSP();
	VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();
	//////////////////////////////////////////////////////////////////////////
	//先求出每个ID区域
	//MAP_FRAMEID MapFrameID;
	//MapFrameID.clear();
	for (auto iter=VecFrame.begin();iter!=VecFrame.end();iter++)
	{
		XMultiVideoWindowFrame* pFrame=*iter;
		unsigned int nFrameGroupID=pFrame->GetFrameGroupID();

		if(nFrameGroupID!=0)
		{
			SDL_Rect rect=GetInterRectByGroupID(nFrameGroupID);

			MAP_FRAMEID::iterator iterID=m_MapFrameID.find(nFrameGroupID);
			if(iterID!=m_MapFrameID.end())
				iterID->second=rect;
			else
				m_MapFrameID.insert(std::pair<unsigned int,SDL_Rect>(nFrameGroupID,rect));
		}
	}
	//////////////////////////////////////////////////////////////////////////
	for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter=VecFrame.begin();iter!=VecFrame.end();iter++)
	{
		XMultiVideoWindowFrame* pFrame=*iter;

		if (!pFrame->GetShow())
			continue;

		if (!pFrame->m_Draw)
			continue;

		SDL_Rect rect=pFrame->GetRect();

		SDL_Rect rectFrame={0,0,0,0};
		if(m_bIsMainMultiVideo)
		{
			rectFrame.x=rect.x*m_dwScale+m_nOrgX;
			rectFrame.y=rect.y*m_dwScale+m_nOrgY;
			rectFrame.w=rect.w*m_dwScale;
			rectFrame.h=rect.h*m_dwScale;
		}
		else
		{
			rectFrame=rect;
		}

		//TRACE(_T("m_dwScale=%f\n"),m_dwScale);
		//////////////////////////////////////////////////////////////////////////
		int nFrameIndex=pFrame->GetFrameIndex();
		int nFrameUltraIndex=pFrame->GetFrameUltraIndex();
		unsigned int nFrameGroupID=pFrame->GetFrameGroupID();
		BOOL bIsUltra=pFrame->GetFrameIsUltra();

		//根据组ID获取 信号序号
		VEC_NUM VecIndex;
		VecIndex.clear();
		GetVecIndexByFrameGroupID(nFrameGroupID,VecIndex);

		//TRACE(_T("SIZE=%d\n"),VecIndex.size());

		//if(nFrameGroupID!=0
		//	&&VecIndex.size()!=0)
		//		MapFrameID.insert(std::pair<unsigned int,int>(nFrameGroupID,VecIndex[0]));

		/////////////////////////////////////////////////////
		//图像
		BOOL bRenderCopyImage=FALSE;
		CString szRTSPAddr=pFrame->GetRTSPAddr();
		if (szRTSPAddr!=_T(""))
		{
			MAP_RTSP::iterator iterRTSP = MapRTSP.find(szRTSPAddr);
			if(MapRTSP.end()!=iterRTSP)
			{
				XRTSP* pRTSP=iterRTSP->second;
				EnterCriticalSection(&pRTSP->m_CSFrameYUV);
				if(pFrame->CreateTexture(m_renderer,pRTSP))
				{
					if(pRTSP->m_frame_yuv!=NULL&&(pRTSP->m_is_file||pRTSP->m_RecvFlagKey)) 
					{
						if (!pFrame->GetSetRectImageReal())
							pFrame->SetRectImageReal();

						SDL_Rect rectImage=pFrame->GetRectImageReal();
						SDL_Texture* pTextTure=pFrame->GetTexture();
						SDL_UpdateTexture(pTextTure,NULL,pRTSP->m_frame_yuv->data[0],pRTSP->m_frame_yuv->linesize[0]);
						SDL_RenderCopy(m_renderer,pTextTure,&rectImage,&rectFrame);

						bRenderCopyImage=TRUE;
					}
				}
				LeaveCriticalSection(&pRTSP->m_CSFrameYUV);
			}
		}

		if(!bRenderCopyImage)
		{	
			//if(pFrame->GetFrameSelected())
			//	SDL_SetRenderDrawColor(m_renderer,13,163,135,255);//(51,153,255)//(50,55,250)//50,55,250,255
			//else
			SDL_SetRenderDrawColor(m_renderer,50,55,250,255);//(51,153,255)//(50,55,250)//50,55,250,255
			SDL_RenderFillRect(m_renderer,&rectFrame);
			SDL_SetRenderDrawColor(m_renderer,186,193,202,80);
			SDL_RenderDrawRect(m_renderer,&rectFrame);

			//////////////////////////////////////////////////////////////////////////
			//输入源文字（左上角）
			if(nFrameGroupID!=0&&VecIndex.size()!=0)
			{
				MAP_FRAMEID::iterator iterID=m_MapFrameID.find(nFrameGroupID);

				SDL_Rect rectInput={0,0,0,0};

				if(iterID!=m_MapFrameID.end())
					rectInput=iterID->second;

				rectInput.x=rectInput.x*m_dwScale;
				rectInput.y=rectInput.y*m_dwScale;
				rectInput.w=rectInput.w*m_dwScale;
				rectInput.h=rectInput.h*m_dwScale;

				CString szAnotherName=GetAnotherNameByIndex(VecIndex[0]);
				CString szText=GetShowText(szAnotherName,VecIndex[0]);

				SetText(szText);

				if(GetCreateTextureText())
					CreateTextureText();

				SDL_Texture* pTextureInputText=GetTextureText();
				if(NULL!=pTextureInputText)
				{
					//防止文字超过信号区域
					int nTextWidth=0;
					if(m_nTextureTextWidth<rectInput.w-10)
						nTextWidth=m_nTextureTextWidth;
					else
						nTextWidth=rectInput.w-10;

					int nTextHeight=0;
					if(m_nTextureTextHeight<rectInput.h)
						nTextHeight=m_nTextureTextHeight;
					else
						nTextHeight=rectInput.h;

					SDL_Rect rectInputText;
					rectInputText.x=rectInput.x+m_nOrgX+5;
					rectInputText.y=rectInput.y+m_nOrgY;
					rectInputText.w=nTextWidth;
					rectInputText.h=nTextHeight;

					SDL_RenderCopy(m_renderer,pTextureInputText,NULL,&rectInputText);
				}
			}
		}
		/////////////////////////////////////////////////////
		//文字(序号)
		if(pFrame->GetCreateTextureText())
			pFrame->CreateTextureText();

		SDL_Texture* pTextureText=pFrame->GetTextureText();

		if(NULL!=pTextureText)
		{
			int nTextWidth=pFrame->GetTextureTextWidth();
			int nTextHeight=pFrame->GetTextureTextHeight();

			SDL_Rect rectText;
			rectText.x=rectFrame.x+5;
			rectText.y=rectFrame.y;
			rectText.w=nTextWidth;
			rectText.h=nTextHeight;

			SDL_RenderCopy(m_renderer,pTextureText,NULL,&rectText);
		}
	}
}

void XMultiVideoWindow::GetVecIndexByFrameGroupID(unsigned int nFrameGroupID,VEC_NUM& VecIndex)
{
	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

		for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = VecFrame.begin(); iter != VecFrame.end(); iter++)
		{
			XMultiVideoWindowFrame* pFrame = *iter;

			if(nFrameGroupID==pFrame->GetFrameGroupID())
			{
				int nIndex=pFrame->GetFrameIndex();

				if(nIndex!=0)
				{
					VecIndex.push_back(nIndex);
				}	
			}
		}
	}
}

CString XMultiVideoWindow::GetShowText(CString szName,int nIndex)
{
	CString szText=_T("");

	CString szTemp=_T("");

	CString szText1=_T("输入源");

	if(szName==_T(""))
	{
		szTemp.Format(_T("%d"),nIndex);

		szText=szText1+_T(":")+szTemp;
	}
	else
	{
		szText=szText1+_T(":")+szName;
	}

	return szText;
}

CString XMultiVideoWindow::GetAnotherNameByIndex(int nIndex)
{
	CString szName=_T("");

	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

		for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = VecFrame.begin(); iter != VecFrame.end(); iter++)
		{
			XMultiVideoWindowFrame* pFrame = *iter;

			if(nIndex==pFrame->GetFrameIndex())
			{
				szName=pFrame->GetFrameAnotherName();
			}
		}
	}

	return szName;
}

SDL_Rect XMultiVideoWindow::GetInterRectByGroupID(unsigned int nGroupID)
{
	SDL_Rect rect;
	rect.x=0;
	rect.y=0;
	rect.w=0;
	rect.h=0;

	BOOL bFirst=TRUE;

	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

		for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = VecFrame.begin(); iter != VecFrame.end(); iter++)
		{
			XMultiVideoWindowFrame* pFrame = *iter;

			unsigned int nGID=pFrame->GetFrameGroupID();

			if(nGID==nGroupID)
			{
				SDL_Rect tempRect=pFrame->GetRect();

				if(bFirst)
				{
					rect=tempRect;

					bFirst=FALSE;
				}
				else
				{
					SDL_UnionRect(&rect,&tempRect,&rect);
				}
			}
		}
	}

	return rect;	
}

CSize XMultiVideoWindow::ViewGetSize()
{	
	int nTempX=0;
	for(auto iter=m_MapColInfo.begin();iter!=m_MapColInfo.end();++iter)
	{
		XScreenColInfo* pInfo=iter->second;
		nTempX+=pInfo->GetScreenWidth()*m_dwScale;
	}

	int nTempY=0;
	for(auto iter=m_MapRowInfo.begin();iter!=m_MapRowInfo.end();++iter)
	{
		XScreenRowInfo* pInfo=iter->second;
		nTempY+=pInfo->GetScreenHeight()*m_dwScale;
	}

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+nTempX);
	size.cy=LONG(DRAWDISTANCE_Y*2+nTempY);

	//TRACE(_T("sizeX=%d,sizeY=%d\n"),size.cx,size.cy);
	return size;
}

BOOL XMultiVideoWindow::IsHaveDevice(int nIndex)
{
	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin();iter!=m_MapFrames.end();++iter)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		int nScreenIndex=pFrames->GetBoardIndex();

		if(nIndex==nScreenIndex)
		{
			if(pFrames->GetReStatus()==0x01
				||pFrames->GetReStatus()==0x11
				||pFrames->GetReStatus()==0x12
				||pFrames->GetReStatus()==0x13)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void XMultiVideoWindow::ClearVecFrames()
{
	EnterCriticalSection(&m_CS);

	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin();iter!=m_MapFrames.end();++iter)
	{
		delete iter->second;
	}

	m_MapFrames.clear();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ClearRowInfo()
{
	EnterCriticalSection(&m_CS);

	for(auto iter=m_MapRowInfo.begin();iter!=m_MapRowInfo.end();++iter)
	{
		delete iter->second;
	}

	m_MapRowInfo.clear();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ClearColInfo()
{
	EnterCriticalSection(&m_CS);

	for(auto iter=m_MapColInfo.begin();iter!=m_MapColInfo.end();++iter)
	{
		delete iter->second;
	}

	m_MapColInfo.clear();

	LeaveCriticalSection(&m_CS);
}

XMultiVideoWindowFrame* XMultiVideoWindow::AddFrame(int nScreenIndex, CString szRTSPAddr, RECTF rFrame, 
	RECTF rImage, BOOL bShow)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	XMultiVideoWindowFrame* pFrame = pFrames->AddFrame(szRTSPAddr, rFrame, rImage, bShow);

	LeaveCriticalSection(&m_CS);

	return pFrame;
}

XMultiVideoWindowFrames* XMultiVideoWindow::AddFrames(int nScreenIndex,int nBoardIndex,RECTF rScreenRect,int nPaneNum,BOOL bIsTwoScreen)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nScreenIndex);

	pFrames->SetBoardIndex(nBoardIndex);

	pFrames->SetScreenRect(rScreenRect);

	pFrames->SetPaneNum(nPaneNum);

	pFrames->SetIsTwoScreen(bIsTwoScreen);

	LeaveCriticalSection(&m_CS);

	return pFrames;
}

XMultiVideoWindowFrame* XMultiVideoWindow::GetFrame(int nScreenIndex,unsigned int nSignalID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nScreenIndex);

	XMultiVideoWindowFrame* pFrame=pFrames->GetFrame(nSignalID);

	LeaveCriticalSection(&m_CS);

	return pFrame;
}

void XMultiVideoWindow::SetFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, RECTF rFrame, RECTF rImage)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrame(pFrame, rFrame, rImage);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, CString szRTSPAddr)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrame(pFrame, szRTSPAddr);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameID(int nScreenIndex,XMultiVideoWindowFrame* pFrame,unsigned int nFrameID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameID(pFrame,nFrameID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameGroupID(int nScreenIndex,XMultiVideoWindowFrame* pFrame,unsigned int nFrameGroupID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameGroupID(pFrame,nFrameGroupID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameIndex(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameIndex(pFrame,nIndex);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameUltraIndex(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nUltraIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameUltraIndex(pFrame,nUltraIndex);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameIsUltra(int nScreenIndex,XMultiVideoWindowFrame* pFrame,BOOL b)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameIsUltra(pFrame,b);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameAnotherName(int nScreenIndex,XMultiVideoWindowFrame* pFrame,CString szAnotherName)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameAnotherName(pFrame,szAnotherName);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nScreenIndex,XMultiVideoWindowFrame* pFrame, RECTF rFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrame(pFrame, rFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameImage(int nScreenIndex, XMultiVideoWindowFrame* pFrame, RECTF rImage)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameImage(pFrame, rImage);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameText(int nScreenIndex, XMultiVideoWindowFrame* pFrame, CString text)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameText(pFrame, text);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameText(int nScreenIndex,XMultiVideoWindowFrame* pFrame, COLORREF nTextColor, int nTextSize)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameText(pFrame, nTextColor, nTextSize);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesText(int nScreenIndex,CString szText,int ntextSize)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFramesText(szText,ntextSize);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteFrame(int nScreenIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->DeleteFrame(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteFrame(int nScreenIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->ClearVecFrame();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteAllFrame()
{
	EnterCriticalSection(&m_CS);

	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin();iter!=m_MapFrames.end();++iter)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		pFrames->ClearVecFrame();
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ShowFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, BOOL bShow)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->ShowFrame(pFrame, bShow);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ShowFrame(int nScreenIndex,unsigned int nGroupID, BOOL bShow)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->ShowFrame(nGroupID,bShow);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameTop(int nScreenIndex, XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameTop(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameTopByGroupID(int nScreenIndex,unsigned int nGroupID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameTopByGroupID(nGroupID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameBottom(int nScreenIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameBottom(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameBottomByGroupID(int nScreenIndex,unsigned int nGroupID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameBottomByGroupID(nGroupID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameUp(int nScreenIndex, XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameUp(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameUpByGroupID(int nScreenIndex, unsigned int nGroupID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameUpByGroupID(nGroupID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameDown(int nScreenIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameDown(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameDownByGroupID(int nScreenIndex, unsigned int nGroupID)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameDownByGroupID(nGroupID);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameLevel(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nLevel)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetFrameLevel(pFrame,nLevel);

	LeaveCriticalSection(&m_CS);
}
//
//void XMultiVideoWindow::DeleteAllFrames()
//{
//	EnterCriticalSection(&m_CS);
//
//	ClearVecFrames();
//
//	LeaveCriticalSection(&m_CS);
//}

void XMultiVideoWindow::SortFrame(int nScreenIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SortFrame();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesReIndex(int nScreenIndex,int nIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReScreenIndex(nIndex);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReDateLen(int nScreenIndex,int nDataLen)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReDataLen(nDataLen);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReStatus(int nScreenIndex,int nStatus)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReStatus(nStatus);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReResulationH(int nScreenIndex,int nResulationH)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReScreenHdpi(nResulationH);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReResulationV(int nScreenIndex,int nResulationV)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReScreenVdpi(nResulationV);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReResulationIndex(int nScreenIndex,int nIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReDpiIndex(nIndex);

	LeaveCriticalSection(&m_CS);
}
void XMultiVideoWindow::SetFramesReRefreash(int nScreenIndex,int nRefreash)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames = GetFrames(nScreenIndex);

	pFrames->SetReRefresh(nRefreash);

	LeaveCriticalSection(&m_CS);
}

XMultiVideoWindowFrames* XMultiVideoWindow::GetFrames(int nScreenIndex)
{
	MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.find(nScreenIndex);

	if (m_MapFrames.end()==iter)
	{
		XMultiVideoWindowFrames* pFrames = new XMultiVideoWindowFrames;

		pFrames->SetMultiVideoWindow(this);

		pFrames->SetScreenIndex(nScreenIndex);

		m_MapFrames.insert(std::pair<int, XMultiVideoWindowFrames*>(nScreenIndex, pFrames));

		return pFrames;
	}
	else
	{
		return iter->second;
	}
}

MAP_MULTIVIDEOWINDOWFRAMES& XMultiVideoWindow::GetMapFrames()
{
	return m_MapFrames;
}

void XMultiVideoWindow::SetBGImage(CString szPath)
{
	EnterCriticalSection(&m_CSBGImage);

	m_szBGImagePath = szPath;

	if (m_CreateRender)
	{
		char path[MAX_PATH];

		ZeroMemory(path, MAX_PATH);

		HandleCode::GetUTF8FromUnicode(szPath, path);

		SDL_Texture* texture = GetImageTexture(m_renderer, path);

		szPath.ReleaseBuffer();

		ClearTextureBGImage();

		m_textureBGImage = texture;
	}

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::DeleteBGImage()
{
	EnterCriticalSection(&m_CSBGImage);

	m_szBGImagePath = _T("");

	ClearTextureBGImage();

	LeaveCriticalSection(&m_CSBGImage);
}

SDL_Texture* XMultiVideoWindow::GetImageTexture(SDL_Renderer *pRenderer, char *szFile)
{
	SDL_Surface *pSurface = IMG_Load(szFile);

	if(pSurface == NULL)
	{
		return NULL;
	}

	SDL_Texture *pTexture;

	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

	SDL_FreeSurface(pSurface);

	return pTexture;
}

void XMultiVideoWindow::ClearTextureBGImage()
{
	if (m_textureBGImage != NULL)
	{
		SDL_DestroyTexture(m_textureBGImage);

		m_textureBGImage = NULL;
	}
}

BOOL XMultiVideoWindow::DecideRectInVecRect(VEC_RECT& VecRect, CRect& rect)
{
	for (VEC_RECT::iterator iter = VecRect.begin(); iter != VecRect.end(); iter++)
	{
		CRect& rectTemp = *iter;

		CRect temp;

		if (temp.IntersectRect(rectTemp, rect))
		{
			if (temp.EqualRect(rect))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void XMultiVideoWindow::ResetVideoShow()
{
	ClearRenderer();

	CreateSDLRenderer();

	ReloadBGImage();

	ClearMapFramesTexture();
}

void XMultiVideoWindow::ReloadBGImage()
{
	ClearTextureBGImage();

	if (m_szBGImagePath != _T(""))
	{
		SetBGImage(m_szBGImagePath);
	}
}

void XMultiVideoWindow::ClearMapFramesTexture()
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFramesDrag = NULL;

	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames = iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

		for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter1 = VecFrame.begin(); iter1 != VecFrame.end(); iter1++)
		{
			XMultiVideoWindowFrame* pFrame = *iter1;

			pFrame->ClearTexture();
		}
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetResetVideoShow(BOOL b)
{
	m_bResetVideoShow = b;
}

BOOL XMultiVideoWindow::GetResetVideoShow()
{
	return m_bResetVideoShow;
}

void XMultiVideoWindow::SetBGColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_ColorBG.r = r;
	m_ColorBG.g = g;
	m_ColorBG.b = b;
}

void XMultiVideoWindow::SetLineColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_ColorLine.r = r;
	m_ColorLine.g = g;
	m_ColorLine.b = b;
}

void XMultiVideoWindow::ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)
{
	EnterCriticalSection(&m_CS);

	for (MAP_MULTIVIDEOWINDOWFRAMES::iterator iter = m_MapFrames.begin(); iter != m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame = pFrames->GetVecFrame();

		for (VEC_MULTIVIDEOWINDOWFRAME::iterator iter = VecFrame.begin(); iter != VecFrame.end(); iter++)
		{
			XMultiVideoWindowFrame* pFrame = *iter;

			if(nInputIndex==pFrame->GetFrameIndex())
			{
				pFrame->SetFrameAnotherName(szAnotherName);
			}
		}
	}

	LeaveCriticalSection(&m_CS);
}


void XMultiVideoWindow::SetText(CString text)
{
	if (m_szText != text)
	{
		m_szText = text;

		m_CreateTextureText = TRUE;
	}
}

BOOL XMultiVideoWindow::GetCreateTextureText()
{
	return m_CreateTextureText;
}

void XMultiVideoWindow::CreateTextureText()
{
	ClearTextureText();

	m_VideoPlayer->CreateTextureOfText(m_renderer, m_szText, m_nTextSize, 
		m_TextColor, m_textureText, m_nTextureTextWidth, m_nTextureTextHeight);

	m_CreateTextureText = FALSE;
}

SDL_Texture* XMultiVideoWindow::GetTextureText()
{
	return m_textureText;
}

void XMultiVideoWindow::ClearTextureText()
{
	if (NULL != m_textureText)
	{
		SDL_DestroyTexture(m_textureText);

		m_textureText = NULL;
	}
}

