#pragma once

#include "../resource.h"
#include "HYXText.h"
#include "HYXInputNode.h"
#include "HYXOutputNode.h"
#include "HYXGrid.h"
#include "HYXDelegateInputNode.h"
#include "HYXDelegateOutputNode.h"
#include "HYXDelegateGrid.h"

class XUserManage;
class XUserInfo;

#define NOTICETEXT_HEIGHT			40			//提示文字高度
#define INPUTNODERECT_HEIGHT		50			//输入节点高度
#define OUTPUTNODERECT_WIDTH		120			//输出结点宽度

// CUserPowerManageDlg 对话框

class CUserPowerManageDlg : public CDialogEx, 
							public HYXDelegateInputNode, 
							public HYXDelegateOutputNode, 
							public HYXDelegateGrid
{
	DECLARE_DYNAMIC(CUserPowerManageDlg)

public:
	CUserPowerManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserPowerManageDlg();

	virtual BOOL OnInitDialog();

	virtual void OnOK();

// 对话框数据
	enum { IDD = IDD_DLG_USERPOWERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:

	void SetUserManage(XUserManage* p);

	void SetUserInfo(XUserInfo* p);

private:

	//重载界面
	void ReloadInterface();

	//设置对话框区域
	void SetDlgRect();

	//初始化提示文字
	void InitNoticeText();

	//初始化输入节点
	void InitInputNodes();

	//初始化输出节点
	void InitOutputNodes();

	//初始化表格
	void InitGrid();

private:

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault);

	//调整网格
	virtual void AdjustGrid();

	//调整水平滚动
	virtual void AdjustScrollH();

	//调整水平滚动
	virtual void AdjustScrollV();

	//获取滚动宽度
	virtual int GetScrollWidth();

	//获取滚动高度
	virtual int GetScrollHeight();

	//水平滚动
	virtual void ScrollH(int nPos);

	//垂直滚动
	virtual void ScrollV(int nPos);

	//获取输入展开设备项集合
	virtual void GetInputExpandDeviceItem(HYVEC_TREENODEITEM& VecItem);

	//获取输出展开设备项集合
	virtual void GetOutputExpandDeviceItem(HYVEC_VTREENODEITEM& VecItem);

	//表格音频区域点击
	virtual void GridRectClick(HYXGridItem* pItem);

	//表格右键弹起
	virtual void GridRButtonUp();

	//获取节点权限
	virtual BOOL GetNodePower(int nInputIndex, int nOutputIndex);

private:

	XUserManage* m_UserManage;

	XUserInfo* m_UserInfo;

	HYXText m_NoticeInputNode;

	HYXText m_NoticeOutputNode;

	//输入节点
	HYXInputNode m_InputNode;

	//输出节点
	HYXOutputNode m_OutputNode;

	//表格
	HYXGrid m_Grid;
};
