#pragma once

#include "XBaseScreenManage.h"
#include "XConstantIM.h"
#include "XExpandInfo.h"
#include "XDragInfo.h"
#include "XScreen.h"
#include "XDelegateResolution.h"
#include "XDelegateSaveScence.h"
#include "XDelegateChangeInput.h"
#include "XDelegateScreenMoveDlg.h"
#include "XDelegateScreenAttributes.h"
#include "XDelegateTimedPollingDlg.h"
#include "XSendData.h"
#include "XScreenMoveDlg.h"
#include "XDelegateDeleteScene.h"
#include "XDelegateAllResulation.h"
#include "XDelegateRunOldOrder.h"
#include "XOldOrderInfo.h"
#include "XScreenMoveInfo.h"
#include "XTimedPollingInfo.h"
#include "XAllResulationInfo.h"
#include "XDelegateChangeScreen.h"
#include "XDelegateScreenMoveChangeDlg.h"
#include "XDelegateSelectEquipment.h"
#include "XDelegateSetBoard.h"
#include "XDelegateSetScreenRange.h"
#include "XMenuScreenSetInfo.h"
#include "VideoPlayerConstant.h"
#include "XScreenRetInfo.h"
#include "XDelegateMatrixResolution.h"
#include "XDelegateAllMatrixResolution.h"
#include "XDelegateMatrixScreenAttributes.h"
#include "XDelegateSetScreenName.h"
#include "XSaveScence.h"
#include "XResulationHCutInfo.h"
#include "XResulationVCutInfo.h"
#include "XDelegateSetRowResoluation.h"
#include "XDelegateSetColResoluation.h"


class XSignal;
class XInputSignal;
class XRTSPInfo;
class CMultiviewerView;
class XScreenSetInfo;




class XScreenManage : public XBaseScreenManage,
					  public XDelegateResolution,
					  public XDelegateSaveScence,
					  public XDelegateChangeInput,
					  public XDelegateScreenMoveDlg,
					  public XDelegateScreenAttributesDlg,
					  public XDelegateTimedPollingDlg,
					  public XDelegateDeleteSceneDlg,
					  public XDelegateAllResulution,
					  public XDelegateRunOldOrderDlg,
					  public XDelegateChangeScreen,
					  public XDelegateScreenMoveChangeDlg,
					  public XDelegateSelectEquipment,
					  public XDelegateSetBoard,
					  public XDelegateSetScreenRange,
					  public XDelegateMatrixResolution,
					  public XDelegateAllMatrixResolution,
					  public XDelegateMatrixScreenAttributesDlg,
					  public XDelegateSetScreenName,
					  public XDelegateSetRowResoluation,
					  public XDelegateSetColResoluation
			
