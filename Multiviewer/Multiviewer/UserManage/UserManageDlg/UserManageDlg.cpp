// ChangeRTSPAddrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserManageDlg.h"
#include "afxdialogex.h"
#include "XUserManage.h"
#include "XDelegateUserManage.h"
#include "..\XConstant.h"
#include "HandleListCtrl.h"
#include "XUserInfo.h"
#include "UserPowerManageDlg.h"
#include "XNodePowerInfo.h"

//操作类型
enum UMOPERATETYPE
{
	UMOPERATETYPE_EDIT,
	UMOPERATETYPE_ADD,
	UMOPERATETYPE_COPY,

	UMOPERATETYPE_NULL
};

// CUserManageDlg 对话框

IMPLEMENT_DYNAMIC(CUserManageDlg, CDialogEx)

CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserManageDlg::IDD, pParent)
{
	m_UserManage = NULL;

	m_EditUserInfo = NULL;

	m_CopyUserInfo=NULL;
}

CUserManageDlg::~CUserManageDlg()
{
}

void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERLIST, m_ListCtrl_User);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_Edit_Account);
	DDX_Control(pDX, IDC_EDIT_PSW2, m_Edit_PSW);
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CUserManageDlg::OnBtnClickedAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CUserManageDlg::OnBtnClickedEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CUserManageDlg::OnBtnClickedDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CUserManageDlg::OnBtnClickedSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CUserManageDlg::OnBtnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_COPY, &CUserManageDlg::OnBtnClickedCopy)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USERLIST, &CUserManageDlg::OnNMDblclkListCtrlUser)
	ON_EN_CHANGE(IDC_EDIT_NOTICE,&CUserManageDlg::OnEditNoticeChange)
END_MESSAGE_MAP()


// CUserManageDlg 消息处理程序

void CUserManageDlg::OnOK()
{
}

