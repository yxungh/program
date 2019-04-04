#include <iostream>

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/time.h"
}

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")

using namespace std;

int AvError(int error)
{
	char buf[1024]={0};
	av_strerror(error,buf,sizeof(buf));
	cout<<buf<<endl;
	getchar();
	return -1;
}

static double r2d(AVRational r)
{
	return r.num==0||r.den==0?0.:(double)r.num/(double)r.den;
}

int main(int argc,char*argv[])
{
	//文件名
	char* inUrl="test.mp4";
	char* outUrl="rtmp://192.168.1.67/live";

	av_register_all();
	avformat_network_init();

	//输入输出上下文
	AVFormatContext* iCtx=NULL;
	AVFormatContext* oCtx=NULL;

	//输入
	int ret=avformat_open_input(&iCtx,inUrl,NULL,NULL);
	if(!iCtx)
	{
		return AvError(ret);
	}

	ret=avformat_find_stream_info(iCtx,NULL);
	if(ret<0)
	{
		return AvError(ret);
	}

	av_dump_format(iCtx,0,inUrl,0);
	cout<<"=================================="<<endl;
	//输出
	ret=avformat_alloc_output_context2(&oCtx,NULL,"flv",outUrl);
	if(ret<0)
	{
		return AvError(ret);
	}

	for(int i=0;i<iCtx->nb_streams;i++)
	{
		//创建输出流
		AVStream* out=avformat_new_stream(oCtx,iCtx->streams[i]->codec->codec);
		if(!out)
		{
			return AvError(0);
		}

		//ret=avcodec_copy_context(out->codec,iCtx->streams[i]->codec);
		ret=avcodec_parameters_copy(out->codecpar,iCtx->streams[i]->codecpar);
		if(ret<0)
		{
			return AvError(ret);
		}
		out->codec->codec_tag=0;
		out->codecpar->codec_tag=0;
	}

	av_dump_format(oCtx,0,outUrl,1);

	//打开IO
	ret=avio_open(&oCtx->pb,outUrl,AVIO_FLAG_WRITE);
	if(ret<0)
	{
		return AvError(ret);
	}

	//写入头文件
	ret=avformat_write_header(oCtx,NULL);
	if(ret<0)
	{
		return AvError(ret);
	}

	//获取时间，开机计算
	int64_t startTime=av_gettime();
	AVPacket pkt;
	for(;;)
	{
		ret=av_read_frame(iCtx,&pkt);
		if(ret<0)
		{
			//return AvError(ret);
			break;
		}


		//视频延时
		if(iCtx->streams[pkt.stream_index]->codecpar->codec_type==AVMEDIA_TYPE_AUDIO)
		{
			AVRational tb=iCtx->streams[pkt.stream_index]->time_base;
			AVRational time_base_q={1,AV_TIME_BASE};

			int64_t now=av_gettime()-startTime;
			int64_t dts=0;

			dts=av_rescale_q(pkt.dts,tb,time_base_q);
			//dts=pkt.dts*(1000*1000*r2d(tb));

			if(dts>now)
				av_usleep((unsigned int)(dts-now));
		}

			
		//计算pts
		AVRational itimeBase=iCtx->streams[pkt.stream_index]->time_base;
		AVRational otimeBase=oCtx->streams[pkt.stream_index]->time_base;
		pkt.pts=av_rescale_q(pkt.pts,itimeBase,otimeBase);
		pkt.dts=av_rescale_q(pkt.dts,itimeBase,otimeBase);
		pkt.duration=av_rescale_q(pkt.duration,itimeBase,otimeBase);
		pkt.pos=-1;


		cout<<pkt.pts<<" "<<flush;
		ret=av_interleaved_write_frame(oCtx,&pkt);
		if(ret<0)
		{
			return AvError(ret);
		}
	}

	getchar();
	return 0;
}