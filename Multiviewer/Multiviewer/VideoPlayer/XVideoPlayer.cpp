#include "StdAfx.h"
#include "XVideoPlayer.h"
#include "XRTSP.h"
#include "XRTSPHWND.h"
#include "XRTSPInfo.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XConstantIM.h"
#include "XMultiVideoWindow.h"
#include "XVideoPreviewPane.h"

//SDL
#define SDL_BREAK_EVENT	(SDL_USEREVENT + 1)

XVideoPlayer::XVideoPlayer(void)
{
	m_Running = FALSE;

	m_MainThreadEvent = NULL;

	m_HardDecode = TRUE;

	m_TCP = FALSE;

	m_SetFontPath = FALSE;

	InitializeCriticalSection(&m_CSRTSP);

	InitializeCriticalSection(&m_CSRTSPHWND);

	InitializeCriticalSection(&m_CSMultiVideoWindow);
}

XVideoPlayer::~XVideoPlayer(void)
{
	DeleteCriticalSection(&m_CSRTSP);

	DeleteCriticalSection(&m_CSRTSPHWND);

	DeleteCriticalSection(&m_CSMultiVideoWindow);
}

void XVideoPlayer::ClearData()
{
	//TRACE("XVideoPlayer::ClearData Begin\n");

	av_lockmgr_register(NULL);

	Quit();

	//TRACE("XVideoPlayer::ClearData End\n");
}

void XVideoPlayer::ClearVecRTSPHWND()
{
	for (VEC_RTSPHWND::iterator iter = m_VecRTSPHWND.begin(); iter != m_VecRTSPHWND.end(); iter++)
	{
		delete *iter;
	}

	m_VecRTSPHWND.clear();
}

void XVideoPlayer::ClearMapRTSP()
{
	for (MAP_RTSP::iterator iter = m_MapRTSP.begin(); iter != m_MapRTSP.end(); iter++)
	{
		delete iter->second;
	}

	m_MapRTSP.clear();
}

void XVideoPlayer::ClearVecMultiVideoWindow()
{
	for (VEC_MULTIVIDEOWINDOW::iterator iter = m_VecMultiVideoWindow.begin(); iter != m_VecMultiVideoWindow.end(); iter++)
	{
		XMultiVideoWindow* p=*iter;

		//TRACE("ClearVecMultiVideoWindow=%x\n",p->GetHWND());

		delete *iter;
	}

	m_VecMultiVideoWindow.clear();
}

void XVideoPlayer::StopAllRTSPRunning()
{
	for (MAP_RTSP::iterator iter = m_MapRTSP.begin(); iter != m_MapRTSP.end(); iter++)
	{
		XRTSP* pRTSP = iter->second;

		pRTSP->SetRunning(FALSE);
	}
}

void XVideoPlayer::AddRTSP(CString szRTSPAddr,int ncount)
{
	if (_T("") == szRTSPAddr)
	{
		return;
	}

	AddRTSPAddr(szRTSPAddr,ncount);
}

void XVideoPlayer::AddRTSPAddr(CString szRTSPAddr,int nCount)
{
	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter=m_MapRTSP.find(szRTSPAddr);

	XRTSP* pRTSP=NULL;

	if (m_MapRTSP.end()==iter)
	{
		pRTSP = new XRTSP();
		pRTSP->SetVideoPlayer(this);
		pRTSP->SetRSTPAddr(szRTSPAddr);
		pRTSP->Init();

		m_MapRTSP.insert(std::pair<CString, XRTSP*>(szRTSPAddr, pRTSP));
	}
	else
	{
		pRTSP = iter->second;
	}

	pRTSP->SetCount(nCount);

	pRTSP->SetTCP(m_TCP);

	pRTSP->SetConnectTimeOut(2000);

	LeaveCriticalSection(&m_CSRTSP);
}

