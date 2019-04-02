#pragma once

class HYXDelegateOutputNode
{
public:
	HYXDelegateOutputNode(void);
	~HYXDelegateOutputNode(void);

	//获取字符串
	virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//调整网格
	virtual void AdjustGrid() = 0;

	//调整水平滚动
	virtual void AdjustScrollV() = 0;
};

