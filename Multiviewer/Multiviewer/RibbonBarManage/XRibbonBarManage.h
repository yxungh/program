#pragma once

#include "XBaseRibbonBarManage.h"
#include "XRibbonBar.h"
#include "XDelegateRibbonBar.h"

class XRibbonBarManage : public XBaseRibbonBarManage, XDelegateRibbonBar
{
public:
	XRibbonBarManage(void);
	~XRibbonBarManage(void);

	//初始化
	virtual void Init();

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type);

	//重载界面
	virtual void ReloadInterface();

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type);

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(CString szName);

	//操作
	void Operate(OPERATETYPE type, void* pData);

private:

	//初始化RibbonBar
	void InitRibbonBar();

	//初始化状态栏
	void InitStatusBar();

	//初始化RibbonBar
	void InitRibbonBar(CMFCRibbonBar* pRibbonBar);

	BOOL InitImageList();

	//获取CWnd
	CWnd* GetCWND();

	//获取字符串
	CString GetTranslationString(CString szKey, CString szDefault);

	//更新所有控件数据显示
	void UpdateControlDataShowOfAll();

	//设置温度信息
	void SetTemperatureInfo(CString s);

	void SetPanInfo(CString s);

	void SetChipInfo(CString s);


private://工具栏页面 

	XRibbonBar m_wndRibbonBar;

	//主页
	CMFCRibbonCategory* m_pCategoryMain;

private:

	CMFCRibbonStatusBar m_wndStatusBar;

private:

	//关闭
	CMFCRibbonButton* m_pBtnAbout;

private:

	//主设置
	CMFCRibbonPanel* m_pPanelMainSet;

	//新建视图
	CMFCRibbonButton* m_pBtnNewView;

	//关闭视图
	CMFCRibbonButton* m_pBtnCloseView;

	//切换视图
	//CMFCRibbonComboBox* m_pComboBoxView;

	//语言名称
	CMFCRibbonComboBox* m_pComboBoxLanguage;

	//比例
	CMFCRibbonComboBox* m_pComboBoxScale;

private:

	//场景
	CMFCRibbonPanel* m_pPanelMainScene;

	//保存场景
	CMFCRibbonButton* m_pBtnSaveScence;

	//打开场景
	CMFCRibbonButton* m_pBtnOpenScence;

	//删除场景
	CMFCRibbonButton* m_pBtnDeleteScence;

private:

	//操作
	CMFCRibbonPanel* m_pPanelMainOperator;

	//删除所有信号
	CMFCRibbonButton* m_pBtnDeleteAllSignal;

	//设置定时轮询
	CMFCRibbonButton* m_pBtnTimedPolling;

	//屏幕滚动
	CMFCRibbonButton* m_pBtnScreenMove;

	//设置输出分辨率
	CMFCRibbonButton* m_pBtnScreenResulation;

	//旧指令
	CMFCRibbonButton* m_pBtnOldOrder;

private:

	//场景
	CMFCRibbonPanel* m_pPanelScene;

	//多页面场景
	CMFCRibbonButton* m_pBtnInterScene;

	//单页面场景
	CMFCRibbonButton* m_pSingleScene;

private:

	//预览
	CMFCRibbonPanel* m_pPanelMainPreview;

	CMFCRibbonButton* m_pBtnPreview;

private:
	
	//网络面板
	CMFCRibbonPanel* m_pPanelMainNet;

	//打开网络
	CMFCRibbonButton* m_pBtnOpenNet;

	//关闭网络
	CMFCRibbonButton* m_pBtnCloseNet;
	
private:

	//设备面板
	CMFCRibbonPanel* m_pPanelMainDevice;

	//设备IP
	CMFCRibbonEdit* m_pEditDeviceIP;

	//设备端口
	CMFCRibbonEdit* m_pEditDevicePort;

private:

	//温度面板
	CMFCRibbonPanel* m_pPanelMainTemperature;

	//温度图标
	CMFCRibbonButton* m_pBtnTemperature;

private:

	//矩阵面板
	CMFCRibbonPanel* m_pPanelMainMultiviewer;

	//输入个数
	CMFCRibbonEdit* m_pEditInputCount;

	//水平输出个数
	CMFCRibbonEdit* m_pEditOutputCountH;

	//垂直输出个数
	CMFCRibbonEdit* m_pEditOutputCountV;

private:

	//用户面板
	CMFCRibbonPanel* m_pPanelMainUser;

	//登陆
	CMFCRibbonButton* m_pBtnLogin;

	//注销
	CMFCRibbonButton* m_pBtnLogout;

	//用户管理
	CMFCRibbonButton* m_pBtnUserManage;

	//权限管理
	CMFCRibbonButton* m_pBtnPowerManage;

private:

	//状态
	CMFCRibbonPanel* m_pPanelMainStatus;

	CMFCRibbonButton* m_pBtnPan;

	CMFCRibbonButton* m_pBtnChip;

private:

	//模式C
	CMFCRibbonPanel* m_pPaneModel;

	CMFCRibbonButton* m_pBtnNamal;

	CMFCRibbonButton* m_pBtnFull;

	CMFCRibbonButton* m_pBtnFoure;

	CMFCRibbonButton* m_pBtnInter;

	CMFCRibbonButton* m_pBtnCopy;

private:

	CMFCRibbonPanel* m_pPaneDrag;

	CMFCRibbonButton* m_pBtnTip;

	CMFCRibbonButton* m_pBtnUp;

	CMFCRibbonButton* m_pBtnDown;
};

