#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <lt8612.h>
#include "uni_i2c_ioctl.h"


#define I2C_DEVADDR_LT8612_PAGE1   0x78 ///LT8612 I2C设备地址page1
#define I2C_DEVADDR_LT8612_PAGE2   0x7c ///LT8612 I2C设备地址page2
#define LT8612_HDMI_MODE_ADDR	   0x72 ///HDMI mode状态寄存器地址
#define LT8612_HDMI_HSYNC_ADDR	   0x7f ///HDMI hsync状态寄存器地址
#define I2C_CHANNEL_ADDR    		0x70

typedef enum I2cWriteReadFlag_e
{
	I2C_WRITE_FLAG = 0,
	I2C_READ_FLAG  = 1,
}I2cWriteReadFlag_e;

int32_t I2cWriteReadSerial(uint8_t *Value, I2cWriteReadFlag_e flag, int32_t offset, int32_t iDevAddr, int32_t i2cNum, int32_t iBusNum)   //i2cNum:所接cpu的i2c号，iBusNum：所接总器件的分支号
{
	int fd = -1;
	int ret = -1;
	UNI_I2cInitReq_t I2cInitReq;
	UNI_I2cRwIoctl_t UNI_I2cRwByte;
	uint8_t ByteBuf[1] = { 0 };

	fd = open(UNI_I2C_DEV_FULL_NAME, O_RDWR);
	if (fd < 0)
	{
		printf("open [%s] failed\n", UNI_I2C_DEV_FULL_NAME);
		return -1;
	}

	memset(&I2cInitReq, 0, sizeof(I2cInitReq));
	I2cInitReq.I2cBusRes.ComI2cRes.BusId = i2cNum;
	I2cInitReq.I2cBusRes.ControlType = I2C_CONTROL_TYPE_COM;

	ret = ioctl(fd, UNI_I2C_INIT, &I2cInitReq);
	if(ret < 0)
	{
		printf("init i2c failed \n");
		goto err;
	}
	
	memset(&UNI_I2cRwByte, 0, sizeof(UNI_I2cRwByte));
	UNI_I2cRwByte.ProcotolType = I2C_PROCOTOL_TYPE_COM;
	UNI_I2cRwByte.Cmd = 0;
	UNI_I2cRwByte.ChipAddr = iDevAddr;   //
	UNI_I2cRwByte.RegOffset = offset;
	UNI_I2cRwByte.I2cRegLen = I2C_REGLEN_1;
	UNI_I2cRwByte.BusHandle = I2cInitReq.BusHandle;
    UNI_I2cRwByte.pBuf = ByteBuf;
	UNI_I2cRwByte.BufLen = 1;
#if 0	
	UNI_I2cRwByte.ChannelFlag = CHANNEL_I2C_USED;
	UNI_I2cRwByte.ChannelChipAddr = I2C_CHANNEL_ADDR;
	UNI_I2cRwByte.ChannelValue = iBusNum;
	UNI_I2cRwByte.ChannelRegOffset = iBusNum;
#endif
	if(flag == I2C_READ_FLAG)
	{
		if (ioctl(fd, UNI_I2C_READ, &UNI_I2cRwByte) < 0)
		{
			printf("UNI_I2C_READ failed\n");
			goto err;
		}
		*Value = ByteBuf[0];
	}
	else if(flag == I2C_WRITE_FLAG)
	{
		ByteBuf[0] = *Value;
		if (ioctl(fd, UNI_I2C_WRITE, &UNI_I2cRwByte) < 0)
		{
			printf("UNI_I2C_WRITE failed\n");
			goto err;
		}
	}
	else
	{
		printf("don't support I2C cmd\n");
		goto err;
	}
	
	close(fd);
	return 0;
err:
	close(fd);
	return -1;
}

/*默认是写成page1，实际调用时先设置此地址再调用读写函数*/
static int iI2cLt8612Addr = 0;
static int iI2cNumLt8612;
static int HDMI_WriteI2C_Byte(unsigned int reg_addr, unsigned int data)
{
	int iRet = -1;
	uint8_t u8Value = 0;
	u8Value = (uint8_t)data;
	iRet = I2cWriteReadSerial(&u8Value, I2C_WRITE_FLAG, reg_addr, iI2cLt8612Addr, iI2cNumLt8612, 0x02);

	return iRet;
}

