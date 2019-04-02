#pragma once

#include "../resource.h"
#include "XEquipmentInput.h"
#include "XEquipmentOutput.h"


class XDelegateSelectEquipment;
class XScreen;
class XScreenManage;

class XSelectEquipment : public CDialogEx
{
	DECLARE_DYNAMIC(XSelectEquipment)

public:
	XSelectEquipment(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSelectEquipment();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SELECTEQUIPMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSelectEquipment* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitComoboBox();

	int GetEquipment();

	void SetEquipment(int n);

	void SetIsMenuSet(BOOL b);

	void InitData();


private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateSelectEquipment* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	CComboBox m_Combo_Equipment;

	int m_nEquipment;

	BOOL m_bIsMenuSet;
};