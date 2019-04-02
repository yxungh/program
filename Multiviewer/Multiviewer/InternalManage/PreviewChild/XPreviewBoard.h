#pragma once
#include "XConstantIM.h"


class XPreviewBoardWnd;
class HYXText;
class XPreviewChild;
class XInternalManage;
class MySplitButton;


class XPreviewBoard
{
public:

	XPreviewBoard();
	~XPreviewBoard();

public:

	void SetPreviewChild(XPreviewChild* p);

	XPreviewChild* GetPreviewChild();

	void SetBaseManage(XInternalManage* p);

	void SetIndex(int n);

	int GetIndex();

	void SetBoardIndex(int n);

	int GetBoardIndex();

	void SetSecretSel(int n);

	int GetSecretSel();

	void SetUseName(CString szName);

	CString GetUseName();

	void SetPassWd(CString szPassWd);

	CString GetPassWd();

	void SetModelSel(int n);

	int GetModelSel();

	void SetIP(CString szIP);

	CString GetIP();

	void SetMask(CString szMask);

	CString GetMask();

	void SetGateWay(CString szGateWay);

	CString GetGateWay();

	void SetMAC(CString szMAC);
	
	CString GetMAC();

	void SetRect(CRect rect);

	CRect GetRect();

	void Init();

	void InitPreviewBoardWnd();

	void InitPreviewTextWnd();

	void InitSplitBtn();

	void SetSplitDorpDown();

	void UpDateText();

	MySplitButton* GetMySplitBtn();

	void SetSelected(BOOL b);

	BOOL GetSelected();

	void UpDateImage();

	void OnShowMenu();

private:

	void ClearPreviewBoardWnd();

	void ClearPreviewTextWnd();

	void ClearSplitButton();
	
private:

	XInternalManage* m_pManage;

	XPreviewChild* m_pPreviewChild;

	XPreviewBoardWnd* m_pPreviewBoardWnd;

	HYXText* m_pPreviewTextWnd;

	CRect m_Rect;

	CRect m_BoardRect;

	CRect m_TextRect;

	MySplitButton* m_pSplitBtn;

private:

	BOOL m_bSelected;

	int m_nIndex;

	int m_nBoardIndex;

	int m_nSecretSel;

	CString m_szUserName;

	CString m_szPassWd;

	int m_nModelSel;

	CString m_szIP;

	CString m_szMask;

	CString m_szGateWay;

	CString m_szMAC;

};