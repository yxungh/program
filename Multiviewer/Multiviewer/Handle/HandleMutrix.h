#pragma once

class XOSDInfo;
class XScreenMoveInfo;

class HandleMutrix
{
private:
	HandleMutrix(void);
	~HandleMutrix(void);

public:

	//设置OSD字模
	static BOOL SetOSDMutrix(CClientDC& dc, XOSDInfo* pOSDInfo, BOOL& bExceed);

	//设置滚动画面字模
	static BOOL SetScreenMoveMutrix(CClientDC& dc, XScreenMoveInfo* pMoveInfo, BOOL& bExceed);

private:

	//创建OSD字体
	static BOOL CreateOSDFont(XOSDInfo* pOSDInfo, CFont& font);

	//获取字符字模
	static BOOL GetTextMutrix(CClientDC& dc, GLYPHMETRICS& glyph, TCHAR c, 
		unsigned char*& pTextMutrix);

	//显示字符字模数据
	static void ShowTextMatrixData(TCHAR c, unsigned char* pTextMutrix, GLYPHMETRICS& glyph, 
		XOSDInfo* pOSDInfo);

	//设置OSD文字字模数据
	static int SetOSDTextMatrixData(XOSDInfo* pOSDInfo, int& nX, int& nY, 
		TCHAR c, TEXTMETRIC& tm, CClientDC& dc);

	//填充字模数据到OSD
	static int FillTextMatrixDataToOSD(XOSDInfo* pOSDInfo, int nX, int nY, 
		unsigned char* pTextMutrix, GLYPHMETRICS& glyph, TEXTMETRIC& tm);

	//***********************************
	//创建滚动画面字体
	static BOOL CreateScreenMoveFont(XScreenMoveInfo* pMoveInfo, CFont& font);

	//显示滚动画面字符字模数据
	static void ShowScreenMoveTextMatrixData(TCHAR c, unsigned char* pTextMutrix, GLYPHMETRICS& glyph, 
		XScreenMoveInfo* pMoveInfo);

	//设置滚动画面文字字模数据
	static int SetScreenMoveTextMatrixData(XScreenMoveInfo* pMoveInfo, int& nX, int& nY, 
		TCHAR c, TEXTMETRIC& tm, CClientDC& dc);

	//填充字模数据到滚动画面
	static int FillTextMatrixDataToScreenMove(XScreenMoveInfo* pMoveInfo, int nX, int nY, 
		unsigned char* pTextMutrix, GLYPHMETRICS& glyph, TEXTMETRIC& tm);

	//居中数据
	static void CenterMutrixData(XOSDInfo* pOSDInfo,int& nMaxX,int& nMaxY);

	//居中数据
	static void CenterMoveMutrixData(XScreenMoveInfo* pMoveInfo,int& nMaxX,int& nMaxY);

};

