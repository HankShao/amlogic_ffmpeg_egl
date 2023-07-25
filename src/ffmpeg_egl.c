#include "ffmpeg_egl.h"
#include "lt8612.h"
static long get_current_time(void)
{
	struct  timeval now_timeval;
	long ts_in_ms;
	gettimeofday(&now_timeval, NULL);
	ts_in_ms = 1000 * ((unsigned long long)now_timeval.tv_sec) +
			   ((unsigned long long)now_timeval.tv_usec / 1000);
	return ts_in_ms;
}

static int dtsctrl(AVContext *avctx,double dts)
{
	int64_t dtsdiff,timediff;
	int64_t diffoffset = 5;
	
	if(avctx->ctrl.firstdts == 0 || avctx->ctrl.fisttime == 0)
	{
		avctx->ctrl.firstdts = dts;
		avctx->ctrl.fisttime = get_current_time();
		return 0;
	}

	dtsdiff = dts-avctx->ctrl.firstdts;
	timediff = get_current_time() - avctx->ctrl.fisttime;

	if(timediff > dtsdiff || dtsdiff-timediff < diffoffset)
	{
		return 0;	
	}

	return -1;
}


static int pool_init(AVContext * avctx)
{
	struct AmlIPCVideoFormat fmt = {AML_PIXFMT_NV12, 1920, 1088, 1};

	fmt.width = IMAGE_ALIGNMENT(avctx->codec_ctx[avctx->best_streamid]->width,32);
	fmt.height = IMAGE_ALIGNMENT(avctx->codec_ctx[avctx->best_streamid]->height,32);
	fmt.pixfmt = AML_PIXFMT_NV12;
	
	int i,pitch;
	int size = aml_ipc_get_image_size(fmt.pixfmt, fmt.width , fmt.height, &pitch, 32);
	
    pthread_mutex_init(&avctx->pool.poollock, NULL);

	for(i = 0;i<MAX_DEC_REF_CNT;i++)
	{
		avctx->pool.dma_pool_array[i].dmabuf = AML_OBJ_NEW(AmlIPCVideoBuffer);
		// allocate a VideoBuffer to hold the pixel data
		if (aml_ipc_dma_buffer_alloc(avctx->pool.dma_pool_array[i].dmabuf, size) != 0) 
		{
			printf("dma pool alloc failed size:%d\n",size);
			return -1;
		}	

		avctx->pool.dma_pool_array[i].data = aml_ipc_dma_buffer_map(avctx->pool.dma_pool_array[i].dmabuf, AML_MAP_READ|AML_MAP_WRITE);
		if(NULL == avctx->pool.dma_pool_array[i].data)
		{
			printf("dma pool map failed\n");
			return -1;
		}
		avctx->pool.dma_pool_array[i].size = size;
		avctx->pool.dma_pool_array[i].used = 0;
		avctx->pool.dma_pool_array[i].id = i;
		
	}
	avctx->pool.pool_num = 0;	
	
	return 0;
}

static int pool_getentry(AVContext * avctx,void** ppdata,int *psize)
{
	if(!ppdata || !psize)
	{	
		printf("param error\n");
		return -1;	
	}
	
	int i;
	
	pthread_mutex_lock(&avctx->pool.poollock);
	for(i = 0;i<MAX_DEC_REF_CNT;i++)
	{
		if(avctx->pool.dma_pool_array[i].data && 0 == avctx->pool.dma_pool_array[i].used)
		{
			break;;
		}	
	}

	if(i >= MAX_DEC_REF_CNT)
	{
		printf("pool node not enough\n");
		pthread_mutex_unlock(&avctx->pool.poollock);
		return -1;
	}

	avctx->pool.pool_num++;	
	avctx->pool.dma_pool_array[i].used = 1;
	*ppdata = avctx->pool.dma_pool_array[i].data;
	*psize = avctx->pool.dma_pool_array[i].size;
	pthread_mutex_unlock(&avctx->pool.poollock);

	return 0;	
}

static int pool_putentry(AVContext * avctx,void *pdata)
{
	if(!pdata)
	{	
		printf("param error\n");
		return -1;	
	}
	
	int i;
	pthread_mutex_lock(&avctx->pool.poollock);
	for(i = 0;i<MAX_DEC_REF_CNT;i++)
	{
		if(pdata == avctx->pool.dma_pool_array[i].data && 1 == avctx->pool.dma_pool_array[i].used)
		{
			break;
		}	
	}

	if(i >= MAX_DEC_REF_CNT)
	{
		printf("pool node not find enough\n");
		pthread_mutex_unlock(&avctx->pool.poollock);
		return -1;
	}

	avctx->pool.pool_num--;	
	avctx->pool.dma_pool_array[i].used = 0;
	
	pthread_mutex_unlock(&avctx->pool.poollock);

	return 0;	
}

static AVDmaPoolNode* pool_quereyentry(AVContext * avctx, void *pdata)
{
	if(!pdata)
	{	
		printf("param error\n");
		return NULL;	
	}
	
	int i;
	pthread_mutex_lock(&avctx->pool.poollock);
	for(i = 0;i<MAX_DEC_REF_CNT;i++)
	{
		if(pdata == avctx->pool.dma_pool_array[i].data)
		{
			break;
		}	
	}

	if(i >= MAX_DEC_REF_CNT)
	{
		printf("pool node not find enough\n");
		pthread_mutex_unlock(&avctx->pool.poollock);
		return NULL;
	}
	pthread_mutex_unlock(&avctx->pool.poollock);

	return &avctx->pool.dma_pool_array[i];	
}


static int pool_uninit(AVContext * avctx)
{
	int i;
	for(i = 0;i<MAX_DEC_REF_CNT;i++)
	{
		aml_ipc_dma_buffer_unmap(avctx->pool.dma_pool_array[i].dmabuf);
		aml_obj_release(AML_OBJECT(avctx->pool.dma_pool_array[i].dmabuf));
	}

    pthread_mutex_init(&avctx->pool.poollock,NULL);

	memset(&avctx->pool,0,sizeof(AVDmaPool));
	
	return 0;
}

