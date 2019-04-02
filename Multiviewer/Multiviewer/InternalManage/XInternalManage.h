 #pragma once

#include "XBaseInternalManage.h"
#include "XDelegateRibbonBarManage.h"
#include "XDelegateTranslationManage.h"
#include "XDelegateMessageBoxDlg.h"
#include "XDelegateScreenManage.h"
#include "XDelegateInputSignalPane.h"
#include "XDelegateNetManage.h"
#include "XDelegateIniManage.h"
#include "XDelegateDataManage.h"
#include "XDelegateAboutDlg.h"
#include "XDelegateUDPWatchPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "XDelegateUserManage.h"
#include "XDelegateNewViewDlg.h"
#include "XVideoPlayer.h"
#include "XDelegateScenePane.h"
#include "XDelegatePreviewChild.h"
#include "XDelegateSetPreviewBoard.h"
#include "XBoardNetInfo.h"
#include "XBitRateInfo.h"
#include "XSaveAllScence.h"


class XBaseRibbonBarManage;
class XBaseTranslationManage;
class XBaseScreenManage;
class XBasePathManage;
class XBaseNetManage;
class XInputSignalPane;
class XBaseChildManage;
class XIniManage;
class XDataManage;
class XUDPWatchPane;
class XVideoPreviewPane;
class XUserManage;
class XRTSPInfoDragWnd;
class XScenePane;
class CMultiviewerView;
class XMultiVideoWindow;
class XSetPreviewBoard;
class XMyTabCtrl;


