#pragma once

#include "XConstantIM.h"
#include "XUDPWatchPaneToolBar.h"

class XDelegateUDPWatchPane;

// XUDPWatchPane

class XUDPWatchPane : public CDockablePane
{
	DECLARE_DYNAMIC(XUDPWatchPane)
public:

	XUDPWatchPane();
	virtual ~XUDPWatchPane();

	virtual BOOL CanBeClosed() const{return FALSE;};

	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod = DM_UNKNOWN, bool bShow = true) { return FALSE; }

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClear();
	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateUDPWatchPane* pDelegate);

	//重载界面
	void ReloadInterface();

	//添加UDP信息
	void AddUDPInfo(unsigned char* pData, int nDataLen);

public:

	//获取字符串
	CString GetTranslationString(CString szKey, CString szDefault);

private:

	//创建Pane
	void CreatePane();

	//调整布局
	void AdjustLayout();

	//初始化字体
	void InitFont();

	//初始化信息列表框
	BOOL InitListBoxInfo();

	//初始化工具栏
	BOOL InitToolBar();

	//添加信息
	void AddInfo(CString szInfo);

private:

	//委托
	XDelegateUDPWatchPane* m_pDelegate;

	//信息列表框
	CListBox m_ListBox_Info;

	//工具栏
	XUDPWatchPaneToolBar m_wndToolBar;

	//信息序号
	int m_InfoIndex;

	CFont m_Font;
};


