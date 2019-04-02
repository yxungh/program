#pragma once


class XStatusBar : public CWnd
{
	DECLARE_DYNAMIC(XStatusBar)

public:
	XStatusBar();
	virtual ~XStatusBar();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:

	//设置版本信息
	void SetVersion(CString szVersion);

	//设置信息
	void SetInfo(CString szInfo);

	//重新加载界面
	void ReloadInterface();

	void SetDlgType(DWORD dType);

private:

	void SetTextInfo();

private:

	//版本信息
	CString m_szVersion;

	//信息
	CString m_szInfo;

	//父对话框类型
	DWORD m_dDlgType;
};


