#pragma once

#include "../resource.h"
#include "XConstantIM.h"



class XInternalManage;


class XPreviewBoardBitRate : public CDialogEx
{
	DECLARE_DYNAMIC(XPreviewBoardBitRate)

public:
	XPreviewBoardBitRate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XPreviewBoardBitRate();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_BITRATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedRead();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托


	void SetManage(XInternalManage* p);

	void SetBoardIndex(int n);
	int GetBoardIndex();

	//////////////////////////////////////////////////////////////////////////
	void SetMainDpi(int n);
	int GetMianDpi();

	void SetMainBitRate(int n);
	int GetMainBitRate();

	void SetSubDpi(int n);
	int GetSubDpi();

	void SetSubBitRate(int n);
	int GetSunBitRate();

	void SetMainDpi2(int n);
	int GetMianDpi2();

	void SetMainBitRate2(int n);
	int GetMainBitRate2();

	void SetSubDpi2(int n);
	int GetSubDpi2();

	void SetSubBitRate2(int n);
	int GetSunBitRate2();


	void SetMainDpi3(int n);
	int GetMianDpi3();

	void SetMainBitRate3(int n);
	int GetMainBitRate3();

	void SetSubDpi3(int n);
	int GetSubDpi3();

	void SetSubBitRate3(int n);
	int GetSunBitRate3();


	void SetMainDpi4(int n);
	int GetMianDpi4();

	void SetMainBitRate4(int n);
	int GetMainBitRate4();

	void SetSubDpi4(int n);
	int GetSubDpi4();

	void SetSubBitRate4(int n);
	int GetSunBitRate4();

	//////////////////////////////////////////////////////////////////////////

	void ResetDate();

	void InitComboBox();

private:

	//重载界面
	void ReloadInterface();

private:

	//委托

	XInternalManage* m_pManage;

	CComboBox m_Combo_MainDpi;

	CComboBox m_Combo_SubDpi;

	CComboBox m_Combo_MainBitRate;

	CComboBox m_Combo_SubBitRate;


	CComboBox m_Combo_MainDpi2;

	CComboBox m_Combo_SubDpi2;

	CComboBox m_Combo_MainBitRate2;

	CComboBox m_Combo_SubBitRate2;


	CComboBox m_Combo_MainDpi3;

	CComboBox m_Combo_SubDpi3;

	CComboBox m_Combo_MainBitRate3;

	CComboBox m_Combo_SubBitRate3;


	CComboBox m_Combo_MainDpi4;

	CComboBox m_Combo_SubDpi4;

	CComboBox m_Combo_MainBitRate4;

	CComboBox m_Combo_SubBitRate4;


	int m_nBoardIndex;


	int m_nMainDpi;

	int m_nMainBitRate;

	int m_nSubDpi;

	int m_nSubBitRate;


	int m_nMainDpi2;

	int m_nMainBitRate2;

	int m_nSubDpi2;

	int m_nSubBitRate2;


	int m_nMainDpi3;

	int m_nMainBitRate3;

	int m_nSubDpi3;

	int m_nSubBitRate3;


	int m_nMainDpi4;

	int m_nMainBitRate4;

	int m_nSubDpi4;

	int m_nSubBitRate4;
};