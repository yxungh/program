#include "stdafx.h"
#include "XSetPreviewBoard.h"
#include "afxdialogex.h"
#include "XDelegateSetPreviewBoard.h"
#include "XInternalManage.h"




// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XSetPreviewBoard, CDialogEx)

	XSetPreviewBoard::XSetPreviewBoard(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetPreviewBoard::IDD, pParent)
{
	m_pDelegate = NULL;
}

XSetPreviewBoard::~XSetPreviewBoard()
{

}

void XSetPreviewBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSetPreviewBoard, CDialogEx)
	ON_BN_CLICKED(IDOK, &XSetPreviewBoard::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XSetPreviewBoard::SetDelegate(XDelegateSetPreviewBoard* p)
{
	m_pDelegate = p;
}

void XSetPreviewBoard::SetBaseManage(XInternalManage* p)
{
	m_pBaseManage=p;
}

BOOL XSetPreviewBoard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitData();

	InitChildDlg();

	return FALSE;  
}

void XSetPreviewBoard::InitChildDlg()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_PREVIEWBOARD)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_PreviewDlg.Create(IDD_DIALOG_PREVIEWCHILD,this);
	m_PreviewDlg.SetPreviewParent(this);
	m_PreviewDlg.SetBaseManage(m_pBaseManage);
	m_PreviewDlg.SetDelegate((XDelegatePreviewChild*)m_pBaseManage);
	m_PreviewDlg.MoveWindow(&rect);
	m_PreviewDlg.Init();
	m_PreviewDlg.ShowWindow(TRUE);
}

void XSetPreviewBoard::InitData()
{
	//VEC_PREVIEWBOARD& VecPreviewBoard=m_PreviewDlg.GetVecPreviewBoard();
	//if(VecPreviewBoard.size()==0)
	//{
	//	GetDlgItem(IDOK)->ShowWindow(FALSE);
	//	GetDlgItem(IDCANCEL)->ShowWindow(FALSE);
	//	GetDlgItem(IDC_STATIC_TIPS100)->ShowWindow(FALSE);
	//}
	//else
	//{
	//	GetDlgItem(IDOK)->ShowWindow(TRUE);
	//	GetDlgItem(IDCANCEL)->ShowWindow(TRUE);
	//	GetDlgItem(IDC_STATIC_TIPS100)->ShowWindow(TRUE);
	//}
}

void XSetPreviewBoard::SetButtonStatus(BOOL b)
{
	GetDlgItem(IDOK)->ShowWindow(b);
	GetDlgItem(IDCANCEL)->ShowWindow(b);
	GetDlgItem(IDC_STATIC_TIPS100)->ShowWindow(b);

	GetDlgItem(IDC_STATIC_TIPS101)->ShowWindow(!b);
}

void XSetPreviewBoard::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("681"), _T("配置预览卡")));
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("214"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"),_T("取消")));	
	GetDlgItem(IDC_STATIC_TIPS100)->SetWindowText(m_pDelegate->GetTranslationString(_T("691"),_T("提示:单击选中，双击取消选中，右键或点击设置按钮配置预览卡")));
	GetDlgItem(IDC_STATIC_TIPS101)->SetWindowText(m_pDelegate->GetTranslationString(_T("761"),_T("没有检测到预览卡！")));
}

void XSetPreviewBoard::OnBnClickedOk()
{
	VEC_PREVIEWBOARD& VecPreviewBoard=m_PreviewDlg.GetVecPreviewBoard();

	m_pBaseManage->CopySelectedBoardInfo(VecPreviewBoard);

	m_pBaseManage->SetPreviewPane();

	CDialogEx::OnOK();
}


void XSetPreviewBoard::OnSplitNetSet()
{
	m_PreviewDlg.OnSplitNetSet();
}

void XSetPreviewBoard::OnSplitBiteRate()
{
	m_PreviewDlg.OnSplitBiteRate();
}

void XSetPreviewBoard::OperateOfReadPreviewNet(char* pData)
{
	m_PreviewDlg.OperateOfReadPreviewNet(pData);
}

void XSetPreviewBoard::OperateOfReadPreviewBitRate(char* pData)
{
	m_PreviewDlg.OperateOfReadPreviewBitRate(pData);
}