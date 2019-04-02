#pragma once


class XAllResulationInfo
{
public:
	XAllResulationInfo();
	~XAllResulationInfo();

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

	int GetRightCut();

	int GetBottomCut();

	int GetComboModel();

	inline BOOL GetIsRight(){return m_bIsRight;}

	inline BOOL GetIsBottom(){return m_bIsBottom;}

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

	void SetRightCut(int n);

	void SetBottomCut(int n);

	void SetComboModel(int n);

	inline void SetIsRight(BOOL b){m_bIsRight=b;}

	inline void SetIsBottom(BOOL b){m_bIsBottom=b;}

	inline void SetRefreash(int n){m_nRefreash=n;}

	//////////////////////////////////////////////////////////////////////////

	inline void SetScreenWidth(int n){m_nScreenWidth=n;}

	inline int GetScreenWidth(){return m_nScreenWidth;}

	inline void SetScreenHight(int n){m_nScreenHight=n;}

	inline int GetScreenHight(){return m_nScreenHight;}

	inline void SetScreenRow(int n){m_nScreenRow=n;}

	inline int GetScreenRow(){return m_nScreenRow;}

	inline void SetScreenCol(int n){m_nScreenCol=n;}

	inline int GetScreenCol(){return m_nScreenCol;}

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

	int m_nRightCut;

	int m_nBottomCut;

	BOOL m_bIsRight;

	BOOL m_bIsBottom;
	//æÿ’Û
	int m_ComboModel;
	
	int m_nRefreash;

	//////////////////////////////////////////////////////////////////////////

	int m_nScreenWidth;
	int m_nScreenHight;

	int m_nScreenRow;
	int m_nScreenCol;
};