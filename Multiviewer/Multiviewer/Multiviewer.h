// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// Multiviewer.h : Multiviewer 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMultiviewerApp:
// 有关此类的实现，请参阅 Multiviewer.cpp
//

class CMDITabOptions
{
public:
	CMDITabOptions();

	enum MDITabsType
	{
		None,
		MDITabsStandard,
		MDITabbedGroups
	};


	MDITabsType			m_nMDITabsType;
	BOOL				m_bTabsOnTop;
	BOOL				m_bActiveTabCloseButton;
	CMFCTabCtrl::Style	m_nTabsStyle;
	BOOL				m_bTabsAutoColor;
	BOOL				m_bMDITabsIcons;
	BOOL				m_bMDITabsDocMenu;
	BOOL				m_bDragMDITabs;
	BOOL				m_bMDITabsContextMenu;
	int					m_nMDITabsBorderSize;
	BOOL				m_bDisableMDIChildRedraw;
	BOOL				m_bFlatFrame;
	BOOL				m_bCustomTooltips;

	void Load ();
	void Save ();

	BOOL IsMDITabsDisabled () const {return m_nMDITabsType == CMDITabOptions::None;}
};


class CMultiviewerApp : public CWinAppEx
{
public:
	CMultiviewerApp();
	~CMultiviewerApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CMDITabOptions	m_Options;

// 实现
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	

	DECLARE_MESSAGE_MAP()

private:

	ULONG_PTR m_TokenGdi;
};

extern CMultiviewerApp theApp;
