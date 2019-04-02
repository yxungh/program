#pragma once

class XDelegateAboutDlg
{
public:
	XDelegateAboutDlg(void);
	~XDelegateAboutDlg(void);

	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;
};

