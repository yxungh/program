#pragma once
#include "XConstantIM.h"
#include "XBoardChild.h"

class XEquipmentInputWnd;
class HYXText;


class XEquipmentInput
{
public:
	XEquipmentInput(void);
	~XEquipmentInput(void);

	//初始化
	void Init();

	//设置区域
	void SetRect(CRect r);

	//设置序号
	void SetIndex(int n);

	//获取区域
	CRect GetRect();

	//设置父窗口
	void SetInputBoardChild(XBoardChild* pChild);

	XBoardChild* GetInputBoardChild();

	//获取序号
	int GetIndex();

	//重载界面
	void ReloadInterface();

	//获取区域
	CRect GetEquipmentRect();

	//设置输入信号名称
	void SetInputName(CString szName);

	//获取输入信号名称
	CString GetInputName();

	//清除窗口
	void ClearEquipmentWnd();

	//清除文字窗口
	void ClearEquipmentTextWnd();

	//设置种类
	void SetEquipmentType(int n);

	void SetInputType(int n);

public:

	//更新文字
	void UpdateText();

private:

	//创建窗口
	void CreateEquipmentWnd();

	//创建文字窗口
	void CreateEquipmentTextWnd();

private:

	XBoardChild* m_pChild;

	//区域
	CRect m_Rect;

	//序号
	int m_Index;

	//输入信号mingc
	CString m_szInputName;

	//窗口
	XEquipmentInputWnd* m_EquipmentWnd;

	//文字窗口
	HYXText* m_EquipmentTextWnd;

	int m_nInputType;
};

