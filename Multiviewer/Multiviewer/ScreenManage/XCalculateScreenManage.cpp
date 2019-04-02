#include "StdAfx.h"
#include "XCalculateScreenManage.h"
#include "HandleCalculate.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "XSignal.h"
#include "XInputSignal.h"
#include "XScreenColInfo.h"
#include "XScreenRowInfo.h"

XCalculateScreenManage::XCalculateScreenManage(void)
{
}


XCalculateScreenManage::~XCalculateScreenManage(void)
{
}

CSize XCalculateScreenManage::ViewGetSize(XScreenManage* pManage)
{
	float dwScale = pManage->GetScale();

	//int nResolutionH = pManage->GetResolutionH();

	//int nResolutionV = pManage->GetResolutionV();

	int nScreenCountH = pManage->GetScreenCountH();

	int nScreenCountV = pManage->GetScreenCountV();

	//int nRightResulationH=pManage->GetRightResulationH();

	//int nBottomResulationH=pManage->GetBottomResulationV();

	
	int nTempX=0;
	MAP_COLINFO& MapColInfo=pManage->GetMapColInfo();
	for(auto iter=MapColInfo.begin();iter!=MapColInfo.end();++iter)
	{
		XScreenColInfo* pInfo=iter->second;

		nTempX+=pInfo->GetScreenWidth()*dwScale;
	}

	int nTempY=0;
	MAP_ROWINFO& MapRowInfo=pManage->GetMapRowInfo();
	for(auto iter=MapRowInfo.begin();iter!=MapRowInfo.end();++iter)
	{
		XScreenRowInfo* pInfo=iter->second;
		nTempY+=pInfo->GetScreenHeight()*dwScale;
	}

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+nTempX);
	size.cy=LONG(DRAWDISTANCE_Y*2+nTempY);

	return size;
}

void XCalculateScreenManage::SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, 
	CSize& size, float& dwScale, CDC& dc)
{
	HandleCalculate::SetViewPortOrg(rect, noffsetX, noffsetY, size, dwScale, DRAWDISTANCE_X, DRAWDISTANCE_Y, dc);
}

void XCalculateScreenManage::SetPreviewOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale,CSize& orgSize)
{
	HandleCalculate::SetPreviewOrg(rect, noffsetX, noffsetY, size, dwScale, DRAWDISTANCE_X, DRAWDISTANCE_Y,orgSize);
}

void XCalculateScreenManage::GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,
	CSize& size, float& dwScale, int& nOrgX, int& nOrgY)
{
	HandleCalculate::GetViewPortOrg(rect, noffsetX, noffsetY, size, dwScale, DRAWDISTANCE_X, DRAWDISTANCE_Y, nOrgX, nOrgY);
}

void XCalculateScreenManage::ReductionPoint(XScreenManage* pManage, CRect& rect, int noffsetX, 
	int noffsetY, CPoint& srcPoint, POINTF& desPoint)
{
	CSize size = pManage->ViewGetSize();
	float dwScale = pManage->GetScale();

	int nResolutionH = pManage->GetResolutionH();
	int nResolutionV = pManage->GetResolutionV();

	//float dwScaleResolutionH = nResolutionH * dwScale;
	//float dwScaleResolutionV = nResolutionV * dwScale;

	int nOrgX = 0;
	int nOrgY = 0;

	GetViewPortOrg(rect, noffsetX, noffsetY, size, dwScale, nOrgX, nOrgY);

	int nTempX = srcPoint.x - nOrgX;
	int nTempY = srcPoint.y - nOrgY;

	//desPoint.X = (float)(1.0f * nResolutionH/dwScaleResolutionH*nTempX);
	//desPoint.Y = (float)(1.0f * nResolutionV/dwScaleResolutionV*nTempY);
	desPoint.X = (float)(1.0f * nTempX/dwScale);
	desPoint.Y = (float)(1.0f * nTempY/dwScale);

	//TRACE(_T("X:%f, Y:%f\n"), desPoint.X, desPoint.Y);
}

