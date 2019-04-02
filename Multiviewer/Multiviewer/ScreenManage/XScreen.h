#pragma once

#include "XConstantIM.h"
#include "XResulationInfo.h"
#include "XAllResulationInfo.h"

class XSignal;
class XExpandInfo;
class XScreenManage;
class XSignalCutInfo;


class XScreen
{
public:
	XScreen(void);
	~XScreen(void);

	//获取屏幕序号
	int GetIndex();

	//设置屏幕序号
	void SetIndex(int n);

	RECTF GetRect();

	void SetRect(RECTF r);

	//添加信号源
	XSignal* AddSignal(
		RECTF& rect, 
		int& nLevel,
		int& nInputIndex,
		CString szAnothgerName,
		unsigned int& signalID,
		unsigned int& signalGroupID,
		XExpandInfo* pExpandInfo,
		BOOL bIsUltra);

	//获取信号集合
	VEC_SIGNAL& GetVecSignal();

	//清除信号源集合
	void ClearVecSignal();

	//根据组ID删除信号
	void DeleteSignalBySignalGroupID(XScreenManage *pManage,int nScreenIndex,unsigned int nGroupID);
	void DeleteSignalBySignalID(XScreenManage *pManage,int nScreenIndex,unsigned int nID);

	//删除信号
	void DeleteSignal(XSignal* p);

	//设置屏幕管理
	void SetManage(XScreenManage* p);

	//获取屏幕管理
	XScreenManage* GetManage();

	//屏幕分辨率参数
	XResulationInfo* GetResulationInfo();

	//屏幕分辨率
	XAllResulationInfo* GetAllResulationInfo();

	//设置信号置顶
	void SetSignalTopByGroupID(int nScreenIndex,unsigned int nGroupID);
	void SetSignalTopByID(int nScreenIndex,unsigned int nID);

	//设置信号置底
	void SetSignalBottom(int nScreenIndex,unsigned int nGroupID);

	//设置信号上移
	void SetSignalShiftUp(int nScreenIndex,unsigned int nGroupID);

	//设置信号上移
	void SetSignalShiftDown(int nScreenIndex,unsigned int nGroupID);

	XSignal* GetSignalByID(unsigned int nID);

	BOOL CanAddSignal(int i);

	BOOL CanAddSignal();

	//同步信号排序
	void SortSignal();

	int GetScreenHdpi();

	int GetScreenVdpi();

	void SetScreenHdpi(int n);

	void SetScreenVdpi(int n);

	//设置屏幕信号个数
	void SetAddSignalNumInScreen(int n);

	//获取屏幕信号个数
	int GetAddSignalNumInScreen();

	//设置最大个数
	void SetMaxSignalNumInScreen(int n);

	//获取最大信号个数
	int GetMaxSignalNumInScreen();

	//设置是否为两路
	void SetIsTwoSignal(BOOL b);

	//获取是否为两路
	BOOL GetIsTwoSignal();

	//设置板卡序号
	void SetBoardIndex(int n);

	//获取板卡序号
	int GetBoardIndex();

	//设置两路第几个
	void SetNumOfTwoScreen(int n);

	//获取两路第几个
	int GetNumOfTwoScreen();

	//重置最大可添加数
	void ResetMaxSignalInScreen();

	//是否为预览卡
	void SetIsPreview(BOOL b);

	//获取是否为预览卡
	BOOL GetIsPreview();


public:

	void SeteDataLen(int n);

	void SetReScreenIndex(int n);

	void SetReStatus(int n);

	void SetReScreenHdpi(int n);

	void SetReScreenVdpi(int n);

	void SetReDpiIndex(int n);

	void SetReRefresh(int n);

	int GeteDataLen();

	int GetReScreenIndex();

	int GetReStatus();

	int GetReScreenHdpi();

	int GetReScreenVdpi();

	int GetReDpiIndex();

	int GetReRefresh();

	//////////////////////////////////////////////////////////////////////////
	BOOL GetIsHasSignalOfMatrix();
	void SetIsHasSignalOfMatrix(BOOL b);

	void SetScreenType(int n);
	int GetScreenType();

public:
	
	inline CString GetScreenName(){return m_szScreenName;}

	inline void SetScreenName(CString szName){m_szScreenName=szName;}

	inline BOOL GetIsRight(){return m_bIsRight;}

	inline void SetIsRight(BOOL b){m_bIsRight=b;}

	inline BOOL GetIsBottom(){return m_bIsBottom;}

	inline void SetIsBottom(BOOL b){m_bIsBottom=b;}

	inline void SetScreenRow(int n){m_nRow=n;}

	inline int GetScreenRow(){return m_nRow;}

	inline void SetScreenCol(int n){m_nCol=n;}

	inline int GetScreenCol(){return m_nCol;}

private:

	//屏幕管理
	XScreenManage* m_pManage;

	//屏幕分辨率
	XResulationInfo m_ResulationInfo;

	//屏幕分辨率信息
	XAllResulationInfo m_AllResulationInfo;

	//信号集合
	VEC_SIGNAL m_VecSignal;

	//屏幕序号
	int m_nIndex;

	//板卡序号
	int m_nBoardIndex;

	//区域
	RECTF m_Rect;

	int m_Hdpi;

	int m_Vdpi;

	//每个屏幕所能添加信号个数
	int m_nAddSignalNum;

	//每个屏幕最大可添加信号个数
	int m_nMaxSignalNum;

	//屏幕是否为两路
	BOOL m_bIsTwoSignal;

	//两路情况为第几个
	int m_nNumOfTwoScreen;

	//是否为预览卡
	BOOL m_bIsPreview;

	//是否为右侧屏幕
	BOOL m_bIsRight;

	//是否为底部
	BOOL m_bIsBottom;

	int m_nCol;

	int m_nRow;

private:
	//返回数据
	int m_ScreenIndex;

	int m_ReDataLen;

	int m_ReStatus;

	int m_ReScreenHdpi;

	int m_ReScreenVdpi;

	int m_ReDpiIndex;

	int m_ReRefresh;

	private:

	BOOL m_bIsHasSignalOfMatrix;

	int m_nScreenType;

	CString m_szScreenName;
};

