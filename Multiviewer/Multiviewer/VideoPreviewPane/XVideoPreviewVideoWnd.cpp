// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XVideoPreviewVideoWnd.h"
#include "XVideoPreviewFrame.h"
#include "XConstantIM.h"
#include "XVideoPreviewPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "XDeviceInfo.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XInputSignal.h"
#include "XExpandInfo.h"
#include "XInputSignalExpand.h"

// XVideoPreviewVideoWnd

IMPLEMENT_DYNAMIC(XVideoPreviewVideoWnd, CWnd)

XVideoPreviewVideoWnd::XVideoPreviewVideoWnd()
{
	m_Frame = NULL;

	m_PreviewDragWnd=NULL;

	m_Drag=FALSE;

	m_Contain=NULL;

	m_szTips=_T("");

}

XVideoPreviewVideoWnd::~XVideoPreviewVideoWnd()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XVideoPreviewVideoWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// XVideoPreviewVideoWnd 消息处理程序

BOOL XVideoPreviewVideoWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);
}

BOOL XVideoPreviewVideoWnd::PreTranslateMessage(MSG* pMsg)
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
		default:
			break;
		}  
	} 
	else if(pMsg->message==WM_MOUSEMOVE)
	{
		m_TipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

void XVideoPreviewVideoWnd::SetFrame(XVideoPreviewFrame* p)
{
	m_Frame = p;
}

void XVideoPreviewVideoWnd::SetVideoPreviewPan(XVideoPreviewPane* p)
{
	m_Pan=p;
}

void XVideoPreviewVideoWnd::SetVideoPreviewContain(XVideoPreviewContain* p)
{
	m_Contain=p;
}

BOOL XVideoPreviewVideoWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XVideoPreviewVideoWnd::ReloadInterface()
{
	m_szTips=m_Pan->GetTranslationString(_T("692"),_T("拖拽输入信号到此处进行预览，网络和码率在添加预览卡中设置"));
	m_TipCtrl.AddTool(this,m_szTips);
}

void XVideoPreviewVideoWnd::InitTips()
{
	//m_szTips=m_Pan->GetTranslationString(_T("692"),_T("拖拽输入信号到此处进行预览，网络和码率在添加预览卡中设置"));
	
	m_TipCtrl.Create(this);
	m_TipCtrl.SetDelayTime(200); 
	m_TipCtrl.SetTipTextColor(RGB(0,0,255));
	m_TipCtrl.SetTipBkColor(RGB(240,240,240));
	m_TipCtrl.Activate(TRUE); 
}

void XVideoPreviewVideoWnd::OnPaint()
{
	CPaintDC dc(this); 
	/*
	CRect rt;
	GetClientRect(&rt);

	CBrush bru;
	bru.CreateSolidBrush(RGB(255, 0, 0));
	dc.FillRect(&rt, &bru);
	*/
}

void XVideoPreviewVideoWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_Frame != NULL)
	{
		m_Frame->GetPane()->ShowViewPreviewDlg(m_Frame->GetIP(),m_Frame->GetRTSPAddr(),m_Frame->GetIndex(),m_Frame->GetUseName(),m_Frame->getPassWd());
	}
}

void XVideoPreviewVideoWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnRButtonUp(nFlags, point);

	if (m_Frame->GetPane()->GetDelegate()->IsLogin())
	{
		//ShowMenu();
	}
}

void XVideoPreviewVideoWnd::ShowMenu()
{

}

void XVideoPreviewVideoWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();

	GetCursorPos(&point);

	m_DragPoint=point;

	m_Drag=TRUE;

	m_PreviewDragWnd=NULL;
}

void XVideoPreviewVideoWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_Drag)
	{
		return;
	}

	ClientToScreen(&point);

	//设置拖拽信息
	SetDragRTSPInfo();

	if(m_PreviewDragWnd==NULL)
	{
		CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

		int nDecideMoveDistance=HandleIni::GetInt(_T("Info"),_T("DecideMoveDistance"),10,szIniPath);

		if((abs(point.x-m_DragPoint.x)>nDecideMoveDistance)||(abs(point.y-m_DragPoint.y)>nDecideMoveDistance))
		{
			CreatePreviewDragWnd();
		}
	}

	MovePreviewDragWnd(point);
}

