#pragma once

class HandleCalculate
{
private:
	HandleCalculate(void);
	~HandleCalculate(void);

public:

	//设置视图原点
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, 
		CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY, CDC& dc);

	static void SetPreviewOrg(CRect& rect, int& noffsetX, int& noffsetY, 
		CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY,CSize& orgSize);


	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,
		CSize& size, float& dwScale, const int& nDrawDistanceX, const int& nDrawDistanceY, int& nOrgX, int& nOrgY);

	//判断IP是否正确
	static BOOL DecideIP(CString szIP);

	//判断RTSP地址是否正确
	static BOOL DecideRTSPAddr(CString szRTSPAddr);

	static CString GetIPByRTSPAddr(CString szRTSPAddr);
};

