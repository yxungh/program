// InputSignal.cpp : 实现文件
//

#include "stdafx.h"
#include "XScenePane.h"
#include "..\resource.h"
#include "..\MainFrm.h"
#include "XDelegateScenePane.h"
#include "XDataScenePane.h"
#include "XSceneInfo.h"
#include "XSceneGroupInfo.h"
#include "XReName.h"


#define ITEM_SCENELIST  1
#define ITEM_SCENENAME  2

IMPLEMENT_DYNAMIC(XScenePane, CDockablePane)

	XScenePane::XScenePane()
{
	m_pDelegate = NULL;
	m_bDisableAnimation = TRUE;
	m_nSlideSteps = 1;
	m_pInputSignalPane=NULL;
	m_szSceneName=_T("");
	m_RootItem=NULL;
	m_RbItem=NULL;
	m_RootItem=NULL;
	m_ChildItem=NULL;
	m_ChildChildItem=NULL;
}

XScenePane::~XScenePane()
{
	ClearMapScene();
	ClearMapItem();
	ClearMapItemName();
	ClearSceneGroup();
}

BEGIN_MESSAGE_MAP(XScenePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, ID_SCENETREE, OnDblclkTreeVcard)
	ON_NOTIFY(NM_RCLICK, ID_SCENETREE, OnNMRClickTree)
	ON_COMMAND(ID_SCENE_DELETE,OnDeleteScene)
	ON_COMMAND(ID_SCENE_RENAME,OnReSceneName)
	ON_COMMAND(ID_SCENE_REMOVE,OnReMove)
	ON_COMMAND(ID_SCENE_DELETEGROUP,OnDeleteGroup)
	ON_COMMAND(ID_SCENE_RENAMEGROUP,OnReNameGroup)

	ON_COMMAND(ID_COPYORDER,OnCopyOrder)

END_MESSAGE_MAP()



// XScenePane 消息处理程序

void XScenePane::ClearMapItem()
{
	m_MapItem.clear();
}

void XScenePane::ClearMapItemName()
{
	m_MapItemName.clear();
}

void XScenePane::ClearSceneGroup()
{
	for(MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.begin();iter!=m_MapSceneGroup.end();++iter)
		delete iter->second;

	m_MapSceneGroup.clear();
}

void XScenePane::ClearMapScene()
{
	for(MAP_SCENE::iterator iter=m_MapScene.begin();iter!=m_MapScene.end();++iter)
		delete iter->second;

	m_MapScene.clear();
}

void XScenePane::SetDelegate(XDelegateScenePane* pDelegate)
{
	m_pDelegate = pDelegate;
}

XDelegateScenePane* XScenePane::GetDelegate()
{
	return m_pDelegate;
}

void XScenePane::SetInputSignalPane(XInputSignalPane* pPane)
{
	m_pInputSignalPane=pPane;
}

void XScenePane::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}

void XScenePane::Init()
{
	CreatePane();
	ChangeSceneTreeModel();
}

void XScenePane::InitData()
{

}

void XScenePane::CreatePane()
{
	CWnd* pWnd = m_pDelegate->GetCWND();
	CMainFrame* pMainFrame = (CMainFrame*)pWnd;
	CString szTitle = m_pDelegate->GetTranslationString(_T("388"), _T("场景"));

	if (!Create(szTitle, pMainFrame, CRect(0, 0, 200, 50), TRUE, 
		ID_INPUTSIGNALPANE, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_FLOAT_MULTI, 
		AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE))
		return; 

	EnableDocking(CBRS_ALIGN_LEFT);
	pMainFrame->DockPane(this);

	CSize size(200,200);
	CDockablePane::SetMinSize(size);

	//CDockablePane::SetResizeMode(TRUE);

	DockToWindow(m_pInputSignalPane,CBRS_BOTTOM);
}

void XScenePane::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("388"), _T("场景")));
	ChangeSceneTreeModel();
}

int XScenePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!InitImageList())
		return -1; 

	if (!InitTreeCtrl())
		return -1;

	return 0;
}

BOOL XScenePane::InitImageList()
{
	if (!m_ImageList.Create(24, 24, ILC_COLOR32|ILC_MASK, 0, 1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCENE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_VIEW));

	return TRUE;
}