void XVideoPreviewVideoWnd::SetDragRTSPInfo()
{
	XVideoPreviewFrame* pFrame=m_Frame;

	int nPreviewIndex=pFrame->GetIndex();

	CString szAnotherName=pFrame->GetAnotherName();

	CString szRTSP=pFrame->GetRTSPAddr();

	CString szIP=pFrame->GetIP();

	CString szUseName=pFrame->GetUseName();

	CString szPassWd=pFrame->getPassWd();

	BOOL bIsUltra=pFrame->GetIsUltra();

	BOOL bIsHaveSignal=pFrame->GetIsHaveSignal();

	BOOL bIsHavePane=pFrame->GetIsHavePane();

	VEC_CSTRING& VecRTSPAddr=pFrame->GetVecRTSPAddr();

	//ID集合和序号集合
	SetVecPreviewIndexAndID(nPreviewIndex);

	XInputSignal* pInput=m_Pan->GetDelegate()->GetInputByIndex(nPreviewIndex);

	if(pInput==NULL)
	{
		return;
	}

	XInputSignalExpand* pExpand=pInput->GetDefaultExpand();

	XExpandInfo* pExpandInfo=pExpand->GetExpandInfo();

	//局部放大为零（预览先不要局部放大）
	pExpandInfo->SetExpand(0,0,0,0);

	m_RTSPInfo.SetPreviewGroupID(m_signalGroupID+1);
	m_RTSPInfo.SetIsUltra(bIsUltra);
	m_RTSPInfo.SetRTSPAddr(szRTSP);
	m_RTSPInfo.SetPreviewIndex(nPreviewIndex);
	m_RTSPInfo.SetAnotherName(szAnotherName);
	m_RTSPInfo.SetExpandInfo(pExpandInfo);
	m_RTSPInfo.SetVecRTSPAddr(VecRTSPAddr);
	m_RTSPInfo.SetIPAddr(szIP);
	m_RTSPInfo.SetUseName(szUseName);
	m_RTSPInfo.SetPassWd(szPassWd);
	m_RTSPInfo.SetIsHaveSignal(bIsHaveSignal);
	m_RTSPInfo.SetIsHavePane(bIsHavePane);

	//delete pExpandInfo;
}

BOOL XVideoPreviewVideoWnd::GetIsUltra(int& nIndex)
{
	BOOL IsUltra=FALSE;

	VEC_INPUTSIGNAL& VecInput=m_Pan->GetDelegate()->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal* pInput=*iter;

		if(pInput->GetInputIndex()==nIndex)
		{
			IsUltra=pInput->GetIsUltra();
		}
	}

	return IsUltra;
}

void XVideoPreviewVideoWnd::SetVecPreviewIndexAndID(int nIndex)
{
	VEC_UNINT VecSignalID;
	m_RTSPInfo.SetPreviewID(m_signalID+1);
	unsigned int nSignalID=m_signalID;
	nSignalID&=0xFFFFFFF;
	nSignalID=nSignalID<<4;
	for(int i=0;i<4;i++)
	{
		nSignalID+=1;
		VecSignalID.push_back(nSignalID);
	}
	m_RTSPInfo.SetVecPreviewID(VecSignalID);
	//***************************
	//4k信号序号集合
	HYVEC_NUM VecSignalIndex;
	int nTempInputIndex=nIndex;
	for(int i=0;i<4;i++)
	{
		VecSignalIndex.push_back(nTempInputIndex);
		nTempInputIndex+=1;
	}
	m_RTSPInfo.SetVecPreviewIndex(VecSignalIndex);
}

void XVideoPreviewVideoWnd::CreatePreviewDragWnd()
{
	m_PreviewDragWnd=m_Pan->CreatePreviewDragWnd(&m_RTSPInfo);
}

void XVideoPreviewVideoWnd::MovePreviewDragWnd(CPoint& point)
{
	if(m_PreviewDragWnd!=NULL)
	{
		m_PreviewDragWnd->Move(point);
	}
}

void XVideoPreviewVideoWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(this==GetCapture())
	{
		ReleaseCapture();
	}

	m_Drag=FALSE;

	MovePreviewDragWndEnd();
}

void XVideoPreviewVideoWnd::MovePreviewDragWndEnd()
{
	if(m_PreviewDragWnd!=NULL)
	{
		if(m_Pan->GetNetState())
		{
			CRect rectDrag;

			m_PreviewDragWnd->GetWindowRect(&rectDrag);

			m_PreviewDragWnd->Hide();

			m_Pan->DragInfo(rectDrag,m_PreviewDragWnd->GetRTSPInfo());

			m_PreviewDragWnd=NULL;
		}
		else
		{
			m_PreviewDragWnd->Hide();

			m_PreviewDragWnd=NULL;

			m_Pan->MessageBoxFromKey(_T("312"), _T("网络未打开!"), MB_OK);
		}
	}
}
