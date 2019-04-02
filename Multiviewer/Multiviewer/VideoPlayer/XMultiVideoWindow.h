#pragma once

#include "XConstantIM.h"
#include "videoinc.h"
#include "VideoPlayerConstant.h"

class XMultiVideoWindowFrames;
class XVideoPlayer;
class XMultiVideoWindowFrame;
class XBaseScreenManage;
class XScreenManage;
class XScreenDataInfo;

class XMultiVideoWindow
{
public:
	XMultiVideoWindow(void);
	~XMultiVideoWindow(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	XVideoPlayer* GetVideoPlayer();

	BOOL CreateSDLWindow();

	BOOL CreateSDLRenderer();

	BOOL GetCreateSDLWindow();

	//获取是否创建SDLRenderer
	BOOL GetCreateSDLRenderer();

	HWND GetHWND();

	void SetHWND(HWND h);

	void InitFont();

	//设置边框
	void SetFrame(int nRow, int nColumn);

	//绘制
	void Draw();

	//////////////////////////////////////////////////////////////////////////
	void SetMultiScale(float f);

	void SetFramesCountH(int n);

	void SetFramesCountV(int n);

	void SetFramesResulationH(int n);

	void SetFramesResulationV(int n);

	void SetFramesRightResulationH(int n);

	void SetFramesBottomResulationV(int n);

	void SetFrameSelectByGroupID(unsigned int nGroupID);
	//////////////////////////////////////////////////////////////////////////
	//用于获取视图区域大小（以上函数暂时不用）
	void SetMapRowInfo(MAP_ROWINFO& MapRowInfo);
	void SetMapColInfo(MAP_COLINFO& MapColInfo);
	//////////////////////////////////////////////////////////////////////////
	//添加Frame
	XMultiVideoWindowFrame* AddFrame(int nScreenIndex, CString szRTSPAddr, RECTF rFrame, 
		RECTF rImage, BOOL bShow = TRUE);

	//添加Frames
	XMultiVideoWindowFrames* AddFrames(int nScreenIndex,int nBoardIndex,RECTF rScreenRect,int nPaneNum,BOOL bIsTwoScreen);

	//获取信号
	XMultiVideoWindowFrame* GetFrame(int nScreenIndex,unsigned int nSignalID);

	//设置Frame
	void SetFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, RECTF rFrame, RECTF rImage);

	//设置Frame
	void SetFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, RECTF rFrame);

	//设置Frame
	void SetFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, CString szRTSPAddr);

	//设置Frame
	void SetFrameID(int nScreenIndex,XMultiVideoWindowFrame* pFrame,unsigned int nFrameID);

	//设置Frame
	void SetFrameGroupID(int nScreenIndex,XMultiVideoWindowFrame* pFrame,unsigned int nFrameGroupID);

	//设置frame是否为高清
	void SetFrameIsUltra(int nScreenIndex,XMultiVideoWindowFrame* pFrame,BOOL b);

	//设置Frame索引
	void SetFrameIndex(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nIndex);

	//设置高清序号
	void SetFrameUltraIndex(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nUltraIndex);

	//设置Frame备注
	void SetFrameAnotherName(int nScreenIndex,XMultiVideoWindowFrame* pFrame,CString szAnotherName);

	//设置Frame Image
	void SetFrameImage(int nScreenIndex, XMultiVideoWindowFrame* pFrame, RECTF rImage);

	//设置Frame文字
	void SetFrameText(int nScreenIndex, XMultiVideoWindowFrame* pFrame, CString text);

	//设置Frame文字
	void SetFrameText(int nScreenIndex, XMultiVideoWindowFrame* pFrame, COLORREF nTextColor, int nTextSize);

	//设置Frames文字
	void SetFramesText(int nScreenIndex,CString szText,int ntextSize);

	//删除Frame
	void DeleteFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame);

	//删除屏幕Frame
	void DeleteFrame(int nScreenIndex);

	//显示或隐藏Frame
	void ShowFrame(int nScreenIndex, XMultiVideoWindowFrame* pFrame, BOOL bShow);

	//显示或隐藏Frame
	void ShowFrame(int nScreenIndex, unsigned int nGroupID, BOOL bShow);

	//设置Frame置顶
	void SetFrameTop(int nScreenIndex, XMultiVideoWindowFrame* pFrame);

	//设置Frame置顶
	void SetFrameTopByGroupID(int nScreenIndex,unsigned int nGroupID);

	//设置Frame置底
	void SetFrameBottom(int nScreenIndex,XMultiVideoWindowFrame* pFrame);

	//设置Frame置底
	void SetFrameBottomByGroupID(int nScreenIndex,unsigned int nGroupID);

	//设置Frame上移
	void SetFrameUp(int nScreenIndex, XMultiVideoWindowFrame* pFrame);

	//设置Frame上移
	void SetFrameUpByGroupID(int nScreenIndex, unsigned int nGroupID);

	//设置Frame下移
	void SetFrameDown(int nScreenIndex, XMultiVideoWindowFrame* pFrame);

	//设置Frame下移
	void SetFrameDownByGroupID(int nScreenIndex, unsigned int nGroupID);

	//设置Frame层次
	void SetFrameLevel(int nScreenIndex,XMultiVideoWindowFrame* pFrame,int nLevel);

	//设置屏幕类型
	void SetScreenModel(int n);

	//删除所有Frames
	//void DeleteAllFrames();

	//删除所有Frame
	void DeleteAllFrame();

	//设置Frames返回序号
	void SetFramesReIndex(int nScreenIndex,int nIndex);

	//设置Frames返回数据长度
	void SetFramesReDateLen(int nScreenIndex,int nDataLen);

	//设置frames返回状态
	void SetFramesReStatus(int nScreenIndex,int nStatus);

	//设置Frames返回分辨率
	void SetFramesReResulationH(int nScreenIndex,int nResulationH);

	//设置Frames返回分辨率
	void SetFramesReResulationV(int nScreenIndex,int nResulationV);

	//设置Frames返回分辨率序号
	void SetFramesReResulationIndex(int nScreenIndex,int nIndex);

	//设置Frames返回刷新率
	void SetFramesReRefreash(int nScreenIndex,int nRefreash);

	//冒泡排序Frame
	void SortFrame(int nScreenIndex);

	//设置背景图片
	void SetBGImage(CString szPath);

	//设置背景颜色
	void SetBGColor(Uint8 r, Uint8 g, Uint8 b);

	//设置分隔线颜色
	void SetLineColor(Uint8 r, Uint8 g, Uint8 b);

	//删除背景图片
	void DeleteBGImage();

	//设置重置视频显示
	void SetResetVideoShow(BOOL b);

	//获取重置视频显示
	BOOL GetResetVideoShow();

	void ResetVideoShow();

	SDL_Renderer* GetRenderer();

	void SetMushHardCode(BOOL b);

	//获取Frames集合
	MAP_MULTIVIDEOWINDOWFRAMES& GetMapFrames();

	void ClearVecFrames();

	BOOL IsHaveDevice(int nIndex);

	CSize ViewGetSize();

	void SetIsMainMultiVideo(BOOL b);

	SDL_Rect GetInterRectByGroupID(unsigned int nGroupID);

	CString GetAnotherNameByIndex(int nIndex);

	CString GetShowText(CString szName,int nIndex);

	void SetIsDragFrame(BOOL b);

	void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName);

	void GetVecIndexByFrameGroupID(unsigned int nFrameGroupID,VEC_NUM& VecIndex);

	//清楚屏幕行列信息
	void ClearRowInfo();

	void ClearColInfo();