BOOL XScenePane::InitTreeCtrl()
{
	m_SceneTree.SetScenePane(this);

	if (m_SceneTree.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, CRect(0, 0, 0, 0), this, ID_SCENETREE))
	{
		m_SceneTree.SetImageList(&m_ImageList, TVSIL_NORMAL);
		return TRUE;
	}
	else
		return FALSE;

	return TRUE;
}

CString XScenePane::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

int XScenePane::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

void XScenePane::GetData(CArchive& arch)
{
	XDataScenePane::GetData(this,arch);
}

void XScenePane::SaveData(CArchive& arch)
{
	XDataScenePane::SaveData(this,arch);
}

MAP_SCENEGROUP& XScenePane::GetMapSceneGroup()
{
	return m_MapSceneGroup;
}

void XScenePane::ResetData()
{

}

void XScenePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void XScenePane::AdjustLayout()
{
	if(nullptr == GetSafeHwnd())
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	CRect rectTree = rectClient;
	m_SceneTree.SetWindowPos(NULL, rectTree.left + 2, rectTree.top + 1, rectTree.Width() - 3, rectTree.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void XScenePane::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rect, &bruDB);

	CRect rectTreeCtrl;
	m_SceneTree.GetWindowRect(rectTreeCtrl);
	ScreenToClient(rectTreeCtrl);
	rectTreeCtrl.InflateRect(1, 1);
	dc.Draw3dRect(rectTreeCtrl, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

MAP_SCENE& XScenePane::GetMapScene()
{
	return m_MapScene;
}

BOOL XScenePane::JudgeSceneName(CString szName)
{
	MAP_SCENE::iterator iter=m_MapScene.find(szName);
	
	if(iter!=m_MapScene.end())
		return TRUE;

	return FALSE;
}

HTREEITEM XScenePane::AddSceneToTree(int nSceneIndex,CString szSceneName,int nType,CString szSceneGroup)
{
	if(szSceneName==_T(""))
		return NULL;

	HTREEITEM itemTemp=NULL;

	if(szSceneGroup!=_T(""))
	{
		//这里需要添加到组
		//根据组名称得到  节点（map）

		HTREEITEM itemGroup=NULL;
		MAP_ITEMNAME::iterator iter=m_MapItemName.find(szSceneGroup);

		if(iter!=m_MapItemName.end())
			itemGroup=iter->second;
	
		SetItemChild(itemGroup);
		HTREEITEM itemChildChild=AddChildChild(szSceneName);
		itemTemp=itemChildChild;
		//////////////////////////////////////////////////////////////////////////
		MAP_SCENE::iterator iterScene=m_MapScene.find(szSceneName);

		if(iterScene==m_MapScene.end())
		{
			XSceneInfo* pInfo=new XSceneInfo;

			pInfo->SetType(nType);
			pInfo->SetSceneIndex(nSceneIndex);
			pInfo->SetIsInGroup(TRUE);
			pInfo->SetGroupName(szSceneGroup);
			pInfo->SetSceneName(szSceneName);

			m_MapScene.insert(std::pair<CString,XSceneInfo*>(szSceneName,pInfo));
		}

		m_SceneTree.Expand(itemGroup,TVE_EXPAND);
	}
	else
	{
		HTREEITEM item=NULL;

		switch(nType)
		{
		case SCREENMODEL_SPLIC:
		case SCREENMODEL_MATRIX:
			{
				MAP_ITEM::iterator iter=m_MapItem.find(ITEM_SIGNAL);

				if(iter!=m_MapItem.end())
					item=iter->second;

				SetItemChild(item);
				HTREEITEM itemChildChild=AddChildChild(szSceneName);
				itemTemp=itemChildChild;

				m_SceneTree.Expand(item,TVE_EXPAND);
			}
			break;
		case SCREENMODEL_DEV:
			{
				MAP_ITEM::iterator iter=m_MapItem.find(ITEM_DEV);

				if(iter!=m_MapItem.end())
					item=iter->second;

				SetItemChild(item);
				HTREEITEM itemChildChild=AddChildChild(szSceneName);
				itemTemp=itemChildChild;

				m_SceneTree.Expand(item,TVE_EXPAND);
			}
			break;
		default:
			break;
		}

		//////////////////////////////////////////////////////////////////////////
		MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

		if(iter==m_MapScene.end())
		{
			XSceneInfo* pInfo=new XSceneInfo;

			pInfo->SetType(nType);
			pInfo->SetSceneIndex(nSceneIndex);
			pInfo->SetIsInGroup(FALSE);
			pInfo->SetGroupName(_T(""));
			pInfo->SetSceneName(szSceneName);

			m_MapScene.insert(std::pair<CString,XSceneInfo*>(szSceneName,pInfo));
		}
	}

	return itemTemp;
}

void XScenePane::AddViewNameToScene(HTREEITEM item,CString szSceneName,int nIndex,CString szViewName)
{
	if(item==NULL)
		return;

	MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

	if(iter!=m_MapScene.end())
	{
		XSceneInfo* pInfo=iter->second;
		pInfo->InsertMapSelScene(szViewName,nIndex);		
		SetItemChildChild(item);
		AddChildChildChild(szViewName);
	}
}

void XScenePane::AddSceneIntoGroup(HTREEITEM hItemDragS,HTREEITEM hItemDragD)
{
	//拖拽到组
	//itemDragS为拖拽节点，itemDragD被拖拽节点
	if(hItemDragS==NULL||hItemDragD==NULL)
		return;

	DWORD dwDataS=m_SceneTree.GetItemData(hItemDragS);
	DWORD dwDataD=m_SceneTree.GetItemData(hItemDragD);

	CString szItemTextS=m_SceneTree.GetItemText(hItemDragS);
	CString szItemTextD=m_SceneTree.GetItemText(hItemDragD);

	if(dwDataD==ITEM_DEV
		||dwDataD==ITEM_SIGNAL
		||dwDataD==ITEM_SCENEGROUP)
		return;

	XSceneInfo* pInfoS=GetSceenInfoBySceneName(szItemTextS);
	if(pInfoS==NULL)
		return;

	if(!pInfoS->GetIsInGroup())
	{
		HTREEITEM itemS=m_SceneTree.GetParentItem(hItemDragS);

		//拖拽不在组内
		if(dwDataD==ITEM_SCENE)
		{
			//被拖拽为场景
			HTREEITEM itemD=m_SceneTree.GetParentItem(hItemDragD);
			
			XSceneInfo* pInfoD=GetSceenInfoBySceneName(szItemTextD);
			if(pInfoD==NULL)
				return;

			if(!pInfoD->GetIsInGroup())
			{
				//被拖拽不在组内
				//如果不在同一类别内
				if(itemS!=itemD)
					return;
				//根节点
				//HTREEITEM ItemRoot=m_SceneTree.GetParentItem(itemD);
				DWORD dwItemRoot=m_SceneTree.GetItemData(itemD);

				CString szFrontName=m_pDelegate->GetTranslationString(_T("693"),_T("分组"));
				CString szGroupName=GetGroupNameByFrontName(szFrontName);

				SetItemRoot(itemS);
				AddChild(szGroupName);
				//////////////////////////////////////////////////////////////////////////
				pInfoS->SetIsInGroup(TRUE);
				pInfoS->SetGroupName(szGroupName);

				pInfoD->SetIsInGroup(TRUE);
				pInfoD->SetGroupName(szGroupName);

				//////////////////////////////////////////////////////////////////////////
				MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szGroupName);
				XSceneGroupInfo* pInfo=NULL;
				if(iter==m_MapSceneGroup.end())
				{
					pInfo=new XSceneGroupInfo;

					pInfo->SetGroupName(szGroupName);
					pInfo->SetSceneType(dwItemRoot);

					m_MapSceneGroup.insert(std::pair<CString,XSceneGroupInfo*>(szGroupName,pInfo));
				}
			}
			else
			{
				//被拖拽在组内
				CString szItemGroupName=m_SceneTree.GetItemText(itemD);

				pInfoS->SetIsInGroup(TRUE);
				pInfoS->SetGroupName(szItemGroupName);
			}
		}
		else if(dwDataD==ITEM_SCENEGROUP)
		{
			//被拖拽为组
			HTREEITEM itemD=m_SceneTree.GetParentItem(hItemDragD);
			//不在同一类
			if(itemD!=itemS)
				return;

			CString szItemGroupName=m_SceneTree.GetItemText(hItemDragD);

			pInfoS->SetIsInGroup(TRUE);
			pInfoS->SetGroupName(szItemGroupName);

		}
		else if(dwDataD==ITEM_SCENEROOT)
			//被拖拽为列别,不处理
			return;
	}
	else
	{
		//拖拽在组内
		HTREEITEM ItemGroupS=m_SceneTree.GetParentItem(hItemDragS);
		HTREEITEM ItemRootS=m_SceneTree.GetParentItem(ItemGroupS);

		XSceneInfo* pInfoS=GetSceenInfoBySceneName(szItemTextS);
		if(pInfoS==NULL)
			return;

		if(dwDataD==ITEM_SCENE)
		{
			//被拖拽为场景
			HTREEITEM itemD=m_SceneTree.GetParentItem(hItemDragD);

			XSceneInfo* pInfoD=GetSceenInfoBySceneName(szItemTextD);
			if(pInfoD==NULL)
				return;

			if(!pInfoD->GetIsInGroup())
			{
				//被拖拽不在组里
				//如果不在同意类别内
				if(ItemRootS!=itemD)
					return;

				pInfoS->SetIsInGroup(FALSE);
				pInfoS->SetGroupName(_T(""));
				//////////////////////////////////////////////////////////////////////////
				//如果组里没有成员，则删除组
				CString szGroupName=m_SceneTree.GetItemText(ItemGroupS);
				MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szGroupName);

				if(iter!=m_MapSceneGroup.end())
				{
					//如果没有删除组
					if(!JudgetGroupHaveScene(szGroupName))
						m_MapSceneGroup.erase(iter);
				}
			}
			else
			{
				HTREEITEM ItemRootD=m_SceneTree.GetParentItem(itemD);
				if(ItemRootS!=ItemRootD)
					return;
				
				if(ItemGroupS!=itemD)
				{
					CString ItemGroupName=m_SceneTree.GetItemText(itemD);

					//不同组
					pInfoS->SetIsInGroup(TRUE);
					pInfoS->SetGroupName(ItemGroupName);
				}
				else
					//同组
					return;
			}
		}
		else if(dwDataD==ITEM_SCENEGROUP)
		{
			//被拖拽为组
			HTREEITEM ItemRootD=m_SceneTree.GetParentItem(hItemDragD);
			//不在同一类
			if(ItemRootS!=ItemRootD)
				return;

			if(ItemGroupS!=hItemDragD)
			{
				//不在同一组
				CString szGroupNameD=m_SceneTree.GetItemText(hItemDragD);

				pInfoS->SetIsInGroup(TRUE);
				pInfoS->SetGroupName(szGroupNameD);
			}
			else
				//在同一组
				return;
		}
		else if(dwDataD==ITEM_SCENEROOT)
			//被拖拽为列别，不处理
			return;
	}

	ChangeSceneTreeModel();
}

