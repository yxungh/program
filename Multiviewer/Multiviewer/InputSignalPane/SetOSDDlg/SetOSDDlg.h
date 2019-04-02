#pragma once

#include "../resource.h"
#include "XDelegateOSDGrid.h"
#include "XOSDGrid.h"

class XDelegateSetOSDDlg;
class XInputSignal;
class XInputSignalPane;

// CSetOSDDlg 对话框

class CSetOSDDlg : public CDialogEx, public XDelegateOSDGrid
{
	DECLARE_DYNAMIC(CSetOSDDlg)

public:
	CSetOSDDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetOSDDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SETOSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSend();
	afx_msg void OnEnChangeEditText();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSetOSDDlg* p);

	//设置输入信号
	void SetInputSignal(XInputSignal* p);

	//设置输入信号面板
	void SetInputSignalPane(XInputSignalPane* p);

	//设置输入信号名称
	void SetInputSignalName(CString s);

public:

	void AddFont(CString s);

private:

	//重载界面
	void ReloadInterface();

	//初始化显示数据
	void InitShowData();

	//初始化字体
	void InitComboBoxFont();

	//初始化样式
	void InitComboBoxType();

	//创建OSD网格
	void CreateOSDGrid();

	//设置OSD字模
	void SetOSDMutrix();

	//调整位置
	void AdjustPos();


private:

	//委托
	XDelegateSetOSDDlg* m_pDelegate;

	//输入信号
	XInputSignal* m_InputSignal;

	//输入信号面板
	XInputSignalPane* m_InputSignalPane;

	//输入信号名称
	CString m_InputSignalName;

	CMFCColorButton m_Color;

	CMFCColorButton m_Color_Bk;

	CComboBox m_ComboBox_Font;

	CComboBox m_ComboBox_Type;

	CComboBox m_ComboBox_Center;

	XOSDGrid m_Grid;

	//对话框最小区域
	CRect m_DlgMinRect;

	//是否初始化对话框
	BOOL m_InitDlg;

	
};
