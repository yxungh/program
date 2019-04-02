// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XSetColResoluation.h"
#include "XDelegateSetColResoluation.h"
#include "../XConstant.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "XResulationInfo.h"

// XSetColResoluation 对话框

IMPLEMENT_DYNAMIC(XSetColResoluation, CDialogEx)

	XSetColResoluation::XSetColResoluation(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetColResoluation::IDD, pParent)
{
	m_Delegate = NULL;
	m_pScreenManage=NULL;
	m_pScreen=NULL;
}

XSetColResoluation::~XSetColResoluation()
{
}

void XSetColResoluation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSetColResoluation, CDialogEx)
	ON_BN_CLICKED(IDOK, &XSetColResoluation::OnBtnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CURSHUIPING,&XSetColResoluation::OnSelDpiChange)
END_MESSAGE_MAP()


// XSetColResoluation 消息处理程序
BOOL XSetColResoluation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void XSetColResoluation::SetDelegate(XDelegateSetColResoluation* p)
{
	m_Delegate = p;
}

void XSetColResoluation::Init()
{
	InitData();

	ReloadInterface();
}

void XSetColResoluation::InitData()
{
	XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();

	int nCurHdpi=pAllInfo->GetResolutionH();
	CString szCurHdpi;
	szCurHdpi.Format(_T("%d"),nCurHdpi);
	GetDlgItem(IDC_EDIT_JICHU)->SetWindowText(szCurHdpi);
	//////////////////////////////////////////////////////////////////////////
	int nCurScreenHDpi=m_pScreen->GetScreenHdpi();

	CString szCurScreenHDpi;
	szCurScreenHDpi.Format(_T("%d"),nCurScreenHDpi);
	GetDlgItem(IDC_EDIT_CURSHUIPING)->SetWindowText(szCurScreenHDpi);

	XResulationInfo* pInfo=m_pScreen->GetResulationInfo();

	CString szHFproch;
	szHFproch.Format(_T("%d"),pInfo->GetHFPorch());
	GetDlgItem(IDC_EDIT_SHUIQIAN)->SetWindowText(szHFproch);

	CString szHPixel;
	szHPixel.Format(_T("%d"),pInfo->GetHpixel());
	GetDlgItem(IDC_EDIT_SHUIHUOXIANG)->SetWindowText(szHPixel);

	CString szHBproch;
	szHBproch.Format(_T("%d"),pInfo->GetHBPorch());
	GetDlgItem(IDC_EDIT_SHUIHOU)->SetWindowText(szHBproch);

	CString szHSysnWidth;
	szHSysnWidth.Format(_T("%d"),pInfo->GetHSyncTime());
	GetDlgItem(IDC_EDIT_SHUITONGKUAN)->SetWindowText(szHSysnWidth);

	CString szHSyncPolarity;
	szHSyncPolarity.Format(_T("%d"),pInfo->GetHSyncPolarity());
	GetDlgItem(IDC_EDIT_SHUITONGJI)->SetWindowText(szHSyncPolarity);
}

void XSetColResoluation::ReloadInterface()
{
	SetWindowText(m_pScreenManage->GetTranslationString(_T("768"),_T("设置列分辨率")));

	GetDlgItem(IDC_STATIC_JICHU)->SetWindowText(m_pScreenManage->GetTranslationString(_T("766"),_T("基础分辨率")));
	GetDlgItem(IDC_STATIC_CURSHUIPING)->SetWindowText(m_pScreenManage->GetTranslationString(_T("769"),_T("当前水平分辨率")));
	GetDlgItem(IDC_STATIC_SHUIQIAN)->SetWindowText(m_pScreenManage->GetTranslationString(_T("405"),_T("水平前沿")));
	GetDlgItem(IDC_STATIC_SHUIHUOXIANG)->SetWindowText(m_pScreenManage->GetTranslationString(_T("406"),_T("水平活动像素")));
	GetDlgItem(IDC_STATIC_SHUIHOU)->SetWindowText(m_pScreenManage->GetTranslationString(_T("407"),_T("水平后沿")));
	GetDlgItem(IDC_STATIC_SHUITONGKUAN)->SetWindowText(m_pScreenManage->GetTranslationString(_T("408"),_T("水平同步宽度")));
	GetDlgItem(IDC_STATIC_SHUITONGJI)->SetWindowText(m_pScreenManage->GetTranslationString(_T("409"),_T("水平同步极性")));
	GetDlgItem(IDC_STATIC_COL)->SetWindowText(m_pScreenManage->GetTranslationString(_T("771"),_T("提示:只用于设置该列非标准水平分辨率，必须先选择基础分辨率!")));


}

