#pragma once


class XResulationHCutInfo
{
public:

	XResulationHCutInfo();
	~XResulationHCutInfo();

public:

	inline void SetResulationIndex(int n){m_nResulationIndex=n;}

	inline int GetResulationIndex(){return m_nResulationIndex;}

	inline void SetResulationH(int n){m_nResulationH=n;}

	inline int GetResulationH(){return m_nResulationH;}

	inline void SetResulationCut(int n){m_nResulationCut=n;}

	inline int GetResulationCut(){return m_nResulationCut;}

	inline void SetHFront(int n){m_nHFront=n;}

	inline int GetHFront(){return m_nHFront;}

	inline void SetHActive(int n){m_nHActive=n;}

	inline int GetHActive(){return m_nHActive;}

	inline void SetHBack(int n){m_nHBack=n;}

	inline int GetHBack(){return m_nHBack;}

	inline void SetHSyn(int n){m_nHSyn=n;}

	inline int GetHSyn(){return m_nHSyn;}

	inline void SetHPolarity(int n){m_nHPolarity=n;}

	inline int GetHPolarity(){return m_nHPolarity;}

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_nResulationIndex;

	int m_nResulationH;

	int m_nResulationCut;

	int m_nHFront;

	int m_nHActive;

	int m_nHBack;

	int m_nHSyn;

	int m_nHPolarity;

};