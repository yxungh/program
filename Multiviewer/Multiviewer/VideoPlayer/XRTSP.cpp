#include "StdAfx.h"
#include "XRTSP.h"
#include "XVideoPlayer.h"
#include <atlconv.h>

XRTSP::XRTSP(void)
{
	m_VideoPlayer = NULL;

	m_bOpenThread = FALSE;

	m_bDecodeThread = FALSE;

	m_fmt_ctx = NULL;

	m_frame_yuv = NULL;

	m_frame_yuv_Width = -1;

	m_frame_yuv_Height = -1;

	m_Running = FALSE;

	m_Name = _T("");

	m_StateType = STATETYPE_NULL;

	m_RecvFlagKey = FALSE;

	m_SwsScale = TRUE;

	m_DecodeThreadEvent = NULL;

	m_OpenThreadEvent = NULL;

	m_TCP = FALSE;

	m_ConnectTimeOut = 1500;

	m_nCount=0;

	InitializeCriticalSection(&m_CSFrameYUV);
}

XRTSP::~XRTSP(void)
{
	ClearData();

	ClearFrameYUVData();

	DeleteCriticalSection(&m_CSFrameYUV);
}

void XRTSP::ClearFrameYUVData()
{
	if (m_frame_yuv != NULL)
	{
		av_frame_free(&m_frame_yuv);

		m_frame_yuv = NULL;
	}
}

void XRTSP::SetVideoPlayer(XVideoPlayer* p)
{
	m_VideoPlayer = p;
}

CString XRTSP::GetRSTPAddr()
{
	return m_RSTPAddr;
}

void XRTSP::SetRSTPAddr(CString s)
{
	m_RSTPAddr = s;
}

CString XRTSP::GetRSTPHDAddr()
{
	return m_RSTPHDAddr;
}

CString XRTSP::GetName()
{
	return m_Name;
}

void XRTSP::SetName(CString s)
{
	m_Name = s;
}

void XRTSP::Init()
{
	USES_CONVERSION;
	char* pURL = W2A(m_RSTPAddr);
	ZeroMemory(m_cRSTPAddr, MAX_PATH);
	memcpy(m_cRSTPAddr, pURL, strlen(pURL));

	m_is_file = !strstr(pURL, "://") || strstr(pURL, "file://");
}

void XRTSP::SetRSTPHDAddr(CString s)
{
	m_RSTPHDAddr = s;
}

