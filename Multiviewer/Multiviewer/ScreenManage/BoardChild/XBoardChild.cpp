#include "stdafx.h"
#include "XBoardChild.h"
#include "afxdialogex.h"
#include "XDelegateSelectEquipment.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "HandlePath.h"
#include "XEquipmentInput.h"
#include "XEquipmentOutput.h"
#include "XSetOSD.h"
#include "XScreenInfo.h"
#include "XMenuScreenSetInfo.h"
#include "XOutputInfo.h"
#include "HYXText.h"
#include "XInputType.h"



// CAddExpandDlg 对话框

#define SCROOL_TIME_ELAPSE  200
#define FONT_SIZE			17		//字体大小

IMPLEMENT_DYNAMIC(XBoardChild, CDialogEx)

	XBoardChild::XBoardChild(CWnd* pParent /*=NULL*/)
	: CDialogEx(XBoardChild::IDD, pParent)
{
	m_pDelegate=NULL;

	m_bScrollTimerV=FALSE;

	m_nScrollPosV=0;

	m_nScrollTimerV=0;

	m_nScrellHight=0;

	m_nScreenNumH=0;

	m_nScreenNumV=0;

	m_IsMenuSet=FALSE;

	//m_nBeginScreenIndex=1;

	m_nScreenModel=0;
}

XBoardChild::~XBoardChild()
{
	ClearVecEquipment();

	ClearVecTextWnd();

	ClearScreenInfo();

	DeleteFont();

	ClearBoardType();
}

void XBoardChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XBoardChild, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_PAINT()
	
	//ON_BN_CLICKED(ID_BTNCHECKBOX+1,OnCheckBox)

	ON_CBN_SELCHANGE(ID_BTNCHECKBOX+10,OnSelchangeCombo)

END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序
void XBoardChild::ClearVecEquipment()
{
	ClearVecInput();

	ClearVecOutput();
}

void XBoardChild::ClearVecInput()
{
	for(VEC_EQUIPMENTINPUT::iterator iter=m_VecEquipmentInput.begin();iter!=m_VecEquipmentInput.end();++iter)
	{
		delete *iter;
	}

	m_VecEquipmentInput.clear();
}

void XBoardChild::ClearVecOutput()
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		delete *iter;
	}

	m_VecEquipmentOutput.clear();
}

void XBoardChild::ClearVecTextWnd()
{
	for(VEC_VIEWTEXT::iterator iter=m_VecViewText.begin();iter!=m_VecViewText.end();++iter)
	{
		delete *iter;
	}

	m_VecViewText.clear();
}

void XBoardChild::ClearScreenInfo()
{
	for(VEC_SCREENINFO::iterator iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		delete *iter;
	}

	m_VecScreenInfo.clear();
}

void XBoardChild::ClearBoardType()
{
	m_pScreenManage->ClearMapBoardType();

	m_pScreenManage->ClearInputType();
}

void XBoardChild::DeleteFont()
{
	m_Font.DeleteObject();
}

void XBoardChild::SetDelegate(XDelegateSelectEquipment* p)
{
	m_pDelegate = p;
}

XDelegateSelectEquipment* XBoardChild::GetDelegate()
{
	return m_pDelegate;
}

void XBoardChild::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XBoardChild::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

CString XBoardChild::GetTranslationString(CString szKey, CString szDefault)
{
	return m_pDelegate->GetTranslationString(szKey, szDefault);
}

int XBoardChild::MessageBoxFromKey(CString szKey, CString szDefault, UINT uType)
{
	return m_pDelegate->MessageBoxFromKey(szKey, szDefault, uType);
}

int XBoardChild::GetRow()
{
	return m_nScreenNumV;
}

int XBoardChild::GetColumn()
{
	return m_nScreenNumH;
}