void XScenePane::ChangeSceneTreeModel()
{
	m_SceneTree.DeleteAllItems();
	ClearMapItemName();
	ClearMapItem();

	//类别节点
	AddRoot(m_pDelegate->GetTranslationString(_T("728"),_T("多页面场景")),ITEM_DEV);
	AddRoot(m_pDelegate->GetTranslationString(_T("745"),_T("单页面场景")),ITEM_SIGNAL);
	//////////////////////////////////////////////////////////////////////////
	//组节点
	for(MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.begin();iter!=m_MapSceneGroup.end();++iter)
	{
		CString szGroupName=iter->first;
		XSceneGroupInfo* pInfo=iter->second;
		int nType=pInfo->GetSceneType();
		MAP_ITEM::iterator iterRoot=m_MapItem.find(nType);

		if(iterRoot!=m_MapItem.end())
		{
			HTREEITEM itemRoot=iterRoot->second;
			SetItemRoot(itemRoot);
			AddChild(szGroupName);
			m_SceneTree.Expand(itemRoot,TVE_EXPAND);
		}
	}
	//场景节点
	for(MAP_SCENE::iterator iter=m_MapScene.begin();iter!=m_MapScene.end();++iter)
	{
		CString szSceneName=iter->first;

		XSceneInfo* pInfo=iter->second;
		int nTempType=pInfo->GetType();
		//////////////////////////////////////////////////////////////////////////
		int nType=0;
		switch(nTempType)
		{
		case SCREENMODEL_DEV:
			nType=ITEM_DEV;
			break;
		case SCREENMODEL_SPLIC:
		case SCREENMODEL_MATRIX:
			nType=ITEM_SIGNAL;
			break;
		default:
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		if(pInfo->GetIsInGroup())
		{
			//在组里
			CString szGroupName=pInfo->GetGroupName();
			MAP_SCENEGROUP::iterator iterGroup=m_MapSceneGroup.find(szGroupName);

			if(iterGroup!=m_MapSceneGroup.end())
			{
				MAP_ITEMNAME::iterator iterItem=m_MapItemName.find(szGroupName);
				if(iterItem!=m_MapItemName.end())
				{
					HTREEITEM itemGroup=iterItem->second;

					SetItemChild(itemGroup);
					HTREEITEM item=AddChildChild(szSceneName);
					SetItemChildChild(item);

					MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();
					for(MAP_SELSCENE::iterator iter=MapSelScene.begin();iter!=MapSelScene.end();++iter)
					{
						CString szViewName=iter->second;
						AddChildChildChild(szViewName);
					}
					m_SceneTree.Expand(itemGroup,TVE_EXPAND);
				}
			}
		}
		else
		{
			//不在组里
			MAP_ITEM::iterator iterRoot=m_MapItem.find(nType);

			if(iterRoot!=m_MapItem.end())
			{
				HTREEITEM itemRoot=iterRoot->second;

				SetItemChild(itemRoot);
				HTREEITEM item=AddChildChild(szSceneName);
				SetItemChildChild(item);

				MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();
				for(MAP_SELSCENE::iterator iter=MapSelScene.begin();iter!=MapSelScene.end();++iter)
				{
					CString szViewName=iter->second;
					AddChildChildChild(szViewName);
				}

				m_SceneTree.Expand(itemRoot,TVE_EXPAND);
			}
		}	
	}
}

CString XScenePane::GetGroupNameByFrontName(CString szName)
{
	CString szTemp;

	int n=1;
	while(1)
	{
		szTemp.Format(_T("%d"),n);
		szTemp=szName+szTemp;

		MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szTemp);

		if(iter==m_MapSceneGroup.end())
			break;
		n++;
	}
	return szTemp;
}