static void aml_sdk_init()
{
	// init AML IPC SDK and log system
	system("echo 1 > /sys/module/amvdec_ports/parameters/bypass_vpp");
	
	if(aml_ipc_sdk_init() < 0)
	{
		printf("aml_ipc_sdk_init error\n");
		return;
	}
	aml_ipc_log_set_from_string(".*:3");
	aml_ipc_trace_set_from_string(".*:3");
	
	//AML GUI
	system("echo 0 > /sys/class/graphics/fb1/blank");
	
	return;
}

static void aml_free_buffer(void * opaque,uint8_t * data)
{
	AVContext * avctx = (AVContext *)opaque;
	if(pool_putentry(avctx,(void *)data)<0)
	{
		printf("pool put node error\n");
		return;	
	}
	
	return;
}

#if 0
static int aml_get_buffer(struct AVCodecContext* avctx,AVFrame * pic,int flags)
{
	AVBufferRef * buf = NULL;
	uint8_t *data = NULL;
	int size = 0;

	if(pool_getentry(avctx,(void**)&data,&size)<0)
	{
		printf("pool get node error\n");
		return -1;	
	}

	buf = av_buffer_create(data,size,aml_free_buffer,NULL,0);

	pic->buf[0] = buf;
	//待补充

	return 0;	
}
#endif

int openfile(char *filename, AVContext *avctx)
{
	AVFormatContext *pfmt_ctx = NULL;
	AVDictionary *opt = NULL;
	int streamid = -1;

//#define RTSP
#ifdef  RTSP

	av_dict_set(&opt, "buffer_size", "2048000", 0);
	//av_dict_set(&opt, "rtsp_transport", "tcp", 0);
	av_dict_set(&opt, "stimeout", "20000000", 0);
	av_dict_set(&opt, "max_delay", "30000000", 0);
#endif	
	
	if(avformat_open_input(&pfmt_ctx, filename, NULL, &opt)<0)
	{
		fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
		return -1;
	}

	//av_dict_free(&opt);
	
	if(avformat_find_stream_info(pfmt_ctx,NULL)<0)
	{
		fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
		return -1;
	}

	streamid = av_find_best_stream(pfmt_ctx,AVMEDIA_TYPE_VIDEO,-1,-1,NULL,0);
	if(streamid < 0)
	{
		fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
		return -1;
	}
	
	av_dump_format(pfmt_ctx,0,filename,0);

	avctx->fmt_ctx = pfmt_ctx;
	avctx->best_streamid = streamid;

	return 0;
}

 int opendecoder(AVContext *avctx)
{	
	int i;
	avctx->codec_ctx = av_malloc_array(avctx->fmt_ctx->nb_streams,sizeof(AVCodecContext *));
	
	for(i=0;i<avctx->fmt_ctx->nb_streams;i++)
	{
		
		AVStream * pstream = avctx->fmt_ctx->streams[i];
		if(AVMEDIA_TYPE_VIDEO != pstream->codecpar->codec_type
			&& AVMEDIA_TYPE_AUDIO != pstream->codecpar->codec_type)
		{
			continue;
		}
		
		const AVCodec * pdec = avcodec_find_decoder(pstream->codecpar->codec_id);
		if(!pdec)
		{
			fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
			return -1;
		}
		
		AVCodecContext *pcodec_ctx;
		pcodec_ctx = avcodec_alloc_context3(pdec);
		if(!pcodec_ctx)
		{
			fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
			return -1;
		}

		//pstream->codecpar->format = AV_PIX_FMT_NV12;
		if(avcodec_parameters_to_context(pcodec_ctx, pstream->codecpar)<0)
		{
			fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
			return -1;
		}

		if(AVMEDIA_TYPE_VIDEO == pstream->codecpar->codec_type)
		{
			pcodec_ctx->framerate = av_guess_frame_rate(avctx->fmt_ctx, pstream, NULL);
		}
		
		AVDictionary *opt = NULL;
#ifdef  RTSP

		av_dict_set(&opt, "buffer_size", "2048000", 0);
		//av_dict_set(&opt, "rtsp_transport", "tcp", 0);
		av_dict_set(&opt, "stimeout", "20000000", 0);
		av_dict_set(&opt, "max_delay", "30000000", 0);
#endif	
		
		/*多线程解码*/
		pcodec_ctx->active_thread_type |= FF_THREAD_FRAME;
		pcodec_ctx->thread_type |= FF_THREAD_FRAME;
		pcodec_ctx->thread_count = 4;
		if(avcodec_open2(pcodec_ctx,pdec,&opt)<0)
		{
			fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);	
			return -1;
		}

		av_dict_free(&opt);

		fprintf(stdout,"vdec cap:%x\n",pdec->capabilities);	
		
		avctx->codec_ctx[pstream->index] = pcodec_ctx;	
		avctx->codec_ctx[pstream->index]->opaque = (void *)avctx;
#if 0	
		avctx->codec_ctx[pstream->index].get_buffer2 = aml_get_buffer;
#endif
	}

	return 0;
}

int opensws(AVContext *avctx,int index)
{
	AVCodecContext *pcodec_ctx = avctx->codec_ctx[index];
	avctx->sws_ctx = sws_getContext(pcodec_ctx->width, pcodec_ctx->height,pcodec_ctx->pix_fmt, pcodec_ctx->width, pcodec_ctx->height, AV_PIX_FMT_NV12,SWS_BILINEAR,NULL,NULL,NULL);
	
	return 0;
}

