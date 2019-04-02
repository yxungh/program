#include "stdafx.h"
#include "XPreviewChild.h"
#include "afxdialogex.h"
#include "XDelegatePreviewChild.h"
#include "XInternalManage.h"
#include "XScreenRetInfo.h"
#include "XPreviewBoard.h"
#include "HYXText.h"
#include "XBoardNet.h"
#include "XSelectBoardInfo.h"
#include "XpreviewBoardBitRate.h"
#include "XSetPreviewBoard.h"


#define FONT_SIZE 18
#define SCROOL_TIME_ELAPSE  200


IMPLEMENT_DYNAMIC(XPreviewChild, CDialogEx)

	XPreviewChild::XPreviewChild(CWnd* pParent /*=NULL*/)
	: CDialogEx(XPreviewChild::IDD, pParent)
{
	m_pParent=NULL;

	m_pDelegate=NULL;

	m_bScrollTimerV=FALSE;

	m_nScrollPosV=0;

	m_nScrollTimerV=0;

	m_nScrellHight=0;

	m_pBoardNetDlg=NULL;

	m_pBoardBitRateDlg=NULL;
}

XPreviewChild::~XPreviewChild()
{
	DeleteFont();
}

void XPreviewChild::DeleteFont()
{
	m_Font.DeleteObject();

	ClearVecPreviewBoard();

	ClearVecTextWnd();
}

void XPreviewChild::ClearVecPreviewBoard()
{
	for(VEC_PREVIEWBOARD::iterator iter=m_VecPreViewBoard.begin();iter!=m_VecPreViewBoard.end();++iter)
		delete *iter;

	m_VecPreViewBoard.clear();
}

void XPreviewChild::ClearVecTextWnd()
{
	for(VEC_VIEWTEXT::iterator iter=m_VecPreviewText.begin();iter!=m_VecPreviewText.end();++iter)
		delete *iter;

	m_VecPreviewText.clear();
}

void XPreviewChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XPreviewChild, CDialogEx)
	ON_BN_CLICKED(ID_SPLITBTN,&XPreviewChild::OnSplitBtn)
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	
	ON_COMMAND(ID_MENU_NET,OnMenuNet)
	ON_COMMAND(ID_MENU_BITRATE,OnMenuBitRate)

END_MESSAGE_MAP()


void XPreviewChild::SetDelegate(XDelegatePreviewChild* p)
{
	m_pDelegate=p;
}

void XPreviewChild::SetPreviewParent(XSetPreviewBoard* p)
{
	m_pParent=p;
}

void XPreviewChild::SetBaseManage(XInternalManage* p)
{
	m_pBaseManage=p;
}

CFont* XPreviewChild::GetFont()
{
	return &m_Font;
}

BOOL XPreviewChild::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return FALSE;  
}

void XPreviewChild::Init()
{
	InitFont();

	InitVecPreview();

	InitTextWnd();

	InitVecPreviewBoard();

	AdjustScrollV();

	InitData();

	ReloadInterface();

	ResetVecPreciewBoard();
}

