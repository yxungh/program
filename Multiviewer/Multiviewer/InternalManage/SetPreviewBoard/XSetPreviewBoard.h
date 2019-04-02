#pragma once

#include "../resource.h"
#include "XPreviewChild.h"


class XDelegateSetPreviewBoard;
class XInternalManage;


class XSetPreviewBoard : public CDialogEx
{
	DECLARE_DYNAMIC(XSetPreviewBoard)

public:
	XSetPreviewBoard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetPreviewBoard();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSetPreviewBoard* p);

	void SetBaseManage(XInternalManage* p);

	void InitData();

	void InitChildDlg();

	void OnSplitNetSet();

	void OnSplitBiteRate();

	void SetButtonStatus(BOOL b);

public:

	void OperateOfReadPreviewNet(char* pData);

	void OperateOfReadPreviewBitRate(char* pData);

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateSetPreviewBoard* m_pDelegate;

	XInternalManage* m_pBaseManage;

	XPreviewChild m_PreviewDlg;
};
