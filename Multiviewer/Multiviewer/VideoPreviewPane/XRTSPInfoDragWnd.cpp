// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XRTSPInfoDragWnd.h"
#include "..\XConstant.h"
#include "XVideoPlayer.h"
#include "XVideoPreviewPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrame.h"

// XRTSPInfoDragWnd
#define FRAMESINDEX  1000

IMPLEMENT_DYNAMIC(XRTSPInfoDragWnd, CWnd)

XRTSPInfoDragWnd::XRTSPInfoDragWnd()
{
	m_RTSPHWND = NULL;

	m_pMultiVideoWindow=NULL;
}

XRTSPInfoDragWnd::~XRTSPInfoDragWnd()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XRTSPInfoDragWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void XRTSPInfoDragWnd::SetVideoPreviewPan(XVideoPreviewPane* p)
{
	m_Pan=p;
}

// XRTSPInfoDragWnd 消息处理程序

BOOL XRTSPInfoDragWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(0,AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL,IDC_ARROW),NULL,NULL),0,dwStyle,rect,pParentWnd,nID);
}

BOOL XRTSPInfoDragWnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_RETURN://屏蔽回车  
			{
				return TRUE;  
			}
			break;
		//case VK_ESCAPE://屏蔽Esc  
		//	{
		//		return TRUE;  
		//	}
		//	break;
		}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

BOOL XRTSPInfoDragWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle|=WS_EX_TOOLWINDOW;

	return CWnd::PreCreateWindow(cs);
}

BOOL XRTSPInfoDragWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XRTSPInfoDragWnd::OnPaint()
{
	CPaintDC dc(this); 	
}

XRTSPHWND* XRTSPInfoDragWnd::GetRTSPHWND()
{
	return m_RTSPHWND;
}

void XRTSPInfoDragWnd::SetRTSPHWND(XRTSPHWND* p)
{
	m_RTSPHWND = p;
}

void XRTSPInfoDragWnd::Show(XRTSPInfo* pInfo)
{
	KillTimer(1);

	m_RTSPInfo=*pInfo;

	BOOL bIsUltra=m_RTSPInfo.GetIsUltra();

	BOOL bIsHaveSignal=m_RTSPInfo.GetIsHaveSignal();

	BOOL bIsHavePane=m_RTSPInfo.GetIsHavePane();

	m_pMultiVideoWindow=m_RTSPInfo.GetMultiVideoWindow();

	ClearFrame();

	if(bIsUltra)
	{
		if(bIsHaveSignal&&bIsHavePane)
		{
			AddUltraFrame();
		}	
	}
	else
	{
		if(bIsHaveSignal&&bIsHavePane)
		{
			AddCommFrame();
		}
	}

	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}

void XRTSPInfoDragWnd::ClearFrame()
{
	if(m_pMultiVideoWindow==NULL)
	{
		return;
	}

	m_pMultiVideoWindow->DeleteFrame(FRAMESINDEX);
}

void XRTSPInfoDragWnd::AddUltraFrame()
{
	RECTF rect(0,0,160,90);
	VEC_RECTF VecRect;
	SetRectToFoure(rect,VecRect);

	RECTF InterRect(0,0,1920,1088);

	VEC_CSTRING& VecRTSPAddr=m_RTSPInfo.GetVecRTSPAddr();

	int i=0;
	for(VEC_RECTF::iterator iter=VecRect.begin();iter!=VecRect.end();++iter)
	{
		RECTF rect=*iter;

		CString szRTSPAddr=VecRTSPAddr[i];

		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szRTSPAddr,rect,InterRect);

		i++;
	}
}

void XRTSPInfoDragWnd::AddCommFrame()
{
	RECTF rect(0,0,160,90);

	RECTF InterRect(0,0,1920,1088);

	CString szRTSPAddr=m_RTSPInfo.GetRTSPAddr();

	XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szRTSPAddr,rect,InterRect);
}

void XRTSPInfoDragWnd::SetRectToFoure(RECTF rect,VEC_RECTF& VecRect)
{
	RECTF rect1(rect.X,rect.Y,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect1);

	RECTF rect2(rect.X+rect.Width/2,rect.Y,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect2);	

	RECTF rect3(rect.X,rect.Y+rect.Height/2,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect3);

	RECTF rect4(rect.X+rect.Width/2,rect.Y+rect.Height/2,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect4);
}

void XRTSPInfoDragWnd::Hide()
{
	//通过定时器隐藏是因为直接隐藏的话，那会造成显示墙闪一下，显示墙添加的信号没有那么快显示出来
	SetTimer(1, 50, NULL);
}

void XRTSPInfoDragWnd::OnTimer(UINT_PTR nIDEvent)
{
	if(1==nIDEvent)
	{
		KillTimer(1);

		m_RTSPInfo.ClearData();

		ClearFrame();

		ShowWindow(SW_HIDE);
	}
}

XRTSPInfo* XRTSPInfoDragWnd::GetRTSPInfo()
{
	return &m_RTSPInfo;
}

void XRTSPInfoDragWnd::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x-nWidth/2,point.y-nHeight/2),CSize(nWidth,nHeight));

	MoveWindow(newRect);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}