void XBoardChild::CopyVecBoardToVecScreeInfo(VEC_SCREENINFO& VecScreenInfo)
{
	int nCount=m_nScreenNumH*m_nScreenNumV;

	int nIndex=m_pScreenManage->GetBeginIndex();

	for(int i = 0; i < m_nScreenNumH; i++)
	{
		for(int j = 0; j < m_nScreenNumV; j++)
		{
			XScreenInfo* pInfo=new XScreenInfo;

			pInfo->SetScreenIndex(nIndex);

			VecScreenInfo.push_back(pInfo);

			nIndex++;
		}
	}

	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nBoardIndex=pOutput->GetBoardIndex();

		int nScreenIndex1=pOutput->GetScreenIndex();

		int nScreenIndex2=pOutput->GetScreenIndex2();

		int nScreenIndex3=pOutput->GetScreenIndex3();

		int nScreenIndex4=pOutput->GetScreenIndex4();

		BOOL bIsTwoScreen=pOutput->GetIsTwoScreen();

		MAP_NUMOFSCREEN& MapNumOfScreen=pOutput->GetMapNumOfScreen();

		switch(m_nScreenModel)
		{
		case SCREENMODEL_SPLIC:
			{
				for(VEC_SCREENINFO::iterator iter=VecScreenInfo.begin();iter!=VecScreenInfo.end();++iter)
				{
					XScreenInfo* pInfo=*iter;

					int nScreenIndex=pInfo->GetScreenIndex();

					if(nScreenIndex==nScreenIndex1
						||nScreenIndex==nScreenIndex2)
					{
						MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.find(nScreenIndex);

						if(iter!=MapNumOfScreen.end())
						{
							int nNum=iter->second;

							pInfo->SetNumOfScreen(nNum);
						}

						pInfo->SetBoardIndex(nBoardIndex);

						pInfo->SetIsTwoScreen(bIsTwoScreen);
					}
				}
			}
			break;
		case SCREENMODEL_MATRIX:
			{
				for(VEC_SCREENINFO::iterator iter=VecScreenInfo.begin();iter!=VecScreenInfo.end();++iter)
				{
					XScreenInfo* pInfo=*iter;

					int nScreenIndex=pInfo->GetScreenIndex();

					if(nScreenIndex==nScreenIndex1
						||nScreenIndex==nScreenIndex2
						||nScreenIndex==nScreenIndex3
						||nScreenIndex==nScreenIndex4)
					{
						MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.find(nScreenIndex);

						if(iter!=MapNumOfScreen.end())
						{
							int nNum=iter->second;

							pInfo->SetNumOfScreen(nNum);
						}

						pInfo->SetScreenModel(m_nScreenModel);

						pInfo->SetBoardIndex(nBoardIndex);

						pInfo->SetIsTwoScreen(bIsTwoScreen);
					}
				}
			}
			break;
		default:
			break;
		}
	}
}

int XBoardChild::GetEquipment()
{
	return m_nEquipment;
}

void XBoardChild::SetEquipment(int n)
{
	m_nEquipment=n;
}

BOOL XBoardChild::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Init();

	//ReloadInterface();

	return FALSE;  
}

void XBoardChild::OnPaint()
{
	CPaintDC dc(this); 

}

void XBoardChild::ReloadInterface()
{

}

void XBoardChild::SetIsMenuSet(BOOL IsmenuSet)
{
	m_IsMenuSet=IsmenuSet;
}

BOOL XBoardChild::GetIsMenuSet()
{
	return m_IsMenuSet;
}

void XBoardChild::Init()
{
	InitFont();

	InitVec();

	InitIndexWnd();

	InitVecEquipment();

	AdjustScrollV();	

	if(m_IsMenuSet)
		ResetVecEquipment();
	else
		SetVecEquipment();
}