class XInternalManage : public XBaseInternalManage, 
	XDelegateRibbonBarManage, 
	XDelegateTranslationManage, 
	XDelegateMessageBoxDlg,
	XDelegateScreenManage,
	XDelegateInputSignalPane,
	XDelegateNetManage,
	XDelegateIniManage,
	XDelegateDataManage,
	XDelegateAboutDlg,
	XDelegateUDPWatchPane,
	XDelegateVideoPreviewPane,
	XDelegateUserManage,
	XDelegateNewViewDlg,
	XDelegateScenePane,
	XDelegatePreviewChild,
	XDelegateSetPreviewBoard
{
public:
	XInternalManage(void);
	~XInternalManage(void);

	//初始化
	virtual void Init();

	virtual BOOL AppClose();

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl);

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type);

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl);

	//重载界面
	virtual void ReloadInterface();

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(CString szName);

	//显示消息对话框
	virtual int MessageBox(CString szText, CString szCaption, UINT uType);

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

	//获取场景文件路径
	virtual CString GetSceneFilePath(int nSceneIndex, CString szSceneName);

	virtual CString GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex);

	//获取场景文件夹路径
	virtual CString GetSceneFolderPath();

	//重设视图大小
	virtual void ResetViewSize();

	//刷新视图
	virtual void InvalidateView();

	//获取窗口句柄
	virtual HWND GetHWND();

	//操作
	virtual void Operate(OPERATETYPE type, void* pData);

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type);

	//获取CWnd
	virtual CWnd* GetCWND();

	//获取缩放比例
	virtual float GetScale();

	//设置缩放比例
	virtual void SetScale(float f);

	//获取设备IP
	virtual CString GetDeviceIP();

	//获取设备端口
	virtual int GetDevicePort();

	//设置设备IP
	virtual void SetDeviceIP(CString str);

	//设置设备端口号
	virtual void SetDevicePort(int n);

	//获取语言类型
	virtual CString GetLanguagetype();

	//设置语言类型
	virtual void SetLanguagetype(CString type);

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY);

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

	//视图左键双击
	virtual void ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//发送数据
	virtual BOOL SendData(char* pData, int nDataLen);

	//创建拖动窗口
	virtual XDragWnd* CreateDragWnd(XDragInfo* pInfo);

	//创建预览拖动窗口
	virtual XRTSPInfoDragWnd* CreatePreviewDragWnd(XRTSPInfo* pInfo);

	//拖动信息-输入信号
	virtual void DragInfo(CRect rc,CPoint point,XDragInfo* pInfo);

	//预览拖动信息-输入信号
	virtual void DragInfo(CRect rc,XRTSPInfo* pInfo);

	//获取视图
	virtual CView* GetView();

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam, LPARAM lParam);

	//处理UDP数据
	virtual void HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);

	//获取网络状态
	virtual BOOL GetNetState();

	//初始化Pane
	virtual void InitPane();

	//添加RTSP
	virtual void AddRTSP(CString szRTSPAddr);

	//添加RTSP
	virtual void AddRTSP(CString szRTSPAddr,int nCount);

	//计数增加
	virtual void SetRTSPCountPlus(CString szRTSPAddr);

	//RTSP计数减少
	virtual void SetRTSPCountLess(CString szRTSPAddr);

	//添加RTSP HWND
	virtual void AddRTSPHWND(HWND h);

	//设置RTSP HWND RTSP地址
	virtual void SetRTSPHWNDRTSPAddr(HWND h, CString szRSTPAddr);

	//调整RTSP HWND区域大小
	virtual void AdjustRTSPHWNDSize(HWND h, int nWidth, int nHeight);

	//添加视频墙
	virtual XMultiVideoWindow* AddMultiVideoWindow(HWND h);

	//删除RTSP
	virtual void DeleteRTSP(CString szRTSPAddr);

	//获取输出个数
	virtual int GetOutputCount();

	//获取输入个数
	virtual int GetInputCount();

	//设置输入信号个数
	virtual void SetInputCount(int n);

	//是否登录
	virtual BOOL IsLogin();

	//获取用户节点权限
	virtual BOOL GetUserNodePower(int nInputIndex, int nOutputIndex);

	//是否管理员用户
	virtual BOOL IsAdminUser();

	//重置输入数据（打开场景）
	virtual void ReSetInputData();

	//添加场景到树
	virtual HTREEITEM AddSceneToTree(int nSceneIndex,CString szSceneName,int nType,CString szSceneGroup);

	virtual void AddViewNameToScene(HTREEITEM item,CString szSceneName,int nIndex,CString szViewName);

	//获取输入信号集合
	virtual VEC_INPUTSIGNAL& GetVecInputSignal();

	//获取屏幕集合
	virtual VEC_SCREEN& GetVecScreen();

	//根据序号获取输入名称
	virtual CString GetInputNameByIndex(int nIndex);

	//根据序号获取input
	virtual XInputSignal* GetInputByIndex(int nIndex);

	//设置预览别名
	virtual void SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName);

	//打开场景
	virtual void OpenScene(CString szSceneName,int nSceneIndex,CString szViewName);

	//删除场景
	virtual void DeleteScene(int nSceneIndex);

	//设置osd
	virtual void SetOSD(XInputSignal* pInputSignal);

	//重置输入（scene）
	virtual void ResetDataBySceneInputCountChange();

	//获取是否为4K
	virtual void IsUltra(int nIndex);

	//設置是否爲第一次啓動
	virtual void SetIsFirstTime(BOOL IsFirstTime);

	//获取是否为第一次启动
	virtual BOOL GetIsFirstTime();

	//获取保存数据
	virtual XMenuScreenSetInfo* GetMenuScreenSetInfo();

	//判断changjingmingc
	virtual BOOL JudgeSceneName(CString szName);
	
	//显示菜单（标签页右键）
	virtual void ShowMenu(CPoint& point);

	//调整预览墙大小
	virtual void AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth,int nHight);

	//判断输入是否为4K
	virtual void JudgetInputIsultra(int nInputIndex);

	//设置RTSP加
	virtual void SetRTSPAddrCountPlus(CString szRTSPAddr);

	//设置RTSP减
	virtual void SetRTSPAddrCountLess(CString szRTSPAddr);

	//重置RTSP计数
	virtual void SetRTSPAddrCountReset(CString szRTSPAddr);

	//直接设置RTSP计数
	virtual void SetRTSPAddrCount(CString szRTSPAddr,int nCount);

	//根据RTSP获取屏幕信号的RTSP个数
	virtual int GetRTSPCountBySignal(CString szRTSP);

	//设置输入信号的RTSP地址，拖拽
	virtual void SetInputRTSPAddrByIndex(int nIndex,CString szRTSP);

	//设置屏幕中信号RTSP
	virtual void SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP);

	//设置输入信号信息
	virtual void SetInputParaByIndex(int nIndex,CString szIP,CString szUseName,CString szPassWd);

	//输入是否有信号
	virtual BOOL IsHaveSignal(int nIndex);

	//输入是否有板卡
	virtual BOOL IsHavePane(int nIndex);

	//设置预览墙缩放
	virtual void SetMultiScale(float f);

	//改变预览墙信号别名
	virtual void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName);

	//激活的预览面板
	virtual void SetActiveDockPane();

	//关闭预览面板
	virtual void CloseActivePane();

	//获取场景集合
	virtual MAP_SCENEGROUP& GetMapSceneGroup();

	//打开全部场景
	virtual void OpenAllScene(CString szSceneName,int nSceneIndex);

	//打开全部场景中的一个
	virtual void OpenOneSceneOfAll(CString szSceneName,int nSceneIndex,CString szViewName);

	//拷贝指令
	virtual void CopyOrderToShare(CString szSceneName,int nSceneIndex,CString szViewName);

	virtual void CopySingleOrderToShare(CString szSceneName,int nSceneIndex,CString szViewName);

	//获取屏幕管理个数
	virtual int GetVecBaseManageSize();

	//根据序号设置预览框中RTSP计数为1
	virtual void SetFrameRTSPCountByIndex(int nInputIndex);

	//获取权限提示语
	virtual CString GetNotice();

	//双击底部Tab标签
	virtual BOOL SetTabCtrlDbCLick(POINT point);

	//双击同步Tab标签
	virtual BOOL SetViewTabBarDbClick(POINT point);

	//单击底部Tab标签
	virtual void SetTabCtrlCLick(POINT point);

	//标签备注
	virtual MAP_TABLABLE& GetMapBottomTabLable();

	//获取屏幕管理类
	virtual VEC_BASESCREENMANAGE& GetVecBaseScreenManage();

	//设置选中信号信息
	virtual BOOL SetSelInputDataInfo();

	//获取拖拽信息
	virtual XDragInfo& GetDragInfo();

	virtual CString GetRTSPAddrFromPreviewPane(int nSignalIndex);

