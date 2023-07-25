#ifndef _AVCOMM_H
#define _AVCOMM_H

#include "Types.h"
#include "Memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CHIPS_PER_CARD (16)

typedef enum channel_type 
{
  TYPE_VID_IN 		= 0,          
  TYPE_VID_LOCALENC,        
  TYPE_VID_MIXENC,          
  TYPE_VID_REMOTEDEC,		
  TYPE_VID_LOCALDEC,		
  TYPE_VID_TRANSDEC,		
  TYPE_VID_ANALYSEDEC,      
  TYPE_VID_IVAANALYSE,      
  TYPE_VID_PIPENC,          
  TYPE_VID_AVEDIT,          
  TYPE_VID_OUTPUT 	= 64,     
  TYPE_AUD_IN		= 128,         
  TYPE_AUD_LOCALENC,          
  TYPE_AUD_MIXENC,			
  TYPE_AUD_REMOTEDEC,		
  TYPE_AUD_LOCALDEC,		
  TYPE_AUD_TRANSDEC,		
  TYPE_AUD_SPEAKIN,			
  TYPE_AUD_SPEAKOUT,		
  TYPE_AUD_MIX,             
  TYPE_AUD_BROADCAST,		
  TYPE_AUD_4G,              
  TYPE_AUD_OUTPUT 	= 192,    
  TYPE_INVALID 		= 0xff       
}channel_type_e;

typedef enum channel_functional_attribute
{
    FUNC_ATTR_INVALID =0,                  
    FUNC_ATTR_PLAY,                        
    FUNC_ATTR_ANALYSE,                       
    FUNC_ATTR_FISHEYE,                     
    FUNC_ATTR_VIDEO_TRANSCODING,           
    FUNC_ATTR_FACE_DETECTION,                
    FUNC_ATTR_FACE_RECOGNISE,                   
    FUNC_ATTR_VEHICLE_ANALYSE,             
    FUNC_ATTR_VIDEO_DIAGNOSIS,             
    FUNC_ATTR_VIDEO_SYNOPSIS,              
    FUNC_ATTR_COMMON_ANALYSE,                
    FUNC_ATTR_VIDEO_ATM,                   
    FUNC_ATTR_TRAFFIC_PATROL,              
    FUNC_ATTR_TRAFFIC_PRISON_ROOM,         
    FUNC_ATTR_NUMBER_STATISTICS,           
    FUNC_ATTR_WIDE_VIEW,                   
    FUNC_ATTR_TRACK,                       
    FUNC_ATTR_COURSE_RECORD,               
    FUNC_ATTR_STUDENT_SITDOWN,             
    FUNC_ATTR_SCR,                         
    FUNC_ATTR_HIGHWAY_DETECTION,               
    FUNC_ATTR_CITY_DETECTION,                
    FUNC_ATTR_LE_TRACK,                        
    FUNC_ATTR_LE_HEAD_DECTION,                
    FUNC_ATTR_NR
}functional_attribute_e;

typedef struct 
{
    int32_t i32chipId;    
    int32_t i32chnId;     
    int32_t res[4];
} functional_chipInfo_s;

typedef struct 
{
    functional_attribute_e eFunAttr;   
    functional_chipInfo_s stFuncInfo;     
    int32_t res[32];
} functional_info_s;   

typedef enum video_standard
{
   VIDEO_STANDARD_PAL = 0,  
   VIDEO_STANDARD_NTSC,     
   VIDEO_STANDARD_SECAM     
}video_standard_e;

enum capture_comp_t
{
    CAPTURE_COMP_DIVX_MPEG4,    
    CAPTURE_COMP_MS_MPEG4,      
    CAPTURE_COMP_MPEG2,         
    CAPTURE_COMP_MPEG1,         
    CAPTURE_COMP_H263,          
    CAPTURE_COMP_MJPG,          
    CAPTURE_COMP_FCC_MPEG4,     
    CAPTURE_COMP_H264,          
    CAPTURE_COMP_SVAC,          
    CAPTURE_COMP_H26L,           
    CAPTURE_COMP_TIFF,          
    CAPTURE_COMP_HK,            
    CAPTURE_COMP_H265,          
    CAPTURE_COMP_PNG,           
    CAPTURE_COMP_ARGB8888,      
    CAPTURE_COMP_RGB565,        
    CAPTURE_COMP_NR             
};

