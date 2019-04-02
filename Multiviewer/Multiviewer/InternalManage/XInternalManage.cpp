#include "StdAfx.h"
#include "XInternalManage.h"
#include "XRibbonBarManage.h"
#include "XTranslationManage.h"
#include "XDelegateInternalManage.h"
#include "XMessageBoxDlg.h"
#include "XScreenManage.h"
#include "XInputSignalPane.h"
#include "XNetManage.h"
#include "XIniManage.h"
#include "HandlePath.h"
#include "XDragWnd.h"
#include "HandleIni.h"
#include "XDataManage.h"
#include "AboutDlg.h"
#include "XUDPWatchPane.h"
#include "XVideoPreviewPane.h"
#include "XUserManage.h"
#include "XPathManage.h"
#include "XNewViewDlg.h"
#include "XRTSPInfoDragWnd.h"
#include "XScenePane.h"
#include "..\ChildFrm.h"
#include "..\MultiviewerView.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrames.h"
#include "XSetPreviewBoard.h"
#include "XSetPreviewBoard.h"
#include "XSelectBoardInfo.h"
#include "XPreviewBoard.h"
#include "XDataInternalManage.h"
#include "XSendDataScreenManage.h"
#include "XSendDataOfPreviewBoard.h"
#include "XSceneInfo.h"
#include "XMyTabCtrl.h"
#include "XReNameTabCtrl.h"



XInternalManage::XInternalManage(void)
{
	m_pRibbonBarManage=nullptr;
	m_pTranslationManage=nullptr;
	m_pNowScreenManage=nullptr;
	m_pInputSignalPane=nullptr;
	m_pUDPWatchPane=nullptr;
	m_pNetManage=nullptr;
	m_pIniManage=nullptr;
	m_pChildManage=nullptr;
	m_pDataManage=nullptr;
	m_DragWnd=nullptr;
	m_PreviewDragWnd=nullptr;
	m_VideoPreviewPane=nullptr;
	m_pUserManage=nullptr;
	m_pMultiVideoWindow=nullptr;
	m_pDragInputMultiVideoWindow=nullptr;
	m_pDragPreviewMultiVideoWindow=nullptr;
	m_bIsFirstTime=FALSE;
	m_SetPreviewBoardDlg=nullptr;
	m_pTabbedBar=nullptr;
	m_pTemp=nullptr;
	m_pTabCtrl=nullptr;
	m_pViewTabCtrl=NULL;
}

XInternalManage::~XInternalManage(void)
{
	Clear();
	ClearVecBaseScreenManage();
	ClearTempBase();
	ClearVecPreviewPane();
	ClearVecPreviewPaneTemp();
	ClearMapSelectBoard();
	ClearPreviewTemp();
	ClearMapBottomTabLable();
}

void XInternalManage::Clear()
{
	m_VideoPlayer.ClearData();

	if(nullptr!=m_pPathManage)
	{
		delete m_pPathManage;
		m_pPathManage=nullptr;
	}

	if (nullptr != m_pRibbonBarManage)
	{
		delete m_pRibbonBarManage;
		m_pRibbonBarManage = nullptr;
	}

	if (nullptr != m_pTranslationManage)
	{
		delete m_pTranslationManage;
		m_pTranslationManage = nullptr;
	}

	if (nullptr != m_pNetManage)
	{
		delete m_pNetManage;
		m_pNetManage = nullptr;
	}

	if(nullptr != m_pInputSignalPane)
	{
		delete m_pInputSignalPane;
		m_pInputSignalPane = nullptr;
	}

	if (nullptr != m_pUDPWatchPane)
	{
		delete m_pUDPWatchPane;
		m_pUDPWatchPane = nullptr;
	}

	if (nullptr != m_pIniManage)
	{
		delete m_pIniManage;
		m_pIniManage = nullptr;
	}

	if (nullptr != m_pDataManage)
	{
		delete m_pDataManage;
		m_pDataManage = nullptr;
	}

	if (nullptr != m_DragWnd)
	{
		delete m_DragWnd;
		m_DragWnd = nullptr;
	}

	if (nullptr != m_PreviewDragWnd)
	{
		delete m_PreviewDragWnd;
		m_PreviewDragWnd = nullptr;
	}

	if (nullptr != m_pUserManage)
	{
		delete m_pUserManage;
		m_pUserManage = nullptr;
	}

	if(nullptr!=m_pScenePane)
	{
		delete m_pScenePane;
		m_pScenePane=nullptr;
	}
}

void XInternalManage::ClearMapBottomTabLable()
{
	m_MapBottomTabCtrLable.clear();
}

void XInternalManage::ClearVecBaseScreenManage()
{
	for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();++iter)
		delete *iter;
	m_VecBaseScreenManage.clear();
}

void XInternalManage::ClearTempBase()
{
	for(VEC_BASESCREENMANAGE::iterator iter=m_VecTemp.begin();iter!=m_VecTemp.end();++iter)
		delete *iter;
	m_VecTemp.clear();
}

void XInternalManage::ClearVecPreviewPane()
{
	for(VEC_VIDEOPREVIEWPANE::iterator iter=m_VecVideoPreviewPane.begin();iter!=m_VecVideoPreviewPane.end();++iter)
		delete *iter;
	m_VecVideoPreviewPane.clear();
}

void XInternalManage::ClearVecPreviewPaneTemp()
{
	for(VEC_VIDEOPREVIEWPANETEMP::iterator iter=m_VecVideoPreviewPaneTemp.begin();iter!=m_VecVideoPreviewPaneTemp.end();++iter)
		delete *iter;
	m_VecVideoPreviewPaneTemp.clear();
}

void XInternalManage::ClearPreviewTemp()
{
	m_MapPreviewTemp.clear();
}

void XInternalManage::Init()
{
	InitManage();
	InitAppData();
	SetShowScreenManage();
	UpdateControlDataShow(XDATATYPE_ALL);
}

void XInternalManage::SetShowScreenManage()
{
	int nSize=m_VecBaseScreenManage.size();
	m_pNowScreenManage=m_VecBaseScreenManage[nSize-1];
	m_pChildManage=m_pNowScreenManage;
}

void XInternalManage::SetNowScreenManage(XBaseScreenManage* p)
{
	m_pNowScreenManage=p;
}

void XInternalManage::AddDocument()
{
	for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();++iter)
	{
		XBaseScreenManage* pManage=*iter;		
		AddDocument(pManage);
	}

	SetShowScreenManage();
	UpdateControlDataShow(XDATATYPE_ALL);
}

void XInternalManage::AddDocument(XBaseScreenManage* pManage)
{
	CWinApp* pApp=AfxGetApp();  

	POSITION curTemplatePos = pApp->GetFirstDocTemplatePosition();  
	CDocTemplate* curTemplate=pApp->GetNextDocTemplate(curTemplatePos);  
	CDocument* pDoc=curTemplate->OpenDocumentFile(NULL,TRUE);  
	CString szStr=pManage->GetViewName();
	CString szName=GetTitle(szStr);
	pDoc->SetTitle(szName); 

	CMultiviewerView* pView=(CMultiviewerView*)GetDocumentFrontView(pDoc);
	pView->SetScreenManage(pManage);
	pView->Init();

	//=========================================
	//添加预览墙
	m_pMultiVideoWindow=m_VideoPlayer.AddMultiVideoWindow(pView->GetSafeHwnd(),186,193,202);
	m_pMultiVideoWindow->SetIsMainMultiVideo(TRUE);
	//******************************************
	int nScreenModel=pManage->GetScreenModel();
	m_pMultiVideoWindow->SetScreenModel(nScreenModel);

	float dwScale=pManage->GetMultiScale();
	m_pMultiVideoWindow->SetMultiScale(dwScale);

	int nFramesCountH=pManage->GetFramesCountH();
	m_pMultiVideoWindow->SetFramesCountH(nFramesCountH);

	int nFramesCountV=pManage->GetFramesCountV();
	m_pMultiVideoWindow->SetFramesCountV(nFramesCountV);

	int nFramesResulationH=pManage->GetFramesResulationH();
	m_pMultiVideoWindow->SetFramesResulationH(nFramesResulationH);

	int nFramesResulationV=pManage->GetFramesResulationV();
	m_pMultiVideoWindow->SetFramesResulationV(nFramesResulationV);

	int nFramesRightResulationH=pManage->GetFramesRightResulationH();
	m_pMultiVideoWindow->SetFramesRightResulationH(nFramesRightResulationH);

	int nFramesBottomResulationV=pManage->GetFramesBottomResulationV();
	m_pMultiVideoWindow->SetFramesBottomResulationV(nFramesBottomResulationV);
	//////////////////////////////////////////////////////////////////////////
	MAP_ROWINFO& MapRowInfo=pManage->GetMapRowInfo();
	m_pMultiVideoWindow->SetMapRowInfo(MapRowInfo);

	MAP_COLINFO& MapColInfo=pManage->GetMapColInfo();
	m_pMultiVideoWindow->SetMapColInfo(MapColInfo);

	//////////////////////////////////////////////////////////////////////////
	//******************************************
	AddFrames(pManage);
	pManage->SetMultiVideoWindow(m_pMultiVideoWindow);
	pManage->SetView(pView);
	//=========================================
	CChildFrame* pFrame=(CChildFrame*)pView->GetParentFrame();
	pFrame->setScreenManage(pManage);
	pFrame->setParentDelegate(this);

	//=========================================
	//获取顶部TabCtrl
	if(NULL==m_pViewTabCtrl)
	{
		m_pViewTabCtrl=(XMyTabCtrl*)pFrame->GetRelatedTabGroup();
	}
}

