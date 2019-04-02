#include "StdAfx.h"
#include "XVideoPreviewFrame.h"
#include "XVideoPreviewVideoWnd.h"
#include "XVideoPreviewPane.h"
#include "XVideoPreviewTextWnd.h"
#include "XDelegateVideoPreviewPane.h"
#include "ChangeRTSPAddrDlg.h"
#include "ChangeInputDlg.h"
#include "XSendDataVideoPreview.h"
#include "XInputSignal.h"
#include "XMultiVideoWindow.h"

XVideoPreviewFrame::XVideoPreviewFrame(void)
{
	m_Pane = NULL;

	m_TextWnd = NULL;

	m_VideoWnd = NULL;

	m_nFrameIndex = 0;

	m_RTSPAddr = _T("");

	m_szIP=_T("");

	m_szUseName=_T("");

	m_szPassWd=_T("");

	m_Index = 0;

	m_nBoardIndex=0;

	m_DeviceInfo=NULL;

	m_pMultiVideoWindow=NULL;

	m_bIsUltra=FALSE;

	m_bIsHaveSignal=FALSE;

	m_bIsHavePane=FALSE;
}

XVideoPreviewFrame::~XVideoPreviewFrame(void)
{
	ClearVideoWnd();

	ClearTextWnd();
}

void XVideoPreviewFrame::ClearVideoWnd()
{
	if (m_VideoWnd != NULL)
	{
		delete m_VideoWnd;
		m_VideoWnd = NULL;
	}
}

void XVideoPreviewFrame::ClearTextWnd()
{
	if (m_TextWnd != NULL)
	{
		delete m_TextWnd;
		m_TextWnd = NULL;
	}
}

void XVideoPreviewFrame::SetPane(XVideoPreviewPane* p)
{
	m_Pane = p;
}

void XVideoPreviewFrame::SetFrameIndex(int n)
{
	m_nFrameIndex = n;
}

void XVideoPreviewFrame::SetContain(XVideoPreviewContain* p)
{
	m_Contain = p;
}

void XVideoPreviewFrame::SetRect(CRect r)
{
	m_Rect = r;
}

int XVideoPreviewFrame::GetFrameIndex()
{
	return m_nFrameIndex;
}

CRect XVideoPreviewFrame::GetRect()
{
	return m_Rect;
}

void XVideoPreviewFrame::SetRTSPAddr(CString s)
{
	m_RTSPAddr = s;
}

CString XVideoPreviewFrame::GetRTSPAddr()
{
	return m_RTSPAddr;
}

void XVideoPreviewFrame::SetIndex(int n)
{
	m_Index = n;
}

int XVideoPreviewFrame::GetIndex()
{
	return m_Index;
}

void XVideoPreviewFrame::SetIP(CString szIP)
{
	m_szIP=szIP;
}

CString XVideoPreviewFrame::GetIP()
{
	return m_szIP;
}

void XVideoPreviewFrame::SetUseName(CString szName)
{
	m_szUseName=szName;
}

CString XVideoPreviewFrame::GetUseName()
{
	return m_szUseName;
}

void XVideoPreviewFrame::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}
CString XVideoPreviewFrame::getPassWd()
{
	return m_szPassWd;
}

void XVideoPreviewFrame::SetIsUltra(BOOL bIsUltra)
{
	m_bIsUltra=bIsUltra;
}

BOOL XVideoPreviewFrame::GetIsUltra()
{
	return m_bIsUltra;
}

void XVideoPreviewFrame::SetIsHaveSignal(BOOL b)
{
	m_bIsHaveSignal=b;
}

BOOL XVideoPreviewFrame::GetIsHaveSignal()
{
	return m_bIsHaveSignal;
}

void XVideoPreviewFrame::SetIsHavePane(BOOL b)
{
	m_bIsHavePane=b;
}

BOOL XVideoPreviewFrame::GetIsHavePane()
{
	return m_bIsHavePane;
}

void XVideoPreviewFrame::SetPreviewBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XVideoPreviewFrame::GetPreviewBoardIndex()
{
	return m_nBoardIndex;
}

void XVideoPreviewFrame::SetAnotherName(CString szAnotherName)
{
	m_szAnotherName=szAnotherName;
}

