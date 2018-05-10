/*
  ����˵��: CT117EǶ��ʽ������LCD��������
  �������: Keil uVision 4.10 
  Ӳ������: CT117EǶ��ʽ������
  ��    ��: 2011-8-9
*/
/*2016/12/21�����������ԭ����Ļ����*/
/*2017/01/14���֧�ֺ���������*/
/*2017/02/07�޸�֧�ֺ���uC932X��uC8230�Ϳ������Ĵ�������*/
#include "lcd.h"
#include "fonts.h"
#include "ziku.h"

vu16 TextColor = 0x0000, BackColor = 0xFFFF;
vu16 dummy;
/*******************************************************************************
* Function Name  : Delay_LCD
* Description    : Inserts a delay time.����һ���ӳ�ʱ��
* Input          : nCount: specifies the delay time length.nCount:ָ���ӳ�ʱ�䳤��
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_LCD(u16 n)
{
	u16 i,j;
	for (i = 0;i<n;++i)
		for(j=0;j<3000;++j);
}
/*uC8230��Һ���������Ĵ�������*/
void REG_8230_Init(void)
{
	LCD_WriteReg(0x0000,0x0001);
	Delay_LCD(1000); 
	LCD_WriteReg(0x0001,0x0000);
	LCD_WriteReg(0x0010,0x1790);
	LCD_WriteReg(0x0060,0x2700);
	LCD_WriteReg(0x0061,0x0001);
	LCD_WriteReg(0x0046,0x0002);
	LCD_WriteReg(0x0013,0x8010);
	LCD_WriteReg(0x0012,0x80fe);
	LCD_WriteReg(0x0002,0x0500);
	LCD_WriteReg(0x0003,0x1030);
	
	LCD_WriteReg(0x0030,0x0303);
	LCD_WriteReg(0x0031,0x0303);
	LCD_WriteReg(0x0032,0x0303);
	LCD_WriteReg(0x0033,0x0300);
	LCD_WriteReg(0x0034,0x0003);
	LCD_WriteReg(0x0035,0x0303);
	LCD_WriteReg(0x0036,0x0014);
	LCD_WriteReg(0x0037,0x0303);
	LCD_WriteReg(0x0038,0x0303);
	LCD_WriteReg(0x0039,0x0303);
	LCD_WriteReg(0x003a,0x0300);
	LCD_WriteReg(0x003b,0x0003);
	LCD_WriteReg(0x003c,0x0303);
	LCD_WriteReg(0x003d,0x1400);
	  
	LCD_WriteReg(0x0092,0x0200);
	LCD_WriteReg(0x0093,0x0303);
	LCD_WriteReg(0x0090,0x080d); 
	LCD_WriteReg(0x0003,0x1018); 
	LCD_WriteReg(0x0007,0x0173);
}
/*uC932X��Һ���������Ĵ�������*/
void REG_932X_Init(void)
{
	LCD_WriteReg(R227, 0x3008);   // Set internal timing
	LCD_WriteReg(R231, 0x0012); // Set internal timing
	LCD_WriteReg(R239, 0x1231);   // Set internal timing
	LCD_WriteReg(R1  , 0x0000); // set SS and SM bit		  //0x0100
	LCD_WriteReg(R2  , 0x0700); // set 1 line inversion
	LCD_WriteReg(R3  , 0x1030);   // set GRAM write direction and BGR=1.
	LCD_WriteReg(R4  , 0x0000);   // Resize register
	LCD_WriteReg(R8  , 0x0207);   // set the back porch and front porch
	LCD_WriteReg(R9  , 0x0000);   // set non-display area refresh cycle ISC[3:0]
	LCD_WriteReg(R10 , 0x0000);   // FMARK function
	LCD_WriteReg(R12 , 0x0000); // RGB interface setting
	LCD_WriteReg(R13 , 0x0000);   // Frame marker Position
	LCD_WriteReg(R15 , 0x0000); // RGB interface polarity
	/**************Power On sequence ****************/
	LCD_WriteReg(R16 , 0x0000);   // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(R17 , 0x0007);   // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WriteReg(R18 , 0x0000); // VREG1OUT voltage
	LCD_WriteReg(R19 , 0x0000);   // VDV[4:0] for VCOM amplitude
	Delay_LCD(1000);                    // Delay 200 MS , Dis-charge capacitor power voltage
	LCD_WriteReg(R16 , 0x1690);   // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(R17 , 0x0227); // R11H=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	Delay_LCD(50);      // Delay XXms
	LCD_WriteReg(R18 , 0x001D); // External reference voltage= Vci;
	Delay_LCD(50);      // Delay XXms
	LCD_WriteReg(R19 , 0x0800); // R13H=1D00 when R12H=009D;VDV[4:0] for VCOM amplitude
	LCD_WriteReg(R41 , 0x0014); // R29H=0013 when R12H=009D;VCM[5:0] for VCOMH
	LCD_WriteReg(R43 , 0x000B);   // Frame Rate = 96Hz
	Delay_LCD(50);      // Delay XXms
	LCD_WriteReg(R32 , 0x0000); // GRAM horizontal Address
	LCD_WriteReg(R33 , 0x0000); // GRAM Vertical Address
	/* ----------- Adjust the Gamma Curve ---------- */
	LCD_WriteReg(R48 , 0x0007);
	LCD_WriteReg(R49 , 0x0707);
	LCD_WriteReg(R50 , 0x0006);
	LCD_WriteReg(R53 , 0x0704);
	LCD_WriteReg(R54 , 0x1F04);
	LCD_WriteReg(R55 , 0x0004);
	LCD_WriteReg(R56 , 0x0000);
	LCD_WriteReg(R57 , 0x0706);
	LCD_WriteReg(R60 , 0x0701);
	LCD_WriteReg(R61 , 0x000F);
	/* ------------------ Set GRAM area --------------- */
	LCD_WriteReg(R80 , 0x0000);   // Horizontal GRAM Start Address
	LCD_WriteReg(R81 , 0x00EF);   // Horizontal GRAM End Address
	LCD_WriteReg(R82 , 0x0000); // Vertical GRAM Start Address
	LCD_WriteReg(R83 , 0x013F); // Vertical GRAM Start Address
	LCD_WriteReg(R96 , 0x2700); // Gate Scan Line		  0xA700
	LCD_WriteReg(R97 , 0x0001); // NDL,VLE, REV
	LCD_WriteReg(R106, 0x0000); // set scrolling line
	/* -------------- Partial Display Control --------- */
	LCD_WriteReg(R128, 0x0000);   
	LCD_WriteReg(R129, 0x0000);
	LCD_WriteReg(R130, 0x0000);
	LCD_WriteReg(R131, 0x0000);
	LCD_WriteReg(R132, 0x0000);
	LCD_WriteReg(R133, 0x0000);
	/* -------------- Panel Control ------------------- */
	LCD_WriteReg(R144, 0x0010);
	LCD_WriteReg(R146, 0x0000);
	LCD_WriteReg(R147, 0x0003);
	LCD_WriteReg(R149, 0x0110);
	LCD_WriteReg(R151, 0x0000);
	LCD_WriteReg(R152, 0x0000);
	/* Set GRAM write direction and BGR = 1 */
	/* I/D=01 (Horizontal : increment, Vertical : decrement) */
	/* AM=1 (address is updated in vertical writing direction) */
	LCD_WriteReg(R3  , 0x01018);  //0x1018	
	LCD_WriteReg(R7  , 0x0173); // 262K color and display ON
}
/*******************************************************************************
* Function Name  : STM3210B_LCD_Init
* Description    : Initializes the LCD.��ʼ��Һ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void STM3210B_LCD_Init(void)
{ 	
	#if USE_HORIZONTAL /*����*/
	LCD_CtrlLinesConfig();
	Delay_LCD(50); // delay 50 ms 
	LCD_WriteReg(0x0000,0x0001); //�����ڲ�ʱ��
	Delay_LCD(80); // delay 80 ms 	 
	LCD_WriteReg(0x00EC,0x108F);// internal timeing  
	LCD_WriteReg(0x00EF,0x1234);// ADD 
	LCD_WriteReg(0x0001,0x0100);     
    LCD_WriteReg(0x0002,0x0700);//��Դ����     
    LCD_WriteReg(0x0001,0x0100);     
    LCD_WriteReg(0x0002,0x0700);//��Դ����                    
    LCD_WriteReg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
    LCD_WriteReg(0x0004,0x0000);                                   
    LCD_WriteReg(0x0008,0x0207);	           
    LCD_WriteReg(0x0009,0x0000);         
    LCD_WriteReg(0x000a,0x0000);//display setting         
    LCD_WriteReg(0x000c,0x0001);//display setting          
    LCD_WriteReg(0x000d,0x0000);//0f3c          
    LCD_WriteReg(0x000f,0x0000);
	//��Դ����
    LCD_WriteReg(0x0010,0x0000);   
    LCD_WriteReg(0x0011,0x0007);
    LCD_WriteReg(0x0012,0x0000);                                                                 
    LCD_WriteReg(0x0013,0x0000);                 
    Delay_LCD(50); 
    LCD_WriteReg(0x0010,0x1590);   
    LCD_WriteReg(0x0011,0x0227);
    Delay_LCD(50); 
    LCD_WriteReg(0x0012,0x009c);                  
    Delay_LCD(50); 
    LCD_WriteReg(0x0013,0x1900);   
    LCD_WriteReg(0x0029,0x0023);
    LCD_WriteReg(0x002b,0x000e);//
    Delay_LCD(50); 
    LCD_WriteReg(0x0020,0x0000);//ȷ������                                                            
    LCD_WriteReg(0x0021,0x013f);           
  	Delay_LCD(50); 
	//٤��У��
    LCD_WriteReg(0x0030,0x0007); 
    LCD_WriteReg(0x0031,0x0707);   
    LCD_WriteReg(0x0032,0x0006);
    LCD_WriteReg(0x0035,0x0704);
    LCD_WriteReg(0x0036,0x1f04); 
    LCD_WriteReg(0x0037,0x0004);
    LCD_WriteReg(0x0038,0x0000);        
    LCD_WriteReg(0x0039,0x0706);     
    LCD_WriteReg(0x003c,0x0701);
    LCD_WriteReg(0x003d,0x000f);
    Delay_LCD(50);
	//GRAM����
    LCD_WriteReg(0x0050,0x0000); //ˮƽGRAM��ʼλ�� 
    LCD_WriteReg(0x0051,0x00ef); //ˮƽGRAM��ֹλ��                    
    LCD_WriteReg(0x0052,0x0000); //��ֱGRAM��ʼλ��                    
    LCD_WriteReg(0x0053,0x013f); //��ֱGRAM��ֹλ��      
    LCD_WriteReg(0x0060,0xa700);        
    LCD_WriteReg(0x0061,0x0001); 
    LCD_WriteReg(0x006a,0x0000);
	 //������ʾ����
    LCD_WriteReg(0x0080,0x0000);
    LCD_WriteReg(0x0081,0x0000);
    LCD_WriteReg(0x0082,0x0000);
    LCD_WriteReg(0x0083,0x0000);
    LCD_WriteReg(0x0084,0x0000);
    LCD_WriteReg(0x0085,0x0000);
  	//������
    LCD_WriteReg(0x0090,0x0010);     
    LCD_WriteReg(0x0092,0x0600);  
    //����26��ɫ��ʾ����    
    LCD_WriteReg(0x0007,0x0133);  	  
	LCD_Clear(White);
	#else   /*����*/
	LCD_CtrlLinesConfig();
	dummy = LCD_ReadReg(0);		
	if(dummy == 0x8230)
	{
		REG_8230_Init();
	}
	else
	{
		REG_932X_Init();	
	}
	dummy = LCD_ReadReg(0);
	#endif
}
/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : Sets the Text color.�����ı���ɫ��
* Input          : - Color: specifies the Text color code RGB(5-6-5).
				   ��ɫ:ָ���ı���ɫ����RGB(5-6-5)��
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
				   ����TextColor:��ɫLCD_DrawChar��LCD_DrawPicture������ʹ�õ�ȫ�ֱ�����
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(vu16 Color)
{
	TextColor = Color;
}
/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : Sets the Background color.���ñ�����ɫ��
* Input          : - Color: specifies the Background color code RGB(5-6-5).
				   ��ɫ:ָ��������ɫ����RGB(5-6-5)��
* Output         : - BackColor: Background color global variable used by 
*                  LCD_DrawChar and LCD_DrawPicture functions.
				   ����ɫ:������ɫLCD_DrawChar��ʹ�õ�ȫ�ֱ�����LCD_DrawPicture���ܡ�
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(vu16 Color)
{
	BackColor = Color;
}
/*******************************************************************************
* Function Name  : LCD_ClearLine
* Description    : Clears the selected line.�����ѡ�С�
* Input          : - Line: the Line to be cleared. ��:�߱������
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearLine(u8 Line)
{
	LCD_DisplayStringLine(Line, "                    ");
}
/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.Һ��ɨ���˶���
* Input          : Color: the color of the background.��ɫ:��ɫ�ı�����
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
	#if USE_HORIZONTAL
	uint32_t index=0;      
	LCD_SetCursor(0x00,0x0000);//���ù��λ�� 
	LCD_WriteRAM_Prepare(); //��ʼд��GRAM	
	for(index=0;index<76800;index++)//240 *320 
	{
		LCD_WR_DATA(Color);    
	}
	#else 
	u32 index = 0;
	LCD_SetCursor(0x00, 0x0000); 
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 76800; index++)
	{
		LCD_WriteRAM(Color);    
	}
	#endif 	
}
/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.���ù��λ�á�
* Input          : - Xpos: specifies the X position.
				   Xpos:ָ����X��λ��
*                  - Ypos: specifies the Y position. 
				   Ypos:ָ����Y��λ��
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u8 Xpos, u16 Ypos)
{ 
	LCD_WriteReg(R32, Xpos);
	LCD_WriteReg(R33, Ypos); 
}
//����
//����x:0~239,y:0~319
//����x:0~319,y:0~239
//TextColor:�˵����ɫ 
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	#if USE_HORIZONTAL
	LCD_SetCursor(x,y);//���ù��λ�� 
	#else		  
	y=319-y;		  //�������ǵ�תx,y����
	LCD_SetCursor(x,y);//���ù��λ�� 
	#endif
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(R34);//��ʼд��GRAM
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
	LCD_WR_DATA(TextColor); 	
} 
/*******************************************************************************
* Function Name  : LCD_DrawChar �ַ�
* Description    : Draws a character on LCD.����һ���ַ�Һ��
* Input          : - Xpos: the Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Ypos: start column address.
*                  - c: pointer to the character data. ָ��ָ����ַ�����
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c)
{
	#if USE_HORIZONTAL
	u32 index = 0, i = 0;	
	u8 Xaddress = 0;
	u16 temp; //�������浱ǰ�ı���
	uint16_t colortemp = TextColor;//������ʱ����pointcolor
	Xaddress = Xpos;
	LCD_SetCursor(Xpos,Ypos);
	for(index = 0; index < 24; index++)//24��
	{
		temp = c[index];  //���浱ǰ���� 16λ
		for(i = 0; i < 16; i++)//ÿ��16λ
		{
			if(temp & 0x01)//��֤ĳλ�Ƿ�Ϊ1
			{
				TextColor = colortemp;//ѡ��ӡ��ɫ��ӡ
			}
			else
			{
			  TextColor = BackColor;//ѡ������ɫ��ӡ
			}
			LCD_DrawPoint(Xaddress,Ypos);//�������
			temp>>=1;  //����ѭ��һλ
		  Xaddress++; //ͬһ����һ����
		}
		Xaddress = Xpos;//x�����λ
		Ypos++;  //��һ��
		LCD_SetCursor(Xaddress, Ypos);
	}
	TextColor = colortemp;//��ԭϵͳ�Ĵ�ӡ��ɫ
	#else 
	u32 index = 0, i = 0;
	u8 Xaddress = 0;
   
	Xaddress = Xpos;
	LCD_SetCursor(Xaddress, Ypos);
  
	for(index = 0; index < 24; index++)
	{
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for(i = 0; i < 16; i++)
		{
			if((c[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
			}
			else
			{
				LCD_WriteRAM(TextColor);
			}
		}
		Xaddress++;
		LCD_SetCursor(Xaddress, Ypos);
	}
	#endif 	
}
/*******************************************************************************
* Function Name  : LCD_DisplayChar  �ַ���
* Description    : Displays one character (16dots width, 24dots height).
					��ʾһ���ַ�(16����,24��߶�)
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Column: start column address.
*                  - Ascii: character ascii code, must be between 0x20 and 0x7E.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii)
{
	Ascii -= 32;//�ո��ASC��
	#if USE_HORIZONTAL
	LCD_DrawChar(Column, Line, &ASCII_Table[Ascii * 24]);
	#else 
	LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
	#endif 
}
/*******************************************************************************
* Function Name  : LCD_DisplayStringLine
* Description    : Displays a maximum of 20 char on the LCD. ��Һ����ʾ���20���ַ�
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayStringLine(u8 Line, u8 *ptr)
{
	u32 i = 0;	
	#if USE_HORIZONTAL
	u16 refcolumn = 0;
	while ((*ptr != 0) && (i < 15))   //����һ��������ʾ15���ַ�
	{
		LCD_DisplayChar(Line, refcolumn, *ptr); 
		refcolumn += 16;
		ptr++;
		i++;
	}
	#else 
	u16 refcolumn = 319;//319;
	while ((*ptr != 0) && (i < 20))	 //����һ��������ʾ20���ַ�
	{
		LCD_DisplayChar(Line, refcolumn, *ptr);
		refcolumn -= 16;
		ptr++;
		i++;
	}
	#endif 	
}
/*******************************************************************************
* Function Name  : LCD_SetDisplayWindow
* Description    : Sets a display window������ʾ����
* Input          : - Xpos: specifies the X buttom left position.
					 Xpos��ָ��x��ť��ߵ�λ��
*                  - Ypos: specifies the Y buttom left position. 
					 Ypos��ָ��Y��ť��ߵ�λ��
*                  - Height: display window height.
					 �߶�:��ʾ���ڸ߶ȡ�
*                  - Width: display window width.
					 ���:��ʾ���ڿ�ȡ�
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Height, u16 Width)
{
	if(Xpos >= Height)
	{
		LCD_WriteReg(R80, (Xpos - Height + 1));
	}
	else
	{
		LCD_WriteReg(R80, 0);
	}
	LCD_WriteReg(R81, Xpos);
	if(Ypos >= Width)
	{
		LCD_WriteReg(R82, (Ypos - Width + 1));
	}  
	else
	{
		LCD_WriteReg(R82, 0);
	}
	/* Vertical GRAM End Address */
	LCD_WriteReg(R83, Ypos);
	LCD_SetCursor(Xpos, Ypos);
}
/*******************************************************************************
* Function Name  : LCD_WindowModeDisable
* Description    : Disables LCD Window mode. ����LCD����ģʽ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WindowModeDisable(void)
{
	LCD_SetDisplayWindow(239, 0x13F, 240, 320);
	LCD_WriteReg(R3, 0x1018);    
}
/*******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Displays a line.��ʾһ��ֱ�ߡ�
* Input          : - Xpos: specifies the X position.
					 Xpos:ָ����X��λ�á�
*                  - Ypos: specifies the Y position.
					 Ypos:ָ��Yλ�á�
*                  - Length: line length.
					 ����:�߳��ȡ�
*                  - Direction: line direction.
					 ����:�߷��򡣸ò�������������ֵ֮һ:��ֱ��ˮƽ��
*                    This parameter can be one of the following values: Vertical 
*                    or Horizontal.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8 Direction)
{
	u32 i = 0; 
	#if USE_HORIZONTAL
	LCD_SetCursor(Xpos, Ypos);
	if(Direction == 0x01)
	{
		for(i = 0; i < Length; i++)
		{
			LCD_WriteRAM_Prepare();  /* Prepare to write GRAM */
			LCD_WriteRAM(TextColor);
			Ypos++;
			LCD_SetCursor(Xpos, Ypos);
		}	
	}
	else
	{
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for(i = 0; i < Length; i++)
		{
			LCD_WriteRAM(TextColor);
		}	
	}
	#else
	LCD_SetCursor(Xpos, Ypos);
	if(Direction == 0x01)
	{
		for(i = 0; i < Length; i++)
		{
			LCD_WriteRAM_Prepare();  /* Prepare to write GRAM */
			LCD_WriteRAM(TextColor);
			Xpos++;
			LCD_SetCursor(Xpos, Ypos);
		}	
	}
	else
	{
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for(i = 0; i < Length; i++)
		{
			LCD_WriteRAM(TextColor);
		}	
	}
	#endif			
}
/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.��ʾһ�����Ρ�
* Input          : - Xpos: specifies the X position. 
					 Xpos:ָ����X��λ�á�
