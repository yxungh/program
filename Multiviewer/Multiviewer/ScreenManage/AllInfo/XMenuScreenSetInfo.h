#pragma once
#include "XConstantIM.h"

class XMenuScreenSetInfo
{
public:

	XMenuScreenSetInfo();

	~XMenuScreenSetInfo();

public:

	void SetCheck(int n);

	int GetCheck();

	void SetScreenCountH(int n);

	int GetScreenCountH();

	void SetScreenCountV(int n);

	int GetScreenCountV();

	void SetScreenModel(int nModel);

	int GetScreenModel();

	VEC_OUTPUTINFO GetVecOutputInfo();

	void ClearOutputInfo();

	void AddOutputInfo(XOutputInfo* pInfo);

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_nCheck;

	int m_nScreenCountH;

	int m_nScreenCountV;

	VEC_OUTPUTINFO m_VecOutputInfo;

	int m_nScreenModel;
};