void XSetColResoluation::OnBtnClickedOk()
{
	//////////////////////////////////////////////////////////////////////////
	CString szSetHDpi;
	GetDlgItem(IDC_EDIT_CURSHUIPING)->GetWindowText(szSetHDpi);
	szSetHDpi.Trim();
	int nSetHDpi=_ttoi(szSetHDpi);

	//////////////////////////////////////////////////////////////////////////
	CString szFront;
	GetDlgItem(IDC_EDIT_SHUIQIAN)->GetWindowText(szFront);
	szFront.Trim();
	int nFront=_ttoi(szFront);
	//////////////////////////////////////////////////////////////////////////
	CString szActive;
	GetDlgItem(IDC_EDIT_SHUIHUOXIANG)->GetWindowText(szActive);
	szActive.Trim();
	int nActive=_ttoi(szActive);
	//////////////////////////////////////////////////////////////////////////
	CString szBack;
	GetDlgItem(IDC_EDIT_SHUIHOU)->GetWindowText(szBack);
	szBack.Trim();
	int nBack=_ttoi(szBack);
	//////////////////////////////////////////////////////////////////////////
	CString szSyncWidth;
	GetDlgItem(IDC_EDIT_SHUITONGKUAN)->GetWindowText(szSyncWidth);
	szSyncWidth.Trim();
	int nSyncWidth=_ttoi(szSyncWidth);
	//////////////////////////////////////////////////////////////////////////
	CString szSyncPol;
	GetDlgItem(IDC_EDIT_SHUITONGJI)->GetWindowText(szSyncPol);
	szSyncPol.Trim();
	int nSyncPol=_ttoi(szSyncPol);
	//////////////////////////////////////////////////////////////////////////

	XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();
	pAllInfo->SetRightCut(nActive);
	//////////////////////////////////////////////////////////////////////////
	//设置行屏幕参数
	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetScreenCol()==m_pScreen->GetScreenCol())
		{
			XResulationInfo* pInfo=pScreen->GetResulationInfo();

			pInfo->SetResolutionH(nActive);
			pInfo->SetCurDpi(nSetHDpi);
			pInfo->SetHFPorch(nFront);
			pInfo->SetHpixel(nActive);
			pInfo->SetHBPorch(nBack);
			pInfo->SetHSyncTime(nSyncWidth);
			pInfo->SetHSyncPolarity(nSyncPol);

			pScreen->SetScreenHdpi(nActive);
		}
	}

	CDialogEx::OnOK();
}

void XSetColResoluation::OnSelDpiChange()
{
	XAllResulationInfo* pInfo=m_pScreenManage->GetAllResulationInfo();	
	int nFront=pInfo->GetHFPorch();
	int nBack=pInfo->GetHBPorch();

	//////////////////////////////////////////////////////////////////////////
	CString szSetHDpi;
	GetDlgItem(IDC_EDIT_CURSHUIPING)->GetWindowText(szSetHDpi);
	szSetHDpi.Trim();
	int nSetHDpi=_ttoi(szSetHDpi);
	//////////////////////////////////////////////////////////////////////////
	//基础分辨率
	CString szCurHDpi;
	GetDlgItem(IDC_EDIT_JICHU)->GetWindowText(szCurHDpi);
	szCurHDpi.Trim();
	int nCurHDpi=_ttoi(szCurHDpi);
	//////////////////////////////////////////////////////////////////////////
	int nTemp=(nCurHDpi-nSetHDpi)/2;
	//////////////////////////////////////////////////////////////////////////

	CString szPlus;
	szPlus.Format(_T("%d"),nFront+nTemp);
	GetDlgItem(IDC_EDIT_SHUIQIAN)->SetWindowText(szPlus);

	szPlus.Format(_T("%d"),nBack+nTemp);
	GetDlgItem(IDC_EDIT_SHUIHOU)->SetWindowText(szPlus);

	szPlus.Format(_T("%d"),nSetHDpi);
	GetDlgItem(IDC_EDIT_SHUIHUOXIANG)->SetWindowText(szPlus);
}