void XBoardChild::SetVecEquipment()
{
	//TRACE(_T("Begin=%d\n"),GetTickCount());

	VEC_BASESCREENMANAGE& VecBaseScreenManage=m_pScreenManage->GetVecBaseScreenManage();

	for(VEC_BASESCREENMANAGE::iterator iter=VecBaseScreenManage.begin();iter!=VecBaseScreenManage.end();++iter)
	{
		XBaseScreenManage* pBase=*iter;

		XMenuScreenSetInfo* pInfo=pBase->GetMenuScreenSetInfo();

		VEC_OUTPUTINFO& pOutput=pInfo->GetVecOutputInfo();

		for(VEC_OUTPUTINFO::iterator iter=pOutput.begin();iter!=pOutput.end();++iter)
		{
			//TRACE(_T("Begin=%d\n"),GetTickCount());

			XOutputInfo* pOutInfo=*iter;

			int nBoardIndex=pOutInfo->GetBoardIndex();

			MAP_NUMOFSCREEN& MapNumOfScreen=pOutInfo->GetMapScreenNum();

			for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
			{
				XEquipmentOutput* pOldOutput=*iter;

				int nOldBoardIndex=pOldOutput->GetBoardIndex();

				if(nBoardIndex==nOldBoardIndex)
				{
					pOldOutput->SetInputName(pOutInfo->GetInputName());

					pOldOutput->SetIsFirstPan(pOutInfo->GetIsFirstPan());

					pOldOutput->SetIsTwoScreen(pOutInfo->GetIsTwoScreen());

					pOldOutput->SetCorrpScreenNum(pOutInfo->GetCorrpScreenNum());

					pOldOutput->SetScreenIndex(pOutInfo->GetScreenIndex1());

					pOldOutput->SetScreenIndex2(pOutInfo->GetScreenIndex2());

					pOldOutput->SetScreenIndex3(pOutInfo->GetScreenIndex3());

					pOldOutput->SetScreenIndex4(pOutInfo->GetScreenIndex4());

					pOldOutput->SetCheckNum(pOutInfo->GetCheckNum());

					pOldOutput->SetMapNumOfScreen(MapNumOfScreen);
				}

				pOldOutput->SetComboBox();

				pOldOutput->UpdateImage();

				pOldOutput->UpdateComboBox();

				pOldOutput->UpdateText();
			}

			//TRACE(_T("End=%d\n"),GetTickCount());
		}
	}

	//TRACE(_T("End=%d\n"),GetTickCount());
}

void XBoardChild::ResetVecEquipment()
{
	XMenuScreenSetInfo* pInfo=m_pScreenManage->GetMenuScreenSetInfo();

	VEC_OUTPUTINFO& pOutput=pInfo->GetVecOutputInfo();

	for(VEC_OUTPUTINFO::iterator iter=pOutput.begin();iter!=pOutput.end();++iter)
	{
		XOutputInfo* pOutInfo=*iter;

		int nBoardIndex=pOutInfo->GetBoardIndex();

		MAP_NUMOFSCREEN& MapNumOfScreen=pOutInfo->GetMapScreenNum();

		for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
		{
			XEquipmentOutput* pOldOutput=*iter;

			int nOldBoardIndex=pOldOutput->GetBoardIndex();

			if(nBoardIndex==nOldBoardIndex)
			{
				pOldOutput->SetInputName(pOutInfo->GetInputName());

				pOldOutput->SetIsFirstPan(pOutInfo->GetIsFirstPan());

				pOldOutput->SetIsTwoScreen(pOutInfo->GetIsTwoScreen());

				pOldOutput->SetCorrpScreenNum(pOutInfo->GetCorrpScreenNum());

				pOldOutput->SetScreenIndex(pOutInfo->GetScreenIndex1());

				pOldOutput->SetScreenIndex2(pOutInfo->GetScreenIndex2());

				pOldOutput->SetScreenIndex3(pOutInfo->GetScreenIndex3());

				pOldOutput->SetScreenIndex4(pOutInfo->GetScreenIndex4());

				pOldOutput->SetCheckNum(pOutInfo->GetCheckNum());

				pOldOutput->SetMapNumOfScreen(MapNumOfScreen);
			}

			pOldOutput->SetComboBox();

			pOldOutput->UpdateImage();

			pOldOutput->UpdateComboBox();

			pOldOutput->UpdateText();
		}
	}
}

void XBoardChild::InitFont()
{
	m_Font.CreateFont(   
		FONT_SIZE,    
		0,                
		0,                
		0,                 
		0,                 
		FALSE,             
		FALSE,              
		FALSE,              
		DEFAULT_CHARSET,     
		OUT_DEFAULT_PRECIS,   
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,      
		DEFAULT_PITCH,         
		APP_FONT);
}
CFont* XBoardChild::GetFont()
{
	return &m_Font;
}

void XBoardChild::InitVec()
{
	InitVecInput();
	InitVecOutput();
}

void XBoardChild::InitVecInput()
{
	MAP_INPUTTYPE& MapInputType=m_pScreenManage->GetMapInputType();

	int nEquipment=m_nEquipment/4;

	for(int i=0;i<nEquipment;i++)
	{
		int nIndex=i+1;

		XEquipmentInput* pInput=new XEquipmentInput;
		pInput->SetInputBoardChild(this);

		MAP_INPUTTYPE::iterator iter=MapInputType.find(i);

		if(MapInputType.size()==0)
		{
			pInput->SetInputType(INPUTTYPE_NULL);
		}
		else
		{
			if(iter!=MapInputType.end())
			{
				XInputType* pInutType=iter->second;
				pInput->SetInputType(pInutType->GetType());
			}
			else
			{
				pInput->SetInputType(INPUTTYPE_NOPANE);
			}
		}

		pInput->SetIndex(nIndex);
		m_VecEquipmentInput.push_back(pInput);
	}
}

