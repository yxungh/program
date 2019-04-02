#pragma once

class XExpandInfo
{
public:
	XExpandInfo(void);
	~XExpandInfo(void);

	void SetExpand(unsigned short nX1, unsigned short nY1, unsigned short nX2, unsigned short nY2);

	unsigned short GetExpandX1();

	unsigned short GetExpandY1();

	unsigned short GetExpandX2();

	unsigned short GetExpandY2();

	void Reset();

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	unsigned short m_ExpandX1;

	unsigned short m_ExpandY1;

	unsigned short m_ExpandX2;

	unsigned short m_ExpandY2;
};

