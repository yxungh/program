#pragma once

#include "XExpandInfo.h"
#include "XConstantIM.h"
#include "XSignalCutInfo.h"


class XMultiVideoWindow;
class XMultiVideoWindowFrame;

class XDragInfo
{
public:
	XDragInfo(void);
	~XDragInfo(void);

	//获取输入序号
	int GetInputIndex();

	//获取文字
	CString GetText();

	//局部放大偏移
	XExpandInfo* GetExpandInfo();
	void SetExpand(XExpandInfo* pInfo);

	//设置输入序号
	void SetInputIndex(int n);

	//设置文字
	void SetText(CString s);

	//信号ID
	unsigned int GetSignalID();
	void SetSignalID(unsigned int ID);

	//信号组ID
	unsigned int GetSignalGroupID();
	void SetSignalGroupID(unsigned int ID);

	//拖拽信号ID
	unsigned int GetDragSignalID();
	void SetDragSignalID(unsigned int SignalID);

	//拖拽信号组ID
	unsigned int GetDragSignalGroupID();
	void SetDragSignalGroupID(unsigned int SignalID);

	//信号分辨率
	void SetSignalResulationH(int n);
	int GetSignalResulationH();
	void SetSignalResulationV(int n);
	int GetSignalResulationV();

	//设置别名
	void SetAnotherName(CString szName);
	CString GetAnotherName();

	//是否为4K
	BOOL GetIsUltra();
	void SetIsUltra(BOOL b);

	//信号ID集合
	VEC_UNINT& GetVecSignalID();
	void SetVecSignalID(VEC_UNINT& VecInt);

	//信号序号集合
	HYVEC_NUM& GetVecSignalIndex();
	void SetVecSignalIndex(HYVEC_NUM& VecIndex);

	//信号ID集合(用于拖拽)
	VEC_UNINT& GetVecDragSignalID();
	void SetVecDragSignalID(VEC_UNINT& VecInt);

	//信号序号集合(用于拖拽)
	HYVEC_NUM& GetVecDragSignalIndex();
	void SetVecDragSignalIndex(HYVEC_NUM& VecIndex);

	//信号ID集合(用于扩展)
	VEC_UNINT& GetVecExpandSignalID();
	void SetVecExpandSignalID(VEC_UNINT& VecInt);

	//信号序号集合(用于扩展)
	HYVEC_NUM& GetVecExpandSignalIndex();
	void SetVecExpandSignalIndex(HYVEC_NUM& VecIndex);

	//信号ID集合（用于切换输入）
	VEC_UNINT& GetVecChangeInputID();
	void SetVecChangeInputID(VEC_UNINT& VecInt);

	//*********************************
	//视频预览
	CString GetRTSPAddr();
	void SetRTSPAddr(CString s);
	void ClearRTSPData();

	//IP地址
	CString GetScreenIP();
	void SetScreenIP(CString szIP);

	//预览Frame
	XMultiVideoWindowFrame* GetPreviewFrame();
	void SetPreviewFrame(XMultiVideoWindowFrame* p);

	//输入序号
	int GetInputNum();
	void SetInputNum(int n);

	//4个RTSP地址
	VEC_CSTRING& GetVecRTSPAddr();
	void SetVecRTSPAddr(VEC_CSTRING& VecStr);

	//预览墙
	XMultiVideoWindow* GetMultiVideoWindow();
	void SetMultiVideoWindow(XMultiVideoWindow* p);

	//IP地址
	CString GetIPAddr();
	void SetIPAddr(CString szIP);

	//是否有信号
	BOOL GetIsHaveSignal();
	void SetIsHaveSignal(BOOL b);

	//是否有板卡
	BOOL GetIsHavePane();
	void SetIsHavePane(BOOL b);

	//用户名
	CString GetUseName();
	void SetUseName(CString szUseName);

	//密码
	CString GetPassWd();
	void SetPassWd(CString szPassWd);

private:

	//输入序号
	unsigned short m_InputIndex;

	//局部放大信息
	XExpandInfo m_ExpandInfo;

	//文字
	CString m_Text;

	//信号ID用于拖动
	unsigned int m_nDragSignalID;

	//信号组ID
	unsigned int m_nDragSignalGroupID;

	//信号分辨率
	int m_SignalresulationH;

	int m_SignalresulationV;

	//别名
	CString m_AnotherName;

	//是否为4K
	BOOL m_IsUltra;

	//RTSP地址
	CString m_szRTSPAddr;

	//用户名
	CString m_szUseName;

	//密码
	CString m_szPassWd;

	//IP地址(屏幕IP)
	CString m_szScreenIP;

	//信号ID集合
	VEC_UNINT m_VecSignalID;

	//信号序号集合
	HYVEC_NUM m_VecSignalIndex;

	//信号ID集合(用于拖拽)
	VEC_UNINT m_VecDragSignalID;

	//信号序号集合(用于拖拽)
	HYVEC_NUM m_VecDragSignalIndex;

	//信号ID集合(用于扩展)
	VEC_UNINT m_VecExpandSignalID;

	//信号序号集合(用于扩展)
	HYVEC_NUM m_VecExpandSignalIndex;

	//信号ID集合（用于切换输入源）
	VEC_UNINT m_VecChangeInputID;

	XMultiVideoWindowFrame* m_pFrame;

	//输入信号序号（中控切换）
	int m_nInputNum;

	//4个RTSP地址
	VEC_CSTRING m_VecRTSPAddr;

	//预览墙
	XMultiVideoWindow* m_pMultiVideoWindow;

	//4K信号IP(用于生成RTSP地址)
	CString m_szIPAddr;

	//是否有信号
	BOOL m_bIsHaveSignal;

	//是否有板卡
	BOOL m_bIsHavePane;


};

