// InputSignal.cpp : 实现文件
//

#include "stdafx.h"
#include "XVideoPreviewPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "..\MainFrm.h"
#include "..\resource.h"
#include "XVideoPreviewFrame.h"
#include "XDataVideoPreviewPane.h"
#include "HandleIni.h"
#include "HandlePath.h"
#include "XDeviceInfo.h"
#include "XSendDataVideoPreview.h"
#include "XPreviewRTSPInfo.h"
#include "XInputSignal.h"
#include "XDragInfo.h"



#define FONT_SIZE			20		//字体大小
#define FRAME_DISTANCE		10		//预览框间隔

IMPLEMENT_DYNAMIC(XVideoPreviewPane, CDockablePane)

XVideoPreviewPane::XVideoPreviewPane()
{
	m_pDelegate = NULL;
	m_bDisableAnimation = TRUE;
	m_nSlideSteps = 1;
	m_CreateContain = FALSE;
	m_ViewPreviewDlg = NULL;
	m_InterRect=0;
	m_pMultiVideoWindow=NULL;
	m_nBoardIndex=0;
	m_szUserName=_T("");
	m_szPassWd=_T("");
	m_szIP=_T("");
}

XVideoPreviewPane::~XVideoPreviewPane()
{
	ClearVecFrame();
	ClearDeviceInfo();
	DeleteFont();
	ClearPreviewDlg();
	ClearVecRTSP();
}

BEGIN_MESSAGE_MAP(XVideoPreviewPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()

END_MESSAGE_MAP()


// XVideoPreviewPane 消息处理程序


void XVideoPreviewPane::SetDelegate(XDelegateVideoPreviewPane* pDelegate)
{
	m_pDelegate = pDelegate;
}

XDelegateVideoPreviewPane* XVideoPreviewPane::GetDelegate()
{
	return m_pDelegate;
}

void XVideoPreviewPane::ClearVecFrame()
{
	for (VEC_VIDEOPREVIEWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
		delete *iter;

	m_VecFrame.clear();
}

void XVideoPreviewPane::ClearDeviceInfo()
{
	for (VEC_DEVICEINFO::iterator iter = m_VecDeviceInfo.begin(); iter != m_VecDeviceInfo.end(); iter++)
		delete *iter;

	m_VecDeviceInfo.clear();
}

void XVideoPreviewPane::DeleteFont()
{
	m_Font.DeleteObject();
}

void XVideoPreviewPane::ClearPreviewDlg()
{
	if (NULL != m_ViewPreviewDlg)
	{
		delete m_ViewPreviewDlg;
		m_ViewPreviewDlg = NULL;
	}
}

void XVideoPreviewPane::ClearVecRTSP()
{
	m_VecRTSPAddr.clear();
}


VEC_VIDEOPREVIEWFRAME& XVideoPreviewPane::GetVecFrame()
{
	return m_VecFrame;
}

VEC_DEVICEINFO& XVideoPreviewPane::GetVecDeviceInfo()
{
	return m_VecDeviceInfo;
}

VEC_INPUTSIGNAL& XVideoPreviewPane::GetVecInputSignal()
{
	return m_pDelegate->GetVecInputSignal();
}

void XVideoPreviewPane::Init()
{
	InitFont();
	CreatePane();
	CreateContain();
	InitVecFrame();
	AdjustScroll();
	InitViewPreviewDlg();
	CreateRTSPAddr();
	SetFrameParamater();
}

void XVideoPreviewPane::InitFont()
{
	m_Font.CreateFont(   
		FONT_SIZE,    
		0,                
		0,                
		0,                 
		0,                 
		FALSE,             
		FALSE,              
		FALSE,              
		DEFAULT_CHARSET,     
		OUT_DEFAULT_PRECIS,   
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,      
		DEFAULT_PITCH,         
		APP_FONT);
}

CFont* XVideoPreviewPane::GetFont()
{
	return &m_Font;
}

CString XVideoPreviewPane::GetTitle()
{
	MAP_TABLABLE& MapTabLable=m_pDelegate->GetMapBottomTabLable();

	CString szPreview=m_pDelegate->GetTranslationString(_T("682"),_T("预览卡"));
	CString szTemp=m_pDelegate->GetTranslationString(_T("683"),_T("槽位"));

	CString szName=_T("");
	szName.Format(_T("%s-%s%d"),szPreview,szTemp,m_nBoardIndex);

	CString szTitle=_T("");
	MAP_TABLABLE::iterator iter=MapTabLable.find(szName);
	if(iter!=MapTabLable.end())
	{
		CString szAnotherName=iter->second;

		CString szTempTitle=_T("");
		if(szAnotherName!=_T(""))
			szTempTitle.Format(_T("%s(%s)"),szName,szAnotherName);
		else
			szTempTitle=szName;

		szTitle=szTempTitle;
	}
	else
		szTitle=szName;

	int nLen=szTitle.GetLength();
	if(nLen<20)
	{
		int n=20-nLen;
		for(int i=0;i<n;i++)
			szTitle+=_T(" ");
	}

	return szTitle;
}

void XVideoPreviewPane::CreatePane()
{
	CWnd* pWnd=m_pDelegate->GetCWND();
	CMainFrame* pMainFrame=(CMainFrame*)pWnd;
	CString szTitle=GetTitle();

	if (!Create(szTitle,pMainFrame,CRect(0,0,400,230),TRUE,
		ID_VIDEOPREVIEWPANE,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|
		WS_CLIPCHILDREN|CBRS_BOTTOM,AFX_CBRS_REGULAR_TABS))
		return; 

	EnableDocking(CBRS_BORDER_ANY);
	pMainFrame->DockPane(this);
	CSize size(400,200);
	CDockablePane::SetMinSize(size);
	ShowPane(FALSE,FALSE,TRUE);
}

void XVideoPreviewPane::CreateContain()
{
	CRect rt;
	GetClientRect(&rt);

	m_Contain.SetPane(this);
	m_Contain.Create(WS_CHILD|WS_VISIBLE, rt, this, 0);
	m_Contain.ShowWindow(SW_SHOW);
	m_Contain.UpdateWindow();
	
	m_CreateContain = TRUE;
}

void XVideoPreviewPane::AdjustScroll()
{
	m_Contain.AdjustScrollV();
	m_Contain.AdjustScrollH();
}

void XVideoPreviewPane::ReloadInterface()
{
	CString szTitle=GetTitle();
	SetWindowText(szTitle);

	for (VEC_VIDEOPREVIEWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XVideoPreviewFrame* pFrame = *iter;
		pFrame->ReloadInterface();
	}
}

int XVideoPreviewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void XVideoPreviewPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout1();
	AdjustMultiVideoWindowSize();
}

void XVideoPreviewPane::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rect, &bruDB);
}