BOOL CUserManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitList();

	ReloadInterface();

	ReloadListInterface();

	InitListData();

	ShowOperateInterface(UMOPERATETYPE_NULL);

	((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetLimitText(18);
	((CEdit*)GetDlgItem(IDC_EDIT_PSW))->SetLimitText(18);
	((CButton*)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(TRUE);

	InitNotice();

	return FALSE;  
}

void CUserManageDlg::ReloadInterface()
{
	XDelegateUserManage* pDelegate = m_UserManage->GetDelegate();

	SetWindowText(pDelegate->GetTranslationString(_T("346"), _T("用户管理")));

	GetDlgItem(IDC_STATIC_TIPSUSER)->SetWindowText(pDelegate->GetTranslationString(_T("680"), _T("提示:双击用户设置其权限")));

	GetDlgItem(IDC_STATIC_USERINFO)->SetWindowText(pDelegate->GetTranslationString(_T("354"), _T("帐号信息")));

	GetDlgItem(IDC_BTN_SAVE)->SetWindowText(pDelegate->GetTranslationString(_T("355"), _T("保存")));
	GetDlgItem(IDC_BTN_CANCEL)->SetWindowText(pDelegate->GetTranslationString(_T("356"), _T("取消")));
	GetDlgItem(IDC_BTN_ADD)->SetWindowText(pDelegate->GetTranslationString(_T("357"), _T("添加")));
	GetDlgItem(IDC_BTN_EDIT)->SetWindowText(pDelegate->GetTranslationString(_T("358"), _T("编辑")));
	GetDlgItem(IDC_BTN_DEL)->SetWindowText(pDelegate->GetTranslationString(_T("359"), _T("删除")));

	GetDlgItem(IDC_STATIC_ACCOUNT)->SetWindowText(pDelegate->GetTranslationString(_T("348"), _T("帐号")) + _T(":"));

	GetDlgItem(IDC_STATIC_PSW)->SetWindowText(pDelegate->GetTranslationString(_T("349"), _T("密码")) + _T(":"));

	GetDlgItem(IDC_STATIC_POWER)->SetWindowText(pDelegate->GetTranslationString(_T("361"), _T("类型")) + _T(":"));

	GetDlgItem(IDC_RADIO_ADMIN)->SetWindowText(pDelegate->GetTranslationString(_T("362"), _T("管理员")));

	GetDlgItem(IDC_RADIO_NORMAL)->SetWindowText(pDelegate->GetTranslationString(_T("363"), _T("用户")));
}

void CUserManageDlg::InitNotice()
{
	CString szNotice=m_UserManage->GetNotice();
	GetDlgItem(IDC_EDIT_NOTICE)->SetWindowText(szNotice);
}

void CUserManageDlg::ReloadListInterface()
{
	XDelegateUserManage* pDelegate = m_UserManage->GetDelegate();

	LVCOLUMN col;

	CString szTemp = _T("");

	szTemp = pDelegate->GetTranslationString(_T("353"), _T("帐号列表"));
	col.mask = LVCF_TEXT;
	col.pszText = szTemp.GetBuffer();
	m_ListCtrl_User.SetColumn(0, &col);
	szTemp.ReleaseBuffer();
}

void CUserManageDlg::SetUserManage(XUserManage* p)
{
	m_UserManage = p;
}

void CUserManageDlg::InitList()
{
	HandleListCtrl::InitList(&m_ListCtrl_User, 1, FALSE);
}

void CUserManageDlg::InitListData()
{
	VEC_USERINFO& VecUserInfo = m_UserManage->GetVecUserInfo();

	for (VEC_USERINFO::iterator iter = VecUserInfo.begin(); iter != VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo = *iter;

		AddInfo(pInfo->GetAccount());
	}
}

int CUserManageDlg::AddInfo(CString szAccount)
{
	int n = m_ListCtrl_User.GetItemCount();

	m_ListCtrl_User.InsertItem(n, _T(""));

	SetInfo(n, szAccount);

	return n;
}

void CUserManageDlg::SetInfo(int n, CString szAccount)
{
	m_ListCtrl_User.SetItemText(n, 0, szAccount);
}

void CUserManageDlg::ShowOperateInterface(char type)
{
	m_OperateType = type;

	switch(type)
	{
	case UMOPERATETYPE_ADD:
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(TRUE);

			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(TRUE);

			m_Edit_Account.EnableWindow(TRUE);
			m_Edit_Account.SetWindowText(_T(""));
			m_Edit_Account.SetFocus();

			m_Edit_PSW.EnableWindow(TRUE);
			m_Edit_PSW.SetWindowText(_T(""));

			m_ListCtrl_User.EnableWindow(FALSE);
		}
		break;
	case UMOPERATETYPE_EDIT:
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(TRUE);

			if (m_EditUserInfo->GetAccount() == DEFAULTACCOUNT)
			{
				GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(FALSE);

				m_Edit_Account.EnableWindow(FALSE);
				m_Edit_PSW.EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(TRUE);

				m_Edit_Account.EnableWindow(TRUE);
				m_Edit_PSW.EnableWindow(TRUE);
			}
			
			m_ListCtrl_User.EnableWindow(FALSE);
		}
		break;
	case UMOPERATETYPE_COPY:
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(TRUE);

			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(FALSE);

			m_Edit_Account.EnableWindow(TRUE);
			m_Edit_Account.SetWindowText(_T(""));

			m_Edit_PSW.EnableWindow(TRUE);
			m_Edit_PSW.SetWindowText(_T(""));

			m_ListCtrl_User.EnableWindow(FALSE);
		}
		break;
	case UMOPERATETYPE_NULL:
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_COPY)->EnableWindow(TRUE);

			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(FALSE);

			GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_NORMAL)->EnableWindow(FALSE);

			m_Edit_Account.EnableWindow(FALSE);
			m_Edit_Account.SetWindowText(_T(""));

			m_Edit_PSW.EnableWindow(FALSE);
			m_Edit_PSW.SetWindowText(_T(""));

			m_ListCtrl_User.EnableWindow(TRUE);
		}
		break;
	default:
		break;
	}
}

