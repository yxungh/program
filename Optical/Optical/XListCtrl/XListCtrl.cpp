// XListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XListCtrl.h"


// XListCtrl

IMPLEMENT_DYNAMIC(XListCtrl, CListCtrl)

XListCtrl::XListCtrl():
	m_OddItemBkColor(0xFEF1E3),
	m_EvenItemBkColor(0xD2D2D2),
	m_HoverItemBkColor(0x1E00FF),
	m_SelectItemBkColor(GetSysColor(COLOR_HIGHLIGHT)),
	m_OddItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_EvenItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_HoverItemTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)),
	m_SelectItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_nHoverIndex(-1),
	m_bTracking(FALSE),
	m_bEnableTips(FALSE)
{
}

XListCtrl::~XListCtrl()
{
}

BEGIN_MESSAGE_MAP(XListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,&XListCtrl::OnNMCustomdraw)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// XListCtrl 消息处理程序
void XListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult=CDRF_DODEFAULT;

	int nItemIndex=pNMCD->nmcd.dwItemSpec;
	if (CDDS_PREPAINT==pNMCD->nmcd.dwDrawStage)
	{
		*pResult=CDRF_NOTIFYITEMDRAW;
	}
	else if(CDDS_ITEMPREPAINT==pNMCD->nmcd.dwDrawStage)
	{
		*pResult=CDRF_NOTIFYSUBITEMDRAW;
	}
	else if((CDDS_ITEMPREPAINT|CDDS_SUBITEM)==pNMCD->nmcd.dwDrawStage)
	{
		if(nItemIndex==m_nHoverIndex)
		{ 
			pNMCD->clrTextBk=m_HoverItemBkColor;
			pNMCD->clrText=m_HoverItemTextColor;
		}
		else if(GetItemState(nItemIndex,LVIS_SELECTED)==LVIS_SELECTED)
		{
			pNMCD->clrTextBk=m_SelectItemBkColor;
			pNMCD->clrText=pNMCD->clrFace=m_SelectItemTextColor;
			::SetTextColor(pNMCD->nmcd.hdc,m_SelectItemTextColor);
		}
		else if(nItemIndex%2==0)
		{
			pNMCD->clrTextBk=m_EvenItemBkColor;
			pNMCD->clrText=m_EvenItemTextColor;
		}
		else
		{	
			pNMCD->clrTextBk=m_OddItemBkColor;
			pNMCD->clrText=m_OddItemTextColor;
		}
		*pResult=CDRF_NEWFONT;
	}
}

void XListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	int nIndex=HitTest(point);
	if(nIndex!=m_nHoverIndex)
	{
		int nOldIndex=m_nHoverIndex;
		m_nHoverIndex=nIndex;

		CRect rc;
		if(nOldIndex!=-1)
		{
			GetItemRect(nOldIndex,&rc,LVIR_BOUNDS);
			InvalidateRect(&rc);
		}		

		if(m_nHoverIndex!=-1)
		{
			GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
			InvalidateRect(&rc);
		}
	}

	if(!m_bTracking) 
	{ 
		TRACKMOUSEEVENT tme; 
		tme.cbSize=sizeof(tme); 
		tme.hwndTrack=m_hWnd; 
		tme.dwFlags=TME_LEAVE/*|TME_HOVER*/; 
		tme.dwHoverTime=1; 
		m_bTracking=_TrackMouseEvent(&tme); 
	}

	//==================提示=========================
	if(m_bEnableTips)  
	{  
		CString szTips;  

		LVHITTESTINFO lvhti;  
		lvhti.pt = point;      
		SubItemHitTest(&lvhti);  

		if((lvhti.iItem!=m_nItem)||(lvhti.iSubItem!=m_nSubItem))  
		{  
			m_nItem=lvhti.iItem;  
			m_nSubItem=lvhti.iSubItem;  
			if((m_nItem!=-1)&&(m_nSubItem!=-1))  
			{  
				szTips=GetItemText(m_nItem,m_nSubItem); 
				int strWidth=GetStringWidth(szTips);
				int columnWidth=GetColumnWidth(m_nSubItem);

				//不知道为什么显示不全，但列的宽度还是大于字符串宽度，所以字符串宽度添加多20
				if(columnWidth<(strWidth+20))
				{
					m_ToolTip.AddTool(this,szTips);
					m_ToolTip.Pop();
				}
				else
				{
					m_ToolTip.AddTool(this,_T("")); 
					m_ToolTip.Pop();
				}
			}  
			else  
			{  
				m_ToolTip.AddTool(this,_T(""));  
				m_ToolTip.Pop();
			}  
		}  
	}  

	CListCtrl::OnMouseMove(nFlags, point);
}

void XListCtrl::OnMouseLeave()
{
	m_bTracking=FALSE;
	if(m_nHoverIndex!=-1)
	{
		CRect rc;
		GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
		m_nHoverIndex=-1;
		InvalidateRect(&rc);
	}

	CListCtrl::OnMouseLeave();
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
	m_bEnableTips=b;

	if(m_bEnableTips)
	{
		m_ToolTip.Create(this,TTS_ALWAYSTIP);
	}
}