*                  - Ypos: specifies the Y position.
					 Ypos:ָ��Yλ�á�
*                  - Height: display rectangle height.
					 �߶�:��ʾ���εĸ߶ȡ�
*                  - Width: display rectangle width.
					 ���:��ʾ���εĿ�ȡ�
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width)
{
	#if USE_HORIZONTAL
	LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
	LCD_DrawLine((Xpos+Height), Ypos, Width, Vertical);	
	LCD_DrawLine(Xpos, Ypos, Height, Vertical);
	LCD_DrawLine(Xpos, (Ypos+Width), Height, Horizontal);
	#else
	LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
	LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);	
	LCD_DrawLine(Xpos, Ypos, Height, Vertical);
	LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);	
	#endif	
}
/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Displays a circle.��ʾһ��Բ��
* Input          : - Xpos: specifies the X position.
					 Xpos:ָ����X��λ�á�
*                  - Ypos: specifies the Y position.
					 Ypos:ָ��Yλ�á�
*                  - Height: display rectangle height.
					 �߶�:��ʾ���εĸ߶ȡ�
*                  - Width: display rectangle width.
					 ���:��ʾ���εĿ�ȡ�
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius)
{
	s32  D;
	u32  CurX;
	u32  CurY;
  	D = 3 - (Radius << 1);
  	CurX = 0;
  	CurY = Radius;
  	while (CurX <= CurY)
  	{
	    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos + CurX, Ypos - CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos - CurX, Ypos + CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos - CurX, Ypos - CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos + CurY, Ypos - CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos - CurY, Ypos + CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    LCD_SetCursor(Xpos - CurY, Ypos - CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);	
	    if (D < 0)
	    { 
	      D += (CurX << 2) + 6;
	    }
	    else
	    {
	      D += ((CurX - CurY) << 2) + 10;
	      CurY--;
	    }
	    CurX++;
  	}
}
/*******************************************************************************
* Function Name  : LCD_DrawMonoPict//��ɫͼƬ
* Description    : Displays a monocolor picture.��ʾһ����ɫ��Ƭ��
* Input          : - Pict: pointer to the picture array.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawMonoPict(uc32 *Pict)
{
	u32 index = 0, i = 0;
	LCD_SetCursor(0, 319); 
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 2400; index++)
	{
		for(i = 0; i < 32; i++)
		{
			if((Pict[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
			}
			else
			{
				LCD_WriteRAM(TextColor);
			}
		}
	}
}
/*******************************************************************************
* Function Name  : LCD_WriteBMP
* Description    : Displays a bitmap picture loaded in the internal Flash.
				   ��ʾһ��λͼͼ���ڲ�Flash���ء�
* Input          : - BmpAddress: Bmp picture address in the internal Flash.
				   - BmpAddress:BmpͼƬ��ַ���ڲ�Flash��
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteBMP(u32 BmpAddress)
{
	u32 index = 0, size = 0;
	size = *(vu16 *) (BmpAddress + 2);
	size |= (*(vu16 *) (BmpAddress + 4)) << 16;
	index = *(vu16 *) (BmpAddress + 10);
	index |= (*(vu16 *) (BmpAddress + 12)) << 16;
	size = (size - index)/2;
	BmpAddress += index;
	LCD_WriteReg(R3, 0x1008);
	LCD_WriteRAM_Prepare();
	for(index = 0; index < size; index++)
	{
		LCD_WriteRAM(*(vu16 *)BmpAddress);
		BmpAddress += 2;
	}
	LCD_WriteReg(R3, 0x1018);
}
/**********************************************************
 * @brief  LCD_WR_REG д�Ĵ�����ַ����  
 * @param  data  ���Ĵ�����ַ               
 * @retval  None            
 *********************************************************/
