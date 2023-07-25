#ifndef __I2C_RESOURCE_H__
#define __I2C_RESOURCE_H__

/******************************************************************************
  文 件 名   : i2c_resource.h
  版 本 号   : 初稿
  作    者   : Pretstar
  生成日期   : 2019年6月6日
  最近修改   :
  功能描述   : i2c_resource.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2019年6月6日
    作    者   : Pretstar
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "gpio_resource.h"
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

typedef uint32_t I2cBusHandle;

/* I2C总线句柄描述 */
#define I2C_BUS_HANDLE_MAGIC 0x49324300  /*!< 'I' '2' 'C' '\0' */
#define I2C_BUS_HANDLE_MASK  0xFFFFFF00
#define I2C_BUS_INVALID_HANDLE (I2cBusHandle)(-1)


/** 
 * I2C寄存器偏移长度枚举,
 * 使用枚举是因为之前单字节读写没有偏移大小，固定一字节大小
 * 为了保持向前兼容，避免修改资源文件,所以定义成这样
 */
typedef enum I2cRegLen_e
{
	I2C_REGLEN_1 = 0,  /* i2c寄存器偏移长度为1(一个字节) */
	I2C_REGLEN_0 = 1,  /* i2c寄存器偏移长度为0,没有寄存器偏移地址。 如果是标准I2C控制器，不允许使用该枚举 */
	I2C_REGLEN_2 = 2,  /* i2c寄存器偏移长度为2(两个字节) */
	I2C_REGLEN_BUT,
}I2cRegLen_e;

/** 将以上定义在此的目的是为了减少头文件映射次数 */ 
 
/*I2C实现方式*/
typedef enum I2cControlType_e
{
	I2C_CONTROL_TYPE_UNKNOW = 0,
	I2C_CONTROL_TYPE_COM = 1,		/*系统自带驱动*/
	I2C_CONTROL_TYPE_GPIO = 2,	/*GPIO模拟*/
	I2C_CONTROL_TYPE_SMBUS = 3,	/*SMBUS*/
	I2C_CONTROL_TYPE_BUT,
}I2cControlType_e;

 
/*I2C 数据宽度枚举*/
typedef enum I2cDataBitWidth_e
{
	I2C_8BITWIDTH_DATA = 0,     /*默认数据宽度为8  bit width */
	I2C_16BITWIDTH_DATA = 1,   /* 数据宽度为16 bit width*/
	I2C_M__DATA_BUT,
}I2cDataBitWidth_e;

/*I2C协议类型*/
typedef enum I2cProcotolType_e
{
	I2C_PROCOTOL_TYPE_UNKNOW = 0,
	I2C_PROCOTOL_TYPE_COM = 1,		/*标准I2C协议*/    
	I2C_PROCOTOL_TYPE_BUT,
}I2cProcotolType_e;

/*结构体大小24字节*/
typedef struct GpioI2cRes_s
{
	GpioRes_t Sda;			/*Sda数据线*/
	GpioRes_t Scl;			/*Scl时钟线*/
}GpioI2cRes_t, *GpioI2cRes_p;

/*结构体大小8字节*/
typedef struct ComI2cRes_s
{
	uint32_t BusId;
	I2cDataBitWidth_e  DataBitWidth;	/* I2C 数据BIT 宽度*/
}ComI2cRes_t, *ComI2cRes_p;


/*结构体大小8字节*/
typedef struct SmbusI2cRes_s
{
	uint32_t BusId;
	int8_t Reverse[4];
}SmbusI2cRes_t, *SmbusI2cRes_p;

/*结构体大小32字节*/
typedef struct I2cRes_s
{
	I2cControlType_e ControlType;	/*I2C实现方式*/
	//I2cProcotolType_e ProcotolType;	/*I2C协议类型*/
	
	union
	{
		GpioI2cRes_t  GpioI2cRes;
		ComI2cRes_t   ComI2cRes;
        SmbusI2cRes_t SmbusI2cRes;
	};
	int8_t Reverse[4];
	
}I2cRes_t, *I2cRes_p;


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

#endif /* __I2C_RESOURCE_H__ */

