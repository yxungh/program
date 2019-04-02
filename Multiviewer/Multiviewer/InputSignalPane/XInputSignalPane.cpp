// InputSignal.cpp : 实现文件
//

#include "stdafx.h"
#include "XInputSignalPane.h"
#include "XDelegateInputSignalPane.h"
#include "XConstantIM.h"
#include "..\resource.h"
#include "..\MainFrm.h"
#include "XInputSignal.h"
#include "XInputSignalExpand.h"
#include "AddExpandDlg.h"
#include "EditExpandDlg.h"
#include "XDataInputSignalPane.h"
#include "SetOSDDlg.h"
#include "XScreenManage.h"
#include "XInputSignalCutDlg.h"
#include "XSendDataInputSignal.h"
#include "XBorderOverlayDlg.h"
#include "XAttributeDlg.h"
#include "XEDIDDlg.h"
#include "XSetAnotherNameDlg.h"
#include "XChangeChanelDlg.h"
#include "XUltraAttributeDlg.h"
#include "XAnotherNameInfo.h"
#include "XAddGroup.h"
#include "XInputGroup.h"
#include "XInputInfoInGroup.h"
#include "XGroupName2.h"
#include <algorithm>




IMPLEMENT_DYNAMIC(XInputSignalPane, CDockablePane)

	XInputSignalPane::XInputSignalPane()
{
	m_pDelegate = NULL;
	m_InputCount = 32;
}

XInputSignalPane::~XInputSignalPane()
{
	ClearVecInputSignal();
	ClearNameInfo();
	ClearInputGroup();
	ClearImageList();
}

void XInputSignalPane::ClearVecInputSignal()
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
		delete *iter;

	m_VecInputSignal.clear();
}

void XInputSignalPane::ClearNameInfo()
{
	for(VEC_NAMEINFO::iterator iter=m_VecNameInfo.begin();iter!=m_VecNameInfo.end();++iter)
		delete *iter;

	m_VecNameInfo.clear();
}

void XInputSignalPane::ClearInputGroup()
{
	for(MAP_GROUP::iterator iter=m_MapGroup.begin();iter!=m_MapGroup.end();++iter)
		delete iter->second;

	m_MapGroup.clear();
}

void XInputSignalPane::ClearImageList()
{
	if (NULL != m_ImageList.m_hImageList)
		m_ImageList.DeleteImageList();
}

BEGIN_MESSAGE_MAP(XInputSignalPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, ID_INPUTSIGNAL_TREECTRL, OnNMRClickTree)
	ON_COMMAND(ID_EDITINPUTSIGNALEXPAND, OnEditExpand)
	ON_COMMAND(ID_ADDINPUTSIGNALEXPAND, OnAddExpand)
	ON_COMMAND(ID_DELINPUTSIGNALEXPAND, OnDelExpand)
	ON_COMMAND(ID_SETINPUTSIGNALDEFAULTEXPAND, OnSetDefaultExpand)
	ON_COMMAND(ID_SETOSD, OnSetOSD)
	ON_COMMAND(ID_INPUTSIGNALCUT, OnInputSignalCut)
	ON_COMMAND(ID_BORDEROVERLAT,OnBorderOverlay)
	ON_COMMAND(ID_EDID,OnSetEDID)
	ON_COMMAND(ID_ATTRIBUTE_SIGNAL,OnAttribute)
	ON_COMMAND(ID_SETANOTHERNAME,OnSetAnotherName)
	ON_COMMAND(ID_CHANGEANOTHERNAME,OnChangeAnotherName)
	ON_COMMAND(ID_SELECTCHENAL,OnSelectChanel)
	ON_COMMAND(ID_IPSTREAMADDR,OnIPStreamAddr)
	ON_COMMAND(ID_SETPANENET,OnPaneIPSet)
	ON_COMMAND(ID_ADDGROUP,OnAddGroup)
	ON_COMMAND(ID_DELFROMGROUP,OnDelFromGroup)
	ON_COMMAND(ID_INPUTGROUP_DELETE,OnDeleteGroup)
	ON_COMMAND(ID_INPUTGROUP_CHANGE,OnChangeGroup)

END_MESSAGE_MAP()



// XInputSignalPane 消息处理程序

void XInputSignalPane::SetDelegate(XDelegateInputSignalPane* pDelegate)
{
	m_pDelegate = pDelegate;
}

XDelegateInputSignalPane* XInputSignalPane::GetDelegate()
{
	return m_pDelegate;
}

void XInputSignalPane::Init()
{
	CreatePane();

	InitInputSignal();
}

void XInputSignalPane::CreatePane()
{
	CWnd* pWnd = m_pDelegate->GetCWND();

	CMainFrame* pMainFrame = (CMainFrame*)pWnd;

	CString szTitle = m_pDelegate->GetTranslationString(_T("202"), _T("输入信号"));

	if (!Create(szTitle, pMainFrame, CRect(0, 0, 230, 100), TRUE, 
		ID_INPUTSIGNALPANE, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_FLOAT_MULTI, 
		AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE))
	{
		return; 
	}

	EnableDocking(CBRS_ALIGN_LEFT);

	pMainFrame->DockPane(this);
}

int XInputSignalPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!InitImageList())
		return -1; 

	if (!InitTreeCtrl())
		return -1;

	return 0;
}

BOOL XInputSignalPane::InitTreeCtrl()
{
	m_TreeCtrl.SetInputSignalPane(this);

	if (m_TreeCtrl.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |TVS_SHOWSELALWAYS, CRect(0, 0, 0, 0), this, ID_INPUTSIGNAL_TREECTRL))
	{
		m_TreeCtrl.SetImageList(&m_ImageList, TVSIL_NORMAL);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL XInputSignalPane::InitImageList()
{
	if(!m_ImageList.Create(24,24,ILC_COLOR32|ILC_MASK,0,1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LAYER));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LATER1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LAYER2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NORMAL));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SELECT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ULTRA));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ULTRA1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IP1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IP4K));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IP4K1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));

	return TRUE;
}

void XInputSignalPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void XInputSignalPane::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(rect);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rect, &bruDB);

	CRect rectTreeCtrl;
	m_TreeCtrl.GetWindowRect(rectTreeCtrl);
	ScreenToClient(rectTreeCtrl);
	rectTreeCtrl.InflateRect(1, 1);
	dc.Draw3dRect(rectTreeCtrl, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void XInputSignalPane::AdjustLayout()
{
	if (nullptr == GetSafeHwnd())
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_TreeCtrl.SetWindowPos(NULL,rectClient.left+2,rectClient.top+1,rectClient.Width()-3,rectClient.Height()-2,SWP_NOACTIVATE|SWP_NOZORDER);
}


void XInputSignalPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_TreeCtrl.SetFocus();
}

void XInputSignalPane::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}

void XInputSignalPane::ResetData()
{
	ResetInputSignal();
}

void XInputSignalPane::ResetDataOfScene()
{
	ClearNameInfo();

	CopyAnotherNameByVecInput(m_VecNameInfo);

	m_TreeCtrl.DeleteAllItems();

	ClearVecInputSignal();

	ResetInputSignal();

	CopyAnotherNameToVecInput(m_VecNameInfo);

	InitInputSignal();

	m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);
}

void XInputSignalPane::CopyAnotherNameByVecInput(VEC_NAMEINFO& VecNameInfo)
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInput=*iter;

		CString szAnotherName=pInput->GetAnotherName();

		int nInputIndex=pInput->GetInputIndex();

		XAnotherNameInfo* pInfo=new XAnotherNameInfo;

		pInfo->SetInputIndex(nInputIndex);

		pInfo->SetAnotherName(szAnotherName);

		VecNameInfo.push_back(pInfo);
	}
}

void XInputSignalPane::CopyAnotherNameToVecInput(VEC_NAMEINFO& VecNameInfo)
{
	for(VEC_NAMEINFO::iterator iter=VecNameInfo.begin();iter!=VecNameInfo.end();++iter)
	{
		XAnotherNameInfo* pInfo=*iter;

		CString szAnotherName=pInfo->GetAnotherName();

		int nInfoIndex=pInfo->GetInputIndex();

		for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
		{
			XInputSignal* pInput=*iter;

			int nInputIndex=pInput->GetInputIndex();

			if(nInfoIndex==nInputIndex)
			{
				pInput->SetAnotherName(szAnotherName);
			}
		}
	}
}

