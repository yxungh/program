#pragma once

#include "../resource.h"

class XVideoPreviewFrame;

// CChangeRTSPAddrDlg 对话框

class CChangeRTSPAddrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeRTSPAddrDlg)

public:
	CChangeRTSPAddrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeRTSPAddrDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_CHANGERTSPADDR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	
	void SetRTSPAddr(CString s);

	CString GetRTSPAddr();

	void SetFrame(XVideoPreviewFrame* p);

private:

	CString m_RTSPAddr;

	XVideoPreviewFrame* m_Frame;
};
