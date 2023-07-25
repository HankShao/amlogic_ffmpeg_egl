
#ifndef _LT8612_H_
#define _LT8612_H_

typedef enum
{
	MIPI_MSG_NONE       = -1,
	MIPI_MSG_1080P 		= 0,
	MIPI_MSG_1280X1024,
	MIPI_MSG_720P,
	MIPI_MSG_1024X768,
	MIPI_MSG_3840X2160P30,
}mipi_msgq_type_en;

void delay1ms(unsigned int uMs);
 
/**
 * 请先确认配置I2C可以正常通信(读取0x00和0x01的值分别为0x86和0x12)，I2C速率为100k以下，
 * 然后配置初始化部分，正常显示后，在根据需要配置如下后续的配置和检测部分。
 *
 **/
void HDMI_VGA_Mode(void);

void step(void);

void LT8612_HDrst(void);

void AC_Mode_VccInt(void);


void VideoRst(void);

/*
 * 关闭HDMI输出
 */
void Disable_HDMI_Out(void);

/*
 * 打开HDMI输出
 */
void Enable_HDMI_Out(void);

/*
 * 打开VGA输出
 */
void Enable_VGA_Out(void);

/*
 * 关闭VGA输出//4K输出时关闭VGA，只打开HDMI
 */
void Disable_VGA_Out(void);

/*
 * 关闭音频输出
 */
void Disable_Audio(void);

/*
 * 打开音频输出
 */
void Enable_Audio(void);

int Lt8612_Config(int port, unsigned int enType);

int LT8612_HDMI_MODE_STATUS(int port);

void Lt8612_read_config(void);

#endif  //_LT8612_H_