enum capture_size_t
{
    CAPTURE_SIZE_D1 = 0,    
    CAPTURE_SIZE_HD1,       
    CAPTURE_SIZE_BCIF,      
    CAPTURE_SIZE_CIF,       
    CAPTURE_SIZE_QCIF,      
    CAPTURE_SIZE_VGA,       
    CAPTURE_SIZE_QVGA,      
    CAPTURE_SIZE_SVCD,      
    CAPTURE_SIZE_QQVGA,     
    CAPTURE_SIZE_SVGA,      
    CAPTURE_SIZE_XVGA = 10,      
    CAPTURE_SIZE_WXGA,      
    CAPTURE_SIZE_SXGA,      
    CAPTURE_SIZE_WSXGA,     
    CAPTURE_SIZE_UXGA,      
    CAPTURE_SIZE_WUXGA,     
    CAPTURE_SIZE_LTF,       
    CAPTURE_SIZE_720p,      
    CAPTURE_SIZE_1080p,     
    CAPTURE_SIZE_1_3M,      
    CAPTURE_SIZE_2_5M = 20,      
    CAPTURE_SIZE_5M,        
    CAPTURE_SIZE_3M,        
    CAPTURE_SIZE_5_0M,      
    CAPTURE_SIZE_1_2M,      
    CAPTURE_SIZE_1408_1024, 
    CAPTURE_SIZE_8M,        
    CAPTURE_SIZE_2560_1920, 
    CAPTURE_SIZE_960H,      
    CAPTURE_SIZE_320_256,
    CAPTURE_SIZE_640_512 = 30,
    CAPTURE_SIZE_640_360,
    CAPTURE_SIZE_WVGA,      
    CAPTURE_SIZE_FWVGA,     
    CAPTURE_SIZE_HALF1080P, 
    CAPTURE_SIZE_960_720,	
    CAPTURE_SIZE_NHD,               
    CAPTURE_SIZE_QNHD,            
    CAPTURE_SIZE_QQNHD,         
    CAPTURE_SIZE_960_540,         
    CAPTURE_SIZE_640_352 = 40,         
    CAPTURE_SIZE_640_400,         
    CAPTURE_SIZE_1360_768,   
    CAPTURE_SIZE_1440_900,   
    CAPTURE_SIZE_1600_900,   
    CAPTURE_SIZE_320_192,         
    CAPTURE_SIZE_320_176,         
    CAPTURE_SIZE_2560_1440,         
    CAPTURE_SIZE_3840_2160,         
    CAPTURE_SIZE_2592_1944,         
    CAPTURE_SIZE_1280_1440 = 50,         
    CAPTURE_SIZE_1920_2160,         
    CAPTURE_SIZE_2880_1920,			
    CAPTURE_SIZE_1296_1944,         
    CAPTURE_SIZE_1440_1920,			
    CAPTURE_SIZE_NR         
};

enum capture_brc_t
{
    CAPTURE_BRC_CBR, 
    CAPTURE_BRC_VBR, 
    CAPTURE_BRC_MBR, 
    CAPTURE_BRC_NR 
};

typedef struct video_param
{
    uint8_t Brightness;   
    uint8_t Contrast;		
    uint8_t Saturation;   
    uint8_t Hue;			
    uint8_t CustomMode;   
    uint8_t Reserved[3];
}video_param_s;

typedef enum video_aspectParam
{
    VIDEO_ASPECT_RATION_DEFAULT = 0,         
    VIDEO_ASPECT_RATION_ORIGINAL    
 
}video_aspectParam_e;

typedef struct window_Info
{
    uint32_t 		u32Channel; 		
    channel_type_e  u32ChannelType; 	
    uint32_t 		u32ZOrde; 			
    Rect     		stSourceRect; 		
    Rect     		stDestRect; 		

    video_aspectParam_e aspect; 
    uint32_t  winEnable; 		
    uint8_t   drawLineEn[4]; 	
    uint32_t  windowId;    		
    uint32_t  windowType;		
    int32_t   reserved[16];
}window_info_s;

