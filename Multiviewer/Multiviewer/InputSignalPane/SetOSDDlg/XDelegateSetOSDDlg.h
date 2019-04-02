#pragma once

class XDelegateSetOSDDlg
{
public:
	XDelegateSetOSDDlg(void);
	~XDelegateSetOSDDlg(void);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	//获取网络状态
	virtual BOOL GetNetState() = 0;
};

