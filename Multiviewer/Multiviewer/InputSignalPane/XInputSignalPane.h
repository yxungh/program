#pragma once

#include "XDelegateAddExpandDlg.h"
#include "XDelegateEditExpandDlg.h"
#include "XDelegateSetOSDDlg.h"
#include "XDelegateInputSignalCutDlg.h"
#include "XDelegateBorderOverlayDlg.h"
#include "XDelegateAttributeDlg.h"
#include "XInputSignalTreeCtrl.h"
#include "XDelegateEDIDDlg.h"
#include "XConstantIM.h"
#include "XDelegateSetAnotherNameDlg.h"
#include "XDelegateChangeChanelDlg.h"
#include "XDelegateUltraAttributeDlg.h"
#include "XDelegateStreamAddr.h"
#include "XDelegatePaneIPAddr.h"
#include "XStreamAddr.h"
#include "XPaneIPAddr.h"
#include "XDelegateAddGroup.h"


class XDelegateInputSignalPane;
class XDragInfo;


// XInputSignalPane

class XInputSignalPane : public CDockablePane, 
	public XDelegateAddExpandDlg,
	public XDelegateEditExpandDlg,
	public XDelegateSetOSDDlg,
	public XDelegateInputSignalCutDlg,
	public XDelegateBorderOverlayDlg,
	public XDelegateAttributeDlg,
	public XDelegateEDIDDlg,
	public XDelegateSetAnotherNameDlg,
	public XDelegateChangeChenalDlg,
	public XDelegateUltraAttributeDlg,
	public XDelegateStreamAddr,
	public XDelegatePaneIPAddr,
	public XDelegateAddGroup
{
	DECLARE_DYNAMIC(XInputSignalPane)
public:

	XInputSignalPane();
	virtual ~XInputSignalPane();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelExpand();
	afx_msg void OnAddExpand();
	afx_msg void OnEditExpand();
	afx_msg void OnSetDefaultExpand();
	afx_msg void OnSetOSD();
	afx_msg void OnInputSignalCut();
	afx_msg void OnBorderOverlay();
	afx_msg void OnSetEDID();
	afx_msg void OnAttribute();
	afx_msg void OnSetAnotherName();
	afx_msg void OnChangeAnotherName();
	afx_msg void OnSelectChanel();
	afx_msg void OnIPStreamAddr();
	afx_msg void OnPaneIPSet();
	afx_msg void OnAddGroup();
	afx_msg void OnDelFromGroup();
	afx_msg void OnDeleteGroup();
	afx_msg void OnChangeGroup();

	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateInputSignalPane* pDelegate);

	//获取委托
	XDelegateInputSignalPane* GetDelegate();

	//重置数据
	void ResetData();

	//重载界面
	void ReloadInterface();

	//获取数据
	void GetData(CArchive& arch);

	//保存数据
	void SaveData(CArchive& arch);

	//操作
	void Operate(OPERATETYPE type, void* pData);

	//更新控件数据显示
	void UpdateControlDataShow(XDATATYPE type, void* pControl);

	//控件数据改变
	void ControlDataChange(XDATATYPE type, void* pControl);

	//重置数据（场景）
	void ResetDataOfScene();

	void ResetDataBySceneInputCountChange();

	//创建拖动窗口
	XDragWnd* CreateDragWnd(XDragInfo* pInfo);

	//拖动信息
	void DragInfo(CRect rc,CPoint point,XDragInfo* pInfo);

	//发送数据
	BOOL SendData(char* pData, int nDataLen);

	//获取网络状态
	BOOL GetNetState();

	//获取输入个数
	int GetInputCount();

	//设置输入个数
	void SetInputCount(int n);
	
	//判断是否有信号
	BOOL IsHaveSignal(int nIndex);

	//判断是否有设备
	BOOL IsHavePan(int nIndex);

	//是否为4K
	void IsUltra(int nIndex);

	//是否为IP预览卡
	BOOL IsIpPreview(int nIndex);

	//刷新输入信号图标
	void RefreshInputIcon();

	//根据序号获取输入名称
	CString GetInputNameByIndex(int nIndex);

	//根据序号获取Input
	XInputSignal* GetInputByIndex(int nIndex);

	//设置预览窗口别名
	void SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName);

	//设置预览窗口别名
	void SetPreviewNameByAnotherName();

	void SetInputRTSPAddrByIndex(int nIndex,CString szRTSP);

	void SetInputParaByIndex(int nIndex,CString szIP,CString szUseName,CString szPassWd);

	void SetInputSignalPara();

	//组名称是否存在
	BOOL IsNameHas(CString szName);

	//改变输入树状态
	void ChangeInputModel();

	XInputSignal* GetInputSignalByIndex(int nIndex);

	int GetInputIndexByItemName(CString szItemText);

	//处理输入信号拖拽
	void AddDragIntoGroup(const HTREEITEM& itemDragS,const HTREEITEM& itemDragD);

	void SetOSD(XInputSignal* pInputSignal);

	//设置选中输入信息
	BOOL SetSelInputDataInfo();

	//获取拖拽信息
	XDragInfo& GetDragInfo();

