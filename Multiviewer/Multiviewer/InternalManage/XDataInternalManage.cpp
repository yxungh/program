#include "stdafx.h"
#include "XDataInternalManage.h"
#include "XInternalManage.h"
#include "XBaseScreenManage.h"
#include "XScreenManage.h"
#include "XSelectBoardInfo.h"
#include "XVideoPreviewPane.h"

XDataInternalManage::XDataInternalManage()
{

}

XDataInternalManage::~XDataInternalManage()
{

}

void XDataInternalManage::GetData(XInternalManage* pManage, CArchive& arch)
{
	GetVecScreenManage(pManage,arch);

	GetVecPreviewPane(pManage,arch);

	GetSelectBoardInfo(pManage,arch);

	GetPreviewTemp(pManage,arch);

	GetMapBottomTabLable(pManage,arch);
}

void XDataInternalManage::GetVecScreenManage(XInternalManage* pManage, CArchive& arch)
{
	VEC_BASESCREENMANAGE& VecBaseScreenManage=pManage->GetBaseManage();

	int nSize=0;
	arch>>nSize;


	for(int i=0;i<nSize;i++)
	{
		CString szName;
		arch>>szName;

		XBaseScreenManage* pBase=new XScreenManage;

		pBase->SetDelegate((XDelegateScreenManage*)pManage);

		pBase->SetViewName(szName);

		pBase->GetData(arch);

		VecBaseScreenManage.push_back(pBase);
	}
}

void XDataInternalManage::GetVecPreviewPane(XInternalManage* pManage, CArchive& arch)
{
	VEC_VIDEOPREVIEWPANE& VecPreviewPane=pManage->GetVecPreviewPane();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nBoardIndex=0;
		arch>>nBoardIndex;

		CString szUserName;
		arch>>szUserName;

		CString szPassWd;
		arch>>szPassWd;

		CString szIP;
		arch>>szIP;

		XVideoPreviewPane* pPane=new XVideoPreviewPane;

		pPane->SetDelegate((XDelegateVideoPreviewPane*)pManage);
		pPane->SetBoardIndex(nBoardIndex);
		pPane->SetUserName(szUserName);
		pPane->SetPassWd(szPassWd);
		pPane->SetIP(szIP);

		pPane->GetData(arch);

		VecPreviewPane.push_back(pPane);
	}
}

void XDataInternalManage::GetSelectBoardInfo(XInternalManage* pManage, CArchive& arch)
{
	MAP_SELECTBOARD& MapSelectBoard=pManage->GetMapSelectBoard();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nBoard=0;
		arch>>nBoard;

		int nIndex=0;
		arch>>nIndex;

		int nBoardIndex=0;
		arch>>nBoardIndex;

		int nSecretSel=0;
		arch>>nSecretSel;

		CString szUserName;
		arch>>szUserName;

		CString szPassWd;
		arch>>szPassWd;

		int nModelSel=0;
		arch>>nModelSel;

		CString szIP;
		arch>>szIP;

		CString szMask;
		arch>>szMask;

		CString szGateWay;
		arch>>szGateWay;

		CString szMAC;
		arch>>szMAC;

		BOOL bSelected;
		arch>>bSelected;

		//////////////////////////////////////////////////////////////////////////

		XSelectBoardInfo* pInfo=new XSelectBoardInfo;

		pInfo->SetBoardIndex(nBoardIndex);
		pInfo->SetIndex(nIndex);
		pInfo->SetSecretSel(nSecretSel);
		pInfo->SetUserName(szUserName);
		pInfo->SetPassWd(szPassWd);
		pInfo->SetModelSel(nModelSel);
		pInfo->SetIP(szIP);
		pInfo->SetMask(szMask);
		pInfo->SetGateWay(szGateWay);
		pInfo->SetMAC(szMAC);
		pInfo->SetSelected(bSelected);

		MapSelectBoard.insert(std::pair<int,XSelectBoardInfo*>(nBoard,pInfo));
	}
}

void XDataInternalManage::GetPreviewTemp(XInternalManage* pManage, CArchive& arch)
{
	MAP_PREVIEWTEMP& MapPreviewTemp=pManage->GetMapPreviewTemp();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nFirst=0;
		arch>>nFirst;

		int nSecond=0;
		arch>>nSecond;

		MapPreviewTemp.insert(std::pair<int,int>(nFirst,nSecond));
	}
}

