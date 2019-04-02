// ControlTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XInputSignalTreeCtrl.h"
#include "XDragWnd.h"
#include "XInputSignalExpand.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XConstantIM.h"
#include "XSignalCutInfo.h"

// XInputSignalTreeCtrl
#define   DRAG_DELAY   60

IMPLEMENT_DYNAMIC(XInputSignalTreeCtrl, CTreeCtrl)

XInputSignalTreeCtrl::XInputSignalTreeCtrl()
{
	m_InputSignalPane = NULL;
	m_Drag = FALSE;
	m_DragWnd = NULL;
	m_bDragging=FALSE;
}

XInputSignalTreeCtrl::~XInputSignalTreeCtrl()
{

}

BEGIN_MESSAGE_MAP(XInputSignalTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &XInputSignalTreeCtrl::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_GESTURE, OnGesture)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &XInputSignalTreeCtrl::OnNMCustomdrawTreeCtrl)
END_MESSAGE_MAP()

ULONG XInputSignalTreeCtrl::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XInputSignalTreeCtrl::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

void XInputSignalTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void XInputSignalTreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;
	HTREEITEM item=pNMTreeView->itemNew.hItem;

	DWORD dwData=GetItemData(item);
	CString szItemText=GetItemText(item);
	XInputSignalExpand* pExpand = NULL;

	if(dwData==ITEMTYPE_INPUTGROUP)
		return;
	else if(dwData==ITEMTYPE_INPUTSIGNAL)
	{
		int nInputIndex=m_InputSignalPane->GetInputIndexByItemName(szItemText);
		XInputSignal* pSignal=m_InputSignalPane->GetInputSignalByIndex(nInputIndex);

		if(pSignal==NULL)
			return;

		pExpand=pSignal->GetDefaultExpand();
		//**************************************
		m_hItemDragS=item;
		m_hItemDragD=NULL;
		m_pDragImage=CreateDragImage(m_hItemDragS);
		if(!m_pDragImage)
			return;

		m_bDragging=TRUE;
		m_pDragImage->BeginDrag(0,CPoint(10,10));
		CPoint pt=pNMTreeView->ptDrag;
		ClientToScreen(&pt);
		m_pDragImage->DragEnter(this,pt);
		m_nScrollTimerID=SetTimer(2,40,NULL);
		//**************************************
	}
	else
		pExpand=(XInputSignalExpand*)GetItemData(item);

	if(NULL==pExpand)
		return;

	SelectItem(pNMTreeView->itemNew.hItem);
	SetCapture();
	CPoint point;
	GetCursorPos(&point);
	m_DragPoint=point;
	m_Drag=TRUE;
	m_DragWnd=NULL;

	int nInputIndex = pExpand->GetInputSignal()->GetInputIndex();
	XExpandInfo expandInfo = *(pExpand->GetExpandInfo());
	CString szExpandName = pExpand->GetName();
	CString szAnotherName=pExpand->GetInputSignal()->GetAnotherName();
	CString szRTSPAddr=pExpand->GetInputSignal()->GetRTSPAddr();

	//是否为4K
	m_InputSignalPane->IsUltra(nInputIndex);
	BOOL bIsUltra=pExpand->GetInputSignal()->GetIsUltra();

	//是否有信号
	BOOL bIsHaveSignal=m_InputSignalPane->IsHaveSignal(nInputIndex);

	//是否有板卡
	BOOL bIsHavePane=m_InputSignalPane->IsHavePan(nInputIndex);

	CString szIP=pExpand->GetInputSignal()->GetIPAddr();
	CString szUseName=pExpand->GetInputSignal()->GetUseName();
	CString szPAssWd=pExpand->GetInputSignal()->GetPassWd();

	if(bIsUltra)
	{
		m_DragInfo.SetIPAddr(szIP);
		m_DragInfo.SetUseName(szUseName);
		m_DragInfo.SetPassWd(szPAssWd);
	}
	//***************************
	SetVecInputSignalIndexAndID(nInputIndex);
	//***************************
	//4K生成4个RTSP地址
	CreateRTSPAddr(szIP,szUseName,szPAssWd);
	//***************************
	m_DragInfo.SetText(szExpandName);
	m_DragInfo.SetExpand(&expandInfo);
	m_DragInfo.SetSignalGroupID(m_signalGroupID+1);
	m_DragInfo.SetInputIndex(nInputIndex);
	m_DragInfo.SetAnotherName(szAnotherName);
	m_DragInfo.SetRTSPAddr(szRTSPAddr);
	m_DragInfo.SetIsUltra(bIsUltra);
	m_DragInfo.SetIsHaveSignal(bIsHaveSignal);
	m_DragInfo.SetIsHavePane(bIsHavePane);
	m_DragInfo.SetSignalResulationH(pExpand->GetInputSignal()->GetReResulationH());
	m_DragInfo.SetSignalResulationV(pExpand->GetInputSignal()->GetReResulationV());
}

