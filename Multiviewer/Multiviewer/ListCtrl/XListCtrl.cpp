// XListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XListCtrl.h"


// XListCtrl

IMPLEMENT_DYNAMIC(XListCtrl, CListCtrl)

XListCtrl::XListCtrl()
{
	m_bEnableTips = FALSE;
}

XListCtrl::~XListCtrl()
{
}


BEGIN_MESSAGE_MAP(XListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &XListCtrl::OnNMCustomdraw)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// XListCtrl 消息处理程序

void XListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		COLORREF clrNewTextColor, clrNewBkColor;

		int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		POSITION pos = GetFirstSelectedItemPosition();

		int index = GetNextSelectedItem(pos);

		if (index == nItem && IsWindowEnabled())
		{
			clrNewTextColor = RGB(255,255,255);		
			clrNewBkColor = RGB(51,153,255);		
		}
		else
		{
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor = RGB(255,255,255);
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		*pResult = CDRF_DODEFAULT;
	}
}


void XListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bEnableTips)  
	{  
		CString str;  

		LVHITTESTINFO lvhti;  

		lvhti.pt = point;      

		SubItemHitTest(&lvhti);  

		if((lvhti.iItem != m_nItem) || (lvhti.iSubItem != m_nSubItem))  
		{  
			m_nItem = lvhti.iItem;  

			m_nSubItem = lvhti.iSubItem;  

			if((m_nItem != -1) && (m_nSubItem != -1))  
			{  
				str = GetItemText(m_nItem ,m_nSubItem); 

				int strWidth = GetStringWidth(str);

				int columnWidth = GetColumnWidth(m_nSubItem);

				//不知道为什么显示不全，但列的宽度还是大于字符串宽度，所以字符串宽度添加多20
				if (columnWidth < (strWidth + 20))
				{
					m_ToolTip.AddTool(this, str);

					m_ToolTip.Pop();
				}
				else
				{
					m_ToolTip.AddTool(this, _T("")); 

					m_ToolTip.Pop();
				}
			}  
			else  
			{  
				m_ToolTip.AddTool(this, _T(""));  

				m_ToolTip.Pop();
			}  
		}  
	}  
	CListCtrl::OnMouseMove(nFlags, point);
}

BOOL XListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEnableTips && m_ToolTip.GetSafeHwnd())  
	{
		m_ToolTip.RelayEvent(pMsg); 
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void XListCtrl::EnableToolTips(BOOL b)
{
	m_bEnableTips = b;

	if (m_bEnableTips)
	{
		m_ToolTip.Create(this, TTS_ALWAYSTIP);
	}
}