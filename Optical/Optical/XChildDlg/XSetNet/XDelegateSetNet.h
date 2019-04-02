#pragma once


class XDelegateSetNet
{
public:
	XDelegateSetNet();
	~XDelegateSetNet();

public:

	virtual void SetDeviceIPAndPort(CString szIP,int nPort)=0;

	virtual void SaveDeviceIPAndPort(CString szIP,int nPort)=0;

	virtual CString GetIP()=0;

	virtual int GetPort()=0;

	virtual void SendHeart()=0;
};