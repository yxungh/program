#pragma once
#include "XBtn.h"
#include "XConstantIM.h"

class XVideoPreviewPane;
 
class XVideoPreviewContain : public CWnd
{
	DECLARE_DYNAMIC(XVideoPreviewContain)

public:
	XVideoPreviewContain();
	virtual ~XVideoPreviewContain();

	virtual void PreSubclassWindow();

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	 
public:

	//初始化
	void Init();

	//调整垂直滚动条
	void AdjustScrollV();

	//调整水平滚动条
	void AdjustScrollH();

	//设置面板
	void SetPane(XVideoPreviewPane* p);


protected:

	//绘制
	void Draw(CDC* pDC, CRect rt);

private:

	BOOL m_bScrollTimerV;

	int m_nScrollPosV;

	int m_nScrollTimerV;

	int m_ScrollPosV;

	int m_nScrollHMin;

	int m_nScrollHMax;

private:

	BOOL m_bScrollTimerH;

	int m_nScrollPosH;

	int m_nScrollTimerH;

	int m_ScrollPosH;


protected:

	XVideoPreviewPane* m_Pane;

	//是否按下
	BOOL m_bDown;


};


