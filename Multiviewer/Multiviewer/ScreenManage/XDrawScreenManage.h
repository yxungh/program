#pragma once

#include "XConstantIM.h"
#include "XDragInfo.h"

class XScreenManage;
class XScreen;
class XSignal;

class XDrawScreenManage
{
private:
	XDrawScreenManage(void);
	~XDrawScreenManage(void);

public:

	//视图绘制
	static void ViewDraw(CDC* pDC,CRect rect, int noffsetX, 
		int noffsetY, XScreenManage* pManage);

private:

	//绘制
	static void Draw(Graphics& graphics, XScreenManage* pManage);

	//绘制屏幕集合
	static void DrawVecScreen(Graphics& graphics, XScreenManage* pManage);

	//绘制信号移动窗口
	static void DrawDragRect(Graphics& graphics, XScreenManage* pManage);

private:

	XDragInfo m_DragInfo;
};

