#pragma once

class XPowerManage;
class XBtn;
class XText;

class XPowerManageItem
{
public:
	XPowerManageItem();
	~XPowerManageItem();

public:

	inline CString GetFilePath(){return m_szFilePath;}

	inline void SetFilePath(CString szFilePath){m_szFilePath=szFilePath;}

	inline CString GetText(){return m_szText;}

	inline void SetText(CString szText){m_szText=szText;}

	inline DWORD GetID(){return m_nID;}

	inline void SetID(DWORD nID){m_nID=nID;}

	inline CRect GetRect(){return m_Rect;}

	inline void SetRect(CRect rect){m_Rect=rect;}

	inline void SetParent(XPowerManage* p){m_pParent=p;}

public:

	void Init();

	void SetText();

private:

	void ClearBtn();

	void ClearText();

	void CreateBtn();

	void CreateText();

private:

	XPowerManage* m_pParent;

	XBtn* m_pBtn;

	XText* m_pText;

private:

	CString m_szFilePath;

	CString m_szText;

	DWORD m_nID;

	CRect m_Rect;
};