// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XScreenInfosWnd.h"
#include "XScreenInfo.h"
#include "XScreenNumInfo.h"



// XScreenInfosWnd

IMPLEMENT_DYNAMIC(XScreenInfosWnd, CWnd)

XScreenInfosWnd::XScreenInfosWnd()
{
	m_nBoardIndex=0;

	m_pDelegate=NULL;

	m_bIsTwoScreen=FALSE;

	m_nBeginScreenIndex=1;
}

XScreenInfosWnd::~XScreenInfosWnd()
{
	ClearMapMatrix();

	ClearMapBoard();
}

BEGIN_MESSAGE_MAP(XScreenInfosWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// XScreenInfosWnd 消息处理程序

BOOL XScreenInfosWnd::Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 
		0, 
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS), 
		0, 
		dwStyle, 
		rect, 
		pParentWnd, 
		nID);
}

void XScreenInfosWnd::ClearMapBoard()
{
	m_BoardMapMatrix.clear();
}

void XScreenInfosWnd::ClearMapMatrix()
{
	m_ScreenIndexMapMatrix.clear();
}

void XScreenInfosWnd::SetDelegate(XDelegateScreenInfosWnd* pDelegate)
{
	m_pDelegate = pDelegate;
}

void XScreenInfosWnd::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

void XScreenInfosWnd::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

void XScreenInfosWnd::SetBeginScreenIndex(int n)
{
	m_nBeginScreenIndex=n;
}

int XScreenInfosWnd::GetBeginScreenIndex()
{
	return m_nBeginScreenIndex;
}

void XScreenInfosWnd::OnPaint()
{
	CPaintDC dc(this); 

	CDC* pDC = &dc;

	CRect rect;
	GetClientRect(rect);

	int nWidth = rect.Width();

	int nHeight = rect.Height();

	HDC hdc = pDC->GetSafeHdc();

	CDC  tempDC;
	tempDC.CreateCompatibleDC(pDC);

	HDC hMemdc = tempDC.GetSafeHdc();

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);

	HBITMAP hOldbmp = (HBITMAP)SelectObject(hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	graphics.Clear(Color(255, 230, 230, 230));

	///////////////////////////////////////////////////////
	DrawArea(graphics, rect);

	DrawScreenInfo(graphics, rect);

	///////////////////////////////////////////////////////

	BitBlt(hdc, 0, 0, nWidth, nHeight, hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC(hMemdc);

	SelectObject(hMemdc, hOldbmp);

	tempDC.DeleteDC();

	DeleteObject(hMembmp);
}

void XScreenInfosWnd::DrawArea(Graphics& graphics, CRect rect)
{
	//边框
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0), 1.0f);
	graphics.DrawRectangle(&pen, 0, 0, rect.Width() - 1, rect.Height() - 1);

	//分隔线
	int nShowColumn = m_pDelegate->GetScreenColumn();

	int nShowRow = m_pDelegate->GetScreenRow();

	float distanceWidth = 1.0f * rect.Width() / nShowColumn;

	float distanceHeight = 1.0f * rect.Height() / nShowRow;

	Gdiplus::Pen pendash(Gdiplus::Color(255, 0, 0, 0), 1.0f);
	Gdiplus::REAL dashVal[4] = {1,4,1,4}; 
	pendash.SetDashPattern(dashVal,4);

	float left = 0.0f;
	float top = 0.0f;
	float right = (float)rect.Width();
	float bottom = (float)rect.Height();
	float temp = 0.0f;

	for(int i = 1; i < nShowColumn; i++)
	{
		temp = i * distanceWidth;

		graphics.DrawLine(&pen, temp, top, temp, bottom);
	}

	for(int i = 1; i < nShowRow; i++)
	{
		temp = i * distanceHeight;

		graphics.DrawLine(&pen, left, temp, right, temp);
	}
}

