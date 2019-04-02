#include "StdAfx.h"
#include "XUserManage.h"
#include "XUserInfo.h"
#include "XDelegateUserManage.h"
#include "XDataUserManage.h"
#include "LoginDlg.h"
#include "UserManageDlg.h"
#include "..\XConstant.h"

XUserManage::XUserManage(void)
{
	m_CurUserInfo = NULL;

	m_szNotice=_T("");
}

XUserManage::~XUserManage(void)
{
	ClearData();
}

void XUserManage::ClearData()
{
	for (VEC_USERINFO::iterator iter = m_VecUserInfo.begin(); iter != m_VecUserInfo.end(); iter++)
	{
		delete *iter;
	}

	m_VecUserInfo.clear();
}

void XUserManage::SetDelegate(XDelegateUserManage* p)
{
	m_pDelegate = p;
}

void XUserManage::Init()
{
	
}

void XUserManage::ResetData()
{
	//添加默认用户
	XUserInfo* pUserInfo = new XUserInfo;
	pUserInfo->SetAccount(DEFAULTACCOUNT);
	pUserInfo->SetPassword(DEFAULTACCOUNT);
	pUserInfo->SetPower(POWERTYPE_ADMIN);

	m_VecUserInfo.push_back(pUserInfo);
}

void XUserManage::GetData(CArchive& arch)
{
	XDataUserManage::GetData(this, arch);

	//m_CurUserInfo = m_VecUserInfo[0];
}

void XUserManage::SaveData(CArchive& arch)
{
	XDataUserManage::SaveData(this, arch);
}

XUserInfo* XUserManage::AddUserInfo(CString szAccount, CString szPSW, POWERTYPE type)
{
	XUserInfo* pUserInfo = new XUserInfo;

	pUserInfo->SetAccount(szAccount);
	pUserInfo->SetPassword(szPSW);
	pUserInfo->SetPower(type);

	m_VecUserInfo.push_back(pUserInfo);

	return pUserInfo;
}