static int HDMI_ReadI2C_Byte(unsigned int reg_addr)
{
    int iRet = -1;
	uint8_t u8Value = 0;
	iRet = I2cWriteReadSerial(&u8Value, I2C_READ_FLAG, reg_addr, iI2cLt8612Addr, iI2cNumLt8612, 0x02);
	if (0 != iRet)
	{
		return iRet;
	}
	return u8Value;
}

static void priv_msleep(unsigned int ms)
{
    struct timespec delayTime, elaspedTime;

    delayTime.tv_sec  = (time_t)(ms / 1000);
    delayTime.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&delayTime, &elaspedTime);
    return ;
}

void delay1ms(unsigned int uMs)
{
	priv_msleep(uMs);
}

/**
 * 请先确认配置I2C可以正常通信(读取0x00和0x01的值分别为0x86和0x12)，I2C速率为100k以下，
 * 然后配置初始化部分，正常显示后，在根据需要配置如下后续的配置和检测部分。
 *
 **/
void HDMI_VGA_Mode(void)//初始化
{
		LT8612_HDrst();
//		I2CADR=0x78;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		VideoRst();
		HDMI_WriteI2C_Byte(0x5c,0x1d);//set HDMI TX HPD software
		HDMI_WriteI2C_Byte(0xA8,0x08);//
		HDMI_WriteI2C_Byte(0x09,0x2b);
		HDMI_WriteI2C_Byte(0x0a,0xdf);
		HDMI_WriteI2C_Byte(0x0b,0xf9);
		//HDMI_WriteI2C_Byte(0x0c,0x31);
		HDMI_WriteI2C_Byte(0x0d,0x5b);

		HDMI_WriteI2C_Byte(0xac,0x00);
		HDMI_WriteI2C_Byte(0xad,0x00);
		HDMI_WriteI2C_Byte(0xb4,0x80);
		HDMI_WriteI2C_Byte(0x52,0x1a);
		HDMI_WriteI2C_Byte(0xb8,0xb0);
		HDMI_WriteI2C_Byte(0xbb,0xec);
		HDMI_WriteI2C_Byte(0x4f,0x00);
		//HDMI_WriteI2C_Byte(0xab,0x3f);
		//HDMI_WriteI2C_Byte(0x93,0x50);
		HDMI_WriteI2C_Byte(0x4d,0x10);
		/*I2CADR=0x7c;
		HDMI_WriteI2C_Byte(0x24,0x33);
		HDMI_WriteI2C_Byte(0x19,0x7e);
		HDMI_WriteI2C_Byte(0x49,0x00);
		I2CADR=0x78;
		*/		
		/********************END********************/
		
		/********************VGA_OUTPUT********************/
//		I2CADR=0x78;
		HDMI_WriteI2C_Byte(0x8d,0xf0);
		HDMI_WriteI2C_Byte(0x91,0xf0);
		HDMI_WriteI2C_Byte(0x43,0x00);													//调节RGB的色偏
//		I2CADR=0x7c;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE2;
		HDMI_WriteI2C_Byte(0x55,0xea);
		HDMI_WriteI2C_Byte(0x56,0x54);
//		I2CADR=0x78;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		/********************END********************/
		 AC_Mode_VccInt();
		 printf("[%s, %d] lt8612 init over!!!\n", __FUNCTION__, __LINE__);
}