XScreen* XCalculateScreenManage::GetScreenByPoint(XScreenManage* pManage, POINTF& point)
{
	VEC_SCREEN& VecScreen = pManage->GetVecScreen();

	for (VEC_SCREEN::iterator iter = VecScreen.begin(); iter != VecScreen.end(); iter++)
	{
		XScreen* pScreen = *iter;

		RECTF rect = pScreen->GetRect();

		if (rect.Contains(point))
		{
			return pScreen;
		}
	}
	return NULL;
}

XSignal* XCalculateScreenManage::GetSignalByPoint(XScreen* pScreen, POINTF& point)
{
	VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

	for (VEC_SIGNAL::reverse_iterator iter = VecSignal.rbegin(); iter != VecSignal.rend(); iter++)
	{
		XSignal* pSignal=*iter;

		RECTF rect=pSignal->GetRect();

		if (rect.Contains(point))
		{
			return pSignal;
		}
	}
	return NULL;
}

XSignal* XCalculateScreenManage::GetSignalByID(XScreenManage *pManage,unsigned int ID)
{
	VEC_SCREEN& VecScreen = pManage->GetVecScreen();

	for (VEC_SCREEN::iterator iter = VecScreen.begin(); iter != VecScreen.end(); iter++)
	{
		XScreen* pScreen = *iter;

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal *pSignal=*iter;

			if(pSignal->GetSignalID()==ID)
			{
				return pSignal;
			}
		}
	}

	return NULL;
}

XInputSignal* XCalculateScreenManage::GetSignalByIndex(XScreenManage *pManage,int nIndex)
{
	VEC_INPUTSIGNAL& VecInputSignal=pManage->GetVecInputSignal();

	for(VEC_INPUTSIGNAL::iterator iter=VecInputSignal.begin();iter!=VecInputSignal.end();iter++)
	{
		XInputSignal *pInputSignal=*iter;

		int nThisIndex=pInputSignal->GetInputIndex();

		if(nThisIndex==nIndex)
		{
			return pInputSignal;

			break;
		}
	}

	return NULL;
}

BOOL XCalculateScreenManage::DecidePointInSignal(XScreenManage* pManage,XSignal*& pSignal, POINTF& point)
{
	VEC_SCREEN& VecScreen=pManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(VEC_SIGNAL::reverse_iterator iter=VecSignal.rbegin();iter!=VecSignal.rend();++iter)
		{
			XSignal* pCurSignal=*iter;

			RECTF rect=pCurSignal->GetRect();

			if(rect.Contains(point))
			{
				pSignal=pCurSignal;

				return TRUE;
			}
		}
	}

	pSignal=NULL;

	return FALSE;
}

BOOL XCalculateScreenManage::DecidePointInScreen(XScreenManage* pManage,POINTF& point)
{
	VEC_SCREEN& VecScreen=pManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;

		RECTF rect=pScreen->GetRect();

		if(rect.Contains(point))
		{
			return TRUE;
		}
	}

	return FALSE;
}

RECTF XCalculateScreenManage::GetInterRectByAllScreen(XScreenManage* pManage)
{
	VEC_SCREEN& VecScreen=pManage->GetVecScreen();

	RECTF rect;

	BOOL bFirst=TRUE;

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		RECTF tempRect=pScreen->GetRect();

		if(bFirst)
		{
			rect=tempRect;

			bFirst=FALSE;
		}
		else
		{
			rect.Union(rect,rect,tempRect);
		}
	}

	return rect;
}

