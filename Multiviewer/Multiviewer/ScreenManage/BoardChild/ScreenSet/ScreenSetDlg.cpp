// ParameterSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenSetDlg.h"
#include "afxdialogex.h"
#include "XScreenInfo.h"
#include "XScreen.h"
#include "..\resource.h"
#include "HYXText.h"


const int SCREENROW_MAX = 100;
const int SCREENROW_MIN = 1;

const int SCREENCOLUMN_MAX = 100;
const int SCREENCOLUMN_MIN = 1;

// CScreenSetDlg 对话框

#define NFONTSIZE   19

IMPLEMENT_DYNAMIC(CScreenSetDlg, CDialogEx)

	CScreenSetDlg::CScreenSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenSetDlg::IDD, pParent)
{
	m_pScreenInfosWnd = nullptr;

	m_nBoardIndex=0;

	m_nBeginScreenIndex=1;

	m_TextInfo1=NULL;

	m_TextInfo2=NULL;

	m_TextInfo3=NULL;

	m_TextInfo4=NULL;

	m_TextInfo5=NULL;

	m_nScreenIndex=-1;

	m_nScreenIndex2=-1;

	m_nScreenIndex3=-1;

	m_nScreenIndex4=-1;

	m_nNumOfScreen=0;
}

CScreenSetDlg::~CScreenSetDlg()
{
	ClearVecScreenInfo();

	ClearWnd();

	ClearText();

	DeleteFont();
}

void CScreenSetDlg::ClearWnd()
{
	if (nullptr != m_pScreenInfosWnd)
	{
		delete m_pScreenInfosWnd;

		m_pScreenInfosWnd = nullptr;
	}
}

void CScreenSetDlg::ClearText()
{
	if(m_TextInfo1!=NULL)
	{
		delete m_TextInfo1;

		m_TextInfo1=NULL;
	}

	if(m_TextInfo2!=NULL)
	{
		delete m_TextInfo2;

		m_TextInfo2=NULL;
	}

	if(m_TextInfo3!=NULL)
	{
		delete m_TextInfo3;

		m_TextInfo3=NULL;
	}

	if(m_TextInfo4!=NULL)
	{
		delete m_TextInfo4;

		m_TextInfo4=NULL;
	}

	if(m_TextInfo5!=NULL)
	{
		delete m_TextInfo5;

		m_TextInfo5=NULL;
	}
}

void CScreenSetDlg::ClearVecScreenInfo()
{
	for (VEC_SCREENINFO::iterator iter = m_VecScreenInfo.begin(); iter != m_VecScreenInfo.end(); iter++)
	{
		delete *iter;
	}

	m_VecScreenInfo.clear();
}

void CScreenSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreenSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScreenSetDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BTN_SETSCREEN, &CScreenSetDlg::OnBnClickedSetScreen)
END_MESSAGE_MAP()


// CScreenSetDlg 消息处理程序

BOOL CScreenSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitFont();

	InitData();

	SetWindowText(m_pDelegate->GetTranslationString(_T("595"), _T("设置向导-选择信号对应屏幕")));
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("208"), _T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("209"), _T("取消")));
	GetDlgItem(IDC_STATIC_CURPAN)->SetWindowText(m_pDelegate->GetTranslationString(_T("587"), _T("当前板卡"))+_T(":"));
	GetDlgItem(IDC_STATIC_FIRST)->SetWindowText(m_pDelegate->GetTranslationString(_T("588"), _T("第一路对应屏幕"))+_T(":"));
	GetDlgItem(IDC_STATIC_SECOND)->SetWindowText(m_pDelegate->GetTranslationString(_T("600"), _T("第二路对应屏幕"))+_T(":"));
	GetDlgItem(IDC_STATIC_THREE)->SetWindowText(m_pDelegate->GetTranslationString(_T("699"), _T("第三路对应屏幕"))+_T(":"));
	GetDlgItem(IDC_STATIC_FOUR)->SetWindowText(m_pDelegate->GetTranslationString(_T("700"), _T("第四路对应屏幕"))+_T(":"));
	GetDlgItem(IDC_STATIC_TIPS11)->SetWindowText(m_pDelegate->GetTranslationString(_T("698"), _T("提示:双击选择信号所对应屏幕，一路信号对应一个屏幕，两路对应两个屏幕")));

	if(m_nScreenModel==SCREENMODEL_SPLIC)
	{
		GetDlgItem(IDC_STATIC_THREE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_FOUR)->ShowWindow(FALSE);
	}

	CreateScreenInfosWnd();

	CreateText();

	//UpdataText();

	InitText();

	return FALSE;  
}

