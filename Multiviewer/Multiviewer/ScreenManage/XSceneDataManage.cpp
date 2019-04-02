#include "stdafx.h"
#include "XSceneDataManage.h"
#include "XScreenManage.h"
#include "XConstantIM.h"
#include "XScreen.h"
#include "XSignal.h"
#include "XInputSignal.h"


XSceneDataManage::XSceneDataManage()
{

}

XSceneDataManage::~XSceneDataManage()
{

}

BOOL XSceneDataManage::SaveData(XScreenManage* p, CString szPath)
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

void XSceneDataManage::SaveData(XScreenManage* p, CArchive& arch)
{
	arch<<p->GetDeviceIP()
		<<p->GetDevicePort()
		<<p->GetCurScale()
		//<<p->GetInputCount()
		<<p->GetScreenCountH()
		<<p->GetScreenCountV()
		<<p->GetResolutionH()
		<<p->GetResolutionV();


	///////////////////////////////////////////////
	///////////////////////////////////////////////
	//±ðÃû
	//VEC_INPUTSIGNAL& VecInput=p->GetVecInputSignal();
	//int nSize=VecInput.size();
	//arch<<nSize;
	//for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	//{
	//	XInputSignal* pInput=*iter;

	//	arch<<pInput->GetAnotherName()
	//		<<pInput->GetInputIndex();
	//}
	///////////////////////////////////////////////
	///////////////////////////////////////////////

	SaveSceneOfVecScreen(p, arch);
}

void XSceneDataManage::SaveSceneOfVecScreen(XScreenManage* p, CArchive& arch)
{
	VEC_SCREEN& VecScreen = p->GetVecScreen();

	arch<<VecScreen.size();

	for (VEC_SCREEN::iterator iter = VecScreen.begin(); iter != VecScreen.end(); iter++)
	{
		SaveSceneOfScreen(*iter, arch);
	}
}

void XSceneDataManage::SaveSceneOfScreen(XScreen* p, CArchive& arch)
{
	arch<<p->GetIndex()
		<<p->GetScreenName()
		<<p->GetBoardIndex()
		<<p->GetIsTwoSignal()
		<<p->GetMaxSignalNumInScreen()
		<<p->GetNumOfTwoScreen()
		<<p->GetScreenHdpi()
		<<p->GetScreenVdpi()
		<<p->GetRect().X
		<<p->GetRect().Y
		<<p->GetRect().Width
		<<p->GetRect().Height;

	SaveSceneOfVecSignal(p, arch);
}

void XSceneDataManage::SaveSceneOfVecSignal(XScreen* p, CArchive& arch)
{
	VEC_SIGNAL& VecSignal=p->GetVecSignal();

	arch<<VecSignal.size();

	for (VEC_SIGNAL::iterator iter = VecSignal.begin(); iter != VecSignal.end(); iter++)
	{
		SaveSceneOfSignal(*iter, arch);
	}
}

void XSceneDataManage::SaveSceneOfSignal(XSignal* p, CArchive& arch)
{
	arch<<p->GetSignalID()
		<<p->GetSignalGroupID()
		<<p->GetSignalLevel()
		<<p->GetIsUltra()
		<<p->GetInputIndex()
		<<p->GetSignalHdpi()
		<<p->GetSignalVdpi()
		<<p->GetRect().X
		<<p->GetRect().Y
		<<p->GetRect().Width
		<<p->GetRect().Height
		<<p->GetAnotherName()
		<<p->GetExpandInfo()->GetExpandX1()
		<<p->GetExpandInfo()->GetExpandX2()
		<<p->GetExpandInfo()->GetExpandY1()
		<<p->GetExpandInfo()->GetExpandY2();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BOOL XSceneDataManage::GetData(XScreenManage* p, CString szPath)
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

	return TRUE;
}

void XSceneDataManage::GetData(XScreenManage* p, CArchive& arch)
{
	CString strIP;
	arch>>strIP;
	p->SetDeviceIP(strIP);

	int nPort=0;
	arch>>nPort;
	p->SetDevicePort(nPort);

	int nScale=0;
	arch>>nScale;
	p->SetCurScale(nScale);

	//int nInputCount=0;
	//arch>>nInputCount;
	//p->SetInputCount(nInputCount);

	int nScreenCountH=0;
	arch>>nScreenCountH;
	p->SetScreenCountH(nScreenCountH);

	int nScreenCountV=0;
	arch>>nScreenCountV;
	p->SetScreenCountV(nScreenCountV);

	int nResolutionH=0;
	arch>>nResolutionH;
	p->SetResolutionH(nResolutionH);

	int nResolutionV=0;
	arch>>nResolutionV;
	p->SetResolutionV(nResolutionV);

	/////////////////////////////////////////////
	/////////////////////////////////////////////
	//int nSize=0;
	//arch>>nSize;

	//VEC_INPUTSIGNAL& VecInput=p->GetVecInputSignal();
	////////////////////////////////////////////////////////////////////////////
	//for(VEC_INPUTSIGNAL::iterator iter=VecInput.begin();iter!=VecInput.end();++iter)
	//{
	//	delete *iter;
	//}

	//VecInput.clear();
	////////////////////////////////////////////////////////////////////////////

	//for(int i=0;i<nSize;i++)
	//{
	//	XInputSignal* pInput=new XInputSignal;

	//	CString szAnotherName;
	//	arch>>szAnotherName;
	//	pInput->SetAnotherName(szAnotherName);

	//	int nInputIndex;
	//	arch>>nInputIndex;
	//	pInput->SetInputIndex(nInputIndex);

	//	VecInput.push_back(pInput);
	//}
	/////////////////////////////////////////////
	/////////////////////////////////////////////

	GetVecScreen(p,arch);
}

