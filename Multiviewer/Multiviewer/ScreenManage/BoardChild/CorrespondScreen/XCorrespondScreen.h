#pragma once

#include "../resource.h"

class XEquipmentOutput;

class XCorrespondScreen : public CDialogEx
{
	DECLARE_DYNAMIC(XCorrespondScreen)

public:
	XCorrespondScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XCorrespondScreen();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_CORRSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	afx_msg void OnSelchange();
	DECLARE_MESSAGE_MAP()

public:

	void SetEquipmentOutputWnd(XEquipmentOutput* p);

	void InitCombo();

	int GetScreenNum();

	int GetScreenIndex1();

	int GetScreenIndex2();

	BOOL CheckIndex(int nIndex);

private:

	//重载界面
	void ReloadInterface();

private:

	XEquipmentOutput* m_pEquipmentOutput;

	CComboBox m_Combo_Correspond;

	int m_nScreenNum;

	int m_nScreenIndex1;

	int m_nScreenIndex2;
};