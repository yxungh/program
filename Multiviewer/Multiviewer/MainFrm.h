// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "XRibbonBar.h"
#include "XDelegateView.h"
#include "XDelegateInternalManage.h"

class XBaseInternalManage;

class CMainFrame : public CMDIFrameWndEx, XDelegateView, XDelegateInternalManage
{
	
public: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual BOOL OnShowPopupMenu (CMFCPopupMenu* pMenuPopup);

	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);

	virtual BOOL OnCloseDockingPane(CDockablePane* );

	virtual BOOL PreTranslateMessage(MSG* pMsg);


// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;

// 生成的消息映射函数
protected:
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnAddDocument(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnNewScene(WPARAM wParam,LPARAM lParam);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnUDP(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnComboLanguage();
	afx_msg void OnComboScale();
	afx_msg void OnComboView();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnOpenNet();
	afx_msg void OnBtnCloseNet();
	afx_msg void OnBtnSaveScence();
	afx_msg void OnBtnOpenScence();
	afx_msg void OnBtnDeleteScence();
	afx_msg void OnBtnScreenMove();
	afx_msg void OnBtnTimedPolling();
	afx_msg void OnBtnDeleteAllSignal();
	afx_msg void OnBtnSetScreenResulation();
	afx_msg void OnBtnPan();
	afx_msg void OnBtnChip();
	afx_msg void OnBtnNewView();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnRunOldOrder();
	afx_msg void OnBtnTemperature();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnBtnUserManage();
	//afx_msg void OnBtnPowerManage();
	afx_msg void OnEditDeviceIP();
	afx_msg void OnEditDevicePort();
	afx_msg void OnEditInputCount();
	afx_msg void OnEditOutputCountH();
	afx_msg void OnEditOutputCountV();
	afx_msg void OnUpdateBtnOpenNet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnCloseNet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnLogin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnLogout(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnUserManage(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateBtnPowerManage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSaveScence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnOpenScence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnDeleteScence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnScreenMove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnTimedPolling(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSetScreenResulation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnDeleteAllSignal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditInputCount(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditOutputCountH(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditOutputCountV(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDeviceIP(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDevicePort(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnRunOldOrder(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnPan(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnChip(CCmdUI *pCmdUI);
	afx_msg void OnUpdataBtnNewView(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnPreview(CCmdUI* pCmdUI);
	afx_msg void OnScreenCloseSignal();
	afx_msg void OnScreenSeparate();
	afx_msg void OnScreenNoSeparate();
	afx_msg void OnBtnChangeScreen();
	afx_msg void OnScreenAttribute();
	afx_msg void OnBtnSetSignalTop();
	afx_msg void OnBtnSetSignalBottom();
	afx_msg void OnBtnSetSignalShiftUp();
	afx_msg void OnBtnSetSignalShiftDown();
	afx_msg void OnBtnChangeInput();
	afx_msg void OnBtnExpandSignal();
	afx_msg void OnBtnMenuScreenSet();
	afx_msg void OnBtnMenuSaveScence();

	afx_msg void OnSplitNetSet();
	afx_msg void OnSplitBitRate();

	afx_msg void OnBtnNormal();
	afx_msg void OnBtnFull();
	afx_msg void OnBtnFour();
	afx_msg void OnBtnInter();
	afx_msg void OnUpDateBtnNormal(CCmdUI* pCmdUI);
	afx_msg void OnUpDateBtnFull(CCmdUI* pCmdUI);
	afx_msg void OnUpDateBtnFour(CCmdUI* pCmdUI);
	afx_msg void OnUpDateBtnInter(CCmdUI* pCmdUI);

	afx_msg void OnBtnTipModel();
	afx_msg void OnUpDateBtnTipModel(CCmdUI* pCmdUI);
	afx_msg void OnBtnUpModel();
	afx_msg void OnUpDateBtnUpModel(CCmdUI* pCmdUI);
	afx_msg void OnBtnDownModel();
	afx_msg void OnUpDateBtnDownModel(CCmdUI* pCmdUI);
	afx_msg void OnBtnCopyModal();
	afx_msg void OnUpDateBtnCopy(CCmdUI* pCmdUI);

	afx_msg void OnBtnSaveAllScene();
	afx_msg void OnUpDateBtnSaveAllScene(CCmdUI* pCmdUI);

	afx_msg void OnBtnSaveSingleScene();
	afx_msg void OnUpDateSaveSingleScene(CCmdUI* pCmdUI);

	

	afx_msg void OnScreenResulationOfMatrix();
	afx_msg LRESULT OnAfxWmOnchangeActiveTab(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSetRowDpi();
	afx_msg void OnSetColDpi();


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	//初始化管理
	void InitManage();

	//初始化Pane
	void InitPane();

	//清除
	void Clear();

	XBaseInternalManage* GetInterManage();

	void ShowMenu(CPoint& point);

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
		int noffsetY);

	//视图获取大小
	virtual CSize ViewGetSize();

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图鼠标离开
	virtual void ViewMouseLeave();

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar);

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
		CRect& rect, int noffsetX, int noffsetY);

	virtual void ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

public:

	//获取CWnd
	virtual CWnd* GetCWND();

	//显示消息对话框
	virtual int MessageBox(CString szText, CString szCaption, UINT uType);

	//重设视图大小
	virtual void ResetViewSize();

	//刷新视图
	virtual void InvalidateView();

	//获取窗口句柄
	virtual HWND GetHWND();

	//获取视图
	virtual CView* GetView();

private:

	//开始定时器
	void BeginTimer();

private:

	//核心管理
	XBaseInternalManage* m_pInternalManage;

	BOOL m_bIsReady;

	CMFCTabCtrl* m_pTabCtrl;
};


