#pragma once

#include "..\resource.h"
#include "XScreenInfosWnd.h"
#include "XConstantIM.h"


class HYXText;

class XDelegateScreenSetDlg
{
public:

	XDelegateScreenSetDlg(void){};

	~XDelegateScreenSetDlg(void){};

	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	virtual int GetRow()=0;

	virtual int GetColumn()=0;

	virtual void CopyVecBoardToVecScreeInfo(VEC_SCREENINFO& VecScreenInfo)=0;

	virtual void SetVecBoardOutpout(XScreenInfo* pInfo)=0;

	virtual void SetVecBoard(XScreenInfo* pInfo)=0;

	virtual void UpdataImage(int nBoard)=0;

	virtual void UpdateText(int nBoard)=0; 

	virtual int GetBeginScreenIndex()=0;

	virtual CFont* GetFont()=0;

	virtual BOOL CheckScreenNum(int nBoardIndex)=0;

	virtual void SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo)=0;

	virtual BOOL CheckRepeat(int nScreenIndex)=0;

	virtual BOOL GetIsMenuSet()=0;
};

// CScreenSetDlg 对话框

class CScreenSetDlg : public CDialogEx, XDelegateScreenInfosWnd
{
	DECLARE_DYNAMIC(CScreenSetDlg)

public:
	CScreenSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScreenSetDlg();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 对话框数据
	enum { IDD = IDD_DLG_SCREENSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedSetScreen();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateScreenSetDlg* pDelegate);

public:

	virtual int GetScreenColumn();

	virtual int GetScreenRow();

	virtual VEC_SCREENINFO& GetVecScreenInfo();

	virtual void ScreenInfoLBDblClk(XScreenInfo* pInfo);

	virtual void ScreenInfoLBtnDown(XScreenInfo* pInfo);

	virtual CString GetTranslationString(CString szKey, CString szDefault);

	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

	virtual BOOL CheckRepeat(int nScreenIndex);

private:

	void InitData();

	void InitScreenIndex();

	void InitText();

	void InitText2();

	void InitText3();

	void InitText4();

	void InitText5();

	void InitFont();

	void DeleteFont();

	void CreateScreenInfosWnd();

	void CreateText();

	void CreateText1();

	void CreateText2();

	void CreateText3();

	void CreateText4();

	void CreateText5();

	void InitVecScreenData();

	void ClearVecScreenInfo();

	void ClearWnd();

	void ClearText();

public:

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetIsTwoScreen(BOOL bIsTwoScreen);

	BOOL GetIsTwoScreen();

	void SetBeginScreenIndex(int n);

	int GetBeginScreenIndex();

	void UpdataText();

	void UpdataText1();

	void UpdataText2();

	void UpdataText3();

	void UpdataText4();

	void UpdataText5();

	void SetScreenModel(int nModel);

	int GetScreenModel();

	void SetCorrpScreenNum(int n);

	int GetCorrpScreenNum();

private:

	XDelegateScreenSetDlg* m_pDelegate;

	int m_nScreenRow;

	int m_nScreenColumn;

	VEC_SCREENINFO m_VecScreenInfo;

	XScreenInfosWnd* m_pScreenInfosWnd;

	int m_nBoardIndex;

	BOOL m_bIsTwoScreen;

	int m_nBeginScreenIndex;

	int m_nScreenIndex;

	int m_nScreenIndex2;

	int m_nScreenIndex3;

	int m_nScreenIndex4;

	HYXText* m_TextInfo1;

	HYXText* m_TextInfo2;

	HYXText* m_TextInfo3;

	HYXText* m_TextInfo4;

	HYXText* m_TextInfo5;

	CFont m_Font;

	int m_nNumOfScreen;

	int m_nScreenModel;

	int m_nCorrScreenNum;
};