/*当前送流仅以best video id为准*/
void* sendPkt_Thr(void * param)
{	
	AVContext *av_ctx = (AVContext *)param;
	int ret = 0;
	AVStream * stream = NULL;
	AVCodecContext* codec_ctx = NULL;
	AVPacket packet = {0};
	int finished = 0;
	int64_t dts = 0;

	
	av_packet_unref(&packet);
		
	while(!finished)
	{	
		ret = av_read_frame(av_ctx->fmt_ctx,&packet);
		if(ret< 0)
		{
			if(ret == AVERROR_EOF)
			{
				if(av_ctx->ctrl.loop)
				{
					ret = av_seek_frame(av_ctx->fmt_ctx, av_ctx->best_streamid, 0, AVSEEK_FLAG_BYTE);
					if (ret < 0) {
						fprintf(stderr,"loop seek failed\n");
						break;
					}	
					printf("read loop\n");
					continue;
				}
				else
				{
					/*flush 包*/
					av_packet_unref(&packet);
					packet.stream_index = av_ctx->best_streamid;
					finished = 1;
				}
			}
			else
			{
				fprintf(stderr,"av_read_frame failed\n");
				break;
			}
		}
		
		/*
		if(AVMEDIA_TYPE_VIDEO != pstream->codecpar->codec_type
			&& AVMEDIA_TYPE_AUDIO != pstream->codecpar->codec_type)
		{
			av_packet_unref(&packet);
			continue;
		}*/

		if(packet.stream_index != av_ctx->best_streamid)
		{
			av_packet_unref(&packet);
			continue;
		}
	
		stream = av_ctx->fmt_ctx->streams[av_ctx->best_streamid];		
		codec_ctx = av_ctx->codec_ctx[packet.stream_index];

		//帧率控制dts
		dts = packet.dts*av_q2d(stream->time_base)*1000;
		usleep(40*1000);
#if 0
		while(dtsctrl(av_ctx,dts)<0)
		{
			usleep(10*1000);
			continue;
		}
#endif		
		//file->decode 时间基转换
		av_packet_rescale_ts(&packet,stream->time_base, codec_ctx->time_base);
		

		//pkt data ref一次，源pkt可unref
		//送流解码按照dts顺序
		do
		{
			pthread_mutex_lock(&av_ctx->lock);
			ret = avcodec_send_packet(codec_ctx,&packet);
			if(ret < 0)
			{
				if(ret == AVERROR(EAGAIN))
				{
					pthread_mutex_unlock(&av_ctx->lock);
					usleep(10*1000);
					continue;
				}
				else
				{
					fprintf(stderr,"%s:%d avcodec_send_packet error code:%d\n",__FUNCTION__,__LINE__,ret);
				}
			}
			pthread_mutex_unlock(&av_ctx->lock);
		}while(ret == AVERROR(EAGAIN));
		av_packet_unref(&packet);
	}

	
	printf("sendPkt Thr exit\n");
	
	return NULL;
}
	
/*当前送流仅以best video id为准*/
void* frameProcess_Thr(void * param)
{
	int ret;
	AVContext * av_ctx = (AVContext *)param;
	AVCodecContext ** codec_ctx = av_ctx->codec_ctx;
	AVCodecContext * pcodec_ctx = NULL;
	struct SwsContext * sws_ctx = av_ctx->sws_ctx;
	int finished = 0;
	
	while(!finished)
	{
		AVFrame * srcframe = av_frame_alloc();

		/*接收解码后数据*/
		pthread_mutex_lock(&av_ctx->lock);
		pcodec_ctx = codec_ctx[av_ctx->best_streamid];
		ret = avcodec_receive_frame(pcodec_ctx,srcframe);
		/*接收以pts顺序*/
		if(ret == AVERROR_EOF)
		{
			printf("decode flush\n");
			avcodec_flush_buffers(pcodec_ctx);
			av_frame_free(&srcframe);
			finished = 1;
		}
		else if(ret == AVERROR(EAGAIN))
		{
			pthread_mutex_unlock(&av_ctx->lock);
			usleep(10*1000);
			continue;
		}

		pthread_mutex_unlock(&av_ctx->lock);

		/*对解码后数据进行sws后处理*/		
		AVFrame * dstframe = av_frame_alloc();
		uint8_t *data = NULL;
		int size = 0;	
		while(pool_getentry(av_ctx,(void**)&data,&size) != 0)
		{
			printf("pool get node error\n");
			usleep(50*1000);
		}

		av_image_fill_arrays(dstframe->data, dstframe->linesize, data, AV_PIX_FMT_NV12, srcframe->width,srcframe->height,1);			
		AVBufferRef * buf = NULL;	
		buf = av_buffer_create(data,size,aml_free_buffer, (void*)av_ctx,0);//opaque传递
		dstframe->buf[0] = buf;
		
		ret = sws_scale(sws_ctx,(const uint8_t *const*)srcframe->data,srcframe->linesize,0,srcframe->height,dstframe->data,dstframe->linesize);
		if(ret < 0)
		{
			fprintf(stderr,"%s:%d sws_scale error\n",__FUNCTION__,__LINE__);
		}

		//暂时填值
		dstframe->width = srcframe->width;
		dstframe->height = srcframe->height;		
		dstframe->format = AV_PIX_FMT_NV12;

		pthread_mutex_lock(&av_ctx->frmlist.lock);
		framenode * node = &av_ctx->frmlist.head;
		while(node->next)
		{
			node = node->next;
		}	
		node->next = calloc(1,sizeof(framenode));
		node->next->frame = dstframe;
		av_ctx->frmlist.num++;
		pthread_mutex_unlock(&av_ctx->frmlist.lock);

		av_frame_free(&srcframe);

	}

	return NULL;	
}