XSceneInfo* XScenePane::GetSceenInfoBySceneName(CString szSceneName)
{
	XSceneInfo* pInfo=NULL;
	MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

	if(iter!=m_MapScene.end())
		pInfo=iter->second;

	return pInfo;
}

void XScenePane::OnDblclkTreeVcard(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	HTREEITEM hItem=m_SceneTree.GetSelectedItem();

	if(hItem==NULL)
		return;

	DWORD dwData=m_SceneTree.GetItemData(hItem);
	CString szSceneName=m_SceneTree.GetItemText(hItem);

	

	//如果是三级节点，获取父节点
	CString szViewName=_T("");
	if(dwData==(DWORD)ITEM_SCENEVIEWNAME)
	{
		szViewName=m_SceneTree.GetItemText(hItem);

		HTREEITEM hParentItem=m_SceneTree.GetParentItem(hItem);
		szSceneName=m_SceneTree.GetItemText(hParentItem);
	}

	if(szSceneName!=_T(""))
	{
		MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

		if(iter!=m_MapScene.end())
		{
			XSceneInfo* pInfo=iter->second;

			int nSceneIndex=pInfo->GetSceneIndex();
			int nType=pInfo->GetType();

			switch(nType)
			{
			case SCREENMODEL_DEV:
				{
					if(dwData==ITEM_SCENE)
					{
						m_pDelegate->OpenAllScene(szSceneName,nSceneIndex);
					}
					else if(dwData==ITEM_SCENEVIEWNAME)
					{
						m_pDelegate->OpenOneSceneOfAll(szSceneName,nSceneIndex,szViewName);
					}
				}
				break;
			case SCREENMODEL_SPLIC:
			case SCREENMODEL_MATRIX:
				{
					CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);
					if(!PathFileExists(szPath))
					{
						m_pDelegate->MessageBoxFromKey(_T("730"),_T("调取场景文件不存在！"),MB_OK);
						return;
					}

					MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

					if(iter!=m_MapScene.end())
					{
						XSceneInfo* pInfo=iter->second;

						MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();
						MAP_SELSCENE::iterator iterSel=MapSelScene.begin();
						CString szViewName=iterSel->second;
						m_pDelegate->OpenScene(szSceneName,nSceneIndex,szViewName);
					}	
				}
				break;
			default:
				break;
			}
		}
	}
}