{
public:
	XScreenManage(void);
	~XScreenManage(void);

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl);

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl);

	//获取数据
	virtual void GetData(CArchive& arch);

	//保存数据
	virtual void SaveData(CArchive& arch);

	//获取放缩
	virtual float GetMultiScale();

	//获取水平屏幕
	virtual int GetFramesCountH();

	//获取垂直屏幕个数
	virtual int GetFramesCountV();

	//获取屏幕分辨率
	virtual int GetFramesResulationH();

	//获取屏幕分辨率
	virtual int GetFramesResulationV();

	//获取右侧水平分辨率
	virtual int GetFramesRightResulationH();

	//获取底部垂直分辨率
	virtual int GetFramesBottomResulationV();

	//重置数据
	virtual void ResetData();

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
		int noffsetY);

	//视图获取大小
	virtual CSize ViewGetSize();

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图双击
	virtual void ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY);

	//视图鼠标离开
	virtual void ViewMouseLeave();

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar);

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
		CRect& rect, int noffsetX, int noffsetY);

	//操作
	virtual void Operate(OPERATETYPE type, void* pData);

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//显示或隐藏
	virtual void ShowManage(int nShowState);

	//拖动信息
	virtual BOOL DragInfo(CRect rc,CPoint point,XDragInfo* pInfo);

	//预览拖动信息
	virtual BOOL DragInfo(CRect rc, XRTSPInfo* pInfo);

	//获取输出个数
	virtual int GetOutputCount();

	//设置视图名称
	virtual void SetViewName(CString szName);

	//获取视图名称
	virtual CString GetViewName();

	//打开场景（场景树）
	virtual void OpenScene(CString szSceneName,int nSceneIndex,CString szViewName);

	//删除场景
	virtual void DeleteScene(int nSceneIndex);

	//是否登录
	virtual BOOL IsLogin();

	//刷新视图
	virtual void InvalidateView();

	//重置视图大小
	virtual void ResetViewSize();

	//显示菜单（右键标签栏）
	virtual void ShowMenu(CPoint& point);

	//视图放缩调整预览墙大小
	virtual void AdjustMultiVideoWindowSize();

	//获取屏幕集合
	virtual VEC_SCREEN& GetVecScreen1();

	//菜单屏幕设置
	virtual XMenuScreenSetInfo* GetMenuScreenSetInfo();

	//获取屏幕上面信号中RTSP总数
	virtual int GetRTSPCountBySignal(CString szRTSP);

	//设置屏幕文字
	virtual CString SetText(XScreen* pScreen);

	//刷新界面（翻译）
	virtual void ReLoadInterface();

	//设置屏幕上面信号的RTSP(拖拽预览时)
	virtual void SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP);

	virtual MAP_BOARDTYPE& GetMapBoardType();

	//改变预览墙上面信号别名
	virtual void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName);

	//设置屏幕开始序号
	virtual void SetBeginIndex(int n);

	//设置屏幕类型（矩阵，拼接）
	virtual void SetScreenModel(int n);

	//获取屏幕类型
	virtual int GetScreenModel();

	//获取屏幕类型
	virtual int GetScreenType();

	//添加场景
	virtual void OnBtnNewScene();

	//关闭标签页时，提示保存场景
	virtual void SaveSceneByCloseView();

	//获取场景组
	virtual MAP_SCENEGROUP& GetMapSceneGroup();

	//保存全部场景
    virtual void SaveAllScene(CString szSceenName,int nSceneIndex,CString szSceneGroup,int nIndex,int nType);

	//打开全部场景
	virtual void OpenAllScene(CString szSceneName,int nSceneIndex,int nIndex,int nType,CString szViewName=_T(""));

	virtual void CopyOrderToShare(CString szSceneName,int nSceneIndex,int nIndex,CString szViewName);

	virtual void CopySingleOrderToShare(CString szSceneNane,int nSceneIndex,CString szViewName);

	//设置当前视图缩放
	virtual void SetMultiScale(float f);

	//获取拖拽信息
	virtual XDragInfo& GetDragInfo();

	//鼠标滚轮
	virtual BOOL AddScalingByMouseWheel(short zDelta);

	//双击标签微调
	virtual void SetScreenByDbClick();

	virtual MAP_COLINFO& GetMapColInfo();

	virtual MAP_ROWINFO& GetMapRowInfo();

public:

	//获取缩放比例
	float GetScale();

	//保存缩放比例
	void SetCurScale(int n);

	//获取放缩比例
	int GetCurScale();

	//获取设备IP
	CString GetDeviceIP();

	//设置设备IP
	void SetDeviceIP(CString str);

	//获取设备端口
	int GetDevicePort();

	//设置设备端口号
	void SetDevicePort(int n);

	//获取语言类型
	CString GetLanguagetype();

	//根据屏幕个数改变重置数据
	void ResetDataBySceneScreenCountChange();

	//重置输入数据
	void ResetDataBySceneInputCountChange();

	//设置语言类型
	void SetLanguagetype(CString type);

	//发送数据
	BOOL SendData(char* pData, int nDataLen);

	//获取屏幕
	XScreen* GetScreen(int n);

	//移动信号
	void MoveSignal(POINTF& point1, POINTF& point2);

	//拖拽产生新信号
	void MoveSignalOfNew(POINTF& point1, POINTF& point2);

	//获取区域和
	RECTF GetInterRect();

	//根据组ID删除信号
	void DeleteSignalBySignalGroupID(unsigned int nID);

	//根据ID删除信号
	void DeleteSignalBySignalID(unsigned int nID);

	//设置输入信号个数
	void SetInputCount(int n);

	//获取输入信号个数
	int GetInputCount();

	//设置右侧剪切
	void SetRightResulationH(int n);

	//获取右侧剪切
	int GetRightResulationH();

	//设置底部剪切
	void SetBottomResulationV(int n);

	//获取底部剪切
	int GetBottomResulationV();

	//从场景路径获取场景序号
	int GetSceneIndexFromScenePath(CString szPath);

	//判断屏幕有无设备
	BOOL IsHaveDevice(int nIndex);

	//发送打包数据
	void SendAllData(BOOL bCopy=FALSE);

	//获取视图是否按下鼠标
	BOOL GetISViewButtonDown();

	//获取屏幕开始序号
	int GetBeginIndex();

	//是否为两路
	void IsTwoScreen(int nIndex);

	//设置OSD
	void SetOSD(int nIndex);

	//获取view
	CMultiviewerView* GetView();

	//设置view
	void SetView(CMultiviewerView* pView);

	//设置是否为标签栏右键点击
	void SetIsMenuSet(BOOL b);

	//获取是否为标签菜单右键点击
	BOOL GetIsMenuSet();

	//根据序号获取信号个数
	int GetSignalCountByIndex(int nIndex);

	//根据序号设置预览框中RTSP计数为1
	void SetFrameRTSPCountByIndex(int nInputIndex);

	//根据序号获取板卡类型
	int GetBoardTypeByReStatus(int nStatus);

	int GetInputTypeByReStatus(int nStatus);

	BOOL JudgeIsCanOpenScene();

