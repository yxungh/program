#include "stdafx.h"
#include "CMyButton.h"


IMPLEMENT_DYNAMIC(CMyButton, CButton)

	CMyButton::CMyButton()
{
	m_nCheckBocNum=0;
}

CMyButton::~CMyButton()
{

}

BEGIN_MESSAGE_MAP(CMyButton, CButton)

END_MESSAGE_MAP()

void CMyButton::SetCheckBoxNum(int n)
{
	m_nCheckBocNum=n;
}

int CMyButton::GetCheckBoxNum()
{
	return m_nCheckBocNum;
}