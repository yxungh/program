#include "stdafx.h"
#include "XBitRateInfo.h"


XBitRateInfo::XBitRateInfo()
{
	m_nMainDpi1=0;
	m_nMainBitRate1=0;
	m_nSubDpi1=0;
	m_nSubBitRate1=0;
	m_nMainDpi2=0;
	m_nMainBitRate2=0;
	m_nSubDpi2=0;
	m_nSubBitRate2=0;
	m_nMainDpi3=0;
	m_nMainBitRate3=0;
	m_nSubDpi3=0;
	m_nSubBitRate3=0;
	m_nMainDpi4=0;
	m_nMainBitRate4=0;
	m_nSubDpi4=0;
	m_nSubBitRate4=0;
	m_nChenal=0;
	m_nFlag1=0;
	m_nFlag2=0;
	m_nFlag3=0;
	m_nFlag4=0;
}

XBitRateInfo::~XBitRateInfo()
{

}

void XBitRateInfo::SetMainDpi1(int n)
{
	m_nMainDpi1=n;
}
int XBitRateInfo::GetMainDpi1()
{
	return m_nMainDpi1;
}
void XBitRateInfo::SetMainBitRate1(int n)
{
	m_nMainBitRate1=n;
}
int XBitRateInfo::GetMainBitRate1()
{
	return m_nMainBitRate1;
}
void XBitRateInfo::SetSubDpi1(int n)
{
	m_nSubDpi1=n;
}
int XBitRateInfo::GetSubDpi1()
{
	return m_nSubDpi1;
}
void XBitRateInfo::SetSubBitRate1(int n)
{
	m_nSubBitRate1=n;
}
int XBitRateInfo::GetSubBitRate1()
{
	return m_nSubBitRate1;
}

void XBitRateInfo::SetMainDpi2(int n)
{
	m_nMainDpi2=n;
}
int XBitRateInfo::GetMainDpi2()
{
	return m_nMainDpi2;
}
void XBitRateInfo::SetMainBitRate2(int n)
{
	m_nMainBitRate2=n;
}
int XBitRateInfo::GetMainBitRate2()
{
	return m_nMainBitRate2;
}
void XBitRateInfo::SetSubDpi2(int n)
{
	m_nSubDpi2=n;
}
int XBitRateInfo::GetSubDpi2()
{
	return m_nSubDpi2;
}
void XBitRateInfo::SetSubBitRate2(int n)
{
	m_nSubBitRate2=n;
}
int XBitRateInfo::GetSubBitRate2()
{
	return m_nSubBitRate2;
}

void XBitRateInfo::SetMainDpi3(int n)
{
	m_nMainDpi3=n;
}
int XBitRateInfo::GetMainDpi3()
{
	return m_nMainDpi3;
}
void XBitRateInfo::SetMainBitRate3(int n)
{
	m_nMainBitRate3=n;
}
int XBitRateInfo::GetMainBitRate3()
{
	return m_nMainBitRate3;
}
void XBitRateInfo::SetSubDpi3(int n)
{
	m_nSubDpi3=n;
}
int XBitRateInfo::GetSubDpi3()
{
	return m_nSubDpi3;
}
void XBitRateInfo::SetSubBitRate3(int n)
{
	m_nSubBitRate3=n;
}
int XBitRateInfo::GetSubBitRate3()
{
	return m_nSubBitRate3;
}

void XBitRateInfo::SetMainDpi4(int n)
{
	m_nMainDpi4=n;
}
int XBitRateInfo::GetMainDpi4()
{
	return m_nMainDpi4;
}
void XBitRateInfo::SetMainBitRate4(int n)
{
	m_nMainBitRate4=n;
}
int XBitRateInfo::GetMainBitRate4()
{
	return m_nMainBitRate4;
}
void XBitRateInfo::SetSubDpi4(int n)
{
	m_nSubDpi4=n;
}
int XBitRateInfo::GetSubDpi4()
{
	return m_nSubDpi4;
}
void XBitRateInfo::SetSubBitRate4(int n)
{
	m_nSubBitRate4=n;
}
int XBitRateInfo::GetSubBitRate4()
{
	return m_nSubBitRate4;
}

void XBitRateInfo::SetChenal(int n)
{
	m_nChenal=n;
}

int XBitRateInfo::GetChenal()
{
	return m_nChenal;
}

int XBitRateInfo::GetFlag1()
{
	return m_nFlag1;
}
void XBitRateInfo::SetFlag1(int n)
{
	m_nFlag1=n;
}
int XBitRateInfo::GetFlag2()
{
	return m_nFlag2;
}
void XBitRateInfo::SetFlag2(int n)
{
	m_nFlag2=n;
}
int XBitRateInfo::GetFlag3()
{
	return m_nFlag3;
}
void XBitRateInfo::SetFlag3(int n)
{
	m_nFlag3=n;
}
int XBitRateInfo::GetFlag4()
{
	return m_nFlag4;
}
void XBitRateInfo::SetFlag4(int n)
{
	m_nFlag4=n;
}

void XBitRateInfo::GetData(CArchive& arch)
{
	arch>>m_nChenal
		>>m_nMainDpi1
		>>m_nMainBitRate1
		>>m_nMainDpi2
		>>m_nMainBitRate2
		>>m_nMainDpi3
		>>m_nMainBitRate3
		>>m_nMainDpi4
		>>m_nMainBitRate4
		>>m_nSubDpi1
		>>m_nSubBitRate1
		>>m_nSubDpi2
		>>m_nSubBitRate2
		>>m_nSubDpi3
		>>m_nSubBitRate3
		>>m_nSubDpi4
		>>m_nSubBitRate4;
}

void XBitRateInfo::SaveData(CArchive& arch)
{
	arch<<m_nChenal
		<<m_nMainDpi1
		<<m_nMainBitRate1
		<<m_nMainDpi2
		<<m_nMainBitRate2
		<<m_nMainDpi3
		<<m_nMainBitRate3
		<<m_nMainDpi4
		<<m_nMainBitRate4
		<<m_nSubDpi1
		<<m_nSubBitRate1
		<<m_nSubDpi2
		<<m_nSubBitRate2
		<<m_nSubDpi3
		<<m_nSubBitRate3
		<<m_nSubDpi4
		<<m_nSubBitRate4;
}