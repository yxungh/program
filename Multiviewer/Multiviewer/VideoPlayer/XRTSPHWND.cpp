#include "StdAfx.h"
#include "XRTSPHWND.h"
#include "XRTSP.h"
#include "XVideoPlayer.h"

XRTSPHWND::XRTSPHWND(void)
{
	m_CreateWindow = FALSE;

	m_CreateTexture = FALSE;

	m_CreateRender = FALSE;

	m_window = NULL;

	m_HWND = NULL;

	m_texture = NULL;

	m_renderer = NULL;

	m_RTSPAddr = _T("");

	m_VideoPlayer = NULL;

	m_bResetVideoShow = FALSE;

	m_HWNDWidth = 0;
	m_HWNDHeight = 0;

	m_BGColor.r = 40;
	m_BGColor.g = 41;
	m_BGColor.b = 45;
	m_BGColor.a = 255;

	//文字
	m_textureText = NULL;
	m_szText = _T("");
	m_TextColor.r = 255; 
	m_TextColor.g = 0; 
	m_TextColor.b = 0; 
	m_TextColor.a = 255; 
	m_nTextSize = 30;
	m_nTextureTextWidth = 0;
	m_nTextureTextHeight = 0;
	m_CreateTextureText = FALSE;

	//滚动
	m_ScrollLeft = 0;
	m_ScrollTop = 0;
	m_ScrollRight = 100;
	m_ScrollStep = 2;
	m_ScrollDistanceTime = 10000;
}

XRTSPHWND::~XRTSPHWND(void)
{
	ClearData();
}

void XRTSPHWND::ClearRenderer()
{
	m_CreateRender = FALSE;

	if (m_renderer != NULL)
	{
		SDL_DestroyRenderer(m_renderer);

		m_renderer = NULL;
	}
}

void XRTSPHWND::ClearTexture()
{
	m_CreateTexture = FALSE;

	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);

		m_texture = NULL;
	}
}

void XRTSPHWND::ClearData()
{
	m_CreateWindow = FALSE;

	ClearTexture();

	ClearTextureText();

	ClearRenderer();
	
	if (m_window != NULL)
	{
		SDL_DestroyWindow(m_window);
		m_window = NULL;
	}

	if (NULL != m_HWND)
	{
		//ShowWindow(m_HWND, SW_SHOW);
	}
}

HWND XRTSPHWND::GetHWND()
{
	return m_HWND;
}

void XRTSPHWND::SetHWND(HWND h)
{
	m_HWND = h;
}

CString XRTSPHWND::GetRTSPAddr()
{
	return m_RTSPAddr;
}

void XRTSPHWND::SetRTSPAddr(CString s)
{
	m_RTSPAddr = s;
}

void XRTSPHWND::SetVideoPlayer(XVideoPlayer* p)
{
	m_VideoPlayer = p;
}

BOOL XRTSPHWND::CreateSDLWindow()
{
	WNDPROC wndproc = (WNDPROC) GetWindowLongPtr(m_HWND, GWLP_WNDPROC);	// 获取窗口处理函数
	
	SDL_Window* window = SDL_CreateWindowFrom(m_HWND);

	if (!window)
	{
		return FALSE;
	}

	///*
	WNDPROC sdlproc = (WNDPROC)GetWindowLongPtr(m_HWND, GWLP_WNDPROC);
	if (sdlproc != wndproc) 
	{
		SetWindowLongPtr(m_HWND, GWLP_WNDPROC, (LONG_PTR)wndproc);
	}
	//*/

	//::UnregisterTouchWindow(m_HWND);

	CRect rect;
	::GetClientRect(m_HWND, &rect);
	m_HWNDWidth = rect.Width();
	m_HWNDHeight = rect.Height();

	m_ScrollRight = m_HWNDWidth;

	m_window = window;

	m_CreateWindow = TRUE;

	return TRUE;
}

BOOL XRTSPHWND::CreateSDLRenderer()
{
	if (!m_CreateWindow)
	{
		return FALSE;
	}

	SDL_Renderer* renderer = NULL;

	if (m_VideoPlayer != NULL && m_VideoPlayer->GetHardDecode())
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

BOOL XRTSPHWND::GetCreateSDLWindow()
{
	return m_CreateWindow;
}

BOOL XRTSPHWND::GetCreateSDLRenderer()
{
	return m_CreateRender;
}

BOOL XRTSPHWND::CreateTexture(XRTSP* pRTSP)
{
	if (!m_CreateWindow)
	{
		return FALSE;
	}

	if (!m_CreateRender)
	{
		return FALSE;
	}

	if (m_CreateTexture)
	{
		if (m_textureWidth != pRTSP->m_frame_yuv_Width || m_textureHeight != pRTSP->m_frame_yuv_Height)
		{
			ClearTexture();
		}
	}

	if (m_CreateTexture)
	{
		return TRUE;
	}

	if (pRTSP->m_frame_yuv == NULL)
	{
		return FALSE;
	}

	SDL_Texture* texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
			pRTSP->m_frame_yuv_Width, pRTSP->m_frame_yuv_Height);

	if (!texture) 
	{
		return FALSE;
	}

	m_texture = texture;

	m_textureWidth = pRTSP->m_frame_yuv_Width;

	m_textureHeight = pRTSP->m_frame_yuv_Height;

	m_CreateTexture = TRUE;

	return TRUE;
}