typedef enum capture_title_scheme_type
{
    CAPTURE_TITLE_SCHEME_TYPE_INSERT=0,    
    CAPTURE_TITLE_SCHEME_TYPE_OVERLAY,     
    CAPTURE_TITLE_SCHEME_TYPE_NORMAL,      
    CAPTURE_TITLE_SCHEME_TYPE_DHAV,        
    CAPTURE_TITLE_SCHEME_TYPE_BUTT
}capture_title_scheme_type_e;

typedef struct CAPTURE_TITLE_PARAM
{
    uint32_t index;
    uint32_t enable;  
    uint16_t x;		
    uint16_t y;
    uint16_t width;		
    uint16_t height;		
    uint32_t fg_color;
    uint32_t bg_color;
    uint8_t *raster;
    uint8_t  coordinateOption;
    uint8_t  isPoliceStdOSD;
    uint8_t  isDrawBorder;
    uint32_t bufsize;
	capture_title_scheme_type_e enType;
    uint8_t reserved[468];
}CAPTURE_TITLE_PARAM;

typedef enum overlay_foramt
{
    OVERLAY_FORMAT_JPEG,
    OVERLAY_FORMAT_BMP,
    OVERLAY_FORMAT_PNG,
    OVERLAY_FORMAT_YUV422,
    OVERLAY_FORMAT_ARGB8888,
    OVERLAY_FORMAT_ARGB1555,
    OVERLAY_FORMAT_ARGB565,
    OVERLAY_FORMAT_NR,
}overlay_foramt_e;

typedef struct enc_overlay_param
{
    uint32_t index;
    uint32_t enable;
    uint32_t dataformat;
    uint16_t x;		
    uint16_t y;
    Size src;
    Size dst;
    uint32_t len;
    uint8_t *raster;
    uint32_t alpha;
    uint32_t res[3];
}enc_overlay_param_s;

typedef enum video_cover_opt 
{
    VIDEO_COVER_WINDOW_CLEAR = 0,	
    VIDEO_COVER_WINDOW_DRAW,		
    VIDEO_COVER_FULLSCREEN_CLEAR,	
    VIDEO_COVER_FULLSCREEN_DRAW		
}video_cover_opt_e;

typedef struct video_cover_param
{
    int32_t 			index;
    video_cover_opt_e	enable;
    Rect	 rect;
    uint32_t color;
}video_cover_param_s;

typedef struct AudioSource_s
{
    int32_t i32Channel;		
    int32_t i32Type;			
}AudioSource_s;

typedef enum chip_card_type
{
    ChipCardInput = 0,  
    ChipCardOutput,     
    ChipCardEncode,     
    ChipCardDecode,     
    ChipCardCascade,    
    ChipCardIntelli,    
    ChipCardAlarm,      
    ChipCardNR
} chip_card_type_e;

typedef enum chip_card_interface
{
    ChipCardCVBS,       
    ChipCardVGA,        
    ChipCardDVI,        
    ChipCardSPF,        
    ChipCardSDI,        
    ChipCardHDCVI,      
    ChipCardInterfaceNumber
} chip_card_interface_e;

typedef enum chip_card_definition
{
    ChipCardStandardDefinition, 
    ChipCardHighDefinition,     
    ChipCardDefinitionNumber    
} chip_card_definition_e;

typedef enum chip_card_status
{
    ChipCardNormal,         
    ChipCardNoResponse,     
    ChipCardNetAbort,       
    ChipCardIPConflict,     
    ChipCardUpgrading,      
    ChipCardLinkStatusError,
    ChipCardStatusNumber
} chip_card_status_e;

typedef struct chip_cascade_video_in_chn_param
{
    uint32_t sourceValue;
    int32_t reserve[3];
}chip_cascade_video_in_chn_param_s;

