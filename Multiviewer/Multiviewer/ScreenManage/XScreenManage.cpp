#include "StdAfx.h"
#include "XScreenManage.h"
#include "XDelegateScreenManage.h"
#include "XDataScreenManage.h"
#include "XCalculateScreenManage.h"
#include "XDrawScreenManage.h"
#include "XSignal.h"
#include "..\resource.h"
#include "HandlePath.h"
#include "XSendDataScreenManage.h"
#include "HandleIni.h"
#include "XExpandInfo.h"
#include "XResolution.h"
#include <algorithm>
#include "XInputSignal.h"
#include "XChangeInput.h"
#include "XInputSignalExpand.h"
#include "XSceneDataManage.h"
#include "XSendData.h"
#include "XScreenAttributes.h"
#include "XTimedPollingDlg.h"
#include "XAllResulation.h"
#include "XRunOldOrder.h"
#include "XChangeScreen.h"
#include "XRTSPInfo.h"
#include "XSelectEquipment.h"
#include "XSetBoard.h"
#include "XSetScreenRange.h"
#include "XScreenData.h"
#include "..\MultiviewerView.h"
#include "XScreenInfo.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrame.h"
#include "XScreenDataInfo.h"
#include "XMultiVideoWindowFrames.h"
#include "XMatrixResolution.h"
#include "XMatrixAllResolution.h"
#include "XMatrixScreenAttributes.h"
#include "XSetScreenName.h"
#include "XInputType.h"
#include "HandleShearPlate.h"
#include "XSetRowResoluation.h"
#include "XSetColResoluation.h"
#include "XScreenRowInfo.h"
#include "XScreenColInfo.h"


XScreenManage::XScreenManage(void)
{
	m_nResolutionH = 200;
	m_nResolutionV = 112;
	m_nRightResulationH=200;
	m_nBottomResulationV=112;
	m_nScreenCountH = 0;
	m_nScreenCountV = 0;
	m_SynTime = 0;
	m_CursorType=CURSORTYPE_NORMAL;
	m_ISViewButtonDown=FALSE;
	m_RBtnIndex=0;
	m_RBtnSignalID=0;
	m_RBtnSignalGroupID=0;
	m_IsSendPocket=FALSE;
	pAskData=NULL;
	m_BeginIndex=1;
	m_LBDIndex=0;
	m_LBDSignalID=0;
	m_LBDSignalGroupID=0;
	m_bIsLBDClick=FALSE;
	m_bIsMenuSet=FALSE;
	m_pScreenMoveDlg=NULL;
	m_nScreenModel=SCREENMODEL_SPLIC;
	m_nStatus=DRAGSTATUS_NORMAL;
	m_nDragModel=DRAGMODEL_TIPMODEL;
	m_nCurScale=100;
	m_bCreateSignal=FALSE;
	m_nPreResolutionH=0;
	m_nPreResolutionV=0;

	m_TempScreen=NULL;
}

XScreenManage::~XScreenManage(void)
{
	ClearVecScreen();
	ClearDragFrame();
	ClearVecScreenData();
	ClearVecScreenInfo();	
	ClearVecSendData();
	ClearMapBoardType();
	ClearExpandInfo();
	ClearReMapRTSP();
	ClearInputType();
	ClearRowInfo();
	ClearColInfo();
}

void XScreenManage::ClearInputType()
{
	for(MAP_INPUTTYPE::iterator iter=m_MapInputType.begin();iter!=m_MapInputType.end();++iter)
		delete iter->second;
	m_MapInputType.clear();
}

void XScreenManage::ClearExpandInfo()
{
	for(VEC_EXPANDINFO::iterator iter=m_VecExpandInfo.begin();iter!=m_VecExpandInfo.end();++iter)
		delete *iter;
	m_VecExpandInfo.clear();
}

void XScreenManage::ClearVecScreen()
{
	for (VEC_SCREEN::iterator iter = m_VecScreen.begin(); iter != m_VecScreen.end(); iter++)
		delete *iter;
	m_VecScreen.clear();
}

void XScreenManage::ClearVecScreenData()
{
	for (VEC_SCREENDATA::iterator iter=m_VecScreenData.begin();iter!=m_VecScreenData.end();iter++)
		delete *iter;
	m_VecScreenData.clear();
}

void XScreenManage::ClearVecScreenInfo()
{
	for (VEC_SCREENINFO::iterator iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();iter++)
		delete *iter;

	m_VecScreenInfo.clear();
}

void XScreenManage::ClearMapBoardType()
{
	m_MapBoardType.clear();
}

void XScreenManage::ClearReMapRTSP()
{
	m_MapReRTSPAddr.clear();
}

void XScreenManage::ClearRowInfo()
{
	for(auto iter=m_MapRowInfo.begin();iter!=m_MapRowInfo.end();++iter)
	{
		delete iter->second;
	}

	m_MapRowInfo.clear();
}

void XScreenManage::ClearColInfo()
{
	for(auto iter=m_MapColInfo.begin();iter!=m_MapColInfo.end();++iter)
	{
		delete iter->second;
	}

	m_MapColInfo.clear();
}

void XScreenManage::GetData(CArchive& arch)
{
	XDataScreenManage::GetData(this, arch);
}

void XScreenManage::SaveData(CArchive& arch)
{
	XDataScreenManage::SaveData(this, arch);
}

void XScreenManage::ResetData()
{
	m_MoveInfo.Init();
	InitVecScreen();
}

void XScreenManage::ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
	int noffsetY)
{
	XDrawScreenManage::ViewDraw(pDC, rect, noffsetX, noffsetY, this);
}

CSize XScreenManage::ViewGetSize()
{
	return XCalculateScreenManage::ViewGetSize(this);
}

void XScreenManage::ViewLBDClick(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	POINTF TempPoint;

	XCalculateScreenManage::ReductionPoint(this, rect, noffsetX, noffsetY, point, TempPoint);
	XScreen* pScreen=XCalculateScreenManage::GetScreenByPoint(this, TempPoint);

	if (NULL==pScreen)
		return;

	int nModel=GetScreenModel();
	if(nModel==SCREENMODEL_MATRIX)
	{
		//双击屏幕，该屏幕名称
		XSetScreenName Dlg;
		Dlg.SetDelegate(this);

		CString szScreenName=pScreen->GetScreenName();
		CString szTitle=_T("");
		if(szScreenName==_T(""))
			szTitle=m_pDelegate->GetTranslationString(_T("722"),_T("设置屏幕备注"));
		else
			szTitle=m_pDelegate->GetTranslationString(_T("723"),_T("更改屏幕备注"));
		Dlg.SetTitle(szTitle);

		if(IDOK==Dlg.DoModal())
		{
			CString szName=Dlg.GetScreenName();
			pScreen->SetScreenName(szName);
			CString szText=SetText(pScreen);

			m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
		}

		return;
	}

	XSignal* pSignal=XCalculateScreenManage::GetSignalByPoint(pScreen,TempPoint);

	if(NULL==pSignal)
	{
		//双击屏幕，该屏幕名称
		XSetScreenName Dlg;
		Dlg.SetDelegate(this);

		CString szScreenName=pScreen->GetScreenName();
		CString szTitle=_T("");
		if(szScreenName==_T(""))
			szTitle=m_pDelegate->GetTranslationString(_T("722"),_T("设置屏幕备注"));
		else
			szTitle=m_pDelegate->GetTranslationString(_T("723"),_T("更改屏幕备注"));
		Dlg.SetTitle(szTitle);

		if(IDOK==Dlg.DoModal())
		{
			CString szName=Dlg.GetScreenName();
			pScreen->SetScreenName(szName);
			CString szText=SetText(pScreen);

			m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
		}
	}
	else
	{
		//双击信号
		//m_pMultiVideoWindow->SetIsDragFrame(FALSE);

		m_bIsLBDClick=TRUE;
		int nIndex=pSignal->GetInputIndex();
		m_LBDIndex=nIndex;

		unsigned int nSignalID=pSignal->GetSignalID();
		unsigned int nGroupID=pSignal->GetSignalGroupID();

		m_LBDSignalID=nSignalID;
		m_LBDSignalGroupID=nGroupID;

		BOOL IsUltra=pSignal->GetIsUltra();
		XExpandInfo pExpand=*(pSignal->GetExpandInfo());
		CString szIP=pSignal->GetIPAddr();
		CString szUseName=pSignal->GetUseName();
		CString szPassWd=pSignal->GetPassWd();

		//生成RTSP
		CreateRTSPAddr(szIP,szUseName,szPassWd);

		//信号ID集合
		VEC_UNINT VecSignalID;
		GetVecSignalID(nGroupID,VecSignalID);
		m_DragInfo.SetVecExpandSignalID(VecSignalID);

		//信号序号集合
		HYVEC_NUM VecSignalIndex;
		GetVecSignalIndex(nGroupID,VecSignalIndex);
		m_DragInfo.SetVecExpandSignalIndex(VecSignalIndex);
		m_DragInfo.SetIsUltra(IsUltra);
		m_DragInfo.SetExpand(&pExpand);
		m_DragInfo.SetIPAddr(szIP);
		OperateOfExpandSignal();
	}
}

void XScreenManage::ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	int nModel=GetScreenModel();
	if(nModel==SCREENMODEL_MATRIX)
		return;

	if (!m_pDelegate->IsLogin())
	{
		m_pDelegate->MessageBoxFromKey(_T("378"), _T("请先进行登陆操作！"), MB_OK);
		return;
	}

	XCalculateScreenManage::ReductionPoint(this, rect, noffsetX, noffsetY, point, m_Point);
	XScreen* pScreen=XCalculateScreenManage::GetScreenByPoint(this, m_Point);

	if(NULL==pScreen)
		return;

	m_TempScreen=pScreen;

	XSignal *pSignal=XCalculateScreenManage::GetSignalByPoint(pScreen,m_Point);

	if(NULL==pSignal)
	{
		m_ISViewButtonDown=TRUE;
		m_bIsLBDClick=FALSE;
		if(!m_pDelegate->SetSelInputDataInfo())
			return;
			
		m_CursorType=CURSORTYPE_NORMAL;
		SetCursor(m_CursorType);
		RECTF rect(m_Point.X,m_Point.Y,0,0);
		m_InterRect=rect;
		AddDragFrame(m_InterRect);

		m_bCreateSignal=TRUE;
	}
	else
	{
		m_bCreateSignal=FALSE;
		m_bIsLBDClick=FALSE;
		m_ISViewButtonDown=TRUE;
		UpdateSynTime();

		CString szAnotherName=pSignal->GetAnotherName();
		unsigned int nSignalID=pSignal->GetSignalID();
		unsigned int nSignalGroupID=pSignal->GetSignalGroupID();

		//（右键信号ID）用于拖走删除信号
		m_RBtnIndex=pSignal->GetInputIndex();

		m_RBtnSignalGroupID=nSignalGroupID;
		TRACE(_T("GID=%d\n"),m_RBtnSignalGroupID);
		//////////////////////////////////////////////////////////////////////////
		//SetSignalSelectByGroupID(nSignalGroupID);
		//SetFrameSelectByGroupID(nSignalGroupID);
		//////////////////////////////////////////////////////////////////////////
		BOOL bIsUltra=pSignal->GetIsUltra();
		BOOL bIs4kTo2k=pSignal->GetIs4kTo2k();
		int nSingnalIndex=pSignal->GetInputIndex();
		CString szIPAddr=pSignal->GetIPAddr();
		CString szUseName=pSignal->GetUseName();
		CString szPassWd=pSignal->GetPassWd();

		//生成RTSP
		CreateRTSPAddr(szIPAddr,szUseName,szPassWd);
		//**********************************
		SetVecInputSignalIndexAndID(pSignal);
		//**********************************
		XExpandInfo pExpand=*(pSignal->GetExpandInfo());
		//==================================
		//预览
		CString szRTSPAddr=pSignal->GetRTSPAddr();
		XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();
		int nInputNum=pSignal->GetSignalNum();

		m_DragInfo.SetInputNum(nInputNum);
		m_DragInfo.SetRTSPAddr(szRTSPAddr);
		m_DragInfo.SetPreviewFrame(pFrame);

		//==================================
		m_DragInfo.SetDragSignalID(nSignalID);
		m_DragInfo.SetDragSignalGroupID(nSignalGroupID);
		m_DragInfo.SetInputIndex(nSingnalIndex);
		m_DragInfo.SetExpand(&pExpand);
		m_DragInfo.SetAnotherName(szAnotherName);
		m_DragInfo.SetIsUltra(bIsUltra);
		m_DragInfo.SetIPAddr(szIPAddr);

		//根据组ID地址隐藏预览信号
		SetPreviewFrameShow(nSignalGroupID,FALSE);

		//添加拖动窗口
		AddDragFrame(m_InterRect);

		//如果是4K转2K
		if(bIs4kTo2k)
		{
			DeleteAnotherSignalByGroupID(nSignalGroupID,nSignalID);
			SetSelectSignalIDTopInVecDrag(nSignalID);
		}
	}
}

void XScreenManage::SetSignalSelectByGroupID(unsigned int nGroupID)
{
	for(auto iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(auto iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			if(pSignal->GetSignalGroupID()==nGroupID)
				pSignal->SetSelected(TRUE);
			else
				pSignal->SetSelected(FALSE);
		}
	}
}

void XScreenManage::SetFrameSelectByGroupID(unsigned int nGroupID)
{
	m_pMultiVideoWindow->SetFrameSelectByGroupID(nGroupID);
}

//4kTo2k删除其他三个信号
void XScreenManage::DeleteAnotherSignalByGroupID(unsigned int nSignalGroupID,unsigned int nSignalID)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		BOOL bISTwoScreen=pScreen->GetIsTwoSignal();
		int nNum=pScreen->GetNumOfTwoScreen();
		int nScreenPane=pScreen->GetBoardIndex();
		int nScreenIndex=pScreen->GetIndex();

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		VEC_SIGNAL::iterator iterSignal=VecSignal.begin();

		while(iterSignal!=VecSignal.end())
		{
			XSignal *pSignal=*iterSignal;
			unsigned int nID=pSignal->GetSignalID();
			if(pSignal->GetSignalGroupID()==nSignalGroupID)
			{
				if(nID!=nSignalID)
				{
					//删除信号Frame
					XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();
					m_pMultiVideoWindow->DeleteFrame(nScreenIndex,pFrame);

					//删除信号
					iterSignal=VecSignal.erase(iterSignal);
					delete pSignal;

					XSendDataScreenManage::AddSendDataOfSignalClose(this,nScreenPane,nID,nNum,bISTwoScreen);
				}
				else
					++iterSignal;
			}
		}
	}
}

//设置所点击信号ID置顶
void XScreenManage::SetSelectSignalIDTopInVecDrag(unsigned int nSignalID)
{
	VEC_UNINT VecSignalID=m_DragInfo.GetVecDragSignalID();

	for(VEC_UNINT::iterator iter=VecSignalID.begin();iter!=VecSignalID.end();++iter)
	{
		unsigned int nID=*iter;
		if(nID==nSignalID)
		{
			VecSignalID.erase(iter);
			VecSignalID.insert(VecSignalID.begin(),nID);
			break;
		}
	}

	m_DragInfo.SetVecDragSignalID(VecSignalID);
}

void XScreenManage::SetPreviewFrameShow(unsigned int nGroupID,BOOL bShow)
{
	VEC_SCREEN& VecScreen=GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		m_pMultiVideoWindow->ShowFrame(pScreen->GetIndex(),nGroupID,bShow);
	}
}

//判断4K时，添加4个Frame
void XScreenManage::AddDragFrame(RECTF rectInter)
{
	//整个视频区域
	RECTF InterRect(0,0,1920,1088);

	CString szRTSPAddr=m_DragInfo.GetRTSPAddr();

	int nInputNum=m_DragInfo.GetInputNum();
	CString szNum=_T("");
	if(nInputNum!=0)
		szNum.Format(_T("%d"),nInputNum);

	VEC_CSTRING& VecRTSPAddr=m_DragInfo.GetVecRTSPAddr();
	BOOL bIsUltra=m_DragInfo.GetIsUltra();
	//////////////////////////////////////////////////////////////////////////
	if(bIsUltra)
	{
		RECTF rect=rectInter;
		VEC_RECTF VecRect;
		SetRectToFoure(rect,VecRect);

		int i=0;
		for(VEC_RECTF::iterator iter=VecRect.begin();iter!=VecRect.end();++iter)
		{
			RECTF NewRect=*iter;
			CString szUltraRTSPAddr=VecRTSPAddr[i];
			XMultiVideoWindowFrame*pDragFrame=m_pMultiVideoWindow->AddFrame(0,szUltraRTSPAddr,NewRect,InterRect);

			m_pMultiVideoWindow->SetIsDragFrame(TRUE);

			if(i==0)
				m_pMultiVideoWindow->SetFrameText(0,pDragFrame,szNum);

			m_VecDragFrame.push_back(pDragFrame);
			i++;
		}
	}
	else
	{
		XMultiVideoWindowFrame* pDragFrame=m_pMultiVideoWindow->AddFrame(0,szRTSPAddr,rectInter,InterRect);
		m_pMultiVideoWindow->SetIsDragFrame(TRUE);

		m_pMultiVideoWindow->SetFrameText(0,pDragFrame,szNum);
		m_VecDragFrame.push_back(pDragFrame);
	}
}

void XScreenManage::ClearDragFrame()
{
	//TRACE(_T("ClearDragFrame\n"));

	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecDragFrame.begin();iter!=m_VecDragFrame.end();++iter)
	{
		XMultiVideoWindowFrame* pFrame=*iter;
		m_pMultiVideoWindow->DeleteFrame(0,pFrame);
	}
	m_VecDragFrame.clear();
}

void XScreenManage::CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd)
{
	VEC_CSTRING VecRTSPAddr;

	CString szHead=_T("rtsp://");
	CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
	//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

	CString szSubRTSP=_T("");
	for(int i=0;i<4;i++)
	{
		szSubRTSP=szHead+szUseName+_T(":")+szPassWd+_T("@")+szIP+szChenal[i]+_T("/")+_T("sub");
		VecRTSPAddr.push_back(szSubRTSP);
	}

	m_DragInfo.SetVecRTSPAddr(VecRTSPAddr);
}

void XScreenManage::CreateRTSPAddr(CString szIP,CString szUseName,CString szPassWd,VEC_CSTRING& Vec)
{
	CString szHead=_T("rtsp://");
	CString szChenal[4]={_T(":554"),_T(":1554"),_T(":2554"),_T(":3554")};
	//CString szChn[4]={_T("chn1"),_T("chn2"), _T("chn3"),_T("chn4")};

	CString szSubRTSP=_T("");
	for(int i=0;i<4;i++)
	{
		szSubRTSP=szHead+szUseName+_T(":")+szPassWd+_T("@")+szIP+szChenal[i]+_T("/")+_T("sub");
		Vec.push_back(szSubRTSP);
	}
}

void XScreenManage::SetVecInputSignalIndexAndID(XSignal* pSignal)
{
	int nSignalIndex=pSignal->GetInputIndex();
	int nTempIndex=(nSignalIndex-1)/4;
	int nFirstIndex=nTempIndex*4+1;

	unsigned int nSignalID=pSignal->GetSignalID();
	unsigned int nSignalGroupID=pSignal->GetSignalGroupID();

	BOOL bIsUltra=pSignal->GetIsUltra();
	//**********************************
	//信号ID集合
	VEC_UNINT VecSignalID;
	GetVecSignalID(nSignalGroupID,VecSignalID);
	m_DragInfo.SetVecDragSignalID(VecSignalID);

	//信号序号集合
	HYVEC_NUM VecSignalIndex;
	GetVecSignalIndex(nSignalGroupID,VecSignalIndex);
	m_DragInfo.SetVecDragSignalIndex(VecSignalIndex);

	if(bIsUltra)
	{
		if(VecSignalID.size()<4)
		{
			VecSignalID.clear();
			unsigned int nTempSignalID=nSignalID;
			nTempSignalID&=0xFFFFFFF0;

			for(int i=0;i<4;i++)
			{
				nTempSignalID+=1;
				VecSignalID.push_back(nTempSignalID);
			}
			m_DragInfo.SetVecDragSignalID(VecSignalID);
		}

		if(VecSignalIndex.size()<4)
		{
			VecSignalIndex.clear();
			int nTempFirstIndex=nFirstIndex;

			for(int i=0;i<4;i++)
			{
				VecSignalIndex.push_back(nTempFirstIndex);
				nTempFirstIndex+=1;
			}
			m_DragInfo.SetVecDragSignalIndex(VecSignalIndex);
		}
	}
}

void XScreenManage::GetVecSignalID(unsigned int nGroupID,VEC_UNINT& VecInt)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal *pSignal=*iter;
			int nSignalID=pSignal->GetSignalID();
			if(pSignal->GetSignalGroupID()==nGroupID)
				VecInt.push_back(nSignalID);
		}
	}

	sort(VecInt.begin(),VecInt.end());
	VecInt.erase(unique(VecInt.begin(), VecInt.end()), VecInt.end());
}

void XScreenManage::GetVecSignalIndex(unsigned int nGroupID,HYVEC_NUM& VecInt)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal *pSignal=*iter;
			int nSignalIndex=pSignal->GetInputIndex();
			if(pSignal->GetSignalGroupID()==nGroupID)
				VecInt.push_back(nSignalIndex);
		}
	}

	sort(VecInt.begin(),VecInt.end());
	VecInt.erase(unique(VecInt.begin(), VecInt.end()), VecInt.end());
}

