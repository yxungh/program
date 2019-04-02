#pragma once

#include "../resource.h"
#include "XDelegateScreenMoveDlg.h"
#include "XScreenMoveGrid.h"
#include "XDelegateScreenMoveGrid.h"
#include "XConstantIM.h"



class XDelegateScreenMoveDlg;
class XScreenManage;
class XScreen;

// CSetOSDDlg 对话框

class XScreenMoveDlg : public CDialogEx,
	public XDelegateScreenMoveGrid
{
	DECLARE_DYNAMIC(XScreenMoveDlg)

public:
	XScreenMoveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XScreenMoveDlg();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCREENMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnChange();
	afx_msg void OnBtnCencel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnEnChangeEditText();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSelchangeBeginX();
	afx_msg void OnSelchangeLong();

	afx_msg LRESULT OnUpdataShowData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateScreenMoveDlg* p);

	void SetScreenManage(XScreenManage* p);

	void AddFont(CString s);

	void SetReTime(DWORD& dWTime);

private:

	//重载界面
	void ReloadInterface();

	void Init();

	void InitShowData();

	void InitCombo();

	void InitComboFont();

	void InitProgress();

	void AdjustPos();

	void SetScreenMoveMutrix();

	void CreateScreenMoveGrid();

	void ClearMutrixData();

	void InitSendData();

	void SendData(int& nSendDataIndex);

	void SendMutrixData(int nSendDataIndex);

	void BeginSendTimer();

	void StopSendTimer();

	void UpdataProgress();

	void ResetProgress();

	void UpdataSendData();

	XScreen* GetScreenByIndex(int nIndex);

	void UpdateTime();

	BOOL IsNULL(char* pData,int& nLen);

private:

	//委托
	XDelegateScreenMoveDlg* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreenMoveGrid m_Grid;

	CComboBox m_ComboBox_Font;

	CComboBox m_ComboBox_Type;

	CComboBox m_ComboBox_Long;

	CComboBox m_ComboBox_Width;

	CComboBox m_ComboBox_BeginX;

	CComboBox m_ComboBox_BeginY;

	CComboBox m_ComboBox_Center;

	CRect m_DlgMinRect;

	BOOL m_InitDlg;

	CMFCColorButton m_FColor;

	CMFCColorButton m_BKColor;


private:

	unsigned char *m_pMutrixData;

	unsigned int m_MutrixDataLen;

	int m_SendDataIndex;

	int m_Time;

	BOOL m_IsOneTime;

	BOOL m_IsLastTime;

	unsigned int m_Pos;

	DWORD m_dReTime;

	DWORD m_UpdataTime;

	XScreen* m_pScreen;

	int m_SendSpace;
};