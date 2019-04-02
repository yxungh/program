#include "StdAfx.h"
#include "XEquipmentOutputWnd.h"
#include "HYXText.h"
#include "HandlePath.h"
#include "XDelegateSelectEquipment.h"
#include "CMyButton.h"



XEquipmentOutput::XEquipmentOutput(void)
{
	m_EquipmentWnd=NULL;

	m_EquipmentTextWnd=NULL;

	m_nBoardIndex = 0;

	m_bIsTwoScreen=FALSE;

	m_ChecKBox=NULL;

	m_bIsFirstPan=FALSE;

	m_nCheckNum=0;

	m_nCorrpScreenNum=CORRPSCREENNUM_ONE;

	m_nScreenModel=0;

	m_ComboBox=NULL;

	m_nBoardIndex=BOARDTYPE_SIGNALSPLICE;
}

XEquipmentOutput::~XEquipmentOutput(void)
{
	ClearEquipmentWnd();

	ClearComboBox();

	ClearEquipmentTextWnd();

	ClearMapNumOfScreen();
}

void XEquipmentOutput::ClearEquipmentWnd()
{
	if(NULL!=m_EquipmentWnd)
	{
		delete m_EquipmentWnd;

		m_EquipmentWnd=NULL;
	}
}

void XEquipmentOutput::ClearEquipmentTextWnd()
{
	if(NULL!=m_EquipmentTextWnd)
	{
		delete m_EquipmentTextWnd;

		m_EquipmentTextWnd=NULL;
	}
}


void XEquipmentOutput::ClearComboBox()
{
	if(NULL!=m_ComboBox)
	{
		delete m_ComboBox;

		m_ComboBox=NULL;
	}
}

void XEquipmentOutput::ClearMapNumOfScreen()
{
	m_NumOfScreen.clear();
}

void XEquipmentOutput::SetOutputBoardChild(XBoardChild* pChild)
{
	m_pChild=pChild;
}

XBoardChild* XEquipmentOutput::GetOutputBoardChild()
{
	return m_pChild;
}

void XEquipmentOutput::SetRect(CRect r)
{
	m_Rect = r;
}

CRect XEquipmentOutput::GetRect()
{
	return m_Rect;
}

void XEquipmentOutput::SetBoardIndex(int n)
{
	m_nBoardIndex = n;
}

int XEquipmentOutput::GetBoardIndex()
{
	return m_nBoardIndex;
}

void XEquipmentOutput::SetScreenIndex(int n)
{
	m_nScreenIndex=n;
}

int XEquipmentOutput::GetScreenIndex()
{
	return m_nScreenIndex;
}

void XEquipmentOutput::SetScreenIndex2(int n)
{
	m_nScreenIndex2=n;
}

int XEquipmentOutput::GetScreenIndex2()
{
	return m_nScreenIndex2;
}

void XEquipmentOutput::SetIsTwoScreen(BOOL b)
{
	m_bIsTwoScreen=b;
}

BOOL XEquipmentOutput::GetIsTwoScreen()
{
	return m_bIsTwoScreen;
}

void XEquipmentOutput::SetInputName(CString szName)
{
	m_szInputName=szName;
}

CString XEquipmentOutput::GetInputName()
{
	return m_szInputName;
}

void XEquipmentOutput::SetIsFirstPan(BOOL b)
{
	m_bIsFirstPan=b;
}

BOOL XEquipmentOutput::GetIsFirstPan()
{
	return m_bIsFirstPan;
}

MAP_NUMOFSCREEN& XEquipmentOutput::GetMapNumOfScreen()
{
	return m_NumOfScreen;
}

void XEquipmentOutput::SetMapNumOfScreen(MAP_NUMOFSCREEN& MapNumOfScreen)
{
	for(MAP_NUMOFSCREEN::iterator iter=MapNumOfScreen.begin();iter!=MapNumOfScreen.end();++iter)
	{
		int nFirst=iter->first;

		int nSecond=iter->second;

		m_NumOfScreen.insert(std::pair<int,int>(nFirst,nSecond));
	}
}

