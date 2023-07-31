


#define _GNU_SOURCE 			/* See feature_test_macros(7) */
#include <fcntl.h>				/* Obtain O_* constant definitions */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/mman.h>


#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <libavutil/error.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
//#include <libswscale/swscale_internal.h>

#include <drm.h>
#include <drm_fourcc.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#include <gbm.h>
//#include <gbmint.h>
#define EGL_EGLEXT_PROTOTYPES
//#define GL_GLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "aml_ipc_sdk.h"
#include <linux/fb.h>


#define FRM_LIST_NODE_NUM 10
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MAX_DISPLAY_CHN 16
#define DISPLAY_CHN 1
#define SCREEN_NSPLIT 2
#define MAX_DEC_REF_CNT 8

#define IMAGE_ALIGNMENT(size, align) ((size) + (((align) - ((size) % (align))) % (align)))
typedef struct framenode
{
	AVFrame *frame;
	struct framenode *next;
}framenode;

typedef struct framelist
{
	framenode head;
	int num;
	pthread_mutex_t lock;
}framelist;


typedef struct AVCtrl
{
	int loop;
	int64_t fisttime;  //ms
	int64_t firstdts; //ms
}AVCtrl;

typedef struct pos
{
	int left;
	int top;
	int width;
	int height;
}pos;

typedef struct Vo_Chn_Obj
{
    GLuint idTexture;
    EGLImageKHR egl_image;
	pos position;
    GLfloat vVertices[20];
	AVFrame *preframe;
	int z_order;
	struct Vo_Chn_Obj * next;
}Vo_Chn_Obj_s;

typedef struct AVDrmContext
{
	char *disdev;
	pthread_t tid; //display thread
	int fd;	  //drm fd
    uint32_t prefb; //drm fb
    int pipefd[2];

    uint32_t connector_id;
    uint32_t crtc_id;
	uint32_t encoder_id;
    drmModeCrtcPtr crtc;
	drmModeConnectorPtr connector;
    drmModeModeInfo mode;

    struct gbm_device * gbm;
    struct gbm_surface *gbm_surface;
    struct gbm_bo *prebo;

    EGLConfig config;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    GLint locPos;
    GLint locCord;
    GLint locSampler;
    GLint locAlpha;
	Vo_Chn_Obj_s voObj[MAX_DISPLAY_CHN];
	Vo_Chn_Obj_s * sorthead;
	
	pthread_mutex_t lock;
	pthread_cond_t cond;

}AVDrmContext;

struct thread_function {
    int (*pfn)(void *p1, void *p2, int p3);
    void *p1;
    void *p2;
	int p3;
};


typedef struct AVDmaPoolNode
{
	int id;
	int used;
	struct AmlIPCVideoBuffer *dmabuf; //dma id可以从此处取
	void * data;
	int    size;
}AVDmaPoolNode;

typedef struct AVDmaPool
{
	AVDmaPoolNode dma_pool_array[MAX_DEC_REF_CNT];
	int pool_num;
	pthread_mutex_t poollock;
}AVDmaPool;


typedef struct AVContext
{
	AVFormatContext * fmt_ctx;
	int 			best_streamid;
	AVCodecContext ** codec_ctx;
	struct SwsContext *    sws_ctx;
	AVDrmContext   drm_ctx;
	AVCtrl 	       ctrl;
	framelist frmlist;
	AVDmaPool pool;
	pthread_mutex_t lock;
	
}AVContext;

#define EGL_DL_FUNC_TABLE(M)                                                                       \
    M(eglGetPlatformDisplayEXT, PFNEGLGETPLATFORMDISPLAYEXTPROC)                                   \
    M(glEGLImageTargetTexture2DOES, PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)                           \
    M(eglCreateImageKHR, PFNEGLCREATEIMAGEKHRPROC)                                                 \
    M(eglDestroyImageKHR, PFNEGLDESTROYIMAGEKHRPROC)

#define DECL_EGL_FUNC_POINTER(f, t) t f;
static struct { EGL_DL_FUNC_TABLE(DECL_EGL_FUNC_POINTER) } egl_funcs;