void CScreenSetDlg::SetDelegate(XDelegateScreenSetDlg* pDelegate)
{
	m_pDelegate = pDelegate;
}

void CScreenSetDlg::InitFont()
{
	m_Font.CreateFont(   
		NFONTSIZE,    
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

void CScreenSetDlg::DeleteFont()
{
	m_Font.DeleteObject();
}

void CScreenSetDlg::InitData()
{
	m_nScreenColumn = m_pDelegate->GetColumn();

	m_nScreenRow = m_pDelegate->GetRow();

	m_nBeginScreenIndex=m_pDelegate->GetBeginScreenIndex();

	m_pDelegate->CopyVecBoardToVecScreeInfo(m_VecScreenInfo);

	//初始化 初始屏幕序号
	InitScreenIndex();
}

void CScreenSetDlg::InitScreenIndex()
{
	for(VEC_SCREENINFO::iterator iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		XScreenInfo* pInfo=*iter;

		int nNumOfScreen=pInfo->GetNumOfScreen();

		int nBorardIndex=pInfo->GetBoardIndex();

		if(nBorardIndex==m_nBoardIndex)
		{
			if(nNumOfScreen==0)
			{
				m_nScreenIndex=pInfo->GetScreenIndex();
			}
			else if(nNumOfScreen==1)
			{
				m_nScreenIndex=pInfo->GetScreenIndex();
			}
			else if(nNumOfScreen==2)
			{
				m_nScreenIndex2=pInfo->GetScreenIndex();
			}
			else if(nNumOfScreen==3)
			{
				m_nScreenIndex3=pInfo->GetScreenIndex();
			}
			else if(nNumOfScreen==4)
			{
				m_nScreenIndex4=pInfo->GetScreenIndex();
			}
		}
	}
}

void CScreenSetDlg::InitText()
{
	UpdataText1();

	InitText2();

	InitText3();

	if(m_nScreenModel==SCREENMODEL_MATRIX)
	{
		InitText4();

		InitText5();
	}	
}

void CScreenSetDlg::InitText2()
{
	if(m_nScreenIndex==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
		m_TextInfo2->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo2->SetText(szText);
	}
}

void CScreenSetDlg::InitText3()
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			if(!m_bIsTwoScreen)
			{
				CString szStr=m_pDelegate->GetTranslationString(_T("551"),_T("无"));
				m_TextInfo3->SetText(szStr);
			}
			else
			{
				if(m_nScreenIndex2==-1)
				{
					CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
					m_TextInfo3->SetText(szStr);
				}
				else
				{
					CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

					CString szScreenIndex;

					szScreenIndex.Format(_T("%d"),m_nScreenIndex2);

					CString szText=szStr2+szScreenIndex;

					m_TextInfo3->SetText(szText);
				}
			}
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			if(m_nScreenIndex2==-1)
			{
				CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
				m_TextInfo3->SetText(szStr);
			}
			else
			{
				CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

				CString szScreenIndex;

				szScreenIndex.Format(_T("%d"),m_nScreenIndex2);

				CString szText=szStr2+szScreenIndex;

				m_TextInfo3->SetText(szText);
			}
		}
		break;
	default:
		break;
	}
}

void CScreenSetDlg::InitText4()
{
	if(m_nScreenIndex3==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
		m_TextInfo4->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex3);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo4->SetText(szText);
	}
}