void XScreenManage::ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
	int noffsetX, int noffsetY)
{
	//////////////////////////////////////////////////////////////////////////
	int nModel=GetScreenModel();
	if(nModel==SCREENMODEL_MATRIX)
		return;

	if(m_bIsLBDClick)
		return;

	POINTF tempPoint;
	XCalculateScreenManage::ReductionPoint(this, rect, noffsetX, noffsetY, point, tempPoint);

	if(m_CursorType==CURSORTYPE_NORMAL&&!m_bCreateSignal)
		return;

	UpdateSynTime();
	unsigned int nSignalID=m_DragInfo.GetDragSignalID();
	unsigned int nMoveSignalGroupID=m_DragInfo.GetDragSignalGroupID();
	//TRACE(_T("GroupID=%d\n"),nMoveSignalGroupID);

	//SetSignalSelectByGroupID(nMoveSignalGroupID);
	//SetFrameSelectByGroupID(nMoveSignalGroupID);

	CString szAnotherName=m_DragInfo.GetAnotherName();
	BOOL bIsUltra=m_DragInfo.GetIsUltra();
	XExpandInfo* pExpandInfo=m_DragInfo.GetExpandInfo();
	VEC_UNINT& VecSignalID=m_DragInfo.GetVecDragSignalID();
	int nIndex=m_DragInfo.GetInputIndex();
	HYVEC_NUM& VecSignalIndex=m_DragInfo.GetVecDragSignalIndex();
	CString szIP=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();
	VEC_CSTRING& VecRTSPAddr=m_DragInfo.GetVecRTSPAddr();
	//*******************
	//预览Info
	CString szRTSPAddr=m_DragInfo.GetRTSPAddr();
	XMultiVideoWindowFrame* pResFrame=m_DragInfo.GetPreviewFrame();

	//信号分辨率
	int nResulationH=1920;
	int nResulationV=1088;
	//*******************
	if(bIsUltra)
	{
		if((VecSignalID.size()!=4)
			||(VecSignalIndex.size()!=4))
			return;
	}
	else
	{
		if((VecSignalID.size()==0)
			||(VecSignalIndex.size()==0))
			return;
	}

	//*******************
	//利用m_NewRect会出错，没有重置
	//RECTF newRect=m_NewRect;
	RECTF newRect=m_InterRect;
	//*******************
	VEC_RECTF VecDragRectF;
	if(bIsUltra)
		SetRectToFoure(newRect,VecDragRectF);
	else
		VecDragRectF.push_back(newRect);

	//=======================
	//是否能移动
	ResetSignalNumInScreen();

	//******************
	//m_IsSendPocket=TRUE;
	//ClearVecSendData();
	//*******************
	int j=0;
	for(VEC_RECTF::iterator iter=VecDragRectF.begin();iter!=VecDragRectF.end();++iter)
	{
		RECTF rectDrag=*iter;

		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectDrag,VecScreen);
		unsigned int nSignalID=VecSignalID[j];
		if(!IsCanMoveSignal(VecScreen,nSignalID))
		{
			MAP_GROUPID MapDelSignalGroupID;
			MapDelSignalGroupID.clear();

			switch(m_nDragModel)
			{
			case DRAGMODEL_TIPMODEL:
				{
					m_ISViewButtonDown=FALSE;
					//清除拖动框
					ClearDragFrame();
					//设置拖拽标志位FALSE
					m_pMultiVideoWindow->SetIsDragFrame(FALSE);
					SetPreviewFrameShow(nMoveSignalGroupID,TRUE);
					m_pDelegate->MessageBoxFromKey(_T("384"),_T("该屏幕已超过最大信号个数，不能再添加信号！"),MB_OK);
					return;
				}
				break;
			case DRAGMODEL_UPMODEL:
				{
					//删除上面的
					GetDeleteSignalByCount(rectDrag,DRAGMODEL_UPMODEL,MapDelSignalGroupID);
				}
				break;
			case DRAGMODEL_DOWNMODEL:
				{
					//删除下面的
					GetDeleteSignalByCount(rectDrag,DRAGMODEL_DOWNMODEL,MapDelSignalGroupID);
				}
				break;
			default:
				break;
			}

			//删除信号
			for(MAP_GROUPID::iterator iter=MapDelSignalGroupID.begin();iter!=MapDelSignalGroupID.end();++iter)
			{
				unsigned int nGroupID=iter->first;
				DeleteSignalBySignalGroupID(nGroupID);
			}
		}
		j++;
	}
	//=======================
	//左键提起
	m_ISViewButtonDown=FALSE;
	m_bCreateSignal=FALSE;
	//清除拖动框
	ClearDragFrame();
	//设置拖拽标志位FALSE
	m_pMultiVideoWindow->SetIsDragFrame(FALSE);
	//========================
	//如果出去就删除
	//判断鼠标在不在屏幕中
	if(!XCalculateScreenManage::DecidePointInScreen(this,tempPoint))
	{
		//DeleteSignalBySignalGroupID(nMoveSignalGroupID);
		//XSendDataScreenManage::AddSendDataOfFinash(this);

		if(!OperateOfCloseSignal())
		{
			SetPreviewFrameShow(nMoveSignalGroupID,TRUE);
		}

		return;
	}

	//***********************
	int i=0;
	for(VEC_RECTF::iterator iter=VecDragRectF.begin();iter!=VecDragRectF.end();++iter)
	{
		RECTF rectDrag=*iter;

		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectDrag,VecScreen);
		//*******************
		unsigned int nMoveSignalID=VecSignalID[i];
		//TRACE(_T("ID=%d\n"),nMoveSignalID);

		int nSignalIndex=VecSignalIndex[i];
		CString szUltraRTSPAddr=VecRTSPAddr[i];
		//*******************
		//int nLevel=-1;
		VEC_SCREEN VecUPScreen;
		if(VecScreen.size()<=0)
			return;

		//判断是否新建信号
		BOOL bCreateNewSignal=IsCreateNewSignal(VecScreen,nMoveSignalID);

		for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;
			//*******************
			RECTF ScreenRect=pScreen->GetRect();
			if(ScreenRect.Intersect(rectDrag))
			{
				XSignal* pSignal=pScreen->GetSignalByID(nMoveSignalID);

				RECTF rectSignal;
				RECTF::Intersect(rectSignal,rectDrag,pScreen->GetRect());
				//******************************************************
				//所交区域占整个视频区域的
				float nResBeginX=(rectSignal.X-rectDrag.X)*nResulationH/rectDrag.Width;
				float nResBeginY=(rectSignal.Y-rectDrag.Y)*nResulationV/rectDrag.Height;
				float nTempResWidth=rectSignal.Width*nResulationH/rectDrag.Width;
				float nTempResHight=rectSignal.Height*nResulationV/rectDrag.Height; 

				RECTF rectImage;
				rectImage.X=nResBeginX;
				rectImage.Y=nResBeginY;
				rectImage.Width=nTempResWidth;
				rectImage.Height=nTempResHight;
				//******************************************************
				//新建信号
				if(pSignal==NULL)
				{
					pSignal=pScreen->AddSignal(
						rectSignal,
						nLevel,
						nSignalIndex, 
						szAnotherName,
						nMoveSignalID,
						nMoveSignalGroupID,
						pExpandInfo,
						bIsUltra);

					pSignal->SetIPAddr(szIP);
					pSignal->SetUseName(szUseName);
					pSignal->SetPassWd(szPassWd);
					//////////////////////////////////////////////////////////////////////////
					XMultiVideoWindowFrame* pFrame=NULL;
					if(bIsUltra)
					{
						pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szUltraRTSPAddr,rectSignal,rectImage);
						m_pDelegate->SetRTSPAddrCountPlus(szUltraRTSPAddr);
						pSignal->SetRTSPAddr(szUltraRTSPAddr);
					}
					else
					{
						pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
						m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
						pSignal->SetRTSPAddr(szRTSPAddr);
					}

					m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
					m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nSignalIndex);
					m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
					m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nMoveSignalID);
					m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nMoveSignalGroupID);

					pSignal->SetPreviewFrame(pFrame);
					//////////////////////////////////////////////////////////////////////////
					XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectDrag);
				}
				else
				{
					pSignal->SetRect(rectSignal);
					pSignal->SetIPAddr(szIP);
					pSignal->SetUseName(szUseName);
					pSignal->SetPassWd(szPassWd);
					//===========================
					XMultiVideoWindowFrame* pOldFrame=pSignal->GetPreviewFrame();
					m_pMultiVideoWindow->SetFrame(pScreen->GetIndex(),pOldFrame,rectSignal,rectImage);
					m_pMultiVideoWindow->ShowFrame(pScreen->GetIndex(),pOldFrame,TRUE);
			
					//发送开窗
					XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectDrag);
					//设置没有新建信号的屏幕进行信号置顶
					if(bCreateNewSignal)
						VecUPScreen.push_back(pScreen);
				}
			}
			else
			{
				int nPaneIndex=pScreen->GetBoardIndex();
				pScreen->DeleteSignalBySignalID(this,nPaneIndex,nMoveSignalID);
			}
		}

		//没有新建部分置顶
		for(VEC_SCREEN::iterator iter=VecUPScreen.begin();iter!=VecUPScreen.end();++iter)
		{
			XScreen *pScreen=*iter;
			int nPaneIndex=pScreen->GetBoardIndex();
			pScreen->SetSignalTopByID(nPaneIndex,nMoveSignalID);	
		}
		i++;
	}

	XSendDataScreenManage::AddSendDataOfFinash(this);
	//*******************
	//m_IsSendPocket=FALSE;
	//SendAllData();
	//*******************
}

void XScreenManage::SendAllData(BOOL bCopy) 
{
	int nDataLen=0;
	for(VEC_SENDDATA::iterator iter=m_VecSendData.begin();iter!=m_VecSendData.end();++iter)
	{
		XSendData* pSendData=*iter;
		nDataLen+=pSendData->m_DataLen;
	}
	//********************
	unsigned char* pData=new unsigned char[nDataLen];
	int nPos=0;
	for(VEC_SENDDATA::iterator iter=m_VecSendData.begin();iter!=m_VecSendData.end();++iter)
	{
		XSendData* pSendData=*iter;
		memcpy(pData+nPos,pSendData->m_Data,pSendData->m_DataLen);
		nPos+=pSendData->m_DataLen;
	}

	//********************
	unsigned char* pTemp=pData;
	//////////////////////////////////////////////////////////////////////////
	if(bCopy)
	{
		CString szTemp=_T("");
		CString szStr=_T("");
		for(int i=0;i<nDataLen;i++)
		{
			szTemp.Format(_T("%02X "),pTemp[i]);
			szStr+=szTemp;
		}

		//TRACE(_T("STR=%s\n"),szStr);
		HandleShearPlate::CopyOrderToSharePlate(szStr);
	}
	//////////////////////////////////////////////////////////////////////////

	int nMaxSendDataLen=1024;
	while(nDataLen>0)
	{
		int nSendDataLen=0;
		if(nDataLen>nMaxSendDataLen)
		{			
			nSendDataLen=nMaxSendDataLen;

			int nCount=0;
			if((pData[nSendDataLen+1]!=0xFF
				&&pData[nSendDataLen+2]!=0xFE)
				||(pData[nSendDataLen+1]==0xFF
				&&pData[nSendDataLen+2]==0xFE
				&&pData[nSendDataLen]==0xFE
				&&pData[nSendDataLen-1]==0xFF))
			{
				for(int i=0;i<nSendDataLen;i++)
				{
					if(pData[nSendDataLen-i]==0xFF
						&&pData[nSendDataLen-i+1]==0xFE)
					{
						nCount=i;
						break;
					}
				}
			}
			nSendDataLen-=nCount;
		}
		else
			nSendDataLen=nDataLen;

		nDataLen-=nSendDataLen;
		unsigned char* pSendData=new unsigned char[nSendDataLen];
		memcpy(pSendData,pTemp,nSendDataLen);

		if(!bCopy)
		{
			m_pDelegate->SendData((char*)pSendData, nSendDataLen);
		}

		delete []pSendData;
		pTemp+=nSendDataLen;
	}

	delete []pData;
	ClearVecSendData();		
}

void XScreenManage::ClearVecSendData()
{
	for(VEC_SENDDATA::iterator iter=m_VecSendData.begin();iter!=m_VecSendData.end();iter++)
		delete *iter;
	m_VecSendData.clear();
}

//添加拖拽模式后，用不到
//////////////////////////////////////////////////////////////////////////
BOOL XScreenManage::CanMoveSignal(VEC_RECTF& VecDragRectF,VEC_UNINT& VecSignalID,unsigned int GroupID)
{
	int i=0;
	for(VEC_RECTF::iterator iter=VecDragRectF.begin();iter!=VecDragRectF.end();++iter)
	{
		RECTF rectDrag=*iter;

		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectDrag,VecScreen);

		unsigned int nSignalID=VecSignalID[i];
		if(!IsCanMoveSignal(VecScreen,nSignalID))
		{
			m_ISViewButtonDown=FALSE;
			return FALSE;
		}

		i++;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL XScreenManage::IsCanMoveSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID)
{
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		int nNum=pScreen->GetAddSignalNumInScreen();
		XSignal* pSignal=pScreen->GetSignalByID(nSignalID);

		if(pSignal!=NULL)
			continue;

		int n=nNum;
		n=n+1;
		pScreen->SetAddSignalNumInScreen(n);

		if(!pScreen->CanAddSignal())
			return FALSE;	
	}

	return TRUE;
}

void XScreenManage::ResetSignalNumInScreen()
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		int nSize=VecSignal.size();
		pScreen->SetAddSignalNumInScreen(nSize);
	}
}

BOOL XScreenManage::CanMoveSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID)
{	
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		XSignal* pSignal=pScreen->GetSignalByID(nSignalID);
		if(pSignal!=NULL)
			continue;

		if(!pScreen->CanAddSignal())
		{
			m_pDelegate->MessageBoxFromKey(_T("384"),_T("该屏幕已经超过4个信号！"),MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL XScreenManage::IsCreateNewSignal(VEC_SCREEN& VecScreen,unsigned int nSignalID)
{
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		XSignal* pSignal = pScreen->GetSignalByID(nSignalID);

		if (pSignal==NULL)
			return TRUE;
	}

	return FALSE;
}

BOOL XScreenManage::IsHaveSignal(int nIndex)
{
	return m_pDelegate->IsHaveSignal(nIndex);
}

BOOL XScreenManage::IsHavePane(int nIndex)
{
	return m_pDelegate->IsHavePane(nIndex);
}

BOOL XScreenManage::IsHaveDevice(int nIndex)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		int nScreenIndex=pScreen->GetBoardIndex();
		if(nIndex==nScreenIndex)
		{
			if(pScreen->GetReStatus()==0x01
				||pScreen->GetReStatus()==0x11
				||pScreen->GetReStatus()==0x12
				||pScreen->GetReStatus()==0x13)
				return TRUE;
		}
	}
	return FALSE;
}

//是否为两路
void XScreenManage::IsTwoScreen(int nIndex)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		//int nScreenIndex=pScreen->GetReScreenIndex();

		int nBoardIndex=pScreen->GetBoardIndex();
		if(nIndex==nBoardIndex)
		{
			if(pScreen->GetReStatus()==0x11
				||pScreen->GetReStatus()==0x12
				||pScreen->GetReStatus()==0x13)
				pScreen->SetIsTwoSignal(TRUE);
		}
	}
}

void XScreenManage::ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)
{
	int nModel=GetScreenModel();
	if(nModel==SCREENMODEL_MATRIX)
	{
		SetCursor(CURSORTYPE_NORMAL);
		return;
	}

	POINTF tempPoint;
	XCalculateScreenManage::ReductionPoint(this, rect, noffsetX, noffsetY, point, tempPoint);

	if(nFlags&MK_LBUTTON
		&&m_ISViewButtonDown)
	{
		if(m_bCreateSignal)
		{
			UpdateSynTime();
			MoveSignalOfNew(m_Point,tempPoint);
			m_Point=tempPoint;
		}
		else
		{
			if(CURSORTYPE_NULL!=m_CursorType)
			{
				UpdateSynTime();
				MoveSignal(m_Point,tempPoint);
				m_Point=tempPoint;
			}
		}
	}
	else
	{
		XSignal* pSignal=NULL;
		if(XCalculateScreenManage::DecidePointInSignal(this,pSignal,tempPoint))
		{
			if(NULL==pSignal)
				return;

			unsigned int nSignalID=pSignal->GetSignalID();
			unsigned int nSignalGroupID=pSignal->GetSignalGroupID();
			RECTF rect=XCalculateScreenManage::GetRectBySignal(this,nSignalGroupID);

			m_InterRect=rect;
			//m_NewRect=rect;

			m_PositionType=XCalculateScreenManage::DecidePointInSignalPosition(this,rect,tempPoint);
			m_CursorType=XCalculateScreenManage::GetCursorTypeByPositionType(m_PositionType);
		}
		else
			m_CursorType=CURSORTYPE_NORMAL;
	}

	SetCursor(m_CursorType);
}

void XScreenManage::MoveSignalOfNew(POINTF& point1, POINTF& point2)
{
	RECTF tempRect=m_InterRect;

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;
	XCalculateScreenManage::MoveSignalOfNew(tempRect,size);

	//TRACE(_T("X=%f,y=%f,W=%f,H=%f\n"),tempRect.X,tempRect.Y,tempRect.Width,tempRect.Height);

	RECTF rectF=tempRect;
	BOOL bIsUltra=m_DragInfo.GetIsUltra();

	VEC_RECTF VecRect;
	SetRectToFoure(rectF,VecRect);

	if(bIsUltra)
	{
		int i=0;
		for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecDragFrame.begin();iter!=m_VecDragFrame.end();++iter)
		{
			XMultiVideoWindowFrame* pFrame=*iter;
			RECTF rect=VecRect[i];
			m_pMultiVideoWindow->SetFrame(0,pFrame,rect);
			i++;
		}
	}
	else
	{
		for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecDragFrame.begin();iter!=m_VecDragFrame.end();++iter)
		{
			XMultiVideoWindowFrame* pFrame=*iter;
			m_pMultiVideoWindow->SetFrame(0,pFrame,rectF);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	m_InterRect=tempRect;
	//m_NewRect=tempRect;
}

void XScreenManage::MoveSignal(POINTF& point1, POINTF& point2)
{
	RECTF tempRect=m_InterRect;

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCalculateScreenManage::MoveSignal(m_PositionType,tempRect,size);
	/////////////////////////////////////////////////////////////////////////
	//拖动Frame
	RECTF rectF=tempRect;
	BOOL bIsUltra=m_DragInfo.GetIsUltra();

	VEC_RECTF VecRect;
	SetRectToFoure(rectF,VecRect);

	if(bIsUltra)
	{
		int i=0;
		for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecDragFrame.begin();iter!=m_VecDragFrame.end();++iter)
		{
			XMultiVideoWindowFrame* pFrame=*iter;
			RECTF rect=VecRect[i];
			m_pMultiVideoWindow->SetFrame(0,pFrame,rect);
			i++;
		}
	}
	else
	{
		for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecDragFrame.begin();iter!=m_VecDragFrame.end();++iter)
		{
			XMultiVideoWindowFrame* pFrame=*iter;
			m_pMultiVideoWindow->SetFrame(0,pFrame,rectF);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	m_InterRect=tempRect;
	//m_NewRect=tempRect;
}

RECTF XScreenManage::GetInterRect()
{
	return m_InterRect;
}

VEC_SCREEN& XScreenManage::GetVecScreen()
{
	return m_VecScreen;
}

VEC_SCREEN& XScreenManage::GetVecScreen1()
{
	return m_VecScreen;
}

int XScreenManage::GetRTSPCountBySignal(CString szRTSP)
{
	if(szRTSP==_T(""))
		return 0;

	int nCount=0;
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			CString szRTSPAddr=pSignal->GetRTSPAddr();
			if(szRTSPAddr==szRTSP)
				nCount+=1;	
		}
	}

	return nCount;
}

XDragInfo& XScreenManage::GetDragInfo()
{
	return m_DragInfo;
}

void XScreenManage::ViewMouseLeave()
{

}

void XScreenManage::ViewKeyUp(UINT nChar)
{

} 

void XScreenManage::ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
	CRect& rect, int noffsetX, int noffsetY)
{
	if (!m_pDelegate->IsLogin())
	{
		m_pDelegate->MessageBoxFromKey(_T("378"), _T("请先进行登陆操作！"), MB_OK);
		return;
	}

	POINTF tempPoint;
	XCalculateScreenManage::ReductionPoint(this, rect, noffsetX, noffsetY, point, tempPoint);
	XScreen* pScreen=XCalculateScreenManage::GetScreenByPoint(this, tempPoint);

	if(NULL==pScreen)	
		return;

	m_TempScreen=pScreen;
	XSignal* pSignal=XCalculateScreenManage::GetSignalByPoint(pScreen,tempPoint);

	if(NULL!=pSignal)
	{
		int nIndex=pSignal->GetInputIndex();
		m_RBtnIndex=nIndex;
		unsigned int nSignalID=pSignal->GetSignalID();
		unsigned int nGroupID=pSignal->GetSignalGroupID();

		m_RBtnSignalID=nSignalID;
		m_RBtnSignalGroupID=nGroupID;

		BOOL IsUltra=pSignal->GetIsUltra();
		XExpandInfo pExpand=*(pSignal->GetExpandInfo());

		//////////////////////////////////////////////
		//预览
		XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();

		int nResulationH=pSignal->GetSignalHdpi();
		int nResulationV=pSignal->GetSignalVdpi();
		CString szIP=pSignal->GetIPAddr();
		CString szUseName=pSignal->GetUseName();
		CString szPassWd=pSignal->GetPassWd();
		CString szRTSPAddr=pSignal->GetRTSPAddr();
		//////////////////////////////////////////////
		//生成RTSP地址
		CreateRTSPAddr(szIP,szUseName,szPassWd);

		//信号ID集合
		VEC_UNINT VecSignalID;
		GetVecSignalID(nGroupID,VecSignalID);
		m_DragInfo.SetVecExpandSignalID(VecSignalID);

		//信号序号集合
		HYVEC_NUM VecSignalIndex;
		GetVecSignalIndex(nGroupID,VecSignalIndex);
		m_DragInfo.SetVecExpandSignalIndex(VecSignalIndex);
		
		/////////////////////////////////////////
		//重新分配四个ID(用于2k切4k)
		VEC_UNINT VecNewSignalID;
		m_DragInfo.SetSignalID(m_signalID+1);
		unsigned int nNewSignalID=m_signalID;
		nNewSignalID&=0xFFFFFFF;
		nNewSignalID=nNewSignalID<<4;
		for(int i=0;i<4;i++)
		{
			nNewSignalID+=1;
			VecNewSignalID.push_back(nNewSignalID);
		}
		m_DragInfo.SetVecChangeInputID(VecNewSignalID);
		/////////////////////////////////////////

		m_DragInfo.SetRTSPAddr(szRTSPAddr);
		m_DragInfo.SetIsUltra(IsUltra);
		m_DragInfo.SetExpand(&pExpand);
		m_DragInfo.SetPreviewFrame(pFrame);
		m_DragInfo.SetSignalResulationH(nResulationH);
		m_DragInfo.SetSignalResulationV(nResulationV);

		ShowSignalMenu();
	}
	else
		ShowScreenMenu();
}

void XScreenManage::ShowScreenMenu()
{
	CPoint p;
	GetCursorPos(&p);

	CMenu menu; 
	menu.CreatePopupMenu();

	int nIndex=m_TempScreen->GetBoardIndex();
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			//if(IsHaveDevice(nIndex))
			//{
			//	menu.AppendMenu(MF_STRING, ID_SCREEN_NOSEPARATE, m_pDelegate->GetTranslationString(_T("385"), _T("设置分辨率")));	

			//	//交换屏幕功能（放开即可）
			//	//menu.AppendMenu(MF_STRING, ID_SCREENCHANGE, m_pDelegate->GetTranslationString(_T("490"), _T("交换屏幕")));

			//	menu.AppendMenu(MF_SEPARATOR);
			//}

			//添加设置行列分辨率
			menu.AppendMenu(MF_STRING, ID_SETROWDPI, m_pDelegate->GetTranslationString(_T("762"), _T("行分辨率")));	
			menu.AppendMenu(MF_STRING, ID_SETCOLDPI, m_pDelegate->GetTranslationString(_T("763"), _T("列分辨率")));
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			if (m_pDelegate->IsAdminUser())
			{
				menu.AppendMenu(MF_STRING, ID_SCREEN_RESULATIONOFMATRIX, m_pDelegate->GetTranslationString(_T("385"), _T("设置分辨率")));
				menu.AppendMenu(MF_SEPARATOR);
			}
		}
		break;
	default:
		break;
	}

	menu.AppendMenu(MF_STRING, ID_ATTRIBUTE_SCREEN, m_pDelegate->GetTranslationString(_T("456"), _T("属性")));
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, p.x, p.y, m_pDelegate->GetCWND());
	menu.DestroyMenu(); 
}

void XScreenManage::ShowSignalMenu()
{
	CPoint p;
	GetCursorPos(&p);

	CMenu menu; 
	menu.CreatePopupMenu();

	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			if (m_pDelegate->IsAdminUser())
			{
				menu.AppendMenu(MF_STRING,ID_BTN_SETSIGNALTOP,m_pDelegate->GetTranslationString(_T("379"),_T("置顶")));
				menu.AppendMenu(MF_STRING,ID_BTN_SETSIGNALBOTTOM,m_pDelegate->GetTranslationString(_T("380"),_T("置底")));
				menu.AppendMenu(MF_STRING,ID_BTN_SETSIGNALSHIFTUP,m_pDelegate->GetTranslationString(_T("381"),_T("上移")));
				menu.AppendMenu(MF_STRING,ID_BTN_SETSIGNALSHIFTDOWN,m_pDelegate->GetTranslationString(_T("382"),_T("下移")));
				//menu.AppendMenu(MF_STRING,ID_BTN_SETSIGNALEXPAND,m_pDelegate->GetTranslationString(_T("383"),_T("扩展")));
				menu.AppendMenu(MF_STRING,ID_CHANGEINPUT,m_pDelegate->GetTranslationString(_T("436"),_T("切换")));
			}
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			if (m_pDelegate->IsAdminUser())
			{
				menu.AppendMenu(MF_STRING, ID_SCREEN_RESULATIONOFMATRIX, m_pDelegate->GetTranslationString(_T("385"), _T("设置分辨率")));
				menu.AppendMenu(MF_SEPARATOR);
			}
		}
		break;
	default:
		break;
	}

	menu.AppendMenu(MF_STRING, ID_SCREEN_CLOSESIGNAL, m_pDelegate->GetTranslationString(_T("235"), _T("关闭")));
	////////////////////////////////////////////////////////////////////////////////////////
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, p.x, p.y, m_pDelegate->GetCWND());
	menu.DestroyMenu(); 
}

CString XScreenManage::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

void XScreenManage::SetCursor(CURSORTYPE type)
{
	::SetCursor(GetCursor(type));
}

HCURSOR XScreenManage::GetCursor(CURSORTYPE type)
{
	HCURSOR cursor = NULL;

	switch(type)
	{
	case CURSORTYPE_NORMAL:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
		break;
	case CURSORTYPE_MOVE:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL));
		break;
	case CURSORTYPE_NESW:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW));
		break;
	case CURSORTYPE_NS:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
		break;
	case CURSORTYPE_NWSE:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE));
		break;
	case CURSORTYPE_WE:
		cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE));
		break;
	default:
		break;
	}
	return cursor;
}

void XScreenManage::SetBeginIndex(int n)
{
	m_BeginIndex=n;
}

int XScreenManage::GetBeginIndex()
{
	return m_BeginIndex;
}

void XScreenManage::SetScreenModel(int n)
{
	m_nScreenModel=n;
}

int XScreenManage::GetScreenModel()
{
	return m_nScreenModel;
}

void XScreenManage::SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo)
{
	m_VecScreenInfo=VecScreenInfo;
}

VEC_SCREENDATA& XScreenManage::GetVecScreenData()
{
	return m_VecScreenData;
}

MAP_ROWINFO& XScreenManage::GetMapRowInfo()
{
	return m_MapRowInfo;
}

