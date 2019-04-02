#pragma once

class XDelegateInternalManage
{
public:
	XDelegateInternalManage(void);
	~XDelegateInternalManage(void);

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//获取窗口句柄
	virtual HWND GetHWND() = 0;

	//显示消息对话框
	virtual int MessageBox(CString szText, CString szCaption, UINT uType) = 0;

	//重设视图大小
	virtual void ResetViewSize() = 0;

	//刷新视图
	virtual void InvalidateView() = 0;

	//获取视图
	virtual CView* GetView() = 0;
};

