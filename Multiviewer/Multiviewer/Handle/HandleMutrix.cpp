#include "StdAfx.h"
#include "HandleMutrix.h"
#include "XOSDInfo.h"
#include "XScreenMoveInfo.h"



HandleMutrix::HandleMutrix(void)
{

}

HandleMutrix::~HandleMutrix(void)
{

}

BOOL HandleMutrix::SetOSDMutrix(CClientDC& dc, XOSDInfo* pOSDInfo, BOOL& bExceed)
{
	CFont font;
	if (!CreateOSDFont(pOSDInfo, font))
	{
		return FALSE;
	}

	CFont* pOldFont = dc.SelectObject(&font);

	TEXTMETRIC tm;
	if(0 == dc.GetTextMetrics(&tm))
	{
		return FALSE;
	}

	CString szText = pOSDInfo->GetText();

	int nTextLen = szText.GetLength();

	int nX = 0;

	int nY = 0;

	//*******************
	int nMaxX=0;
	//*******************

	BOOL bExceedWidth = FALSE;

	BOOL bResult = TRUE;

	for (int i = 0; i < nTextLen; i++)
	{
		TCHAR c = szText.GetAt(i);

		if (bExceedWidth)
		{
			if (c == '\n')
			{
				bExceedWidth = FALSE;
			}
			else
			{
				continue;
			}
		}

		if (c == '\r')
		{
			continue;
		}

		if (c == '\n')
		{		
			nX = 0;

			nY += pOSDInfo->GetTextSize();

			continue;
		}

		int nResult = SetOSDTextMatrixData(pOSDInfo, nX, nY, c, tm, dc);
		
		if (nX>nMaxX)
		{
			nMaxX=nX;
		}

		if (0 == nResult)
		{
			bResult = FALSE;

			break;
		}
		else if (-1 == nResult)
		{
			bExceedWidth = TRUE;

			bExceed = TRUE;
		}
		else if (-2 == nResult)
		{
			bExceed = TRUE;

			break;
		}
	}
	int nMaxY=nY + pOSDInfo->GetTextSize();

	if(pOSDInfo->GetCenterType()==1)
	{
		CenterMutrixData(pOSDInfo, nMaxX, nMaxY);
	}

	dc.SelectObject(pOldFont);

	return bResult;
}

void HandleMutrix::CenterMutrixData(XOSDInfo* pOSDInfo,int& nMaxX,int& nMaxY)
{
	int nWidth=pOSDInfo->GetWidth();

	int nHight=pOSDInfo->GetHeight();

	if(nMaxX>nWidth)
	{
		nMaxX=nWidth;
	}
	if(nMaxY>nHight)
	{
		nMaxY=nHight;
	}

	if(nMaxX==0||nMaxY==0)
	{
		return;
	}

	int nMutrixDataLen=pOSDInfo->GetMutrixDataLen();

	char* pMutrixData = new char[nMutrixDataLen];
	ZeroMemory(pMutrixData, nMutrixDataLen);

	int nCenterX=(nWidth-nMaxX)/2;

	int nCenterY=(nHight-nMaxY)/2;

	for (int i = 0; i < nMaxY; i++)
	{
		char* pOldRowData = pOSDInfo->GetMutrixData()+i*(nWidth/8);

		char* pNewRowData=pMutrixData+(nCenterY + i)*(nWidth/8);

		for (int j = 0; j < nMaxX; j++)
		{
			int nOldPos = j;

			int nOldPosByte = nOldPos / 8;

			int nOldPosBit = nOldPos % 8;

			char* pOldData = (pOldRowData + nOldPosByte);
			/////////////////////////////////////////
			int nPos = nCenterX + j;

			int nPosByte = nPos / 8;

			int nPosBit = nPos % 8;

			char* pData = (pNewRowData + nPosByte);
			////////////////////////////////////////////
			*pData = (*pData) | (((((*pOldData) & (0x80>>nOldPosBit))>>(7 - nOldPosBit)))<<(7 - nPosBit));

		}
	}

	pOSDInfo->reSetData(pMutrixData);

}

BOOL HandleMutrix::CreateOSDFont(XOSDInfo* pOSDInfo, CFont& font)
{                                    
	return font.CreateFont(
		pOSDInfo->GetTextSize(),    // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH|FF_SWISS,		// nPitchAndFamily
		pOSDInfo->GetFont());      // lpszFacename
}

