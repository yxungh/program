#pragma once

#include "XConstantIM.h"

class XScreenManage;
class XSignal;
class XInputSignal;

class XCalculateScreenManage
{
public:
	XCalculateScreenManage(void);
	~XCalculateScreenManage(void);

	//视图获取大小
	static CSize ViewGetSize(XScreenManage* pManage);

	//设置视图原点
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale, CDC& dc);

	//设置预览墙坐标原点
	static void SetPreviewOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale,CSize& orgSize);

	//还原缩放的点
	static void ReductionPoint(XScreenManage* pManage, CRect& rect, int noffsetX, int noffsetY, CPoint& srcPoint, POINTF& desPoint);

	//根据点获取屏幕
	static XScreen* GetScreenByPoint(XScreenManage* pManage, POINTF& point);

	//根据点获取信号
	static XSignal* GetSignalByPoint(XScreen* pScreen, POINTF& point);

	//根据信号位置类型获取信号区域
	static RECTF GetSignalRectBySignalPosType(XScreen*& pScreen, SIGNALPOSTYPE type);

	//判断点在信号区域
	static BOOL DecidePointInSignal(XScreenManage* pManage,XSignal*& pSignal, POINTF& point);

	//static BOOL DecidePointInScreen(XScreenManage* pManage,POINTF& point);

	//判断点在信号区域的位置类型
	static POSITIONTYPE DecidePointInSignalPosition(XScreenManage* pManage, RECTF& rect, POINTF& point);

	//根据位置类型获取鼠标类型
	static CURSORTYPE GetCursorTypeByPositionType(POSITIONTYPE type);

	//获取信号整个区域
	static RECTF GetRectBySignal(XScreenManage* pManage, unsigned int nSignalID);

	//获取所占屏幕总区域
	static RECTF GetRectByVecScreen(VEC_SCREEN& VecScreen);

	//移动信号
	static void MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size);

	//移动信号
	static void MoveSignalOfNew(RECTF& rect,SIZEF& size);

	//判断鼠标在视图区域
	static BOOL DecidePointInScreen(XScreenManage *pManage,POINTF& point);

	//根据ID获取信号
	static XSignal* GetSignalByID(XScreenManage *pManage,unsigned int ID);

	//根据序号获取信号
	static XInputSignal* GetSignalByIndex(XScreenManage *pManage,int nIndex);

	//浮点数四舍五入
	static int GetIntFromFloat(float fwData);

	//////////////////////////////////////////////////////////////////////////
	static RECTF GetInterRectByAllScreen(XScreenManage* pManage);
	



private:

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,
		CSize& size, float& dwScale, int& nOrgX, int& nOrgY);
};





