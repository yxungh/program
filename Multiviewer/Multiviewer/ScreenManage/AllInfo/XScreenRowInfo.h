#pragma once

class XScreenRowInfo
{
public:
	XScreenRowInfo();
	~XScreenRowInfo();

public:

	inline void SetScreenHeight(float n){m_nScreenHeight=n;}

	inline float GetScreenHeight(){return m_nScreenHeight;}

	inline void SetResoluationV(int n){m_nResoluationV=n;}

	inline int GetResoluationV(){return m_nResoluationV;}
private:

	float m_nScreenHeight;

	int m_nResoluationV;
};