void XScreenInfosWnd::DrawScreenInfo(Graphics& graphics, CRect rect)
{
	int nScreenColumn = m_pDelegate->GetScreenColumn();

	int nScreenRow = m_pDelegate->GetScreenRow();

	float left = 0.0f;
	float top = 0.0f;

	float nScreenWidth = 1.0f * rect.Width() / nScreenColumn;
	float nScreenHeight = 1.0f * rect.Height() / nScreenRow;

	int nIndex = 0;

	int nScreenIndex=m_nBeginScreenIndex;

	VEC_SCREENINFO& VecScreenInfo = m_pDelegate->GetVecScreenInfo();

	Gdiplus::Font font(_T("微软雅黑"), 8.0f, FontStyleRegular, UnitPoint);

	Gdiplus::SolidBrush brushRect(Gdiplus::Color(255, 184, 184, 184));//区域颜色

	if (font.GetLastStatus() == Gdiplus::Ok)
	{
		Gdiplus::Color brushColor(255, 0, 0, 0);
		Gdiplus::SolidBrush brush(brushColor);

		graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

		for(int i = 0; i < nScreenRow; i++)
		{
			for(int j = 0; j < nScreenColumn; j++)
			{
				XScreenInfo* pInfo = VecScreenInfo[nIndex++];

				int nIndex=pInfo->GetScreenIndex();

				int nBoardIndex=pInfo->GetBoardIndex();

				int nNumOfScreen=pInfo->GetNumOfScreen();

				Gdiplus::StringFormat stringFormat;
				stringFormat.SetAlignment(StringAlignmentCenter);
				stringFormat.SetLineAlignment(StringAlignmentCenter);

				Gdiplus::RectF r(left, top, nScreenWidth, nScreenHeight);

				CString szText = _T("");

				if(nBoardIndex!=0)
				{		
					if(nNumOfScreen==0)
					{
						szText.Format(_T("%s: %d->%s: %d"),
							m_pDelegate->GetTranslationString(_T("230"),_T("屏幕")),
							nScreenIndex,
							m_pDelegate->GetTranslationString(_T("505"),_T("板卡")),
							nBoardIndex);
					}
					else
					{
						szText.Format(_T("%s: %d->%s: %d-%d"),
							m_pDelegate->GetTranslationString(_T("230"),_T("屏幕")),
							nScreenIndex,
							m_pDelegate->GetTranslationString(_T("505"),_T("板卡")),
							nBoardIndex,
							nNumOfScreen);
					}

					graphics.FillRectangle(&brushRect, r.X, r.Y, r.Width - 1, r.Height - 1);
				}
				else
				{
					szText.Format(_T("%s: %d->%s"),
						m_pDelegate->GetTranslationString(_T("230"),_T("屏幕")),
						nScreenIndex,
						m_pDelegate->GetTranslationString(_T("586"),_T("未分配")));
				}

				graphics.DrawString(szText, -1, &font, r, &stringFormat, &brush);

				left += nScreenWidth;

				nScreenIndex+=1;
			}

			left = 0.0f;

			top += nScreenHeight;
		}
	}
}

void XScreenInfosWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	MSG message; 

	DWORD st = GetTickCount(); 

	while(1)   
	{   
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))   
		{   
			::TranslateMessage(&message); 

			::DispatchMessage(&message);  

			if(message.message == WM_LBUTTONDBLCLK)   
			{  
				break;  
			}   
		}   

		DWORD et=GetTickCount();   

		if(et-st>200)   
		{  
			TRACE(_T("one\n"));

			CRect rect;
			GetClientRect(rect);

			int nScreenColumn = m_pDelegate->GetScreenColumn();

			int nScreenRow = m_pDelegate->GetScreenRow();

			float nChildWidth = 1.0f * rect.Width() / nScreenColumn;

			float nChildHeight = 1.0f * rect.Height() / nScreenRow;

			int nRowIndex = (int)((point.y - rect.top) / nChildHeight);

			int nColumnIndex = (int)((point.x- rect.left) / nChildWidth);

			VEC_SCREENINFO& VecScreenInfo = m_pDelegate->GetVecScreenInfo();

			XScreenInfo* pInfo = VecScreenInfo[nRowIndex * nScreenColumn + nColumnIndex];

			int nCurScreenIndex=pInfo->GetScreenIndex();

			pInfo->SetIsTwoScreen(m_bIsTwoScreen);

			int nTempBoardIndex=pInfo->GetBoardIndex();

			//只有未分配板卡时，才给与分配
			if(nTempBoardIndex==0)
			{
				pInfo->SetBoardIndex(m_nBoardIndex);
			}

			//记录当前板卡
			pInfo->SetCurBoardIndex(m_nBoardIndex);

			//判断已分配板卡是否为当前板卡
			if(pInfo->GetBoardIndex()!=pInfo->GetCurBoardIndex())
			{
				m_pDelegate->MessageBoxFromKey(_T("599"),_T("所选对应屏幕重复，请重新选择！"),MB_OK);

				return;
			}
			///////////////////////////////////////////////////
			//首先初始化（MAP_NUMOFMATRIXSCREEN）
			for(VEC_SCREENINFO::iterator iter=VecScreenInfo.begin();iter!=VecScreenInfo.end();++iter)
			{
				XScreenInfo* pInfo=*iter;

				int nNumOfScreen=pInfo->GetNumOfScreen();

				if(nNumOfScreen!=0)
				{
					int nBoardIndex=pInfo->GetBoardIndex();

					int nScreenIndex=pInfo->GetScreenIndex();

					MAP_NUMOFMATRIXSCREEN::iterator iter2=m_BoardMapMatrix.find(nBoardIndex);

					if(iter2!=m_BoardMapMatrix.end())
					{
						MAP_MATRIX& Map=iter2->second;

						MAP_MATRIX::iterator iter3=Map.find(nScreenIndex);

						if(iter3==Map.end())
						{
							Map.insert(std::pair<int,int>(nScreenIndex,nNumOfScreen));

							m_BoardMapMatrix.insert(std::pair<int,MAP_MATRIX>(nBoardIndex,Map));
						}
					}
					else
					{
						MAP_MATRIX Map;

						Map.insert(std::pair<int,int>(nScreenIndex,nNumOfScreen));

						m_BoardMapMatrix.insert(std::pair<int,MAP_MATRIX>(nBoardIndex,Map));
					}
				}
			}

			//////////////////////////////////////////////////
			switch(m_nScreenModel)
			{
			case SCREENMODEL_SPLIC:
				{
					if(m_bIsTwoScreen)
					{
						MAP_NUMOFMATRIXSCREEN::iterator iter=m_BoardMapMatrix.find(m_nBoardIndex);

						if(iter!=m_BoardMapMatrix.end())
						{
							int nBoardIndex=iter->first;

							MAP_MATRIX& MapMatrixScreenNum=iter->second;

							//////////////////////////////////////////////////////////////////////////
							MAP_MATRIX::iterator iterTemp=MapMatrixScreenNum.find(nCurScreenIndex);

							int nSize=MapMatrixScreenNum.size();

							if(nSize>2)
							{
								return;
							}

							if(iterTemp==MapMatrixScreenNum.end())
							{
								int nScreenNum=GetNum(m_nBoardIndex,2);

								MapMatrixScreenNum.insert(std::pair<int,int>(nCurScreenIndex,nScreenNum));
							}
							else
							{
								//重复
								m_pDelegate->MessageBoxFromKey(_T("599"),_T("所选对应屏幕重复，请重新选择！"),MB_OK);

								return;
							}
						}
						else
						{
							int nScreenNum=1;

							m_ScreenIndexMapMatrix.insert(std::pair<int,int>(nCurScreenIndex,nScreenNum));

							m_BoardMapMatrix.insert(std::pair<int,MAP_MATRIX>(m_nBoardIndex,m_ScreenIndexMapMatrix));
						}
					}
				}
				break;
			case SCREENMODEL_MATRIX:
				{
					MAP_NUMOFMATRIXSCREEN::iterator iter=m_BoardMapMatrix.find(m_nBoardIndex);

					if(iter!=m_BoardMapMatrix.end())
					{
						int nBoardIndex=iter->first;

						MAP_MATRIX& MapMatrixScreenNum=iter->second;

						//////////////////////////////////////////////////////////////////////////
						MAP_MATRIX::iterator iterTemp=MapMatrixScreenNum.find(nCurScreenIndex);

						if(iterTemp==MapMatrixScreenNum.end())
						{
							int nScreenNum=GetNum(m_nBoardIndex,4);

							MapMatrixScreenNum.insert(std::pair<int,int>(nCurScreenIndex,nScreenNum));
						}
						else
						{
							int nNumOfScreen=iterTemp->second;

							if(nNumOfScreen!=0)
							{
								//重复
								m_pDelegate->MessageBoxFromKey(_T("599"),_T("所选对应屏幕重复，请重新选择！"),MB_OK);

								return;
							}
						}
					}
					else
					{
						int nScreenNum=1;

						m_ScreenIndexMapMatrix.insert(std::pair<int,int>(nCurScreenIndex,nScreenNum));

						m_BoardMapMatrix.insert(std::pair<int,MAP_MATRIX>(m_nBoardIndex,m_ScreenIndexMapMatrix));
					}
				}
				break;
			default:
				break;
			}

			for(MAP_NUMOFMATRIXSCREEN::iterator iter=m_BoardMapMatrix.begin();iter!=m_BoardMapMatrix.end();++iter)
			{
				int nBoardIndex=iter->first;

				MAP_MATRIX& MapMatrix=iter->second;

				for(MAP_MATRIX::iterator iter2=MapMatrix.begin();iter2!=MapMatrix.end();++iter2)
				{
					int nScreenIndex=iter2->first;

					int nNumOfScreen=iter2->second;

					if(m_nBoardIndex==nBoardIndex
						&&nCurScreenIndex==nScreenIndex)
					{
						pInfo->SetNumOfScreen(nNumOfScreen);
					}
				}
			}

			m_pDelegate->ScreenInfoLBtnDown(pInfo);

			break;  
		}   
	}
}

