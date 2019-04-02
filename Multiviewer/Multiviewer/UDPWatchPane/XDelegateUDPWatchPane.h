#pragma once

class XDelegateUDPWatchPane
{
public:
	XDelegateUDPWatchPane(void);
	~XDelegateUDPWatchPane(void);

	//获取CWnd
	virtual CWnd* GetCWND() = 0;

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;
};

