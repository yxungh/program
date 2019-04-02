#include "StdAfx.h"
#include "XUDPWatchPaneToolBar.h"
#include "XUDPWatchPane.h"
#include "..\resource.h"

BOOL XUDPWatchPaneToolBar::OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText ) const
{
	switch(pButton->m_nID)
	{
	case ID_CLEAR:
		{
			strTTText = m_Pane->GetTranslationString(_T("328"), _T("Çå¿Õ"));
		}
		break;
	default:
		break;
	}

	return TRUE;
}