BOOL HandleMutrix::GetTextMutrix(CClientDC& dc, GLYPHMETRICS& glyph, TCHAR c, 
	unsigned char*& pTextMutrix)
{
	MAT2 m2; 
	memset(&m2, 0, sizeof(MAT2));
	m2.eM11.value = 1;
	m2.eM22.value = 1; 

	BOOL bResult = FALSE;

	DWORD dwNeedByte = dc.GetGlyphOutline(c, GGO_BITMAP, &glyph, 0, NULL, &m2);

	if(dwNeedByte > 0)
	{
		pTextMutrix = new BYTE[dwNeedByte];

		if(NULL != pTextMutrix)
		{
			//输出位图GGO_BITMAP 的信息。输出信息4字节（DWORD）对齐
			if(-1 != dc.GetGlyphOutline(c, GGO_BITMAP, &glyph, dwNeedByte, pTextMutrix, &m2))
			{
				bResult = TRUE;
			}
		}
	}
	else if (dwNeedByte == 0)//空格为0
	{
		bResult = TRUE;
	}

	return bResult;
}

void HandleMutrix::ShowTextMatrixData(TCHAR c, unsigned char* pTextMutrix, GLYPHMETRICS& glyph,
	XOSDInfo* pOSDInfo)
{
	int FontWidth = ((glyph.gmBlackBoxX + 31) >> 5) << 2;

	CString szShowData = _T("");

	szShowData.Format(_T("%c,W:%d,H:%d\r\n"), c, glyph.gmBlackBoxX, glyph.gmBlackBoxY);

	for (UINT i = 0; i < glyph.gmBlackBoxY; i++)
	{
		for (UINT j = 0; j < glyph.gmBlackBoxX; j++)
		{
			//一个字节有8位,一个位代表1个点
			char btCode = pTextMutrix[i * FontWidth + j / 8];

			int nPos = j%8;

			if (btCode & (0x80>>nPos))
			{
				szShowData += _T("1");
			}
			else
			{
				szShowData += _T("0");
			}

			szShowData += _T(" ");
		}

		szShowData += _T("\r\n");
	}

	AfxMessageBox(szShowData);
}

BOOL HandleMutrix::FillTextMatrixDataToOSD(XOSDInfo* pOSDInfo, int nX, int nY, 
	unsigned char* pTextMutrix, GLYPHMETRICS& glyph, TEXTMETRIC& tm)
{
	int nOSDWidth = pOSDInfo->GetWidth();

	int nOSDHeight = pOSDInfo->GetHeight();

	if ((nX + glyph.gmCellIncX) > nOSDWidth)
	{
		return -1;
	}

	if ((nY + pOSDInfo->GetTextSize()) > nOSDHeight)
	{
		return -2;
	}

	int FontWidth = ((glyph.gmBlackBoxX + 31) >> 5) << 2;

	int nFontOffY = tm.tmAscent - glyph.gmptGlyphOrigin.y;

	int nFontOffX = glyph.gmptGlyphOrigin.x < 0 ? 0 : glyph.gmptGlyphOrigin.x;

	int nBeginX = nX + nFontOffX;

	int nTempX = nBeginX;

	int nTempY = nY + nFontOffY;

	char* pMutrixData = pOSDInfo->GetMutrixData();

	for (UINT i = 0; i < glyph.gmBlackBoxY; i++)
	{
		nTempX = nBeginX;

		//定位到行首字节
		char* pMutrixRow = pMutrixData + ((nTempY + i) * (nOSDWidth/8));

		for (UINT j = 0; j < glyph.gmBlackBoxX; j++)
		{
			//定位到行列字节
			char* pMutrixColumn = pMutrixRow + (nTempX + j)/8;

			//定位文字字模数据
			char cTextMutrix = pTextMutrix[i * FontWidth + j / 8];

			if (cTextMutrix & (0x80>>(j%8)))
			{
				int nMutrixPos = (nTempX + j)%8;

				*pMutrixColumn = *pMutrixColumn | (0x80>>nMutrixPos);
			}
		}
	}

	return 1;
}

