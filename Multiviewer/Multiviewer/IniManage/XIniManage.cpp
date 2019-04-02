#include "StdAfx.h"
#include "XIniManage.h"
#include "XDelegateIniManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "HandleCalculate.h"

XIniManage::XIniManage(void)
{
	m_pDelegate = NULL;
}

XIniManage::~XIniManage(void)
{
}

void XIniManage::SetDelegate(XDelegateIniManage* p)
{
	m_pDelegate = p;
}

void XIniManage::Init()
{
	GetIniData();
}

void XIniManage::GetIniData()
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	m_DeviceIP = HandleIni::GetString(_T("Info"), _T("DeviceIP"), _T(""), szIniPath);
	if (_T("") == m_DeviceIP)
	{
		m_DeviceIP = _T("192.168.1.234");

		HandleIni::WriteData(_T("Info"), _T("DeviceIP"), m_DeviceIP, szIniPath);
	}

	m_DevicePort = HandleIni::GetInt(_T("Info"), _T("DevicePort"), 0, szIniPath);
	if (0 == m_DevicePort)
	{
		m_DevicePort = 8888;

		CString szTemp = _T("");
		szTemp.Format(_T("%d"), m_DevicePort);

		HandleIni::WriteData(_T("Info"), _T("DevicePort"), szTemp, szIniPath);
	}

	m_Scale = HandleIni::GetInt(_T("Info"), _T("Scale"), 70, szIniPath);
}

void XIniManage::SaveDataOfDevicePort(int n)
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	CString szTemp = _T("");
	szTemp.Format(_T("%d"), n);

	HandleIni::WriteData(_T("Info"), _T("DevicePort"), szTemp, szIniPath);
}

void XIniManage::SaveDataOfDeviceIP(CString s)
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	HandleIni::WriteData(_T("Info"), _T("DeviceIP"), s, szIniPath);
}

CString XIniManage::GetDeviceIP()
{
	return m_DeviceIP;
}

void XIniManage::SetDeviceIP(CString str)
{
	m_DeviceIP=str;
}

int XIniManage::GetDevicePort()
{
	return m_DevicePort;
}

void XIniManage::SetDevicePort(int n)
{
	m_DevicePort=n;
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void XIniManage::UpdateControlDataShowOfDeviceIP(CMFCRibbonEdit* p)
{
	p->SetEditText(m_DeviceIP);
}

void XIniManage::ControlDataChangeOfDeviceIP(CMFCRibbonEdit* p)
{
	CString szTemp = p->GetEditText();

	szTemp.Trim();

	if (_T("") == szTemp)
	{
		p->SetEditText(m_DeviceIP);

		return;
	}

	if (!HandleCalculate::DecideIP(szTemp))
	{
		m_pDelegate->MessageBoxFromKey(_T("250"), _T("设备IP地址输入错误，请重新输入!"), MB_OK);

		p->SetEditText(m_DeviceIP);

		return;
	}

	if (szTemp != m_DeviceIP)
	{
		SaveDataOfDeviceIP(szTemp);

		m_DeviceIP = szTemp;

		p->SetEditText(szTemp);

		m_pDelegate->Operate(OPERATETYPE_RESETTEMPERATURE, NULL);
	}
}

void XIniManage::UpdateControlDataShowOfDevicePort(CMFCRibbonEdit* p)
{
	CString szTemp = _T("");
	szTemp.Format(_T("%d"), m_DevicePort);

	p->SetEditText(szTemp);
}

void XIniManage::ControlDataChangeOfDevicePort(CMFCRibbonEdit* p)
{
	CString szTemp = p->GetEditText();

	szTemp.Trim();

	if (_T("") == szTemp)
	{
		szTemp.Format(_T("%d"), m_DevicePort);

		p->SetEditText(szTemp);

		return;
	}

	int nPort = _ttoi(szTemp);

	if (nPort < 1024 || nPort > 65535)
	{
		m_pDelegate->MessageBoxFromKey(_T("251"), _T("设备端口输入错误，请重新输入!"), MB_OK);

		szTemp.Format(_T("%d"), m_DevicePort);

		p->SetEditText(szTemp);

		return;
	}


	if (nPort != m_DevicePort)
	{
		SaveDataOfDevicePort(nPort);

		m_DevicePort = nPort;

		p->SetEditText(szTemp);

		m_pDelegate->Operate(OPERATETYPE_RESETTEMPERATURE, NULL);
	}
}

void XIniManage::UpdateControlDataShow(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_DEVICEIP:
		{
			UpdateControlDataShowOfDeviceIP((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_DEVICEPORT:
		{
			UpdateControlDataShowOfDevicePort((CMFCRibbonEdit*)pControl);
		}
		break;
	default:
		break;
	}
}

void XIniManage::ControlDataChange(XDATATYPE type, void* pControl)
{
	switch(type)
	{
	case XDATATYPE_DEVICEIP:
		{
			ControlDataChangeOfDeviceIP((CMFCRibbonEdit*)pControl);
		}
		break;
	case XDATATYPE_DEVICEPORT:
		{
			ControlDataChangeOfDevicePort((CMFCRibbonEdit*)pControl);
		}
		break;
	default:
		break;
	}
}