void XVideoPlayer::SetRTSPCountPlus(CString szRTSPAddr)
{
	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter = m_MapRTSP.find(szRTSPAddr);

	if (m_MapRTSP.end() != iter)
	{
		XRTSP* pRTSP = iter->second;

		int nCount=pRTSP->GetCount();

		nCount=nCount+1;

		pRTSP->SetCount(nCount);
	}

	LeaveCriticalSection(&m_CSRTSP);
}

void XVideoPlayer::SetRTSPCountLess(CString szRTSPAddr)
{
	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter = m_MapRTSP.find(szRTSPAddr);

	if (m_MapRTSP.end() != iter)
	{
		XRTSP* pRTSP = iter->second;

		int nCount=pRTSP->GetCount();

		if(nCount!=0)
		{
			nCount=nCount-1;

			pRTSP->SetCount(nCount);
		}
	}

	LeaveCriticalSection(&m_CSRTSP);
}

void XVideoPlayer::SetRTSPAddrCount(CString szRTSPAddr,int nCount)
{
	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter = m_MapRTSP.find(szRTSPAddr);

	if (m_MapRTSP.end() != iter)
	{
		XRTSP* pRTSP = iter->second;

		if(nCount!=0)
		{
			pRTSP->SetCount(nCount);
		}
	}

	LeaveCriticalSection(&m_CSRTSP);
}

void XVideoPlayer::DeleteRTSP(CString szRTSPAddr)
{
	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter = m_MapRTSP.find(szRTSPAddr);

	if (m_MapRTSP.end() != iter)
	{
		XRTSP* pRTSP = iter->second;

		int nCount=pRTSP->GetCount();

		nCount=0;

		pRTSP->SetCount(nCount);
	}

	LeaveCriticalSection(&m_CSRTSP);
}

int XVideoPlayer::GetRTSPConnectState(CString szRTSPAddr)
{
	int nResult = 0;

	EnterCriticalSection(&m_CSRTSP);

	MAP_RTSP::iterator iter = m_MapRTSP.find(szRTSPAddr);

	XRTSP* pRTSP = NULL;

	if (m_MapRTSP.end() == iter)
	{
		nResult = -2;
	}
	else
	{
		pRTSP = iter->second;

		if (pRTSP->m_bDecodeThread)
		{
			nResult = 1;
		}
		else if (pRTSP->m_bOpenThread)
		{
			nResult = 2;
		}
		else
		{
			nResult = 0;
		}
	}

	LeaveCriticalSection(&m_CSRTSP);

	return nResult;
}

void XVideoPlayer::AddRTSPHWND(HWND h)
{
	AddRTSPHWND(h, _T(""));
}

XRTSPHWND* XVideoPlayer::GetRTSPHWND(HWND h)
{
	for (VEC_RTSPHWND::iterator iter = m_VecRTSPHWND.begin(); iter != m_VecRTSPHWND.end(); iter++)
	{
		XRTSPHWND* pRTSPHwnd = *iter;

		if (pRTSPHwnd->m_HWND == h)
		{
			return pRTSPHwnd;
		}
	}

	return NULL;
}

