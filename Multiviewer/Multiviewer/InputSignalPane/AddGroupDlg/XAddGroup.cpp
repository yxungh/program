#include "stdafx.h"
#include "XAddGroup.h"
#include "afxdialogex.h"
#include "XDelegateAddGroup.h"
#include "XInputSignal.h"
#include "XInputSignalPane.h"
#include "XGroupName.h"
#include "XGroupName2.h"
#include "XInputGroup.h"
#include "XInputInfoInGroup.h"
#include <algorithm>


// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XAddGroup, CDialogEx)

	XAddGroup::XAddGroup(CWnd* pParent /*=NULL*/)
	: CDialogEx(XAddGroup::IDD, pParent)
{
	m_pDelegate = NULL;

	m_InputSignal=NULL;

	m_InputSignalPane=NULL;

	m_szRbGroupName=_T("");

	m_nType=-1;

	m_RbItem=NULL;
}

XAddGroup::~XAddGroup()
{

}

void XAddGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE_GROUP, m_TreeGroup);
}


BEGIN_MESSAGE_MAP(XAddGroup, CDialogEx)
	ON_BN_CLICKED(IDOK,OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_NEWGROUP,OnBnAddGroup)
	ON_BN_CLICKED(IDC_BTN_ADDINGROUP,OnAddInGroup)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_GROUP, OnNMRClickTree)
	ON_COMMAND(ID_GROUP_DELETE,OnDelete)
	ON_COMMAND(ID_GROUP_CHANGE,OnChange)
	
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序

void XAddGroup::SetDelegate(XDelegateAddGroup* p)
{
	m_pDelegate = p;

	m_szGroupName=_T("");

	m_szNewGroupName=_T("");
}

void XAddGroup::SetInputSignal(XInputSignal* p)
{
	m_InputSignal = p;
}

void XAddGroup::SetGroupName(CString s)
{
	m_szGroupName=s;
}

CString XAddGroup::GetGroupName()
{
	return m_szGroupName;
}

void XAddGroup::SetInputSignalPane(XInputSignalPane* p)
{
	m_InputSignalPane = p;
}

BOOL XAddGroup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_szRoot=m_pDelegate->GetTranslationString(_T("666"),_T("分组列表"));

	ReloadInterface();

	Init();

	InitData();

	return FALSE;  
}

void XAddGroup::InitData()
{
	MAP_GROUP& MapGroup=m_InputSignalPane->GetMapGroup();

	for(MAP_GROUP::iterator iter=MapGroup.begin();iter!=MapGroup.end();++iter)
	{
		XInputGroup* pInputGroup=iter->second;

		CString szGroupName=pInputGroup->GetGroupName();

		AddChild(szGroupName);

		VEC_INPUTINFOINGROUP& VecInputSignal=pInputGroup->GetVecInputInGroup();

		for(VEC_INPUTINFOINGROUP::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
		{
			XInputInfoInGroup* pInput=*iter;

			CString szInputName=pInput->GetAnotherName();

			int nIndex=pInput->GetIndex();

			CString szTemp;

			szTemp.Format(_T("%d"),nIndex);

			CString szChild;

			if(szInputName!=_T(""))
			{
				szChild=m_pDelegate->GetTranslationString(_T("439"),_T("输入"))+szTemp+_T("(")+szInputName+_T(")");
			}
			else
			{
				szChild=m_pDelegate->GetTranslationString(_T("439"),_T("输入"))+szTemp;
			}

			HTREEITEM hChildChild=AddChildChild(szChild);

			m_TreeGroup.SetItemData(hChildChild,(DWORD_PTR)pInput);
		}
	}

	HTREEITEM item=m_TreeGroup.GetRootItem();

	m_TreeGroup.Expand(item,TVE_EXPAND);
}

void XAddGroup::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("667"),_T("添加分组")));
	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("214"), _T("确定")));
	//GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("215"), _T("取消")));
	GetDlgItem(IDC_BTN_NEWGROUP)->SetWindowText(m_pDelegate->GetTranslationString(_T("668"),_T("新建分组")));
}

void XAddGroup::Init()
{
	InitTreeImageList();

	AddRoot(m_szRoot);
}

void XAddGroup::InitTreeImageList()
{
	m_TreeImageList.Create(24, 24, ILC_COLOR32, 0, 0);

	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUPCHILD));

	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));

	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LAYER));

	m_TreeGroup.SetImageList(&m_TreeImageList, TVSIL_NORMAL);
}

//仿函数
BOOL Compare1(XInputInfoInGroup* pInfo1,XInputInfoInGroup* pInfo2)
{
	if(pInfo1->GetIndex()<pInfo2->GetIndex())
		return TRUE;
	else
		return FALSE;
}