static int decode_thread(void *ptr)
{
	XRTSP* pRTSP = (XRTSP*)ptr;

	//TRACE("DecodeThread begin %s\n", pRTSP->m_cRSTPAddr);

	AVPacket packet;
	int got_picture = 0;
	int frame_delay_msec = 40000;

	//BOOL bRecvFlagKey = FALSE;

	av_init_packet(&packet);

	AVStream* st = pRTSP->m_fmt_ctx->streams[pRTSP->m_video_index];

	if (st->avg_frame_rate.den && st->avg_frame_rate.num) 
	{
		double d = av_q2d(st->avg_frame_rate);
		frame_delay_msec = (int)(1000000 / d);
	}

	pRTSP->m_seek_to_msec = -1;

	while (pRTSP->m_Running) 
	{
		if (pRTSP->m_seek_to_msec > -1) 
		{
			AVRational time_base = { 1, AV_TIME_BASE };

			int64_t seek_start = av_rescale_q(pRTSP->m_seek_to_msec * 1000, time_base, 
				pRTSP->m_fmt_ctx->streams[pRTSP->m_video_index]->time_base);

			av_seek_frame(pRTSP->m_fmt_ctx, pRTSP->m_video_index, seek_start, AVSEEK_FLAG_BACKWARD);

			pRTSP->m_seek_to_msec = -1;
		}

		if (!got_picture) 
		{
			if (av_read_frame(pRTSP->m_fmt_ctx, &packet) < 0) 
			{
				av_free_packet(&packet);

				//视频源是文件，返回到第一帧再读取
				if (pRTSP->m_is_file) 
				{	
					av_seek_frame(pRTSP->m_fmt_ctx, 0, 0, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
					continue;
				}

				break;
			}

			if (packet.stream_index == pRTSP->m_video_index) 
			{	
				avcodec_decode_video2(pRTSP->m_codec_ctx, pRTSP->m_frame, &got_picture, &packet);

				if (got_picture) 
				{
					if (pRTSP->m_codec_ctx->width != pRTSP->m_frame_yuv_Width
						|| pRTSP->m_codec_ctx->height != pRTSP->m_frame_yuv_Height)
					{
						av_free_packet(&packet);
						break;
					}

					/*
					if (!bRecvFlagKey && (packet.flags & AV_PKT_FLAG_KEY) && pRTSP->m_SwsScale)
					{
					bRecvFlagKey = TRUE;
					}

					// 转换YUV格式
					if(bRecvFlagKey && pRTSP->m_SwsScale)
					{
					sws_scale(pRTSP->m_sws_ctx, (const uint8_t* const*)pRTSP->m_frame->data, pRTSP->m_frame->linesize, 
					0, pRTSP->m_codec_ctx->height, pRTSP->m_frame_yuv->data, pRTSP->m_frame_yuv->linesize);

					if (!pRTSP->m_RecvFlagKey)
					{
					pRTSP->m_RecvFlagKey = TRUE;
					}
					}
					*/

					sws_scale(pRTSP->m_sws_ctx, (const uint8_t* const*)pRTSP->m_frame->data, pRTSP->m_frame->linesize, 
						0, pRTSP->m_codec_ctx->height, pRTSP->m_frame_yuv->data, pRTSP->m_frame_yuv->linesize);

					if (!pRTSP->m_RecvFlagKey)
					{
						pRTSP->m_RecvFlagKey = TRUE;
					}

					AVRational time_base = { 1, AV_TIME_BASE };

					int64_t next_pts = av_rescale_q(packet.pts, pRTSP->m_fmt_ctx->streams[pRTSP->m_video_index]->time_base, time_base);

					if (!pRTSP->m_is_file || pRTSP->m_pts == AV_NOPTS_VALUE || next_pts - pRTSP->m_pts <= 10000) 
					{
						pRTSP->m_pts = next_pts;

						got_picture = 0;
					} 
					else 
					{
						pRTSP->m_wait_time = next_pts - pRTSP->m_pts;

						if (pRTSP->m_wait_time > frame_delay_msec)
							pRTSP->m_wait_time = frame_delay_msec;

						pRTSP->m_wait_time += av_gettime();

						pRTSP->m_pts = next_pts;
					}
				}
			}

			av_free_packet(&packet);
		} 
		else if (got_picture)
		{
			if (av_gettime() >= pRTSP->m_wait_time) 
			{
				got_picture = 0;
			} 
			else 
			{
				SDL_Delay(10);
			}
		} 
		else 
		{
			SDL_Delay(10);
		}
	}

	if (NULL != pRTSP->m_DecodeThreadEvent)
	{
		SetEvent(pRTSP->m_DecodeThreadEvent);
	}

	pRTSP->m_bDecodeThread = FALSE;

	pRTSP->m_RecvFlagKey = FALSE;

	//TRACE("DecodeThread end %s\n", pRTSP->m_cRSTPAddr);

	return 0;
}

static int interrupt_cb(void* ctx)
{
	XRTSP* pRTSP = (XRTSP*)ctx;

	if(pRTSP->m_Running||(!pRTSP->m_bOpenThread&&!pRTSP->m_bDecodeThread))
	{
		return 0;
	}
	else
	{
		return 1;
	}

	return 0;
}

static int urlopen_thread(void *ptr)
{
	XRTSP* pRTSP = (XRTSP*)ptr;
	int64_t open_wait_time = 0;

	while (pRTSP->m_Running) 
	{
		if (av_gettime() > open_wait_time) 
		{
			AVCodecContext* codec_ctx = 0;
			AVCodec* codec;
			int video_index;

			AVFormatContext* fmt_ctx = 0;
			fmt_ctx = avformat_alloc_context();

			fmt_ctx->interrupt_callback.callback = interrupt_cb;
			fmt_ctx->interrupt_callback.opaque = pRTSP;
			fmt_ctx->probesize=100*1024;
			fmt_ctx->max_analyze_duration=5*AV_TIME_BASE;

			struct AVDictionary* opts = 0;

			int nTimeOut = pRTSP->m_ConnectTimeOut * 1000;
			char timeout[MAX_PATH]={0};
			sprintf_s(timeout, "%d", nTimeOut);
			av_dict_set(&opts, "stimeout", timeout, 0); // 设置超时时间，单位微秒

			if (pRTSP->m_TCP)
				av_dict_set(&opts, "rtsp_transport", "tcp", 0); 

			if(avformat_open_input(&fmt_ctx, pRTSP->m_cRSTPAddr, NULL, &opts)==0) 
			{
				TRACE(_T("RTSP=%s\n"),pRTSP->m_RSTPAddr);

				if(avformat_find_stream_info(fmt_ctx, NULL)>=0)
				{
					TRACE(_T("RTSP=%s\n"),pRTSP->m_RSTPAddr);

					av_dict_free(&opts);
					for (int i = 0; i < (int)fmt_ctx->nb_streams; i++) 
					{
						if(fmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
						{
							codec_ctx = fmt_ctx->streams[i]->codec;
							video_index = i;
							break;
						}
					}

					if (codec_ctx == 0) 
					{
						// 不包含视频，退出
						avformat_close_input(&fmt_ctx);
						open_wait_time = av_gettime() + 1500000;
						continue;
					}

					codec = avcodec_find_decoder(codec_ctx->codec_id);
					if (codec == NULL)
					{
						// 找不到解码器，退出
						avformat_close_input(&fmt_ctx);
						open_wait_time = av_gettime() + 1500000;
						continue;
					}

					if (avcodec_open2(codec_ctx, codec, NULL) < 0)
					{
						// 打开解码器错误，退出
						avformat_close_input(&fmt_ctx);
						open_wait_time = av_gettime() + 1500000;
						continue;
					}

					if ((0 == codec_ctx->width)
						|| (0 == codec_ctx->height)
						|| (-1 == codec_ctx->pix_fmt))
					{
						avcodec_close(codec_ctx);
						avformat_close_input(&fmt_ctx);
						open_wait_time = av_gettime() + 1500000;
						continue;
					}

					pRTSP->m_sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt, 
						codec_ctx->width, codec_ctx->height, AV_PIX_FMT_YUV420P, 
						SWS_FAST_BILINEAR, NULL, NULL, NULL); 

					if (NULL == pRTSP->m_sws_ctx)
					{
						avcodec_close(codec_ctx);
						avformat_close_input(&fmt_ctx);
						open_wait_time = av_gettime() + 1500000;
						continue;
					}

					pRTSP->m_codec_ctx = codec_ctx;
					pRTSP->m_codec = codec;
					pRTSP->m_frame = av_frame_alloc();

					EnterCriticalSection(&pRTSP->m_CSFrameYUV);
					if (pRTSP->m_frame_yuv_Width != codec_ctx->width || pRTSP->m_frame_yuv_Height != codec_ctx->height)
					{
						if (pRTSP->m_frame_yuv_Width != -1)
						{
							//afxDump<<"not equal ip:"<<pRTSP->m_RSTPAddr<<" codec_ctx width:"<<codec_ctx->width<<" Height:"<<codec_ctx->height<<" old width:"<<pRTSP->m_frame_yuv_Width<<" old Height:"<<pRTSP->m_frame_yuv_Height<<"\n";
						}
						pRTSP->ClearFrameYUVData();
					}

					if (pRTSP->m_frame_yuv == NULL)
					{
						pRTSP->m_frame_yuv = av_frame_alloc();
						int nOut_buffer_Size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codec_ctx->width, codec_ctx->height, 1);
						pRTSP->m_out_buffer = (uint8_t *)av_malloc(nOut_buffer_Size);
						ZeroMemory(pRTSP->m_out_buffer, nOut_buffer_Size);
						av_image_fill_arrays(pRTSP->m_frame_yuv->data, pRTSP->m_frame_yuv->linesize, 
							pRTSP->m_out_buffer, AV_PIX_FMT_YUV420P, 
							codec_ctx->width, codec_ctx->height, 1);
						pRTSP->m_frame_yuv_Width = codec_ctx->width;
						pRTSP->m_frame_yuv_Height = codec_ctx->height;
					}

					LeaveCriticalSection(&pRTSP->m_CSFrameYUV);

					pRTSP->m_video_index = video_index;
					pRTSP->m_pts = AV_NOPTS_VALUE;
					pRTSP->m_fmt_ctx = fmt_ctx;
					pRTSP->StartDecodeThread();
					break;
				}
				else
				{
					TRACE(_T("%s--%s\n"),pRTSP->m_RSTPAddr,_T("avformat_find_stream_info error\n"));
				}
			}
			else
			{
				TRACE(_T("%s--%s\n"),pRTSP->m_RSTPAddr,_T("avformat_open_input error\n"));
			}

			av_dict_free(&opts);
			if (fmt_ctx)
			{
				avformat_close_input(&fmt_ctx);
			}
			open_wait_time = av_gettime() + 1500000;	
		} 
		else 
		{
			SDL_Delay(50);
		}
	}

	if (NULL != pRTSP->m_OpenThreadEvent)
	{
		SetEvent(pRTSP->m_OpenThreadEvent);
	}

	pRTSP->m_bOpenThread = FALSE;
	return 0;
}