private:

	
	//清除数据
	void ClearData();

	//绘制背景颜色
	void DrawBGColor();

	void DrawFrames();

	void DrawFrame();

	void DrawRect(RECTF& rect);

	void DrawFrame(XMultiVideoWindowFrames* pFrames);

	//获取预览屏幕
	XMultiVideoWindowFrames* GetFrames(int nScreenIndex);

	void DrawBGImage();

	SDL_Texture* GetImageTexture(SDL_Renderer *pRenderer, char *szFile);

	void ClearTextureBGImage();

	void ClearRenderer();

	void ClearMapFramesTexture();

	void ReloadBGImage();

	void SetFrameDraw(XMultiVideoWindowFrames* pFrames);

	BOOL DecideRectInVecRect(VEC_RECT& VecRect, CRect& rect);

	void CreateTextureText();

	void ClearTextureText();

	void SetText(CString text);

	BOOL GetCreateTextureText();

	SDL_Texture* GetTextureText();

public:

	XVideoPlayer* m_VideoPlayer;

	//XBaseScreenManage* m_pManage;

	//句柄
	HWND m_HWND;

	//是否创建Window
	BOOL m_CreateWindow;

	SDL_Window* m_window;

	SDL_Renderer* m_renderer;

	//是否创建renderer
	BOOL m_CreateRender;

	int m_Row;

	int m_Column;

	CRITICAL_SECTION m_CS;

	CRITICAL_SECTION m_CSBGImage;

	SDL_Texture* m_textureBGImage;

	SDL_Texture* m_textureText;

	CString m_szBGImagePath;

	MAP_MULTIVIDEOWINDOWFRAMES m_MapFrames;

	BOOL m_bResetVideoShow;

	//背景颜色
	SDL_Color m_ColorBG;

	//分隔线颜色
	SDL_Color m_ColorLine;

	//文字颜色
	SDL_Color m_TextColor;

	//是否必需硬解
	BOOL m_MushHardCode;

	//纹理宽度
	int m_nTextureTextWidth;

	//纹理高度
	int m_nTextureTextHeight;

	//屏幕信息集合
	VEC_SCREENDATAINFO m_VecScreenInfo;

	//原点偏移
	int m_nOrgX;

	int m_nOrgY;

	//屏幕类型
	int m_nScreenModel;

	float m_dwScale;

	//水平个数
	int m_nFramesCountH;

	//垂直个数
	int m_nFramesCountV;

	//水平分辨率
	int m_nFramesResolutionH;

	//垂直分辨率
	int m_nFramesResolutionV;

	int m_nRightResulationH;

	int m_nBottomResulationV;

	BOOL m_bIsMainMultiVideo;

private:

	//文字颜色
	SDL_Color m_ColorText;

	//文字
	CString m_szText;

	//文字大小
	int m_nTextSize;

	//是否创建文字
	BOOL m_CreateTextureText;

	BOOL m_DrawText;

	BOOL m_bIsDragFrame;

	SDL_Rect m_TempRectImage;

	MAP_FRAMEID m_MapFrameID;
	
	MAP_FRAMECOLINFO m_MapColInfo;

	MAP_FRAMEROWINFO m_MapRowInfo;

};