void XInputSignalTreeCtrl::DragDataInfo(HTREEITEM item)
{
	XDragInfo& pInfo=m_InputSignalPane->GetDragInfo();

	DWORD dwData=GetItemData(item);
	CString szItemText=GetItemText(item);
	XInputSignalExpand* pExpand=NULL;

	if(dwData==ITEMTYPE_INPUTGROUP)
		return;
	else if(dwData==ITEMTYPE_INPUTSIGNAL)
	{
		int nInputIndex=m_InputSignalPane->GetInputIndexByItemName(szItemText);
		XInputSignal* pSignal=m_InputSignalPane->GetInputSignalByIndex(nInputIndex);

		if(pSignal==NULL)
			return;

		pExpand=pSignal->GetDefaultExpand();
	}
	else
		pExpand = (XInputSignalExpand*)GetItemData(item);

	if (NULL==pExpand)
		return;

	int nInputIndex=pExpand->GetInputSignal()->GetInputIndex();
	XExpandInfo expandInfo=*(pExpand->GetExpandInfo());
	CString szExpandName=pExpand->GetName();
	CString szAnotherName=pExpand->GetInputSignal()->GetAnotherName();
	CString szRTSPAddr=pExpand->GetInputSignal()->GetRTSPAddr();

	//是否为4K
	m_InputSignalPane->IsUltra(nInputIndex);
	BOOL bIsUltra=pExpand->GetInputSignal()->GetIsUltra();

	//是否有信号
	BOOL bIsHaveSignal=m_InputSignalPane->IsHaveSignal(nInputIndex);

	//是否有板卡
	BOOL bIsHavePane=m_InputSignalPane->IsHavePan(nInputIndex);

	CString szIP=pExpand->GetInputSignal()->GetIPAddr();
	CString szUseName=pExpand->GetInputSignal()->GetUseName();
	CString szPassWd=pExpand->GetInputSignal()->GetPassWd();

	if(bIsUltra)
	{
		pInfo.SetIPAddr(szIP);
		pInfo.SetUseName(szUseName);
		pInfo.SetPassWd(szPassWd);
	}
	//***************************
	VEC_UNINT VecSignalID;
	pInfo.SetDragSignalID(m_signalID+1);
	pInfo.SetSignalID(m_signalID+1);
	unsigned int nSignalID=m_signalID;
	nSignalID&=0xFFFFFFF;
	nSignalID=nSignalID<<4;
	for(int i=0;i<4;i++)
	{
		nSignalID+=1;
		VecSignalID.push_back(nSignalID);
	}
	pInfo.SetVecDragSignalID(VecSignalID);
	//4k信号序号集合
	HYVEC_NUM VecSignalIndex;
	int nTempInputIndex=nInputIndex;
	for(int i=0;i<4;i++)
	{
		VecSignalIndex.push_back(nTempInputIndex);
		nTempInputIndex+=1;
	}
	pInfo.SetVecDragSignalIndex(VecSignalIndex);
	//***************************
	//4K生成4个RTSP地址
	VEC_CSTRING VecRTSPAddr;
	CString szHead=_T("rtsp://");
	CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
	//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

	CString szSubRTSP=_T("");
	for(int i=0;i<4;i++)
	{
		szSubRTSP=szHead+szUseName+_T(":")+szPassWd+_T("@")+szIP+szChenal[i]+_T("/")+_T("sub");
		VecRTSPAddr.push_back(szSubRTSP);
	}

	pInfo.SetVecRTSPAddr(VecRTSPAddr);
	//***************************
	pInfo.SetText(szExpandName);
	pInfo.SetExpand(&expandInfo);
	pInfo.SetDragSignalGroupID(m_signalGroupID+1);
	pInfo.SetSignalGroupID(m_signalGroupID+1);
	pInfo.SetInputIndex(nInputIndex);
	pInfo.SetAnotherName(szAnotherName);
	pInfo.SetRTSPAddr(szRTSPAddr);
	pInfo.SetIsUltra(bIsUltra);
	pInfo.SetIsHaveSignal(bIsHaveSignal);
	pInfo.SetIsHavePane(bIsHavePane);
}