CString XVideoPreviewFrame::GetAnotherName()
{
	return m_szAnotherName;
}

XDeviceInfo* XVideoPreviewFrame::GetDeviceInfo()
{
	return m_DeviceInfo;
}

void XVideoPreviewFrame::SetDeviceInfo(XDeviceInfo* pInfo)
{
	m_DeviceInfo=pInfo;
}

void XVideoPreviewFrame::Init()
{
	ClearVideoWnd();

	ClearTextWnd();

	CreateVideoWnd();

	CreateTextWnd();

	UpdateText();

	AddMultiVideoWindow();

	CreateRTSPAddr();

	AddRTSP();

	InitFrame();
}

void XVideoPreviewFrame::AdjustRect()
{
	CRect rectV=m_Rect;
	rectV.bottom=rectV.bottom-VIDEOPREVIEW_TEXTHEIGHT;
	m_VideoRect=rectV;

	m_VideoWnd->MoveWindow(m_VideoRect);

	CRect rectT=m_Rect;
	rectT.top=rectT.bottom - VIDEOPREVIEW_TEXTHEIGHT;
	m_TextWnd->MoveWindow(rectT);

	m_Contain->Invalidate(FALSE);
}

void XVideoPreviewFrame::AdjustMultiVideoWindowSize()
{
	CRect rect;

	GetClientRect(m_VideoWnd->GetSafeHwnd(),&rect);
	m_Pane->GetDelegate()->AdjustMultiVideoWindowHWNDSize(m_pMultiVideoWindow,rect.Width(),rect.Height());
}

void XVideoPreviewFrame::AddMultiVideoWindow()
{
	m_pMultiVideoWindow=m_Pane->GetDelegate()->AddMultiVideoWindow(m_VideoWnd->GetSafeHwnd());
}

void XVideoPreviewFrame::InitFrame()
{
	if(m_bIsUltra)
	{
		if(m_bIsHaveSignal&&m_bIsHavePane)
			AddUltraFrame();
		else
			ClearFrame();
	}
	else
	{
		if(m_bIsHaveSignal&&m_bIsHavePane)
			AddCommFrame();
		else
			ClearFrame();	
	}
}

void XVideoPreviewFrame::ClearFrame()
{
	if(m_pMultiVideoWindow==NULL)
		return;

	m_pMultiVideoWindow->DeleteFrame(m_nFrameIndex);
}

void XVideoPreviewFrame::AddUltraFrame()
{
	if(m_pMultiVideoWindow==NULL)
		return;

	RECTF rect(0,0,200,112);
	VEC_RECTF VecRect;
	m_Pane->SetRectToFoure(rect,VecRect);

	RECTF InterRect(0,0,1920,1088);

	int i=0;
	for(VEC_RECTF::iterator iter=VecRect.begin();iter!=VecRect.end();++iter)
	{
		RECTF rect=*iter;

		CString szRTSPAddr=m_VecRTSPAddr[i];
		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nFrameIndex,szRTSPAddr,rect,InterRect);
		i++;
	}
}

void XVideoPreviewFrame::AddCommFrame()
{
	if(m_pMultiVideoWindow==NULL)
		return;

	RECTF rect(0,0,200,112);
	RECTF InterRect(0,0,1920,1088);
	XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nFrameIndex,m_RTSPAddr,rect,InterRect);
}

void XVideoPreviewFrame::CreateRTSPAddr()
{
	if(m_szUseName!=_T("")
		&&m_szPassWd!=_T("")
		&&m_szIP!=_T(""))
	{
		ClearRTSPAddr();

		CString szHead=_T("rtsp://");
		CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
		//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

		CString szSubRTSP=_T("");
		for(int i=0;i<4;i++)
		{
			szSubRTSP=szHead+m_szUseName+_T(":")+m_szPassWd+_T("@")+m_szIP+szChenal[i]+_T("/")+_T("sub");
			m_VecRTSPAddr.push_back(szSubRTSP);
			//TRACE(_T("CreateRTSP=%s\n"),szSubRTSP);
		}
	}
}

VEC_CSTRING& XVideoPreviewFrame::GetVecRTSPAddr()
{
	return m_VecRTSPAddr;
}

