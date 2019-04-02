#pragma once
#include "XConstantIM.h"
#include "XBoardChild.h"

class XEquipmentOutputWnd;
class HYXText;
class CMyButton;



class XEquipmentOutput
{
public:
	XEquipmentOutput(void);
	~XEquipmentOutput(void);

	//初始化
	void Init();

	//设置区域
	void SetRect(CRect r);

	//设置序号
	void SetBoardIndex(int n);

	//获取序号
	int GetBoardIndex();

	//设置屏幕序号
	void SetScreenIndex(int n);

	//获取屏幕序号
	int GetScreenIndex();

	//设置屏幕序号
	void SetScreenIndex2(int n);

	//获取屏幕序号
	int GetScreenIndex2();

	//获取区域
	CRect GetRect();

	//设置父窗口
	void SetOutputBoardChild(XBoardChild* pChild);

	XBoardChild* GetOutputBoardChild();

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

	//清楚ComboBox
	void ClearComboBox();

	//清除文字窗口
	void ClearEquipmentTextWnd();

	//清除MAP
	void ClearMapNumOfScreen();

	//设置种类
	void SetEquipmentType(int n);

	//设置是否为两路
	void SetIsTwoScreen(BOOL b);

	//获取是否为两路
	BOOL GetIsTwoScreen();

	void SetIsFirstPan(BOOL b);

	BOOL GetIsFirstPan();

	void SetCheckNum(int n);

	int GetCheckNum();

	void SetComboBox();

	MAP_NUMOFSCREEN& GetMapNumOfScreen();

	void SetMapNumOfScreen(MAP_NUMOFSCREEN& MapNumOfScreen);

public:

	//更新文字
	void UpdateText();

	void UpdateImage();

	void UpdateComboBox();

	void InitComboBox();

private:

	//创建窗口
	void CreateEquipmentWnd();

	//创建文字窗口
	void CreateEquipmentTextWnd();

	//创建CheckBox
	void CreateCheckBox();

	//创建ComboBox
	void CreateComboBox();

	//void CreateCombo();

public:

	inline void SetBoardType(int n){m_nBoardType=n;}

	inline int GetBoardType(){return m_nBoardType;}

public:

	//设置屏幕序号
	inline void SetScreenIndex3(int n){m_nScreenIndex3=n;}

	//获取屏幕序号
	inline int GetScreenIndex3(){return m_nScreenIndex3;}

	//设置屏幕序号
	inline void SetScreenIndex4(int n){m_nScreenIndex4=n;}

	//获取屏幕序号
	inline int GetScreenIndex4(){return m_nScreenIndex4;}

	inline void SetScreenModel(int nModel){m_nScreenModel=nModel;}

	inline int GetScreenModel(){return m_nScreenModel;}

	//设置对应屏幕个数
	inline void SetCorrpScreenNum(int n){m_nCorrpScreenNum=n;}

	inline int GetCorrpScreenNum(){return m_nCorrpScreenNum;}

private:

	XBoardChild* m_pChild;

	//区域
	CRect m_Rect;

	//板卡区域
	CRect m_PaneRect;

	//板卡序号
	int m_nBoardIndex;

	//屏幕序号
	int m_nScreenIndex;

	//屏幕序号2
	int m_nScreenIndex2;

	//屏幕序号3
	int m_nScreenIndex3;

	int m_nScreenIndex4;

	//是否为两路
	BOOL m_bIsTwoScreen;

	//输入信号mingc
	CString m_szInputName;

	//窗口
	XEquipmentOutputWnd* m_EquipmentWnd;

	//文字窗口
	HYXText* m_EquipmentTextWnd;

	//checkbox
	CMyButton* m_ChecKBox;

	//ComboBox
	CComboBox* m_ComboBox;

	//第几个板卡
	BOOL m_bIsFirstPan;

	//checkBox
	int m_nCheckNum;

	MAP_NUMOFSCREEN m_NumOfScreen;

	int m_nScreenModel;

	int m_nCorrpScreenNum;

	int m_nBoardType;

};