void XInputSignalPane::ResetInputSignal()
{
	int nSignalCount=m_InputCount;

	for (int i=1; i<=nSignalCount;i++)
	{
		XInputSignal* pInputSignal=new XInputSignal;

		pInputSignal->SetInputIndex(i);

		//初始化OSD数据
		pInputSignal->GetOSDInfo()->Init();
		/////////////////////////////////////
		XInputSignalExpand* pExpand=new XInputSignalExpand;

		pExpand->SetInputSignal(pInputSignal);
		pExpand->SetCanEdit(FALSE);
		pExpand->SetID(1);
		pExpand->SetName(_T("全屏(Full Screen)"));

		pInputSignal->AddExpand(pExpand);
		/////////////////////////////////////
		m_VecInputSignal.push_back(pInputSignal);
	}
}

void XInputSignalPane::InitInputSignal()
{
	int nSize=m_MapGroup.size();

	if(nSize==0)
	{
		for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
		{
			XInputSignal* pInputSignal = *iter;

			TRACE(_T("RTSP=%s\n"),pInputSignal->GetRTSPAddr());

			InsertInputSignal(pInputSignal);
		}
	}
	else
		ChangeInputModel();
}

void XInputSignalPane::ReloadInterface()
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("202"), _T("Input Signal")));

	ReloadInterfaceOfTree();
}

void XInputSignalPane::ReloadInterfaceOfTree()
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		int nSignalIndex = pInputSignal->GetInputIndex();

		CString szTemp;
		szTemp.Format(_T("%s %d"), m_pDelegate->GetTranslationString(_T("203"), _T("信号")), nSignalIndex);

		HTREEITEM item = pInputSignal->GetTreeItem();

		m_TreeCtrl.SetItemText(item, szTemp);
	}
}

CString XInputSignalPane::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

int XInputSignalPane::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

BOOL XInputSignalPane::IsInputSignalItem(HTREEITEM item)
{
	HTREEITEM parent=m_TreeCtrl.GetParentItem(item);

	if(NULL==parent)
		return TRUE;
	else
		return FALSE;
}

void XInputSignalPane::OnNMRClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_pDelegate->IsLogin())
		return;

	CPoint point;
	GetCursorPos(&point);

	CPoint tempPoint = point;
	m_TreeCtrl.ScreenToClient(&tempPoint);

	UINT flags; 

	HTREEITEM  hItem = m_TreeCtrl.HitTest(tempPoint, &flags);  

	if (hItem != NULL) 
	{ 
		m_RBItem=hItem;

		m_TreeCtrl.SelectItem(hItem);

		DWORD dwData = m_TreeCtrl.GetItemData(hItem);

		CString szItemText=m_TreeCtrl.GetItemText(hItem);

		if(dwData==ITEMTYPE_INPUTGROUP)//组
		{
			ShowMenuOfInputGroup();
		}
		else if(dwData==ITEMTYPE_INPUTSIGNAL)//输入
		{
			int nInputIndex=GetInputIndexByItemName(szItemText);

			m_RBInputSignal=GetInputSignalByIndex(nInputIndex);

			if(m_RBInputSignal==NULL)
				return;

			ShowMenuOfInputSignal();
		}
		else//局部放大
		{
			m_RBInputSignalExpand = (XInputSignalExpand*)dwData;

			int nIndex=m_RBInputSignalExpand->GetInputSignal()->GetInputIndex();

			if(IsHaveSignal(nIndex)&&IsHavePan(nIndex))
			{
				ShowMenuOfInputSignalExpand();
			}
		}
	}
}

int XInputSignalPane::GetInputIndexByItemName(CString szItemText)
{
	int nPos=szItemText.Find('(');

	TRACE(_T("nPos=%d\n"),nPos);

	int nInputIndex=-1;

	if(nPos==-1)
	{
		int nTempPos=szItemText.Find(' ');

		CString szIndex=szItemText.Mid(nTempPos);

		nInputIndex=_ttoi(szIndex);
	}
	else
	{
		CString szTemp=szItemText.Left(nPos);

		int nTempPos=szTemp.Find(' ');

		CString szIndex=szTemp.Mid(nTempPos);

		nInputIndex=_ttoi(szIndex);
	}

	return nInputIndex;
}

XInputSignal* XInputSignalPane::GetInputSignalByIndex(int nIndex)
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInputSignal=*iter;

		int nInputIndex=pInputSignal->GetInputIndex();

		if(nInputIndex==nIndex)
		{
			return pInputSignal;
		}
	}

	return NULL;
}

void XInputSignalPane::ShowMenuOfInputGroup()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_INPUTGROUP_CHANGE, m_pDelegate->GetTranslationString(_T("678"), _T("修改")) + _T("(&C)")); 

	menu.AppendMenu(MF_STRING, ID_INPUTGROUP_DELETE, m_pDelegate->GetTranslationString(_T("207"), _T("删除")) + _T("(&D)")); 

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 

	menu.DestroyMenu();
}

void XInputSignalPane::ShowMenuOfInputSignal()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();

	int nIndex=m_RBInputSignal->GetInputIndex();

	CString szAnotherName=m_RBInputSignal->GetAnotherName();
	if(szAnotherName!=_T(""))
	{
		menu.AppendMenu(MF_STRING,ID_CHANGEANOTHERNAME, m_pDelegate->GetTranslationString(_T("662"),_T("修改备注"))+ _T("(&C)"));
	}
	else
	{
		menu.AppendMenu(MF_STRING,ID_SETANOTHERNAME, m_pDelegate->GetTranslationString(_T("494"),_T("添加备注"))+ _T("(&N)"));
	}
	menu.AppendMenu(MF_SEPARATOR);

	if(m_RBInputSignal->GetIsInGroup())
	{
		menu.AppendMenu(MF_STRING,ID_DELFROMGROUP, m_pDelegate->GetTranslationString(_T("664"),_T("从分组中移除"))+ _T("(&D)"));
	}
	else
	{
		menu.AppendMenu(MF_STRING,ID_ADDGROUP, m_pDelegate->GetTranslationString(_T("665"),_T("添加到分组"))+ _T("(&A)"));
	}

	menu.AppendMenu(MF_SEPARATOR);

	IsUltra(nIndex);
	if(m_RBInputSignal->GetIsUltra())
	{
		int nTempIndex=nIndex-1;
		if(nTempIndex%4==0)
		{
			menu.AppendMenu(MF_STRING,ID_SELECTCHENAL, m_pDelegate->GetTranslationString(_T("540"),_T("切换通道"))+ _T("(&S)"));
			menu.AppendMenu(MF_SEPARATOR);
		}
	}

	if(IsIpPreview(nIndex))
	{
		int nTempIndex=nIndex-1;

		if(nTempIndex%4==0)
		{
			menu.AppendMenu(MF_STRING,ID_SETPANENET, m_pDelegate->GetTranslationString(_T("620"),_T("网络配置"))+ _T("(&I)"));
		}

		menu.AppendMenu(MF_STRING,ID_IPSTREAMADDR, m_pDelegate->GetTranslationString(_T("614"),_T("视频流地址"))+ _T("(&V)"));

		menu.AppendMenu(MF_SEPARATOR);
	}

	if(IsHaveSignal(nIndex)&&IsHavePan(nIndex))
	{
		menu.AppendMenu(MF_STRING,ID_INPUTSIGNALCUT, m_pDelegate->GetTranslationString(_T("431"),_T("输入裁剪"))+ _T("(&B)"));

		menu.AppendMenu(MF_STRING,ID_BORDEROVERLAT,m_pDelegate->GetTranslationString(_T("440"),_T("边框叠加")) + _T("(&I)"));

		menu.AppendMenu(MF_STRING, ID_ADDINPUTSIGNALEXPAND, m_pDelegate->GetTranslationString(_T("205"), _T("局部放大")) + _T("(&P)"));  

		menu.AppendMenu(MF_STRING, ID_SETOSD, m_pDelegate->GetTranslationString(_T("258"), _T("设置OSD")) + _T("(&O)"));  

		menu.AppendMenu(MF_STRING, ID_EDID, m_pDelegate->GetTranslationString(_T("455"), _T("设置EDID")) + _T("(&E)"));  
		menu.AppendMenu(MF_SEPARATOR);
	}	

	menu.AppendMenu(MF_STRING, ID_ATTRIBUTE_SIGNAL, m_pDelegate->GetTranslationString(_T("456"), _T("属性")) + _T("(&A)"));  

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 

	menu.DestroyMenu(); 
}