static int update_video_position(AVContext *avctx, int chn) 
{
    GLfloat fx1, fx2, fy1, fy2;
	
	int left = 0;
	int top = 0;
	int width = 1920;
	int height = 1080;
	
    if ( left == 0 
		&& top == 0 
		&& width == 0 
		&& height == 0) {
        fx1 = -1.0f, fx2 = 1.0f, fy1 = 1.0f, fy2 = -1.0f;
    } else {
        fx1 = 2.0f * left / SCREEN_WIDTH - 1.0f;
        fx2 = fx1 + 2.0f * width / SCREEN_WIDTH;
        fy1 = 1.0f - 2.0f * top / SCREEN_HEIGHT;
        fy2 = fy1 - 2.0f * height / SCREEN_HEIGHT;
    }
	
    GLfloat *vtx = avctx->drm_ctx.voObj[chn].vVertices;
    *vtx++ = 0.0f, *vtx++ = 0.0f;
    *vtx++ = 0.0f, *vtx++ = 1.0f;
    *vtx++ = 1.0f, *vtx++ = 1.0f;
    *vtx++ = 1.0f, *vtx++ = 0.0f;
    *vtx++ = fx1, *vtx++ = fy1, *vtx++ = 0.0f;
    *vtx++ = fx1, *vtx++ = fy2, *vtx++ = 0.0f;
    *vtx++ = fx2, *vtx++ = fy2, *vtx++ = 0.0f;
    *vtx++ = fx2, *vtx++ = fy1, *vtx++ = 0.0f;
	
    return 0;
}

//单层纹理更新——视频通道
static int update_video_texture(AVContext *avctx, AVFrame *frame,int chn)
{
	/*撕裂现象1：为了保证显示时纹理的有效性，在更新时才释放上一次内容，否则撕裂闪屏现象*/
	if(avctx->drm_ctx.voObj[chn].egl_image)
	{
		eglDestroyImageKHR(avctx->drm_ctx.display, avctx->drm_ctx.voObj[chn].egl_image);
		avctx->drm_ctx.voObj[chn].egl_image = NULL;
	}
	
	if(avctx->drm_ctx.voObj[chn].preframe)
	{
		/*暂时黑，渲染四通道*/
		if(chn == DISPLAY_CHN-1)
		{
			av_frame_free(&avctx->drm_ctx.voObj[chn].preframe);	
		}
		avctx->drm_ctx.voObj[chn].preframe = NULL;
	}
	
    int off;
	int dma_fd = (int)frame->opaque;

    if (!avctx->drm_ctx.voObj[chn].idTexture)
        glGenTextures(1, &avctx->drm_ctx.voObj[chn].idTexture); //创建纹理对象

	off = frame->linesize[0]*frame->height;

    // clang-format off
    EGLint attribs[] = {
        EGL_WIDTH, frame->width,
        EGL_HEIGHT, frame->height,
        EGL_LINUX_DRM_FOURCC_EXT, DRM_FORMAT_NV12,
        EGL_YUV_COLOR_SPACE_HINT_EXT, EGL_ITU_REC2020_EXT,
        EGL_SAMPLE_RANGE_HINT_EXT, EGL_YUV_NARROW_RANGE_EXT,
        EGL_DMA_BUF_PLANE0_FD_EXT, dma_fd,
        EGL_DMA_BUF_PLANE0_OFFSET_EXT, 0,
        EGL_DMA_BUF_PLANE0_PITCH_EXT, frame->linesize[0],
        EGL_DMA_BUF_PLANE1_FD_EXT, dma_fd,
        EGL_DMA_BUF_PLANE1_OFFSET_EXT, off,
        EGL_DMA_BUF_PLANE1_PITCH_EXT, frame->linesize[0],
        EGL_NONE
    };
		
#if 0
		FILE *fp = fopen("./texture.yuv","w+");
		fwrite(frame->data[0],1,frame->linesize[0]*frame->height,fp);
		fwrite(frame->data[1],1,frame->linesize[0]*frame->height/2,fp);
		fclose(fp);
		printf("update_video_texture handle[w%d h%d dmafd:%d fmt:%d frame:%lx]\n",frame->width,frame->height,dma_fd,frame->format,frame);
#endif	
   printf("update_video_texture chn:%d handle[w%d h%d dmafd:%d fmt:%d frame:%lx]\n"
   						,chn,frame->width,frame->height,dma_fd,frame->format,frame);
   // if (aml_ipc_pixfmt_nplane(frame->format.pixfmt) == 1)
   //    attribs[16] = EGL_NONE;
	
    // clang-format on
    avctx->drm_ctx.voObj[chn].egl_image = eglCreateImageKHR(avctx->drm_ctx.display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, attribs);
    if (avctx->drm_ctx.voObj[chn].egl_image == EGL_NO_IMAGE_KHR) 
	{
        printf("fail to create KHR image 0x%x\n", eglGetError());
    }
	
	//GL_TEXTURE_EXTERNAL_OES只用于此情景的yuv格式
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, avctx->drm_ctx.voObj[chn].idTexture);  //OpenGL ES绑定纹理对象
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  //设置纹理过滤器缩下使用邻近算法
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //设置纹理过滤器放大使用邻近算法
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//设置纹理S轴坐标类型
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//设置纹理T轴坐标类型

	//根据指定参数生成一个2D纹理,相当于glTexImage2D（）
    egl_funcs.glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, avctx->drm_ctx.voObj[chn].egl_image);
    GLint iret;
    glGetTexParameteriv(GL_TEXTURE_EXTERNAL_OES, GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES, &iret);	

	avctx->drm_ctx.voObj[chn].preframe = frame;

    return 0;
}

static int sync_video_texture(AVContext *avctx, AVFrame *frame ,int chn)
{
	//pthread_mutex_lock(&avctx->drm_ctx.lock); 
	/*异步处理*/
	do {																						   									 
		struct thread_function func = {(typeof(func.pfn))update_video_texture, avctx, frame, chn};							 
		int len = write(avctx->drm_ctx.pipefd[1], &func, sizeof(func));									 
		if (len != sizeof(func))
		{															   
			printf("write to pipe fail %d != %lu, %d %s", len, sizeof(func), errno,strerror(errno));														   
			goto exit;															  
		}																					   																			   
	} while (0);
		
	//pthread_cond_wait(&avctx->drm_ctx.cond,&avctx->drm_ctx.lock);	

exit:	
	//pthread_mutex_unlock(&avctx->drm_ctx.lock);	
	//释放帧
	//av_frame_free(&frame);	
	
	return 0;

}