void XVideoPreviewFrame::AddRTSP()
{
	m_Pane->AddRTSPAddr(m_RTSPAddr);

	for(VEC_CSTRING::iterator iter=m_VecRTSPAddr.begin();iter!=m_VecRTSPAddr.end();++iter)
	{
		CString szRTSPAddr=*iter;
		m_Pane->AddRTSPAddr(szRTSPAddr);
		//TRACE(_T("FrameRTSP=%s\n"),szRTSPAddr);
	}
}

void XVideoPreviewFrame::ClearRTSPAddr()
{
	m_VecRTSPAddr.clear();
}

void XVideoPreviewFrame::CreateVideoWnd()
{
	CRect rect = m_Rect;
	rect.bottom = rect.bottom - VIDEOPREVIEW_TEXTHEIGHT;

	m_VideoRect=rect;

	XVideoPreviewVideoWnd* pWnd = new XVideoPreviewVideoWnd;
	pWnd->Create(WS_CHILD|WS_VISIBLE, rect, m_Contain, 0);
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();
	pWnd->SetFrame(this);
	pWnd->SetVideoPreviewPan(m_Pane);
	pWnd->SetVideoPreviewContain(m_Contain);

	//显示提示信息
	
	pWnd->InitTips();
	pWnd->ReloadInterface();

	m_VideoWnd = pWnd;
}

void XVideoPreviewFrame::CreateTextWnd()
{
	CRect rect = m_Rect;
	rect.top = rect.bottom - VIDEOPREVIEW_TEXTHEIGHT;

	XVideoPreviewTextWnd* pWnd = new XVideoPreviewTextWnd;
	pWnd->Create(WS_CHILD|WS_VISIBLE, rect, m_Contain, 0);
	pWnd->SetFont(m_Pane->GetFont());
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();

	m_TextWnd = pWnd;
}

void XVideoPreviewFrame::UpdateText()
{
	CString szText = _T("");

	if(m_Index!=0)
	{
		if(m_szAnotherName!=_T(""))
		{
			szText.Format(_T("%s %d"),
				m_Pane->GetDelegate()->GetTranslationString(_T("373"), _T("输入")), 
				m_Index);

			CString szStr=szText+_T("(")+m_szAnotherName+_T(")");
			m_TextWnd->SetText(szStr);
		}
		else
		{
			szText.Format(_T("%s %d"),
				m_Pane->GetDelegate()->GetTranslationString(_T("373"), _T("输入")), 
				m_Index);
			m_TextWnd->SetText(szText);
		}
	}
	else
		m_TextWnd->SetText(_T(""));
}

void XVideoPreviewFrame::ReloadInterface()
{
	UpdateText();
	m_VideoWnd->ReloadInterface();
}

XVideoPreviewPane* XVideoPreviewFrame::GetPane()
{
	return m_Pane;
}

CRect XVideoPreviewFrame::GetVideoRect()
{
	CRect rect;
	m_VideoWnd->GetWindowRect(&rect);
	return rect;
}

void XVideoPreviewFrame::SetPreviewFrame()
{
	ClearFrame();
	CreateRTSPAddr();

	if(m_bIsUltra)
	{
		if(m_bIsHaveSignal&&m_bIsHavePane)
			AddUltraFrame();
	}
	else
	{
		if(m_bIsHaveSignal&&m_bIsHavePane)
			AddCommFrame();
	}
}

void XVideoPreviewFrame::RunOrder()
{
	//发送指令切换输入源到预览卡
	int nBoardChenal=(m_nBoardIndex-1)*4+m_nFrameIndex;
	XSendDataVideoPreview::AddSendDataOfCorrBoardChenal(m_Pane,m_Index,nBoardChenal);
}

void XVideoPreviewFrame::SetSignalRTSPAddr()
{
	//设置输入RTSP地址
	m_Pane->SetInputRTSPAddrByIndex(m_Index,m_RTSPAddr);

	//设置屏幕信号RTSP
	m_Pane->SetScreenSignalRTSPAddrByIndex(m_Index,m_RTSPAddr);

	//设置输入信号IP，用户名，密码
	m_Pane->SetInputParaByIndex(m_Index,m_szIP,m_szUseName,m_szPassWd);
}