void XInputSignalPane::ShowMenuOfInputSignalExpand()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();

	if (m_RBInputSignalExpand->GetCanEdit())
	{
		menu.AppendMenu(MF_STRING, ID_EDITINPUTSIGNALEXPAND, m_pDelegate->GetTranslationString(_T("206"), _T("编辑")) + _T("(&E)")); 

		menu.AppendMenu(MF_STRING, ID_DELINPUTSIGNALEXPAND, m_pDelegate->GetTranslationString(_T("207"), _T("删除")) + _T("(&D)")); 
	}

	menu.AppendMenu(MF_STRING, ID_SETINPUTSIGNALDEFAULTEXPAND, m_pDelegate->GetTranslationString(_T("273"), _T("设置当前局部放大为默认"))); 

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); 

	menu.DestroyMenu();
}

void XInputSignalPane::OnDelExpand()
{
	if (NULL == m_RBInputSignalExpand)
		return;

	HTREEITEM item = m_RBInputSignalExpand->GetTreeItem();

	m_TreeCtrl.DeleteItem(item);

	XInputSignal* pInputSignal = m_RBInputSignalExpand->GetInputSignal();

	int nExpandID = m_RBInputSignalExpand->GetID();

	pInputSignal->DeleteExpand(m_RBInputSignalExpand);

	if (pInputSignal->GetDefaultExpandID() == nExpandID)
	{
		pInputSignal->ResetDefaultExpandID();

		AdjustInputSignalExpandImage(pInputSignal);
	}
}

void XInputSignalPane::OnAddExpand()
{
	if (NULL == m_RBInputSignal)
		return;

	CAddExpandDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	dlg.SetInputSignalPan(this);

	if(dlg.DoModal()==IDOK)
	{
		HTREEITEM itemExpand = m_TreeCtrl.InsertItem(dlg.GetName(), 3, 3, m_RBInputSignal->GetTreeItem());

		XInputSignalExpand* pExpand = new XInputSignalExpand;
		pExpand->SetInputSignal(m_RBInputSignal);
		pExpand->SetExpand(dlg.GetExpandInfo());
		pExpand->SetName(dlg.GetName());
		pExpand->SetID(m_RBInputSignal->GetNewExpandID());
		pExpand->SetTreeItem(itemExpand);

		m_TreeCtrl.SetItemData(itemExpand, (DWORD_PTR)pExpand);

		m_RBInputSignal->AddExpand(pExpand);

		m_TreeCtrl.Expand(m_RBInputSignal->GetTreeItem(), TVE_EXPAND);

		m_TreeCtrl.SelectItem(itemExpand);

		m_TreeCtrl.SetFocus();
	}
}

void XInputSignalPane::OnEditExpand()
{
	if (NULL == m_RBInputSignalExpand)
		return;

	CEditExpandDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalExpand(m_RBInputSignalExpand);

	dlg.SetInputSignalPan(this);

	if(dlg.DoModal()==IDOK)
	{
		HTREEITEM itemExpand = m_RBInputSignalExpand->GetTreeItem();

		m_TreeCtrl.SetItemText(itemExpand, m_RBInputSignalExpand->GetName());

		m_TreeCtrl.SelectItem(itemExpand);

		m_TreeCtrl.SetFocus();
	}
}

void XInputSignalPane::OnSetDefaultExpand()
{
	if (NULL != m_RBInputSignalExpand)
	{
		XInputSignal* pInputSignal = m_RBInputSignalExpand->GetInputSignal();

		int nID = m_RBInputSignalExpand->GetID();

		if (pInputSignal->GetDefaultExpandID() != nID)
		{
			pInputSignal->SetDefaultExpandID(nID);

			AdjustInputSignalExpandImage(pInputSignal);
		}
	}
}

void XInputSignalPane::AdjustInputSignalExpandImage(XInputSignal* pInputSignal)
{
	int nID = pInputSignal->GetDefaultExpandID();

	VEC_INPUTSIGNALEXPAND& VecExpand = pInputSignal->GetVecExpand();

	for (VEC_INPUTSIGNALEXPAND::iterator iterEx = VecExpand.begin(); iterEx != VecExpand.end(); iterEx++)
	{
		XInputSignalExpand* pExpand = *iterEx;

		HTREEITEM itemExpand = pExpand->GetTreeItem();

		if (pExpand->GetID() == pInputSignal->GetDefaultExpandID())
		{
			m_TreeCtrl.SetItemImage(itemExpand, 4, 4);
		}
		else
		{
			m_TreeCtrl.SetItemImage(itemExpand, 3, 3);
		}
	}
}

void XInputSignalPane::GetData(CArchive& arch)
{
	XDataInputSignalPane::GetData(this, arch);
}

void XInputSignalPane::SaveData(CArchive& arch)
{
	XDataInputSignalPane::SaveData(this, arch);
}

VEC_INPUTSIGNAL& XInputSignalPane::GetVecInputSignal()
{
	return m_VecInputSignal;
}

MAP_GROUP& XInputSignalPane::GetMapGroup()
{
	return m_MapGroup;
}

XDragWnd* XInputSignalPane::CreateDragWnd(XDragInfo* pInfo)
{
	return m_pDelegate->CreateDragWnd(pInfo);
}

void XInputSignalPane::DragInfo(CRect rc,CPoint point,XDragInfo* pInfo)
{
	return m_pDelegate->DragInfo(rc,point,pInfo);
}

void XInputSignalPane::OnSetOSD()
{
	if (NULL==m_RBInputSignal)
		return; 

	CSetOSDDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	dlg.DoModal();
}

void XInputSignalPane::SetOSD(XInputSignal* pInputSignal)
{
	CSetOSDDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(pInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(pInputSignal->GetTreeItem()));

	dlg.DoModal();
}

void XInputSignalPane::OnInputSignalCut()
{
	if (NULL == m_RBInputSignal)
		return;

	XInputSignalCutDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==dlg.DoModal())
	{		
		XSendDataInputSignal::AddSendDataOfSignalCut(this,m_RBInputSignal);
	}
}

void XInputSignalPane::OnBorderOverlay()
{
	if (NULL==m_RBInputSignal)
		return;

	XBorderOverlayDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==dlg.DoModal())
	{
		XSendDataInputSignal::AddSendDataOfBorderOverlay(this,m_RBInputSignal);
	}
}

void XInputSignalPane::OnSetEDID()
{
	if (NULL == m_RBInputSignal)
		return; 

	XEDIDDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==dlg.DoModal())
	{
		XSendDataInputSignal::AddSendDataOfEDID(this,m_RBInputSignal);
	}
}

void XInputSignalPane::OnAttribute()
{
	if (NULL == m_RBInputSignal)
		return; 

	IsUltra(m_RBInputSignal->GetInputIndex());

	if(m_RBInputSignal->GetIsUltra())
	{
		XUltraAttributeDlg dlg;

		dlg.SetDelegate(this);

		dlg.SetInputSignalPane(this);

		dlg.SetInputSignal(m_RBInputSignal);

		dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

		dlg.DoModal();
	}
	else
	{
		XAttributeDlg dlg;

		dlg.SetDelegate(this);

		dlg.SetInputSignalPane(this);

		dlg.SetInputSignal(m_RBInputSignal);

		dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

		dlg.DoModal();
	}
}

void XInputSignalPane::OnChangeAnotherName()
{
	if (NULL == m_RBInputSignal)
		return; 

	XSetAnotherNameDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	dlg.SetTitle(GetTranslationString(_T("662"),_T("修改备注")));

	if(IDOK==dlg.DoModal())
	{
		CString szAnotherName=dlg.GetAnotherName();

		m_RBInputSignal->SetAnotherName(szAnotherName);

		SetAnotherName(m_RBInputSignal,szAnotherName);

		SetAnotherNameInOther(m_RBInputSignal,szAnotherName);
	}
}

