#pragma once

#include "XConstantIM.h"
#include "XInputSignalPane.h"
#include "XSceneTree.h"
#include "XDelegateReName.h"

class XDelegateScenePane;

// XScenePane

class XScenePane : public CDockablePane,
	               public XDelegateReName
{
	DECLARE_DYNAMIC(XScenePane)
public:

	XScenePane();
	virtual ~XScenePane();

	virtual BOOL CanBeClosed() const{return FALSE;};

	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod = DM_UNKNOWN, bool bShow = true) { return FALSE; }

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDblclkTreeVcard(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeleteScene();
	afx_msg void OnReSceneName();
	afx_msg void OnReMove();
	afx_msg void OnDeleteGroup();
	afx_msg void OnReNameGroup();

	afx_msg void OnCopyOrder();


	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateScenePane* pDelegate);

	//获取委托
	XDelegateScenePane* GetDelegate();

	//重载界面
	void ReloadInterface();

	//获取输入面板
	void SetInputSignalPane(XInputSignalPane* pPane);

	//添加场景到树
	HTREEITEM AddSceneToTree(int nSceneIndex,CString szSceneName,int nType,CString szSceneGroup);

	void AddViewNameToScene(HTREEITEM item,CString szSceneName,int nIndex,CString szViewName);

	//添加场景到组
	void AddSceneIntoGroup(HTREEITEM hItemDragS,HTREEITEM hItemDragD);

	//判断场景是否重名
	BOOL JudgeSceneName(CString szName);

	//获取场景集合
	MAP_SCENE& GetMapScene();

	//获取场景组
	MAP_SCENEGROUP& GetMapSceneGroup();

private:

	void ClearMapItem();

	void ClearMapItemName();

	void ClearMapScene();

	void ClearSceneGroup();

public:

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

	void ResetData();

private:

	//创建Pane
	void CreatePane();

	//初始化数据
	void InitData();

	//调整布局
	void AdjustLayout();

	//初始化树形控件
	BOOL InitTreeCtrl();

	//初始化图片列表
	BOOL InitImageList();

	//添加父节点
	HTREEITEM AddRoot(CString szRoot,int nType);

	//设置节点
	void SetItemRoot(HTREEITEM h);

	//获取根节点
	HTREEITEM GetItemRoot();

	//添加子节点
	HTREEITEM AddChild(CString szChild);

	//设置子节点
	void SetItemChild(HTREEITEM h);

	//获取子节点
	HTREEITEM GetItemChild();

	//添加子节点
	HTREEITEM AddChildChild(CString szChildChild);

	//设置子节点
	void SetItemChildChild(HTREEITEM h);

	//获取子节点
	HTREEITEM GetItemChildChild();

	//添加子节点
	HTREEITEM AddChildChildChild(CString szChildChild);

	//显示场景菜单
	void ShowMenu();

	//显示场景菜单
	void ShowCopyMenu();

	//显示场景组菜单
	void ShowGroupMenu();
	
	//根据场景名称获取场景信息类
	XSceneInfo* GetSceenInfoBySceneName(CString szSceneName);

	//获取默认组名称
	CString GetGroupNameByFrontName(CString szName);

	//改变场景树形态
	void ChangeSceneTreeModel();

	//判断场景是否再组内
	BOOL JudgeSceneIsInGroup(CString szName);

	//判断组内是否有场景
	BOOL JudgetGroupHaveScene(CString szGroupName);

private:

	//委托
	XDelegateScenePane* m_pDelegate;

	//输入面板
	XInputSignalPane* m_pInputSignalPane;

	//图片列表
	CImageList m_ImageList;

	//场景树
	XSceneTree m_SceneTree;

	//根节点
	HTREEITEM m_RootItem;

	//子节点
	HTREEITEM m_ChildItem;

	//子节点
	HTREEITEM m_ChildChildItem;

	//子节点
	HTREEITEM m_ChildChildChildItem;

	//右键树节点
	HTREEITEM m_RbItem;

	//场景名称
	CString m_szSceneName;

	//场景集合
	MAP_SCENE m_MapScene;

	//树节点集合
	MAP_ITEM m_MapItem;

	//场景组(需要保存)
	MAP_SCENEGROUP m_MapSceneGroup;

	//名称和节点集合
	MAP_ITEMNAME m_MapItemName;
};