#pragma once

#include "../resource.h"
#include "XConstantIM.h"

#define NEWDISTANCE 17
#define DISTANCE 10
#define PREVIEW_TEXTHEIGHT 30
#define SPLITBTN_WIDTH  70




class XDelegatePreviewChild;
class XInternalManage;
class XSetPreviewBoard;
class HYXText;
class XBoardNet;
class XPreviewBoardBitRate;


class XPreviewChild : public CDialogEx
{
	DECLARE_DYNAMIC(XPreviewChild)

public:
	XPreviewChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XPreviewChild();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_PREVIEWCHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSplitBtn();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnMenuNet();
	afx_msg void OnMenuBitRate();
	DECLARE_MESSAGE_MAP()

public:

	//设置委托
	void SetDelegate(XDelegatePreviewChild* p);

	void SetBaseManage(XInternalManage* p);

	void SetPreviewParent(XSetPreviewBoard* p);

	void Init();

	void InitFont();

	CFont* GetFont();

	void DeleteFont();

	void InitData();

	void InitVecPreview();

	void InitVecPreviewBoard();

	void InitTextWnd();

	void ClearVecPreviewBoard();

	void ClearVecTextWnd();

	void OnSplitNetSet();

	void OnSplitBiteRate();

	VEC_PREVIEWBOARD& GetVecPreviewBoard();

	void ResetVecPreciewBoard();


	void OnShowMenu();

public:

	void OperateOfReadPreviewNet(char* pData);

	void OperateOfReadPreviewBitRate(char* pData);

private:

	//重载界面
	void ReloadInterface();

	XPreviewBoard* GetPreviewBoardByPoint(CPoint point);

	BOOL CheckSumNum(char* pData,int nLen);

	unsigned short CheckNum(char *pData,int nLen);


	/////////////////////////////////////////////
	void SplitNetSet();
	void SplitBiteRate();

private:

	void AdjustScrollV();

	int GetScrollHight();

private:

	XDelegatePreviewChild* m_pDelegate;

	XInternalManage* m_pBaseManage;

	XSetPreviewBoard* m_pParent;

	CFont m_Font;

	VEC_PREVIEWBOARD m_VecPreViewBoard;

	VEC_PREVIEWTEXT m_VecPreviewText;

	CRect m_TextRect;

	XPreviewBoardBitRate* m_pBoardBitRateDlg;

	XBoardNet* m_pBoardNetDlg;




private:

	BOOL m_bScrollTimerV;

	int m_nScrollPosV;

	int m_nScrollTimerV;

	int m_nScrellHight;
};