void XAddGroup::OnAddInGroup()
{
	CString szText=_T("");

	HTREEITEM hItem=m_TreeGroup.GetSelectedItem();

	if(hItem==m_TreeGroup.GetRootItem())
	{
		m_pDelegate->MessageBoxFromKey(_T("669"),_T("请选择分组！"),MB_OK);

		return;
	}

	if(hItem==NULL)
	{
		m_pDelegate->MessageBoxFromKey(_T("669"),_T("请选择分组！"),MB_OK);

		return;
	}

	szText=m_TreeGroup.GetItemText(hItem);

	m_szGroupName=szText;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	MAP_GROUP& MapInputGroup=m_InputSignalPane->GetMapGroup();

	VEC_INPUTSIGNAL& VecInputSignal=m_InputSignalPane->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		if(pInput==m_InputSignal)
		{
			//添加到集合
			pInput->SetGroupName(m_szGroupName);
			pInput->SetIsInGroup(TRUE);
			//////////////////////////////////////////////////////////////////////////
			XInputGroup* pInputGroup=NULL;

			XInputInfoInGroup* pInputInfoInGroup=new XInputInfoInGroup;
			pInputInfoInGroup->SetIndex(pInput->GetInputIndex());
			pInputInfoInGroup->SetAnotherName(pInput->GetAnotherName());
			pInputInfoInGroup->SetGroupName(m_szGroupName);
			//////////////////////////////////////////////////////////////////////////

			MAP_GROUP::iterator iter=MapInputGroup.find(m_szGroupName);

			if(iter==MapInputGroup.end())
			{
				pInputGroup=new XInputGroup;

				pInputGroup->SetGroupName(m_szGroupName);

				pInputGroup->AddVecInputGroup(pInputInfoInGroup);

				//排序
				VEC_INPUTINFOINGROUP& VecInputInGroup=pInputGroup->GetVecInputInGroup();
				sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare1);

				MapInputGroup.insert(std::pair<CString,XInputGroup*>(m_szGroupName,pInputGroup));
			}
			else
			{
				pInputGroup=iter->second;

				pInputGroup->SetGroupName(m_szGroupName);

				pInputGroup->AddVecInputGroup(pInputInfoInGroup);

				//排序
				VEC_INPUTINFOINGROUP& VecInputInGroup=pInputGroup->GetVecInputInGroup();
				sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare1);
			}

			//////////////////////////////////////////////////////////////////////////
			//把输入插入到分组根目录
			CString szInputName=pInputInfoInGroup->GetAnotherName();

			int nIndex=pInputInfoInGroup->GetIndex();

			CString szTemp;

			szTemp.Format(_T("%d"),nIndex);

			CString szChild;

			if(szInputName!=_T(""))
			{
				szChild=m_pDelegate->GetTranslationString(_T("439"),_T("输入"))+szTemp+_T("(")+szInputName+_T(")");
			}
			else
			{
				szChild=m_pDelegate->GetTranslationString(_T("439"),_T("输入"))+szTemp;
			}

			SetItemChild(hItem);

			HTREEITEM hChildchild=AddChildChild(szChild);

			m_TreeGroup.SetItemData(hChildchild,(DWORD_PTR)pInputInfoInGroup);
		}
	}

	m_TreeGroup.Expand(hItem,TVE_EXPAND);

	m_InputSignalPane->ChangeInputModel();

	GetDlgItem(IDC_BTN_ADDINGROUP)->EnableWindow(FALSE);
}

void XAddGroup::OnBnClickedOk()
{

	CDialogEx::OnOK();
}

void XAddGroup::OnBnAddGroup()
{
	//新建分组
	XGroupName dlg;

	dlg.SetInputSignalPane(m_InputSignalPane);

	dlg.SetInputSignal(m_InputSignal);

	if(IDOK==dlg.DoModal())
	{
		CString szName=dlg.GetAnotherName();

		m_szNewGroupName=szName;

		AddChild(szName);

		//////////////////////////////////////////////////////////////////////////
		MAP_GROUP& MapInputGroup=m_InputSignalPane->GetMapGroup();

		MAP_GROUP::iterator iter=MapInputGroup.find(szName);

		if(iter==MapInputGroup.end())
		{
			XInputGroup* pGroup=new XInputGroup;
			pGroup->SetGroupName(szName);
			pGroup->SetTreeItem(GetItemRoot());
			pGroup->SetType(ITEMTYPE_ROOT);
			
			MapInputGroup.insert(std::pair<CString,XInputGroup*>(szName,pGroup));
		}

		m_InputSignalPane->ChangeInputModel();
	}

	m_TreeGroup.Expand(GetItemRoot(), TVE_EXPAND);
}