typedef struct avs_card_info
{
    int32_t i32Exist;                   
    int32_t i32Type;                    
    int32_t i32VideoInputChs;           
    int32_t i32ChipNums;                
    int32_t i32ChnsPerChip[MAX_CHIPS_PER_CARD]; 
    int32_t i32TransDecFlag;            
    int32_t i32LocalIntelliFlag;        
    int32_t i32AudioInputChs;           
    int32_t i32VideoOutputChs;           
    int32_t i32AudioOutputChs;          
    int32_t i32VideoEncodeChs;          
    int32_t i32AudioEncodeChs;          
    int32_t i32VideoDecodeChs;          
    int32_t i32AudioDecodeChs;          
    int32_t i32VideoAnalyseChs;         
    int32_t i32AlarmInputChs;           
    int32_t i32AlarmOutputChs;          
    int32_t i32CascadeChs;              
    int32_t i32CascadeChanelBitrate;    
    int32_t i32PcieLinkWidth;           
    int32_t i32PcieLinkSpeed;           
    int32_t i32IsSupportSetBandRate;    
    int32_t i32CapturesrcMaxRes;        
    int32_t i32Port;                    
    int8_t  i32Address[32];             
    int8_t  i32ComPorts;                
    int32_t i32ChipDecType;             
    chip_card_interface_e  enInterface; 
    chip_card_definition_e enDefinition;
    chip_card_status_e     enStatus;    
    chip_cascade_video_in_chn_param_s stCasCaptureChnInfo[32];
    int32_t reserved[32];                   				  
}avs_card_info_s;

typedef struct avs_describe
{
    int32_t i32Card;    
    int32_t i32Chip;    
    int32_t i32Tv;      
    int32_t i32Win;     
    int32_t i32Reserved[8];
}avs_describe_s;

typedef struct vdec_video_convert_info
{
    int32_t i32StreamFormat;    
    int32_t i32RawDataFlag;     
    uint8_t *puSteamBuffer;     
    int32_t i32StreamSize;      
    int32_t *pi32ImageWidth;    
    int32_t *pi32ImageHeight;   
    uint8_t *puImageBuffer;     
    int32_t i32ImageSize;       
    int32_t i32ColorFormat;     
    int32_t i32EncFormat;       
	int32_t i32StreamSrcWidth;  
    int32_t i32StreamSrcHeight;  
    int32_t i32Res[4];
}vdec_video_convert_info_s;

typedef struct video_pos_title_param
{
    int32_t erase;
    int32_t x;       
    int32_t y;
    Size  ref_size;
    int32_t width;       
    int32_t height;          
    uint32_t fg_color;
    uint32_t bg_color;
    uint8_t *raster;
    int32_t raster_size;
    int32_t raster_valid_len;
    int32_t  reserved[64];
}video_pos_title_param_s;

typedef enum json_cover_type 
{
    JSON_COVER_TYPE_NE=0,     
    JSON_COVER_TYPE_POS,      
    JSON_COVER_TYPE_INTELLI,  
} json_cover_type_e;

typedef struct avs_ch_info
{
    int32_t i32ChnNum;    
    int32_t i32IvsChnNum; 
    int32_t i32Reserved[7];
}avs_ch_info_s;

typedef enum avs_api_mode
{
    AVS_API_MODE_SYNC = 0,  
    AVS_API_MODE_ASYNC,     
}avs_api_mode_e;

#define AVS_MAX_MMAP_NUM 64

typedef struct avs_addr_map
{
    uintptr_t uintptrPhyAddr;  
    uint8_t *pu8VirAddr; 
    int32_t s32Size;   
    int32_t s32Reserved[7];   
}avs_addr_map_s;

typedef struct avs_av_mmap_info
{
    int32_t 		s32MmapNum;    					 
    avs_addr_map_s 	stAddrMapInfo[AVS_MAX_MMAP_NUM]; 
}avs_av_mmap_info_s;

int32_t AVS_Init(void);

int32_t AVS_SetVideoStd(video_standard_e eStandard);

int32_t AVS_GetCardNums(void);   

int32_t AVS_GetCardInfo(int32_t i32Card, avs_card_info_s *pstCardInfo);

int32_t AVS_Get_AvMapInfo(avs_av_mmap_info_s *pstMmapInfo);

int32_t AVS_Release_AvMapInfo(avs_av_mmap_info_s *pstMmapInfo);

int32_t DEC_ChMap(int32_t i32Channel, avs_describe_s *pstDescribe); 

int32_t AVS_DebugConsole(int32_t argc, char* argv[]);

int32_t AVS_SetMemParm(const avs_ch_info_s *pstChnInfo);   

