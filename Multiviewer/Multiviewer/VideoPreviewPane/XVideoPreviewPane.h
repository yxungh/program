#pragma once

#include "XConstantIM.h"
#include "XVideoPreviewContain.h"
#include "ViewPreviewDlg.h"
#include "VideoPlayerConstant.h"

#define VIDEOPREVIEW_TEXTHEIGHT 20//文字大小

class XDelegateVideoPreviewPane;
class XRTSPInfo;
class XVideoPreviewInfo;
class XRTSPInfoDragWnd;
class XSelectInputDlg;
class XDragInfo;

// XVideoPreviewPane
class XVideoPreviewPane : public CDockablePane
{
	DECLARE_DYNAMIC(XVideoPreviewPane)
public:

	XVideoPreviewPane();
	virtual ~XVideoPreviewPane();

	virtual BOOL OnBeforeFloat(CRect& rectFloat, AFX_DOCK_METHOD dockMethod){return FALSE;}
	virtual BOOL CanFloat() const {return FALSE;}  
	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod = DM_UNKNOWN, bool bShow = true) { return FALSE; }
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateVideoPreviewPane* pDelegate);

	//重载界面
	void ReloadInterface();

	//重置数据
	void ResetData();

	//获取网络状态
	BOOL GetNetState();

	//发送数据
	BOOL SendData(char* pData, int nDataLen);

	//获取数据
	void GetData(CArchive& arch);

	//保存数据
	void SaveData(CArchive& arch);

	//操作
	void Operate(OPERATETYPE type, void* pData);

	//创建拖动窗口
	XRTSPInfoDragWnd* CreatePreviewDragWnd(XRTSPInfo* pInfo);

	//拖动信息
	void DragInfo(CRect rc,XRTSPInfo* pInfo);

	//拖拽
	BOOL DragInfoToFrame(CPoint point,XDragInfo* pInfo);

	//调整预览墙大小
	void AdjustMultiVideoWindowSize();

	//包括主预览墙以及窗口预览墙
	void AdjustMultiVideoWindowsSize();

	CString GetRTSPAddrFromPreviewPane(int nSignalIndex);
 
public:

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

private:

	BOOL CheckSumNum(char* pData,int nLen);

	unsigned short CheckNum(char *pData,int nLen);

public:

	//获取容器滚动高度
	int GetContainScrollHeight();

	//获取滚动宽度
	int GetContainScrollMax();

	//获取窗口左侧
	int GetFrameLeft();

	//获取窗口右侧
	int GetFrameRight();

	//获取字体
	CFont* GetFont();

	//获取委托
	XDelegateVideoPreviewPane* GetDelegate();

	//设置计数加
	void SetRTSPAddrCountPlus(CString szRTSPAddr);

	//设置计数减
	void SetRTSPAddrCountLess(CString szRTSPAddr);

	//重置计数
	void SetRTSPAddrCountReset(CString szRTSPAddr);

	//删除RTSP
	void DeleteRTSP(CString szRTSPAddr);

	//显示视频预览对话框
	void ShowViewPreviewDlg(CString szIP,CString szRTSPAddr,int nInputIndex,CString szUseName,CString szPassWd);

	//设置预览窗口别名
	void SetPreviewNameByAnotherName(int& nInputIndx,CString szAnotherName);

	//设置预览板卡网络集合
	void SetMapBoardNetInfo();

	//获取屏幕信号RTSP地址个数
	int GetRTSPCountBySignal(CString szRTSP);

	//设置输入RTSP地址
	void SetInputRTSPAddrByIndex(int nIndex,CString szRTSP=_T(""));

	//设置屏幕信号RTSP地址
	void SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP=_T(""));

	//设置输入IP
	void SetInputParaByIndex(int nInputIndex,CString szIP=_T(""),CString szUseName=_T(""),CString szPassWd=_T(""));

	//添加RTSP
	void AddRTSPAddr(CString szRTSP);

	//判断输入信号状态（4K,有无信号，有无板卡）
	void AdjustInputStatus(int nIndex,BOOL& bIsUltra,BOOL& bIsHaveSignal,BOOL& bIsHavePane);

	//区域四分（用于4K）
	void SetRectToFoure(RECTF rect,VEC_RECTF& VecRect);

	//根据IP生成RTSP
	void CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd,VEC_CSTRING& VecRTSPAddr);

	//根据子流地址获取主流地址
	CString GetMainRTSPBySubRTSP(CString szRTSPAddr);

	//根据序号设置FrameRTSP计数
	void SetFrameRTSPCountByIndex(int nInputIndex);