void XBoardChild::InitVecOutput()
{
	MAP_BOARDTYPE& MapBoardType=m_pScreenManage->GetMapBoardType();

	int nEquipment=m_nEquipment/4;

	for(int i=0;i<nEquipment;i++)
	{
		int nIndex=i+1;

		MAP_BOARDTYPE::iterator iter=MapBoardType.find(nIndex);

		if(MapBoardType.size()==0)
		{
			XEquipmentOutput* pOutput=new XEquipmentOutput;
			pOutput->SetOutputBoardChild(this);
			pOutput->SetBoardIndex(nIndex);
			pOutput->SetBoardType(BOARDTYPE_NULL);
			pOutput->SetScreenIndex(-1);
			pOutput->SetScreenIndex2(-1);
			pOutput->SetScreenIndex3(-1);
			pOutput->SetScreenIndex4(-1);
			m_VecEquipmentOutput.push_back(pOutput);
		}
		else
		{
			if(iter!=MapBoardType.end())
			{
				int nType=iter->second;

				XEquipmentOutput* pOutput=new XEquipmentOutput;
				pOutput->SetOutputBoardChild(this);
				pOutput->SetBoardIndex(nIndex);
				pOutput->SetBoardType(nType);
				pOutput->SetScreenIndex(-1);
				pOutput->SetScreenIndex2(-1);
				pOutput->SetScreenIndex3(-1);
				pOutput->SetScreenIndex4(-1);
				m_VecEquipmentOutput.push_back(pOutput);
			}
			else
			{
				XEquipmentOutput* pOutput=new XEquipmentOutput;
				pOutput->SetOutputBoardChild(this);
				pOutput->SetBoardIndex(nIndex);
				pOutput->SetBoardType(BOARDTYPE_NOPANE);
				pOutput->SetScreenIndex(-1);
				pOutput->SetScreenIndex2(-1);
				pOutput->SetScreenIndex3(-1);
				pOutput->SetScreenIndex4(-1);
				m_VecEquipmentOutput.push_back(pOutput);
			}
		}
	}
}

void XBoardChild::InitVecEquipment()
{
	InitVecEquipmentInput();

	InitVecEquipmentOutput();
}

void XBoardChild::InitVecEquipmentInput()
{
	CRect rect;
	GetClientRect(&rect);

	int nDistance=DISTANCE;
	int nEquipmentWidth=260;
	int nEquipmentHight=25+EQUIPMENT_TEXTHEIGHT;

	int nBeginX=m_TextRect.right;
	int nBeginY=rect.top;

	int nX=nBeginX+nDistance;
	int nY=nBeginY;

	for(VEC_EQUIPMENTINPUT::iterator iter=m_VecEquipmentInput.begin();iter!=m_VecEquipmentInput.end();++iter)
	{
		XEquipmentInput* pInput=*iter;

		CRect rect(nX,nY,nX+nEquipmentWidth,nY+nEquipmentHight);

		pInput->SetRect(rect);

		pInput->Init();

		pInput->UpdateText();

		nY=nY+nDistance+nEquipmentHight;
	}
}

void XBoardChild::InitVecEquipmentOutput()
{
	CRect rect;
	GetClientRect(&rect);

	int nDistance=DISTANCE;

	int nWidth=260+nDistance;
	int nHight=25;

	int nEquipmentWidth=260+CHEVKBOX_WIDTH;
	int nEquipmentHight=25+EQUIPMENT_TEXTHEIGHT;

	int nBeginX=m_TextRect.right+nWidth;
	int nBeginY=rect.top;

	int nX=nBeginX+nDistance;
	int nY=nBeginY;

	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nBoardIndex=pOutput->GetBoardIndex();

		CRect rect(nX,nY,nX+nEquipmentWidth,nY+nEquipmentHight);

		pOutput->SetRect(rect);

		pOutput->Init();

		pOutput->SetScreenModel(m_nScreenModel);

		pOutput->InitComboBox();

		pOutput->UpdateComboBox();

		pOutput->UpdateText();

		nY=nY+nDistance+nEquipmentHight;
	}
}