void XInputSignalPane::OnSetAnotherName()
{
	if (NULL == m_RBInputSignal)
		return; 

	XSetAnotherNameDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	dlg.SetTitle(GetTranslationString(_T("494"),_T("添加备注")));

	if(IDOK==dlg.DoModal())
	{
		CString szAnotherName=dlg.GetAnotherName();

		m_RBInputSignal->SetAnotherName(szAnotherName);

		SetAnotherName(m_RBInputSignal,szAnotherName);

		SetAnotherNameInOther(m_RBInputSignal,szAnotherName);
	}
}

void XInputSignalPane::SetAnotherName(XInputSignal* pInput,CString szAnotherName)
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pSignal=*iter;

		if(pSignal==pInput)
		{
			pSignal->SetAnotherName(szAnotherName);

			CString szTemp;
			szTemp.Format(_T("%s %d"), m_pDelegate->GetTranslationString(_T("293"), _T("输入")), pSignal->GetInputIndex());

			CString szName=_T("");

			if (_T("")!=szAnotherName)
			{
				szName=_T("(")+szAnotherName+_T(")");
			}

			CString szItemText=szTemp+szName;

			m_TreeCtrl.SetItemText(pSignal->GetTreeItem(),szItemText);
		}
	}
}

void XInputSignalPane::SetAnotherNameInOther(XInputSignal* pInput,CString szAnotherName)
{
	int nInputIndex=pInput->GetInputIndex();

	SetPreviewNameByAnotherName(nInputIndex,szAnotherName);

	ChangeInputAnotherNameInGroup(nInputIndex,szAnotherName);

	//修改显示墙上面文字显示
	ChangeMultiVideoWindowsAnotherName(nInputIndex,szAnotherName);

	//修改屏幕上面信号备注
	//m_pDelegate->SetScreenSignalAnotherName(nInputIndex,szAnotherName);
}

void XInputSignalPane::ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)
{
	m_pDelegate->ChangeMultiVideoWindowsAnotherName(nInputIndex,szAnotherName);
}

void XInputSignalPane::ChangeInputAnotherNameInGroup(int nInputIndex,CString szAnotherName)
{
	for(MAP_GROUP::iterator iter=m_MapGroup.begin();iter!=m_MapGroup.end();++iter)
	{
		XInputGroup* pInput=iter->second;

		VEC_INPUTINFOINGROUP& VecInputInfo=pInput->GetVecInputInGroup();

		for(VEC_INPUTINFOINGROUP::iterator iterInfo=VecInputInfo.begin();iterInfo!=VecInputInfo.end();++iterInfo)
		{
			XInputInfoInGroup* pInputInfo=*iterInfo;

			int nIndex=pInputInfo->GetIndex();

			if(nIndex==nInputIndex)
			{
				pInputInfo->SetAnotherName(szAnotherName);
			}
		}
	}
}

void XInputSignalPane::OnSelectChanel()
{
	if (NULL == m_RBInputSignal)
		return; 

	XChangeChenalDlg dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==dlg.DoModal())
	{
		int nCurChe=dlg.GetCurChe();

		int nSelectedChe=dlg.GetSelectedChe();

		XSendDataInputSignal::AddSendDataOfChangeChenal(this,m_RBInputSignal,nCurChe,nSelectedChe);
	}
}

void XInputSignalPane::SetPreviewNameByAnotherName(int& nInputIndex,CString szAnotherName)
{
	m_pDelegate->SetPreviewNameByAnotherName(nInputIndex,szAnotherName);
}

void XInputSignalPane::SetPreviewNameByAnotherName()
{
	VEC_INPUTSIGNAL& VecInput=GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nInputIndex=pInput->GetInputIndex();

		CString szAnotherName=pInput->GetAnotherName();

		SetPreviewNameByAnotherName(nInputIndex,szAnotherName);
	}
}

BOOL XInputSignalPane::SendData(char* pData, int nDataLen)
{
	return m_pDelegate->SendData(pData, nDataLen);
}

BOOL XInputSignalPane::GetNetState()
{
	return m_pDelegate->GetNetState();
}

int XInputSignalPane::GetInputCount()
{
	return m_InputCount;
}

void XInputSignalPane::SetInputCount(int n)
{
	m_InputCount = n;
}

void XInputSignalPane::RefreshInputIcon()
{
	for(VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		int nSignalIndex = pInputSignal->GetInputIndex();

		int nStatus=pInputSignal->GetReStatus();

		//TRACE("nSignalIndex=%d\n",nSignalIndex);

		HTREEITEM nItem=pInputSignal->GetTreeItem();

		if(pInputSignal->GetReDataLen()==28)
		{
			//4K
			if(pInputSignal->GetReStatus()==0x11     //有信号通道1
				||pInputSignal->GetReStatus()==0x1A  //有信号通道2
				||pInputSignal->GetReStatus()==0x13  //有信号双通道-选中1
				||pInputSignal->GetReStatus()==0x1B) //有信号双通道-选中2
			{
				m_TreeCtrl.SetItemImage(nItem,5,5);			
			}
			else if(pInputSignal->GetReStatus()==0x10
				||pInputSignal->GetReStatus()==0x18
				||pInputSignal->GetReStatus()==0x12
				||pInputSignal->GetReStatus()==0x19)
			{			
				m_TreeCtrl.SetItemImage(nItem,6,6);			
			}

			//2K
			if(pInputSignal->GetReStatus()==0x01)
			{
				m_TreeCtrl.SetItemImage(nItem,0,0);			
			}
			else if(pInputSignal->GetReStatus()==0x00)
			{
				m_TreeCtrl.SetItemImage(nItem,1,1);
			}

			//VGA
			if(pInputSignal->GetReStatus()==0x21)
			{
				m_TreeCtrl.SetItemImage(nItem,0,0);			
			}
			else if(pInputSignal->GetReStatus()==0x20)
			{
				m_TreeCtrl.SetItemImage(nItem,1,1);
			}

			//SDI
			if(pInputSignal->GetReStatus()==0x31)
			{
				m_TreeCtrl.SetItemImage(nItem,0,0);			
			}
			else if(pInputSignal->GetReStatus()==0x30)
			{
				m_TreeCtrl.SetItemImage(nItem,1,1);
			}

			//AV
			if(pInputSignal->GetReStatus()==0x41)
			{
				m_TreeCtrl.SetItemImage(nItem,0,0);			
			}
			else if(pInputSignal->GetReStatus()==0x40)
			{
				m_TreeCtrl.SetItemImage(nItem,1,1);
			}

			//IP2k
			if(pInputSignal->GetReStatus()==0x51)
			{
				m_TreeCtrl.SetItemImage(nItem,7,7);
			}
			else if(pInputSignal->GetReStatus()==0x50)
			{
				m_TreeCtrl.SetItemImage(nItem,8,8);
			}

			//IP4K
			if(pInputSignal->GetReStatus()==0x61)
			{
				m_TreeCtrl.SetItemImage(nItem,9,9);
			}
			else if(pInputSignal->GetReStatus()==0x60)
			{
				m_TreeCtrl.SetItemImage(nItem,10,10);
			}

			//TRACE("ReStatus=%x\n",pInputSignal->GetReStatus());
		}

		//没有板卡
		if(pInputSignal->GetReDataLen()==0
			&&pInputSignal->GetReStatus()==0
			&&pInputSignal->GetReResulationH()==0
			&&pInputSignal->GetReResulationV()==0
			&&pInputSignal->GetReRefresh()==0
			&&pInputSignal->GetReVideoSelect()==0)
		{
			m_TreeCtrl.SetItemImage(nItem,2,2);
		}
	}
}

int XInputSignalPane::GetInputTypeByReStatus(int nStatus)
{
	if(nStatus==0x00
		||nStatus==0x01)
	{
		return INPUTTYPE_2K;
	}
	else if((nStatus&0xF0)==16)
	{
		return INPUTTYPE_4K;
	}
	else if((nStatus&0xF0)==32)
	{
		return INPUTTYPE_VGA;
	}
	else if((nStatus&0xF0)==48)
	{
		return INPUTTYPE_SDI;
	}
	else if((nStatus&0xF0)==64)
	{
		return INPUTTYPE_AV;
	}
	else if((nStatus&0xF0)==80)
	{
		return INPUTTYPE_IP2K;
	}
	else if((nStatus&0xF0)==96)
	{
		return INPUTTYPE_IP4K;
	}

	return INPUTTYPE_NULL;
}