void XVideoPreviewPane::AdjustLayout1()
{
	if (!m_CreateContain)
		return;

	CRect rect;
	GetClientRect(rect);
	m_Contain.MoveWindow(rect);
	AdjustVecFrame(rect);
	AdjustScroll();
}

void XVideoPreviewPane::AdjustVecFrame(CRect rect)
{
	int nDistance=FRAME_DISTANCE;
	int nFrameWidth=200;
	int nFrameHeight=112+FONT_SIZE;
	int nInterWidth=nFrameWidth*4+nDistance*3;
	int nBeginWidth=(rect.Width()-nInterWidth)/2;
	int nBeginHight=(rect.Height()-nFrameHeight)/2;
	int nX=nBeginWidth;
	int nY=nBeginHight+nDistance;

	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();iter++)
	{
		CRect rectFrame(nX,nY,nX+nFrameWidth,nY+nFrameHeight);

		XVideoPreviewFrame* pFrame=*iter;
		pFrame->ClearFrame();
		pFrame->SetRect(rectFrame);
		pFrame->AdjustRect();
		pFrame->InitFrame();
		nX=nX+nFrameWidth+nDistance;
	}
}

void XVideoPreviewPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
}

void XVideoPreviewPane::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	return;
}

void XVideoPreviewPane::InitVecFrame()
{
	CRect rect;
	m_Contain.GetClientRect(&rect);

	int nDistance=FRAME_DISTANCE;
	int nFrameWidth=200;
	int nFrameHeight=112+FONT_SIZE;
	int nInterWidth=nFrameWidth*4+nDistance*3;
	int nBeginWidth=(rect.Width()-nInterWidth)/2;
	int nBeginHight=(rect.Height()-nFrameHeight)/2;
	int nX=nBeginWidth;
	int nY=nBeginHight+nDistance;

	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();iter++)
	{
		CRect rectFrame(nX,nY,nX+nFrameWidth,nY+nFrameHeight);
		XVideoPreviewFrame* pFrame=*iter;
		pFrame->SetRect(rectFrame);
		pFrame->SetContain(&m_Contain);
		pFrame->Init();
		nX=nX+nFrameWidth+nDistance;
	}
}

