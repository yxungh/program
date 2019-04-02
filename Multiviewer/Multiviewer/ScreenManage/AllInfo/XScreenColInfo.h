#pragma once

class XScreenColInfo
{
public:
	XScreenColInfo();
	~XScreenColInfo();

public:

	inline void SetScreenWidth(float n){m_nScreenWidth=n;}

	inline float GetScreenWidth(){return m_nScreenWidth;}

	inline void SetResoluationH(int n){m_nResoluationH=n;}

	inline int GetResoluationH(){return m_nResoluationH;}

private:

	float m_nScreenWidth;

	int m_nResoluationH;
};