BOOL XInternalManage::SetViewTabBarDbClick(POINT point)
{
	CPoint pt(point);

	if(m_pViewTabCtrl==NULL)
		return FALSE;

	m_pViewTabCtrl->ScreenToClient(&pt);
	int nTab=m_pViewTabCtrl->GetTabFromPoint(pt);
	if(m_pViewTabCtrl->IsPtInTabArea(pt))
	{
		if(nTab!=-1)
		{
			//双击标签
			if(NULL!=m_pNowScreenManage)
				m_pNowScreenManage->SetScreenByDbClick();
		}
		else
		{
			//双击非标签处
			CWnd* pTargeWnd=m_pViewTabCtrl->FindTargetWnd(pt);
			if(NULL==pTargeWnd)
				OperateOfNewView();
			else 
				return FALSE;	
		}
	}
	else
		return FALSE;

	return TRUE;
}

void XInternalManage::AddFrames(XBaseScreenManage* pManage)
{
	VEC_SCREEN& VecScreen=pManage->GetVecScreen1();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(
			                           pScreen->GetIndex(),
									   pScreen->GetBoardIndex(),
									   pScreen->GetRect(),
									   pScreen->GetNumOfTwoScreen(),
									   pScreen->GetIsTwoSignal());

		CString szText=pManage->SetText(pScreen);
		m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
	}
}

CView* XInternalManage::GetDocumentFrontView(CDocument* p)
{
	POSITION pos;
	CView* pView=NULL; 
	pos=p->GetFirstViewPosition();
	pView=p->GetNextView(pos);
	return pView;
}

void XInternalManage::InitManage()
{
	m_pPathManage = new XPathManage;
	m_pPathManage->Init();

	m_VideoPlayer.InitFFMPEG();
	m_VideoPlayer.Init();

	m_pTranslationManage = new XTranslationManage;
	m_pTranslationManage->SetDelegate(this);
	m_pTranslationManage->Init();
	
	m_pIniManage = new XIniManage;
	m_pIniManage->SetDelegate(this);
	m_pIniManage->Init();

	m_pUserManage = new XUserManage;
	m_pUserManage->SetDelegate(this);
	m_pUserManage->Init();

	m_pDataManage = new XDataManage;
	m_pDataManage->SetDelegate(this);
	m_pDataManage->Init();

	m_pNetManage = new XNetManage;
	m_pNetManage->SetDelegate(this);
	m_pNetManage->Init();

	m_pRibbonBarManage = new XRibbonBarManage;
	m_pRibbonBarManage->SetDelegate(this);
	m_pRibbonBarManage->Init();

	m_pInputSignalPane = new XInputSignalPane;
	m_pInputSignalPane->SetDelegate(this);

	m_pScenePane=new XScenePane;
	m_pScenePane->SetDelegate(this);
	m_pScenePane->SetInputSignalPane(m_pInputSignalPane);

	m_pUDPWatchPane = new XUDPWatchPane;
	m_pUDPWatchPane->SetDelegate(this);
}

void XInternalManage::InitAppData()
{
	BOOL bResult=FALSE;

	try
	{
		bResult=GetAppData();
		m_bIsFirstTime=bResult;
	}
	catch(CException* e) 
	{
		e->Delete();
	}

	if(!bResult)
		ResetAppData();
}

void XInternalManage::SetIsFirstTime(BOOL IsFirstTime)
{
	m_bIsFirstTime=IsFirstTime;
}

BOOL XInternalManage::GetIsFirstTime()
{
	return m_bIsFirstTime;
}

void XInternalManage::OperateOfNewView()
{
	XNewViewDlg dlg;

	dlg.SetDelegate(this);
	dlg.SetBaseManage(this);
	if(IDOK==dlg.DoModal())
	{
		CString szName=dlg.GetViewName();
		int nIndex=dlg.GetBeginIndex();
		int nScreenModel=dlg.GetScreenModel();

		XScreenManage* pScreenManage=new XScreenManage;
		pScreenManage->SetDelegate(this);
		pScreenManage->SetViewName(szName);
		pScreenManage->SetBeginIndex(nIndex);
		pScreenManage->SetScreenModel(nScreenModel);
		pScreenManage->ResetData();
		m_VecBaseScreenManage.push_back(pScreenManage);

		AddDocument(pScreenManage);
		SetShowScreenManage();
		pScreenManage->OnBtnNewScene();
	}

	UpdateControlDataShow(XDATATYPE_ALL);
}

XMenuScreenSetInfo* XInternalManage::GetMenuScreenSetInfo()
{
	return m_pNowScreenManage->GetMenuScreenSetInfo();
}

XUserManage* XInternalManage::GetUserManage()
{
	return m_pUserManage;
}

void XInternalManage::CloseMDI(XBaseScreenManage* pManage)
{
	for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();iter++)
	{
		XBaseScreenManage* pBase=*iter;

		if(pBase==pManage)
		{
			//暂时没用到
			//m_VecTemp.push_back(pBase);

			delete pBase;
			m_VecBaseScreenManage.erase(iter);
			break;
		}
	}

	SetShowScreenManage();	
}

BOOL XInternalManage::GetAppData()
{
	CFile mFile;

	CString szDataPath = HandlePath::GetDataFilePath(APP_DATAFILENAME);

	if(mFile.Open(szDataPath, CFile::modeRead))
	{
		CArchive arch(&mFile, CArchive::load);

		GetAppData(arch);
		arch.Close();
		mFile.Close();
		return TRUE;
	}
	else
		return FALSE;
}

void XInternalManage::GetAppData(CArchive& arch)
{
	XDataInternalManage::GetData(this,arch);
	m_pUserManage->GetData(arch);
	m_pInputSignalPane->GetData(arch);
	m_pScenePane->GetData(arch);
}

void XInternalManage::ResetAppData()
{
	XScreenManage* pScreenManage=new XScreenManage;

	pScreenManage->SetDelegate(this);
	CString szStr=_T("拼接屏(VWS)");
	CString szName=GetTitle(szStr);
	pScreenManage->SetViewName(szName);
	pScreenManage->ResetData();
	m_VecBaseScreenManage.push_back(pScreenManage);
	m_pUserManage->ResetData();
	m_pInputSignalPane->ResetData();
}

CString XInternalManage::GetTitle(CString szStr)
{
	CString szTitle=szStr;
	int nLen=szStr.GetLength();

	if(nLen<25)
	{
		int n=25-nLen;
		for(int i=0;i<n;i++)
			szTitle+=_T(" ");
	}
	return szTitle;
}

void XInternalManage::InitPane()
{
	m_pInputSignalPane->Init();
	m_pScenePane->Init();
	m_pUDPWatchPane->Init();
	InitPreviewPane();
}

BOOL XInternalManage::AppClose()
{
	BOOL bResult=FALSE;
	if(SaveAppData())
		bResult=TRUE;
	else
	{
		if(IDYES==MessageBoxFromKey(_T("224"), _T("保存程序数据失败，请确认是否继续退出程序？"), MB_YESNO))
			bResult=TRUE;
	}
	return bResult;
}

CString XInternalManage::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pTranslationManage->GetTranslationString(szKey, szDefault);
}