void CUserManageDlg::OnBtnClickedAdd()
{
	ShowOperateInterface(UMOPERATETYPE_ADD);
}

void CUserManageDlg::OnBtnClickedEdit()
{
	int nSelect = HandleListCtrl::GetListSelectItem(&m_ListCtrl_User);

	if(-1 == nSelect)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("364"), _T("请在账号列表选择需要编辑的帐号!"), MB_OK);

		return;
	}

	CString szAccount = m_ListCtrl_User.GetItemText(nSelect, 0);

	XUserInfo* pUserInfo = m_UserManage->GetAccountInfo(szAccount);

	if (NULL == pUserInfo)
	{
		return;
	}

	m_EditUserInfo = pUserInfo;

	m_EditListItem = nSelect;

	ShowOperateInterface(UMOPERATETYPE_EDIT);

	m_Edit_Account.SetWindowText(pUserInfo->GetAccount());

	m_Edit_PSW.SetWindowText(pUserInfo->GetPassword());
	
	SelectPower((POWERTYPE)pUserInfo->GetPower());
}

void CUserManageDlg::OnBtnClickedCopy()
{
	int nSelect = HandleListCtrl::GetListSelectItem(&m_ListCtrl_User);

	if(-1 == nSelect)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("364"), _T("请在账号列表选择需要编辑的帐号!"), MB_OK);

		return;
	}

	CString szAccount = m_ListCtrl_User.GetItemText(nSelect, 0);

	XUserInfo* pUserInfo = m_UserManage->GetAccountInfo(szAccount);

	if (NULL == pUserInfo)
	{
		return;
	}

	m_CopyUserInfo = pUserInfo;

	ShowOperateInterface(UMOPERATETYPE_COPY);

	SelectPower((POWERTYPE)pUserInfo->GetPower());
}

void CUserManageDlg::SelectPower(POWERTYPE type)
{
	switch(type)
	{
	case POWERTYPE_ADMIN:
		{
			((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(FALSE);
		}
		break;
	case POWERTYPE_NORMAL:
		{
			((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(TRUE);
		}
		break;
	default:
		break;
	}
}

void CUserManageDlg::OnBtnClickedDel()
{
	if (!m_UserManage->IsAdminUser())
	{
		return;
	}

	int nSelect = HandleListCtrl::GetListSelectItem(&m_ListCtrl_User);

	if(-1 == nSelect)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("67"), _T("请在账号列表选择需要删除的帐号!"), MB_OK);

		return;
	}

	CString szAccount = m_ListCtrl_User.GetItemText(nSelect, 0);

	if (szAccount == DEFAULTACCOUNT)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("368"), _T("不能删除默认帐号!"), MB_OK);

		return;
	}

	if (m_UserManage->GetDelegate()->MessageBoxFromKey(_T("369"), _T("请确认是否删除用户？"), MB_YESNO) != IDYES)
	{
		return;
	}

	CString szCurAccount = m_UserManage->GetCurUserInfo()->GetAccount();

	m_UserManage->DeleteAccount(szAccount);

	m_ListCtrl_User.DeleteItem(nSelect);

	//删除的用户为当前登陆用户
	if (szCurAccount == szAccount)
	{
		m_UserManage->SetCurUserInfo(NULL);

		CDialogEx::OnCancel();
	}
}

void CUserManageDlg::OnBtnClickedSave()
{
	if (!m_UserManage->IsAdminUser())
	{
		return;
	}

	switch(m_OperateType)
	{
	case UMOPERATETYPE_ADD:
		{
			SaveAdd();
		}
		break;
	case UMOPERATETYPE_EDIT:
		{
			SaveEdit();
		}
		break;
	case UMOPERATETYPE_COPY:
		{
			SaveCopy();
		}
		break;
	default:
		break;
	}
}

