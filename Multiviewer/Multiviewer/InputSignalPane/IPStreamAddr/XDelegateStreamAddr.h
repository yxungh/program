#pragma once

class XDelegateStreamAddr
{
public:
	XDelegateStreamAddr(void);
	~XDelegateStreamAddr(void);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//根据KEY显示消息对话框
	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;
};