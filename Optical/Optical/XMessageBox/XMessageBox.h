#pragma once

class XMessageBox
{
private:
	XMessageBox();
	~XMessageBox();

public:

	static XMessageBox* GetInstance();

	static void Release();

	int MessageBoxByKey(CString szTextKey,CString szDefault,UINT uType);

	int MessageBox(CString szText,CString szCaption,UINT uType);

private:

	static XMessageBox* m_pMessageBox;
};