BOOL XUserManage::DecideAccountExist(CString name)
{
	if(GetAccountInfo(name)==NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

XUserInfo* XUserManage::GetAccountInfo(CString name)
{
	for (VEC_USERINFO::iterator iter = m_VecUserInfo.begin(); iter != m_VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo =  *iter;

		if (pInfo->GetAccount() == name)
		{
			return pInfo;
		}
	}

	return NULL;
}

XUserInfo* XUserManage::DecideAccountAndPsw(CString name, CString psw)
{
	XUserInfo* pInfo = GetAccountInfo(name);

	if ((pInfo != NULL)
		&& (pInfo->GetPassword() == psw))
	{
		return pInfo;
	}
	else
	{
		return NULL;
	}
}

void XUserManage::DeleteAccount(CString name)
{
	for (VEC_USERINFO::iterator iter = m_VecUserInfo.begin(); iter != m_VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo =  *iter;

		if (pInfo->GetAccount() == name)
		{
			m_VecUserInfo.erase(iter);

			delete pInfo;

			return;
		}
	}
}

void XUserManage::GetNormalUser(VEC_USERINFO& VecUesrInfo)
{
	for (VEC_USERINFO::iterator iter = m_VecUserInfo.begin(); iter != m_VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo =  *iter;

		if (pInfo->GetPower() == POWERTYPE_NORMAL)
		{
			VecUesrInfo.push_back(pInfo);
		}
	}
}

VEC_USERINFO& XUserManage::GetVecUserInfo()
{
	return m_VecUserInfo;
}

XDelegateUserManage* XUserManage::GetDelegate()
{
	return m_pDelegate;
}

void XUserManage::SetCurUserInfo(XUserInfo* p)
{
	m_CurUserInfo = p;

	if (p != NULL)
	{
		AfxGetMainWnd()->SetWindowText(APP_NAME + _T(" ") + APP_VERSION + _T(" - ") + p->GetAccount());
	}
	else
	{
		AfxGetMainWnd()->SetWindowText(APP_NAME + _T(" ") + APP_VERSION);
	}
}

XUserInfo* XUserManage::GetCurUserInfo()
{
	return m_CurUserInfo;
}

BOOL XUserManage::IsLogin()
{
	if (NULL != m_CurUserInfo)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL XUserManage::GetUserNodePower(int nInputIndex, int nOutputIndex)
{
	if (NULL == m_CurUserInfo)
	{
		return FALSE;
	}

	return m_CurUserInfo->GetNodePower(nInputIndex, nOutputIndex);
}

BOOL XUserManage::IsAdminUser()
{
	if (NULL != m_CurUserInfo
		&& POWERTYPE_ADMIN == m_CurUserInfo->GetPower())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XUserManage::UpdateControlUIByAdmin(CCmdUI* pCmdUI)
{
	if ((NULL == m_CurUserInfo)
		|| (POWERTYPE_ADMIN != m_CurUserInfo->GetPower()))
	{
		pCmdUI->Enable(FALSE);
	}
}

void XUserManage::OperateOfLogin()
{
	CLoginDlg dlg;

	dlg.SetUserManage(this);

	dlg.DoModal();
}

void XUserManage::OperateOfUserManage()
{
	if (!IsAdminUser())
	{
		return;
	}

	CUserManageDlg dlg;

	dlg.SetUserManage(this);

	dlg.DoModal();
}

void XUserManage::OperateOfResetUserNodePower()
{
	for (VEC_USERINFO::iterator iter = m_VecUserInfo.begin(); iter != m_VecUserInfo.end(); iter++)
	{
		XUserInfo* pInfo =  *iter;

		pInfo->ClearMapNodePowerInfo();
	}
}

void XUserManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_LOGIN:
		{
			OperateOfLogin();
		}
		break;
	case OPERATETYPE_LOGOUT:
		{
			SetCurUserInfo(NULL);
		}
		break;
	case OPERATETYPE_USERMANAGE:
		{
			OperateOfUserManage();
		}
		break;
	case OPERATETYPE_RESETUSERNODEPOWER:
		{
			OperateOfResetUserNodePower();
		}
		break;
	default:
		break;
	}
}

void XUserManage::UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)
{
	switch(type)
	{
	case CMDUITYPE_LOGIN:
		{
			if (NULL != m_CurUserInfo)
			{
				pCmdUI->Enable(FALSE);
			}
		}
		break;
	case CMDUITYPE_LOGOUT:
		{
			if (NULL == m_CurUserInfo)
			{
				pCmdUI->Enable(FALSE);
			}
		}
		break;
	case CMDUITYPE_USERMANAGE:
	case CMDUITYPE_POWERMANAGE:
	case CMDUITYPE_INPUTCOUNT:
	case CMDUITYPE_OUTPUTCOUNTH:
	case CMDUITYPE_OUTPUTCOUNTV:
	case CMDUITYPE_DEVICEIP:
	case CMDUITYPE_DEVICEPORT:
	case CMDUITYPE_RUNOLDORDER:
	case CMDUITYPE_SAVESCENCE:
	case CMDUITYPE_OPENSCENCE:
	case CMDUITYPE_DELETESCENCE:
	case CMDUITYPE_SCREENMOVE:
	case CMDUITYPE_TIMEDPOLLING:
	case CMDUITYPE_DELETEALLSIGNAL:
	case CMDUITYPE_SETSCREENRESULATION:
	case CMDUITYPE_NEWVIEW:
	case CMDUITYPE_CLOSEVIEW:
	case CMDUITYPE_PREVIEW:
	case CMDUITYPE_NORMAL:
	case CMDUITYPE_FOUR:
	case CMDUITYPE_FULL:
	case CMDUITYPE_INTER:
	case CMDUITYPE_TIPMODEL:
	case CMDUITYPE_UPMODEL:
	case CMDUITYPE_DOWNMODEL:
	case CMDUITYPE_SAVEALLSCENE:
	case CMDUITYPE_COPYMODEL:
		{
			UpdateControlUIByAdmin(pCmdUI);
		}
		break;
	default:
		break;
	}
}
