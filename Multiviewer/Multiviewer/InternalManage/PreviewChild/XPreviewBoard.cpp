#include "stdafx.h"
#include "XPreviewBoard.h"
#include "XPreviewBoardWnd.h"
#include "HYXText.h"
#include "HandlePath.h"
#include "XPreviewChild.h"
#include "XInternalManage.h"
#include "MySplitButton.h"

XPreviewBoard::XPreviewBoard()
{
	m_nIndex=0;

	m_nBoardIndex=0;

	m_pPreviewBoardWnd=NULL;

	m_pPreviewTextWnd=NULL;

	m_pPreviewChild=NULL;

	m_pSplitBtn=NULL;

	m_pManage=NULL;

	m_nSecretSel=0;

	m_nModelSel=0;

	m_szIP=_T("");

	m_szUserName=_T("");

	m_szPassWd=_T("");

	m_szMask=_T("");

	m_szGateWay=_T("");

	m_szMAC=_T("");

	m_bSelected=FALSE;

}

XPreviewBoard::~XPreviewBoard()
{
	ClearPreviewBoardWnd();

	ClearPreviewTextWnd();

	ClearSplitButton();
}

void XPreviewBoard::ClearPreviewBoardWnd()
{
	if(m_pPreviewBoardWnd!=NULL)
	{
		delete m_pPreviewBoardWnd;

		m_pPreviewBoardWnd=NULL;
	}
}

void XPreviewBoard::ClearPreviewTextWnd()
{
	if(m_pPreviewTextWnd!=NULL)
	{
		delete m_pPreviewTextWnd;

		m_pPreviewTextWnd=NULL;
	}
}

//void XPreviewBoard::ClearPreviewBoardInfo()
//{
//	for(VEC_PREVIEWBOARDINFO::iterator iter=m_VecPreviewBoardInfo.begin();iter!=m_VecPreviewBoardInfo.end();++iter)
//	{
//		delete *iter;
//	}
//
//	m_VecPreviewBoardInfo.clear();
//}

void XPreviewBoard::ClearSplitButton()
{
	if(m_pSplitBtn!=NULL)
	{
		delete m_pSplitBtn;

		m_pSplitBtn=NULL;
	}
}

void XPreviewBoard::SetBaseManage(XInternalManage* p)
{
	m_pManage=p;
}

void XPreviewBoard::SetPreviewChild(XPreviewChild* p)
{
	m_pPreviewChild=p;
}

XPreviewChild* XPreviewBoard::GetPreviewChild()
{
	return m_pPreviewChild;
}

void XPreviewBoard::SetIndex(int n)
{
	m_nIndex=n;
}

int XPreviewBoard::GetIndex()
{
	return m_nIndex;
}

void XPreviewBoard::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int XPreviewBoard::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XPreviewBoard::SetRect(CRect rect)
{
	m_Rect=rect;
}

CRect XPreviewBoard::GetRect()
{
	return m_Rect;
}

void XPreviewBoard::SetUseName(CString szName)
{
	m_szUserName=szName;
}

CString XPreviewBoard::GetUseName()
{
	return m_szUserName;
}

void XPreviewBoard::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

CString XPreviewBoard::GetPassWd()
{
	return m_szPassWd;
}

void XPreviewBoard::SetIP(CString szIP)
{
	m_szIP=szIP;
}

CString XPreviewBoard::GetIP()
{
	return m_szIP;
}

void XPreviewBoard::SetSecretSel(int n)
{
	m_nSecretSel=n;
}

int XPreviewBoard::GetSecretSel()
{
	return m_nSecretSel;
}

void XPreviewBoard::SetModelSel(int n)
{
	m_nModelSel=n;
}

int XPreviewBoard::GetModelSel()
{
	return m_nModelSel;
}

void XPreviewBoard::SetMask(CString szMask)
{
	m_szMask=szMask;
}

CString XPreviewBoard::GetMask()
{
	return m_szMask;
}

void XPreviewBoard::SetGateWay(CString szGateWay)
{
	m_szGateWay=szGateWay;
}

CString XPreviewBoard::GetGateWay()
{
	return m_szGateWay;
}

void XPreviewBoard::SetMAC(CString szMAC)
{
	m_szMAC=szMAC;
}