typedef enum AVS_DEVSTATUS_TYPE
{
    AVS_DEVSTATUS_TYPE_VIDEO_DELAY = 1,    
    AVS_DEVSTATUS_TYPE_VIDEO_ABNORMAL,     
    AVS_DEVSTATUS_TYPE_AUDIO_LOST = 10,    
    AVS_DEVSTATUS_TYPE_AUDIO_NODATA,       
    AVS_DEVSTATUS_TYPE_AUDIO_ABNORMAL,     
    AVS_DEVSTATUS_TYPE_NR
}AVS_DEVSTATUS_TYPE_E;

typedef struct avs_devstatus_details_v_delay
{
    uint16_t u16CommonLayerDelayMs;     
    uint16_t u16ShareQueToSDKDelayMs;   
    uint16_t u16SdkDecodeDelayMs;       
    uint16_t u16SdkDisplayDelayMs;      
    uint16_t u16TotalDelayMs;           
    uint16_t u16NetCtrlBaseMs;          
    uint16_t u16DiffMs;                 
    uint16_t u16Res[5];
}avs_devstatus_details_v_delay_s;

typedef enum AVS_DEVSTATUS_VIDEO_ABNORMAL_SUBTYPE
{
    VIDEO_ABNORMAL_SUBTYPE_LOST,            
    VIDEO_ABNORMAL_SUBTYPE_INTERVAL_ERR,    
    VIDEO_ABNORMAL_SUBTYPE_STUCK,           
    VIDEO_ABNORMAL_SUBTYPE_NODATA,          
    VIDEO_ABNORMAL_SUBTYPE_DATAPARSE_ERR,   
    VIDEO_ABNORMAL_SUBTYPE_STREAM_ERR,      
    VIDEO_ABNORMAL_SUBTYPE_NR
}AVS_DEVSTATUS_VIDEO_ABNORMAL_SUBTYPE_E;

typedef enum AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE
{
    AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE_DEC_ERR,            
    AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE_DEC_NOSUPPORT_TYPE, 
    AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE_DEC_NOENOUGH_FRM,   
}AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE_E;

typedef struct avs_devstatus_video_abnormal_lost_info
{
    int32_t i32LostFrameNumPerCircle;       
    uint32_t u32Res[3];
}avs_devstatus_video_abnormal_lost_info_s;

typedef struct avs_devstatus_video_abnormal_interval_err_info
{
    uint16_t u16ActIntervalTime;         
    uint16_t u16TotalDelayMs;           
    uint16_t u16NetCtrlBaseMs;          
    uint32_t u32Res[5];
}avs_devstatus_video_abnormal_interval_err_info_s;

typedef struct avs_devstatus_video_abnormal_stuck_info
{
    uint32_t u32Res[3];
}avs_devstatus_video_abnormal_stuck_info_s;

typedef enum AVS_VIDEO_NODATA_TYPE
{
    AVS_VIDEO_NODATA_TYPE_NOTSENDDATA,
    AVS_VIDEO_NODATA_TYPE_DECODERNOTCREATE,
    AVS_VIDEO_NODATA_TYPE_OVERDECABILITY,
    AVS_VIDEO_NODATA_TYPE_OVERZOOMABILITY,
    AVS_VIDEO_NODATA_TYPE_UNSUPPORTRES,
    AVS_VIDEO_NODATA_TYPE_UNSUPPORTFMT,
    AVS_VIDEO_NODATA_TYPE_PARAMERR,
    AVS_VIDEO_NODATA_TYPE_NR
}AVS_VIDEO_NODATA_TYPE_E;

typedef struct avs_devstatus_video_abnormal_nodata_info
{
    AVS_VIDEO_NODATA_TYPE_E enNodataInfo;
    uint32_t u32Res[4];
}avs_devstatus_video_abnormal_nodata_info_s;

typedef struct avs_devstatus_video_abnormal_dataparse_err_info
{
    int32_t i32FailedTimesPerCircle;        
    uint32_t u32Res[3];
}avs_devstatus_video_abnormal_dataparse_err_info_s;

typedef struct avs_devstatus_video_abnormal_stream_err_info
{
    int32_t i32DecoderFailedTimesPerCircle; 
    uint32_t u32Res[3];
}avs_devstatus_video_abnormal_stream_err_info_s;

