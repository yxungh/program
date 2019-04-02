#include "stdafx.h"
#include "HandleShearPlate.h"

HandleShearPlate::HandleShearPlate()
{

}

HandleShearPlate::~HandleShearPlate()
{

}

void HandleShearPlate::CopyOrderToSharePlate(CString szOrder)
{
	
	if(OpenClipboard(NULL)) 
	{ 
		int nLen=szOrder.GetLength();

		HGLOBAL clipbuffer; 
		char* buffer; 
		EmptyClipboard(); 
		clipbuffer=GlobalAlloc(GMEM_DDESHARE,nLen); 
		buffer=(char*)GlobalLock(clipbuffer); 


		USES_CONVERSION;
		char* p=T2A(szOrder.GetBuffer(0));
		szOrder.ReleaseBuffer();

		//strcpy(buffer,(LPSTR)(LPCTSTR)szOrder); 
		memcpy(buffer,p,nLen);

		GlobalUnlock(clipbuffer); 
		SetClipboardData(CF_TEXT,clipbuffer); 
		CloseClipboard(); 
	}
}