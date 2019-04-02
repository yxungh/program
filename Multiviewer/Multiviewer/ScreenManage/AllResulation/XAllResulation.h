#pragma once
#include "../resource.h"
#include "XDelegateAllResulation.h"
#include "XScreen.h"
#include "XResulationHCutInfo.h"
#include "XResulationVCutInfo.h"


// XAllResulution 对话框

class XScreenManage;

class XAllResulution : public CDialogEx
{
	DECLARE_DYNAMIC(XAllResulution)

public:
	XAllResulution(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XAllResulution();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_SPLICALLRESALUTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	afx_msg void OnBtnCancle();
	afx_msg void OnClickedExpand();
	afx_msg void OnSelchangeIndex();
	afx_msg void OnSelchangeRefresh();
	afx_msg void OnResulationHChange();
	afx_msg void OnResulationVChange();
	afx_msg void OnSelRightCut();
	afx_msg void OnSelBottomCut();

	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateAllResulution* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen*& p);

	void ReloadInterface();

	void SetDialog();

	void Init();

	void InitCombo();

	void InitShowData();

	void SetControlStatus(CTRLSTATUS type);

	void ResulationHChange(int nFront,int nBack,int nChangeResulation,int nResResulation);

	void ResulationVChange(int nFront,int nBack,int nChangeResulation,int nResResulation);

	void SetRCutStatus(BOOL b);

	void SetBCutStatus(BOOL b);

	XResulationHCutInfo* GetResulationHCutInfo();

	XResulationVCutInfo* GetResulationVCutInfo();

	void SetCheckBoxStatus(int nComboxIndex);

private:

	void SetScreenResulationInfo();

private:

	XDelegateAllResulution* m_Delegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	CRect m_Rect;

	CRect m_ExpaneRect;

	CComboBox m_Combo_Index;

	CComboBox m_Combo_Refresh;

	XResulationHCutInfo m_ResulationHInfo;

	XResulationVCutInfo m_ResulationVInfo;

};