void CScreenSetDlg::InitText5()
{
	if(m_nScreenIndex4==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
		m_TextInfo5->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex4);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo5->SetText(szText);
	}
}

int CScreenSetDlg::GetScreenColumn()
{
	return m_nScreenColumn;
}

int CScreenSetDlg::GetScreenRow()
{
	return m_nScreenRow;
}

void CScreenSetDlg::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int CScreenSetDlg::GetBoardIndex()
{
	return m_nBoardIndex;
}

void CScreenSetDlg::SetIsTwoScreen(BOOL bIsTwoScreen)
{
	m_bIsTwoScreen=bIsTwoScreen;
}

BOOL CScreenSetDlg::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

void CScreenSetDlg::SetBeginScreenIndex(int n)
{
	m_nBeginScreenIndex=n;
}

int CScreenSetDlg::GetBeginScreenIndex()
{
	return m_nBeginScreenIndex;
}

void CScreenSetDlg::SetScreenModel(int nModel)
{
	m_nScreenModel=nModel;
}

int CScreenSetDlg::GetScreenModel()
{
	return m_nScreenModel;
}

void CScreenSetDlg::SetCorrpScreenNum(int n)
{
	m_nCorrScreenNum=n;
}

int CScreenSetDlg::GetCorrpScreenNum()
{
	return m_nCorrScreenNum;
}

VEC_SCREENINFO& CScreenSetDlg::GetVecScreenInfo()
{
	return m_VecScreenInfo;
}

void CScreenSetDlg::CreateScreenInfosWnd()
{
	CRect rect;

	GetDlgItem(IDC_STATIC_SCREENINFOWND)->GetWindowRect(rect);

	ScreenToClient(rect);

	m_pScreenInfosWnd = new XScreenInfosWnd();

	m_pScreenInfosWnd->SetDelegate(this);

	m_pScreenInfosWnd->Create(WS_CHILD|WS_VISIBLE, rect, this, 0/*ID_SCREENINFOSWND*/);

	m_pScreenInfosWnd->SetBoardIndex(m_nBoardIndex);

	m_pScreenInfosWnd->SetScreenModel(m_nScreenModel);

	m_pScreenInfosWnd->SetIsTwoScreen(m_bIsTwoScreen);

	m_pScreenInfosWnd->SetBeginScreenIndex(m_nBeginScreenIndex);

	m_pScreenInfosWnd->ShowWindow(SW_SHOW);

	m_pScreenInfosWnd->UpdateWindow();
}

void CScreenSetDlg::CreateText()
{
	CreateText1();

	CreateText2();

	CreateText3();

	if(m_nScreenModel==SCREENMODEL_MATRIX)
	{
		CreateText4();

		CreateText5();
	}
}

void CScreenSetDlg::CreateText1()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_CURPAN)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nLeft=rect.right;

	int nTop=rect.top-2;

	int nRight=nLeft+100;

	int nBottom=nTop+NFONTSIZE;

	CRect fontRect(nLeft,nTop,nRight,nBottom);

	HYXText* pText=new HYXText;
	pText->Create(WS_CHILD|WS_VISIBLE,fontRect,this,0);
	pText->SetTextColor(RGB(255,0,0));
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();

	m_TextInfo1=pText;
}

void CScreenSetDlg::CreateText2()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_FIRST)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nLeft=rect.right;

	int nTop=rect.top-2;

	int nRight=nLeft+50;

	int nBottom=nTop+NFONTSIZE;

	CRect fontRect(nLeft,nTop,nRight,nBottom);

	HYXText* pText=new HYXText;
	pText->Create(WS_CHILD|WS_VISIBLE,fontRect,this,0);
	pText->SetTextColor(RGB(255,0,0));
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();

	m_TextInfo2=pText;
}

void CScreenSetDlg::CreateText3()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_SECOND)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nLeft=rect.right;

	int nTop=rect.top-2;

	int nRight=nLeft+50;

	int nBottom=nTop+NFONTSIZE;

	CRect fontRect(nLeft,nTop,nRight,nBottom);

	HYXText* pText=new HYXText;
	pText->Create(WS_CHILD|WS_VISIBLE,fontRect,this,0);
	pText->SetTextColor(RGB(255,0,0));
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();

	m_TextInfo3=pText;
}