RECTF XCalculateScreenManage::GetRectBySignal(XScreenManage* pManage, unsigned int nSignalGroupID)
{
	VEC_SIGNAL VecTempSignal;

	VEC_SCREEN& VecScreen=pManage->GetVecScreen();

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen *pScreen=*iter;

		VEC_SIGNAL& VecSignal=pScreen->GetVecSignal();

		for(VEC_SIGNAL::iterator iter=VecSignal.begin();iter!=VecSignal.end();++iter)
		{
			XSignal* pTempSignal=*iter;

			int nGroupID=pTempSignal->GetSignalGroupID();

			if(nGroupID==nSignalGroupID)
			{
				VecTempSignal.push_back(pTempSignal);
			}
		}
	}

	RECTF rect;

	BOOL bFirst=TRUE;

	for(VEC_SIGNAL::iterator iter=VecTempSignal.begin();iter!=VecTempSignal.end();++iter)
	{
		XSignal *pSignal=*iter;

		RECTF tempRect=pSignal->GetRect();

		if(bFirst)
		{
			rect=tempRect;

			bFirst=FALSE;
		}
		else
		{
			rect.Union(rect,rect,tempRect);
		}
	}

	return rect;
}

RECTF XCalculateScreenManage::GetRectByVecScreen(VEC_SCREEN& VecScreen)
{
	RECTF rect;

	BOOL bFirst=TRUE;

	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();iter++)
	{
		XScreen *pScreen=*iter;

		RECTF tempRect=pScreen->GetRect();

		if(bFirst)
		{
			rect=tempRect;

			bFirst=FALSE;
		}
		else
		{
			rect.Union(rect,rect,tempRect);
		}
	}

	return rect;
}

void XCalculateScreenManage::MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size)
{
	float nRate=1.0*rect.Width/rect.Height;
	float nRateReciprocal=1.0*rect.Height/rect.Width;

	switch(PositionType)
	{
	case POSITIONTYPE_LT:
		{
			rect.X+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Width=rect.Width-size.Width;

			rect.Y+=nTemp;

			rect.Height-=nTemp;
		}
		break;
	case POSITIONTYPE_RT:
		{
			rect.Y+=size.Height;

			float nTemp=1.0*(size.Height)*nRate;

			rect.Width-=nTemp;

			rect.Height-=size.Height;
		}
		break;
	case POSITIONTYPE_LB:
		{
			rect.X+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Width-=size.Width;

			rect.Height-=nTemp;
		}
		break;
	case POSITIONTYPE_RB:
		{
			rect.Width+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Height+=nTemp;
		}
		break;
	case POSITIONTYPE_L:
		{
			rect.X+=size.Width;

			rect.Width=rect.Width-size.Width;
		}
		break;
	case POSITIONTYPE_R:
		{
			rect.Width+=size.Width;
		}
		break;
	case POSITIONTYPE_T:
		{
			rect.Y+=size.Height;

			rect.Height-=size.Height;
		}
		break;
	case POSITIONTYPE_B:
		{
			rect.Height+=size.Height;
		}
		break;
	default:
		{
			rect.Offset(size.Width,size.Height);
		}
		break;
	}
}


void XCalculateScreenManage::MoveSignalOfNew(RECTF& rect,SIZEF& size)
{
	rect.Width+=size.Width;
	rect.Height+=size.Height;
}

//BOOL XCalculateScreenManage::DecidePointInScreen(XScreenManage *pManage,POINTF& point)
//{
//	RECTF rect;
//
//	BOOL bFirst=TRUE;
//
//	VEC_SCREEN& VecScreen=pManage->GetVecScreen();
//
//	for(VEC_SCREEN::iterator iter=VecScreen.begin();iter!=VecScreen.end();iter++)
//	{
//		XScreen *pScreen=*iter;
//
//		RECTF tempRect=pScreen->GetRect();
//
//		if(bFirst)
//		{
//			rect=tempRect;
//
//			bFirst=FALSE;
//		}
//		else
//		{
//			rect.Union(rect,rect,tempRect);
//		}
//	}
//
//	if(rect.Contains(pManage->GetInterRect()))
//	{
//		return TRUE;
//	}
//
//	return FALSE;
//}