public:

	//获取屏幕集合
	VEC_SCREEN& GetVecScreen();

	//获取输入信号集合
	VEC_INPUTSIGNAL& GetVecInputSignal();

	//设置屏幕信息
	void SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo);

	//获取屏幕数据集合
	VEC_SCREENDATA& GetVecScreenData();

	//设置屏幕数据集合
	void SetVecScreenData(VEC_SCREENDATA& VecData);

	//获取办卡类别
	//MAP_BOARDTYPE& GetMapBoardType();

	MAP_INPUTTYPE& GetMapInputType();

	VEC_BASESCREENMANAGE& GetVecBaseScreenManage();


public:

	//获取屏幕动画参数
	XScreenMoveInfo* GetScreenMoveInfo();

	//轮询时间间隔
	XTimedPollingInfo* GetTimedPollingInfo();

	//所有分辨率
	XAllResulationInfo* GetAllResulationInfo();

	//右侧剪切
	XResulationHCutInfo* GetResulationHCutInfo();

	//底部剪切
	XResulationVCutInfo* GetResulationVCutInfo();

	//旧指令
	XOldOrderInfo* GetOldOrderInfo();


private:

	//初始化屏幕集合
	void InitVecScreen();

	//初始化场景屏幕集合
	void InitSceneVecScreen();

	//根据分辨率重置屏幕区域
	void ResetScreenArray();

	void ResetScreenArrayByRow();

	void ResetScreenArrayByCol();

	//获取鼠标
	HCURSOR GetCursor(CURSORTYPE type);

	//设置鼠标
	void SetCursor(CURSORTYPE type);

	//显示屏幕菜单
	void ShowScreenMenu();

	//显示信号菜单
	void ShowSignalMenu();

	//删除所有信号
	void DeleteAllSignal();

	//删除所有Frame
	void DeleteAllFrame();

	//更新同步时间
	void UpdateSynTime();

	//根据屏幕个数改变重置数据
	void ResetDataByScreenCountChange();

	//是否能添加信号
	BOOL CanAddNewSignal(VEC_SCREEN& VecScreen);

	//是否能添加信号
	BOOL CanAddNewSignal(VEC_RECTF& VecRectF);

	//是否能移动信号
	BOOL CanMoveSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID);

	//是否能移动信号
	BOOL IsCanMoveSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID);

	//恢复屏幕信号个数
	void ResetSignalNumInScreen();

	//是否能移动信号
	BOOL CanMoveSignal(VEC_RECTF& VecDragRectF,VEC_UNINT& VecSignalID,unsigned int GroupID);

	//是否能添加信号
	BOOL IsCreateNewSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID);

	//判断输入是否有信号
	BOOL IsHaveSignal(int nIndex);

	//判断输入是否插入面板
	BOOL IsHavePane(int nIndex);

	//根据序号获取屏幕
	XScreen* GetScreenByIndex(int nIndex);

	//根据板卡号获取屏幕序号
	void GetScreenIndexByPaneIndex(int& nPaneIndex,int& nNum,int& nScreenIndex);

	//根据板卡号获取屏幕序号
	void GetScreenIndexByPaneIndex(int& nPaneIndex,int& nScreenIndex);

	//同步获取屏幕分辨率
	BOOL GetScreenResulation(int nIndex,int& nH,int& nV);

	//同步获取屏幕分辨率
	BOOL GetSignalResulation(int nIndex,int& nH,int& nV);

	//切换输入
	void ChangeInput(XInputSignal*& pInputSignal,RECTF& rect,BOOL bResIsUltra);

	//校验和
	unsigned short CheckNum(char* pData,int nLen);

	//校验码校验
	BOOL CheckSumNum(char* pData,int nLen);

	//获取信号ID和序号集合
	void SetVecInputSignalIndexAndID(XSignal* pSignal);

	//生成4个RTSP
	void CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd);

	//创建RTSP到集合
	void CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd,VEC_CSTRING& Vec);

	//区域分块（4块）
	void SetRectToFoure(RECTF rect,VEC_RECTF& VecRect);

	//区域分块（两块）
	void SetRectToTwo(RECTF rect,VEC_RECTF& VecRect);

	//输入分辨率分块
	void SetInputResulationToFoure(RECTF rect,VEC_RECTF& VecRect);

	//计算每个信号所占屏幕
	void CalculateVecScreen(RECTF rect,VEC_SCREEN& VecScreen);

	//根据组ID获取ID集合
	void GetVecSignalID(unsigned int nGroupID,VEC_UNINT& VecInt);

	//根据组ID获取ID集合
	void GetVecSignalIndex(unsigned int nGroupID,HYVEC_NUM& VecInt);

	//创建拖动Frame
	void AddDragFrame(RECTF rectInter);

	//设置Frame显示或隐藏
	void SetPreviewFrameShow(unsigned int nGroupID,BOOL bShow);

	//判断是否为标签页菜单设置
	void DecideIsMenuSet(BOOL bIsMenuSet);

	//判断输入源是否为4K
	void JudgetInputIsultra(int nInputIndex);

	//删除其他三个信号（4k切2k,移动）
	void DeleteAnotherSignalByGroupID(unsigned int nSignalGroupID,unsigned int nSignalID);

	//所选信号ID置顶
	void SetSelectSignalIDTopInVecDrag(unsigned int nSignalID);

	//重置RTSP计数
	void SetRTSPAddrCountReset();

	//打开场景（处理预览墙）
	void AddScene();

	void AddSceneToCopyScene(XScreenManage* pTemp,CString szPath);

	//更新拼接模式工具栏按键状态
	void UpdateControlUIByStatus(CCmdUI* pCmdUI,int nStatus);

	//更新拖拽模式工具栏按键状态
	void UpdateControlUIByModel(CCmdUI* pCmdUI,int nModel);

	//拖拽拼接
	BOOL DragSplicInfo(CRect rc, XDragInfo* pInfo);

	//拖拽矩阵
	BOOL DragMatrixInfo(CRect rc, XDragInfo* pInfo);

	//拖拽拼接
	BOOL DragSplicInfo(CRect rc, XRTSPInfo* pInfo);

	//拖拽矩阵
	BOOL DragMatrixInfo(CRect rc, XRTSPInfo* pInfo);

	//根据板卡以及屏幕分配序号获取屏幕
	XScreen* GetScreenByBoardIndex(int nBoardIndex,int nChenal);

	//获取矩阵信号ID(全局ID)
	unsigned int GetMatrixSignalID();

	//设置矩阵信号ID
	void SetMatrixSignalID(unsigned int nID);

	//根据区域获取要删除信号组ID
	void GetDeleteSignalByCount(RECTF rect,int nType,MAP_GROUPID& Map);

	//设置信号选中
	void SetSignalSelectByGroupID(unsigned int nGroupID);

	//设置Frame选中
	void SetFrameSelectByGroupID(unsigned int nGroupID);

	//按照新分辨率重新开窗
	void ResetSignalByNewResulation();

	CString GetRTSPAddrFromPreviewPane(int nSignalIndex);

	void SetScreenWidthAndHight();

