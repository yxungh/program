#include "stdafx.h"
#include "XMessageBox.h"
#include "XMessageBoxDlg.h"
#include "XTranslationManage.h"


XMessageBox* XMessageBox::m_pMessageBox=NULL;

XMessageBox::XMessageBox()
{

}

XMessageBox::~XMessageBox()
{
	//TRACE(_T("~XMessageBox\n"));
}

XMessageBox* XMessageBox::GetInstance()
{
	if(NULL==m_pMessageBox)
	{
		m_pMessageBox=new XMessageBox;
	}
	return m_pMessageBox;
}

void XMessageBox::Release()
{
	if(NULL!=m_pMessageBox)
	{
		delete m_pMessageBox;
		m_pMessageBox=NULL;
	}
}

int XMessageBox::MessageBoxByKey(CString szTextKey,CString szDefault,UINT uType)
{
	return MessageBox(XTranslationManage::GetInstance()->GetTranslationString(szTextKey,szDefault),XTranslationManage::GetInstance()->GetTranslationString(_T("5")),uType);
}

int XMessageBox::MessageBox(CString szText,CString szCaption,UINT uType)
{
	XMessageBoxDlg dlg(szText,szCaption,uType);
	return dlg.DoModal();
}
