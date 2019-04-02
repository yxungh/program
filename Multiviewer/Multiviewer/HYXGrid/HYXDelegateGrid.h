#pragma once

#include "XConstantIM.h"

class HYXGridItem;

class HYXDelegateGrid
{
public:
	HYXDelegateGrid(void);
	~HYXDelegateGrid(void);

	//获取滚动宽度
	virtual int GetScrollWidth() = 0;

	//获取滚动高度
	virtual int GetScrollHeight() = 0;

	//水平滚动
	virtual void ScrollH(int nPos) = 0;

	//垂直滚动
	virtual void ScrollV(int nPos) = 0;

	//获取输入展开设备项集合
	virtual void GetInputExpandDeviceItem(HYVEC_TREENODEITEM& VecItem) = 0;

	//获取输出展开设备项集合
	virtual void GetOutputExpandDeviceItem(HYVEC_VTREENODEITEM& VecItem) = 0;

	//表格音频区域点击
	virtual void GridRectClick(HYXGridItem* pItem) = 0;

	//表格右键弹起
	virtual void GridRButtonUp() = 0;

	//获取节点权限
	virtual BOOL GetNodePower(int nInputIndex, int nOutputIndex) = 0;
};

