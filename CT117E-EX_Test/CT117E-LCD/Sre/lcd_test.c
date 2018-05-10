	
#include "lcd.h"
#include "stm32f10x.h"
void lcd_test(void)
{



	LCD_DrawLine(120,0,320,Horizontal);
	LCD_DrawLine(0,160,240,Vertical);
	Delay_Ms(1000);
	LCD_Clear(Blue);

	LCD_DrawRect(70,210,100,100);
	Delay_Ms(1000);
	LCD_Clear(Blue);

	LCD_DrawCircle(120,160,50);
	Delay_Ms(1000);

	LCD_Clear(Blue);
	LCD_DisplayStringLine(Line4 ,(unsigned char *)"    Hello,world.   ");
	Delay_Ms(1000);

	LCD_SetBackColor(White);
	LCD_DisplayStringLine(Line0,(unsigned char *)"                    ");	
	LCD_SetBackColor(Black);
	LCD_DisplayStringLine(Line1,(unsigned char *)"                    ");	
	LCD_SetBackColor(Grey);
	LCD_DisplayStringLine(Line2,(unsigned char *)"                    ");
	LCD_SetBackColor(Blue);
	LCD_DisplayStringLine(Line3,(unsigned char *)"                    ");
	LCD_SetBackColor(Blue2);
	LCD_DisplayStringLine(Line4,(unsigned char *)"                    ");
	LCD_SetBackColor(Red);						
	LCD_DisplayStringLine(Line5,(unsigned char *)"                    ");
	LCD_SetBackColor(Magenta);	
	LCD_DisplayStringLine(Line6,(unsigned char *)"                    ");
	LCD_SetBackColor(Green);	
	LCD_DisplayStringLine(Line7,(unsigned char *)"                    ");	
	LCD_SetBackColor(Cyan);	
	LCD_DisplayStringLine(Line8,(unsigned char *)"                    ");
	LCD_SetBackColor(Yellow);		
	LCD_DisplayStringLine(Line9,(unsigned char *)"                    ");	
	}