POSITIONTYPE XCalculateScreenManage::DecidePointInSignalPosition(XScreenManage* pManage, RECTF& rect, POINTF& point)
{
	double dwScale = pManage->GetScale();

	int nDistance = (int)(5 / dwScale);

	if ((point.X - rect.GetLeft()) <= nDistance)
	{
		if(point.Y-rect.GetTop()<=nDistance)
		{
			return POSITIONTYPE_LT;
		}
		else if((rect.GetBottom()-point.Y)<=nDistance)
		{
			return POSITIONTYPE_LB;
		}
		else
		{
			return POSITIONTYPE_L;
		}
	}
	else if((rect.GetRight()-point.X)<=nDistance)
	{
		if ((point.Y - rect.GetTop()) <= nDistance)
		{
			return POSITIONTYPE_RT;
		}
		else if ((rect.GetBottom() - point.Y) <= nDistance)
		{
			return POSITIONTYPE_RB;
		}
		else
		{
			return POSITIONTYPE_R;
		}
	}
	else if ((point.Y - rect.GetTop()) <= nDistance)
	{
		return POSITIONTYPE_T;
	}
	else if ((rect.GetBottom() - point.Y) <= nDistance)
	{
		return POSITIONTYPE_B;
	}

	return POSITIONTYPE_NULL;
}

CURSORTYPE XCalculateScreenManage::GetCursorTypeByPositionType(POSITIONTYPE type)
{
	CURSORTYPE cursortype = CURSORTYPE_NULL;

	switch(type)
	{
	case POSITIONTYPE_LT:
		{
			cursortype = CURSORTYPE_NWSE;
		}
		break;
	case POSITIONTYPE_LB:
		{
			cursortype = CURSORTYPE_NESW;
		}
		break;
	case POSITIONTYPE_RT:
		{
			cursortype = CURSORTYPE_NESW;
		}
		break;
	case POSITIONTYPE_RB:
		{
			cursortype = CURSORTYPE_NWSE;
		}
		break;
	case POSITIONTYPE_L:
		{
			cursortype = CURSORTYPE_WE;
		}
		break;
	case POSITIONTYPE_R:
		{
			cursortype = CURSORTYPE_WE;
		}
		break;
	case POSITIONTYPE_T:
		{
			cursortype = CURSORTYPE_NS;
		}
		break;
	case POSITIONTYPE_B:
		{
			cursortype = CURSORTYPE_NS;
		}
		break;
	default:
		{
			cursortype = CURSORTYPE_MOVE;
		}
		break;
	}
	return cursortype;
}

RECTF XCalculateScreenManage::GetSignalRectBySignalPosType(XScreen*& pScreen, SIGNALPOSTYPE type)
{
	RECTF rectScreen = pScreen->GetRect();

	float dwSignalWidth = rectScreen.Width / 2;

	float dwSignalHeight = rectScreen.Height / 2;

	float nMiddleX = rectScreen.X + rectScreen.Width / 2;

	float nMiddleY = rectScreen.Y + rectScreen.Height / 2;

	RECTF rect;

	switch (type)
	{
	case SIGNALPOSTYPE_NULL:
		{
			rect = rectScreen;
		}
		break;
	case SIGNALPOSTYPE_1:
		{
			rect = RectF(rectScreen.X, rectScreen.Y, dwSignalWidth, dwSignalHeight);
		}
		break;
	case SIGNALPOSTYPE_2:
		{
			rect = RectF(nMiddleX, rectScreen.Y, dwSignalWidth, dwSignalHeight);
		}
		break;
	case SIGNALPOSTYPE_3:
		{
			rect = RectF(rectScreen.X, nMiddleY, dwSignalWidth, dwSignalHeight);
		}
		break;
	case SIGNALPOSTYPE_4:
		{
			rect = RectF(nMiddleX, nMiddleY, dwSignalWidth, dwSignalHeight);
		}
		break;
	default:
		break;
	}

	return rect;
}

int XCalculateScreenManage::GetIntFromFloat(float fwData)
{
	int nTemp=(int)fwData;

	if(fabs(fwData-nTemp)>=0.5)
	{
		if(fwData>=0)
		{
			nTemp++;
		}
		else
		{
			nTemp--;
		}
	}
	return nTemp;
}