#ifndef __GBK_H_
#define __GBK_H_
#include "sys.h"

//字库区域占用的总扇区数大小(3个字库+unigbk表+字库信息=3238700字节,约占791个W25QXX扇区)
#define FONTSECSIZE	 	791
//字库存放起始地址 1Byte(字节)=8Bit(位)1KB=1024Byte 1MB=1024KB 1GB=1024MB=1024*1024KB=1024*1024*1024Byte
#define FONTINFOADDR 	1024*1024*4 //从4M地址以后开始存放字库
																	//前面4M被fatfs占用了
																	//4M以后紧跟3个字库+UNIGBK.BIN,总大小3.09M,被字库占用了,不能动!
																	//7.10M以后,用户可以自由使用.建议用最后的100K字节比较好.					
																	

//字库信息结构体定义
//用来保存字库基本信息，地址，大小等
__packed typedef struct 
{
	u8 fontok;				//字库存在标志，0XAA，字库正常；其他，字库不存在
	u32 ugbkaddr; 			//unigbk的地址
	u32 ugbksize;			//unigbk的大小	 
	u32 f12addr;			//gbk12地址	
	u32 gbk12size;			//gbk12的大小	 
	u32 f16addr;			//gbk16地址
	u32 gbk16size;			//gbk16的大小		 
	u32 f24addr;			//gbk24地址
	u32 gkb24size;			//gbk24的大小 
}_font_info; 
extern _font_info ftinfo;	//字库信息结构体

void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size);
u8 font_init(void);
#endif


