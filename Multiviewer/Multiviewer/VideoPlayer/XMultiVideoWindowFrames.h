#pragma once

#include "XConstantIM.h"
#include "VideoPlayerConstant.h"

class XMultiVideoWindow;
class XVideoPlayer;

class XMultiVideoWindowFrames
{
public:
	XMultiVideoWindowFrames(void);
	~XMultiVideoWindowFrames(void);

public:

	void SetMultiVideoWindow(XMultiVideoWindow* p);

	XVideoPlayer* GetVideoPlayer();

	SDL_Renderer* GetRenderer();


	//屏幕序号
	int GetScreenIndex();
	void SetScreenIndex(int n);

	//板卡序号
	int GetBoardIndex();
	void SetBoardIndex(int n);

	//区域
	RECTF GetScreenRect();
	void SetScreenRect(RECTF rect);

	//num Ofscreen
	int GetPaneNum();
	void SetPaneNum(int n);

	//是否两路
	BOOL GetIsTwoScreen();
	void SetIsTwoScreen(BOOL b);

	void SetFrameSelectByGroupID(unsigned int nGroupID);

	//获取Frame集合
	VEC_MULTIVIDEOWINDOWFRAME& GetVecFrame();

	//添加Frame
	XMultiVideoWindowFrame* AddFrame(CString szRTSPAddr, RECTF rFrame, RECTF rImage, 
		BOOL bShow);

	//获取Frame
	XMultiVideoWindowFrame* GetFrame(unsigned int nSignalID);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame, RECTF rFrame, RECTF rImage);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame, RECTF rFrame);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame, CString szRTSPAddr);

	//设置Frame
	void SetFrameID(XMultiVideoWindowFrame* pFrame,unsigned int nFrameID);

	//设置Frame
	void SetFrameGroupID(XMultiVideoWindowFrame* pFrame,unsigned int nFrameGroupID);

	//设置Frame是否高清
	void SetFrameIsUltra(XMultiVideoWindowFrame* pFrame,BOOL b);

	//设置Frame索引
	void SetFrameIndex(XMultiVideoWindowFrame* pFrame,int nFrameIndex);

	//设置高清序号
	void SetFrameUltraIndex(XMultiVideoWindowFrame* pFrame,int nUltraFrameIndex);

	//设置Frame备注
	void SetFrameAnotherName(XMultiVideoWindowFrame* pFrame,CString szAnotherName);

	//设置Frame文字
	void SetFrameText(XMultiVideoWindowFrame* pFrame, CString text);

	//设置Frame文字
	void SetFrameText(XMultiVideoWindowFrame* pFrame, COLORREF nTextColor, int nTextSize);

	//设置Frames文字
	void SetFramesText(CString szText,int nTextSize);

	//设置Frame Image
	void SetFrameImage(XMultiVideoWindowFrame* pFrame, RECTF rImage);

	//删除Frame
	void DeleteFrame(XMultiVideoWindowFrame* pFrame);

	//显示或隐藏Frame
	void ShowFrame(XMultiVideoWindowFrame* pFrame, BOOL bShow);

	//显示或隐藏Frame
	void ShowFrame(unsigned int nGroup, BOOL bShow);

	//设置Frame置顶
	void SetFrameTop(XMultiVideoWindowFrame* pFrame);
	void SetFrameTopByGroupID(unsigned int nGroupID);

	//设置Frame置底
	void SetFrameBottom(XMultiVideoWindowFrame* pFrame);
	void SetFrameBottomByGroupID(unsigned int nGroupID);

	//设置Frame上移
	void SetFrameUp(XMultiVideoWindowFrame* pFrame);
	void SetFrameUpByGroupID(unsigned int nGroupID);

	//设置Frame下移
	void SetFrameDown(XMultiVideoWindowFrame* pFrame);
	void SetFrameDownByGroupID(unsigned int nGroupID);

	//设置Frame层次
	void SetFrameLevel(XMultiVideoWindowFrame* pFrame,int nLevel);

	//删除所有Frame
	void DeleteAllFrame();

	//排序Frame
	void SortFrame();

	void ClearVecFrame();

public:

	void CreateScreenText(float f=1.0f);

	void ClearScreenText();

	BOOL GetCreateTextureText();

public:

	void SetReDataLen(int n);

	void SetReScreenIndex(int n);

	void SetReStatus(int n);

	void SetReScreenHdpi(int n);

	void SetReScreenVdpi(int n);

	void SetReDpiIndex(int n);

	void SetReRefresh(int n);

	int GeteDataLen();

	int GetReScreenIndex();

	int GetReStatus();

	int GetReScreenHdpi();

	int GetReScreenVdpi();

	int GetReDpiIndex();

	int GetReRefresh();

public:

	XMultiVideoWindow* m_MultiVideoWindow;

	SDL_Texture* m_textureText;

	int m_nScreenIndex;

	int m_nBoardIndex;

	RECTF m_ScreenRect;

	int m_nPaneNum;

	BOOL m_bIsTwoScreen;

	VEC_MULTIVIDEOWINDOWFRAME m_VecFrame;

	int GetTextureTextWidth();

	int GetTextureTextHeight();

	SDL_Texture* GetTextureText();

private:

	CString m_szText;

	int m_nTextSize;

	SDL_Color m_ColorText;

	//文字宽度
	int m_nTextureTextWidth;

	//文字高度
	int m_nTextureTextHeight;

	//是否创建文字
	BOOL m_CreateTextureText;

private:
	//返回数据

	int m_nReScreenIndex;

	int m_ReDataLen;

	int m_ReStatus;

	int m_ReScreenHdpi;

	int m_ReScreenVdpi;

	int m_ReDpiIndex;

	int m_ReRefresh;

};