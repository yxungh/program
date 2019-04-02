// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XUserManage.h"
#include "afxdialogex.h"
#include "XHandlePath.h"
#include "XTranslationManage.h"
#include "XSetListCtrl.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XSendDataManage.h"

// XUserManage 对话框

IMPLEMENT_DYNAMIC(XUserManage, XDialog)

	XUserManage::XUserManage(CWnd* pParent,CString szPhotoPath)
	: XDialog(XUserManage::IDD, pParent,szPhotoPath),
	m_pDelegate(NULL),
	m_OperateType(USEROPERATE_NULL),
	m_szUserName(_T("")),
	m_szPassWord(_T("")),
	m_Power(USERPOWER_NULL)
{
}

XUserManage::~XUserManage()
{
}

void XUserManage::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
	DDX_Control(pDX,ID_BTN_OK,m_Btn_Ok);
	DDX_Control(pDX,ID_BTN_CANCEL,m_Btn_Cancel);
	DDX_Control(pDX,IDC_LIST_USER,m_List_User);
	DDX_Control(pDX,ID_BTN_ADDUSER,m_Btn_AddUser);
	DDX_Control(pDX,ID_BTN_DELUSER,m_Btn_DelUser);
	DDX_Control(pDX,ID_BTN_ALTERUSER,m_Btn_UpdateUser);
}

BEGIN_MESSAGE_MAP(XUserManage, XDialog)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
END_MESSAGE_MAP()


// XUserManage 消息处理程序

BOOL XUserManage::OnInitDialog()
{
	XDialog::OnInitDialog();

	Init();

	return TRUE;
}

void XUserManage::Init()
{
	InitBtn();
	InitList();
	SetEditLimit();
	UpdateOperateStatus();

	ReLoadInterface();
}

void XUserManage::InitBtn()
{
	m_Btn_Ok.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_Cancel.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_AddUser.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_DelUser.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));
	m_Btn_UpdateUser.SetImage(XHandlePath::GetPhotoPath(_T("btn.png")));

	CRect rect;
	GetClientRect(&rect);

	int nLeft=rect.right-47;
	CRect rtClose(nLeft,1,nLeft+46,29);
	m_Btn_Close.Create(WS_CHILD|WS_VISIBLE,rtClose,this,ID_BTN_CLOSE);
	m_Btn_Close.ShowWindow(SW_SHOW);
	m_Btn_Close.UpdateWindow();
	m_Btn_Close.SetImage(XHandlePath::GetPhotoPath(_T("close.png")));
}

void XUserManage::InitList()
{
	XSetListCtrl::InitList(&m_List_User,2,FALSE);
}

CString XUserManage::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XUserManage::ReLoadInterface()
{
	SetWindowText(GetTranslationString(_T("18"), _T("用户管理")));
	//GetDlgItem(IDC_STATIC_ID)->SetWindowText(GetTranslationString(_T("30"),_T("ID")));
	GetDlgItem(IDC_STATIC_USER)->SetWindowText(GetTranslationString(_T("23"),_T("用户名"))+_T(":"));
	GetDlgItem(IDC_STATIC_PASSWD)->SetWindowText(GetTranslationString(_T("24"),_T("密码"))+_T(":"));
	GetDlgItem(IDC_STATIC_POWER)->SetWindowText(GetTranslationString(_T("32"),_T("权限"))+_T(":"));
	GetDlgItem(IDC_RADIO_ADMIN)->SetWindowText(GetTranslationString(_T("33"),_T("管理员")));
	GetDlgItem(IDC_RADIO_NORMAL)->SetWindowText(GetTranslationString(_T("34"),_T("用户")));

	m_Btn_Ok.SetCaption(GetTranslationString(_T("1")));
	m_Btn_Cancel.SetCaption(GetTranslationString(_T("2")));
	m_Btn_AddUser.SetCaption(GetTranslationString(_T("39"),_T("添加")));
	m_Btn_DelUser.SetCaption(GetTranslationString(_T("40"),_T("删除")));
	m_Btn_UpdateUser.SetCaption(GetTranslationString(_T("41"),_T("修改")));
	

	ReloadListInterface();
}

void XUserManage::ReloadListInterface()
{
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	//szTemp=GetTranslationString(_T("30"),_T("ID"));
	//col.pszText=szTemp.GetBuffer();
	//m_List_User.SetColumn(0,&col);
	//szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("31"),_T("用户名"));
	col.pszText=szTemp.GetBuffer();
	m_List_User.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("32"),_T("权限"));
	col.pszText=szTemp.GetBuffer();
	m_List_User.SetColumn(1,&col);
	szTemp.ReleaseBuffer();
}

void XUserManage::SetEditLimit()
{
	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(18);
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetLimitText(18);

	((CButton*)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(TRUE);
}

int XUserManage::GetListItem(CString szUserName)
{
	int nCount=m_List_User.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		CString szText=m_List_User.GetItemText(i,0);
		if(szText==szUserName)
		{
			return i;
		}
	}
	return -1;
}

void XUserManage::OnBtnClickedAdd()
{
	SetOperateType(USEROPERATE_ADD);
	UpdateOperateStatus();
}