void XEquipmentOutput::Init()
{
	ClearEquipmentWnd();

	ClearEquipmentTextWnd();

	ClearComboBox();

	CreateEquipmentWnd();

	CreateComboBox();

	//InitComboBox();

	CreateEquipmentTextWnd();

	//UpdateText();
}

void XEquipmentOutput::CreateEquipmentWnd()
{
	CRect rect=m_Rect;
	rect.bottom=rect.bottom-EQUIPMENT_TEXTHEIGHT;
	rect.right=rect.right-CHEVKBOX_WIDTH;

	m_PaneRect=rect;

	XEquipmentOutputWnd* pWnd=new XEquipmentOutputWnd;
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pChild,0);
	pWnd->SetEquipmentOutput(this);
	pWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();
	
	m_EquipmentWnd=pWnd;
}

void XEquipmentOutput::CreateComboBox()
{
	if(m_nBoardType==BOARDTYPE_PREVIEW
		||m_nBoardType==BOARDTYPE_NOPANE)
	{
		return;
	}

	CRect rect=m_Rect;
	rect.left=m_PaneRect.right+DISTANCE;
	rect.bottom=rect.bottom-EQUIPMENT_TEXTHEIGHT;

	CComboBox* pComboBox=new CComboBox;
	ASSERT_VALID(pComboBox);
	pComboBox->Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_HASSTRINGS|WS_VSCROLL,
		rect,m_pChild,ID_BTNCHECKBOX+10);
	pComboBox->SetFont(m_pChild->GetFont());
	pComboBox->ShowWindow(SW_SHOW);
	pComboBox->UpdateWindow();

	m_ComboBox=pComboBox;
}

void XEquipmentOutput::InitComboBox()
{
	if(m_nBoardType==BOARDTYPE_SIGNALSPLICE)
	{
		m_ComboBox->AddString(m_pChild->GetDelegate()->GetTranslationString(_T("604"), _T("1路")));
	}
	else if(m_nBoardType==BOARDTYPE_MULTISPLICE)
	{
		m_ComboBox->AddString(m_pChild->GetDelegate()->GetTranslationString(_T("605"), _T("2路")));
	}
	else if(m_nBoardType==BOARDTYPE_NULL)
	{
		m_ComboBox->AddString(m_pChild->GetDelegate()->GetTranslationString(_T("604"), _T("1路")));
		m_ComboBox->AddString(m_pChild->GetDelegate()->GetTranslationString(_T("605"), _T("2路")));
	}
	else if(m_nBoardType==BOARDTYPE_MATRIX)
	{
		m_ComboBox->AddString(m_pChild->GetDelegate()->GetTranslationString(_T("703"), _T("4路")));
	}
	else if(m_nBoardType==BOARDTYPE_PREVIEW
		||m_nBoardType==BOARDTYPE_NOPANE)
	{
		return;
	}

	m_ComboBox->SetCurSel(0);
}

void XEquipmentOutput::CreateEquipmentTextWnd()
{
	CRect rect=m_Rect;
	rect.top=rect.bottom-EQUIPMENT_TEXTHEIGHT;
	rect.right=rect.right-CHEVKBOX_WIDTH;

	HYXText* pWnd=new HYXText;
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pChild,0);
	//pWnd->SetFont(m_pChild->GetFont());
	pWnd->SetTextColor(RGB(255,0,0));
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();

	m_EquipmentTextWnd = pWnd;
}

void XEquipmentOutput::UpdateImage()
{
	switch(m_nCorrpScreenNum)
	{
	case CORRPSCREENNUM_ONE:
		{
			if(m_nScreenIndex!=-1)
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_12.png")));
			}
			else
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
			}
		}
		break;
	case CORRPSCREENNUM_TWO:
		{
			if(m_nScreenIndex!=-1
				&&m_nScreenIndex2!=-1)
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_12.png")));
			}
			else
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
			}
		}
		break;
	case CORRPSCREENNUM_FOUR:
		{
			if(m_nScreenIndex!=-1
				&&m_nScreenIndex2!=-1
				&&m_nScreenIndex3!=-1
				&&m_nScreenIndex4!=-1)
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_12.png")));
			}
			else
			{
				m_EquipmentWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
			}
		}
		break;
	default:
		break;
	}
}

