#pragma once

class XDelegateMessageBoxDlg
{
public:
	XDelegateMessageBoxDlg(void);
	~XDelegateMessageBoxDlg(void);

	//»ñÈ¡×Ö·û´®
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;
};