public:

	//获取预览框集合
	VEC_VIDEOPREVIEWFRAME& GetVecFrame();

	//获取预览信息集合
	VEC_DEVICEINFO& GetVecDeviceInfo();

	//获取输入集合
	VEC_INPUTSIGNAL& GetVecInputSignal();

private:

	//创建Pane
	void CreatePane();

	//创建预览容器
	void CreateContain();

	//初始化字体
	void InitFont();

	//调整布局
	void AdjustLayout1();

	//调整滚动条
	void AdjustScroll();

	//初始化预览框集合
	void InitVecFrame();

	//初始化视频预览对话框
	void InitViewPreviewDlg();

	//删除字体
	void DeleteFont();

	//分割字符串
	void SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr);

	//根据序号获取输入名称
	CString GetInputNameByIndex(int& nIndex);

	//设置初始RTSP计数
	void InitMapRTSPAddrCount(CString szRTSPAddr,int n);

	//调整Frame
	void AdjustVecFrame(CRect rect);

	//重置
	void ResetInitVecFrame();

	//根据IP生成RTSP
	void CreateRTSPAddr();

	//添加RTSP到集合
	void AddVecRTSP(CString szSubRTSP);

	BOOL JudgeOldIndexIsExist(int nIndex);

private:

	//清除预览框集合
	void ClearVecFrame();

	//清除预览信息集合
	void ClearDeviceInfo();

	//清除预览对话框
	void ClearPreviewDlg();

	//清除RTSP集合
	void ClearVecRTSP();

public:

	inline int GetBoardIndex(){return m_nBoardIndex;}

	inline void SetBoardIndex(int n){m_nBoardIndex=n;}

	inline CString GetUserName(){return m_szUserName;}

	inline void SetUserName(CString szName){m_szUserName=szName;}

	inline CString GetPassWd(){return m_szPassWd;}

	inline void SetPassWd(CString szPassWd){m_szPassWd=szPassWd;}

	inline CString GetszIP(){return m_szIP;}

	inline void SetIP(CString szIP){m_szIP=szIP;}

public:

	CString GetTitle();

	void SetFrameParamater();

	void SetframeRTSPAddr();

	void ResetRTSPInfo();

	void UpdateInputAnotherNameByPreview();

	void SetInputRTSPAddr();

	void DeleteCurPaneRTSP();

private:

	//委托
	XDelegateVideoPreviewPane* m_pDelegate;

	//预览容器
	XVideoPreviewContain m_Contain;

	//是否创建预览容器
	BOOL m_CreateContain;

	//字体
	CFont m_Font;

	//预览对话框
	CViewPreviewDlg* m_ViewPreviewDlg;

	//面板区域缓存
	CRect m_InterRect;

	//窗口缓存
	XVideoPreviewFrame* m_pTempFrame;

	//双击查看高清视频流（显示墙）
	XMultiVideoWindow* m_pMultiVideoWindow;

private:

	//预览框集合
	VEC_VIDEOPREVIEWFRAME m_VecFrame;

	//预览信息集合
	VEC_DEVICEINFO m_VecDeviceInfo;

	//RTSP地址
	VEC_RTSP m_VecRTSPAddr;

private:

	int m_nBoardIndex;

	CString m_szUserName;

	CString m_szPassWd;

	CString m_szIP;
};


