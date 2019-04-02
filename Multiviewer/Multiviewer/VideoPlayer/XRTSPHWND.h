#pragma once

class XRTSP;
class XVideoPlayer;

class XRTSPHWND
{
public:
	XRTSPHWND(void);
	~XRTSPHWND(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	BOOL CreateSDLWindow();

	BOOL CreateSDLRenderer();

	BOOL CreateTexture(XRTSP* pRTSP);

	HWND GetHWND();

	void SetHWND(HWND h);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString s);

	//获取是否创建SDLWindow
	BOOL GetCreateSDLWindow();

	//获取是否创建SDLRenderer
	BOOL GetCreateSDLRenderer();

	//清除数据
	void ClearData();

	void ClearRenderer();

	void ClearTexture();

	//设置重置视频显示
	void SetResetVideoShow(BOOL b);

	//获取重置视频显示
	BOOL GetResetVideoShow();

	//重置视频显示
	void ResetVideoShow();

	//设置背景颜色
	void SetBGColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

public:

	//设置文字
	void SetText(CString szText);

	//设置文字颜色
	void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	//设置文字大小
	void SetTextSize(int n);

	//清除文字Texture
	void ClearTextureText();

	//创建文字Texture
	void CreateTextureText();

public:

	//设置文字滚动区域
	void SetTextScrollRect(int nLeft, int nTop, int nRight);

	//设置文字滚动时间和步进
	void SetHWNDTextScrollTimeAndStep(int nDistanceTime, int nStep);

	//开始文字滚动
	void BeginTextScroll();

	//获取文字滚动起始区域
	SDL_Rect GetTextScrollSrcRect();

	//获取文字滚动目标区域
	SDL_Rect GetTextScrollDesRect();

	//文字滚动
	void TextScroll();

public:

	XVideoPlayer* m_VideoPlayer;

	//句柄
	HWND m_HWND;

	//RTSP地址
	CString m_RTSPAddr;

	//是否创建Window
	BOOL m_CreateWindow;

	//是否创建renderer
	BOOL m_CreateRender;

	//是否创建Texture
	BOOL m_CreateTexture;

	SDL_Window* m_window;

	SDL_Renderer* m_renderer;

	SDL_Texture* m_texture;

	int m_textureWidth;

	int m_textureHeight;

	BOOL m_bResetVideoShow;

	//背景颜色
	SDL_Color m_BGColor;

	int m_HWNDWidth;

	int m_HWNDHeight;

public://文字

	//文字Texture
	SDL_Texture* m_textureText;

	//文字
	CString m_szText;

	//文字颜色
	SDL_Color m_TextColor;

	//文字大小
	int m_nTextSize;

	//是否需要创建文字
	BOOL m_CreateTextureText;

	//文字宽度
	int m_nTextureTextWidth;

	//文字高度
	int m_nTextureTextHeight;

public:

	//滚动左
	int m_ScrollLeft;

	//滚动上
	int m_ScrollTop;

	//滚动右
	int m_ScrollRight;

	//滚动座标X
	int m_ScrollX;

	//滚动时间
	int64_t m_ScrollTime;

	//滚动步进
	int m_ScrollStep;

	//滚动时间间隔(微秒)
	int m_ScrollDistanceTime;
};