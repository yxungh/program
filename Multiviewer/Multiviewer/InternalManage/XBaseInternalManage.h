#pragma once

#include "XConstantIM.h"

class XDelegateInternalManage;


class XBaseInternalManage
{
public:
	XBaseInternalManage(void);
	virtual ~XBaseInternalManage(void);

public:

	//初始化
	virtual void Init() = 0;

	//程序关闭
	virtual BOOL AppClose() = 0;

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type) = 0;

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI) = 0;

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
		int noffsetY) = 0;

	//视图获取大小
	virtual CSize ViewGetSize() = 0;

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图鼠标离开
	virtual void ViewMouseLeave() = 0;

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar) = 0;

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
		CRect& rect, int noffsetX, int noffsetY) = 0;

	virtual void ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY)=0;

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam, LPARAM lParam) = 0;

	//初始化Pane
	virtual void InitPane() = 0;

	virtual void AddDocument() = 0; 

	virtual void SetIsFirstTime(BOOL IsFirstTime)=0;

	virtual BOOL GetIsFirstTime()=0;

	virtual void ShowMenu(CPoint& point)=0;

	virtual void SetActiveDockPane()=0;

	virtual void CloseActivePane()=0;

	virtual BOOL SetTabCtrlDbCLick(POINT point)=0;

	virtual BOOL SetViewTabBarDbClick(POINT point)=0;

	virtual void SetTabCtrlCLick(POINT point)=0;


public:

	//设置委托
	void SetDelegate(XDelegateInternalManage* p);

protected:

	//委托
	XDelegateInternalManage* m_pDelegate;
};

