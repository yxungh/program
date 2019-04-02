#pragma once

#include "XConstantIM.h"
#include "XBaseChildManage.h"

class XDelegateScreenManage;
class XDragInfo;
class XRTSPInfo;
class CMultiviewerView;
class XMultiVideoWindow;
class XMenuScreenSetInfo;

class XBaseScreenManage : public XBaseChildManage
{
public:
	XBaseScreenManage(void);
	virtual ~XBaseScreenManage(void);

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl) = 0;

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type, void* pControl) = 0;

	//获取数据
	virtual void GetData(CArchive& arch) = 0;

	//保存数据
	virtual void SaveData(CArchive& arch) = 0;

	//重置数据
	virtual void ResetData() = 0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData) = 0;

	//更新控件UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI) = 0;

	//拖动信息
	virtual BOOL DragInfo(CRect rc,CPoint point,XDragInfo* pInfo) = 0;

	//拖动信息
	virtual BOOL DragInfo(CRect rc, XRTSPInfo* pInfo) = 0;

	//获取输出个数
	virtual int GetOutputCount() = 0;

	//设置视图名称
	virtual void SetViewName(CString szName)=0;

	//获取视图名称
	virtual CString GetViewName()=0;

	//获取屏幕配置信息
	virtual XMenuScreenSetInfo* GetMenuScreenSetInfo()=0;

	//双击打开场景
	virtual void OpenScene(CString szSceneName,int nSceneIndex,CString szViewName)=0;

	//鼠标滚轮
	virtual BOOL AddScalingByMouseWheel(short zDelta)=0;

	virtual void DeleteScene(int nSceneIndex)=0;

	virtual void ResetViewSize()=0;

	virtual void InvalidateView()=0;

	virtual void ShowMenu(CPoint& point)=0;

	virtual void AdjustMultiVideoWindowSize()=0;

	virtual VEC_SCREEN& GetVecScreen1()=0;

	virtual int GetRTSPCountBySignal(CString szRTSP)=0;

	virtual CString SetText(XScreen* pScreen)=0;

	virtual void SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP)=0;

	virtual void ReLoadInterface()=0;

	virtual float GetMultiScale()=0;

	virtual int GetFramesCountH()=0;

	virtual int GetFramesCountV()=0;

	virtual int GetFramesResulationH()=0;

	virtual int GetFramesResulationV()=0;

	virtual int GetFramesRightResulationH()=0;

	virtual int GetFramesBottomResulationV()=0;

	virtual MAP_BOARDTYPE& GetMapBoardType()=0;

	virtual void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)=0;

	virtual void SetBeginIndex(int n)=0;

	virtual void SetScreenModel(int n)=0;

	virtual int GetScreenModel()=0;

	virtual void OnBtnNewScene()=0;

	virtual void SaveSceneByCloseView()=0;

	virtual void SaveAllScene(CString szSceenName,int nSceneIndex,CString szSceneGroup,int nIndex,int nType)=0;

	virtual void OpenAllScene(CString szSceneName,int nSceneIndex,int nIndex,int nType,CString szViewName=_T(""))=0;

	virtual void CopyOrderToShare(CString szSceneName,int nSceneIndex,int nIndex,CString szViewName)=0;

	virtual void CopySingleOrderToShare(CString szSceneNane,int nSceneIndex,CString szViewName)=0;

	virtual void SetMultiScale(float f)=0;

	virtual XDragInfo& GetDragInfo()=0;

	virtual void SetScreenByDbClick()=0;

	virtual MAP_COLINFO& GetMapColInfo()=0;

	virtual MAP_ROWINFO& GetMapRowInfo()=0;

public:

	CString GetTitle();

	CMultiviewerView* GetView();

	void SetTitle(CString s);

	void SetView(CMultiviewerView* p);

	void SetMultiVideoWindow(XMultiVideoWindow* p);

	XMultiVideoWindow* GetMultiVideoWIndow();

public:

	//设置委托
	void SetDelegate(XDelegateScreenManage* p);

	XDelegateScreenManage* GetDelegate();

protected:

	//委托
	XDelegateScreenManage* m_pDelegate;

	CString m_szTitle;

	CMultiviewerView* m_View;

	XMultiVideoWindow* m_pMultiVideoWindow;
};