void XScenePane::OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	GetCursorPos(&point);

	CPoint tempPoint = point;
	m_SceneTree.ScreenToClient(&tempPoint);

	UINT flags; 

	HTREEITEM  hItem = m_SceneTree.HitTest(tempPoint, &flags);  

	if (hItem != NULL) 
	{ 
		m_RbItem=hItem;
		m_SceneTree.SelectItem(hItem);
		m_szSceneName=m_SceneTree.GetItemText(hItem);
		int nData=m_SceneTree.GetItemData(hItem);

		if(nData==ITEM_DEV
			||nData==ITEM_SIGNAL)
			return;
		else if(nData==ITEM_SCENEGROUP)
			ShowGroupMenu();
		else if(nData==ITEM_SCENE)
			ShowMenu();
		else if(nData==ITEM_SCENEVIEWNAME)
			ShowCopyMenu();

	}
}

void XScenePane::ShowCopyMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_COPYORDER,m_pDelegate->GetTranslationString(_T("759"),_T("拷贝指令到剪切板")) + _T("(&C)"));

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 
	menu.DestroyMenu();
}

void XScenePane::OnCopyOrder()
{
	if(m_RbItem==NULL)
		return;

	DWORD dwData=m_SceneTree.GetItemData(m_RbItem);
	CString szViewName=m_SceneTree.GetItemText(m_RbItem);

	CString szSceneName=_T("");
	if(dwData==(DWORD)ITEM_SCENEVIEWNAME)
	{
		HTREEITEM hParentItem=m_SceneTree.GetParentItem(m_RbItem);
		szSceneName=m_SceneTree.GetItemText(hParentItem);
	}

	if(szSceneName!=_T(""))
	{
		MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

		if(iter!=m_MapScene.end())
		{
			XSceneInfo* pInfo=iter->second;

			int nSceneIndex=pInfo->GetSceneIndex();
			int nType=pInfo->GetType();

			TRACE(_T("Type=%d\n"),nType);
			if(nType==3)
			{
				m_pDelegate->CopyOrderToShare(szSceneName,nSceneIndex,szViewName);
			}
			else if(nType==2)
			{
				CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);
				if(!PathFileExists(szPath))
				{
					m_pDelegate->MessageBoxFromKey(_T("730"),_T("调取场景文件不存在！"),MB_OK);
					return;
				}

				MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

				if(iter!=m_MapScene.end())
				{
					XSceneInfo* pInfo=iter->second;

					MAP_SELSCENE& MapSelScene=pInfo->GetMapSelScene();
					MAP_SELSCENE::iterator iterSel=MapSelScene.begin();
					CString szViewName=iterSel->second;
					//m_pDelegate->OpenScene(szSceneName,nSceneIndex,szViewName);
					m_pDelegate->CopySingleOrderToShare(szSceneName,nSceneIndex,szViewName);
				}	
			}
		}
	}
}