BOOL XInternalManage::SaveAppData()
{
	CFile mFile;
	CString szDataPath = HandlePath::GetDataFilePath(APP_DATAFILENAME);
	if (mFile.Open(szDataPath, CFile::modeCreate|CFile::modeWrite))
	{
		CArchive arch(&mFile, CArchive::store);
		SaveAppData(arch);
		arch.Close();
		mFile.Close();
		return TRUE;
	}
	else
		return FALSE;
}

void XInternalManage::SaveAppData(CArchive& arch)
{
	XDataInternalManage::SaveData(this,arch);
	m_pUserManage->SaveData(arch);
	m_pInputSignalPane->SaveData(arch);
	m_pScenePane->SaveData(arch);
}

int XInternalManage::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return MessageBox(GetTranslationString(szKey, szDefault), GetTranslationString(_T("239"), _T("提示")), uType);
}

CString XInternalManage::GetSceneFilePath(int nSceneIndex, CString szSceneName)
{
	return m_pPathManage->GetSceneFilePath(nSceneIndex, szSceneName);
}

CString XInternalManage::GetAllSceneFilePath(int nSceneIndex, CString szSceneName,int nIndex)
{
	return m_pPathManage->GetAllSceneFilePath(nSceneIndex, szSceneName,nIndex);
}

CString XInternalManage::GetSceneFolderPath()
{
	return m_pPathManage->GetSceneFolderPath();
}

int XInternalManage::MessageBox(CString szText, CString szCaption, UINT uType)
{
	XMessageBoxDlg dlg(szText, szCaption, uType);
	dlg.SetDelegate(this);
	return dlg.DoModal();
}

void XInternalManage::ControlDataChange(XDATATYPE type)
{
	m_pRibbonBarManage->ControlDataChange(type);
}

void XInternalManage::ReloadInterface()
{
	m_pRibbonBarManage->ReloadInterface();
	m_pInputSignalPane->ReloadInterface();
	m_pScenePane->ReloadInterface();
	m_pUDPWatchPane->ReloadInterface();
	PreviewPaneReloadInterface();
	ScreenReloadInterface();
}

void XInternalManage::ScreenReloadInterface()
{
	for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();++iter)
	{
		XBaseScreenManage* pManage=*iter;
		pManage->ReLoadInterface();
	}
}

void XInternalManage::ResetViewSize()
{
	m_pNowScreenManage->ResetViewSize();
}

void XInternalManage::InvalidateView()
{
	m_pNowScreenManage->InvalidateView();
}

CWnd* XInternalManage::GetCWND()
{
	return m_pDelegate->GetCWND();
}

void XInternalManage::RibbonBarShowCategory(CString szName)
{
	XBaseChildManage* pChildManage=GetChildManage(szName);

	if (m_pChildManage!=pChildManage)
	{
		if (NULL!=m_pChildManage)
			m_pChildManage->ShowManage(SHOWTYPE_HIDE);

		if (NULL!=pChildManage)
			pChildManage->ShowManage(SHOWTYPE_SHOW);

		m_pChildManage=pChildManage;	
		ResetViewSize();
		InvalidateView();
	}
}

XBaseChildManage* XInternalManage::GetChildManage(CString szName)
{
	CString szCategoryMain=GetTranslationString(_T("201"),_T("主页"));
	XBaseChildManage* pChildManage=NULL;
	if(szName==szCategoryMain)
		pChildManage=m_pNowScreenManage;

	return pChildManage;
}

HWND XInternalManage::GetHWND()
{
	return m_pDelegate->GetHWND();
}

void XInternalManage::UpdateControlDataShow(XDATATYPE type)
{
	m_pRibbonBarManage->UpdateControlDataShow(type);
}

void XInternalManage::ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
	int noffsetY)
{
	m_pChildManage->ViewDraw(pDC, rect, noffsetX, noffsetY);
}

CSize XInternalManage::ViewGetSize()
{
	return m_pChildManage->ViewGetSize();
}

void XInternalManage::ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	m_pChildManage->ViewLButtonDown(nFlags, point, rect, noffsetX, noffsetY);
}

void XInternalManage::ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	m_pChildManage->ViewLButtonUp(nFlags, point, rect, noffsetX, noffsetY);
}

void XInternalManage::ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	m_pChildManage->ViewMouseMove(nFlags, point, rect, noffsetX, noffsetY);
}

void XInternalManage::ViewMouseLeave()
{
	m_pChildManage->ViewMouseLeave();
}

void XInternalManage::ViewKeyUp(UINT nChar)
{
	m_pChildManage->ViewKeyUp(nChar);
}

void XInternalManage::ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
	CRect& rect, int noffsetX, int noffsetY)
{
	m_pChildManage->ViewRButtonUp(pWnd, nFlags, point, rect, noffsetX, noffsetY);
}

void XInternalManage::ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	m_pChildManage->ViewLBDClick(nFlags, point, rect, noffsetX, noffsetY);
}

BOOL XInternalManage::SendData(char* pData, int nDataLen)
{
	BOOL bResult = FALSE;

	if ((nullptr != pData) && (nDataLen > 0))
		bResult = m_pNetManage->SendData(GetDeviceIP(), GetDevicePort(), pData, nDataLen);

	return bResult;
}

XDragWnd* XInternalManage::CreateDragWnd(XDragInfo* pInfo)
{
	if(m_DragWnd==NULL)
	{
		CreateDragWnd();
		m_pDragInputMultiVideoWindow=m_VideoPlayer.AddMultiVideoWindow(m_DragWnd->GetSafeHwnd());
	}

	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	int nDragWidth=HandleIni::GetInt(_T("Info"),_T("PreviewDragWidth"),160,szIniPath);
	int nDragHeight=HandleIni::GetInt(_T("Info"),_T("PreviewDragHeight"),90,szIniPath);
	float fScale=GetScale();

	if(fScale<=1)
	{
		CRect rect(CPoint(0,0), CSize(nDragWidth*fScale,nDragHeight*fScale));
		m_DragWnd->MoveWindow(rect);
	}
	else
	{
		CRect rect(CPoint(0,0), CSize(nDragWidth,nDragHeight));
		m_DragWnd->MoveWindow(rect);
	}

	pInfo->SetMultiVideoWindow(m_pDragInputMultiVideoWindow);	
	m_DragWnd->Show(pInfo);
	return m_DragWnd;
}

void XInternalManage::CreateDragWnd() 
{ 
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	int nDragWidth=HandleIni::GetInt(_T("Info"),_T("PreviewDragWidth"),160,szIniPath);
	int nDragHeight=HandleIni::GetInt(_T("Info"),_T("PreviewDragHeight"),90,szIniPath);

	CRect rect(CPoint(0, 0), CSize(nDragWidth, nDragHeight));

	m_DragWnd = new XDragWnd;
	m_DragWnd->Create(WS_CHILD|WS_VISIBLE, rect, m_pDelegate->GetCWND()->GetDesktopWindow(), 0);
	m_DragWnd->SetInputSignalPan(m_pInputSignalPane);
	m_DragWnd->ShowWindow(SW_HIDE);
	m_DragWnd->UpdateWindow();
}

void XInternalManage::DragInfo(CRect rc,CPoint point,XDragInfo* pInfo)
{
	if(m_pNowScreenManage!=NULL)
	{
		if(m_pNowScreenManage->DragInfo(rc,point,pInfo))
			return;
	}

	if(m_VideoPreviewPane!=NULL)
	{
		if(m_VideoPreviewPane->DragInfoToFrame(point,pInfo))
			return;
	}
}

XRTSPInfoDragWnd* XInternalManage::CreatePreviewDragWnd(XRTSPInfo* pInfo)
{
	if (NULL==m_PreviewDragWnd)
	{
		CreatePreviewDragWnd();
		m_pDragPreviewMultiVideoWindow=m_VideoPlayer.AddMultiVideoWindow(m_PreviewDragWnd->GetSafeHwnd());
	}

	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	int nDragWidth=HandleIni::GetInt(_T("Info"),_T("PreviewDragWidth"),160,szIniPath);
	int nDragHeight=HandleIni::GetInt(_T("Info"),_T("PreviewDragHeight"),90,szIniPath);
	float fScale=GetScale();


	if(fScale<=1)
	{
		CRect rect(CPoint(0, 0), CSize(nDragWidth*fScale, nDragHeight*fScale));
		m_PreviewDragWnd->MoveWindow(rect);
	}
	else
	{
		CRect rect(CPoint(0, 0), CSize(nDragWidth, nDragHeight));
		m_PreviewDragWnd->MoveWindow(rect);
	}

	pInfo->SetMultiVideoWindow(m_pDragPreviewMultiVideoWindow);
	m_PreviewDragWnd->Show(pInfo);
	return m_PreviewDragWnd;
}

