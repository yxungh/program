#pragma once

#include "XConstantIM.h"

class XDragInfo;
class XDragWnd;
class XMultiVideoWindow;

class XDelegateInputSignalPane
{
public:
	XDelegateInputSignalPane(void);
	~XDelegateInputSignalPane(void);

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//创建拖动窗口
	virtual XDragWnd* CreateDragWnd(XDragInfo* pInfo) = 0;

	//拖动信息
	virtual void DragInfo(CRect rc,CPoint point,XDragInfo* pInfo) = 0;

	//发送数据
	virtual BOOL SendData(char* pData, int nDataLen) = 0;

	//获取网络状态
	virtual BOOL GetNetState() = 0;

	//是否登录
	virtual BOOL IsLogin() = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//设置预览别名
	virtual void SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName)=0;

	//添加RTSP
	virtual void AddRTSP(CString szRTSPAddr) = 0;

	//添加RTSP HWND
	virtual void AddRTSPHWND(HWND h) = 0;

	//设置RTSP HWND RTSP地址
	virtual void SetRTSPHWNDRTSPAddr(HWND h, CString szRSTPAddr) = 0;

	//删除RTSP
	virtual void DeleteRTSP(CString szRTSPAddr) = 0;

	virtual void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)=0;

	//获取拖拽信息
	virtual XDragInfo& GetDragInfo()=0;
};

