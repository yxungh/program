#include "stdafx.h"
#include "XSetBoard.h"
#include "afxdialogex.h"
#include "XDelegateSelectEquipment.h"
#include "XScreen.h"
#include "XScreenManage.h"
#include "HandlePath.h"
#include "XEquipmentInput.h"
#include "XEquipmentOutput.h"
#include "XDelegateScreenManage.h"
#include "XMenuScreenSetInfo.h"
#include "XOutputInfo.h"



// CAddExpandDlg 对话框

IMPLEMENT_DYNAMIC(XSetBoard, CDialogEx)

	XSetBoard::XSetBoard(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSetBoard::IDD, pParent)
{
	m_pDelegate = NULL;

	m_nInputNum=0;

	m_nOutputNum=0;

	m_nScreenNumH=0;

	m_nScreenNumV=0;

	m_bIsMenuSet=FALSE;

	m_nScreenModel=0;
}

XSetBoard::~XSetBoard()
{
	
}

void XSetBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_DIALOG, m_Static_Dialog);
}


BEGIN_MESSAGE_MAP(XSetBoard, CDialogEx)
	ON_BN_CLICKED( IDOK, &XSetBoard::OnBtnOK)
END_MESSAGE_MAP()


// CAddExpandDlg 消息处理程序


void XSetBoard::SetDelegate(XDelegateSelectEquipment* p)
{
	m_pDelegate = p;
}

void XSetBoard::SetScreenManage(XScreenManage* p)
{
	m_pScreenManage=p;
}

void XSetBoard::SetScreen(XScreen* p)
{
	m_pScreen=p;
}

void XSetBoard::SetEquipment(int n)
{
	m_nEquipment=n;
}

void XSetBoard::InitData()
{

}

BOOL XSetBoard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReloadInterface();

	InitBoardChild();

	InitData();

	return FALSE;  
}

void XSetBoard::ReloadInterface()	
{
	SetWindowText(m_pDelegate->GetTranslationString(_T("563"),_T("设置向导-板卡配置")));

	GetDlgItem(IDOK)->SetWindowText(m_pDelegate->GetTranslationString(_T("208"),_T("确定")));
	GetDlgItem(IDCANCEL)->SetWindowText(m_pDelegate->GetTranslationString(_T("209"),_T("取消")));

	GetDlgItem(IDC_STATIC_INPUT)->SetWindowText(m_pDelegate->GetTranslationString(_T("596"),_T("输入板卡(双击设置OSD)")));

	if(m_nScreenModel==SCREENMODEL_SPLIC)
	{
		GetDlgItem(IDC_STATIC_OUTPUT)->SetWindowText(m_pDelegate->GetTranslationString(_T("597"),_T("拼接输出板卡(双击进行配置，复选框代表是否为两路)")));
		GetDlgItem(IDC_STATIC_TIPS20)->SetWindowText(m_pDelegate->GetTranslationString(_T("611"),_T("提示:如果一路、两路相互切换，需先取消原来的配置")));
	}
	else
	{
		GetDlgItem(IDC_STATIC_OUTPUT)->SetWindowText(m_pDelegate->GetTranslationString(_T("701"),_T("矩阵输出板卡(双击进行配置，对应4个屏幕)")));
		GetDlgItem(IDC_STATIC_TIPS20)->SetWindowText(m_pDelegate->GetTranslationString(_T("702"),_T("提示:每个矩阵输出板卡，对应4个屏幕！")));
	}
}

void XSetBoard::InitBoardChild()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_DIALOG)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_BoardChildDlg.SetDelegate(m_pDelegate);
	m_BoardChildDlg.SetScreenManage(m_pScreenManage);
	m_BoardChildDlg.Create(IDD_DLG_CHILD,this);
	m_BoardChildDlg.SetEquipment(m_nEquipment);
	m_BoardChildDlg.SetScreenNumH(m_nScreenNumH);
	m_BoardChildDlg.SetScreenNumV(m_nScreenNumV);
	m_BoardChildDlg.SetIsMenuSet(m_bIsMenuSet);
	m_BoardChildDlg.SetScreenModel(m_nScreenModel);
	m_BoardChildDlg.MoveWindow(&rect);
	m_BoardChildDlg.Init();
	m_BoardChildDlg.ShowWindow(TRUE);
}

int XSetBoard::GetEquipment()
{
	return m_nEquipment;
}

