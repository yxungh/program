#include "StdAfx.h"
#include "XEquipmentInputWnd.h"
#include "HYXText.h"
#include "HandlePath.h"
#include "XDelegateSelectEquipment.h"


XEquipmentInput::XEquipmentInput(void)
{
	m_EquipmentWnd=NULL;

	m_EquipmentTextWnd=NULL;

	m_Index = 0;

	m_nInputType=INPUTTYPE_NULL;
}

XEquipmentInput::~XEquipmentInput(void)
{
	ClearEquipmentWnd();

	ClearEquipmentTextWnd();
}

void XEquipmentInput::ClearEquipmentWnd()
{
	if(NULL!=m_EquipmentWnd)
	{
		delete m_EquipmentWnd;

		m_EquipmentWnd=NULL;
	}
}

void XEquipmentInput::ClearEquipmentTextWnd()
{
	if(NULL!=m_EquipmentTextWnd)
	{
		delete m_EquipmentTextWnd;

		m_EquipmentTextWnd=NULL;
	}
}

void XEquipmentInput::SetInputBoardChild(XBoardChild* pChild)
{
	m_pChild=pChild;
}

XBoardChild* XEquipmentInput::GetInputBoardChild()
{
	return m_pChild;
}

void XEquipmentInput::SetRect(CRect r)
{
	m_Rect = r;
}

CRect XEquipmentInput::GetRect()
{
	return m_Rect;
}

void XEquipmentInput::SetIndex(int n)
{
	m_Index = n;
}

int XEquipmentInput::GetIndex()
{
	return m_Index;
}

void XEquipmentInput::SetInputType(int n)
{
	m_nInputType=n;
}

void XEquipmentInput::SetInputName(CString szName)
{
	m_szInputName=szName;
}

CString XEquipmentInput::GetInputName()
{
	return m_szInputName;
}

void XEquipmentInput::Init()
{
	ClearEquipmentWnd();

	ClearEquipmentTextWnd();

	CreateEquipmentWnd();

	CreateEquipmentTextWnd();

	//UpdateText();
}

void XEquipmentInput::CreateEquipmentWnd()
{
	CRect rect=m_Rect;
	rect.bottom=rect.bottom-EQUIPMENT_TEXTHEIGHT;

	XEquipmentInputWnd* pWnd=new XEquipmentInputWnd;
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pChild,0);
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();
	pWnd->SetImage(HandlePath::GetPhotoPath(_T("Board_0.png")));
	pWnd->SetEquipmentInput(this);

	m_EquipmentWnd=pWnd;
}


void XEquipmentInput::CreateEquipmentTextWnd()
{
	CRect rect=m_Rect;
	rect.top=rect.bottom-EQUIPMENT_TEXTHEIGHT;

	HYXText* pWnd=new HYXText;
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pChild,0);
	pWnd->SetTextColor(RGB(255,0,0));
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();

	m_EquipmentTextWnd = pWnd;
}

void XEquipmentInput::UpdateText()
{
	CString szType;
	switch(m_nInputType)
	{
	case INPUTTYPE_2K:
		szType=m_pChild->GetDelegate()->GetTranslationString(_T("542"), _T("2K HDMI/DVI"));
		break;
	case INPUTTYPE_4K:
		szType=m_pChild->GetDelegate()->GetTranslationString(_T("543"), _T("4K HDMI/DVI"));
		break;
	case INPUTTYPE_IP2K:
	case INPUTTYPE_IP4K:
		szType=m_pChild->GetDelegate()->GetTranslationString(_T("627"), _T("IPC卡"));
		break;
	case INPUTTYPE_VGA:
		szType=_T("VGA");
		break;
	case INPUTTYPE_SDI:
		szType=_T("SDI");
		break;
	case INPUTTYPE_AV:
		szType=_T("AV");
		break;
	case INPUTTYPE_NOPANE:
		szType=m_pChild->GetDelegate()->GetTranslationString(_T("757"), _T("无板卡"));
		break;
	default:
		break;
	}

	CString szText=_T("");
	if(m_nInputType==INPUTTYPE_NULL)
	{
		szText.Format(_T("%s:%d"),
			m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
			m_Index);
	}
	else
	{
		szText.Format(_T("%s:%d,%s:%s"),
			m_pChild->GetDelegate()->GetTranslationString(_T("683"), _T("槽位")),
			m_Index,
			m_pChild->GetDelegate()->GetTranslationString(_T("361"), _T("类型")),
			szType);
	}

	m_EquipmentTextWnd->SetText(szText);
}

void XEquipmentInput::ReloadInterface()
{
	UpdateText();
}

CRect XEquipmentInput::GetEquipmentRect()
{
	CRect rect;

	m_EquipmentWnd->GetWindowRect(&rect);

	return rect;
}