void XPreviewChild::InitFont()
{
	m_Font.CreateFont(   
		12,    
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

void XPreviewChild::ResetVecPreciewBoard()
{
	MAP_SELECTBOARD& MapSelectBoard=m_pBaseManage->GetMapSelectBoard();

	for(MAP_SELECTBOARD::iterator iter=MapSelectBoard.begin();iter!=MapSelectBoard.end();++iter)
	{
		XSelectBoardInfo* pInfo=iter->second;

		int nBoardIndex=pInfo->GetBoardIndex();

		for(VEC_PREVIEWBOARD::iterator iterPre=m_VecPreViewBoard.begin();iterPre!=m_VecPreViewBoard.end();++iterPre)
		{
			XPreviewBoard* pBoard=*iterPre;

			if(nBoardIndex==pBoard->GetBoardIndex())
			{
				pBoard->SetSelected(pInfo->GetSelected());
				pBoard->UpDateImage();
			}
		}
	}
}

void XPreviewChild::InitVecPreview()
{
	MAP_BOARDTYPE& MapBoardType=m_pBaseManage->GetMapBoardType();

	int nIndex=1;

	for(MAP_BOARDTYPE::iterator iter=MapBoardType.begin();iter!=MapBoardType.end();++iter)
	{
		int nBoardIndex=iter->first;

		int nType=iter->second;

		if(nType==BOARDTYPE_PREVIEW)
		{
			XPreviewBoard* pBoard=new XPreviewBoard;

			pBoard->SetIndex(nIndex);

			pBoard->SetBoardIndex(nBoardIndex);

			m_VecPreViewBoard.push_back(pBoard);

			nIndex++;
		}
	}


	//int nIndex=1;
	//for(int i=0;i<10;i++)
	//{
	//	XPreviewBoard* pBoard=new XPreviewBoard;

	//	pBoard->SetIndex(nIndex);

	//	pBoard->SetBoardIndex(nIndex);

	//	m_VecPreViewBoard.push_back(pBoard);

	//	nIndex++;
	//}

	if(m_VecPreViewBoard.size()==0)
		m_pParent->SetButtonStatus(FALSE);
	else
		m_pParent->SetButtonStatus(TRUE);
}

void XPreviewChild::InitTextWnd()
{
	CRect rect;
	GetClientRect(&rect);

	int nDistance=NEWDISTANCE;

	int nTextWidth=DISTANCE+15;
	int nTextHight=25;

	int nBeginX=rect.left;
	int nBeginY=rect.top;

	int nX=nBeginX;
	int nY=nBeginY;

	int nSize=m_VecPreViewBoard.size();
	for(int i=0;i<nSize;i++)
	{
		int nIndex=i+1;
		CString szText;

		szText.Format(_T("%d"),nIndex);
		CRect rect(nX,nY,nX+nTextWidth,nY+nTextHight);
		m_TextRect=rect;

		HYXText* pTextWnd=new HYXText;
		pTextWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,0);
		//pTextWnd->SetFont(&m_Font);
		pTextWnd->SetText(szText);
		pTextWnd->ShowWindow(SW_SHOW);
		pTextWnd->UpdateWindow();
		
		m_VecPreviewText.push_back(pTextWnd);
		//m_pTextWnd=pTextWnd;

		nY=nY+nDistance+nTextHight+PREVIEW_TEXTHEIGHT;
	}
}

void XPreviewChild::InitVecPreviewBoard()
{
	CRect rect;
	GetClientRect(&rect);

	int nDistance=NEWDISTANCE;
	int nBoardWidth=260+SPLITBTN_WIDTH;
	int nBoardHight=25+PREVIEW_TEXTHEIGHT;

	int nBeginX=m_TextRect.right;
	int nBeginY=rect.top;

	int nX=nBeginX+DISTANCE;
	int nY=nBeginY;

	for(VEC_PREVIEWBOARD::iterator iter=m_VecPreViewBoard.begin();iter!=m_VecPreViewBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;

		CRect rect(nX,nY,nX+nBoardWidth,nY+nBoardHight);

		pBoard->SetBaseManage(m_pBaseManage);

		pBoard->SetPreviewChild(this);

		pBoard->SetRect(rect);

		pBoard->Init();

		pBoard->SetSplitDorpDown();

		pBoard->UpDateText();

		nY=nY+nDistance+nBoardHight;
	}
}

void XPreviewChild::InitData()
{

}

void XPreviewChild::OnShowMenu()
{
	CPoint p;
	GetCursorPos(&p);

	CMenu menu; 
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_MENU_NET, m_pDelegate->GetTranslationString(_T("233"), _T("网络")));
	menu.AppendMenu(MF_STRING, ID_MENU_BITRATE, m_pDelegate->GetTranslationString(_T("772"), _T("码率")));
	////////////////////////////////////////////////////////////////////////////////////////
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, p.x, p.y, this);
	menu.DestroyMenu(); 
}

void XPreviewChild::OnMenuNet()
{

	SplitNetSet();
}

void XPreviewChild::OnMenuBitRate()
{
	SplitBiteRate();
}

void XPreviewChild::ReloadInterface()
{
	for(VEC_PREVIEWBOARD::iterator iter=m_VecPreViewBoard.begin();iter!=m_VecPreViewBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;
		pBoard->UpDateText();
	}
}

void XPreviewChild::OnSplitBtn()
{
	if(m_pBaseManage!=NULL)
		m_pBaseManage->OperateOfSplitNetSet();
}

