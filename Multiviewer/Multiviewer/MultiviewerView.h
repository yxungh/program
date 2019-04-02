// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MultiviewerView.h : CMultiviewerView 类的接口
//

#pragma once

class CMultiviewerDoc;
class XDelegateView;
class XBaseScreenManage;

class CMultiviewerView : public CScrollView
{
protected: // 仅从序列化创建
	CMultiviewerView();
	DECLARE_DYNCREATE(CMultiviewerView)

// 特性
public:
	CMultiviewerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

protected:

// 实现
public:
	virtual ~CMultiviewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT fFlags, short zDelta, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate();

	//重设视图大小
	void ResetSize();

	void SetScreenManage(XBaseScreenManage* p);

	XBaseScreenManage* GetScreenManage();

private:

	//委托
	XDelegateView* m_pDelegate;

	XBaseScreenManage* m_pScreenManage;

	//鼠标离开标识
	BOOL m_bMouseLeave;

};

#ifndef _DEBUG  // MultiviewerView.cpp 中的调试版本
inline CMultiviewerDoc* CMultiviewerView::GetDocument() const
   { return reinterpret_cast<CMultiviewerDoc*>(m_pDocument); }
#endif

