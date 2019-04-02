#pragma once
#include "XConstantIM.h"

class HandleListCtrl
{
private:
	HandleListCtrl(void);
	~HandleListCtrl(void);

public:

	//初始化列表
	static void InitList(CListCtrl* pListCtrl, int nColumnCount, BOOL bCheckBox, int nColumnWidth = -1);

	//设置列表项的文字
	static void SetColumnText(CListCtrl* pListCtrl, int n, CString s);

	//获取列表选择项
	static int GetListSelectItem(CListCtrl* pListCtrl);

	//获取列表勾选个数
	static int GetListCheckCount(CListCtrl* pListCtrl);

	//获取列表勾选项
	static int GetListCheckItem(CListCtrl* pListCtrl);

	//获取列表勾选项的文字
	static CString GetListCheckItemText(CListCtrl* pListCtrl);

	//获取列表勾选项的文字
	static void GetListCheckItemText(CListCtrl* pListCtrl,VEC_CSTRING& VecStr);

	//获取列表勾选项的文字
	static void GetListCheckItemText(CListCtrl* pListCtrl,MAP_SELSCENE& MapScene);

	//获取列表勾选项集合
	static void GetListCheckNum(CListCtrl* pListCtrl,HYVEC_NUM& VecNum);

	//设置列表项选中
	static void SetListItemSelect(CListCtrl* pListCtrl, int nItem);


};

