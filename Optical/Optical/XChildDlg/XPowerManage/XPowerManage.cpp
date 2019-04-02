// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XBtn.h"
#include "XText.h"
#include "XPowerManage.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XHandleCalculate.h"
#include "XTranslationManage.h"
#include "XDelegatePowerManage.h"
#include "XTranslationManage.h"
#include "XPowerManageItem.h"
#include "XLogin.h"
#include "XLoginLoad.h"
#include "XUserManage.h"
#include "XConstant.h"
#include "XMessageBox.h"
#include "XLoginInfo.h"
#include "XJsonManage.h"
#include "XSendDataManage.h"
#include "XResult.h"


// XPowerManage 对话框
IMPLEMENT_DYNAMIC(XPowerManage, XChildDialog)

	XPowerManage::XPowerManage(CWnd* pParent)
	: XChildDialog(XPowerManage::IDD, pParent),
	m_pDelegate(NULL),
	m_pLoginBtn(NULL),
	m_pLoginText(NULL),
	m_pLogin(NULL),
	m_pLoginLoad(NULL),
	m_szLoginUserName(_T("")),
	m_szLoginPassWd(_T("")),
	m_dLoginTime(0)
{
	m_rtBtn.SetRectEmpty();
}

XPowerManage::~XPowerManage()
{
	ClearItem();
	ClearLoginBtn();
	ClearLoginText();
}

void XPowerManage::ClearLoginBtn()
{
	RELEASE(m_pLoginBtn);
}

void XPowerManage::ClearLoginText()
{
	RELEASE(m_pLoginText);
}

void XPowerManage::ClearItem()
{
	for(auto iter=m_VecPowerManageItem.begin();iter!=m_VecPowerManageItem.end();++iter)
	{
		delete *iter;
	}

	m_VecPowerManageItem.clear();
}

void XPowerManage::DoDataExchange(CDataExchange* pDX)
{
	XChildDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XPowerManage, XChildDialog)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// XPowerManage 消息处理程序

BOOL XPowerManage::OnInitDialog()
{
	XChildDialog::OnInitDialog();

	InitLoginText();

	InitLoginBtn();

	ReloadInterface();

	return TRUE;
}

void XPowerManage::SetDelegate(XDelegatePowerManage* p)
{
	m_pDelegate=p;
}

void XPowerManage::InitLoginText()
{
	CRect rect;
	GetClientRect(&rect);

	int nWight=600;
	int nHight=40;

	int nX=rect.left+100;
	int nY=rect.top+100;

	CRect rtText(nX,nY,nX+nWight,nY+nHight);

	m_rtBtn=rtText;

	XText* pLoginText=new XText;
	pLoginText->Create(WS_CHILD|WS_VISIBLE,rtText,this,0);
	pLoginText->SetTextColor(RGB(80,80,80));
	pLoginText->SetText(GetTranslationString(_T("19")));
	pLoginText->SetLeft(TRUE);
	pLoginText->SetTextSize(20);
	pLoginText->ShowWindow(SW_SHOW);
	pLoginText->UpdateWindow();

	m_pLoginText=pLoginText;
}

void XPowerManage::InitLoginBtn()
{
	int nWight=80;
	int nHight=30;

	int nX=m_rtBtn.left+5;
	int nY=m_rtBtn.bottom+5;

	CRect rect(nX,nY,nX+nWight,nY+nHight);

	XBtn* pLoginBtn=new XBtn;
	pLoginBtn->Create(WS_CHILD|WS_VISIBLE,rect,this,(DWORD)SUBBTNTYPE_LOGIN);
	pLoginBtn->SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	pLoginBtn->ShowWindow(SW_SHOW);
	pLoginBtn->UpdateWindow();

	m_pLoginBtn=pLoginBtn;
}

void XPowerManage::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==TIMERID_LOAD)
	{
		DWORD dCurTime=GetTickCount();

		//TRACE(_T("dCurTime=%d\n"),dCurTime);

		if(abs((long)(m_dLoginTime)-(long)(dCurTime))>=5000)
		{
			KillTimer(TIMERID_LOAD);

			XMessageBox::GetInstance()->MessageBoxByKey(_T("45"),_T("登录超时！"),MB_OK);

			HideLoginLoadDlg();
			Login();
		
			
		}
	}
}

BOOL XPowerManage::IsLogin()
{
	return m_pDelegate->IsLogin();
}

CString XPowerManage::GetCurUserName()
{
	return m_pDelegate->GetCurUserName();
}

void XPowerManage::SetCurUserName(CString szUserName)
{
	m_pDelegate->SetCurUserName(szUserName);
}

void XPowerManage::SetLoginUser(CString szUserName,CString szPassWd)
{
	m_szLoginUserName=szUserName;
	m_szLoginPassWd=szPassWd;
}

void XPowerManage::SetLoginLoad()
{
	m_dLoginTime=GetTickCount();
	//TRACE(_T("m_dLoginTime=%d\n"),m_dLoginTime);

	SetTimer(TIMERID_LOAD,TIMERSPACE_LOAD,NULL);

	HideLoginDlg();
	ShowLoginLoadDlg();
}

