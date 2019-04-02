#pragma once

#include "XConstantIM.h"

class XRTSPInfo;
class XRTSPInfoDragWnd;
class XMultiVideoWindow;


class XDelegateVideoPreviewPane
{
public:
	XDelegateVideoPreviewPane(void);
	~XDelegateVideoPreviewPane(void);

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//添加RTSP
	virtual void AddRTSP(CString szRTSPAddr) = 0;

	//添加RTSP
	virtual void AddRTSP(CString szRTSPAddr,int nCount)=0;

	//RTSP计数增加
	virtual void SetRTSPCountPlus(CString szRTSPAddr)=0;

	virtual void SetRTSPCountLess(CString szRTSPAddr)=0;

	//添加RTSP HWND
	virtual void AddRTSPHWND(HWND h) = 0;

	//设置RTSP HWND RTSP地址
	virtual void SetRTSPHWNDRTSPAddr(HWND h, CString szRSTPAddr) = 0;

	//添加视频墙
	virtual XMultiVideoWindow* AddMultiVideoWindow(HWND h)=0;

	//删除RTSP
	virtual void DeleteRTSP(CString szRTSPAddr) = 0;

	//发送数据
	virtual BOOL SendData(char* pData, int nDataLen) = 0;

	//获取网络状态
	virtual BOOL GetNetState() = 0;

	//获取输出个数
	virtual int GetInputCount() = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//是否登录
	virtual BOOL IsLogin() = 0;

	//获取用户节点权限
	virtual BOOL GetUserNodePower(int nInputIndex, int nOutputIndex) = 0;

	//调整RTSP HWND区域大小
	virtual void AdjustRTSPHWNDSize(HWND h, int nWidth, int nHeight) = 0;

	//获取输入集合
	virtual VEC_INPUTSIGNAL& GetVecInputSignal()=0;

	//获取屏幕集合
	virtual VEC_SCREEN& GetVecScreen()=0;

	//根据序号获取输入名称
	virtual CString GetInputNameByIndex(int nIndex)=0;

	//根据序号获取Input
	virtual XInputSignal* GetInputByIndex(int nIndex)=0;
	
	//创建拖拽窗口
	virtual XRTSPInfoDragWnd* CreatePreviewDragWnd(XRTSPInfo* pInfo)=0;

	//拖动信息
	virtual void DragInfo(CRect rc,XRTSPInfo* pInfo)=0;

	//获取是否为4K
	virtual void IsUltra(int nIndex)=0;

	//判断输入是否有信号
	virtual BOOL IsHaveSignal(int nIndex)=0;

	//判断是否有板卡
	virtual BOOL IsHavePane(int nIndex)=0;

	//从所有信号获取RTSP数量
	virtual int GetRTSPCountBySignal(CString szRTSP)=0;

	//根据信号序号设置输入信号RTSP
	virtual void SetInputRTSPAddrByIndex(int nIndex,CString szRTSP)=0;

	virtual void SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP)=0;

	//根据信号序号设置输入信号IP
	virtual void SetInputParaByIndex(int nIndex,CString szIP,CString szUseName,CString szPassWd)=0;

	//调整预览墙大小
	virtual void AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth,int nHight)=0;

	virtual void SetRTSPAddrCount(CString szRTSPAddr,int nCount)=0;

	virtual MAP_TABLABLE& GetMapBottomTabLable()=0;

};