void XPreviewChild::OnSplitNetSet()
{
	//判断是否为XP系统。xp系统不支持SpliButton
	OSVERSIONINFOEX os; 
	os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX); 
	if(GetVersionEx((OSVERSIONINFO *)&os))
	{
		if(os.dwMajorVersion==5)
		{
			return;
		}
	}

	SplitNetSet();
}

void XPreviewChild::OperateOfReadPreviewNet(char* pData)
{
	int nLen=61+8;

	if(!CheckSumNum(pData,nLen))
		return;

	if(m_pBoardNetDlg==NULL)
		return;
	//*************************************
	int nModel=pData[8];
	//*************************************
	int nIP1=pData[9]&0xFF;
	int nIP2=pData[10]&0xFF;
	int nIP3=pData[11]&0xFF;
	int nIP4=pData[12]&0xFF;

	CString szPaneIP=_T("");
	szPaneIP.Format(_T("%d.%d.%d.%d"),nIP1,nIP2,nIP3,nIP4);
	//*************************************
	int nMask1=pData[13]&0xFF;
	int nMask2=pData[14]&0xFF;
	int nMask3=pData[15]&0xFF;
	int nMask4=pData[16]&0xFF;

	CString szPaneMask=_T("");
	szPaneMask.Format(_T("%d.%d.%d.%d"),nMask1,nMask2,nMask3,nMask4);
	//*************************************
	int nGateWay1=pData[17]&0xFF;
	int nGateWay2=pData[18]&0xFF;
	int nGateWay3=pData[19]&0xFF;
	int nGateWay4=pData[20]&0xFF;

	CString szPaneGateWay=_T("");
	szPaneGateWay.Format(_T("%d.%d.%d.%d"),nGateWay1,nGateWay2,nGateWay3,nGateWay4);
	//*************************************
	int nMAC1=pData[21]&0xFF;
	int nMAC2=pData[22]&0xFF;
	int nMAC3=pData[23]&0xFF;
	int nMAC4=pData[24]&0xFF;
	int nMAC5=pData[25]&0xFF;
	int nMAC6=pData[26]&0xFF;

	CString szPaneMAC=_T("");
	szPaneMAC.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),nMAC1,nMAC2,nMAC3,nMAC4,nMAC5,nMAC6);
	//*************************************
	int nUseNameLen=16;
	char* pUseNameData=new char[nUseNameLen];
	memcpy(pUseNameData,pData+27,nUseNameLen);

	char* pTempUseNameData=pUseNameData;
	USES_CONVERSION;
	CString szUseName=A2W(pTempUseNameData);
	szUseName.Trim();
	delete []pUseNameData;
	//*************************************
	int nPassWdLen=16;
	char* pPassWdData=new char[nPassWdLen];
	memcpy(pPassWdData,pData+43,nPassWdLen);

	char* pTempPassWdData=pPassWdData;
	CString szpPassWd=A2W(pTempPassWdData);
	szpPassWd.Trim();
	delete []pPassWdData;

	int nSecret=pData[59];
	//修改标志
	int nFlag=pData[60];

	char pTime[9]={0};
	memcpy(pTime,pData+61,8);
	pTime[8]='\0';

	CString szTime(pTime);
	//*************************************
	m_pBoardNetDlg->SetUseName(szUseName);
	m_pBoardNetDlg->SetPassWd(szpPassWd);
	m_pBoardNetDlg->SetIP(szPaneIP);
	m_pBoardNetDlg->SetMask(szPaneMask);
	m_pBoardNetDlg->SetGateWay(szPaneGateWay);
	m_pBoardNetDlg->SetMAC(szPaneMAC);
	m_pBoardNetDlg->SetModel(nModel);
	m_pBoardNetDlg->SetSecret(nSecret);
	m_pBoardNetDlg->SetVersion(szTime);
	
	m_pBoardNetDlg->ResetNet();
}

void XPreviewChild::OnSplitBiteRate()
{
	OSVERSIONINFOEX os; 
	os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX); 
	if(GetVersionEx((OSVERSIONINFO *)&os))
	{
		if(os.dwMajorVersion==5)
		{
			return;
		}
	}

	SplitBiteRate();
}

