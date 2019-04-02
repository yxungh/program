#pragma once

#include "../resource.h"
#include "XConstantIM.h"

class XVideoPreviewPane;
class XMultiVideoWindow;

// CViewPreviewDlg 对话框

class CViewPreviewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewPreviewDlg)

public:
	CViewPreviewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CViewPreviewDlg();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL OnInitDialog();

	virtual void OnCancel();

// 对话框数据
	enum { IDD = IDD_DLG_VIEWPREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()

public:

	void SetTitle();

	void SetPane(XVideoPreviewPane* p);

	void Init();

	void SetIP(CString szIP);

	void SetRTSPAddr(CString szRTSPAddr);

	void SetInputIndex(int nIndex);

	void SetUserName(CString szName);

	void SetPassWord(CString szPassWd);

	void CreateRTSPAddr();

	void AddFrame();

	void AdjustLayoutDlg();

	void DeleteMultiVideoWindow();

	void ClearFrame();

	void SetMultiVideoWindow(XMultiVideoWindow* p);

private:

	void Hide();

private:

	XVideoPreviewPane* m_Pane;

	BOOL m_InitDlg;

	VEC_CSTRING m_VecRTSPAddr;

	XMultiVideoWindow* m_pMultiVideoWindow;

	CString m_szIP;

	CString m_szRTSPAddr;

	int m_nIndex;

	CString m_szName;

	CString m_szPassWd;
};