MAP_COLINFO& XScreenManage::GetMapColInfo()
{
	return m_MapColInfo;
}

void XScreenManage::SetVecScreenData(VEC_SCREENDATA& VecData)
{
	m_VecScreenData=VecData;
}

void XScreenManage::InitVecScreen()
{
	int nSignalCount=m_nScreenCountH*m_nScreenCountV;

	float top=0.0f;
	float left=0.0f;
	int nIndex=GetBeginIndex();

	for(int i=0;i<m_nScreenCountV;i++)
	{
		left=0.0f;
		for(int j=0;j<m_nScreenCountH;j++)
		{
			RECTF screenRect(left, top, (Gdiplus::REAL)m_nResolutionH, (Gdiplus::REAL)m_nResolutionV);
			XScreen* pScreen=new XScreen;
			pScreen->SetManage(this);
			pScreen->SetIndex(nIndex);
			pScreen->SetBoardIndex(nIndex);
			pScreen->SetRect(screenRect);
			pScreen->ResetMaxSignalInScreen();

			//是否为右、下侧屏幕
			if(i==m_nScreenCountV-1)
				pScreen->SetIsBottom(TRUE);
			if(j==m_nScreenCountH-1)
				pScreen->SetIsRight(TRUE);

			//////////////////////////////////////////////////////////////////////////
			pScreen->SetScreenRow(i+1);
			pScreen->SetScreenCol(j+1);

			//////////////////////////////////////////////////////////////////////////

			m_VecScreen.push_back(pScreen);
			//**************************************
			XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(nIndex,nIndex,screenRect,0,FALSE);
			CString szText=SetText(pScreen);
			m_pMultiVideoWindow->SetFramesText(nIndex,szText,12);

			//m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
			//m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
			//m_pMultiVideoWindow->SetFramesResulationH(m_nResolutionH);
			//m_pMultiVideoWindow->SetFramesResulationV(m_nResolutionV);
			//**************************************
			left += m_nResolutionH;
			nIndex++;

			//////////////////////////////////////////////////////////////////////////
		}
		top+=m_nResolutionV;
	}

	if(m_nScreenCountH!=0&&m_nScreenCountV!=0)
	{
		SetScreenWidthAndHight();
		m_pMultiVideoWindow->SetMapRowInfo(m_MapRowInfo);
		m_pMultiVideoWindow->SetMapColInfo(m_MapColInfo);
	}
}

void XScreenManage::InitSceneVecScreen()
{
	int nSignalCount=m_nScreenCountH*m_nScreenCountV;

	float top=0.0f;
	float left=0.0f;
	VEC_SCREENINFO& VecScreenInfo=m_VecScreenInfo;
	int k=0;
	for(int i=0;i<m_nScreenCountV;i++)
	{
		left=0.0f;
		for(int j=0;j<m_nScreenCountH;j++)
		{
			XScreenInfo* pData=VecScreenInfo[k];
			RECTF screenRect(left, top, (Gdiplus::REAL)m_nResolutionH, (Gdiplus::REAL)m_nResolutionV);
			XScreen* pScreen = new XScreen;
			int nScreenIndex=pData->GetScreenIndex();
			int nBoardIndex=pData->GetBoardIndex();
			BOOL bIsTwoScreen=pData->GetIsTwoScreen();
			int nNumOfTwo=pData->GetNumOfScreen();
			pScreen->SetManage(this);
			pScreen->SetIndex(nScreenIndex);
			pScreen->SetBoardIndex(nBoardIndex);
			pScreen->SetIsTwoSignal(bIsTwoScreen);
			pScreen->SetNumOfTwoScreen(nNumOfTwo);
			pScreen->SetRect(screenRect);
			pScreen->ResetMaxSignalInScreen();

			//是否为右、下侧屏幕
			if(i==m_nScreenCountV-1)
				pScreen->SetIsBottom(TRUE);
			if(j==m_nScreenCountH-1)
				pScreen->SetIsRight(TRUE);

			//////////////////////////////////////////////////////////////////////////
			pScreen->SetScreenRow(i+1);
			pScreen->SetScreenCol(j+1);

			//////////////////////////////////////////////////////////////////////////

			m_VecScreen.push_back(pScreen);
			//===================================
			//添加预览墙屏幕
			XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(nScreenIndex,nBoardIndex,screenRect,nNumOfTwo,bIsTwoScreen);
			CString szText=SetText(pScreen);
			m_pMultiVideoWindow->SetFramesText(nScreenIndex,szText,12);

			//m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
			//m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
			//m_pMultiVideoWindow->SetFramesResulationH(m_nResolutionH);
			//m_pMultiVideoWindow->SetFramesResulationV(m_nResolutionV);
			//===================================
			left+=m_nResolutionH;
			k++;
		}
		top+=m_nResolutionV;
	}
	ClearVecScreenData();

	if(m_nScreenCountH!=0&&m_nScreenCountV!=0)
	{
		SetScreenWidthAndHight();
		m_pMultiVideoWindow->SetMapRowInfo(m_MapRowInfo);
		m_pMultiVideoWindow->SetMapColInfo(m_MapColInfo);
	}
}

//更新屏幕字体
void XScreenManage::ReLoadInterface()
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		CString szText=SetText(pScreen);
		m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
	}
}

CString XScreenManage::SetText(XScreen* pScreen)
{
	int nScreenIndex=pScreen->GetIndex();
	int nBoardIndex=pScreen->GetBoardIndex();

	BOOL bIsTwoScreen=pScreen->GetIsTwoSignal();
	int nPaneIndex=pScreen->GetNumOfTwoScreen();

	CString szText=_T("");
	CString szStr=m_pDelegate->GetTranslationString(_T("230"), _T("屏幕"));
	CString szStr1=m_pDelegate->GetTranslationString(_T("505"), _T("板卡"));

	CString szScreenName=pScreen->GetScreenName();

	if(nBoardIndex==0)
	{
		CString szStr2=m_pDelegate->GetTranslationString(_T("610"), _T("未分配"));

		if(szScreenName==_T(""))
			szText.Format(_T("%s:%d %s:%s"),szStr,nScreenIndex,szStr1,szStr2);
		else
			szText.Format(_T("%s:%d(%s) %s:%s"),szStr,nScreenIndex,szScreenName,szStr1,szStr2);
	}
	else
	{
		switch(m_nScreenModel)
		{
		case SCREENMODEL_SPLIC:
			{
				if(bIsTwoScreen)
				{
					if(szScreenName==_T(""))
					{
						if(nPaneIndex)
							szText.Format(_T("%s:%d %s:%d-%d"),szStr,nScreenIndex,szStr1,nBoardIndex,nPaneIndex);
						else
							szText.Format(_T("%s:%d %s:%d"),szStr,nScreenIndex,szStr1,nBoardIndex);
					}
					else
					{
						if(nPaneIndex)
							szText.Format(_T("%s:%d(%s) %s:%d-%d"),szStr,nScreenIndex,szScreenName,szStr1,nBoardIndex,nPaneIndex);
						else
							szText.Format(_T("%s:%d(%s) %s:%d"),szStr,nScreenIndex,szScreenName,szStr1,nBoardIndex);
					}
				}
				else
				{
					if(szScreenName==_T(""))
						szText.Format(_T("%s:%d %s:%d"),szStr,nScreenIndex,szStr1,nBoardIndex);
					else
						szText.Format(_T("%s:%d(%s) %s:%d"),szStr,nScreenIndex,szScreenName,szStr1,nBoardIndex);
				}
			}
			break;
		case SCREENMODEL_MATRIX:
			{
				if(szScreenName==_T(""))
				{
					if(nPaneIndex)
						szText.Format(_T("%s:%d %s:%d-%d"),szStr,nScreenIndex,szStr1,nBoardIndex,nPaneIndex);
					else
						szText.Format(_T("%s:%d %s:%d"),szStr,nScreenIndex,szStr1,nBoardIndex);
				}
				else
				{
					if(nPaneIndex)
						szText.Format(_T("%s:%d(%s) %s:%d-%d"),szStr,nScreenIndex,szScreenName,szStr1,nBoardIndex,nPaneIndex);
					else
						szText.Format(_T("%s:%d(%s) %s:%d"),szStr,nScreenIndex,szScreenName,szStr1,nBoardIndex);
				}
			}
			break;
		default:
			break;
		}
	}
	return szText;
}

int XScreenManage::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

BOOL XScreenManage::SendData(char* pData, int nDataLen)
{
	if(m_IsSendPocket)
	{
		XSendData* pSendData=new XSendData;

		pSendData->m_Data=new unsigned char[nDataLen];
		memcpy(pSendData->m_Data,pData,nDataLen);

		pSendData->m_DataLen=nDataLen;

		m_VecSendData.push_back(pSendData);
		return TRUE;
	}
	else
		return m_pDelegate->SendData(pData, nDataLen);
}

void XScreenManage::ShowManage(int nShowState)
{
	m_ShowType = nShowState;
}

float XScreenManage::GetMultiScale()
{
	return m_nCurScale/100.0f;
}

float XScreenManage::GetScale()
{
	return m_nCurScale/100.0f;
}

void XScreenManage::SetCurScale(int n)
{
	m_nCurScale=n;
}

int XScreenManage::GetCurScale()
{
	return m_nCurScale;
}

CString XScreenManage::GetDeviceIP()
{
	return m_pDelegate->GetDeviceIP();
}

void XScreenManage::SetDeviceIP(CString str)
{
	m_pDelegate->SetDeviceIP(str);
}

int XScreenManage::GetDevicePort()
{
	return m_pDelegate->GetDevicePort();
}

void XScreenManage::SetDevicePort(int n)
{
	m_pDelegate->SetDevicePort(n);
}

CString XScreenManage::GetLanguagetype()
{
	return m_pDelegate->GetLanguagetype();
}

void XScreenManage::SetLanguagetype(CString type)
{
	m_pDelegate->SetLanguagetype(type);
}

void XScreenManage::InvalidateView()
{

}

void XScreenManage::ResetViewSize()
{
	if(NULL!=m_View)
		m_View->ResetSize();
}

BOOL XScreenManage::DragSplicInfo(CRect rc, XDragInfo* pInfo)
{
	unsigned int nSignalGroupID=pInfo->GetSignalGroupID();
	BOOL bIsUltra=pInfo->GetIsUltra();

	//BOOL bIsUltra=TRUE;

	//局部放大偏移
	XExpandInfo* pExpandInfo=pInfo->GetExpandInfo();
	CString szAnotherName=pInfo->GetAnotherName();
	CString szRTSPAddr=pInfo->GetRTSPAddr();
	int nSignalIndex=pInfo->GetInputIndex();
	HYVEC_NUM& VecSignalIndex=pInfo->GetVecSignalIndex();
	VEC_UNINT& VecSignalID=pInfo->GetVecSignalID();
	VEC_CSTRING& VecRTSPAddr=pInfo->GetVecRTSPAddr();
	CString szIPAddr=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();

	if(bIsUltra)
	{
		if((VecSignalID.size()!=4)||(VecSignalIndex.size()!=4))
			return FALSE;
	}
	//***********************
	//判断是否插入面板
	if(!IsHavePane(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("395"),_T("该输入没有插入面板！"),MB_OK);
		return FALSE;
	}
	//判断该输入是否有信号
	if(!IsHaveSignal(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("394"),_T("该输入无信号！"),MB_OK);
		return FALSE;
	}

	//********************************
	CMultiviewerView* pView=GetView();
	pView->ScreenToClient(&rc);
	CRect rectView;
	pView->GetClientRect(&rectView);

	//判断信号是否托在预览面板上面
	if(rc.top>rectView.bottom)
		return FALSE;

	POINTF tempPointLT;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.TopLeft(),tempPointLT);
	POINTF tempPointRB;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.BottomRight(),tempPointRB);

	//整个区域
	RECTF rectNormal(tempPointLT.X,tempPointLT.Y,tempPointRB.X-tempPointLT.X, tempPointRB.Y-tempPointLT.Y);
	//********************************
	//根据状态模式来求整体区域
	RECTF rect;
	switch(m_nStatus)
	{
	case DRAGSTATUS_FULL:
		{
			VEC_SCREEN VecScreenTemp;
			CalculateVecScreen(rectNormal,VecScreenTemp);
			RECTF rectFull=XCalculateScreenManage::GetRectByVecScreen(VecScreenTemp);
			//////////////////////////////////////////////////////////////////////////
			//删除原有信号
			VEC_UNINT VecGroupID;
			for(VEC_SCREEN::iterator iter=VecScreenTemp.begin();iter!=VecScreenTemp.end();++iter)
			{
				XScreen* pTempScreen=*iter;
				VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
				for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
				{
					XSignal* pSignal=*iter;
					unsigned int nGroupID=pSignal->GetSignalGroupID();
					VecGroupID.push_back(nGroupID);
				}
			}
			//删除信号
			for(VEC_UNINT::iterator iter=VecGroupID.begin();iter!=VecGroupID.end();++iter)
			{
				unsigned int nGroupID=*iter;
				DeleteSignalBySignalGroupID(nGroupID);
			}
			//////////////////////////////////////////////////////////////////////////
			rect=rectFull;
		}
		break;
	case DRAGSTATUS_NORMAL:
		rect=rectNormal;
		break;
	case DRAGSTATUS_FOUR:
		{
			//鼠标位置
			POINTF tempPoint;
			tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
			tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

			//首先鼠标所在屏幕
			XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);
			if(pTempScreen==NULL)
				return FALSE;

			RECTF rectTemp=pTempScreen->GetRect();
			//等分区域
			VEC_RECTF VecFourRect;

			if(pTempScreen->GetIsTwoSignal())
				SetRectToTwo(rectTemp,VecFourRect);
			else
				SetRectToFoure(rectTemp,VecFourRect);

			for(VEC_RECTF::iterator iter=VecFourRect.begin();iter!=VecFourRect.end();++iter)
			{
				RECTF rectFour=*iter;
				if(rectFour.Contains(tempPoint))
					rect=rectFour;
			}
		}
		break;
	case DRAGSTATUS_INTER:
		{
			RECTF rectInter=XCalculateScreenManage::GetInterRectByAllScreen(this);
			rect=rectInter;
		}
		break;
	case DRAGSTATUS_COPY:
		{
			//鼠标位置
			POINTF tempPoint;
			tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
			tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

			//首先鼠标所在屏幕
			XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);
			if(pTempScreen==NULL)
				return FALSE;

			VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
			int nSize=VecSignal.size();

			if(nSize==0)
				rect=rectNormal;
			else
			{
				XSignal* pSignal=VecSignal[nSize-1];
				if(pSignal==NULL)
					return FALSE;

				unsigned int nID=pSignal->GetSignalGroupID();
				RECTF rectTemp=XCalculateScreenManage::GetRectBySignal(this,nID);
				rect=rectTemp;
			}
		}
		break;
	default:
		break;
	}

	//********************************
	//是否为4k（4块区域）
	VEC_RECTF VecRectF;
	if(bIsUltra)
		SetRectToFoure(rect,VecRectF);
	else
		VecRectF.push_back(rect);
	//********************************
	//判断是否超过信号个数
	ResetSignalNumInScreen();
	for(VEC_RECTF::iterator iter=VecRectF.begin();iter!=VecRectF.end();++iter)
	{
		RECTF rectReal=*iter;
		//******************************
		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectReal,VecScreen);
		//******************************
		//判断是否超过四个信号
		if(!CanAddNewSignal(VecScreen))
		{
			//需要先找出需要删除的信号
			MAP_GROUPID MapDelSignalGroupID;
			MapDelSignalGroupID.clear();

			switch(m_nDragModel)
			{
			case DRAGMODEL_TIPMODEL:
				{
					m_pDelegate->MessageBoxFromKey(_T("384"),_T("该屏幕已超过最大信号个数，不能再添加信号！"),MB_OK);
					return FALSE;
				}
				break;
			case DRAGMODEL_UPMODEL:
				//删除上面的
				GetDeleteSignalByCount(rectReal,DRAGMODEL_UPMODEL,MapDelSignalGroupID);
				break;
			case DRAGMODEL_DOWNMODEL:
				//删除下面的
				GetDeleteSignalByCount(rectReal,DRAGMODEL_DOWNMODEL,MapDelSignalGroupID);
				break;
			default:
				break;
			}

			//删除信号
			for(MAP_GROUPID::iterator iter=MapDelSignalGroupID.begin();iter!=MapDelSignalGroupID.end();++iter)
			{
				unsigned int nGroupID=iter->first;
				DeleteSignalBySignalGroupID(nGroupID);
			}
		}
	}

	//********************************
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//********************************
	//任何分辨率都转化为1920*1088
	int nResulationH=1920;
	int nResulationV=1088;
	//***********************
	int i=0;
	for(VEC_RECTF::iterator iter=VecRectF.begin();iter!=VecRectF.end();++iter)
	{
		RECTF rectReal=*iter;
		//******************************
		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectReal,VecScreen);
		//******************************
		if(VecScreen.size()<=0)
		{
			m_IsSendPocket=FALSE;
			return FALSE;
		}
			

		//信号ID
		unsigned int nSignalID=VecSignalID[i];
		nSignalID&=0x7FFFFFFF;

		if(bIsUltra)
			nSignalID|=0x80000000;
		//************************************
		//信号序号
		int nSignalIndex=VecSignalIndex[i];
		//************************************
		//4KRTSP地址
		CString szUltraRTSPAddr=VecRTSPAddr[i];
		//************************************
		UpdateSynTime();
		
		for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			int nScreenIndex=pScreen->GetIndex();
			//=======================================================
			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;
			//=======================================================
			if (!m_pDelegate->GetUserNodePower(pInfo->GetInputIndex(), nScreenIndex))
			{
				CString szNotice=m_pDelegate->GetNotice();

				if(szNotice!=_T(""))
					m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
				else
					m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

				m_IsSendPocket=FALSE;

				return FALSE;
			}
			
			//与每个屏幕所交区域
			RECTF rectSignal;
			RECTF::Intersect(rectSignal,rectReal,pScreen->GetRect());
			//=======================================================
			//视频区域
			float nResBeginX=nResBeginX=(rectSignal.X-rectReal.X)*nResulationH/rectReal.Width;
			float nResBeginY=nResBeginY=(rectSignal.Y-rectReal.Y)*nResulationV/rectReal.Height;
			float nTempResWidth=nTempResWidth=rectSignal.Width*nResulationH/rectReal.Width;
			float nTempResHight=nTempResHight=rectSignal.Height*nResulationV/rectReal.Height; 

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//TRACE(_T("rectImageX=%f,rectImageY=%f,rectImageW=%f,rectImageH=%f\n"),rectImage.X,rectImage.Y,rectImage.Width,rectImage.Height);
			//=======================================================
			XSignal* pSignal=pScreen->AddSignal(
				rectSignal,
				nLevel,
				nSignalIndex, 
				szAnotherName,
				nSignalID,
				nSignalGroupID,
				pExpandInfo,
				bIsUltra);

			pSignal->SetIPAddr(szIPAddr);
			pSignal->SetUseName(szUseName);
			pSignal->SetPassWd(szPassWd);

			//TRACE(_T("rectSignalX=%f,rectSignalY=%f,rectSignalW=%f,rectSignalH=%f\n"),rectSignal.X,rectSignal.Y,rectSignal.Width,rectSignal.Height);
			
			//添加视频墙
			//////////////////////////////////////////////////////////////////////////
			XMultiVideoWindowFrame* pFrame=NULL;
			if(bIsUltra)
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szUltraRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szUltraRTSPAddr);
				pSignal->SetRTSPAddr(szUltraRTSPAddr);	
			}
			else
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
				pSignal->SetRTSPAddr(szRTSPAddr);	
			}

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nSignalIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nSignalID);
			m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nSignalGroupID);

			pSignal->SetPreviewFrame(pFrame);
			//////////////////////////////////////////////////////////////////////////
			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectReal);
		}
		i++;
	}

	XSendDataScreenManage::AddSendDataOfFinash(this);
	//*****************************
	m_IsSendPocket=FALSE;
	SendAllData();
	//******************************
	return TRUE;
}

void XScreenManage::GetDeleteSignalByCount(RECTF rect,int nType,MAP_GROUPID& Map)
{
	VEC_SCREEN VecScreen;
	CalculateVecScreen(rect,VecScreen);

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		int nSignalCount=pScreen->GetMaxSignalNumInScreen();
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		int nSize=VecSignal.size();
		if(nSignalCount==nSize)
		{	
			XSignal* pSignal=NULL;

			switch(nType)
			{
			case DRAGMODEL_UPMODEL:
				pSignal=VecSignal[nSize-1];
				break;
			case DRAGMODEL_DOWNMODEL:
				pSignal=VecSignal[0];
				break;
			default:
				break;
			}

			if(pSignal==NULL)
				return;

			int nIndex=pSignal->GetInputIndex();
			unsigned int nGroupID=pSignal->GetSignalGroupID();
			MAP_GROUPID::iterator iterMap=Map.find(nGroupID);
			if(iterMap==Map.end())
				Map.insert(std::pair<unsigned int,int>(nGroupID,nIndex));
		}
	}
}

BOOL XScreenManage::DragMatrixInfo(CRect rc, XDragInfo* pInfo)
{
	BOOL bIsUltra=pInfo->GetIsUltra();

	if(bIsUltra)
	{
		m_pDelegate->MessageBoxFromKey(_T("708"),_T("矩阵不能添加4K信号！"),MB_OK);
		return FALSE;
	}

	unsigned int nSignalGroupID=pInfo->GetSignalGroupID();
	//BOOL bIsUltra=TRUE;

	//局部放大偏移
	XExpandInfo* pExpandInfo=pInfo->GetExpandInfo();
	CString szAnotherName=pInfo->GetAnotherName();
	CString szRTSPAddr=pInfo->GetRTSPAddr();
	int nSignalIndex=pInfo->GetInputIndex();
	unsigned int nSignalID=pInfo->GetSignalID();
	CString szIPAddr=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();

	//***********************
	//判断是否插入面板
	if(!IsHavePane(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("395"),_T("该输入没有插入面板！"),MB_OK);
		return FALSE;
	}
	//判断该输入是否有信号
	if(!IsHaveSignal(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("394"),_T("该输入无信号！"),MB_OK);
		return FALSE;
	}

	//********************************
	CMultiviewerView* pView=GetView();
	pView->ScreenToClient(&rc);
	CRect rectView;
	pView->GetClientRect(&rectView);

	//判断信号是否托在预览面板上面
	if(rc.top>rectView.bottom)
		return FALSE;

	POINTF tempPointLT;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.TopLeft(),tempPointLT);
	POINTF tempPointRB;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.BottomRight(),tempPointRB);

	POINTF tempPoint;
	tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
	tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

	XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);

	if(pTempScreen==NULL)
		return FALSE;

	RECTF rect=pTempScreen->GetRect();

	//删除原来信号
	VEC_UNINT VecGroupID;
	VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
	for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
	{
		XSignal* pSignal=*iter;
		unsigned int nGroupID=pSignal->GetSignalGroupID();
		VecGroupID.push_back(nGroupID);
	}
	//删除信号
	for(VEC_UNINT::iterator iter=VecGroupID.begin();iter!=VecGroupID.end();++iter)
	{
		unsigned int nGroupID=*iter;
		DeleteSignalBySignalGroupID(nGroupID);
	}

	//********************************
	//任何分辨率都转化为1920*1088
	int nResulationH=1920;
	int nResulationV=1088;
	//************************************
	//4KRTSP地址
	CString szUltraRTSPAddr=_T("");
	//信号ID
	nSignalID&=0x7FFFFFFF;

	//************************************
	UpdateSynTime();
	int nLevel=1;

	int nScreenIndex=pTempScreen->GetIndex();

	if (!m_pDelegate->GetUserNodePower(pInfo->GetInputIndex(), nScreenIndex))
	{
		CString szNotice=m_pDelegate->GetNotice();

		if(szNotice!=_T(""))
			m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
		else
			m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

		return FALSE;
	}

	//与每个屏幕所交区域
	RECTF rectSignal;
	RECTF::Intersect(rectSignal,rect,pTempScreen->GetRect());
	//=======================================================
	//视频区域
	float nResBeginX=nResBeginX=(rectSignal.X-rect.X)*nResulationH/rect.Width;
	float nResBeginY=nResBeginY=(rectSignal.Y-rect.Y)*nResulationV/rect.Height;
	float nTempResWidth=nTempResWidth=rectSignal.Width*nResulationH/rect.Width;
	float nTempResHight=nTempResHight=rectSignal.Height*nResulationV/rect.Height; 

	RECTF rectImage;
	rectImage.X=nResBeginX;
	rectImage.Y=nResBeginY;
	rectImage.Width=nTempResWidth;
	rectImage.Height=nTempResHight;
	//TRACE(_T("rectImageX=%f,rectImageY=%f,rectImageW=%f,rectImageH=%f\n"),rectImage.X,rectImage.Y,rectImage.Width,rectImage.Height);
	//=======================================================
	XSignal* pSignal=pTempScreen->AddSignal(
		rectSignal,
		nLevel,
		nSignalIndex, 
		szAnotherName,
		nSignalID,
		nSignalGroupID,
		pExpandInfo,
		bIsUltra);

	pSignal->SetIPAddr(szIPAddr);
	pSignal->SetUseName(szUseName);
	pSignal->SetPassWd(szPassWd);

	//TRACE(_T("rectSignalX=%f,rectSignalY=%f,rectSignalW=%f,rectSignalH=%f\n"),rectSignal.X,rectSignal.Y,rectSignal.Width,rectSignal.Height);

	//添加视频墙
	//////////////////////////////////////////////////////////////////////////
	XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(pTempScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
	m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
	pSignal->SetRTSPAddr(szRTSPAddr);

	m_pMultiVideoWindow->SetFrameIndex(pTempScreen->GetIndex(),pFrame,nSignalIndex);
	m_pMultiVideoWindow->SetFrameAnotherName(pTempScreen->GetIndex(),pFrame,szAnotherName);
	m_pMultiVideoWindow->SetFrameID(pTempScreen->GetIndex(),pFrame,nSignalID);
	m_pMultiVideoWindow->SetFrameGroupID(pTempScreen->GetIndex(),pFrame,nSignalGroupID);

	pSignal->SetPreviewFrame(pFrame);
	//////////////////////////////////////////////////////////////////////////
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	XSendDataScreenManage::AddSendDataOfMatrixSignal(this,pSignal,pTempScreen);
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//*****************************
	m_IsSendPocket=FALSE;
	SendAllData();

	return TRUE;
}

