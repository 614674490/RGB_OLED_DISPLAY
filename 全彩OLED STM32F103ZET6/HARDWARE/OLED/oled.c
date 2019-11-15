#include "oled.h"
#include "delay.h"
#include "string.h"
#include "W25Q64.h"
#include "oled_display.h"
void Clock_Test(void)
{
	ssd1331_display_Chinese_Index(16*0,0,0,MediumOrchid);
	ssd1331_display_Chinese_Index(16*1,0,1,MediumOrchid);
	ssd1331_display_Chinese_Index(16*2,0,2,MediumOrchid);
	ssd1331_display_Chinese_Index(16*3,0,3,MediumOrchid);
	ssd1331_display_Chinese_Index(16*4,0,4,MediumOrchid);
	ssd1331_display_Chinese_Index(16*5,0,5,MediumOrchid);
	ssd1331_draw_64Kpattern(gImage_hebust_40x39,27,23);
	delay_ms(3000);
	Clear_Screen;
	
	ssd1331_display_sentence_screen_center(Max_Width,12,(uint8_t *)("汉字显示测试"),FONT_1206,RosyBrown,DisOverlay_Display);
	ssd1331_display_sentence_screen_center(Max_Width,Max_Height-12,(uint8_t *)("又双叒叕\n火炎焱燚\n土圭垚\n金鍂鑫 "),FONT_1206,Cyan,DisOverlay_Display);
	delay_ms(3000);
	Clear_Screen;
	
	ssd1331_draw_bitmap(c_chSingal_8x16,	0 , 2, Yellow);
	ssd1331_draw_bitmap(c_chMsg_8x16,			19, 2, Yellow);
	ssd1331_draw_bitmap(c_chBluetooth_8x8,38, 2, Yellow);
	ssd1331_draw_bitmap(c_chGPRS_8x8,			52, 2, Yellow);
	ssd1331_draw_bitmap(c_chAlarm_8x8,		66, 2, Yellow);
	ssd1331_draw_bitmap(c_chBat_8x16,			 80, 2, Yellow);

	ssd1331_display_char(8,16, '2',FONT_3216, Blue,DisOverlay_Display);
	ssd1331_display_char(24,16, '3',FONT_3216, Blue,DisOverlay_Display);
	ssd1331_display_char(40,16, ':',FONT_3216, Red,DisOverlay_Display);
	ssd1331_display_char(56,16, '5',FONT_3216, Blue,DisOverlay_Display);
	ssd1331_display_char(72,16, '6',FONT_3216, Blue,DisOverlay_Display);

	ssd1331_display_sentence(9, 48, (uint8_t*)("2019-11-13"), FONT_1608, Brown,DisOverlay_Display);
}
/**
 *	上色
 *	再次输入第三个色无效
**/
void ssd1331_set_color(ColorType Color)
{
	Write_Data(Color>>8); //RRRRRGGG
	Write_Data(Color);		//GGGBBBBB
}
/*
********************************************************************************
*	函 数 名: ssd1331_draw_point
*	功能说明: 在指定位置画1个像素点
*	形    参:
*	chXpos,chYpos : 像素坐标
*	hwColor  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, ColorType hwColor) 
{
	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
  //set column point
  Set_Column_Address(chXpos,chXpos);	//设置起始和结束COLUMN地址
  //set row point
  Set_Row_Address(chYpos,chYpos);			//这个指令设置起始和结束ROW地址
  //fill 16bit colour
	ssd1331_set_color(hwColor);
}
/*
********************************************************************************
*	函 数 名: ssd1331_clear_screen
*	功能说明: 指定颜色清屏
*	形    参:
*	Color  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_clear_screen(ColorType Color)  
{
	Fill_RAM(Color>>8,Color);
}
/*
********************************************************************************
*	函 数 名: ssd1331_clear_screen
*	功能说明: 块填充
*	形    参:
*	Color  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_fill_black(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2,ColorType Color)  
{
	Fill_Block(_usX1,_usX2,_usY1,_usY2,Color>>8,Color);
}
/*
********************************************************************************
*	函 数 名: ssd1331_clear_screen
*	功能说明: 块复制
*	形    参:
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_copy(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 ,uint16_t _usY2,uint16_t _usX3 , uint16_t _usY3) 
{
	copy(_usX1,_usY1,_usX2,_usY2,_usX3,_usY3);
}
/*
********************************************************************************
*	函 数 名: ssd1331_DrawLine
*	功能说明: 采用 Bresenham 算法，在2点间画一条直线。
*	形    参:
*	_usX1, _usY1 ：起始点坐标
*	_usX2, _usY2 ：终止点Y坐标
*	_ucColor  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , ColorType _ucColor)
{
	int32_t dx , dy ;
	int32_t tx , ty ;
	int32_t inc1 , inc2 ;
	int32_t d , iTag ;
	int32_t x , y ;

	/* 采用 Bresenham 算法，在2点间画一条直线 */

	ssd1331_draw_point(_usX1 , _usY1 , _ucColor);

	/* 如果两点重合，结束后面的动作。*/
	if ( _usX1 == _usX2 && _usY1 == _usY2 )
	{
		return;
	}

	iTag = 0 ;
	/* dx = abs ( _usX2 - _usX1 ); */
	if (_usX2 >= _usX1)
	{
		dx = _usX2 - _usX1;
	}
	else
	{
		dx = _usX1 - _usX2;
	}

	/* dy = abs ( _usY2 - _usY1 ); */
	if (_usY2 >= _usY1)
	{
		dy = _usY2 - _usY1;
	}
	else
	{
		dy = _usY1 - _usY2;
	}

	if ( dx < dy )   /*如果dy为计长方向，则交换纵横坐标。*/
	{
		uint16_t temp;
		iTag = 1 ;
		temp = _usX1; _usX1 = _usY1; _usY1 = temp;
		temp = _usX2; _usX2 = _usY2; _usY2 = temp;
		temp = dx; dx = dy; dy = temp;
	}
	tx = _usX2 > _usX1 ? 1 : -1 ;    /* 确定是增1还是减1 */
	ty = _usY2 > _usY1 ? 1 : -1 ;
	x = _usX1 ;
	y = _usY1 ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while ( x != _usX2 )     /* 循环画点 */
	{
		if ( d < 0 )
		{
			d += inc1 ;
		}
		else
		{
			y += ty ;
			d += inc2 ;
		}
		if ( iTag )
		{
			ssd1331_draw_point ( y , x , _ucColor) ;
		}
		else
		{
			ssd1331_draw_point ( x , y , _ucColor) ;
		}
		x += tx ;
	}
}
//画竖线
void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, ColorType hwColor)
{	
	uint16_t i, y1 = MIN(chYpos + chHeight, Max_Row - 1);

	if (chXpos >= Max_Column || chYpos >= Max_Row) {
		return;
	}
	
    for (i = chYpos; i < y1; i ++) {
        ssd1331_draw_point(chXpos, i, hwColor);
    }
}
//画横线
void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, ColorType hwColor)
{	
	uint16_t i, x1 = MIN(chXpos + chWidth, Max_Column- 1);

	if (chXpos >= Max_Column || chYpos >= Max_Row) {
		return;
	}
	
    for (i = chXpos; i < x1; i ++) {
        ssd1331_draw_point(i, chYpos, hwColor);
    }
}
/*
********************************************************************************
*	函 数 名: ssd1331_DrawRectangle
*	功能说明: 绘制一个矩形(可填充)
*	形    参:
*	_usX, _usY ：圆心坐标
*	_usRadius ：半径
*	_ucColor  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_DrawRectangle(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2, ColorType _lineColor,ColorType _areaColor)
{
	Draw_Rectangle(_usX1,_usY1,_usX2,_usY2,_lineColor>>11,_lineColor>>5&0x1f,_lineColor&0x1f,_areaColor>>11,_areaColor>>5&0x1f,_areaColor&0x1f);
}
/*
********************************************************************************
*	函 数 名: ssd1331_DrawCircle
*	功能说明: 绘制一个圆。
*	形    参:
*	_usX, _usY ：圆心坐标
*	_usRadius ：半径
*	_ucColor  ：像素颜色
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, ColorType _ucColor)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;	/* 当前 X 值 */
	uint32_t  CurY;	/* 当前 Y 值 */
	
	D = 3 - (_usRadius << 1);
	CurX = 0;
	CurY = _usRadius;
	
	while (CurX <= CurY)
	{
		ssd1331_draw_point(_usX + CurX, _usY + CurY, _ucColor);
		ssd1331_draw_point(_usX + CurX, _usY - CurY, _ucColor);
		ssd1331_draw_point(_usX - CurX, _usY + CurY, _ucColor);
		ssd1331_draw_point(_usX - CurX, _usY - CurY, _ucColor);
		ssd1331_draw_point(_usX + CurY, _usY + CurX, _ucColor);
		ssd1331_draw_point(_usX + CurY, _usY - CurX, _ucColor);
		ssd1331_draw_point(_usX - CurY, _usY + CurX, _ucColor);
		ssd1331_draw_point(_usX - CurY, _usY - CurX, _ucColor);
	
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
/*
********************************************************************************
*	函 数 名: ssd1331_display_char
*	功能说明: 显示一个字符
*	形    参:
*	chXpos, chXpos ：起点坐标(左上)
*	chChr  ：字符
*	chSize ：字符大小
*	hwColor：像素颜色
* mode   ：1:叠加方式 0:非叠加方式
*	返 回 值: 无
********************************************************************************
*/
void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, ColorType hwColor,uint8_t mode)
{       
	uint8_t i, j, chSize1;
	uint8_t chYpos0 = chYpos; //记录起始行
	unsigned char *PtrData=NULL,chTemp;

	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
	switch (chSize)
	{
		case FONT_1206 :
		{
			PtrData = &oled_asc2_1206[chChr - 0x20][0]; 
			chSize1= chSize;	
			break;
		}
		case FONT_1608 :
		{
			PtrData = &oled_asc2_1608[chChr - 0x20][0]; 
			chSize1= chSize;	
			break;
		}
		case FONT_2412 :
		{
			PtrData = &oled_asc2_2412[chChr - 0x20][0]; 
			chSize1= chSize;	
			break;
		}
		case FONT_1612 :
		{
			PtrData = &oled_asc2_1612[chChr - 0x30][0]; 
			chSize1= 16;	
			break;
		}
		case FONT_3216 :
		{
			PtrData = &oled_asc2_3216[chChr - 0x30][0]; 
			chSize1= 32;	
			break;
		}
	}
//				第j列
//        --------------->| 第i行	
//        --------------->|	
//        --------------->|	
//              .				  .	
//         		  .				  .	
//         			.				  .	
//        --------------->|	
//                        ∨	
//          	
	PtrData--;
  for (i = 0; i < chSize; i ++) //以行为单位 遍历所有列												
	{			                                                                
		PtrData++;    
		chTemp = *PtrData;		
    for (j = 0; j < 8*sizeof(char); j ++)//每个码值占8bit 遍历0x__            
		{ 
			if (chTemp& 0x80)                                                
			{                                                                     
				ssd1331_draw_point(chXpos, chYpos, hwColor);                        
			}           
			else if(mode==0)
				ssd1331_draw_point(chXpos,chYpos,Black);
			chTemp <<= 1; //高位在前 低位在后 码值不断左移来进行当前列的遍历显示    
			chYpos ++;    //行累加 每一位遍历完之后都会占用OLED的1个像素点
			
			if ((chYpos - chYpos0) == chSize1) //每列chSize行 第n列遍历完毕
			{
				chYpos = chYpos0; //行值恢复初值
				chXpos ++;				//列数+1 
				break;						//退出当前列扫描循环 开始进行下一列扫描 此句执行次数仅有chSize决定 与子循环次数无关
			}
			
		}  	 
  } 
}
/* 显示字符串 */
void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode)
{
	uint8_t chXpos0=chXpos;
	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
  while (*pchString != '\0') 
	{
		if (chXpos > (Max_Column - chSize / 2)) 
		{
			chXpos = 0;
			chYpos += chSize;
			if (chYpos > (Max_Row - chSize)) //更换到下一页
			{
				chYpos = chXpos = 0;
				Clear_Screen;
			}
		}
		if(*pchString=='\n')//换行符号
	  {         
	    chYpos+=chSize;
			chXpos=chXpos0;
		  pchString++; 
	  }
		else
		{
			ssd1331_display_char(chXpos, chYpos, *pchString, chSize, hwColor,mode);
			pchString ++; 
			chXpos += chSize / 2;
		}
	} 
}
//在屏幕正中央显示字符串 仅针对ACSII码
void ssd1331_display_sentence_screen_center(uint16_t Width,uint16_t Height,uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode)
{
	uint8_t chYpos,chXpos;
	uint16_t length = strlen((char *)(pchString))*(chSize/2);
	uint16_t height = chSize;
	if(length<Width)  //总长度不会超过屏幕宽度
	{
		chYpos = (Height-height)/2;
		chXpos = (Width - length)/2;
		ssd1331_display_sentence(chXpos,chYpos,pchString,chSize,hwColor,mode);
	}
	else
	{
		if((length)%(Width))
			height=(length)/(Width)*chSize+chSize;
		else
			height=(length)/(Width)*chSize;
		chXpos=0;
		chYpos = (Height - height)/2;
		ssd1331_display_sentence(chXpos,chYpos,pchString,chSize,hwColor,mode);
	}
}

