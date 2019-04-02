
// ChildFrm.h : CChildFrame 类的接口
//

#pragma once

class XInternalManage;
class XBaseScreenManage;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

// 生成的消息映射函数
protected:

	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);

	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()

public:

	void setParentDelegate(XInternalManage* p);

	void setScreenManage(XBaseScreenManage* p);

	XBaseScreenManage* GetScreenManage();

private:

	XInternalManage* m_pManage;

	XBaseScreenManage* m_pScreenManage;

};