BOOL XInputSignalPane::IsHaveSignal(int nIndex)
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		if(nIndex==pInputSignal->GetInputIndex())
		{
			if(pInputSignal->GetReDataLen()==28)			
			{
				if(pInputSignal->GetReStatus()==0x00
					||pInputSignal->GetReStatus()==0x10
					||pInputSignal->GetReStatus()==0x18
					||pInputSignal->GetReStatus()==0x20
					||pInputSignal->GetReStatus()==0x30
					||pInputSignal->GetReStatus()==0x40
					||pInputSignal->GetReStatus()==0x50
					||pInputSignal->GetReStatus()==0x60)
				{
					return FALSE;
				}	
			}
		}
	}
	return TRUE;
}

BOOL XInputSignalPane::IsHavePan(int nIndex)
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		if(nIndex==pInputSignal->GetInputIndex())
		{
			if(pInputSignal->GetReDataLen()==0
				&&pInputSignal->GetReStatus()==0
				&&pInputSignal->GetReResulationH()==0
				&&pInputSignal->GetReResulationV()==0
				&&pInputSignal->GetReRefresh()==0
				&&pInputSignal->GetReVideoSelect()==0)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

//是否为4K
void XInputSignalPane::IsUltra(int nIndex)
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal=*iter;

		int nSignalIndex=pInputSignal->GetInputIndex();

		if(nIndex==nSignalIndex)
		{
			if(pInputSignal->GetReStatus()==0x11     //有信号通道1
				||pInputSignal->GetReStatus()==0x1A  //有信号通道2
				||pInputSignal->GetReStatus()==0x13  //有信号双通道-选中1
				||pInputSignal->GetReStatus()==0x1B  //有信号双通道-选中2
				||pInputSignal->GetReStatus()==0x10  //无信号
				||pInputSignal->GetReStatus()==0x19  //有信号通道1-选中2
				||pInputSignal->GetReStatus()==0x18
				||pInputSignal->GetReStatus()==0x12)  //有信号通道2-选中1 
			{
				pInputSignal->SetIsUltra(TRUE);
			}
			else
			{
				pInputSignal->SetIsUltra(FALSE);
			}
		}
	}
}

CString XInputSignalPane::GetInputNameByIndex(int nIndex)
{
	CString szAnotherName=_T("");

	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nInputIndex=pInput->GetInputIndex();

		if(nInputIndex==nIndex)
		{
			szAnotherName=pInput->GetAnotherName();
		}
	}

	return szAnotherName;
}

XInputSignal* XInputSignalPane::GetInputByIndex(int nIndex)
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nInputIndex=pInput->GetInputIndex();

		if(nInputIndex==nIndex)
			return pInput;	
	}

	return NULL;
}

void XInputSignalPane::ResetDataBySceneInputCountChange()
{
	m_TreeCtrl.DeleteAllItems();

	ClearVecInputSignal();

	ResetInputSignal();

	InitInputSignal();

	m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);
}

//是否为IP卡
BOOL XInputSignalPane::IsIpPreview(int nIndex)
{
	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		if(nIndex==pInputSignal->GetInputIndex())
		{
			int nStatus=pInputSignal->GetReStatus();

			if((nStatus&0xF0)==96
				||(nStatus&0xF0)==80)
				return TRUE;
		}
	}

	return FALSE;
}

void XInputSignalPane::OnIPStreamAddr()
{
	if (NULL == m_RBInputSignal)
		return;

	m_StreamAddrDlg.SetDelegate(this);

	m_StreamAddrDlg.SetInputSignalPane(this);

	m_StreamAddrDlg.SetInputSignal(m_RBInputSignal);

	m_StreamAddrDlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==m_StreamAddrDlg.DoModal())
	{
		XSendDataInputSignal::AddSendDataOfStreamAddr(this,m_RBInputSignal);
	}
}

void XInputSignalPane::OnPaneIPSet()
{
	if (NULL == m_RBInputSignal)
		return; 

	m_PaneIPAddrDlg.SetDelegate(this);

	m_PaneIPAddrDlg.SetInputSignalPane(this);

	m_PaneIPAddrDlg.SetInputSignal(m_RBInputSignal);

	m_PaneIPAddrDlg.SetInputSignalName(m_TreeCtrl.GetItemText(m_RBInputSignal->GetTreeItem()));

	if(IDOK==m_PaneIPAddrDlg.DoModal())
	{
		XSendDataInputSignal::AddSendDataOfPaneIPAddr(this,m_RBInputSignal);
	}
}

void XInputSignalPane::OnAddGroup()
{
	if (NULL == m_RBInputSignal)
		return; 

	XAddGroup dlg;

	dlg.SetDelegate(this);

	dlg.SetInputSignalPane(this);

	dlg.SetInputSignal(m_RBInputSignal);

	dlg.DoModal();
}

void XInputSignalPane::OnDelFromGroup()
{
	//从分组中移除
	//////////////////////////////////////////////////////////////////////////
	int nInputIndex=m_RBInputSignal->GetInputIndex();

	HTREEITEM hRoot=m_TreeCtrl.GetParentItem(m_RBItem);

	if(hRoot==NULL)
		return;

	CString szItemText=m_TreeCtrl.GetItemText(hRoot);

	MAP_GROUP::iterator iter=m_MapGroup.find(szItemText);

	if(iter!=m_MapGroup.end())
	{
		//先在总输入集合中设置为无分组
		for(VEC_INPUTSIGNAL::iterator iter1=m_VecInputSignal.begin();iter1!=m_VecInputSignal.end();++iter1)
		{
			XInputSignal* pInputSignal=*iter1;

			if(nInputIndex==pInputSignal->GetInputIndex())
			{
				pInputSignal->SetGroupName(_T(""));

				pInputSignal->SetIsInGroup(FALSE);
			}
		}

		//再从组集合中删除
		XInputGroup* pInputGroup=iter->second;

		VEC_INPUTINFOINGROUP& VecInput=pInputGroup->GetVecInputInGroup();

		for(VEC_INPUTINFOINGROUP::iterator iter2=VecInput.begin();iter2!=VecInput.end();)
		{
			XInputInfoInGroup* pInput=*iter2;

			if(nInputIndex==pInput->GetIndex())
			{
				iter2=VecInput.erase(iter2);
			}
			else
			{
				++iter2;
			}
		}
	}

	//判断组里有没有成员
	for(MAP_GROUP::iterator iter3=m_MapGroup.begin();iter3!=m_MapGroup.end();)
	{
		XInputGroup* pGroup=iter3->second;

		VEC_INPUTINFOINGROUP& pInput=pGroup->GetVecInputInGroup();

		if(pInput.size()==0)
		{
			m_TreeCtrl.DeleteItem(hRoot);

			iter3=m_MapGroup.erase(iter3);
		}
		else
		{
			++iter3;
		}
	}

	ChangeInputModel();
}

void XInputSignalPane::OnDeleteGroup()
{
	//删除分组
	//////////////////////////////////////////////////////////////////////////
	CString szGroupName=m_TreeCtrl.GetItemText(m_RBItem);

	MAP_GROUP::iterator iter=m_MapGroup.find(szGroupName);

	if(iter!=m_MapGroup.end())
	{
		XInputGroup* pInputGroup=iter->second;

		VEC_INPUTINFOINGROUP& VecInput=pInputGroup->GetVecInputInGroup();

		for(VEC_INPUTINFOINGROUP::iterator iter1=VecInput.begin();iter1!=VecInput.end();++iter1)
		{
			XInputInfoInGroup* pInput=*iter1;

			int nIndex=pInput->GetIndex();

			for(VEC_INPUTSIGNAL::iterator iter2=m_VecInputSignal.begin();iter2!=m_VecInputSignal.end();++iter2)
			{
				XInputSignal* pInputSignal=*iter2;

				if(nIndex==pInputSignal->GetInputIndex())
				{
					pInputSignal->SetGroupName(_T(""));

					pInputSignal->SetIsInGroup(FALSE);
				}
			}
		}

		m_MapGroup.erase(iter);
	}

	ChangeInputModel();
}

