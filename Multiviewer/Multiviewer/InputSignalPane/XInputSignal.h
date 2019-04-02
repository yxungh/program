#pragma once

#include "XOSDInfo.h"
#include "XExpandInfo.h"
#include "XConstantIM.h"
#include "XSignalCutInfo.h"
#include "XBorderOverlay.h"
#include "XEDIDInfo.h"
#include "XStreamAddrInfo.h"
#include "XPaneIPAddrInfo.h"



class XInputSignal
{
public:
	XInputSignal(void);
	~XInputSignal(void);

	//设置输入序号
	void SetInputIndex(int n);

	//获取输入序号
	int GetInputIndex();

	//设置树形控件所在项
	void SetTreeItem(HTREEITEM h);

	//获取树形控件所在项
	HTREEITEM GetTreeItem();

	//添加局部放大
	void AddExpand(XInputSignalExpand* p);

	//删除局部放大
	void DeleteExpand(XInputSignalExpand* p);

	//获取局部放大集合
	VEC_INPUTSIGNALEXPAND& GetVecExpand();

	//判断名称是否存在
	BOOL DecideExpandNameExist(XInputSignalExpand* pExpand, CString szName);

	//获取新局部放大ID
	int GetNewExpandID();

	//设置默认局部放大ID
	void SetDefaultExpandID(int nID);

	//获取默认局部放大ID
	int GetDefaultExpandID();

	//重置默认局部放大ID
	void ResetDefaultExpandID();

	//设置别名
	void SetAnotherName(CString szName);

	//获取别名
	CString GetAnotherName();

	//是否为4K
	BOOL GetIsUltra();

	void SetIsUltra(BOOL b);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString szRTSP);

	CString GetIPAddr();

	void SetIPAddr(CString szIP);

	CString GetUseName();

	void SetUseName(CString szUseName);

	CString GetPassWd();

	void SetPassWd(CString szPassWd);

	//设置组名称
	void SetGroupName(CString szName);

	//获取组名称
	CString GetGroupName();

	//设置是否在组内
	void SetIsInGroup(BOOL b);

	BOOL GetIsInGroup();

public:
	//返回信号信息
	void SetChanel(int n);

	void SetReStatus(int n);

	void SetReResulationH(int n);

	void SetReResulationV(int n);

	void SetReRefresh(int n);

	void SetReVideoSelect(int n);

	void SetReDataLen(int n);

	int GetReSignalIndex();

	int GetReSignalChenal();

	int GetChanel();

	int GetReStatus();

	int GetReResulationH();

	int GetReResulationV();

	int GetReRefresh();

	int GetReVideoSelect();

	int GetReDataLen();

public:

	//获取OSD信息
	XOSDInfo* GetOSDInfo();

	//获取默认局部放大
	XInputSignalExpand* GetDefaultExpand();

	//获取边框叠加
	XBorderOverlay* GetBorderOverLay();

	//获取剪切信息
	XSignalCutInfo* GetDefaultCutInfo();

	//EDID参数
	XEDIDInfo* GetEDIDInfo();

	//视频流地址
	XStreamAddrInfo* GetStreamInfo();

	//板卡IP地址
	XPaneIPAddrInfo* GetPaneIPAddrInfo();

	//获取局部放大
	XInputSignalExpand* GetExpandByID(int nID);

private:

	//清除局部放大集合
	void ClearVecExpand();

private:

	//局部放大集合
	VEC_INPUTSIGNALEXPAND m_VecExpand;

private:

	//树形控件所在项
	HTREEITEM m_TreeItem;

	//输入序号
	int m_InputIndex;

	//默认局部放大ID
	int m_DefaultExpandID;

	CString m_AnotherName;

	//是否为4K
	BOOL m_IsUltra;

	//RTSP地址
	CString m_szRTSPAddr;

	//IP地址用于4K拖拽画面产生RTSP
	CString m_szIPAddr;
	CString m_szRTSPName;
	CString m_szRTSPPassWd;

	//组名称
	CString m_szGroupName;

	//是否在组内
	BOOL m_bIsInGroup;


private:

	XOSDInfo m_OSDInfo;

	XBorderOverlay m_Border;

	XSignalCutInfo m_CutInfo;

	XEDIDInfo m_EDIDInfo;

	XStreamAddrInfo m_StreamInfo;

	XPaneIPAddrInfo m_PaneIPInfo;

private:
	//返回输入状态
	int m_Chenal;

	int m_ReSignalIndex;

	int m_ReSignalChenal;

	int m_ReStatus;

	int m_ReResulationH;

	int m_ReResulationV;

	int m_ReRefresh;

	int m_ReVideoSelect;

	int m_ReDataLen;

};

