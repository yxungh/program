// ViewPreviewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ViewPreviewDlg.h"
#include "afxdialogex.h"
#include "XVideoPreviewPane.h"
#include "XDelegateVideoPreviewPane.h"
#include "XMultiVideoWindow.h"

// CViewPreviewDlg 对话框

#define FRAMESINDEX 1002

IMPLEMENT_DYNAMIC(CViewPreviewDlg, CDialogEx)

CViewPreviewDlg::CViewPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewPreviewDlg::IDD, pParent)
{
	m_Pane = NULL;

	m_InitDlg = FALSE;

	m_pMultiVideoWindow=NULL;
}

CViewPreviewDlg::~CViewPreviewDlg()
{
	DestroyWindow();
}

void CViewPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CViewPreviewDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CViewPreviewDlg 消息处理程序
BOOL CViewPreviewDlg::PreTranslateMessage(MSG* pMsg)
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

	return __super::PreTranslateMessage(pMsg);
}

BOOL CViewPreviewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTitle();

	m_InitDlg = TRUE;

	return FALSE;  
}

void CViewPreviewDlg::SetPane(XVideoPreviewPane* p)
{
	m_Pane = p;
}

void CViewPreviewDlg::SetIP(CString szIP)
{
	m_szIP=szIP;
}

void CViewPreviewDlg::SetRTSPAddr(CString szRTSPAddr)
{
	m_szRTSPAddr=szRTSPAddr;
}

void CViewPreviewDlg::SetInputIndex(int nIndex)
{
	m_nIndex=nIndex;
}

void CViewPreviewDlg::SetUserName(CString szName)
{
	m_szName=szName;
}

void CViewPreviewDlg::SetPassWord(CString szPassWd)
{
	m_szPassWd=szPassWd;
}

void CViewPreviewDlg::Init()
{
	CreateRTSPAddr();

	ClearFrame();

	AddFrame();
}

void CViewPreviewDlg::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_pMultiVideoWindow=p;
}

void CViewPreviewDlg::CreateRTSPAddr()
{
	m_VecRTSPAddr.clear();

	m_Pane->CreateRTSPAddr(m_szIP,m_szName,m_szPassWd,m_VecRTSPAddr);
}

void CViewPreviewDlg::AddFrame()
{
	BOOL bIsUltra=FALSE,bIsHaveSignal=FALSE,bIsHavePane=FALSE;
	m_Pane->AdjustInputStatus(m_nIndex,bIsUltra,bIsHaveSignal,bIsHavePane);

	CRect rect;
	GetClientRect(&rect);

	RECTF rectF;
	rectF.X=rect.left;
	rectF.Y=rect.top;
	rectF.Width=rect.Width();
	rectF.Height=rect.Height();

	//TRACE("X=%f,Y=%f,W=%f,H=%f\n",rectF.X,rectF.Y,rectF.Width,rectF.Height);

	RECTF InterRect(0,0,1920,1088);

	if(bIsUltra)
	{
		if(bIsHaveSignal&&bIsHavePane)
		{
			VEC_RECTF VecRect;
			m_Pane->SetRectToFoure(rectF,VecRect);

			int i=0;
			for(VEC_RECTF::iterator iter=VecRect.begin();iter!=VecRect.end();++iter)
			{
				RECTF rect1=*iter;
				CString szRTSP=m_VecRTSPAddr[i];
				CString szMainRTSPAddr=m_Pane->GetMainRTSPBySubRTSP(szRTSP);
				m_Pane->AddRTSPAddr(szMainRTSPAddr);

				XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szMainRTSPAddr,rect1,InterRect);
			}
		}
	}
	else
	{
		if(bIsHaveSignal&&bIsHavePane)
		{
			CString szMainRTSPAddr=m_Pane->GetMainRTSPBySubRTSP(m_szRTSPAddr);
			m_Pane->AddRTSPAddr(szMainRTSPAddr);
			
			XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(FRAMESINDEX,szMainRTSPAddr,rectF,InterRect);
		}
	}
}

void CViewPreviewDlg::SetTitle()
{
	SetWindowText(m_Pane->GetDelegate()->GetTranslationString(_T("694"), _T("高清预览")));
}

void CViewPreviewDlg::Hide()
{
	ShowWindow(SW_HIDE);

	CString szMainRTSPAddr=m_Pane->GetMainRTSPBySubRTSP(m_szRTSPAddr);
	m_Pane->DeleteRTSP(szMainRTSPAddr);

	for(VEC_CSTRING::iterator iter=m_VecRTSPAddr.begin();iter!=m_VecRTSPAddr.end();++iter)
	{
		CString szRTSP=*iter;

		CString szMainRTSPAddr=m_Pane->GetMainRTSPBySubRTSP(szRTSP);

		m_Pane->DeleteRTSP(szMainRTSPAddr);
	}
}

void CViewPreviewDlg::OnCancel()
{
	Hide();
}

void CViewPreviewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_InitDlg)
	{
		AdjustLayoutDlg();

		m_Pane->GetDelegate()->AdjustMultiVideoWindowHWNDSize(m_pMultiVideoWindow,rect.Width(),rect.Height());
	}
}

void CViewPreviewDlg::ClearFrame()
{
	if(m_pMultiVideoWindow==NULL)
	{
		return;
	}

	m_pMultiVideoWindow->DeleteFrame(FRAMESINDEX);
}

void CViewPreviewDlg::AdjustLayoutDlg()
{
	ClearFrame();

	AddFrame();
}

void CViewPreviewDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (m_InitDlg)
	{
		lpMMI->ptMinTrackSize.x = 200;

		lpMMI->ptMinTrackSize.y = 132;
	}

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


