#include "stdafx.h"
#include "XResulationVCutInfo.h"

#define RESULATIONCUT_VERSION 1

XResulationVCutInfo::XResulationVCutInfo()
{
	m_nResulationV	=0;
	m_nVFront		=0;
	m_nVActive		=0;
	m_nVBack		=0;
	m_nVSyn			=0;
	m_nVPolarity	=0;
	m_nResulationIndex=-1;
	m_nResulationCut=0;
}

XResulationVCutInfo::~XResulationVCutInfo()
{

}


void XResulationVCutInfo::GetData(CArchive& arch)
{
	int Version;
	arch>>Version;

	arch>>m_nResulationIndex
		>>m_nResulationV	
		>>m_nResulationCut
		>>m_nVFront		
		>>m_nVActive		
		>>m_nVBack		
		>>m_nVSyn			
		>>m_nVPolarity;	

}

void XResulationVCutInfo::SaveData(CArchive& arch)
{
	arch<<RESULATIONCUT_VERSION
		<<m_nResulationIndex
		<<m_nResulationV
		<<m_nResulationCut
		<<m_nVFront		
		<<m_nVActive		
		<<m_nVBack		
		<<m_nVSyn			
		<<m_nVPolarity;
}