void XVideoPreviewPane::SetFrameParamater()
{
	int nIndex=0;

	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();iter++)
	{
		XVideoPreviewFrame* pFrame=*iter;
		pFrame->SetPreviewBoardIndex(m_nBoardIndex);
		pFrame->SetIP(m_szIP);
		pFrame->SetUseName(m_szUserName);
		pFrame->SetPassWd(m_szPassWd);
		nIndex++;
	}
}

int XVideoPreviewPane::GetContainScrollHeight()
{
	int nFrameSize=m_VecFrame.size();

	if (nFrameSize<=0)
		return 0;

	XVideoPreviewFrame* pFrame=m_VecFrame[nFrameSize-1];
	CRect rect=pFrame->GetRect();
	return rect.bottom+FRAME_DISTANCE;
}

int XVideoPreviewPane::GetContainScrollMax()
{
	int nFrameSize=m_VecFrame.size();

	if (nFrameSize<=0)
		return 0;

	XVideoPreviewFrame* pFrame=m_VecFrame[nFrameSize-1];
	CRect rect=pFrame->GetRect();
	return rect.right+FRAME_DISTANCE;
}

int XVideoPreviewPane::GetFrameLeft()
{
	int nFrameSize=m_VecFrame.size();

	if (nFrameSize<=0)
		return 0;

	XVideoPreviewFrame* pFrame=m_VecFrame[0];
	CRect rect=pFrame->GetRect();
	return rect.left-FRAME_DISTANCE;
}

int XVideoPreviewPane::GetFrameRight()
{
	int nFrameSize=m_VecFrame.size();

	if (nFrameSize<=0)
		return 0;

	XVideoPreviewFrame* pFrame=m_VecFrame[nFrameSize-1];
	CRect rect=pFrame->GetRect();
	return rect.right+FRAME_DISTANCE;
}

void XVideoPreviewPane::CreateRTSPAddr()
{
	if(m_szUserName!=_T("")
		&&m_szPassWd!=_T("")
		&&m_szIP!=_T(""))
	{
		CString szHead=_T("rtsp://");
		CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
		//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

		CString szSubRTSP=_T("");
		for(int i=0;i<4;i++)
		{
			szSubRTSP=szHead+m_szUserName+_T(":")+m_szPassWd+_T("@")+m_szIP+szChenal[i]+_T("/")+_T("sub");
			AddRTSPAddr(szSubRTSP);
			AddVecRTSP(szSubRTSP);
		}

		SetframeRTSPAddr();
	}
}

void XVideoPreviewPane::SetframeRTSPAddr()
{
	int nIndex=0;

	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();iter++)
	{
		XVideoPreviewFrame* pFrame=*iter;
		pFrame->SetRTSPAddr(m_VecRTSPAddr[nIndex]);
		nIndex++;
	}
}

void XVideoPreviewPane::AddVecRTSP(CString szSubRTSP)
{
	m_VecRTSPAddr.push_back(szSubRTSP);
}

void XVideoPreviewPane::ResetData()
{
	for(int i=1;i<=4;i++)
	{
		XVideoPreviewFrame* pFrame=new XVideoPreviewFrame;
		pFrame->SetPane(this);
		pFrame->SetFrameIndex(i);
		m_VecFrame.push_back(pFrame);
	}
}

void XVideoPreviewPane::GetData(CArchive& arch)
{
	XDataVideoPreviewPane::GetData(this, arch);
}