public:

	//清除屏幕集合
	void ClearVecScreen();

	//清除发送缓存集合
	void ClearVecSendData();

	//清除屏幕数据集合
	void ClearVecScreenData();

	void ClearVecScreenInfo();

	//清除板卡类别
	void ClearMapBoardType();

	//清除拖动窗口
	void ClearDragFrame();

	void ClearReMapRTSP();

	//释放局部放大信息
	void ClearExpandInfo();

	void ClearInputType();

	void ClearRowInfo();

	void ClearColInfo();

private:

	//更新水平输出个数显示
	void UpdateControlDataShowOfOutputCountH(CMFCRibbonEdit* p);

	//水平输出个数改变
	void ControlDataChangeOfOutputCountH(CMFCRibbonEdit* p);

	void UpdateControlDataShowOfScale(CMFCRibbonComboBox* pCombox);

	//更新垂直输出个数显示
	void UpdateControlDataShowOfOutputCountV(CMFCRibbonEdit* p);

	void ControlDataChangeOfScale(CMFCRibbonComboBox* pCombox);

	//垂直输出个数改变
	void ControlDataChangeOfOutputCountV(CMFCRibbonEdit* p);

	//信号置顶
	void OperateOfTopSignal();

	//信号置底
	void OperateOfBottomSignal();

	//信号上移
	void OperateOfShiftUPSignal();

	//信号下移
	void OperateOfShiftDownSignal();

	//信号扩展
	void OperateOfExpandSignal();

	//切换输入源
	void OperateOfChangeInput();

	//删除信号
	BOOL OperateOfCloseSignal();

	//删除所有信号
	void OperateOfDeleteAllSignal();

	//滚动画面
	void OperateOfSetScreenMove();

	//设置定时轮询时间间隔
	void OperateOfSetTimedPolling();

	//设置屏幕分辨率
	void OperateOfSetScreenResulation();

	//屏幕分辨率
	void OperateOfScreenResulation();

	//屏幕属性
	void OperateOfScreenAttribute();

	//发送数据获取屏幕参数
	void OperateOfGetScreenParamater();

	//获取的屏幕参数(矩阵)
	void OperateOfSetScreenParamaterOfMatrix(char* pData);

	//获取所有信号参数
	void OperatorOfGetSignalParamater();

	//获取窗口配置
	void OperatorOfGetWindowParamater();

	//设置窗口配置
	void OperatorOfSetWindowParamater(char* pData);

	//设置获取的信号参数
	void OperateOfSetSignalParamater(char* pData);

	//获取的屏幕参数
	void OperateOfSetScreenParamater(char* pData);

	//获取屏幕滚动应答
	void OperatorOfSetScreenMoveAsk(char* pData);

	//设置场景序号
	void OperatorOfSetSceneIndex(char* pData);

	//设置设备状态
	void OperateOfSetDeviceStatus(char* pData);

	//保存场景
	void OperateOfSaveScene();

	//打开场景
	void OperateOfOpenScene();

	//删除场景
	void OperateOfDeleteScene();

	//获取场景序号
	void OperateOfGetSceneIndex();

	//获取设备状态
	void OperateOfGetDeviceStatus();

	//执行旧指令
	void OperateOfRunOldOrder();

	//交换屏幕
	void OperateOfChangeScreen();

	//标签页菜单（设置屏幕）
	void OperateMenuScreenSet();

	//标签页菜单（保存场景）
	void OperateMenuSaveScene();

	//获取输入信号序号
	void OperateOfGetInputNum();

	//设置输入信号序号
	void OperateOfSetInputNum(char* pData);

	//设置普通状态
	void OperateOfSetNormal();

	//设置全屏状态
	void OperateOfSetFull();

	//设置四等分模式
	void OperateOfSetFour();

	//设置满屏模式
	void OperateOfSetInter();

	//设置复制模式
	void OperateOfSetCopyModel();

	//设置限制拖拽模式
	void OperateOfSetTipModel();

	//设置删除顶层拖拽模式
	void OperateOfSetUpModel();

	//删除底层拖拽模式
	void OperateOfSetDownModel();

	//设置屏幕分辨率（矩阵）
	void OperateOfSetScreenResulationByMatrix();

	//同步矩阵
	void OperateOfSetMatrixWindowParamater(char* pData);

	//设置行分辨率
	void OperateOfSetRowDpi();

	//设置列分辨率
	void OperateOfSetColDpi();

