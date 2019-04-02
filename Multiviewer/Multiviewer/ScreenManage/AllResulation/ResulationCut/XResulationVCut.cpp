#include "stdafx.h"
#include "XResulationVCut.h"
#include "..\resource.h"
#include "XScreenManage.h"
#include "XScreen.h"
#include "XAllResulation.h"
#include "XResulationVCutInfo.h"


IMPLEMENT_DYNAMIC(XResulationVCut, CDialogEx)

	XResulationVCut::XResulationVCut(CWnd* pParent /*=NULL*/)
	: CDialogEx(XResulationVCut::IDD, pParent)
{
	m_pAllResulation=NULL;
	m_pScreen=NULL;
	m_pScreenManage=NULL;
	m_nResulationIndex=0;
}

XResulationVCut::~XResulationVCut()
{

}

void XResulationVCut::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(XResulationVCut, CDialogEx)
	ON_BN_CLICKED(IDOK,&XResulationVCut::OnBtnOK)
	ON_BN_CLICKED(IDCANCEL,&XResulationVCut::OnBtnCancel)
	ON_EN_CHANGE(IDC_EDIT_RCUT,&XResulationVCut::OnSelRightCut)

END_MESSAGE_MAP()



void XResulationVCut::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XResulationVCut::SetScreen(XScreen*& p)
{
	m_pScreen=p;
}

void XResulationVCut::SetParent(XAllResulution* p)
{
	m_pAllResulation=p;
}

void XResulationVCut::SetResulationIndex(int n)
{
	m_nResulationIndex=n;
}

BOOL XResulationVCut::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	Init();

	InitDate();

	return FALSE; 
}

void XResulationVCut::Init()
{

}

void XResulationVCut::InitDate()
{
	XResulationVCutInfo* pInfo=m_pScreenManage->GetResulationVCutInfo();
	int nResulationIndex=pInfo->GetResulationIndex();

	XResulationVCutInfo* pInfoOther=m_pAllResulation->GetResulationVCutInfo();

	CString szTemp;

	if(nResulationIndex!=-1
		&&nResulationIndex==m_nResulationIndex)
	{
		CString szTemp;

		szTemp.Format(_T("%d"), pInfo->GetResulationV());
		GetDlgItem(IDC_EDIT_CUR)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetResulationCut());
		GetDlgItem(IDC_EDIT_RCUT)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetVFront());
		GetDlgItem(IDC_EDIT_FRONT)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetVActive());
		GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetVBack());
		GetDlgItem(IDC_EDIT_BACK)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetVSyn());
		GetDlgItem(IDC_EDIT_SYN)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfo->GetVPolarity());
		GetDlgItem(IDC_EDIT_POLARITY)->SetWindowText(szTemp);
	}
	else
	{
		CString szTemp;

		szTemp.Format(_T("%d"), pInfoOther->GetResulationV());
		GetDlgItem(IDC_EDIT_CUR)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), 0);
		GetDlgItem(IDC_EDIT_RCUT)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfoOther->GetVFront());
		GetDlgItem(IDC_EDIT_FRONT)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfoOther->GetVActive());
		GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfoOther->GetVBack());
		GetDlgItem(IDC_EDIT_BACK)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfoOther->GetVSyn());
		GetDlgItem(IDC_EDIT_SYN)->SetWindowText(szTemp);

		szTemp.Format(_T("%d"), pInfoOther->GetVPolarity());
		GetDlgItem(IDC_EDIT_POLARITY)->SetWindowText(szTemp);
	}
}