void XRTSP::ClearData()
{
	//afxDump<<"XRTSP::ClearData() begin "<<m_cRSTPAddr<<"\n";

	m_Running = FALSE;

	StopOpenThread();
	StopDecodeThread();

	if (m_fmt_ctx) 
	{
		sws_freeContext(m_sws_ctx);
		av_frame_free(&m_frame);
		avcodec_close(m_codec_ctx);
		avformat_close_input(&m_fmt_ctx);
		m_fmt_ctx=NULL;
	}

	m_RecvFlagKey=FALSE;

	//afxDump<<"XRTSP::ClearData() end "<<m_cRSTPAddr<<"\n";
}

void XRTSP::StopOpenThread()
{
	if (m_OpenThreadEvent != NULL)
	{
		WaitForSingleObject(m_OpenThreadEvent, INFINITE);

		CloseHandle(m_OpenThreadEvent); 

		m_OpenThreadEvent = NULL;
	}
}

void XRTSP::CloseOpenThreadEvent()
{
	if (m_OpenThreadEvent != NULL)
	{
		CloseHandle(m_OpenThreadEvent); 

		m_OpenThreadEvent = NULL;
	}
}

void XRTSP::StopDecodeThread()
{
	if (m_DecodeThreadEvent != NULL)
	{
		WaitForSingleObject(m_DecodeThreadEvent, INFINITE);

		CloseHandle(m_DecodeThreadEvent); 

		m_DecodeThreadEvent = NULL;
	}
}

