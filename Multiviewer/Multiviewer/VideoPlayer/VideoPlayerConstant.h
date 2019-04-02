#pragma once

class XRTSP;
#define MAP_RTSP std::map<CString, XRTSP*>

class XRTSPHWNDS;
#define MAP_RTSPHWNDS std::map<CString, XRTSPHWNDS*>

class XMultiVideoWindow;
#define VEC_MULTIVIDEOWINDOW std::vector<XMultiVideoWindow*>

class XMultiVideoWindowFrame;
#define VEC_MULTIVIDEOWINDOWFRAME std::vector<XMultiVideoWindowFrame*>

class XMultiVideoWindowFrames;
#define MAP_MULTIVIDEOWINDOWFRAMES std::map<int, XMultiVideoWindowFrames*>

class XRTSPHWND;
#define VEC_RTSPHWND std::vector<XRTSPHWND*>

#define MAP_RTSPADDRSHOWCOUNT std::map<CString, unsigned int>

#define VEC_RECT std::vector<CRect>

#define VEC_NUM std::vector<int>

#define MAP_FRAMEID std::map<unsigned int,SDL_Rect>

class XScreenRowInfo;
#define MAP_FRAMEROWINFO std::map<int,XScreenRowInfo*>

class XScreenColInfo;
#define MAP_FRAMECOLINFO std::map<int,XScreenColInfo*>