void XVideoPreviewPane::SaveData(CArchive& arch)
{
	XDataVideoPreviewPane::SaveData(this, arch);
}

BOOL XVideoPreviewPane::GetNetState()
{
	return m_pDelegate->GetNetState();
}

BOOL XVideoPreviewPane::SendData(char* pData, int nDataLen)
{
	return m_pDelegate->SendData(pData, nDataLen);
}

CString XVideoPreviewPane::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

int XVideoPreviewPane::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

XRTSPInfoDragWnd* XVideoPreviewPane::CreatePreviewDragWnd(XRTSPInfo* pInfo)
{
	return m_pDelegate->CreatePreviewDragWnd(pInfo);
}

void XVideoPreviewPane::DragInfo(CRect rc, XRTSPInfo* pInfo)
{
	return m_pDelegate->DragInfo(rc, pInfo);
}

BOOL XVideoPreviewPane::DragInfoToFrame(CPoint point,XDragInfo* pInfo)
{
	if (!IsWindowVisible())
		return FALSE;

	CRect rect;
	GetWindowRect(&rect);

	CRect rectTemp;

	for (VEC_VIDEOPREVIEWFRAME::iterator iter = m_VecFrame.begin(); iter != m_VecFrame.end(); iter++)
	{
		XVideoPreviewFrame* pTemp = *iter;

		CRect rectFrame = pTemp->GetVideoRect();

		if (!rectTemp.IntersectRect(&rect, rectFrame))
			continue;

		if (!rectTemp.PtInRect(point))
			continue;

		if (!m_pDelegate->IsLogin())
		{
			m_pDelegate->MessageBoxFromKey(_T("378"), _T("请先进行登陆操作！"), MB_OK);
			return TRUE;
		}
		//////////////////////////////////////////////////////////////////////////
		//删除原来信号地址
		int nOldIndex=pTemp->GetIndex();
		
		//判断预览框中有没有信号
		if(nOldIndex!=0)
		{	
			if(!JudgeOldIndexIsExist(nOldIndex))
			{
				//设置输入RTSP地址
				SetInputRTSPAddrByIndex(nOldIndex);

				//设置屏幕信号RTSP
				SetScreenSignalRTSPAddrByIndex(nOldIndex);

				//设置输入信号IP，用户名，密码
				SetInputParaByIndex(nOldIndex);	
			}
		}
		//////////////////////////////////////////////////////////////////////////
		CString szAnotherName=pInfo->GetAnotherName();

		int nInputIndex=pInfo->GetInputIndex();

		BOOL bIsUltra=FALSE; BOOL bIsHaveSignal=FALSE; BOOL bIsHavePane=FALSE;
		AdjustInputStatus(nInputIndex,bIsUltra,bIsHaveSignal,bIsHavePane);

		pTemp->SetAnotherName(szAnotherName);
		pTemp->SetIndex(nInputIndex);
		pTemp->SetIsUltra(bIsUltra);
		pTemp->SetIsHaveSignal(bIsHaveSignal);
		pTemp->SetIsHavePane(bIsHavePane);
		pTemp->SetSignalRTSPAddr();
		pTemp->SetPreviewFrame();
		pTemp->RunOrder();
		pTemp->UpdateText();
	}
	return FALSE;
}