private:

	//初始化管理
	void InitManage();

	//初始化程序数据
	void InitAppData();

	//初始化输入信号
	void InitInputSignal();

	//初始化视频管理
	void InitVideoPlayer();

	//获取应用数据
	BOOL GetAppData();

	//获取应用数据
	void GetAppData(CArchive& arch);

	//保存应用数据
	BOOL SaveAppData();

	//保存应用数据
	void SaveAppData(CArchive& arch);

	//重置应用数据
	void ResetAppData();

	//获取标题名称
	CString GetTitle(CString szStr);

	//根据名称获取管理类
	XBaseChildManage* GetChildManage(CString szName);

	//创建拖动窗口
	void CreateDragWnd();

	//创建预览拖动窗口
	void CreatePreviewDragWnd();

	//显示关于对话框
	void ShowAboutDlg();

	//添加预览屏幕
	void AddFrames(XBaseScreenManage* pManage);

	//设置预览屏幕文字
	CString SetText(XScreen* pScreen);

	BOOL CheckSumNum(char* pData,int& nLen);

	unsigned short CheckNum(char *pData,int nLen);

	XBaseScreenManage* GetBaseScreenManageByViewName(CString szViewName);

	void GetAnotherNameByTabLable(CString szTabLable,CString& szName,CString& szAnotherName);

	CString GetLabelByTab(CString szLable);

	//清理所有输入RTSP信息
	void SetInputSignalPara();

public:

	//清除
	void Clear();

	//清除屏幕管理集合
	void ClearVecBaseScreenManage();

	//释放关闭的屏幕管理类
	void ClearTempBase();

	//清除预览面板
	void ClearVecPreviewPane();

	//清除预览面板缓存
	void ClearVecPreviewPaneTemp();

	void ClearMapSelectBoard();

	void ClearPreviewTemp();

	void ClearMapBottomTabLable();

