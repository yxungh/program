#pragma once
#include "XConstantIM.h"


class XVideoPreviewPane;
class XVideoPreviewVideoWnd;
class XVideoPreviewTextWnd;
class XVideoPreviewContain;
class XMultiVideoWindow;

class XVideoPreviewFrame
{
public:
	XVideoPreviewFrame(void);
	~XVideoPreviewFrame(void);

	//初始化
	void Init();

	//添加视频墙
	void AddMultiVideoWindow();

	//设置面板
	void SetPane(XVideoPreviewPane* p);

	//设置容器
	void SetContain(XVideoPreviewContain* p);

	//设置输出
	void SetFrameIndex(int n);

	//设置RTSP地址
	void SetRTSPAddr(CString s);

	//设置区域
	void SetRect(CRect r);

	//设置序号
	void SetIndex(int n);

	//获取输出
	int GetFrameIndex();

	//获取区域
	CRect GetRect();

	//获取RTSP地址
	CString GetRTSPAddr();

	//获取序号
	int GetIndex();

	//设置IP
	void SetIP(CString szIP);

	//获取IP
	CString GetIP();

	//设置用户名
	void SetUseName(CString szName);
	CString GetUseName();

	//设置密码
	void SetPassWd(CString szPassWd);
	CString getPassWd();

	//输入是不是4K
	void SetIsUltra(BOOL bIsUltra);
	BOOL GetIsUltra();

	//是否有信号
	void SetIsHaveSignal(BOOL b);
	BOOL GetIsHaveSignal();

	//是否有板卡
	void SetIsHavePane(BOOL b);
	BOOL GetIsHavePane();

	//重载界面
	void ReloadInterface();

	//获取视频区域
	CRect GetVideoRect();

	//设置输入信号名称
	void SetAnotherName(CString szAnotherName);

	//获取输入信号名称
	CString GetAnotherName();

	//清除建视频窗口
	void ClearVideoWnd();

	//清除文字窗口
	void ClearTextWnd();

	//设置预览卡序号
	void SetPreviewBoardIndex(int n);
	int GetPreviewBoardIndex();

	//添加画面
	void AddUltraFrame();
	void AddCommFrame();

	//清除之前Frame
	void ClearFrame();

	//添加Frame
	void SetPreviewFrame();

	//执行切换指令
	void RunOrder();

	//设置输入以及屏幕信号信息
	void SetSignalRTSPAddr();

public:

	XVideoPreviewPane* GetPane();

	//更新文字
	void UpdateText();

	//获取设备信息
	XDeviceInfo* GetDeviceInfo();

	//设置设备信息
	void SetDeviceInfo(XDeviceInfo* pInfo);

	//生产4个RTSP地址(4k)
	void CreateRTSPAddr();

	//获取RTSP地址集合
	VEC_CSTRING& GetVecRTSPAddr();

	//调整视频墙大小
	void AdjustMultiVideoWindowSize();

	//初始化Frame
	void InitFrame();

	//根据位置调整Frame窗口位置
	void AdjustRect();

private:

	//创建视频窗口
	void CreateVideoWnd();

	//创建文字窗口
	void CreateTextWnd();

	//清除RTSPjihe
	void ClearRTSPAddr();

	//添加RTSP
	void AddRTSP();

private:

	XVideoPreviewPane* m_Pane;

	XVideoPreviewContain* m_Contain;

	XDeviceInfo* m_DeviceInfo;

	//视频窗口
	XVideoPreviewVideoWnd* m_VideoWnd;

	//文字窗口
	XVideoPreviewTextWnd* m_TextWnd;

	//视频墙
	XMultiVideoWindow* m_pMultiVideoWindow;

private:

	//区域
	CRect m_Rect;

	//视频区域
	CRect m_VideoRect;

	//窗口序号
	int m_nFrameIndex;

	//预览卡序号
	int m_nBoardIndex;

	//RTSP地址
	CString m_RTSPAddr;

	//输入4k时，同来生成RTSP
	CString m_szIP;

	//用户名
	CString m_szUseName;

	//密码
	CString m_szPassWd;

private:

	//输入源序号
	int m_Index;

	//是否为4K
	BOOL m_bIsUltra;

	//RTSP集合
	VEC_CSTRING m_VecRTSPAddr;

	//输入有没有信号
	BOOL m_bIsHaveSignal;

	//输入有没有板卡
	BOOL m_bIsHavePane;

	//输入信号
	CString m_szAnotherName;
};

