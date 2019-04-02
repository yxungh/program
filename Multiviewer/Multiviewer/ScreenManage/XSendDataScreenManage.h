#pragma once

#include "XConstantIM.h"
#include <vector>

class XScreenManage;
class XScreen;
class XSignal;

class XSendDataScreenManage
{
public:

	//添加发送数据-信号
	static void AddSendDataOfSignal(XScreenManage* pScreenManage, XSignal*& pSignal,RECTF& rect);

	//发送添加矩阵数据—信号
	static void AddSendDataOfMatrixSignal(XScreenManage* pScreenManage,XSignal* pSignal,XScreen* pScreen);

	//添加发送数据-配置完成
	static void AddSendDataOfFinash(XScreenManage* pScreenManage);

	//添加发送数据-删除所有信号
	static void AddSendDataOfDeleteAllSignal(XScreenManage* pScreenManage);

	//删除所有信号
	static void AddSendDataOfDeleteAllMatrixSignal(XScreenManage* pScreenManage);

	//添加发送数据-信号置顶
	static void AddSendDataOfSetSignalTop(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen);

	//添加发送数据-信号置底
	static void AddSendDataOfSetSignalBottom(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen);

	//添加发送数据-信号上移
	static void AddSendDataOfSetSignalShiftUP(XScreenManage* pScreenManage, int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen);

	//添加发送数据-信号下移
	static void AddSendDataOfSetSignalShiftDown(XScreenManage* pScreenManage, int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen);

	//添加发送数据-关闭信号
	static void AddSendDataOfSignalClose(XScreenManage* pScreenManage,int nScreenIndex,unsigned int ID,int nNum,BOOL bIsTwoScreen);

	//添加发送数据-关闭信号(矩阵)
	static void AddSendDataOfDeleteMatrixSignal(XScreenManage* pScreenManage,XScreen* pScreen);

	//添加发送数据-获取幕数据
	static void AddSendDataOfGetScreenParamater(XScreenManage* pScreenManage);

	//添加发送数据-获取信号信息
	static void AddSendDataOfGetSignalParamater(XScreenManage* pScreenManage);

	//添加发送数据-获取窗口信息
	static void AddSendDataOfGetWindowParamater(XScreenManage* pScreenManage);

	//添加发送数据-保存场景
	static void SendDataBySaveScene(XScreenManage* pScreenManage,int nSceneIndex);

	//添加发送数据-打开场景
	static void SendDataByOpenScene(XScreenManage* pScreenManage,int nSceneIndex);

	//添加发送数据-获取场景序号
	static void AddSendDataOfDeleteScene(XScreenManage* pScreenManage,int nSceneIndex);

	//添加发送数据-设置屏幕分辨率
	static void SendDataOfSetScreenResualtion(XScreenManage* pScreenManage,XScreen*& pScreen);

	//添加发送数据-设置所有屏幕分辨率
	static void SendDataOfSetAllScreenResualtion(XScreenManage* pScreenManage);

	static void SendDataOfSetScreenRowResualtion(XScreenManage* pScreenManage);

	//全部分辨率之前
	static void AddSendDataOfResulationFront(XScreenManage* pScreenManage);

	//添加发送数据-屏幕滚动画面
	static void SendDataOfScreenMove(XScreenManage* pScreenManage,XScreen*& pScreen);

	//添加发送数据-屏幕滚动画面内容
	static void SendDataOfScreenMoveData(XScreenManage* pScreenManage,unsigned char* pMutrixData,int nMutrixDataLen);

	//添加发送数据-时间间隔
	static void SendDataByTimedPolling(XScreenManage* pScreenManage);

	//添加发送数据-询问是否可以发送
	static void SendDataOfScreenMoveAsk(XScreenManage* pScreenManage);

	//添加发送数据-获取场景序号
	static void AddSendDataOfGetSceneIndex(XScreenManage* pScreenManage);

	//添加发送数据-执行旧指令
	static void SendDataByRunOldOrder(XScreenManage* pScreenManage);

	//获取设备状态
	static void SendDataByDeviceStatus(XScreenManage* pScreenManage);

	//滚动拼接复位关
	static void AddSendDataOfScreenMoveOff(XScreenManage* pScreenManage);

	//滚动拼接不显示
	static void AddSendDataOfScreenMoveZero(XScreenManage* pScreenManage);

	//滚动拼接复位开
	static void AddSendDataOfScreenMoveOn(XScreenManage* pScreenManage);

	//更改拼接参数
	static void AddSendDataOfChangeMoveParamater(XScreenManage* pScreenManage);

	//获取信号序号
	static void AddSendDataOfGetSignalNum(XScreenManage* pScreenManage);

	//添加发送数据-设置屏幕分辨率(矩阵)
	static void SendDataOfSetMatrixScreenResualtion(XScreenManage* pScreenManage,XScreen* pScreen);

	static void SendDataOfSetMatrixAllScreenResualtion(XScreenManage* pScreenManage);

	//获取矩阵屏幕配置
	static void AddSendDataOfGetMatrix(XScreenManage* pScreenManage);

	//*****************
	static BOOL GetReScreenResulation(XScreenManage* pScreenManage,XScreen*& pScreen,int& nReH,int& nReV);
	static BOOL GetReSignalResulation(XScreenManage* pScreenManage,XSignal*& pSignal,int& nResH,int& nResV);

private:

	//添加发送数据-关闭屏幕信号
	static void AddSendDataOfScreenClose(XScreenManage* pScreenManage, int nScreenIndex, char type);

	//添加发送数据-协议
	static void AddSendDataByProtocol(XScreenManage* pScreenManage, unsigned char* pSrcData, unsigned short nSrcDataLen,ADDRESSTYPE addressType,ORDERNUM orderNum,ORDERTYPE orderType);

	//校验和
	static unsigned short CheckNum(unsigned char *pData,int nLen);

private:
	XSendDataScreenManage(void);
	~XSendDataScreenManage(void);

public:

	static int m_Index;

	static int m_Chenal;

	static int m_Index2;

	static int m_Chenal2;

	static int m_nScreenNumOfTwo;
};

