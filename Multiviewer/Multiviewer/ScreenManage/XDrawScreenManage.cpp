#include "StdAfx.h"
#include "XDrawScreenManage.h"
#include "XScreenManage.h"
#include "XCalculateScreenManage.h"
#include "XScreen.h"
#include "XSignal.h"

XDrawScreenManage::XDrawScreenManage(void)
{
}

XDrawScreenManage::~XDrawScreenManage(void)
{
}

void XDrawScreenManage::ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
	int noffsetY, XScreenManage* pManage)
{
	float dwScale = pManage->GetScale();

	CSize size = pManage->ViewGetSize();

	int nWidth = rect.Width();

	int nHeight = rect.Height();

	HDC hdc = pDC->GetSafeHdc();

	CDC tempDC;

	tempDC.CreateCompatibleDC(pDC);

	XCalculateScreenManage::SetViewPortOrg(rect, noffsetX, noffsetY,size, dwScale, tempDC);

	HDC hMemdc = tempDC.GetSafeHdc();

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);

	HBITMAP hOldbmp = (HBITMAP)SelectObject(hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	graphics.Clear(Color(255, 230, 230, 230));

	///////////////////////////////////////////////////////

	DrawVecScreen(graphics, pManage);

	///////////////////////////////////////////////////////

	BitBlt(hdc, noffsetX, noffsetY, nWidth, nHeight, hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC(hMemdc);

	SelectObject(hMemdc, hOldbmp);

	tempDC.DeleteDC();

	DeleteObject(hMembmp);
}


void XDrawScreenManage::DrawVecScreen(Graphics& graphics, XScreenManage* pManage)
{
	float dwScale = pManage->GetScale();

	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  

	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0), 1.0f);//直线画笔

	//Gdiplus::Pen Signalpen(Gdiplus::Color(255, 230, 230, 230), 1.0f);//直线画笔

	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 184, 184, 184));//区域颜色

	Gdiplus::SolidBrush brushDisenable(Gdiplus::Color(255, 230, 230, 230));//禁用区域颜色

	Gdiplus::SolidBrush brushSignal(Gdiplus::Color(/*51, 153, 255*/90, 198, 149));//信号颜色

	Gdiplus::SolidBrush brushPreview(Gdiplus::Color(255,102, 102, 213));//预览颜色

	Gdiplus::Pen penMiddle(Gdiplus::Color(255, 0, 0, 0), 1.0f);//虚线画笔

	Gdiplus::REAL dashVal[4] = {1,4,1,4}; 

	penMiddle.SetDashPattern(dashVal,4);

	float dwTextSize = 10 * dwScale;

	float dwTextSizeSignal = 14 * dwScale;

	Gdiplus::SolidBrush textbrush(Color(255, 255, 255, 255));

	Gdiplus::SolidBrush textbrushSignal(Color(255, 0, 0, 255));

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, dwTextSize, FontStyleRegular,UnitPoint);

	Gdiplus::Font fontSignal(&fontfamily, dwTextSizeSignal, FontStyleRegular,UnitPoint);

	Gdiplus::StringFormat stringForamt;

	stringForamt.SetAlignment(StringAlignmentFar);

	stringForamt.SetLineAlignment(StringAlignmentFar);

	CString szTextCustomize = pManage->GetTranslationString(_T("294"), _T("自定义"));

	VEC_SCREEN& VecScreen = pManage->GetVecScreen();

	for(VEC_SCREEN::iterator iterScreen = VecScreen.begin(); iterScreen != VecScreen.end(); iterScreen++)
	{
		XScreen* pScreen = *iterScreen;

		int nIndex = pScreen->GetIndex();

		int nBoardIndex=pScreen->GetBoardIndex();

		int nPaneNumIndex=pScreen->GetNumOfTwoScreen();

		BOOL bIsTwoScreen=pScreen->GetIsTwoSignal();

		RECTF rect = pScreen->GetRect();

		RECTF drawRect(rect.X * dwScale, rect.Y * dwScale, rect.Width * dwScale, rect.Height * dwScale);

		//绘制区域
		//pManage->IsTwoScreen(nIndex);
		//TRACE(_T("nIndex=%d\n"),nIndex);

		//BOOL b=pManage->IsHaveDevice(nIndex);

		//TRACE(_T("b=%d\n"),b);

		BOOL b=pManage->IsHaveDevice(nBoardIndex);

		if(pManage->IsHaveDevice(nBoardIndex))
		{
			graphics.FillRectangle(&brush, drawRect.X, drawRect.Y, drawRect.Width - 1, drawRect.Height - 1);
		}
		else
		{
			graphics.FillRectangle(&brushDisenable, drawRect.X, drawRect.Y, drawRect.Width - 1, drawRect.Height - 1);
		}

		graphics.DrawRectangle(&pen, drawRect.X, drawRect.Y, drawRect.Width - 1, drawRect.Height - 1);

		//绘制信号
		VEC_SIGNAL& VecSignal = pScreen->GetVecSignal();

		for (VEC_SIGNAL::iterator iter = VecSignal.begin(); iter != VecSignal.end(); iter++)
		{
			XSignal* pSignal = *iter;

			if(pSignal->GetSignalHide())
			{
				continue;
			}

			RECTF rectSignal = pSignal->GetRect();

			RECTF drawRectSignal(rectSignal.X * dwScale, rectSignal.Y * dwScale, rectSignal.Width * dwScale-1, rectSignal.Height * dwScale-1);

			//绘制区域
			graphics.FillRectangle(&brushSignal, drawRectSignal);

			graphics.DrawRectangle(&pen, drawRectSignal);
	
		}
		
		//////////////////////////////////////////////////////////////////////////

		//绘制文字
		CString szTemp = _T("");

		CString szStr=pManage->GetTranslationString(_T("230"), _T("屏幕"));
		CString szStr2=pManage->GetTranslationString(_T("505"), _T("板卡"));


		if(nBoardIndex==0)
		{
			CString szStr3=_T("未分配");

			szTemp.Format(_T("%s: %d\n%s: %s"),szStr,nIndex,szStr2,szStr3);	
		}
		else
		{
			if(bIsTwoScreen)
			{
				if(nPaneNumIndex)
				{
					szTemp.Format(_T("%s: %d\n%s: %d%s%d"),szStr,nIndex,szStr2,nBoardIndex,_T("-"),nPaneNumIndex);	
				}
				else
				{
					szTemp.Format(_T("%s: %d\n%s: %d"),szStr,nIndex,szStr2,nBoardIndex);
				}			
			}
			else
			{
				szTemp.Format(_T("%s: %d\n%s: %d"),szStr,nIndex,szStr2,nBoardIndex);
			}
		}

		graphics.DrawString(szTemp, -1, &font, Gdiplus::PointF(drawRect.X, drawRect.Y), &textbrush);

		//////////////////////////////////////////////////////////////////////////
		if(nBoardIndex==0)
		{
			continue;
		}

		//绘制分隔线
		pManage->IsTwoScreen(nBoardIndex);
		if (!pScreen->GetIsTwoSignal())
		{
			float X1,Y1,X2,Y2;

			X1 = drawRect.X;
			X2 = drawRect.X + drawRect.Width;
			Y1 = Y2 = drawRect.Y + drawRect.Height / 2 - 1;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			Y1 = Y2 = drawRect.Y + drawRect.Height / 2;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			X1 = X2 = drawRect.X + drawRect.Width / 2 - 1;
			Y1 = drawRect.Y;
			Y2 = drawRect.Y + drawRect.Height;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			X1 = X2 = drawRect.X + drawRect.Width / 2;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);
		}
		else
		{
			float X1,Y1,X2,Y2;

			X1 = drawRect.X;
			X2 = drawRect.X + drawRect.Width;
			Y1 = Y2 = drawRect.Y + drawRect.Height / 2 - 1;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			Y1 = Y2 = drawRect.Y + drawRect.Height / 2;
			graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			X1 = X2 = drawRect.X + drawRect.Width / 2 - 1;
			Y1 = drawRect.Y;
			Y2 = drawRect.Y + drawRect.Height;
			//graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);

			X1 = X2 = drawRect.X + drawRect.Width / 2;
			//graphics.DrawLine(&penMiddle, X1, Y1, X2, Y2);
		}

		
	}

	if(pManage->GetISViewButtonDown())
	{
		DrawDragRect(graphics, pManage);
	}
}