void XInputSignalPane::OnChangeGroup()
{
	//修改分组
	CString szOldName=m_TreeCtrl.GetItemText(m_RBItem);

	if(szOldName==_T(""))
		return;

	XGroupName2 dlg;
	dlg.SetInputSignalPane(this);
	dlg.SetInputSignal(m_RBInputSignal);
	if(IDOK==dlg.DoModal())
	{
		CString szNewName=dlg.GetAnotherName();

		MAP_GROUP::iterator iter=m_MapGroup.find(szOldName);

		XInputGroup* pNewGroup=NULL;

		if(iter!=m_MapGroup.end())
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
			for(VEC_INPUTSIGNAL::iterator iter2=m_VecInputSignal.begin();iter2!=m_VecInputSignal.end();++iter2)
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

			m_MapGroup.insert(std::pair<CString,XInputGroup*>(szNewName,pNewGroup));

			m_MapGroup.erase(iter);
		}

		ChangeInputModel();
	}
}

void XInputSignalPane::ChangeInputModel()
{
	m_TreeCtrl.DeleteAllItems();

	for(MAP_GROUP::iterator iter=m_MapGroup.begin();iter!=m_MapGroup.end();++iter)
	{
		XInputGroup* pInputGroup=iter->second;

		CString szGroupName=pInputGroup->GetGroupName();

		HTREEITEM itemGroup;

		itemGroup=m_TreeCtrl.InsertItem(szGroupName);

		m_TreeCtrl.SetItemImage(itemGroup, 11, 11);

		m_TreeCtrl.SetItemData(itemGroup, ITEMTYPE_INPUTGROUP);

		pInputGroup->SetTreeItem(itemGroup);

		//////////////////////////////////////////////////////////////////////////

		for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
		{
			XInputSignal* pInputSignal = *iter;

			CString szInputGroupName=pInputSignal->GetGroupName();

			if(szInputGroupName==szGroupName)
			{
				InsertInputSignal(pInputSignal,itemGroup);
			}
		}

		m_TreeCtrl.Expand(itemGroup,TVE_EXPAND);
	}

	for (VEC_INPUTSIGNAL::iterator iter = m_VecInputSignal.begin(); iter != m_VecInputSignal.end(); iter++)
	{
		XInputSignal* pInputSignal = *iter;

		//添加不在组里面的输入
		if(pInputSignal->GetIsInGroup())
			continue;

		InsertInputSignal(pInputSignal);
	}
}

void XInputSignalPane::InsertInputSignal(XInputSignal* pInputSignal,HTREEITEM itemRoot)
{
	int nSignalIndex = pInputSignal->GetInputIndex();

	CString szTemp;
	szTemp.Format(_T("%s %d"), m_pDelegate->GetTranslationString(_T("293"), _T("输入")), nSignalIndex);

	HTREEITEM item;

	CString szName = _T("");

	if (_T("") != pInputSignal->GetAnotherName())
	{
		szName=_T("(") + pInputSignal->GetAnotherName() + _T(")");
	}

	item = m_TreeCtrl.InsertItem(szTemp + szName,itemRoot);

	pInputSignal->SetTreeItem(item);

	//m_TreeCtrl.SetItemData(item, (DWORD_PTR)pInputSignal);
	m_TreeCtrl.SetItemData(item, ITEMTYPE_INPUTSIGNAL);

	/////////////////////////////////////////
	VEC_INPUTSIGNALEXPAND& VecExpand = pInputSignal->GetVecExpand();

	for (VEC_INPUTSIGNALEXPAND::iterator iterEx = VecExpand.begin(); iterEx != VecExpand.end(); iterEx++)
	{
		XInputSignalExpand* pExpand = *iterEx;

		HTREEITEM itemExpand = m_TreeCtrl.InsertItem(pExpand->GetName(), item);

		pExpand->SetTreeItem(itemExpand);

		if (pExpand->GetID() == pInputSignal->GetDefaultExpandID())
		{
			m_TreeCtrl.SetItemImage(itemExpand, 4, 4);
		}
		else
		{
			m_TreeCtrl.SetItemImage(itemExpand, 3, 3);
		}

		m_TreeCtrl.SetItemData(itemExpand, (DWORD_PTR)pExpand);
		//m_TreeCtrl.SetItemData(itemExpand, ITEMTYPE_EXPAND);
	}
}

//仿函数
BOOL Compare(XInputInfoInGroup* pInfo1,XInputInfoInGroup* pInfo2)
{
	if(pInfo1->GetIndex()<pInfo2->GetIndex())
		return TRUE;
	else
		return FALSE;
}

