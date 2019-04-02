#pragma once

//Windows
extern "C"
{
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libswscale/swscale.h"
	#include "libswresample/swresample.h"
	#include "libavutil/imgutils.h"
	#include "libavutil/time.h"
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_error.h"
	#include "SDL2/SDL_image.h"
	#include "SDL2/SDL_ttf.h"
};

#pragma comment(lib, "videolib/avcodec.lib")
#pragma comment(lib, "videolib/avformat.lib")
#pragma comment(lib, "videolib/avutil.lib")
#pragma comment(lib, "videolib/swresample.lib")
#pragma comment(lib, "videolib/swscale.lib")
#pragma comment(lib, "videolib/SDL2.lib")
#pragma comment(lib, "videolib/SDL2_image.lib")
#pragma comment(lib, "videolib/SDL2_ttf.lib")

