#pragma once

#include "../resource.h"
#include "XConstantIM.h"

class XDelegateSetScreenRange;
class XScreen;
class XScreenManage;

class XSetScreenRange : public CDialogEx
{
	DECLARE_DYNAMIC(XSetScreenRange)

public:
	XSetScreenRange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSetScreenRange();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_SCREENRANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegateSetScreenRange* p);

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void InitData();

	void SetIsMenuSet(BOOL b);

	BOOL GetIsMenuSet();


	//void SetInputNum(int n);

	//void SetOutputNum(int n);

	////设置输入板卡集合
	//void SetVecEquInput(VEC_EQUIPMENTINPUT& VecInput);

	////设置输出板卡集合
	//void SetVecEquOutput(VEC_EQUIPMENTOUTPUT& VecOutput);

	void SetEquipmentNum(int n);

	int GetEquipmentNum();

	void SetScreenNumH(int n);

	int GetScreenNumH();

	void SetScreenNumV(int n);

	int GetScreenNumV();

private:

	//重载界面
	void ReloadInterface();

private:

	//委托
	XDelegateSetScreenRange* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	//int m_nInputNum;

	//int m_nOutputNum;

	//VEC_EQUIPMENTINPUT m_VecEquInput;

	//VEC_EQUIPMENTOUTPUT m_VecEquOutput;

	int m_nEquipmentNum;

	int m_nScreenNumH;

	int m_nScreenNumV;

	BOOL m_bIsMenuSet;

};