void XInputSignalTreeCtrl::SetVecInputSignalIndexAndID(int nIndex)
{
	VEC_UNINT VecSignalID;
	m_DragInfo.SetSignalID(m_signalID+1);
	unsigned int nSignalID=m_signalID;
	nSignalID&=0xFFFFFFF;
	nSignalID=nSignalID<<4;
	for(int i=0;i<4;i++)
	{
		nSignalID+=1;
		VecSignalID.push_back(nSignalID);
	}
	m_DragInfo.SetVecSignalID(VecSignalID);
	//***************************
	//4k信号序号集合
	HYVEC_NUM VecSignalIndex;
	int nTempInputIndex=nIndex;
	for(int i=0;i<4;i++)
	{
		VecSignalIndex.push_back(nTempInputIndex);
		nTempInputIndex+=1;
	}
	m_DragInfo.SetVecSignalIndex(VecSignalIndex);
}

void XInputSignalTreeCtrl::CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd)
{
	VEC_CSTRING VecRTSPAddr;

	CString szHead=_T("rtsp://");
	CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};

	CString szSubRTSP=_T("");
	for(int i=0;i<4;i++)
	{
		szSubRTSP=szHead+szUseName+_T(":")+szPassWd+_T("@")+szIP+szChenal[i]+_T("/")+_T("sub");
		VecRTSPAddr.push_back(szSubRTSP);
	}

	m_DragInfo.SetVecRTSPAddr(VecRTSPAddr);
}

void XInputSignalTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM hItem;
	UINT flags;

	//m_HoverPoint=point;

	CRect rect;
	GetClientRect(&rect);

	if(point.x<rect.right)
	{
		if(m_bDragging)
		{
			CPoint pt=point;
			CImageList::DragMove(pt);
			CImageList::DragShowNolock(FALSE);
			if((hItem=HitTest(point,&flags))!=NULL)
			{
				SelectDropTarget(hItem);
				m_hItemDragD=hItem;

				//TRACE(_T("m_hItemDragD\n"));
			}
			CImageList::DragShowNolock(TRUE);
		}
	}	
	else
	{
		if(m_bDragging)
		{
			m_bDragging=FALSE;
			CImageList::DragLeave(this);
			CImageList::EndDrag();
			delete m_pDragImage;
			SelectDropTarget(NULL);
			KillTimer(m_nScrollTimerID);
		}
		if (!m_Drag)
			return;
		ClientToScreen(&point);
		if (m_DragWnd==NULL)
			CreateDragWnd();
		MoveDragWnd(point);
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void XInputSignalTreeCtrl::CreateDragWnd()
{
	m_DragWnd = m_InputSignalPane->CreateDragWnd(&m_DragInfo);
}

void XInputSignalTreeCtrl::MoveDragWnd(CPoint& point)
{
	if (m_DragWnd!=NULL)
		m_DragWnd->Move(point);
}

void XInputSignalTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	if(point.x<rect.right)
	{
		if(m_bDragging)
		{
			m_bDragging=FALSE;
			CImageList::DragLeave(this);
			CImageList::EndDrag();
			ReleaseCapture();
			delete m_pDragImage;
			SelectDropTarget(NULL);
			KillTimer(m_nScrollTimerID);

			Expand(m_hItemDragD,TVE_EXPAND);

			//添加组
			m_InputSignalPane->AddDragIntoGroup(m_hItemDragS,m_hItemDragD);
		}
	}
	else
	{
		if(this==GetCapture())
			ReleaseCapture();
		m_Drag = FALSE;
		MoveDragWndEnd();
	}
}