void XDataInternalManage::GetMapBottomTabLable(XInternalManage* pManage, CArchive& arch)
{
	MAP_TABLABLE& MapBottomTabLable=pManage->GetMapBottomTabLable();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		CString szName;
		arch>>szName;

		CString szAnotherName;
		arch>>szAnotherName;

		MapBottomTabLable.insert(std::pair<CString,CString>(szName,szAnotherName));
	}
}

//////////////////////////////////////////////////////////////////////////

void XDataInternalManage::SaveData(XInternalManage* pManage, CArchive& arch)
{
	SaveVecScreenManage(pManage,arch);

	SaveVecPreviewPane(pManage,arch);

	SaveSelectBoardInfo(pManage,arch);

	SavePreviewTemp(pManage,arch);

	SaveMapBottomTabLable(pManage,arch);
}

void XDataInternalManage::SaveVecScreenManage(XInternalManage* pManage, CArchive& arch)
{
	VEC_BASESCREENMANAGE& VecBaseScreenManage=pManage->GetBaseManage();

	int nScreenManageCount=VecBaseScreenManage.size();

	arch<<nScreenManageCount;

	for(VEC_BASESCREENMANAGE::iterator iter=VecBaseScreenManage.begin();iter!=VecBaseScreenManage.end();++iter)
	{
		XBaseScreenManage* pBase=*iter;

		CString szName=pBase->GetViewName();

		arch<<szName;

		pBase->SaveData(arch);
	}
}

void XDataInternalManage::SaveVecPreviewPane(XInternalManage* pManage, CArchive& arch)
{
	VEC_VIDEOPREVIEWPANE& VecPreviewPane=pManage->GetVecPreviewPane();

	arch<<VecPreviewPane.size();

	for(VEC_VIDEOPREVIEWPANE::iterator iter=VecPreviewPane.begin();iter!=VecPreviewPane.end();++iter)
	{
		XVideoPreviewPane* pPane=*iter;
		arch<<pPane->GetBoardIndex()
			<<pPane->GetUserName()
			<<pPane->GetPassWd()
			<<pPane->GetszIP();

		pPane->SaveData(arch);
	}
}

void XDataInternalManage::SaveSelectBoardInfo(XInternalManage* pManage, CArchive& arch)
{
	MAP_SELECTBOARD& MapSelectBoard=pManage->GetMapSelectBoard();

	arch<<MapSelectBoard.size();

	for(MAP_SELECTBOARD::iterator iter=MapSelectBoard.begin();iter!=MapSelectBoard.end();++iter)
	{
		int nBoardIndex=iter->first;
		arch<<nBoardIndex;

		XSelectBoardInfo* pInfo=iter->second;
		arch<<pInfo->GetIndex()
			<<pInfo->GetBoardIndex()
			<<pInfo->GetSecretSel()
			<<pInfo->GetUserName()
			<<pInfo->GetPassWd()
			<<pInfo->GetModelSel()
			<<pInfo->GetszIP()
			<<pInfo->GetMask()
			<<pInfo->GetGateWay()
			<<pInfo->GetMAC()
			<<pInfo->GetSelected();
	}
}

void XDataInternalManage::SavePreviewTemp(XInternalManage* pManage, CArchive& arch)
{
	MAP_PREVIEWTEMP& MapPreviewTemp=pManage->GetMapPreviewTemp();

	arch<<MapPreviewTemp.size();

	for(MAP_PREVIEWTEMP::iterator iter=MapPreviewTemp.begin();iter!=MapPreviewTemp.end();++iter)
	{
		arch<<iter->first;
		arch<<iter->second;
	}
}

void XDataInternalManage::SaveMapBottomTabLable(XInternalManage* pManage, CArchive& arch)
{
	MAP_TABLABLE& MapBottomTabLable=pManage->GetMapBottomTabLable();

	arch<<MapBottomTabLable.size();

	for(MAP_TABLABLE::iterator iter=MapBottomTabLable.begin();iter!=MapBottomTabLable.end();++iter)
	{
		arch<<iter->first;
		arch<<iter->second;
	}
}