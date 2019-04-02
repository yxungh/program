#pragma once


class XResulationVCutInfo
{
public:

	XResulationVCutInfo();
	~XResulationVCutInfo();

public:

	inline void SetResulationIndex(int n){m_nResulationIndex=n;}

	inline int GetResulationIndex(){return m_nResulationIndex;}

	inline void SetResulationV(int n){m_nResulationV=n;}

	inline int GetResulationV(){return m_nResulationV;}

	inline void SetResulationCut(int n){m_nResulationCut=n;}

	inline int GetResulationCut(){return m_nResulationCut;}

	inline void SetVFront(int n){m_nVFront=n;}

	inline int GetVFront(){return m_nVFront;}

	inline void SetVActive(int n){m_nVActive=n;}

	inline int GetVActive(){return m_nVActive;}

	inline void SetVBack(int n){m_nVBack=n;}

	inline int GetVBack(){return m_nVBack;}

	inline void SetVSyn(int n){m_nVSyn=n;}

	inline int GetVSyn(){return m_nVSyn;}

	inline void SetVPolarity(int n){m_nVPolarity=n;}

	inline int GetVPolarity(){return m_nVPolarity;}

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_nResulationIndex;

	int m_nResulationV;

	int m_nResulationCut;

	int m_nVFront;

	int m_nVActive;

	int m_nVBack;

	int m_nVSyn;

	int m_nVPolarity;

};