void XInternalManage::CreatePreviewDragWnd()
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	int nPreviewDragWidth=HandleIni::GetInt(_T("Info"),_T("PreviewDragWidth"),160,szIniPath);
	int nPreviewDragHeight=HandleIni::GetInt(_T("Info"),_T("PreviewDragHeight"),90,szIniPath);

	CRect rect(CPoint(0,0),CSize(nPreviewDragWidth,nPreviewDragHeight));

	m_PreviewDragWnd=new XRTSPInfoDragWnd;
	m_PreviewDragWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pDelegate->GetCWND()->GetDesktopWindow(),0);
	m_PreviewDragWnd->SetVideoPreviewPan(m_VideoPreviewPane);
	m_PreviewDragWnd->ShowWindow(SW_HIDE);
	m_PreviewDragWnd->UpdateWindow();
}

void XInternalManage::DragInfo(CRect rc,XRTSPInfo* pInfo)
{
	if(m_pNowScreenManage->DragInfo(rc, pInfo))
		return;
}

CView* XInternalManage::GetView()
{
	return m_pDelegate->GetView();
}

float XInternalManage::GetScale()
{
	return m_pNowScreenManage->GetMultiScale();
}

void XInternalManage::SetScale(float f)
{
	//m_pIniManage->SetScale(f);
}

CString XInternalManage::GetDeviceIP()
{
	return m_pIniManage->GetDeviceIP();
}

int XInternalManage::GetDevicePort()
{
	return m_pIniManage->GetDevicePort();
}

void XInternalManage::SetDeviceIP(CString str)
{
	m_pIniManage->SetDeviceIP(str);
}

void XInternalManage::SetDevicePort(int n)
{
	m_pIniManage->SetDevicePort(n);
}

CString XInternalManage::GetLanguagetype()
{
	return m_pTranslationManage->GetLanguagetype();
}

void XInternalManage::SetLanguagetype(CString type)
{
	m_pTranslationManage->SetLanguagetype(type);
}

void XInternalManage::HandleUDPMsg(WPARAM wParam, LPARAM lParam)
{
	m_pNetManage->HandleUDPMsg(wParam, lParam);
}

void XInternalManage::HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr)
{
	m_pUDPWatchPane->AddUDPInfo(pData, nDataLen);

	if (m_pDataManage->HandleUDPData(pData, nDataLen, addr))
		return;
}

void XInternalManage::ShowAboutDlg()
{
	CAboutDlg dlg;

	dlg.SetDelegate(this);
	dlg.DoModal();
}

BOOL XInternalManage::GetNetState()
{
	return m_pNetManage->GetState();
}

void XInternalManage::AddRTSP(CString szRTSPAddr)
{
	//m_VideoPlayer.AddRTSP(szRTSPAddr);
}

void XInternalManage::AddRTSP(CString szRTSPAddr,int nCount)
{
	m_VideoPlayer.AddRTSP(szRTSPAddr,nCount);
}

void XInternalManage::SetRTSPCountPlus(CString szRTSPAddr)
{
	m_VideoPlayer.SetRTSPCountPlus(szRTSPAddr);
}

void XInternalManage::SetRTSPCountLess(CString szRTSPAddr)
{
	m_VideoPlayer.SetRTSPCountLess(szRTSPAddr);
}

void XInternalManage::AddRTSPHWND(HWND h)
{
	m_VideoPlayer.AddRTSPHWND(h);
}

XMultiVideoWindow* XInternalManage::AddMultiVideoWindow(HWND h)
{
	return m_VideoPlayer.AddMultiVideoWindow(h);
}

void XInternalManage::SetRTSPHWNDRTSPAddr(HWND h, CString szRSTPAddr)
{
	m_VideoPlayer.SetRTSPHWNDRTSPAddr(h, szRSTPAddr);
}

void XInternalManage::DeleteRTSP(CString szRTSPAddr)
{
	m_VideoPlayer.DeleteRTSP(szRTSPAddr);
}

int XInternalManage::GetOutputCount()
{
	return m_pNowScreenManage->GetOutputCount();
}

int XInternalManage::GetInputCount()
{
	return m_pInputSignalPane->GetInputCount();
}

void XInternalManage::SetInputCount(int n)
{
	m_pInputSignalPane->SetInputCount(n);
}

BOOL XInternalManage::IsLogin()
{
	return m_pUserManage->IsLogin();
}

BOOL XInternalManage::GetUserNodePower(int nInputIndex, int nOutputIndex)
{
	return m_pUserManage->GetUserNodePower(nInputIndex, nOutputIndex);
}

BOOL XInternalManage::IsAdminUser()
{
	return m_pUserManage->IsAdminUser();
}

void XInternalManage::ReSetInputData()
{
	m_pInputSignalPane->ResetDataOfScene();
}

VEC_INPUTSIGNAL& XInternalManage::GetVecInputSignal()
{
	return m_pInputSignalPane->GetVecInputSignal();
}

VEC_SCREEN& XInternalManage::GetVecScreen()
{
	return m_pNowScreenManage->GetVecScreen1();
}

CString XInternalManage::GetInputNameByIndex(int nIndex)
{
	return m_pInputSignalPane->GetInputNameByIndex(nIndex);
}

XInputSignal* XInternalManage::GetInputByIndex(int nIndex)
{
	return m_pInputSignalPane->GetInputByIndex(nIndex);
}

void XInternalManage::SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName)
{
	if(m_VideoPreviewPane!=NULL)
		m_VideoPreviewPane->SetPreviewNameByAnotherName(nInputIndex,szAnotherName);
}

void XInternalManage::AdjustRTSPHWNDSize(HWND h, int nWidth, int nHeight)
{
	m_VideoPlayer.AdjustRTSPHWNDSize(h, nWidth, nHeight);
}

VEC_BASESCREENMANAGE& XInternalManage::GetBaseManage()
{
	return m_VecBaseScreenManage;
}

VEC_BASESCREENMANAGE& XInternalManage::GetVecBaseScreenManage()
{
	return m_VecBaseScreenManage;
}

VEC_VIDEOPREVIEWPANE& XInternalManage::GetVecPreviewPane()
{
	return m_VecVideoPreviewPane;
}

MAP_SELECTBOARD& XInternalManage::GetMapSelectBoard()
{
	return m_MapSelectBoard;
}

MAP_PREVIEWTEMP& XInternalManage::GetMapPreviewTemp()
{
	return m_MapPreviewTemp;
}

MAP_BOARDTYPE& XInternalManage::GetMapBoardType()
{
	return m_pNowScreenManage->GetMapBoardType();
}

MAP_TABLABLE& XInternalManage::GetMapBottomTabLable()
{
	return m_MapBottomTabCtrLable;
}

void XInternalManage::SetOSD(XInputSignal* pInputSignal)
{
	m_pInputSignalPane->SetOSD(pInputSignal);
}

void XInternalManage::ResetDataBySceneInputCountChange()
{
	m_pInputSignalPane->ResetDataBySceneInputCountChange();
}

void XInternalManage::IsUltra(int nIndex)
{
	m_pInputSignalPane->IsUltra(nIndex);
}

void XInternalManage::ShowMenu(CPoint& point)
{
	m_pNowScreenManage->ShowMenu(point);
}

void XInternalManage::AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth,int nHight)
{
	m_VideoPlayer.AdjustMultiVideoWindowHWNDSize(p,nWidth,nHight);
}

void XInternalManage::JudgetInputIsultra(int nInputIndex)
{
	m_pInputSignalPane->IsUltra(nInputIndex);
}

void XInternalManage::SetRTSPAddrCountPlus(CString szRTSPAddr)
{
	if(m_VideoPreviewPane==NULL)
		return;

	m_VideoPreviewPane->SetRTSPAddrCountPlus(szRTSPAddr);
}

void XInternalManage::SetRTSPAddrCountLess(CString szRTSPAddr)
{
	if(m_VideoPreviewPane==NULL)
		return;

	m_VideoPreviewPane->SetRTSPAddrCountLess(szRTSPAddr);
}