void XScenePane::ShowMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_SCENE_RENAME,m_pDelegate->GetTranslationString(_T("678"),_T("修改")) + _T("(&M)"));

	if(JudgeSceneIsInGroup(m_szSceneName))
		menu.AppendMenu(MF_STRING,ID_SCENE_REMOVE,m_pDelegate->GetTranslationString(_T("664"),_T("从分组中移除")) + _T("(&R)"));

	menu.AppendMenu(MF_STRING, ID_SCENE_DELETE, m_pDelegate->GetTranslationString(_T("207"), _T("删除")) + _T("(&D)"));
	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 
	menu.DestroyMenu();
}

void XScenePane::ShowGroupMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_SCENE_RENAMEGROUP, m_pDelegate->GetTranslationString(_T("678"), _T("修改")) + _T("(&M)"));
	menu.AppendMenu(MF_STRING, ID_SCENE_DELETEGROUP, m_pDelegate->GetTranslationString(_T("207"), _T("删除")) + _T("(&D)"));
	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 
	menu.DestroyMenu();
}

void XScenePane::OnDeleteScene()
{
	//删除场景
	if(m_RbItem==NULL)
		return;

	HTREEITEM item=m_SceneTree.GetParentItem(m_RbItem);
	if(item==NULL)
		return;

	DWORD dwDate=m_SceneTree.GetItemData(item);
	CString szSceneName=m_szSceneName;

	if(szSceneName!=_T(""))
	{
		MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);
		if(iter!=m_MapScene.end())
		{
			XSceneInfo* pInfo=iter->second;
			int nSceneIndex=pInfo->GetSceneIndex();
			m_pDelegate->DeleteScene(nSceneIndex);

			if(dwDate==ITEM_DEV)
			{
				int n=m_pDelegate->GetVecBaseManageSize();
				for(int i=1;i<=n;i++)
				{
					CString szPath=m_pDelegate->GetAllSceneFilePath(nSceneIndex,szSceneName,i);
					::DeleteFile(szPath);
				}
			}
			else
			{
				CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);
				::DeleteFile(szPath);
			}

			m_SceneTree.DeleteItem(m_RbItem);	
			m_MapScene.erase(iter);
		}
	}
}