BOOL XVideoPreviewPane::JudgeOldIndexIsExist(int nOldIndex)
{
	int nIndex=0;
	for (VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();iter++)
	{
		XVideoPreviewFrame* pTemp=*iter;
		if(pTemp->GetIndex()==nOldIndex)
			nIndex++;
	}

	if(nIndex>1)
		return TRUE;

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
void XVideoPreviewPane::InitViewPreviewDlg()
{
	m_ViewPreviewDlg = new CViewPreviewDlg;
	m_ViewPreviewDlg->SetPane(this);
	m_ViewPreviewDlg->Create(IDD_DLG_VIEWPREVIEW);

	m_pMultiVideoWindow=m_pDelegate->AddMultiVideoWindow(m_ViewPreviewDlg->GetSafeHwnd());
	m_ViewPreviewDlg->SetMultiVideoWindow(m_pMultiVideoWindow);
	m_ViewPreviewDlg->ShowWindow(SW_HIDE);
}

void XVideoPreviewPane::ShowViewPreviewDlg(CString szIP,CString szRTSPAddr,int nInputIndex,CString szUseName,CString szPassWd)
{	
	m_ViewPreviewDlg->SetIP(szIP);
	m_ViewPreviewDlg->SetRTSPAddr(szRTSPAddr);
	m_ViewPreviewDlg->SetInputIndex(nInputIndex);
	m_ViewPreviewDlg->SetUserName(szUseName);
	m_ViewPreviewDlg->SetPassWord(szPassWd);
	m_ViewPreviewDlg->Init();
	m_ViewPreviewDlg->ShowWindow(SW_SHOW);
}

void XVideoPreviewPane::CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd,VEC_CSTRING& VecRTSPAddr)
{
	CString szHead=_T("rtsp://");
	CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
	//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

	CString szSubRTSP=_T("");
	for(int i=0;i<4;i++)
	{
		szSubRTSP=szHead+szUseName+_T(":")+szPassWd+_T("@")+szIP+szChenal[i]+_T("/")+_T("sub");

		AddRTSPAddr(szSubRTSP);
		VecRTSPAddr.push_back(szSubRTSP);
	}
}

void XVideoPreviewPane::SetRectToFoure(RECTF rect,VEC_RECTF& VecRect)
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

CString XVideoPreviewPane::GetMainRTSPBySubRTSP(CString szRTSPAddr)
{
	if(szRTSPAddr==_T(""))
		return _T("");

	CString szMainRTSPAddr=_T("");

	int nCount=szRTSPAddr.GetLength();
	//CString s=szRTSPAddr.Left(nCount-3);

	int n=szRTSPAddr.Delete(nCount-3,3);
	szMainRTSPAddr=szRTSPAddr+_T("main");
	return szMainRTSPAddr;
}
//////////////////////////////////////////////////////////////////////////

void XVideoPreviewPane::AdjustInputStatus(int nIndex,BOOL& bIsUltra,BOOL& bIsHaveSignal,BOOL& bIsHavePane)
{
	bIsHavePane=m_pDelegate->IsHavePane(nIndex);
	bIsHaveSignal=m_pDelegate->IsHaveSignal(nIndex);

	m_pDelegate->IsUltra(nIndex);

	XInputSignal* pInput=m_pDelegate->GetInputByIndex(nIndex);
	if(pInput==NULL)
		return;

	bIsUltra=pInput->GetIsUltra();
}

void XVideoPreviewPane::AddRTSPAddr(CString szRTSP)
{
	int nCount=GetRTSPCountBySignal(szRTSP);
	int nTemp=nCount+1;
	m_pDelegate->AddRTSP(szRTSP,nTemp);
}

int XVideoPreviewPane::GetRTSPCountBySignal(CString szRTSP)
{
	return m_pDelegate->GetRTSPCountBySignal(szRTSP);
}

