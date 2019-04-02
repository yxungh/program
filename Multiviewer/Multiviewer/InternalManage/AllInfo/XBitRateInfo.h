#pragma once

class XBitRateInfo
{
public:

	XBitRateInfo();
	~XBitRateInfo();

public:

	void SetMainDpi1(int n);
	int GetMainDpi1();
	void SetMainBitRate1(int n);
	int GetMainBitRate1();
	void SetSubDpi1(int n);
	int GetSubDpi1();
	void SetSubBitRate1(int n);
	int GetSubBitRate1();

	void SetMainDpi2(int n);
	int GetMainDpi2();
	void SetMainBitRate2(int n);
	int GetMainBitRate2();
	void SetSubDpi2(int n);
	int GetSubDpi2();
	void SetSubBitRate2(int n);
	int GetSubBitRate2();

	void SetMainDpi3(int n);
	int GetMainDpi3();
	void SetMainBitRate3(int n);
	int GetMainBitRate3();
	void SetSubDpi3(int n);
	int GetSubDpi3();
	void SetSubBitRate3(int n);
	int GetSubBitRate3();

	void SetMainDpi4(int n);
	int GetMainDpi4();
	void SetMainBitRate4(int n);
	int GetMainBitRate4();
	void SetSubDpi4(int n);
	int GetSubDpi4();
	void SetSubBitRate4(int n);
	int GetSubBitRate4();

	int GetFlag1();
	void SetFlag1(int n);
	int GetFlag2();
	void SetFlag2(int n);
	int GetFlag3();
	void SetFlag3(int n);
	int GetFlag4();
	void SetFlag4(int n);

	void SetChenal(int n);
	int GetChenal();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_nMainDpi1;
	int m_nMainBitRate1;
	int m_nSubDpi1;
	int m_nSubBitRate1;

	int m_nMainDpi2;
	int m_nMainBitRate2;
	int m_nSubDpi2;
	int m_nSubBitRate2;

	int m_nMainDpi3;
	int m_nMainBitRate3;
	int m_nSubDpi3;
	int m_nSubBitRate3;

	int m_nMainDpi4;
	int m_nMainBitRate4;
	int m_nSubDpi4;
	int m_nSubBitRate4;

	int m_nFlag1;
	int m_nFlag2;
	int m_nFlag3;
	int m_nFlag4;

	int m_nChenal;
};