typedef struct avs_devstatus_details_v_abnormal
{
    AVS_DEVSTATUS_VIDEO_ABNORMAL_SUBTYPE_E enAbnormalSubType;
    union
    {
        avs_devstatus_video_abnormal_lost_info_s stLostInfo;
        avs_devstatus_video_abnormal_interval_err_info_s stIntervalErrInfo;
        avs_devstatus_video_abnormal_nodata_info_s stNodataInfo;
        avs_devstatus_video_abnormal_dataparse_err_info_s stDataParseErrInfo;
        avs_devstatus_video_abnormal_stream_err_info_s stStreamErrInfo;
    }subtypeinfo;
    uint16_t u16Res[3];
}avs_devstatus_details_v_abnormal_s;

typedef struct avs_devstatus_details_a_lost
{
    uint32_t i32LostFrameNumPerCircle;              
    uint32_t u32Res[4];
}avs_devstatus_details_a_lost_s;

typedef struct avs_devstatus_details_a_nodata
{
    uint16_t u16NoDataFlag;                         
    uint16_t u16Res[2];
}avs_devstatus_details_a_nodata_s;

typedef struct avs_devstatus_audio_dec_err
{
    uint32_t u32ErrFrameNumPerCircle;               
    uint32_t u32Res[2];
}avs_devstatus_audio_dec_err_s;

typedef struct avs_devstatus_adec_nosupport_type
{
    uint32_t u32NoSupportFlag;                      
    uint32_t u32Res[2];
}avs_devstatus_adec_nosupport_type_s;

typedef struct avs_devstatus_audio_noenough_frm
{
    uint32_t u32SrcFrm;                         
    uint32_t u32CurFrm;                         
    uint32_t u32Res[2];
}avs_devstatus_audio_noenough_frm_s;

typedef struct avs_devstatus_details_a_abnormal
{
    AVS_DEVSTATUS_AUDIO_ABNORMAL_SUBTYPE_E enAbnormalType;
    union
    {
        avs_devstatus_audio_dec_err_s stDecErr;
        avs_devstatus_adec_nosupport_type_s stNoSupport;
        avs_devstatus_audio_noenough_frm_s stNoEnoughFrm;
    };
    uint32_t u32Res[8];
}avs_devstatus_details_a_abnormal_s;

typedef struct avs_devstatus_info
{
    AVS_DEVSTATUS_TYPE_E   enDevStatus;                     
    union
    {
        avs_devstatus_details_v_delay_s stVideoDelay;       
        avs_devstatus_details_v_abnormal_s stVideoAbnormal; 
        avs_devstatus_details_a_lost_s  stAudioLost;        
        avs_devstatus_details_a_nodata_s stAudioNoData;     
        avs_devstatus_details_a_abnormal_s stAudioAbnormal; 
    }unDevStatusDetails; 
    uint32_t               u32ErrorCodeLow;                 
    uint32_t               u32ErrorCodeHigh;                
    uint32_t u32Res[8];
}avs_devstatus_info_s;

typedef struct system_time
{
    int32_t  i32Year;          
    int32_t  i32Month;         
    int32_t  i32Day;           
    int32_t  i32Wday;          
    int32_t  i32Hour;          
    int32_t  i32Minute;        
    int32_t  i32Second;        
    int32_t  i32Sdst;          
    int32_t  i32Msec;          
    int32_t  i32Rev[3];
}system_time_s;

typedef struct avs_databuff_info
{
    uintptr_t pAvBuffAddr;
    uint32_t  u32AvBuffSize;
    int32_t   i32Reserved[10];
}avs_databuff_info_s;

int32_t AVS_DevStatus_Enable(int32_t i32Enalbe, AVS_DEVSTATUS_TYPE_E enDevStatusType);

int32_t AVS_DevStatus_SetCircleTime(int32_t i32CircleTime, AVS_DEVSTATUS_TYPE_E enDevStatusType);

typedef int32_t (*AVS_DevStatus_CallBack)(int32_t i32Channel, channel_type_e eChType, avs_devstatus_info_s *pstDevStatusInfo);

int32_t AVS_RegisterDevStatusCBFunc(AVS_DevStatus_CallBack pfnCallBack);

int32_t AVS_GetDataBuffInfo(avs_databuff_info_s *pstDataBufInfo, uint32_t *puiBuffNum);

#ifdef __cplusplus
}
#endif

#endif