void XAddGroup::OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	GetCursorPos(&point);

	CPoint tempPoint = point;
	m_TreeGroup.ScreenToClient(&tempPoint);

	UINT flags; 

	HTREEITEM  hItem = m_TreeGroup.HitTest(tempPoint, &flags);  

	m_RbItem=hItem;

	if (hItem != NULL) 
	{ 
		m_TreeGroup.SelectItem(hItem);

		m_szRbGroupName=m_TreeGroup.GetItemText(hItem);

		m_nType=(int)m_TreeGroup.GetItemData(hItem);

		ShowMenu();
	}
}

void XAddGroup::ShowMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();

	if(m_nType==ITEMTYPE_ROOT)
	{
		return;
	}

	if(m_nType==ITEMTYPE_CHILD)
	{
		menu.AppendMenu(MF_STRING, ID_GROUP_CHANGE, m_pDelegate->GetTranslationString(_T("678"), _T("修改")) + _T("(&C)"));  
	}

	menu.AppendMenu(MF_STRING,ID_GROUP_DELETE, m_pDelegate->GetTranslationString(_T("207"),_T("删除"))+ _T("(&D)"));

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 

	menu.DestroyMenu(); 
}

void XAddGroup::OnDelete()
{
	VEC_INPUTSIGNAL& VecInputSignal=m_InputSignalPane->GetVecInputSignal();

	MAP_GROUP& MapGroup=m_InputSignalPane->GetMapGroup();

	if(m_nType==ITEMTYPE_CHILD)
	{
		MAP_GROUP::iterator iter=MapGroup.find(m_szRbGroupName);

		if(iter!=MapGroup.end())
		{
			XInputGroup* pInputGroup=iter->second;

			VEC_INPUTINFOINGROUP& VecInput=pInputGroup->GetVecInputInGroup();

			for(VEC_INPUTINFOINGROUP::iterator iter1=VecInput.begin();iter1!=VecInput.end();++iter1)
			{
				XInputInfoInGroup* pInput=*iter1;

				int nIndex=pInput->GetIndex();

				for(VEC_INPUTSIGNAL::iterator iter2=VecInputSignal.begin();iter2!=VecInputSignal.end();++iter2)
				{
					XInputSignal* pInputSignal=*iter2;

					if(nIndex==pInputSignal->GetInputIndex())
					{
						pInputSignal->SetGroupName(_T(""));

						pInputSignal->SetIsInGroup(FALSE);
					}
				}
			}

			MapGroup.erase(iter);
		}

		m_TreeGroup.DeleteItem(m_RbItem);
	}
	else
	{	
		XInputInfoInGroup* pTemp=(XInputInfoInGroup*)m_TreeGroup.GetItemData(m_RbItem);

		if(pTemp==NULL)
		{
			return;
		}
		
		int nTempIndex=pTemp->GetIndex();

		HTREEITEM hRoot=m_TreeGroup.GetParentItem(m_RbItem);

		if(hRoot==NULL)
		{
			return;
		}

		CString szName=m_TreeGroup.GetItemText(hRoot);

		MAP_GROUP::iterator iter=MapGroup.find(szName);

		if(iter!=MapGroup.end())
		{
			for(VEC_INPUTSIGNAL::iterator iter2=VecInputSignal.begin();iter2!=VecInputSignal.end();++iter2)
			{
				XInputSignal* pInputSignal=*iter2;

				if(nTempIndex==pInputSignal->GetInputIndex())
				{
					pInputSignal->SetGroupName(_T(""));

					pInputSignal->SetIsInGroup(FALSE);
				}
			}

			//////////////////////////////////////////////////////////////////////////
			XInputGroup* pInputGroup=iter->second;

			VEC_INPUTINFOINGROUP& VecInput=pInputGroup->GetVecInputInGroup();

			for(VEC_INPUTINFOINGROUP::iterator iter1=VecInput.begin();iter1!=VecInput.end();)
			{
				XInputInfoInGroup* pInput=*iter1;

				if(pInput==pTemp)
				{
					iter1=VecInput.erase(iter1);
				}
				else
				{
					iter1++;
				}
			}

			m_TreeGroup.DeleteItem(m_RbItem);
		}

		//////////////////////////////////////////////////////////////////////////
		//判断组里有没有成员
		for(MAP_GROUP::iterator iter3=MapGroup.begin();iter3!=MapGroup.end();)
		{
			XInputGroup* pGroup=iter3->second;

			VEC_INPUTINFOINGROUP& pInput=pGroup->GetVecInputInGroup();

			if(pInput.size()==0)
			{
				m_TreeGroup.DeleteItem(hRoot);

				iter3=MapGroup.erase(iter3);
			}
			else
			{
				++iter3;
			}
		}
	}

	m_InputSignalPane->ChangeInputModel();
}