public:

	inline int GetScreenCountH(){return m_nScreenCountH;}

	inline void SetScreenCountH(int n){m_nScreenCountH=n;}

	inline int GetScreenCountV(){return m_nScreenCountV;}

	inline void SetScreenCountV(int n){m_nScreenCountV=n;}

	inline int GetResolutionH(){return m_nResolutionH;}

	inline void SetResolutionH(int n){m_nResolutionH=n;}

	inline int GetResolutionV(){return m_nResolutionV;}

	inline void SetResolutionV(int n){m_nResolutionV=n;}

	inline int GetDragStatus(){return m_nStatus;}

	inline void SetDragStatus(int n){m_nStatus=n;}

	inline int GetDragModel(){return m_nDragModel;}

	inline void SetDragModel(int n){m_nDragModel=n;}

private:

	//视图名称
	CString m_ViewName;

	//屏幕开始序号
	int m_BeginIndex;

	//显示类型
	int m_ShowType;

	//同步时间
	DWORD m_SynTime;

	//鼠标按下位置
	POINTF m_Point;

	//屏幕缓存
	XScreen* m_TempScreen;

	//水平个数
	int m_nScreenCountH;

	//垂直个数
	int m_nScreenCountV;

	//水平分辨率
	int m_nResolutionH;

	//垂直分辨率
	int m_nResolutionV;

	//右侧剪切
	int m_nRightResulationH;

	//底部剪切
	int m_nBottomResulationV;

	//鼠标类型
	CURSORTYPE m_CursorType;

	//鼠标在信号的位置,用于拉伸信号
	POSITIONTYPE m_PositionType;

	//视图鼠标按下
	BOOL m_ISViewButtonDown;

	//信号所有区域和用于鼠标样式和创建矩形窗口
	RECTF m_InterRect;

	//整体区域移动后区域
	//RECTF m_NewRect;

	//是否缓存完成
	BOOL m_IsSendPocket;

	//右键信号序号用于信号切换
	int m_RBtnIndex;

	//右键信号ID用于右键操作
	unsigned int m_RBtnSignalID;

	//右键信号组ID
	unsigned int m_RBtnSignalGroupID;

	//双击信号序号用于信号切换
	int m_LBDIndex;

	//双击信号ID用于右键操作
	unsigned int m_LBDSignalID;

	//双击信号组ID
	unsigned int m_LBDSignalGroupID;
	
	//屏幕滚动应答数据
	char* pAskData;

	//屏幕移动对话框
	XScreenMoveDlg* m_pScreenMoveDlg;

	//保存场景对话框
	XSaveScence m_SaveSceneDlg;

	//是否双击
	BOOL m_bIsLBDClick;

	//是否移动
	BOOL m_bIsMoveSignal;

	//RTSP地址（用于移动）
	CString m_szRBRTSPAddr;

	//IP地址（用于移动）
	CString m_szRBIPAddr;

	//是否需要赋值
	BOOL m_bIsMenuSet;

	//屏幕模式
	int m_nScreenModel;

	//拖拽状态
	int m_nStatus;

	//拖拽模式
	int m_nDragModel;

	//当前屏幕管理缩放
	int m_nCurScale;

	//是否创建信号（拖动）
	BOOL m_bCreateSignal;

	//没改之前分辨率
	int m_nPreResolutionH;

	int m_nPreResolutionV;