void step(void)
{
	unsigned int Clk_Fre = 0;
	unsigned int Fre1 = 0;

  Clk_Fre = HDMI_ReadI2C_Byte(0xf5);
  Clk_Fre &= 	0x07;
  Clk_Fre <<= 16;
  Fre1 = HDMI_ReadI2C_Byte(0xf6);
  Fre1	 &= 0xff;
  Fre1 <<= 8;
  Fre1	 |= HDMI_ReadI2C_Byte(0xf7);
  Clk_Fre |= 	Fre1;
  /************According to the resolution of PLL step************/
///  I2CADR =	LT8612SX_PAGE1_ADR;
  HDMI_WriteI2C_Byte(0xb7, 0x34);	//pll_auto_rst_en=0,manual config
  if(Clk_Fre >= 250000)			//250M
  { 
	HDMI_WriteI2C_Byte(0xba, 0xff);
  }
  else if(Clk_Fre < 250000 && Clk_Fre >= 200000)			//200M
  {
	HDMI_WriteI2C_Byte(0xba, 0x30);
  }
  else if(Clk_Fre < 200000 && Clk_Fre >= 150000)			//150M
  {
	HDMI_WriteI2C_Byte(0xba, 0x0c);
  }
  else 
  {
	HDMI_WriteI2C_Byte(0xba, 0x00);
  }
}

void LT8612_HDrst(void)
{
    if (0x02 == iI2cNumLt8612)
    {/* 硬件复位 */
		if (0 != access("/sys/class/gpio/gpio433/value", W_OK))
		{
			system("echo 433 > /sys/class/gpio/export");
		}

		system("echo 0 > /sys/class/gpio/gpio433/value");
		delay1ms(200);
		system("echo 1 > /sys/class/gpio/gpio433/value");
    }
}

void AC_Mode_VccInt(void)
{
		//HDMI_WriteI2C_Byte(0x94,0x99);//clk ibias set
		HDMI_WriteI2C_Byte(0x95,0xa7);//clk swing set  518.25mv
		HDMI_WriteI2C_Byte(0x96,0xd8);//tap0 en
		HDMI_WriteI2C_Byte(0x97,0x38);//hdmitx en sel rg
		//HDMI_WriteI2C_Byte(0x98,0x33);//tap0 swing sel rg
		HDMI_WriteI2C_Byte(0x99,0xda);// 0xd0 tap0 d0 swing set 562.5 mv
		//HDMI_WriteI2C_Byte(0x9a,0xc8);//tap1 d0 swing set
		HDMI_WriteI2C_Byte(0x9b,0xc2);//LDO select
		HDMI_WriteI2C_Byte(0x9c,0x5a);//0x4f tap0 d1 swing 562.5 mv
		HDMI_WriteI2C_Byte(0x9d,0x5a);//0x4e tap0 d2 swing 562.5 mv
		HDMI_WriteI2C_Byte(0x9e,0x40);//tap1 d1/d2 swing
}


void VideoRst(void)  //需要复位LT8612SX RX模块（切换分辨率或信号变化时，需要操作这一模块）
{
	HDMI_WriteI2C_Byte(0x03, 0xdf);
	HDMI_WriteI2C_Byte(0x05, 0xfb);//reset pll
	HDMI_WriteI2C_Byte(0x04, 0xef);//reset pll trace
	delay1ms(20);
	HDMI_WriteI2C_Byte(0x03, 0xff);
	delay1ms(20);
	HDMI_WriteI2C_Byte(0x05, 0xff);
	delay1ms(10);
	HDMI_WriteI2C_Byte(0x04, 0xff);
}

/*
 * 关闭HDMI输出
 */
void Disable_HDMI_Out(void)
{
///		I2CADR=LT8612SX_PAGE1_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		HDMI_WriteI2C_Byte(0xB7,0x24);
		HDMI_WriteI2C_Byte(0x97,0x18);
		HDMI_WriteI2C_Byte(0x96,0x50);
}

/*
 * 打开HDMI输出
 */
void Enable_HDMI_Out(void)
{
  AC_Mode_VccInt();
}

/*
 * 打开VGA输出
 */
void Enable_VGA_Out(void)
{
///		I2CADR=LT8612SX_PAGE1_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		HDMI_WriteI2C_Byte(0x09,0x2b);
		HDMI_WriteI2C_Byte(0x0a,0xdf);
		HDMI_WriteI2C_Byte(0x0b,0xf9);
		HDMI_WriteI2C_Byte(0x0d,0x5b);
		HDMI_WriteI2C_Byte(0x8d,(HDMI_ReadI2C_Byte(0x8d) |0xf0));
		HDMI_WriteI2C_Byte(0x91,(HDMI_ReadI2C_Byte(0x91) |0xf0));
		//HDMI_WriteI2C_Byte(0x43,0x20);											//调节RGB的色偏
///		I2CADR=LT8612SX_PAGE2_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE2;
		HDMI_WriteI2C_Byte(0x55,0xea);
		HDMI_WriteI2C_Byte(0x56,0x54);
}

