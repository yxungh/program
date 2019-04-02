#pragma once
#include "../resource.h"
#include "XDelegateChangeInput.h"
#include "XConstantIM.h"

class XSignal;
class XScreenManage;

class XChangeInput : public CDialogEx
{
	DECLARE_DYNAMIC(XChangeInput)

public:
	XChangeInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XChangeInput();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_CHANGEINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnOK();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateChangeInput* p);

	void SetScreenManage(XScreenManage* p);

	//void SetSigal(XSignal*& p);

	void ReloadInterface();

	void InitData();

	void InitCombo();

	void SetVecSignal(VEC_INPUTSIGNAL& Vec);

	int GetComboIndex();

	void SetInputIndex(int n);

	void SetIsUltra(BOOL IsUltra);

private:

	XDelegateChangeInput *m_pDelegate;

	XScreenManage* m_pScreenManage;

	//XSignal* m_pSignal;

	CComboBox m_Combo_Input;

	VEC_INPUTSIGNAL m_VecInput;

	int m_InputIndex;

	int m_ComboIndex;

	BOOL m_IsUltra;
};