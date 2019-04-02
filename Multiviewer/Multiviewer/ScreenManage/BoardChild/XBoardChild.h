#pragma once

#include "../resource.h"
#include "XConstantIM.h"
#include "ScreenSetDlg.h"


class XDelegateSelectEquipment;
class XScreen;
class XScreenManage;
class XDelegateScreenSetDlg;
class XScreenInfo;
class HYXText;



#define EQUIPMENT_TEXTHEIGHT 30
#define CHEVKBOX_WIDTH       55
#define DISTANCE            10

class XBoardChild : public CDialogEx,XDelegateScreenSetDlg
{
	DECLARE_DYNAMIC(XBoardChild)

public:
	XBoardChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XBoardChild();

	virtual BOOL OnInitDialog();

	enum { IDD = IDD_DLG_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();

	//afx_msg void OnCheckBox();
	afx_msg void OnSelchangeCombo();

	DECLARE_MESSAGE_MAP()

public:

	virtual CString GetTranslationString(CString szKey, CString szDefault);

	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType);

	virtual int GetRow();

	virtual int GetColumn();

	virtual void CopyVecBoardToVecScreeInfo(VEC_SCREENINFO& VecScreenInfo);

	virtual void SetVecBoardOutpout(XScreenInfo* pInfo);

	virtual void SetVecBoard(XScreenInfo* pInfo);

	virtual void UpdataImage(int nBoard);

	virtual void UpdateText(int nBoard); 

	virtual int GetBeginScreenIndex();

	virtual CFont* GetFont();

	virtual BOOL CheckScreenNum(int nBoardIndex);

	virtual void SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo);

	virtual BOOL CheckRepeat(int nScreenIndex);

	virtual BOOL GetIsMenuSet();

public:

	void SetDelegate(XDelegateSelectEquipment* p);

	XDelegateSelectEquipment* GetDelegate();

	void SetScreenManage(XScreenManage* p);

	void SetScreen(XScreen* p);

	void ReloadInterface();

	void Init();

	void InitFont();

	void DeleteFont();

	void InitIndexWnd();

	void InitVec();

	void InitVecInput();

	void InitVecOutput();

	void InitVecEquipment();

	void InitVecEquipmentInput();

	void InitVecEquipmentOutput();

	void ResetVecEquipment();

	void SetVecEquipment();

	void SetEquipment(int n);

	int GetEquipment();

	void AdjustScrollV();

	int GetScrollHight();

	VEC_EQUIPMENTINPUT& GetVecEquipmentInput();

	VEC_EQUIPMENTOUTPUT& GetVecEquipmentOutput();

	VEC_SCREENINFO& GetVecScreenInfo();

	//void SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo);

	void SetOSD(XEquipmentInput* pDisplay);

	void SetCorrespondScreenNum(XEquipmentOutput* pEquipmentOutput,BOOL IsTwoScreen,int nScreenIndex1,int nScreenIndex2);

	void SetIsMenuSet(BOOL IsmenuSet);

	//BOOL GetIsMenuSet();

private:

	void ClearVecEquipment();

	void ClearVecInput();

	void ClearVecOutput();

	void ClearVecTextWnd();

	void ClearScreenInfo();

	void ClearBoardType();

	//////////////////////////////////////////////////////////////////////////
public:
	void SetScreenNumH(int n);

	int GetScreenNumH();

	void SetScreenNumV(int n);

	int GetScreenNumV();

	//void SetBeginScreenIndex(int n);

public:

	inline void SetScreenModel(int n){m_nScreenModel=n;}

	inline int GetScreenModel(){return m_nScreenModel;}

private:

	XDelegateSelectEquipment* m_pDelegate;

	XScreenManage* m_pScreenManage;

	XScreen* m_pScreen;

	int m_nEquipment;

	CFont m_Font;

	CRect m_TextRect;

private:

	BOOL m_bScrollTimerV;

	int m_nScrollPosV;

	int m_nScrollTimerV;

	int m_nScrellHight;

public:

	VEC_VIEWTEXT m_VecViewText;

	VEC_EQUIPMENTINPUT m_VecEquipmentInput;

	VEC_EQUIPMENTOUTPUT m_VecEquipmentOutput;

	VEC_SCREENINFO m_VecScreenInfo;
	//////////////////////////////////////////////////////////////////////////
private:

	int m_nScreenNumH;

	int m_nScreenNumV;

	BOOL m_IsMenuSet;

	//int m_nBeginScreenIndex;

	int m_nScreenModel;

};