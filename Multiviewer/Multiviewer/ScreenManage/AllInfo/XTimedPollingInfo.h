#pragma once


class XTimedPollingInfo
{
public:
	XTimedPollingInfo();
	~XTimedPollingInfo();

public:

	int GetTimedPolling();

	void SetTimePolling(int n);

public:

	void GetData(CArchive& arch);

	void SaveData(CArchive& arch);

private:

	int m_Time;
};