void XUserManage::OnBtnClickedDel()
{
	int nSelect=XSetListCtrl::GetListSelectItem(&m_List_User);
	if(-1==nSelect)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("43"),_T("请选择要删除的用户！"),MB_OK);
		return;
	}

	CString szUserName=m_List_User.GetItemText(nSelect,0);

	int nItem=GetListItem(szUserName);
	//删除行
	m_List_User.DeleteItem(nItem);
	m_List_User.Invalidate(TRUE);

}

void XUserManage::OnBtnClickedAlter()
{
	int nSelect=XSetListCtrl::GetListSelectItem(&m_List_User);
	if(-1==nSelect)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("42"),_T("请选择要编辑的用户！"),MB_OK);
		return;
	}

	CString szUserName=m_List_User.GetItemText(nSelect,0);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(szUserName);

	SetOperateType(USEROPERATE_ALTER);
	UpdateOperateStatus();
}

void XUserManage::OnBtnClickedOk()
{
	CString szUserName=_T("");
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(szUserName);
	szUserName.Trim();
	if(_T("")==szUserName)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("25"),_T("用户名不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if (_T("")==szPassWd)
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("26"),_T("密码不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		return;
	}

	if (!XHandleVerification::VerificationString(szUserName))
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("27"),_T("用户名包含非法字符！"),MB_OK);
		return;
	}

	if (!XHandleVerification::VerificationString(szPassWd))
	{
		XMessageBox::GetInstance()->MessageBoxByKey(_T("28"),_T("密码包含非法字符！"),MB_OK);
		return;
	}

	char power=USERPOWER_NULL;
	if((((CButton*)GetDlgItem(IDC_RADIO_ADMIN)))->GetCheck())
	{
		power=USERPOWER_ADMIN;
	}
	else
	{
		power=USERPOWER_NORMAL;
	}

	m_szUserName=szUserName;
	m_szPassWord=szPassWd;
	m_Power=power;
	//////////////////////////////////////////////////////////////////////////
	switch(m_OperateType)
	{
	case USEROPERATE_ADD:
		{
			SaveAdd();
		}
		break;
	case USEROPERATE_ALTER:
		{
			SaveAlter();
		}
		break;
	default:
		break;
	}
}

void XUserManage::SaveAdd()
{
	//保存添加
	AddListInfo(m_szUserName,m_Power);
}

void XUserManage::SaveAlter()
{
	//保存修改

}

void XUserManage::OnBtnClickedCancel()
{
	SetOperateType(USEROPERATE_NULL);
	UpdateOperateStatus();
}

int XUserManage::AddListInfo(CString szUserName,char cType)
{
	int nCount=m_List_User.GetItemCount();
	m_List_User.InsertItem(nCount,_T(""));
	SetListInfo(nCount,szUserName,cType);

	return nCount;
}

void XUserManage::SetListInfo(int nCount,CString szUserName,char cType)
{
	m_List_User.SetItemText(nCount,0,szUserName);

	switch(cType)
	{
	case USERPOWER_ADMIN:
		{
			m_List_User.SetItemText(nCount,1,GetTranslationString(_T("33"),_T("管理员")));
		}
		break;
	case USERPOWER_NORMAL:
		{
			m_List_User.SetItemText(nCount,1,GetTranslationString(_T("34"),_T("用户")));
		}
		break;
	default:
		break;
	}
}

LRESULT XUserManage::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	if(ID_BTN_CLOSE==wParam)
	{
		OnCancel();
	}
	else
	{
		switch(wParam)
		{
		case ID_BTN_ADDUSER:
			{
				OnBtnClickedAdd();
			}
			break;
		case ID_BTN_DELUSER:
			{
				OnBtnClickedDel();
			}
			break;
		case ID_BTN_ALTERUSER:
			{
				OnBtnClickedAlter();
			}
			break;
		case ID_BTN_OK:
			{
				OnBtnClickedOk();
			}
			break;
		case ID_BTN_CANCEL:
			{
				OnBtnClickedCancel();
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

HBRUSH XUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(IDC_RADIO_ADMIN==pWnd->GetDlgCtrlID()
		||IDC_RADIO_NORMAL==pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH brush=CreateSolidBrush(RGB(232,239,242));
		return brush;
	}
	else if(IDC_EDIT_USERNAME==pWnd->GetDlgCtrlID()
		||IDC_EDIT_PASSWORD==pWnd->GetDlgCtrlID())
	{
		//编辑框调用父类，不太行
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH brush=CreateSolidBrush(RGB(255,255,255));
		return brush;
	}

	return XDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void XUserManage::UpdateOperateStatus()
{
	switch(m_OperateType)
	{
	case USEROPERATE_ADD:
		{
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(_T(""));

			GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T(""));

			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_ADDUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_DELUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_ALTERUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_OK)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_CANCEL)->EnableWindow(TRUE);

			GetDlgItem(IDC_LIST_USER)->EnableWindow(FALSE);
		}
		break;
	case USEROPERATE_DEL:
	case USEROPERATE_NULL:
		{
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(_T(""));

			GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T(""));

			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_ADDUSER)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_DELUSER)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_ALTERUSER)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_OK)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_CANCEL)->EnableWindow(FALSE);

			GetDlgItem(IDC_LIST_USER)->EnableWindow(TRUE);
		}
		break;
	case USEROPERATE_ALTER:
		{
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_ADDUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_DELUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_ALTERUSER)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_OK)->EnableWindow(TRUE);
			GetDlgItem(ID_BTN_CANCEL)->EnableWindow(TRUE);
		}
		break;
	default:
		break;
	}
}