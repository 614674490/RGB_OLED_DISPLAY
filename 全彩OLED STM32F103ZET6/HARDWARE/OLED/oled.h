#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	  
#include "color.h"
//  ����˵��
//	SCL	->	PB0/PB9		<-	WR
//	SDA	->	PB1/PB10	<-	RD
//	CS	->	PB6
//	D/C	->	PB7
//	RES	->	PB8
//OLEDģʽ����
//0: 4�ߴ���ģʽ  ��ģ���BS1��BS2����GND��
//1: ����8080ģʽ ��ģ���BS1��BS2����VCC��
#define OLED_MODE 0

#define Max_Column	0x5f			// 0-95
#define Max_Row			0x3f			// 0-63
#define Max_Width 	96		
#define Max_Height  64		
#define	Brightness	0x0F			  
//-----------------OLED�˿ڶ���----------------  					   

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_6);	//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_6)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_15)	//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOG,GPIO_Pin_15)

#define OLED_RS_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_3)	//DC
#define OLED_RS_Set() GPIO_SetBits(GPIOD,GPIO_Pin_3)

#define OLED_WR_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_14)
#define OLED_WR_Set() GPIO_SetBits(GPIOG,GPIO_Pin_14)

#define OLED_RD_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_13)
#define OLED_RD_Set() GPIO_SetBits(GPIOG,GPIO_Pin_13)



//PC0~7,��Ϊ������
#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
//ʹ��4�ߴ��нӿ�ʱʹ�� 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_0)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_0)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_1)	//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_1)



  
//ʹ��4�ߴ��нӿ�ʱʹ�� 
  
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//���Ժ���
void Clock_Test(void);
//OLED�����ú���
void ssd1331_set_color(ColorType Color);
void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, ColorType hwColor) ;
void ssd1331_clear_screen(ColorType Color);
void ssd1331_fill_black(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2,ColorType Color);
void ssd1331_copy(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 ,uint16_t _usY2,uint16_t _usX3 , uint16_t _usY3);
void ssd1331_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , ColorType _ucColor);
void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, ColorType hwColor);
void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, ColorType hwColor);
void ssd1331_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, ColorType _ucColor);
void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, ColorType hwColor,uint8_t mode);
void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode);
void ssd1331_display_sentence_screen_center(uint16_t Width,uint16_t Height,uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode);
void ssd1331_display_Chinese_Index(uint8_t chXpos, uint8_t chYpos, uint8_t no, ColorType hwColor);
void ssd1331_display_Chinese_Font(u16 x,u16 y,u8 *font,u8 size,ColorType color,u8 mode);
void ssd1331_display_sentence(u16 x,u16 y,u8*str,u8 size,ColorType color,uint8_t mode);
u32 ssd1331_pow(u8 m,u8 n);
void ssd1331_display_number(u8 x,u8 y,u32 num,u8 len,u8 size,ColorType Color,uint8_t mode);
void ssd1331_draw_bitmap(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos, ColorType hwColor);
void ssd1331_DrawRectangle(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2, ColorType _lineColor,ColorType _areaColor);
void ssd1331_draw_64Kpattern(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos);
void ssd1331_vertical_scroll(uint8_t scrollingDirection, uint8_t row_perStep, uint16_t timeStepms);
void OLED_Init(void);

#endif  
	 