void XVideoPreviewPane::SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName)
{
	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pPreviewFrame=*iter;

		int nIndex=pPreviewFrame->GetIndex();
		if(nIndex==nInputIndex)
		{
			pPreviewFrame->SetAnotherName(szAnotherName);
			pPreviewFrame->UpdateText();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XVideoPreviewPane::SetInputRTSPAddrByIndex(int nIndex,CString szRTSP)
{
	m_pDelegate->SetInputRTSPAddrByIndex(nIndex,szRTSP);
}

void XVideoPreviewPane::SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP)
{
	m_pDelegate->SetScreenSignalRTSPAddrByIndex(nInputIndex,szRTSP);
}

//4k时设置输入IP,用户名 密码
void XVideoPreviewPane::SetInputParaByIndex(int nInputIndex,CString szIP,CString szUseName,CString szPassWd)
{
	m_pDelegate->SetInputParaByIndex(nInputIndex,szIP,szUseName,szPassWd);
}

void XVideoPreviewPane::SetFrameRTSPCountByIndex(int nInputIndex)
{
	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;

		CString szRTSPAddr=pFrame->GetRTSPAddr();
		if(nInputIndex==pFrame->GetIndex())
			m_pDelegate->SetRTSPAddrCount(szRTSPAddr,1);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CString XVideoPreviewPane::GetInputNameByIndex(int& nIndex)
{
	return m_pDelegate->GetInputNameByIndex(nIndex);
}

void XVideoPreviewPane::SpiltCString(CString szSrc,CString ch,VEC_CSTRING& VecStr)
{
	CString szTemp;

	int nPos=0;
	szTemp=szSrc.Tokenize(ch,nPos);

	while(!szTemp.IsEmpty())
	{
		VecStr.push_back(szTemp);
		szTemp=szSrc.Tokenize(ch,nPos);
	}
}

void XVideoPreviewPane::SetRTSPAddrCountPlus(CString szRTSPAddr)
{
	if(_T("")==szRTSPAddr)
		return;

	m_pDelegate->SetRTSPCountPlus(szRTSPAddr);
}

void XVideoPreviewPane::SetRTSPAddrCountLess(CString szRTSPAddr)
{
	if(_T("")==szRTSPAddr)
		return;

	m_pDelegate->SetRTSPCountLess(szRTSPAddr);
}

void XVideoPreviewPane::SetRTSPAddrCountReset(CString szRTSPAddr)
{
	if(_T("")==szRTSPAddr)
		return;

	m_pDelegate->AddRTSP(szRTSPAddr,0);

	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pPreviewFrame=*iter;

		CString szRTSP=pPreviewFrame->GetRTSPAddr();
		if(szRTSP==szRTSPAddr)
			m_pDelegate->AddRTSP(szRTSPAddr,1);
	}
}

void XVideoPreviewPane::DeleteRTSP(CString szRTSPAddr)
{
	if(_T("")==szRTSPAddr)
		return;

	m_pDelegate->DeleteRTSP(szRTSPAddr);
}

BOOL XVideoPreviewPane::CheckSumNum(char* pData,int nLen)
{
	char* data=new char[nLen];
	char* pTempData=pData;
	memcpy(data,pTempData,nLen);
	unsigned short nSum=CheckNum(data,nLen);
	delete []data;

	char* pTemp=pData;
	unsigned short nTempSum=0;
	memcpy(&nTempSum,pTemp+nLen,2);
	unsigned short nReSum=nTempSum&0xFF;
	if(nSum!=nReSum)
		return FALSE;
	else
		return TRUE;
}

unsigned short XVideoPreviewPane::CheckNum(char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
		nSum=nSum&0xFF;
	}

	return nSum;
}

void XVideoPreviewPane::AdjustMultiVideoWindowSize()
{
	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;
		pFrame->AdjustMultiVideoWindowSize();
	}
}

void XVideoPreviewPane::ResetRTSPInfo()
{
	CreateRTSPAddr();
	SetFrameParamater();
}

void XVideoPreviewPane::UpdateInputAnotherNameByPreview()
{
	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;

		int nIndex=pFrame->GetIndex();
		CString szANotherName=m_pDelegate->GetInputNameByIndex(nIndex);
		pFrame->SetAnotherName(szANotherName);
		pFrame->UpdateText();
	}
}

void XVideoPreviewPane::SetInputRTSPAddr()
{
	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;
		int nIndex=pFrame->GetIndex();

		if(nIndex!=0)
		{
			SetInputRTSPAddrByIndex(nIndex);
			SetInputParaByIndex(nIndex);
		}
	}
}

void XVideoPreviewPane::DeleteCurPaneRTSP()
{
	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;

		auto szRTSPAddr=pFrame->GetRTSPAddr();
		DeleteRTSP(szRTSPAddr);
	}
}

CString XVideoPreviewPane::GetRTSPAddrFromPreviewPane(int nSignalIndex)
{
	for(VEC_VIDEOPREVIEWFRAME::iterator iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XVideoPreviewFrame* pFrame=*iter;

		if(nSignalIndex==pFrame->GetIndex())
		{
			return pFrame->GetRTSPAddr();
		}
	}

	return _T("");
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void XVideoPreviewPane::Operate(OPERATETYPE type, void* pData)
{

}


