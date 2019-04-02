// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XSetRowResoluation.h"
#include "XDelegateSetRowResoluation.h"
#include "../XConstant.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "XResulationInfo.h"

// XSetRowResoluation 对话框

IMPLEMENT_DYNAMIC(XSetRowResoluation, CDialogEx)

	XSetRowResoluation::XSetRowResoluation(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetRowResoluation::IDD, pParent)
{
	m_Delegate = NULL;
	m_pScreenManage=NULL;
	m_pScreen=NULL;
}

XSetRowResoluation::~XSetRowResoluation()
{
}

void XSetRowResoluation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSetRowResoluation, CDialogEx)
	ON_BN_CLICKED(IDOK, &XSetRowResoluation::OnBtnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SETVDPI,&XSetRowResoluation::OnSelDpiChange)
END_MESSAGE_MAP()


// XSetRowResoluation 消息处理程序
BOOL XSetRowResoluation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void XSetRowResoluation::SetDelegate(XDelegateSetRowResoluation* p)
{
	m_Delegate = p;
}

void XSetRowResoluation::Init()
{
	InitData();

	ReloadInterface();
}

void XSetRowResoluation::InitData()
{
	XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();

	int nCurVdpi=pAllInfo->GetResolutionV();
	CString szCurVdpi;
	szCurVdpi.Format(_T("%d"),nCurVdpi);
	GetDlgItem(IDC_EDIT_CURCHUI)->SetWindowText(szCurVdpi);
	//////////////////////////////////////////////////////////////////////////
	int nCurScreenVDpi=m_pScreen->GetScreenVdpi();

	CString szCurScreenVDpi;
	szCurScreenVDpi.Format(_T("%d"),nCurScreenVDpi);
	GetDlgItem(IDC_EDIT_SETVDPI)->SetWindowText(szCurScreenVDpi);

	XResulationInfo* pInfo=m_pScreen->GetResulationInfo();

	CString szVFproch;
	szVFproch.Format(_T("%d"),pInfo->GetVFPorch());
	GetDlgItem(IDC_EDIT_CHUIQIAN)->SetWindowText(szVFproch);

	CString szVPixel;
	szVPixel.Format(_T("%d"),pInfo->GetVPixel());
	GetDlgItem(IDC_EDIT_CHUIHUOXIANG)->SetWindowText(szVPixel);

	CString szVBproch;
	szVBproch.Format(_T("%d"),pInfo->GetVBProch());
	GetDlgItem(IDC_EDIT_CHUIHOU)->SetWindowText(szVBproch);

	CString szVSysnWidth;
	szVSysnWidth.Format(_T("%d"),pInfo->GetVSyncTime());
	GetDlgItem(IDC_EDIT_CHUITONGKUAN)->SetWindowText(szVSysnWidth);

	CString szVSyncPolarity;
	szVSyncPolarity.Format(_T("%d"),pInfo->GetVSyncPolarity());
	GetDlgItem(IDC_EDIT_CHUITONGJI)->SetWindowText(szVSyncPolarity);
}

void XSetRowResoluation::ReloadInterface()
{
	SetWindowText(m_pScreenManage->GetTranslationString(_T("764"),_T("设置行分辨率")));

	GetDlgItem(IDC_STATIC_CUR)->SetWindowText(m_pScreenManage->GetTranslationString(_T("766"),_T("基础分辨率")));
	GetDlgItem(IDC_STATIC_SETVDPI)->SetWindowText(m_pScreenManage->GetTranslationString(_T("765"),_T("当前垂直分辨率")));
	GetDlgItem(IDC_STATIC_CHUIQIAN)->SetWindowText(m_pScreenManage->GetTranslationString(_T("410"),_T("垂直前沿")));
	GetDlgItem(IDC_STATIC_CHUIHUOXIANG)->SetWindowText(m_pScreenManage->GetTranslationString(_T("411"),_T("垂直活动像素")));
	GetDlgItem(IDC_STATIC_CHUIHOU)->SetWindowText(m_pScreenManage->GetTranslationString(_T("412"),_T("垂直后沿")));
	GetDlgItem(IDC_STATIC_CHUITONGKUAN)->SetWindowText(m_pScreenManage->GetTranslationString(_T("413"),_T("垂直同步宽度")));
	GetDlgItem(IDC_STATIC_CHUITONGJI)->SetWindowText(m_pScreenManage->GetTranslationString(_T("414"),_T("垂直同步极性")));
	GetDlgItem(IDC_STATIC_ROW)->SetWindowText(m_pScreenManage->GetTranslationString(_T("770"),_T("提示:只用于设置该行非标准垂直分辨率，必须先选择基础分辨率！")));

}

