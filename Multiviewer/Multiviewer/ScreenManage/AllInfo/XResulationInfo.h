#pragma once


class XResulationInfo
{
public:
	XResulationInfo();
	~XResulationInfo();

public:
	int GetResolutionH();

	int GetResolutionV();

	int GetHFPorch();

	int GetVFPorch();

	int GetHpixel();

	int GetVPixel();

	int GetHBPorch();

	int GetVBProch();

	int GetHSyncTime();

	int GetVSyncTime();

	int GetHSyncPolarity();

	int GetVSyncPolarity();

	int GetComboIndex();

	int GetComboRefresh();

	int GetComboModel();

	inline int GetRefreash(){return m_nRefreash;}
	//**********
	void SetResolutionH(int n);
		 
	void SetResolutionV(int n);
		 
	void SetHFPorch(int n);
		 
	void SetVFPorch(int n);
		 
	void SetHpixel(int n);
		 
	void SetVPixel(int n);
		 
	void SetHBPorch(int n);
		 
	void SetVBProch(int n);
		 
	void SetHSyncTime(int n);
		 
	void SetVSyncTime(int n);
		 
	void SetHSyncPolarity(int n);
		 
	void SetVSyncPolarity(int n);
		 
	void SetComboIndex(int n);
		 
	void SetComboRefresh(int n);

	void SetComboModel(int n);

	inline void SetRefreash(int n){m_nRefreash=n;}

	inline void SetCurDpi(int n){m_nCurDpi=n;}

	inline int GetCurDpi(){return m_nCurDpi;}

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_ResolutionH;

	int m_ResolutionV;

	int m_HFPorch;

	int m_VFPorch;

	int m_Hpixel;

	int m_VPixel;

	int m_HBPorch;

	int m_VBProch;

	int m_HSyncTime;

	int m_VSyncTime;

	int m_HSyncPolarity;

	int m_VSyncPolarity;

	int m_ComboIndex;

	int m_ComboRefresh;

	//æÿ’Û
	int m_ComboModel;

	int m_nRefreash;

	int m_nCurDpi;
};