void CUserManageDlg::OnNMDblclkListCtrlUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nSelect = HandleListCtrl::GetListSelectItem(&m_ListCtrl_User);

	if(-1 != nSelect)
	{
		//OnBtnClickedEdit();

		//双击权限管理
		SetPower();
	}
	else
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("371"), _T("请从帐号列表选择需要设置权限的帐号!"), MB_OK);

		return;
	}

	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////////
void CUserManageDlg::SetPower()
{
	int nSelect = HandleListCtrl::GetListSelectItem(&m_ListCtrl_User);

	CString szAccount = m_ListCtrl_User.GetItemText(nSelect, 0);

	XUserInfo* pUserInfo = m_UserManage->GetAccountInfo(szAccount);

	if (NULL == pUserInfo)
	{
		return;
	}

	CUserPowerManageDlg dlg;

	dlg.SetUserManage(m_UserManage);

	dlg.SetUserInfo(pUserInfo);

	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////

void CUserManageDlg::OnBtnClickedCancel()
{
	ShowOperateInterface(UMOPERATETYPE_NULL);
}

POWERTYPE CUserManageDlg::GetSelectPower()
{
	if (((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->GetCheck())
	{
		return POWERTYPE_ADMIN;
	}
	else
	{
		return POWERTYPE_NORMAL;
	}
}

void CUserManageDlg::SaveAdd()
{
	CString szAccount = _T("");
	m_Edit_Account.GetWindowText(szAccount);
	szAccount.Trim();
	if (_T("") == szAccount)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("350"), _T("帐号不能为空,请输入!"), MB_OK);

		m_Edit_Account.SetFocus();

		return;
	}

	CString szPSW = _T("");
	m_Edit_PSW.GetWindowText(szPSW);
	szPSW.Trim();
	if (_T("") == szPSW)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("21"), _T("密码不能为空,请输入!"), MB_OK);

		m_Edit_PSW.SetFocus();

		return;
	}

	if(m_UserManage->DecideAccountExist(szAccount))
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("360"), _T("帐号已存在，请重新输入!"), MB_OK);

		return;
	}

	POWERTYPE type = GetSelectPower();

	m_UserManage->AddUserInfo(szAccount, szPSW, type);

	ShowOperateInterface(UMOPERATETYPE_NULL);

	int nInsertItem = AddInfo(szAccount);

	m_ListCtrl_User.EnsureVisible(nInsertItem, FALSE);

	HandleListCtrl::SetListItemSelect(&m_ListCtrl_User, nInsertItem);

	if(type==POWERTYPE_NORMAL)
	{
		XUserInfo* pUserInfo = m_UserManage->GetAccountInfo(szAccount);

		CUserPowerManageDlg dlg;

		dlg.SetUserManage(m_UserManage);

		dlg.SetUserInfo(pUserInfo);

		dlg.DoModal();
	}

	m_UserManage->GetDelegate()->MessageBoxFromKey(_T("366"), _T("添加用户成功!"), MB_OK);
}