void XInputSignalPane::AddDragIntoGroup(const HTREEITEM& itemDragS,const HTREEITEM& itemDragD)
{
	//itemDragS为拖拽节点，itemDragD被拖拽节点
	if(itemDragS==NULL||itemDragD==NULL)
		return;

	DWORD dwDataS=m_TreeCtrl.GetItemData(itemDragS);
	DWORD dwDataD=m_TreeCtrl.GetItemData(itemDragD);

	CString szItemTextS=m_TreeCtrl.GetItemText(itemDragS);
	CString szItemTextD=m_TreeCtrl.GetItemText(itemDragD);

	if(dwDataS==ITEMTYPE_INPUTSIGNAL)
	{
		//拖拽为输入
		int nInputIndexS=GetInputIndexByItemName(szItemTextS);
		XInputSignal* pSignalS=GetInputSignalByIndex(nInputIndexS);
		if(pSignalS==NULL)
			return;

		if(!pSignalS->GetIsInGroup())
		{
			//拖拽为输入，不在组内
			if(dwDataD==ITEMTYPE_INPUTSIGNAL)
			{
				//被拖拽为输入
				int nInputIndexD=GetInputIndexByItemName(szItemTextD);
				XInputSignal* pSignalD=GetInputSignalByIndex(nInputIndexD);
				if(pSignalD==NULL)
					return;

				if(!pSignalD->GetIsInGroup())
				{
					//被拖拽不在组内	
					//如果为自己
					if(pSignalS==pSignalD)
						return;

					CString szFrontName=m_pDelegate->GetTranslationString(_T("693"),_T("分组"));
					CString szGroupName=GetGroupNameByFrontName(szFrontName);

					pSignalS->SetGroupName(szGroupName);
					pSignalS->SetIsInGroup(TRUE);
					XInputInfoInGroup* pInfoIngroupS=new XInputInfoInGroup;
					pInfoIngroupS->SetIndex(pSignalS->GetInputIndex());
					pInfoIngroupS->SetAnotherName(pSignalS->GetAnotherName());
					pInfoIngroupS->SetGroupName(szGroupName);
					//////////////////////////////////////////////////////////////////////////
					pSignalD->SetGroupName(szGroupName);
					pSignalD->SetIsInGroup(TRUE);
					XInputInfoInGroup* pInfoIngroupD=new XInputInfoInGroup;
					pInfoIngroupD->SetIndex(pSignalD->GetInputIndex());
					pInfoIngroupD->SetAnotherName(pSignalD->GetAnotherName());
					pInfoIngroupD->SetGroupName(szGroupName);
					//////////////////////////////////////////////////////////////////////////
					XInputGroup* pInputGroup=new XInputGroup;
					pInputGroup->SetGroupName(szGroupName);
					pInputGroup->AddVecInputGroup(pInfoIngroupS);
					pInputGroup->AddVecInputGroup(pInfoIngroupD);

					//排序
					VEC_INPUTINFOINGROUP& VecInputInGroup=pInputGroup->GetVecInputInGroup();
					sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare);

					m_MapGroup.insert(std::pair<CString,XInputGroup*>(szGroupName,pInputGroup));
				}
				else
				{
					//被拖拽在组内
					HTREEITEM itemTemp=m_TreeCtrl.GetParentItem(itemDragD);
					if(itemTemp==NULL)
						return;

					CString szGroupName=m_TreeCtrl.GetItemText(itemTemp);

					MAP_GROUP::iterator iter=m_MapGroup.find(szGroupName);
					if(iter!=m_MapGroup.end())
					{
						pSignalS->SetGroupName(szGroupName);
						pSignalS->SetIsInGroup(TRUE);

						XInputGroup* pInfo=iter->second;

						XInputInfoInGroup* pInfoInGroup=new XInputInfoInGroup;
						pInfoInGroup->SetIndex(pSignalS->GetInputIndex());
						pInfoInGroup->SetAnotherName(pSignalS->GetAnotherName());
						pInfoInGroup->SetGroupName(szGroupName);
						pInfo->AddVecInputGroup(pInfoInGroup);

						//排序
						VEC_INPUTINFOINGROUP& VecInputInGroup=pInfo->GetVecInputInGroup();
						sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare);
					}
				}
			}
			else if(dwDataD==ITEMTYPE_INPUTGROUP)
			{
				//被拖拽为组
				CString szGroupName=m_TreeCtrl.GetItemText(itemDragD);
				MAP_GROUP::iterator iter=m_MapGroup.find(szGroupName);

				if(iter!=m_MapGroup.end())
				{
					pSignalS->SetGroupName(szGroupName);
					pSignalS->SetIsInGroup(TRUE);

					XInputGroup* pInfo=iter->second;

					XInputInfoInGroup* pInfoInGroup=new XInputInfoInGroup;
					pInfoInGroup->SetIndex(pSignalS->GetInputIndex());
					pInfoInGroup->SetAnotherName(pSignalS->GetAnotherName());
					pInfoInGroup->SetGroupName(szGroupName);

					pInfo->AddVecInputGroup(pInfoInGroup);
					//排序
					VEC_INPUTINFOINGROUP& VecInputInGroup=pInfo->GetVecInputInGroup();
					sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare);
				}
			}
			else
			{
				//被拖拽为放大，不处理
				return;
			}
		}
		else
		{
			//拖拽为输入，在组内
			if(dwDataD==ITEMTYPE_INPUTSIGNAL)
			{
				//被拖拽为输入
				int nInputIndexD=GetInputIndexByItemName(szItemTextD);
				XInputSignal* pSignalD=GetInputSignalByIndex(nInputIndexD);
				if(pSignalD==NULL)
					return;

				if(!pSignalD->GetIsInGroup())
				{
					//被拖拽不在组内
					HTREEITEM itemTemp=m_TreeCtrl.GetParentItem(itemDragS);
					if(itemTemp==NULL)
						return;

					CString szGroupName=m_TreeCtrl.GetItemText(itemTemp);
					MAP_GROUP::iterator iter=m_MapGroup.find(szGroupName);
					if(iter!=m_MapGroup.end())
					{
						pSignalS->SetGroupName(_T(""));
						pSignalS->SetIsInGroup(FALSE);

						XInputGroup* pInput=iter->second;

						VEC_INPUTINFOINGROUP& VecInputInGroup=pInput->GetVecInputInGroup();
						for(VEC_INPUTINFOINGROUP::iterator iter=VecInputInGroup.begin();iter!=VecInputInGroup.end();++iter)
						{
							XInputInfoInGroup* pInfo=*iter;
							if(szGroupName==pInfo->GetGroupName()
								&&pSignalS->GetInputIndex()==pInfo->GetIndex())
							{
								VecInputInGroup.erase(iter);
								delete pInfo;
								break;
							}
						}		
					}

					//如果组为空，则删除组
					for(MAP_GROUP::iterator iter3=m_MapGroup.begin();iter3!=m_MapGroup.end();)
					{
						XInputGroup* pGroup=iter3->second;

						VEC_INPUTINFOINGROUP& pInput=pGroup->GetVecInputInGroup();

						if(pInput.size()==0)
						{
							m_TreeCtrl.DeleteItem(itemTemp);

							iter3=m_MapGroup.erase(iter3);
						}
						else
						{
							++iter3;
						}
					}
				}
				else
				{
					//被拖拽在组内
					HTREEITEM itemTempS=m_TreeCtrl.GetParentItem(itemDragS);
					if(itemTempS==NULL)
						return;
					CString szGroupNameS=m_TreeCtrl.GetItemText(itemTempS);

					HTREEITEM itemTempD=m_TreeCtrl.GetParentItem(itemDragD);
					if(itemTempD==NULL)
						return;
					CString szGroupNameD=m_TreeCtrl.GetItemText(itemTempD);

					if(szGroupNameD==szGroupNameS)
					{
						//在同一组内，不处理
						return;
					}
					else
					{
						//在不同组
						//先从组里删除
						MAP_GROUP::iterator iterS=m_MapGroup.find(szGroupNameS);
						if(iterS!=m_MapGroup.end())
						{
							pSignalS->SetGroupName(_T(""));
							pSignalS->SetIsInGroup(FALSE);

							XInputGroup* pInput=iterS->second;
							//pInput->SetGroupName(_T(""));

							VEC_INPUTINFOINGROUP& VecInputInGroup=pInput->GetVecInputInGroup();
							for(VEC_INPUTINFOINGROUP::iterator iter=VecInputInGroup.begin();iter!=VecInputInGroup.end();++iter)
							{
								XInputInfoInGroup* pInfo=*iter;

								if(szGroupNameS==pInfo->GetGroupName()
									&&pSignalS->GetInputIndex()==pInfo->GetIndex())
								{
									VecInputInGroup.erase(iter);
									delete pInfo;
									break;
								}
							}		
						}

						//在添加到被拖拽组
						MAP_GROUP::iterator iterD=m_MapGroup.find(szGroupNameD);

						if(iterD!=m_MapGroup.end())
						{
							pSignalS->SetGroupName(szGroupNameD);
							pSignalS->SetIsInGroup(TRUE);

							XInputGroup* pInput=iterD->second;
							pInput->SetGroupName(szGroupNameD);

							XInputInfoInGroup* pInfo=new XInputInfoInGroup;
							pInfo->SetGroupName(szGroupNameD);
							pInfo->SetAnotherName(pSignalS->GetAnotherName());
							pInfo->SetIndex(pSignalS->GetInputIndex());

							pInput->AddVecInputGroup(pInfo);
							//排序
							VEC_INPUTINFOINGROUP& VecInputInGroup=pInput->GetVecInputInGroup();
							sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare);
						}
					}
				}
			}
			else if(dwDataD==ITEMTYPE_INPUTGROUP)
			{
				//被拖拽为组
				HTREEITEM itemTemp=m_TreeCtrl.GetParentItem(itemDragS);
				if(itemTemp==NULL)
					return;
				CString szGroupNameS=m_TreeCtrl.GetItemText(itemTemp);

				CString szGroupNameD=m_TreeCtrl.GetItemText(itemDragD);

				if(szGroupNameS==szGroupNameD)
				{
					//不处理
					return;
				}
				else
				{
					//先从组里删除
					MAP_GROUP::iterator iterS=m_MapGroup.find(szGroupNameS);
					if(iterS!=m_MapGroup.end())
					{
						pSignalS->SetGroupName(_T(""));
						pSignalS->SetIsInGroup(FALSE);

						XInputGroup* pInput=iterS->second;
						//pInput->SetGroupName(_T(""));

						VEC_INPUTINFOINGROUP& VecInputInGroup=pInput->GetVecInputInGroup();
						for(VEC_INPUTINFOINGROUP::iterator iter=VecInputInGroup.begin();iter!=VecInputInGroup.end();++iter)
						{
							XInputInfoInGroup* pInfo=*iter;

							if(szGroupNameS==pInfo->GetGroupName()
								&&pSignalS->GetInputIndex()==pInfo->GetIndex())
							{
								VecInputInGroup.erase(iter);
								delete pInfo;
								break;
							}
						}		
					}

					//在添加到被拖拽组
					MAP_GROUP::iterator iterD=m_MapGroup.find(szGroupNameD);

					if(iterD!=m_MapGroup.end())
					{
						pSignalS->SetGroupName(szGroupNameD);
						pSignalS->SetIsInGroup(TRUE);

						XInputGroup* pInput=iterD->second;
						pInput->SetGroupName(szGroupNameD);

						XInputInfoInGroup* pInfo=new XInputInfoInGroup;
						pInfo->SetGroupName(szGroupNameD);
						pInfo->SetAnotherName(pSignalS->GetAnotherName());
						pInfo->SetIndex(pSignalS->GetInputIndex());

						pInput->AddVecInputGroup(pInfo);
						//排序
						VEC_INPUTINFOINGROUP& VecInputInGroup=pInput->GetVecInputInGroup();
						sort(VecInputInGroup.begin(),VecInputInGroup.end(),Compare);
					}
				}
			}
			else
			{
				//被拖拽为放大
				return;
			}
		}
	}
	else
	{
		//拖拽为其他，不处理
		return;
	}

	ChangeInputModel();
}

