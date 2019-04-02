// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XDragWnd.h"
#include "XConstantIM.h"
#include "XInputSignalPane.h"
#include "XDelegateInputSignalPane.h"
#include "XMultiVideoWindow.h"

// XDragWnd
#define FRAMESINDEX 1001

IMPLEMENT_DYNAMIC(XDragWnd, CWnd)

XDragWnd::XDragWnd()
{
	m_pMultiVideoWindow=NULL;
}

XDragWnd::~XDragWnd()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XDragWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// XDragWnd 消息处理程序

BOOL XDragWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);
}

void XDragWnd::SetInputSignalPan(XInputSignalPane* p)
{
	m_Pan=p;
}

BOOL XDragWnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)  
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

BOOL XDragWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |=WS_EX_TOOLWINDOW;

	return CWnd::PreCreateWindow(cs);
}

BOOL XDragWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XDragWnd::OnPaint()
{
	CPaintDC dc(this); 
	//
	/*CRect rt;
	GetClientRect(&rt);

	Graphics graphics(dc.GetSafeHdc());

	graphics.Clear(Gdiplus::Color(90, 198, 149));

	Gdiplus::Pen pen(Color(0, 0, 0), 1);
	graphics.DrawRectangle(&pen, Rect(rt.left,rt.top,rt.Width() - 1, rt.Height() - 1));

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, 12, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(Color(0, 0, 255));

	Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());


	CString szTemp = _T("");
	szTemp.Format(_T("%d\r\n(%s)"), m_DragInfo.GetInputIndex(), m_DragInfo.GetText());

	graphics.DrawString(szTemp, -1, &font, reF, &stringformat, &brush);*/

}

XDragInfo* XDragWnd::GetDragInfo()
{
	return &m_DragInfo;
}

void XDragWnd::Show(XDragInfo* pInfo)
{
	KillTimer(1);

	m_DragInfo = *pInfo;

	m_pMultiVideoWindow=m_DragInfo.GetMultiVideoWindow();

	BOOL bIsUltra=m_DragInfo.GetIsUltra();

	BOOL bIsHaveSignal=m_DragInfo.GetIsHaveSignal();

	BOOL bIsHavePane=m_DragInfo.GetIsHavePane();

	if(bIsUltra)
	{
		ClearFrame();

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

	SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
}

void XDragWnd::ClearFrame()
{
	if(m_pMultiVideoWindow==NULL)
	{
		return;
	}

	m_pMultiVideoWindow->DeleteFrame(FRAMESINDEX);
}

void XDragWnd::AddUltraFrame()
{
	RECTF rect(0,0,160,90);

	VEC_RECTF VecRect;
	SetRectToFoure(rect,VecRect);

	RECTF InterRect(0,0,1920,1088);

	VEC_CSTRING& VecRTSPAddr=m_DragInfo.GetVecRTSPAddr();

	int i=0;
	for(VEC_RECTF::iterator iter=VecRect.begin();iter!=VecRect.end();++iter)
	{
		RECTF rect=*iter;

		CString szRTSPAddr=VecRTSPAddr[i];

		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szRTSPAddr,rect,InterRect);

		i++;
	}
}

void XDragWnd::AddCommFrame()
{
	RECTF rect(0,0,160,90);

	RECTF InterRect(0,0,1920,1088);

	CString szRTSPAddr=m_DragInfo.GetRTSPAddr();

	TRACE(_T("DragRTSP=%s\n"),szRTSPAddr);

	XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szRTSPAddr,rect,InterRect);
}

void XDragWnd::SetRectToFoure(RECTF rect,VEC_RECTF& VecRect)
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

void XDragWnd::Hide()
{
	//通过定时器隐藏是因为直接隐藏的话，那会造成显示墙闪一下，显示墙添加的信号没有那么快显示出来
	SetTimer(1, 50, NULL);
}

void XDragWnd::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		KillTimer(1);

		m_DragInfo.ClearRTSPData();

		ClearFrame();

		ShowWindow(SW_HIDE);
	}
}

void XDragWnd::Move(CPoint point)
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