static void setup_connector(AVContext *avctx, const drmModeRes * res)
{
	drmModeConnectorPtr connector = NULL;
	for (int i = 0; i < res->count_connectors && avctx->drm_ctx.connector_id == 0; i++) {
		connector = drmModeGetConnector(avctx->drm_ctx.fd, res->connectors[i]);
		if (connector) {
			if (connector->connector_type == DRM_MODE_CONNECTOR_HDMIA) {
				printf("Find HDMIA out-put %d count_modes:%d", connector->connector_id,connector->count_modes);
				for (int j = 0; j < connector->count_modes; j++) {
					drmModeModeInfo *info = &connector->modes[j];
					if (info->hdisplay == SCREEN_WIDTH && info->vdisplay == SCREEN_HEIGHT  && info->vrefresh == 60) {
						printf("Use mode: [%s] %dx%d@%d", info->name, info->hdisplay,info->vdisplay, info->vrefresh);
						avctx->drm_ctx.mode = *info;
						avctx->drm_ctx.connector_id = connector->connector_id; 
						avctx->drm_ctx.connector = connector;
						break;
					}
				}
			}
		}
	}

	return;
}
static void setup_crtc(AVContext *avctx, const drmModeRes * res)
{
	/*already bind --find encoder*/
	drmModeEncoderPtr encoder = NULL;
	drmModeConnectorPtr connector = NULL;

	connector = avctx->drm_ctx.connector;
	if(connector)
	{
		encoder = drmModeGetEncoder(avctx->drm_ctx.fd,connector->encoder_id);		
		avctx->drm_ctx.connector = NULL;
		
		if(encoder)
		{
			avctx->drm_ctx.crtc_id = encoder->crtc_id;
			avctx->drm_ctx.encoder_id = encoder->encoder_id;
			avctx->drm_ctx.crtc = drmModeGetCrtc(avctx->drm_ctx.fd, avctx->drm_ctx.crtc_id);
			
			drmModeFreeConnector(connector);
			drmModeFreeEncoder(encoder);
			
			return;
		}	
	}

	/*first use*/
	for(int i = 0;i < connector->count_encoders;i++)
	{
		encoder = drmModeGetEncoder(avctx->drm_ctx.fd,connector->encoders[i]);
		if(!encoder)
		{
			printf("cannot retrive encoder %d",i);
			continue;
		}

		for(int j = 0;j < res->count_crtcs;++j)
		{
			if(!(encoder->possible_crtcs & (1<<j)))
			{
				continue;
			}

			avctx->drm_ctx.crtc_id = res->crtcs[j];
			avctx->drm_ctx.encoder_id = encoder->encoder_id;
			avctx->drm_ctx.crtc = drmModeGetCrtc(avctx->drm_ctx.fd, avctx->drm_ctx.crtc_id);
			
			break;
		}
	}

	return;
}


int opendisplay(AVContext *avctx) 
{		
	 //avctx->drm_ctx.fd = drmOpen(avctx->drm_ctx.disdev, NULL);//aml"meson"
	 avctx->drm_ctx.fd = open("/dev/dri/card0", O_RDWR|O_CLOEXEC);
	 if(avctx->drm_ctx.fd < 0)
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
	 
	 drmModeRes *res = drmModeGetResources(avctx->drm_ctx.fd);
	 if(res == NULL || res->count_connectors < 1 || res->count_crtcs < 1)
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
	 
	 setup_connector(avctx,res);
	 setup_crtc(avctx,res);	 

	 drmModeFreeResources(res);
	
	 if(avctx->drm_ctx.connector_id == 0)
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
	 
	 //GBM+EGL做opengl显示绘制 	
	 if(!(avctx->drm_ctx.gbm = gbm_create_device(avctx->drm_ctx.fd)))
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
	 avctx->drm_ctx.gbm_surface = gbm_surface_create(avctx->drm_ctx.gbm, SCREEN_WIDTH, SCREEN_HEIGHT, DRM_FORMAT_ARGB8888, GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
	 if(!avctx->drm_ctx.gbm_surface)
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 } 

	//动态符号初始化加载——eglGetProcAddress
	 egl_funcs.eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
	 egl_funcs.glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
	 egl_funcs.eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
	 egl_funcs.eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
	  
	if(!(avctx->drm_ctx.display = egl_funcs.eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_KHR, avctx->drm_ctx.gbm, NULL)))
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
			 
	 EGLint major, minor;
	 if(!eglInitialize(avctx->drm_ctx.display, &major, &minor))
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }
	 
	 if(!eglBindAPI(EGL_OPENGL_ES_API))
	 {
		 fprintf(stderr,"%s:%d error\n",__FUNCTION__,__LINE__);  
		 return -1;
	 }	 
	 // clang-format off
	 EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
								EGL_RED_SIZE, 8,
								EGL_GREEN_SIZE, 8,
								EGL_BLUE_SIZE, 8,
								EGL_ALPHA_SIZE, 8,
								EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
								//EGL_SAMPLE_BUFFERS,1,
								//EGL_SAMPLES,4,
								EGL_NONE};
	 // clang-format on
	 EGLint count = 0;
	 eglGetConfigs(avctx->drm_ctx.display, NULL, 0, &count);
	 EGLConfig configs[count];
	 EGLint num_conf = 0;
	 eglChooseConfig(avctx->drm_ctx.display, config_attribs, configs, count, &num_conf);
	 for (int i = 0; i < num_conf; ++i) {
		 EGLint id;
		 if (!eglGetConfigAttrib(avctx->drm_ctx.display, configs[i], EGL_NATIVE_VISUAL_ID, &id))
			 continue;
		 if (id == DRM_FORMAT_ARGB8888 || id == DRM_FORMAT_ABGR8888 || id == DRM_FORMAT_RGBA8888 ||
			 id == DRM_FORMAT_BGRA8888) {
			 avctx->drm_ctx.config = configs[i];
			 break;
		 }
	 }
	 
	 printf("EGL API:%d.%d version:%s vendor:%s\nclient EXTENSIONS:%s\ndisplay EXTENSIONS:%s\n",
			  major, minor, eglQueryString(avctx->drm_ctx.display, EGL_VERSION),
			  eglQueryString(avctx->drm_ctx.display, EGL_VENDOR), eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS),
			  eglQueryString(avctx->drm_ctx.display, EGL_EXTENSIONS));

	  printf("restore CRTC id:%d fb:%d conn:%d %dx%d@%d\n", avctx->drm_ctx.crtc_id, avctx->drm_ctx.crtc->buffer_id,
			   avctx->drm_ctx.connector_id, avctx->drm_ctx.mode.hdisplay, avctx->drm_ctx.mode.vdisplay,
			   avctx->drm_ctx.mode.vrefresh);

	//无名pipe默认堵塞	pipe2？		  
	if (pipe2(avctx->drm_ctx.pipefd,O_CLOEXEC | O_DIRECT) == -1) // 
	{
	  printf("fail to create pipe %d %s", errno, strerror(errno));
	}

	for(int i=0;i<MAX_DISPLAY_CHN;i++)
	{
		avctx->drm_ctx.voObj[i].position.left = (i%SCREEN_NSPLIT)*(SCREEN_WIDTH/SCREEN_NSPLIT);
		avctx->drm_ctx.voObj[i].position.top = (i/SCREEN_NSPLIT)*(SCREEN_HEIGHT/SCREEN_NSPLIT);
		avctx->drm_ctx.voObj[i].position.width = SCREEN_WIDTH/SCREEN_NSPLIT;
		avctx->drm_ctx.voObj[i].position.height = SCREEN_HEIGHT/SCREEN_NSPLIT;
	
		//更新显示坐标
		update_video_position(avctx,i);
	}
	
	return 0;
 }
