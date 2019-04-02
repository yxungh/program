#include "StdAfx.h"
#include "XHandleVerification.h"

XHandleVerification::XHandleVerification(void)
{
}


XHandleVerification::~XHandleVerification(void)
{
}

BOOL XHandleVerification::VerificationString(CString szTemp)
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