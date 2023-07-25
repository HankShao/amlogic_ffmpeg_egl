
#ifndef __UNI_I2C_IOCTL_H__
#define __UNI_I2C_IOCTL_H__

/******************************************************************************
  文 件 名   : uni_i2c_ioctl.h
  版 本 号   : 初稿
  作    者   : Pretstar
  生成日期   : 2019年6月6日
  最近修改   :
  功能描述   : i2c 驱动和库交互的头文件,用户态各内核态交互的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2019年6月6日
    作    者   : Pretstar
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "i2c_resource.h"
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
 #define UNI_I2C_DEV_NAME	 "uni_i2c"
 #define UNI_I2C_DEV_FULL_NAME	"/dev/"UNI_I2C_DEV_NAME


/** 驱动内部使用，句柄数组, 指向I2C_Dev */
#define MAX_I2C_BUS_COUNT 16

#define CHANNEL_I2C_USED		1
#define CHANNEL_I2C_NOTUSED		0

/** 
 * i2c初始化请求结构体
 * 1. 在内核态:
        ① UNI_I2cInitReq_t中填写I2cRes和ProcotolType
		    ProcotolType如果不等于I2C_PROCOTOL_MCU_2 则发送STOP信号
		    ProcotolType也可以直接等于0，这样默认动作是发送STOP信号
        ② 调用UNI_I2cInit()
        ③ UNI_I2cInitReq_t中的BusHandle返回I2C句柄
 * 2. 在用户态:
        ① UNI_I2cInitReq_t中填写I2cRes和ProcotolType
           保持ProcotolType == 0(用户态暂时不支持初始化带ProcotolType)
        ② 使用ioctl UNI_I2C_INIT 到内核态
        ③ ioctl返回后UNI_I2cInitReq_t中返回BusHandle  
 * 如果成功, 则UNI_I2cInitReq_t返回申请到的BusHandle;
 * 用户态需要记录这个BusHandle,就像open打开一个节点一样
 */
typedef struct UNI_I2cInitRequest_s
{
    I2cBusHandle  BusHandle;/* 从驱动中返回i2c总线句柄 */
    I2cRes_t  I2cBusRes;    /* 传入I2C总线资源 */
     /**
      * 某些特殊的I2C时序需要根据这个值进行处理
      * 目前当该值等于I2C_PROCOTOL_TYPE_MCU_2时，初始化将不发送STOP信号
      */
    I2cProcotolType_e ProcotolType;
    uint8_t reserve[24];
}UNI_I2cInitReq_t, *UNI_I2cInitReq_p;



/** 
 * i2c读写的请求结构
 */
typedef struct UNI_I2cRwIoctl_s
{
    I2cBusHandle  BusHandle;        /* i2c总线句柄, 由UNI_I2C_INIT返回 */
    uint8_t ChipAddr;               /* 芯片地址 */
    uint8_t RESV[3];                /* 保留位, 不使用 */
    I2cRegLen_e I2cRegLen;          /* 寄存器RegOffset长度, 必须取枚举值,定义在i2c_resource.h中 */
    uint16_t RegOffset;			    /* 寄存器偏移 */
    uint16_t BufLen;                /* pBuf长度 1~65535字节 */
    uint8_t *pBuf;                  /* 数据缓冲区 */
    uint8_t Commd[10];              /* 命令码 */
    uint16_t CmdLen;                /* 命令码长度 */
    I2cProcotolType_e ProcotolType;	/* I2C协议类型 */
	
	/**
	 * I2C命令字, 当I2C资源中的 
	 * ControlType = I2C_CONTROL_TYPE_GPIO
	 * 且ProcotolType = I2C_PROCOTOL_TYPE_MCU_xx
	 * 时，此命令才会被发送，详见uni_i2c_driver相关代码
	 * 当前Cmd长度固定为1,只使用一个字节
	 * McuNoStop=1, GpioI2cReadMcu不发送停止信号,默认发送。车载奥迪项目特殊规避
	 */
	uint8_t ChannelFlag;				   /*是否使用选通芯片，1代表使用，0代表使用*/
	uint8_t ChannelChipAddr;               /*选通 芯片地址 */
	uint8_t ChannelValue;				   /*选通芯片的值*/
    uint16_t ChannelRegOffset;			   /* 选通寄存器偏移 */
	uint32_t Cmd;
	uint32_t McuNoStop;
}UNI_I2cRwIoctl_t, *UNI_I2cRwIoctl_p;



#define UNI_I2C_MAGIC_BASE	'I'

/** 
 * i2c初始化, 用户态在打开设备符述符后, 必须调用此ioctl进行初始化，
 * 在UNI_I2cInitReq_t 中填写I2cRes,然后调用该ioctl，
 * 如果成功, 则UNI_I2cInitReq_t返回申请到的BusHandle;
 * 用户态需要记录这个BusHandle,就像open打开一个节点一样
 */
#define UNI_I2C_INIT   _IOW(UNI_I2C_MAGIC_BASE, 1, UNI_I2cInitReq_t)	
		
/* I2c设备读请求 */
#define UNI_I2C_READ   _IOW(UNI_I2C_MAGIC_BASE, 2, UNI_I2cInitReq_t)

/* I2c设备写请求 */
#define UNI_I2C_WRITE  _IOW(UNI_I2C_MAGIC_BASE, 3, UNI_I2cInitReq_t)

/*I2C设备关闭请求*/
#define UNI_I2C_CLOSE  _IOW(UNI_I2C_MAGIC_BASE, 4, UNI_I2cInitReq_t)




#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __UNI_I2C_IOCTL_H__ */