int HandleMutrix::SetOSDTextMatrixData(XOSDInfo* pOSDInfo, int& nX, int& nY, 
	TCHAR c, TEXTMETRIC& tm, CClientDC& dc)
{
	unsigned char* pTextMutrix = NULL;

	GLYPHMETRICS glyph;

	int nResult = 1;

	if (GetTextMutrix(dc, glyph, c, pTextMutrix))
	{
		//ShowTextMatrixData(c, pTextMutrix, glyph, pOSDInfo);

		if (NULL == pTextMutrix)
		{
			nX += glyph.gmCellIncX;
		}
		else
		{
			nResult = FillTextMatrixDataToOSD(pOSDInfo, nX, nY, pTextMutrix, glyph, tm);

			if (1 == nResult)
			{
				nX += glyph.gmCellIncX;
			}
		}
	}
	else
	{
		nResult = 0;
	}

	if (NULL != pTextMutrix)
	{
		delete[] pTextMutrix;
	}

	return nResult;
}

///////////////////////////////////////////////

BOOL HandleMutrix::SetScreenMoveMutrix(CClientDC& dc, XScreenMoveInfo* pMoveInfo, BOOL& bExceed)
{
	CFont font;
	if (!CreateScreenMoveFont(pMoveInfo, font))
	{
		return FALSE;
	}

	CFont* pOldFont = dc.SelectObject(&font);

	TEXTMETRIC tm;
	if(0 == dc.GetTextMetrics(&tm))
	{
		return FALSE;
	}

	CString szText = pMoveInfo->GetText();

	int nTextLen = szText.GetLength();

	int nX = 0;

	int nY = 0;

	//*******************
	int nMaxX=0;
	//*******************

	BOOL bExceedWidth = FALSE;

	BOOL bResult = TRUE;

	for (int i = 0; i < nTextLen; i++)
	{
		TCHAR c = szText.GetAt(i);

		if (bExceedWidth)
		{
			if (c == '\n')
			{
				bExceedWidth = FALSE;
			}
			else
			{
				continue;
			}
		}

		if (c == '\r')
		{
			continue;
		}

		if (c == '\n')
		{
			nX = 0;

			nY += pMoveInfo->GetFontSize();

			continue;
		}

		int nResult = SetScreenMoveTextMatrixData(pMoveInfo, nX, nY, c, tm, dc);

		if (nX>nMaxX)
		{
			nMaxX=nX;
		}

		if (0 == nResult)
		{
			bResult = FALSE;

			break;
		}
		else if (-1 == nResult)
		{
			bExceedWidth = TRUE;

			bExceed = TRUE;
		}
		else if (-2 == nResult)
		{
			bExceed = TRUE;

			break;
		}
	}

	int nMaxY=nY + pMoveInfo->GetFontSize();

	if(pMoveInfo->GetCenter()==1)
	{
		CenterMoveMutrixData(pMoveInfo, nMaxX, nMaxY);
	}

	dc.SelectObject(pOldFont);

	return bResult;
}

void HandleMutrix::CenterMoveMutrixData(XScreenMoveInfo* pMoveInfo,int& nMaxX,int& nMaxY)
{
	int nWidth=pMoveInfo->GetWidth();

	int nHight=pMoveInfo->GetHight();

	if(nMaxX>nWidth)
	{
		nMaxX=nWidth;
	}
	if(nMaxY>nHight)
	{
		nMaxY=nHight;
	}

	if(nMaxX==0||nMaxY==0)
	{
		return;
	}

	int nMutrixDataLen=pMoveInfo->GetMutrixDataLen();

	char* pMutrixData = new char[nMutrixDataLen];
	ZeroMemory(pMutrixData, nMutrixDataLen);

	int nCenterX=(nWidth-nMaxX)/2;

	int nCenterY=(nHight-nMaxY)/2;

	for (int i = 0; i < nMaxY; i++)
	{
		char* pOldRowData = pMoveInfo->GetMutrixData()+i*(nWidth/8);

		char* pNewRowData=pMutrixData+(nCenterY + i)*(nWidth/8);

		for (int j = 0; j < nMaxX; j++)
		{
			int nOldPos = j;

			int nOldPosByte = nOldPos / 8;

			int nOldPosBit = nOldPos % 8;

			char* pOldData = (pOldRowData + nOldPosByte);
			/////////////////////////////////////////
			int nPos = nCenterX + j;

			int nPosByte = nPos / 8;

			int nPosBit = nPos % 8;

			char* pData = (pNewRowData + nPosByte);
			////////////////////////////////////////////
			*pData = (*pData) | (((((*pOldData) & (0x80>>nOldPosBit))>>(7 - nOldPosBit)))<<(7 - nPosBit));

		}
	}

	pMoveInfo->reSetData(pMutrixData);
}

