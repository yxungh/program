#include "stdafx.h"
#include "HandleVerification.h"

HandleVerification::HandleVerification()
{
}

HandleVerification::~HandleVerification()
{

}


BOOL HandleVerification::VerificationString(CString szTemp)
{
	int nLen = szTemp.GetLength();

	for (int i = 0; i < nLen; i++)
	{
		TCHAR c = szTemp.GetAt(i);

		if (('(' == c)
			|| (')' == c)
			|| (' ' == c)
			|| ('=' == c)
			|| ('\'' == c)
			|| ('-' == c)
			|| (';' == c)
			|| ('>' == c)
			|| ('<' == c)
			|| ('*' == c)
			|| ('!' == c)
			|| ('%' == c))
		{
			return FALSE;
		}
	}

	return TRUE;
}