#pragma once

#include "VideoPlayerConstant.h"

class XMultiVideoWindow;
class XVideoPreviewPane;

class XVideoPlayer
{
public:
	XVideoPlayer(void);
	~XVideoPlayer(void);

public:

	static void InitFFMPEG();

public:

	//初始化
	int Init();

	//清除数据
	void ClearData();
	
	//处理RTSP显示
	void HandleRTSPShow();

	//void SetPreviewPan(XVideoPreviewPane* pan);

	MAP_RTSP& GetMapRTSP();

public:

	//添加RTSP
	//void AddRTSP(CString szRTSPAddr);

	void AddRTSP(CString szRTSPAddr,int ncount);

	void SetRTSPCountPlus(CString szRTSPAddr);

	void SetRTSPCountLess(CString szRTSPAddr);

	void SetRTSPAddrCount(CString szRTSPAddr,int nCount);

	//删除RTSP
	void DeleteRTSP(CString szRTSPAddr);

	//获取RTSP地址连接状态
	int GetRTSPConnectState(CString szRTSPAddr);

public:

	//设置是否硬解
	void SetHardDecode(BOOL bHardDecode);

	//获取是否硬解码
	BOOL GetHardDecode();

public:

	//添加RTSP HWND
	void AddRTSPHWND(HWND h);

	//添加RTSP HWND
	void AddRTSPHWND(HWND h, CString szRSTPAddr);

	//设置RTSP HWND RTSP地址
	void SetRTSPHWNDRTSPAddr(HWND h, CString szRSTPAddr);

	//设置RTSP HWND 背景颜色
	void SetRTSPHWNDBGColor(HWND h, Uint8 r, Uint8 g, Uint8 b);

	//删除RTSP HWND
	void DeleteRTSPHWND(HWND h);

	//添加MultiVideoWindow
	XMultiVideoWindow* AddMultiVideoWindow(HWND h);

	//添加MultiVideoWindow
	XMultiVideoWindow* AddMultiVideoWindow(HWND h, Uint8 g, Uint8 b, Uint8 a);

	//调整RTSP HWND区域大小
	void AdjustRTSPHWNDSize(HWND h, int nWidth, int nHeight);

	//设置RTSP HWND文字
	void SetRTSPHWNDText(HWND h, CString szText);

	//设置RTSP HWND文字颜色
	void SetRTSPHWNDTextColor(HWND h, Uint8 r, Uint8 g, Uint8 b);

	//设置RTSP HWND文字大小
	void SetRTSPHWNDTextSize(HWND h, int n);

	//设置RTSP HWND文字滚动
	void SetRTSPHWNDTextScrollRect(HWND h, int nLeft, int nTop, int nRight);

	//设置RTSP HWND文字滚动时间和步进
	void SetRTSPHWNDTextScrollTimeAndStep(HWND h, int nDistanceTime, int nStep);

	//调整
	void AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth, int nHeight);

public:

	//设置字体路径
	void SetFontPath(CString szFontPath);

	//获取文字Texture
	void CreateTextureOfText(SDL_Renderer* pRenderer, CString szText, int nTextSize, 
		SDL_Color color, SDL_Texture*& pTexture, int& nWidth, int& nHeight);

	//获取文字Surface
	SDL_Surface* CreateSurfaceOfText(CString szText, int nTextSize, SDL_Color color);

public:

	//绘制RTSP视频框
	void Display_rtsphwnd();

	//绘制视频墙
	void Display_multiVideoWindow();

private:

	//初始化数据
	void InitData();

	//退出
	void Quit();

	void ClearMapRTSP();

	void ClearVecRTSPHWND();

	void ClearVecMultiVideoWindow();

	//停止所有RTSP运行
	void StopAllRTSPRunning();

	//添加RTSP地址
	void AddRTSPAddr(CString szRTSPAddr,int nCount);

	//添加RTSP地址显示个数
	void AddRTSPAddrShowCount(CString szRTSPAddr);

	//设置RTSP地址显示个数
	void SetRTSPAddrShowCount(CString szRTSPAddr, int n);

	//添加RTSP地址显示个数
	void DeleteRTSPAddrShowCount(CString szRTSPAddr);

	//获取RTSPAddr显示个数
	unsigned int GetCount(MAP_RTSPADDRSHOWCOUNT& MapCount, CString szRTSPAddr);

	//获取RTSP HWND
	XRTSPHWND* GetRTSPHWND(HWND h);

	//转换数据到UTF8
	void ChangeDataToUTF8(CString szFontPath, char* pUTF8Data);

	//开始主线程
	BOOL BeginMainThread();

	//停止主线程
	void StopMainThread();

	//关闭主线程Event
	void CloseMainThreadEvent();

private:

	MAP_RTSP m_MapRTSP;

	VEC_RTSPHWND m_VecRTSPHWND;

	VEC_MULTIVIDEOWINDOW m_VecMultiVideoWindow;

public:

	CRITICAL_SECTION m_CSRTSP;

	CRITICAL_SECTION m_CSRTSPHWND;

	CRITICAL_SECTION m_CSRTSPADDRSHOWCOUNT;

	CRITICAL_SECTION m_CSMultiVideoWindow;

	HANDLE m_MainThreadEvent;

	BOOL m_Running;

	BOOL m_HardDecode;

	BOOL m_TCP;

	//字体文件路径
	char m_FontPath[MAX_PATH];

	//是否设置了字体文件路径
	BOOL m_SetFontPath;
};