CString XInputSignalPane::GetGroupNameByFrontName(CString szName)
{
	CString szTemp;

	int n=1;

	while(1)
	{
		szTemp.Format(_T("%d"),n);
		szTemp=szName+szTemp;

		MAP_GROUP::iterator iter=m_MapGroup.find(szTemp);

		if(iter==m_MapGroup.end())
			break;
		n++;
	}

	return szTemp;
}

void XInputSignalPane::OperateOfReadPaneIP(char* pData)
{
	int nLen=61;

	if(!CheckSumNum(pData,nLen))
		return;
	//*************************************
	int nModel=pData[8];
	int nSelect=0;
	if(nModel==1)
		nSelect=0;
	else if(nModel==2)
		nSelect=1;
	else if(nModel==0)
		nSelect=2;

	//*************************************
	int nIP1=pData[9]&0xFF;
	int nIP2=pData[10]&0xFF;
	int nIP3=pData[11]&0xFF;
	int nIP4=pData[12]&0xFF;

	CString szPaneIP=_T("");
	szPaneIP.Format(_T("%d.%d.%d.%d"),nIP1,nIP2,nIP3,nIP4);
	//*************************************
	int nMask1=pData[13]&0xFF;
	int nMask2=pData[14]&0xFF;
	int nMask3=pData[15]&0xFF;
	int nMask4=pData[16]&0xFF;

	CString szPaneMask=_T("");
	szPaneMask.Format(_T("%d.%d.%d.%d"),nMask1,nMask2,nMask3,nMask4);
	//*************************************
	int nGateWay1=pData[17]&0xFF;
	int nGateWay2=pData[18]&0xFF;
	int nGateWay3=pData[19]&0xFF;
	int nGateWay4=pData[20]&0xFF;

	CString szPaneGateWay=_T("");
	szPaneGateWay.Format(_T("%d.%d.%d.%d"),nGateWay1,nGateWay2,nGateWay3,nGateWay4);
	//*************************************
	int nMAC1=pData[21]&0xFF;
	int nMAC2=pData[22]&0xFF;
	int nMAC3=pData[23]&0xFF;
	int nMAC4=pData[24]&0xFF;
	int nMAC5=pData[25]&0xFF;
	int nMAC6=pData[26]&0xFF;

	CString szPaneMAC=_T("");
	szPaneMAC.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),nMAC1,nMAC2,nMAC3,nMAC4,nMAC5,nMAC6);

	//*************************************
	m_PaneIPAddrDlg.SetIP(szPaneIP);
	m_PaneIPAddrDlg.SetMask(szPaneMask);
	m_PaneIPAddrDlg.SetGateWay(szPaneGateWay);
	m_PaneIPAddrDlg.SetMAC(szPaneMAC);
	m_PaneIPAddrDlg.SetModel(nSelect);
	m_PaneIPAddrDlg.ResetNet();
}

void XInputSignalPane::OperateOfReadStreamAddr(char* pData)
{
	int nLen=136;

	if(!CheckSumNum(pData,nLen))
		return;
	//*************************************
	int nUrlLen=pData[8];
	if(nUrlLen==0)
		nUrlLen=1;

	//之前因为申请内存不够大 导致无法释放
	char* pUrlData=new char[nUrlLen+1];
	memset(pUrlData,0,nUrlLen);
	pUrlData[nUrlLen]='\0';
	memcpy(pUrlData,pData+9,nUrlLen);

	CString szUrl(pUrlData);
	szUrl.Trim();
	//*************************************
	m_StreamAddrDlg.SetStreamAddr(szUrl);
	m_StreamAddrDlg.ResetStream();

	delete []pUrlData;
}

BOOL XInputSignalPane::CheckSumNum(char* pData,int nLen)
{
	char* data=new char[nLen];
	char* pTempData=pData;
	memcpy(data,pTempData,nLen);
	unsigned short nSum=CheckNum(data,nLen);
	delete []data;

	char* pTemp=pData;
	unsigned short nTempSum=0;
	memcpy(&nTempSum,pTemp+nLen,2);
	unsigned short nReSum=nTempSum&0xFF;

	if(nSum!=nReSum)
		return FALSE;
	else
		return TRUE;
}

unsigned short XInputSignalPane::CheckNum(char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];

		nSum=nSum&0xFF;
	}

	return nSum;
}

void XInputSignalPane::SetInputSignalPara()
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		pInput->SetRTSPAddr(_T(""));
		pInput->SetIPAddr(_T(""));
		pInput->SetUseName(_T(""));
		pInput->SetPassWd(_T(""));
	}
}

void XInputSignalPane::SetInputRTSPAddrByIndex(int nIndex,CString szRTSP)
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nInputIndex=pInput->GetInputIndex();

		if(nInputIndex==nIndex)
		{
			pInput->SetRTSPAddr(szRTSP);
		}
	}
}

void XInputSignalPane::SetInputParaByIndex(int nIndex,CString szIP,CString szUseName,CString szPassWd)
{
	for(VEC_INPUTSIGNAL::iterator iter=m_VecInputSignal.begin();iter!=m_VecInputSignal.end();++iter)
	{
		XInputSignal* pInput=*iter;

		int nInputIndex=pInput->GetInputIndex();

		if(nInputIndex==nIndex)
		{
			pInput->SetIPAddr(szIP);
			pInput->SetUseName(szUseName);
			pInput->SetPassWd(szPassWd);
		}
	}
}

BOOL XInputSignalPane::IsNameHas(CString szName)
{
	MAP_GROUP::iterator iter=m_MapGroup.find(szName);

	if(iter!=m_MapGroup.end())
		return TRUE;
	else
		return FALSE;
}

BOOL XInputSignalPane::SetSelInputDataInfo()
{
	HTREEITEM hItem=m_TreeCtrl.GetSelectedItem();

	if(hItem==NULL)
		return FALSE;

	CString szItemText=m_TreeCtrl.GetItemText(hItem);

	m_TreeCtrl.DragDataInfo(hItem);

	return TRUE;
}

XDragInfo& XInputSignalPane::GetDragInfo()
{
	return m_pDelegate->GetDragInfo();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void XInputSignalPane::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_SETSIGNALICON:
		{
			RefreshInputIcon();
		}
		break;
	case OPERATETYPE_GETPANEIPADDR:
		{
			OperateOfReadPaneIP((char*)pData);
		}
		break;
	case OPERATETYPE_GETSTREAMADDR:
		{
			OperateOfReadStreamAddr((char*)pData);
		}
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////
void XInputSignalPane::UpdateControlDataShowOfInputCount(CMFCRibbonEdit* p)
{
	CString szTemp = _T("");
	szTemp.Format(_T("%d"), m_InputCount);

	p->SetEditText(szTemp);
}

void XInputSignalPane::ControlDataChangeOfInputCount(CMFCRibbonEdit* p)
{
	CString szTemp = p->GetEditText();

	szTemp.Trim();

	if (_T("") == szTemp)
	{
		szTemp.Format(_T("%d"), m_InputCount);

		p->SetEditText(szTemp);

		return;
	}

	int nInputCount = _ttoi(szTemp);

	if (nInputCount < 0 || nInputCount > 200)
	{
		m_pDelegate->MessageBoxFromKey(_T("339"), _T("输入个数错误，范围为1~200,请重新输入!"), MB_OK);

		szTemp.Format(_T("%d"), m_InputCount);

		p->SetEditText(szTemp);

		return;
	}

	if (nInputCount != m_InputCount)
	{
		m_InputCount = nInputCount;

		p->SetEditText(szTemp);

		m_TreeCtrl.DeleteAllItems();

		ClearVecInputSignal();

		ResetInputSignal();

		InitInputSignal();

		m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);

		SetPreviewNameByAnotherName();
	}
}

void XInputSignalPane::UpdateControlDataShow(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_INPUTCOUNT:
		{
			UpdateControlDataShowOfInputCount((CMFCRibbonEdit*)pControl);
		}
		break;
	default:
		break;
	}
}

void XInputSignalPane::ControlDataChange(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_INPUTCOUNT:
		{
			ControlDataChangeOfInputCount((CMFCRibbonEdit*)pControl);
		}
		break;
	default:
		break;
	}
}