BOOL XScreenManage::DragInfo(CRect rc,CPoint point,XDragInfo* pInfo)
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		return DragSplicInfo(rc,pInfo);
		break;
	case SCREENMODEL_MATRIX:
		return DragMatrixInfo(rc,pInfo);
		break;
	default:
		break;
	}

	return TRUE;
}

BOOL XScreenManage::DragSplicInfo(CRect rc, XRTSPInfo* pInfo)
{
	int nPreviewIndex=pInfo->GetPreviewIndex();

	if(nPreviewIndex==0)
	{
		m_pDelegate->MessageBoxFromKey(_T("684"),_T("请先拖拽输入信号！"),MB_OK);
		return FALSE;
	}

	unsigned int nPreviewGroupID=pInfo->GetPreviewGroupID();
	BOOL bIsUltra=pInfo->GetIsUltra();
	//局部放大偏移
	XExpandInfo* pExpandInfo=pInfo->GetExpandInfo();
	CString szAnotherName=pInfo->GetAnotherName();
	HYVEC_NUM& VecPreviewIndex=pInfo->GetVecPreviewIndex();
	VEC_UNINT& VecPreviewID=pInfo->GetVecPreviewID();
	VEC_CSTRING& VecRTSPAddr=pInfo->GetVecRTSPAddr();
	CString szIP=pInfo->GetIPAddr();
	CString szUseName=pInfo->GetUseName();
	CString szPassWd=pInfo->GetPassWd();
	/////////////////////////////////////////////////////
	CString szRTSPAddr=pInfo->GetRTSPAddr();
	/////////////////////////////////////////////////////

	if(bIsUltra)
	{
		if((VecPreviewID.size()!=4)||(VecPreviewIndex.size()!=4))
			return FALSE;
	}
	//***********************
	//判断是否插入面板
	if(!IsHavePane(nPreviewIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("395"),_T("该输入没有插入面板！"),MB_OK);
		return FALSE;
	}
	//判断该输入是否有信号
	if(!IsHaveSignal(nPreviewIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("394"),_T("该输入无信号！"),MB_OK);
		return FALSE;
	}

	//********************************
	CMultiviewerView* pView=GetView();
	pView->ScreenToClient(&rc);
	CRect rectView;
	pView->GetClientRect(&rectView);
	POINTF tempPointLT;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.TopLeft(),tempPointLT);
	POINTF tempPointRB;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.BottomRight(),tempPointRB);

	//整个区域
	RECTF rectNormal(tempPointLT.X,tempPointLT.Y,tempPointRB.X-tempPointLT.X, tempPointRB.Y-tempPointLT.Y);
	//********************************
	//根据状态模式来求整体区域
	RECTF rect;
	switch(m_nStatus)
	{
	case DRAGSTATUS_FULL:
		{
			VEC_SCREEN VecScreenTemp;
			CalculateVecScreen(rectNormal,VecScreenTemp);
			RECTF rectFull=XCalculateScreenManage::GetRectByVecScreen(VecScreenTemp);
			//////////////////////////////////////////////////////////////////////////
			//删除原有信号
			VEC_UNINT VecGroupID;
			for(VEC_SCREEN::iterator iter=VecScreenTemp.begin();iter!=VecScreenTemp.end();++iter)
			{
				XScreen* pTempScreen=*iter;
				VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
				for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
				{
					XSignal* pSignal=*iter;
					unsigned int nGroupID=pSignal->GetSignalGroupID();
					VecGroupID.push_back(nGroupID);
				}
			}
			//删除信号
			for(VEC_UNINT::iterator iter=VecGroupID.begin();iter!=VecGroupID.end();++iter)
			{
				unsigned int nGroupID=*iter;
				DeleteSignalBySignalGroupID(nGroupID);
			}
			//////////////////////////////////////////////////////////////////////////
			rect=rectFull;
		}
		break;
	case DRAGSTATUS_NORMAL:
		{
			rect=rectNormal;
		}
		break;
	case DRAGSTATUS_FOUR:
		{
			//鼠标位置
			POINTF tempPoint;
			tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
			tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

			//首先鼠标所在屏幕
			XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);
			if(pTempScreen==NULL)
				return FALSE;

			RECTF rectTemp=pTempScreen->GetRect();
			//四等分区域
			VEC_RECTF VecFourRect;
			//SetRectToFoure(rectTemp,VecFourRect);

			if(pTempScreen->GetIsTwoSignal())
				SetRectToTwo(rectTemp,VecFourRect);
			else
				SetRectToFoure(rectTemp,VecFourRect);

			for(VEC_RECTF::iterator iter=VecFourRect.begin();iter!=VecFourRect.end();++iter)
			{
				RECTF rectFour=*iter;
				if(rectFour.Contains(tempPoint))
					rect=rectFour;
			}
		}
		break;
	case DRAGSTATUS_INTER:
		{
			RECTF rectInter=XCalculateScreenManage::GetInterRectByAllScreen(this);
			rect=rectInter;
		}
		break;
	case DRAGSTATUS_COPY:
		{
			//鼠标位置
			POINTF tempPoint;
			tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
			tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

			//首先鼠标所在屏幕
			XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);
			if(pTempScreen==NULL)
				return FALSE;

			VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
			int nSize=VecSignal.size();
			if(nSize==0)
				rect=rectNormal;
			else
			{
				XSignal* pSignal=VecSignal[nSize-1];

				if(pSignal==NULL)
					return FALSE;

				unsigned int nID=pSignal->GetSignalGroupID();
				RECTF rectTemp=XCalculateScreenManage::GetRectBySignal(this,nID);
				rect=rectTemp;
			}
		}
		break;
	default:
		break;
	}
	//********************************
	VEC_RECTF VecRectF;
	if(bIsUltra)
		SetRectToFoure(rect,VecRectF);
	else
		VecRectF.push_back(rect);
	//********************************
	//判断是否超过信号个数
	ResetSignalNumInScreen();
	for(VEC_RECTF::iterator iter=VecRectF.begin();iter!=VecRectF.end();++iter)
	{
		RECTF rectReal=*iter;
		//******************************
		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectReal,VecScreen);
		//******************************
		//判断是否超过四个信号
		if(!CanAddNewSignal(VecScreen))
		{
			//需要先找出需要删除的信号
			MAP_GROUPID MapDelSignalGroupID;
			MapDelSignalGroupID.clear();

			switch(m_nDragModel)
			{
			case DRAGMODEL_TIPMODEL:
				{
					m_pDelegate->MessageBoxFromKey(_T("384"),_T("该屏幕已超过最大信号个数，不能再添加信号！"),MB_OK);
					return FALSE;
				}
				break;
			case DRAGMODEL_UPMODEL:
				{
					//删除上面的
					GetDeleteSignalByCount(rectReal,DRAGMODEL_UPMODEL,MapDelSignalGroupID);
				}
				break;
			case DRAGMODEL_DOWNMODEL:
				{
					//删除下面的
					GetDeleteSignalByCount(rectReal,DRAGMODEL_DOWNMODEL,MapDelSignalGroupID);
				}
				break;
			default:
				break;
			}

			//删除信号
			for(MAP_GROUPID::iterator iter=MapDelSignalGroupID.begin();iter!=MapDelSignalGroupID.end();++iter)
			{
				unsigned int nGroupID=iter->first;
				DeleteSignalBySignalGroupID(nGroupID);
			}
		}
	}
	//*******************************
	//任何分辨率都按1920*1088计算
	int nResulationH=1920;
	int nResulationV=1088;
	//********************************
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//***********************
	int i=0;
	for(VEC_RECTF::iterator iter=VecRectF.begin();iter!=VecRectF.end();++iter)
	{
		RECTF rectReal=*iter;
		//******************************
		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectReal,VecScreen);
		//******************************
		if(VecScreen.size()<=0)
		{
			m_IsSendPocket=FALSE;
			return FALSE;
		}
			
		//***********************************************
		//信号ID
		unsigned int nPreviewID=VecPreviewID[i];
		nPreviewID&=0x7FFFFFFF;

		if(bIsUltra)
			nPreviewID|=0x80000000;
		//***********************************************
		//信号序号
		int nPreviewIndex=VecPreviewIndex[i];
		//***********************************************
		//4K信号RTSP地址
		CString szUltraRTSPAddr=_T("");

		if(VecRTSPAddr.size()!=0)
			szUltraRTSPAddr=VecRTSPAddr[i];

		//***********************************************
		UpdateSynTime();
		
		for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			int nScreenIndex=pScreen->GetIndex();
			//=======================================================
			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;
			//=======================================================
			if (!m_pDelegate->GetUserNodePower(pInfo->GetPreviewIndex(), nScreenIndex))
			{
				CString szNotice=m_pDelegate->GetNotice();

				if(szNotice!=_T(""))
					m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
				else
					m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

				m_IsSendPocket=FALSE;
				return FALSE;
			}
			
			//与每个屏幕所交区域
			RECTF rectSignal;
			RECTF::Intersect(rectSignal,rectReal,pScreen->GetRect());
			//=======================================================
			//所交区域占整个视频区域的
			float nResBeginX=(rectSignal.X-rectReal.X)*nResulationH/rectReal.Width;
			float nResBeginY=(rectSignal.Y-rectReal.Y)*nResulationV/rectReal.Height;
			float nTempResWidth=rectSignal.Width*nResulationH/rectReal.Width;
			float nTempResHight=rectSignal.Height*nResulationV/rectReal.Height; 

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//=======================================================
			XSignal* pSignal=pScreen->AddSignal(
				rectSignal,
				nLevel,
				nPreviewIndex, 
				szAnotherName,
				nPreviewID,
				nPreviewGroupID,
				pExpandInfo,
				bIsUltra);

			pSignal->SetIPAddr(szIP);
			pSignal->SetUseName(szUseName);
			pSignal->SetPassWd(szPassWd);

			//////////////////////////////////////////////////////////////////////////
			XMultiVideoWindowFrame* pFrame=NULL;
			if(bIsUltra)
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szUltraRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szUltraRTSPAddr);
				pSignal->SetRTSPAddr(szUltraRTSPAddr);
			}
			else
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
				pSignal->SetRTSPAddr(szRTSPAddr);
			}

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nPreviewIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nPreviewID);
			m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nPreviewGroupID);

			pSignal->SetPreviewFrame(pFrame);	
			//////////////////////////////////////////////////////////////////////////
			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectReal);
		}
		i++;
	}

	XSendDataScreenManage::AddSendDataOfFinash(this);
	//*****************************
	m_IsSendPocket=FALSE;
	SendAllData();
	//******************************
	return TRUE;
}

BOOL XScreenManage::DragMatrixInfo(CRect rc, XRTSPInfo* pInfo)
{
	BOOL bIsUltra=pInfo->GetIsUltra();
	if(bIsUltra)
	{
		m_pDelegate->MessageBoxFromKey(_T("708"),_T("矩阵不能添加4K信号！"),MB_OK);
		return FALSE;
	}

	unsigned int nSignalGroupID=pInfo->GetPreviewGroupID();
	//BOOL bIsUltra=TRUE;

	//局部放大偏移
	XExpandInfo* pExpandInfo=pInfo->GetExpandInfo();
	CString szAnotherName=pInfo->GetAnotherName();
	CString szRTSPAddr=pInfo->GetRTSPAddr();
	int nSignalIndex=pInfo->GetPreviewIndex();
	unsigned int nSignalID=pInfo->GetPreviewID();
	CString szIPAddr=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();

	//***********************
	//判断是否插入面板
	if(!IsHavePane(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("395"),_T("该输入没有插入面板！"),MB_OK);
		return FALSE;
	}
	//判断该输入是否有信号
	if(!IsHaveSignal(nSignalIndex))
	{
		m_pDelegate->MessageBoxFromKey(_T("394"),_T("该输入无信号！"),MB_OK);
		return FALSE;
	}

	//********************************
	CMultiviewerView* pView=GetView();
	pView->ScreenToClient(&rc);
	CRect rectView;
	pView->GetClientRect(&rectView);
	POINTF tempPointLT;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.TopLeft(),tempPointLT);
	POINTF tempPointRB;
	XCalculateScreenManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rc.BottomRight(),tempPointRB);

	POINTF tempPoint;
	tempPoint.X=(tempPointRB.X-tempPointLT.X)/2+tempPointLT.X;
	tempPoint.Y=(tempPointRB.Y-tempPointLT.Y)/2+tempPointLT.Y;

	XScreen* pTempScreen = XCalculateScreenManage::GetScreenByPoint(this, tempPoint);

	if(pTempScreen==NULL)
		return FALSE;

	RECTF rect=pTempScreen->GetRect();

	//删除原来信号
	VEC_UNINT VecGroupID;
	VEC_SIGNAL& VecSignal=pTempScreen->GetVecSignal();
	for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
	{
		XSignal* pSignal=*iter;
		unsigned int nGroupID=pSignal->GetSignalGroupID();
		VecGroupID.push_back(nGroupID);
	}
	//删除信号
	for(VEC_UNINT::iterator iter=VecGroupID.begin();iter!=VecGroupID.end();++iter)
	{
		unsigned int nGroupID=*iter;
		DeleteSignalBySignalGroupID(nGroupID);
	}

	//********************************
	//任何分辨率都转化为1920*1088
	int nResulationH=1920;
	int nResulationV=1088;
	//************************************
	//4KRTSP地址
	CString szUltraRTSPAddr=_T("");

	//信号ID
	nSignalID&=0x7FFFFFFF;
	//************************************
	UpdateSynTime();
	int nLevel=1;

	int nScreenIndex=pTempScreen->GetIndex();

	if (!m_pDelegate->GetUserNodePower(pInfo->GetPreviewIndex(), nScreenIndex))
	{
		CString szNotice=m_pDelegate->GetNotice();

		if(szNotice!=_T(""))
			m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
		else
			m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

		return FALSE;
	}

	//与每个屏幕所交区域
	RECTF rectSignal;
	RECTF::Intersect(rectSignal,rect,pTempScreen->GetRect());
	//=======================================================
	//视频区域
	float nResBeginX=nResBeginX=(rectSignal.X-rect.X)*nResulationH/rect.Width;
	float nResBeginY=nResBeginY=(rectSignal.Y-rect.Y)*nResulationV/rect.Height;
	float nTempResWidth=nTempResWidth=rectSignal.Width*nResulationH/rect.Width;
	float nTempResHight=nTempResHight=rectSignal.Height*nResulationV/rect.Height; 

	RECTF rectImage;
	rectImage.X=nResBeginX;
	rectImage.Y=nResBeginY;
	rectImage.Width=nTempResWidth;
	rectImage.Height=nTempResHight;
	//TRACE(_T("rectImageX=%f,rectImageY=%f,rectImageW=%f,rectImageH=%f\n"),rectImage.X,rectImage.Y,rectImage.Width,rectImage.Height);
	//=======================================================
	XSignal* pSignal=pTempScreen->AddSignal(
		rectSignal,
		nLevel,
		nSignalIndex, 
		szAnotherName,
		nSignalID,
		nSignalGroupID,
		pExpandInfo,
		bIsUltra);

	pSignal->SetIPAddr(szIPAddr);
	pSignal->SetUseName(szUseName);
	pSignal->SetPassWd(szPassWd);

	//TRACE(_T("rectSignalX=%f,rectSignalY=%f,rectSignalW=%f,rectSignalH=%f\n"),rectSignal.X,rectSignal.Y,rectSignal.Width,rectSignal.Height);

	//添加视频墙
	//////////////////////////////////////////////////////////////////////////
	XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(pTempScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
	m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
	pSignal->SetRTSPAddr(szRTSPAddr);

	m_pMultiVideoWindow->SetFrameIndex(pTempScreen->GetIndex(),pFrame,nSignalIndex);
	m_pMultiVideoWindow->SetFrameAnotherName(pTempScreen->GetIndex(),pFrame,szAnotherName);
	m_pMultiVideoWindow->SetFrameID(pTempScreen->GetIndex(),pFrame,nSignalID);
	m_pMultiVideoWindow->SetFrameGroupID(pTempScreen->GetIndex(),pFrame,nSignalGroupID);

	pSignal->SetPreviewFrame(pFrame);
	//////////////////////////////////////////////////////////////////////////
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	XSendDataScreenManage::AddSendDataOfMatrixSignal(this,pSignal,pTempScreen);
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//*****************************
	m_IsSendPocket=FALSE;
	SendAllData();

	return TRUE;
}

BOOL XScreenManage::DragInfo(CRect rc, XRTSPInfo* pInfo)
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			return DragSplicInfo(rc,pInfo);
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			return DragMatrixInfo(rc,pInfo);
		}
		break;
	default:
		break;
	}

	return TRUE;
}

//添加拖拽模式，用不到
//////////////////////////////////////////////////////////////////////////
BOOL XScreenManage::CanAddNewSignal(VEC_RECTF& VecRectF)
{
	for(VEC_RECTF::iterator iter=VecRectF.begin();iter!=VecRectF.end();++iter)
	{
		RECTF rectReal=*iter;
		//******************************
		VEC_SCREEN VecScreen;
		CalculateVecScreen(rectReal,VecScreen);

		//******************************
		//判断是否超过四个信号
		if(!CanAddNewSignal(VecScreen))
			return FALSE;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////

BOOL XScreenManage::CanAddNewSignal(VEC_SCREEN& VecScreen)
{
	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		int nNum=pScreen->GetAddSignalNumInScreen();
		int n=nNum;
		n+=1;
		pScreen->SetAddSignalNumInScreen(n);
		if(!pScreen->CanAddSignal())
			return FALSE;
	}

	return TRUE;
}

void XScreenManage::OperateOfTopSignal()
{
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//*******************
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		unsigned int nGroupID=m_RBtnSignalGroupID;
		pScreen->SetSignalTopByGroupID(nPaneIndex,nGroupID);
	}	
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}
void XScreenManage::OperateOfBottomSignal()
{
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//*******************
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		unsigned int nGroupID=m_RBtnSignalGroupID;
		pScreen->SetSignalBottom(nPaneIndex,nGroupID);
	}	
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}

void XScreenManage::OperateOfShiftUPSignal()
{
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//*******************
	XMultiVideoWindowFrame* pFrame=m_DragInfo.GetPreviewFrame();

	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		unsigned int nGroupID=m_RBtnSignalGroupID;
		pScreen->SetSignalShiftUp(nPaneIndex,nGroupID);
		//m_pMultiVideoWindow->SetFrameUp(pScreen->GetIndex(),pFrame);
		m_pMultiVideoWindow->SetFrameUpByGroupID(pScreen->GetIndex(),nGroupID);
	}	

	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}

void XScreenManage::OperateOfShiftDownSignal()
{	
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//*******************
	XMultiVideoWindowFrame* PFrame=m_DragInfo.GetPreviewFrame();

	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		unsigned int nGroupID=m_RBtnSignalGroupID;
		pScreen->SetSignalShiftDown(nPaneIndex,nGroupID);
		//m_pMultiVideoWindow->SetFrameDown(pScreen->GetIndex(),PFrame);
		m_pMultiVideoWindow->SetFrameDownByGroupID(pScreen->GetIndex(),nGroupID);
	}	
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}

BOOL XScreenManage::OperateOfCloseSignal()
{
	if (NULL!=m_TempScreen)
	{
		UpdateSynTime();
		int nIndex=m_RBtnIndex;
		if(nIndex!=0)
		{
			if (!m_pDelegate->GetUserNodePower(nIndex, m_TempScreen->GetIndex()))
			{
				CString szNotice=m_pDelegate->GetNotice();

				if(szNotice!=_T(""))
					m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
				else
					m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

				return FALSE;
			}

			unsigned int nGroupID=m_RBtnSignalGroupID;
			TRACE(_T("nGroupID=%d\n"),nGroupID);

			DeleteSignalBySignalGroupID(nGroupID);
			XSendDataScreenManage::AddSendDataOfFinash(this);

			return TRUE;
		}

		return FALSE;
	}
	
	return FALSE;

}

void XScreenManage::DeleteSignalBySignalGroupID(unsigned int nGroupID)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		pScreen->DeleteSignalBySignalGroupID(this,nPaneIndex,nGroupID);	
	}
}

void XScreenManage::DeleteSignalBySignalID(unsigned int nID)
{
	UpdateSynTime();
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;
		int nPaneIndex=pScreen->GetBoardIndex();
		pScreen->DeleteSignalBySignalID(this,nPaneIndex,nID);
	}
}

void XScreenManage::OperateOfDeleteAllSignal()
{
	UpdateSynTime();
	SetRTSPAddrCountReset();
	DeleteAllFrame();
	DeleteAllSignal();
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			XSendDataScreenManage::AddSendDataOfDeleteAllSignal(this);
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			XSendDataScreenManage::AddSendDataOfDeleteAllMatrixSignal(this);
		}
		break;
	default:
		break;
	}

	XSendDataScreenManage::AddSendDataOfFinash(this);
}

void XScreenManage::SetRTSPAddrCountReset()
{
	VEC_SCREEN& VecScreen=GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			CString szRTSPAddr=pSignal->GetRTSPAddr();
			m_pDelegate->SetRTSPAddrCountReset(szRTSPAddr);
		}
	}
}

void XScreenManage::DeleteAllSignal()
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
		(*iter)->ClearVecSignal();
}

void XScreenManage::DeleteAllFrame()
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			m_pMultiVideoWindow->DeleteFrame(pScreen->GetIndex(),pSignal->GetPreviewFrame());
		}
	}
}