void XRTSP::CloseDecodeThreadEvent()
{
	if (m_DecodeThreadEvent != NULL)
	{
		CloseHandle(m_DecodeThreadEvent); 

		m_DecodeThreadEvent = NULL;
	}
}

void XRTSP::OpenURL()
{
	StartOpenThread();
}

BOOL XRTSP::StartDecodeThread()
{
	//需要先设置线程启动变量为TRUE,否则线程立即结束，导致线程结束，但线程启动变量为TRUE问题出现
	m_bDecodeThread = TRUE;

	m_DecodeThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (NULL != m_DecodeThreadEvent)
	{
		CWinThread* pDecodethread = AfxBeginThread((AFX_THREADPROC)decode_thread, (void*)this);

		if (NULL == pDecodethread) 
		{
			CloseDecodeThreadEvent();

			//TRACE("StartDecodeThread AfxBeginThread failed\n");

			m_bDecodeThread = FALSE;
		}
	}
	else
	{
		m_bDecodeThread = FALSE;
	}

	return m_bDecodeThread;
}

BOOL XRTSP::StartOpenThread()
{
	m_bOpenThread = TRUE;

	m_OpenThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_OpenThreadEvent != NULL)
	{
		CWinThread* pOpenThread = AfxBeginThread((AFX_THREADPROC)urlopen_thread, (void*)this);

		if (NULL == pOpenThread) 
		{
			CloseOpenThreadEvent();

			//TRACE("urlopen_thread AfxBeginThread failed\n");

			m_bOpenThread = FALSE;
		} 
	}
	else
	{
		m_bOpenThread = FALSE;
	}

	return m_bOpenThread;
}

void XRTSP::SetStateType(STATETYPE s)
{
	m_StateType = s;
}

void XRTSP::Open()
{
	m_StateType = STATETYPE_OPEN;

	m_Running = TRUE;

	OpenURL();
}

void XRTSP::Close()
{
	m_Running = FALSE;

	m_StateType = STATETYPE_CLOSE;
}

void XRTSP::Stop()
{
	m_Running = FALSE;

	m_StateType = STATETYPE_STOP;
}

void XRTSP::SetRunning(BOOL b)
{
	m_Running = b;
}

STATETYPE XRTSP::GetStateType()
{
	return m_StateType;
}

BOOL XRTSP::ThreadRunState()
{
	if (m_bOpenThread)
	{
		return TRUE;
	}

	if (m_bDecodeThread)
	{
		return TRUE;
	}

	return FALSE;
}

void XRTSP::SetTCP(BOOL b)
{
	m_TCP = b;
}

void XRTSP::SetConnectTimeOut(int n)
{
	m_ConnectTimeOut = n;
}

void XRTSP::SetCount(int n)
{
	m_nCount=n;
}

int XRTSP::GetCount()
{
	return m_nCount;
}