/* 显示单个中文 按索引显示 */
void ssd1331_display_Chinese_Index(uint8_t chXpos, uint8_t chYpos, uint8_t no, ColorType hwColor)
{
	uint8_t i, j;
	uint8_t Temp = 0, chYpos0 = chYpos;

	for (i = 0; i < 32; i ++) 
	{
		Temp = CHINESE[no][i];
		for (j = 0; j < 8; j ++) 
		{
			if (Temp & 0x80) 
			{
				ssd1331_draw_point(chXpos, chYpos, hwColor);
			}
			Temp <<= 1;
			chYpos ++;
			if ((chYpos - chYpos0) == 16) 
			{
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}
//按字库偏移值显示一个指定大小的汉字
//x,y :汉字的坐标
//font:汉字GBK码
//size:字体大小
//mode:0,正常显示,1,叠加显示	   
void ssd1331_display_Chinese_Font(u16 x,u16 y,u8 *font,u8 size,ColorType color,u8 mode)
{
	u8 temp,t,t1;
	u16 y0=y;
	u8 dzk[72];   
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	if(size!=12&&size!=16&&size!=24)
		return;	//不支持的size
	Get_HzMat(font,dzk,size);	//得到相应大小的点阵数据 
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];			//得到点阵数据                          
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
				ssd1331_draw_point(x,y,color);
			else if(mode==0)
				ssd1331_draw_point(x,y,Black); 
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}
/**在指定位置开始显示一个字符串(包含汉字和英文)	    
  *支持自动换行
  *(x,y):起始坐标
  *width,height:区域
  *str  :字符串
  *size :字体大小
  *color:字体颜色  	
  *mode :是否叠加sentece
**/
void ssd1331_display_sentence(u16 x,u16 y,u8*str,u8 size,ColorType color,uint8_t mode)
{
	u16 x0=x;					  	  
  u8 bHz=0;     //字符或者中文
  while(*str!=0)//数据未结束
  { 	
    if(!bHz)
    {
	    if(*str>0x80)
				bHz=1;//中文 
	    else              //字符
	    {      
        if (x > (Max_Column - size / 2)) 
				{
					x = 0;
					y += size;
					if (y > (Max_Row - size))
					{
						y = x = 0;
						Clear_Screen;
					}
				}   
	      if(*str=='\n')//换行符号
	      {         
	        y+=size;
					x=x0;
	        str++; 
	      }  
	      else 
				{
					ssd1331_display_char(x,y,*str,size,color,mode);//有效部分写入 
					str++; 
					x+=size/2; //字符,为全字的一半 
				}	
	    }
    } 
	  else//中文 
    {     
      bHz=0;//有汉字库
			if (x > (Max_Column - size)) 
			{
				x = 0;
				y += size;
				if (y > (Max_Row - size))
				{
					y = x = 0;
					Clear_Screen;
				}
			}   						     
	    ssd1331_display_Chinese_Font(x,y,str,size,color,mode); //显示这个汉字,空心显示 
	    str+=2; 
	    x+=size;//下一个汉字偏移	    
    }						 
  }   
} 
//m^n函数
u32 ssd1331_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/** 显示2个数字
 *x,y :起点坐标	 
 *len :数字的位数
 *size:字体大小
 *mode:模式	0,填充模式;1,叠加模式
 *num:数值(0~4294967295);
**/
void ssd1331_display_number(u8 x,u8 y,u32 num,u8 len,u8 size,ColorType Color,uint8_t mode)
{
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/ssd1331_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				ssd1331_display_char(x+(size/2)*t,y,' ',size,Color,mode);
				continue;
			}else enshow=1; 
		 	 
		}
	 	ssd1331_display_char(x+(size/2)*t,y,temp+'0',size,Color,mode); 
	}
} 
/*
********************************************************************************
*	函 数 名: ssd1331_draw_bitmap
*	功能说明: 在指定位置画一个图片 显示黑白图 颜色自定义
*	形    参:
*	chXpos,chYpos : 像素坐标
*	pchBmp：像素指针
*	chWidth,chHeight：图片大小
*	hwColor  ：像素颜色
*	返 回 值: 无
* 说    明：取模软件采用pctolcd2002，图片大小就是新建图片时图片的宽度和高度
*	取模方式：逐行式，顺向
********************************************************************************
*/
void ssd1331_draw_bitmap(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos, ColorType hwColor)
{
	uint16_t chWidth = *pchBmp;
	uint16_t chHeight = *(pchBmp+1);
	uint8_t *pchTemp = pchBmp+2;
	uint16_t i, j, byteWidth = (chWidth + 7) / 8;

  for(j = 0; j < chHeight; j ++)
	{
    for(i = 0; i < chWidth; i ++ ) 
		{
			if(*(pchTemp + j * byteWidth + i / 8) & (128 >> (i & 7))) /* 用于判断字模中哪些位是1，就用相应颜色点亮 */
			{
				ssd1331_draw_point(chXpos + i, chYpos + j, hwColor);
      }
    }
  }
}
//显示原图
void ssd1331_draw_64Kpattern(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos)
{
	Show_64k_Pattern(pchBmp+2,chXpos,chXpos+(*pchBmp)-1,chYpos,chYpos+(*(pchBmp+1))-1);
}
void ssd1331_vertical_scroll(uint8_t scrollingDirection, uint8_t row_perStep, uint16_t timeStepms)
{
	Vertical_Scroll(scrollingDirection,row_perStep,timeStepms);
}