void XBoardChild::OnSelchangeCombo()
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		pOutput->UpdateComboBox();

		pOutput->UpdateText();
	}
}

void XBoardChild::InitIndexWnd()
{
	CRect rect;
	GetClientRect(&rect);

	int nDistance=DISTANCE;

	int nTextWidth=nDistance+20;
	int nTextHight=25;

	int nBeginX=rect.left;
	int nBeginY=rect.top;

	int nX=nBeginX;
	int nY=nBeginY;

	int nEquipment=m_nEquipment/4;
	for(int i=0;i<nEquipment;i++)
	{
		int nIndex=i+1;
		CString szText;

		szText.Format(_T("%d"),nIndex);

		CRect rect(nX,nY,nX+nTextWidth,nY+nTextHight);

		m_TextRect=rect;

	    HYXText* pTextWnd=new HYXText;
		pTextWnd->Create(WS_CHILD|WS_VISIBLE,rect,this,0);
		pTextWnd->SetText(szText);
		pTextWnd->ShowWindow(SW_SHOW);
		pTextWnd->UpdateWindow();

		m_VecViewText.push_back(pTextWnd);

		nY=nY+nDistance+nTextHight+EQUIPMENT_TEXTHEIGHT;
	}
}

void XBoardChild::AdjustScrollV()
{
	CRect rt;
	GetClientRect(rt);

	int nScrollHeight=GetScrollHight();

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si) ;

	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = nScrollHeight;
	si.nPage = rt.Height();
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (m_nScrollPosV > si.nPos)
	{
		m_nScrollPosV = si.nPos;
	}
}

int XBoardChild::GetScrollHight()
{
	int nBtnHight=25;

	int nEquipment=m_nEquipment/4;

	int nHight=(DISTANCE+nBtnHight+EQUIPMENT_TEXTHEIGHT)*nEquipment-DISTANCE;

	return nHight;
}

VEC_EQUIPMENTINPUT& XBoardChild::GetVecEquipmentInput()
{
	return m_VecEquipmentInput;
}

VEC_EQUIPMENTOUTPUT& XBoardChild::GetVecEquipmentOutput()
{
	return m_VecEquipmentOutput;
}

void XBoardChild::SetOSD(XEquipmentInput* pDisplay)
{
	for(VEC_EQUIPMENTINPUT::iterator iter=m_VecEquipmentInput.begin();iter!=m_VecEquipmentInput.end();++iter)
	{
		XEquipmentInput* pEquipment=*iter;

		if(pEquipment==pDisplay)
		{
			int nIndex=pEquipment->GetIndex();

			XSetOSD OSDDlg;

			OSDDlg.SetScreenManage(m_pScreenManage);

			OSDDlg.SetInputIndex(nIndex);

			if(IDOK==OSDDlg.DoModal())
			{
				int nOSDIndex=OSDDlg.GetOSDIndex();

				m_pScreenManage->SetOSD(nOSDIndex);
			}	
		}
	}
}

void XBoardChild::SetScreenNumH(int n)
{
	m_nScreenNumH=n;
}

int XBoardChild::GetScreenNumH()
{
	return m_nScreenNumH;
}

void XBoardChild::SetScreenNumV(int n)
{
	m_nScreenNumV=n;
}

int XBoardChild::GetScreenNumV()
{
	return m_nScreenNumV;
}

int XBoardChild::GetBeginScreenIndex()
{
	return m_pScreenManage->GetBeginIndex();
}

