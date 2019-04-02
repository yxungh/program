#pragma once

#include "XConstantIM.h"

class XRTSP;
class XMultiVideoWindowFrames;

class XMultiVideoWindowFrame
{
public:
	XMultiVideoWindowFrame(void);
	~XMultiVideoWindowFrame(void);

public:

	void SetMultiVideoWindowFrames(XMultiVideoWindowFrames* p);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString s);

	void SetRect(RECTF r);

	SDL_Rect GetRect();

	void SetRectImage(RECTF r);

	RECTF& GetRectImage();

	BOOL CreateTexture(SDL_Renderer* renderer, XRTSP* pRTSP);

	void ClearTexture();

	SDL_Texture* GetTexture();

	SDL_Rect GetRectImageReal();

	BOOL GetSetRectImageReal();

	void SetRectImageReal();

	void Show(BOOL bShow);

	BOOL GetShow();

	unsigned int GetFrameID();

	void SetFrameID(unsigned int nID);

	unsigned int GetFrameGroupID();

	void SetFrameGroupID(unsigned int nGroupID);

	int GetFrameIndex();
	
	void SetFrameIndex(int n);

	int GetFrameUltraIndex();

	void SetFrameUltraIndex(int n);

	CString GetFrameAnotherName();

	void SetFrameAnotherName(CString szName);

	void SetFrameIsUltra(BOOL b);

	BOOL GetFrameIsUltra();

	void SetLevel(int n);

	int GetLevel();



public:

	XMultiVideoWindowFrames* m_MultiVideoWindowFrames;

	//RTSP地址
	CString m_RTSPAddr;

	//显示区域
	SDL_Rect m_Rect;

	//显示图像区域,按照1920*1088比例
	RECTF m_RectImage;

	//是否创建Texture
	BOOL m_CreateTexture;

	SDL_Texture* m_texture;

	int m_textureWidth;

	int m_textureHeight;

	//是否设置真实图像区域
	BOOL m_SetRectImageReal;

	//真实图像区域
	SDL_Rect m_RectImageReal;

	//显示状态
	BOOL m_Show;

	//是否绘制
	BOOL m_Draw;

public://文字

	void SetText(CString text);

	void SetText(COLORREF nTextColor, int nTextSize);

	BOOL GetCreateTextureText();

	void CreateTextureText();

	SDL_Texture* GetTextureText();

	int GetTextureTextWidth();

	int GetTextureTextHeight();

	void ClearTextureText();

public:

	inline void SetFrameSelected(BOOL b){m_bIsSelected=b;}

	inline BOOL GetFrameSelected(){return m_bIsSelected;}

private://文字

	//文字Texture
	SDL_Texture* m_textureText;

	//文字
	CString m_szText;

	//文字颜色
	SDL_Color m_ColorText;

	//文字大小
	int m_nTextSize;

	//是否创建文字
	BOOL m_CreateTextureText;

	//文字宽度
	int m_nTextureTextWidth;

	//文字高度
	int m_nTextureTextHeight;

	//FrameID
	unsigned int m_nFrameID;

	//Frame GroupID
	unsigned int m_nFrameGroupID;

	int m_nIndex;

	int m_nUltraIndex;

	CString m_szAnotherName;

	int m_nLevel;

	BOOL m_bIsUltra;

	BOOL m_bIsSelected;


};


