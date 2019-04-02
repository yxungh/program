#include "StdAfx.h"
#include "XDataVideoPreviewPane.h"
#include "XVideoPreviewPane.h"
#include "XVideoPreviewFrame.h"
#include "XDeviceInfo.h"

XDataVideoPreviewPane::XDataVideoPreviewPane(void)
{
}


XDataVideoPreviewPane::~XDataVideoPreviewPane(void)
{
}

void XDataVideoPreviewPane::GetData(XVideoPreviewPane* pPane, CArchive& arch)
{
	int nVersion;
	arch>>nVersion;

	switch(nVersion)
	{
	case 1:
		{
			GetDataOfVersion1(pPane, arch);
		}
		break;
	default:
		break;
	}
}

void XDataVideoPreviewPane::GetDataOfVersion1(XVideoPreviewPane* pPane, CArchive& arch)
{
	GetVecFrame(pPane,arch);
}

void XDataVideoPreviewPane::GetVecFrame(XVideoPreviewPane* pPane, CArchive& arch)
{
	//pPane->ClearVecFrame();

	VEC_VIDEOPREVIEWFRAME& VecFrame=pPane->GetVecFrame();

	int nFrameCount;
	arch>>nFrameCount;

	for(int i=0;i<nFrameCount;i++)
	{
		int nIndex=0;
		arch>>nIndex;
		
		int nBoardIndex=0;
		arch>>nBoardIndex;

		int nFrameIndex=0;
		arch>>nFrameIndex;

		CString szInputName=_T("");
		arch>>szInputName;

		CString szRTSPAddr=_T("");
		arch>>szRTSPAddr;

		CString szIP=_T("");
		arch>>szIP;

		CString szUseName=_T("");
		arch>>szUseName;

		CString szPassWd=_T("");
		arch>>szPassWd;

		BOOL bIsUltra=FALSE;
		arch>>bIsUltra;

		BOOL bIsHaveSignal=FALSE;
		arch>>bIsHaveSignal;

		BOOL bIsHavePane=FALSE;
		arch>>bIsHavePane;

		/////////////////////////////////////////////
		XVideoPreviewFrame* pFrame=new XVideoPreviewFrame;
		pFrame->SetPane(pPane);
		pFrame->SetIndex(nIndex);
		pFrame->SetPreviewBoardIndex(nBoardIndex);
		pFrame->SetFrameIndex(nFrameIndex);
		pFrame->SetAnotherName(szInputName);
		pFrame->SetRTSPAddr(szRTSPAddr);
		pFrame->SetIP(szIP);
		pFrame->SetUseName(szUseName);
		pFrame->SetPassWd(szPassWd);
		pFrame->SetIsUltra(bIsUltra);
		pFrame->SetIsHaveSignal(bIsHaveSignal);
		pFrame->SetIsHavePane(bIsHavePane);
		/////////////////////////////////////////////
		VecFrame.push_back(pFrame);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XDataVideoPreviewPane::SaveData(XVideoPreviewPane* pPane, CArchive& arch)
{
	arch<<VIDEOPREVIEWPANE_DATAVERSION;

	SaveVecFrame(pPane,arch);
}

void XDataVideoPreviewPane::SaveVecFrame(XVideoPreviewPane* pPane, CArchive& arch)
{
	VEC_VIDEOPREVIEWFRAME& VecFrame=pPane->GetVecFrame();

	arch<<VecFrame.size();

	for (VEC_VIDEOPREVIEWFRAME::iterator iter = VecFrame.begin(); iter != VecFrame.end(); iter++)
	{
		XVideoPreviewFrame* pFrame = *iter;

		arch<<pFrame->GetIndex()
			<<pFrame->GetPreviewBoardIndex()
			<<pFrame->GetFrameIndex()
			<<pFrame->GetAnotherName()
			<<pFrame->GetRTSPAddr()
			<<pFrame->GetIP()
			<<pFrame->GetUseName()
			<<pFrame->getPassWd()
			<<pFrame->GetIsUltra()
			<<pFrame->GetIsHaveSignal()
			<<pFrame->GetIsHavePane();
	}
}

