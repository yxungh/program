#include "Stdafx.h"
#include "XResulationHCutInfo.h"

#define RESULATIONCUT_VERSION 1

XResulationHCutInfo::XResulationHCutInfo()
{
	m_nResulationH	=0;
	m_nHFront		=0;
	m_nHActive		=0;
	m_nHBack		=0;
	m_nHSyn			=0;
	m_nHPolarity	=0;
	m_nResulationIndex=-1;
	m_nResulationCut=0;
}

XResulationHCutInfo::~XResulationHCutInfo()
{

}


void XResulationHCutInfo::GetData(CArchive& arch)
{
	int Version;
	arch>>Version;

	arch>>m_nResulationIndex
		>>m_nResulationH
		>>m_nResulationCut
		>>m_nHFront
		>>m_nHActive
		>>m_nHBack
		>>m_nHSyn
		>>m_nHPolarity;

}

void XResulationHCutInfo::SaveData(CArchive& arch)
{
	arch<<RESULATIONCUT_VERSION
		<<m_nResulationIndex
		<<m_nResulationH
		<<m_nResulationCut
		<<m_nHFront
		<<m_nHActive
		<<m_nHBack
		<<m_nHSyn
		<<m_nHPolarity;
}