private:

	//移动时拖拽信息
	XDragInfo m_DragInfo;

	//屏幕滚动画面
	XScreenMoveInfo m_MoveInfo;

	//定时轮询
	XTimedPollingInfo m_PollingInfo;

	//所有分辨率
	XAllResulationInfo m_AllInfo;

	//旧指令
	XOldOrderInfo m_OldOrderInfo;

	//菜单屏幕设置
	XMenuScreenSetInfo m_ScreenSetInfo;

	//剪切分辨率
	XResulationHCutInfo m_ResulationHInfo;

	//底部剪切
	XResulationVCutInfo m_ResulationVInfo;

private:

	//屏幕集合
	VEC_SCREEN m_VecScreen;

	//发送数据集合
	VEC_SENDDATA m_VecSendData; 

	//屏幕数据集合
	VEC_SCREENDATA m_VecScreenData;

	//屏幕信息集合
	VEC_SCREENINFO m_VecScreenInfo;

	//拖动Frame
	VEC_MULTIVIDEOWINDOWFRAME m_VecDragFrame;

	//板卡类别
	MAP_BOARDTYPE m_MapBoardType;

	//输入卡类型
	MAP_INPUTTYPE m_MapInputType;

	//保存局部放大
	VEC_EXPANDINFO m_VecExpandInfo;

	//同步RTSP地址
	MAP_RERTSPADDR m_MapReRTSPAddr;

	MAP_ROWINFO m_MapRowInfo;

	MAP_COLINFO m_MapColInfo;
};

