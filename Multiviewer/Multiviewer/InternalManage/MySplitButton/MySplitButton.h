#pragma once

class MySplitButton:public CSplitButton
{
	DECLARE_DYNAMIC(MySplitButton)

public:
	MySplitButton();
	virtual ~MySplitButton();


	DECLARE_MESSAGE_MAP()



public:

	void SetIndex(int n);

	int GetIndex();

	void SetBoardIndex(int n);

	int GetBoardIndex();


private:

	int m_nIndex;

	int m_nBoardIndex;
};