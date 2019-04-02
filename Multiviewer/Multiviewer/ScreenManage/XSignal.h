#pragma once

#include "XConstantIM.h"
#include "XExpandInfo.h"
#include "XSignalCutInfo.h"

class XScreen;
class XMultiVideoWindowFrame;

class XSignal
{
public:
	XSignal(void);
	~XSignal(void);

	void SetInputIndex(int n);

	void SetExpand(XExpandInfo* pInfo);

	void SetCutInfo(XSignalCutInfo* pCutInfo);

	void SetRect(RECTF r);

	void SetScreen(XScreen* p);

	XExpandInfo* GetExpandInfo();

	XSignalCutInfo* GetCutInfo();

	int GetInputIndex();

	RECTF GetRect();

	XScreen* GetScreen();

	unsigned int GetSignalID();

	void SetSignalID(unsigned int ID);

	unsigned int GetSignalGroupID();

	void SetSignalGroupID(unsigned int ID);

	void SetSignalLevel(int n);

	int GetSignalLevel();

	BOOL GetSignalHide();

	void SetSignalHide(BOOL b);

	int GetSignalHdpi();

	int GetSignalVdpi();

	void SetSignalHdpi(int n);

	void SetSignalVdpi(int n);

	void SetAnotherName(CString szName);

	CString GetAnotherName();

	BOOL GetIsUltra();

	void SetIsUltra(BOOL b);

	CString GetIPAddr();

	void SetIPAddr(CString szIP);

	CString GetUseName();

	void SetUseName(CString szUseName);

	CString GetPassWd();

	void SetPassWd(CString szPassWd);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString szRTSPAddr);

	XMultiVideoWindowFrame* GetPreviewFrame();

	void SetPreviewFrame(XMultiVideoWindowFrame* p);

	BOOL GetIs4kTo2k();

	void SetIs4kTo2k(BOOL b);

	int GetSignalNum();

	void SetSignalNum(int n);

public:

	inline void SetSelected(BOOL b){m_bIsSelected=b;}

	inline BOOL GetSelected(){return m_bIsSelected;}

	inline void SetInteRect(RECTF rect){m_InteRect=rect;}

	inline RECTF GetInteRect(){return m_InteRect;}

public:

	//局部放大信息
	XExpandInfo m_ExpandInfo;

private:

	//屏幕
	XScreen* m_Screen;

	//区域
	RECTF m_Rect;

	//输入序号
	int m_InputIndex;

	//信号裁剪
	XSignalCutInfo m_CutInfo;

	//屏幕水平分辨率
	int m_SignalHdpi;

	//屏幕垂直分辨率
	int m_SignalVdpi;

	//信号层次
	int m_SignalLevel;

	//信号ID
	unsigned int m_nSignalID;

	//信号组ID
	unsigned int m_nSingalGroupID;

	//隐藏
	BOOL m_IsHide;

	//别名
	CString m_szAnotherName;

	//信号序号
	int m_nSignalNum;

	//是否为4K
	BOOL m_IsUltra;

	//是否为4k切2K
	BOOL m_bIs4kTo2k;

	//IP地址(用于4K生成RTSP地址)
	CString m_szIPAddr;

	//RTSP地址
	CString m_szRTSPAddr;

	CString m_szUseName;

	CString m_szPassWd;

	//信号墙Frame
	XMultiVideoWindowFrame* m_pFrame;

	BOOL m_bIsSelected;

	//信号的整体区域（用于设置分辨率后重新开窗）
	RECTF m_InteRect;
	
};