public:

	//获取输入信号集合
	VEC_INPUTSIGNAL& GetVecInputSignal();

	//获取组集合
	MAP_GROUP& GetMapGroup();

private:

	//创建Pane
	void CreatePane();

	//初始化树形控件
	BOOL InitTreeCtrl();

	//初始化图片列表
	BOOL InitImageList();

	//初始化输入信号
	void InitInputSignal();

	//调整布局
	void AdjustLayout();

	//重载界面-树
	void ReloadInterfaceOfTree();

	//是否输入信号项
	BOOL IsInputSignalItem(HTREEITEM item);

	void ShowMenuOfInputSignal();

	void ShowMenuOfInputSignalExpand();

	void ShowMenuOfInputGroup();

	//调整输入信号局部放大图像
	void AdjustInputSignalExpandImage(XInputSignal* pInputSignal);

	//更新输入个数显示
	void UpdateControlDataShowOfInputCount(CMFCRibbonEdit* p);

	//输入个数改变
	void ControlDataChangeOfInputCount(CMFCRibbonEdit* p);

	//重置输入信号
	void ResetInputSignal();

	void CopyAnotherNameByVecInput(VEC_NAMEINFO& VecNameInfo);

	void CopyAnotherNameToVecInput(VEC_NAMEINFO& VecNameInfo);

	void OperateOfReadPaneIP(char* pData);

	void OperateOfReadStreamAddr(char* pData);

	BOOL CheckSumNum(char* pData,int nLen);

	unsigned short CheckNum(char *pData,int nLen);

	void SetAnotherName(XInputSignal* pInput,CString szAnotherName);

	void SetAnotherNameInOther(XInputSignal* pInput,CString szAnotherName);

	void ChangeInputAnotherNameInGroup(int nInputIndex,CString szAnotherName);

	void ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName);

	void InsertInputSignal(XInputSignal* pInputSignal,HTREEITEM itemRoot=NULL);

	CString GetGroupNameByFrontName(CString szName);

	int GetInputTypeByReStatus(int nStatus);

private:

	//清除输入信号集合
	void ClearVecInputSignal();

	//清除别名集合
	void ClearNameInfo();

	//清除组
	void ClearInputGroup();

	//清除图片集合
	void ClearImageList();

public:

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

private:

	//委托
	XDelegateInputSignalPane* m_pDelegate;

	//树形控件
	XInputSignalTreeCtrl m_TreeCtrl;

	//图片列表
	CImageList m_ImageList;

	//鼠标右键输入信号
	XInputSignal* m_RBInputSignal;

	//鼠标右键输入信号局部放大
	XInputSignalExpand* m_RBInputSignalExpand;

	//输入个数
	int m_InputCount;

	//右键选中树节点
	HTREEITEM m_RBItem;

private:

	//视频流对话框
	XStreamAddr m_StreamAddrDlg;

	//板卡网络对话框
	XPaneIPAddr m_PaneIPAddrDlg;

private:

	//输入信号集合
	VEC_INPUTSIGNAL m_VecInputSignal;

	//别名集合
	VEC_NAMEINFO m_VecNameInfo;

	//组集合
	MAP_GROUP m_MapGroup;
};


