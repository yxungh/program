#pragma once

class XSignalCutInfo
{
public:
	XSignalCutInfo(void);
	~XSignalCutInfo(void);

	void SetSignalCut(unsigned short nX1, unsigned short nY1, unsigned short nX2, unsigned short nY2);


	unsigned short GetSignalCutX1();

	unsigned short GetSignalCutY1();

	unsigned short GetSignalCutX2();

	unsigned short GetSignalCutY2();
	//////////////////////////////////////////////////////////////////////////


	void Reset();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	unsigned short m_SignalCutX1;

	unsigned short m_SignalCutY1;

	unsigned short m_SignalCutX2;

	unsigned short m_SignalCutY2;
	


};