void XScreenManage::OperateOfExpandSignal()
{
	unsigned int nSignalID=m_LBDSignalID;
	unsigned int nSignalGroupID=m_LBDSignalGroupID;
	BOOL bIsUltra=m_DragInfo.GetIsUltra();
	XExpandInfo* pExpandInfo=m_DragInfo.GetExpandInfo();
	CString szRTSPAddr=m_DragInfo.GetRTSPAddr();
	CString szAnotherName=m_DragInfo.GetAnotherName();
	CString szIPAddr=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();

	int nResulationH=1920;
	int nResulationV=1088;

	RECTF rect=XCalculateScreenManage::GetRectBySignal(this,nSignalGroupID);
	//*******************
	VEC_UNINT VecSignalID=m_DragInfo.GetVecExpandSignalID();
	HYVEC_NUM VecSignalIndex=m_DragInfo.GetVecExpandSignalIndex();
	VEC_CSTRING& VecRTSPAddr=m_DragInfo.GetVecRTSPAddr();

	if(bIsUltra)
	{
		if((VecSignalID.size()!=4)||(VecSignalIndex.size()!=4))
			return;
	}

	//*******************
	//删除原来信号
	DeleteSignalBySignalGroupID(nSignalGroupID);
	//*******************
	VEC_SCREEN VecScreen;
	CalculateVecScreen(rect,VecScreen);
	RECTF InterRect=XCalculateScreenManage::GetRectByVecScreen(VecScreen);

	//*******************
	VEC_RECTF VecExpandRectF;
	if(bIsUltra)
		SetRectToFoure(InterRect,VecExpandRectF);
	else
		VecExpandRectF.push_back(InterRect);

	int n=VecExpandRectF.size();

	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//*******************
	int i=0;
	for(VEC_RECTF::iterator iter=VecExpandRectF.begin();iter!=VecExpandRectF.end();++iter)
	{
		RECTF newRect=*iter;
		//******************************
		VEC_SCREEN NewVecScreen;
		CalculateVecScreen(newRect,NewVecScreen);
		//******************************
		int n=NewVecScreen.size();
		////******************************
		//信号ID
		unsigned int nSignalID=VecSignalID[i];
		//信号序号
		int nSignalIndex=VecSignalIndex[i];
		CString szUltraRTSPAddr=VecRTSPAddr[i];
		//******************************
		UpdateSynTime();

		for(VEC_SCREEN::iterator iter=NewVecScreen.begin();iter!=NewVecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;

			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;
			
			RECTF rectSignal;
			RECTF::Intersect(rectSignal,newRect,pScreen->GetRect());
			//**********************************************************
			//所交区域占整个视频区域的
			float nResBeginX=(rectSignal.X-newRect.X)*nResulationH/newRect.Width;
			float nResBeginY=(rectSignal.Y-newRect.Y)*nResulationV/newRect.Height;
			float nTempResWidth=rectSignal.Width*nResulationH/newRect.Width;
			float nTempResHight=rectSignal.Height*nResulationV/newRect.Height;

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//**********************************************************
			XSignal* pSignal=pScreen->AddSignal(
				rectSignal,
				nLevel,
				nSignalIndex, 
				szAnotherName,
				nSignalID,
				nSignalGroupID,
				pExpandInfo,
				bIsUltra);
			
			pSignal->SetIPAddr(szIPAddr);
			pSignal->SetUseName(szUseName);
			pSignal->SetPassWd(szPassWd);
			//////////////////////////////////////////////////////////////////////////
			XMultiVideoWindowFrame* pFrame=NULL;

			if(bIsUltra)
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szUltraRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szUltraRTSPAddr);
				pSignal->SetRTSPAddr(szUltraRTSPAddr);
			}
			else
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
				pSignal->SetRTSPAddr(szRTSPAddr);
			}

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nSignalIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nSignalID);
			m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nSignalGroupID);

			pSignal->SetPreviewFrame(pFrame);
			//////////////////////////////////////////////////////////////////////////
			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,newRect);
		}
		i++;
	}

	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}

void XScreenManage::OperateOfChangeInput()
{
	BOOL bResIsUltra=m_DragInfo.GetIsUltra();
	HYVEC_NUM& VecSignalIndex=m_DragInfo.GetVecExpandSignalIndex();
	int nResInputIndex=VecSignalIndex[0];
	unsigned int nSignalGroupID=m_RBtnSignalGroupID;
	RECTF rect=XCalculateScreenManage::GetRectBySignal(this,nSignalGroupID);
	VEC_INPUTSIGNAL& VecInput=GetVecInputSignal();

	XChangeInput dlg;
	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	dlg.SetIsUltra(bResIsUltra);
	dlg.SetInputIndex(nResInputIndex);

	if(IDOK==dlg.DoModal())
	{
		int nSelectIndex=dlg.GetComboIndex();
		if(nResInputIndex==nSelectIndex)
			return;

		//设置输入源是否为4k
		JudgetInputIsultra(nSelectIndex);
		XInputSignal* pInputSignal=XCalculateScreenManage::GetSignalByIndex(this,nSelectIndex);

		if(pInputSignal==NULL)
			return;

		//删除原来信号	
		DeleteSignalBySignalGroupID(nSignalGroupID);
		m_pMultiVideoWindow->DeleteFrame(nResInputIndex,m_DragInfo.GetPreviewFrame());

		m_IsSendPocket=TRUE;
		ClearVecSendData();
		//******************
		ChangeInput(pInputSignal,rect,bResIsUltra);
	}
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//**************
	m_IsSendPocket=FALSE;
	SendAllData();
	//***************
}

void XScreenManage::ChangeInput(XInputSignal*& pInputSignal,RECTF& rect,BOOL bResIsUltra)
{
	RECTF newRectF=rect;
	//*************************
	//信号组ID（不变）
	unsigned int nInputGroupID=m_RBtnSignalGroupID;

	//原来信号ID集合
	VEC_UNINT& VecInputID=m_DragInfo.GetVecExpandSignalID();

	//原来信号序号集合
	HYVEC_NUM& VecSignalIndex=m_DragInfo.GetVecExpandSignalIndex();

	//原来信号
	CString szIP=m_DragInfo.GetIPAddr();
	CString szUseName=m_DragInfo.GetUseName();
	CString szPassWd=m_DragInfo.GetPassWd();
	CString szRTSP=m_DragInfo.GetRTSPAddr();

	//TRACE(_T("RTSP=%s\n"),szRTSP);
	VEC_CSTRING& VecRTSPAddr=m_DragInfo.GetVecRTSPAddr();
	//////////////////////////////////////////////////////////////////////////
	//当前信号别名
	CString szAnotherName=pInputSignal->GetAnotherName();
	//当前信号
	CString szCurIP=pInputSignal->GetIPAddr();
	CString szCurUseName=pInputSignal->GetUseName();
	CString szCurPassWd=pInputSignal->GetPassWd();
	CString szCurRTSPAddr=pInputSignal->GetRTSPAddr();

	VEC_CSTRING VecCurRTSPAddr;
	CreateRTSPAddr(szCurIP,szCurUseName,szCurPassWd,VecCurRTSPAddr);

	//局部放大
	XInputSignalExpand* pExpand=pInputSignal->GetDefaultExpand();
	XExpandInfo* pExpandInfo=pExpand->GetExpandInfo();

	//原来信号分辨率
	int nResResulationH=1920;
	int nResResulationV=1088;

	//新信号是否为4K
	BOOL bIsUltra=pInputSignal->GetIsUltra();

	VEC_RECTF VecChangeInputRectF;
	if(bIsUltra)
		SetRectToFoure(newRectF,VecChangeInputRectF);
	else
		VecChangeInputRectF.push_back(newRectF);
	//*************************
	//输入信号分辨率
	int nResulationH=1920;
	int nResulationV=1088;
	//*************************
	//判断是否超过信号个数
	ResetSignalNumInScreen();
	if(!CanAddNewSignal(VecChangeInputRectF))
	{
		m_pDelegate->MessageBoxFromKey(_T("384"),_T("该屏幕已超过最大信号个数，不能再添加信号！"),MB_OK);

		//********************************
		//如果不能切换4K,要换回原来的窗口
		int nIndex=VecSignalIndex[0];
		unsigned int nID=VecInputID[0];

		//区域所占屏幕个数
		VEC_SCREEN VecScreen;
		for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			RECTF rectScreen=pScreen->GetRect();
			if(rectScreen.Intersect(newRectF))
				VecScreen.push_back(pScreen);
		}

		UpdateSynTime();

		for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;

			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;

			RECTF rectSignal;
			RECTF::Intersect(rectSignal,newRectF,pScreen->GetRect());
			//****************************************************
			//所交区域占整个视频区域的
			float nResBeginX=(rectSignal.X-newRectF.X)*nResResulationH/newRectF.Width;
			float nResBeginY=(rectSignal.Y-newRectF.Y)*nResResulationV/newRectF.Height;
			float nTempResWidth=rectSignal.Width*nResResulationH/newRectF.Width;
			float nTempResHight=rectSignal.Height*nResResulationV/newRectF.Height;
			float nResEndX=nResBeginX+nTempResWidth-1;
			float nResEndY=nResBeginY+nTempResHight-1;

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//****************************************************
			XSignal* pSignal=pScreen->AddSignal(
				rectSignal,
				nLevel,
				nIndex, 
				szAnotherName,
				nID,
				nInputGroupID,
				pExpandInfo,
				bResIsUltra);
			//pInputSignal->GetRTSPAddr()
			pSignal->SetIPAddr(szIP);
			pSignal->SetUseName(szUseName);
			pSignal->SetPassWd(szPassWd);

			//****************************************************
			XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSP,rectSignal,rectImage);

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bResIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nID);
			m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nInputGroupID);

			pSignal->SetPreviewFrame(pFrame);
			pSignal->SetRTSPAddr(szRTSP);	
			m_pDelegate->SetRTSPAddrCountPlus(szRTSP);
			//****************************************************
			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,newRectF);
		}

		m_IsSendPocket=FALSE;
		SendAllData();

		return;
	}

	//*************************
	//输入序号（根据切换信号得出）
	int nInputIndex=pInputSignal->GetInputIndex();
	HYVEC_NUM VecInputIndex;
	for(int i=0;i<4;i++)
	{
		VecInputIndex.push_back(nInputIndex);
		nInputIndex++;
	}

	//*************************
	//新分配信号ID集合
	VEC_UNINT& VecNewInputID=m_DragInfo.GetVecChangeInputID();
	//*************************
	int i=0;
	for(VEC_RECTF::iterator iter=VecChangeInputRectF.begin();iter!=VecChangeInputRectF.end();++iter)
	{
		RECTF rectNow=*iter;
		//******************************
		VEC_SCREEN NewVecScreen;
		CalculateVecScreen(rectNow,NewVecScreen);
		//******************************
		if(NewVecScreen.size()<=0)
		{
			m_IsSendPocket=FALSE;
			return;
		}
			
		//******************************
		//信号ID
		unsigned int nSignalID=VecNewInputID[i];
		nSignalID&=0x7FFFFFFF;

		if(bIsUltra)
			nSignalID|=0x80000000;
		//******************************
		//信号序号
		int nSignalIndex=VecInputIndex[i];
		//RTSP地址
		CString szRTSPAddr=VecCurRTSPAddr[i];
		//******************************
		UpdateSynTime();
		for(VEC_SCREEN::iterator iter=NewVecScreen.begin();iter!=NewVecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;

			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			int nLevel=VecSignal.size()+1;

			RECTF rectSignal;
			RECTF::Intersect(rectSignal,rectNow,pScreen->GetRect());
			//**********************************************************
			//所交区域占整个视频区域的
			float nResBeginX=(rectSignal.X-rectNow.X)*nResulationH/rectNow.Width;
			float nResBeginY=(rectSignal.Y-rectNow.Y)*nResulationV/rectNow.Height;
			float nTempResWidth=rectSignal.Width*nResulationH/rectNow.Width;
			float nTempResHight=rectSignal.Height*nResulationV/rectNow.Height;
			//float nResEndX=nResBeginX+nTempResWidth-1;
			//float nResEndY=nResBeginY+nTempResHight-1;

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//**********************************************************
			XSignal* pSignal=pScreen->AddSignal(
				rectSignal,
				nLevel,
				nSignalIndex, 
				szAnotherName,
				nSignalID,
				nInputGroupID,
				pExpandInfo,
				bIsUltra);

			pSignal->SetIPAddr(szCurIP);
			pSignal->SetUseName(szCurUseName);
			pSignal->SetPassWd(szCurPassWd);

			//TRACE(_T("nIndex=%d,szIP=%s,szUseName=%s,szPasswd=%s\n"),nSignalIndex,szCurIP,szCurUseName,szCurPassWd);
			//*******************************************
			XMultiVideoWindowFrame* pFrame=NULL;

			if(bIsUltra)
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
				pSignal->SetRTSPAddr(szRTSPAddr);
			}
			else
			{
				pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szCurRTSPAddr,rectSignal,rectImage);
				m_pDelegate->SetRTSPAddrCountPlus(szCurRTSPAddr);
				pSignal->SetRTSPAddr(szCurRTSPAddr);
			}

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nSignalIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nSignalID);
			m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nInputGroupID);

			pSignal->SetPreviewFrame(pFrame);
			//*******************************************

			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectNow);
		}
		i++;
	}
}

void XScreenManage::JudgetInputIsultra(int nInputIndex)
{
	m_pDelegate->JudgetInputIsultra(nInputIndex);
}

void XScreenManage::SetRectToFoure(RECTF rect,VEC_RECTF& VecRect)
{
	RECTF rect1(rect.X,rect.Y,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect1);

	RECTF rect2(rect.X+rect.Width/2,rect.Y,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect2);	

	RECTF rect3(rect.X,rect.Y+rect.Height/2,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect3);

	RECTF rect4(rect.X+rect.Width/2,rect.Y+rect.Height/2,rect.Width/2,rect.Height/2);
	VecRect.push_back(rect4);
}

void XScreenManage::SetRectToTwo(RECTF rect,VEC_RECTF& VecRect)
{
	RECTF rect1(rect.X,rect.Y,rect.Width,rect.Height/2);
	VecRect.push_back(rect1);

	RECTF rect3(rect.X,rect.Y+rect.Height/2,rect.Width,rect.Height/2);
	VecRect.push_back(rect3);
}

void XScreenManage::CalculateVecScreen(RECTF rect,VEC_SCREEN& VecScreen)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		RECTF rectf=pScreen->GetRect();
		if(rectf.Intersect(rect))
			VecScreen.push_back(pScreen);
	}
}

void XScreenManage::OperateOfScreenResulation()
{
	XResolution dlg;

	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	dlg.SetScreen(m_TempScreen);
	if(dlg.DoModal()==IDOK)
		XSendDataScreenManage::SendDataOfSetScreenResualtion(this,m_TempScreen);
}

void XScreenManage::OperateOfSetRowDpi()
{
	if(NULL==m_TempScreen)
		return;
	//先保存所有行列的视图宽高

	XSetRowResoluation dlg;

	dlg.SetScreen(m_TempScreen);
	dlg.SetScreenManage(this);
	dlg.SetDelegate(this);
	if(dlg.DoModal()==IDOK)
	{
		//根据分辨率，设置屏幕区域
		ResetScreenArrayByRow();
		ResetViewSize();

		XSendDataScreenManage::AddSendDataOfResulationFront(this);
		XSendDataScreenManage::SendDataOfSetScreenRowResualtion(this);
		ResetSignalByNewResulation();
		XSendDataScreenManage::AddSendDataOfFinash(this);
	}
		
}

void XScreenManage::OperateOfSetColDpi()
{
	if(NULL==m_TempScreen)
		return;
	//先保存所有行列的视图宽高

	XSetColResoluation dlg;

	dlg.SetScreen(m_TempScreen);
	dlg.SetScreenManage(this);
	dlg.SetDelegate(this);
	if(dlg.DoModal()==IDOK)
	{
		//根据分辨率，设置屏幕区域
		ResetScreenArrayByCol();
		ResetViewSize();

		XSendDataScreenManage::AddSendDataOfResulationFront(this);
		XSendDataScreenManage::SendDataOfSetScreenRowResualtion(this);
		ResetSignalByNewResulation();
		XSendDataScreenManage::AddSendDataOfFinash(this);
	}
}

void XScreenManage::ResetScreenArrayByRow()
{
	XAllResulationInfo* pInfo=GetAllResulationInfo();//设置整体分辨率时设置
	int nScreenRow=m_TempScreen->GetScreenRow();

	//底部剩余分辨率
	int nNonstandV=pInfo->GetBottomCut();

	int nTempResulationH=0;
	int nTempResulationV=0;

	float top=0.0f;
	float left=0.0f;
	int nIndex=GetBeginIndex();
	for(int i=0;i<m_nScreenCountV;i++)
	{
		left=0.0f;
		//***************************
		int nRow=i+1;
		TRACE(_T("nCol=%d\n"),nRow);

		int nHight=0;
		int nResoluationV=0;
		MAP_ROWINFO::iterator iterRow=m_MapRowInfo.find(nRow);
		if(iterRow!=m_MapRowInfo.end())
		{
			XScreenRowInfo* pRowInfo=iterRow->second;

			nHight=pRowInfo->GetScreenHeight();
			nResoluationV=pRowInfo->GetResoluationV();
		}

		if(nRow==nScreenRow)
		{
			nTempResulationV=nHight*nNonstandV/nResoluationV;
		}
		else
		{
			nTempResulationV=nHight;
		}
		TRACE(_T("nTempResulationV=%d\n"),nTempResulationV);

		//***************************
		for(int j=0;j<m_nScreenCountH;j++)
		{	
			//重新计算
			int nCol=j+1;
			TRACE(_T("nRow=%d\n"),nCol);

			float nWidth=0;
			int nResoluationH=0;

			MAP_COLINFO::iterator iter=m_MapColInfo.find(nCol);
			if(iter!=m_MapColInfo.end())
			{
				XScreenColInfo* pCol=iter->second;

				nWidth=pCol->GetScreenWidth();
				nResoluationH=pCol->GetResoluationH();
			}

			nTempResulationH=nWidth;
			//***************************
			RECTF screenRect(left,top,(Gdiplus::REAL)nTempResulationH,(Gdiplus::REAL)nTempResulationV);

			int nScreenIndex=i*m_nScreenCountH+(j+nIndex);
			XScreen* pScreen=GetScreenByIndex(nScreenIndex);
			if(pScreen==NULL)
				return;

			int nBoardIndex=pScreen->GetBoardIndex();
			int nPaneIndex=pScreen->GetNumOfTwoScreen();
			BOOL bIsTwoSignal=pScreen->GetIsTwoSignal();
			pScreen->SetRect(screenRect);
			//**************************************
			XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(nScreenIndex,nBoardIndex,screenRect,nPaneIndex,bIsTwoSignal);
			CString szText=SetText(pScreen);
			m_pMultiVideoWindow->SetFramesText(nScreenIndex,szText,12);

			//m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
			//m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
			//m_pMultiVideoWindow->SetFramesResulationH(nDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesResulationV(nDefaultResulationV);
			//m_pMultiVideoWindow->SetFramesRightResulationH(nRightDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesBottomResulationV(nBottomDefaultResulationV);
			//**************************************
			left+=nTempResulationH;
		}
		top+=nTempResulationV;
	}

	SetScreenWidthAndHight();
	m_pMultiVideoWindow->SetMapRowInfo(m_MapRowInfo);
	m_pMultiVideoWindow->SetMapColInfo(m_MapColInfo);
}

void XScreenManage::ResetScreenArrayByCol()
{
	XAllResulationInfo* pInfo=GetAllResulationInfo();//设置整体分辨率时设置
	int nScreenCol=m_TempScreen->GetScreenCol();

	//底部剩余分辨率
	int nNonstandH=pInfo->GetRightCut();

	int nTempResulationH=0;
	int nTempResulationV=0;

	float top=0.0f;
	float left=0.0f;
	int nIndex=GetBeginIndex();
	for(int i=0;i<m_nScreenCountV;i++)
	{
		left=0.0f;
		//***************************
		//重新计算
		int nRow=i+1;
		TRACE(_T("nCol=%d\n"),nRow);

		int nHight=0;
		int nResoluationV=0;
		MAP_ROWINFO::iterator iterRow=m_MapRowInfo.find(nRow);
		if(iterRow!=m_MapRowInfo.end())
		{
			XScreenRowInfo* pRowInfo=iterRow->second;

			nHight=pRowInfo->GetScreenHeight();
			nResoluationV=pRowInfo->GetResoluationV();
		}

		nTempResulationV=nHight;
		TRACE(_T("nTempResulationV=%d\n"),nTempResulationV);

		//***************************
		for(int j=0;j<m_nScreenCountH;j++)
		{	
			//原来的
			int nCol=j+1;
			TRACE(_T("nRow=%d\n"),nCol);

			float nWidth=0;
			int nResoluationH=0;

			MAP_COLINFO::iterator iter=m_MapColInfo.find(nCol);
			if(iter!=m_MapColInfo.end())
			{
				XScreenColInfo* pCol=iter->second;

				nWidth=pCol->GetScreenWidth();
				nResoluationH=pCol->GetResoluationH();
			}

			if(nCol==nScreenCol)
			{
				nTempResulationH=nWidth*nNonstandH/nResoluationH;
			}
			else
			{
				nTempResulationH=nWidth;
			}

			//***************************
			RECTF screenRect(left,top,(Gdiplus::REAL)nTempResulationH,(Gdiplus::REAL)nTempResulationV);

			int nScreenIndex=i*m_nScreenCountH+(j+nIndex);
			XScreen* pScreen=GetScreenByIndex(nScreenIndex);
			if(pScreen==NULL)
				return;

			int nBoardIndex=pScreen->GetBoardIndex();
			int nPaneIndex=pScreen->GetNumOfTwoScreen();
			BOOL bIsTwoSignal=pScreen->GetIsTwoSignal();
			pScreen->SetRect(screenRect);
			//**************************************
			XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(nScreenIndex,nBoardIndex,screenRect,nPaneIndex,bIsTwoSignal);
			CString szText=SetText(pScreen);
			m_pMultiVideoWindow->SetFramesText(nScreenIndex,szText,12);

			//m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
			//m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
			//m_pMultiVideoWindow->SetFramesResulationH(nDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesResulationV(nDefaultResulationV);
			//m_pMultiVideoWindow->SetFramesRightResulationH(nRightDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesBottomResulationV(nBottomDefaultResulationV);
			//**************************************
			left+=nTempResulationH;
		}
		top+=nTempResulationV;
	}

	SetScreenWidthAndHight();
	m_pMultiVideoWindow->SetMapRowInfo(m_MapRowInfo);
	m_pMultiVideoWindow->SetMapColInfo(m_MapColInfo);
}

void XScreenManage::OperateOfSetScreenResulation()
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			//先拿到没改之前的分辨率(先忽略不规则)
			if(m_VecScreen.size()!=0)
			{
				m_nPreResolutionH=m_VecScreen[0]->GetScreenHdpi();
				m_nPreResolutionV=m_VecScreen[0]->GetScreenVdpi();
			}
			else
			{
				m_nPreResolutionH=1920;
				m_nPreResolutionV=1080;
			}
			//////////////////////////////////////////////////////////////////////////
			XAllResulution dlg;
			dlg.SetDelegate(this);
			dlg.SetScreenManage(this);
			if(dlg.DoModal()==IDOK)
			{
				//根据分辨率，设置屏幕区域
				ResetScreenArray();
				ResetViewSize();
				//////////////////////////////////////////////////////////////////////////
				XSendDataScreenManage::AddSendDataOfResulationFront(this);
				XSendDataScreenManage::SendDataOfSetAllScreenResualtion(this);
				ResetSignalByNewResulation();
				XSendDataScreenManage::AddSendDataOfFinash(this);
			}
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			XMatrixAllResolution dlg;
			dlg.SetDelegate(this);
			dlg.SetScreenManage(this);
			dlg.SetScreen(m_TempScreen);

			if(IDOK==dlg.DoModal())
				XSendDataScreenManage::SendDataOfSetMatrixAllScreenResualtion(this);
		}
		break;
	default:
		break;
	}
}

void XScreenManage::ResetSignalByNewResulation()
{
	//先求出每个信号的整体区域
	for(auto iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		RECTF rectScreen=pScreen->GetRect();

		int nResolutionH=pScreen->GetScreenHdpi();
		int nResolutionV=pScreen->GetScreenVdpi();

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(auto iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;

			RECTF rect=pSignal->GetRect();
			//转换成更改后分辨率区域
			//RECTF rectSignal(0,0,0,0);

			rect.X=(Gdiplus::REAL)rect.X*nResolutionH/m_nPreResolutionH;
			rect.Y=(Gdiplus::REAL)rect.Y*nResolutionV/m_nPreResolutionV;
			rect.Width=(Gdiplus::REAL)rect.Width*nResolutionH/m_nPreResolutionH;
			rect.Height=(Gdiplus::REAL)rect.Height*nResolutionV/m_nPreResolutionV;

			//rectSignal.X=rect.X;
			//rectSignal.Y=rect.Y;

			//rectSignal.Width=160;
			//rectSignal.Height=(Gdiplus::REAL)rectSignal.Width*rect.Height/rect.Width;


			pSignal->SetRect(rect);

			XMultiVideoWindowFrame* pOldFrame=pSignal->GetPreviewFrame();
			m_pMultiVideoWindow->SetFrame(pScreen->GetIndex(),pOldFrame,rect);


			//RECTF InteRect=XCalculateScreenManage::GetRectBySignal(this,pSignal->GetSignalGroupID());

			//InteRect.X=(Gdiplus::REAL)InteRect.X*nResolutionH/m_nPreResolutionH;
			//InteRect.Y=(Gdiplus::REAL)InteRect.Y*nResolutionV/m_nPreResolutionV;
			//InteRect.Width=(Gdiplus::REAL)InteRect.Width*nResolutionH/m_nPreResolutionH;
			//InteRect.Height=(Gdiplus::REAL)InteRect.Height*nResolutionV/m_nPreResolutionV;
			//
		}
	}

	for(auto iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(auto iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;

			RECTF InteRect=XCalculateScreenManage::GetRectBySignal(this,pSignal->GetSignalGroupID());

			pSignal->SetInteRect(InteRect);	

			XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,pSignal->GetInteRect());
		}
	}
}