void XInternalManage::SetRTSPAddrCountReset(CString szRTSPAddr)
{
	if(m_VideoPreviewPane==NULL)
		return;

	m_VideoPreviewPane->SetRTSPAddrCountReset(szRTSPAddr);
}

void XInternalManage::SetRTSPAddrCount(CString szRTSPAddr,int nCount)
{
	m_VideoPlayer.SetRTSPAddrCount(szRTSPAddr,nCount);
}

int XInternalManage::GetRTSPCountBySignal(CString szRTSP)
{
	return m_pNowScreenManage->GetRTSPCountBySignal(szRTSP);
}

void XInternalManage::SetInputRTSPAddrByIndex(int nIndex,CString szRTSP)
{
	m_pInputSignalPane->SetInputRTSPAddrByIndex(nIndex,szRTSP);
}

void XInternalManage::SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP)
{
	m_pNowScreenManage->SetScreenSignalRTSPAddrByIndex(nInputIndex,szRTSP);
}

void XInternalManage::SetInputParaByIndex(int nIndex,CString szIP,CString szUseName,CString szPassWd)
{
	m_pInputSignalPane->SetInputParaByIndex(nIndex,szIP,szUseName,szPassWd);
}

BOOL XInternalManage::IsHaveSignal(int nIndex)
{
	return m_pInputSignalPane->IsHaveSignal(nIndex);
}

BOOL XInternalManage::IsHavePane(int nIndex)
{
	return m_pInputSignalPane->IsHavePan(nIndex);
}

void XInternalManage::SetMultiScale(float f)
{
	m_pNowScreenManage->SetMultiScale(f);
}

void XInternalManage::OpenScene(CString szSceneName,int nSceneIndex,CString szViewName)
{
	m_pNowScreenManage->OpenScene(szSceneName,nSceneIndex,szViewName);
}

void XInternalManage::DeleteScene(int nSceneIndex)
{
	m_pNowScreenManage->DeleteScene(nSceneIndex);
}

HTREEITEM XInternalManage::AddSceneToTree(int nSceneIndex,CString szSceneName,int nType,CString szSceneGroup)
{
	return m_pScenePane->AddSceneToTree(nSceneIndex,szSceneName,nType,szSceneGroup);
}

void XInternalManage::AddViewNameToScene(HTREEITEM item,CString szSceneName,int nIndex,CString szViewName)
{
	m_pScenePane->AddViewNameToScene(item,szSceneName,nIndex,szViewName);
}

void XInternalManage::ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)
{
	m_pNowScreenManage->ChangeMultiVideoWindowsAnotherName(nInputIndex,szAnotherName);
}

void XInternalManage::OperateOfSetPreviewBoard()
{
	XSetPreviewBoard dlg;
	dlg.SetDelegate(this);
	dlg.SetBaseManage(this);

	m_SetPreviewBoardDlg=&dlg;

	dlg.DoModal();
	m_SetPreviewBoardDlg=NULL;
}

void XInternalManage::OperateOfSplitNetSet()
{
	//Split网络
	if(m_SetPreviewBoardDlg!=NULL)
		m_SetPreviewBoardDlg->OnSplitNetSet();
}

void XInternalManage::OpersteOdSplitBitRate()
{
	//Split码率
	if(m_SetPreviewBoardDlg!=NULL)
		m_SetPreviewBoardDlg->OnSplitBiteRate();
}

XBoardNetInfo* XInternalManage::GetBoardInfo()
{
	return &m_BoardInfo;
}

void XInternalManage::OperateOfReadPreviewNet(char *pData)
{
	if(m_SetPreviewBoardDlg!=NULL)
		m_SetPreviewBoardDlg->OperateOfReadPreviewNet(pData);
}

void XInternalManage::OperateOfReadPreviewBitRate(char* pData)
{
	if(m_SetPreviewBoardDlg!=NULL)
		m_SetPreviewBoardDlg->OperateOfReadPreviewBitRate(pData);
}

void XInternalManage::ClearMapSelectBoard()
{
	for(MAP_SELECTBOARD::iterator iter=m_MapSelectBoard.begin();iter!=m_MapSelectBoard.end();++iter)
		delete iter->second;

	m_MapSelectBoard.clear();
}

//全部接受，然后保存，再次打开  读取数据
void XInternalManage::CopySelectedBoardInfo(VEC_PREVIEWBOARD& VecBoard)
{
	for(VEC_PREVIEWBOARD::iterator iter=VecBoard.begin();iter!=VecBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;
		int nBoardIndex=pBoard->GetBoardIndex();
		XSelectBoardInfo* pInfo=NULL;

		MAP_SELECTBOARD::iterator iterMap=m_MapSelectBoard.find(nBoardIndex);
		if(iterMap==m_MapSelectBoard.end())
		{
			pInfo=new XSelectBoardInfo;
			pInfo->SetSelected(pBoard->GetSelected());
			pInfo->SetIndex(pBoard->GetIndex());
			pInfo->SetBoardIndex(pBoard->GetBoardIndex());
			pInfo->SetSecretSel(pBoard->GetSecretSel());
			pInfo->SetUserName(pBoard->GetUseName());
			pInfo->SetPassWd(pBoard->GetPassWd());
			pInfo->SetModelSel(pBoard->GetModelSel());
			pInfo->SetIP(pBoard->GetIP());
			pInfo->SetMask(pBoard->GetMask());
			pInfo->SetGateWay(pBoard->GetGateWay());
			pInfo->SetMAC(pBoard->GetMAC());
			m_MapSelectBoard.insert(std::pair<int,XSelectBoardInfo*>(nBoardIndex,pInfo));
		}
		else
		{
			pInfo=iterMap->second;
			pInfo->SetSelected(pBoard->GetSelected());
			pInfo->SetIndex(pBoard->GetIndex());
			pInfo->SetBoardIndex(pBoard->GetBoardIndex());
			pInfo->SetSecretSel(pBoard->GetSecretSel());
			pInfo->SetUserName(pBoard->GetUseName());
			pInfo->SetPassWd(pBoard->GetPassWd());
			pInfo->SetModelSel(pBoard->GetModelSel());
			pInfo->SetIP(pBoard->GetIP());
			pInfo->SetMask(pBoard->GetMask());
			pInfo->SetGateWay(pBoard->GetGateWay());
			pInfo->SetMAC(pBoard->GetMAC());
		}
	}
}

void XInternalManage::SetPreviewPane()
{
	for(MAP_SELECTBOARD::iterator iter=m_MapSelectBoard.begin();iter!=m_MapSelectBoard.end();++iter)
	{
		XSelectBoardInfo* pInfo=iter->second;
		int nBoardIndex=pInfo->GetBoardIndex();
		if(pInfo->GetSelected())
		{
			MAP_PREVIEWTEMP::iterator iterTemp=m_MapPreviewTemp.find(nBoardIndex);
			if(iterTemp==m_MapPreviewTemp.end())
			{
				XVideoPreviewPane* pPane=new XVideoPreviewPane;
				pPane->SetDelegate(this);
				pPane->ResetData();
				pPane->SetBoardIndex(pInfo->GetBoardIndex());
				pPane->SetUserName(pInfo->GetUserName());
				pPane->SetPassWd(pInfo->GetPassWd());
				pPane->SetIP(pInfo->GetszIP());
				pPane->Init();
				AddPreviewPane(pPane);
				m_VecVideoPreviewPane.push_back(pPane);
				m_MapPreviewTemp.insert(std::pair<int,int>(nBoardIndex,nBoardIndex));
			}
			else
			{
				for(VEC_VIDEOPREVIEWPANE::iterator iter=m_VecVideoPreviewPane.begin();iter!=m_VecVideoPreviewPane.end();++iter)
				{
					XVideoPreviewPane* pPane=*iter;
					if(nBoardIndex==pPane->GetBoardIndex())
					{
						pPane->SetBoardIndex(pInfo->GetBoardIndex());
						pPane->SetUserName(pInfo->GetUserName());
						pPane->SetPassWd(pInfo->GetPassWd());
						pPane->SetIP(pInfo->GetszIP());
						pPane->ResetRTSPInfo();
					}
				}
			}
		}
	}

	SetBaseTabCtr();
	SetActiveDockPane();
}

