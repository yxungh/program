#include "StdAfx.h"
#include "XSetListCtrl.h"

XSetListCtrl::XSetListCtrl(void)
{
}

XSetListCtrl::~XSetListCtrl(void)
{
}

void XSetListCtrl::InitList(CListCtrl* pListCtrl, int nColumnCount, BOOL bCheckBox,
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

int XSetListCtrl::GetListSelectItem(CListCtrl* pListCtrl)
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

int XSetListCtrl::GetListCheckCount(CListCtrl* pListCtrl)
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

int XSetListCtrl::GetListCheckItem(CListCtrl* pListCtrl)
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

void XSetListCtrl::SetColumnText(CListCtrl* pListCtrl, int n, CString s)
{
	LVCOLUMN col;
	col.mask = LVCF_TEXT;
	col.pszText = s.GetBuffer();

	pListCtrl->SetColumn(n, &col);

	s.ReleaseBuffer();
}

void XSetListCtrl::SetListItemSelect(CListCtrl* pListCtrl, int nItem)
{
	pListCtrl->SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);

	pListCtrl->SetSelectionMark(nItem);
}