void XAddGroup::OnChange()
{
	CString szOldName=_T("");

	if(m_nType==ITEMTYPE_CHILD)
	{
		szOldName=m_szRbGroupName;
	}
	else
	{
		return;
	}

	//////////////////////////////////////////////////////////////////////////

	XGroupName2 dlg;
	dlg.SetInputSignalPane(m_InputSignalPane);
	dlg.SetInputSignal(m_InputSignal);
	if(IDOK==dlg.DoModal())
	{
		CString szNewName=dlg.GetAnotherName();

		//////////////////////////////////////////////////////////////////////////
		MAP_GROUP& MapGroup=m_InputSignalPane->GetMapGroup();

		MAP_GROUP::iterator iter=MapGroup.find(szOldName);

		XInputGroup* pNewGroup=NULL;

		if(iter!=MapGroup.end())
		{
			XInputGroup* pGroup=iter->second;
			//更改组名称
			pGroup->SetGroupName(szNewName);
			VEC_INPUTINFOINGROUP& VecInput=pGroup->GetVecInputInGroup();
			for(VEC_INPUTINFOINGROUP::iterator iter1=VecInput.begin();iter1!=VecInput.end();++iter1)
			{
				XInputInfoInGroup* pInput=*iter1;

				pInput->SetGroupName(szNewName);
			}
			//////////////////////////////////////////////////////////////////////////
			//修改总体输入集合组名称
			VEC_INPUTSIGNAL& VecInputSignal=m_InputSignalPane->GetVecInputSignal();
			for(VEC_INPUTSIGNAL::iterator iter2=VecInputSignal.begin();iter2!=VecInputSignal.end();++iter2)
			{
				XInputSignal* pInputSignal=*iter2;

				if(pInputSignal->GetGroupName()==szOldName)
				{
					pInputSignal->SetGroupName(szNewName);
				}
			}

			//////////////////////////////////////////////////////////////////////////
			pNewGroup=new XInputGroup;
			pNewGroup->SetGroupName(pGroup->GetGroupName());
			pNewGroup->SetType(pGroup->GetType());
			pNewGroup->SetTreeItem(pGroup->GetTreeItem());
			pNewGroup->SetVecInputInGroup(pGroup->GetVecInputInGroup());
			
			MapGroup.insert(std::pair<CString,XInputGroup*>(szNewName,pNewGroup));

			MapGroup.erase(iter);
		}

		m_TreeGroup.SetItemText(m_RbItem,szNewName);

		m_InputSignalPane->ChangeInputModel();
	}

}

HTREEITEM XAddGroup::AddRoot(CString szRoot)
{
	CString szCategories=szRoot;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = TVI_ROOT;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 0;
	item = m_TreeGroup.InsertItem(&tvinsert);

	szCategories.ReleaseBuffer();

	m_TreeGroup.SetItemData(item,(DWORD_PTR)ITEMTYPE_ROOT);

	SetItemRoot(item);

	return item;
}

void XAddGroup::SetItemRoot(HTREEITEM h)
{
	m_ItemRoot=h;
}

HTREEITEM XAddGroup::GetItemRoot()
{
	return m_ItemRoot;
}

HTREEITEM XAddGroup::AddChild(CString szChild)
{
	CString szCategories=szChild;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = GetItemRoot();
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 1;
	tvinsert.item.iSelectedImage = 1;
	item = m_TreeGroup.InsertItem(&tvinsert);

	szCategories.ReleaseBuffer();

	m_TreeGroup.SetItemData(item,(DWORD_PTR)ITEMTYPE_CHILD);

	SetItemChild(item);

	return item;
}

void XAddGroup::SetItemChild(HTREEITEM h)
{
	m_ItemChild=h;
}

HTREEITEM XAddGroup::GetItemCHild()
{
	return m_ItemChild;
}

HTREEITEM XAddGroup::AddChildChild(CString szChildChild)
{
	CString szCategories=szChildChild;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = GetItemCHild();
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 2;
	item = m_TreeGroup.InsertItem(&tvinsert);

	szCategories.ReleaseBuffer();

	//m_TreeGroup.SetItemData(item,(DWORD_PTR)ITEMTYPE_CHILDCHILD);

	return item;
}