void XInternalManage::InitPreviewPane()
{
	for(VEC_VIDEOPREVIEWPANE::iterator iter=m_VecVideoPreviewPane.begin();iter!=m_VecVideoPreviewPane.end();++iter)
	{
		XVideoPreviewPane* pPane=*iter;
		pPane->SetDelegate(this);
		pPane->Init();
		AddPreviewPane(pPane);
	}

	SetBaseTabCtr();
	SetActiveDockPane();
}

void XInternalManage::AddPreviewPane(XVideoPreviewPane* pPane)
{
	if(m_pTemp!=NULL)
		pPane->AttachToTabWnd(m_pTemp,DM_SHOW,TRUE,(CDockablePane**)&m_pTabbedBar);

	pPane->ShowPane(TRUE,FALSE,TRUE);
	m_pTemp=pPane;
	m_VideoPreviewPane=m_pTemp;
}

void XInternalManage::SetBaseTabCtr()
{
	if(m_pTabbedBar!=NULL)
	{
		m_pTabCtrl=(XMyTabCtrl*)m_pTabbedBar->GetTabWnd();
		m_pTabCtrl->ModifyTabStyle(CMFCTabCtrl::STYLE_3D_SCROLLED);
		m_pTabCtrl->EnableAutoColor(TRUE);
		m_pTabCtrl->EnableTabSwap(FALSE);
	}
}

BOOL XInternalManage::SetTabCtrlDbCLick(POINT point)
{
	//同时处理顶部与底部双击
	CPoint pt(point);

	if(NULL==m_pTabCtrl)
		return FALSE;

	m_pTabCtrl->ScreenToClient(&pt);
	int nTab=m_pTabCtrl->GetTabFromPoint(pt);
	if(m_pTabCtrl->IsPtInTabArea(pt))
	{
		if(nTab!=-1)
		{
			CString szTabLable;
			m_pTabCtrl->GetTabLabel(nTab,szTabLable);

			CString szName,szAnotherName;
			GetAnotherNameByTabLable(szTabLable,szName,szAnotherName);

			XReNameTabCtrl dlg;
			dlg.SetManage(this);

			CString szTitle=_T("");
			if(szAnotherName==_T(""))
				szTitle=GetTranslationString(_T("494"),_T("添加备注"));
			else
				szTitle=GetTranslationString(_T("662"),_T("修改备注"));

			dlg.SetTitle(szTitle);
			dlg.SetOldName(szAnotherName);

			if(IDOK==dlg.DoModal())
			{
				CString szTempName=dlg.GetNewName();

				CString szTabLable=_T("");
				if(szTempName==_T(""))
					szTabLable.Format(_T("%s"),szName);
				else
					szTabLable.Format(_T("%s(%s)"),szName,szTempName);

				CString szTempLable=GetLabelByTab(szTabLable);
				m_pTabCtrl->SetTabLabel(nTab,szTempLable);

				MAP_TABLABLE::iterator iter=m_MapBottomTabCtrLable.find(szName);
				if(iter!=m_MapBottomTabCtrLable.end())
					iter->second=szTempName;
				else
					m_MapBottomTabCtrLable.insert(std::pair<CString,CString>(szName,szTempName));
			}
		}
		else
		{
			CWnd* pTargeWnd=m_pTabCtrl->FindTargetWnd(pt);
			//如果为空，双击为上面的TabBar
			if(pTargeWnd==NULL)	
				return FALSE;
		}
	}
	else
		return FALSE;

	return TRUE;
}

CString XInternalManage::GetLabelByTab(CString szLable)
{
	CString szTitle(szLable);
	int nLen=szTitle.GetLength();
	if(nLen<20)
	{
		int n=20-nLen;
		for(int i=0;i<n;i++)
			szTitle+=_T(" ");
	}

	return szTitle;
}

void XInternalManage::GetAnotherNameByTabLable(CString szTabLable,CString& szName,CString& szAnotherName)
{
	szTabLable.Trim();

	int nPosFront=szTabLable.Find('(');
	int nPosBack=szTabLable.Find(')');

	if(nPosFront==-1
		||nPosBack==-1)
	{
		szName=szTabLable;
		szAnotherName=_T("");
	}
	else
	{
		szName=szTabLable.Left(nPosFront);

		CString szTemp=szTabLable.Mid(nPosFront+1);
		int nPos=szTemp.Find(')');
		if(nPos==-1)
			szAnotherName=szTemp;
		else
			szAnotherName=szTemp.Left(nPos);
	}
}

//截取单击事件,发生比较早,有问题
void XInternalManage::SetTabCtrlCLick(POINT point)
{
	CPoint pt(point);

	if(m_pTabCtrl!=NULL)
	{
		m_pTabCtrl->ScreenToClient(&pt);
		if(m_pTabCtrl->IsPtInTabArea(pt)&&m_pTabCtrl->GetTabFromPoint(pt)!=-1)
			SetActiveDockPane();
	}
}

void XInternalManage::SetActiveDockPane()
{
	//if(m_VideoPreviewPane!=NULL)
		//m_VideoPreviewPane->SetInputRTSPAddr();

	if(m_pTabCtrl!=NULL)
	{
		CWnd* pWnd=m_pTabCtrl->GetActiveWnd();
		if(pWnd!=NULL)
		{
			m_VideoPreviewPane=(XVideoPreviewPane*)pWnd;
			m_pTemp=m_VideoPreviewPane;
		}
	}

	//更改预览别名
	if(m_VideoPreviewPane!=NULL)
		m_VideoPreviewPane->UpdateInputAnotherNameByPreview();
}

void XInternalManage::CloseActivePane()
{
	if(m_VideoPreviewPane==NULL)
		return;

	//清除输入RTSP地址信息
	m_VideoPreviewPane->SetInputRTSPAddr();

	//预览RTSP计数值为零
	m_VideoPreviewPane->DeleteCurPaneRTSP();

	//1,删除MapTemp
	int nBoardIndex=m_VideoPreviewPane->GetBoardIndex();
	MAP_PREVIEWTEMP::iterator iterTemp=m_MapPreviewTemp.find(nBoardIndex);
	if(iterTemp!=m_MapPreviewTemp.end())
		m_MapPreviewTemp.erase(iterTemp);
	//////////////////////////////////////////////////////////////////////////////
	//3,设置为不选中
	MAP_SELECTBOARD::iterator iterSel=m_MapSelectBoard.find(nBoardIndex);
	if(iterSel!=m_MapSelectBoard.end())
	{
		XSelectBoardInfo* pInfo=iterSel->second;
		pInfo->SetSelected(FALSE);
	}
	////////////////////////////////////////////////////////////////////////////////
	//2,删除VecPreview
	int nSize=m_VecVideoPreviewPane.size();

	for(VEC_VIDEOPREVIEWPANE::iterator iter=m_VecVideoPreviewPane.begin();iter!=m_VecVideoPreviewPane.end();++iter)
	{
		XVideoPreviewPane* pPane=*iter;

		if(pPane==m_VideoPreviewPane)
		{
			m_VecVideoPreviewPaneTemp.push_back(pPane);
			m_VecVideoPreviewPane.erase(iter);
			m_VideoPreviewPane=NULL;
			break;
		}
	}

	//如果没有预览面板，全部置空
	if(m_VecVideoPreviewPane.size()==0)
	{
		m_VideoPreviewPane=NULL;
		m_pTabCtrl=NULL;
		m_pTabbedBar=NULL;
		m_pTemp=NULL;

		//所有输入置空
		SetInputSignalPara();
	}

	//////////////////////////////////////////////////////////////////////////
	//删除别名
	CString szPreview=GetTranslationString(_T("682"),_T("预览卡"));
	CString szTemp=GetTranslationString(_T("683"),_T("槽位"));

	CString szName=_T("");
	szName.Format(_T("%s-%s%d"),szPreview,szTemp,nBoardIndex);

	MAP_TABLABLE::iterator iter=m_MapBottomTabCtrLable.find(szName);
	if(iter!=m_MapBottomTabCtrLable.end())
		m_MapBottomTabCtrLable.erase(iter);
	//////////////////////////////////////////////////////////////////////////
	SetActiveDockPane();
}

void XInternalManage::SetInputSignalPara()
{
	m_pInputSignalPane->SetInputSignalPara();
}

XBitRateInfo* XInternalManage::GetBitRateInfo()
{
	return &m_BitRateInfo;
}

void XInternalManage::PreviewPaneReloadInterface()
{
	for(VEC_VIDEOPREVIEWPANE::iterator iter=m_VecVideoPreviewPane.begin();iter!=m_VecVideoPreviewPane.end();++iter)
	{
		XVideoPreviewPane* pTemp=*iter;
		pTemp->ReloadInterface();
	}
}

