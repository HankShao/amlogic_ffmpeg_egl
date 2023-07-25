/******************************************************************************
  文 件 名   : gpio_resource.h
  版 本 号   : 初稿
  作    者   : Pretstar
  生成日期   : 2019年6月5日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月24日
    作    者   : Pretstar
    修改内容   : 创建文件

******************************************************************************/
   
/**  
 * @addtogroup gpio_resource  
 * @{  
 */
   
#ifndef __GPIO_RESOURCE_H__
#define __GPIO_RESOURCE_H__

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "comm/Types.h"

/** 
 * GPIO类型, 嵌入式跟X86有所区别，
 * 不能单一通过port/bit区分,
 * 因此分出type，在各自的func中实现。
 */
typedef enum GpioType_e
{
    GPIO_TYPE_EMBEDED = 0, /*!< 嵌入式片上GPIO方式   */
    GPIO_TYPE_PCH = 1,     /*!< X86南桥自带GPIO方式  */
    GPIO_TYPE_SIO = 2,     /*!< X86南桥SuperIO方式   */
    GPIO_TYPE_EXTEND = 3,  /*!< 扩展芯片方式(MAX7311)*/
    GPIO_TYPE_BUT,
}GpioType_e;

/*结构体大小12字节*/
/**  GPIO资源结构体 */
typedef struct GpioRes_s
{
	uint8_t Port;		     /*!<  PORT号 */
	uint8_t Bit;			 /*!<  BIT号  */
	uint16_t Reverse;        /*!<  仅供驱动内部使用 */
    uint32_t Index;          /*!<  当GPIO类型为扩展芯片时，该成员代表芯片索引号, 否则为0 */ 
    GpioType_e GpioType;     /*!<  gpio类型 */ 
}GpioRes_t, *GpioRes_p;

/** 比较是否为同一个GPIO引脚, 通常 用于判断总线引脚是否冲突/公用等 */
static inline int32_t GpioResEqual(const GpioRes_t *pRes1, const GpioRes_t *pRes2)
{
    return (   (pRes1->Bit == pRes2->Bit) 
            && (pRes1->Port == pRes2->Port)
            && (pRes1->Index == pRes2->Index)
            && (pRes1->GpioType == pRes2->GpioType));
}

/** 打印GPIO信息 */
#define __GpioResPrint(__print_method, pGpioRes)            \
do                                                          \
{                                                           \
    const GpioRes_t *__pRes = (pGpioRes);                   \
    const char *__Type[GPIO_TYPE_BUT] = {                   \
        [GPIO_TYPE_EMBEDED] = "soc-gpio",                   \
        [GPIO_TYPE_PCH]     = "x86-pch-gpio",               \
        [GPIO_TYPE_SIO]     = "x86-superIO",                \
        [GPIO_TYPE_EXTEND]  = "extend-gpio(7311)",          \
    };                                                      \
                                                            \
    if (   NULL == __pRes                                   \
        || __pRes->GpioType < 0                             \
        || __pRes->GpioType >= GPIO_TYPE_BUT)               \
    {                                                       \
        OSA_ERROR("gpio res invalid\n");                    \
        break;                                              \
    }                                                       \
                                                            \
    __print_method("GpioRes(port=%d, bit=%d, type=%s"       \
                   ", index=%d)\n", __pRes->Port            \
                                 , __pRes->Bit              \
                                 , __Type[__pRes->GpioType] \
                                 , __pRes->Index);          \
}while(0)

#define GpioResPrintInfo(pGpioRes)  __GpioResPrint(OSA_printf, pGpioRes)
#define GpioResPrintWarn(pGpioRes)   __GpioResPrint(OSA_WARN  , pGpioRes)
#define GpioResPrintError(pGpioRes)  __GpioResPrint(OSA_ERROR , pGpioRes)

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