void XBoardChild::SetVecBoard(XScreenInfo* pInfo)
{
	int nTempScreenIndex=pInfo->GetScreenIndex();

	int nTempBoardIndex=pInfo->GetBoardIndex();

	int nTempCurBoardIndex=pInfo->GetCurBoardIndex();

	BOOL bIsTwoScreen=pInfo->GetIsTwoScreen();

	int nNumOfScreen=pInfo->GetNumOfScreen();

	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nScreenIndex=pOutput->GetScreenIndex();

		int nScreenIndex2=pOutput->GetScreenIndex2();

		int nScreenIndex3=pOutput->GetScreenIndex3();

		int nScreenIndex4=pOutput->GetScreenIndex4();

		int nBoardIndex=pOutput->GetBoardIndex();

		MAP_NUMOFSCREEN& MapNumOfScreen=pOutput->GetMapNumOfScreen();

		//矩阵拼接 通用
		if(nNumOfScreen==0)
		{
			if(nScreenIndex==nTempScreenIndex
				&&nTempCurBoardIndex==nBoardIndex)
			{
				if(!bIsTwoScreen)
				{
					pOutput->SetScreenIndex(-1);
				}
			}
		}
		else if(nNumOfScreen==1)
		{
			if(nScreenIndex==nTempScreenIndex
				&&nTempCurBoardIndex==nBoardIndex)
			{
				pOutput->SetScreenIndex(-1);
			}
		}
		else if(nNumOfScreen==2)
		{
			if(nScreenIndex2==nTempScreenIndex
				&&nTempCurBoardIndex==nBoardIndex)
			{
				pOutput->SetScreenIndex2(-1);
			}
		}
		else if(nNumOfScreen==3)
		{
			if(nScreenIndex3==nTempScreenIndex
				&&nTempCurBoardIndex==nBoardIndex)
			{
				pOutput->SetScreenIndex3(-1);
			}
		}
		else if(nNumOfScreen==4)
		{
			if(nScreenIndex4==nTempScreenIndex
				&&nTempCurBoardIndex==nBoardIndex)
			{
				pOutput->SetScreenIndex4(-1);
			}
		}

		MAP_NUMOFSCREEN::iterator iter1=MapNumOfScreen.find(nTempScreenIndex);

		if(iter1!=MapNumOfScreen.end())
		{
			MapNumOfScreen.erase(iter1);
		}

		pOutput->UpdateImage();
	}
}

void XBoardChild::SetVecBoardOutpout(XScreenInfo* pInfo)
{
	BOOL bIsTwoScreen=pInfo->GetIsTwoScreen();

	int nScreenIndex=pInfo->GetScreenIndex();

	int nBoardIndexInfo=pInfo->GetBoardIndex();

	int nNumOfScreen=pInfo->GetNumOfScreen();


	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nBoardIndex=pOutput->GetBoardIndex();

		int nScreenIndex1=pOutput->GetScreenIndex();

		int nScreenIndex2=pOutput->GetScreenIndex2();

		int nScreenIndex3=pOutput->GetScreenIndex3();

		int nScreenIndex4=pOutput->GetScreenIndex4();

		//////////////////////////////////////////////

		int nScreenModel=pOutput->GetScreenModel();

		switch(nScreenModel)
		{
		case SCREENMODEL_SPLIC:
			{
				//拼接
				if(nBoardIndex==pInfo->GetBoardIndex())
				{
					if(!bIsTwoScreen)
					{
						if(nScreenIndex1==-1)
						{
							pOutput->SetScreenIndex(nScreenIndex);
						}
					}
					else
					{
						if(nScreenIndex1==-1&&
							nNumOfScreen==1)
						{
							pOutput->SetScreenIndex(nScreenIndex);

						}
						else if(nScreenIndex2==-1
							&&nNumOfScreen==2)
						{
							pOutput->SetScreenIndex2(nScreenIndex);
						}	

						MAP_NUMOFSCREEN& MapNumOfScreen=pOutput->GetMapNumOfScreen();

						MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.find(nScreenIndex);

						if(iter!=MapNumOfScreen.end())
						{
							iter->second=nNumOfScreen;

						}
						else
						{
							MapNumOfScreen.insert(std::pair<int,int>(nScreenIndex,nNumOfScreen));
						}
					}
				}
			}
			break;
		case SCREENMODEL_MATRIX:
			{
				if(nBoardIndex==pInfo->GetBoardIndex())
				{
					if(nScreenIndex1==-1&&
						nNumOfScreen==1)
					{
						pOutput->SetScreenIndex(nScreenIndex);
					}
					else if(nScreenIndex2==-1&&
						nNumOfScreen==2)
					{
						pOutput->SetScreenIndex2(nScreenIndex);
					}
					else if(nScreenIndex3==-1&&
						nNumOfScreen==3)
					{
						pOutput->SetScreenIndex3(nScreenIndex);
					}
					else if(nScreenIndex4==-1&&
						nNumOfScreen==4)
					{
						pOutput->SetScreenIndex4(nScreenIndex);
					}

					MAP_NUMOFSCREEN& MapNumOfScreen=pOutput->GetMapNumOfScreen();

					MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.find(nScreenIndex);

					if(iter!=MapNumOfScreen.end())
					{
						iter->second=nNumOfScreen;
					}
					else
					{
						MapNumOfScreen.insert(std::pair<int,int>(nScreenIndex,nNumOfScreen));
					}
				}
			}
			break;
		default:
			break;
		}

		pOutput->UpdateComboBox();

		pOutput->UpdateText();	
	}
}