void XRTSPHWND::ResetVideoShow()
{
	ClearRenderer();

	CreateSDLRenderer();

	ClearTexture();

	ClearTextureText();
}

void XRTSPHWND::SetResetVideoShow(BOOL b)
{
	m_bResetVideoShow = b;
}

BOOL XRTSPHWND::GetResetVideoShow()
{
	return m_bResetVideoShow;
}

void XRTSPHWND::SetBGColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_BGColor.r = r;
	m_BGColor.g = g;
	m_BGColor.b = b;
	m_BGColor.a = a;
}

void XRTSPHWND::ClearTextureText()
{
	if (NULL != m_textureText)
	{
		SDL_DestroyTexture(m_textureText);

		m_textureText = NULL;
	}
}

void XRTSPHWND::SetText(CString szText)
{
	if (m_szText != szText)
	{
		m_szText = szText;

		m_CreateTextureText = TRUE;
	}
}

void XRTSPHWND::SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (m_TextColor.r != r 
		|| m_TextColor.g != g
		|| m_TextColor.b != b
		|| m_TextColor.a != a)
	{
		m_TextColor.r = r;
		m_TextColor.g = g;
		m_TextColor.b = b;
		m_TextColor.a = a;

		if (_T("") != m_szText)
		{
			m_CreateTextureText = TRUE;
		}
	}
}

void XRTSPHWND::SetTextSize(int n)
{
	//文字大小不允许小于0
	if (0 >= n)
	{
		n = 10;
	}

	if (m_nTextSize != n)
	{
		m_nTextSize = n;

		if (_T("") != m_szText)
		{
			m_CreateTextureText = TRUE;
		}
	}
}

void XRTSPHWND::CreateTextureText()
{
	ClearTextureText();

	m_CreateTextureText = FALSE;

	if (!m_CreateRender)
	{
		return;
	}

	if (_T("") != m_szText)
	{
		//TRACE("XRTSPHWND::CreateTextureText\n");

		m_VideoPlayer->CreateTextureOfText(m_renderer, m_szText, m_nTextSize, 
			m_TextColor, m_textureText, m_nTextureTextWidth, m_nTextureTextHeight);
	}
}

void XRTSPHWND::SetTextScrollRect(int nLeft, int nTop, int nRight)
{
	m_ScrollLeft = nLeft;

	m_ScrollTop = nTop;

	m_ScrollRight = nRight;

	//不允许滚动右小于滚动左
	if (m_ScrollRight <= m_ScrollLeft)
	{
		m_ScrollRight = m_ScrollLeft + 100;
	}
}

void XRTSPHWND::BeginTextScroll()
{
	m_ScrollX = m_ScrollRight;

	m_ScrollTime = av_gettime();
}

void XRTSPHWND::TextScroll()
{
	int64_t nowTime = av_gettime();

	if((nowTime - m_ScrollTime) > m_ScrollDistanceTime)
	{
		m_ScrollTime = nowTime;

		m_ScrollX -= m_ScrollStep;
	}
}

SDL_Rect XRTSPHWND::GetTextScrollSrcRect()
{
	SDL_Rect rect;

	int nSrcWidth = m_ScrollRight - m_ScrollX + 1;

	if (nSrcWidth > m_nTextureTextWidth)
	{
		nSrcWidth = m_nTextureTextWidth;
	}

	int nX = m_ScrollX;

	if (m_ScrollX < m_ScrollLeft)
	{
		nX = m_ScrollLeft - m_ScrollX;

		nSrcWidth -= (m_ScrollLeft - m_ScrollX);
	}
	else
	{
		nX = 0;
	}

	int nScrollWidth = m_ScrollRight - m_ScrollLeft + 1;

	if (nSrcWidth > nScrollWidth)
	{
		nSrcWidth = nScrollWidth;
	}

	rect.x = nX;
	rect.y = 0;
	rect.h = m_nTextureTextHeight;
	rect.w = nSrcWidth;

	return rect;
}

SDL_Rect XRTSPHWND::GetTextScrollDesRect()
{
	SDL_Rect srcRect = GetTextScrollSrcRect();

	SDL_Rect rect;

	int nX = m_ScrollX;

	if (m_ScrollX < m_ScrollLeft)
	{
		nX = m_ScrollLeft;
	}

	rect.x = nX;
	rect.y = m_ScrollTop;
	rect.w = srcRect.w;
	rect.h = m_nTextureTextHeight;

	return rect;
}

void XRTSPHWND::SetHWNDTextScrollTimeAndStep(int nDistanceTime, int nStep)
{
	if (nStep <= 0)
	{
		nStep = 2;
	}

	if (nDistanceTime <= 0)
	{
		nDistanceTime = 10;
	}

	m_ScrollDistanceTime = nDistanceTime * 1000;

	m_ScrollStep = nStep;
}