void XVideoPlayer::AddRTSPHWND(HWND h, CString szRTSPAddr)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	if (NULL == GetRTSPHWND(h))
	{
		XRTSPHWND* pRTSPHWND = new XRTSPHWND;

		pRTSPHWND->SetVideoPlayer(this);

		pRTSPHWND->SetHWND(h);

		pRTSPHWND->CreateSDLWindow();

		pRTSPHWND->SetResetVideoShow(TRUE);

		pRTSPHWND->SetRTSPAddr(szRTSPAddr);

		m_VecRTSPHWND.push_back(pRTSPHWND);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::SetRTSPHWNDRTSPAddr(HWND h, CString szRTSPAddr)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetRTSPAddr(szRTSPAddr);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::SetRTSPHWNDBGColor(HWND h, Uint8 r, Uint8 g, Uint8 b)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetBGColor(r, g, b, 240);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::AdjustRTSPHWNDSize(HWND h, int nWidth, int nHeight)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND && NULL != pRTSPHWND->m_window)
	{
		if (pRTSPHWND->m_HWNDWidth != nWidth || pRTSPHWND->m_HWNDHeight != nHeight)
		{
			//TRACE("SDL_SetWindowSize begin\n");

			SDL_SetWindowSize(pRTSPHWND->m_window, nWidth, nHeight);

			pRTSPHWND->m_HWNDWidth = nWidth;

			pRTSPHWND->m_HWNDHeight = nHeight;
		}
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::DeleteRTSPHWND(HWND h)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	for (VEC_RTSPHWND::iterator iter = m_VecRTSPHWND.begin(); iter != m_VecRTSPHWND.end(); iter++)
	{
		XRTSPHWND* pRTSPHwnd = *iter;

		if (pRTSPHwnd->m_HWND == h)
		{
			delete pRTSPHwnd;

			m_VecRTSPHWND.erase(iter);

			break;
		}
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

XMultiVideoWindow* XVideoPlayer::AddMultiVideoWindow(HWND h)
{
	return AddMultiVideoWindow(h, 40, 41, 45);
}

XMultiVideoWindow* XVideoPlayer::AddMultiVideoWindow(HWND h, Uint8 r, Uint8 g, Uint8 b)
{
	EnterCriticalSection(&m_CSMultiVideoWindow);

	XMultiVideoWindow* pMultiVideoWindow = NULL;

	pMultiVideoWindow = new XMultiVideoWindow;

	pMultiVideoWindow->SetVideoPlayer(this);

	pMultiVideoWindow->InitFont();

	pMultiVideoWindow->SetHWND(h);

	pMultiVideoWindow->CreateSDLWindow();

	pMultiVideoWindow->SetBGColor(r, g, b);

	pMultiVideoWindow->SetResetVideoShow(TRUE);

	m_VecMultiVideoWindow.push_back(pMultiVideoWindow);

	LeaveCriticalSection(&m_CSMultiVideoWindow);

	return pMultiVideoWindow;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void XVideoPlayer::Display_rtsphwnd()
{
	//DWORD dwBegin = GetTickCount();

	EnterCriticalSection(&m_CSRTSP);

	EnterCriticalSection(&m_CSRTSPHWND);

	for (VEC_RTSPHWND::iterator iter = m_VecRTSPHWND.begin(); iter != m_VecRTSPHWND.end(); iter++)
	{
		XRTSPHWND* pHWND = *iter;

		if (pHWND->GetCreateSDLWindow())
		{
			HWND hwnd = pHWND->GetHWND();

			if(!::IsWindowVisible(hwnd))
			{
				continue;
			}

			if (pHWND->GetResetVideoShow())
			{
				pHWND->ResetVideoShow();

				pHWND->SetResetVideoShow(FALSE);

				continue;
			}

			if (!pHWND->GetCreateSDLRenderer())
			{
				continue;
			}

			BOOL bRenderCopyImage = FALSE;
			
			CString szRTSPAddr = pHWND->GetRTSPAddr();

			if (szRTSPAddr != _T(""))
			{
				/////////////////////////////////////////////////////////ÕºœÒ
				MAP_RTSP::iterator iterRTSP = m_MapRTSP.find(szRTSPAddr);

				if (m_MapRTSP.end() != iterRTSP)
				{
					XRTSP* pRTSP = iterRTSP->second;
	
					EnterCriticalSection(&pRTSP->m_CSFrameYUV);

					if (pHWND->CreateTexture(pRTSP))
					{
						if (pRTSP->m_frame_yuv != NULL && pRTSP->m_RecvFlagKey) 
						{
							SDL_UpdateTexture(pHWND->m_texture, NULL, pRTSP->m_frame_yuv->data[0], pRTSP->m_frame_yuv->linesize[0]);

							SDL_RenderCopy(pHWND->m_renderer, pHWND->m_texture, NULL, NULL);

							bRenderCopyImage = TRUE;
						}
					}

					LeaveCriticalSection(&pRTSP->m_CSFrameYUV);
				}
			}

			//±≥æ∞—’…´
			if (!bRenderCopyImage)
			{
				SDL_SetRenderDrawColor(pHWND->m_renderer, pHWND->m_BGColor.r, pHWND->m_BGColor.g, pHWND->m_BGColor.b, pHWND->m_BGColor.a);

				SDL_RenderClear(pHWND->m_renderer);
			}

			//Œƒ◊÷
			if (pHWND->m_CreateTextureText)
			{
				pHWND->CreateTextureText();

				pHWND->BeginTextScroll();
			}

			if (NULL != pHWND->m_textureText)
			{
				SDL_Rect srcRect = pHWND->GetTextScrollSrcRect();

				if (srcRect.w <= 0)
				{
					pHWND->BeginTextScroll();
				}
				else
				{
					SDL_Rect desRect = pHWND->GetTextScrollDesRect();

					SDL_RenderCopy(pHWND->m_renderer, pHWND->m_textureText, &srcRect, &desRect);

					pHWND->TextScroll();
				}
			}

			SDL_RenderPresent(pHWND->m_renderer);
		}
	}

	LeaveCriticalSection(&m_CSRTSPHWND);

	LeaveCriticalSection(&m_CSRTSP);

	//DWORD dwEnd = GetTickCount();

	//afxDump<<"Display_rtsphwnd UserTime:"<<dwEnd - dwBegin<<"===================\n";
}

static int main_thread(void *ptr)
{
	XVideoPlayer* pVideoPlayer = (XVideoPlayer*)ptr;

	SDL_Event event;

	int64_t show_time = av_gettime();
	//TRACE(_T("show_time=%d\n"),show_time);
	//TRACE(_T("GetTickCount=%d\n"),GetTickCount());
	int64_t handlertspshow_time = av_gettime();

	while (pVideoPlayer->m_Running) 
	{
		if (SDL_WaitEventTimeout(&event, 0)) 
		{	
			switch (event.type) 
			{
			case SDL_QUIT:
			case SDL_BREAK_EVENT:
				{
					pVideoPlayer->m_Running = false;
				}
				break;
			default:
				break;
			}
		} 
		else if (av_gettime() >= show_time)
		{
			//afxDump<<"Display_video begin\n";
			//TRACE(_T("av_gettime=%d\n"),av_gettime());

			pVideoPlayer->Display_rtsphwnd();

			pVideoPlayer->Display_multiVideoWindow();

			//afxDump<<"Display_video end\n";

			// œ‘ æ ”∆µ£¨√ø√Î30÷°
			show_time += (1000000/30);

			if(av_gettime() >= handlertspshow_time)
			{
				pVideoPlayer->HandleRTSPShow();

				handlertspshow_time += (1000000);
			}
		}
		else
		{
			SDL_Delay(5);
		}
	}

	if (NULL != pVideoPlayer->m_MainThreadEvent)
	{
		SetEvent(pVideoPlayer->m_MainThreadEvent);
	}

	return 0;
}


int XVideoPlayer::Init()
{
	// SDL≥ı ºªØ
	int ret=SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS/* | SDL_INIT_TIMER*/);

	if (ret) 
	{
		return ret;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	IMG_Init(IMG_INIT_JPG);

	TTF_Init(); 

	InitData();

	m_Running=TRUE;

	if(!BeginMainThread())
	{
		return -1;
	}

	//TRACE("XVideoPlayer::Init Success\n");

	return 0;
}

void XVideoPlayer::InitData()
{
	CString szIniPath = HandlePath::GetIniPath(APP_ININAME);

	CString szHardDecode = HandleIni::GetString(_T("Info"), _T("HardDecode"), _T(""), szIniPath);
	if (_T("") == szHardDecode)
	{
		m_HardDecode = TRUE;
		HandleIni::WriteData(_T("Info"), _T("HardDecode"), _T("1"), szIniPath);
	}
	else
	{
		m_HardDecode = _ttoi(szHardDecode);
	}

	CString szTCP = HandleIni::GetString(_T("Info"), _T("RTSPTCP"), _T(""), szIniPath);
	if (_T("") == szTCP)
	{
		m_TCP = FALSE;
		HandleIni::WriteData(_T("Info"), _T("RTSPTCP"), _T("0"), szIniPath);
	}
	else
	{
		m_TCP = _ttoi(szTCP);
	}
}

BOOL XVideoPlayer::BeginMainThread()
{
	m_Running = TRUE;

	m_MainThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_MainThreadEvent != NULL)
	{
		CWinThread* pThread = AfxBeginThread((AFX_THREADPROC)main_thread, (void*)this);

		if (NULL == pThread) 
		{
			CloseMainThreadEvent();

			TRACE("main_thread AfxBeginThread failed\n");

			m_Running = FALSE;
		} 
	}
	else
	{
		m_Running = FALSE;
	}

	return m_Running;
}

void XVideoPlayer::StopMainThread()
{
	if (m_MainThreadEvent != NULL)
	{
		WaitForSingleObject(m_MainThreadEvent, INFINITE);

		CloseHandle(m_MainThreadEvent); 

		m_MainThreadEvent = NULL;
	}
}

void XVideoPlayer::CloseMainThreadEvent()
{
	if (m_MainThreadEvent != NULL)
	{
		CloseHandle(m_MainThreadEvent); 

		m_MainThreadEvent = NULL;
	}
}

static int lockmgr(void **mtx, enum AVLockOp op)
{
	switch(op) 
	{
	case AV_LOCK_CREATE:
		*mtx = SDL_CreateMutex();
		if(!*mtx) 
		{
			av_log(NULL, AV_LOG_FATAL, "SDL_CreateMutex(): %s\n", SDL_GetError());
			return 1;
		}
		return 0;
	case AV_LOCK_OBTAIN:
		return !!SDL_LockMutex((SDL_mutex *)(*mtx));
	case AV_LOCK_RELEASE:
		return !!SDL_UnlockMutex((SDL_mutex *)(*mtx));
	case AV_LOCK_DESTROY:
		SDL_DestroyMutex((SDL_mutex *)(*mtx));
		return 0;
	}

	return 1;
}

void ffmpeg_log_callback(void*avcl, int level, const char*fmt, va_list vl)  
{  
	char log[1024]; 

	vsnprintf_s(log,sizeof(log),fmt,vl);  

	OutputDebugStringA(log);  
}  

void XVideoPlayer::InitFFMPEG()
{
	av_register_all();
	//avcodec_register_all();
	avformat_network_init();

	//av_log_set_callback(ffmpeg_log_callback);

	if (av_lockmgr_register(lockmgr) < 0) {

		//TRACE("av_lockmgr_register Fail\n");
	}
	else
	{
		//TRACE("XVideoPlayer::InitFFMPEG Success\n");
	}
}

void XVideoPlayer::Quit()
{
	//afxDump<<"XVideoPlayer::Quit() begin\n";

	m_Running = FALSE;

	StopMainThread();

	StopAllRTSPRunning();

	ClearVecRTSPHWND();

	ClearVecMultiVideoWindow();

	ClearMapRTSP();

	SDL_Quit();

	//afxDump<<"XVideoPlayer::Quit() end\n";
}

void XVideoPlayer::HandleRTSPShow()
{
	//TRACE("XVideoPlayer::HandleRTSPShow Begin %d\n", GetTickCount())

	EnterCriticalSection(&m_CSRTSP);
	//EnterCriticalSection(&m_CSRTSPADDRSHOWCOUNT);
	
	for (MAP_RTSP::iterator iter = m_MapRTSP.begin(); iter != m_MapRTSP.end();)
	{
		XRTSP* pRTSP = iter->second;

		CString szRTSPAddr = pRTSP->GetRSTPAddr();

		//unsigned int nShowCount = m_PreviewPan->GetRTSPAddrCount(szRTSPAddr);

		int nShowCount=pRTSP->GetCount();

		//TRACE(_T("ShowRTSP=%s,Count=%d\n"),szRTSPAddr,nShowCount);

		STATETYPE stateType = pRTSP->GetStateType();

		switch(stateType)
		{
		case STATETYPE_NULL:
			{
				if (nShowCount > 0)
				{
					//afxDump<<"STATETYPE_NULL Open RTSP:"<<pRTSP->GetRSTPAddr()<<"\n";

					pRTSP->Open();
				}
			}
			break;
		case STATETYPE_OPEN:
			{
				if (nShowCount == 0)
				{
					//afxDump<<"STATETYPE_OPEN Stop RTSP:"<<pRTSP->GetRSTPAddr()<<"\n";

					pRTSP->Stop();
				}
				else
				{
					if (!pRTSP->ThreadRunState())
					{
						//afxDump<<"STATETYPE_OPEN ThreadRunState RTSP:"<<pRTSP->GetRSTPAddr()<<"\n";

						pRTSP->ClearData();

						pRTSP->Open();
					}
				}
			}
			break;
		case STATETYPE_STOP:
			{
				if (!pRTSP->ThreadRunState())
				{
					//afxDump<<"STATETYPE_STOP StopSuccess RTSP:"<<pRTSP->GetRSTPAddr()<<"\n";

					pRTSP->ClearData();

					pRTSP->SetStateType(STATETYPE_NULL);
				}
			}
			break;
		case STATETYPE_CLOSE:
			{
				if (!pRTSP->ThreadRunState())
				{
					//afxDump<<"STATETYPE_CLOSE CloseSuccess RTSP:"<<pRTSP->GetRSTPAddr()<<"\n";

					delete pRTSP;

					iter = m_MapRTSP.erase(iter);

					continue;
				}
				else
				{
					//afxDump<<"STATETYPE_CLOSE running"<<"\n";
				}
			}
			break;
		default:
			break;
		}

		iter++;
	}

	LeaveCriticalSection(&m_CSRTSP);
	//LeaveCriticalSection(&m_CSRTSPADDRSHOWCOUNT);

	//TRACE("XVideoPlayer::HandleRTSPShow End %d\n", GetTickCount());
}


BOOL XVideoPlayer::GetHardDecode()
{
	return m_HardDecode;
}

MAP_RTSP& XVideoPlayer::GetMapRTSP()
{
	return m_MapRTSP;
}

void XVideoPlayer::SetHardDecode(BOOL bHardDecode)
{
	m_HardDecode = bHardDecode;
}

void XVideoPlayer::SetFontPath(CString szFontPath)
{
	ZeroMemory(m_FontPath, MAX_PATH);

	ChangeDataToUTF8(szFontPath, m_FontPath);

	m_SetFontPath = TRUE;
}

void XVideoPlayer::ChangeDataToUTF8(CString szFontPath, char* pUTF8Data)
{
	LPTSTR pSrc = szFontPath.GetBuffer(0);

	int nLen = ::WideCharToMultiByte(CP_UTF8,  0,  pSrc,  -1, NULL, 0, NULL, FALSE);

	if (nLen > 0)
	{
		::WideCharToMultiByte(CP_UTF8,  0,  pSrc,  -1,  pUTF8Data,  nLen, NULL, FALSE);
	}

	szFontPath.ReleaseBuffer();
}

void XVideoPlayer::SetRTSPHWNDText(HWND h, CString szText)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetText(szText);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::SetRTSPHWNDTextColor(HWND h, Uint8 r, Uint8 g, Uint8 b)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetTextColor(r, g, b, 255);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::SetRTSPHWNDTextSize(HWND h, int n)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetTextSize(n);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::CreateTextureOfText(SDL_Renderer* pRenderer, CString szText, int nTextSize, 
	SDL_Color color, SDL_Texture*& pTexture, int& nWidth, int& nHeight)
{
	if (!m_SetFontPath)
	{
		return;
	}

	if (NULL == pRenderer)
	{
		return;
	}

	if (_T("") == szText)
	{
		return;
	}

	SDL_Surface* pSurface = CreateSurfaceOfText(szText, nTextSize, color);

	if (pSurface == NULL)
	{
		return;
	}

	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

	nWidth = pSurface->w;

	nHeight = pSurface->h;

	SDL_FreeSurface(pSurface);
}

SDL_Surface* XVideoPlayer::CreateSurfaceOfText(CString szText, int nTextSize, SDL_Color color)
{
	if (szText == _T(""))
	{
		return NULL;
	}

	TTF_Font *font = TTF_OpenFont(m_FontPath, nTextSize); 

	if (font == NULL)  
	{  
		return NULL;  
	}  

	SDL_Surface* pSurface = TTF_RenderUNICODE_Blended(font,(Uint16*)szText.GetBuffer(0), color);
	//SDL_Surface* pSurface=TTF_RenderUNICODE_Blended_Wrapped(font,(Uint16*)szText.GetBuffer(0),color,70);

	szText.ReleaseBuffer();

	TTF_CloseFont(font);

	return pSurface;
}

void XVideoPlayer::SetRTSPHWNDTextScrollRect(HWND h, int nLeft, int nTop, int nRight)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetTextScrollRect(nLeft, nTop, nRight);

		pRTSPHWND->BeginTextScroll();
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::SetRTSPHWNDTextScrollTimeAndStep(HWND h, int nDistanceTime, int nStep)
{
	EnterCriticalSection(&m_CSRTSPHWND);

	XRTSPHWND* pRTSPHWND = GetRTSPHWND(h);

	if (NULL != pRTSPHWND)
	{
		pRTSPHWND->SetHWNDTextScrollTimeAndStep(nDistanceTime, nStep);
	}

	LeaveCriticalSection(&m_CSRTSPHWND);
}

void XVideoPlayer::AdjustMultiVideoWindowHWNDSize(XMultiVideoWindow* p,int nWidth, int nHeight)
{
	//TRACE("AdjustMultiVideoWindowHWNDSize begin\n");
	EnterCriticalSection(&m_CSMultiVideoWindow);

	for (VEC_MULTIVIDEOWINDOW::iterator iter = m_VecMultiVideoWindow.begin(); iter != m_VecMultiVideoWindow.end(); ++iter)
	{
		XMultiVideoWindow* pTemp = *iter;

		if(pTemp==p)
		{
			SDL_SetWindowSize(pTemp->m_window, nWidth, nHeight);
	
			//TRACE("AdjustMultiVideoWindowHWNDSize W:%d, H:%d\n", nWidth, nHeight);
		}
	}

	LeaveCriticalSection(&m_CSMultiVideoWindow);

	//TRACE("AdjustMultiVideoWindowHWNDSize end\n");
}

void XVideoPlayer::Display_multiVideoWindow()
{
	//DWORD dwBegin = GetTickCount();

	EnterCriticalSection(&m_CSMultiVideoWindow);

	for (VEC_MULTIVIDEOWINDOW::iterator iter = m_VecMultiVideoWindow.begin(); iter != m_VecMultiVideoWindow.end(); iter++)
	{
		XMultiVideoWindow* pHWND = *iter;

		if (!pHWND->GetCreateSDLWindow())
		{
			continue;
		}

		HWND hwnd = pHWND->GetHWND();

		if(!::IsWindowVisible(hwnd))
		{
			continue;
		}

		if (pHWND->GetResetVideoShow())
		{
			pHWND->ResetVideoShow();

			pHWND->SetResetVideoShow(FALSE);

			continue;
		}

		EnterCriticalSection(&m_CSRTSP);

		pHWND->Draw();

		LeaveCriticalSection(&m_CSRTSP);
	}

	LeaveCriticalSection(&m_CSMultiVideoWindow);

	//DWORD dwEnd = GetTickCount();

	//afxDump<<"Display_multiVideoWindow UserTime:"<<dwEnd - dwBegin<<"\n";
}