BOOL HandleMutrix::CreateScreenMoveFont(XScreenMoveInfo* pMoveInfo, CFont& font)
{
	return font.CreateFont(
		pMoveInfo->GetFontSize(),    // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH|FF_SWISS,		// nPitchAndFamily
		pMoveInfo->GetFont());      // lpszFacename
}

void HandleMutrix::ShowScreenMoveTextMatrixData(TCHAR c, unsigned char* pTextMutrix, GLYPHMETRICS& glyph, 
	XScreenMoveInfo* pMoveInfo)
{
	int FontWidth = ((glyph.gmBlackBoxX + 31) >> 5) << 2;

	CString szShowData = _T("");

	szShowData.Format(_T("%c,W:%d,H:%d\r\n"), c, glyph.gmBlackBoxX, glyph.gmBlackBoxY);

	for (UINT i = 0; i < glyph.gmBlackBoxY; i++)
	{
		for (UINT j = 0; j < glyph.gmBlackBoxX; j++)
		{
			//一个字节有8位,一个位代表1个点
			char btCode = pTextMutrix[i * FontWidth + j / 8];

			int nPos = j%8;

			if (btCode & (0x80>>nPos))
			{
				szShowData += _T("1");
			}
			else
			{
				szShowData += _T("0");
			}

			szShowData += _T(" ");
		}

		szShowData += _T("\r\n");
	}

	AfxMessageBox(szShowData);
}

int HandleMutrix::SetScreenMoveTextMatrixData(XScreenMoveInfo* pMoveInfo, int& nX, int& nY, 
	TCHAR c, TEXTMETRIC& tm, CClientDC& dc)
{
	unsigned char* pTextMutrix = NULL;

	GLYPHMETRICS glyph;

	int nResult = 1;

	if (GetTextMutrix(dc, glyph, c, pTextMutrix))
	{
		if (NULL == pTextMutrix)
		{
			nX += glyph.gmCellIncX;
		}
		else
		{
			nResult = FillTextMatrixDataToScreenMove(pMoveInfo, nX, nY, pTextMutrix, glyph, tm);

			if (1 == nResult)
			{
				nX += glyph.gmCellIncX;
			}
		}
	}
	else
	{
		nResult = 0;
	}

	if (NULL != pTextMutrix)
	{
		delete[] pTextMutrix;
	}

	return nResult;
}

int HandleMutrix::FillTextMatrixDataToScreenMove(XScreenMoveInfo* pMoveInfo, int nX, int nY, 
	unsigned char* pTextMutrix, GLYPHMETRICS& glyph, TEXTMETRIC& tm)
{
	int nScreenMoveWidth = pMoveInfo->GetWidth();

	int nScreenMoveHeight = pMoveInfo->GetHight();

	if ((nX + glyph.gmCellIncX) > nScreenMoveWidth)
	{
		return -1;
	}

	if ((nY + pMoveInfo->GetFontSize()) > nScreenMoveHeight)
	{
		return -2;
	}

	int FontWidth = ((glyph.gmBlackBoxX + 31) >> 5) << 2;

	int nFontOffY = tm.tmAscent - glyph.gmptGlyphOrigin.y;

	int nFontOffX = glyph.gmptGlyphOrigin.x < 0 ? 0 : glyph.gmptGlyphOrigin.x;

	int nBeginX = nX + nFontOffX;

	int nTempX = nBeginX;

	int nTempY = nY + nFontOffY;

	char* pMutrixData = pMoveInfo->GetMutrixData();

	for (UINT i = 0; i < glyph.gmBlackBoxY; i++)
	{
		nTempX = nBeginX;

		//定位到行首字节
		char* pMutrixRow = pMutrixData + ((nTempY + i) * (nScreenMoveWidth/8));

		for (UINT j = 0; j < glyph.gmBlackBoxX; j++)
		{
			//定位到行列字节
			char* pMutrixColumn = pMutrixRow + (nTempX + j)/8;

			//定位文字字模数据
			char cTextMutrix = pTextMutrix[i * FontWidth + j / 8];

			if (cTextMutrix & (0x80>>(j%8)))
			{
				int nMutrixPos = (nTempX + j)%8;

				*pMutrixColumn = *pMutrixColumn | (0x80>>nMutrixPos);
			}
		}
	}

	return 1;
}