void XScenePane::OnReSceneName()
{
	//重命名场景
	if(m_RbItem==NULL)
		return;

	XReName dlg;
	dlg.SetDelegate(this);

	CString szTemp=GetTranslationString(_T("732"),_T("更改场景名称"));
	dlg.SetTitle(szTemp);

	if(dlg.DoModal()==IDOK)
	{
		CString szNewName=dlg.GetScreenName();
		CString szSceneName=m_szSceneName;

		if(szSceneName!=_T(""))
		{
			MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);
			if(iter!=m_MapScene.end())
			{
				XSceneInfo* pInfo=iter->second;
				int nSceneIndex=pInfo->GetSceneIndex();
				m_pDelegate->DeleteScene(nSceneIndex);

				CString szOldPath=m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);
				CString szNewPath=m_pDelegate->GetSceneFilePath(nSceneIndex,szNewName);

				if(!PathFileExists(szOldPath))
				{
					m_pDelegate->MessageBoxFromKey(_T("729"),_T("所修改场景文件不存在！"),MB_OK);
					return;
				}

				CFile::Rename(szOldPath,szNewPath);
				m_SceneTree.SetItemText(m_RbItem,szNewName);
			}

			//////////////////////////////////////////////////////////////////////////
			MAP_SCENE::iterator iterScene=m_MapScene.find(szSceneName);

			if(iterScene!=m_MapScene.end())
			{
				XSceneInfo* pInfo=iterScene->second;

				XSceneInfo* pNew=new XSceneInfo;

				pNew->SetGroupName(szNewName);
				pNew->SetIsInGroup(pInfo->GetIsInGroup());
				pNew->SetSceneIndex(pInfo->GetSceneIndex());
				pNew->SetSceneName(pInfo->GetSceneName());
				pNew->SetType(pInfo->GetType());
				pNew->CopyMapSelScene(pInfo->GetMapSelScene());

				m_MapScene.erase(iterScene);
				m_MapScene.insert(std::pair<CString,XSceneInfo*>(szNewName,pNew));
			}
		}
	}
}

void XScenePane::OnReMove()
{
	//从分组中移除
	if(m_RbItem==NULL)
		return;

	MAP_SCENE::iterator iterScene=m_MapScene.find(m_szSceneName);

	if(iterScene!=m_MapScene.end())
	{
		XSceneInfo* pInfoScene=iterScene->second;

		pInfoScene->SetGroupName(_T(""));
		pInfoScene->SetIsInGroup(FALSE);
	}

	//////////////////////////////////////////////////////////////////////////
	HTREEITEM item=m_SceneTree.GetParentItem(m_RbItem);
	CString szGroupName=m_SceneTree.GetItemText(item);

	MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szGroupName);

	if(iter!=m_MapSceneGroup.end())
	{
		//如果没有删除组
		if(!JudgetGroupHaveScene(szGroupName))
			m_MapSceneGroup.erase(iter);
	}

	ChangeSceneTreeModel();
}

BOOL XScenePane::JudgetGroupHaveScene(CString szGroupName)
{
	BOOL bFlag=FALSE;

	for(MAP_SCENE::iterator iter=m_MapScene.begin();iter!=m_MapScene.end();++iter)
	{
		XSceneInfo* pInfo=iter->second;
		if(szGroupName==pInfo->GetGroupName())
			bFlag=TRUE;
	}

	return bFlag;
}

