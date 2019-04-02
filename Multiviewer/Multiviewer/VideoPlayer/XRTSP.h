#pragma once

enum STATETYPE
{
	STATETYPE_OPEN,//打开状态
	STATETYPE_CLOSE,//关闭状态
	STATETYPE_STOP,//停止状态

	STATETYPE_NULL
};

class XVideoPlayer;

class XRTSP
{
public:
	XRTSP(void);
	~XRTSP(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	//初始化
	void Init();

	//打开
	void Open();

	//停止
	void Stop();

	//关闭
	void Close();

	//清除数据
	void ClearData();

	//清除图像数据
	void ClearFrameYUVData();

	//设置运行状态
	void SetRunning(BOOL b);

	CString GetRSTPAddr();

	CString GetRSTPHDAddr();

	CString GetName();

	BOOL GetTF680();

	void SetRSTPAddr(CString s);

	void SetRSTPHDAddr(CString s);

	void SetName(CString s);

	//获取状态
	STATETYPE GetStateType();

	//设置状态
	void SetStateType(STATETYPE s);

	//线程运行状态
	BOOL ThreadRunState();

	//设置TCP
	void SetTCP(BOOL b);

	//设置连接超时时间
	void SetConnectTimeOut(int n);

	//设置计数
	void SetCount(int n);
	int GetCount();

public:

	void OpenURL();

	void StopOpenThread();

	void CloseOpenThreadEvent();

	void StopDecodeThread();

	void CloseDecodeThreadEvent();

	BOOL StartDecodeThread();

	BOOL StartOpenThread();

public:

	XVideoPlayer* m_VideoPlayer;

	//RTSP地址
	CString m_RSTPAddr;

	//RTSP HD地址
	CString m_RSTPHDAddr;

	//名称
	CString m_Name;

	//RTSP地址
	char m_cRSTPAddr[MAX_PATH];

	HANDLE m_OpenThreadEvent; 

	volatile BOOL m_bOpenThread;

	AVCodecContext* m_codec_ctx;

	AVCodec* m_codec;

	struct SwsContext * m_sws_ctx;

	AVFrame* m_frame;

	AVFrame* m_frame_yuv;

	int m_frame_yuv_Width;

	int m_frame_yuv_Height;

	uint8_t* m_out_buffer;

	HANDLE m_DecodeThreadEvent; 

	volatile BOOL m_bDecodeThread;

	int m_video_index;

	int64_t m_pts;

	AVFormatContext* m_fmt_ctx;

	int64_t m_seek_to_msec;

	BOOL m_is_file;

	int64_t m_wait_time;

	volatile BOOL m_Running;

	STATETYPE m_StateType;
	
	BOOL m_RecvFlagKey;

	//是否进行sws_scale计算
	BOOL m_SwsScale;

	CRITICAL_SECTION m_CSFrameYUV;

	BOOL m_TCP;

	int m_ConnectTimeOut;

	//RTSP计数
	int m_nCount;
};