void XPreviewChild::OperateOfReadPreviewBitRate(char* pData)
{
	int nLen=32;

	if(!CheckSumNum(pData,nLen))
		return;

	//通道1
	int nMainDpi1=pData[8];
	int nMainBitRate1=pData[9];
	int nSubDPi1=pData[11];
	int nSubBitRate1=pData[12];

	//通道2
	int nMainDpi2=pData[14];
	int nMainBitRate2=pData[15];
	int nSubDPi2=pData[17];
	int nSubBitRate2=pData[18];

	//通道3
	int nMainDpi3=pData[20];
	int nMainBitRate3=pData[21];
	int nSubDPi3=pData[23];
	int nSubBitRate3=pData[24];

	//通道4
	int nMainDpi4=pData[26];
	int nMainBitRate4=pData[27];
	int nSubDPi4=pData[29];
	int nSubBitRate4=pData[30];
	//////////////////////////////////////////////////////////////////////////

	if(m_pBoardBitRateDlg==NULL)
		return;

	m_pBoardBitRateDlg->SetMainDpi(nMainDpi1);
	m_pBoardBitRateDlg->SetMainDpi2(nMainDpi2);
	m_pBoardBitRateDlg->SetMainDpi3(nMainDpi3);
	m_pBoardBitRateDlg->SetMainDpi4(nMainDpi4);
	m_pBoardBitRateDlg->SetMainBitRate(nMainBitRate1);
	m_pBoardBitRateDlg->SetMainBitRate2(nMainBitRate2);
	m_pBoardBitRateDlg->SetMainBitRate3(nMainBitRate3);
	m_pBoardBitRateDlg->SetMainBitRate4(nMainBitRate4);

	m_pBoardBitRateDlg->SetSubDpi(nSubDPi1);
	m_pBoardBitRateDlg->SetSubDpi2(nSubDPi2);
	m_pBoardBitRateDlg->SetSubDpi3(nSubDPi3);
	m_pBoardBitRateDlg->SetSubDpi4(nSubDPi4);
	m_pBoardBitRateDlg->SetSubBitRate(nSubBitRate1);
	m_pBoardBitRateDlg->SetSubBitRate2(nSubBitRate2);
	m_pBoardBitRateDlg->SetSubBitRate3(nSubBitRate3);
	m_pBoardBitRateDlg->SetSubBitRate4(nSubBitRate4);

	m_pBoardBitRateDlg->ResetDate();
}

void XPreviewChild::SplitNetSet()
{
	//根据区域来判断是哪一个
	CPoint point;
	GetCursorPos(&point);

	CRect rect;
	ClientToScreen(&rect);

	CPoint TempPoint;
	TempPoint.x=point.x-rect.left;
	TempPoint.y=point.y-rect.top;
	TempPoint.y+=m_nScrollPosV;

	XPreviewBoard* pPreviewBoard=GetPreviewBoardByPoint(TempPoint);

	if(pPreviewBoard==NULL)
		return;

	//TRACE(_T("BoardIndex=%d\n"),pPreviewBoard->GetBoardIndex());
	//TRACE(_T("m_nScrollPosV=%d\n"),m_nScrollPosV);

	XBoardNet dlg;
	dlg.SetInternalManage(m_pBaseManage);
	dlg.SetBoardIndex(pPreviewBoard->GetBoardIndex());
	m_pBoardNetDlg=&dlg;

	if(IDOK==dlg.DoModal())
	{
		XBoardNetInfo* pInfo=m_pBaseManage->GetBoardInfo();
		for(VEC_PREVIEWBOARD::iterator iter=m_VecPreViewBoard.begin();iter!=m_VecPreViewBoard.end();++iter)
		{
			XPreviewBoard* pBoard=*iter;
			if(pBoard==pPreviewBoard)
			{
				pBoard->SetSecretSel(pInfo->GetSecretSelect());
				pBoard->SetUseName(pInfo->GetUseName());
				pBoard->SetPassWd(pInfo->GetPassWd());
				pBoard->SetModelSel(pInfo->GetSelect());
				pBoard->SetIP(pInfo->GetIPAddr());
				pBoard->SetMask(pInfo->GetMaskAddr());
				pBoard->SetGateWay(pInfo->GetGateWayAddr());
				pBoard->SetMAC(pInfo->GetMACAddr());
			}
		}
	}

	m_pBoardNetDlg=NULL;
}

