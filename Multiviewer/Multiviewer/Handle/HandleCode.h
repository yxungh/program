#pragma once

//编码转换类
class HandleCode
{
public:

	//多字节转Unicode字符串
	static CString ConvertAsciitoUnicode(char* pData);

	//Unicode字符串转多字节
	static void ConvertUnicodeToAscii(const CString& szData, char*& pData, int& nDataLen);

	//Unicode转UTF8
	static void GetUTF8FromUnicode(const CString& szSrc,char* pDes);
};