void OLED_Init()
{
unsigned char i;


 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);	 //??PC,D,G????

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6;	 //PD3,PD6????  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//??50MHz
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	  //???GPIOD3,6
 	GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_6);	//PD3,PD6 ???

 #if OLED_MODE==1
 
 	GPIO_InitStructure.GPIO_Pin =0xFF; //PC0~7 OUT????
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,0xFF); //PC0~7???

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //PG13,14,15 OUT????
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOG,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PG13,14,15 OUT  ???

 #else
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //PC0,1 OUT????
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);						 //PC0,1 OUT  ???

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //PG15 OUT????	  RST
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOG,GPIO_Pin_15);						 //PG15 OUT  ???


 #endif
	OLED_RST_Clr();
	for(i=0;i<250;i++)
	{
		uOLED_Delay(250);
	}
	OLED_RST_Set();
  Set_Display_On_Off(0x00);		    													// Display Off (0x00/0x01)
	Set_Remap_Format(0x72);																		// Set Horizontal Address Increment  0x72(rgb)0x74(bgr)
	Set_Start_Line(0x00);			           										 	// Set Mapping RAM Display Start Line (0x00~0x3F)
	Set_Display_Offset(0x00);		            									// Shift Mapping RAM Counter (0x00~0x7F)
	Set_Display_Mode(0x00);			       			 									// Normal Display Mode (0x00/0x01/0x02/0x03)
	Set_Multiplex_Ratio(0x3F);		            								// 1/128 Duty (0x0F~0x7F)
	Set_Master_Configuration(0x8e);            								// set master configuration
	Set_Power_Saving_Mode(0x0b);              	 							// set power save
	Set_Reset_Pre_charge_period(0x31);         								// phase 1 and 2 period adjustment
	Set_Oscillator_Frequency_Clock_Divider(0xf0);							// display clock divider / oscillator frequency
	Set_Second_Pre_charge_Speed_of_Color(0x64, 0x78, 0x64);		// Set Second Pre-change Speed For Color
	Set_Pre_charge_Level(0x3a);                								// Set Pre-Change Level
	Set_VCOMH(0x3e);			               											// Set Common Pins Deselect Voltage Level as 0.82*VCC
	Set_Master_Current(0x06);	        												// Set Scale Factor of Segment Output Current Control	 Brightness
  Set_Contrast_Color(0x91,0x50,0x7d);												// Set Contrast of Color A (Red) B (Green) C (Blue)	                 
  Set_Display_On_Off(0x01);		        											// Display On (0x00/0x01)
	Fill_Enable_Disable(1);																		// Enable Fill	
	Fill_RAM(0x00,0x00);			        												// Clear Screen
	W25QXX_Init();
	if(W25QXX_TYPE!=W25Q64&&W25QXX_TYPE!=W25Q128&&W25QXX_TYPE!=W25Q32&&W25QXX_TYPE!=W25Q16&&W25QXX_TYPE!=W25Q80)
	{
		ssd1331_display_sentence_screen_center(Max_Width,Max_Height,(uint8_t*)("Not Found W25QXX!"),FONT_1206,Red,DisOverlay_Display);
	}
	else if(font_init())
		ssd1331_display_sentence_screen_center(Max_Width,Max_Height,(uint8_t*)("Not Found Font!"),FONT_1206,Red,DisOverlay_Display);
	else
		ssd1331_display_sentence_screen_center(Max_Width,Max_Height,(uint8_t*)("Loading font successfully"),FONT_1206,Green,DisOverlay_Display);
	delay_ms(5000);
	Fill_RAM(0x00,0x00);			        												// Clear Screen
}

