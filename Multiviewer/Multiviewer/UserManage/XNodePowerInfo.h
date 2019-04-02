#pragma once

#include "XUserManage.h"

class XNodePowerInfo
{
public:
	XNodePowerInfo(void);
	~XNodePowerInfo(void);

public:

	int GetInputIndex();

	int GetOutputIndex();

	BOOL GetPower();

	void SetInputIndex(int n);

	void SetOutputIndex(int n);

	void SetPower(BOOL b);

public:

	void GetData(CArchive& arch, unsigned char* pKey);

	void SaveData(CArchive& arch, unsigned char* pKey);

private:

	int m_InputIndex;

	int m_OutputIndex;

	BOOL m_Power;
};