void XSetRowResoluation::OnBtnClickedOk()
{
	//////////////////////////////////////////////////////////////////////////
	CString szSetVDpi;
	GetDlgItem(IDC_EDIT_SETVDPI)->GetWindowText(szSetVDpi);
	szSetVDpi.Trim();
	int nSetVDpi=_ttoi(szSetVDpi);

	//////////////////////////////////////////////////////////////////////////
	CString szFront;
	GetDlgItem(IDC_EDIT_CHUIQIAN)->GetWindowText(szFront);
	szFront.Trim();
	int nFront=_ttoi(szFront);
	//////////////////////////////////////////////////////////////////////////
	CString szActive;
	GetDlgItem(IDC_EDIT_CHUIHUOXIANG)->GetWindowText(szActive);
	szActive.Trim();
	int nActive=_ttoi(szActive);
	//////////////////////////////////////////////////////////////////////////
	CString szBack;
	GetDlgItem(IDC_EDIT_CHUIHOU)->GetWindowText(szBack);
	szBack.Trim();
	int nBack=_ttoi(szBack);
	//////////////////////////////////////////////////////////////////////////
	CString szSyncWidth;
	GetDlgItem(IDC_EDIT_CHUITONGKUAN)->GetWindowText(szSyncWidth);
	szSyncWidth.Trim();
	int nSyncWidth=_ttoi(szSyncWidth);
	//////////////////////////////////////////////////////////////////////////
	CString szSyncPol;
	GetDlgItem(IDC_EDIT_CHUITONGKUAN)->GetWindowText(szSyncPol);
	szSyncPol.Trim();
	int nSyncPol=_ttoi(szSyncPol);
	//////////////////////////////////////////////////////////////////////////

	XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();
	pAllInfo->SetBottomCut(nActive);

	//////////////////////////////////////////////////////////////////////////
	//设置行屏幕参数
	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetScreenRow()==m_pScreen->GetScreenRow())
		{
			XResulationInfo* pInfo=pScreen->GetResulationInfo();

			pInfo->SetResolutionV(nActive);
			pInfo->SetCurDpi(nSetVDpi);
			pInfo->SetVFPorch(nFront);
			pInfo->SetVPixel(nActive);
			pInfo->SetVBProch(nBack);
			pInfo->SetVSyncTime(nSyncWidth);
			pInfo->SetVSyncPolarity(nSyncPol);

			pScreen->SetScreenVdpi(nActive);
		}
	}

	CDialogEx::OnOK();
}

void XSetRowResoluation::OnSelDpiChange()
{
	XAllResulationInfo* pInfo=m_pScreenManage->GetAllResulationInfo();	
	int nFront=pInfo->GetVFPorch();
	int nBack=pInfo->GetVBProch();

	//////////////////////////////////////////////////////////////////////////
	CString szSetVDpi;
	GetDlgItem(IDC_EDIT_SETVDPI)->GetWindowText(szSetVDpi);
	szSetVDpi.Trim();
	int nSetVDpi=_ttoi(szSetVDpi);
	//////////////////////////////////////////////////////////////////////////
	//基础分辨率
	CString szCurVDpi;
	GetDlgItem(IDC_EDIT_CUR)->GetWindowText(szCurVDpi);
	szCurVDpi.Trim();
	int nCurVDpi=_ttoi(szCurVDpi);
	//////////////////////////////////////////////////////////////////////////
	int nTemp=(nCurVDpi-nSetVDpi)/2;
	//////////////////////////////////////////////////////////////////////////

	CString szPlus;
	szPlus.Format(_T("%d"),nFront+nTemp);
	GetDlgItem(IDC_EDIT_CHUIQIAN)->SetWindowText(szPlus);

	szPlus.Format(_T("%d"),nBack+nTemp);
	GetDlgItem(IDC_EDIT_CHUIHOU)->SetWindowText(szPlus);

	szPlus.Format(_T("%d"),nSetVDpi);
	GetDlgItem(IDC_EDIT_CHUIHUOXIANG)->SetWindowText(szPlus);
}