void XSceneDataManage::GetVecScreen(XScreenManage* p,CArchive& arch)
{
	p->ClearVecScreen();

	VEC_SCREEN& VecScreen=p->GetVecScreen();

	unsigned int nCount=0;
	arch>>nCount;

	for (unsigned int i=0;i<nCount;i++)
	{
		XScreen* pScreen=new XScreen;

		pScreen->SetManage(p);

		GetSceneOfScreen(pScreen, arch);

		VecScreen.push_back(pScreen);
	}
}

void XSceneDataManage::GetSceneOfScreen(XScreen* pScreen,CArchive& arch)
{
	int nIndex=0;
	arch>>nIndex;
	pScreen->SetIndex(nIndex);

	CString szScreenName=_T("");
	arch>>szScreenName;
	pScreen->SetScreenName(szScreenName);

	int nBoardIndex;
	arch>>nBoardIndex;
	pScreen->SetBoardIndex(nBoardIndex);

	BOOL bIsTwoScreen;
	arch>>bIsTwoScreen;
	pScreen->SetIsTwoSignal(bIsTwoScreen);

	int nMaxSignal;
	arch>>nMaxSignal;
	pScreen->SetMaxSignalNumInScreen(nMaxSignal);

	int nNumOfTwo;
	arch>>nNumOfTwo;
	pScreen->SetNumOfTwoScreen(nNumOfTwo);

	int nHdpi=0;
	arch>>nHdpi;
	pScreen->SetScreenHdpi(nHdpi);

	int nVdpi=0;
	arch>>nVdpi;
	pScreen->SetScreenVdpi(nVdpi);

	//int nReHdpi=0;
	//arch>>nReHdpi;
	//pScreen->SetReScreenHdpi(nHdpi);

	//int nReVdpi=0;
	//arch>>nReVdpi;
	//pScreen->SetReScreenVdpi(nVdpi);

	RECTF rect;
	arch>>rect.X
		>>rect.Y
		>>rect.Width
		>>rect.Height;

	pScreen->SetRect(rect);

	GetSceneOfVecSignal(pScreen,arch);
}

void XSceneDataManage::GetSceneOfVecSignal(XScreen* pScreen,CArchive& arch)
{
	pScreen->ClearVecSignal();

	VEC_SIGNAL& VecSignal = pScreen->GetVecSignal();

	unsigned int nCount=0;
	arch>>nCount;

	for (unsigned int i=0;i<nCount;i++)
	{
		XSignal* pSignal = new XSignal;

		pSignal->SetScreen(pScreen);

		GetSignalOfScreen(pSignal,arch);

		VecSignal.push_back(pSignal);
	}
}

void XSceneDataManage::GetSignalOfScreen(XSignal* pSignal,CArchive& arch)
{
	unsigned int nSignalID=0;
	arch>>nSignalID;
	pSignal->SetSignalID(nSignalID);

	unsigned int nSignalGroupID=0;
	arch>>nSignalGroupID;
	pSignal->SetSignalGroupID(nSignalGroupID);

	int nLeval;
	arch>>nLeval;
	pSignal->SetSignalLevel(nLeval);

	BOOL bIsUltra;
	arch>>bIsUltra;
	pSignal->SetIsUltra(bIsUltra);

	int nSignalIndex=0;
	arch>>nSignalIndex;
	pSignal->SetInputIndex(nSignalIndex);

	int nHdpi=0;
	arch>>nHdpi;
	pSignal->SetSignalHdpi(nHdpi);

	int nVdpi=0;
	arch>>nVdpi;
	pSignal->SetSignalVdpi(nHdpi);

	RECTF rect;

	arch>>rect.X
		>>rect.Y
		>>rect.Width
		>>rect.Height;
	pSignal->SetRect(rect);

	CString szAnotherName;
	arch>>szAnotherName;
	pSignal->SetAnotherName(szAnotherName);

	unsigned short X1=0;
	arch>>X1;

	unsigned short X2=0;
	arch>>X2;

	unsigned short Y1=0;
	arch>>Y1;

	unsigned short Y2=0;
	arch>>Y2;

	pSignal->m_ExpandInfo.SetExpand(X1,X2,Y1,Y2);
}