CString XPreviewBoard::GetMAC()
{
	return m_szMAC;
}

MySplitButton* XPreviewBoard::GetMySplitBtn()
{
	return m_pSplitBtn;
}

void XPreviewBoard::SetSelected(BOOL b)
{
	m_bSelected=b;
}

BOOL XPreviewBoard::GetSelected()
{
	return m_bSelected;
}

//VEC_PREVIEWBOARDINFO& XPreviewBoard::GetVecBoardInfo()
//{
//	return m_VecPreviewBoardInfo;
//}

void XPreviewBoard::Init()
{
	ClearPreviewBoardWnd();

	ClearPreviewTextWnd();

	InitPreviewBoardWnd();

	InitSplitBtn();

	InitPreviewTextWnd();
}

void XPreviewBoard::InitPreviewBoardWnd()
{
	CRect rect=m_Rect;
	rect.bottom=rect.bottom-PREVIEW_TEXTHEIGHT;
	rect.right=rect.right-SPLITBTN_WIDTH;

	m_BoardRect=rect;

	XPreviewBoardWnd* pWnd=new XPreviewBoardWnd;
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pPreviewChild,0);
	pWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
	pWnd->SetParent(this);
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();

	m_pPreviewBoardWnd=pWnd;
}

void XPreviewBoard::OnShowMenu()
{
	if(NULL!=m_pPreviewChild)
		m_pPreviewChild->OnShowMenu();
}

void XPreviewBoard::InitSplitBtn()
{
	CRect rect=m_Rect;

	rect.left=m_BoardRect.right+10;
	rect.bottom=rect.bottom-PREVIEW_TEXTHEIGHT;

	MySplitButton* pSplitBtn=new MySplitButton;

	CString szTitle=m_pManage->GetTranslationString(_T("268"),_T("ÉèÖÃ"));

	pSplitBtn->Create(szTitle,WS_CHILD|WS_VISIBLE,rect,m_pPreviewChild,ID_SPLITBTN);
	pSplitBtn->SetFont(m_pPreviewChild->GetFont());
	pSplitBtn->ShowWindow(SW_SHOW);
	pSplitBtn->UpdateWindow();

	pSplitBtn->SetBoardIndex(m_nIndex);
	pSplitBtn->SetBoardIndex(m_nBoardIndex);

	m_pSplitBtn=pSplitBtn;
}

void XPreviewBoard::SetSplitDorpDown()
{
	if(m_pSplitBtn!=NULL)
	{
		m_pSplitBtn->SetDropDownMenu(IDR_MENU_SPLIT,0);
	}
}

void XPreviewBoard::InitPreviewTextWnd()
{
	CRect rect=m_Rect;
	rect.top=rect.bottom-PREVIEW_TEXTHEIGHT;
	rect.right=rect.right-SPLITBTN_WIDTH;

	HYXText* pTextWnd=new HYXText;
	pTextWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pPreviewChild,0);
	//pTextWnd->SetFont(m_pPreviewChild->GetFont());
	pTextWnd->SetTextColor(RGB(255,0,0));
	pTextWnd->ShowWindow(SW_SHOW);
	pTextWnd->UpdateWindow();

	m_pPreviewTextWnd=pTextWnd;
}

void XPreviewBoard::UpDateText()
{
	CString szText=_T("");

	CString szTemp=m_pManage->GetTranslationString(_T("682"),_T("Ô¤ÀÀ¿¨"));

	CString szTemp2=m_pManage->GetTranslationString(_T("683"),_T("²ÛÎ»"));

	CString szIndex;
	szIndex.Format(_T("%d"),m_nIndex);

	CString szBoardIndex;
	szBoardIndex.Format(_T("%d"),m_nBoardIndex);

	szText=szTemp+_T(":")+szIndex+_T(",")+szTemp2+_T(":")+szBoardIndex;

	if(m_pPreviewTextWnd!=NULL)
	{
		m_pPreviewTextWnd->SetText(szText);
	}

}


void XPreviewBoard::UpDateImage()
{
	if(m_pPreviewBoardWnd!=NULL)
	{
		if(GetSelected())
		{
			m_pPreviewBoardWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_12.png")));
		}
		else
		{
			m_pPreviewBoardWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
		}
	}
}