int XScreenInfosWnd::GetNum(int nBoardIndex,int nNum)
{
	int nGetNum=0;

	MAP_NUM MapNum;

	for(MAP_NUMOFMATRIXSCREEN::iterator iter=m_BoardMapMatrix.begin();iter!=m_BoardMapMatrix.end();++iter)
	{
		int nTempBoard=iter->first;

		if(nTempBoard==nBoardIndex)
		{
			MAP_MATRIX& MapMarix=iter->second;

			for(MAP_MATRIX::iterator iter2=MapMarix.begin();iter2!=MapMarix.end();++iter2)
			{
				int nScreenNum=iter2->second;

				MapNum.insert(std::pair<int,int>(nScreenNum,1));
			}
		}
	}

	int nSize=MapNum.size();

	if(nSize<nNum)
	{
		for(int i=1;i<=nNum;i++)
		{
			MAP_NUM::iterator iter=MapNum.find(i);

			if(iter==MapNum.end())
			{
				MapNum.insert(std::pair<int,int>(i,0));
			}
		}
	}

	for(int i=1;i<=nNum;i++)
	{
		int n=MapNum[i];

		if(n==0)
		{
			nGetNum=i;

			return nGetNum;
		}
	}

	return nGetNum;
}

void XScreenInfosWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	TRACE(_T("Two\n"));

	CRect rect;
	GetClientRect(rect);

	int nScreenColumn = m_pDelegate->GetScreenColumn();

	int nScreenRow = m_pDelegate->GetScreenRow();

	float nChildWidth = 1.0f * rect.Width() / nScreenColumn;

	float nChildHeight = 1.0f * rect.Height() / nScreenRow;

	int nRowIndex = (int)((point.y - rect.top) / nChildHeight);

	int nColumnIndex = (int)((point.x- rect.left) / nChildWidth);

	VEC_SCREENINFO& VecScreenInfo = m_pDelegate->GetVecScreenInfo();

	XScreenInfo* pInfo = VecScreenInfo[nRowIndex * nScreenColumn + nColumnIndex];

	//当前双击屏幕
	int nCurScreenIndex=pInfo->GetScreenIndex();

	//记录当前板卡
	pInfo->SetCurBoardIndex(m_nBoardIndex);

	//是否为两路
	pInfo->SetIsTwoScreen(m_bIsTwoScreen);

	//当前第几个屏幕
	int nNumOfScreen=pInfo->GetNumOfScreen();

	//判断已分配板卡是否为当前板卡
	if(pInfo->GetBoardIndex()!=pInfo->GetCurBoardIndex())
	{
		m_pDelegate->MessageBoxFromKey(_T("758"),_T("无法清除其他板卡的屏幕配置！"),MB_OK);

		return;
	}

	////////////////////////////////////////
	MAP_NUMOFMATRIXSCREEN::iterator iter=m_BoardMapMatrix.find(m_nBoardIndex);

	if(iter!=m_BoardMapMatrix.end())
	{
		int nBoardIndex=iter->first;

		MAP_MATRIX& MapMatrix=iter->second;

		MAP_MATRIX::iterator iter2=MapMatrix.find(nCurScreenIndex);

		if(iter2!=MapMatrix.end())
		{
			int nScreenIndex=iter2->first;

			int nTempNumOfScreen=iter2->second;

			MapMatrix.erase(iter2);
		}
	}
	///////////////////////////////////////

	m_pDelegate->ScreenInfoLBDblClk(pInfo);

	//m_bIsFirstTime=TRUE;
}
