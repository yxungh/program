#pragma once

#include "XConstantIM.h"

class XMultiVideoWindow;

class XDelegateScreenManage
{
public:
	XDelegateScreenManage(void);
	~XDelegateScreenManage(void);

	//重设视图大小
	virtual void ResetViewSize() = 0;

	//刷新视图
	virtual void InvalidateView() = 0;

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type) = 0;

	//更新控价数据
	virtual void ControlDataChange(XDATATYPE type)=0;

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//获取场景文件路径
	virtual CString GetSceneFilePath(int nSceneIndex, CString szSceneName) = 0;

	virtual CString GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex) = 0;

	//获取场景文件夹路径
	virtual CString GetSceneFolderPath() = 0;

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI) = 0;

	//发送数据
	virtual BOOL SendData(char* pData, int nDataLen) = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//获取视图
	virtual CView* GetView() = 0;

	//获取缩放比例
	virtual float GetScale() = 0;

	//设置缩放比例
	virtual void SetScale(float f)=0;

	//获取设备IP
	virtual CString GetDeviceIP()=0;

	//设置设备IP
	virtual void SetDeviceIP(CString str)=0;

	//获取设备端口
	virtual int GetDevicePort()=0;

	//设置设备端口号
	virtual void SetDevicePort(int n)=0;

	//获取语言类型
	virtual CString GetLanguagetype()=0;

	//设置语言类型
	virtual void SetLanguagetype(CString type)=0;

	//获取网络状态
	virtual BOOL GetNetState() = 0;

	//是否登录
	virtual BOOL IsLogin() = 0;

	//获取用户节点权限
	virtual BOOL GetUserNodePower(int nInputIndex, int nOutputIndex) = 0;

	//是否管理员用户
	virtual BOOL IsAdminUser() = 0;

	//获取输入个数
	virtual int GetInputCount()=0;

	//设置输入信号个数
	virtual void SetInputCount(int n)=0;

	//重置输入数据（打开场景）
	virtual void ReSetInputData()=0;

	//获取输入信号集合
	virtual VEC_INPUTSIGNAL& GetVecInputSignal()=0;

	//设置OSD
	virtual void SetOSD(XInputSignal* pInputSignal)=0;
	
	//
	virtual void ResetDataBySceneInputCountChange()=0;

	//判断输入是否为4K
	virtual void JudgetInputIsultra(int nInputIndex)=0;

	//RTSP计数+1
	virtual void SetRTSPAddrCountPlus(CString szRTSPAddr)=0;

	//RTSP计数-1
	virtual void SetRTSPAddrCountLess(CString szRTSPAddr)=0;

	//重置RTSP计数
	virtual void SetRTSPAddrCountReset(CString szRTSPAddr)=0;

	//直接设置RTSP计数
	virtual void SetRTSPAddrCount(CString szRTSPAddr,int nCount)=0;

	//判断是否有信号
	virtual BOOL IsHaveSignal(int nIndex)=0;

	//判断是否有板卡
	virtual BOOL IsHavePane(int nIndex)=0;

	//调整预览墙大小
	virtual void AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth,int nHight)=0;

	//添加场景到树
	virtual HTREEITEM AddSceneToTree(int nSceneIndex,CString szSceneName,int nYtpe,CString szSceneGroup)=0;

	//判断场景名称
	virtual BOOL JudgeSceneName(CString szName)=0;

	//获取场景组集合
	virtual MAP_SCENEGROUP& GetMapSceneGroup()=0;

	//根据序号设置预览框中RTSP计数为1
	virtual void SetFrameRTSPCountByIndex(int nInputIndex)=0;

	//添加页面名称到保存的场景
	virtual void AddViewNameToScene(HTREEITEM item,CString szSceneName,int nIndex,CString szViewName)=0;

	virtual CString GetNotice()=0;

	virtual VEC_BASESCREENMANAGE& GetVecBaseScreenManage()=0;

	//设置选中信号信息
	virtual BOOL SetSelInputDataInfo()=0;

	virtual CString GetRTSPAddrFromPreviewPane(int nSignalIndex)=0;
};