BOOL XBoardChild::CheckScreenNum(int nBoardIndex)
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nTempBoardIndex=pOutput->GetBoardIndex();

		if(nTempBoardIndex==nBoardIndex)
		{
			int nScreenIndex1=pOutput->GetScreenIndex();

			int nScreenIndex2=pOutput->GetScreenIndex2();

			if(nScreenIndex1==-1
				||nScreenIndex2==-1)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}


BOOL XBoardChild::CheckRepeat(int nScreenIndex)
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nScreenIndex1=pOutput->GetScreenIndex();

		int nScreenIndex2=pOutput->GetScreenIndex2();

		if(nScreenIndex==nScreenIndex1
			||nScreenIndex==nScreenIndex2)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void XBoardChild::UpdateText(int nBoard)
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		pOutput->UpdateText();
	}
}

void XBoardChild::UpdataImage(int nBoard)
{
	for(VEC_EQUIPMENTOUTPUT::iterator iter=m_VecEquipmentOutput.begin();iter!=m_VecEquipmentOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		pOutput->UpdateImage();
	}
}

VEC_SCREENINFO& XBoardChild::GetVecScreenInfo()
{
	return m_VecScreenInfo;
}

void XBoardChild::SetVecScreenInfo(VEC_SCREENINFO& VecScreenInfo)
{
	//m_VecScreenInfo=VecScreenInfo;

	for(VEC_SCREENINFO::iterator iter=VecScreenInfo.begin();iter!=VecScreenInfo.end();++iter)
	{
		XScreenInfo* pInfo=*iter;

		XScreenInfo* pNew=new XScreenInfo;
		pNew->SetBoardIndex(pInfo->GetBoardIndex());
		pNew->SetCurBoardIndex(pInfo->GetCurBoardIndex());
		pNew->SetIsTwoScreen(pInfo->GetIsTwoScreen());
		pNew->SetLBDclick(pInfo->GetLBDclick());
		pNew->SetNumOfScreen(pInfo->GetNumOfScreen());
		pNew->SetScreenIndex(pInfo->GetScreenIndex());

		m_VecScreenInfo.push_back(pNew);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void XBoardChild::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si) ;
	si.fMask = SIF_ALL ;

	GetScrollInfo(SB_VERT, &si) ;

	int pos = si.nPos;

	switch (nSBCode)
	{
	case SB_TOP:
		si.nPos = si.nMin ;
		break ;

	case SB_BOTTOM:
		si.nPos = si.nMax ;
		break ;

	case SB_LINEUP:
		si.nPos -= 20;
		break ;

	case SB_LINEDOWN:
		si.nPos += 20 ;
		break ;

	case SB_PAGEUP:
		si.nPos -= si.nPage ;
		break ;

	case SB_PAGEDOWN:
		si.nPos += si.nPage ;
		break ;

	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos ;
		break ;

	default:
		break ;         
	}

	si.fMask = SIF_POS ;

	SetScrollInfo(SB_VERT, &si, TRUE);

	GetScrollInfo(SB_VERT, &si) ;

	if (si.nPos != pos)
	{                    
		if (!m_bScrollTimerV)
		{
			SetTimer(1, SCROOL_TIME_ELAPSE, NULL);

			m_bScrollTimerV = TRUE;
		}
	}

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}


void XBoardChild::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		SCROLLINFO si;

		GetScrollInfo(SB_VERT, &si) ;

		int nPos = si.nPos;

		//TRACE("XOSDGrid::ScrollV Pos:%d\n", nPos);

		if (nPos != m_nScrollPosV)
		{
			ScrollWindow(0, m_nScrollPosV - nPos, NULL, NULL);

			m_nScrollPosV = nPos;

			m_nScrollTimerV = 0;

			Invalidate();
		}
		else
		{
			m_nScrollTimerV++;

			if (m_nScrollTimerV >= 5)
			{
				KillTimer(1);

				m_bScrollTimerV = FALSE;
			}
		}
	}

	CWnd::OnTimer(nIDEvent);
}