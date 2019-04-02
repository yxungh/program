#pragma once
#include "..\XConstantIM.h"
#include "XExpandInfo.h"

class XMultiVideoWindow;


class XRTSPInfo
{
public:
	XRTSPInfo(void);
	~XRTSPInfo(void);

public:

	//初始化
	void Init(CString szRTSPAddr, CString szRTSPHDAddr, CString szAnotherName);

	//获取RTSP地址
	CString GetRTSPAddr();
	
	//获取RTSP地址
	CString GetRTSPHDAddr();

	//设置RTSP地址
	void SetRTSPAddr(CString s);

	//获取RTSP地址
	void SetRTSPHDAddr(CString s);

	//获取别名
	CString GetAnotherName();

	//设置别名
	void SetAnotherName(CString s);

	//获取预览信号序号
	int GetPreviewIndex();

	//设置信号序号
	void SetPreviewIndex(int n);

	//获取预览ID
	unsigned int GetPreviewID();

	//设置预览ID
	void SetPreviewID(unsigned int nID);

	//获取信号组ID
	unsigned int GetPreviewGroupID();

	//设置信号组ID
	void SetPreviewGroupID(unsigned int nGroupID);

	//获取是否为4K
	BOOL GetIsUltra();

	//设置是否为4k
	void SetIsUltra(BOOL IsUltra);

	//清除数据
	void ClearData();

	//获取局部放大信息
	XExpandInfo* GetExpandInfo();

	//设置局部放大信息
	void SetExpandInfo(XExpandInfo* p);

	//信号ID集合
	VEC_UNINT& GetVecPreviewID();

	//设置信号ID集合
	void SetVecPreviewID(VEC_UNINT& VecInt);

	//信号序号集合
	HYVEC_NUM& GetVecPreviewIndex();

	//设置信号序号集合
	void SetVecPreviewIndex(HYVEC_NUM& VecIndex);

	//4kRTSP集合
	VEC_CSTRING& GetVecRTSPAddr();
	void SetVecRTSPAddr(VEC_CSTRING& VecStr);

	//设置预览墙
	void SetMultiVideoWindow(XMultiVideoWindow* p);
	XMultiVideoWindow* GetMultiVideoWindow();

	//IP地址（用于4K拖拽产生RTSP）
	void SetIPAddr(CString szIP);
	CString GetIPAddr();

	//是否有信号
	void SetIsHaveSignal(BOOL b);
	BOOL GetIsHaveSignal();

	//是否有板卡
	void SetIsHavePane(BOOL b);
	BOOL GetIsHavePane();

	//用户名
	void SetUseName(CString szUseName);
	CString GetUseName();
	//密码

	void SetPassWd(CString szPssWd);
	CString GetPassWd();


public:

	//RTSP地址
	CString m_RTSPAddr;

	//RTSP HD地址
	CString m_RTSPHDAddr;

	//名称
	CString m_szAnotherName;

	//序号
	int m_nPreviewIndex;

	//信号ID
	unsigned int m_nPreviewID;

	//信号组ID
	unsigned int m_nPreviewGroupID;

	//局部放大信息
	XExpandInfo m_ExpandInfo;

	//是否为4K
	BOOL m_bIsUltra;

	BOOL m_bIsHaveSignal;

	BOOL m_bIsHavePane;

	//信号ID集合
	VEC_UNINT m_VecPreviewID;

	//信号序号集合
	HYVEC_NUM m_VecPreviewIndex;

	XMultiVideoWindow* m_pMultiVideoWindow;

	VEC_CSTRING m_VecRTSPAddr;

	CString m_szIPAddr;

	CString m_szUseName;

	CString m_szPassWd;

};
