#include "stdafx.h"
#include "XHandleCalculate.h"


XHandleCalculate::XHandleCalculate()
{

}

XHandleCalculate::~XHandleCalculate()
{

}

CString XHandleCalculate::GetTranslationKeyFromTime()
{
	CTime time;
	time=CTime::GetCurrentTime();
	int nHour=time.GetHour();

	CString szKey=_T("");
	int nKey=0;

	CString szFrontText=_T("");
	if(nHour>=5&&nHour<=8)
		nKey=35;
	else if(nHour>8&&nHour<12)
		nKey=36;
	else if(nHour>12&&nHour<18)
		nKey=37;
	else
		nKey=38;

	szKey.Format(_T("%d"),nKey);

	return szKey;
}