BOOL XInternalManage::JudgeSceneName(CString szName)
{
	return m_pScenePane->JudgeSceneName(szName);
}

void XInternalManage::SaveSceneByCloseView()
{
	m_pNowScreenManage->SaveSceneByCloseView();
}

MAP_SCENEGROUP& XInternalManage::GetMapSceneGroup()
{
	return m_pScenePane->GetMapSceneGroup();
}

void XInternalManage::OperateOfSaveAllScene()
{
	m_SaveAllSceneDlg.SetManage(this);

	if(IDOK==m_SaveAllSceneDlg.DoModal())
	{
		CString szSceneName=m_SaveAllSceneDlg.GetSceneName();
		int nSceneIndex=m_SaveAllSceneDlg.GetSceneIndex();
		CString szSceneGroup=m_SaveAllSceneDlg.GetSceneGroup();
		MAP_SELSCENE& MapSelScene=m_SaveAllSceneDlg.GetMapSelScene();

		if(JudgeSceneName(szSceneName))
		{
			MessageBoxFromKey(_T("726"),_T("场景名称重复！"),MB_OK);
			return;
		}
		//////////////////////////////////////////////////////////////////////////
		HTREEITEM item=AddSceneToTree(nSceneIndex,szSceneName,SCREENMODEL_DEV,szSceneGroup);

		for(MAP_SELSCENE::iterator iter=MapSelScene.begin();iter!=MapSelScene.end();++iter)
		{
			int nIndex=iter->first;
			CString szViewName=iter->second;
			for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();++iter)
			{
				XBaseScreenManage* pBase=*iter;
				if(szViewName==pBase->GetViewName())
				{
					pBase->SaveAllScene(szSceneName,nSceneIndex,szSceneGroup,nIndex,SCREENMODEL_DEV);
					AddViewNameToScene(item,szSceneName,nIndex,szViewName);
				}
			}
		}
	}
}

void XInternalManage::OperateOfReadSceneIndex(char* pData)
{
	//返回可用场景序号
	int nLen=12;

	if(!CheckSumNum(pData,nLen))
		return;

	m_SaveAllSceneDlg.SetData(pData);
}

int XInternalManage::GetScreenType()
{
	return m_pNowScreenManage->GetScreenModel();
}

void XInternalManage::OpenAllScene(CString szSceneName,int nSceneIndex)
{
	MAP_SCENE& MapScene=m_pScenePane->GetMapScene();
	MAP_SCENE::iterator iter=MapScene.find(szSceneName);
	if(iter!=MapScene.end())
	{
		XSceneInfo* pInfo=iter->second;
		MAP_SELSCENE& MapSel=pInfo->GetMapSelScene();
		for(MAP_SELSCENE::iterator iter=MapSel.begin();iter!=MapSel.end();++iter)
		{
			CString szViewName=iter->second;
			XBaseScreenManage* pBase=GetBaseScreenManageByViewName(szViewName);
			if(pBase==NULL)
			{
				MessageBoxFromKey(_T("744"),_T("屏幕标签发生变化，场景已经不适用！"),MB_OK);
				return;
			}
		}

		for(MAP_SELSCENE::iterator iter=MapSel.begin();iter!=MapSel.end();++iter)
		{
			int nIndex=iter->first;
			CString szViewName=iter->second;
			XBaseScreenManage* pBase=GetBaseScreenManageByViewName(szViewName);
			pBase->OpenAllScene(szSceneName,nSceneIndex,nIndex,SCREENMODEL_DEV,_T(""));
		}
	}
}

void XInternalManage::OpenOneSceneOfAll(CString szSceneName,int nSceneIndex,CString szViewName)
{
	MAP_SCENE& MapScene=m_pScenePane->GetMapScene();
	MAP_SCENE::iterator iter=MapScene.find(szSceneName);
	if(iter!=MapScene.end())
	{
		XSceneInfo* pInfo=iter->second;
		MAP_SELSCENE& MapSel=pInfo->GetMapSelScene();
		//for(MAP_SELSCENE::iterator iter=MapSel.begin();iter!=MapSel.end();++iter)
		//{
		//	CString szViewName=iter->second;
		//	XBaseScreenManage* pBase=GetBaseScreenManageByViewName(szViewName);
		//	if(pBase==NULL)
		//	{
		//		MessageBoxFromKey(_T("744"),_T("屏幕标签发生变化，场景已经不适用！"),MB_OK);
		//		return;
		//	}
		//}


		for(MAP_SELSCENE::iterator iter=MapSel.begin();iter!=MapSel.end();++iter)
		{
			int nIndex=iter->first;
			if(szViewName==iter->second)
			{
				XBaseScreenManage* pBase=GetBaseScreenManageByViewName(szViewName);
				pBase->OpenAllScene(szSceneName,nSceneIndex,nIndex,SCREENMODEL_FLAG,szViewName);
			}
		}
	}
}

void XInternalManage::CopyOrderToShare(CString szSceneName,int nSceneIndex,CString szViewName)
{
	MAP_SCENE& MapScene=m_pScenePane->GetMapScene();
	MAP_SCENE::iterator iter=MapScene.find(szSceneName);
	if(iter!=MapScene.end())
	{
		XSceneInfo* pInfo=iter->second;
		MAP_SELSCENE& MapSel=pInfo->GetMapSelScene();

		for(MAP_SELSCENE::iterator iter=MapSel.begin();iter!=MapSel.end();++iter)
		{
			int nIndex=iter->first;
			if(szViewName==iter->second)
			{
				XBaseScreenManage* pBase=GetBaseScreenManageByViewName(szViewName);
				//pBase->OpenAllScene(szSceneName,nSceneIndex,nIndex,SCREENMODEL_FLAG,szViewName);
				pBase->CopyOrderToShare(szSceneName,nSceneIndex,nIndex,szViewName);
			}
		}
	}
}

void XInternalManage::CopySingleOrderToShare(CString szSceneName,int nSceneIndex,CString szViewName)
{
	m_pNowScreenManage->CopySingleOrderToShare(szSceneName,nSceneIndex,szViewName);
}

XBaseScreenManage* XInternalManage::GetBaseScreenManageByViewName(CString szViewName)
{
	XBaseScreenManage* pBase=NULL;

	for(VEC_BASESCREENMANAGE::iterator iter=m_VecBaseScreenManage.begin();iter!=m_VecBaseScreenManage.end();++iter)
	{
		XBaseScreenManage* pTempBase=*iter;	
		if(szViewName==pTempBase->GetViewName())
			pBase=pTempBase;
	}
	return pBase;
}

int XInternalManage::GetVecBaseManageSize()
{
	return m_VecBaseScreenManage.size();
}

void XInternalManage::SetFrameRTSPCountByIndex(int nInputIndex)
{
	if(m_VideoPreviewPane!=NULL)
		m_VideoPreviewPane->SetFrameRTSPCountByIndex(nInputIndex);
}

CString XInternalManage::GetNotice()
{
	return m_pUserManage->GetNotice();
}

BOOL XInternalManage::SetSelInputDataInfo()
{
	return m_pInputSignalPane->SetSelInputDataInfo();
}

XDragInfo& XInternalManage::GetDragInfo()
{
	return m_pNowScreenManage->GetDragInfo();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

BOOL XInternalManage::CheckSumNum(char* pData,int& nLen)
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

unsigned short XInternalManage::CheckNum(char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
		nSum=nSum&0xFF;
	}

	return nSum;
}

CString XInternalManage::GetRTSPAddrFromPreviewPane(int nSignalIndex)
{
	if(NULL!=m_VideoPreviewPane)
	{
		return m_VideoPreviewPane->GetRTSPAddrFromPreviewPane(nSignalIndex);
	}

	return _T("");
}

//////////////////////////////////////////////////////////////////////////
void XInternalManage::UpdateControlDataShow(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_LANGUAGENAME:
		{
			m_pTranslationManage->UpdateControlDataShow(type, pControl);
		}
		break;
	case XDATATYPE_DEVICEIP:
	case XDATATYPE_DEVICEPORT:
		{
			m_pIniManage->UpdateControlDataShow(type, pControl);
		}
		break;
	case XDATATYPE_INPUTCOUNT:
		{
			m_pInputSignalPane->UpdateControlDataShow(type, pControl);
		}
		break;
	case XDATATYPE_SCALE:
	case XDATATYPE_OUTPUTCOUNTH:
	case XDATATYPE_OUTPUTCOUNTV:
		{
			m_pNowScreenManage->UpdateControlDataShow(type, pControl);
		}
		break;
	default:
		break;
	}
}