void * update_texture_Thr(void *param)
{
	AVContext * av_ctx = (AVContext *)param;

	while(1)
	{
		pthread_mutex_lock(&av_ctx->frmlist.lock);
		framenode * node = av_ctx->frmlist.head.next;
		if(!node)
		{
			pthread_mutex_unlock(&av_ctx->frmlist.lock);
			usleep(10*1000);
			continue;
		}	
		
		av_ctx->frmlist.head.next = node->next;
		pthread_mutex_unlock(&av_ctx->frmlist.lock);
		
		AVFrame * framedata = node->frame;
		free(node);

		AVDmaPoolNode* dmanode = pool_quereyentry(av_ctx,framedata->data[0]);


		framedata->opaque = (void*)dmanode->dmabuf->dma_fd;

		for(int i=0;i<DISPLAY_CHN;i++)
		{
			//更新纹理
			sync_video_texture(av_ctx,framedata, i);
		}

	}
	
}


static GLuint gles_load_shader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint ret;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
    if (!ret) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &ret);
        if (ret > 1) {
            char log[ret];
            glGetShaderInfoLog(shader, ret, NULL, log);
            printf("glCompileShader fail %s", log);
        }
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

static GLuint gles_load_program(const char *vert_shader, const char *frag_shader) {
    GLuint vertexShader = gles_load_shader(GL_VERTEX_SHADER, vert_shader);
    GLuint fragmentShader = gles_load_shader(GL_FRAGMENT_SHADER, frag_shader);
    GLuint programObject = glCreateProgram();

	printf("shader program:%d %d %d\n",vertexShader,fragmentShader,programObject);
    if (!vertexShader || !fragmentShader || !programObject)
        goto done;
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);
    GLint ret;
    glGetProgramiv(programObject, GL_LINK_STATUS, &ret);
    if (!ret) {
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &ret);
        if (ret > 1) {
            char log[ret];
            glGetProgramInfoLog(programObject, ret, NULL, log);
            printf("glLinkProgram fail %s", log);
        }
        glDeleteProgram(programObject);
        programObject = 0;
    }
done:
    if (vertexShader)
        glDeleteShader(vertexShader);
    if (fragmentShader)
        glDeleteShader(fragmentShader);
    return programObject;
}

static void page_flip_handler(int fd, unsigned int frame, unsigned int sec, unsigned int usec,
                              void *data) {
    int *waiting_for_flip = (int *)data;
    *waiting_for_flip = 0;
}
							  