void CScreenSetDlg::CreateText4()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_THREE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nLeft=rect.right;

	int nTop=rect.top-2;

	int nRight=nLeft+50;

	int nBottom=nTop+NFONTSIZE;

	CRect fontRect(nLeft,nTop,nRight,nBottom);

	HYXText* pText=new HYXText;
	pText->Create(WS_CHILD|WS_VISIBLE,fontRect,this,0);
	pText->SetTextColor(RGB(255,0,0));
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();

	m_TextInfo4=pText;
}

void CScreenSetDlg::CreateText5()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_FOUR)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nLeft=rect.right;

	int nTop=rect.top-2;

	int nRight=nLeft+50;

	int nBottom=nTop+NFONTSIZE;

	CRect fontRect(nLeft,nTop,nRight,nBottom);

	HYXText* pText=new HYXText;
	pText->Create(WS_CHILD|WS_VISIBLE,fontRect,this,0);
	pText->SetTextColor(RGB(255,0,0));
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();

	m_TextInfo5=pText;
}


void CScreenSetDlg::UpdataText1()
{
	if(NULL==m_TextInfo1)
	{
		return;
	}

	CString szBoardIndex;
	szBoardIndex.Format(_T("%d"),m_nBoardIndex);

	CString szStr1=m_pDelegate->GetTranslationString(_T("606"),_T("第"));
	CString szStr2=m_pDelegate->GetTranslationString(_T("607"),_T("道"));
	CString szStr3=_T(" ");
	CString szStr4=m_pDelegate->GetTranslationString(_T("608"),_T("共"));

	CString szScreen;
	if(m_bIsTwoScreen)
	{
		szScreen.Format(_T("%d"),2);
	}
	else
	{
		szScreen.Format(_T("%d"),1);
	}

	CString szRoad=m_pDelegate->GetTranslationString(_T("609"),_T("路"));

	CString szText=szStr1+szBoardIndex+szStr2+szStr3
		+_T("(")+szStr4+szScreen+szRoad+_T(")");

	m_TextInfo1->SetText(szText);
}

void CScreenSetDlg::UpdataText2()
{
	if(m_nScreenIndex==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));

		m_TextInfo2->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo2->SetText(szText);
	}
}

void CScreenSetDlg::UpdataText3()
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			if(!m_bIsTwoScreen)
			{
				CString szStr=m_pDelegate->GetTranslationString(_T("551"),_T("无"));
				m_TextInfo3->SetText(szStr);
			}
			else
			{
				if(m_nScreenIndex==-1)
				{
					CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
					m_TextInfo3->SetText(szStr);
				}
				else
				{
					CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

					CString szScreenIndex;

					szScreenIndex.Format(_T("%d"),m_nScreenIndex);

					CString szText=szStr2+szScreenIndex;

					m_TextInfo3->SetText(szText);
				}
			}
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			if(m_nScreenIndex==-1)
			{
				CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
				m_TextInfo3->SetText(szStr);
			}
			else
			{
				CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

				CString szScreenIndex;

				szScreenIndex.Format(_T("%d"),m_nScreenIndex);

				CString szText=szStr2+szScreenIndex;

				m_TextInfo3->SetText(szText);
			}

		}
		break;
	default:
		break;
	}
}

void CScreenSetDlg::UpdataText4()
{
	if(m_nScreenIndex==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
		m_TextInfo4->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo4->SetText(szText);
	}
}

void CScreenSetDlg::UpdataText5()
{
	if(m_nScreenIndex==-1)
	{
		CString szStr=m_pDelegate->GetTranslationString(_T("610"),_T("未分配"));
		m_TextInfo5->SetText(szStr);
	}
	else
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("230"),_T("屏幕"));

		CString szScreenIndex;

		szScreenIndex.Format(_T("%d"),m_nScreenIndex);

		CString szText=szStr2+szScreenIndex;

		m_TextInfo5->SetText(szText);
	}
}

