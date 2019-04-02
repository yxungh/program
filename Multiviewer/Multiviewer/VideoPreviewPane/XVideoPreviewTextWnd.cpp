// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XVideoPreviewTextWnd.h"

// XVideoPreviewTextWnd

IMPLEMENT_DYNAMIC(XVideoPreviewTextWnd, CWnd)

XVideoPreviewTextWnd::XVideoPreviewTextWnd()
{
	m_Text = _T("");
}

XVideoPreviewTextWnd::~XVideoPreviewTextWnd()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XVideoPreviewTextWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// XVideoPreviewTextWnd 消息处理程序

BOOL XVideoPreviewTextWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);
}

BOOL XVideoPreviewTextWnd::PreTranslateMessage(MSG* pMsg)
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
		case VK_ESCAPE://屏蔽Esc  
			{
				return TRUE;  
			}
			break;
		}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

void XVideoPreviewTextWnd::SetText(CString s)
{
	if (m_Text != s)
	{
		m_Text = s;

		InvalidateView();
	}
}

void XVideoPreviewTextWnd::InvalidateView()
{
	InvalidateRect(NULL);
}

CString XVideoPreviewTextWnd::GetText()
{
	return m_Text;
}

BOOL XVideoPreviewTextWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XVideoPreviewTextWnd::SetTextSize(int n)
{
	m_TextSize = n;
}

void XVideoPreviewTextWnd::SetFont(CFont* p)
{
	m_Font = p;
}

void XVideoPreviewTextWnd::OnPaint()
{
	CPaintDC dc(this); 

	CRect rt;
	GetClientRect(&rt);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rt, &bruDB);

	if(m_Text != _T(""))
	{
		CFont* pOldFont = dc.SelectObject(m_Font);

		dc.SetBkMode(TRANSPARENT);

		dc.SetTextColor(RGB(0, 0, 0));

		dc.DrawText(m_Text, rt, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		dc.SelectObject(pOldFont);
	}
}