void XInternalManage::ControlDataChange(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_LANGUAGENAME:
		{
			m_pTranslationManage->ControlDataChange(type, pControl);
		}
		break;
	case XDATATYPE_DEVICEIP:
	case XDATATYPE_DEVICEPORT:
		{
			m_pIniManage->ControlDataChange(type, pControl);
		}
		break;
	case XDATATYPE_INPUTCOUNT:
		{
			m_pInputSignalPane->ControlDataChange(type, pControl);
		}
		break;
	case XDATATYPE_SCALE:
	case XDATATYPE_OUTPUTCOUNTH:
	case XDATATYPE_OUTPUTCOUNTV:
		{
			m_pNowScreenManage->ControlDataChange(type, pControl);
		}
		break;
	default:
		break;
	}
}

void XInternalManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_RELOADINTERFACE:
		{
			ReloadInterface();
		}
		break;
	case OPERATETYPE_ABOUT:
		{
			ShowAboutDlg();
		}
	case OPERATETYPE_RESETTEMPERATURE:
		{
			m_pDataManage->Operate(type, pData);
		}
		break;
	case OPERATETYPE_DEVICESTATUS:
	case OPERATETYPE_SCREENCLOSESIGNAL:
	case OPERATETYPE_SAVESCENCE:
	case OPERATETYPE_OPENSCENCE:
	case OPERATETYPE_DELETESCENCE:
	case OPERATETYPE_DELETEALLSIGNAL:
	case OPERATETYPE_SETSCREENRESULATION:
	case OPERATETYPE_RUNOLDORDER:
	case OPERATETYPE_SCREENMOVE:
	case OPERATETYPE_TIMEDPOLLING:
	case OPERATETYPE_SETSIGNALTOP:
	case OPERATETYPE_SETSIGNALBOTTOM:
	case OPERATETYPE_SETSIGNALSHIFTUP:
	case OPERATETYPE_SETSIGNALSHIFTDOWN:
	case OPERATETYPE_CHANGEINPUT:
	case OPERATETYPE_SCREENSEPARATE:
	case OPERATETYPE_SCREENRESULATION:
	case OPERATETYPE_CHANGESCREEN:
	case OPERATETYPE_SCREENATTRIBUTE:
	case OPERATETYPE_HANDLESCREENSYNBYVIDEOPREVIEW:
	case OPERATETYPE_SETSIGNALPARAMATER:
	case OPERATETYPE_GETSCREENPARAMATER:
	case OPERATETYPE_GETSIGNALPARAMATER:
	case OPERATETYPE_GETWINDOWPARAMATER:
	case OPERATETYPE_SETSCREENPARAMATER:
	case OPERATETYPE_SETSCREENPARAMATEROFMATRIX:
	case OPERATETYPE_SETWINDOWPARAMATER:
	case OPERATETYPE_GETSCREENMOVEASK:
	case OPERATETYPE_SETDEVICESTATUS:
	case OPERATETYPE_GETSCENEINDEX:
	case OPERATETYPE_SETSIGNALCUT:
	case OPERATETYPE_SETSIGNALEXPAND:
	case OPERATETYPE_MENUSCREENSET:
	case OPERATETYPE_MENUSAVESCENE:
	case OPERATETYPE_GETINPUTNUM:
	case OPERATETYPE_SETINPUTNUM:
	case OPERATETYPE_NEWSCENE:
	case OPERATETYPE_NORMAL:
	case OPERATETYPE_FULL:
	case OPERATETYPE_FOUR:
	case OPERATETYPE_INTER:
	case OPERATETYPE_TIPMODEL:
	case OPERATETYPE_UPMODEL:
	case OPERATETYPE_DOWNMODEL:
	case OPERATETYPE_SCREENRESULATIONOFMATRIX:
	case OPERATETYPE_GETMATRIXOUTPUT:
	case OPERATETYPE_SETSCENEINDEX:
	case OPERATETYPE_COPYMODEL:
	case OPERATETYPE_MATRIXOUTPUT:
	case OPERATETYPE_SINGLESCENE:
	case OPERATETYPE_SETROWDPI:
	case OPERATETYPE_SETCOLDPI:
		{
			m_pNowScreenManage->Operate(type, pData);
		}
		break;
	case OPERATETYPE_SETSCENEINDEX1:
		{
			OperateOfReadSceneIndex((char*)pData);
		}
		break;
	case OPERATETYPE_OPENNET:
	case OPERATETYPE_CLOSENET:
		{
			m_pNetManage->Operate(type, pData);
		}
		break;
	case OPERATETYPE_SETTEMPERATURE:
	case OPERATETYPE_REFRESHPAN:
	case OPERATETYPE_REFRESHCHIP:
		{
			m_pRibbonBarManage->Operate(type, pData);
		}
		break;
	case OPERATETYPE_LOGIN:
	case OPERATETYPE_LOGOUT:
	case OPERATETYPE_USERMANAGE:
	case OPERATETYPE_RESETUSERNODEPOWER:
		{
			m_pUserManage->Operate(type, pData);
		}
		break;
	case OPERATETYPE_SETSIGNALICON:
	case OPERATETYPE_GETPANEIPADDR:
	case OPERATETYPE_GETSTREAMADDR:
		{
			m_pInputSignalPane->Operate(type, pData);
		}
		break;
	case OPERATETYPE_NEWVIEW:
		{
			OperateOfNewView();
		}
		break;
	case OPERATETYPE_PREVIEW:
		{
			OperateOfSetPreviewBoard();
		}
		break;
	case OPERATETYPE_GETPREVIEWNET:
		{
			OperateOfReadPreviewNet((char*)pData);
		}
		break;
	case OPERATETYPE_GETBITRATE:
		{
			OperateOfReadPreviewBitRate((char*)pData);
		}
		break;
	case OPERATETYPE_SPLITBITRATE:
		{
			OpersteOdSplitBitRate();
		}
		break;
	case OPERATETYPE_SPLITNETSET:
		{
			OperateOfSplitNetSet();
		}
		break;
	case OPERATETYPE_SAVEALLSECNE:
		{
			OperateOfSaveAllScene();
		}
		break;
	default:
		break;
	}
}

void XInternalManage::UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)
{
	switch(type)
	{
	case CMDUITYPE_OPENNET:
	case CMDUITYPE_CLOSENET:
		{
			m_pNetManage->UpdateControlUI(type, pCmdUI);
		}
		break;
	case CMDUITYPE_LOGIN:
	case CMDUITYPE_LOGOUT:
	case CMDUITYPE_USERMANAGE:
	case CMDUITYPE_POWERMANAGE:
	case CMDUITYPE_INPUTCOUNT:
	case CMDUITYPE_OUTPUTCOUNTH:
	case CMDUITYPE_OUTPUTCOUNTV:
	case CMDUITYPE_DEVICEIP:
	case CMDUITYPE_DEVICEPORT:
	case CMDUITYPE_RUNOLDORDER:
	case CMDUITYPE_SAVESCENCE:
	case CMDUITYPE_OPENSCENCE:
	case CMDUITYPE_DELETESCENCE:
	case CMDUITYPE_DELETEALLSIGNAL:
	case CMDUITYPE_SCREENMOVE:
	case CMDUITYPE_TIMEDPOLLING:
	case CMDUITYPE_SETSCREENRESULATION:
	case CMDUITYPE_NEWVIEW:
	case CMDUITYPE_PREVIEW:
	case CMDUITYPE_SAVEALLSCENE:
		{
			m_pUserManage->UpdateControlUI(type, pCmdUI);
		}
		break;
	case CMDUITYPE_NORMAL:
	case CMDUITYPE_FULL:
	case CMDUITYPE_FOUR:
	case CMDUITYPE_INTER:
	case CMDUITYPE_TIPMODEL:
	case CMDUITYPE_UPMODEL:
	case CMDUITYPE_DOWNMODEL:
	case CMDUITYPE_COPYMODEL:
		{
			m_pUserManage->UpdateControlUI(type, pCmdUI);

			m_pNowScreenManage->UpdateControlUI(type,pCmdUI);
		}
		break;
	default:
		break;
	}
}