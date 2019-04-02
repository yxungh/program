#include "StdAfx.h"
#include "XDataScreenManage.h"
#include "XScreenManage.h"
#include "XConstantIM.h"
#include "XScreen.h"
#include "XSignal.h"
#include "XCalculateScreenManage.h"
#include "XScreenDataInfo.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrames.h"
#include "XDelegateScreenManage.h"
#include "XScreenRowInfo.h"
#include "XScreenColInfo.h"

XDataScreenManage::XDataScreenManage(void)
{
}


XDataScreenManage::~XDataScreenManage(void)
{
}

BOOL XDataScreenManage::GetData(XScreenManage* p, CString szPath)
{
	CFile mFile;

	if (mFile.Open(szPath, CFile::modeRead))
	{
		CArchive arch(&mFile, CArchive::load);

		GetData(p, arch);

		arch.Close();

		mFile.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XDataScreenManage::GetData(XScreenManage* p, CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	switch(nVersion)
	{
	case 1:
		{
			GetDataOfVersion1(p, arch);
		}
		break;
	default:
		break;
	}
}

void XDataScreenManage::GetDataOfVersion1(XScreenManage* p, CArchive& arch)
{
	int nScreenCountH;
	arch>>nScreenCountH;
	
	int nScreenCountV;
	arch>>nScreenCountV;

	int nResolutionH;
	arch>>nResolutionH;
	
	int nResolutionV;
	arch>>nResolutionV;

	int nRightResulationH;
	arch>>nRightResulationH;

	int nBottomResulationV;
	arch>>nBottomResulationV;

	int nBeginIndex;
	arch>>nBeginIndex;

	BOOL bIsMenuSet;
	arch>>bIsMenuSet;

	int nScreenModel;
	arch>>nScreenModel;

	int nScale;
	arch>>nScale;


	p->SetScreenCountH(nScreenCountH);
	p->SetScreenCountV(nScreenCountV);
	p->SetResolutionH(nResolutionH);
	p->SetResolutionV(nResolutionV);
	p->SetRightResulationH(nRightResulationH);
	p->SetBottomResulationV(nBottomResulationV);
	p->SetBeginIndex(nBeginIndex);
	p->SetIsMenuSet(bIsMenuSet);
	p->SetScreenModel(nScreenModel);
	//p->SetMultiScale(nScale);
	p->SetCurScale(nScale);


	p->GetScreenMoveInfo()->GetData(arch);
	p->GetTimedPollingInfo()->GetData(arch);
	p->GetAllResulationInfo()->GetData(arch);
	p->GetResulationHCutInfo()->GetData(arch);
	p->GetResulationVCutInfo()->GetData(arch);
	p->GetOldOrderInfo()->GetData(arch);
	p->GetMenuScreenSetInfo()->GetData(arch);

	//////////////////////////////////////////////////////////////////////////
	MAP_ROWINFO& MapRowInfo=p->GetMapRowInfo();
	//p->ClearRowInfo();
	int nRowSize=0;
	arch>>nRowSize;
	for(int i=0;i<nRowSize;i++)
	{
		int nRow=0;
		arch>>nRow;

		XScreenRowInfo* pInfo=new XScreenRowInfo;

		float nHeight=0;
		arch>>nHeight;

		int nRV=0;
		arch>>nRV;

		pInfo->SetScreenHeight(nHeight);
		pInfo->SetResoluationV(nRV);
		MapRowInfo.insert(std::pair<int,XScreenRowInfo*>(nRow,pInfo));
	}

	MAP_COLINFO& MapColInfo=p->GetMapColInfo();
	//p->ClearColInfo();
	int nColSize=0;
	arch>>nColSize;
	for(int i=0;i<nColSize;i++)
	{
		int nCol=0;
		arch>>nCol;

		XScreenColInfo* pInfo=new XScreenColInfo;

		float nWidth=0;
		arch>>nWidth;

		int nH=0;
		arch>>nH;

		pInfo->SetScreenWidth(nWidth);
		pInfo->SetResoluationH(nH);

		MapColInfo.insert(std::pair<int,XScreenColInfo*>(nCol,pInfo));
	}

	//////////////////////////////////////////////////////////////////////////

	GetDataOfVecScreen(p, arch);
}

void XDataScreenManage::GetDataOfVecScreen(XScreenManage* p, CArchive& arch)
{
	p->ClearVecScreen();

	VEC_SCREEN& VecScreen = p->GetVecScreen();

	unsigned int nCount;
	arch>>nCount;

	for (unsigned int i = 0; i < nCount; i++)
	{
		XScreen* pScreen = new XScreen;

		pScreen->SetManage(p);

		GetDataOfScreen(pScreen, arch);

		VecScreen.push_back(pScreen);
	}
}

void XDataScreenManage::GetDataOfScreen(XScreen* p, CArchive& arch)
{
	p->GetResulationInfo()->GetData(arch);

	int nIndex;
	arch>>nIndex;

	CString szScreenName;
	arch>>szScreenName;

	int nBoardIndex;
	arch>>nBoardIndex;

	BOOL bIsTwoSignal;
	arch>>bIsTwoSignal;

	int nMaxSignalInScreen;
	arch>>nMaxSignalInScreen;

	int nNumOfTwo;
	arch>>nNumOfTwo;

	int nScreenHdpi=0;
	arch>>nScreenHdpi;

	int nScreenVdpi=0;
	arch>>nScreenVdpi;

	int nRow=0;
	arch>>nRow;

	int nCol=0;
	arch>>nCol;


	RECTF rect;
	arch>>rect.X
		>>rect.Y
		>>rect.Width
		>>rect.Height;

	p->SetIndex(nIndex);
	p->SetScreenName(szScreenName);
	p->SetBoardIndex(nBoardIndex);
	p->SetIsTwoSignal(bIsTwoSignal);
	p->SetMaxSignalNumInScreen(nMaxSignalInScreen);
	p->SetNumOfTwoScreen(nNumOfTwo);
	p->SetScreenHdpi(nScreenHdpi);
	p->SetScreenVdpi(nScreenVdpi);
	p->SetScreenRow(nRow);
	p->SetScreenCol(nCol);

	p->SetRect(rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL XDataScreenManage::SaveData(XScreenManage* p, CString szPath)
{
	CFile mFile;

	if (mFile.Open(szPath, CFile::modeCreate|CFile::modeWrite))
	{
		CArchive arch(&mFile, CArchive::store);

		SaveData(p, arch);

		arch.Close();

		mFile.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XDataScreenManage::SaveData(XScreenManage* p, CArchive& arch)
{
	arch<<SM_DATAVERSION
		<<p->GetScreenCountH()
		<<p->GetScreenCountV()
		<<p->GetResolutionH()
		<<p->GetResolutionV()
		<<p->GetRightResulationH()
		<<p->GetBottomResulationV()
		<<p->GetBeginIndex()
		<<p->GetIsMenuSet()
		<<p->GetScreenModel()
		<<p->GetCurScale();

	p->GetScreenMoveInfo()->SaveData(arch);
	p->GetTimedPollingInfo()->SaveData(arch);
	p->GetAllResulationInfo()->SaveData(arch);
	p->GetResulationHCutInfo()->SaveData(arch);
	p->GetResulationVCutInfo()->SaveData(arch);
	p->GetOldOrderInfo()->SaveData(arch);
	p->GetMenuScreenSetInfo()->SaveData(arch);
	//p->GetAllResulationInfo()
	//////////////////////////////////////////////////////////////////////////
	//屏幕行列信息
	MAP_ROWINFO& MapRowInfo=p->GetMapRowInfo();
	arch<<MapRowInfo.size();
	for(auto iter=MapRowInfo.begin();iter!=MapRowInfo.end();++iter)
	{
		arch<<iter->first;

		XScreenRowInfo* pInfo=iter->second;
		arch<<pInfo->GetScreenHeight();
		arch<<pInfo->GetResoluationV();
	}

	MAP_COLINFO& MapColInfo=p->GetMapColInfo();
	arch<<MapColInfo.size();
	for(auto iter=MapColInfo.begin();iter!=MapColInfo.end();++iter)
	{
		arch<<iter->first;

		XScreenColInfo* pInfo=iter->second;
		arch<<pInfo->GetScreenWidth();
		arch<<pInfo->GetResoluationH();
	}
	//////////////////////////////////////////////////////////////////////////

	
	//******************************************
	VEC_SCREEN& VecScreen=p->GetVecScreen();
	arch<<VecScreen.size();

	for(VEC_SCREEN::iterator iter = VecScreen.begin(); iter != VecScreen.end(); iter++)
	{
		XScreen* pScreen=*iter;

		SaveDataOfScreen(pScreen, arch);
	}
	//******************************************
}


void XDataScreenManage::SaveDataOfScreen(XScreen* p, CArchive& arch)
{
	p->GetResulationInfo()->SaveData(arch);

	arch<<p->GetIndex()
		<<p->GetScreenName()
		<<p->GetBoardIndex()
		<<p->GetIsTwoSignal()
		<<p->GetMaxSignalNumInScreen()
		<<p->GetNumOfTwoScreen()
		<<p->GetScreenHdpi()
		<<p->GetScreenVdpi()
		<<p->GetScreenRow()
		<<p->GetScreenCol()
		<<p->GetRect().X
		<<p->GetRect().Y
		<<p->GetRect().Width
		<<p->GetRect().Height;
}