void XResulationVCut::ReloadInterface()
{
	SetWindowText(m_pScreenManage->GetTranslationString(_T("748"), _T("底部剪切")));

	GetDlgItem(IDC_STATIC_CURH)->SetWindowText(m_pScreenManage->GetTranslationString(_T("403"),_T("垂直分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_RCUT)->SetWindowText(m_pScreenManage->GetTranslationString(_T("749"),_T("剪切分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_FRONT)->SetWindowText(m_pScreenManage->GetTranslationString(_T("410"),_T("垂直前沿"))+_T(":"));
	GetDlgItem(IDC_STATIC_ACTIVE)->SetWindowText(m_pScreenManage->GetTranslationString(_T("411"),_T("垂直活动像素"))+_T(":"));
	GetDlgItem(IDC_STATIC_BACK)->SetWindowText(m_pScreenManage->GetTranslationString(_T("412"),_T("垂直总数"))+_T(":"));
	GetDlgItem(IDC_STATIC_SYN)->SetWindowText(m_pScreenManage->GetTranslationString(_T("413"),_T("垂直同步宽度"))+_T(":"));
	GetDlgItem(IDC_STATIC_POLARITY)->SetWindowText(m_pScreenManage->GetTranslationString(_T("414"),_T("垂直同步极性"))+_T(":"));
	GetDlgItem(IDC_STATIC_TIPS103)->SetWindowText(m_pScreenManage->GetTranslationString(_T("751"),_T("提示:剪切分辨率为底部屏幕垂直分辨率小于正常屏幕分辨率时剪掉的分辨率")));
	GetDlgItem(IDOK)->SetWindowText(m_pScreenManage->GetTranslationString(_T("208"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pScreenManage->GetTranslationString(_T("209"),_T("取消")));  
}

void XResulationVCut::OnSelRightCut()
{
	XResulationVCutInfo* pInfo=m_pAllResulation->GetResulationVCutInfo();	
	int nCur=pInfo->GetResulationV();
	int nFront=pInfo->GetVFront();
	int nBack=pInfo->GetVBack();
	int nActive=pInfo->GetVActive();

	CString szCut;
	GetDlgItem(IDC_EDIT_RCUT)->GetWindowText(szCut);
	int nCut=_ttoi(szCut);

	int nTempResulation=nCur-nCut;
	int nTemp=nCut/2;

	CString szActive;
	szActive.Format(_T("%d"),nTempResulation);
	GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(szActive);

	CString szChange;
	szChange.Format(_T("%d"),nTempResulation);
	GetDlgItem(IDC_EDIT_CUR)->SetWindowText(szChange);

	CString szChangeFront;
	szChangeFront.Format(_T("%d"),nFront+nTemp);
	GetDlgItem(IDC_EDIT_FRONT)->SetWindowText(szChangeFront);

	CString szChangeBack;
	szChangeBack.Format(_T("%d"),nBack+nTemp);
	GetDlgItem(IDC_EDIT_BACK)->SetWindowText(szChangeBack);
}

void XResulationVCut::OnBtnOK()
{
	CString szHResulation;
	GetDlgItem(IDC_EDIT_CUR)->GetWindowText(szHResulation);
	szHResulation.Trim();
	if(szHResulation==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("417"),_T("水平分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_CUR)->SetFocus();
		return;
	}
	int nResolutionH=_ttoi(szHResulation);
	//////////////////////////////////////////////////////////////////////////
	CString szResulationCut;
	GetDlgItem(IDC_EDIT_RCUT)->GetWindowText(szResulationCut);
	szResulationCut.Trim();
	//if(szHResulation==_T(""))
	//{
	//	m_pScreenManage->MessageBoxFromKey(_T("417"),_T("水平分辨率不能为空！"),MB_OK);
	//	GetDlgItem(IDC_EDIT_CUR)->SetFocus();
	//	return;
	//}
	int nResulationCut=_ttoi(szResulationCut);
	//////////////////////////////////////////////////////////////////////////
	CString szHFProch;
	GetDlgItem(IDC_EDIT_FRONT)->GetWindowText(szHFProch);
	if(szHFProch==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("420"),_T("水平前沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_FRONT)->SetFocus();
		return;
	}
	int nHFPorch=_ttoi(szHFProch);
	//////////////////////////////////////////////////////////////////////////
	CString szHpixel;
	GetDlgItem(IDC_EDIT_ACTIVE)->GetWindowText(szHpixel);
	if(szHpixel==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("422"),_T("水平活动像素不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_ACTIVE)->SetFocus();
		return;
	}
	int nHpixel=_ttoi(szHpixel);
	//////////////////////////////////////////////////////////////////////////
	CString szHBForch;
	GetDlgItem(IDC_EDIT_BACK)->GetWindowText(szHBForch);
	if(szHBForch==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("424"),_T("水平后沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_BACK)->SetFocus();
		return;
	}
	int nHBPorch=_ttoi(szHBForch);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncTime;
	GetDlgItem(IDC_EDIT_SYN)->GetWindowText(szHSyncTime);
	if(szHSyncTime==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("426"),_T("水平同步宽度不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_SYN)->SetFocus();
		return;
	}
	int nHSyncTime=_ttoi(szHSyncTime);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncPolarity;
	GetDlgItem(IDC_EDIT_POLARITY)->GetWindowText(szHSyncPolarity);
	if(szHSyncPolarity==_T(""))
	{
		m_pScreenManage->MessageBoxFromKey(_T("428"),_T("水平同步极性不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_POLARITY)->SetFocus();
		return;
	}
	int nHSyncPolarity=_ttoi(szHSyncPolarity);

	//////////////////////////////////////////////////////////////////////////
	XResulationVCutInfo* pInfo=m_pScreenManage->GetResulationVCutInfo();
	pInfo->SetResulationV(nResolutionH);
	pInfo->SetVFront(nHFPorch);
	pInfo->SetVActive(nHpixel);
	pInfo->SetVBack(nHBPorch);
	pInfo->SetVSyn(nHSyncTime);
	pInfo->SetVPolarity(nHSyncPolarity);
	pInfo->SetResulationCut(nResulationCut);
	pInfo->SetResulationIndex(m_nResulationIndex);
	//////////////////////////////////////////////////////////////////////////
	CString szRCut;
	GetDlgItem(IDC_EDIT_RCUT)->GetWindowText(szRCut);
	int nRCut=_ttoi(szRCut);

	if(nRCut==0)
		m_pAllResulation->SetBCutStatus(FALSE);
	else
		m_pAllResulation->SetBCutStatus(TRUE);

	CDialogEx::OnOK();
}

void XResulationVCut::OnBtnCancel()
{
	//m_pAllResulation->SetBCutStatus(FALSE);
	CString szRCut;
	GetDlgItem(IDC_EDIT_RCUT)->GetWindowText(szRCut);
	int nRCut=_ttoi(szRCut);


	if(nRCut==0)
		m_pAllResulation->SetBCutStatus(FALSE);
	else
		m_pAllResulation->SetBCutStatus(TRUE);

	CDialogEx::OnCancel();
}
