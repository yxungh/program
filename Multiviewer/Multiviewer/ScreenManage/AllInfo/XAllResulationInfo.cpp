#include "stdafx.h"
#include "XAllResulationInfo.h"

#define RESULATIONVERSION 1

XAllResulationInfo::XAllResulationInfo()
{
	m_ResolutionH=800;
	m_ResolutionV=600;
	m_HFPorch=40;
	m_VFPorch=1;
	m_Hpixel=800;
	m_VPixel=600;
	m_HBPorch=88;
	m_VBProch=23;
	m_HSyncTime=128;
	m_VSyncTime=4;
	m_HSyncPolarity=1;
	m_VSyncPolarity=1;
	m_ComboIndex=0;
	m_ComboRefresh=0;
	m_ComboModel=0;
	m_nRightCut=0;
	m_nBottomCut=0;
	m_bIsRight=FALSE;
	m_bIsBottom=FALSE;
	m_nRefreash=0;
}
XAllResulationInfo::~XAllResulationInfo()
{

}

int XAllResulationInfo::GetResolutionH()
{
	return m_ResolutionH;
}

int XAllResulationInfo::GetResolutionV()
{
	return m_ResolutionV;
}

int XAllResulationInfo::GetHFPorch()
{
	return m_HFPorch;
}

int XAllResulationInfo::GetVFPorch()
{
	return m_VFPorch;
}

int XAllResulationInfo::GetHpixel()
{
	return m_Hpixel;
}

int XAllResulationInfo::GetVPixel()
{
	return m_VPixel;
}

int XAllResulationInfo::GetHBPorch()
{
	return m_HBPorch;
}

int XAllResulationInfo::GetVBProch()
{
	return m_VBProch;
}

int XAllResulationInfo::GetHSyncTime()
{
	return m_HSyncTime;
}

int XAllResulationInfo::GetVSyncTime()
{
	return m_VSyncTime;
}

int XAllResulationInfo::GetHSyncPolarity()
{
	return m_HSyncPolarity;
}

int XAllResulationInfo::GetVSyncPolarity()
{
	return m_VSyncPolarity;
}

int XAllResulationInfo::GetComboIndex()
{
	return m_ComboIndex;
}

int XAllResulationInfo::GetComboRefresh()
{
	return m_ComboRefresh;
}

int XAllResulationInfo::GetRightCut()
{
	return m_nRightCut;
}

int XAllResulationInfo::GetBottomCut()
{
	return m_nBottomCut;
}

int XAllResulationInfo::GetComboModel()
{
	return m_ComboModel;
}

void XAllResulationInfo::SetResolutionH(int n)
{
	m_ResolutionH=n;
}
void XAllResulationInfo::SetResolutionV(int n)
{
	m_ResolutionV=n;
}
void XAllResulationInfo::SetHFPorch(int n)
{
	m_HFPorch=n;
}
void XAllResulationInfo::SetVFPorch(int n)
{
	m_VFPorch=n;
}
void XAllResulationInfo::SetHpixel(int n)
{
	m_Hpixel=n;
}
void XAllResulationInfo::SetVPixel(int n)
{
	m_VPixel=n;
}
void XAllResulationInfo::SetHBPorch(int n)
{
	m_HBPorch=n;
}
void XAllResulationInfo::SetVBProch(int n)
{
	m_VBProch=n;
}
void XAllResulationInfo::SetHSyncTime(int n)
{
	m_HSyncTime=n;
}
void XAllResulationInfo::SetVSyncTime(int n)
{
	m_VSyncTime=n;
}
void XAllResulationInfo::SetHSyncPolarity(int n)
{
	m_HSyncPolarity=n;
}
void XAllResulationInfo::SetVSyncPolarity(int n)
{
	m_VSyncPolarity=n;
}
void XAllResulationInfo::SetComboIndex(int n)
{
	m_ComboIndex=n;
}
void XAllResulationInfo::SetComboRefresh(int n)
{
	m_ComboRefresh=n;
}

void XAllResulationInfo::SetRightCut(int n)
{
	m_nRightCut=n;
}

void XAllResulationInfo::SetBottomCut(int n)
{
	m_nBottomCut=n;
}

void XAllResulationInfo::SetComboModel(int n)
{
	m_ComboModel=n;
}

void XAllResulationInfo::GetData(CArchive& arch)
{
	int Version;
	arch>>Version;

	arch>>m_ResolutionH
		>>m_ResolutionV
		>>m_HFPorch
		>>m_VFPorch
		>>m_Hpixel
		>>m_VPixel
		>>m_HBPorch
		>>m_VBProch
		>>m_HSyncTime
		>>m_VSyncTime
		>>m_HSyncPolarity
		>>m_VSyncPolarity
		>>m_ComboIndex
		>>m_ComboRefresh
		>>m_ComboModel
		>>m_nRightCut
		>>m_nBottomCut
		>>m_bIsRight
		>>m_bIsBottom;
}

void XAllResulationInfo::SaveData(CArchive& arch)
{
	arch<<RESULATIONVERSION
		<<m_ResolutionH
		<<m_ResolutionV
		<<m_HFPorch
		<<m_VFPorch
		<<m_Hpixel
		<<m_VPixel
		<<m_HBPorch
		<<m_VBProch
		<<m_HSyncTime
		<<m_VSyncTime
		<<m_HSyncPolarity
		<<m_VSyncPolarity
		<<m_ComboIndex
		<<m_ComboRefresh
		<<m_ComboModel
		<<m_nRightCut
		<<m_nBottomCut
		<<m_bIsRight
		<<m_bIsBottom;
}