void XSetBoard::OnBtnOK()
{
	if(!CheckVec())
	{
		if(IDOK!=m_pDelegate->MessageBoxFromKey(_T("583"),_T("您没有全部分配输出匹配屏幕！"),MB_OKCANCEL))
		{
			return;
		}
	}

	VEC_EQUIPMENTINPUT& VecInput=m_BoardChildDlg.GetVecEquipmentInput();
	VEC_EQUIPMENTOUTPUT& VecOutput=m_BoardChildDlg.GetVecEquipmentOutput();

	int nInputNum=VecInput.size()*4;


	VEC_SCREENINFO VecScreenInfo;
	m_BoardChildDlg.CopyVecBoardToVecScreeInfo(VecScreenInfo);
	//////////////////////////////////////////////////////////////////////////
	m_pScreenManage->SetInputCount(nInputNum);
	m_pScreenManage->SetScreenCountH(m_nScreenNumH);
	m_pScreenManage->SetScreenCountV(m_nScreenNumV);
	m_pScreenManage->SetVecScreenInfo(VecScreenInfo);

	m_pScreenManage->GetDelegate()->UpdateControlDataShow(XDATATYPE_INPUTCOUNT);
	m_pScreenManage->GetDelegate()->UpdateControlDataShow(XDATATYPE_OUTPUTCOUNTH);
	m_pScreenManage->GetDelegate()->UpdateControlDataShow(XDATATYPE_OUTPUTCOUNTV);

	m_pScreenManage->ResetDataBySceneScreenCountChange();


	VEC_INPUTSIGNAL& VecSignal=m_pScreenManage->GetVecInputSignal();

	if(nInputNum!=VecSignal.size())
	{
		m_pScreenManage->ResetDataBySceneInputCountChange();
	}
	//////////////////////////////////////////////////////////////////////////
	XMenuScreenSetInfo* pInfo=m_pScreenManage->GetMenuScreenSetInfo();

	for(VEC_EQUIPMENTOUTPUT::iterator iter=VecOutput.begin();iter!=VecOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		XOutputInfo* pOutputInfo=new XOutputInfo;

		pOutputInfo->SetBoardIndex(pOutput->GetBoardIndex());
		pOutputInfo->SetInputName(pOutput->GetInputName());
		pOutputInfo->SetIsFirstPan(pOutput->GetIsFirstPan());
		pOutputInfo->SetIsTwoScreen(pOutput->GetIsTwoScreen());
		pOutputInfo->SetScreenIndex1(pOutput->GetScreenIndex());
		pOutputInfo->SetScreenIndex2(pOutput->GetScreenIndex2());

		pOutputInfo->SetScreenIndex3(pOutput->GetScreenIndex3());
		pOutputInfo->SetScreenIndex4(pOutput->GetScreenIndex4());

		pOutputInfo->SetCorrpScreenNum(pOutput->GetCorrpScreenNum());

		pOutputInfo->SetCheckNum(pOutput->GetCheckNum());
		pOutputInfo->SetMapScreenNum(pOutput->GetMapNumOfScreen());

		pInfo->AddOutputInfo(pOutputInfo);
	}

	CDialogEx::OnOK();
}

BOOL XSetBoard::CheckVec()
{
	VEC_EQUIPMENTINPUT& VecInput=m_BoardChildDlg.GetVecEquipmentInput();

	VEC_EQUIPMENTOUTPUT& VecOutput=m_BoardChildDlg.GetVecEquipmentOutput();

	for(VEC_EQUIPMENTOUTPUT::iterator iter=VecOutput.begin();iter!=VecOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nScreenIndex1=pOutput->GetScreenIndex();
		int nScreenIndex2=pOutput->GetScreenIndex2();

		if(pOutput->GetIsTwoScreen())
		{
			if(nScreenIndex1==-1
				||nScreenIndex2==-1)
			{
				return FALSE;
			}
		}
		else
		{
			if(nScreenIndex1==-1)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

int XSetBoard::GetInputNum()
{
	VEC_EQUIPMENTINPUT& VecInput=m_BoardChildDlg.GetVecEquipmentInput();

	int nInputNum=VecInput.size();

	return nInputNum;
}

int XSetBoard::GetOutputNum()
{
	int nOutputNum=0;

	VEC_EQUIPMENTOUTPUT& VecOutput=m_BoardChildDlg.GetVecEquipmentOutput();

	for(VEC_EQUIPMENTOUTPUT::iterator iter=VecOutput.begin();iter!=VecOutput.end();++iter)
	{
		XEquipmentOutput* pOutput=*iter;

		int nScreenIndex1=pOutput->GetScreenIndex();
		int nScreenIndex2=pOutput->GetScreenIndex2();
		BOOL bIsTwoScreen=pOutput->GetIsTwoScreen();

		if(!pOutput->GetIsTwoScreen())
		{
			if(nScreenIndex1==-1)
			{
				continue;
			}
			else
			{
				nOutputNum+=1;
			}
		}
		else
		{
			if(nScreenIndex1!=-1)
			{
				nOutputNum+=1;
			}

			if(nScreenIndex2!=-1)
			{
				nOutputNum+=1;
			}
		}
	}

	return nOutputNum;
}

int XSetBoard::GetInput()
{
	return m_nInputNum;
}

int XSetBoard::GetOutput()
{
	return m_nOutputNum;
}

VEC_EQUIPMENTINPUT& XSetBoard::GetVecInput()
{
	VEC_EQUIPMENTINPUT& VecInput=m_BoardChildDlg.GetVecEquipmentInput();

	return VecInput;
}

VEC_EQUIPMENTOUTPUT& XSetBoard::GetVecOutput()
{
	VEC_EQUIPMENTOUTPUT& VecOutput=m_BoardChildDlg.GetVecEquipmentOutput();

	return VecOutput;
}

//////////////////////////////////////////////////////////////////////////

void XSetBoard::SetScreenNumH(int n)
{
	m_nScreenNumH=n;
}

int XSetBoard::GetScreenNumH()
{
	return m_nScreenNumH;
}

void XSetBoard::SetScreenNumV(int n)
{
	m_nScreenNumV=n;
}

int XSetBoard::GetScreenNumV()
{
	return m_nScreenNumV;
}

void XSetBoard::SetIsMenuSet(BOOL b)
{
	m_bIsMenuSet=b;
}

BOOL XSetBoard::GetIsMenuSet()
{
	return m_bIsMenuSet;
}