void XPowerManage::ShowLoginLoadDlg()
{
	XLoginLoad dlg;
	m_pLoginLoad=&dlg;
	dlg.DoModal();

	m_pLoginLoad=NULL;
}

void XPowerManage::HideLoginLoadDlg()
{
	if(NULL!=m_pLoginLoad)
	{
		m_pLoginLoad->OnOK();
		m_pLoginLoad=NULL;
	}
}

void XPowerManage::UserManage()
{
	XUserManage dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();
}

void XPowerManage::Login()
{
	XLogin dlg;

	m_pLogin=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();

	m_pLogin=NULL;
}

void XPowerManage::HideLoginDlg()
{
	if (NULL!=m_pLogin)
	{
		m_pLogin->OnOK();
		m_pLogin=NULL;
	}
}

void XPowerManage::LoginOut()
{
	TRACE(_T("LoginOut\n"));

	if(IsLogin())
	{
		XSendDataManage::GetInstance()->AddSendDataOfLoginOut(GetCurUserName());
	}
}

void XPowerManage::NodeManage()
{
	TRACE(_T("NodeManage\n"));
}

void XPowerManage::OperateOfLogin(char* pData)
{
	XLoginInfo UserInfo;
	XJsonManage::GetInstance()->ParseJsonToLogin(pData,UserInfo);

	if(UserInfo.GetResult()>0)
	{
		if(m_szLoginUserName==UserInfo.GetUserName()&&
			m_szLoginPassWd==UserInfo.GetPassWd())
		{
			//登陆成功
			SetCurUserName(UserInfo.GetUserName());
			m_pDelegate->SetLogin(TRUE);

			KillTimer(TIMERID_LOAD);

			HideLoginLoadDlg();
			HideLoginDlg();

			UpdateText();
		}
	}
}

void XPowerManage::OperateOfLoginOut(char* pData)
{
	XResult result;
	XJsonManage::GetInstance()->ParseJsonToLoginOut(pData,result);

	if(result.GetResult()==0)
	{
		//注销
		SetCurUserName(_T(""));
		m_pDelegate->SetLogin(FALSE);

		UpdateText();
	}
}

//////////////////////////////////////////////////////////////////////////
void XPowerManage::InsertItem(CString szFilePath,UINT nID,CString szText)
{
	if(nID==0)
		return;

	XPowerManageItem* pItem=new XPowerManageItem;

	pItem->SetFilePath(szFilePath);
	pItem->SetID(nID);
	pItem->SetText(szText);

	m_VecPowerManageItem.push_back(pItem);
}

void XPowerManage::InitSub()
{
	InitRect();
	ReloadInterface();
}

void XPowerManage::ReloadInterface()
{
	UpdateText();

	for(auto iter=m_VecPowerManageItem.begin();iter!=m_VecPowerManageItem.end();++iter)
	{
		XPowerManageItem* pItem=*iter;
		pItem->SetText();
	}
}

void XPowerManage::UpdateText()
{
	CString szKey=XHandleCalculate::GetTranslationKeyFromTime();
	CString szFrontText=GetTranslationString(szKey);

	if(!IsLogin())
	{
		CString szTemp=_T("");
		szTemp.Format(_T("%s，%s"),szFrontText,GetTranslationString(_T("19")));

		m_pLoginText->SetText(szTemp);
		m_pLoginBtn->SetCaption(GetTranslationString(_T("20")));
	}
	else
	{
		CString szCurUserName=GetCurUserName();

		CString szTemp;
		szTemp.Format(_T("%s，%s"),szCurUserName,GetTranslationString(_T("21")));

		m_pLoginText->SetText(szTemp);
		m_pLoginBtn->SetCaption(GetTranslationString(_T("22")));
	}
}

CString XPowerManage::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XPowerManage::InitRect()
{
	CRect rect;
	GetClientRect(&rect);

	int nBottom=rect.bottom;
	int nRight=rect.right;

	int nWidth=60;
	int nHight=60+TEXT_HIGHT;

	int nX=rect.right-nWidth-DISTANCE;
	int nY=rect.bottom-nHight-DISTANCE;

	for(auto iter=m_VecPowerManageItem.begin();iter!=m_VecPowerManageItem.end();++iter)
	{
		XPowerManageItem* pItem=*iter;

		CRect rect(nX,nY,nX+nWidth,nY+nHight);

		pItem->SetParent(this);

		pItem->SetRect(rect);

		pItem->Init();

		nX=nX-nWidth-DISTANCE;
	}
}



//////////////////////////////////////////////////////////////////////////
LRESULT XPowerManage::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SUBBTNTYPE_USERMANAGE:
		{
			UserManage();
		}
		break;
	case SUBBTNTYPE_NODEMANAGE:
		{
			NodeManage();
		}
		break;
	case SUBBTNTYPE_LOGIN:
		{
			if(!IsLogin())
				Login();
			else
				LoginOut();
		}
		break;
	default:
		break;
	}

	return 0;
}


void XPowerManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_WELCOMETEXT:
		{
			UpdateText();
		}
		break;
	case OPERATETYPE_LOGIN:
		{
			OperateOfLogin((char*)pData);
		}
		break;
	case OPERATETYPE_LOGINOUT:
		{
			OperateOfLoginOut((char*)pData);
		}
		break;
	default:
		break;
	}
}