public:

	VEC_BASESCREENMANAGE& GetBaseManage();

	MAP_SELECTBOARD& GetMapSelectBoard();

	VEC_VIDEOPREVIEWPANE& GetVecPreviewPane();

	MAP_PREVIEWTEMP& GetMapPreviewTemp();

	MAP_BOARDTYPE& GetMapBoardType();

	void SetNowScreenManage(XBaseScreenManage* p);

	void OperateOfNewView();

	void AddDocument(); 

	void AddDocument(XBaseScreenManage* pManage);

	CView* GetDocumentFrontView(CDocument* p);

	void CloseMDI(XBaseScreenManage* pManage);

	XUserManage* GetUserManage();

	XBoardNetInfo* GetBoardInfo();

	XBitRateInfo* GetBitRateInfo();

	void SetShowScreenManage();

	void CopySelectedBoardInfo(VEC_PREVIEWBOARD& VecBoard);

	void SetPreviewPane();

	void InitPreviewPane();

	void SetBaseTabCtr();

	void AddPreviewPane(XVideoPreviewPane* pPane);

	void PreviewPaneReloadInterface();

	void ScreenReloadInterface();

	void SaveSceneByCloseView();

	int GetScreenType();

public:

	void OperateOfSetPreviewBoard();

	void OperateOfSplitNetSet();

	void OpersteOdSplitBitRate();

	void OperateOfSaveAllScene();

	void OperateOfFirstView();

	void OperateOfReadPreviewNet(char *pData);

	void OperateOfReadPreviewBitRate(char* pData);

	void OperateOfReadSceneIndex(char* pData);


private:

	//RibbonBar管理
	XBaseRibbonBarManage* m_pRibbonBarManage;

	//翻译管理
	XBaseTranslationManage* m_pTranslationManage;

	//屏幕管理
	XBaseScreenManage* m_pNowScreenManage;

	//路径管理
	XBasePathManage* m_pPathManage;

	//输入信号面板
	XInputSignalPane* m_pInputSignalPane;

	//UDP监视面板
	XUDPWatchPane* m_pUDPWatchPane;

	//网络管理
	XBaseNetManage* m_pNetManage;

	//屏幕管理基类
	XBaseChildManage* m_pChildManage;

	//Ini管理类
	XIniManage* m_pIniManage;

	//数据管理
	XDataManage* m_pDataManage;

	//视频预览面板
	XVideoPreviewPane* m_VideoPreviewPane;

	//视频管理
	XVideoPlayer m_VideoPlayer;

	//用户管理
	XUserManage* m_pUserManage;

	//场景面板
	XScenePane* m_pScenePane;

private:
	
	//拖动窗口
	XDragWnd* m_DragWnd;

	//预览拖动窗口
	XRTSPInfoDragWnd* m_PreviewDragWnd;

	//预览卡窗口
	XSetPreviewBoard* m_SetPreviewBoardDlg;

	//预览卡网络信息
	XBoardNetInfo m_BoardInfo;

private:

	//选中视图名称
	CString m_SelectViewName;

	//视频墙
	XMultiVideoWindow* m_pMultiVideoWindow;
	
	XMultiVideoWindow* m_pDragInputMultiVideoWindow;

	XMultiVideoWindow* m_pDragPreviewMultiVideoWindow;

	BOOL m_bIsFirstTime;

private:

	//预览面板
	CTabbedPane* m_pTabbedBar;

	//预览面板标签页
	XMyTabCtrl* m_pTabCtrl;

	//CMFCTabCtrl* m_pTabCtrl;

	//视图Tabbar
	XMyTabCtrl* m_pViewTabCtrl;

	//预览面板类
	XVideoPreviewPane* m_pTemp;

	//预览卡码率信息
	XBitRateInfo m_BitRateInfo;

	//保存多个场景
	XSaveAllScence m_SaveAllSceneDlg;

private:

	//视图管理
	VEC_BASESCREENMANAGE m_VecBaseScreenManage;

	VEC_BASETEMP m_VecTemp;

	//预览面板
	VEC_VIDEOPREVIEWPANE m_VecVideoPreviewPane;

	//预览面板缓存
	VEC_VIDEOPREVIEWPANETEMP m_VecVideoPreviewPaneTemp;

	//所有预览卡信息
	MAP_SELECTBOARD m_MapSelectBoard;

	//预览卡槽位集合（防止重复）
	MAP_PREVIEWTEMP m_MapPreviewTemp;

	//底部标签备注
	MAP_TABLABLE m_MapBottomTabCtrLable;

};