void LCD_WR_REG(uint8_t data)
{ 	
	LCD_CS_CLR;
	LCD_RS_CLR;//д��ַ  	 
	DATAOUT(data); 
	LCD_WR_CLR; 
	LCD_WR_SET; 
 	LCD_CS_SET;   
}
/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
	GPIOB->BRR = 0x0200;   //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100;   //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOC->ODR = LCD_Reg;  //GPIO_Write(LCD_DataPort,LCD_Reg);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	GPIOC->ODR = LCD_RegValue;  //GPIO_Write(LCD_DataPort,LCD_RegValue);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH(); 
}
/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
	u16 temp;
	GPIOB->BRR = 0x0200;   //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100;   //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOC->ODR = LCD_Reg;  //GPIO_Write(LCD_DataPort,LCD_Reg);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	LCD_BusIn();
	GPIOB->BRR = 0x0400;   //LCD_NRD_LOW();
	temp = GPIOC->IDR;     //temp=GPIO_ReadInputData(LCD_DataPort);
	GPIOB->BSRR = 0x0400;  //LCD_NRD_HIGH();
	LCD_BusOut();
	GPIOB->BSRR = 0x0200;  //LCD_NCS_HIGH();
	return temp;
}
/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{ 
	GPIOB->BRR = 0x0200;   //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100;   //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOC->ODR = R34;      //GPIO_Write(LCD_DataPort,R34);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	GPIOB->BSRR = 0x0200;  //LCD_NCS_HIGH();
}
/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{
	GPIOB->BRR = 0x0200;   //LCD_NCS_LOW();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOC->ODR = RGB_Code; //GPIO_Write(LCD_DataPort,RGB_Code);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	GPIOB->BSRR = 0x0200;  //LCD_NCS_HIGH();
}
/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
	u16 temp;
	GPIOB->BRR = 0x0200;   //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100;   //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOC->ODR = R34;      //GPIO_Write(LCD_DataPort,R34);
	GPIOB->BRR = 0x0020;   //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020;  //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100;  //LCD_RS_HIGH();
	LCD_BusIn();
	GPIOB->BRR = 0x0400;   //LCD_NRD_LOW();
	temp = GPIOC->IDR;     //temp=GPIO_ReadInputData(LCD_DataPort);
	GPIOB->BSRR = 0x0400;  //LCD_NRD_HIGH();
	LCD_BusOut();
	GPIOB->BSRR = 0x0200;  //LCD_NCS_HIGH();                       
	return temp;
}
/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : Power on the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PowerOn(void)
{
	LCD_WriteReg(R16, 0x0000);
	LCD_WriteReg(R17, 0x0000); 
	LCD_WriteReg(R18, 0x0000);
	LCD_WriteReg(R19, 0x0000); 
	Delay_LCD(20);             
	LCD_WriteReg(R16, 0x17B0); 
	LCD_WriteReg(R17, 0x0137);
	Delay_LCD(5);             
	LCD_WriteReg(R18, 0x0139); 
	Delay_LCD(5);             
	LCD_WriteReg(R19, 0x1d00); 
	LCD_WriteReg(R41, 0x0013); 
	Delay_LCD(5);             
	LCD_WriteReg(R7, 0x0173);
}
/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
	LCD_WriteReg(R7, 0x0173);
}
/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
	LCD_WriteReg(R7, 0x0000); 
}
/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines.
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	LCD_BusOut();
	GPIOB->BSRR |= 0x0620;
}
/*******************************************************************************
* Function Name  : LCD_BusIn
* Description    : Configures the Parallel interface for LCD(PortC)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_BusIn(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : LCD_BusOut
* Description    : Configures the Parallel interface for LCD(PortC)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_BusOut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
//16��ɫ��PIC
/*******************************************************************************
* Function Name  : LCD_DrawPicture
* Description    : Displays a 16 color picture.��ʾ16����ɫͼƬ��
* Input          : - picture: pointer to the picture array.
				   ����ͼƬ:ָ�����顣
* Output         : None
* Return         : None
*******************************************************************************/
//picture ��һ���ֽ����飬ÿ�����ֽ���һ�����ص���ɫֵ��
void LCD_DrawPicture(const u8* picture)
{
	int index;
	LCD_SetCursor(0x00, 0x0000); 
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 76800; index++)
	{
		LCD_WriteRAM(picture[2*index+1]<<8|picture[2*index]);	
	}
}

