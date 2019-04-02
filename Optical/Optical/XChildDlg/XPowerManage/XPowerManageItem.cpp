#include "Stdafx.h"
#include "XPowerManageItem.h"
#include "XPowerManage.h"
#include "XTranslationManage.h"
#include "XBtn.h"
#include "XText.h"


XPowerManageItem::XPowerManageItem():
	m_szFilePath(_T("")),
	m_nID(0),
	m_szText(_T("")),
	m_pParent(NULL),
	m_pBtn(NULL),
	m_pText(NULL)
{
	m_Rect.SetRectEmpty();
}

XPowerManageItem::~XPowerManageItem()
{
	ClearBtn();
	ClearText();
}

void XPowerManageItem::ClearBtn()
{
	if(NULL!=m_pBtn)
	{
		m_pBtn->DestroyWindow();
		delete m_pBtn;
		m_pBtn=NULL;
	}
}

void XPowerManageItem::ClearText()
{
	if(NULL!=m_pText)
	{
		m_pText->DestroyWindow();
		delete m_pText;
		m_pText=NULL;
	}
}

void XPowerManageItem::Init()
{
	ClearBtn();
	ClearText();

	CreateBtn();
	CreateText();
}

void XPowerManageItem::CreateBtn()
{
	CRect rect=m_Rect;
	rect.bottom=rect.bottom-TEXT_HIGHT;
	rect.left=rect.left+6;
	rect.right=rect.right-6;
	rect.top=rect.top+12;

	XBtn* pBtn=new XBtn;
	pBtn->Create(WS_CHILD|WS_VISIBLE,rect,m_pParent,m_nID);
	pBtn->SetImage(m_szFilePath);
	pBtn->ShowWindow(SW_SHOW);
	pBtn->UpdateWindow();

	m_pBtn=pBtn;
}

void XPowerManageItem::CreateText()
{
	CRect rect=m_Rect;
	rect.top=rect.bottom-TEXT_HIGHT;

	XText* pText=new XText;
	pText->Create(WS_CHILD|WS_VISIBLE,rect,m_pParent,0);
	pText->SetTextColor(RGB(80,80,80));
	pText->SetText(m_szText);
	pText->SetTextSize(8);
	pText->ShowWindow(SW_SHOW);
	pText->UpdateWindow();
	
	m_pText=pText;
}

void XPowerManageItem::SetText()
{
	if(NULL!=m_pText)
	{
		switch(m_nID)
		{
		case SUBBTNTYPE_USERMANAGE:
			{
				m_pText->SetText(XTranslationManage::GetInstance()->GetTranslationString(_T("18")));
			}
			break;
		case SUBBTNTYPE_NODEMANAGE:
			{
				m_pText->SetText(XTranslationManage::GetInstance()->GetTranslationString(_T("29")));
			}
			break;
		default:
			break;
		}
	}
}