void XPreviewChild::SplitBiteRate()
{
	CPoint point;
	GetCursorPos(&point);

	CRect rect;
	ClientToScreen(&rect);

	CPoint TempPoint;
	TempPoint.x=point.x-rect.left;
	TempPoint.y=point.y-rect.top;
	TempPoint.y+=m_nScrollPosV;

	XPreviewBoard* pPreviewBoard=GetPreviewBoardByPoint(TempPoint);

	if(pPreviewBoard==NULL)
		return;

	//TRACE(_T("BoardIndex=%d\n"),pPreviewBoard->GetBoardIndex());
	//TRACE(_T("m_nScrollPosV=%d\n"),m_nScrollPosV);

	//设置码率
	XPreviewBoardBitRate dlg;
	dlg.SetManage(m_pBaseManage);
	dlg.SetBoardIndex(pPreviewBoard->GetBoardIndex());
	m_pBoardBitRateDlg=&dlg;

	dlg.DoModal();

	m_pBoardBitRateDlg=NULL;
}

VEC_PREVIEWBOARD& XPreviewChild::GetVecPreviewBoard()
{
	return m_VecPreViewBoard;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void XPreviewChild::AdjustScrollV()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollHeight=GetScrollHight();

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollHeight;
	si.nPage = rt.Height();
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (m_nScrollPosV > si.nPos)
	{
		m_nScrollPosV = si.nPos;
	}
}

void XPreviewChild::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si) ;
	si.fMask = SIF_ALL ;

	GetScrollInfo(SB_VERT, &si) ;

	int pos = si.nPos;

	switch (nSBCode)
	{
	case SB_TOP:
		si.nPos = si.nMin ;
		break ;

	case SB_BOTTOM:
		si.nPos = si.nMax ;
		break ;

	case SB_LINEUP:
		si.nPos -= 20;
		break ;

	case SB_LINEDOWN:
		si.nPos += 20 ;
		break ;

	case SB_PAGEUP:
		si.nPos -= si.nPage ;
		break ;

	case SB_PAGEDOWN:
		si.nPos += si.nPage ;
		break ;

	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos ;
		break ;

	default:
		break ;         
	}

	si.fMask = SIF_POS ;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (si.nPos != pos)
	{                    
		if (!m_bScrollTimerV)
		{
			SetTimer(1, SCROOL_TIME_ELAPSE, NULL);
			m_bScrollTimerV = TRUE;
		}
	}

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}


void XPreviewChild::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_VERT, &si) ;
		int nPos = si.nPos;

		//TRACE("XOSDGrid::ScrollV Pos:%d\n", nPos);

		if (nPos != m_nScrollPosV)
		{
			ScrollWindow(0, m_nScrollPosV - nPos, NULL, NULL);
			m_nScrollPosV = nPos;
			m_nScrollTimerV = 0;
			Invalidate();
		}
		else
		{
			m_nScrollTimerV++;

			if (m_nScrollTimerV >= 5)
			{
				KillTimer(1);
				m_bScrollTimerV = FALSE;
			}
		}
	}

	CWnd::OnTimer(nIDEvent);
}

int XPreviewChild::GetScrollHight()
{
	int nBtnHight=25;
	int nSize=m_VecPreViewBoard.size();
	return (NEWDISTANCE+nBtnHight+PREVIEW_TEXTHEIGHT)*nSize-NEWDISTANCE;
}

XPreviewBoard* XPreviewChild::GetPreviewBoardByPoint(CPoint point)
{
	for(VEC_PREVIEWBOARD::iterator iter=m_VecPreViewBoard.begin();iter!=m_VecPreViewBoard.end();++iter)
	{
		XPreviewBoard* pBoard=*iter;

		CRect rect=pBoard->GetRect();
		if((point.y-rect.top)<=72)
			return pBoard;
	}

	return NULL;
}

BOOL XPreviewChild::CheckSumNum(char* pData,int nLen)
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

unsigned short XPreviewChild::CheckNum(char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
		nSum=nSum&0xFF;
	}

	return nSum;
}