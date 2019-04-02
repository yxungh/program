#include "StdAfx.h"
#include "XSendData.h"

XSendData::XSendData(void)
{
	m_Data = NULL;

	m_DataLen = 0;
}

XSendData::~XSendData(void)
{
	if (m_Data != NULL)
	{
		delete[] m_Data;

		m_Data = NULL;
	}
}