void *display_render_Thr(void *param) 
{
	AVContext * av_ctx = (AVContext *)param;
	av_ctx->drm_ctx.tid =  pthread_self();
	int ret =0;
	int waiting_for_flip = 0;
	uint32_t handle = -1;
	int pitch = 0;
	uint32_t fb = 0;
	struct gbm_bo *bo = NULL;
	uint32_t width,height,pixfmt;
	int iniflag = 0;

	const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
	//context opgl状态机，gl指令执行环境
	av_ctx->drm_ctx.context = eglCreateContext( av_ctx->drm_ctx.display,av_ctx->drm_ctx.config, EGL_NO_CONTEXT, context_attribs);

	//将suface与bufferQueue关联
	av_ctx->drm_ctx.surface = eglCreateWindowSurface( av_ctx->drm_ctx.display,  av_ctx->drm_ctx.config, (EGLNativeWindowType) av_ctx->drm_ctx.gbm_surface, NULL);
	if(av_ctx->drm_ctx.surface == EGL_NO_SURFACE)
	{
		fprintf(stderr,"%s:%d sws_scale error\n",__FUNCTION__,__LINE__);
		return -1;
	}
	
	eglMakeCurrent(av_ctx->drm_ctx.display, av_ctx->drm_ctx.surface, av_ctx->drm_ctx.surface, av_ctx->drm_ctx.context);

	 /*gl指令程序：编译加载shader程序：先eglMakeCurrent*/
	 const static GLchar vert_shader[] = "attribute vec4 pos;\n"
										 "attribute vec2 vTexCoord;\n"
										 "varying vec2 TexCoord;\n"
										 "void main() {\n"
										 "	gl_Position = pos;\n"
										 "	TexCoord = vec2(vTexCoord);\n"
										 "}\n";
	 const static GLchar fram_shader[] = "#extension GL_OES_EGL_image_external : enable\n"
										 "precision mediump float;\n"
										 "uniform samplerExternalOES uTex;\n"
										 "uniform float alpha;\n"
										 "varying vec2 TexCoord;\n"
										 "void main() {\n"
										 "	 vec4 col = texture2D(uTex, TexCoord);\n"
										 "	 gl_FragColor = vec4(col.rgb, col.a * alpha);\n"
										 "}\n";
	
	GLuint program = gles_load_program(vert_shader, fram_shader); //创建GPU绘制的可执行程序
	
	printf("egl load program return code:%x\n",eglGetError());	
	printf("gl return code:%x\n",glGetError());  
	
	if(!program)
		 return NULL;
	 av_ctx->drm_ctx.locPos = glGetAttribLocation(program, "pos");
	 av_ctx->drm_ctx.locCord = glGetAttribLocation(program, "vTexCoord");
	 av_ctx->drm_ctx.locSampler = glGetUniformLocation(program, "uTex");
	 av_ctx->drm_ctx.locAlpha = glGetUniformLocation(program, "alpha");
	 glUseProgram(program);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
    drmEventContext evctx = {.version = 2, .page_flip_handler = page_flip_handler};
    struct pollfd pfd[2] = {{.events = POLLIN, .fd = av_ctx->drm_ctx.fd}, {.events = POLLIN, .fd = av_ctx->drm_ctx.pipefd[0]}};
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    int64_t ns_start = ts.tv_sec * 1000000000LL + ts.tv_nsec;
    int num_frames = 0;
    while (1) 
	{
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);

		for(int i=0;i<DISPLAY_CHN;i++)
		{
			/*2D纹理渲染bo*/
	        if (av_ctx->drm_ctx.voObj[i].idTexture != 0)
	        {
				//1、顶点着色器
				//顶点坐标更新
				GLfloat *vtx = av_ctx->drm_ctx.voObj[i].vVertices;
				GLushort indices[] = {0, 1, 2, 0, 2, 3};
				glVertexAttribPointer(av_ctx->drm_ctx.locCord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), vtx);    //设置物体坐标
				glEnableVertexAttribArray(av_ctx->drm_ctx.locCord);
				glVertexAttribPointer(av_ctx->drm_ctx.locPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), &vtx[8]); //设置纹理坐标
				glEnableVertexAttribArray(av_ctx->drm_ctx.locPos);				
				
				//2、片元着色器			
				//idTexture bind ，表示当前处理GL_TEXTURE0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_EXTERNAL_OES,av_ctx->drm_ctx.voObj[i].idTexture);

				glUniform1f(av_ctx->drm_ctx.locAlpha, 255 / 255.0f);
				glUniform1i(av_ctx->drm_ctx.locSampler, 0);//0与GL_TEXTURE0对应，表示第0层纹理
				//GL_TRIANGLES绘制三角形,2个三角形需要6个顶点
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
				//刷新gl指令至GPU处理 
				glFinish();
	        }
		}


		//刷新gl指令至GPU处理
        eglSwapBuffers(av_ctx->drm_ctx.display, av_ctx->drm_ctx.surface);
		//锁定前端缓冲
        bo = gbm_surface_lock_front_buffer(av_ctx->drm_ctx.gbm_surface);	
		width = gbm_bo_get_width(bo);
		height = gbm_bo_get_height(bo);
		handle = gbm_bo_get_handle(bo).u32;
		pitch = gbm_bo_get_stride(bo);
		pixfmt = gbm_bo_get_format(bo);

		//drmModeAddFB(av_ctx->drm_ctx.fd, width, height, 32, 32, pitch, handle, &fb);	
		drmModeAddFB2(av_ctx->drm_ctx.fd, width, height, pixfmt,(uint32_t[4]){handle, 0, 0, 0}, (uint32_t[4]){pitch, 0, 0, 0},
			(uint32_t[4]){0, 0, 0, 0}, &fb, 0);
		

		if(iniflag == 0)
		{
			//初始化整个显示链路,并显示出fb的内容
			drmModeSetCrtc(av_ctx->drm_ctx.fd, av_ctx->drm_ctx.crtc_id, fb, 0, 0, &av_ctx->drm_ctx.connector_id, 1, &av_ctx->drm_ctx.mode);
		
			printf("drmModeSetCrtc crtc:%d fb:%d conn:%d %dx%d@%d\n"
				, av_ctx->drm_ctx.crtc_id, fb, av_ctx->drm_ctx.connector_id, av_ctx->drm_ctx.mode.hdisplay
				, av_ctx->drm_ctx.mode.vdisplay, av_ctx->drm_ctx.mode.vrefresh);
			iniflag = 1;
		}
        waiting_for_flip = 1;

        ret = drmModePageFlip(av_ctx->drm_ctx.fd, av_ctx->drm_ctx.crtc_id, fb, DRM_MODE_PAGE_FLIP_EVENT, &waiting_for_flip);
        if (ret) {
            printf("drmModePageFlip fail %d %s\n", errno, strerror(errno));
            waiting_for_flip = 2;
        }
		
		//ret = drmModeSetPlane(av_ctx->drm_ctx.fd,26,av_ctx->drm_ctx.crtc_id, fb, 0,0,0,1920,1080,0,0,1920<<16,1080<<16);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        int64_t ns_timeout = ts.tv_sec * 1000000000LL + ts.tv_nsec + 100000000LL;

        while(waiting_for_flip) {
			/*监视文件描述符*/
            ret = poll(pfd, sizeof(pfd) / sizeof(pfd[0]), 33);
            if (ret < 0) {
                if (errno == EINTR)
                    continue;
                break;
            }
			
			if (pfd[1].revents & POLLIN) {
                struct thread_function func;
                ret = read(av_ctx->drm_ctx.pipefd[0], &func, sizeof(func));
                if (ret == sizeof(func)) {
                    func.pfn(func.p1, func.p2, func.p3);
                }				
            }

            if (pfd[0].revents & POLLIN) {
                drmHandleEvent(av_ctx->drm_ctx.fd, &evctx);
				
				printf("bo info  w:%d stride:%d h:%d fmt:%s handle:%d fb:%d\n"
					, width, pitch, height,pixfmt==DRM_FORMAT_ARGB8888?"ARGB8888":"error"
					,gbm_bo_get_handle(bo).u32,fb);
            }
			
            if (waiting_for_flip == 2) {
                clock_gettime(CLOCK_MONOTONIC, &ts);
                if (ts.tv_sec * 1000000000LL + ts.tv_nsec > ns_timeout)
                    break;
            }
        } 

		//释放上一次内容；当前显示中的内容需保证fb及bo资源有效性，不可提前释放，否则drmModePageFlip报错；
	    if (av_ctx->drm_ctx.prebo) {
	        drmModeRmFB(av_ctx->drm_ctx.fd,av_ctx->drm_ctx.prefb);
	        gbm_surface_release_buffer(av_ctx->drm_ctx.gbm_surface, av_ctx->drm_ctx.prebo);
	    }

		av_ctx->drm_ctx.prebo = bo;
		av_ctx->drm_ctx.prefb = fb;
		
	    ++num_frames;
	    clock_gettime(CLOCK_MONOTONIC, &ts);
	    int64_t ns_now = ts.tv_sec * 1000000000LL + ts.tv_nsec;
	    int diff = ns_now - ns_start;
	    if (diff >= 1000000000) {
	        printf("vo fps %d\n", num_frames);
	        ns_start = ns_now;
	        num_frames = 0;
	    }
    }

    printf("restore CRTC id:%d fb:%d conn:%d %dx%d@%d", av_ctx->drm_ctx.crtc_id, av_ctx->drm_ctx.crtc->buffer_id,
             av_ctx->drm_ctx.connector_id, av_ctx->drm_ctx.mode.hdisplay, av_ctx->drm_ctx.mode.vdisplay,
             av_ctx->drm_ctx.mode.vrefresh);
	//crtc资源释放
    drmModeSetCrtc(av_ctx->drm_ctx.fd, av_ctx->drm_ctx.crtc_id, av_ctx->drm_ctx.crtc->buffer_id, av_ctx->drm_ctx.crtc->x, av_ctx->drm_ctx.crtc->y,
                   &av_ctx->drm_ctx.connector_id, 1, &av_ctx->drm_ctx.mode);
    drmModeFreeCrtc(av_ctx->drm_ctx.crtc);

	//opengl资源释放
    glDeleteProgram(program);
    eglMakeCurrent(av_ctx->drm_ctx.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(av_ctx->drm_ctx.display, av_ctx->drm_ctx.surface); 
	av_ctx->drm_ctx.surface = NULL;
    eglDestroyContext(av_ctx->drm_ctx.display, av_ctx->drm_ctx.context); 
	av_ctx->drm_ctx.context = NULL;

	//释放bo用于渲染
	if (av_ctx->drm_ctx.prebo) {
		drmModeRmFB(av_ctx->drm_ctx.fd, av_ctx->drm_ctx.prefb);
		gbm_surface_release_buffer(av_ctx->drm_ctx.gbm_surface, av_ctx->drm_ctx.prebo);
		av_ctx->drm_ctx.prebo = NULL;
	}

	for(int i = 0;i< DISPLAY_CHN;i++)
	{
		if (av_ctx->drm_ctx.voObj[i].egl_image) {
			eglDestroyImageKHR(av_ctx->drm_ctx.display, av_ctx->drm_ctx.voObj[i].egl_image);
			av_ctx->drm_ctx.voObj[i].egl_image = NULL;
		}
		
		if (av_ctx->drm_ctx.voObj[i].idTexture) {
			glDeleteTextures(1, &av_ctx->drm_ctx.voObj[i].idTexture);
			av_ctx->drm_ctx.voObj[i].idTexture = 0;
		}
	}
	
    return NULL;
}