void CUserManageDlg::SaveEdit()
{
	CString szAccount = _T("");
	m_Edit_Account.GetWindowText(szAccount);
	szAccount.Trim();
	if (_T("") == szAccount)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("350"), _T("帐号不能为空,请输入!"), MB_OK);

		m_Edit_Account.SetFocus();

		return;
	}

	CString szPSW = _T("");
	m_Edit_PSW.GetWindowText(szPSW);
	szPSW.Trim();
	if (_T("") == szPSW)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("21"), _T("密码不能为空,请输入!"), MB_OK);

		m_Edit_PSW.SetFocus();

		return;
	}

	if (m_EditUserInfo->GetAccount() != szAccount)
	{
		if(m_UserManage->DecideAccountExist(szAccount))
		{
			m_UserManage->GetDelegate()->MessageBoxFromKey(_T("360"), _T("帐号已存在，请重新输入!"), MB_OK);

			return;
		}
	}
	
	POWERTYPE type = GetSelectPower();

	if (m_EditUserInfo->GetAccount() == DEFAULTACCOUNT)
	{
		m_EditUserInfo->SetPassword(szPSW);
	}
	else
	{
		m_EditUserInfo->SetAccount(szAccount);

		m_EditUserInfo->SetPassword(szPSW);

		m_EditUserInfo->SetPower(type);
	}

	SetInfo(m_EditListItem, szAccount);

	ShowOperateInterface(UMOPERATETYPE_NULL);

	m_UserManage->GetDelegate()->MessageBoxFromKey(_T("365"), _T("编辑用户成功!"), MB_OK);

	//编辑的用户为当前登陆用户
	if ((m_UserManage->GetCurUserInfo() == m_EditUserInfo)
		&& (type != POWERTYPE_ADMIN))
	{
		m_UserManage->SetCurUserInfo(NULL);

		CDialogEx::OnCancel();
	}
}

void CUserManageDlg::SaveCopy()
{
	CString szAccount = _T("");
	m_Edit_Account.GetWindowText(szAccount);
	szAccount.Trim();
	if (_T("") == szAccount)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("350"), _T("帐号不能为空,请输入!"), MB_OK);

		m_Edit_Account.SetFocus();

		return;
	}

	CString szPSW = _T("");
	m_Edit_PSW.GetWindowText(szPSW);
	szPSW.Trim();
	if (_T("") == szPSW)
	{
		m_UserManage->GetDelegate()->MessageBoxFromKey(_T("21"), _T("密码不能为空,请输入!"), MB_OK);

		m_Edit_PSW.SetFocus();

		return;
	}

	if(m_CopyUserInfo==NULL)
	{
		return;
	}

	if (m_CopyUserInfo->GetAccount() != szAccount)
	{
		if(m_UserManage->DecideAccountExist(szAccount))
		{
			m_UserManage->GetDelegate()->MessageBoxFromKey(_T("360"), _T("帐号已存在，请重新输入!"), MB_OK);

			return;
		}
	}

	POWERTYPE type = GetSelectPower();

	XUserInfo* pUserInfo=m_UserManage->AddUserInfo(szAccount, szPSW, type);

	int nInsertItem = AddInfo(szAccount);

	m_ListCtrl_User.EnsureVisible(nInsertItem, FALSE);

	HandleListCtrl::SetListItemSelect(&m_ListCtrl_User, nInsertItem);

	MAP_NODEPOWERINFO& MapCopyPoewrInfo=m_CopyUserInfo->GetMapPowerInfo();

	MAP_NODEPOWERINFO& MapPowerInfo=pUserInfo->GetMapPowerInfo();

	for(MAP_NODEPOWERINFO::iterator iter=MapCopyPoewrInfo.begin();iter!=MapCopyPoewrInfo.end();++iter)
	{
		unsigned int nKey=iter->first;

		XNodePowerInfo* pInfo=iter->second;

		MAP_NODEPOWERINFO::iterator iterUser=MapPowerInfo.find(nKey);

		if(iterUser==MapPowerInfo.end())
		{
			XNodePowerInfo* pNewInfo=new XNodePowerInfo;

			pNewInfo->SetInputIndex(pInfo->GetInputIndex());

			pNewInfo->SetOutputIndex(pInfo->GetOutputIndex());

			pNewInfo->SetPower(pInfo->GetPower());

			MapPowerInfo.insert(std::pair<unsigned int,XNodePowerInfo*>(nKey,pNewInfo));
		}
	}

	ShowOperateInterface(UMOPERATETYPE_NULL);
}

void CUserManageDlg::OnEditNoticeChange()
{
	CString szNotice=_T("");
	GetDlgItem(IDC_EDIT_NOTICE)->GetWindowText(szNotice);

	m_UserManage->SetNotice(szNotice);
}