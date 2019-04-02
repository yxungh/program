#pragma once

class XInputType
{
public:
	XInputType();
	~XInputType();

public:

	inline void SetChannel(int n){m_nChannel=n;}

	inline int GetChannel(){return m_nChannel;}

	inline void SetType(int n){m_nType=n;}

	inline int GetType(){return m_nType;}

private:

	int m_nChannel;

	int m_nType;
};