void XScreenManage::ResetScreenArray()
{
	//////////////////////////////////////////////////////////////////////////
	XAllResulationInfo* pInfo=GetAllResulationInfo();

	int nResulationH=pInfo->GetResolutionH();
	int nResulationV=pInfo->GetResolutionV();

	//右侧底部剩余分辨率
	int nRightRemaind=pInfo->GetRightCut();
	int nBottomRemaind=pInfo->GetBottomCut();

	//获取屏幕比例
	int nDefaultResulationH=0;
	int nDefaultResulationV=0;

	int nTempH=200;
	int nTempV=nTempH*nResulationV/nResulationH;

	//int nTempH=nResulationH*200/1920;
	//int nTempV=nResulationV*112/1080;
	
	//if(nTempV>112)
	//{
	//	nTempV=112;
	//	nTempH=nTempV*nResulationH/nResulationV;	
	//}

	nDefaultResulationH=nTempH;
	nDefaultResulationV=nTempV;

	//右侧不规则屏幕比例
	int nRightDefaultResulationH=nDefaultResulationH*nRightRemaind/nResulationH;
	int nBottomDefaultResulationV=nDefaultResulationV*nBottomRemaind/nResulationV;

	SetResolutionH(nDefaultResulationH);
	SetResolutionV(nDefaultResulationV);
	SetRightResulationH(nRightDefaultResulationH);
	SetBottomResulationV(nBottomDefaultResulationV);

	int nTempResulationH=0;
	int nTempResulationV=0;

	float top=0.0f;
	float left=0.0f;
	int nIndex=GetBeginIndex();
	for(int i=0;i<m_nScreenCountV;i++)
	{
		left=0.0f;
		//***************************
		if(i==m_nScreenCountV-1)
			nTempResulationV=nBottomDefaultResulationV;
		else
			nTempResulationV=nDefaultResulationV;
		//***************************
		for(int j=0;j<m_nScreenCountH;j++)
		{	
			//***************************
			if(j==m_nScreenCountH-1)
				nTempResulationH=nRightDefaultResulationH;
			else
				nTempResulationH=nDefaultResulationH;
			//***************************
			RECTF screenRect(left,top,(Gdiplus::REAL)nTempResulationH,(Gdiplus::REAL)nTempResulationV);

			int nScreenIndex=i*m_nScreenCountH+(j+nIndex);
			XScreen* pScreen=GetScreenByIndex(nScreenIndex);
			if(pScreen==NULL)
				return;

			int nBoardIndex=pScreen->GetBoardIndex();
			int nPaneIndex=pScreen->GetNumOfTwoScreen();
			BOOL bIsTwoSignal=pScreen->GetIsTwoSignal();
			pScreen->SetRect(screenRect);
			//**************************************
			XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(nScreenIndex,nBoardIndex,screenRect,nPaneIndex,bIsTwoSignal);
			CString szText=SetText(pScreen);
			m_pMultiVideoWindow->SetFramesText(nScreenIndex,szText,12);


			//m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
			//m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
			//m_pMultiVideoWindow->SetFramesResulationH(nDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesResulationV(nDefaultResulationV);
			//m_pMultiVideoWindow->SetFramesRightResulationH(nRightDefaultResulationH);
			//m_pMultiVideoWindow->SetFramesBottomResulationV(nBottomDefaultResulationV);
			//**************************************
			left+=nTempResulationH;
		}
		top+=nTempResulationV;
	}
	//获取屏幕行列宽高，分辨率

	SetScreenWidthAndHight();
	m_pMultiVideoWindow->SetMapRowInfo(m_MapRowInfo);
	m_pMultiVideoWindow->SetMapColInfo(m_MapColInfo);
}

void XScreenManage::SetScreenWidthAndHight()
{
	ClearColInfo();
	ClearRowInfo();

	//获取每块屏幕宽、高、水平以及垂直分辨率
	for(auto iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		RECTF rect=pScreen->GetRect();
		int nScreenRow=pScreen->GetScreenRow();
		int nScreenCol=pScreen->GetScreenCol();

		int nResoluationH=pScreen->GetScreenHdpi();
		int nResoluationV=pScreen->GetScreenVdpi();

		XScreenRowInfo* pRowInfo=NULL;
		MAP_ROWINFO::iterator iterRow=m_MapRowInfo.find(nScreenRow);
		if(iterRow==m_MapRowInfo.end())
		{
			pRowInfo=new XScreenRowInfo;
			pRowInfo->SetScreenHeight(rect.Height);
			pRowInfo->SetResoluationV(nResoluationV);

			m_MapRowInfo.insert(std::pair<int,XScreenRowInfo*>(nScreenRow,pRowInfo));
		}
		else
		{
			pRowInfo=iterRow->second;
			pRowInfo->SetScreenHeight(rect.Height);
			pRowInfo->SetResoluationV(nResoluationV);
		}
		////////////////////////////////////////////////////////////////////////////
		XScreenColInfo* pInfo=NULL;
		MAP_COLINFO::iterator iterCol=m_MapColInfo.find(nScreenCol);
		if(iterCol==m_MapColInfo.end())
		{
			pInfo=new XScreenColInfo;
			pInfo->SetResoluationH(nResoluationH);
			pInfo->SetScreenWidth(rect.Width);

			m_MapColInfo.insert(std::pair<int,XScreenColInfo*>(nScreenCol,pInfo));
		}
		else
		{
			pInfo=iterCol->second;
			pInfo->SetResoluationH(nResoluationH);
			pInfo->SetScreenWidth(rect.Width);
		}
	}
}

void XScreenManage::OperateOfScreenAttribute()
{
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		{
			XScreenAttributesDlg dlg;
			dlg.SetDelegate(this);
			dlg.SetScreenManage(this);
			dlg.SetScreen(m_TempScreen);
			dlg.DoModal();
		}
		break;
	case SCREENMODEL_MATRIX:
		{
			XScreenMatrixAttributesDlg dlg;
			dlg.SetDelegate(this);
			dlg.SetScreenManage(this);
			dlg.SetScreen(m_TempScreen);
			dlg.DoModal();
		}
		break;
	default:
		break;
	}
}

void XScreenManage::OperateOfSetScreenResulationByMatrix()
{
	XMatrixResolution dlg;
	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	dlg.SetScreen(m_TempScreen);
	if(IDOK==dlg.DoModal())
		XSendDataScreenManage::SendDataOfSetMatrixScreenResualtion(this,m_TempScreen);
}

void XScreenManage::UpdateSynTime()
{
	m_SynTime=GetTickCount();
}

XScreen* XScreenManage::GetScreen(int n)
{
	for (VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();iter++)
	{
		XScreen* pScreen = *iter;
		if (pScreen->GetIndex()==n)
			return pScreen;
	}
	return NULL;
}

void XScreenManage::ResetDataByScreenCountChange()
{
	m_bIsMenuSet=FALSE;
	m_pMultiVideoWindow->ClearVecFrames();
	//DeleteAllFrame();
	m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
	m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);

	ClearVecScreen();
	InitVecScreen();
	ResetViewSize();
	//m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);
}

void XScreenManage::ResetDataBySceneScreenCountChange()
{
	m_bIsMenuSet=TRUE;
	m_pMultiVideoWindow->ClearVecFrames();
	m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
	m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
	ClearVecScreen();
	InitSceneVecScreen();
	ResetViewSize();
	//m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);
}

void XScreenManage::ResetDataBySceneInputCountChange()
{
	m_pDelegate->ResetDataBySceneInputCountChange();
}

int XScreenManage::GetFramesCountH()
{
	return m_nScreenCountH;
}

int XScreenManage::GetFramesCountV()
{
	return m_nScreenCountV;
}

int XScreenManage::GetFramesResulationH()
{
	return m_nResolutionH;
}

int XScreenManage::GetFramesResulationV()
{
	return m_nResolutionV;
}

int XScreenManage::GetFramesRightResulationH()
{
	return m_nRightResulationH;
}

int XScreenManage::GetFramesBottomResulationV()
{
	return m_nBottomResulationV;
}

void XScreenManage::SetRightResulationH(int n)
{
	m_nRightResulationH=n;
}

int XScreenManage::GetRightResulationH()
{
	return m_nRightResulationH;
}

void XScreenManage::SetBottomResulationV(int n)
{
	m_nBottomResulationV=n;
}

int XScreenManage::GetBottomResulationV()
{
	return m_nBottomResulationV;
}

int XScreenManage::GetInputCount()
{
	return m_pDelegate->GetInputCount();
}

void XScreenManage::SetInputCount(int n)
{
	m_pDelegate->SetInputCount(n);
}

int XScreenManage::GetOutputCount()
{
	return m_nScreenCountH*m_nScreenCountV;
}

BOOL XScreenManage::GetISViewButtonDown()
{
	return m_ISViewButtonDown;
}

void XScreenManage::SetViewName(CString szName)
{
	m_ViewName=szName;
}

CString XScreenManage::GetViewName()
{
	return m_ViewName;
}

CMultiviewerView* XScreenManage::GetView()
{
	return m_View;
}

void XScreenManage::SetView(CMultiviewerView* pView)
{
	m_View=pView;
}

void XScreenManage::OperateOfGetScreenParamater()
{
	XSendDataScreenManage::AddSendDataOfGetScreenParamater(this);
}

void XScreenManage::OperatorOfGetSignalParamater()
{
	XSendDataScreenManage::AddSendDataOfGetSignalParamater(this);
}

void XScreenManage::OperatorOfGetWindowParamater()
{
	XSendDataScreenManage::AddSendDataOfGetWindowParamater(this);
}

VEC_INPUTSIGNAL& XScreenManage::GetVecInputSignal()
{
	return m_pDelegate->GetVecInputSignal();
}

BOOL XScreenManage::IsLogin()
{
	return m_pDelegate->IsLogin();
}

void XScreenManage::OperateOfSetSignalParamater(char* pData)
{
	int nLen=36;

	if(!CheckSumNum(pData,nLen))
		return;
	//*************
	VEC_INPUTSIGNAL& VecSignal=GetVecInputSignal();

	int nInputIndex=0;
	nInputIndex=pData[2]&0xFF;

	//TRACE(_T("nInputIndex=%d\n"),nInputIndex);
	int nDataLen=0;
	memcpy(&nDataLen,pData+6,2);

	//TRACE(_T("nDataLen=%d\n"),nDataLen);
	for(int i=0;i<=3;i++)
	{
		int nChenal=i;	
		int nStatus=pData[8+i*7];

		//TRACE(_T("nStatus=%X\n"),nStatus);

		for(VEC_INPUTSIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XInputSignal *pInputSignal=*iter;

			int nIndex=pInputSignal->GetInputIndex();
	
			int nSignalIndex=(nIndex-1)/4;
			int nSignalChenal=(nIndex-1)%4;

			if((nSignalIndex==nInputIndex)
			&&(nSignalChenal==nChenal))
			{
			    pInputSignal->SetChanel(nSignalChenal);
				pInputSignal->SetReDataLen(nDataLen);
				pInputSignal->SetReStatus(pData[8+i*7]);

				int nHResulation=0;
				memcpy(&nHResulation,pData+9+i*7,2);
				pInputSignal->SetReResulationH(nHResulation);

				int nVResulation=0;
				memcpy(&nVResulation,pData+11+i*7,2);
				pInputSignal->SetReResulationV(nVResulation);

				pInputSignal->SetReRefresh(pData[13+i*7]);
				pInputSignal->SetReVideoSelect(pData[14+i*7]);
			}
		}
		//*************
		//输入板卡类别
		MAP_INPUTTYPE::iterator iter=m_MapInputType.find(nInputIndex);

		if(iter!=m_MapInputType.end())
		{
			XInputType* pType=iter->second;
			if(nDataLen==0)
			{
				pType->SetChannel(nChenal);
				pType->SetType(INPUTTYPE_NOPANE);
			}
			else
			{
				int nType=GetInputTypeByReStatus(nStatus);	
				pType->SetChannel(nChenal);
				pType->SetType(nType);
			}
		}
		else
		{
			XInputType* pType=new XInputType;
			if(nDataLen==0)
			{
				pType->SetChannel(nChenal);
				pType->SetType(INPUTTYPE_NOPANE);
				m_MapInputType.insert(std::pair<int,XInputType*>(nInputIndex,pType));
			}
			else
			{
				int nType=GetInputTypeByReStatus(nStatus);
				pType->SetChannel(nChenal);
				pType->SetType(nType);
				m_MapInputType.insert(std::pair<int,XInputType*>(nInputIndex,pType));
			}
		}
	}	
}

int XScreenManage::GetInputTypeByReStatus(int nStatus)
{
	if(nStatus==0x00
		||nStatus==0x01)
		return INPUTTYPE_2K;
	else if((nStatus&0xF0)==16)
		return INPUTTYPE_4K;
	else if((nStatus&0xF0)==32)
		return INPUTTYPE_VGA;
	else if((nStatus&0xF0)==48)
		return INPUTTYPE_SDI;
	else if((nStatus&0xF0)==64)
		return INPUTTYPE_AV;
	else if((nStatus&0xF0)==80)
		return INPUTTYPE_IP2K;
	else if((nStatus&0xF0)==96)
		return INPUTTYPE_IP4K;

	return INPUTTYPE_NULL;
}

MAP_INPUTTYPE& XScreenManage::GetMapInputType()
{
	return m_MapInputType;
}

void XScreenManage::OperateOfSetScreenParamaterOfMatrix(char* pData)
{
	int nLen=33;

	if(!CheckSumNum(pData,nLen))
		return;
	//////////////////////////////////////////////////////////////////////////
	//板卡号
	unsigned int nIndex=pData[2]&0xFF;
	int nBoardIndex=nIndex-127;

	//TRACE(_T("bIndex=%d\n"),nBoardIndex);

	//状态(四路信息)
	int nStatus=pData[8];
	//TRACE(_T("nStatus=%x\n"),nStatus);

	//矩阵卡类型
	int nMatrixType=nStatus&0xF0;
	//TRACE(_T("nMatrixType=%x\n"),nMatrixType);
	//矩阵通道有无信号
	int nTempMatrixChanel=nStatus&0x0F;
	//TRACE(_T("nTempMatrixChanel=%x\n"),nTempMatrixChanel);

	for(int i=0;i<=3;i++)
	{
		for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
		{
			XScreen *pScreen=*iter;

			if(nBoardIndex==pScreen->GetBoardIndex()
				&&(i+1)==pScreen->GetNumOfTwoScreen())
			{
				//TRACE(_T("nBoardIndex=%d\n"),pScreen->GetBoardIndex());

				//是否有信号
				int n=nTempMatrixChanel&1<<i;
				//TRACE(_T("n=%d\n"),n);

				if(pow((double)2,(int)i)==(nTempMatrixChanel&1<<i))
					pScreen->SetIsHasSignalOfMatrix(TRUE);
				else
					pScreen->SetIsHasSignalOfMatrix(FALSE);
				//////////////////////////////////////////////////////////////////////////
				pScreen->SetScreenType(nMatrixType);

				int nScreenHdpi=0;
				memcpy(&nScreenHdpi,pData+9+i*6,2);
				pScreen->SetReScreenHdpi(nScreenHdpi);

				int nScreenVdpi=0;
				memcpy(&nScreenVdpi,pData+11+i*6,2);
				pScreen->SetReScreenVdpi(nScreenVdpi);

				pScreen->SetReDpiIndex(pData[13+i*6]);
				//TRACE(_T("ReDpiIndex=%d\n"),pScreen->GetReDpiIndex());

				pScreen->SetReRefresh(pData[14+i*6]);
				//TRACE(_T("ReRefresh=%d\n"),pScreen->GetReRefresh());
			}
		}
	}

	//板卡类别
	MAP_BOARDTYPE::iterator iter=m_MapBoardType.find(nBoardIndex);

	if(iter!=m_MapBoardType.end())
		iter->second=BOARDTYPE_MATRIX;
	else
		m_MapBoardType.insert(std::pair<int,int>(nBoardIndex,BOARDTYPE_MATRIX));
}

void XScreenManage::OperateOfSetScreenParamater(char *pData)
{
	int nLen=15;

	if(!CheckSumNum(pData,nLen))
		return;

	//板卡序号
	unsigned int nIndex=pData[2]&0xFF;
	unsigned int nBoardIndex=nIndex-127;
	//TRACE(_T("nBoardIndex=%d\n"),nBoardIndex);
	int nStatus=pData[8];
	//TRACE(_T("nStatus=%X\n"),nStatus);

	//////////////////////////////////////////////////////////////////////////
	//板卡类别
	MAP_BOARDTYPE::iterator iterType=m_MapBoardType.find(nBoardIndex);
	if(iterType!=m_MapBoardType.end())
	{
		if(pData[8]==0
			&&pData[9]==0
			&&pData[10]==0
			&&pData[11]==0
			&&pData[12]==0
			&&pData[13]==0
			&&pData[14]==0)
			iterType->second=BOARDTYPE_NOPANE;
		else
		{
			int nType=GetBoardTypeByReStatus(nStatus);
			iterType->second=nType;
		}
	}
	else
	{
		if(pData[8]==0
			&&pData[9]==0
			&&pData[10]==0
			&&pData[11]==0
			&&pData[12]==0
			&&pData[13]==0
			&&pData[14]==0)
			m_MapBoardType.insert(std::pair<int,int>(nBoardIndex,BOARDTYPE_NOPANE));
		else
		{
			int nType=GetBoardTypeByReStatus(nStatus);
			m_MapBoardType.insert(std::pair<int,int>(nBoardIndex,nType));
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//配置屏幕完成之后，设置屏幕返回信息
	MAP_MULTIVIDEOWINDOWFRAMES& MapFrames=m_pMultiVideoWindow->GetMapFrames();
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		int nScreenIndex=pScreen->GetBoardIndex();
		if(nScreenIndex==nIndex-127)
		{
			//TRACE(_T("nScreenIndex=%d\n"),nScreenIndex);

			pScreen->SetReScreenIndex(nIndex);

			int nDataLen=0;
			memcpy(&nDataLen,pData+6,2);
			pScreen->SeteDataLen(nDataLen);

			int nStatus=pData[8];
			pScreen->SetReStatus(nStatus);
			//TRACE(_T("nStatus=%X\n"),nStatus);

			int nScreenHdpi=0;
			memcpy(&nScreenHdpi,pData+9,2);
			pScreen->SetReScreenHdpi(nScreenHdpi);
			//TRACE(_T("nScreenHdpi=%d\n"),nScreenHdpi);

			int nScreenVdpi=0;
			memcpy(&nScreenVdpi,pData+11,2);
			pScreen->SetReScreenVdpi(nScreenVdpi);
			//TRACE(_T("nScreenVdpi=%d\n"),nScreenVdpi);

			int nDpiIndex=pData[13];
			pScreen->SetReDpiIndex(nDpiIndex);
			//TRACE(_T("nDpiIndex=%d\n"),nDpiIndex);

			int nRefreash=pData[14];
			pScreen->SetReRefresh(nRefreash);

			//**********************************************
			int nScreenIndex=pScreen->GetIndex();

			MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=MapFrames.find(nScreenIndex);

			if(iter!=MapFrames.end())
			{
				m_pMultiVideoWindow->SetFramesReIndex(nScreenIndex,nIndex);
				m_pMultiVideoWindow->SetFramesReDateLen(nScreenIndex,nDataLen);
				m_pMultiVideoWindow->SetFramesReStatus(nScreenIndex,nStatus);
				m_pMultiVideoWindow->SetFramesReResulationH(nScreenIndex,nScreenHdpi);
				m_pMultiVideoWindow->SetFramesReResulationV(nScreenIndex,nScreenVdpi);
				m_pMultiVideoWindow->SetFramesReResulationIndex(nScreenIndex,nDpiIndex);
				m_pMultiVideoWindow->SetFramesReRefreash(nScreenIndex,nRefreash);	
			}
		}
	}
}

int XScreenManage::GetBoardTypeByReStatus(int nStatus)
{
	if(nStatus==0x00||nStatus==0x01)
		return BOARDTYPE_SIGNALSPLICE;
	else if((nStatus&0xF0)==16)
		return BOARDTYPE_MULTISPLICE;
	else if((nStatus&0xF0)==32)
		return BOARDTYPE_PREVIEW;

	return BOARDTYPE_NULL;
}

MAP_BOARDTYPE& XScreenManage::GetMapBoardType()
{
	return m_MapBoardType;
}

void XScreenManage::OperatorOfSetWindowParamater(char *pData)
{
	if(m_nScreenModel==SCREENMODEL_MATRIX)
		return;

	DWORD dwNowTime=GetTickCount();
	if (abs((long)dwNowTime-(long)m_SynTime)<2000)
		return;

	int nLen=144;
	if(!CheckSumNum(pData,nLen))
		return;

	int nTemp=0;
	nTemp=pData[2]&0xFF;
	int nPaneIndex=nTemp-127; 

	int nScreenTempNum=pData[3]&0xFF;
	int nScreenNum=nScreenTempNum+1;

	int nScreenIndex=0;
	if(nScreenNum==1
		||nScreenNum==2)
		GetScreenIndexByPaneIndex(nPaneIndex,nScreenNum,nScreenIndex);
	else
		GetScreenIndexByPaneIndex(nPaneIndex,nScreenIndex);
	
	XScreen* pScreen=GetScreenByIndex(nScreenIndex);
	if(NULL==pScreen)
		return;
	else
		pScreen->ClearVecSignal();
	
	if(NULL!=m_pMultiVideoWindow)
		m_pMultiVideoWindow->DeleteFrame(pScreen->GetIndex());
	//====================================
	RECTF rectScreen=pScreen->GetRect();
	//****************************************
	for(int i=0;i<=3;i++)
	{
		int nShowX1=0;
		memcpy(&nShowX1,pData+8+i*34,2);
		int nShowX2=0;
		memcpy(&nShowX2,pData+10+i*34,2);
		int nShowY1=0;
		memcpy(&nShowY1,pData+12+i*34,2);
		int nShowY2=0;
		memcpy(&nShowY2,pData+14+i*34,2);
		//*********************************
		//目标源百分比
		int nResX1=0;
		memcpy(&nResX1,pData+16+i*34,3);
		int nResY1=0;
		memcpy(&nResY1,pData+19+i*34,3);
		int nResX2=0;
		memcpy(&nResX2,pData+22+i*34,3);
		int nResY2=0;
		memcpy(&nResY2,pData+25+i*34,3);
		//****************************************
		//信号ID
		unsigned int nSingalID=0;
		memcpy(&nSingalID,pData+28+i*34,4);

		unsigned int nInputID=nSingalID;
		unsigned int nInputGroupID=nInputID&0xFFFFFFF0;
		
		BOOL bHight=FALSE;
		unsigned int nTempInputID=nInputID&0x80000000;
		if(nTempInputID==0x80000000)
			bHight=TRUE;

		//****************************************
		//输入序号
		int nChenal=pData[32+i*34];
		//****************************************
		//局部放大
		int nExpandX1=0;
		memcpy(&nExpandX1,pData+33+i*34,2);
		int nExpandY1=0;
		memcpy(&nExpandY1,pData+35+i*34,2);
		int nExpandX2=0;
		memcpy(&nExpandX2,pData+37+i*34,2);
		int nExpandY2=0;
		memcpy(&nExpandY2,pData+39+i*34,2);
		//信号局部放大
		XExpandInfo *pExpandInfo=new XExpandInfo;
		pExpandInfo->SetExpand(nExpandX1,nExpandY1,nExpandX2,nExpandY2);
		m_VecExpandInfo.push_back(pExpandInfo);
		//****************************************
		//层次号
		int nLevel=pData[41+i*34];
		//层次为零不显示
		if(nLevel==0)
			continue;
		//****************************************
		int nSignalIndex=nChenal;
		//判断信号是否为4K(根据信号源序号)
		//序号为零就继续循环
		if(nSignalIndex==0)
			continue;
		//判断输入是否为4K
		JudgetInputIsultra(nSignalIndex);
		XInputSignal* pInputSignal=XCalculateScreenManage::GetSignalByIndex(this,nSignalIndex);
		if(pInputSignal==NULL)
			continue;

		BOOL bIsUltra=pInputSignal->GetIsUltra();
		//输入信号RTSP地址
		//CString szRTSPAddr=pInputSignal->GetRTSPAddr();
		//输入信号IP
		CString szIP=pInputSignal->GetIPAddr();
		CString szUseName=pInputSignal->GetUseName();
		CString szPassWd=pInputSignal->GetPassWd();
			//****************************************
	    CString szName=pInputSignal->GetAnotherName();
		//TRACE(_T("szRTSPAddr=%s\n"),szRTSPAddr);
		//****************************************
		//从预览窗口拿到RTSP地址
		CString szRTSPAddr=GetRTSPAddrFromPreviewPane(nSignalIndex);

		//****************************************
		//屏幕分辨率
		int nScreenHdpi=0;
		int nScreenVdpi=0;
		if(!GetScreenResulation(nScreenIndex,nScreenHdpi,nScreenVdpi))
		{
			nScreenHdpi=pScreen->GetScreenHdpi();
			nScreenVdpi=pScreen->GetScreenVdpi();
		}
		//信号分辨率
		int nSignalHdpi=0;
		int nSignalVdpi=0;
		if(!GetSignalResulation(nSignalIndex,nSignalHdpi,nSignalVdpi))
		{
			//nSignalHdpi=pScreen->GetScreenHdpi();
			//nSignalVdpi=pScreen->GetScreenVdpi();
		}

		//****************************************
		//信号区域
		float nAdjustX=(float)1.0*nShowX1*rectScreen.Width/nScreenHdpi+rectScreen.X;
		float nAdjustY=(float)1.0*nShowY1*rectScreen.Height/nScreenVdpi+rectScreen.Y;
		float nSignalWidth=(float)nShowX2-nShowX1+1;
		float nSignalHeight=(float)nShowY2-nShowY1+1;
		float nAdjustSignalWidth=(float)1.0*nSignalWidth*rectScreen.Width/nScreenHdpi;
		float nAdjustSignalHight=(float)1.0*nSignalHeight*rectScreen.Height/nScreenVdpi;
		//****************************************
		//目标源显示区域
		int nResulationH=1920;
		int nResulationV=1088;

		int nTemp=0x800000;
		float nTempBeginX=(float)1.0*((float)nResX1/nTemp);
		float nTempEndX=(float)1.0*((float)nResX2/nTemp);
		float nTempBeginY=(float)1.0*((float)nResY1/nTemp);
		float nTempEndY=(float)1.0*((float)nResY2/nTemp);

		float nResBeginX=nTempBeginX*(nResulationH-1);
		float nResEndX=nTempEndX*(nResulationV-1);
		float nResBeginY=nTempBeginY*(nResulationH-1);
		float nResEndY=nTempEndY*(nResulationV-1); 

		RECTF nResRect;
		nResRect.X=nResBeginX;
		nResRect.Y=nResEndX;
		nResRect.Width=nResBeginY-nResBeginX;
		nResRect.Height=nResEndY-nResEndX;

		//TRACE(_T("X=%f,Y=%f,W=%f,H=%f\n"),nResRect.X,nResRect.Y,nResRect.Width,nResRect.Height);
		//****************************************
		RECTF adjustSignalRect;
		if(bIsUltra)
		{
			adjustSignalRect.X=nAdjustX;
			adjustSignalRect.Y=nAdjustY;
			adjustSignalRect.Width=nAdjustSignalWidth;
			adjustSignalRect.Height=nAdjustSignalHight;
		}
		else
		{
			int nTempAdjustX=XCalculateScreenManage::GetIntFromFloat(nAdjustX);
			int nTempAdjustY=XCalculateScreenManage::GetIntFromFloat(nAdjustY);
			int nTempAdjustW=XCalculateScreenManage::GetIntFromFloat(nAdjustSignalWidth);
			int nTempAdjustH=XCalculateScreenManage::GetIntFromFloat(nAdjustSignalHight);

			adjustSignalRect.X=(Gdiplus::REAL)nTempAdjustX;
			adjustSignalRect.Y=(Gdiplus::REAL)nTempAdjustY;
			adjustSignalRect.Width=(Gdiplus::REAL)nTempAdjustW;
			adjustSignalRect.Height=(Gdiplus::REAL)nTempAdjustH;
		}

		RECTF rectSignal=adjustSignalRect;
		//****************************************
		XSignal* pSignal=pScreen->AddSignal(
			rectSignal,
			nLevel,
			nSignalIndex,
			szName,
			nInputID,
			nInputGroupID,
			pExpandInfo,
			bIsUltra);
			
		pSignal->SetIPAddr(szIP);
		pSignal->SetRTSPAddr(szRTSPAddr);
		pSignal->SetUseName(szUseName);
		pSignal->SetPassWd(szPassWd);

		if(!bIsUltra&&bHight)
			pSignal->SetIs4kTo2k(TRUE);
		//****************************************
		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectSignal,nResRect);

		m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
		m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nSignalIndex);
		m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szName);
		m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nInputID);
		m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nInputGroupID);

		pSignal->SetPreviewFrame(pFrame);
		//限制同步RTSP计数一直增长
		MAP_RERTSPADDR::iterator iter=m_MapReRTSPAddr.find(szRTSPAddr);

		if(iter!=m_MapReRTSPAddr.end())
		{
			int nIndex=iter->second;
			int nCount=GetSignalCountByIndex(nIndex);
			m_pDelegate->SetRTSPAddrCount(szRTSPAddr,nCount+1);
		}
		else
			m_MapReRTSPAddr.insert(std::pair<CString,int>(szRTSPAddr,nSignalIndex));
		//****************************************
	}
	//按层次排序信号
	pScreen->SortSignal();
	m_pMultiVideoWindow->SortFrame(pScreen->GetIndex());
}