/***********************************************************
 *	������ֻ��ѧϰʹ�ã�δ��ԭ������ɣ��������������κ���;
 *  ����˵��: CT117EǶ��ʽ������LCD��������
 *	��ֲ������ԭ��TFTҺ������������ѧϰʹ��
 *  �������: Keil uVision 4.10 
 *  Ӳ������: CT117EǶ��ʽ������
 *  ��ֲ����: 2016/12/21
 ***********************************************************/
//����ĳ���Ϊ������������ԭ�ӵĶ�����ӵ� 

/******************************************************
 * ��������LCD_ColorPoint
 * ����  ����ָ�����괦��ʾһ��ָ����ɫ�ĵ�
 * ����  : -x      ������ʾλ�� 0~239
           -y      ������ʾλ�� 0~319
		   -Color  ָ����ɫ
 * ���  ����
 * ����  ��	LCD_ColorPoint(100,200,0);
		   	LCD_ColorPoint(10,200,100);
		   	LCD_ColorPoint(300,220,1000);
 * ע��  ��	(0,0)λ��ΪҺ�������Ͻ� �Ѳ���
*********************************************************/ 
//���ٻ���  
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
	#if USE_HORIZONTAL
	LCD_SetCursor(x,y);//���ù��λ�� 
	#else	
	u16 x1,y1;		 
	x1=x;y1=y; //x,y���껥��
	y=319-x1;x=y1;//�������ǵ�תx,y����			 	
	LCD_SetCursor(x,y);//���ù��λ�� 
	#endif
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(R34);//��ʼд��GRAM
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
	LCD_WR_DATA(color); 	
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r;
	if(x>=TFT_Width||y>=TFT_Height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	LCD_SetCursor(x,y);
	LCD_WR_REG(0X22);      		 			//����IC���Ͷ�GRAMָ��
	GPIOC->CRL=0X88888888; 							//PB0-7  ��������
	GPIOC->CRH=0X88888888; 							//PB8-15 ��������
	GPIOC->ODR=0XFFFF;     							//ȫ�������
	LCD_RS_SET;
	LCD_CS_CLR;	    
	//��ȡ����(��GRAMʱ,��һ��Ϊ�ٶ�)	
	LCD_RD_CLR;		   
	Delay_LCD(4);									//��ʱ		
 	r=DATAIN;  										//ʵ��������ɫ 
	LCD_RD_SET;
 	//dummy READ
	LCD_RD_CLR;					   
	Delay_LCD(4);//��ʱ					   
 	r=DATAIN;  	//ʵ��������ɫ
	LCD_RD_SET;
	LCD_CS_SET;
	GPIOC->CRL=0X33333333; 		//PB0-7  �������
	GPIOC->CRH=0X33333333; 		//PB8-15 �������
	GPIOC->ODR=0XFFFF;    		//ȫ�������  
	return r;	//�⼸��ICֱ�ӷ�����ɫֵ
}	
//��ָ�����������ָ����ɫ
//�����С:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
	 	LCD_SetCursor(sx,i); 	               //���ù��λ�� 
		LCD_WR_REG(R34);       			        //��ʼд��GRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
	}	
} 
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD_WR_DATA(color[i*width+j]);//д������ 
	}	  
}
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine1(u16 x1, u16 y1, u16 x2, u16 y2)
{			
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{	
	LCD_DrawLine1(x1,y1,x2,y1);
	LCD_DrawLine1(x1,y1,x1,y2);
	LCD_DrawLine1(x1,y2,x2,y2);
	LCD_DrawLine1(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 			 
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
	u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,TextColor);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BackColor);
			temp<<=1;
			y++;
			if(y>=TFT_Height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=TFT_Width)return;	//��������
				break;
			}		
		}  	 
	}  	    		 	  
}
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;	 	
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
}
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 	
	}
}    
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
	while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {
		if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
		p++;
    }        
}
void LCD_Init(void)//��ʼ��
{
	STM3210B_LCD_Init();
	LCD_Clear(White);//����
	LCD_SetTextColor(Black); //������ɫ
	LCD_SetBackColor(White);	 //������ɫ
}
//��ָ��λ����ʾһ������
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:��fonts.h���Զ���
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChinese(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							     		
	u8 csize;
	u8 temp,t1,t;	
	u16 y0=y;
	csize=(2*(size/8+((size%8)?1:0))*(size/2));		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=chinese_12[num][t]; 	 	//����1206����
		else if(size==16)temp=chinese_16[num][t];	//����1608����
		else if(size==24)temp=chinese_24[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,TextColor);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BackColor);
			temp<<=1;
			y++;								
			if(y>=TFT_Height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=TFT_Width)return;	//��������
				break;
			}	
		}  	 
	}  	    	   	 	 	    	   	 	  
}



