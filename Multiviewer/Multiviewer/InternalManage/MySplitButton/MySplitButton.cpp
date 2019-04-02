#include "stdafx.h"
#include "MySplitButton.h"
#include "XConstantIM.h"


IMPLEMENT_DYNAMIC(MySplitButton, CSplitButton)

MySplitButton::MySplitButton()
{
	m_nIndex=0;

	m_nBoardIndex=0;
}

MySplitButton::~MySplitButton()
{

}

BEGIN_MESSAGE_MAP(MySplitButton, CSplitButton)

END_MESSAGE_MAP()


void MySplitButton::SetIndex(int n)
{
	m_nIndex=n;
}

int MySplitButton::GetIndex()
{
	return m_nIndex;
}

void MySplitButton::SetBoardIndex(int n)
{
	m_nBoardIndex=n;
}

int MySplitButton::GetBoardIndex()
{
	return m_nBoardIndex;
}