void XDrawScreenManage::DrawDragRect(Graphics& graphics, XScreenManage* pManage)
{
	float dwScale=pManage->GetScale();

	//TRACE("dwScale=%f\n",dwScale);

	RECTF rect=pManage->GetInterRect();

	RECTF wndRect;
	if((int)dwScale==1)
	{
		float nTempX=rect.X*dwScale;
		float nTempY=rect.Y*dwScale;
		float nTempW=rect.Width*dwScale;
		float nTempH=rect.Height*dwScale;

		int rectX=XCalculateScreenManage::GetIntFromFloat(nTempX);
		int rectY=XCalculateScreenManage::GetIntFromFloat(nTempY);
		int rectW=XCalculateScreenManage::GetIntFromFloat(nTempW);
		int rectH=XCalculateScreenManage::GetIntFromFloat(nTempH);
		RECTF tempRect(rectX,rectY,rectW,rectH);
		wndRect=tempRect;
	}
	else
	{
		RECTF tempRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);
		wndRect=tempRect;
	}

	int nInputIndex=pManage->GetDragInfo().GetInputIndex();

	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  

	Gdiplus::SolidBrush textbrushSignal(Color(255, 0, 100, 255));

	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0), 1.0f);

	Gdiplus::SolidBrush brushSignal(Gdiplus::Color(255,90, 198, 149));

	Gdiplus::SolidBrush brushPreview(Gdiplus::Color(255,102, 102, 213));

	Gdiplus::FontFamily fontfamily(APP_FONT);

	float dwTextSizeSignal = 14 * dwScale;

	Gdiplus::Font fontSignal(&fontfamily, dwTextSizeSignal, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringForamt;

	stringForamt.SetAlignment(StringAlignmentCenter);

	stringForamt.SetLineAlignment(StringAlignmentCenter);

	graphics.FillRectangle(&brushSignal, wndRect);

	graphics.DrawRectangle(&pen, wndRect);

	CString szAnotherName=pManage->GetDragInfo().GetAnotherName();

	BOOL bIsUltra=pManage->GetDragInfo().GetIsUltra();

	if(bIsUltra)
	{
		CString szStr=_T("4K");

		if(szAnotherName!=_T(""))
		{
			graphics.DrawString(szAnotherName+_T("(")+szStr+_T(")"), -1, &fontSignal, wndRect, &stringForamt, &textbrushSignal);
		}
		else
		{
			graphics.DrawString(szStr, -1, &fontSignal, wndRect, &stringForamt, &textbrushSignal);
		}
	}
	else
	{
		if(szAnotherName!=_T(""))
		{
			graphics.DrawString(szAnotherName, -1, &fontSignal, wndRect, &stringForamt, &textbrushSignal);
		}
		else
		{
			CString szTemp = _T("");

			szTemp.Format(_T("%d"), nInputIndex);

			graphics.DrawString(szTemp, -1, &fontSignal, wndRect, &stringForamt, &textbrushSignal);
		}
	}
}

