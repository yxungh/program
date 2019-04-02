#include "StdAfx.h"
#include "HandleListCtrl.h"

HandleListCtrl::HandleListCtrl(void)
{
}


HandleListCtrl::~HandleListCtrl(void)
{
}

void HandleListCtrl::InitList(CListCtrl* pListCtrl, int nColumnCount, BOOL bCheckBox,
	int nColumnWidth)
{
	DWORD dwNewStyle = pListCtrl->GetExtendedStyle()
		| LVS_EX_FLATSB
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES;
	
	pListCtrl->ModifyStyle(0, LVS_SINGLESEL);

	if (bCheckBox)
	{
		dwNewStyle |= LVS_EX_CHECKBOXES;
	}

	pListCtrl->SetExtendedStyle(dwNewStyle);

	int nRealColumnWidth = 0;

	if (-1 == nColumnWidth)
	{
		CRect tempRect;
		pListCtrl->GetClientRect(&tempRect);

		nRealColumnWidth = tempRect.Width() / nColumnCount - 1;
	}
	else
	{
		nRealColumnWidth = nColumnWidth;
	}
	
	for (int i = 0; i < nColumnCount; i++)
	{
		pListCtrl->InsertColumn(i, _T(""), LVCFMT_LEFT, nRealColumnWidth, 0);
	}
}

int HandleListCtrl::GetListSelectItem(CListCtrl* pListCtrl)
{
	int nSelect = pListCtrl->GetSelectionMark();

	if (-1 != nSelect)
	{
		if (LVIS_SELECTED == pListCtrl->GetItemState(nSelect, LVNI_ALL | LVNI_SELECTED))
		{
			return nSelect;
		}
	}

	return -1;
}

int HandleListCtrl::GetListCheckCount(CListCtrl* pListCtrl)
{
	int nCheckCount = 0;

	int nCount = pListCtrl->GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			nCheckCount++;
		}
	}

	return nCheckCount;
}

int HandleListCtrl::GetListCheckItem(CListCtrl* pListCtrl)
{
	int nCount = pListCtrl->GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			return i;
		}
	}

	return -1;
}

CString HandleListCtrl::GetListCheckItemText(CListCtrl* pListCtrl)
{
	int nCount = pListCtrl->GetItemCount();

	CString szName;

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			szName=pListCtrl->GetItemText(i,0);
		}
	}

	return szName;
}

void HandleListCtrl::GetListCheckItemText(CListCtrl* pListCtrl,VEC_CSTRING& VecStr)
{
	int nCount = pListCtrl->GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			CString szText;

			szText=pListCtrl->GetItemText(i,0);

			VecStr.push_back(szText);
		}
	}
}

void HandleListCtrl::GetListCheckItemText(CListCtrl* pListCtrl,MAP_SELSCENE& MapScene)
{
	int nCount = pListCtrl->GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			CString szText;

			szText=pListCtrl->GetItemText(i,0);

			MapScene.insert(std::pair<int,CString>(i,szText));
		}
	}
}

void HandleListCtrl::GetListCheckNum(CListCtrl* pListCtrl,HYVEC_NUM& VecNum)
{
	int nCount = pListCtrl->GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		if(pListCtrl->GetCheck(i))
		{
			VecNum.push_back(i);
		}
	}
}


void HandleListCtrl::SetColumnText(CListCtrl* pListCtrl, int n, CString s)
{
	LVCOLUMN col;
	col.mask = LVCF_TEXT;
	col.pszText = s.GetBuffer();

	pListCtrl->SetColumn(n, &col);

	s.ReleaseBuffer();
}

void HandleListCtrl::SetListItemSelect(CListCtrl* pListCtrl, int nItem)
{
	pListCtrl->SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);

	pListCtrl->SetSelectionMark(nItem);
}