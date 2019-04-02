#pragma once

#include "XConstantIM.h"

class XDelegateScreenInfosWnd
{
public:

	XDelegateScreenInfosWnd(void){};

	~XDelegateScreenInfosWnd(void){};

	virtual int GetScreenColumn() = 0;

	virtual int GetScreenRow() = 0;

	virtual VEC_SCREENINFO& GetVecScreenInfo() = 0;

	virtual void ScreenInfoLBDblClk(XScreenInfo* pInfo) = 0;

	virtual void ScreenInfoLBtnDown(XScreenInfo* pInfo)=0;

	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	virtual int MessageBoxFromKey(CString szKey, CString szDefault, UINT uType) = 0;

	virtual BOOL CheckRepeat(int nScreenIndex)=0;
};

class XScreenInfosWnd : public CWnd
{
	DECLARE_DYNAMIC(XScreenInfosWnd)

public:
	XScreenInfosWnd();
	virtual ~XScreenInfosWnd();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID);
	
public:

	void SetDelegate(XDelegateScreenInfosWnd* pDelegate);

	void SetBoardIndex(int n);

	void SetIsTwoScreen(BOOL b);

	void SetBeginScreenIndex(int n);

	int GetBeginScreenIndex();

	void ClearMapBoard();

	void ClearMapMatrix();

	int GetNum(int nBoardIndex,int nNum);

private:

	void DrawArea(Graphics& graphics, CRect rect);

	void DrawScreenInfo(Graphics& graphics, CRect rect);

public:

	inline int GetScreenModel(){return m_nScreenModel;}

	inline void SetScreenModel(int n){m_nScreenModel=n;}

private:

	XDelegateScreenInfosWnd* m_pDelegate;

	int m_nBoardIndex;

	BOOL m_bIsTwoScreen;

	int m_nBeginScreenIndex;

	//°å¿¨£¬Map£¨ÆÁÄ»£¬ÐòºÅ£©
	MAP_NUMOFMATRIXSCREEN m_BoardMapMatrix;

	//ÆÁÄ»£¬ÐòºÅ
	MAP_MATRIX m_ScreenIndexMapMatrix;

	int m_nScreenModel;

};


