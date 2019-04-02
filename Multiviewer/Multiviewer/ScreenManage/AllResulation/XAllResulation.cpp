#include "stdafx.h"
#include "XAllResulation.h"
#include "..\resource.h"
#include "XResulationInfo.h"
#include "XScreenManage.h"
#include "XResulationCut.h"
#include "XResulationVCut.h"


IMPLEMENT_DYNAMIC(XAllResulution, CDialogEx)

	XAllResulution::XAllResulution(CWnd* pParent /*=NULL*/)
	: CDialogEx(XAllResulution::IDD, pParent)
{

}

XAllResulution::~XAllResulution()
{

}

void XAllResulution::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_Combo_Index);
	DDX_Control(pDX, IDC_COMBO_REFRESH, m_Combo_Refresh);
}

BEGIN_MESSAGE_MAP(XAllResulution, CDialogEx)
	ON_BN_CLICKED( IDC_BUTTON_OK, &XAllResulution::OnBtnOK)
	ON_BN_CLICKED(IDC_BUTTON_CENCLE, &XAllResulution::OnBtnCancle)
	ON_STN_CLICKED(IDC_STATIC_EXPAND, &XAllResulution::OnClickedExpand)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, &XAllResulution::OnSelchangeIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_REFRESH, &XAllResulution::OnSelchangeRefresh)
	ON_EN_CHANGE(IDC_EDIT_HRESULATION,&XAllResulution::OnResulationHChange)
	ON_EN_CHANGE(IDC_EDIT_VRESULATION,&XAllResulution::OnResulationVChange)
	ON_BN_CLICKED(IDC_CHECK_RCUT,&XAllResulution::OnSelRightCut)
	ON_BN_CLICKED(IDC_CHECK_BCUT,&XAllResulution::OnSelBottomCut)

END_MESSAGE_MAP()


void XAllResulution::SetDelegate(XDelegateAllResulution* p)
{
	m_Delegate=p;
}

void XAllResulution::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XAllResulution::SetScreen(XScreen*& p)
{
	m_pScreen=p;
}

BOOL XAllResulution::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	GetWindowRect(&m_Rect);

	GetDlgItem(IDC_STATIC_EXPAND)->GetWindowRect(&m_ExpaneRect);

	SetDialog();

	Init();

	GetDlgItem(IDC_CHECK_RCUT)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK_BCUT)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_RCUT)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_BCUT)->ShowWindow(FALSE);

	GetDlgItem(IDC_EDIT_HRESULATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_VRESULATION)->EnableWindow(FALSE);

	return FALSE; 
}