void XInputSignalTreeCtrl::MoveDragWndEnd()
{
	if (m_DragWnd != NULL)
	{
		if (m_InputSignalPane->GetNetState())
		{
			CRect rectDrag;
			m_DragWnd->GetWindowRect(&rectDrag);

			CPoint point;
			GetCursorPos(&point);

			m_DragWnd->Hide();
			m_InputSignalPane->DragInfo(rectDrag,point,m_DragWnd->GetDragInfo());
			m_DragWnd = NULL;
		}
		else
		{
			m_DragWnd->Hide();
			m_DragWnd = NULL;
			m_InputSignalPane->MessageBoxFromKey(_T("312"), _T("网络未打开!"), MB_OK);
		}
	}
}

void XInputSignalTreeCtrl::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==m_nHoverTimerID)
	{
		//鼠标停留展开树

		//KillTimer(m_nHoverTimerID);

		//m_nHoverTimerID=0;

		//HTREEITEM trItem=0;

		//UINT uFlag=0;

		//trItem=HitTest(m_HoverPoint,&uFlag);

		//if(trItem&&m_bDragging)
		//{
		//	SelectItem(trItem);

		//	Expand(trItem,TVE_EXPAND);
		//}
	}
	else if(nIDEvent==m_nScrollTimerID)
	{
		m_TimerTicks++;

		CPoint  pt;
		GetCursorPos(&pt);
		CRect rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);

		HTREEITEM hItem=GetFirstVisibleItem();
		if(pt.y<rect.top+10)
		{
			//向上滚动
			int slowscroll=6-(rect.top+10-pt.y)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL,SB_LINEUP);
				SelectDropTarget(hItem);
				m_hItemDragD=hItem;
				CImageList::DragShowNolock(TRUE);
			}
		}
		else if(pt.y>rect.bottom-10)
		{
			//向下滚动
			int slowscroll=6-(pt.y-rect.bottom+10)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL,SB_LINEDOWN);
				int nCount=GetVisibleCount();
				for(int i=0;i<nCount-1;i++)
					hItem=GetNextVisibleItem(hItem);
					
				if(hItem)
					SelectDropTarget(hItem);

				m_hItemDragD=hItem;
				CImageList::DragShowNolock(true);
			}
		}
	}

	CTreeCtrl::OnTimer(nIDEvent);
}

void XInputSignalTreeCtrl::OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVCUSTOMDRAW pNMCD=reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);

	NMCUSTOMDRAW nmCustomDraw=pNMCD->nmcd;

	switch(nmCustomDraw.dwDrawStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			if(nmCustomDraw.uItemState&CDIS_SELECTED)
				pNMCD->clrTextBk=RGB(51, 153, 255);
		}
		break;
	default:
		break;
	}

	*pResult=0;
	*pResult|=CDRF_NOTIFYPOSTPAINT;
	*pResult|=CDRF_NOTIFYITEMDRAW;

	return;
}