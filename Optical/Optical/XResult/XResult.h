#pragma once

class XResult
{
public:
	XResult();
	~XResult();

public:

	inline void SetResult(int n){m_nResult=n;}

	inline int GetResult(){return m_nResult;}

private:

	int m_nResult;
};