void XScenePane::OnDeleteGroup()
{
	if(m_RbItem==NULL)
		return;

	CString szGroupName=m_SceneTree.GetItemText(m_RbItem);

	for(MAP_SCENE::iterator iter=m_MapScene.begin();iter!=m_MapScene.end();++iter)
	{
		XSceneInfo* pInfo=iter->second;
		if(szGroupName==pInfo->GetGroupName())
		{
			pInfo->SetGroupName(_T(""));
			pInfo->SetIsInGroup(FALSE);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szGroupName);
	if(iter!=m_MapSceneGroup.end())
	{
		if(!JudgetGroupHaveScene(szGroupName))
			m_MapSceneGroup.erase(iter);
	}

	ChangeSceneTreeModel();
}

BOOL XScenePane::JudgeSceneIsInGroup(CString szName)
{
	BOOL bFlag=FALSE;
	CString szSceneName=m_szSceneName;

	if(szSceneName!=_T(""))
	{
		MAP_SCENE::iterator iter=m_MapScene.find(szSceneName);

		if(iter!=m_MapScene.end())
		{
			XSceneInfo* pInfo=iter->second;
			bFlag=pInfo->GetIsInGroup();
		}
	}

	return bFlag;
}

void XScenePane::OnReNameGroup()
{
	if(m_RbItem==NULL)
		return;

	CString szGroupName=m_SceneTree.GetItemText(m_RbItem);

	XReName dlg;
	dlg.SetDelegate(this);

	CString szTemp=GetTranslationString(_T("733"),_T("更改组名称"));
	dlg.SetTitle(szTemp);

	if(dlg.DoModal()==IDOK)
	{
		CString szNewName=dlg.GetScreenName();
		MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szGroupName);
		XSceneGroupInfo* pNewInfo=new XSceneGroupInfo;

		if(iter!=m_MapSceneGroup.end())
		{
			for(MAP_SCENE::iterator iterScene=m_MapScene.begin();iterScene!=m_MapScene.end();++iterScene)
			{
				XSceneInfo* pSceenInfo=iterScene->second;
				if(pSceenInfo->GetGroupName()==szGroupName)
				{
					pSceenInfo->SetGroupName(szNewName);
					pSceenInfo->SetIsInGroup(TRUE);
				}
			}

			//////////////////////////////////////////////////////////////////////////
			XSceneGroupInfo* pInfo=iter->second;

			pNewInfo->SetGroupName(szNewName);
			pNewInfo->SetSceneIndex(pInfo->GetSceneIndex());
			pNewInfo->SetSceneName(pInfo->GetSceneName());
			pNewInfo->SetSceneType(pInfo->GetSceneType());

			m_MapSceneGroup.erase(iter);
		}

		m_MapSceneGroup.insert(std::pair<CString,XSceneGroupInfo*>(szNewName,pNewInfo));
	}

	ChangeSceneTreeModel();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
HTREEITEM XScenePane::AddRoot(CString szRoot,int nType)
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
	item = m_SceneTree.InsertItem(&tvinsert);
	//类别-节点
	m_MapItem.insert(std::pair<int,HTREEITEM>(nType,item));
	m_SceneTree.SetItemData(item,nType);
	szCategories.ReleaseBuffer();
	SetItemRoot(item);

	return item;
}

void XScenePane::SetItemRoot(HTREEITEM h)
{
	m_RootItem=h;
}

HTREEITEM XScenePane::GetItemRoot()
{
	return m_RootItem;
}

HTREEITEM XScenePane::AddChild(CString szChild)
{
	CString szCategories=szChild;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = GetItemRoot();
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 0;
	item = m_SceneTree.InsertItem(&tvinsert);

	m_MapItemName.insert(std::pair<CString,HTREEITEM>(szChild,item));
	m_SceneTree.SetItemData(item,ITEM_SCENEGROUP);
	szCategories.ReleaseBuffer();
	return item;
}


void XScenePane::SetItemChild(HTREEITEM h)
{
	m_ChildChildItem=h;
}

HTREEITEM XScenePane::GetItemChild()
{
	return m_ChildChildItem;
}

HTREEITEM XScenePane::AddChildChild(CString szChildChild)
{
	CString szCategories=szChildChild;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = GetItemChild();
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 1;
	tvinsert.item.iSelectedImage = 1;
	item = m_SceneTree.InsertItem(&tvinsert);
	m_SceneTree.SetItemData(item,ITEM_SCENE);
	szCategories.ReleaseBuffer();

	return item;
}


void XScenePane::SetItemChildChild(HTREEITEM h)
{
	m_ChildChildChildItem=h;
}

HTREEITEM XScenePane::GetItemChildChild()
{
	return m_ChildChildChildItem;
}

HTREEITEM XScenePane::AddChildChildChild(CString szChildChildChild)
{
	CString szCategories=szChildChildChild;

	HTREEITEM item = NULL;

	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent = GetItemChildChild();
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren = 1; 
	tvinsert.item.pszText = szCategories.GetBuffer();
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 2;
	item = m_SceneTree.InsertItem(&tvinsert);
	m_SceneTree.SetItemData(item,ITEM_SCENEVIEWNAME);
	szCategories.ReleaseBuffer();

	return item;
}