AVContext av_ctx;
//屏幕 drm -fd -gbm device -egl display -gbm surface -egl surface -egl context  -两张fb-bo
//视频显示通道对应不同的texture和eglimage
int main(int argc,char **argv)
{
	int ret;
	pthread_t tid;

	//if(argc != 3)
	{
		//av_log(NULL,AV_LOG_ERROR,"param lack\n");
		//return -1;
	}
	char *filename = argc > 1?argv[1]:"1080P.h264";
	av_ctx.drm_ctx.disdev = argc > 2?argv[2]:"meson";
	
	ret = openfile(filename,&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"openfile fail\n");
		return -1;
	}
	
	ret = opendecoder(&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"opendecoder fail\n");
		return -1;
	}

	ret = opensws(&av_ctx,av_ctx.best_streamid);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"opensws fail\n");
		return -1;
	}

	ret = opendisplay(&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"opendisplay fail\n");
		return -1;
	}

	Lt8612_Config(0, MIPI_MSG_1080P);

	av_ctx.ctrl.loop = 1;
    pthread_mutex_init(&av_ctx.frmlist.lock, NULL);
	pthread_mutex_init(&av_ctx.lock,NULL);
	pthread_mutex_init(&av_ctx.drm_ctx.lock,NULL);
	pthread_cond_init(&av_ctx.drm_ctx.cond,NULL);
	pool_init(&av_ctx);
	aml_sdk_init();

	ret = pthread_create(&tid,NULL,sendPkt_Thr,(void *)&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"sendPkt fail\n");
		return -1;
	}
	
	ret = pthread_create(&tid,NULL,frameProcess_Thr,(void *)&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"frameProcess fail\n");
		return -1;
	}


	ret = pthread_create(&tid,NULL,update_texture_Thr,(void *)&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"update_texture_Thr fail\n");
		return -1;
	}

	ret = pthread_create(&tid,NULL,display_render_Thr,(void *)&av_ctx);
	if(ret != 0)
	{
		av_log(NULL,AV_LOG_ERROR,"display_render_Thr fail\n");
		return -1;
	}


	while(1)
	{
		sleep(1);
	}

	return 0;
}