CString XScreenManage::GetRTSPAddrFromPreviewPane(int nSignalIndex)
{
	return m_pDelegate->GetRTSPAddrFromPreviewPane(nSignalIndex);
}

int XScreenManage::GetSignalCountByIndex(int nIndex)
{
	int nCount=0;
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			if(nIndex==pSignal->GetInputIndex())
				nCount++;
		}
	}
	return nCount;
}

void XScreenManage::OperateOfSetMatrixWindowParamater(char* pData)
{
	if(m_nScreenModel==SCREENMODEL_SPLIC)
		return;

	DWORD dwNowTime=GetTickCount();
	if (abs((long)dwNowTime-(long)m_SynTime)<2000)
		return;

	int nDataLen=0;
	memcpy(&nDataLen,pData+6,2);

	int nLen=nDataLen+10-2;

	if(!CheckSumNum(pData,nLen))
		return;

	for(int i=0;i<nDataLen;i++)
	{
		int nTempBoardIndex=i+1;
		int nInputIndex=pData[i+8];
		int nBoardIndex=(nTempBoardIndex-1)/4+1;
		int nChenal=(nTempBoardIndex-1)%4+1;

		//////////////////////////////////////////////////////////////////////////
		XScreen* pScreen=GetScreenByBoardIndex(nBoardIndex,nChenal);

		if(pScreen==NULL)
			continue;
		else
			pScreen->ClearVecSignal();

		if(NULL!=m_pMultiVideoWindow)
			m_pMultiVideoWindow->DeleteFrame(pScreen->GetIndex());

		RECTF rectScreen=pScreen->GetRect();
		//////////////////////////////////////////////////////////////////////////
		unsigned nMatrixSignalID=GetMatrixSignalID();
		SetMatrixSignalID(nMatrixSignalID+1);

		unsigned nMatrixSignalGroupID=nMatrixSignalID+1000;
		//////////////////////////////////////////////////////////////////////////
		JudgetInputIsultra(nInputIndex);
		XInputSignal* pInputSignal=XCalculateScreenManage::GetSignalByIndex(this,nInputIndex);
		if(pInputSignal==NULL)
			continue;

		CString szAnotherName=pInputSignal->GetAnotherName();
		//CString szRTSPAddr=pInputSignal->GetRTSPAddr();
		RECTF nResRect(0,0,1920,1088);

		//从预览窗口拿到RTSP地址
		CString szRTSPAddr=GetRTSPAddrFromPreviewPane(nInputIndex);

		BOOL bIsUltra=FALSE;
		//////////////////////////////////////////////////////////////////////////
		int nLevel=1;

		XExpandInfo *pExpandInfo=new XExpandInfo;
		pExpandInfo->SetExpand(0,0,0,0);
		m_VecExpandInfo.push_back(pExpandInfo);

		XSignal* pSignal=pScreen->AddSignal(
			rectScreen,
			nLevel,
			nInputIndex,
			szAnotherName,
			nMatrixSignalID,
			nMatrixSignalGroupID,
			pExpandInfo,
			bIsUltra);

		/////////////////////////////////////////////////////////////////////////
		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(pScreen->GetIndex(),szRTSPAddr,rectScreen,nResRect);

		m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nInputIndex);
		m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
		m_pMultiVideoWindow->SetFrameID(pScreen->GetIndex(),pFrame,nMatrixSignalID);
		m_pMultiVideoWindow->SetFrameGroupID(pScreen->GetIndex(),pFrame,nMatrixSignalGroupID);

		pSignal->SetPreviewFrame(pFrame);

		//限制同步RTSP计数一直增长
		MAP_RERTSPADDR::iterator iter=m_MapReRTSPAddr.find(szRTSPAddr);

		if(iter!=m_MapReRTSPAddr.end())
		{
			int nIndex=iter->second;
			int nCount=GetSignalCountByIndex(nIndex);
			m_pDelegate->SetRTSPAddrCount(szRTSPAddr,nCount+1);
		}
		else
			m_MapReRTSPAddr.insert(std::pair<CString,int>(szRTSPAddr,nInputIndex));
	}
}

unsigned int XScreenManage::GetMatrixSignalID()
{
	return m_signalID;
}

void XScreenManage::SetMatrixSignalID(unsigned int nID)
{
	m_signalID=nID;
}

XScreen* XScreenManage::GetScreenByBoardIndex(int nBoardIndex,int nChenal)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;
		if(pScreen->GetBoardIndex()==nBoardIndex
			&&pScreen->GetNumOfTwoScreen()==nChenal)
			return pScreen;
	}

	return NULL;
}

unsigned short XScreenManage::CheckNum(char *pData,int nLen)
{
	unsigned short nSum=0;

	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
		nSum=nSum&0xFF;
	}

	return nSum;
}

BOOL XScreenManage::GetScreenResulation(int nIndex,int& nH,int& nV)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		int nScreenIndex=pScreen->GetIndex();
		if(nScreenIndex==nIndex)
		{
			nH=pScreen->GetReScreenHdpi();
			nV=pScreen->GetReScreenVdpi();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL XScreenManage::GetSignalResulation(int nIndex,int& nH,int& nV)
{
	VEC_INPUTSIGNAL& VecInput=GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	{
		XInputSignal *pInput=*iter;

		int nSignalIndex=pInput->GetInputIndex();

		if(nSignalIndex==nIndex)
		{
			nH=pInput->GetReResulationH();
			nV=pInput->GetReResulationV();
			return TRUE;
		}
	}
	return FALSE;
}

void XScreenManage::GetScreenIndexByPaneIndex(int& nPaneIndex,int& nNum,int& nScreenIndex)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		if(pScreen->GetBoardIndex()==nPaneIndex)
		{
			if(pScreen->GetNumOfTwoScreen()==nNum)
				nScreenIndex=pScreen->GetIndex();
		}
	}	
}

void XScreenManage::GetScreenIndexByPaneIndex(int& nPaneIndex,int& nScreenIndex)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		if(pScreen->GetBoardIndex()==nPaneIndex)
			nScreenIndex=pScreen->GetIndex();
	}
}

XScreen *XScreenManage::GetScreenByIndex(int nIndex)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		if(pScreen->GetIndex()==nIndex)
			return pScreen;
	}

	return NULL;
}

void XScreenManage::OperatorOfSetSceneIndex(char* pData)
{
	//返回可用场景序号
	int nLen=12;
	if(!CheckSumNum(pData,nLen))
		return;

	m_SaveSceneDlg.SetData(pData);
}

void XScreenManage::SaveAllScene(CString szSceenName,int nSceneIndex,CString szSceneGroup,int nIndex,int nType)
{
	CString szPath = m_pDelegate->GetAllSceneFilePath(nSceneIndex, szSceenName,nIndex);

	if (XSceneDataManage::SaveData(this, szPath))
		XSendDataScreenManage::SendDataBySaveScene(this, nSceneIndex);
	else
		MessageBoxFromKey(_T("392"), _T("保存场景失败！"), MB_OK);
}

void XScreenManage::OperateOfSaveScene()
{
	//XSaveScence Dlg;

	m_SaveSceneDlg.SetDelegate(this);

	if(IDOK==m_SaveSceneDlg.DoModal())
	{
		CString szSceneName=m_SaveSceneDlg.GetSceneName();
		int nSceneIndex=m_SaveSceneDlg.GetSceneIndex();
		CString szSceneGroup=m_SaveSceneDlg.GetSceneGroup();

		//判断是否重名
		if(m_pDelegate->JudgeSceneName(szSceneName))
		{
			m_pDelegate->MessageBoxFromKey(_T("726"),_T("场景名称重复！"),MB_OK);
			return;
		}

		CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);

		//判断当前场景，屏幕是否一样
		//JudgeCurScreenResulation(this)

		if (XSceneDataManage::SaveData(this, szPath))
		{
			XSendDataScreenManage::SendDataBySaveScene(this, nSceneIndex);
			//添加到场景树
			HTREEITEM item=m_pDelegate->AddSceneToTree(nSceneIndex,szSceneName,GetScreenModel(),szSceneGroup);
			m_pDelegate->AddViewNameToScene(item,szSceneName,-1,GetViewName());
		}
		else
			MessageBoxFromKey(_T("392"), _T("保存场景失败！"), MB_OK);

	}
}

void XScreenManage::CopyOrderToShare(CString szSceneName,int nSceneIndex,int nIndex,CString szViewName)
{
	CString szPath=m_pDelegate->GetAllSceneFilePath(nSceneIndex, szSceneName,nIndex);

	XScreenManage* pTemp=new XScreenManage;

	pTemp->SetDelegate(this->GetDelegate());
	pTemp->SetBeginIndex(this->GetBeginIndex());
	pTemp->SetScreenModel(GetScreenModel());
	pTemp->ResetData();

	pTemp->m_IsSendPocket=TRUE;
	pTemp->ClearVecSendData();

	AddSceneToCopyScene(pTemp,szPath);

	pTemp->m_IsSendPocket=FALSE;
	pTemp->SendAllData(TRUE);

	delete pTemp;
}

void XScreenManage::CopySingleOrderToShare(CString szSceneName,int nSceneIndex,CString szViewName)
{
	CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);

	XScreenManage* pTemp=new XScreenManage;
	pTemp->SetDelegate(this->GetDelegate());
	pTemp->SetBeginIndex(this->GetBeginIndex());
	pTemp->SetScreenModel(GetScreenModel());
	pTemp->ResetData();

	pTemp->m_IsSendPocket=TRUE;
	pTemp->ClearVecSendData();

	AddSceneToCopyScene(pTemp,szPath);

	pTemp->m_IsSendPocket=FALSE;
	pTemp->SendAllData(TRUE);

	delete pTemp;
}


void XScreenManage::AddSceneToCopyScene(XScreenManage* pTemp,CString szPath)
{
	if (XSceneDataManage::GetData(pTemp,szPath))
	{
		VEC_SCREEN& VecScreen=pTemp->GetVecScreen();
		for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			int nScreenIndex=pScreen->GetIndex();
			RECTF rectScreen=pScreen->GetRect();
			//////////////////////////////////////////////////////////////////////////
			//按层次号排序
			pScreen->SortSignal();

			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
			{
				XSignal* pSignal=*iter;

				CString szRTSPAddr=pSignal->GetRTSPAddr();
				RECTF rect=pSignal->GetRect();
				unsigned int nSignalID=pSignal->GetSignalID();
				unsigned int nSignalGroupID=pSignal->GetSignalGroupID();
				int nIndex=pSignal->GetInputIndex();
				CString szAnotherName=pSignal->GetAnotherName();
				BOOL bIsUltra=pSignal->GetIsUltra();
				//////////////////////////////////////////////////////////////////////////
				RECTF rectInter=XCalculateScreenManage::GetRectBySignal(pTemp,nSignalGroupID);

				switch(pTemp->GetScreenModel())
				{
				case SCREENMODEL_SPLIC:
					XSendDataScreenManage::AddSendDataOfSignal(pTemp,pSignal,rectInter);
					break;
				case SCREENMODEL_MATRIX:
					XSendDataScreenManage::AddSendDataOfMatrixSignal(pTemp,pSignal,pScreen);
					break;
				default:
					break;
				}
			}
		}
	}

	XSendDataScreenManage::AddSendDataOfFinash(pTemp);
}


void XScreenManage::OpenAllScene(CString szSceneName,int nSceneIndex,int nIndex,int nType,CString szViewName)
{
	//删除之前判断 有没有权限
	if(JudgeIsCanOpenScene())
	{
		CString szNotice=m_pDelegate->GetNotice();

		if(szNotice!=_T(""))
			m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
		else
			m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

		return;
	}

	//从多场景中调用单个时，判断是否为当前页
	if(szViewName!=_T(""))
	{
		CString szStr=GetViewName();
		TRACE(_T("ViewName=%s\n"),szStr);

		if(szViewName!=GetViewName())
		{
			m_pDelegate->MessageBoxFromKey(_T("746"),_T("该场景不属于该页面！"),MB_OK);
			return;
		}
	}

	UpdateSynTime();
	SetRTSPAddrCountReset();
	DeleteAllFrame();
	DeleteAllSignal();

	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		XSendDataScreenManage::AddSendDataOfDeleteAllSignal(this);
		break;
	case SCREENMODEL_MATRIX:
		XSendDataScreenManage::AddSendDataOfDeleteAllMatrixSignal(this);
		break;
	default:
		break;
	}

	CString szPath = m_pDelegate->GetAllSceneFilePath(nSceneIndex, szSceneName,nIndex);

	if (XSceneDataManage::GetData(this,szPath))
	{
		m_pDelegate->UpdateControlDataShow(XDATATYPE_ALL);
		m_pMultiVideoWindow->ClearVecFrames();
		m_pMultiVideoWindow->SetMultiScale(GetMultiScale());
		m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
		m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
		ResetViewSize();

		//m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);

		AddScene();
	}
}

void XScreenManage::OpenScene(CString szSceneName,int nSceneIndex,CString szViewName)
{
	CString szStr=GetViewName();
	TRACE(_T("ViewName=%s\n"),szStr);

	if(szViewName!=GetViewName())
	{
		m_pDelegate->MessageBoxFromKey(_T("746"),_T("该场景不属于该页面！"),MB_OK);
		return;
	}

	//判断是否有权限执行，调用之前的删除操作
	if(JudgeIsCanOpenScene())
	{
		CString szNotice=m_pDelegate->GetNotice();

		if(szNotice!=_T(""))
			m_pDelegate->MessageBoxFromKey(_T("100"), szNotice, MB_OK);
		else
			m_pDelegate->MessageBoxFromKey(_T("377"), _T("您没有权限进行此操作!"), MB_OK);

		return;
	}

	UpdateSynTime();
	SetRTSPAddrCountReset();
	DeleteAllFrame();
	DeleteAllSignal();
	switch(m_nScreenModel)
	{
	case SCREENMODEL_SPLIC:
		XSendDataScreenManage::AddSendDataOfDeleteAllSignal(this);
		break;
	case SCREENMODEL_MATRIX:
		XSendDataScreenManage::AddSendDataOfDeleteAllMatrixSignal(this);
		break;
	default:
		break;
	}

	//////////////////////////////////////////////////////////////////////////
	CString szPath = m_pDelegate->GetSceneFilePath(nSceneIndex, szSceneName);

	if (XSceneDataManage::GetData(this,szPath))
	{
		m_pDelegate->UpdateControlDataShow(XDATATYPE_ALL);
		m_pMultiVideoWindow->ClearVecFrames();
		m_pMultiVideoWindow->SetMultiScale(GetMultiScale());
		m_pMultiVideoWindow->SetFramesCountH(m_nScreenCountH);
		m_pMultiVideoWindow->SetFramesCountV(m_nScreenCountV);
		ResetViewSize();
		//m_pDelegate->Operate(OPERATETYPE_RESETUSERNODEPOWER, NULL);
		AddScene();
	}
}

BOOL XScreenManage::JudgeIsCanOpenScene()
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			if (!m_pDelegate->GetUserNodePower(pSignal->GetInputIndex(), pScreen->GetIndex()))
				return TRUE;
		}
	}

	return FALSE;
}

void XScreenManage::OperateOfOpenScene()
{

}

void XScreenManage::AddScene()
{
	//第一块屏出问题（应该是硬件问题），暂停250毫秒，暂时可用
	Sleep(500);
	//////////////////////////////////////////////////////////////////////////
	m_IsSendPocket=TRUE;
	ClearVecSendData();
	//////////////////////////////////////////////////////////////////////////
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		int nScreenIndex=pScreen->GetIndex();
		RECTF rectScreen=pScreen->GetRect();
		//////////////////////////////////////////////////////////////////////////
		XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(
			pScreen->GetIndex(),
			pScreen->GetBoardIndex(),
			pScreen->GetRect(),
			pScreen->GetNumOfTwoScreen(),
			pScreen->GetIsTwoSignal());

		CString szText=SetText(pScreen);
		m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
		//////////////////////////////////////////////////////////////////////////
		//按层次号排序
		pScreen->SortSignal();

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;

			CString szRTSPAddr=pSignal->GetRTSPAddr();
			RECTF rect=pSignal->GetRect();
			unsigned int nSignalID=pSignal->GetSignalID();
			unsigned int nSignalGroupID=pSignal->GetSignalGroupID();
			int nIndex=pSignal->GetInputIndex();
			CString szAnotherName=pSignal->GetAnotherName();
			BOOL bIsUltra=pSignal->GetIsUltra();
			//////////////////////////////////////////////////////////////////////////
			RECTF rectInter=XCalculateScreenManage::GetRectBySignal(this,nSignalGroupID);
			//TRACE(_T("X=%f,Y=%f,W=%f,H=%f\n"),rectInter.X,rectInter.Y,rectInter.Width,rectInter.Height);
			//重新开窗
			//TRACE(_T("Time=%d-%s\n"),GetTickCount(),_T("AddSendDataOfSignal"));
			//拼接/矩阵分别开窗
			switch(m_nScreenModel)
			{
			case SCREENMODEL_SPLIC:
				XSendDataScreenManage::AddSendDataOfSignal(this,pSignal,rectInter);
				break;
			case SCREENMODEL_MATRIX:
				XSendDataScreenManage::AddSendDataOfMatrixSignal(this,pSignal,pScreen);
				break;
			default:
				break;
			}
	
			//Sleep(500);
			//XSendDataScreenManage::AddSendDataOfFinash(this);
			//////////////////////////////////////////////////////////////////////////
			int nResulationH=1920;
			int nResulationV=1088;
			//所交区域占整个视频区域的
			float nResBeginX=(rect.X-rectScreen.X)*nResulationH/rect.Width;
			float nResBeginY=(rect.Y-rectScreen.Y)*nResulationV/rect.Height;
			float nTempResWidth=rect.Width*nResulationH/rect.Width;
			float nTempResHight=rect.Height*nResulationV/rect.Height;
			float nResEndX=nResBeginX+nTempResWidth-1;
			float nResEndY=nResBeginY+nTempResHight-1;

			RECTF rectImage;
			rectImage.X=nResBeginX;
			rectImage.Y=nResBeginY;
			rectImage.Width=nTempResWidth;
			rectImage.Height=nTempResHight;
			//////////////////////////////////////////////////////////////////////////
			XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(nScreenIndex,szRTSPAddr,rect,rectImage,TRUE);

			m_pMultiVideoWindow->SetFrameIsUltra(pScreen->GetIndex(),pFrame,bIsUltra);
			m_pMultiVideoWindow->SetFrameIndex(pScreen->GetIndex(),pFrame,nIndex);
			m_pMultiVideoWindow->SetFrameAnotherName(pScreen->GetIndex(),pFrame,szAnotherName);
			m_pMultiVideoWindow->SetFrameID(nScreenIndex,pFrame,nSignalID);
			m_pMultiVideoWindow->SetFrameGroupID(nScreenIndex,pFrame,nSignalGroupID);

			pSignal->SetPreviewFrame(pFrame);
			m_pDelegate->SetRTSPAddrCountReset(szRTSPAddr);
			m_pDelegate->SetRTSPAddrCountPlus(szRTSPAddr);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	m_IsSendPocket=FALSE;
	SendAllData();
	//////////////////////////////////////////////////////////////////////////
	XSendDataScreenManage::AddSendDataOfFinash(this);
	//TRACE(_T("Time=%d-%s\n"),GetTickCount(),_T("AddSendDataOfFinash"));
}

void XScreenManage::OperateOfGetSceneIndex()
{
	XSendDataScreenManage::AddSendDataOfGetSceneIndex(this);
}

void XScreenManage::DeleteScene(int nSceneIndex)
{
	//更改方式，软件开窗
	XSendDataScreenManage::AddSendDataOfDeleteScene(this,nSceneIndex);
}

void XScreenManage::OperateOfDeleteScene()
{
	//m_DeleteSceneDlg.SetDelegate(this);

	//if(IDOK==m_DeleteSceneDlg.DoModal())
	//{
	//	int nSceneIndex = m_DeleteSceneDlg.GetDelIndex();

	//	XSendDataScreenManage::AddSendDataOfDeleteScene(this,nSceneIndex);
	//}
}

int XScreenManage::GetSceneIndexFromScenePath(CString szPath)
{
	int nIndex=-1;
	int nPos=szPath.ReverseFind('\\');

	if (-1!=nPos)
	{
		CString szFileName=szPath.Mid(nPos+1,szPath.GetLength()-nPos);
		nPos=szFileName.Find('.');
		if (-1!=nPos)
		{
			CString szIndex=szFileName.Left(nPos);
			nIndex=_ttoi(szIndex);
		}
	}

	return nIndex;
}

