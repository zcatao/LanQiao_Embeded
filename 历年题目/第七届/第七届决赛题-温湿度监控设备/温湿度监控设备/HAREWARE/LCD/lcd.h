/*
  程序说明: CT117E嵌入式竞赛板LCD驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT117E嵌入式竞赛板
  日    期: 2011-8-9
*/
/*2016/12/21添加用于正点原子屏幕驱动*/
/*2017/01/14添加支持横竖屏驱动*/
/*2017/02/07修复支持横屏uC932X和uC8230型控制器寄存器配置*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* LCD Registers */
#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R227           0xE3
#define R229           0xE5
#define R231           0xE7
#define R239           0xEF

//以下2个宏定义，定义屏幕的显示方式及IO速度
#define USE_HORIZONTAL  0  	// 0,使用横屏.1,使用竖屏.
#define LCD_FAST_IO     1   //定义是否使用快速IO  0,不实用.1,使用
//LCD画笔和背景颜色
extern  vu16 TextColor; //字体颜色
extern	vu16 BackColor;	//背景颜色
//为了兼容正点原子程序
#define POINT_COLOR TextColor 
#define BACK_COLOR BackColor  

#if USE_HORIZONTAL /*竖屏*/
#define TFT_Width  240	/*宽度*/
#define	TFT_Height 320	/*高度*/
#else   /*横屏*/	
#define TFT_Width  320	/*宽度*/
#define	TFT_Height 240  /*高度*/
#endif

//控制线IO
#if LCD_FAST_IO==1 //快速IO
//操作频繁，为了提高速度，建议直接寄存器操作
#define	LCD_CS_SET  GPIOB->BSRR=1<<9    //片选端口   PB9
#define	LCD_RS_SET	GPIOB->BSRR=1<<8    //数据/命令  PB8	   
#define	LCD_WR_SET	GPIOB->BSRR=1<<5    //写数据	 PB5
#define	LCD_RD_SET	GPIOB->BSRR=1<<10   //读数据	 PB10
								    
#define	LCD_CS_CLR  GPIOB->BRR=1<<9     //片选端口   PB9
#define	LCD_RS_CLR	GPIOB->BRR=1<<8     //数据/命令  PB8	   
#define	LCD_WR_CLR	GPIOB->BRR=1<<5     //写数据	 PB5
#define	LCD_RD_CLR	GPIOB->BRR=1<<10     //读数据	 PB10						    

#else //慢速IO
#define	LCD_CS	PBout(9)  //片选端口     PB9
#define	LCD_RS	PBout(8)  //数据/命令    PB8	   
#define	LCD_WR	PBout(5)  //写数据			 PB5
#define	LCD_RD	PBout(10)  //读数据			 PB10
#endif

//数据线控制
//PC0~15,作为数据线
//在这里，因为操作频繁，为了提高速度，建议直接用寄存器操作。
#define DATAOUT(x)  GPIOC->ODR=x; //数据输出
#define DATAIN      GPIOC->IDR   //数据输入

//数据线传输
//写16位数据函数
//用宏定义,提高速度.
#if LCD_FAST_IO==1 //快速IO
#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 
#else//正常IO
#define LCD_WR_DATA(data){\
LCD_RS=1;\
LCD_CS=0;\
DATAOUT(data);\
LCD_WR=0;\
LCD_WR=1;\
LCD_CS=1;\
} 	
#endif

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	 0X841F //浅绿色 
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#define Line0          0
#define Line1          24
#define Line2          48
#define Line3          72
#define Line4          96
#define Line5          120
#define Line6          144
#define Line7          168
#define Line8          192
#define Line9          216

#define Horizontal     0x00
#define Vertical       0x01

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*----- Medium layer function -----*/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);/*写寄存器*/
void LCD_WR_REG(uint8_t data);/*写寄存器地址函数*/
u16 LCD_ReadReg(u8 LCD_Reg);/*读寄存器*/
void LCD_WriteRAM_Prepare(void);/*写显存准备*/
void LCD_WriteRAM(u16 RGB_Code);/*写显存*/
u16 LCD_ReadRAM(void);/*读显存*/
void LCD_PowerOn(void);/*关LCD*/
void LCD_DisplayOn(void);/*开液晶*/
void LCD_DisplayOff(void);/*禁用显示液晶*/

/*----- Low layer function -----*/
void LCD_CtrlLinesConfig(void);
void LCD_BusIn(void); /*输入*/
void LCD_BusOut(void);/*输出*/

/*----- High layer function -----*/
void STM3210B_LCD_Init(void);/*初始化液晶*/
void LCD_SetTextColor(vu16 Color);/*设置文本颜色*/
void LCD_SetBackColor(vu16 Color);/*设置背景颜色*/
void LCD_ClearLine(u8 Line);/*清除所选行*/
void LCD_Clear(u16 Color);/*液晶重置颜色*/
void LCD_SetCursor(u8 Xpos, u16 Ypos);/*设置光标位置*/

void LCD_DrawPoint(uint16_t x,uint16_t y);/*显示一个点*/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c);/*画了一个字符液晶*/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii);/*显示一个字符(16点宽度,24点高度)*/
void LCD_DisplayStringLine(u8 Line, u8 *ptr);/*某一行输出字符串*/

void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Height, u16 Width);/*设置显示窗口*/
void LCD_WindowModeDisable(void);/*禁用LCD窗口模式*/
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8 Direction);/*显示一条直线*/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width);/*显示一个矩形*/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius);/*显示一个圆*/
void LCD_DrawMonoPict(uc32 *Pict);/*显示一个单色照片*/
void LCD_WriteBMP(u32 BmpAddress);/*显示一个位图图像内部Flash加载*/
void LCD_DrawBMP(u32 BmpAddress);
void LCD_DrawPicture(const u8* picture);/*显示16个颜色图片*/

/*2016/12/21添加用于正点原子屏幕驱动*/
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);//*显示一个点*/
u16 LCD_ReadPoint(u16 x,u16 y); 				   //*读取个某点的颜色值*/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);//*在指定区域内填充指定颜色*/
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);//*在指定区域内填充指定颜色块*/
void LCD_DrawLine1(u16 x1, u16 y1, u16 x2, u16 y2);//*画线*/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);//*画矩形*/
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);//*在指定位置画一个指定大小的圆*/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);//*在指定位置显示一个字符*/
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);//*显示数字,高位为0,则不显示*/
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);//*显示数字,高位为0,还是显示*/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);//*显示字符串*/
void LCD_Init(void);//*初始化*/

void LCD_ShowChinese(u16 x,u16 y,u8 num,u8 size,u8 mode);//在指定位置显示一个汉字

#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
