#include "StdAfx.h"
#include "HandleCalculate.h"

HandleCalculate::HandleCalculate(void)
{
}


HandleCalculate::~HandleCalculate(void)
{
}

CString HandleCalculate::GetIPByRTSPAddr(CString szRTSPAddr)
{
	if (_T("") == szRTSPAddr)
	{
		return _T("");
	}

	int nLen = szRTSPAddr.GetLength();

	if (nLen < 8)
	{
		return _T("");
	}

	CString nPrefix = szRTSPAddr.Mid(0, 7);
	nPrefix.MakeLower();

	if (nPrefix != _T("rtsp://"))
	{
		return _T("");
	}

	int nFirstPos = 7;

	int nPos = szRTSPAddr.Find('@', 7);

	if (nPos != -1) {

		nFirstPos = nPos + 1;
	}

	int nlastPos = nLen - 1;

	nPos = szRTSPAddr.Find(':', nFirstPos);

	if (nPos != -1) {

		nlastPos = nPos - 1;
	}
	else
	{
		nPos = szRTSPAddr.Find('/', nFirstPos);

		if (nPos != -1) {

			nlastPos = nPos - 1;
		}
	}

	CString szIP = szRTSPAddr.Mid(nFirstPos, nlastPos - nFirstPos + 1);

	return szIP;
}

BOOL HandleCalculate::DecideRTSPAddr(CString szRTSPAddr)
{
	CString szIP = GetIPByRTSPAddr(szRTSPAddr);

	if (szIP == _T(""))
	{
		return FALSE;
	}

	USES_CONVERSION;
	char* pIP = W2A(szIP);

	if (INADDR_NONE == inet_addr(pIP))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void HandleCalculate::SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, 
	CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY, CDC& dc)
{
	int nOrgX = 0;
	int nOrgY = 0;

	GetViewPortOrg(rect, noffsetX, noffsetY, size, dwScale, nDrawDistanceX, nDrawDistanceY, nOrgX, nOrgY);

	dc.SetViewportOrg(nOrgX, nOrgY);
}

void HandleCalculate::SetPreviewOrg(CRect& rect, int& noffsetX, int& noffsetY, 
	CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY,CSize& orgSize)
{
	int nOrgX = 0;
	int nOrgY = 0;

	GetViewPortOrg(rect, noffsetX, noffsetY, size, dwScale, nDrawDistanceX, nDrawDistanceY, nOrgX, nOrgY);

	orgSize.cx=nOrgX;
	orgSize.cy=nOrgY;
}

void HandleCalculate::GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,
	CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY, int& nOrgX, int& nOrgY)
{
	int nWidth = rect.Width();
	int nHeight = rect.Height();

	if (nWidth > size.cx)
	{
		nOrgX = (nWidth - size.cx) / 2;
	}
	else
	{
		nOrgX = 0;
	}

	if (nHeight > size.cy)
	{
		nOrgY = (nHeight - size.cy) / 2;
	}
	else
	{
		nOrgY = 0;
	}

	nOrgX = nOrgX - noffsetX + nDrawDistanceX;
	nOrgY = nOrgY - noffsetY + nDrawDistanceY;
}

BOOL HandleCalculate::DecideIP(CString szIP)
{
	USES_CONVERSION;
	char* pIP=W2A(szIP);

	//XP系统不支持IPV6
	//if (inet_pton(AF_INET, pIP, (void *)&addr) > 0)
	//{
	//	return TRUE;
	//}
	//else
	//{
	//	return FALSE;
	//}

	//if(inet_ntop(AF_INET,(void*)&addr,pIP,sizeof(pIP)))
	//{
	//	return TRUE;
	//}
	//else
	//{
	//	return FALSE;
	//}

	if(pIP==NULL)
		return FALSE;

	char temp[4];
	int count=0;
	while(true)
	{
		int index=0;
		while (*pIP!='\0'&&*pIP!='.'&&count<4)
		{
			temp[index++]=*pIP;
			pIP++;
		}

		if(index==4)
			return FALSE;

		temp[index]='\0';
		int num=atoi(temp);
		if(!(num>= 0&&num<=255))
			return FALSE;

		count++;
		if(*pIP=='\0')
		{
			if(count==4)
				return TRUE;
			else
				return FALSE;
		}
		else
			pIP++;
	}
}