void CScreenSetDlg::ScreenInfoLBDblClk(XScreenInfo* pInfo)
{
	int nTempBoardIndex=pInfo->GetBoardIndex();

	int nNumOfScreen=pInfo->GetNumOfScreen();

	if(nTempBoardIndex==m_nBoardIndex)
	{
		m_nScreenIndex=-1;

		if(nNumOfScreen==0)
		{
			UpdataText2();
		}
		else if(nNumOfScreen==1)
		{
			UpdataText2();
		}
		else if(nNumOfScreen==2)
		{
			UpdataText3();
		}
		else if(nNumOfScreen==3)
		{
			UpdataText4();
		}
		else if(nNumOfScreen==4)
		{
			UpdataText5();
		}
	}

	m_pDelegate->SetVecBoard(pInfo);

	ClearVecScreenInfo();

	m_pDelegate->CopyVecBoardToVecScreeInfo(m_VecScreenInfo);

	m_pScreenInfosWnd->Invalidate();
}

void CScreenSetDlg::ScreenInfoLBtnDown(XScreenInfo* pInfo)
{
	int nTempBoardIndex=pInfo->GetBoardIndex();

	m_nScreenIndex=pInfo->GetScreenIndex();

	m_pDelegate->SetVecBoardOutpout(pInfo);

	ClearVecScreenInfo();

	m_pDelegate->CopyVecBoardToVecScreeInfo(m_VecScreenInfo);

	for(VEC_SCREENINFO::iterator iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		XScreenInfo* pInfo=*iter;

		if(m_nScreenIndex==pInfo->GetScreenIndex())
		{
			int nBoardIndex=pInfo->GetBoardIndex();

			int nNunOfScreen=pInfo->GetNumOfScreen();

			switch(m_nScreenModel)
			{
			case SCREENMODEL_SPLIC:
				{
					if(nBoardIndex!=0)
					{
						if(nNunOfScreen==0)
						{
							UpdataText2();
						}

						if(nNunOfScreen==1)
						{
							UpdataText2();
						}
						else if(nNunOfScreen==2)
						{
							UpdataText3();
						}
					}
				}
				break;
			case SCREENMODEL_MATRIX:
				{
					if(nBoardIndex!=0)
					{
						if(nNunOfScreen==0)
						{
							UpdataText2();
						}

						if(nNunOfScreen==1)
						{
							UpdataText2();
						}
						else if(nNunOfScreen==2)
						{
							UpdataText3();
						}
						else if(nNunOfScreen==3)
						{
							UpdataText4();
						}
						else if(nNunOfScreen==4)
						{
							UpdataText5();
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}

	m_pScreenInfosWnd->Invalidate();
}

BOOL CScreenSetDlg::CheckRepeat(int nScreenIndex)
{
	return m_pDelegate->CheckRepeat(nScreenIndex);
}

CString CScreenSetDlg::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

int CScreenSetDlg::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

void CScreenSetDlg::InitVecScreenData()
{
	ClearVecScreenInfo();

	int nCount = m_nScreenColumn * m_nScreenRow;

	m_VecScreenInfo.reserve(nCount);

	for(int i = 0; i < m_nScreenRow; i++)
	{
		for(int j = 0; j < m_nScreenColumn; j++)
		{
			XScreenInfo* pInfo = new XScreenInfo();

			m_VecScreenInfo.push_back(pInfo);
		}
	}
}

BOOL CScreenSetDlg::PreTranslateMessage(MSG* pMsg)
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
		default:
			break;
		}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

void CScreenSetDlg::OnBnClickedOk()
{
	int nSize=m_VecScreenInfo.size();

	m_pDelegate->UpdataImage(m_nBoardIndex);

	//if(m_pDelegate->GetIsMenuSet())
	//{
	m_pDelegate->UpdateText(m_nBoardIndex);
	//}

	m_pDelegate->SetVecScreenInfo(m_VecScreenInfo);

	CDialog::OnOK();
}