/*
 * 关闭VGA输出//4K输出时关闭VGA，只打开HDMI
 */
void Disable_VGA_Out(void)
{
///		I2CADR=LT8612SX_PAGE1_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		HDMI_WriteI2C_Byte(0x09,0x23);
		HDMI_WriteI2C_Byte(0x0a,0x9f);
		HDMI_WriteI2C_Byte(0x0b,0x28);
		HDMI_WriteI2C_Byte(0x0d,0x1b);
		HDMI_WriteI2C_Byte(0x8d,(HDMI_ReadI2C_Byte(0x8d)&0x0f));
		HDMI_WriteI2C_Byte(0x91,(HDMI_ReadI2C_Byte(0x91)&0x0f));
///		I2CADR=LT8612SX_PAGE2_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE2;
		HDMI_WriteI2C_Byte(0x55,0xaa);
		HDMI_WriteI2C_Byte(0x56,0xd4);
}

/*
 * 关闭音频输出
 */
void Disable_Audio(void)
{
///		I2CADR=LT8612SX_PAGE1_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		HDMI_WriteI2C_Byte(0x8d,(HDMI_ReadI2C_Byte(0x8d)&0xf0));
}

/*
 * 打开音频输出
 */
void Enable_Audio(void)
{
///		I2CADR=LT8612SX_PAGE1_ADR;
		iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
		HDMI_WriteI2C_Byte(0x8d,(HDMI_ReadI2C_Byte(0x8d)|0x0f));
}

int Lt8612_Config(int port, unsigned int enType)
{
	iI2cNumLt8612 = (port == 0)?0x2:0x01;
	HDMI_VGA_Mode();
	Enable_HDMI_Out();
	if (MIPI_MSG_3840X2160P30 == enType)
	{
		Disable_VGA_Out();
	}
	else
	{
		Enable_VGA_Out();
	}
	Enable_Audio();

	return 0;
}


void LT8612_Disable_Config()
{
	Disable_VGA_Out();
	Disable_HDMI_Out();
	Disable_Audio();
	printf("disable config\n");
}

void Lt8612_read_config(void)
{
    printf("\n\npage1!!");
	
    iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
	for(int i=0; i <= 0xff; i++)
		printf("reg=%#x, r_val=%#x\n", i, HDMI_ReadI2C_Byte(i));

	printf("\n\npage2!!");
	iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE2;
	for(int i=0; i <= 0xff; i++)
		printf("reg=%#x, r_val=%#x\n", i, HDMI_ReadI2C_Byte(i));
	
    return;
}

/*
 * 检测HDMI MODE状态
 */
int LT8612_HDMI_MODE_STATUS(int port)
{
	int hdmimode = 0;
	int hsync = 0;

	iI2cNumLt8612 = (port == 0)?0x2:0x01;
	iI2cLt8612Addr = I2C_DEVADDR_LT8612_PAGE1;
	hdmimode = HDMI_ReadI2C_Byte(LT8612_HDMI_MODE_ADDR);
	if(hdmimode == -1)
	{
		printf("LT8612 HDMI_MODE_STATUS read error\n");
		return -1;
	}	
	/* bit[7] HDMI模式检测位 */
	hdmimode = (hdmimode & 0x80)>>7;

	hsync = HDMI_ReadI2C_Byte(LT8612_HDMI_HSYNC_ADDR);
	if(hdmimode == -1)
	{
		printf("LT8612 HDMI_HSYNC_ADDR read error\n");
		return -1;
	}
	/* bit[7] Hsync is detected, and is stable */
	hsync = (hsync & 0x80)>>7;

	printf("Lt8612 detect hdmimode:%d hsync:%d \n",hdmimode, hsync);

	return (hdmimode&hsync);
}