XScreenMoveInfo* XScreenManage::GetScreenMoveInfo()
{
	return &m_MoveInfo;
}

XTimedPollingInfo* XScreenManage::GetTimedPollingInfo()
{
	return &m_PollingInfo;
}

XAllResulationInfo* XScreenManage::GetAllResulationInfo()
{
	return &m_AllInfo;
}

XResulationHCutInfo* XScreenManage::GetResulationHCutInfo()
{
	return &m_ResulationHInfo;
}

XResulationVCutInfo* XScreenManage::GetResulationVCutInfo()
{
	return &m_ResulationVInfo;
}

XOldOrderInfo* XScreenManage::GetOldOrderInfo()
{
	return &m_OldOrderInfo;
}

XMenuScreenSetInfo* XScreenManage::GetMenuScreenSetInfo()
{
	return &m_ScreenSetInfo;
}

void XScreenManage::OperateOfSetScreenMove()
{
	XScreenMoveDlg dlg;

	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	m_pScreenMoveDlg=&dlg;
	dlg.DoModal();
	m_pScreenMoveDlg=NULL;
}

void XScreenManage::OperatorOfSetScreenMoveAsk(char* pData)
{
	int nLen=12;
	if(!CheckSumNum(pData,nLen))
		return;

	DWORD dwTime=0;	
	memcpy(&dwTime,pData+8,4);

	if(m_pScreenMoveDlg!=NULL)
		m_pScreenMoveDlg->SetReTime(dwTime);
}

void XScreenManage::OperateOfSetTimedPolling()
{
	XTimedPollingDlg dlg;

	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	if(IDOK==dlg.DoModal())
		XSendDataScreenManage::SendDataByTimedPolling(this);
}

void XScreenManage::OperateOfGetDeviceStatus()
{
	XSendDataScreenManage::SendDataByDeviceStatus(this);
}

void XScreenManage::OperateOfRunOldOrder()
{
	XRunOldOrderDlg dlg;
	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	if(IDOK==dlg.DoModal())
		XSendDataScreenManage::SendDataByRunOldOrder(this);
}

void XScreenManage::OperateOfSetDeviceStatus(char* pData)
{
	int nLen=12;
	if(!CheckSumNum(pData,nLen))
		return;

	//********************
	int nPanStatus=pData[8];
	int nChipStatus=pData[9];
	CString szPanStatus;
	szPanStatus.Format(_T("%d"),nPanStatus);
	m_pDelegate->Operate(OPERATETYPE_REFRESHPAN, &szPanStatus);
	szPanStatus.Format(_T("%d"),nChipStatus);
	m_pDelegate->Operate(OPERATETYPE_REFRESHCHIP, &szPanStatus);
	
	//********************
	int nTemperature=0;
	memcpy(&nTemperature,pData+10,2);
	float nTemp=(float)nTemperature/10;
	int nIntTemperature=(int)nTemp;
	float nDecTemp=nTemp-nIntTemperature;
	int nDecTemperature=(int)nDecTemp*10;
	CString szTemperature;

	if(nDecTemperature!=0)
		szTemperature.Format(_T("%d.%d℃"), nIntTemperature, nDecTemperature);
	else
		szTemperature.Format(_T("%d℃"), nIntTemperature);

	m_pDelegate->Operate(OPERATETYPE_SETTEMPERATURE, &szTemperature);
	//********************
}

void XScreenManage::OperateOfChangeScreen()
{
	XChangeScreen dlg;
	dlg.SetDelegate(this);
	dlg.SetScreenMange(this);
	int nScreenIndex=m_TempScreen->GetIndex();
	dlg.SetScreenIndex(nScreenIndex);

	if(IDOK==dlg.DoModal())
	{
		int nComboIndex=dlg.GetComboIndex();
		for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			if(nComboIndex==pScreen->GetIndex())
				pScreen->SetIndex(nScreenIndex);
		}

		m_TempScreen->SetIndex(nComboIndex);
	}

	//================================
	//更新预览墙屏幕
	m_pMultiVideoWindow->ClearVecFrames();

	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		XMultiVideoWindowFrames* pFrames=m_pMultiVideoWindow->AddFrames(pScreen->GetIndex(),
			                                                            pScreen->GetBoardIndex(),
																		pScreen->GetRect(),
																		pScreen->GetNumOfTwoScreen(),
																		pScreen->GetIsTwoSignal());
		CString szText=SetText(pScreen);
		m_pMultiVideoWindow->SetFramesText(pScreen->GetIndex(),szText,12);
	}
	//=================================
}

BOOL XScreenManage::CheckSumNum(char* pData,int nLen)
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

void XScreenManage::SetIsMenuSet(BOOL b)
{
	m_bIsMenuSet=b;
}

BOOL XScreenManage::GetIsMenuSet()
{
	return m_bIsMenuSet;
}

void XScreenManage::OnBtnNewScene()
{
	DecideIsMenuSet(m_bIsMenuSet);
}

void XScreenManage::SetScreenByDbClick()
{
	OperateMenuScreenSet();
}

void XScreenManage::OperateMenuScreenSet()
{
	DecideIsMenuSet(m_bIsMenuSet);
}

void XScreenManage::DecideIsMenuSet(BOOL bIsMenuSet)
{
	XSelectEquipment dlg;

	dlg.SetDelegate(this);
	dlg.SetScreenManage(this);
	dlg.SetIsMenuSet(bIsMenuSet);
	if(IDOK==dlg.DoModal())
	{
		int nEquipment=dlg.GetEquipment();
		XSetScreenRange RangeDlg;
		RangeDlg.SetDelegate(this);
		RangeDlg.SetScreenManage(this);
		RangeDlg.SetIsMenuSet(bIsMenuSet);
		RangeDlg.SetEquipmentNum(nEquipment);

		if(IDOK==RangeDlg.DoModal())
		{
			int nScreenNumH=RangeDlg.GetScreenNumH();
			int nScreenNumV=RangeDlg.GetScreenNumV();
			int nEquipmentNum=RangeDlg.GetEquipmentNum();

			XSetBoard BoardDlg;
			BoardDlg.SetDelegate(this);
			BoardDlg.SetScreenManage(this);
			BoardDlg.SetIsMenuSet(bIsMenuSet);
			BoardDlg.SetScreenNumH(nScreenNumH);
			BoardDlg.SetScreenNumV(nScreenNumV);
			BoardDlg.SetEquipment(nEquipmentNum);
			BoardDlg.SetScreenModel(m_nScreenModel);
			BoardDlg.DoModal();
		}
	}
}

void XScreenManage::SetOSD(int nIndex)
{
	VEC_INPUTSIGNAL& VecInputSignal=GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();++iter)
	{
		XInputSignal* pInputSignal=*iter;

		int nInputIndex=pInputSignal->GetInputIndex();

		if(nInputIndex==nIndex)
			m_pDelegate->SetOSD(pInputSignal);
	}
}

void XScreenManage::ShowMenu(CPoint& point)
{
	GetCursorPos(&point);

	CMenu menu; 
	menu.CreatePopupMenu();	
	menu.AppendMenu(MF_STRING, ID_SETSCREENMENU, m_pDelegate->GetTranslationString(_T("602"), _T("屏幕设置"))+_T("(&A)"));
	menu.AppendMenu(MF_STRING, ID_SAVESCENEMENU, m_pDelegate->GetTranslationString(_T("386"), _T("保存场景"))+_T("(&S)"));
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, m_pDelegate->GetCWND());
	menu.DestroyMenu(); 
}

void XScreenManage::SaveSceneByCloseView()
{
	OperateOfSaveScene();
}

void XScreenManage::OperateMenuSaveScene()
{
	OperateOfSaveScene();
}

void XScreenManage::AdjustMultiVideoWindowSize()
{
	CRect rect;
	GetClientRect(m_View->GetSafeHwnd(),&rect);
	m_pDelegate->AdjustMultiVideoWindowHWNDSize(m_pMultiVideoWindow,rect.Width(),rect.Height());
}

void XScreenManage::OperateOfGetInputNum()
{
	//获取信号序号
	XSendDataScreenManage::AddSendDataOfGetSignalNum(this);
}

void XScreenManage::OperateOfSetInputNum(char* pData)
{
	int nDataLen=pData[6]&0XFF;
	int nLen=nDataLen+10-2;
	if(!CheckSumNum(pData,nLen))
		return;
	//*************************
	int n=nDataLen/5;
	for(int i=0;i<n;i++)
	{
		int nSignalNum=i+1;
		unsigned int nSignalID=0;	
		memcpy(&nSignalID,pData+8+i*5,4);

		for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
			for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
			{
				XSignal* pSignal=*iter;
				unsigned int nID=pSignal->GetSignalID();
				if(nID==nSignalID)
					pSignal->SetSignalNum(nSignalNum);
			}
		}
	}
}

void XScreenManage::SetScreenSignalRTSPAddrByIndex(int nInputIndex,CString szRTSP)
{
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		int nScreenIndex=pScreen->GetIndex();
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();
		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			int nIndex=pSignal->GetInputIndex();		
			if(nIndex==nInputIndex)
			{	
				pSignal->SetRTSPAddr(szRTSP);
				XMultiVideoWindowFrame* pFrame=pSignal->GetPreviewFrame();
				m_pMultiVideoWindow->SetFrame(nScreenIndex,pFrame,szRTSP);
			}
		}
	}
}

void XScreenManage::ChangeMultiVideoWindowsAnotherName(int nInputIndex,CString szAnotherName)
{
	//更改信号别名
	for(VEC_SCREEN::iterator iter=m_VecScreen.begin();iter!=m_VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pSignal=*iter;
			if(nInputIndex==pSignal->GetInputIndex())
				pSignal->SetAnotherName(szAnotherName);
		}
	}

	//立即更改预览墙显示文字
	m_pMultiVideoWindow->ChangeMultiVideoWindowsAnotherName(nInputIndex,szAnotherName);
}

void XScreenManage::OperateOfSetNormal()
{
	m_nStatus=DRAGSTATUS_NORMAL;
}

void XScreenManage::OperateOfSetFull()
{
	m_nStatus=DRAGSTATUS_FULL;
}

void XScreenManage::OperateOfSetFour()
{
	m_nStatus=DRAGSTATUS_FOUR;
}

void XScreenManage::OperateOfSetCopyModel()
{
	m_nStatus=DRAGSTATUS_COPY;
}

void XScreenManage::OperateOfSetInter()
{
	m_nStatus=DRAGSTATUS_INTER;
}

void XScreenManage::OperateOfSetTipModel()
{
	m_nDragModel=DRAGMODEL_TIPMODEL;
}

void XScreenManage::OperateOfSetUpModel()
{
	m_nDragModel=DRAGMODEL_UPMODEL;
}

void XScreenManage::OperateOfSetDownModel()
{
	m_nDragModel=DRAGMODEL_DOWNMODEL;
}

void XScreenManage::UpdateControlUIByStatus(CCmdUI* pCmdUI,int nStatus)
{
	if(nStatus==m_nStatus)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void XScreenManage::UpdateControlUIByModel(CCmdUI* pCmdUI,int nModel)
{
	if(nModel==m_nDragModel)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

MAP_SCENEGROUP& XScreenManage::GetMapSceneGroup()
{
	return m_pDelegate->GetMapSceneGroup();
}

int XScreenManage::GetScreenType()
{
	return m_nScreenModel;
}

void XScreenManage::SetFrameRTSPCountByIndex(int nInputIndex)
{
	m_pDelegate->SetFrameRTSPCountByIndex(nInputIndex);
}

void XScreenManage::SetMultiScale(float f)
{
	//m_fCurScale=f;

	//if(m_pMultiVideoWindow!=NULL)
	//{
	//	m_pMultiVideoWindow->SetMultiScale(f);
	//}
}

VEC_BASESCREENMANAGE& XScreenManage::GetVecBaseScreenManage()
{
	return m_pDelegate->GetVecBaseScreenManage();
}

BOOL XScreenManage::AddScalingByMouseWheel(short zDelta)
{
	int nScale=0;

	if(zDelta>0)
	{	
		if(m_nCurScale>=100)
		{
			nScale=m_nCurScale+25;
		}
		else if(m_nCurScale<100)
		{
			nScale=m_nCurScale+20;
		}
	}
	else if(zDelta<0)
	{
		if(m_nCurScale>100)
		{
			nScale=m_nCurScale-25;
		}
		else if(m_nCurScale<=100)
		{
			nScale=m_nCurScale-20;
		}
	}

	if(nScale>=300)
	{
		nScale=300;
	}
	else if(nScale<=60)
	{
		nScale=60;
	}

	if(nScale!=m_nCurScale)
	{
		m_nCurScale=nScale;
		SetCurScale(m_nCurScale);
		ResetViewSize();
		float nTemp=m_nCurScale/100.0f;
		if(m_pMultiVideoWindow!=NULL)
			m_pMultiVideoWindow->SetMultiScale(nTemp);
	}

	m_pDelegate->UpdateControlDataShow(XDATATYPE_SCALE);

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XScreenManage::UpdateControlDataShowOfScale(CMFCRibbonComboBox* pCombox)
{
	if (nullptr != pCombox)
	{
		pCombox->RemoveAllItems();

		pCombox->AddItem(_T("300%"));
		pCombox->AddItem(_T("275%"));
		pCombox->AddItem(_T("250%"));
		pCombox->AddItem(_T("225%"));
		pCombox->AddItem(_T("200%"));
		pCombox->AddItem(_T("175%"));
		pCombox->AddItem(_T("150%"));
		pCombox->AddItem(_T("125%"));
		pCombox->AddItem(_T("100%"));
		pCombox->AddItem(_T("80%"));
		pCombox->AddItem(_T("60%"));

		CString szTemp = _T("");
		szTemp.Format(_T("%d%%"), m_nCurScale);

		pCombox->SelectItem(szTemp);
	}
}

void XScreenManage::UpdateControlDataShowOfOutputCountH(CMFCRibbonEdit* p)
{
	CString szTemp = _T("");
	szTemp.Format(_T("%d"), m_nScreenCountH);

	p->SetEditText(szTemp);
}

void XScreenManage::UpdateControlDataShowOfOutputCountV(CMFCRibbonEdit* p)
{
	CString szTemp = _T("");
	szTemp.Format(_T("%d"), m_nScreenCountV);

	p->SetEditText(szTemp);
}

void XScreenManage::ControlDataChangeOfScale(CMFCRibbonComboBox* pCombox)
{
	CString szData = pCombox->GetItem(pCombox->GetCurSel());

	int nScale = _ttoi(szData);

	if (nScale != m_nCurScale)
	{
		SetCurScale(nScale);
		ResetViewSize();
		float nTemp=m_nCurScale/100.0f;
		if(m_pMultiVideoWindow!=NULL)
			m_pMultiVideoWindow->SetMultiScale(nTemp);
	}
}

void XScreenManage::ControlDataChangeOfOutputCountH(CMFCRibbonEdit* p)
{
	CString szTemp = p->GetEditText();
	szTemp.Trim();
	if (_T("") == szTemp)
	{
		szTemp.Format(_T("%d"), m_nScreenCountH);
		p->SetEditText(szTemp);
		return;
	}

	int nCount = _ttoi(szTemp);

	if (nCount < 0 || nCount > 200)
	{
		m_pDelegate->MessageBoxFromKey(_T("342"), _T("输出个数错误，范围为1~200,请重新输入!"), MB_OK);
		szTemp.Format(_T("%d"), m_nScreenCountH);
		p->SetEditText(szTemp);
		return;
	}

	if (nCount != m_nScreenCountH)
	{
		m_nScreenCountH = nCount;
		p->SetEditText(szTemp);
		ResetDataByScreenCountChange();
	}
}

void XScreenManage::ControlDataChangeOfOutputCountV(CMFCRibbonEdit* p)
{
	CString szTemp = p->GetEditText();

	szTemp.Trim();
	if (_T("") == szTemp)
	{
		szTemp.Format(_T("%d"), m_nScreenCountV);
		p->SetEditText(szTemp);
		return;
	}

	int nCount = _ttoi(szTemp);

	if (nCount < 0 || nCount > 200)
	{
		m_pDelegate->MessageBoxFromKey(_T("342"), _T("输出个数错误，范围为1~200,请重新输入!"), MB_OK);
		szTemp.Format(_T("%d"), m_nScreenCountV);
		p->SetEditText(szTemp);
		return;
	}

	if (nCount != m_nScreenCountV)
	{
		m_nScreenCountV = nCount;
		p->SetEditText(szTemp);
		ResetDataByScreenCountChange();
	}
}

void XScreenManage::UpdateControlDataShow(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_OUTPUTCOUNTH:
		{
			UpdateControlDataShowOfOutputCountH((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_OUTPUTCOUNTV:
		{
			UpdateControlDataShowOfOutputCountV((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_SCALE:
		{
			UpdateControlDataShowOfScale((CMFCRibbonComboBox*)pControl);
		}
		break;
	default:
		break;
	}
}

void XScreenManage::ControlDataChange(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_OUTPUTCOUNTH:
		{
			ControlDataChangeOfOutputCountH((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_OUTPUTCOUNTV:
		{
			ControlDataChangeOfOutputCountV((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_SCALE:
		{
			ControlDataChangeOfScale((CMFCRibbonComboBox*)pControl);
		}
		break;
	default:
		break;
	}
}

void XScreenManage::UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)
{
	switch(type)
	{
	case CMDUITYPE_NORMAL:
		{
			UpdateControlUIByStatus(pCmdUI,DRAGSTATUS_NORMAL);
		}
		break;
	case CMDUITYPE_FULL:
		{
			UpdateControlUIByStatus(pCmdUI,DRAGSTATUS_FULL);
		}
		break;
	case CMDUITYPE_FOUR:
		{
			UpdateControlUIByStatus(pCmdUI,DRAGSTATUS_FOUR);
		}
		break;
	case CMDUITYPE_INTER:
		{
			UpdateControlUIByStatus(pCmdUI,DRAGSTATUS_INTER);
		}
		break;
	case CMDUITYPE_COPYMODEL:
		{
			UpdateControlUIByStatus(pCmdUI,DRAGSTATUS_COPY);
		}
		break;
	case CMDUITYPE_TIPMODEL:
		{
			UpdateControlUIByModel(pCmdUI,DRAGMODEL_TIPMODEL);
		}
		break;
	case CMDUITYPE_UPMODEL:
		{
			UpdateControlUIByModel(pCmdUI,DRAGMODEL_UPMODEL);
		}
		break;
	case CMDUITYPE_DOWNMODEL:
		{
			UpdateControlUIByModel(pCmdUI,DRAGMODEL_DOWNMODEL);
		}
		break;
	default:
		break;
	}
}

void XScreenManage::Operate(OPERATETYPE type, void* pData)
{
	switch(type)
	{
	case OPERATETYPE_SCREENCLOSESIGNAL:
		{
			OperateOfCloseSignal();
		}
		break;
	case OPERATETYPE_DELETEALLSIGNAL:
		{
			OperateOfDeleteAllSignal();
		}
		break;
	case OPERATETYPE_SETSIGNALTOP:
		{
			OperateOfTopSignal();
		}
		break;
	case OPERATETYPE_SETSIGNALBOTTOM:
		{
			OperateOfBottomSignal();
		}
		break;
	case OPERATETYPE_SETSIGNALSHIFTUP:
		{
			OperateOfShiftUPSignal();
		}
		break;
	case OPERATETYPE_SETSIGNALSHIFTDOWN:
		{
			OperateOfShiftDownSignal();
		}
		break;
	case OPERATETYPE_CHANGEINPUT:
		{
			OperateOfChangeInput();
		}
		break;
	case OPERATETYPE_DEVICESTATUS:
		{
			OperateOfGetDeviceStatus();
		}
		break;
	case OPERATETYPE_SCREENRESULATION:
		{
			OperateOfScreenResulation();
		}
		break;
	case OPERATETYPE_SCREENATTRIBUTE:
		{
			OperateOfScreenAttribute();
		}
		break;
	case OPERATETYPE_CHANGESCREEN:
		{
			OperateOfChangeScreen();
		}
		break;
	case OPERATETYPE_SETSIGNALPARAMATER:
		{
			OperateOfSetSignalParamater((char*)pData);
		}
		break;
	case OPERATETYPE_SETSCREENPARAMATER:
		{
			OperateOfSetScreenParamater((char*)pData);
		}
		break;
	case OPERATETYPE_SETSCREENPARAMATEROFMATRIX:
		{
			OperateOfSetScreenParamaterOfMatrix((char*)pData);
		}
		break;
	case OPERATETYPE_SETWINDOWPARAMATER:
		{
			OperatorOfSetWindowParamater((char*)pData);
		}
		break;
	case OPERATETYPE_GETSCREENMOVEASK:
		{
			OperatorOfSetScreenMoveAsk((char*)pData);
		}
		break;
	case OPERATETYPE_SETSCENEINDEX:
		{
			OperatorOfSetSceneIndex((char*)pData);
		}
		break;
	case OPERATETYPE_SETDEVICESTATUS:
		{
			OperateOfSetDeviceStatus((char*)pData);
		}
		break;
	case OPERATETYPE_GETSIGNALPARAMATER:
		{
			OperatorOfGetSignalParamater();
		}
		break;
	case OPERATETYPE_GETWINDOWPARAMATER:
		{
			OperatorOfGetWindowParamater();
		}
		break;
	case OPERATETYPE_GETSCREENPARAMATER:
		{
			OperateOfGetScreenParamater();
		}
		break;
	case OPERATETYPE_SAVESCENCE:
		{
			OperateOfSaveScene();
		}
		break;
	case OPERATETYPE_OPENSCENCE:
		{
			OperateOfOpenScene();
		}
		break;
	case OPERATETYPE_DELETESCENCE:
		{
			OperateOfDeleteScene();
		}
		break;
	case OPERATETYPE_GETSCENEINDEX:
		{
			OperateOfGetSceneIndex();
		}
		break;
	case OPERATETYPE_SCREENMOVE:
		{
			OperateOfSetScreenMove();
		}
		break;
	case OPERATETYPE_TIMEDPOLLING:
		{
			OperateOfSetTimedPolling();
		}
		break;
	case OPERATETYPE_SETSCREENRESULATION:
		{
			OperateOfSetScreenResulation();
		}
		break;
	case OPERATETYPE_RUNOLDORDER:
		{
			OperateOfRunOldOrder();
		}
		break;
	case OPERATETYPE_NEWSCENE:
		{
			OnBtnNewScene();
		}
		break;
	case OPERATETYPE_MENUSCREENSET:
		{
			OperateMenuScreenSet();
		}
		break;
	case OPERATETYPE_MENUSAVESCENE:
		{
			OperateMenuSaveScene();
		}
		break;
	case OPERATETYPE_SETSIGNALEXPAND:
		{
			OperateOfExpandSignal();
		}
		break;
	case OPERATETYPE_GETINPUTNUM:
		{
			OperateOfGetInputNum();
		}
		break;
	case OPERATETYPE_SETINPUTNUM:
		{
			OperateOfSetInputNum((char*)pData);
		}
		break;
	case OPERATETYPE_NORMAL:
		{
			OperateOfSetNormal();
		}
		break;
	case OPERATETYPE_FULL:
		{
			OperateOfSetFull();
		}
		break;
	case OPERATETYPE_FOUR:
		{
			OperateOfSetFour();
		}
		break;
	case OPERATETYPE_COPYMODEL:
		{
			OperateOfSetCopyModel();
		}
		break;
	case OPERATETYPE_INTER:
		{
			OperateOfSetInter();
		}
		break;

	case OPERATETYPE_TIPMODEL:
		{
			OperateOfSetTipModel();
		}
		break;
	case OPERATETYPE_UPMODEL:
		{
			OperateOfSetUpModel();
		}
		break;
	case OPERATETYPE_DOWNMODEL:
		{
			OperateOfSetDownModel();
		}
		break;
	case OPERATETYPE_SCREENRESULATIONOFMATRIX:
		{
			OperateOfSetScreenResulationByMatrix();
		}
		break;
	case OPERATETYPE_GETMATRIXOUTPUT:
		{
			OperateOfSetMatrixWindowParamater((char*)pData);
		}
		break;
	case OPERATETYPE_MATRIXOUTPUT:
		{
			XSendDataScreenManage::AddSendDataOfGetMatrix(this);
		}
		break;
	case OPERATETYPE_SINGLESCENE:
		{
			OperateOfSaveScene();
		}
		break;
	case OPERATETYPE_SETROWDPI:
		{
			OperateOfSetRowDpi();
		}
		break;
	case OPERATETYPE_SETCOLDPI:
		{
			OperateOfSetColDpi();
		}
		break;
	default:
		break;
	}
}