void XEquipmentOutput::SetCheckNum(int n)
{
	m_nCheckNum=n;
}

int XEquipmentOutput::GetCheckNum()
{
	return m_nCheckNum;
}

void XEquipmentOutput::SetComboBox()
{
	if(m_nBoardType==BOARDTYPE_PREVIEW
		||m_nBoardType==BOARDTYPE_NOPANE)
	{
		return;
	}

	m_ComboBox->SetCurSel(m_nCheckNum);
}

void XEquipmentOutput::UpdateComboBox()
{
	if(m_nBoardType==BOARDTYPE_PREVIEW
		||m_nBoardType==BOARDTYPE_NOPANE)
	{
		m_bIsTwoScreen=FALSE;
		m_nCorrpScreenNum=CORRPSCREENNUM_ONE;
		return;
	}

	m_nCheckNum=m_ComboBox->GetCurSel();

	if(m_nBoardType==BOARDTYPE_SIGNALSPLICE)
	{
		if(m_nCheckNum==0)
		{
			m_bIsTwoScreen=FALSE;
			m_nCorrpScreenNum=CORRPSCREENNUM_ONE;
		}
	}
	else if(m_nBoardType==BOARDTYPE_MULTISPLICE)
	{
		if(m_nCheckNum==0)
		{
			m_bIsTwoScreen=TRUE;
			m_nCorrpScreenNum=CORRPSCREENNUM_TWO;
		}
	}
	else if(m_nBoardType==BOARDTYPE_MATRIX)
	{
		if(m_nCheckNum==0)
		{
			m_nCorrpScreenNum=CORRPSCREENNUM_FOUR;
		}
	}
	else if(m_nBoardType==BOARDTYPE_NULL)
	{
		if(m_nCheckNum==1)
		{
			m_bIsTwoScreen=TRUE;
			m_nCorrpScreenNum=CORRPSCREENNUM_TWO;
		}
		else if(m_nCheckNum==0)
		{
			m_bIsTwoScreen=FALSE;
			m_nCorrpScreenNum=CORRPSCREENNUM_ONE;
		}
	}
}

