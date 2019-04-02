#include "stdafx.h"
#include "XResulationInfo.h"

#define RESULATIONVERSION 1

XResulationInfo::XResulationInfo()
{
	m_ResolutionH=0;
	m_ResolutionV=0;
	m_HFPorch=0;
	m_VFPorch=0;
	m_Hpixel=0;
	m_VPixel=0;
	m_HBPorch=0;
	m_VBProch=0;
	m_HSyncTime=0;
	m_VSyncTime=0;
	m_HSyncPolarity=0;
	m_VSyncPolarity=0;
	m_ComboIndex=0;
	m_ComboRefresh=0;
	m_ComboModel=0;
	m_nRefreash=0;
	m_nCurDpi=0;
}
XResulationInfo::~XResulationInfo()
{

}

int XResulationInfo::GetResolutionH()
{
	return m_ResolutionH;
}

int XResulationInfo::GetResolutionV()
{
	return m_ResolutionV;
}

int XResulationInfo::GetHFPorch()
{
	return m_HFPorch;
}

int XResulationInfo::GetVFPorch()
{
	return m_VFPorch;
}

int XResulationInfo::GetHpixel()
{
	return m_Hpixel;
}

int XResulationInfo::GetVPixel()
{
	return m_VPixel;
}

int XResulationInfo::GetHBPorch()
{
	return m_HBPorch;
}

int XResulationInfo::GetVBProch()
{
	return m_VBProch;
}

int XResulationInfo::GetHSyncTime()
{
	return m_HSyncTime;
}

int XResulationInfo::GetVSyncTime()
{
	return m_VSyncTime;
}

int XResulationInfo::GetHSyncPolarity()
{
	return m_HSyncPolarity;
}

int XResulationInfo::GetVSyncPolarity()
{
	return m_VSyncPolarity;
}

int XResulationInfo::GetComboIndex()
{
	return m_ComboIndex;
}

int XResulationInfo::GetComboRefresh()
{
	return m_ComboRefresh;
}

int XResulationInfo::GetComboModel()
{
	return m_ComboModel;
}

void XResulationInfo::SetResolutionH(int n)
{
	m_ResolutionH=n;
}
void XResulationInfo::SetResolutionV(int n)
{
	m_ResolutionV=n;
}
void XResulationInfo::SetHFPorch(int n)
{
	m_HFPorch=n;
}
void XResulationInfo::SetVFPorch(int n)
{
	m_VFPorch=n;
}
void XResulationInfo::SetHpixel(int n)
{
	m_Hpixel=n;
}
void XResulationInfo::SetVPixel(int n)
{
	m_VPixel=n;
}
void XResulationInfo::SetHBPorch(int n)
{
	m_HBPorch=n;
}
void XResulationInfo::SetVBProch(int n)
{
	m_VBProch=n;
}
void XResulationInfo::SetHSyncTime(int n)
{
	m_HSyncTime=n;
}
void XResulationInfo::SetVSyncTime(int n)
{
	m_VSyncTime=n;
}
void XResulationInfo::SetHSyncPolarity(int n)
{
	m_HSyncPolarity=n;
}
void XResulationInfo::SetVSyncPolarity(int n)
{
	m_VSyncPolarity=n;
}
void XResulationInfo::SetComboIndex(int n)
{
	m_ComboIndex=n;
}
void XResulationInfo::SetComboRefresh(int n)
{
	m_ComboRefresh=n;
}

void XResulationInfo::SetComboModel(int n)
{
	m_ComboModel=n;
}


void XResulationInfo::GetData(CArchive& arch)
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
		>>m_ComboModel;
}

void XResulationInfo::SaveData(CArchive& arch)
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
		<<m_ComboModel;
}