void XAllResulution::SetDialog()
{
	CRect rtSmall;
	rtSmall.SetRectEmpty();
	if (rtSmall.IsRectEmpty())
	{
		rtSmall.left = m_Rect.left;
		rtSmall.top = m_Rect.top;
		rtSmall.right = m_Rect.right;
		rtSmall.bottom = m_ExpaneRect.bottom+10;
	}
	SetWindowPos(NULL, 0, 0, rtSmall.Width(), rtSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
}

void XAllResulution::Init()
{
	InitCombo();

	InitShowData();
}

void XAllResulution::InitCombo()
{
	m_Combo_Index.AddString(_T("800*600"));
	m_Combo_Index.AddString(_T("1024*768"));
	m_Combo_Index.AddString(_T("1280*720"));
	m_Combo_Index.AddString(_T("1280*768"));
	m_Combo_Index.AddString(_T("1280*800"));
	m_Combo_Index.AddString(_T("1280*1024"));
	m_Combo_Index.AddString(_T("1360*768"));
	m_Combo_Index.AddString(_T("1366*768"));
	m_Combo_Index.AddString(_T("1440*900"));
	m_Combo_Index.AddString(_T("1440*1050"));
	m_Combo_Index.AddString(_T("1600*900"));
	m_Combo_Index.AddString(_T("1680*1050"));
	m_Combo_Index.AddString(_T("1920*1080"));
	m_Combo_Index.AddString(_T("1920*1200"));
	m_Combo_Index.SetCurSel(0);
	m_Combo_Refresh.AddString(_T("60"));
}

void XAllResulution::InitShowData()
{
	XAllResulationInfo* pInfo=m_pScreenManage->GetAllResulationInfo();

	m_Combo_Index.SetCurSel(pInfo->GetComboIndex());
	m_Combo_Refresh.SetCurSel(pInfo->GetComboRefresh());

	CString szTemp;
	szTemp.Format(_T("%d"), pInfo->GetResolutionH());
	GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetResolutionV());
	GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHFPorch());
	GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetVFPorch());
	GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHpixel());
	GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetVPixel());
	GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHBPorch());
	GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetVBProch());
	GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHSyncTime());
	GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetVSyncTime());
	GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetHSyncPolarity());
	GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(szTemp);

	szTemp.Format(_T("%d"), pInfo->GetVSyncPolarity());
	GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(szTemp);

	//TRACE(_T("nIndex=%d\n"),pInfo->GetComboIndex());

	XResulationHCutInfo* pHCutInfo=m_pScreenManage->GetResulationHCutInfo();
	int nHResulation=pHCutInfo->GetResulationCut();
	if(nHResulation==0)
		((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(FALSE);
	else
		((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(TRUE);

	XResulationVCutInfo* pVCutInfo=m_pScreenManage->GetResulationVCutInfo();
	int nVResulation=pVCutInfo->GetResulationCut();
	if(nVResulation==0)
		((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(FALSE);
	else
		((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(TRUE);
}

void XAllResulution::ReloadInterface()
{
	SetWindowText(m_Delegate->GetTranslationString(_T("400"), _T("设置屏幕分辨率")));

	GetDlgItem(IDC_STATIC_SCREENINDEX)->SetWindowText(m_Delegate->GetTranslationString(_T("401"),_T("分辨率序号"))+_T(":"));
	GetDlgItem(IDC_STATIC_RESULATIONX)->SetWindowText(m_Delegate->GetTranslationString(_T("402"),_T("水平分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_RESULATIONY)->SetWindowText(m_Delegate->GetTranslationString(_T("403"),_T("垂直分辨率"))+_T(":"));
	GetDlgItem(IDC_STATIC_EXPAND)->SetWindowText(m_Delegate->GetTranslationString(_T("404"),_T("高级设置"))+_T(">>"));
	GetDlgItem(IDC_STATIC_HPORCH)->SetWindowText(m_Delegate->GetTranslationString(_T("405"),_T("水平前沿"))+_T(":"));
	GetDlgItem(IDC_STATIC_HPOLARITY)->SetWindowText(m_Delegate->GetTranslationString(_T("406"),_T("水平活动像素"))+_T(":"));
	GetDlgItem(IDC_STATIC_HZONG)->SetWindowText(m_Delegate->GetTranslationString(_T("407"),_T("水平总数"))+_T(":"));
	GetDlgItem(IDC_STATIC_HWITH)->SetWindowText(m_Delegate->GetTranslationString(_T("408"),_T("水平同步宽度"))+_T(":"));
	GetDlgItem(IDC_STATIC_HSYNC)->SetWindowText(m_Delegate->GetTranslationString(_T("409"),_T("水平同步极性"))+_T(":"));
	GetDlgItem(IDC_STATIC_VPORCH)->SetWindowText(m_Delegate->GetTranslationString(_T("410"),_T("垂直前沿"))+_T(":"));
	GetDlgItem(IDC_STATIC_VPOLARIT)->SetWindowText(m_Delegate->GetTranslationString(_T("411"),_T("垂直活动像素"))+_T(":"));																																																																														
	GetDlgItem(IDC_STATIC_VZONG)->SetWindowText(m_Delegate->GetTranslationString(_T("412"),_T("垂直总数"))+_T(":"));
	GetDlgItem(IDC_STATIC_VWITH)->SetWindowText(m_Delegate->GetTranslationString(_T("413"),_T("垂直同步宽度"))+_T(":"));
	GetDlgItem(IDC_STATIC_VSYNC)->SetWindowText(m_Delegate->GetTranslationString(_T("414"),_T("垂直同步极性"))+_T(":"));
	GetDlgItem(IDC_STATIC_REFRESH)->SetWindowText(m_Delegate->GetTranslationString(_T("416"),_T("刷新频率"))+_T(":"));
	GetDlgItem(IDC_STATIC_RCUT)->SetWindowText(m_Delegate->GetTranslationString(_T("747"),_T("右侧剪切"))+_T(":"));
	GetDlgItem(IDC_STATIC_BCUT)->SetWindowText(m_Delegate->GetTranslationString(_T("748"),_T("底部剪切"))+_T(":"));
	//GetDlgItem(IDC_STATIC_TIPS101)->SetWindowText(m_Delegate->GetTranslationString(_T("752"),_T("提示:当右侧或底部屏幕分辨率不同时，设置右侧或底部剪切，如有需要，请先设置整体分辨率")));
	GetDlgItem(IDC_BUTTON_OK)->SetWindowText(m_Delegate->GetTranslationString(_T("208"),_T("确定")));
	GetDlgItem(IDC_BUTTON_CENCLE)->SetWindowText(m_Delegate->GetTranslationString(_T("209"),_T("取消")));  
}

void XAllResulution::OnResulationHChange()
{
	CString szResulationH;
	GetDlgItem(IDC_EDIT_HRESULATION)->GetWindowText(szResulationH);
	int nResulationH=_ttoi(szResulationH);

	int nFront=0;
	int nBack=0;
	int nTempResulation=0;

	int nResulationIndex=m_Combo_Index.GetCurSel();
	switch(nResulationIndex)
	{
	case 0:
		{
			nFront=44;
			nBack=88;
			nTempResulation=800;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 1:
		{
			nFront=24;
			nBack=160;
			nTempResulation=1024;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 2:
		{
			nFront=110;
			nBack=220;
			nTempResulation=1280;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 3:
		{
			nFront=64;
			nBack=192;
			nTempResulation=1280;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 4:
		{
			nFront=72;
			nBack=200;
			nTempResulation=1280;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 5:
		{
			nFront=48;
			nBack=248;
			nTempResulation=1280;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 6:
		{
			nFront=64;
			nBack=256;
			nTempResulation=1360;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 7:
		{
			nFront=70;
			nBack=213;
			nTempResulation=1366;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 8:
		{
			nFront=80;
			nBack=232;
			nTempResulation=1440;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 9:
		{
			nFront=80;
			nBack=232;
			nTempResulation=1440;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 10:
		{
			nFront=48;
			nBack=80;
			nTempResulation=1600;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 11:
		{
			nFront=104;
			nBack=280;
			nTempResulation=1680;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 12:
		{
			nFront=88;
			nBack=148;
			nTempResulation=1920;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	case 13:
		{
			nFront=48;
			nBack=80;
			nTempResulation=1920;

			ResulationHChange(nFront,nBack,nResulationH,nTempResulation);
		}
		break;
	default:
		break;
	}
}

void XAllResulution::ResulationHChange(int nFront,int nBack,int nChangeResulation,int nResResulation)
{
	if(nChangeResulation!=nResResulation)
	{
		SetControlStatus(CTRLSTATUS_CHANGE);

		int nTempChange=(nResResulation-nChangeResulation)/2;

		CString szChange;
		szChange.Format(_T("%d"),nChangeResulation);
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(szChange);

		CString szChangeFront;
		szChangeFront.Format(_T("%d"),nFront+nTempChange);
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(szChangeFront);

		CString szChangeBack;
		szChangeBack.Format(_T("%d"),nBack+nTempChange);
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(szChangeBack);
	}
	else
	{
		SetControlStatus(CTRLSTATUS_NOMAL);

		CString szChange;
		szChange.Format(_T("%d"),nChangeResulation);
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(szChange);

		CString szChangeFront;
		szChangeFront.Format(_T("%d"),nFront);
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(szChangeFront);

		CString szChangeBack;
		szChangeBack.Format(_T("%d"),nBack);
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(szChangeBack);
	}
}

void XAllResulution::OnResulationVChange()
{
	CString szResulationV;
	GetDlgItem(IDC_EDIT_VRESULATION)->GetWindowText(szResulationV);
	int nResulationV=_ttoi(szResulationV);

	int nFront=0;
	int nBack=0;
	int nTempResulation=0;

	int nResulationIndex=m_Combo_Index.GetCurSel();
	switch(nResulationIndex)
	{
	case 0:
		{
			nFront=1;
			nBack=23;
			nTempResulation=600;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 1:
		{
			nFront=3;
			nBack=29;
			nTempResulation=768;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 2:
		{
			nFront=5;
			nBack=20;
			nTempResulation=720;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 3:
		{
			nFront=3;
			nBack=20;
			nTempResulation=768;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 4:
		{
			nFront=3;
			nBack=22;
			nTempResulation=800;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 5:
		{
			nFront=48;
			nBack=248;
			nTempResulation=1024;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 6:
		{
			nFront=1;
			nBack=38;
			nTempResulation=768;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 7:
		{
			nFront=3;
			nBack=24;
			nTempResulation=768;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 8:
		{
			nFront=3;
			nBack=25;
			nTempResulation=900;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 9:
		{
			nFront=3;
			nBack=32;
			nTempResulation=1050;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 10:
		{
			nFront=3;
			nBack=18;
			nTempResulation=900;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 11:
		{
			nFront=3;
			nBack=30;
			nTempResulation=1050;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 12:
		{
			nFront=4;
			nBack=36;
			nTempResulation=1080;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	case 13:
		{
			nFront=3;
			nBack=26;
			nTempResulation=1200;

			ResulationVChange(nFront,nBack,nResulationV,nTempResulation);
		}
		break;
	default:
		break;
	}
}

void XAllResulution::ResulationVChange(int nFront,int nBack,int nChangeResulation,int nResResulation)
{
	if(nChangeResulation!=nResResulation)
	{
		SetControlStatus(CTRLSTATUS_CHANGE);

		int nTempChange=(nResResulation-nChangeResulation)/2;

		CString szChange;
		szChange.Format(_T("%d"),nChangeResulation);
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(szChange);

		CString szChangeFront;
		szChangeFront.Format(_T("%d"),nFront+nTempChange);
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(szChangeFront);

		CString szChangeBack;
		szChangeBack.Format(_T("%d"),nBack+nTempChange);
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(szChangeBack);
	}
	else
	{
		SetControlStatus(CTRLSTATUS_NOMAL);

		CString szChange;
		szChange.Format(_T("%d"),nChangeResulation);
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(szChange);

		CString szChangeFront;
		szChangeFront.Format(_T("%d"),nFront);
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(szChangeFront);

		CString szChangeBack;
		szChangeBack.Format(_T("%d"),nBack);
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(szChangeBack);
	}
}

void XAllResulution::SetControlStatus(CTRLSTATUS type)
{
	switch(type)
	{
	case CTRLSTATUS_NOMAL:
		{
			GetDlgItem(IDC_COMBO_INDEX)->EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_REFRESH)->EnableWindow(TRUE);

			//GetDlgItem(IDC_CHECK_RCUT)->EnableWindow(FALSE);
			//GetDlgItem(IDC_CHECK_BCUT)->EnableWindow(FALSE);
		}
		break;
	case CTRLSTATUS_CHANGE:
		{
			GetDlgItem(IDC_COMBO_INDEX)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_REFRESH)->EnableWindow(FALSE);

			//GetDlgItem(IDC_CHECK_RCUT)->EnableWindow(TRUE);
			//GetDlgItem(IDC_CHECK_BCUT)->EnableWindow(TRUE);
		}
		break;
	default:
		break;
	}
}

XResulationHCutInfo* XAllResulution::GetResulationHCutInfo()
{
	return &m_ResulationHInfo;
}

XResulationVCutInfo* XAllResulution::GetResulationVCutInfo()
{
	return &m_ResulationVInfo;
}

void XAllResulution::OnSelRightCut()
{
	int nResulationIndex=m_Combo_Index.GetCurSel();
	//////////////////////////////////////////////////////////////////////////
	CString szHResulation;
	GetDlgItem(IDC_EDIT_HRESULATION)->GetWindowText(szHResulation);
	szHResulation.Trim();
	if(szHResulation==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("417"),_T("水平分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HRESULATION)->SetFocus();
		return;
	}
	int nResolutionH=_ttoi(szHResulation);
	//////////////////////////////////////////////////////////////////////////
	CString szHFProch;
	GetDlgItem(IDC_EDIT_HPORCH)->GetWindowText(szHFProch);
	if(szHFProch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("420"),_T("水平前沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HPORCH)->SetFocus();
		return;
	}
	int nHFPorch=_ttoi(szHFProch);
	//////////////////////////////////////////////////////////////////////////
	CString szHpixel;
	GetDlgItem(IDC_EDIT_HPOLARITY)->GetWindowText(szHpixel);
	if(szHpixel==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("422"),_T("水平活动像素不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetFocus();
		return;
	}
	int nHpixel=_ttoi(szHpixel);
	//////////////////////////////////////////////////////////////////////////
	CString szHBForch;
	GetDlgItem(IDC_EDIT_HTOTAL)->GetWindowText(szHBForch);
	if(szHBForch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("424"),_T("水平后沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HTOTAL)->SetFocus();
		return;
	}
	int nHBPorch=_ttoi(szHBForch);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncTime;
	GetDlgItem(IDC_EDIT_HWITH)->GetWindowText(szHSyncTime);
	if(szHSyncTime==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("426"),_T("水平同步宽度不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HWITH)->SetFocus();
		return;
	}
	int nHSyncTime=_ttoi(szHSyncTime);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncPolarity;
	GetDlgItem(IDC_EDIT_HSYNC)->GetWindowText(szHSyncPolarity);
	if(szHSyncPolarity==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("428"),_T("水平同步极性不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HSYNC)->SetFocus();
		return;
	}
	int nHSyncPolarity=_ttoi(szHSyncPolarity);

	//////////////////////////////////////////////////////////////////////////
	XResulationHCutInfo* pInfo=GetResulationHCutInfo();
	pInfo->SetResulationH(nResolutionH);
	pInfo->SetHFront(nHFPorch);
	pInfo->SetHActive(nHpixel);
	pInfo->SetHBack(nHBPorch);
	pInfo->SetHSyn(nHSyncTime);
	pInfo->SetHPolarity(nHSyncPolarity);
	//////////////////////////////////////////////////////////////////////////
	
	XResulationCut dlg;
	dlg.SetParent(this);
	dlg.SetScreenManage(m_pScreenManage);
	dlg.SetResulationIndex(nResulationIndex);

	dlg.DoModal();
}

void XAllResulution::SetRCutStatus(BOOL b)
{
	((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(b);
}

void XAllResulution::OnSelBottomCut()
{
	int nResulationIndex=m_Combo_Index.GetCurSel();
	//////////////////////////////////////////////////////////////////////////
	CString szVResulation;
	GetDlgItem(IDC_EDIT_VRESULATION)->GetWindowText(szVResulation);
	szVResulation.Trim();
	if(szVResulation==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("419"),_T("垂直分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VRESULATION)->SetFocus();
		return;
	}
	int nResolutionV=_ttoi(szVResulation);
	//////////////////////////////////////////////////////////////////////////
	CString szVFPorch;
	GetDlgItem(IDC_EDIT_VPORCH)->GetWindowText(szVFPorch);
	if(szVFPorch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("421"),_T("垂直前沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VPORCH)->SetFocus();
		return;
	}
	int nVFPorch=_ttoi(szVFPorch);
	//////////////////////////////////////////////////////////////////////////
	CString szVpixel;
	GetDlgItem(IDC_EDIT_VPOLARITY)->GetWindowText(szVpixel);
	if(szVpixel==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("423"),_T("垂直活动像素不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetFocus();
		return;
	}
	int nVPixel=_ttoi(szVpixel);
	//////////////////////////////////////////////////////////////////////////
	CString szVBForch;
	GetDlgItem(IDC_EDIT_VTOTAL)->GetWindowText(szVBForch);
	if(szVBForch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("425"),_T("垂直后沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VTOTAL)->SetFocus();
		return;
	}
	int nVBProch=_ttoi(szVBForch);
	//////////////////////////////////////////////////////////////////////////
	CString szVSyncTime;
	GetDlgItem(IDC_EDIT_VWITH)->GetWindowText(szVSyncTime);
	if(szVSyncTime==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("427"),_T("垂直同步宽度不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VWITH)->SetFocus();
		return;
	}
	int nVSyncTime=_ttoi(szVSyncTime);
	//////////////////////////////////////////////////////////////////////////
	CString szVSyncPolarity;
	GetDlgItem(IDC_EDIT_VSYNC)->GetWindowText(szVSyncPolarity);
	if(szVSyncPolarity==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("429"),_T("垂直同步极性不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VSYNC)->SetFocus();
		return;
	}
	int nVSyncPolarity=_ttoi(szVSyncPolarity);

	//////////////////////////////////////////////////////////////////////////
	XResulationVCutInfo* pInfo=GetResulationVCutInfo();
	pInfo->SetResulationV(nResolutionV);
	pInfo->SetVFront(nVFPorch);
	pInfo->SetVActive(nVPixel);
	pInfo->SetVBack(nVBProch);
	pInfo->SetVSyn(nVSyncTime);
	pInfo->SetVPolarity(nVSyncPolarity);
	//////////////////////////////////////////////////////////////////////////

	XResulationVCut dlg;
	dlg.SetParent(this);
	dlg.SetScreenManage(m_pScreenManage);
	dlg.SetResulationIndex(nResulationIndex);

	dlg.DoModal();
}

void XAllResulution::SetBCutStatus(BOOL b)
{
	((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(b);
}

void XAllResulution::OnBtnOK()
{
	SetScreenResulationInfo();

	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();

	int nRCutStatus=((CButton*)GetDlgItem(IDC_CHECK_RCUT))->GetCheck();
	if(nRCutStatus)
	{
		XResulationHCutInfo* pCutInfo=m_pScreenManage->GetResulationHCutInfo();
		//////////////////////////////////////////////////////////////////////////
		XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();
		pAllInfo->SetRightCut(pCutInfo->GetResulationH());
		pAllInfo->SetIsRight(nRCutStatus);
		//////////////////////////////////////////////////////////////////////////
		for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			if(pScreen->GetIsRight())
			{
				//设置屏幕默认分辨率
				pScreen->SetScreenHdpi(pCutInfo->GetResulationH());

				XAllResulationInfo* pInfo=pScreen->GetAllResulationInfo();
				pInfo->SetResolutionH(pCutInfo->GetResulationH());
				pInfo->SetHFPorch(pCutInfo->GetHFront());
				pInfo->SetHpixel(pCutInfo->GetHActive());
				pInfo->SetHBPorch(pCutInfo->GetHBack());
				pInfo->SetHSyncTime(pCutInfo->GetHSyn());
				pInfo->SetHSyncPolarity(pCutInfo->GetHPolarity());
			}
		}
	}

	int nBCutStatus=((CButton*)GetDlgItem(IDC_CHECK_BCUT))->GetCheck();
	if(nBCutStatus)
	{
		XResulationVCutInfo* pCutInfo=m_pScreenManage->GetResulationVCutInfo();
		//////////////////////////////////////////////////////////////////////////
		XAllResulationInfo* pAllInfo=m_pScreenManage->GetAllResulationInfo();
		pAllInfo->SetBottomCut(pCutInfo->GetResulationV());
		pAllInfo->SetIsBottom(nBCutStatus);
		//////////////////////////////////////////////////////////////////////////
		for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			if(pScreen->GetIsBottom())
			{
				//设置屏幕默认分辨率
				pScreen->SetScreenVdpi(pCutInfo->GetResulationV());

				XAllResulationInfo* pInfo=pScreen->GetAllResulationInfo();
				pInfo->SetResolutionV(pCutInfo->GetResulationV());
				pInfo->SetVFPorch(pCutInfo->GetVFront());
				pInfo->SetVPixel(pCutInfo->GetVActive());
				pInfo->SetVBProch(pCutInfo->GetVBack());
				pInfo->SetVSyncTime(pCutInfo->GetVSyn());
				pInfo->SetVSyncPolarity(pCutInfo->GetVPolarity());
			}
		}
	}

	CDialogEx::OnOK();
}

void XAllResulution::SetScreenResulationInfo()
{
	int nComboIndex=m_Combo_Index.GetCurSel();
	int nComboRefresh=m_Combo_Refresh.GetCurSel();
	//////////////////////////////////////////////////////////////////////////
	CString szHResulation;
	GetDlgItem(IDC_EDIT_HRESULATION)->GetWindowText(szHResulation);
	szHResulation.Trim();
	if(szHResulation==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("417"),_T("水平分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HRESULATION)->SetFocus();
		return;
	}
	int nResolutionH=_ttoi(szHResulation);
	//////////////////////////////////////////////////////////////////////////
	CString szVResulation;
	GetDlgItem(IDC_EDIT_VRESULATION)->GetWindowText(szVResulation);
	szVResulation.Trim();
	if(szVResulation==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("419"),_T("垂直分辨率不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VRESULATION)->SetFocus();
		return;
	}
	int nResolutionV=_ttoi(szVResulation);
	//////////////////////////////////////////////////////////////////////////
	CString szHFProch;
	GetDlgItem(IDC_EDIT_HPORCH)->GetWindowText(szHFProch);
	if(szHFProch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("420"),_T("水平前沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HPORCH)->SetFocus();
		return;
	}
	int nHFPorch=_ttoi(szHFProch);
	//////////////////////////////////////////////////////////////////////////
	CString szVFPorch;
	GetDlgItem(IDC_EDIT_VPORCH)->GetWindowText(szVFPorch);
	if(szVFPorch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("421"),_T("垂直前沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VPORCH)->SetFocus();
		return;
	}
	int nVFPorch=_ttoi(szVFPorch);
	//////////////////////////////////////////////////////////////////////////
	CString szHpixel;
	GetDlgItem(IDC_EDIT_HPOLARITY)->GetWindowText(szHpixel);
	if(szHpixel==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("422"),_T("水平活动像素不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetFocus();
		return;
	}
	int nHpixel=_ttoi(szHpixel);
	//////////////////////////////////////////////////////////////////////////
	CString szVpixel;
	GetDlgItem(IDC_EDIT_VPOLARITY)->GetWindowText(szVpixel);
	if(szVpixel==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("423"),_T("垂直活动像素不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetFocus();
		return;
	}
	int nVPixel=_ttoi(szVpixel);
	//////////////////////////////////////////////////////////////////////////
	CString szHBForch;
	GetDlgItem(IDC_EDIT_HTOTAL)->GetWindowText(szHBForch);
	if(szHBForch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("424"),_T("水平后沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HTOTAL)->SetFocus();
		return;
	}
	int nHBPorch=_ttoi(szHBForch);
	//////////////////////////////////////////////////////////////////////////
	CString szVBForch;
	GetDlgItem(IDC_EDIT_VTOTAL)->GetWindowText(szVBForch);
	if(szVBForch==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("425"),_T("垂直后沿不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VTOTAL)->SetFocus();
		return;
	}
	int nVBProch=_ttoi(szVBForch);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncTime;
	GetDlgItem(IDC_EDIT_HWITH)->GetWindowText(szHSyncTime);
	if(szHSyncTime==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("426"),_T("水平同步宽度不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HWITH)->SetFocus();
		return;
	}
	int nHSyncTime=_ttoi(szHSyncTime);
	//////////////////////////////////////////////////////////////////////////
	CString szVSyncTime;
	GetDlgItem(IDC_EDIT_VWITH)->GetWindowText(szVSyncTime);
	if(szVSyncTime==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("427"),_T("垂直同步宽度不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VWITH)->SetFocus();
		return;
	}
	int nVSyncTime=_ttoi(szVSyncTime);
	//////////////////////////////////////////////////////////////////////////
	CString szHSyncPolarity;
	GetDlgItem(IDC_EDIT_HSYNC)->GetWindowText(szHSyncPolarity);
	if(szHSyncPolarity==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("428"),_T("水平同步极性不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_HSYNC)->SetFocus();
		return;
	}
	int nHSyncPolarity=_ttoi(szHSyncPolarity);
	//////////////////////////////////////////////////////////////////////////
	CString szVSyncPolarity;
	GetDlgItem(IDC_EDIT_VSYNC)->GetWindowText(szVSyncPolarity);
	if(szVSyncPolarity==_T(""))
	{
		m_Delegate->MessageBoxFromKey(_T("429"),_T("垂直同步极性不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_VSYNC)->SetFocus();
		return;
	}
	int nVSyncPolarity=_ttoi(szVSyncPolarity);
	//////////////////////////////////////////////////////////////////////////
	if(m_Combo_Index.GetCurSel()==0)
	{
		if(nResolutionH!=800&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("水平分辨率不能超过高级选项中的水平活动像素，请重新设置！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==1)
	{
		if(nResolutionH!=1024&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("水平分辨率不能超过高级选项中的水平活动像素，请重新设置！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==2||m_Combo_Index.GetCurSel()==3
		||m_Combo_Index.GetCurSel()==4||m_Combo_Index.GetCurSel()==5)
	{
		if(nResolutionH!=1280&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==6)
	{
		if(nResolutionH!=1360&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==7)
	{
		if(nResolutionH!=1366&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==8||m_Combo_Index.GetCurSel()==9)
	{
		if(nResolutionH!=1440&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==10)
	{
		if(nResolutionH!=1400&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==11)
	{
		if(nResolutionH!=1680&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==12||m_Combo_Index.GetCurSel()==13)
	{
		if(nResolutionH!=1920&&nResolutionH>nHpixel)
		{
			m_Delegate->MessageBoxFromKey(_T("418"),_T("请设置高级选项中的水平活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	////////////////////////////////////////////////////////////////////////
	if(m_Combo_Index.GetCurSel()==0)
	{
		if(nResolutionV!=600&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==1||m_Combo_Index.GetCurSel()==3
		||m_Combo_Index.GetCurSel()==6||m_Combo_Index.GetCurSel()==7)
	{
		if(nResolutionV!=768&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==2)
	{
		if(nResolutionV!=720&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==4)
	{
		if(nResolutionV!=800&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==5)
	{
		if(nResolutionV!=1024&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==8||m_Combo_Index.GetCurSel()==10)
	{
		if(nResolutionV!=900&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==9||m_Combo_Index.GetCurSel()==11)
	{
		if(nResolutionV!=1050&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==12)
	{
		if(nResolutionV!=1080&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	else if(m_Combo_Index.GetCurSel()==13)
	{
		if(nResolutionV!=1200&&nResolutionV>nVPixel)
		{
			m_Delegate->MessageBoxFromKey(_T("430"),_T("请设置高级选项中的垂直活动像素以及其他参数！"),MB_OK);
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	XAllResulationInfo* pInfo=m_pScreenManage->GetAllResulationInfo();
	pInfo->SetResolutionH(nResolutionH);
	pInfo->SetResolutionV(nResolutionV);
	pInfo->SetHFPorch(nHFPorch);
	pInfo->SetVFPorch(nVFPorch);
	pInfo->SetHSyncTime(nHSyncTime);
	pInfo->SetVSyncTime(nVSyncTime);
	pInfo->SetHBPorch(nHBPorch);
	pInfo->SetVBProch(nVBProch);
	pInfo->SetHSyncPolarity(nHSyncPolarity);
	pInfo->SetVSyncPolarity(nVSyncPolarity);
	pInfo->SetHpixel(nHpixel);
	pInfo->SetVPixel(nVPixel);
	pInfo->SetComboIndex(nComboIndex);
	pInfo->SetComboRefresh(nComboRefresh);
	pInfo->SetRightCut(nResolutionH);
	pInfo->SetBottomCut(nResolutionV);
	//////////////////////////////////////////////////////////////////////////
	VEC_SCREEN& VecScreen=m_pScreenManage->GetVecScreen();
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		XResulationInfo* pInfo=pScreen->GetResulationInfo();
		pInfo->SetResolutionH(nResolutionH);
		pInfo->SetResolutionV(nResolutionV);
		pInfo->SetHFPorch(nHFPorch);
		pInfo->SetVFPorch(nVFPorch);
		pInfo->SetHSyncTime(nHSyncTime);
		pInfo->SetVSyncTime(nVSyncTime);
		pInfo->SetHBPorch(nHBPorch);
		pInfo->SetVBProch(nVBProch);
		pInfo->SetHSyncPolarity(nHSyncPolarity);
		pInfo->SetVSyncPolarity(nVSyncPolarity);
		pInfo->SetHpixel(nHpixel);
		pInfo->SetVPixel(nVPixel);
		pInfo->SetComboIndex(nComboIndex);
		pInfo->SetComboRefresh(nComboRefresh);

		//设置屏幕默认分辨率
		pScreen->SetScreenHdpi(nResolutionH);
		pScreen->SetScreenVdpi(nResolutionV);
	}
}

void XAllResulution::OnBtnCancle()
{
	CDialogEx::OnCancel();
}

void XAllResulution::OnClickedExpand()
{
	CString str;

	GetDlgItemText(IDC_STATIC_EXPAND,str);

	if(str==_T("高级选项>>"))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("高级选项<<"));
	}
	else if(str==_T("高级选项<<"))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("高级选项>>"));
	}
	if(str==(_T("Advanced settings>>")))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("Advanced settings<<"));
	}
	else if(str==(_T("Advanced settings<<")))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("Advanced settings>>"));
	}
	if(str==(_T("高級選項>>")))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("高級選項<<"));
	}
	else if(str==(_T("高級選項<<")))
	{
		SetDlgItemText(IDC_STATIC_EXPAND,_T("高級選項>>"));
	}

	CRect rtSmall;
	rtSmall.SetRectEmpty();
	if (rtSmall.IsRectEmpty())
	{
		rtSmall.left = m_Rect.left;
		rtSmall.top = m_Rect.top;
		rtSmall.right = m_Rect.right;
		rtSmall.bottom = m_ExpaneRect.bottom+10;
	}

	if(str==_T("高级选项<<"))
	{
		SetWindowPos(NULL, 0, 0, rtSmall.Width(), rtSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	if(str==_T("高级选项>>"))
	{
		SetWindowPos(NULL, 0, 0, m_Rect.Width(), m_Rect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	if(str==_T("Advanced settings<<"))
	{
		SetWindowPos(NULL, 0, 0, rtSmall.Width(), rtSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	if(str==_T("Advanced settings>>"))
	{
		SetWindowPos(NULL, 0, 0, m_Rect.Width(), m_Rect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	if(str==_T("高級選項<<"))
	{
		SetWindowPos(NULL, 0, 0, rtSmall.Width(), rtSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	if(str==_T("高級選項>>"))
	{
		SetWindowPos(NULL, 0, 0, m_Rect.Width(), m_Rect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}

void XAllResulution::OnSelchangeIndex()
{
	int nIndex=m_Combo_Index.GetCurSel();

	SetCheckBoxStatus(nIndex);

	if(nIndex==0)//800 600
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		//SetCheckBoxStatus(nIndex);

		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("800"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("600"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("40"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("800"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("600"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("88"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("23"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("128"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("4"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==1)//1024 768
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////


		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1024"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("24"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1024"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("160"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("29"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("136"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("0"));
	}
	else if(nIndex==2)//1280 720
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.AddString(_T("50"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////


		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("720"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("110"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("5"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("720"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("220"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("20"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("40"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==3)//1280 768
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("64"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("192"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("20"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("112"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==4)//1280 800
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("800"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("72"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("800"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("200"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("22"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("128"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==5)//1280 1024
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("1024"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("48"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1280"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1024"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("248"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("38"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("112"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==6)//1360 768
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1360"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("64"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1360"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("256"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("18"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("112"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==7)//1366 768
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1366"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("70"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1366"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("768"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("213"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("24"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("143"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("13"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==8)//1440 900
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1440"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("900"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("80"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1440"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("900"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("232"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("25"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("152"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==9)//1440 1050
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1440"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("1050"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("80"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1440"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1050"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("232"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("32"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("144"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("4"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==10)//1600 900
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1600"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("900"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("48"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1600"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("900"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("80"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("18"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("32"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("0"));
	}
	else if(nIndex==11)//1680 1050
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1680"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("1050"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("104"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1680"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1050"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("280"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("30"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("176"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("0"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==12)//1920 1080
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.AddString(_T("50"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1920"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("1080"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("88"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("4"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1080"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("148"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("36"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("44"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
	}
	else if(nIndex==13)//1920 1200
	{
		m_Combo_Refresh.ResetContent();
		m_Combo_Refresh.AddString(_T("60"));
		m_Combo_Refresh.SetCurSel(0);
		//////////////////////////////////////////////////////////////////////////
		GetDlgItem(IDC_EDIT_HRESULATION)->SetWindowText(_T("1920"));
		GetDlgItem(IDC_EDIT_VRESULATION)->SetWindowText(_T("1200"));
		GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("48"));
		GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("3"));
		GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
		GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1200"));
		GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("80"));
		GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("26"));
		GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("32"));
		GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("6"));
		GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
		GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("0"));
	}
}

void XAllResulution::SetCheckBoxStatus(int nComboxIndex)
{
	XResulationHCutInfo* pInfoR=m_pScreenManage->GetResulationHCutInfo();
	int nResulationIndexR=pInfoR->GetResulationIndex();
	int nResulationRCut=pInfoR->GetResulationCut();

	XResulationVCutInfo* pInfoB=m_pScreenManage->GetResulationVCutInfo();
	int nResulationIndexB=pInfoB->GetResulationIndex();
	int nResulationBCut=pInfoB->GetResulationCut();
			
	if(nComboxIndex==nResulationIndexR)
	{
		if(nResulationRCut!=0)
			((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_RCUT))->SetCheck(FALSE);
	}
	
	if(nComboxIndex==nResulationIndexB)
	{
		if(nResulationBCut!=0)
			((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_BCUT))->SetCheck(FALSE);
	}
}

void XAllResulution::OnSelchangeRefresh()
{
	CString nSelectStr=_T("");
	m_Combo_Refresh.GetLBText(m_Combo_Refresh.GetCurSel(),nSelectStr);

	if(m_Combo_Index.GetCurSel()==2)
	{
		if(nSelectStr==_T("60"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("110"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("720"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("220"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("20"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("40"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
		else if(nSelectStr==_T("50"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("440"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("720"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("220"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("20"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("40"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
	}

	if(m_Combo_Index.GetCurSel()==12)
	{
		if(nSelectStr==_T("60"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("88"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("4"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("148"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("36"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("44"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
		else if(nSelectStr==_T("50"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("528"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("4"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("148"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("36"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("44"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
		else if(nSelectStr==_T("30"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("88"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("4"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("148"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("36"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("44"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
		else if (nSelectStr==_T("25"))
		{
			GetDlgItem(IDC_EDIT_HPORCH)->SetWindowText(_T("528"));
			GetDlgItem(IDC_EDIT_VPORCH)->SetWindowText(_T("4"));
			GetDlgItem(IDC_EDIT_HPOLARITY)->SetWindowText(_T("1920"));
			GetDlgItem(IDC_EDIT_VPOLARITY)->SetWindowText(_T("1080"));
			GetDlgItem(IDC_EDIT_HTOTAL)->SetWindowText(_T("148"));
			GetDlgItem(IDC_EDIT_VTOTAL)->SetWindowText(_T("36"));
			GetDlgItem(IDC_EDIT_HWITH)->SetWindowText(_T("44"));
			GetDlgItem(IDC_EDIT_VWITH)->SetWindowText(_T("5"));
			GetDlgItem(IDC_EDIT_HSYNC)->SetWindowText(_T("1"));
			GetDlgItem(IDC_EDIT_VSYNC)->SetWindowText(_T("1"));
		}
	}
}