void XEquipmentOutput::UpdateText()
{
	CString szText = _T("");
	//////////////////////////////////////////////////////////////////////////
	switch(m_nCorrpScreenNum)
	{
	case CORRPSCREENNUM_ONE:
		{
			if(m_nBoardType==BOARDTYPE_SIGNALSPLICE
				||m_nBoardType==BOARDTYPE_NULL)
			{
				if(m_nScreenIndex==-1)
				{
					szText.Format(_T("%s: %d; %s: %s; %s: %s"),
						m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
						m_nBoardIndex,

						m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
						m_pChild->GetDelegate()->GetTranslationString(_T("649"), _T("单路拼接卡")),

						m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
						m_pChild->GetDelegate()->GetTranslationString(_T("586"), _T("未设置")));	
				}
				else
				{
					szText.Format(_T("%s: %d; %s: %s; %s: %d"),
						m_pChild->GetDelegate()->GetTranslationString(_T("505"), _T("板卡")),
						m_nBoardIndex,

						m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
						m_pChild->GetDelegate()->GetTranslationString(_T("649"), _T("单路拼接卡")),

						m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
						m_nScreenIndex);	
				}
			}
			else if(m_nBoardType==BOARDTYPE_PREVIEW)
			{
				szText.Format(_T("%s: %d; %s: %s"),
					m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
					m_nBoardIndex,

					m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
					m_pChild->GetDelegate()->GetTranslationString(_T("682"), _T("预览卡")));
			}
			else if(m_nBoardType==BOARDTYPE_NOPANE)
			{
				szText.Format(_T("%s: %d; %s: %s"),
					m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
					m_nBoardIndex,

					m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
					m_pChild->GetDelegate()->GetTranslationString(_T("757"), _T("无板卡")));
			}
		}
		break;
	case CORRPSCREENNUM_TWO:
		{
			if(m_nBoardType==BOARDTYPE_MULTISPLICE
				||m_nBoardType==BOARDTYPE_NULL)
			{
				if(m_nScreenIndex==-1
					||m_nScreenIndex2==-1)
				{
					if(m_nScreenIndex!=-1
						&&m_nScreenIndex2==-1)
					{
						szText.Format(_T("%s: %d; %s: %s; %s: %d"),
							m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
							m_nBoardIndex,

							m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
							m_pChild->GetDelegate()->GetTranslationString(_T("650"), _T("双路拼接卡")),

							m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
							m_nScreenIndex);	
					}
					else if(m_nScreenIndex==-1
						&&m_nScreenIndex2==-1)
					{
						szText.Format(_T("%s: %d; %s: %s; %s: %s"),
							m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
							m_nBoardIndex,

							m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
							m_pChild->GetDelegate()->GetTranslationString(_T("650"), _T("双路拼接卡")),

							m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
							m_pChild->GetDelegate()->GetTranslationString(_T("586"), _T("未设置")));	
					}
					else if(m_nScreenIndex==-1
						&&m_nScreenIndex2!=-1)
					{
						szText.Format(_T("%s: %d; %s: %s; %s: %d"),
							m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
							m_nBoardIndex,

							m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
							m_pChild->GetDelegate()->GetTranslationString(_T("650"), _T("双路拼接卡")),

							m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
							m_nScreenIndex2);
					}
				}
				else
				{
					szText.Format(_T("%s: %d; %s: %s; %s: %d,%d"),
						m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
						m_nBoardIndex,

						m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
						m_pChild->GetDelegate()->GetTranslationString(_T("650"), _T("双路拼接卡")),

						m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
						m_nScreenIndex,m_nScreenIndex2);	
				}
			}
		}
		break;
	case CORRPSCREENNUM_FOUR:
		{
			if(m_nScreenIndex==-1
				&&m_nScreenIndex2==-1
				&&m_nScreenIndex3==-1
				&&m_nScreenIndex4==-1)
			{
				szText.Format(_T("%s: %d; %s: %s; %s: %s"),
					m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
					m_nBoardIndex,

					m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
					m_pChild->GetDelegate()->GetTranslationString(_T("754"), _T("矩阵卡")),

					m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("屏幕")),
					m_pChild->GetDelegate()->GetTranslationString(_T("586"), _T("未设置")));	
			}
			else
			{
				CString szTemp;
				if(m_nScreenIndex!=-1)
				{
					szTemp.Format(_T("%d"),m_nScreenIndex);
				}
				else
				{
					szTemp=_T("");
				}

				CString szTemp2;
				if(m_nScreenIndex2!=-1)
				{
					szTemp2.Format(_T("%d"),m_nScreenIndex2);
				}
				else
				{
					szTemp2=_T("");
				}

				CString szTemp3;
				if(m_nScreenIndex3!=-1)
				{
					szTemp3.Format(_T("%d"),m_nScreenIndex3);
				}
				else
				{
					szTemp3=_T("");
				}

				CString szTemp4;
				if(m_nScreenIndex4!=-1)
				{
					szTemp4.Format(_T("%d"),m_nScreenIndex4);
				}
				else
				{
					szTemp4=_T("");
				}
				//////////////////////////////////////////////////////////////////////////
				CString szTemp5=szTemp+_T(",")+szTemp2+_T(",")+szTemp3+_T(",")+szTemp4;

				szText.Format(_T("%s: %d; %s: %s; %s: %s"),
					m_pChild->GetDelegate()->GetTranslationString(_T("505"), _T("板卡")),
					m_nBoardIndex,

					m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
					m_pChild->GetDelegate()->GetTranslationString(_T("754"), _T("矩阵卡")),

					m_pChild->GetDelegate()->GetTranslationString(_T("570"), _T("对应屏幕")),
					szTemp5);	
			}
		}
		break;
	default:
		break;
	}

	//////////////////////////////////////////////////////////////////////////

	m_EquipmentTextWnd->SetText(szText);

	UpdateImage();
}

void XEquipmentOutput::ReloadInterface()
{
	UpdateText();
}

CRect XEquipmentOutput::GetEquipmentRect()
{
	CRect rect;

	m_EquipmentWnd->GetWindowRect(&rect);

	return rect;
}




