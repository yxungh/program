#pragma once
#include "XRTSPInfo.h"
#include "XRTSPInfoDragWnd.h"

class XVideoPreviewFrame;
class XVideoPreviewPane;
class XVideoPreviewContain;

class XVideoPreviewVideoWnd : public CWnd
{
	DECLARE_DYNAMIC(XVideoPreviewVideoWnd)

public:
	XVideoPreviewVideoWnd();
	virtual ~XVideoPreviewVideoWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	void InitTips();

	void SetFrame(XVideoPreviewFrame* p);

	void SetVideoPreviewPan(XVideoPreviewPane* p);

	void SetVideoPreviewContain(XVideoPreviewContain* p);

	void ReloadInterface(); 


private:

	//显示菜单
	void ShowMenu();

	void CreatePreviewDragWnd();

	void MovePreviewDragWnd(CPoint& point);

	void MovePreviewDragWndEnd();

	void SetDragRTSPInfo();

	BOOL GetIsUltra(int& nIndex);

	void SetVecPreviewIndexAndID(int nIndex);

	void GetInputResulation(int nIndex,int& nResulationH,int& nResulationV);

	BOOL DecidePointInFrame(CPoint point);

private:

	XVideoPreviewPane* m_Pan;

	XVideoPreviewFrame* m_Frame;

	//预览拖动窗口
	XRTSPInfoDragWnd* m_PreviewDragWnd;

	XVideoPreviewContain* m_Contain;

	//拖拽信息
	XRTSPInfo m_RTSPInfo;

	CPoint m_DragPoint;

	BOOL m_Drag;

	CToolTipCtrl m_TipCtrl;

	CString m_szTips;

};


